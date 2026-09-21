/* Writes PNGs of random pixels with wpe_fb_png.h (a sub-rectangle of a larger frame, sizes around the 65535-byte block boundary) and the pixels themselves
 * as raw RGBA, for test_png.py to compare:   gcc -O2 -Wall -I../../meta-hbbtv2/recipes-hbbtv/wpe-shot/files test_png.c -o test_png && ./test_png <dir> */
#include "wpe_fb_png.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    const char *dir = argc > 1 ? argv[1] : ".";
    static const int sizes[][2] = { { 1, 1 }, { 3, 2 }, { 16383, 1 }, { 64, 255 }, { 1920, 200 }, { 1920, 1080 }, { 4, 4096 } };
    enum { STRIDE = 2000, ROWS = 1100 };
    uint32_t *frame = malloc((size_t)STRIDE * ROWS * 4);
    srand(3);
    for (size_t i = 0; i < (size_t)STRIDE * ROWS; i++)
        frame[i] = ((uint32_t)rand() << 16) ^ (uint32_t)rand();
    for (unsigned n = 0; n < sizeof sizes / sizeof sizes[0]; n++) {
        const int w = sizes[n][0], h = sizes[n][1];
        if (w > STRIDE || h > ROWS)
            continue;
        const uint32_t *part = frame + 7 * STRIDE + 5; /* not the corner of the frame */
        size_t len;
        uint8_t *png = png_encode_argb(part, STRIDE, w, h, &len);
        if (!png) {
            printf("encode failed for %dx%d\n", w, h);
            return 1;
        }
        char name[256];
        snprintf(name, sizeof name, "%s/t%u.png", dir, n);
        FILE *f = fopen(name, "wb");
        fwrite(png, 1, len, f);
        fclose(f);
        snprintf(name, sizeof name, "%s/t%u.rgba", dir, n);
        f = fopen(name, "wb");
        for (int y = 0; y < h; y++)
            for (int x = 0; x < w; x++) {
                const uint32_t v = part[(size_t)y * STRIDE + x];
                const uint8_t px[4] = { (uint8_t)(v >> 16), (uint8_t)(v >> 8), (uint8_t)v, (uint8_t)(v >> 24) };
                fwrite(px, 1, 4, f);
            }
        fclose(f);
        free(png);
        printf("t%u %dx%d\n", n, w, h);
    }
    return 0;
}
