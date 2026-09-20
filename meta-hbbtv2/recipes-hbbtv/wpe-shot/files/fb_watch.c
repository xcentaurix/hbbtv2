/*
 * fb_watch - how does enigma2 treat something another process wrote into the framebuffer?
 *
 * Draws three static coloured blocks into the CURRENTLY VISIBLE framebuffer page only (exactly what wpe_fb does),
 * then watches for N seconds and logs, every time something changes:
 *   - the visible page (enigma2 flips pages with FBIOPAN_DISPLAY on every UI redraw)
 *   - on which pages the blocks are still intact (sampled at 15 points), to show whether the display owner's
 *     page-to-page copy carries the overlay along, or whether its redraws overwrite it
 * Nothing else is written. The original pixels are restored at the end (pages where the blocks are still ours).
 *
 *   usage: fb_watch [seconds]   (default 60)   - use the remote meanwhile: infobar, volume, menu, zapping
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

static volatile sig_atomic_t quit;
static void on_signal(int s) { quit = 1; }

static struct fb_var_screeninfo vinfo;
static struct fb_fix_screeninfo finfo;
static unsigned char *fb;
static int pages;

enum { N = 3, BW = 300, BH = 200, GAP = 60, BX = 480, BY = 440, NS = 5 };
static const unsigned colors[N] = { 0xc0ff0000, 0xc000ff00, 0xc00000ff }; /* straight alpha ~75% red, green, blue */

static unsigned *px(int page, int x, int y)
{
    return (unsigned *)(fb + (size_t)(page * vinfo.yres + y) * finfo.line_length + (size_t)x * 4);
}

static double now_s(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

/* how many of the 3*NS sample points on this page still hold our colour */
static int intact(int page)
{
    int ok = 0;
    for (int b = 0; b < N; b++) {
        int x0 = BX + b * (BW + GAP);
        int sx[NS] = { x0 + 15, x0 + BW - 16, x0 + BW / 2, x0 + 15, x0 + BW - 16 };
        int sy[NS] = { BY + 15, BY + 15, BY + BH / 2, BY + BH - 16, BY + BH - 16 };
        for (int i = 0; i < NS; i++)
            ok += *px(page, sx[i], sy[i]) == colors[b];
    }
    return ok;
}

int main(int argc, char **argv)
{
    int secs = argc > 1 ? atoi(argv[1]) : 60;
    int fd = open("/dev/fb0", O_RDWR);
    if (fd < 0) { perror("open /dev/fb0"); return 1; }
    ioctl(fd, FBIOGET_FSCREENINFO, &finfo);
    ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);
    fb = mmap(NULL, finfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (fb == MAP_FAILED) { perror("mmap"); return 1; }
    pages = vinfo.yres_virtual / vinfo.yres;
    if (pages > 4) pages = 4;

    int start_page = vinfo.yoffset / vinfo.yres;
    int total_w = N * BW + (N - 1) * GAP;
    unsigned char *saved = malloc((size_t)BH * total_w * 4);
    for (int y = 0; y < BH; y++)
        memcpy(saved + (size_t)y * total_w * 4, px(start_page, BX, BY + y), (size_t)total_w * 4);
    signal(SIGINT, on_signal);
    signal(SIGTERM, on_signal);

    for (int b = 0; b < N; b++)
        for (int y = BY; y < BY + BH; y++) {
            unsigned *row = px(start_page, BX + b * (BW + GAP), y);
            for (int x = 0; x < BW; x++)
                row[x] = colors[b];
        }
    printf("drawn into visible page %d only. Watching %d s - please use the remote now (OK/infobar, volume, menu, zap).\n", start_page, secs);
    fflush(stdout);

    const double t0 = now_s();
    int last_page = -1, flips = 0, changes = 0;
    int last_ok[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };
    while (!quit && now_s() - t0 < secs) {
        ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);
        int page = vinfo.yoffset / vinfo.yres;
        int ok[8];
        int changed = page != last_page;
        for (int p = 0; p < pages; p++) {
            ok[p] = intact(p);
            if (ok[p] != last_ok[p]) changed = 1;
        }
        if (changed) {
            if (last_page >= 0 && page != last_page) flips++;
            changes++;
            printf("t=%6.2fs visible page %d%s | overlay intact (of %d points):", now_s() - t0, page, page != last_page && last_page >= 0 ? " (FLIP)" : "", N * NS);
            for (int p = 0; p < pages; p++)
                printf(" p%d=%d%s", p, ok[p], p == page ? "*" : "");
            printf("\n");
            fflush(stdout);
            last_page = page;
            memcpy(last_ok, ok, sizeof ok);
        }
        usleep(20000);
    }

    printf("summary: %d page flips, %d state changes in %d s\n", flips, changes, secs);
    /* restore: only pages where our blocks are still fully ours */
    for (int p = 0; p < pages; p++) {
        if (intact(p) == N * NS || p == start_page) {
            for (int y = 0; y < BH; y++)
                memcpy(px(p, BX, BY + y), saved + (size_t)y * total_w * 4, (size_t)total_w * 4);
        }
    }
    printf("restored\n");
    return 0;
}
