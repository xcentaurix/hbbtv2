#!/usr/bin/env python3
"""Map return-address-looking words in a gdb stack dump to functions (WebKit via debug info, vendor libs via dynsyms)."""
import re, subprocess, sys, bisect, os

SP = "/mnt/c/Users/swald/AppData/Local/Temp/claude/u--media-usb-git-dev/0dea01b2-636a-46c9-84e7-d1ce1ec752a4/scratchpad"
T = "/home/alpha/openvix/build-enviroment/builds/openvix/developer/dm900/tmp"
BU = os.path.dirname(subprocess.check_output("find %s/sysroots-components/x86_64/binutils-cross-arm -name arm-oe-linux-gnueabi-nm | head -1" % T, shell=True, text=True).strip())
NM, A2L, RE = BU + "/arm-oe-linux-gnueabi-nm", BU + "/arm-oe-linux-gnueabi-addr2line", BU + "/arm-oe-linux-gnueabi-readelf"
DBG = "/home/alpha/wpe-test/pkg/dbg/usr/lib/.debug/libWPEWebKit-2.0.so.1.11.3"
LIBFILES = {
    "libWPEWebKit-2.0.so.1": "/home/alpha/wpe-test/deploy/lib/libWPEWebKit-2.0.so.1",
    "libv3ddriver.so": "/home/alpha/wpe-test/vendor/libv3ddriver.so",
    "libGLESv2.so.2": "/home/alpha/wpe-test/vendor/libGLESv2.so.2.0.0",
    "libEGL.so.1": "/home/alpha/wpe-test/vendor/libEGL.so.1.0.0",
    "libvc5dream.so.1": "/home/alpha/wpe-test/vendor/libvc5dream.so.1.0.0",
}
txt = open(sys.argv[1] if len(sys.argv) > 1 else SP + "/gdb_out2.txt", errors="replace").read()

# shared library table: From To name  (From = start of .text)
libs = []
for m in re.finditer(r"^(0x[0-9a-f]+)\s+(0x[0-9a-f]+)\s+Yes\s*\(?\*?\)?\s+(\S+)$", txt, re.M):
    libs.append((int(m.group(1), 16), int(m.group(2), 16), os.path.basename(m.group(3))))

def text_vaddr(path):
    out = subprocess.check_output([RE, "-S", "-W", path], text=True)
    m = re.search(r"\.text\s+PROGBITS\s+([0-9a-f]+)", out)
    return int(m.group(1), 16)

bases, dyn = {}, {}
for lo, hi, name in libs:
    if name in LIBFILES and os.path.exists(LIBFILES[name]):
        bases[name] = lo - text_vaddr(LIBFILES[name])
        if name != "libWPEWebKit-2.0.so.1":
            syms = []
            for l in subprocess.check_output([NM, "-D", "--defined-only", "-n", LIBFILES[name]], text=True).splitlines():
                p = l.split()
                if len(p) == 3:
                    syms.append((int(p[0], 16), p[2]))
            dyn[name] = syms

# stack words in order
words = []
in_stack = False
for line in txt.splitlines():
    if line.startswith("==== STACK"):
        in_stack = True; continue
    if line.startswith("==== SHARED"):
        break
    if in_stack:
        m = re.match(r"^(0x[0-9a-f]+)(?: <[^>]*>)?:\s+(.*)$", line)
        if m:
            addr = int(m.group(1), 16)
            for i, w in enumerate(m.group(2).split()):
                if w.startswith("0x"):
                    words.append((addr + 4 * i, int(w, 16)))

def which(v):
    v &= ~1
    for lo, hi, name in libs:
        if lo <= v < hi:
            return name
    return None

print("stack words: %d, libs with symbols: %s" % (len(words), ", ".join(sorted(bases))))
print("\n slot   value       object / function")
count = 0
for slot, v in words:
    name = which(v)
    if not name or name not in bases:
        continue
    vaddr = (v & ~1) - bases[name]
    if name == "libWPEWebKit-2.0.so.1":
        out = subprocess.run([A2L, "-f", "-C", "-p", "-e", DBG, hex(vaddr)], capture_output=True, text=True).stdout.strip()
        fn = out.split(" at ")[0][:110] if out else "?"
    else:
        s = dyn.get(name, [])
        i = bisect.bisect_right([a for a, _ in s], vaddr) - 1
        fn = ("%s+0x%x" % (s[i][1], vaddr - s[i][0])) if i >= 0 else "?"
    print(" %08x %08x  %-22s %s" % (slot, v, name, fn))
    count += 1
    if count >= 60:
        break
