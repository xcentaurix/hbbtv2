#!/usr/bin/env python3
"""Does the infobar flicker on a channel change, and when? Logs every page flip of enigma2's OSD (yoffset of /dev/fb0) with how many of a grid of sample
points in the bottom band of the screen (where the infobar is) are not transparent on the page that is shown; a flicker is a page where that number
drops (the infobar is gone for a page) between pages where it is there. Zaps itself (OpenWebif remote command 402/403 = channel up/down) after 1 s.
    python3 infobar_monitor.py <seconds> [up|down|none]      prints "HH:MM:SS.mmm page samples-with-alpha" per change, like enigma2's debug log
"""
import fcntl, mmap, os, struct, subprocess, sys, time

secs = float(sys.argv[1]) if len(sys.argv) > 1 else 14
zap = sys.argv[2] if len(sys.argv) > 2 else "up"
fd = os.open("/dev/fb0", os.O_RDONLY)
v = struct.unpack("<40I", fcntl.ioctl(fd, 0x4600, bytes(160)))
xres, yres, yv = v[0], v[1], v[3]
stride = xres * 4
m = mmap.mmap(fd, stride * yv, mmap.MAP_SHARED, mmap.PROT_READ)
grid = [(x, y) for y in range(770, 1075, 30) for x in range(20, xres, 60)]  # the band the infobar lives in
top = [(x, y) for y in range(20, 300, 40) for x in range(20, xres, 120)]  # the top of the screen, for contrast


def yoff():
    return struct.unpack("<40I", fcntl.ioctl(fd, 0x4600, bytes(160)))[5] // yres


def count(page, points):
    return sum(m[(page * yres + y) * stride + x * 4 + 3] != 0 for x, y in points)


def stamp():
    t = time.time()
    return time.strftime("%H:%M:%S", time.localtime(t)) + ".%03d" % (t * 1000 % 1000)


# further arguments  <seconds>:<remote command>  press that key (OpenWebif remotecontrol, e.g. 399 = green, 174 = exit) at that time
keys = sorted((float(a.split(":")[0]), int(a.split(":")[1])) for a in sys.argv[3:] if ":" in a)
start, zapped, last = time.time(), False, None
print("%s start, grid of %d samples in the bottom band" % (stamp(), len(grid)))
while time.time() - start < secs:
    if not zapped and time.time() - start > 1:
        zapped = True
        if zap != "none":
            print("%s ZAP %s" % (stamp(), zap))
            subprocess.Popen(["wget", "-q", "-O", "/dev/null", "http://127.0.0.1/api/remotecontrol?command=%d" % (402 if zap == "up" else 403)])
    while keys and time.time() - start >= keys[0][0]:
        print("%s KEY %d" % (stamp(), keys[0][1]))
        subprocess.Popen(["wget", "-q", "-O", "/dev/null", "http://127.0.0.1/api/remotecontrol?command=%d" % keys.pop(0)[1]])
    page = yoff()
    now = (page, count(page, grid), count(page, top))
    if now != last:
        print("%s page %d bottom-band %3d top %3d" % ((stamp(),) + now))
        last = now
    time.sleep(0.002)
print("%s end" % stamp())
