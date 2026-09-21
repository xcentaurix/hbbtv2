#!/usr/bin/env python3
"""Unit test of the plugin's AIT code (parseAit, aitPidOfPmt, AitCollection) against a real captured AIT (testdata/ait_zdfhd.txt).
   usage: python3 test_ait.py     (no box, no enigma2 needed)"""
import os, queue, re, struct, sys, threading, time, select, fcntl, py_compile, tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
P = "/home/alpha/openvix/build-enviroment/meta-hbbtv2/recipes-hbbtv/wpe-plugin/files/WPEHbbTV/plugin.py"
if not os.path.exists(P):
    P = os.path.join(HERE, "../../meta-hbbtv2/recipes-hbbtv/wpe-plugin/files/WPEHbbTV/plugin.py")
py_compile.compile(P, cfile=tempfile.mktemp(), doraise=True)
print("plugin.py compiles")
src = open(P).read()
block = src[src.index("DMX_SET_FILTER ="):src.index("class ChannelAppLauncher")]
ns = {"os": os, "queue": queue, "re": re, "struct": struct, "threading": threading, "time": time, "select": select, "fcntl": fcntl,
      "iServiceInformation": type("SI", (), {"sPMTPID": 1, "sLiveStreamDemuxId": 2}), "currentChannel": lambda s: None}
exec(block, ns)

lines = [l.split() for l in open(os.path.join(HERE, "testdata/ait_zdfhd.txt")) if l.strip()]
pid, sid, section = int(lines[0][0]), int(lines[0][1]), bytes.fromhex(lines[0][2])
apps = ns["parseAit"](section)
for a in apps:
    print(" org %d app %d %s %r %s %r" % (a["org"], a["app"], ns["AIT_CONTROL_CODES"].get(a["control"]), ns["appName"](a), a["http"], a["path"]))
assert len(apps) == 10
start = [a for a in apps if a["control"] == 1]
assert len(start) == 1 and (start[0]["org"], start[0]["app"]) == (17, 1) and ns["appName"](start[0]) == "ZDF Start"
assert start[0]["http"] == ["http://hbbtv.zdf.de/zdfstart/"] and start[0]["path"] == "index.php"
assert sorted(ns["locatorOf"](a) for a in apps if (a["org"], a["app"]) in ((17, 3), (19, 157))) == ["11.3", "13.9d"]  # hexadecimal: dvb://current.ait/11.3
assert {(a["org"], a["app"]) for a in apps if a["control"] == 2} >= {(17, 2), (17, 3), (17, 7), (19, 157)}

# a PMT with an application_signalling_descriptor on an ES of stream type 5
def pmt(es):
    body = b"".join(struct.pack(">BHH", st, 0xE000 | p, 0xF000 | len(d)) + d for st, p, d in es)
    sect = bytes([0x02, 0xB0, 0]) + struct.pack(">HBBBHH", 11110, 0xC1, 0, 0, 0xE000 | 6110, 0xF000) + body + b"\0\0\0\0"
    return sect[:1] + bytes([0xB0 | ((len(sect) - 3) >> 8), (len(sect) - 3) & 0xFF]) + sect[3:]
assert ns["aitPidOfPmt"](pmt([(0x1B, 6110, b"\x52\x01\x00"), (0x05, 6170, b"\x52\x01\x00\x6f\x03\x01\x02\x03")])) == 6170
assert ns["aitPidOfPmt"](pmt([(0x1B, 6110, b"\x52\x01\x00")])) is None

class FakeReader:
    def __init__(self): self.events = queue.Queue(); self.stopped = False
    def stop(self): self.stopped = True
r = FakeReader()
c = ns["AitCollection"](r, (1, 1011, 11110, "ZDF HD"))
assert not c.complete() and c.drain() == []
r.events.put(("section", pid, section))
assert c.drain() == [section] and c.complete() and c.pid == pid
assert c.text() == "%d %d %s\n" % (pid, sid, section.hex())
assert len(c.apps()) == 10
# a two-section table is complete only with both sections
two = bytearray(section); two[7] = 1  # last_section_number = 1
c2 = ns["AitCollection"](r, (1, 1011, 11110, "x"))
r.events.put(("section", pid, bytes(two))); c2.drain()
assert not c2.complete()
second = bytearray(two); second[6] = 1
r.events.put(("section", pid, bytes(second))); c2.drain()
assert c2.complete()
r.events.put(("none",)); c3 = ns["AitCollection"](r, (1, 1, 1, "y")); c3.drain(); assert c3.failed
c3.stop(); assert r.stopped
print("all ok")
