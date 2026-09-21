#!/usr/bin/env python3
"""Checks the PNGs test_png wrote (t<n>.png against t<n>.rgba) with PIL: python3 test_png.py <dir>  (run: test_png <dir> first)"""
import glob, os, sys
from PIL import Image

d = sys.argv[1] if len(sys.argv) > 1 else "."
failures = 0
for png in sorted(glob.glob(os.path.join(d, "t*.png"))):
    im = Image.open(png)
    im.load()  # PIL checks the CRCs and the zlib stream while decoding
    want = open(png[:-4] + ".rgba", "rb").read()
    ok = im.mode == "RGBA" and im.tobytes() == want
    print("%s %s %dx%d" % ("ok  " if ok else "FAIL", os.path.basename(png), im.size[0], im.size[1]))
    failures += not ok
print("all ok" if not failures else "FAILED (%d)" % failures)
sys.exit(1 if failures else 0)
