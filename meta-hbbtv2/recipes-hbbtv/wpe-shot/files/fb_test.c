/*
 * fb_test - which way of writing to the Dreambox framebuffer actually reaches the screen?
 *
 * Draws three solid colour blocks on /dev/fb0, one per phase, each phase pushing its pixels differently:
 *   phase 1: RED   block, plain CPU writes only
 *   phase 2: GREEN block, writes + ioctl(FBIO_BLIT)   (manual-blit mode)
 *   phase 3: BLUE  block, writes + msync(MS_SYNC)     (cache flush of the mapping)
 * The blocks are drawn into ALL virtual pages (so a page flip by the display owner cannot hide them),
 * and the original pixels are restored at the end or on SIGINT/SIGTERM.
 *
 *   usage: fb_test [seconds_per_phase]   (default 6)
 */
#include <fcntl.h>
#include <linux/fb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>

#ifndef FBIO_BLIT
#define FBIO_BLIT 0x22
#endif

static volatile sig_atomic_t quit;
static void on_signal(int s) { quit = 1; }

static struct fb_var_screeninfo vinfo;
static struct fb_fix_screeninfo finfo;
static unsigned char *fb;

enum { BX = 160, BY = 300, BW = 400, BH = 300, GAP = 200, N = 3 };

static unsigned char *saved[8];
static int pages;

static unsigned char *px(int page, int x, int y)
{
    return fb + (size_t)(page * vinfo.yres + y) * finfo.line_length + (size_t)x * 4;
}

static void fill(int block, unsigned argb)
{
    int x0 = BX + block * (BW + GAP);
    for (int p = 0; p < pages; p++)
        for (int y = BY; y < BY + BH; y++) {
            unsigned *row = (unsigned *)px(p, x0, y);
            for (int x = 0; x < BW; x++)
                row[x] = argb;
        }
}

static void wait_secs(int s, const char *what)
{
    printf("  ... %s (%d s)\n", what, s);
    fflush(stdout);
    for (int i = 0; i < s * 10 && !quit; i++)
        usleep(100000);
}

int main(int argc, char **argv)
{
    int secs = argc > 1 ? atoi(argv[1]) : 6;
    int fd = open("/dev/fb0", O_RDWR);
    if (fd < 0) { perror("open /dev/fb0"); return 1; }
    ioctl(fd, FBIOGET_FSCREENINFO, &finfo);
    ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);
    fb = mmap(NULL, finfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (fb == MAP_FAILED) { perror("mmap"); return 1; }
    pages = vinfo.yres_virtual / vinfo.yres;
    if (pages > 8) pages = 8;
    printf("fb %ux%u, %u pages, line %u, visible page yoffset %u (page %u)\n", vinfo.xres, vinfo.yres, pages, finfo.line_length, vinfo.yoffset,
        vinfo.yoffset / vinfo.yres);

    int total_w = N * BW + (N - 1) * GAP;
    for (int p = 0; p < pages; p++) {
        saved[p] = malloc((size_t)BH * total_w * 4);
        for (int y = 0; y < BH; y++)
            memcpy(saved[p] + (size_t)y * total_w * 4, px(p, BX, BY + y), (size_t)total_w * 4);
    }
    signal(SIGINT, on_signal);
    signal(SIGTERM, on_signal);

    printf("PHASE 1: RED block (left), plain CPU writes only\n");
    fill(0, 0xffff0000);
    wait_secs(secs, "look at the screen now");

    if (!quit) {
        printf("PHASE 2: GREEN block (middle), writes + FBIO_BLIT\n");
        fill(1, 0xff00ff00);
        int rc = ioctl(fd, FBIO_BLIT);
        printf("  ioctl(FBIO_BLIT) returned %d (%s)\n", rc, rc < 0 ? "not supported / failed" : "ok");
        wait_secs(secs, "look at the screen now");
    }
    if (!quit) {
        printf("PHASE 3: BLUE block (right), writes + msync\n");
        fill(2, 0xff0000ff);
        int rc = msync(fb, finfo.smem_len, MS_SYNC);
        printf("  msync returned %d\n", rc);
        wait_secs(secs, "look at the screen now");
    }

    printf("restoring the original pixels\n");
    for (int p = 0; p < pages; p++)
        for (int y = 0; y < BH; y++)
            memcpy(px(p, BX, BY + y), saved[p] + (size_t)y * total_w * 4, (size_t)total_w * 4);
    ioctl(fd, FBIO_BLIT);
    msync(fb, finfo.smem_len, MS_SYNC);
    printf("done\n");
    return 0;
}
