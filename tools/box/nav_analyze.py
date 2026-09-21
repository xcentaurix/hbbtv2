#!/usr/bin/env python3
"""Analysis of a navigation benchmark trace (tools/box/nav_bench.sh, docs/performance-plan.txt phase 0).

    nav_analyze.py /tmp/nav_<label>.log             full report of one run
    nav_analyze.py --compare log1 log2 ...          the summary metrics of several runs side by side

Input: the "T <us> ..." lines of wpe_fb --trace (keys, frames, acks, marks) and the "[shm-readback] ..." lines the web process writes
with WEBKIT_SHM_READBACK_LOG=1. Each read-back line is matched to the next frame line in file order (both processes share the log).
Next to the log, nav_<label>.thr0 / .thr1 hold per-thread CPU ticks of the web process before/after the steps and .thr1 the RSS.
"""
import os
import re
import statistics
import sys

TRACE = re.compile(r"^T (\d+) (\S+)\s*(.*)$")
FRAME = re.compile(r"frame (\d+) rects=(\d+) px=(\d+) blit_ms=([\d.]+)")
READBACK = re.compile(r"\[shm-readback\]\s+(partial|full):\s+(\d+)\s+rect\(s\),\s+(\d+)\s+px\s+\(([\d.]+)%[^)]*\),\s+([\d.]+)\s+ms")
KV = re.compile(r"(\w+)=([\d.]+)")
IDLE = re.compile(r"idle(-timeout)? after=(\d+)s frames=(\d+)")
HZ = 100.0  # USER_HZ: /proc/<pid>/stat ticks per second


def parse(path):
    frames, keys_in, keys_done, marks, cpu = [], [], [], [], []
    sends, uith, stalls, drops = [], [], [], []  # sends: (receipt ts, key, harness uptime s); uith: (up, {tid: (name, ticks user, system)}); stalls: (ts, ms)
    pending = []
    for line in open(path, errors="replace"):
        m = READBACK.search(line)
        if m:
            pending.append({"kind": m.group(1), "rects": int(m.group(2)), "px": int(m.group(3)), "pct": float(m.group(4)), "ms": float(m.group(5))})
            continue
        m = TRACE.match(line)
        if not m:
            continue
        ts, kind, rest = int(m.group(1)), m.group(2), m.group(3).strip()
        if kind == "frame":
            f = FRAME.search("frame " + rest)
            if f:
                frames.append({"ts": ts, "n": int(f.group(1)), "rects": int(f.group(2)), "px": int(f.group(3)), "blit": float(f.group(4)),
                               "rb": pending.pop(0) if pending else None})
        elif kind == "key-in":
            keys_in.append((ts, rest))
        elif kind == "key-done":
            keys_done.append((ts, rest))
        elif kind == "key-drop":  # an auto-repeat that wpe_fb did not pass on (the page was still answering the previous key)
            drops.append((ts, rest))
        elif kind == "loop-late":
            stalls.append((ts, float(rest.split()[0])))
        elif kind == "mark":
            if rest.startswith("cpu "):
                d = {k: float(v) for k, v in KV.findall(rest)}
                d["ts"] = ts
                for k in ("ui", "web", "net", "rx"):
                    d[k] = int(d.get(k, 0))
                cpu.append(d)
            elif rest.startswith("uith "):
                th = {}
                for item in rest.split()[1:]:
                    parts = item.split(":")
                    if len(parts) == 3 and "/" in parts[2]:
                        u, sy = parts[2].split("/")
                        th[parts[0]] = (parts[1], int(u), int(sy))
                uith.append((cpu[-1].get("up") if cpu else None, th))
            elif rest.startswith("send "):
                _, key, up = rest.split()
                sends.append((ts, key, float(up)))
            else:
                marks.append((ts, rest))
    offset = None  # trace clock (monotonic us) minus harness clock (uptime us): the smallest receipt delay of any stamped line
    cands = [c["ts"] - c["up"] * 1e6 for c in cpu if "up" in c] + [t - up * 1e6 for t, _, up in sends]
    if cands:
        offset = min(cands)
    return {"frames": frames, "keys_in": keys_in, "keys_done": keys_done, "marks": marks, "cpu": cpu, "sends": sends, "uith": uith, "stalls": stalls, "drops": drops, "offset": offset}


def send_us(run, mark_ts, key):
    """Trace-clock time at which the harness sent `key` (the first 'send' mark for it received at or after mark_ts), or None."""
    if run["offset"] is None:
        return None
    for ts, k, up in run["sends"]:
        if ts >= mark_ts and k == key:
            return up * 1e6 + run["offset"]
    return None


