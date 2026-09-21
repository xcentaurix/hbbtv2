#!/usr/bin/env python3
"""Resolve the stack samples of ua_sample.sh (addresses in libWPEWebKit) with addr2line against the UNSTRIPPED library of the same build and count
what the main thread was doing.   usage: resolve_samples.py <dir with s*.txt and maps.txt> [unstripped lib]"""
import collections, glob, os, re, subprocess, sys

d = sys.argv[1]
LIB = sys.argv[2] if len(sys.argv) > 2 else "/home/alpha/wpe-src/build/lib/libWPEWebKit-2.0.so.1.11.3"
T = "/home/alpha/openvix/build-enviroment/builds/openvix/developer/dm900/tmp"
A2L = subprocess.check_output("find %s/sysroots-components/x86_64/binutils-cross-arm -name arm-oe-linux-gnueabi-addr2line | head -1" % T, shell=True, text=True).strip()

base = None
for line in open(os.path.join(d, "maps.txt")):
    m = re.match(r"([0-9a-f]+)-([0-9a-f]+) \S+ ([0-9a-f]+) \S+ \d+\s*(.*)", line)
    if m and "libWPEWebKit-2.0.so" in m.group(4) and int(m.group(3), 16) == 0 and base is None:
        base = int(m.group(1), 16)
print("libWPEWebKit base: 0x%x" % base)

samples = []  # each: list of (pc, module or None)
for f in sorted(glob.glob(os.path.join(d, "s*.txt")), key=lambda p: int(re.findall(r"\d+", os.path.basename(p))[0])):
    frames, seen0 = [], False
    for line in open(f, errors="replace"):
        m = re.match(r"#(\d+)\s+(?:0x)?([0-9a-f]+)? ?(?:in )?(.*)", line.strip())
        if not m:
            continue
        idx, pc, rest = int(m.group(1)), m.group(2), m.group(3)
        if idx == 0 and seen0 and frames and frames[0][2] == pc:
            continue  # gdb prints frame 0 twice (thread select + bt)
        if idx == 0:
            seen0 = True
        frames.append((idx, rest, pc))
    samples.append(frames)

def is_wk(rest):
    return "libWPEWebKit" in rest

addrs = sorted({int(pc, 16) - base for fr in samples for (_, rest, pc) in fr if is_wk(rest) and pc})
res = {}
if addrs:
    out = subprocess.run([A2L, "-C", "-f", "-e", LIB] + ["0x%x" % a for a in addrs], capture_output=True, text=True).stdout.splitlines()
    for i, a in enumerate(addrs):
        res[a] = out[2 * i] if 2 * i < len(out) else "?"

def name(rest, pc):
    if is_wk(rest) and pc:
        return res.get(int(pc, 16) - base, "?")
    m = re.match(r"(\S+) \(", rest)
    lib = re.search(r"from (\S+)", rest)
    return (m.group(1) if m else rest[:40]) + (" [" + os.path.basename(lib.group(1)) + "]" if lib else "")

CATS = [("idle/wait", r"epoll_wait|poll|futex|pthread_cond|sem_wait|select|nanosleep|g_main_context_iterate|g_poll|WTF::RunLoop::run|sigtimedwait|read \[|recvmsg|IPC::Connection::waitFor|WTF::Condition|ParkingLot"),
        ("JS interpreter (LLInt/JSC)", r"llint|JSC::|vmEntryTo|JavaScript|jsc_|Interpreter::"),
        ("layout", r"Layout|RenderBlock|RenderBox|RenderFlex|RenderGrid|RenderInline|LineLayout|updateLayout|FlexFormatting|Inline|Block"),
        ("style", r"Style::|StyleResolver|Style|SelectorChecker|CSS"),
        ("painting/Skia", r"Sk[A-Z]|Skia|Paint|paint|GraphicsContext|GLES|glDraw|GrGL|Gr[A-Z]|DisplayList"),
        ("IPC/messages", r"IPC::|Connection|MessagePort|Message"),
        ("DOM/bindings", r"WebCore::|jsHTML|JSDOM|Node|Element|Document"),
        ("memory/GC/alloc", r"malloc|free|bmalloc|GC|Heap|memcpy|memset|libpas|pas_")]
def category(stack):
    for label, rx in CATS:
        for nm in stack[:6]:
            if re.search(rx, nm):
                return label
    return "other"

cnt0 = collections.Counter(); cat = collections.Counter()
for fr in samples:
    names = [name(rest, pc) for (_, rest, pc) in fr]
    if not names:
        continue
    cnt0[names[0]] += 1
    cat[category(names)] += 1
n = len(samples)
print("\n%d samples of the main thread. Category (first match in the top 6 frames):" % n)
for k, v in cat.most_common():
    print("  %5.1f %%  %s" % (100.0 * v / n, k))
print("\ntop of stack (frame 0):")
for k, v in cnt0.most_common(14):
    print("  %3d  %s" % (v, k[:110]))
print("\nexample stacks:")
for fr in samples[:3]:
    print("  ---")
    for (_, rest, pc) in fr[:8]:
        print("   ", name(rest, pc)[:120])

# --- exclusive view: what is the LEAF (first frame that is not an allocator)? Time inside the JS engine itself vs native code that JS only calls ---
ALLOC = re.compile(r"malloc|free|veneer|bmalloc|pas_|mi_|memcpy|memset|__GI")
def leaf(names):
    for nm in names:
        if not ALLOC.search(nm):
            return nm
    return names[0]
def kind(nm):
    if re.search(r"llint|^JSC::|vmEntryTo|Interpreter|JavaScriptCore", nm) and not re.search(r"JSC::JS[A-Z]\w+::|Bindings", nm):
        return "JS engine itself (interpreter, property access, code block creation, GC)"
    if re.search(r"epoll|poll|futex|cond|sem_|select|nanosleep|sigtimedwait|recvmsg|g_main", nm):
        return "idle / waiting"
    if re.search(r"Layout|Render[A-Z]|LineLayout|Flex|Inline|Block", nm):
        return "layout"
    if re.search(r"Style", nm):
        return "style"
    if re.search(r"Sk[A-Z]|Skia|Paint|GraphicsContext|Gr[A-Z]|GL|ioctl|DisplayList", nm):
        return "painting / GPU"
    if re.search(r"IPC::|Encoder|Connection", nm):
        return "IPC"
    return "other WebCore/WTF native (DOM, strings, refcounts, ...)"
ex = collections.Counter()
for fr in samples:
    names = [name(rest, pc) for (_, rest, pc) in fr]
    if names:
        ex[kind(leaf(names))] += 1
print("\nexclusive (leaf) view of the %d samples:" % n)
for k, v in ex.most_common():
    print("  %5.1f %%  %s" % (100.0 * v / n, k))
