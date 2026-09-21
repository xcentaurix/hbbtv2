#!/usr/bin/env python3
"""Which ipks must be added to the feed so that opkg can install the three HbbTV packages on the box?
Resolves Depends recursively against (a) the box's installed packages (its opkg status file) and (b) the Packages indexes of the
bitbake deploy directory; prints what is missing and where it comes from. Recommends are ignored (opkg does not install them)."""
import os
import re
import subprocess
import sys

DEPLOY = "/home/alpha/openvix/build-enviroment/builds/openvix/developer/dm900/tmp/deploy/ipk"
ARCHS = ["cortexa15hf-neon-vfpv4", "all", "dm900"]
STATUS = sys.argv[1]
ROOTS = ["enigma2-plugin-extensions-wpehbbtv", "orb", "libwpewebkit-2.0-1"]
CORE = {"libc6", "libgcc1", "libstdc++6", "glibc", "libc6-dev"}  # never add these: a mismatch means a different image


def parse(path):
    pk, cur = [], {}
    key = None
    for line in open(path, errors="replace"):
        line = line.rstrip("\n")
        if not line:
            if cur:
                pk.append(cur)
            cur, key = {}, None
        elif line[0] in " \t" and key:
            cur[key] += " " + line.strip()
        elif ":" in line:
            key, val = line.split(":", 1)
            cur[key], key = val.strip(), key
    if cur:
        pk.append(cur)
    return pk


def deps_of(p):
    out = []
    for item in re.split(r"\s*,\s*", p.get("Depends", "")):
        if not item:
            continue
        for alt in item.split("|"):  # take the first alternative
            m = re.match(r"\s*([^\s(]+)\s*(?:\(\s*([<>=]+)\s*([^)\s]+)\s*\))?", alt)
            if m:
                out.append((m.group(1), m.group(2), m.group(3)))
                break
    return out


def vercmp(a, op, b):
    if not op:
        return True
    op = {"<<": "lt", "<=": "le", "=": "eq", ">=": "ge", ">>": "gt", ">": "gt", "<": "lt"}[op]
    return subprocess.call(["dpkg", "--compare-versions", a, op, b]) == 0


def provides_of(p):
    return [x.split("(")[0].strip() for x in re.split(r"\s*,\s*", p.get("Provides", "")) if x]


installed = {}
for p in parse(STATUS):
    if "installed" in p.get("Status", "installed"):
        installed.setdefault(p["Package"], p["Version"])
        for pr in provides_of(p):
            installed.setdefault(pr, p["Version"])
print("box: %d installed names (incl. provides)" % len(installed))

import glob
import tempfile
import json


def read_control(path):
    """control file of an ipk (an ar archive with control.tar.* inside) as a dict"""
    data = open(path, "rb").read()
    pos = 8
    while pos + 60 <= len(data):
        name = data[pos:pos + 16].decode().strip().rstrip("/")
        size = int(data[pos + 48:pos + 58])
        body = data[pos + 60:pos + 60 + size]
        pos += 60 + size + (size & 1)
        if name.startswith("control.tar"):
            with tempfile.NamedTemporaryFile(suffix="." + name.split(".", 2)[2]) as t:
                t.write(body)
                t.flush()
                txt = subprocess.run(["tar", "-xOf", t.name, "./control"], capture_output=True, text=True).stdout
            p, key = {}, None
            for line in txt.splitlines():
                if line[:1] in " 	" and key:
                    p[key] += " " + line.strip()
                elif ":" in line:
                    key, val = line.split(":", 1)
                    p[key] = val.strip()
            return p
    return {}


cache = "/tmp/ipk_index.json"
allp = json.load(open(cache)) if os.path.exists(cache) else {}
for arch in ARCHS:
    files = glob.glob(os.path.join(DEPLOY, arch, "*.ipk"))
    for f in files:
        key = os.path.relpath(f, DEPLOY)
        if key not in allp or allp[key].get("_mtime") != os.path.getmtime(f):
            p = read_control(f)
            p["_mtime"] = os.path.getmtime(f)
            p["Filename"] = key
            p["Size"] = str(os.path.getsize(f))
            allp[key] = p
json.dump(allp, open(cache, "w"))
index = {}
for key, p in allp.items():
    if "Package" not in p:
        continue
    arch = key.split("/")[0]
    for name in [p["Package"]] + provides_of(p):
        index.setdefault(name, []).append((p["Version"], p, arch))
print("build tree: %d ipks, %d names" % (len(allp), len(index)))


def newest(name):
    c = index.get(name, [])
    best = None
    for v, p, a in c:
        if best is None or subprocess.call(["dpkg", "--compare-versions", v, "gt", best[0]]) == 0:
            best = (v, p, a)
    return best


need, unresolved, problems = {}, [], []
queue = []
for r in ROOTS:
    b = newest(r)
    if not b:
        print("root not built:", r)
        sys.exit(1)
    need[r] = b
    queue.append(r)

while queue:
    name = queue.pop()
    v, p, arch = need[name]
    for dname, op, dver in deps_of(p):
        have = installed.get(dname)
        if have is not None and vercmp(have, op, dver):
            continue
        if dname in CORE:
            problems.append("%s needs %s %s %s, box has %s" % (name, dname, op or "", dver or "", have))
            continue
        b = newest(dname)
        if not b:
            unresolved.append("%s <- %s (%s %s), box has %s" % (dname, name, op or "", dver or "", have))
            continue
        real = b[1]["Package"]
        if real in need or real in [x for x in ROOTS]:
            continue
        if have is not None:
            problems.append("%s: box has %s %s but %s%s is required by %s -> would upgrade to %s" % (dname, dname, have, op or "", dver or "", name, b[0]))
        need[real] = b
        queue.append(real)

print("\nTO ADD (not on the box, or too old there):")
total = 0
for n in sorted(need):
    if n in ROOTS:
        continue
    v, p, arch = need[n]
    size = int(p.get("Size", 0))
    total += size
    print("  %-46s %-24s %-24s %9d  %s" % (n, v[:24], arch, size, p.get("Filename", "")))
print("  total %.1f MB in %d packages" % (total / 1e6, len(need) - len(ROOTS)))
print("\nCORE / VERSION PROBLEMS (must be looked at):" if problems else "\nno core/version problems")
for x in problems:
    print("  " + x)
print("\nUNRESOLVED (not on the box, not built here):" if unresolved else "\nno unresolved dependencies")
for x in unresolved:
    print("  " + x)