def med(values):
    values = [v for v in values if v is not None]
    return statistics.median(values) if values else None


def pct(values, p):
    values = sorted(v for v in values if v is not None)
    if not values:
        return None
    return values[min(len(values) - 1, int(round(p / 100.0 * (len(values) - 1))))]


def fmt(v, digits=0, unit=""):
    if v is None:
        return "-"
    return ("%.*f" % (digits, v)) + unit


def fit_readback(frames):
    """Least squares ms = a + b*px + c*rects over the frames that have a read-back record."""
    rows = [(1.0, f["rb"]["px"] / 1e6, float(f["rb"]["rects"]), f["rb"]["ms"]) for f in frames if f["rb"]]
    if len(rows) < 8:
        return None
    n = 3
    a = [[sum(r[i] * r[j] for r in rows) for j in range(n)] for i in range(n)]
    b = [sum(r[i] * r[3] for r in rows) for i in range(n)]
    for i in range(n):  # Gaussian elimination
        p = max(range(i, n), key=lambda r: abs(a[r][i]))
        if abs(a[p][i]) < 1e-12:
            return None
        a[i], a[p], b[i], b[p] = a[p], a[i], b[p], b[i]
        for r in range(i + 1, n):
            k = a[r][i] / a[i][i]
            for c in range(i, n):
                a[r][c] -= k * a[i][c]
            b[r] -= k * b[i]
    x = [0.0] * n
    for i in reversed(range(n)):
        x[i] = (b[i] - sum(a[i][j] * x[j] for j in range(i + 1, n))) / a[i][i]
    return {"fixed_ms": x[0], "ms_per_mpx": x[1], "ms_per_rect": x[2], "n": len(rows)}


def phases(run):
    """[(name, t0, t1)] from the 'phase X' marks; the last one ends at the 'end' mark."""
    pts = [(ts, txt.split(None, 1)[1]) for ts, txt in run["marks"] if txt.startswith("phase ")]
    end = next((ts for ts, txt in run["marks"] if txt == "end"), run["frames"][-1]["ts"] if run["frames"] else 0)
    out = []
    for i, (ts, name) in enumerate(pts):
        out.append((name, ts, pts[i + 1][0] if i + 1 < len(pts) else end))
    return out


def in_window(items, t0, t1):
    return [x for x in items if t0 <= x["ts"] < t1]


def cpu_pct(run, t0, t1, key):
    marks = [c for c in run["cpu"] if t0 <= c["ts"] <= t1]
    if len(marks) < 2:
        return None
    dt = (marks[-1]["ts"] - marks[0]["ts"]) / 1e6
    # sum of the positive steps: a process that exits (or is replaced) makes the summed counter fall, which is not negative work
    total = sum(max(0, b[key] - a[key]) for a, b in zip(marks, marks[1:]))
    return total / dt if dt > 0 else None  # ticks per second at HZ=100 = percent of one core


def duty(run, t0, t1):
    fr = in_window(run["frames"], t0, t1)
    return 100.0 * sum(f["rb"]["ms"] for f in fr if f["rb"]) / ((t1 - t0) / 1000.0) if t1 > t0 else None


def rx_mb(run, t0, t1):
    marks = [c for c in run["cpu"] if t0 <= c["ts"] <= t1]
    return (marks[-1]["rx"] - marks[0]["rx"]) / 1e6 if len(marks) >= 2 else None


def idle_of(run, phase_t0, phase_t1):
    for ts, txt in run["marks"]:
        if phase_t0 <= ts <= phase_t1 and txt.startswith("idle"):
            m = IDLE.match(txt)
            if m:
                return (None if m.group(1) else int(m.group(2)) - 4, int(m.group(3)))  # idle detection waits 4 s of quiet
    return (None, None)


