/* LD_PRELOAD crash tracer for the WPE web process on ARM32: writes registers, a backtrace and the
 * memory map to /tmp/wpe-crash.txt on SIGSEGV/SIGBUS/SIGILL/SIGABRT, then exits. */
#define _GNU_SOURCE
#include <execinfo.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ucontext.h>
#include <unistd.h>

static void handler(int sig, siginfo_t *si, void *ctx)
{
    ucontext_t *uc = (ucontext_t *)ctx;
    mcontext_t *m = &uc->uc_mcontext;
    int fd = open("/tmp/wpe-crash.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd >= 0) {
        dprintf(fd, "signal %d code %d si_addr %p pid %d\n", sig, si->si_code, si->si_addr, (int)getpid());
        dprintf(fd, "pc=%08lx lr=%08lx sp=%08lx fp=%08lx\n", m->arm_pc, m->arm_lr, m->arm_sp, m->arm_fp);
        dprintf(fd, "r0=%08lx r1=%08lx r2=%08lx r3=%08lx r4=%08lx r5=%08lx r6=%08lx r7=%08lx\n", m->arm_r0, m->arm_r1, m->arm_r2,
            m->arm_r3, m->arm_r4, m->arm_r5, m->arm_r6, m->arm_r7);
        void *bt[64];
        int n = backtrace(bt, 64);
        dprintf(fd, "backtrace %d frames:\n", n);
        for (int i = 0; i < n; i++)
            dprintf(fd, "  BT %p\n", bt[i]);
        dprintf(fd, "maps:\n");
        int mfd = open("/proc/self/maps", O_RDONLY);
        if (mfd >= 0) {
            char buf[4096];
            ssize_t r;
            while ((r = read(mfd, buf, sizeof buf)) > 0)
                if (write(fd, buf, r) < 0)
                    break;
            close(mfd);
        }
        close(fd);
    }
    _exit(128 + sig);
}

__attribute__((constructor)) static void init(void)
{
    static char altstack[64 * 1024];
    stack_t ss = { .ss_sp = altstack, .ss_size = sizeof altstack, .ss_flags = 0 };
    sigaltstack(&ss, NULL);
    struct sigaction sa;
    memset(&sa, 0, sizeof sa);
    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO | SA_ONSTACK | SA_NODEFER;
    sigemptyset(&sa.sa_mask);
    int sigs[] = { SIGSEGV, SIGBUS, SIGILL, SIGABRT, SIGFPE };
    for (unsigned i = 0; i < sizeof sigs / sizeof sigs[0]; i++)
        sigaction(sigs[i], &sa, NULL);
}
