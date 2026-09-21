#!/usr/bin/env python3
"""Read the PMT and the AIT of a service straight from the DVB demux (a second section filter next to enigma2's own) and print what the AIT holds.
   usage: ait_probe.py <adapter> <demux> <sid> <pmt pid>        e.g.  ait_probe.py 0 0 11110 5100
(the sid / pmt pid / demux come from enigma2: sSID, sPMTPID, sLiveStreamDemuxId)"""
import fcntl, os, select, struct, sys, time

DMX_START, DMX_STOP, DMX_SET_FILTER, DMX_SET_BUFFER_SIZE = 0x6f29, 0x6f2a, 0x403c6f2b, 0x6f2d
CHECK_CRC, ONESHOT, IMMEDIATE = 1, 2, 4


def open_filter(adapter, demux, pid, table_id, ext=None, flags=CHECK_CRC | IMMEDIATE):
    fd = os.open("/dev/dvb/adapter%d/demux%d" % (adapter, demux), os.O_RDWR | os.O_NONBLOCK)
    fcntl.ioctl(fd, DMX_SET_BUFFER_SIZE, 8192 * 8)  # enigma2 does the same before the filter; without it this driver delivers nothing
    filt = bytearray(16); mask = bytearray(16); mode = bytearray(16)
    filt[0], mask[0] = table_id, 0xFF
    if ext is not None:
        filt[1], filt[2], mask[1], mask[2] = ext >> 8, ext & 0xFF, 0xFF, 0xFF
    # struct dmx_sct_filter_params: pid, filter[16], mask[16], mode[16], (2 bytes padding), timeout, flags = 60 bytes
    fcntl.ioctl(fd, DMX_SET_FILTER, struct.pack("<H16s16s16s2xII", pid, bytes(filt), bytes(mask), bytes(mode), 0, flags))
    return fd


def read_sections(fd, seconds):
    end, out = time.time() + seconds, []
    while time.time() < end:
        r, _, _ = select.select([fd], [], [], 0.5)
        if r:
            try:
                out.append(os.read(fd, 4096))
            except BlockingIOError:
                pass
    return out


def descriptors(b):
    i = 0
    while i + 2 <= len(b):
        tag, ln = b[i], b[i + 1]
        yield tag, b[i + 2:i + 2 + ln]
        i += 2 + ln


def parse_pmt(sec):
    """[(stream_type, pid, [(tag, data)])]"""
    pil = ((sec[10] & 0x0F) << 8) | sec[11]
    i, end, es = 12 + pil, len(sec) - 4, []
    while i + 5 <= end:
        st, pid, il = sec[i], ((sec[i + 1] & 0x1F) << 8) | sec[i + 2], ((sec[i + 3] & 0x0F) << 8) | sec[i + 4]
        es.append((st, pid, list(descriptors(sec[i + 5:i + 5 + il]))))
        i += 5 + il
    return es


CONTROL = {1: "AUTOSTART", 2: "PRESENT", 3: "DESTROY", 4: "KILL", 5: "PREFETCH", 6: "REMOTE", 7: "UNBOUND"}


def parse_ait(sec):
    app_type = (sec[3] << 8 | sec[4]) & 0x7FFF
    ver = (sec[5] >> 1) & 0x1F
    cdl = ((sec[8] & 0x0F) << 8) | sec[9]
    i = 10 + cdl
    lll = ((sec[i] & 0x0F) << 8) | sec[i + 1]
    i += 2
    end, apps = i + lll, []
    while i + 9 <= end:
        org, app, code = struct.unpack(">IHB", sec[i:i + 7])
        dl = ((sec[i + 7] & 0x0F) << 8) | sec[i + 8]
        info = {"org": org, "app": app, "control": CONTROL.get(code, code), "names": [], "transport": [], "path": "", "prio": None, "profiles": [], "visibility": None, "version": None}
        for tag, d in descriptors(sec[i + 9:i + 9 + dl]):
            if tag == 0x00 and len(d) >= 1:  # application_descriptor
                pl = d[0]
                info["profiles"] = [(d[1 + k * 5] << 8 | d[2 + k * 5], d[3 + k * 5], d[4 + k * 5], d[5 + k * 5]) for k in range(pl // 5)]
                j = 1 + pl
                if j + 3 <= len(d):
                    info["visibility"] = (d[j] >> 5) & 3
                    info["prio"] = d[j + 2]
            elif tag == 0x01:  # application_name_descriptor
                j = 0
                while j + 4 <= len(d):
                    lang, nl = d[j:j + 3].decode("latin1"), d[j + 3]
                    info["names"].append((lang, d[j + 4:j + 4 + nl].decode("utf-8", "replace")))
                    j += 4 + nl
            elif tag == 0x02 and len(d) >= 3:  # transport_protocol_descriptor
                proto, label = d[0] << 8 | d[1], d[2]
                if proto == 3 and len(d) > 3:
                    sel = d[3:]
                    ubl = sel[0]
                    base = sel[1:1 + ubl].decode("latin1")
                    ext, j = [], 1 + ubl
                    n = sel[j] if j < len(sel) else 0
                    j += 1
                    for _ in range(n):
                        el = sel[j]
                        ext.append(sel[j + 1:j + 1 + el].decode("latin1"))
                        j += 1 + el
                    info["transport"].append(("HTTP", label, base, ext))
                elif proto == 1:
                    info["transport"].append(("OC", label))
                else:
                    info["transport"].append((proto, label))
            elif tag == 0x15 and d:  # simple_application_location
                info["path"] = d.decode("latin1")
        apps.append(info)
        i += 9 + dl
    return app_type, ver, apps


def main():
    adapter, demux, sid, pmt_pid = (int(x, 0) for x in sys.argv[1:5])
    fd = open_filter(adapter, demux, pmt_pid, 0x02, sid)
    pmts = read_sections(fd, 4)
    os.close(fd)
    print("PMT sections read: %d" % len(pmts))
    if not pmts:
        return 1
    ait_pids = []
    for st, pid, descs in parse_pmt(pmts[-1]):
        tags = [hex(t) for t, _ in descs]
        signalling = [d for t, d in descs if t == 0x6F]
        print("  ES type 0x%02x pid %d descriptors %s%s" % (st, pid, tags, "  <-- application_signalling" if signalling else ""))
        if signalling:
            ait_pids.append(pid)
    for pid in ait_pids:
        fd = open_filter(adapter, demux, pid, 0x74)
        secs = read_sections(fd, 6)
        os.close(fd)
        print("AIT pid %d: %d sections read" % (pid, len(secs)))
        seen = set()
        for s in secs:
            key = (s[3], s[4], s[5], s[6], s[7])
            if key in seen:
                continue
            seen.add(key)
            app_type, ver, apps = parse_ait(s)
            print(" section %d/%d type 0x%x version %d, %d bytes, %d applications" % (s[6], s[7], app_type, ver, len(s), len(apps)))
            for a in apps:
                print("   org %d app %d control %s names %s" % (a["org"], a["app"], a["control"], a["names"]))
                print("      transport %s  path %r  visibility %s prio %s profiles %s" % (a["transport"], a["path"], a["visibility"], a["prio"], a["profiles"]))
    return 0


sys.exit(main())