def analyse(path):
    run = parse(path)
    r = {"path": path, "frames": run["frames"]}
    if not run["frames"]:
        return run, r
    view_px = None
    hdr = next((txt for ts, txt in run["marks"] if txt.startswith("run ")), "")
    r["header"] = hdr
    m = re.search(r"hidpi=([\d.]+)", hdr)
    hidpi = float(m.group(1)) if m else 1.5
    view_px = (1280 * hidpi) * (720 * hidpi)
    r["view_px"] = view_px

    ph = {name: (t0, t1) for name, t0, t1 in phases(run)}
    r["phases"] = ph

    # load phases
    for name in ("launch", "red"):
        if name in ph:
            t0, t1 = ph[name]
            fr = in_window(run["frames"], t0, t1)
            first = fr[0]["ts"] - t0 if fr else None
            idle_s, nfr = idle_of(run, t0, t1)
            r[name] = {"first_frame_ms": first / 1000 if first is not None else None, "idle_s": idle_s, "frames": len(fr),
                       "mpx": sum(f["px"] for f in fr) / 1e6, "rb_ms": sum(f["rb"]["ms"] for f in fr if f["rb"]), "rx_mb": rx_mb(run, t0, t1),
                       "duty": duty(run, t0, t1), "ui_cpu": cpu_pct(run, t0, t1, "ui")}

    # single steps
    steps = []
    smarks = [(ts, txt.split(None, 1)[1]) for ts, txt in run["marks"] if txt.startswith("step ")]
    end_steps = ph.get("burst", (None, None))[0] or (smarks[-1][0] + 2_000_000 if smarks else 0)
    for i, (mts, name) in enumerate(smarks):
        kin = next((ts for ts, k in run["keys_in"] if ts >= mts and k == name), None)
        if kin is None:
            continue
        kdone = next((ts for ts, k in run["keys_done"] if ts >= kin and k == name), None)
        wend = smarks[i + 1][0] if i + 1 < len(smarks) else end_steps
        snd = send_us(run, mts, name)
        origin = snd if snd is not None else kin  # the send time includes the time the key waited for wpe_fb's main loop
        fr = in_window(run["frames"], origin, wend)
        steps.append({"key": name, "latency_ms": (fr[0]["ts"] - origin) / 1000 if fr else None, "settle_ms": (fr[-1]["ts"] - origin) / 1000 if fr else None,
                      "queue_ms": (kin - snd) / 1000 if snd is not None else None, "frames": len(fr), "kpx": sum(f["px"] for f in fr) / 1e3, "rb_ms": sum(f["rb"]["ms"] for f in fr if f["rb"]),
                      "blit_ms": sum(f["blit"] for f in fr), "rects": sum(f["rects"] for f in fr),
                      "engine_ms": (kdone - kin) / 1000 if kdone else None})
    r["steps"] = steps
    if "steps" in ph:
        r["steps_duty"] = duty(run, ph["steps"][0], ph["steps"][1] if "burst" not in ph else ph["burst"][0])

    # burst = a held key
    if "burst" in ph:
        t0, t1 = ph["burst"]
        keys = [ts for ts, k in run["keys_in"] if t0 <= ts < t1]
        done = [ts for ts, k in run["keys_done"] if t0 <= ts < t1]
        fr = in_window(run["frames"], t0, t1)
        snds = [up * 1e6 + run["offset"] for ts, k, up in run["sends"] if t0 <= ts < t1 and k == "right"] if run["offset"] is not None else []
        queue = [(ki - sn) / 1000 for ki, sn in zip(keys, snds)]
        if keys:
            gaps = [(b - a) / 1000 for a, b in zip(snds or keys, (snds or keys)[1:])]
            r["burst"] = {"keys": len(keys), "frames": len(fr), "mpx": sum(f["px"] for f in fr) / 1e6,
                          "backlog_ms": (fr[-1]["ts"] - (snds[-1] if snds else keys[-1])) / 1000 if fr else None,
                          "queue_med_ms": med(queue), "queue_max_ms": max(queue) if queue else None,
                          "dropped": sum(1 for ts, _ in run["drops"] if t0 <= ts < t1),
                          "key_gap_ms": (statistics.mean(gaps) if gaps else None), "key_gap_max_ms": (max(gaps) if gaps else None),
                          "engine_ms": statistics.mean([(d - k) / 1000 for k, d in zip(keys, done)]) if done else None,
                          "rb_ms": sum(f["rb"]["ms"] for f in fr if f["rb"])}

    # page transition (OK, then BACK)
    for name in ("transition", "back"):
        if name in ph:
            t0, t1 = ph[name]
            kin = next((ts for ts, k in run["keys_in"] if ts >= t0), None)
            fr = in_window(run["frames"], kin, t1) if kin else []
            r[name] = {"duty": duty(run, kin or t0, t1),
                       "first_ms": (fr[0]["ts"] - kin) / 1000 if fr else None, "settle_ms": (fr[-1]["ts"] - kin) / 1000 if fr else None, "frames": len(fr),
                       "mpx": sum(f["px"] for f in fr) / 1e6, "rb_ms": sum(f["rb"]["ms"] for f in fr if f["rb"]),
                       "biggest_frame_pct": max((f["px"] for f in fr), default=0) * 100.0 / view_px}

    # read-back and blit over the whole run
    withrb = [f for f in run["frames"] if f["rb"]]
    r["rb_frames"] = len(withrb)
    r["rb_total_ms"] = sum(f["rb"]["ms"] for f in withrb)
    r["rb_total_mpx"] = sum(f["rb"]["px"] for f in withrb) / 1e6
    r["rb_fit"] = fit_readback(withrb)
    r["blit_ms_per_frame"] = statistics.mean(f["blit"] for f in run["frames"])
    r["blit_ns_per_px"] = (sum(f["blit"] for f in run["frames"]) * 1e6) / max(1, sum(f["px"] for f in run["frames"]))
    r["px_pct"] = [f["px"] * 100.0 / view_px for f in run["frames"]]
    r["full_frames"] = sum(1 for f in withrb if f["rb"]["kind"] == "full")
    return run, r


