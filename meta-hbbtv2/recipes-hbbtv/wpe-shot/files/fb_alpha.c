/*
 * fb_alpha - decisive test of how the Dreambox display blends the OSD framebuffer over video.
 *
 * Draws five blocks with hand-picked ARGB values (into all framebuffer pages, restored afterwards). Left to right:
 *
 *   1  white, alpha 0        premultiplied blend (out = src + (1-a)*video) -> BRIGHT WHITE block
 *                            straight blend      (out = a*src + (1-a)*video) -> invisible (plain video)
 *   2  red (255,0,0), alpha 25%   premultiplied -> very bright red, straight -> mild red tint
 *   3  red ( 64,0,0), alpha 25%   premultiplied -> mild red tint,   straight -> almost no tint (slightly darker)
 *   4  black, alpha 50%      both conventions: video at half brightness (control)
 *   5  black, alpha 0        both: plain video (control)
 *
 * If alpha is only used as on/off (binary), block 1 and 5 are plain video, and 2, 3, 4 are solid.
 *
 *   usage: fb_alpha [seconds]   (default 25)
 */
#include <fcntl.h>
#include <linux/fb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

static volatile sig_atomic_t quit;
static void on_signal(int s) { quit = 1; }

static struct fb_var_screeninfo vinfo;
static struct fb_fix_screeninfo finfo;
static unsigned char *fb;
static int pages;

enum { N = 5, BW = 260, BH = 300, GAP = 40, BX = 130, BY = 340 };

static unsigned char *px(int page, int x, int y)
{
    return fb + (size_t)(page * vinfo.yres + y) * finfo.line_length + (size_t)x * 4;
}

int main(int argc, char **argv)
{
    int secs = argc > 1 ? atoi(argv[1]) : 25;
    int fd = open("/dev/fb0", O_RDWR);
    if (fd < 0) { perror("open /dev/fb0"); return 1; }
    ioctl(fd, FBIOGET_FSCREENINFO, &finfo);
    ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);
    fb = mmap(NULL, finfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (fb == MAP_FAILED) { perror("mmap"); return 1; }
    pages = vinfo.yres_virtual / vinfo.yres;
    if (pages > 8) pages = 8;

    /* ARGB, memory order B,G,R,A on this framebuffer */
    static const unsigned colors[N] = {
        0xffffffff, /* 1 solid white reference (A=255) */
        0x80ffffff, /* 2 white 255, A=50%: premultiplied HW -> solid white like block 1; straight HW -> milky, video visible */
        0x00ffffff, /* 3 white 255, A=0:   premultiplied HW -> solid white;              straight HW -> invisible */
        0x80000000, /* 4 black, A=50%: both conventions -> video at half brightness */
        0xff000000, /* 5 solid black reference (A=255) */
    };

    int total_w = N * BW + (N - 1) * GAP;
    unsigned char *saved[8];
    for (int p = 0; p < pages; p++) {
        saved[p] = malloc((size_t)BH * total_w * 4);
        for (int y = 0; y < BH; y++)
            memcpy(saved[p] + (size_t)y * total_w * 4, px(p, BX, BY + y), (size_t)total_w * 4);
    }
    signal(SIGINT, on_signal);
    signal(SIGTERM, on_signal);

    for (int b = 0; b < N; b++)
        for (int p = 0; p < pages; p++)
            for (int y = BY; y < BY + BH; y++) {
                unsigned *row = (unsigned *)px(p, BX + b * (BW + GAP), y);
                for (int x = 0; x < BW; x++)
                    row[x] = colors[b];
            }

    printf("blocks drawn, left to right: 1 SOLID white, 2 white/A50%%, 3 white/A0, 4 black/A50%%, 5 SOLID black (%d s)\n", secs);
    fflush(stdout);
    for (int i = 0; i < secs * 10 && !quit; i++)
        usleep(100000);

    for (int p = 0; p < pages; p++)
        for (int y = 0; y < BH; y++)
            memcpy(px(p, BX, BY + y), saved[p] + (size_t)y * total_w * 4, (size_t)total_w * 4);
    msync(fb, finfo.smem_len, MS_SYNC);
    printf("restored\n");
    return 0;
}
