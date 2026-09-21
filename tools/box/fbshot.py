#!/usr/bin/env python3
"""Save the visible page of /dev/fb0 as raw BGRA: fbshot.py <out file>   (prints width height yoffset; convert on the PC). The driver has no read(): mmap."""
import fcntl, mmap, os, struct, sys
fd = os.open("/dev/fb0", os.O_RDONLY)
v = struct.unpack("<40I", fcntl.ioctl(fd, 0x4600, bytes(160)))  # FBIOGET_VSCREENINFO: xres, yres, xres_virtual, yres_virtual, xoffset, yoffset ...
xres, yres, yres_virtual, yoff = v[0], v[1], v[3], v[5]
stride = xres * 4
m = mmap.mmap(fd, stride * yres_virtual, mmap.MAP_SHARED, mmap.PROT_READ)
open(sys.argv[1], "wb").write(m[yoff * stride:(yoff + yres) * stride])
print(xres, yres, yoff)