def thread_report(path):
    base = os.path.splitext(path)[0]
    out = []

    def load(p):
        d, extra = {}, []
        if not os.path.exists(p):
            return d, extra
        for line in open(p, errors="replace"):
            parts = line.split()
            if not parts:
                continue
            if parts[0] in ("rss", "mem"):
                extra.append(line.strip())
            elif len(parts) >= 2 and parts[-1].isdigit():
                name = " ".join(parts[:-1])
                d[name] = d.get(name, 0) + int(parts[-1])
        return d, extra

    t0, _ = load(base + ".thr0")
    t1, extra = load(base + ".thr1")
    if t0 and t1:
        diff = sorted(((t1[k] - t0.get(k, 0), k) for k in t1), reverse=True)
        out.append("web process threads, CPU ticks from the start of the steps to the end of the run (all web processes; a process started by a")
        out.append("cross-site navigation counts from its start; 100 ticks = 1 s of one core):")
        out += ["   %6d  %s" % d for d in diff[:8] if d[0] > 0]
    out += ["   " + e for e in extra]
    return out


def phase_of(run, ts):
    for name, t0, t1 in phases(run):
        if t0 <= ts < t1:
            return name
    return "?"


def stall_report(run, path):
    """Main loop stalls ("loop-late" lines of wpe_fb --trace): how many, and what the process did during the worst ones."""
    out = []
    st = run["stalls"]
    if not st:
        return ["main loop: no stalls over 150 ms recorded (--trace watchdog)"]
    off = run["offset"]
    out.append("main loop stalls over 150 ms: %d, together %.1f s, longest %.0f ms" % (len(st), sum(ms for _, ms in st) / 1000, max(ms for _, ms in st)))
    byphase = {}
    for ts, ms in st:
        byphase.setdefault(phase_of(run, ts), []).append(ms)
    out.append("   per phase: " + ", ".join("%s %d x (%.1f s)" % (k, len(v), sum(v) / 1000) for k, v in byphase.items()))
    samples = [(up * 1e6 + off, th) for up, th in run["uith"] if up is not None and off is not None]
    mainlog = []
    mp = os.path.splitext(path)[0] + ".main"
    if os.path.exists(mp) and off is not None:
        for line in open(mp, errors="replace"):
            f = line.split()
            if len(f) >= 4:
                try:
                    mainlog.append((float(f[0]) * 1e6 + off, f[1], int(f[2]), int(f[3]), f[4] if len(f) > 4 else "?"))
                except ValueError:
                    pass
    for ts, ms in sorted(st, key=lambda x: -x[1])[:5]:
        t1, t0 = ts, ts - ms * 1000
        out.append("   stall %.0f ms in phase %s (%s):" % (ms, phase_of(run, ts), "the trace clock"))
        before = [x for x in samples if x[0] <= t0]
        after = [x for x in samples if x[0] >= t1]
        if before and after:
            a, b = before[-1][1], after[0][1]
            dt = (after[0][0] - before[-1][0]) / 1e6
            diff = sorted(((b[t][1] - a.get(t, (0, 0, 0))[1] + b[t][2] - a.get(t, (0, 0, 0))[2], b[t][1] - a.get(t, (0, 0, 0))[1], b[t][2] - a.get(t, (0, 0, 0))[2], t, b[t][0]) for t in b), reverse=True)
            out.append("      wpe_fb threads over the %.1f s around it (ticks, user/system): %s" % (dt, ", ".join(
                "%s(%s) %d = %d/%d" % (d[4], d[3], d[0], d[1], d[2]) for d in diff[:4] if d[0] > 0) or "none busy"))
        if mainlog:
            win = [m for m in mainlog if t0 <= m[0] <= t1]
            if win:
                states = {}
                for m in win:
                    key = m[1] + (":" + m[4] if m[1] != "R" else "")
                    states[key] = states.get(key, 0) + 1
                out.append("      main thread, %d samples of 100 ms: %s; ticks user %+d system %+d" % (
                    len(win), ", ".join("%s x%d" % kv for kv in sorted(states.items(), key=lambda kv: -kv[1])[:4]), win[-1][2] - win[0][2], win[-1][3] - win[0][3]))
    return out


