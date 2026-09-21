#!/usr/bin/env python3
"""Capture the raw AIT sections of a service from the DVB demux into a file, one line per section: "<ait pid> <sid> <hex>".
   usage: ait_capture.py <adapter> <demux> <sid> <pmt pid> <out file>     (test fixtures: tools/box/testdata/ait_*.txt)"""
import importlib.util, os, sys
here = os.path.dirname(os.path.abspath(__file__))
spec = importlib.util.spec_from_file_location("ait_probe_lib", os.path.join(here, "ait_probe.py"))
src = open(os.path.join(here, "ait_probe.py")).read().replace("\nsys.exit(main())", "\n")
ns = {"__name__": "ait_probe_lib"}
exec(compile(src, "ait_probe.py", "exec"), ns)
adapter, demux, sid, pmt_pid = (int(x, 0) for x in sys.argv[1:5])
out = sys.argv[5]
fd = ns["open_filter"](adapter, demux, pmt_pid, 0x02, sid)
pmts = ns["read_sections"](fd, 4)
os.close(fd)
ait_pid = None
for st, pid, descs in ns["parse_pmt"](pmts[-1]):
    if any(t == 0x6F for t, _ in descs):
        ait_pid = pid
fd = ns["open_filter"](adapter, demux, ait_pid, 0x74)
secs = ns["read_sections"](fd, 6)
os.close(fd)
seen, lines = set(), []
for s in secs:
    key = bytes(s)
    if key in seen:
        continue
    seen.add(key)
    lines.append("%d %d %s" % (ait_pid, sid, s.hex()))
open(out, "w").write("\n".join(lines) + "\n")
print("%d distinct AIT section(s) of pid %d written to %s" % (len(lines), ait_pid, out))
