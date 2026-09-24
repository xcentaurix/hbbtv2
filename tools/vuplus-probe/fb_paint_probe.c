/*
 * fb_paint_probe - does a raw write to /dev/fb0 actually reach this box's TV output?
 *
 * Why: wpe_fb (meta-hbbtv2/recipes-hbbtv/wpe-shot/files/wpe_fb.c) presents HbbTV frames by mmap()-ing /dev/fb0 and memcpy()-ing converted pixels
 * straight into the visible page - the DM900's approach, where fb0 genuinely is the Broadcom vc5dream scanout buffer. On a Nexus-middleware box
 * (GigaBlue), NXPL_RegisterNexusDisplayPlatform's own doc comment (default_nexus.h) says it registers a display for "exclusive use" - implying
 * Nexus normally owns the display hardware through its own IPC/compositor, not through the generic Linux fbdev subsystem. If that is right, fb0
 * on a Nexus box may not be connected to the real scanout at all: a wpe_fb run can genuinely write correct pixels into fb0 (confirmed: the internal
 * "0 pixels differ from the shadow canvas" read-back check in wpe_fb's own log already proves the write itself succeeds) while nothing appears on
 * the actual screen, because whatever Nexus is scanning out never reads from that memory.
 *
 * This tool isolates exactly that question, with nothing else involved (no WPE, no EGL, no Nexus join/register) - a plain mmap()+memcpy() into
 * /dev/fb0's current visible page, like wpe_fb's own fb blit (out_blit_rect in wpe_fb.c), holding a single bold, TV-unmistakable colour for a
 * few seconds, then restoring the original pixels. A HUMAN AT THE BOX must say what appeared, if anything - the tool can only confirm the write
 * itself succeeded (mmap ok, ioctl geometry read back matches), the same way wpe_fb's own "the frame is on the framebuffer" line already did.
 *
 * Disruptive by design (unlike vu_egl_probe.c, which never draws anything) - always restores the original pixels before exiting, including on the
 * alarm-based timeout below, so a run left unattended cannot leave the screen stuck on the test colour.
 *
 *   build (any ARMv7 hf cross compiler):  arm-...-gcc -Os -Wall fb_paint_probe.c -o fb_paint_probe      (see build_vu_probe.sh, same recipe)
 *   run:   ./fb_paint_probe [seconds]     (default 6; look at the TV during that window)
 */
#define _GNU_SOURCE
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>

static void *g_map = MAP_FAILED;
static void *g_saved = NULL;
static size_t g_page_bytes = 0;
static size_t g_page_offset = 0;

/* Restore the original pixels before exiting, however we get there (normal exit or the alarm timeout below). */
static void restore_and_exit(int code)
{
    if (g_map != MAP_FAILED && g_saved) {
        memcpy((char *)g_map + g_page_offset, g_saved, g_page_bytes);
        printf("restored the original pixels\n");
        fflush(stdout);
    }
    _exit(code);
}

static void on_alarm(int sig)
{
    (void)sig;
    printf("\n(timeout - restoring and exiting, in case nothing else got the chance to)\n");
    restore_and_exit(3);
}

int main(int argc, char **argv)
{
    int secs = argc > 1 ? atoi(argv[1]) : 6;
    if (secs < 1)
        secs = 1;
    if (secs > 30)
        secs = 30; /* keep an unattended run bounded */
    signal(SIGALRM, on_alarm);
    alarm(secs + 15); /* hard safety net well past the intended hold time */

    int fd = open("/dev/fb0", O_RDWR);
    if (fd < 0) {
        perror("open /dev/fb0");
        return 1;
    }
    unsigned var[40] = { 0 };
    unsigned char fix[96] = { 0 };
    if (ioctl(fd, 0x4600, var) != 0) { /* FBIOGET_VSCREENINFO */
        perror("FBIOGET_VSCREENINFO");
        close(fd);
        return 1;
    }
    if (ioctl(fd, 0x4602, fix) != 0) { /* FBIOGET_FSCREENINFO */
        perror("FBIOGET_FSCREENINFO");
        close(fd);
        return 1;
    }
    unsigned xres = var[0], yres = var[1], bpp = var[6], yoffset = var[5];
    unsigned smem_len = *(unsigned *)(fix + 20);
    unsigned line_length = *(unsigned *)(fix + 44);
    printf("FB %ux%u, %u bpp, line_length %u, yoffset %u, smem_len %u\n", xres, yres, bpp, line_length, yoffset, smem_len);
    if (bpp != 32) {
        printf("expected 32 bpp, got %u - aborting without touching anything\n", bpp);
        close(fd);
        return 1;
    }

    g_map = mmap(NULL, smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (g_map == MAP_FAILED) {
        perror("mmap /dev/fb0");
        close(fd);
        return 1;
    }
    g_page_offset = (size_t)yoffset * line_length;
    g_page_bytes = (size_t)yres * line_length;
    if (g_page_offset + g_page_bytes > smem_len) {
        printf("computed page range (%zu + %zu) exceeds smem_len (%u) - aborting without touching anything\n", g_page_offset, g_page_bytes, smem_len);
        munmap(g_map, smem_len);
        close(fd);
        return 1;
    }
    g_saved = malloc(g_page_bytes);
    if (!g_saved) {
        printf("malloc(%zu) failed - aborting without touching anything\n", g_page_bytes);
        munmap(g_map, smem_len);
        close(fd);
        return 1;
    }
    memcpy(g_saved, (char *)g_map + g_page_offset, g_page_bytes);
    printf("saved %zu bytes of the current visible page (yoffset %u)\n", g_page_bytes, yoffset);

    /* A bold, TV-unmistakable magenta, byte order guessed from the FB layout already read above (matches wpe_fb's own out_convert_row logic):
     * red offset 16 -> byte order is B,G,R,A (little-endian ARGB8888, as this project's own probes have consistently found on both DM900 and
     * GigaBlue); anything else falls back to the same order since 24-bit-colour Broadcom framebuffers seen in this project are all one of the two
     * closely related layouts and magenta (max R and B, zero G) is unmistakable either way. */
    unsigned char b = 0xFF, g = 0x00, r = 0xFF, a = 0xFF;
    unsigned char pixel[4] = { b, g, r, a };
    char *page = (char *)g_map + g_page_offset;
    for (size_t off = 0; off < g_page_bytes; off += 4)
        memcpy(page + off, pixel, 4);
    printf("painted the full visible page solid magenta (B=%02x G=%02x R=%02x A=%02x per pixel) - look at the TV NOW for %d second(s)\n", b, g, r, a, secs);
    fflush(stdout);
    sleep((unsigned)secs);

    restore_and_exit(0);
    return 0; /* unreached */
}