def report(path):
    run, r = analyse(path)
    if not run["frames"]:
        print("%s: no frames in the trace" % path)
        return
    p = print
    p("=" * 100)
    p(path)
    p(r.get("header", ""))
    p("frames delivered: %d (%d with a read-back record, %d full-frame reads); view = %.2f Mpx" % (len(run["frames"]), r["rb_frames"], r["full_frames"], r["view_px"] / 1e6))
    for name in ("launch", "red"):
        if name in r:
            x = r[name]
            p("phase %-7s first frame after %s ms, frames stopped after ~%s s; %d frames, %.1f Mpx, read-back %.0f ms (%s%% of the time); network %s MB" % (
                name, fmt(x["first_frame_ms"]), fmt(x["idle_s"]), x["frames"], x["mpx"], x["rb_ms"], fmt(x["duty"]), fmt(x["rx_mb"], 2)))
    if r.get("steps"):
        p("")
        p("single focus moves (key -> first frame at wpe_fb -> last frame):")
        p("   key     latency  settle  queued  frames  Kpx   read-back ms  blit ms  engine ms   (times from the harness's send)")
        for s in r["steps"]:
            p("   %-6s %7s %7s %7s %6d %6.0f %10.0f %9.1f %8s" % (s["key"], fmt(s["latency_ms"]), fmt(s["settle_ms"]), fmt(s["queue_ms"]), s["frames"], s["kpx"], s["rb_ms"], s["blit_ms"], fmt(s["engine_ms"], 1)))
        lat = [s["latency_ms"] for s in r["steps"]]
        p("   median latency %s ms (p90 %s), median settle %s ms, median frames/step %s, median %s Kpx/step, median read-back %s ms/step" % (
            fmt(med(lat)), fmt(pct(lat, 90)), fmt(med(s["settle_ms"] for s in r["steps"])), fmt(med(s["frames"] for s in r["steps"]), 1),
            fmt(med(s["kpx"] for s in r["steps"])), fmt(med(s["rb_ms"] for s in r["steps"]))))
        p("   the key waited a median of %s ms (max %s) before wpe_fb's main loop read it" % (fmt(med(s["queue_ms"] for s in r["steps"])), fmt(max((s["queue_ms"] for s in r["steps"] if s["queue_ms"] is not None), default=None))))
        if "steps_duty" in r:
            p("   during the steps the compositor was inside glReadPixels %s%% of the time" % fmt(r["steps_duty"]))
    if "burst" in r:
        b = r["burst"]
        p("")
        p("burst (10 keys, nominal 120 ms apart = a held key): %d passed on to the page, %d auto-repeats dropped; sent %.0f ms apart on average (max %.0f); the keys waited %s ms (max %s) for wpe_fb; engine per key %s ms" % (
            b["keys"], b["dropped"],
            b["key_gap_ms"] or 0, b["key_gap_max_ms"] or 0, fmt(b["queue_med_ms"]), fmt(b["queue_max_ms"]), fmt(b["engine_ms"], 1)))
        p("   %d frames, %.1f Mpx, read-back %.0f ms; last frame %s ms AFTER the last key (backlog: the page keeps moving after release)" % (
            b["frames"], b["mpx"], b["rb_ms"], fmt(b["backlog_ms"])))
    for name, label in (("transition", "OK (page transition)"), ("back", "BACK")):
        if name in r:
            x = r[name]
            p("%s: first frame after %s ms, last after %s ms; %d frames, %.1f Mpx, biggest frame %.0f%% of the view, read-back %.0f ms; read-back %s%% of the time" % (
                label, fmt(x["first_ms"]), fmt(x["settle_ms"]), x["frames"], x["mpx"], x["biggest_frame_pct"], x["rb_ms"], fmt(x["duty"])))
    p("")
    p("read-back over the run: %.1f Mpx in %.0f ms = %.1f MB/s effective" % (r["rb_total_mpx"], r["rb_total_ms"], (r["rb_total_mpx"] * 4) / (r["rb_total_ms"] / 1000) if r["rb_total_ms"] else 0))
    fit = r["rb_fit"]
    if fit:
        p("   model over %d frames: read-back ms = %.1f + %.1f * Mpx + %.2f * rects   (=> %.1f MB/s for the pixels; %.2f ms per rect = per glReadPixels call)" % (
            fit["n"], fit["fixed_ms"], fit["ms_per_mpx"], fit["ms_per_rect"], 4.0 / (fit["ms_per_mpx"] / 1000) if fit["ms_per_mpx"] > 0 else 0, fit["ms_per_rect"]))
    px = r["px_pct"]
    p("frame size: median %.1f%% of the view, p90 %.1f%%, max %.1f%%; %d of %d frames larger than 30%%" % (med(px), pct(px, 90), max(px), sum(1 for v in px if v > 30), len(px)))
    p("embedder blit (canvas copy only in headless mode - no conversion, no framebuffer): %.2f ms/frame, %.1f ns/px" % (r["blit_ms_per_frame"], r["blit_ns_per_px"]))
    p("")
    for line in stall_report(run, path):
        p(line)
    for line in thread_report(path):
        p(line)


