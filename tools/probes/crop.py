import sys, zlib, struct
src, dst, x0, y0, w, h, sc = sys.argv[1], sys.argv[2], *map(int, sys.argv[3:8])
d = open(src, "rb").read().split(b"\n", 3)
W, H = map(int, d[1].split()); pix = d[3]
rows = []
for y in range(h * sc):
    sy = y0 + y // sc
    row = bytearray()
    for x in range(w * sc):
        sx = x0 + x // sc
        i = (sy * W + sx) * 3
        row += pix[i:i + 3]
    rows.append(b"\x00" + bytes(row))
raw = b"".join(rows)
def ch(t, b): c = struct.pack(">I", len(b)) + t + b; return c + struct.pack(">I", zlib.crc32(t + b) & 0xffffffff)
open(dst, "wb").write(b"\x89PNG\r\n\x1a\n" + ch(b"IHDR", struct.pack(">IIBBBBB", w * sc, h * sc, 8, 2, 0, 0, 0)) + ch(b"IDAT", zlib.compress(raw)) + ch(b"IEND", b""))
print("ok", w * sc, h * sc)
