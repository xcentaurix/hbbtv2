#!/usr/bin/env python3
"""Resolve pc/lr from the crash report against the maps and the WPE debug file (addr2line)."""
import re, subprocess, sys

SP = "/mnt/c/Users/swald/AppData/Local/Temp/claude/u--media-usb-git-dev/0dea01b2-636a-46c9-84e7-d1ce1ec752a4/scratchpad"
DBG = "/home/alpha/wpe-test/pkg/dbg/usr/lib/.debug/libWPEWebKit-2.0.so.1.11.3"
T = "/home/alpha/openvix/build-enviroment/builds/openvix/developer/dm900/tmp"
A2L = subprocess.check_output("find %s/sysroots-components/x86_64/binutils-cross-arm -name arm-oe-linux-gnueabi-addr2line | head -1" % T, shell=True, text=True).strip()

txt = open(SP + "/crash.txt", errors="replace").read()
regs = dict(re.findall(r"\b(pc|lr|sp|fp|r\d)=([0-9a-f]{8})", txt))
maps = []
for m in re.finditer(r"^([0-9a-f]+)-([0-9a-f]+) (\S+) ([0-9a-f]+) \S+ \d+\s*(.*)$", txt, re.M):
    maps.append((int(m.group(1), 16), int(m.group(2), 16), m.group(3), int(m.group(4), 16), m.group(5).strip()))

def where(addr):
    for lo, hi, perms, off, path in maps:
        if lo <= addr < hi:
            return lo, hi, perms, off, path
    return None

# base of libWPEWebKit = lowest mapping of that file
wk = [m for m in maps if "libWPEWebKit" in m[4]]
base = min(m[0] for m in wk) if wk else None
print("crash header:", txt.splitlines()[0])
print("libWPEWebKit base:", hex(base) if base else None)
for name in ("pc", "lr"):
    a = int(regs[name], 16)
    w = where(a)
    print("\n%s = %08x -> %s" % (name, a, ("%s [%s] (mapping %x-%x)" % (w[4] or "anon", w[2], w[0], w[1])) if w else "unmapped"))
    if w and "libWPEWebKit" in w[4]:
        off = a - base
        print("  offset in lib: 0x%x" % off)
        out = subprocess.run([A2L, "-f", "-C", "-i", "-p", "-e", DBG, hex(off)], capture_output=True, text=True)
        print("  " + (out.stdout.strip() or out.stderr.strip()).replace("\n", "\n  "))

# memory around the faulting register values, to help judge what was null
print("\nregs:", " ".join("%s=%s" % (k, v) for k, v in regs.items()))
print("\nloaded objects (unique):")
seen = []
for lo, hi, perms, off, path in maps:
    if path and path not in seen:
        seen.append(path)
for p in seen:
    print("  ", p)