def summary(path):
    run, r = analyse(path)
    if not run["frames"]:
        return None
    s = {}
    m = re.search(r"label=(\S+)", r.get("header", ""))
    s["label"] = m.group(1) if m else os.path.basename(path)
    for name in ("launch", "red"):
        if name in r:
            s[name + " idle s"] = r[name]["idle_s"]
            s[name + " MB"] = r[name]["rx_mb"]
            s[name + " rb duty%"] = r[name]["duty"]
    st_ = r.get("steps", [])
    s["step latency ms (med)"] = med(x["latency_ms"] for x in st_)
    s["key waited ms (med)"] = med(x["queue_ms"] for x in st_)
    s["step latency ms (p90)"] = pct([x["latency_ms"] for x in st_], 90)
    s["step settle ms (med)"] = med(x["settle_ms"] for x in st_)
    s["frames/step (med)"] = med(x["frames"] for x in st_)
    s["Kpx/step (med)"] = med(x["kpx"] for x in st_)
    s["read-back ms/step (med)"] = med(x["rb_ms"] for x in st_)
    if "steps_duty" in r:
        s["rb duty% in steps"] = r["steps_duty"]
    if "burst" in r:
        s["burst backlog ms"] = r["burst"]["backlog_ms"]
        s["burst keys passed"] = r["burst"]["keys"]
        s["burst key gap ms"] = r["burst"]["key_gap_ms"]
    if "transition" in r:
        s["OK first ms"] = r["transition"]["first_ms"]
        s["OK settle ms"] = r["transition"]["settle_ms"]
        s["OK Mpx"] = r["transition"]["mpx"]
        s["OK rb duty%"] = r["transition"]["duty"]
    s["loop stalls >150ms"] = len(run["stalls"])
    s["stall total s"] = sum(ms for _, ms in run["stalls"]) / 1000
    s["stall max ms"] = max((ms for _, ms in run["stalls"]), default=0)
    s["read-back MB/s"] = (r["rb_total_mpx"] * 4) / (r["rb_total_ms"] / 1000) if r["rb_total_ms"] else None
    if r["rb_fit"]:
        s["ms per rect"] = r["rb_fit"]["ms_per_rect"]
        s["fixed ms/frame"] = r["rb_fit"]["fixed_ms"]
    s["blit ms/frame"] = r["blit_ms_per_frame"]
    return s


def compare(paths):
    sums = [x for x in (summary(p) for p in paths) if x]
    keys = []
    for s in sums:
        for k in s:
            if k not in keys:
                keys.append(k)
    width = max(len(k) for k in keys) + 2
    for k in keys:
        cells = []
        for s in sums:
            v = s.get(k)
            cells.append(("%12s" % v) if isinstance(v, str) else ("%12s" % fmt(v, 1 if isinstance(v, float) and abs(v) < 100 else 0)))
        print(k.ljust(width) + "".join(cells))


if __name__ == "__main__":
    args = sys.argv[1:]
    if args and args[0] == "--compare":
        compare(args[1:])
    elif args:
        for a in args:
            report(a)
    else:
        print(__doc__)
