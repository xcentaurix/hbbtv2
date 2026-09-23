typedef __builtin_va_list __gnuc_va_list;
typedef __gnuc_va_list va_list;
typedef signed char int8_t;
typedef short int int16_t;
typedef int int32_t;
__extension__
typedef long long int int64_t;
typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
__extension__
typedef unsigned long long int uint64_t;
typedef signed char int_least8_t;
typedef short int int_least16_t;
typedef int int_least32_t;
__extension__
typedef long long int int_least64_t;
typedef unsigned char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned int uint_least32_t;
__extension__
typedef unsigned long long int uint_least64_t;
typedef signed char int_fast8_t;
typedef int int_fast16_t;
typedef int int_fast32_t;
__extension__
typedef long long int int_fast64_t;
typedef unsigned char uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned int uint_fast32_t;
__extension__
typedef unsigned long long int uint_fast64_t;
typedef int intptr_t;
typedef unsigned int uintptr_t;
__extension__
typedef long long int intmax_t;
__extension__
typedef unsigned long long int uintmax_t;
typedef int ptrdiff_t;
typedef unsigned int size_t;
typedef unsigned int wchar_t;

typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;
__extension__ typedef signed long long int __int64_t;
__extension__ typedef unsigned long long int __uint64_t;
__extension__ typedef long long int __quad_t;
__extension__ typedef unsigned long long int __u_quad_t;
__extension__ typedef __u_quad_t __dev_t;
__extension__ typedef unsigned int __uid_t;
__extension__ typedef unsigned int __gid_t;
__extension__ typedef unsigned long int __ino_t;
__extension__ typedef __u_quad_t __ino64_t;
__extension__ typedef unsigned int __mode_t;
__extension__ typedef unsigned int __nlink_t;
__extension__ typedef long int __off_t;
__extension__ typedef __quad_t __off64_t;
__extension__ typedef int __pid_t;
__extension__ typedef struct { int __val[2]; } __fsid_t;
__extension__ typedef long int __clock_t;
__extension__ typedef unsigned long int __rlim_t;
__extension__ typedef __u_quad_t __rlim64_t;
__extension__ typedef unsigned int __id_t;
__extension__ typedef long int __time_t;
__extension__ typedef unsigned int __useconds_t;
__extension__ typedef long int __suseconds_t;
__extension__ typedef int __daddr_t;
__extension__ typedef int __key_t;
__extension__ typedef int __clockid_t;
__extension__ typedef void * __timer_t;
__extension__ typedef long int __blksize_t;
__extension__ typedef long int __blkcnt_t;
__extension__ typedef __quad_t __blkcnt64_t;
__extension__ typedef unsigned long int __fsblkcnt_t;
__extension__ typedef __u_quad_t __fsblkcnt64_t;
__extension__ typedef unsigned long int __fsfilcnt_t;
__extension__ typedef __u_quad_t __fsfilcnt64_t;
__extension__ typedef int __fsword_t;
__extension__ typedef int __ssize_t;
__extension__ typedef long int __syscall_slong_t;
__extension__ typedef unsigned long int __syscall_ulong_t;
typedef __off64_t __loff_t;
typedef __quad_t *__qaddr_t;
typedef char *__caddr_t;
__extension__ typedef int __intptr_t;
__extension__ typedef unsigned int __socklen_t;
typedef __ssize_t ssize_t;
typedef __gid_t gid_t;
typedef __uid_t uid_t;
typedef __off64_t off_t;
typedef __off64_t off64_t;
typedef __useconds_t useconds_t;
typedef __pid_t pid_t;
typedef __socklen_t socklen_t;
extern int access (const char *__name, int __type) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int euidaccess (const char *__name, int __type)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int eaccess (const char *__name, int __type)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int faccessat (int __fd, const char *__file, int __type, int __flag)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) ;
extern __off64_t lseek (int __fd, __off64_t __offset, int __whence) __asm__ ("" "lseek64") __attribute__ ((__nothrow__ , __leaf__));
extern __off64_t lseek64 (int __fd, __off64_t __offset, int __whence)
     __attribute__ ((__nothrow__ , __leaf__));
extern int close (int __fd);
extern ssize_t read (int __fd, void *__buf, size_t __nbytes) ;
extern ssize_t write (int __fd, const void *__buf, size_t __n) ;
extern ssize_t pread (int __fd, void *__buf, size_t __nbytes, __off64_t __offset) __asm__ ("" "pread64") ;
extern ssize_t pwrite (int __fd, const void *__buf, size_t __nbytes, __off64_t __offset) __asm__ ("" "pwrite64") ;
extern ssize_t pread64 (int __fd, void *__buf, size_t __nbytes,
   __off64_t __offset) ;
extern ssize_t pwrite64 (int __fd, const void *__buf, size_t __n,
    __off64_t __offset) ;
extern int pipe (int __pipedes[2]) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int pipe2 (int __pipedes[2], int __flags) __attribute__ ((__nothrow__ , __leaf__)) ;
extern unsigned int alarm (unsigned int __seconds) __attribute__ ((__nothrow__ , __leaf__));
extern unsigned int sleep (unsigned int __seconds);
extern __useconds_t ualarm (__useconds_t __value, __useconds_t __interval)
     __attribute__ ((__nothrow__ , __leaf__));
extern int usleep (__useconds_t __useconds);
extern int pause (void);
extern int chown (const char *__file, __uid_t __owner, __gid_t __group)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int fchown (int __fd, __uid_t __owner, __gid_t __group) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int lchown (const char *__file, __uid_t __owner, __gid_t __group)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int fchownat (int __fd, const char *__file, __uid_t __owner,
       __gid_t __group, int __flag)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) ;
extern int chdir (const char *__path) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int fchdir (int __fd) __attribute__ ((__nothrow__ , __leaf__)) ;
extern char *getcwd (char *__buf, size_t __size) __attribute__ ((__nothrow__ , __leaf__)) ;
extern char *get_current_dir_name (void) __attribute__ ((__nothrow__ , __leaf__));
extern char *getwd (char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__deprecated__)) ;
extern int dup (int __fd) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int dup2 (int __fd, int __fd2) __attribute__ ((__nothrow__ , __leaf__));
extern int dup3 (int __fd, int __fd2, int __flags) __attribute__ ((__nothrow__ , __leaf__));
extern char **__environ;
extern char **environ;
extern int execve (const char *__path, char *const __argv[],
     char *const __envp[]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int fexecve (int __fd, char *const __argv[], char *const __envp[])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern int execv (const char *__path, char *const __argv[])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int execle (const char *__path, const char *__arg, ...)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int execl (const char *__path, const char *__arg, ...)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int execvp (const char *__file, char *const __argv[])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int execlp (const char *__file, const char *__arg, ...)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int execvpe (const char *__file, char *const __argv[],
      char *const __envp[])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int nice (int __inc) __attribute__ ((__nothrow__ , __leaf__)) ;
extern void _exit (int __status) __attribute__ ((__noreturn__));
enum
  {
    _PC_LINK_MAX,
    _PC_MAX_CANON,
    _PC_MAX_INPUT,
    _PC_NAME_MAX,
    _PC_PATH_MAX,
    _PC_PIPE_BUF,
    _PC_CHOWN_RESTRICTED,
    _PC_NO_TRUNC,
    _PC_VDISABLE,
    _PC_SYNC_IO,
    _PC_ASYNC_IO,
    _PC_PRIO_IO,
    _PC_SOCK_MAXBUF,
    _PC_FILESIZEBITS,
    _PC_REC_INCR_XFER_SIZE,
    _PC_REC_MAX_XFER_SIZE,
    _PC_REC_MIN_XFER_SIZE,
    _PC_REC_XFER_ALIGN,
    _PC_ALLOC_SIZE_MIN,
    _PC_SYMLINK_MAX,
    _PC_2_SYMLINKS
  };
enum
  {
    _SC_ARG_MAX,
    _SC_CHILD_MAX,
    _SC_CLK_TCK,
    _SC_NGROUPS_MAX,
    _SC_OPEN_MAX,
    _SC_STREAM_MAX,
    _SC_TZNAME_MAX,
    _SC_JOB_CONTROL,
    _SC_SAVED_IDS,
    _SC_REALTIME_SIGNALS,
    _SC_PRIORITY_SCHEDULING,
    _SC_TIMERS,
    _SC_ASYNCHRONOUS_IO,
    _SC_PRIORITIZED_IO,
    _SC_SYNCHRONIZED_IO,
    _SC_FSYNC,
    _SC_MAPPED_FILES,
    _SC_MEMLOCK,
    _SC_MEMLOCK_RANGE,
    _SC_MEMORY_PROTECTION,
    _SC_MESSAGE_PASSING,
    _SC_SEMAPHORES,
    _SC_SHARED_MEMORY_OBJECTS,
    _SC_AIO_LISTIO_MAX,
    _SC_AIO_MAX,
    _SC_AIO_PRIO_DELTA_MAX,
    _SC_DELAYTIMER_MAX,
    _SC_MQ_OPEN_MAX,
    _SC_MQ_PRIO_MAX,
    _SC_VERSION,
    _SC_PAGESIZE,
    _SC_RTSIG_MAX,
    _SC_SEM_NSEMS_MAX,
    _SC_SEM_VALUE_MAX,
    _SC_SIGQUEUE_MAX,
    _SC_TIMER_MAX,
    _SC_BC_BASE_MAX,
    _SC_BC_DIM_MAX,
    _SC_BC_SCALE_MAX,
    _SC_BC_STRING_MAX,
    _SC_COLL_WEIGHTS_MAX,
    _SC_EQUIV_CLASS_MAX,
    _SC_EXPR_NEST_MAX,
    _SC_LINE_MAX,
    _SC_RE_DUP_MAX,
    _SC_CHARCLASS_NAME_MAX,
    _SC_2_VERSION,
    _SC_2_C_BIND,
    _SC_2_C_DEV,
    _SC_2_FORT_DEV,
    _SC_2_FORT_RUN,
    _SC_2_SW_DEV,
    _SC_2_LOCALEDEF,
    _SC_PII,
    _SC_PII_XTI,
    _SC_PII_SOCKET,
    _SC_PII_INTERNET,
    _SC_PII_OSI,
    _SC_POLL,
    _SC_SELECT,
    _SC_UIO_MAXIOV,
    _SC_IOV_MAX = _SC_UIO_MAXIOV,
    _SC_PII_INTERNET_STREAM,
    _SC_PII_INTERNET_DGRAM,
    _SC_PII_OSI_COTS,
    _SC_PII_OSI_CLTS,
    _SC_PII_OSI_M,
    _SC_T_IOV_MAX,
    _SC_THREADS,
    _SC_THREAD_SAFE_FUNCTIONS,
    _SC_GETGR_R_SIZE_MAX,
    _SC_GETPW_R_SIZE_MAX,
    _SC_LOGIN_NAME_MAX,
    _SC_TTY_NAME_MAX,
    _SC_THREAD_DESTRUCTOR_ITERATIONS,
    _SC_THREAD_KEYS_MAX,
    _SC_THREAD_STACK_MIN,
    _SC_THREAD_THREADS_MAX,
    _SC_THREAD_ATTR_STACKADDR,
    _SC_THREAD_ATTR_STACKSIZE,
    _SC_THREAD_PRIORITY_SCHEDULING,
    _SC_THREAD_PRIO_INHERIT,
    _SC_THREAD_PRIO_PROTECT,
    _SC_THREAD_PROCESS_SHARED,
    _SC_NPROCESSORS_CONF,
    _SC_NPROCESSORS_ONLN,
    _SC_PHYS_PAGES,
    _SC_AVPHYS_PAGES,
    _SC_ATEXIT_MAX,
    _SC_PASS_MAX,
    _SC_XOPEN_VERSION,
    _SC_XOPEN_XCU_VERSION,
    _SC_XOPEN_UNIX,
    _SC_XOPEN_CRYPT,
    _SC_XOPEN_ENH_I18N,
    _SC_XOPEN_SHM,
    _SC_2_CHAR_TERM,
    _SC_2_C_VERSION,
    _SC_2_UPE,
    _SC_XOPEN_XPG2,
    _SC_XOPEN_XPG3,
    _SC_XOPEN_XPG4,
    _SC_CHAR_BIT,
    _SC_CHAR_MAX,
    _SC_CHAR_MIN,
    _SC_INT_MAX,
    _SC_INT_MIN,
    _SC_LONG_BIT,
    _SC_WORD_BIT,
    _SC_MB_LEN_MAX,
    _SC_NZERO,
    _SC_SSIZE_MAX,
    _SC_SCHAR_MAX,
    _SC_SCHAR_MIN,
    _SC_SHRT_MAX,
    _SC_SHRT_MIN,
    _SC_UCHAR_MAX,
    _SC_UINT_MAX,
    _SC_ULONG_MAX,
    _SC_USHRT_MAX,
    _SC_NL_ARGMAX,
    _SC_NL_LANGMAX,
    _SC_NL_MSGMAX,
    _SC_NL_NMAX,
    _SC_NL_SETMAX,
    _SC_NL_TEXTMAX,
    _SC_XBS5_ILP32_OFF32,
    _SC_XBS5_ILP32_OFFBIG,
    _SC_XBS5_LP64_OFF64,
    _SC_XBS5_LPBIG_OFFBIG,
    _SC_XOPEN_LEGACY,
    _SC_XOPEN_REALTIME,
    _SC_XOPEN_REALTIME_THREADS,
    _SC_ADVISORY_INFO,
    _SC_BARRIERS,
    _SC_BASE,
    _SC_C_LANG_SUPPORT,
    _SC_C_LANG_SUPPORT_R,
    _SC_CLOCK_SELECTION,
    _SC_CPUTIME,
    _SC_THREAD_CPUTIME,
    _SC_DEVICE_IO,
    _SC_DEVICE_SPECIFIC,
    _SC_DEVICE_SPECIFIC_R,
    _SC_FD_MGMT,
    _SC_FIFO,
    _SC_PIPE,
    _SC_FILE_ATTRIBUTES,
    _SC_FILE_LOCKING,
    _SC_FILE_SYSTEM,
    _SC_MONOTONIC_CLOCK,
    _SC_MULTI_PROCESS,
    _SC_SINGLE_PROCESS,
    _SC_NETWORKING,
    _SC_READER_WRITER_LOCKS,
    _SC_SPIN_LOCKS,
    _SC_REGEXP,
    _SC_REGEX_VERSION,
    _SC_SHELL,
    _SC_SIGNALS,
    _SC_SPAWN,
    _SC_SPORADIC_SERVER,
    _SC_THREAD_SPORADIC_SERVER,
    _SC_SYSTEM_DATABASE,
    _SC_SYSTEM_DATABASE_R,
    _SC_TIMEOUTS,
    _SC_TYPED_MEMORY_OBJECTS,
    _SC_USER_GROUPS,
    _SC_USER_GROUPS_R,
    _SC_2_PBS,
    _SC_2_PBS_ACCOUNTING,
    _SC_2_PBS_LOCATE,
    _SC_2_PBS_MESSAGE,
    _SC_2_PBS_TRACK,
    _SC_SYMLOOP_MAX,
    _SC_STREAMS,
    _SC_2_PBS_CHECKPOINT,
    _SC_V6_ILP32_OFF32,
    _SC_V6_ILP32_OFFBIG,
    _SC_V6_LP64_OFF64,
    _SC_V6_LPBIG_OFFBIG,
    _SC_HOST_NAME_MAX,
    _SC_TRACE,
    _SC_TRACE_EVENT_FILTER,
    _SC_TRACE_INHERIT,
    _SC_TRACE_LOG,
    _SC_LEVEL1_ICACHE_SIZE,
    _SC_LEVEL1_ICACHE_ASSOC,
    _SC_LEVEL1_ICACHE_LINESIZE,
    _SC_LEVEL1_DCACHE_SIZE,
    _SC_LEVEL1_DCACHE_ASSOC,
    _SC_LEVEL1_DCACHE_LINESIZE,
    _SC_LEVEL2_CACHE_SIZE,
    _SC_LEVEL2_CACHE_ASSOC,
    _SC_LEVEL2_CACHE_LINESIZE,
    _SC_LEVEL3_CACHE_SIZE,
    _SC_LEVEL3_CACHE_ASSOC,
    _SC_LEVEL3_CACHE_LINESIZE,
    _SC_LEVEL4_CACHE_SIZE,
    _SC_LEVEL4_CACHE_ASSOC,
    _SC_LEVEL4_CACHE_LINESIZE,
    _SC_IPV6 = _SC_LEVEL1_ICACHE_SIZE + 50,
    _SC_RAW_SOCKETS,
    _SC_V7_ILP32_OFF32,
    _SC_V7_ILP32_OFFBIG,
    _SC_V7_LP64_OFF64,
    _SC_V7_LPBIG_OFFBIG,
    _SC_SS_REPL_MAX,
    _SC_TRACE_EVENT_NAME_MAX,
    _SC_TRACE_NAME_MAX,
    _SC_TRACE_SYS_MAX,
    _SC_TRACE_USER_EVENT_MAX,
    _SC_XOPEN_STREAMS,
    _SC_THREAD_ROBUST_PRIO_INHERIT,
    _SC_THREAD_ROBUST_PRIO_PROTECT
  };
enum
  {
    _CS_PATH,
    _CS_V6_WIDTH_RESTRICTED_ENVS,
    _CS_GNU_LIBC_VERSION,
    _CS_GNU_LIBPTHREAD_VERSION,
    _CS_V5_WIDTH_RESTRICTED_ENVS,
    _CS_V7_WIDTH_RESTRICTED_ENVS,
    _CS_LFS_CFLAGS = 1000,
    _CS_LFS_LDFLAGS,
    _CS_LFS_LIBS,
    _CS_LFS_LINTFLAGS,
    _CS_LFS64_CFLAGS,
    _CS_LFS64_LDFLAGS,
    _CS_LFS64_LIBS,
    _CS_LFS64_LINTFLAGS,
    _CS_XBS5_ILP32_OFF32_CFLAGS = 1100,
    _CS_XBS5_ILP32_OFF32_LDFLAGS,
    _CS_XBS5_ILP32_OFF32_LIBS,
    _CS_XBS5_ILP32_OFF32_LINTFLAGS,
    _CS_XBS5_ILP32_OFFBIG_CFLAGS,
    _CS_XBS5_ILP32_OFFBIG_LDFLAGS,
    _CS_XBS5_ILP32_OFFBIG_LIBS,
    _CS_XBS5_ILP32_OFFBIG_LINTFLAGS,
    _CS_XBS5_LP64_OFF64_CFLAGS,
    _CS_XBS5_LP64_OFF64_LDFLAGS,
    _CS_XBS5_LP64_OFF64_LIBS,
    _CS_XBS5_LP64_OFF64_LINTFLAGS,
    _CS_XBS5_LPBIG_OFFBIG_CFLAGS,
    _CS_XBS5_LPBIG_OFFBIG_LDFLAGS,
    _CS_XBS5_LPBIG_OFFBIG_LIBS,
    _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS,
    _CS_POSIX_V6_ILP32_OFF32_CFLAGS,
    _CS_POSIX_V6_ILP32_OFF32_LDFLAGS,
    _CS_POSIX_V6_ILP32_OFF32_LIBS,
    _CS_POSIX_V6_ILP32_OFF32_LINTFLAGS,
    _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS,
    _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS,
    _CS_POSIX_V6_ILP32_OFFBIG_LIBS,
    _CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS,
    _CS_POSIX_V6_LP64_OFF64_CFLAGS,
    _CS_POSIX_V6_LP64_OFF64_LDFLAGS,
    _CS_POSIX_V6_LP64_OFF64_LIBS,
    _CS_POSIX_V6_LP64_OFF64_LINTFLAGS,
    _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS,
    _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS,
    _CS_POSIX_V6_LPBIG_OFFBIG_LIBS,
    _CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS,
    _CS_POSIX_V7_ILP32_OFF32_CFLAGS,
    _CS_POSIX_V7_ILP32_OFF32_LDFLAGS,
    _CS_POSIX_V7_ILP32_OFF32_LIBS,
    _CS_POSIX_V7_ILP32_OFF32_LINTFLAGS,
    _CS_POSIX_V7_ILP32_OFFBIG_CFLAGS,
    _CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS,
    _CS_POSIX_V7_ILP32_OFFBIG_LIBS,
    _CS_POSIX_V7_ILP32_OFFBIG_LINTFLAGS,
    _CS_POSIX_V7_LP64_OFF64_CFLAGS,
    _CS_POSIX_V7_LP64_OFF64_LDFLAGS,
    _CS_POSIX_V7_LP64_OFF64_LIBS,
    _CS_POSIX_V7_LP64_OFF64_LINTFLAGS,
    _CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS,
    _CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS,
    _CS_POSIX_V7_LPBIG_OFFBIG_LIBS,
    _CS_POSIX_V7_LPBIG_OFFBIG_LINTFLAGS,
    _CS_V6_ENV,
    _CS_V7_ENV
  };
extern long int pathconf (const char *__path, int __name)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern long int fpathconf (int __fd, int __name) __attribute__ ((__nothrow__ , __leaf__));
extern long int sysconf (int __name) __attribute__ ((__nothrow__ , __leaf__));
extern size_t confstr (int __name, char *__buf, size_t __len) __attribute__ ((__nothrow__ , __leaf__));
extern __pid_t getpid (void) __attribute__ ((__nothrow__ , __leaf__));
extern __pid_t getppid (void) __attribute__ ((__nothrow__ , __leaf__));
extern __pid_t getpgrp (void) __attribute__ ((__nothrow__ , __leaf__));
extern __pid_t __getpgid (__pid_t __pid) __attribute__ ((__nothrow__ , __leaf__));
extern __pid_t getpgid (__pid_t __pid) __attribute__ ((__nothrow__ , __leaf__));
extern int setpgid (__pid_t __pid, __pid_t __pgid) __attribute__ ((__nothrow__ , __leaf__));
extern int setpgrp (void) __attribute__ ((__nothrow__ , __leaf__));
extern __pid_t setsid (void) __attribute__ ((__nothrow__ , __leaf__));
extern __pid_t getsid (__pid_t __pid) __attribute__ ((__nothrow__ , __leaf__));
extern __uid_t getuid (void) __attribute__ ((__nothrow__ , __leaf__));
extern __uid_t geteuid (void) __attribute__ ((__nothrow__ , __leaf__));
extern __gid_t getgid (void) __attribute__ ((__nothrow__ , __leaf__));
extern __gid_t getegid (void) __attribute__ ((__nothrow__ , __leaf__));
extern int getgroups (int __size, __gid_t __list[]) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int group_member (__gid_t __gid) __attribute__ ((__nothrow__ , __leaf__));
extern int setuid (__uid_t __uid) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int setreuid (__uid_t __ruid, __uid_t __euid) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int seteuid (__uid_t __uid) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int setgid (__gid_t __gid) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int setregid (__gid_t __rgid, __gid_t __egid) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int setegid (__gid_t __gid) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int getresuid (__uid_t *__ruid, __uid_t *__euid, __uid_t *__suid)
     __attribute__ ((__nothrow__ , __leaf__));
extern int getresgid (__gid_t *__rgid, __gid_t *__egid, __gid_t *__sgid)
     __attribute__ ((__nothrow__ , __leaf__));
extern int setresuid (__uid_t __ruid, __uid_t __euid, __uid_t __suid)
     __attribute__ ((__nothrow__ , __leaf__)) ;
extern int setresgid (__gid_t __rgid, __gid_t __egid, __gid_t __sgid)
     __attribute__ ((__nothrow__ , __leaf__)) ;
extern __pid_t fork (void) __attribute__ ((__nothrow__));
extern __pid_t vfork (void) __attribute__ ((__nothrow__ , __leaf__));
extern char *ttyname (int __fd) __attribute__ ((__nothrow__ , __leaf__));
extern int ttyname_r (int __fd, char *__buf, size_t __buflen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) ;
extern int isatty (int __fd) __attribute__ ((__nothrow__ , __leaf__));
extern int ttyslot (void) __attribute__ ((__nothrow__ , __leaf__));
extern int link (const char *__from, const char *__to)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) ;
extern int linkat (int __fromfd, const char *__from, int __tofd,
     const char *__to, int __flags)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4))) ;
extern int symlink (const char *__from, const char *__to)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) ;
extern ssize_t readlink (const char *__restrict __path,
    char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) ;
extern int symlinkat (const char *__from, int __tofd,
        const char *__to) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3))) ;
extern ssize_t readlinkat (int __fd, const char *__restrict __path,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3))) ;
extern int unlink (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int unlinkat (int __fd, const char *__name, int __flag)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern int rmdir (const char *__path) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern __pid_t tcgetpgrp (int __fd) __attribute__ ((__nothrow__ , __leaf__));
extern int tcsetpgrp (int __fd, __pid_t __pgrp_id) __attribute__ ((__nothrow__ , __leaf__));
extern char *getlogin (void);
extern int getlogin_r (char *__name, size_t __name_len) __attribute__ ((__nonnull__ (1)));
extern int setlogin (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern char *optarg;
extern int optind;
extern int opterr;
extern int optopt;
extern int getopt (int ___argc, char *const *___argv, const char *__shortopts)
       __attribute__ ((__nothrow__ , __leaf__));
extern int gethostname (char *__name, size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int sethostname (const char *__name, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int sethostid (long int __id) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int getdomainname (char *__name, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int setdomainname (const char *__name, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int vhangup (void) __attribute__ ((__nothrow__ , __leaf__));
extern int revoke (const char *__file) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int profil (unsigned short int *__sample_buffer, size_t __size,
     size_t __offset, unsigned int __scale)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int acct (const char *__name) __attribute__ ((__nothrow__ , __leaf__));
extern char *getusershell (void) __attribute__ ((__nothrow__ , __leaf__));
extern void endusershell (void) __attribute__ ((__nothrow__ , __leaf__));
extern void setusershell (void) __attribute__ ((__nothrow__ , __leaf__));
extern int daemon (int __nochdir, int __noclose) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int chroot (const char *__path) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern char *getpass (const char *__prompt) __attribute__ ((__nonnull__ (1)));
extern int fsync (int __fd);
extern int syncfs (int __fd) __attribute__ ((__nothrow__ , __leaf__));
extern long int gethostid (void);
extern void sync (void) __attribute__ ((__nothrow__ , __leaf__));
extern int getpagesize (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int getdtablesize (void) __attribute__ ((__nothrow__ , __leaf__));
extern int truncate (const char *__file, __off64_t __length) __asm__ ("" "truncate64") __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int truncate64 (const char *__file, __off64_t __length)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int ftruncate (int __fd, __off64_t __length) __asm__ ("" "ftruncate64") __attribute__ ((__nothrow__ , __leaf__)) ;
extern int ftruncate64 (int __fd, __off64_t __length) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int brk (void *__addr) __attribute__ ((__nothrow__ , __leaf__)) ;
extern void *sbrk (intptr_t __delta) __attribute__ ((__nothrow__ , __leaf__));
extern long int syscall (long int __sysno, ...) __attribute__ ((__nothrow__ , __leaf__));
extern int lockf (int __fd, int __cmd, __off64_t __len) __asm__ ("" "lockf64") ;
extern int lockf64 (int __fd, int __cmd, __off64_t __len) ;
extern int fdatasync (int __fildes);
extern char *crypt (const char *__key, const char *__salt)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern void encrypt (char *__libc_block, int __edflag) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void swab (const void *__restrict __from, void *__restrict __to,
    ssize_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

typedef uint64_t BSTD_DeviceOffset;
typedef uint32_t BERR_Code;
BERR_Code BDBG_P_PrintError(const char *file, unsigned lineno, const char *error, BERR_Code error_no);
BERR_Code BDBG_P_PrintError_small_isrsafe(const char *file, unsigned lineno, BERR_Code error_no);
static __inline__ BERR_Code BDBG_P_PrintError_inline_isrsafe(const char *file, unsigned lineno, const char *error, BERR_Code error_no) {
    if(__builtin_constant_p(error_no)) {
        if(error_no==0) {
            return 0;
        }
        if(error_no > 10) {
            return BDBG_P_PrintError(file, lineno, error, error_no);
        }
    }
    return BDBG_P_PrintError_small_isrsafe(file, lineno, error_no);
}
typedef enum {
  BDBG_P_eUnknown=0,
  BDBG_eTrace,
  BDBG_eMsg,
  BDBG_eWrn,
  BDBG_eErr,
  BDBG_eLog,
  BDBG_P_eLastEntry
} BDBG_Level;
typedef void *BDBG_Instance;
BERR_Code BDBG_Init(void);
void BDBG_Uninit(void);
typedef struct BDBG_DebugModuleFile *BDBG_pDebugModuleFile;
typedef enum BDBG_ModulePrintKind {
    BDBG_ModulePrintKind_eHeader,
    BDBG_ModulePrintKind_eBody,
    BDBG_ModulePrintKind_eHeaderAndBody,
    BDBG_ModulePrintKind_eString
} BDBG_ModulePrintKind;
typedef struct BDBG_DebugModuleFile BDBG_DebugModuleFile;
typedef void (*BDBG_DebugModule_Print)(
        BDBG_ModulePrintKind kind,
        BDBG_Level level,
        const BDBG_DebugModuleFile *module,
        const char *fmt,
        va_list ap
        );
struct BDBG_DebugModuleFile {
 int8_t level;
 uint8_t module_level;
 _Bool module_alloc;
    struct { struct BDBG_DebugModuleFile *sl_next; } link;
    const char *name;
    BDBG_DebugModule_Print module_print;
};
struct bdbg_obj
{
 const char *bdbg_obj_id;
};
extern const char BDBG_P_EmptyString[];
const char *
BDBG_GetPrintableFileName(const char *pFileName);
const char *BDBG_P_Int64DecArg(int64_t x, char *buf, size_t buf_size);
void BDBG_P_PrintString(const char *fmt, ...) ;
void BDBG_P_Vprintf_Log_isrsafe(BDBG_ModulePrintKind kind, const char *fmt, va_list ap);
BERR_Code BDBG_P_PrintError(const char *file, unsigned lineno, const char *error, BERR_Code error_no);
BERR_Code BDBG_P_PrintError_small_isrsafe(const char *file, unsigned lineno, BERR_Code error_no);
void BDBG_P_PrintErrorString_small_isrsafe(const char *file, unsigned lineno);
void BDBG_P_Assert_isrsafe(_Bool expr, const char *file, unsigned line);
void BDBG_P_AssertFailed(const char *expr, const char *file, unsigned line)
__attribute__ ((noreturn))
    ;
typedef struct balloc_iface const *balloc_iface_t;
struct balloc_iface {
 void *(*bmem_alloc)(balloc_iface_t alloc, size_t size);
 void (*bmem_free)(balloc_iface_t alloc, void *ptr);
};
extern const struct balloc_iface bkni_alloc[1];

typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;
typedef __loff_t loff_t;
typedef __ino64_t ino_t;
typedef __ino64_t ino64_t;
typedef __dev_t dev_t;
typedef __mode_t mode_t;
typedef __nlink_t nlink_t;
typedef __id_t id_t;
typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;
typedef __key_t key_t;

typedef __clock_t clock_t;



typedef __time_t time_t;


typedef __clockid_t clockid_t;
typedef __timer_t timer_t;
typedef __suseconds_t suseconds_t;
typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;
typedef unsigned int u_int8_t __attribute__ ((__mode__ (__QI__)));
typedef unsigned int u_int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int u_int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int u_int64_t __attribute__ ((__mode__ (__DI__)));
typedef int register_t __attribute__ ((__mode__ (__word__)));
static __inline unsigned int
__bswap_32 (unsigned int __bsx)
{
  return __builtin_bswap32 (__bsx);
}
static __inline __uint64_t
__bswap_64 (__uint64_t __bsx)
{
  return __builtin_bswap64 (__bsx);
}
typedef int __sig_atomic_t;
typedef struct
  {
    unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
  } __sigset_t;
typedef __sigset_t sigset_t;
struct timespec
  {
    __time_t tv_sec;
    __syscall_slong_t tv_nsec;
  };
struct timeval
  {
    __time_t tv_sec;
    __suseconds_t tv_usec;
  };
typedef long int __fd_mask;
typedef struct
  {
    __fd_mask fds_bits[1024 / (8 * (int) sizeof (__fd_mask))];
  } fd_set;
typedef __fd_mask fd_mask;

extern int select (int __nfds, fd_set *__restrict __readfds,
     fd_set *__restrict __writefds,
     fd_set *__restrict __exceptfds,
     struct timeval *__restrict __timeout);
extern int pselect (int __nfds, fd_set *__restrict __readfds,
      fd_set *__restrict __writefds,
      fd_set *__restrict __exceptfds,
      const struct timespec *__restrict __timeout,
      const __sigset_t *__restrict __sigmask);


__extension__
extern unsigned int gnu_dev_major (unsigned long long int __dev)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
__extension__
extern unsigned int gnu_dev_minor (unsigned long long int __dev)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
__extension__
extern unsigned long long int gnu_dev_makedev (unsigned int __major,
            unsigned int __minor)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));

typedef __blksize_t blksize_t;
typedef __blkcnt64_t blkcnt_t;
typedef __fsblkcnt64_t fsblkcnt_t;
typedef __fsfilcnt64_t fsfilcnt_t;
typedef __blkcnt64_t blkcnt64_t;
typedef __fsblkcnt64_t fsblkcnt64_t;
typedef __fsfilcnt64_t fsfilcnt64_t;
typedef unsigned long int pthread_t;
union pthread_attr_t
{
  char __size[36];
  long int __align;
};
typedef union pthread_attr_t pthread_attr_t;
typedef struct __pthread_internal_slist
{
  struct __pthread_internal_slist *__next;
} __pthread_slist_t;
typedef union
{
  struct __pthread_mutex_s
  {
    int __lock;
    unsigned int __count;
    int __owner;
    int __kind;
    unsigned int __nusers;
    __extension__ union
    {
      int __spins;
      __pthread_slist_t __list;
    };
  } __data;
  char __size[24];
  long int __align;
} pthread_mutex_t;
typedef union
{
  char __size[4];
  long int __align;
} pthread_mutexattr_t;
typedef union
{
  struct
  {
    int __lock;
    unsigned int __futex;
    __extension__ unsigned long long int __total_seq;
    __extension__ unsigned long long int __wakeup_seq;
    __extension__ unsigned long long int __woken_seq;
    void *__mutex;
    unsigned int __nwaiters;
    unsigned int __broadcast_seq;
  } __data;
  char __size[48];
  __extension__ long long int __align;
} pthread_cond_t;
typedef union
{
  char __size[4];
  long int __align;
} pthread_condattr_t;
typedef unsigned int pthread_key_t;
typedef int pthread_once_t;
typedef union
{
  struct
  {
    int __lock;
    unsigned int __nr_readers;
    unsigned int __readers_wakeup;
    unsigned int __writer_wakeup;
    unsigned int __nr_readers_queued;
    unsigned int __nr_writers_queued;
    unsigned char __flags;
    unsigned char __shared;
    unsigned char __pad1;
    unsigned char __pad2;
    int __writer;
  } __data;
  char __size[32];
  long int __align;
} pthread_rwlock_t;
typedef union
{
  char __size[8];
  long int __align;
} pthread_rwlockattr_t;
typedef volatile int pthread_spinlock_t;
typedef union
{
  char __size[20];
  long int __align;
} pthread_barrier_t;
typedef union
{
  char __size[4];
  int __align;
} pthread_barrierattr_t;

typedef struct bfile_io_read *bfile_io_read_t;
typedef struct bfile_io_write *bfile_io_write_t;
typedef int (*bio_get_priority)(void *cntx);
typedef struct bfile_io_priority {
    bio_get_priority get;
    void *cntx;
} bfile_io_priority;
int bio_default_priority(void *cntx);
struct bfile_io_read {
    ssize_t (*read)(bfile_io_read_t fd, void *buf, size_t length);
    off_t (*seek)(bfile_io_read_t fd, off_t offset, int whence);
    int (*bounds)(bfile_io_read_t fd, off_t *first, off_t *last);
    bfile_io_priority priority;
};
struct bfile_io_write {
    ssize_t (*write)(bfile_io_write_t fd, const void *buf, size_t length);
    off_t (*trim)(bfile_io_write_t fd, off_t trim_pos);
    bfile_io_priority priority;
};
void bio_read_attach_priority(bfile_io_read_t fd, bio_get_priority priority, void *cntx);
void bio_write_attach_priority(bfile_io_write_t fd, bio_get_priority priority, void *cntx);
typedef struct bpool *bpool_t;
typedef struct bpool_status {
 unsigned pools;
 unsigned free;
 unsigned allocated;
} bpool_status;
bpool_t bpool_create(balloc_iface_t alloc, size_t nelem, size_t elem_size);
void bpool_destroy(bpool_t pool);
void *bpool_alloc(bpool_t pool, size_t size);
void bpool_free(bpool_t pool, void *ptr);
_Bool bpool_test_block(bpool_t pool, void *ptr);
void bpool_get_status(bpool_t pool, bpool_status *status);
balloc_iface_t bpool_alloc_iface(bpool_t pool);
void bpool_join(bpool_t parent, bpool_t child);
_Bool bpool_is_empty(bpool_t pool);
void bpool_detach(bpool_t parent, bpool_t child);
bpool_t bpool_last_child(bpool_t pool);
void bpool_dump(bpool_t pool);
typedef struct batom *batom_t;
typedef struct batom_pipe *batom_pipe_t;
typedef struct batom_accum *batom_accum_t;
typedef struct batom_factory *batom_factory_t;
typedef struct batom_vec {
    void *base;
    uint16_t len;
    _Bool dirty;
    uint8_t unused_flags;
} batom_vec;
typedef void (*batom_user_free)(
    batom_t atom,
    void *user
);
typedef struct batom_user {
    batom_user_free user_free;
    size_t user_size;
} batom_user;
typedef struct batom_cursor {
    const uint8_t *cursor;
    int left;
    uint16_t pos;
    uint16_t count;
    const batom_vec *vec;
} batom_cursor;
typedef struct batom_factory_stats {
    unsigned atom_live;
    unsigned atom_allocated;
    unsigned atom_freed;
    unsigned alloc_pool;
    unsigned alloc_arena;
    unsigned alloc_alloc;
    unsigned free_pool;
    unsigned free_arena;
    unsigned free_alloc;
    unsigned full_pool;
    unsigned full_arena;
    bpool_status pool_status;
} batom_factory_stats;
typedef struct batom_checkpoint {
    int cp_left;
    unsigned cp_pos;
} batom_checkpoint;
batom_factory_t batom_factory_create(
    balloc_iface_t alloc,
    size_t natoms
    );
void batom_factory_destroy(
    batom_factory_t factory
    );
void batom_factory_get_stats(batom_factory_t factory, batom_factory_stats *stats);
void batom_factory_dump(batom_factory_t factory);
batom_accum_t batom_accum_create(
    batom_factory_t factory
    );
void batom_accum_clear(
    batom_accum_t acc
    );
void batom_accum_destroy(
    batom_accum_t acc
    );
size_t batom_accum_len(
    batom_accum_t acc
    );
const batom_vec *
batom_accum_get_vectors(
    batom_accum_t acc,
    unsigned *nvecs
    );
void batom_accum_dump(
    batom_accum_t acc,
    const char *name
    );
void batom_accum_add_vec(
    batom_accum_t acc,
    const batom_vec *vec
    );
void batom_accum_add_range(
    batom_accum_t acc,
    const void *base,
    size_t len
);
void batom_accum_add_atom(
    batom_accum_t acc,
    batom_t atom
    );
void batom_accum_trim(
    batom_accum_t acc,
    batom_cursor *cursor
    );
batom_t batom_accum_extract(
    batom_accum_t acc,
    const batom_cursor *first,
    const batom_cursor *last,
    const batom_user *user,
    const void *udata
);
_Bool batom_accum_append(
    batom_accum_t dst,
    batom_accum_t src,
    const batom_cursor *first,
    const batom_cursor *last
);
batom_t batom_from_vector(
    batom_factory_t factory,
    const batom_vec *vec,
    const batom_user *user,
    const void *udata
    );
batom_t batom_from_vectors(
    batom_factory_t factory,
    const batom_vec *vecs,
    unsigned nvecs,
    const batom_user *user,
    const void *udata
    );
batom_t batom_from_range(
    batom_factory_t factory,
    const void *base,
    size_t len,
    const batom_user *user,
    const void *udata
    );
batom_t batom_from_accum(
    batom_accum_t acc,
    const batom_user *user,
    const void *udata
    );
batom_t batom_clone(
    batom_t atom,
    const batom_user *user,
    const void *udata
    );
batom_t batom_from_range_and_atom(
    const void *base,
    size_t len,
    batom_t atom,
    const batom_user *user,
    const void *udata
    );
batom_t batom_from_vec_and_atom(
        const batom_vec *vec,
        batom_t atom,
        const batom_user *user,
        const void *udata
        );
batom_t batom_empty(
        batom_factory_t factory,
        const batom_user *user,
        const void *udata
        );
void batom_lock(
    batom_t atom
    );
void batom_release(
    batom_t atom
    );
size_t batom_len(
    batom_t atom
    );
const batom_vec *batom_get_vec(
    batom_t atom,
    unsigned vecno
    );
unsigned batom_get_nvecs(
    batom_t atom
    );
const batom_vec *
batom_get_vectors(
    batom_t atom,
    unsigned *nvecs
    );
void *batom_userdata(
    batom_t atom
    );
batom_t batom_extract(
    batom_t src,
    const batom_cursor *first,
    const batom_cursor *last,
    const batom_user *user,
    const void *udata
    );
void batom_dump(
    batom_t atom,
    const char *name
    );
void batom_cursor_from_vec(
    batom_cursor *cursor,
    const batom_vec *vec,
    unsigned count
    );
void batom_cursor_from_atom(
    batom_cursor *cursor,
    batom_t atom
    );
void batom_cursor_from_accum(
    batom_cursor *cursor,
    batom_accum_t acc
    );
void batom_cursor_empty(
    batom_cursor *cursor
    );
int batom_cursor_next(
    batom_cursor *cursor
    );
_Bool batom_cursor_eof(
    const batom_cursor *cursor
    );
size_t batom_cursor_skip(
    batom_cursor *cursor,
    size_t count
    );
size_t batom_cursor_copy(
    batom_cursor *cursor,
    void *dest,
    size_t count
    );
size_t batom_cursor_extract (
    const batom_cursor *cursor,
    batom_vec *vecs,
    size_t vec_size,
    size_t *required_vec_size
    );
size_t batom_cursor_distance(
    const batom_cursor *from,
    const batom_cursor *to
    );
void batom_cursor_save(
    const batom_cursor *cursor,
    batom_checkpoint *checkpoint
    );
void batom_cursor_rollback(
    batom_cursor *cursor,
    const batom_checkpoint *checkpoint
    );
void batom_cursor_clone(
    batom_cursor *dst,
    const batom_cursor *src
    );
size_t batom_cursor_pos(
    const batom_cursor *cursor
    );
size_t batom_cursor_size(
    const batom_cursor *cursor
    );
size_t batom_cursor_reserve(
    const batom_cursor *cursor,
    size_t count
    );
int batom_cursor_compare(
    const batom_cursor *cursor,
    const void *buff,
    size_t bytes
    );
void batom_cursor_dump(
    const batom_cursor *c,
    const char *name
    );
uint8_t batom_cursor_byte(
    batom_cursor *c
    );
uint16_t batom_cursor_uint16_le(
    batom_cursor *c
    );
uint16_t batom_cursor_uint16_be(
    batom_cursor *c
    );
uint32_t batom_cursor_uint32_le(
    batom_cursor *c
    );
uint32_t batom_cursor_uint32_be(
    batom_cursor *c
    );
uint64_t batom_cursor_uint64_le(
    batom_cursor *c
    );
uint64_t batom_cursor_uint64_be(
    batom_cursor *c
    );
uint32_t batom_cursor_uint24_le(batom_cursor *c);
uint32_t batom_cursor_uint24_be(
    batom_cursor *c
    );
uint32_t batom_cursor_vword_le(
    batom_cursor *c,
    unsigned bytes
    );
uint32_t batom_cursor_vword_be(
    batom_cursor *c,
    unsigned bytes
    );
const void *batom_cursor_continuous(
    const batom_cursor *c,
    size_t bytes
    );
int batom_cursor_memcmp(
    const batom_cursor *cursor,
    const void *data,
    size_t n
    );
void batom_range_dump(
    const void *data,
    size_t length,
    const char *name
    );
batom_pipe_t batom_pipe_create(
    batom_factory_t factory
    );
void batom_pipe_destroy(
    batom_pipe_t pipe
    );
void batom_pipe_flush(
    batom_pipe_t pipe
    );
void batom_pipe_push(
    batom_pipe_t pipe,
    batom_t atom
    );
batom_t batom_pipe_peek(
    batom_pipe_t pipe
    );
batom_t batom_pipe_pop(
    batom_pipe_t pipe
    );
void batom_pipe_drop(batom_pipe_t pipe);
void batom_vec_init(
    batom_vec *vec,
    const void *base,
    size_t len
    );
typedef struct batom_bitstream {
    batom_cursor *cursor;
    uint32_t cache;
    int cache_pos;
} batom_bitstream;
void batom_bitstream_init(
    batom_bitstream *bs,
    batom_cursor *cursor
    );
_Bool batom_bitstream_eof(
    batom_bitstream *bs
    );
int batom_bitstream_show(
    batom_bitstream *bs
    );
int batom_bitstream_bit(
    batom_bitstream *bs
    );
int batom_bitstream_drop(
    batom_bitstream *bs
    );
unsigned batom_bitstream_bits(
    batom_bitstream *bs,
    unsigned nbits
    );
void batom_bitstream_drop_bits(
    batom_bitstream *bs,
    unsigned nbits
    );
unsigned batom_bitstream_exp_golomb(
    batom_bitstream *bs
   );
void batom_bitstream_dump(
    const batom_bitstream *bs
    );
size_t batom_bitstream_position(
    const batom_bitstream *bs
    );
size_t batom_bitstream_bit_position(
    const batom_bitstream *bs
    );
typedef struct bfile_buffer *bfile_buffer_t;
typedef enum bfile_buffer_overflow_action {
    bfile_buffer_overflow_action_wait,
    bfile_buffer_overflow_action_abort
} bfile_buffer_overflow_action;
typedef struct bfile_buffer_cfg {
 _Bool async;
 unsigned nsegs;
 size_t buf_len;
 void *buf;
 void *sync_cnxt;
 bfile_io_read_t fd;
 void (*async_read)(void *sync_cnxt, bfile_io_read_t fd, void *buf, size_t length, void (*read_cont)(void *cont, ssize_t size), void *cntx);
    bfile_buffer_overflow_action (*async_overflow)(void *sync_cnxt);
} bfile_buffer_cfg;
typedef enum bfile_buffer_result {
 bfile_buffer_result_ok,
 bfile_buffer_result_read_error,
 bfile_buffer_result_eof,
    bfile_buffer_result_no_data,
 bfile_buffer_result_async,
 bfile_buffer_result_buffer_overflow
} bfile_buffer_result;
void bfile_buffer_default_cfg(bfile_buffer_cfg *cfg);
bfile_buffer_t bfile_buffer_create(batom_factory_t factory, bfile_buffer_cfg *cfg);
void bfile_buffer_clear(bfile_buffer_t buf);
void bfile_buffer_destroy(bfile_buffer_t buf);
batom_t bfile_buffer_async_read(bfile_buffer_t buf, off_t off, size_t length, bfile_buffer_result *result, void (*read_complete)(void *, batom_t, bfile_buffer_result ), void *cntx);
batom_t bfile_buffer_read(bfile_buffer_t buf, off_t off, size_t length, bfile_buffer_result *result);
int bfile_buffer_get_bounds(bfile_buffer_t buf, off_t *first, off_t *last);
typedef struct BKNI_EventObj *BKNI_EventHandle;
BERR_Code BKNI_Init(void);
void BKNI_Uninit(void);
void *BKNI_Memset(void *mem, int ch, size_t n);
void *BKNI_Memcpy(void *dest, const void *src, size_t n);
int BKNI_Memcmp(
    const void *s1,
    const void *s2,
    size_t n
    );
void *BKNI_Memchr(const void *mem, int ch, size_t n);
void *BKNI_Memmove(
    void *dest,
    const void *src,
    size_t n
    );
int BKNI_Printf(
    const char *fmt,
    ...
    ) __attribute__((format (printf, 1, 2)));
int BKNI_Snprintf(
    char *s,
    size_t n,
    const char *fmt,
    ...
    ) __attribute__((format (printf, 3, 4)));
int BKNI_Vprintf(const char *fmt, va_list ap);
int BKNI_Vsnprintf(char *s, size_t n, const char *fmt, va_list ap);
void BKNI_Delay(unsigned int microsec);
void *BKNI_Malloc(
    size_t size
    );
void BKNI_Free(
    void *mem
    );
BERR_Code BKNI_Sleep(
    unsigned int millisec
    );
BERR_Code BKNI_CreateEvent(BKNI_EventHandle *event);
void BKNI_DestroyEvent(BKNI_EventHandle event);
BERR_Code BKNI_WaitForEvent(BKNI_EventHandle event, int timeoutMsec);
void BKNI_SetEvent(BKNI_EventHandle event);
void BKNI_ResetEvent(BKNI_EventHandle event);
void BKNI_Fail(void) __attribute__ ((noreturn)) ;
void BKNI_EnterCriticalSection(void);
void BKNI_LeaveCriticalSection(void);
void BKNI_AssertTaskContext(const char *filename, unsigned lineno);
void BKNI_AssertIsrContext_isr(const char *filename, unsigned lineno);
typedef struct BKNI_MallocEntryInfo {
    const void *mem;
    size_t size;
    const char *malloc_file;
    unsigned malloc_line;
    _Bool alive;
    const char *free_file;
    unsigned free_line;
} BKNI_MallocEntryInfo;
BERR_Code BKNI_GetMallocEntryInfo(
    const void *memory,
    BKNI_MallocEntryInfo *info
    );
typedef struct BKNI_MutexObj *BKNI_MutexHandle;
BERR_Code BKNI_CreateMutex(BKNI_MutexHandle *mutex);
void BKNI_DestroyMutex(BKNI_MutexHandle mutex);
BERR_Code BKNI_TryAcquireMutex(
    BKNI_MutexHandle mutex
    );
BERR_Code BKNI_AcquireMutex(
    BKNI_MutexHandle mutex
    );
void BKNI_ReleaseMutex(BKNI_MutexHandle mutex);
typedef struct BKNI_MutexSettings {
    _Bool suspended;
} BKNI_MutexSettings;
void BKNI_GetMutexSettings(BKNI_MutexHandle mutex, BKNI_MutexSettings *pSettings);
BERR_Code BKNI_SetMutexSettings(BKNI_MutexHandle mutex, const BKNI_MutexSettings *pSettings);
struct BLST_AA_Tree_Node;
struct BLST_AA_Tree_Node {
    struct { struct BLST_AA_Tree_Node *aan_parent, *aan_left, *aan_right; unsigned aan_level; } aa_node;
};
struct BLST_AA_Tree_Head {
    struct BLST_AA_Tree_Node aat_root;
};
void BLST_AAT_P_Init(struct BLST_AA_Tree_Head *tree);
struct BLST_AA_Tree_Node *BLST_AAT_P_First(const struct BLST_AA_Tree_Head *tree, unsigned off);
struct BLST_AA_Tree_Node *BLST_AAT_P_Last(const struct BLST_AA_Tree_Head *tree, unsigned off);
struct BLST_AA_Tree_Node *BLST_AAT_P_Next(struct BLST_AA_Tree_Head *tree, struct BLST_AA_Tree_Node *node, unsigned off);
struct BLST_AA_Tree_Node *BLST_AAT_P_Prev(struct BLST_AA_Tree_Head *tree, struct BLST_AA_Tree_Node *node, unsigned off);
void BLST_AAT_P_Insert_Node(struct BLST_AA_Tree_Head *tree, struct BLST_AA_Tree_Node *new_node, struct BLST_AA_Tree_Node *parent, int cmp);
void BLST_AAT_P_Remove(struct BLST_AA_Tree_Head *tree, struct BLST_AA_Tree_Node *node);
typedef enum BM2MC_PACKET_PacketType
{
    BM2MC_PACKET_PacketType_eSourceFeeder = 1,
    BM2MC_PACKET_PacketType_eSourceFeeders,
    BM2MC_PACKET_PacketType_eStripedSourceFeeders,
    BM2MC_PACKET_PacketType_eSourceColor,
    BM2MC_PACKET_PacketType_eSourceNone,
    BM2MC_PACKET_PacketType_eSourceControl,
    BM2MC_PACKET_PacketType_eDestinationFeeder,
    BM2MC_PACKET_PacketType_eDestinationColor,
    BM2MC_PACKET_PacketType_eDestinationNone,
    BM2MC_PACKET_PacketType_eDestinationControl,
    BM2MC_PACKET_PacketType_eOutputFeeder,
    BM2MC_PACKET_PacketType_eOutputControl,
    BM2MC_PACKET_PacketType_eBlend,
    BM2MC_PACKET_PacketType_eBlendColor,
    BM2MC_PACKET_PacketType_eRop,
    BM2MC_PACKET_PacketType_eSourceColorkey,
    BM2MC_PACKET_PacketType_eSourceColorkeyEnable,
    BM2MC_PACKET_PacketType_eDestinationColorkey,
    BM2MC_PACKET_PacketType_eDestinationColorkeyEnable,
    BM2MC_PACKET_PacketType_eFilter,
    BM2MC_PACKET_PacketType_eFilterEnable,
    BM2MC_PACKET_PacketType_eFilterControl,
    BM2MC_PACKET_PacketType_eSourceColorMatrix,
    BM2MC_PACKET_PacketType_eSourceColorMatrixEnable,
    BM2MC_PACKET_PacketType_eSourcePalette,
    BM2MC_PACKET_PacketType_eAlphaPremultiply,
    BM2MC_PACKET_PacketType_eAlphaDemultiply,
    BM2MC_PACKET_PacketType_eDestAlphaPremultiply,
    BM2MC_PACKET_PacketType_eMirror,
    BM2MC_PACKET_PacketType_eFixedScale,
    BM2MC_PACKET_PacketType_eDestripeFixedScale,
    BM2MC_PACKET_PacketType_eFillBlit,
    BM2MC_PACKET_PacketType_eCopyBlit,
    BM2MC_PACKET_PacketType_eBlendBlit,
    BM2MC_PACKET_PacketType_eScaleBlit,
    BM2MC_PACKET_PacketType_eScaleBlendBlit,
    BM2MC_PACKET_PacketType_eUpdateScaleBlit,
    BM2MC_PACKET_PacketType_eDestripeBlit,
    BM2MC_PACKET_PacketType_eResetState,
    BM2MC_PACKET_PacketType_eSaveState,
    BM2MC_PACKET_PacketType_eRestoreState,
    BM2MC_PACKET_PacketType_eMax
}
BM2MC_PACKET_PacketType;
typedef struct
{
    uint8_t type;
    uint8_t size;
    _Bool execute;
    _Bool sync;
}
BM2MC_PACKET_Header;
typedef enum BM2MC_PACKET_PixelFormat
{
    BM2MC_PACKET_PixelFormat_eUnknown = 0,
    BM2MC_PACKET_PixelFormat_eR5_G6_B5,
    BM2MC_PACKET_PixelFormat_eB5_G6_R5,
    BM2MC_PACKET_PixelFormat_eA1_R5_G5_B5,
    BM2MC_PACKET_PixelFormat_eX1_R5_G5_B5,
    BM2MC_PACKET_PixelFormat_eA1_B5_G5_R5,
    BM2MC_PACKET_PixelFormat_eX1_B5_G5_R5,
    BM2MC_PACKET_PixelFormat_eR5_G5_B5_A1,
    BM2MC_PACKET_PixelFormat_eR5_G5_B5_X1,
    BM2MC_PACKET_PixelFormat_eB5_G5_R5_A1,
    BM2MC_PACKET_PixelFormat_eB5_G5_R5_X1,
    BM2MC_PACKET_PixelFormat_eA4_R4_G4_B4,
    BM2MC_PACKET_PixelFormat_eX4_R4_G4_B4,
    BM2MC_PACKET_PixelFormat_eA4_B4_G4_R4,
    BM2MC_PACKET_PixelFormat_eX4_B4_G4_R4,
    BM2MC_PACKET_PixelFormat_eR4_G4_B4_A4,
    BM2MC_PACKET_PixelFormat_eR4_G4_B4_X4,
    BM2MC_PACKET_PixelFormat_eB4_G4_R4_A4,
    BM2MC_PACKET_PixelFormat_eB4_G4_R4_X4,
    BM2MC_PACKET_PixelFormat_eA8_R8_G8_B8,
    BM2MC_PACKET_PixelFormat_eX8_R8_G8_B8,
    BM2MC_PACKET_PixelFormat_eA8_B8_G8_R8,
    BM2MC_PACKET_PixelFormat_eX8_B8_G8_R8,
    BM2MC_PACKET_PixelFormat_eR8_G8_B8_A8,
    BM2MC_PACKET_PixelFormat_eR8_G8_B8_X8,
    BM2MC_PACKET_PixelFormat_eB8_G8_R8_A8,
    BM2MC_PACKET_PixelFormat_eB8_G8_R8_X8,
    BM2MC_PACKET_PixelFormat_eA8,
    BM2MC_PACKET_PixelFormat_eA4,
    BM2MC_PACKET_PixelFormat_eA2,
    BM2MC_PACKET_PixelFormat_eA1,
    BM2MC_PACKET_PixelFormat_eW1,
    BM2MC_PACKET_PixelFormat_eA8_P8,
    BM2MC_PACKET_PixelFormat_eP8,
    BM2MC_PACKET_PixelFormat_eP4,
    BM2MC_PACKET_PixelFormat_eP2,
    BM2MC_PACKET_PixelFormat_eP1,
    BM2MC_PACKET_PixelFormat_eY8_P8,
    BM2MC_PACKET_PixelFormat_eA8_Y8,
    BM2MC_PACKET_PixelFormat_eCb8,
    BM2MC_PACKET_PixelFormat_eCr8,
    BM2MC_PACKET_PixelFormat_eY8,
    BM2MC_PACKET_PixelFormat_eCb8_Cr8,
    BM2MC_PACKET_PixelFormat_eCr8_Cb8,
    BM2MC_PACKET_PixelFormat_eY10,
    BM2MC_PACKET_PixelFormat_eCb10_Cr10,
    BM2MC_PACKET_PixelFormat_eCr10_Cb10,
    BM2MC_PACKET_PixelFormat_eY08_Cb8_Y18_Cr8,
    BM2MC_PACKET_PixelFormat_eY08_Cr8_Y18_Cb8,
    BM2MC_PACKET_PixelFormat_eY18_Cb8_Y08_Cr8,
    BM2MC_PACKET_PixelFormat_eY18_Cr8_Y08_Cb8,
    BM2MC_PACKET_PixelFormat_eCb8_Y08_Cr8_Y18,
    BM2MC_PACKET_PixelFormat_eCb8_Y18_Cr8_Y08,
    BM2MC_PACKET_PixelFormat_eCr8_Y18_Cb8_Y08,
    BM2MC_PACKET_PixelFormat_eCr8_Y08_Cb8_Y18,
    BM2MC_PACKET_PixelFormat_eX2_Cr10_Y10_Cb10,
    BM2MC_PACKET_PixelFormat_eA8_Y8_Cb8_Cr8,
    BM2MC_PACKET_PixelFormat_eA8_Cr8_Cb8_Y8,
    BM2MC_PACKET_PixelFormat_eCr8_Cb8_Y8_A8,
    BM2MC_PACKET_PixelFormat_eY8_Cb8_Cr8_A8,
    BM2MC_PACKET_PixelFormat_eY010_Cb10_Y110_Cr10,
    BM2MC_PACKET_PixelFormat_eY010_Cr10_Y110_Cb10,
    BM2MC_PACKET_PixelFormat_eY110_Cb10_Y010_Cr10,
    BM2MC_PACKET_PixelFormat_eY110_Cr10_Y010_Cb10,
    BM2MC_PACKET_PixelFormat_eCb10_Y010_Cr10_Y110,
    BM2MC_PACKET_PixelFormat_eCb10_Y110_Cr10_Y010,
    BM2MC_PACKET_PixelFormat_eCr10_Y110_Cb10_Y010,
    BM2MC_PACKET_PixelFormat_eCr10_Y010_Cb10_Y110,
    BM2MC_PACKET_PixelFormat_eL8,
    BM2MC_PACKET_PixelFormat_eL4_A4,
    BM2MC_PACKET_PixelFormat_eL8_A8,
    BM2MC_PACKET_PixelFormat_eL15_L05_A6,
    BM2MC_PACKET_PixelFormat_eCompressed_A8_R8_G8_B8,
    BM2MC_PACKET_PixelFormat_eR8_G8_B8,
    BM2MC_PACKET_PixelFormat_eYCbCr422_10bit,
    BM2MC_PACKET_PixelFormat_eMax
}
BM2MC_PACKET_PixelFormat;
typedef struct BM2MC_PACKET_Plane
{
    uint64_t address;
    uint16_t pitch;
    uint8_t format;
    uint16_t width;
    uint16_t height;
}
BM2MC_PACKET_Plane;
typedef struct BM2MC_PACKET_PacketSourceFeeder
{
    BM2MC_PACKET_Header header;
    BM2MC_PACKET_Plane plane;
    uint32_t color;
}
BM2MC_PACKET_PacketSourceFeeder;
typedef struct BM2MC_PACKET_PacketSourceFeeders
{
    BM2MC_PACKET_Header header;
    BM2MC_PACKET_Plane plane0;
    BM2MC_PACKET_Plane plane1;
    uint32_t color;
}
BM2MC_PACKET_PacketSourceFeeders;
typedef struct BM2MC_PACKET_StripedPlane
{
    uint64_t luma_address;
    uint64_t chroma_address;
    uint64_t bottom_field_luma_address;
    uint64_t bottom_field_chroma_address;
    uint16_t width;
    uint16_t height;
    uint16_t stripe_width;
    uint16_t stripe_pitch;
    uint16_t luma_stripe_height;
    uint16_t chroma_stripe_height;
    uint8_t luma_format;
    uint8_t chroma_format;
    uint8_t reserved[2];
}
BM2MC_PACKET_StripedPlane;
typedef struct BM2MC_PACKET_PacketStripedSourceFeeders
{
    BM2MC_PACKET_Header header;
    BM2MC_PACKET_StripedPlane plane;
    uint32_t color;
}
BM2MC_PACKET_PacketStripedSourceFeeders;
typedef struct BM2MC_PACKET_PacketSourceColor
{
    BM2MC_PACKET_Header header;
    uint32_t color;
}
BM2MC_PACKET_PacketSourceColor;
typedef struct BM2MC_PACKET_PacketSourceNone
{
    BM2MC_PACKET_Header header;
}
BM2MC_PACKET_PacketSourceNone;
typedef struct BM2MC_PACKET_PacketSourceControl
{
    BM2MC_PACKET_Header header;
    _Bool zero_pad;
    _Bool chroma_filter;
    _Bool linear_destripe;
    uint8_t reserved[1];
}
BM2MC_PACKET_PacketSourceControl;
typedef struct BM2MC_PACKET_PacketDestinationFeeder
{
    BM2MC_PACKET_Header header;
    BM2MC_PACKET_Plane plane;
    uint32_t color;
}
BM2MC_PACKET_PacketDestinationFeeder;
typedef struct BM2MC_PACKET_PacketDestinationColor
{
    BM2MC_PACKET_Header header;
    uint32_t color;
}
BM2MC_PACKET_PacketDestinationColor;
typedef struct BM2MC_PACKET_PacketDestinationNone
{
    BM2MC_PACKET_Header header;
}
BM2MC_PACKET_PacketDestinationNone;
typedef struct BM2MC_PACKET_PacketDestinationControl
{
    BM2MC_PACKET_Header header;
    _Bool zero_pad;
    _Bool chroma_filter;
    uint8_t reserved[2];
}
BM2MC_PACKET_PacketDestinationControl;
typedef struct BM2MC_PACKET_PacketOutputFeeder
{
    BM2MC_PACKET_Header header;
    BM2MC_PACKET_Plane plane;
}
BM2MC_PACKET_PacketOutputFeeder;
typedef struct BM2MC_PACKET_PacketOutputControl
{
    BM2MC_PACKET_Header header;
    _Bool dither;
    _Bool chroma_filter;
    uint8_t reserved[2];
}
BM2MC_PACKET_PacketOutputControl;
typedef enum BM2MC_PACKET_BlendFactor
{
    BM2MC_PACKET_BlendFactor_eZero = 0,
    BM2MC_PACKET_BlendFactor_eHalf,
    BM2MC_PACKET_BlendFactor_eOne,
    BM2MC_PACKET_BlendFactor_eSourceColor,
    BM2MC_PACKET_BlendFactor_eInverseSourceColor,
    BM2MC_PACKET_BlendFactor_eSourceAlpha,
    BM2MC_PACKET_BlendFactor_eInverseSourceAlpha,
    BM2MC_PACKET_BlendFactor_eDestinationColor,
    BM2MC_PACKET_BlendFactor_eInverseDestinationColor,
    BM2MC_PACKET_BlendFactor_eDestinationAlpha,
    BM2MC_PACKET_BlendFactor_eInverseDestinationAlpha,
    BM2MC_PACKET_BlendFactor_eConstantColor,
    BM2MC_PACKET_BlendFactor_eInverseConstantColor,
    BM2MC_PACKET_BlendFactor_eConstantAlpha,
    BM2MC_PACKET_BlendFactor_eInverseConstantAlpha
}
BM2MC_PACKET_BlendFactor;
typedef struct BM2MC_PACKET_Blend
{
    uint8_t a;
    uint8_t b;
    _Bool sub_cd;
    uint8_t c;
    uint8_t d;
    _Bool sub_e;
    uint8_t e;
}
BM2MC_PACKET_Blend;
typedef struct BM2MC_PACKET_PacketBlend
{
    BM2MC_PACKET_Header header;
    BM2MC_PACKET_Blend color_blend;
    BM2MC_PACKET_Blend alpha_blend;
    uint32_t color;
}
BM2MC_PACKET_PacketBlend;
typedef struct BM2MC_PACKET_PacketBlendColor
{
    BM2MC_PACKET_Header header;
    uint32_t color;
}
BM2MC_PACKET_PacketBlendColor;
typedef struct BM2MC_PACKET_PacketRop
{
    BM2MC_PACKET_Header header;
    uint32_t rop;
    uint32_t pattern0;
    uint32_t pattern1;
    uint32_t color0;
    uint32_t color1;
}
BM2MC_PACKET_PacketRop;
typedef struct BM2MC_PACKET_PacketSourceColorkey
{
    BM2MC_PACKET_Header header;
    uint32_t high;
    uint32_t low;
    uint32_t mask;
    uint32_t replacement;
    uint32_t replacement_mask;
    _Bool exclusive;
}
BM2MC_PACKET_PacketSourceColorkey;
typedef struct BM2MC_PACKET_PacketSourceColorkeyEnable
{
    BM2MC_PACKET_Header header;
    _Bool enable;
    uint8_t reserved[3];
}
BM2MC_PACKET_PacketSourceColorkeyEnable;
typedef struct BM2MC_PACKET_PacketDestinationColorkey
{
    BM2MC_PACKET_Header header;
    uint32_t high;
    uint32_t low;
    uint32_t mask;
    uint32_t replacement;
    uint32_t replacement_mask;
    _Bool exclusive;
}
BM2MC_PACKET_PacketDestinationColorkey;
typedef struct BM2MC_PACKET_PacketDestinationColorkeyEnable
{
    BM2MC_PACKET_Header header;
    _Bool enable;
    uint8_t reserved[3];
}
BM2MC_PACKET_PacketDestinationColorkeyEnable;
typedef struct BM2MC_PACKET_FilterCoeffs
{
    int16_t coeffs[2][3];
}
BM2MC_PACKET_FilterCoeffs;
typedef struct BM2MC_PACKET_PacketFilter
{
    BM2MC_PACKET_Header header;
    BM2MC_PACKET_FilterCoeffs hor;
    BM2MC_PACKET_FilterCoeffs ver;
}
BM2MC_PACKET_PacketFilter;
typedef struct BM2MC_PACKET_PacketFilterEnable
{
    BM2MC_PACKET_Header header;
    _Bool enable;
    uint8_t reserved[3];
}
BM2MC_PACKET_PacketFilterEnable;
typedef enum BM2MC_PACKET_eFilterOrder
{
    BM2MC_PACKET_eFilterOrder_FilterColorkeyMatrix = 0,
    BM2MC_PACKET_eFilterOrder_FilterMatrixColorkey,
    BM2MC_PACKET_eFilterOrder_ColorkeyMatrixFilter,
    BM2MC_PACKET_eFilterOrder_ColorkeyFilterMatrix,
    BM2MC_PACKET_eFilterOrder_MatrixFilterColorkey,
    BM2MC_PACKET_eFilterOrder_MatrixColorkeyFilter,
    BM2MC_PACKET_eFilterOrder_BypassAll
}
BM2MC_PACKET_eFilterOrder;
typedef struct BM2MC_PACKET_PacketFilterControl
{
    BM2MC_PACKET_Header header;
    _Bool round;
    _Bool adjust_color;
    _Bool sub_alpha;
    uint8_t order;
}
BM2MC_PACKET_PacketFilterControl;
typedef struct BM2MC_PACKET_ColorMatrix
{
    int16_t m[4][5];
}
BM2MC_PACKET_ColorMatrix;
typedef struct BM2MC_PACKET_PacketSourceColorMatrix
{
    BM2MC_PACKET_Header header;
    BM2MC_PACKET_ColorMatrix matrix;
}
BM2MC_PACKET_PacketSourceColorMatrix;
typedef struct BM2MC_PACKET_PacketSourceColorMatrixEnable
{
    BM2MC_PACKET_Header header;
    _Bool enable;
    uint8_t reserved[3];
}
BM2MC_PACKET_PacketSourceColorMatrixEnable;
typedef struct BM2MC_PACKET_PacketSourcePalette
{
    BM2MC_PACKET_Header header;
    uint64_t address;
}
BM2MC_PACKET_PacketSourcePalette;
typedef struct BM2MC_PACKET_PacketAlphaPremultiply
{
    BM2MC_PACKET_Header header;
    _Bool enable;
    uint8_t reserved[3];
}
BM2MC_PACKET_PacketAlphaPremultiply;
typedef struct BM2MC_PACKET_PacketAlphaDemultiply
{
    BM2MC_PACKET_Header header;
    _Bool enable;
    uint8_t reserved[3];
}
BM2MC_PACKET_PacketAlphaDemultiply;
typedef struct BM2MC_PACKET_PacketDestAlphaPremultiply
{
    BM2MC_PACKET_Header header;
    _Bool enable;
    uint8_t reserved[3];
}
BM2MC_PACKET_PacketDestAlphaPremultiply;
typedef struct BM2MC_PACKET_PacketMirror
{
    BM2MC_PACKET_Header header;
    _Bool src_hor;
    _Bool src_ver;
    _Bool dst_hor;
    _Bool dst_ver;
    _Bool out_hor;
    _Bool out_ver;
    uint8_t reserved[2];
}
BM2MC_PACKET_PacketMirror;
typedef struct BM2MC_PACKET_Point
{
    uint16_t x;
    uint16_t y;
}
BM2MC_PACKET_Point;
typedef struct BM2MC_PACKET_Size
{
    uint16_t width;
    uint16_t height;
}
BM2MC_PACKET_Size;
typedef struct BM2MC_PACKET_Rectangle
{
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
}
BM2MC_PACKET_Rectangle;
typedef struct BM2MC_PACKET_PacketFixedScale
{
    BM2MC_PACKET_Header header;
    int32_t hor_phase;
    int32_t ver_phase;
    uint32_t hor_step;
    uint32_t ver_step;
    uint32_t shift;
}
BM2MC_PACKET_PacketFixedScale;
typedef struct BM2MC_PACKET_PacketDestripeFixedScale
{
    BM2MC_PACKET_Header header;
    BM2MC_PACKET_Rectangle chroma_rect;
    int32_t hor_luma_phase;
    int32_t ver_luma_phase;
    int32_t hor_chroma_phase;
    int32_t ver_chroma_phase;
    uint32_t hor_luma_step;
    uint32_t ver_luma_step;
    uint32_t shift;
}
BM2MC_PACKET_PacketDestripeFixedScale;
typedef struct BM2MC_PACKET_PacketFillBlit
{
    BM2MC_PACKET_Header header;
    BM2MC_PACKET_Rectangle rect;
}
BM2MC_PACKET_PacketFillBlit;
typedef struct BM2MC_PACKET_PacketCopyBlit
{
    BM2MC_PACKET_Header header;
    BM2MC_PACKET_Rectangle src_rect;
    BM2MC_PACKET_Point out_point;
}
BM2MC_PACKET_PacketCopyBlit;
typedef struct BM2MC_PACKET_PacketBlendBlit
{
    BM2MC_PACKET_Header header;
    BM2MC_PACKET_Rectangle src_rect;
    BM2MC_PACKET_Point out_point;
    BM2MC_PACKET_Point dst_point;
}
BM2MC_PACKET_PacketBlendBlit;
typedef struct BM2MC_PACKET_PacketScaleBlit
{
    BM2MC_PACKET_Header header;
    BM2MC_PACKET_Rectangle src_rect;
    BM2MC_PACKET_Rectangle out_rect;
}
BM2MC_PACKET_PacketScaleBlit;
typedef struct BM2MC_PACKET_PacketScaleBlendBlit
{
    BM2MC_PACKET_Header header;
    BM2MC_PACKET_Rectangle src_rect;
    BM2MC_PACKET_Rectangle out_rect;
    BM2MC_PACKET_Point dst_point;
}
BM2MC_PACKET_PacketScaleBlendBlit;
typedef struct BM2MC_PACKET_PacketUpdateScaleBlit
{
    BM2MC_PACKET_Header header;
    BM2MC_PACKET_Rectangle src_rect;
    BM2MC_PACKET_Rectangle out_rect;
    BM2MC_PACKET_Rectangle update_rect;
}
BM2MC_PACKET_PacketUpdateScaleBlit;
typedef struct BM2MC_PACKET_PacketDestripeBlit
{
    BM2MC_PACKET_Header header;
    BM2MC_PACKET_Rectangle src_rect;
    BM2MC_PACKET_Rectangle out_rect;
    BM2MC_PACKET_Point dst_point;
    uint16_t source_stripe_width;
    uint16_t luma_stripe_height;
    uint16_t chroma_stripe_height;
    uint8_t reserved[2];
}
BM2MC_PACKET_PacketDestripeBlit;
typedef struct BM2MC_PACKET_PacketResetState
{
    BM2MC_PACKET_Header header;
}
BM2MC_PACKET_PacketResetState;
typedef struct BM2MC_PACKET_PacketSaveState
{
    BM2MC_PACKET_Header header;
}
BM2MC_PACKET_PacketSaveState;
typedef struct BM2MC_PACKET_PacketRestoreState
{
    BM2MC_PACKET_Header header;
}
BM2MC_PACKET_PacketRestoreState;
typedef struct BM2MC_PACKET_PacketAll {
    union {
        BM2MC_PACKET_PacketSourceFeeder packetSourceFeeder;
        BM2MC_PACKET_PacketSourceFeeders packetSourceFeeders;
        BM2MC_PACKET_PacketStripedSourceFeeders packetStripedSourceFeeders;
        BM2MC_PACKET_PacketSourceColor packetSourceColor;
        BM2MC_PACKET_PacketSourceNone packetSourceNone;
        BM2MC_PACKET_PacketSourceControl packetSourceControl;
        BM2MC_PACKET_PacketDestinationFeeder packetDestinationFeeder;
        BM2MC_PACKET_PacketDestinationColor packetDestinationColor;
        BM2MC_PACKET_PacketDestinationNone packetDestinationNone;
        BM2MC_PACKET_PacketDestinationControl packetDestinationControl;
        BM2MC_PACKET_PacketOutputFeeder packetOutputFeeder;
        BM2MC_PACKET_PacketOutputControl packetOutputControl;
        BM2MC_PACKET_PacketBlend packetBlend;
        BM2MC_PACKET_PacketBlendColor packetBlendColor;
        BM2MC_PACKET_PacketRop packetRop;
        BM2MC_PACKET_PacketSourceColorkey packetSourceColorkey;
        BM2MC_PACKET_PacketSourceColorkeyEnable packetSourceColorkeyEnable;
        BM2MC_PACKET_PacketDestinationColorkey packetDestinationColorkey;
        BM2MC_PACKET_PacketDestinationColorkeyEnable packetDestinationColorkeyEnable;
        BM2MC_PACKET_PacketFilter packetFilter;
        BM2MC_PACKET_PacketFilterEnable packetFilterEnable;
        BM2MC_PACKET_PacketFilterControl packetFilterControl;
        BM2MC_PACKET_PacketSourceColorMatrix packetSourceColorMatrix;
        BM2MC_PACKET_PacketSourceColorMatrixEnable packetSourceColorMatrixEnable;
        BM2MC_PACKET_PacketSourcePalette packetSourcePalette;
        BM2MC_PACKET_PacketAlphaPremultiply packetAlphaPremultiply;
        BM2MC_PACKET_PacketAlphaDemultiply packetAlphaDemultiply;
        BM2MC_PACKET_PacketDestAlphaPremultiply packetDestAlphaPremultiply;
        BM2MC_PACKET_PacketMirror packetMirror;
        BM2MC_PACKET_PacketFixedScale packetFixedScale;
        BM2MC_PACKET_PacketDestripeFixedScale packetDestripeFixedScale;
        BM2MC_PACKET_PacketFillBlit packetFillBlit;
        BM2MC_PACKET_PacketCopyBlit packetCopyBlit;
        BM2MC_PACKET_PacketBlendBlit packetBlendBlit;
        BM2MC_PACKET_PacketScaleBlit packetScaleBlit;
        BM2MC_PACKET_PacketScaleBlendBlit packetScaleBlendBlit;
        BM2MC_PACKET_PacketUpdateScaleBlit packetUpdateScaleBlit;
        BM2MC_PACKET_PacketDestripeBlit packetDestripeBlit;
        BM2MC_PACKET_PacketResetState packetResetState;
        BM2MC_PACKET_PacketSaveState packetSaveState;
        BM2MC_PACKET_PacketRestoreState packetRestoreState;
    } data;
} BM2MC_PACKET_PacketAll;
typedef struct NEXUS_Heap *NEXUS_HeapHandle;
typedef struct NEXUS_ClientResourceIdList
{
    unsigned id[16];
    unsigned total;
} NEXUS_ClientResourceIdList;
typedef struct NEXUS_ClientResourceCount
{
    unsigned total;
} NEXUS_ClientResourceCount;
typedef struct NEXUS_ClientResources
{
    NEXUS_ClientResourceIdList simpleAudioDecoder;
    NEXUS_ClientResourceIdList simpleVideoDecoder;
    NEXUS_ClientResourceIdList simpleEncoder;
    NEXUS_ClientResourceIdList surfaceClient;
    NEXUS_ClientResourceIdList inputClient;
    NEXUS_ClientResourceIdList audioCapture;
    NEXUS_ClientResourceIdList audioCrc;
    NEXUS_ClientResourceCount dma;
    NEXUS_ClientResourceCount graphics2d;
    NEXUS_ClientResourceCount graphicsv3d;
    NEXUS_ClientResourceCount pictureDecoder;
    NEXUS_ClientResourceCount playpump;
    NEXUS_ClientResourceCount recpump;
    NEXUS_ClientResourceCount simpleAudioPlayback;
    NEXUS_ClientResourceCount simpleStcChannel;
    NEXUS_ClientResourceCount surface;
    struct {
        unsigned sizeLimit;
    } temporaryMemory;
} NEXUS_ClientResources;
typedef enum NEXUS_ClientMode
{
    NEXUS_ClientMode_eUnprotected,
    NEXUS_ClientMode_eVerified,
    NEXUS_ClientMode_eProtected,
    NEXUS_ClientMode_eUntrusted,
    NEXUS_ClientMode_eMax
} NEXUS_ClientMode;
typedef struct NEXUS_ClientConfiguration
{
    NEXUS_ClientMode mode;
    NEXUS_HeapHandle heap[24];
    NEXUS_ClientResources resources;
} NEXUS_ClientConfiguration;
typedef struct NEXUS_Certificate
{
    unsigned char data[256];
    unsigned length;
} NEXUS_Certificate;
typedef struct NEXUS_ClientAuthenticationSettings
{
    NEXUS_Certificate certificate;
} NEXUS_ClientAuthenticationSettings;
typedef unsigned NEXUS_Error;
typedef struct NEXUS_Module *NEXUS_ModuleHandle;
typedef void (*NEXUS_Callback)(void *context, int param);
typedef struct NEXUS_CallbackDesc {
    NEXUS_Callback callback;
    void *context;
    int param;
    unsigned private_cookie;
} NEXUS_CallbackDesc;
void NEXUS_CallbackDesc_Init(
    NEXUS_CallbackDesc *desc
    );
NEXUS_CallbackDesc NEXUS_P_CallbackDescByValue(void);
typedef enum NEXUS_ModulePriority
{
    NEXUS_ModulePriority_eIdle,
    NEXUS_ModulePriority_eLow,
    NEXUS_ModulePriority_eDefault,
    NEXUS_ModulePriority_eHigh,
    NEXUS_ModulePriority_eIdleActiveStandby,
    NEXUS_ModulePriority_eLowActiveStandby,
    NEXUS_ModulePriority_eDefaultActiveStandby,
    NEXUS_ModulePriority_eHighActiveStandby,
    NEXUS_ModulePriority_eMax
} NEXUS_ModulePriority;
typedef struct NEXUS_ModuleSettings
{
    NEXUS_ModulePriority priority;
    void (*dbgPrint)(void);
    const char *dbgModules;
    _Bool passthroughCallbacks;
} NEXUS_ModuleSettings;
typedef enum NEXUS_TristateEnable {
    NEXUS_TristateEnable_eDisable,
    NEXUS_TristateEnable_eEnable,
    NEXUS_TristateEnable_eNotSet,
    NEXUS_TristateEnable_eMax
} NEXUS_TristateEnable;
typedef uint64_t NEXUS_Addr;
typedef void *NEXUS_AnyObject;
typedef void *NEXUS_P_MemoryUserAddr;
typedef unsigned NEXUS_BaseObjectId;
typedef enum NEXUS_AudioCodec
{
    NEXUS_AudioCodec_eUnknown = 0,
    NEXUS_AudioCodec_eMpeg,
    NEXUS_AudioCodec_eMp3,
    NEXUS_AudioCodec_eAac,
    NEXUS_AudioCodec_eAacAdts=NEXUS_AudioCodec_eAac,
    NEXUS_AudioCodec_eAacLoas,
    NEXUS_AudioCodec_eAacPlus,
    NEXUS_AudioCodec_eAacPlusLoas =NEXUS_AudioCodec_eAacPlus,
    NEXUS_AudioCodec_eAacPlusAdts,
    NEXUS_AudioCodec_eAc3,
    NEXUS_AudioCodec_eAc3Plus,
    NEXUS_AudioCodec_eDts,
    NEXUS_AudioCodec_eLpcmDvd,
    NEXUS_AudioCodec_eLpcmHdDvd,
    NEXUS_AudioCodec_eLpcmBluRay,
    NEXUS_AudioCodec_eDtsHd,
    NEXUS_AudioCodec_eWmaStd,
    NEXUS_AudioCodec_eWmaStdTs,
    NEXUS_AudioCodec_eWmaPro,
    NEXUS_AudioCodec_eAvs,
    NEXUS_AudioCodec_ePcm,
    NEXUS_AudioCodec_ePcmWav,
    NEXUS_AudioCodec_eAmrNb,
    NEXUS_AudioCodec_eAmr=NEXUS_AudioCodec_eAmrNb,
    NEXUS_AudioCodec_eAmrWb,
    NEXUS_AudioCodec_eDra,
    NEXUS_AudioCodec_eCook,
    NEXUS_AudioCodec_eAdpcm,
    NEXUS_AudioCodec_eSbc,
    NEXUS_AudioCodec_eDtsCd,
    NEXUS_AudioCodec_eDtsLegacy=NEXUS_AudioCodec_eDtsCd,
    NEXUS_AudioCodec_eDtsExpress,
    NEXUS_AudioCodec_eVorbis,
    NEXUS_AudioCodec_eLpcm1394,
    NEXUS_AudioCodec_eG711,
    NEXUS_AudioCodec_eG723_1,
    NEXUS_AudioCodec_eG726,
    NEXUS_AudioCodec_eG729,
    NEXUS_AudioCodec_eFlac,
    NEXUS_AudioCodec_eMlp,
    NEXUS_AudioCodec_eApe,
    NEXUS_AudioCodec_eIlbc,
    NEXUS_AudioCodec_eIsac,
    NEXUS_AudioCodec_eOpus,
    NEXUS_AudioCodec_eAls,
    NEXUS_AudioCodec_eAlsLoas,
    NEXUS_AudioCodec_eAc4,
    NEXUS_AudioCodec_eMax
} NEXUS_AudioCodec;
typedef enum NEXUS_AudioConnectorType
{
    NEXUS_AudioConnectorType_eStereo,
    NEXUS_AudioConnectorType_eMultichannel,
    NEXUS_AudioConnectorType_eCompressed,
    NEXUS_AudioConnectorType_eCompressed4x,
    NEXUS_AudioConnectorType_eCompressed16x,
    NEXUS_AudioConnectorType_eMono,
    NEXUS_AudioConnectorType_eMax
} NEXUS_AudioConnectorType;
typedef enum NEXUS_AudioMultichannelFormat
{
    NEXUS_AudioMultichannelFormat_eNone,
    NEXUS_AudioMultichannelFormat_eStereo = NEXUS_AudioMultichannelFormat_eNone,
    NEXUS_AudioMultichannelFormat_e5_1,
    NEXUS_AudioMultichannelFormat_e7_1,
    NEXUS_AudioMultichannelFormat_eMax
} NEXUS_AudioMultichannelFormat;
typedef enum NEXUS_AudioChannel
{
    NEXUS_AudioChannel_eLeft,
    NEXUS_AudioChannel_eRight,
    NEXUS_AudioChannel_eLeftSurround,
    NEXUS_AudioChannel_eRightSurround,
    NEXUS_AudioChannel_eCenter,
    NEXUS_AudioChannel_eLfe,
    NEXUS_AudioChannel_eLeftRear,
    NEXUS_AudioChannel_eRightRear,
    NEXUS_AudioChannel_eMax
} NEXUS_AudioChannel;
typedef enum NEXUS_AudioChannelPair
{
    NEXUS_AudioChannelPair_eLeftRight,
    NEXUS_AudioChannelPair_eLeftRightSurround,
    NEXUS_AudioChannelPair_eCenterLfe,
    NEXUS_AudioChannelPair_eLeftRightRear,
    NEXUS_AudioChannelPair_eMax
} NEXUS_AudioChannelPair;
typedef enum NEXUS_AudioVolumeType
{
    NEXUS_AudioVolumeType_eDecibel,
    NEXUS_AudioVolumeType_eLinear,
    NEXUS_AudioVolumeType_eMax
} NEXUS_AudioVolumeType;
typedef enum NEXUS_AudioChannelMode
{
    NEXUS_AudioChannelMode_eStereo,
    NEXUS_AudioChannelMode_eLeft,
    NEXUS_AudioChannelMode_eRight,
    NEXUS_AudioChannelMode_eSwapped,
    NEXUS_AudioChannelMode_eMax
} NEXUS_AudioChannelMode;
typedef enum NEXUS_AudioMonoChannelMode
{
    NEXUS_AudioMonoChannelMode_eLeft,
    NEXUS_AudioMonoChannelMode_eRight,
    NEXUS_AudioMonoChannelMode_eMix,
    NEXUS_AudioMonoChannelMode_eMax
} NEXUS_AudioMonoChannelMode;
typedef enum NEXUS_AudioMode
{
    NEXUS_AudioMode_eAuto,
    NEXUS_AudioMode_e1_0,
    NEXUS_AudioMode_e1_1,
    NEXUS_AudioMode_e2_0,
    NEXUS_AudioMode_e3_0,
    NEXUS_AudioMode_e2_1,
    NEXUS_AudioMode_e3_1,
    NEXUS_AudioMode_e2_2,
    NEXUS_AudioMode_e3_2,
    NEXUS_AudioMode_e3_4,
    NEXUS_AudioMode_eMax
} NEXUS_AudioMode;
typedef struct NEXUS_AudioRawChannelStatus
{
    uint32_t leftChannelHigh;
    uint32_t leftChannelLow;
    uint32_t rightChannelHigh;
    uint32_t rightChannelLow;
} NEXUS_AudioRawChannelStatus;
typedef struct NEXUS_AudioChannelStatusInfo
{
    _Bool professionalMode;
    _Bool swCopyRight;
    uint16_t categoryCode;
    uint16_t clockAccuracy;
    _Bool separateLRChanNum;
    uint8_t cgmsA;
} NEXUS_AudioChannelStatusInfo;
typedef struct NEXUS_AudioInput *NEXUS_AudioInput;
typedef NEXUS_AudioInput NEXUS_AudioInputHandle;
typedef struct NEXUS_AudioOutput *NEXUS_AudioOutput;
typedef NEXUS_AudioOutput NEXUS_AudioOutputHandle;
typedef enum NEXUS_RfAudioEncoding
{
    NEXUS_RfAudioEncoding_eBtsc,
    NEXUS_RfAudioEncoding_eMax
} NEXUS_RfAudioEncoding;
typedef enum NEXUS_EchoCancellerAlgorithm
{
    NEXUS_EchoCancellerAlgorithm_eSpeex,
    NEXUS_EchoCancellerAlgorithm_eMax
} NEXUS_EchoCancellerAlgorithm;
typedef enum
{
    NEXUS_AudioOutputPll_e0,
    NEXUS_AudioOutputPll_e1,
    NEXUS_AudioOutputPll_e2,
    NEXUS_AudioOutputPll_e3,
    NEXUS_AudioOutputPll_eMax
} NEXUS_AudioOutputPll;
typedef enum
{
    NEXUS_AudioOutputNco_e0,
    NEXUS_AudioOutputNco_e1,
    NEXUS_AudioOutputNco_e2,
    NEXUS_AudioOutputNco_e3,
    NEXUS_AudioOutputNco_e4,
    NEXUS_AudioOutputNco_e5,
    NEXUS_AudioOutputNco_e6,
    NEXUS_AudioOutputNco_eMax
} NEXUS_AudioOutputNco;
typedef enum NEXUS_SpdifOutputBurstType
{
    NEXUS_SpdifOutputBurstType_eNull,
    NEXUS_SpdifOutputBurstType_ePause,
    NEXUS_SpdifOutputBurstType_eNone,
    NEXUS_SpdifOutputBurstType_eMax
}NEXUS_SpdifOutputBurstType;
typedef enum NEXUS_AudioLoudnessEquivalenceMode
{
    NEXUS_AudioLoudnessEquivalenceMode_eNone,
    NEXUS_AudioLoudnessEquivalenceMode_eAtscA85,
    NEXUS_AudioLoudnessEquivalenceMode_eEbuR128,
    NEXUS_AudioLoudnessEquivalenceMode_eMax
} NEXUS_AudioLoudnessEquivalenceMode;
typedef enum NEXUS_AudioDolbyCodecVersion
{
    NEXUS_AudioDolbyCodecVersion_eAc3,
    NEXUS_AudioDolbyCodecVersion_eAc3Plus,
    NEXUS_AudioDolbyCodecVersion_eMS10,
    NEXUS_AudioDolbyCodecVersion_eMS11,
    NEXUS_AudioDolbyCodecVersion_eMS12,
    NEXUS_AudioDolbyCodecVersion_eMax
} NEXUS_AudioDolbyCodecVersion;
typedef enum NEXUS_AudioPostProcessing
{
    NEXUS_AudioPostProcessing_eSampleRateConverter,
    NEXUS_AudioPostProcessing_eCustomVoice,
    NEXUS_AudioPostProcessing_eAutoVolumeLevel,
    NEXUS_AudioPostProcessing_eTrueSurround,
    NEXUS_AudioPostProcessing_eTruVolume,
    NEXUS_AudioPostProcessing_eDsola,
    NEXUS_AudioPostProcessing_eBtsc,
    NEXUS_AudioPostProcessing_eFade,
    NEXUS_AudioPostProcessing_eKaraokeVocal,
    NEXUS_AudioPostProcessing_eMax
} NEXUS_AudioPostProcessing;
typedef enum NEXUS_AudioLoudnessDeviceMode
{
    NEXUS_AudioLoudnessDeviceMode_eAuto,
    NEXUS_AudioLoudnessDeviceMode_eActive,
    NEXUS_AudioLoudnessDeviceMode_ePassive,
    NEXUS_AudioLoudnessDeviceMode_eMax
} NEXUS_AudioLoudnessDeviceMode;
typedef struct NEXUS_AudioFadeSettings
{
    unsigned level;
    unsigned duration;
    unsigned type;
} NEXUS_AudioFadeSettings;
typedef struct NEXUS_AudioFadeStatus
{
    _Bool active;
    unsigned remaining;
    unsigned level;
} NEXUS_AudioFadeStatus;
typedef struct NEXUS_AudioMixerInputSettings
{
    int32_t volumeMatrix[NEXUS_AudioChannel_eMax][NEXUS_AudioChannel_eMax];
    _Bool muted;
    NEXUS_AudioFadeSettings fade;
} NEXUS_AudioMixerInputSettings;
typedef struct NEXUS_AudioMixerInputStatus
{
    NEXUS_AudioFadeStatus fade;
} NEXUS_AudioMixerInputStatus;
typedef struct NEXUS_AudioMixerStatus
{
    NEXUS_AudioFadeStatus mainDecodeFade;
} NEXUS_AudioMixerStatus;
typedef enum NEXUS_VideoFrameRate {
    NEXUS_VideoFrameRate_eUnknown = 0,
    NEXUS_VideoFrameRate_e23_976,
    NEXUS_VideoFrameRate_e24,
    NEXUS_VideoFrameRate_e25,
    NEXUS_VideoFrameRate_e29_97,
    NEXUS_VideoFrameRate_e30,
    NEXUS_VideoFrameRate_e50,
    NEXUS_VideoFrameRate_e59_94,
    NEXUS_VideoFrameRate_e60,
    NEXUS_VideoFrameRate_e14_985,
    NEXUS_VideoFrameRate_e7_493,
    NEXUS_VideoFrameRate_e10,
    NEXUS_VideoFrameRate_e15,
    NEXUS_VideoFrameRate_e20,
    NEXUS_VideoFrameRate_e12_5,
    NEXUS_VideoFrameRate_e100,
    NEXUS_VideoFrameRate_e119_88,
    NEXUS_VideoFrameRate_e120,
    NEXUS_VideoFrameRate_e19_98,
    NEXUS_VideoFrameRate_e7_5,
    NEXUS_VideoFrameRate_e12,
    NEXUS_VideoFrameRate_e11_988,
    NEXUS_VideoFrameRate_e9_99,
    NEXUS_VideoFrameRate_eMax
} NEXUS_VideoFrameRate;
typedef enum NEXUS_VideoPolarity {
    NEXUS_VideoPolarity_ePositive,
    NEXUS_VideoPolarity_eNegative
} NEXUS_VideoPolarity ;
typedef enum NEXUS_VideoBufferType
{
   NEXUS_VideoBufferType_eFrame = 1,
   NEXUS_VideoBufferType_eFieldPair,
   NEXUS_VideoBufferType_eTopField,
   NEXUS_VideoBufferType_eBotField,
   NEXUS_VideoBufferType_eMax
} NEXUS_VideoBufferType;
typedef enum NEXUS_PicturePullDown
{
   NEXUS_PicturePullDown_eFrame,
   NEXUS_PicturePullDown_eTop,
   NEXUS_PicturePullDown_eBottom,
   NEXUS_PicturePullDown_eTopBottom,
   NEXUS_PicturePullDown_eBottomTop,
   NEXUS_PicturePullDown_eTopBottomTop,
   NEXUS_PicturePullDown_eBottomTopBottom,
   NEXUS_PicturePullDown_eMax
} NEXUS_PicturePullDown;
typedef enum NEXUS_VideoCodec {
    NEXUS_VideoCodec_eUnknown = 0,
    NEXUS_VideoCodec_eNone = 0,
    NEXUS_VideoCodec_eMpeg1,
    NEXUS_VideoCodec_eMpeg2,
    NEXUS_VideoCodec_eMpeg4Part2,
    NEXUS_VideoCodec_eH263,
    NEXUS_VideoCodec_eH264,
    NEXUS_VideoCodec_eH264_Svc,
    NEXUS_VideoCodec_eH264_Mvc,
    NEXUS_VideoCodec_eVc1,
    NEXUS_VideoCodec_eVc1SimpleMain,
    NEXUS_VideoCodec_eDivx311,
    NEXUS_VideoCodec_eAvs,
    NEXUS_VideoCodec_eRv40,
    NEXUS_VideoCodec_eVp6,
    NEXUS_VideoCodec_eVp7,
    NEXUS_VideoCodec_eVp8,
    NEXUS_VideoCodec_eVp9,
    NEXUS_VideoCodec_eSpark,
    NEXUS_VideoCodec_eMotionJpeg,
    NEXUS_VideoCodec_eH265,
    NEXUS_VideoCodec_eMax
} NEXUS_VideoCodec;
typedef enum NEXUS_VideoFormat {
    NEXUS_VideoFormat_eUnknown = 0,
    NEXUS_VideoFormat_eNtsc,
    NEXUS_VideoFormat_eNtsc443,
    NEXUS_VideoFormat_eNtscJapan,
    NEXUS_VideoFormat_ePalM,
    NEXUS_VideoFormat_ePalN,
    NEXUS_VideoFormat_ePalNc,
    NEXUS_VideoFormat_ePalB,
    NEXUS_VideoFormat_ePalB1,
    NEXUS_VideoFormat_ePalD,
    NEXUS_VideoFormat_ePalD1,
    NEXUS_VideoFormat_ePalDK1=NEXUS_VideoFormat_ePalD1,
    NEXUS_VideoFormat_ePalDK2,
    NEXUS_VideoFormat_ePalDK3,
    NEXUS_VideoFormat_ePalG,
    NEXUS_VideoFormat_ePal = NEXUS_VideoFormat_ePalG,
    NEXUS_VideoFormat_ePalH,
    NEXUS_VideoFormat_ePalK,
    NEXUS_VideoFormat_ePalI,
    NEXUS_VideoFormat_ePal60hz,
    NEXUS_VideoFormat_eSecamL,
    NEXUS_VideoFormat_eSecam = NEXUS_VideoFormat_eSecamL,
    NEXUS_VideoFormat_eSecamB,
    NEXUS_VideoFormat_eSecamG,
    NEXUS_VideoFormat_eSecamD,
    NEXUS_VideoFormat_eSecamK,
    NEXUS_VideoFormat_eSecamH,
    NEXUS_VideoFormat_e480p,
    NEXUS_VideoFormat_e576p,
    NEXUS_VideoFormat_e1080i,
    NEXUS_VideoFormat_e1080i50hz,
    NEXUS_VideoFormat_e1080p24hz,
    NEXUS_VideoFormat_e1080p25hz,
    NEXUS_VideoFormat_e1080p30hz,
    NEXUS_VideoFormat_e1080p50hz,
    NEXUS_VideoFormat_e1080p60hz,
    NEXUS_VideoFormat_e1080p = NEXUS_VideoFormat_e1080p60hz,
    NEXUS_VideoFormat_e1080p100hz,
    NEXUS_VideoFormat_e1080p120hz,
    NEXUS_VideoFormat_e1250i50hz,
    NEXUS_VideoFormat_e720p,
    NEXUS_VideoFormat_e720p50hz,
    NEXUS_VideoFormat_e720p24hz,
    NEXUS_VideoFormat_e720p25hz,
    NEXUS_VideoFormat_e720p30hz,
    NEXUS_VideoFormat_e240p60hz,
    NEXUS_VideoFormat_e288p50hz,
    NEXUS_VideoFormat_e1440x480p60hz,
    NEXUS_VideoFormat_e1440x576p50hz,
    NEXUS_VideoFormat_e3840x2160p24hz,
    NEXUS_VideoFormat_e3840x2160p25hz,
    NEXUS_VideoFormat_e3840x2160p30hz,
    NEXUS_VideoFormat_e3840x2160p50hz,
    NEXUS_VideoFormat_e3840x2160p60hz,
    NEXUS_VideoFormat_e4096x2160p24hz,
    NEXUS_VideoFormat_e4096x2160p25hz,
    NEXUS_VideoFormat_e4096x2160p30hz,
    NEXUS_VideoFormat_e4096x2160p50hz,
    NEXUS_VideoFormat_e4096x2160p60hz,
    NEXUS_VideoFormat_eCustomer1440x240p60hz,
    NEXUS_VideoFormat_eCustomer1440x288p50hz,
    NEXUS_VideoFormat_eCustomer1366x768p60hz,
    NEXUS_VideoFormat_eCustomer1366x768p50hz,
    NEXUS_VideoFormat_eVesa640x480p60hz,
    NEXUS_VideoFormat_eVesa800x600p60hz,
    NEXUS_VideoFormat_eVesa1024x768p60hz,
    NEXUS_VideoFormat_eVesa1280x768p60hz,
    NEXUS_VideoFormat_eVesa1280x768p60hzRed,
    NEXUS_VideoFormat_eVesa1280x720p50hz,
    NEXUS_VideoFormat_eVesa1280x720p60hz,
    NEXUS_VideoFormat_eVesa1280x720pReducedBlank,
    NEXUS_VideoFormat_eVesa640x350p60hz,
    NEXUS_VideoFormat_eVesa640x350p70hz,
    NEXUS_VideoFormat_eVesa640x350p72hz,
    NEXUS_VideoFormat_eVesa640x350p75hz,
    NEXUS_VideoFormat_eVesa640x350p85hz,
    NEXUS_VideoFormat_eVesa640x400p60hz,
    NEXUS_VideoFormat_eVesa640x400p70hz,
    NEXUS_VideoFormat_eVesa640x400p72hz,
    NEXUS_VideoFormat_eVesa640x400p75hz,
    NEXUS_VideoFormat_eVesa640x400p85hz,
    NEXUS_VideoFormat_eVesa640x480p66hz,
    NEXUS_VideoFormat_eVesa640x480p70hz,
    NEXUS_VideoFormat_eVesa640x480p72hz,
    NEXUS_VideoFormat_eVesa640x480p75hz,
    NEXUS_VideoFormat_eVesa640x480p85hz,
    NEXUS_VideoFormat_eVesa720x400p60hz,
    NEXUS_VideoFormat_eVesa720x400p70hz,
    NEXUS_VideoFormat_eVesa720x400p72hz,
    NEXUS_VideoFormat_eVesa720x400p75hz,
    NEXUS_VideoFormat_eVesa720x400p85hz,
    NEXUS_VideoFormat_eVesa800x600p56hz,
    NEXUS_VideoFormat_eVesa800x600p59hzRed,
    NEXUS_VideoFormat_eVesa800x600p70hz,
    NEXUS_VideoFormat_eVesa800x600p72hz,
    NEXUS_VideoFormat_eVesa800x600p75hz,
    NEXUS_VideoFormat_eVesa800x600p85hz,
    NEXUS_VideoFormat_eVesa848x480p60hz,
    NEXUS_VideoFormat_eVesa1024x768p66hz,
    NEXUS_VideoFormat_eVesa1024x768p70hz,
    NEXUS_VideoFormat_eVesa1024x768p72hz,
    NEXUS_VideoFormat_eVesa1024x768p75hz,
    NEXUS_VideoFormat_eVesa1024x768p85hz,
    NEXUS_VideoFormat_eVesa1064x600p60hz,
    NEXUS_VideoFormat_eVesa1280x720p70hz,
    NEXUS_VideoFormat_eVesa1280x720p72hz,
    NEXUS_VideoFormat_eVesa1280x720p75hz,
    NEXUS_VideoFormat_eVesa1280x720p85hz,
    NEXUS_VideoFormat_eVesa1024x768i87hz,
    NEXUS_VideoFormat_eVesa1152x864p75hz,
    NEXUS_VideoFormat_eVesa1280x768p75hz,
    NEXUS_VideoFormat_eVesa1280x768p85hz,
    NEXUS_VideoFormat_eVesa1280x800p_60Hz,
    NEXUS_VideoFormat_eVesa1280x960p60hz,
    NEXUS_VideoFormat_eVesa1280x960p85hz,
    NEXUS_VideoFormat_eVesa1280x1024p60hz,
    NEXUS_VideoFormat_eVesa1280x1024p69hz,
    NEXUS_VideoFormat_eVesa1280x1024p75hz,
    NEXUS_VideoFormat_eVesa1280x1024p85hz,
    NEXUS_VideoFormat_eVesa832x624p75hz,
    NEXUS_VideoFormat_eVesa1360x768p60hz,
    NEXUS_VideoFormat_eVesa1366x768p60hz,
    NEXUS_VideoFormat_eVesa1400x1050p60hz,
    NEXUS_VideoFormat_eVesa1400x1050p60hzReducedBlank,
    NEXUS_VideoFormat_eVesa1400x1050p75hz,
    NEXUS_VideoFormat_eVesa1440x900p60hz,
    NEXUS_VideoFormat_eVesa1600x1200p60hz,
    NEXUS_VideoFormat_eVesa1920x1080p60hzReducedBlank,
    NEXUS_VideoFormat_e720p_3DOU_AS,
    NEXUS_VideoFormat_e720p50hz_3DOU_AS,
    NEXUS_VideoFormat_e720p30hz_3DOU_AS,
    NEXUS_VideoFormat_e720p24hz_3DOU_AS,
    NEXUS_VideoFormat_e1080p24hz_3DOU_AS,
    NEXUS_VideoFormat_e1080p30hz_3DOU_AS,
    NEXUS_VideoFormat_eVesa1680x1050p_60Hz,
    NEXUS_VideoFormat_eVesa1280x800p_60Hz_Red,
    NEXUS_VideoFormat_eVesa1600x1200p_75Hz,
    NEXUS_VideoFormat_eVesa1600x900p_60Hz_Red,
    NEXUS_VideoFormat_eVesa1680x1050p_60Hz_Red,
    NEXUS_VideoFormat_eVesa1920x1200p_60Hz,
    NEXUS_VideoFormat_eVesa1920x1200p_60Hz_Red,
    NEXUS_VideoFormat_eVesa1152x720p_60Hz,
    NEXUS_VideoFormat_eVesa1152x720p_75Hz,
    NEXUS_VideoFormat_eVesa1152x720p_85Hz,
    NEXUS_VideoFormat_eVesa1152x864p_60Hz,
    NEXUS_VideoFormat_eVesa1152x864p_85Hz,
    NEXUS_VideoFormat_eVesa1152x870p_75Hz,
    NEXUS_VideoFormat_eVesa1152x900p_66Hz,
    NEXUS_VideoFormat_eVesa1152x900p_76Hz,
    NEXUS_VideoFormat_eVesa1170x584p_50Hz,
    NEXUS_VideoFormat_eVesa1280x1024p_70Hz,
    NEXUS_VideoFormat_eVesa1280x1024p_72Hz,
    NEXUS_VideoFormat_eVesa1280x1024p_76Hz,
    NEXUS_VideoFormat_eVesa1280x768p_50Hz,
    NEXUS_VideoFormat_eVesa1280x960p_75Hz,
    NEXUS_VideoFormat_eVesa1600x1024p_60Hz,
    NEXUS_VideoFormat_eVesa1600x1024p_76Hz,
    NEXUS_VideoFormat_eVesa1728x1080p_60Hz,
    NEXUS_VideoFormat_eVesa800x600p_100Hz,
    NEXUS_VideoFormat_eVesa800x600p_90Hz,
    NEXUS_VideoFormat_eVesa848x480p_75Hz,
    NEXUS_VideoFormat_eVesa848x480p_85Hz,
    NEXUS_VideoFormat_eVesa852x480p_60Hz,
    NEXUS_VideoFormat_e720x482_NTSC,
    NEXUS_VideoFormat_e720x482_NTSC_J,
    NEXUS_VideoFormat_e720x483p,
    NEXUS_VideoFormat_eCustom0,
    NEXUS_VideoFormat_eCustom1,
    NEXUS_VideoFormat_eCustom2,
    NEXUS_VideoFormat_eCustom1920x2160i_48Hz,
    NEXUS_VideoFormat_eCustom_3D_720p,
    NEXUS_VideoFormat_eCustom_3D_720p_50hz,
    NEXUS_VideoFormat_eCustom_3D_720p_30hz,
    NEXUS_VideoFormat_eCustom_3D_720p_24hz,
    NEXUS_VideoFormat_eCustom_3D_1080p_24hz,
    NEXUS_VideoFormat_eCustom_3D_1080p_30hz,
    NEXUS_VideoFormat_eMax
} NEXUS_VideoFormat;
typedef enum NEXUS_AspectRatio {
    NEXUS_AspectRatio_eUnknown = 0,
    NEXUS_AspectRatio_eSquarePixel,
    NEXUS_AspectRatio_e4x3,
    NEXUS_AspectRatio_e16x9,
    NEXUS_AspectRatio_e221x1,
    NEXUS_AspectRatio_e15x9,
    NEXUS_AspectRatio_eSar,
    NEXUS_AspectRatio_eMax
} NEXUS_AspectRatio;
typedef enum NEXUS_ColorSpace {
    NEXUS_ColorSpace_eAuto,
    NEXUS_ColorSpace_eRgb,
    NEXUS_ColorSpace_eYCbCr422,
    NEXUS_ColorSpace_eYCbCr444,
    NEXUS_ColorSpace_eYCbCr420,
    NEXUS_ColorSpace_eMax
} NEXUS_ColorSpace;
typedef enum NEXUS_ColorRange {
    NEXUS_ColorRange_eLimited,
    NEXUS_ColorRange_eFull,
    NEXUS_ColorRange_eMax
} NEXUS_ColorRange;
typedef unsigned NEXUS_HdmiColorDepth;
typedef struct NEXUS_VideoOutput *NEXUS_VideoOutput;
typedef NEXUS_VideoOutput NEXUS_VideoOutputHandle;
typedef struct NEXUS_VideoInput *NEXUS_VideoInput;
typedef NEXUS_VideoInput NEXUS_VideoInputHandle;
typedef struct NEXUS_ColorMatrix
{
    uint32_t shift;
    int32_t coeffMatrix[(15)];
    _Bool bypass;
} NEXUS_ColorMatrix;
typedef enum NEXUS_MatrixCoefficients
{
    NEXUS_MatrixCoefficients_eHdmi_RGB,
    NEXUS_MatrixCoefficients_eItu_R_BT_709,
    NEXUS_MatrixCoefficients_eUnknown,
    NEXUS_MatrixCoefficients_eDvi_Full_Range_RGB,
    NEXUS_MatrixCoefficients_eFCC,
    NEXUS_MatrixCoefficients_eItu_R_BT_470_2_BG,
    NEXUS_MatrixCoefficients_eSmpte_170M,
    NEXUS_MatrixCoefficients_eSmpte_240M,
    NEXUS_MatrixCoefficients_eXvYCC_709,
    NEXUS_MatrixCoefficients_eXvYCC_601,
    NEXUS_MatrixCoefficients_eItu_R_BT_2020_NCL,
    NEXUS_MatrixCoefficients_eItu_R_BT_2020_CL,
    NEXUS_MatrixCoefficients_eHdmi_Full_Range_YCbCr,
    NEXUS_MatrixCoefficients_eMax
} NEXUS_MatrixCoefficients;
typedef enum NEXUS_ColorPrimaries
{
    NEXUS_ColorPrimaries_eItu_R_BT_709 = 1,
    NEXUS_ColorPrimaries_eUnknown,
    NEXUS_ColorPrimaries_eItu_R_BT_470_2_M = 4,
    NEXUS_ColorPrimaries_eItu_R_BT_470_2_BG,
    NEXUS_ColorPrimaries_eSmpte_170M,
    NEXUS_ColorPrimaries_eSmpte_240M,
    NEXUS_ColorPrimaries_eGenericFilm,
    NEXUS_ColorPrimaries_eItu_R_BT_2020
} NEXUS_ColorPrimaries;
typedef enum NEXUS_TransferCharacteristics
{
    NEXUS_TransferCharacteristics_eItu_R_BT_709 = 1,
    NEXUS_TransferCharacteristics_eUnknown,
    NEXUS_TransferCharacteristics_eItu_R_BT_470_2_M = 4,
    NEXUS_TransferCharacteristics_eItu_R_BT_470_2_BG,
    NEXUS_TransferCharacteristics_eSmpte_170M,
    NEXUS_TransferCharacteristics_eSmpte_240M,
    NEXUS_TransferCharacteristics_eLinear,
    NEXUS_TransferCharacteristics_eIec_61966_2_4 = 11,
    NEXUS_TransferCharacteristics_eItu_R_BT_2020_10bit,
    NEXUS_TransferCharacteristics_eItu_R_BT_2020_12bit,
    NEXUS_TransferCharacteristics_eSmpte_ST_2084,
    NEXUS_TransferCharacteristics_eArib_STD_B67,
    NEXUS_TransferCharacteristics_eMax
} NEXUS_TransferCharacteristics;
typedef enum NEXUS_Video3DStructure
{
    NEXUS_Video3DStructure_eFramePacking,
    NEXUS_Video3DStructure_eFieldAlternative,
    NEXUS_Video3DStructure_eLineAlternative,
    NEXUS_Video3DStructure_eSidexSideFull,
    NEXUS_Video3DStructure_eLDepth,
    NEXUS_Video3DStructure_eLDepthGraphics,
    NEXUS_Video3DStructure_eTopAndBottom,
    NEXUS_Video3DStructure_eReserved,
    NEXUS_Video3DStructure_eSidexSideHalf,
    NEXUS_Video3DStructure_eMax
} NEXUS_Video3DStructure;
typedef enum NEXUS_Video3DSubSample
{
    NEXUS_Video3DSubSample_eNone,
    NEXUS_Video3DSubSample_eHorzOLOR = 0 ,
    NEXUS_Video3DSubSample_eHorzOLER,
    NEXUS_Video3DSubSample_eHorzELOR,
    NEXUS_Video3DSubSample_eHorzELER,
    NEXUS_Video3DSubSample_eQuinOLOR,
    NEXUS_Video3DSubSample_eQuinOLER,
    NEXUS_Video3DSubSample_eQuinELOR,
    NEXUS_Video3DSubSample_eQuinELER,
    NEXUS_Video3DSubSample_eMax
} NEXUS_Video3DSubSample;
typedef enum NEXUS_VideoOrientation {
    NEXUS_VideoOrientation_e2D,
    NEXUS_VideoOrientation_e3D_LeftRight,
    NEXUS_VideoOrientation_e3D_OverUnder,
    NEXUS_VideoOrientation_eMax
} NEXUS_VideoOrientation;
typedef enum NEXUS_PictureCoding
{
    NEXUS_PictureCoding_eUnknown = 0,
    NEXUS_PictureCoding_eI,
    NEXUS_PictureCoding_eP,
    NEXUS_PictureCoding_eB,
    NEXUS_PictureCoding_eMax
} NEXUS_PictureCoding;
typedef enum NEXUS_VideoEotf
{
    NEXUS_VideoEotf_eSdr,
    NEXUS_VideoEotf_eAribStdB67,
    NEXUS_VideoEotf_eSmpteSt2084,
    NEXUS_VideoEotf_eInvalid,
    NEXUS_VideoEotf_eMax,
    NEXUS_VideoEotf_eHdr10 = NEXUS_VideoEotf_eSmpteSt2084,
    NEXUS_VideoEotf_eHlg = NEXUS_VideoEotf_eAribStdB67,
    NEXUS_VideoEotf_eHdr = NEXUS_VideoEotf_eInvalid,
    NEXUS_VideoEotf_eFuture = NEXUS_VideoEotf_eInvalid
} NEXUS_VideoEotf;
typedef enum NEXUS_PictureScan
{
   NEXUS_PictureScan_eUnknown,
   NEXUS_PictureScan_eInterlaced,
   NEXUS_PictureScan_eProgressive,
   NEXUS_PictureScan_eMax
} NEXUS_PictureScan;
typedef enum NEXUS_SecureVideo
{
    NEXUS_SecureVideo_eUnsecure,
    NEXUS_SecureVideo_eSecure,
    NEXUS_SecureVideo_eBoth,
    NEXUS_SecureVideo_eMax
} NEXUS_SecureVideo;
typedef struct NEXUS_KeySlot *NEXUS_KeySlotHandle;
typedef enum NEXUS_SecurityEngine
{
    NEXUS_SecurityEngine_eCa,
    NEXUS_SecurityEngine_eM2m,
    NEXUS_SecurityEngine_eCp,
    NEXUS_SecurityEngine_eCaCp,
    NEXUS_SecurityEngine_eRmx,
    NEXUS_SecurityEngine_eGeneric,
    NEXUS_SecurityEngine_eMax
} NEXUS_SecurityEngine;
typedef enum NEXUS_SecurityKeySlotType
{
    NEXUS_SecurityKeySlotType_eAuto,
    NEXUS_SecurityKeySlotType_eType0,
    NEXUS_SecurityKeySlotType_eType1,
    NEXUS_SecurityKeySlotType_eType2,
    NEXUS_SecurityKeySlotType_eType3,
    NEXUS_SecurityKeySlotType_eType4,
    NEXUS_SecurityKeySlotType_eType5,
    NEXUS_SecurityKeySlotType_eType6,
    NEXUS_SecurityKeySlotType_eType7,
    NEXUS_SecurityKeySlotType_eMax
} NEXUS_SecurityKeySlotType;
typedef unsigned NEXUS_SecurityKeySlotNumber;
typedef enum NEXUS_SecurityClientType {
    NEXUS_SecurityClientType_eHost,
    NEXUS_SecurityClientType_eSage,
    NEXUS_SecurityClientType_eMax
} NEXUS_SecurityClientType;
typedef enum NEXUS_SecurityKeySource
{
    NEXUS_SecurityKeySource_eReserved0,
    NEXUS_SecurityKeySource_eFirstRam = NEXUS_SecurityKeySource_eReserved0,
    NEXUS_SecurityKeySource_eReserved1,
    NEXUS_SecurityKeySource_eSecondRam = NEXUS_SecurityKeySource_eReserved1,
    NEXUS_SecurityKeySource_eReserved2,
    NEXUS_SecurityKeySource_eThirdRam = NEXUS_SecurityKeySource_eReserved2,
    NEXUS_SecurityKeySource_eKey3,
    NEXUS_SecurityKeySource_eKey3KeyLadder1 = NEXUS_SecurityKeySource_eKey3,
    NEXUS_SecurityKeySource_eKey4,
    NEXUS_SecurityKeySource_eKey4KeyLadder1 = NEXUS_SecurityKeySource_eKey4,
    NEXUS_SecurityKeySource_eKey5,
    NEXUS_SecurityKeySource_eKey5KeyLadder1 = NEXUS_SecurityKeySource_eKey5,
    NEXUS_SecurityKeySource_eReserved6,
    NEXUS_SecurityKeySource_eAvCPCW = NEXUS_SecurityKeySource_eReserved6,
    NEXUS_SecurityKeySource_eKey6 = NEXUS_SecurityKeySource_eReserved6,
    NEXUS_SecurityKeySource_eKey3KeyLadder2 = NEXUS_SecurityKeySource_eAvCPCW,
    NEXUS_SecurityKeySource_eReserved7,
    NEXUS_SecurityKeySource_eAvCW = NEXUS_SecurityKeySource_eReserved7,
    NEXUS_SecurityKeySource_eKey7 = NEXUS_SecurityKeySource_eReserved7,
    NEXUS_SecurityKeySource_eKey4KeyLadder2 = NEXUS_SecurityKeySource_eAvCW,
    NEXUS_SecurityKeySource_eFirstRamAskm,
    NEXUS_SecurityKeySource_eKey5KeyLadder2 = NEXUS_SecurityKeySource_eFirstRamAskm,
    NEXUS_SecurityKeySource_ePkl = NEXUS_SecurityKeySource_eKey5KeyLadder2,
    NEXUS_SecurityKeySource_eSecondRamAskm,
    NEXUS_SecurityKeySource_eKey3KeyLadder3 = NEXUS_SecurityKeySource_eSecondRamAskm,
    NEXUS_SecurityKeySource_eFirstRamAskm40nm = NEXUS_SecurityKeySource_eKey3KeyLadder3,
    NEXUS_SecurityKeySource_eThirdRamAskm,
    NEXUS_SecurityKeySource_eKey4KeyLadder3 = NEXUS_SecurityKeySource_eThirdRamAskm,
    NEXUS_SecurityKeySource_eFek = NEXUS_SecurityKeySource_eKey4KeyLadder3,
    NEXUS_SecurityKeySource_eFirstRam2048,
    NEXUS_SecurityKeySource_eKey5KeyLadder3 = NEXUS_SecurityKeySource_eFirstRam2048,
    NEXUS_SecurityKeySource_eSecondRam2048,
    NEXUS_SecurityKeySource_eThirdRam2048,
    NEXUS_SecurityKeySource_eFirstRNRam1024,
    NEXUS_SecurityKeySource_eSecondRNRam1024,
    NEXUS_SecurityKeySource_eMax
} NEXUS_SecurityKeySource;
typedef struct NEXUS_SecurityKeySlotSettings {
    NEXUS_SecurityEngine keySlotEngine;
    NEXUS_SecurityKeySource keySlotSource;
    NEXUS_SecurityKeySlotType keySlotType;
    NEXUS_SecurityClientType client;
} NEXUS_SecurityKeySlotSettings;
typedef struct NEXUS_SecurityKeySlotInfo
{
    NEXUS_SecurityEngine keySlotEngine;
    unsigned keySlotNumber;
    NEXUS_SecurityKeySlotType keySlotType;
    struct {
        unsigned pidChannelIndex;
    }dma;
} NEXUS_SecurityKeySlotInfo;
typedef NEXUS_SecurityKeySlotInfo NEXUS_KeySlotInfo;
typedef enum NEXUS_BypassKeySlot{
    NEXUS_BypassKeySlot_eG2GR,
    NEXUS_BypassKeySlot_eGR2R,
    NEXUS_BypassKeySlot_eMax
} NEXUS_BypassKeySlot;
typedef unsigned long NEXUS_InputBand;
typedef unsigned long NEXUS_ParserBand;
typedef enum NEXUS_TransportType {
    NEXUS_TransportType_eUnknown,
    NEXUS_TransportType_eEs,
    NEXUS_TransportType_eTs,
    NEXUS_TransportType_eMpeg2Pes,
    NEXUS_TransportType_eVob,
    NEXUS_TransportType_eMpeg1Ps,
    NEXUS_TransportType_eDssEs,
    NEXUS_TransportType_eDssPes,
    NEXUS_TransportType_eAsf,
    NEXUS_TransportType_eAvi,
    NEXUS_TransportType_eMp4,
    NEXUS_TransportType_eFlv,
    NEXUS_TransportType_eMkv,
    NEXUS_TransportType_eWav,
    NEXUS_TransportType_eMp4Fragment,
    NEXUS_TransportType_eRmff,
    NEXUS_TransportType_eOgg,
    NEXUS_TransportType_eFlac,
    NEXUS_TransportType_eAiff,
    NEXUS_TransportType_eApe,
    NEXUS_TransportType_eAmr,
    NEXUS_TransportType_eBulk,
    NEXUS_TransportType_eMax
} NEXUS_TransportType;
typedef enum NEXUS_TransportTimestampType {
    NEXUS_TransportTimestampType_eNone,
    NEXUS_TransportTimestampType_e30_2U_Mod300,
    NEXUS_TransportTimestampType_eMod300 = NEXUS_TransportTimestampType_e30_2U_Mod300,
    NEXUS_TransportTimestampType_e30_2U_Binary,
    NEXUS_TransportTimestampType_eBinary = NEXUS_TransportTimestampType_e30_2U_Binary,
    NEXUS_TransportTimestampType_e32_Mod300,
    NEXUS_TransportTimestampType_e32_Binary,
    NEXUS_TransportTimestampType_e28_4P_Mod300,
    NEXUS_TransportTimestampType_eMax
} NEXUS_TransportTimestampType;
typedef unsigned long NEXUS_Timebase;
typedef struct NEXUS_FrontendConnector *NEXUS_FrontendConnectorHandle;
typedef struct NEXUS_Remux *NEXUS_RemuxHandle;
typedef enum NEXUS_CableCardType
{
    NEXUS_CableCardType_eNone,
    NEXUS_CableCardType_eSCard,
    NEXUS_CableCardType_eMCard
} NEXUS_CableCardType;
typedef enum NEXUS_PtsType
{
    NEXUS_PtsType_eCoded,
    NEXUS_PtsType_eInterpolatedFromValidPTS,
    NEXUS_PtsType_eHostProgrammedPTS,
    NEXUS_PtsType_eInterpolatedFromInvalidPTS
} NEXUS_PtsType;
typedef enum NEXUS_PidType {
    NEXUS_PidType_eVideo,
    NEXUS_PidType_eAudio,
    NEXUS_PidType_eOther,
    NEXUS_PidType_eUnknown = NEXUS_PidType_eOther
} NEXUS_PidType;
typedef uint32_t NEXUS_Pixel;
typedef enum NEXUS_PixelFormat
{
    NEXUS_PixelFormat_eUnknown = 0,
    NEXUS_PixelFormat_eR5_G6_B5,
    NEXUS_PixelFormat_eB5_G6_R5,
    NEXUS_PixelFormat_eA1_R5_G5_B5,
    NEXUS_PixelFormat_eX1_R5_G5_B5,
    NEXUS_PixelFormat_eA1_B5_G5_R5,
    NEXUS_PixelFormat_eX1_B5_G5_R5,
    NEXUS_PixelFormat_eR5_G5_B5_A1,
    NEXUS_PixelFormat_eR5_G5_B5_X1,
    NEXUS_PixelFormat_eB5_G5_R5_A1,
    NEXUS_PixelFormat_eB5_G5_R5_X1,
    NEXUS_PixelFormat_eA4_R4_G4_B4,
    NEXUS_PixelFormat_eX4_R4_G4_B4,
    NEXUS_PixelFormat_eA4_B4_G4_R4,
    NEXUS_PixelFormat_eX4_B4_G4_R4,
    NEXUS_PixelFormat_eR4_G4_B4_A4,
    NEXUS_PixelFormat_eR4_G4_B4_X4,
    NEXUS_PixelFormat_eB4_G4_R4_A4,
    NEXUS_PixelFormat_eB4_G4_R4_X4,
    NEXUS_PixelFormat_eA8_R8_G8_B8,
    NEXUS_PixelFormat_eX8_R8_G8_B8,
    NEXUS_PixelFormat_eA8_B8_G8_R8,
    NEXUS_PixelFormat_eX8_B8_G8_R8,
    NEXUS_PixelFormat_eR8_G8_B8_A8,
    NEXUS_PixelFormat_eR8_G8_B8_X8,
    NEXUS_PixelFormat_eB8_G8_R8_A8,
    NEXUS_PixelFormat_eB8_G8_R8_X8,
    NEXUS_PixelFormat_eA8,
    NEXUS_PixelFormat_eA4,
    NEXUS_PixelFormat_eA2,
    NEXUS_PixelFormat_eA1,
    NEXUS_PixelFormat_eW1,
    NEXUS_PixelFormat_eA8_Palette8,
    NEXUS_PixelFormat_ePalette8,
    NEXUS_PixelFormat_ePalette4,
    NEXUS_PixelFormat_ePalette2,
    NEXUS_PixelFormat_ePalette1,
    NEXUS_PixelFormat_eY8_Palette8,
    NEXUS_PixelFormat_eA8_Y8,
    NEXUS_PixelFormat_eCb8,
    NEXUS_PixelFormat_eCr8,
    NEXUS_PixelFormat_eY8,
    NEXUS_PixelFormat_eCb8_Cr8,
    NEXUS_PixelFormat_eCr8_Cb8,
    NEXUS_PixelFormat_eY10,
    NEXUS_PixelFormat_eCb10_Cr10,
    NEXUS_PixelFormat_eCr10_Cb10,
    NEXUS_PixelFormat_eY08_Cb8_Y18_Cr8,
    NEXUS_PixelFormat_eY08_Cr8_Y18_Cb8,
    NEXUS_PixelFormat_eY18_Cb8_Y08_Cr8,
    NEXUS_PixelFormat_eY18_Cr8_Y08_Cb8,
    NEXUS_PixelFormat_eCb8_Y08_Cr8_Y18,
    NEXUS_PixelFormat_eCb8_Y18_Cr8_Y08,
    NEXUS_PixelFormat_eCr8_Y18_Cb8_Y08,
    NEXUS_PixelFormat_eCr8_Y08_Cb8_Y18,
    NEXUS_PixelFormat_eX2_Cr10_Y10_Cb10,
    NEXUS_PixelFormat_eA8_Y8_Cb8_Cr8,
    NEXUS_PixelFormat_eA8_Cr8_Cb8_Y8,
    NEXUS_PixelFormat_eCr8_Cb8_Y8_A8,
    NEXUS_PixelFormat_eY8_Cb8_Cr8_A8,
    NEXUS_PixelFormat_eY010_Cb10_Y110_Cr10,
    NEXUS_PixelFormat_eY010_Cr10_Y110_Cb10,
    NEXUS_PixelFormat_eY110_Cb10_Y010_Cr10,
    NEXUS_PixelFormat_eY110_Cr10_Y010_Cb10,
    NEXUS_PixelFormat_eCb10_Y010_Cr10_Y110,
    NEXUS_PixelFormat_eCb10_Y110_Cr10_Y010,
    NEXUS_PixelFormat_eCr10_Y110_Cb10_Y010,
    NEXUS_PixelFormat_eCr10_Y010_Cb10_Y110,
    NEXUS_PixelFormat_eL8,
    NEXUS_PixelFormat_eL4_A4,
    NEXUS_PixelFormat_eL8_A8,
    NEXUS_PixelFormat_eL15_L05_A6,
    NEXUS_PixelFormat_eCompressed_A8_R8_G8_B8,
    NEXUS_PixelFormat_eR8_G8_B8,
    NEXUS_PixelFormat_eYCbCr422_10bit,
    NEXUS_PixelFormat_eMax
} NEXUS_PixelFormat;
typedef struct NEXUS_DisplayBufferTypeSettings
{
    unsigned count;
    unsigned pipCount;
    NEXUS_PixelFormat pixelFormat;
    NEXUS_VideoFormat format;
    unsigned additionalLines;
} NEXUS_DisplayBufferTypeSettings;
typedef struct NEXUS_DisplayHeapSettings
{
    NEXUS_DisplayBufferTypeSettings quadHdBuffers;
    NEXUS_DisplayBufferTypeSettings fullHdBuffers;
    NEXUS_DisplayBufferTypeSettings hdBuffers;
    NEXUS_DisplayBufferTypeSettings sdBuffers;
} NEXUS_DisplayHeapSettings;
typedef struct NEXUS_Point
{
    int x;
    int y;
} NEXUS_Point;
typedef struct NEXUS_Rect
{
    int16_t x;
    int16_t y;
    uint16_t width;
    uint16_t height;
} NEXUS_Rect;
typedef struct NEXUS_ClipRect
{
    unsigned left;
    unsigned right;
    unsigned top;
    unsigned bottom;
} NEXUS_ClipRect;
typedef enum NEXUS_VbiDataType {
    NEXUS_VbiDataType_eClosedCaption,
    NEXUS_VbiDataType_eSubtitle,
    NEXUS_VbiDataType_eTeletext,
    NEXUS_VbiDataType_eVps,
    NEXUS_VbiDataType_eGemStar,
    NEXUS_VbiDataType_eWss,
    NEXUS_VbiDataType_eCgms,
    NEXUS_VbiDataType_eMax
} NEXUS_VbiDataType;
typedef struct NEXUS_ClosedCaptionData
{
    NEXUS_VbiDataType type;
    uint32_t pts;
    uint16_t field;
    _Bool noData;
    _Bool parityError;
    uint8_t data[2];
} NEXUS_ClosedCaptionData;
typedef unsigned NEXUS_MemoryType;
typedef void (*NEXUS_Core_InterruptFunction)(void *, int);
typedef enum NEXUS_Vcxo
{
    NEXUS_Vcxo_eInvalid=-1,
    NEXUS_Vcxo_e0=0,
    NEXUS_Vcxo_e1,
    NEXUS_Vcxo_e2,
    NEXUS_Vcxo_e3,
    NEXUS_Vcxo_eMax
} NEXUS_Vcxo;
typedef struct NEXUS_CommonModuleSettings
{
    _Bool enabledDuringActiveStandby;
} NEXUS_CommonModuleSettings;
typedef enum NEXUS_EndianMode
{
    NEXUS_EndianMode_eLittle,
    NEXUS_EndianMode_eBig,
    NEXUS_EndianMode_eMax
} NEXUS_EndianMode;
typedef struct NEXUS_MemoryBlock *NEXUS_MemoryBlockHandle;
typedef struct NEXUS_DebugFifoInfo {
    size_t elementSize;
    NEXUS_MemoryBlockHandle buffer;
    unsigned offset;
} NEXUS_DebugFifoInfo;
typedef struct NEXUS_ContentLightLevel
{
    unsigned max;
    unsigned maxFrameAverage;
} NEXUS_ContentLightLevel;
typedef struct NEXUS_MasteringDisplayColorVolume
{
    NEXUS_Point redPrimary;
    NEXUS_Point greenPrimary;
    NEXUS_Point bluePrimary;
    NEXUS_Point whitePoint;
    struct
    {
        unsigned max;
        unsigned min;
    } luminance;
} NEXUS_MasteringDisplayColorVolume;
typedef struct NEXUS_3dSurround *NEXUS_3dSurroundHandle;
typedef enum NEXUS_3dSurroundSpeakerPosition
{
    NEXUS_3dSurroundSpeakerPosition_eCenter,
    NEXUS_3dSurroundSpeakerPosition_eWide,
    NEXUS_3dSurroundSpeakerPosition_eExtraWide,
    NEXUS_3dSurroundSpeakerPosition_eMax
} NEXUS_3dSurroundSpeakerPosition;
typedef struct NEXUS_3dSurroundSettings
{
    _Bool enabled;
    _Bool softLimiterEnabled;
    NEXUS_3dSurroundSpeakerPosition speakerPosition;
} NEXUS_3dSurroundSettings;
void NEXUS_3dSurround_GetDefaultSettings(
    NEXUS_3dSurroundSettings *pSettings
    );
NEXUS_3dSurroundHandle NEXUS_3dSurround_Open(
    const NEXUS_3dSurroundSettings *pSettings
    );
void NEXUS_3dSurround_Close(
    NEXUS_3dSurroundHandle handle
    );
void NEXUS_3dSurround_GetSettings(
    NEXUS_3dSurroundHandle handle,
    NEXUS_3dSurroundSettings *pSettings
    );
NEXUS_Error NEXUS_3dSurround_SetSettings(
    NEXUS_3dSurroundHandle handle,
    const NEXUS_3dSurroundSettings *pSettings
    );
NEXUS_AudioInputHandle NEXUS_3dSurround_GetConnector(
    NEXUS_3dSurroundHandle handle
    );
NEXUS_Error NEXUS_3dSurround_AddInput(
    NEXUS_3dSurroundHandle handle,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_3dSurround_RemoveInput(
    NEXUS_3dSurroundHandle handle,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_3dSurround_RemoveAllInputs(
    NEXUS_3dSurroundHandle handle
    );
typedef struct NEXUS_PidChannel *NEXUS_PidChannelHandle;
typedef enum NEXUS_PidChannelDssHdFilter {
    NEXUS_PidChannelDssHdFilter_eDisabled,
    NEXUS_PidChannelDssHdFilter_eAux,
    NEXUS_PidChannelDssHdFilter_eNonAux,
    NEXUS_PidChannelDssHdFilter_eMax
} NEXUS_PidChannelDssHdFilter;
typedef struct NEXUS_PidChannelRemapSettings
{
    _Bool enabled;
    uint16_t pid;
    _Bool continuityCountEnabled;
}NEXUS_PidChannelRemapSettings;
typedef struct NEXUS_PidChannelSettings
{
    _Bool requireMessageBuffer;
    unsigned pidChannelIndex;
    NEXUS_PidChannelDssHdFilter dssHdFilter;
    _Bool enabled;
    _Bool continuityCountEnabled;
    _Bool generateContinuityCount;
    NEXUS_PidChannelRemapSettings remap;
    struct {
        unsigned low;
        unsigned high;
    } pesFiltering;
} NEXUS_PidChannelSettings;
void NEXUS_PidChannel_GetDefaultSettings(
    NEXUS_PidChannelSettings *pSettings
    );
NEXUS_PidChannelHandle NEXUS_PidChannel_Open(
    NEXUS_ParserBand parserBand,
    uint16_t pid,
    const NEXUS_PidChannelSettings *pSettings
    );
void NEXUS_PidChannel_Close(
    NEXUS_PidChannelHandle pidChannel
    );
void NEXUS_PidChannel_CloseAll(
    NEXUS_ParserBand parserBand
    );
void NEXUS_PidChannel_GetSettings(
    NEXUS_PidChannelHandle handle,
    NEXUS_PidChannelSettings *pSettings
    );
NEXUS_Error NEXUS_PidChannel_SetSettings(
    NEXUS_PidChannelHandle handle,
    const NEXUS_PidChannelSettings *pSettings
    );
typedef struct NEXUS_PidChannelStatus
{
    uint16_t pid;
    unsigned pidChannelIndex;
    NEXUS_TransportType transportType;
    NEXUS_TransportType originalTransportType;
    uint16_t remappedPid;
    _Bool enabled;
    _Bool playback;
    unsigned playbackIndex;
    unsigned parserBand;
    unsigned continuityCountErrors;
    struct {
        unsigned continuityCountErrors;
        unsigned emulationByteRemovalErrors;
        unsigned pusiErrors;
        unsigned teiErrors;
        unsigned cdbOverflowErrors;
        unsigned itbOverflowErrors;
    } raveStatus;
    struct {
        unsigned overflowErrors;
    } xcBufferStatus;
} NEXUS_PidChannelStatus;
NEXUS_Error NEXUS_PidChannel_GetStatus(
    NEXUS_PidChannelHandle pidChannel,
    NEXUS_PidChannelStatus *pStatus
    );
void NEXUS_PidChannel_ConsumerStarted(
    NEXUS_PidChannelHandle pidChannel
    );
NEXUS_Error NEXUS_PidChannel_AddSplicePidChannel(
    NEXUS_PidChannelHandle pidChannel,
    NEXUS_PidChannelHandle splicePidChannel
    );
NEXUS_Error NEXUS_PidChannel_RemoveSplicePidChannel(
    NEXUS_PidChannelHandle pidChannel,
    NEXUS_PidChannelHandle splicePidChannel
    );
void NEXUS_PidChannel_RemoveAllSplicePidChannels(
    NEXUS_PidChannelHandle pidChannel
    );
NEXUS_Error NEXUS_PidChannel_SetEnabled(
    NEXUS_PidChannelHandle pidChannel,
    _Bool enabled
    );
NEXUS_Error NEXUS_PidChannel_SetRemapSettings(
    NEXUS_PidChannelHandle pidChannel,
    const NEXUS_PidChannelRemapSettings *pSettings
    );
NEXUS_Error NEXUS_PidChannel_ResetStatus(
    NEXUS_PidChannelHandle pidChannel
    );
typedef struct NEXUS_PidChannelSlaveSettings
{
    unsigned tbd;
} NEXUS_PidChannelSlaveSettings;
void NEXUS_PidChannel_GetDefaultSlaveSettings(
    NEXUS_PidChannelSlaveSettings *pSettings
    );
NEXUS_Error NEXUS_PidChannel_AddSlavePidChannel(
    NEXUS_PidChannelHandle master,
    NEXUS_PidChannelHandle slave,
    const NEXUS_PidChannelSlaveSettings *pSettings
    );
void NEXUS_PidChannel_RemoveSlavePidChannel(
    NEXUS_PidChannelHandle master,
    NEXUS_PidChannelHandle slave
    );
NEXUS_Error NEXUS_PidChannel_ChangePid(
    NEXUS_PidChannelHandle pidChannel,
    unsigned pid
    );
typedef enum NEXUS_ItbEventType
{
    NEXUS_ItbEventType_ePts,
    NEXUS_ItbEventType_eBtp,
    NEXUS_ItbEventType_eMax
} NEXUS_ItbEventType;
typedef struct NEXUS_ItbEvent
{
    NEXUS_ItbEventType type;
    union {
        uint32_t pts;
        struct {
            unsigned tag;
        } btp;
    } data;
} NEXUS_ItbEvent;
NEXUS_Error NEXUS_PidChannel_ReadItbEvents(
    NEXUS_PidChannelHandle pidChannel,
    NEXUS_ItbEvent *pEvents,
    unsigned numEvents,
    unsigned *pNumReturned
    );
typedef struct NEXUS_StcChannel *NEXUS_StcChannelHandle;
typedef enum NEXUS_StcChannelMode
{
    NEXUS_StcChannelMode_ePcr,
    NEXUS_StcChannelMode_eAuto,
    NEXUS_StcChannelMode_eHost,
    NEXUS_StcChannelMode_eMax
} NEXUS_StcChannelMode;
typedef enum NEXUS_StcChannelAutoModeBehavior
{
    NEXUS_StcChannelAutoModeBehavior_eFirstAvailable,
    NEXUS_StcChannelAutoModeBehavior_eVideoMaster,
    NEXUS_StcChannelAutoModeBehavior_eAudioMaster,
    NEXUS_StcChannelAutoModeBehavior_eMax
} NEXUS_StcChannelAutoModeBehavior;
typedef enum NEXUS_StcChannel_PcrBits {
    NEXUS_StcChannel_PcrBits_eLegacy,
    NEXUS_StcChannel_PcrBits_eLsb32,
    NEXUS_StcChannel_PcrBits_eMsb32,
    NEXUS_StcChannel_PcrBits_eFull42,
    NEXUS_StcChannel_PcrBits_eMax
} NEXUS_StcChannel_PcrBits;
typedef struct NEXUS_StcChannelPcrModeSettings
{
    NEXUS_PidChannelHandle pidChannel;
    unsigned offsetThreshold;
    unsigned maxPcrError;
    _Bool disableTimestampCorrection;
    _Bool disableJitterAdjustment;
} NEXUS_StcChannelPcrModeSettings;
typedef struct NEXUS_StcChannelAutoModeSettings
{
    NEXUS_TransportType transportType;
    NEXUS_StcChannelAutoModeBehavior behavior;
    unsigned offsetThreshold;
} NEXUS_StcChannelAutoModeSettings;
typedef struct NEXUS_StcChannelHostModeSettings
{
    NEXUS_TransportType transportType;
    unsigned offsetThreshold;
} NEXUS_StcChannelHostModeSettings;
typedef enum NEXUS_StcChannelUnderflowHandling
{
    NEXUS_StcChannelUnderflowHandling_eDefault,
    NEXUS_StcChannelUnderflowHandling_eAllowProducerPause,
    NEXUS_StcChannelUnderflowHandling_eMax
} NEXUS_StcChannelUnderflowHandling;
typedef struct NEXUS_StcChannelSettings
{
    NEXUS_Timebase timebase;
    NEXUS_StcChannelMode mode;
    _Bool autoConfigTimebase;
    int stcIndex;
    NEXUS_StcChannel_PcrBits pcrBits;
    NEXUS_StcChannelUnderflowHandling underflowHandling;
    struct
    {
        NEXUS_StcChannelPcrModeSettings pcr;
        NEXUS_StcChannelAutoModeSettings Auto;
        NEXUS_StcChannelHostModeSettings host;
    } modeSettings;
} NEXUS_StcChannelSettings;
typedef struct NEXUS_StcChannelStatus
{
    NEXUS_StcChannelMode mode;
    uint32_t stc;
    _Bool stcValid;
} NEXUS_StcChannelStatus;
void NEXUS_StcChannel_GetDefaultSettings(
    unsigned index,
    NEXUS_StcChannelSettings *pSettings
    );
NEXUS_StcChannelHandle NEXUS_StcChannel_Open(
    unsigned index,
    const NEXUS_StcChannelSettings *pSettings
    );
void NEXUS_StcChannel_Close(
    NEXUS_StcChannelHandle handle
    );
void NEXUS_StcChannel_GetSettings(
    NEXUS_StcChannelHandle handle,
    NEXUS_StcChannelSettings *pSettings
    );
NEXUS_Error NEXUS_StcChannel_SetSettings(
    NEXUS_StcChannelHandle handle,
    const NEXUS_StcChannelSettings *pSettings
    );
NEXUS_Error NEXUS_StcChannel_GetStatus(
    NEXUS_StcChannelHandle handle,
    NEXUS_StcChannelStatus *pStatus
    );
NEXUS_Error NEXUS_StcChannel_Invalidate(
    NEXUS_StcChannelHandle handle
    );
void NEXUS_StcChannel_GetStc(
    NEXUS_StcChannelHandle handle,
    uint32_t *pStc
    );
NEXUS_Error NEXUS_StcChannel_SetStc(
    NEXUS_StcChannelHandle handle,
    uint32_t stc
    );
NEXUS_Error NEXUS_StcChannel_Freeze(
    NEXUS_StcChannelHandle stcChannel,
    _Bool frozen
    );
NEXUS_Error NEXUS_StcChannel_SetRate(
    NEXUS_StcChannelHandle stcChannel,
    unsigned increment,
    unsigned prescale
    );
NEXUS_Error NEXUS_StcChannel_VerifyPidChannel(
    NEXUS_StcChannelHandle stcChannel,
    NEXUS_PidChannelHandle pidChannel
    );
typedef struct NEXUS_StcChannelPairSettings {
    _Bool connected;
    unsigned window;
} NEXUS_StcChannelPairSettings;
void NEXUS_StcChannel_GetDefaultPairSettings(
            NEXUS_StcChannelPairSettings *pSettings
        );
NEXUS_Error NEXUS_StcChannel_SetPairSettings(
    NEXUS_StcChannelHandle stcChannel1,
    NEXUS_StcChannelHandle stcChannel2,
    const NEXUS_StcChannelPairSettings *pSettings
    );
typedef struct NEXUS_AudioDecoder *NEXUS_AudioDecoderHandle;
typedef enum NEXUS_AudioDecoderMixingMode
{
    NEXUS_AudioDecoderMixingMode_eDescription,
    NEXUS_AudioDecoderMixingMode_eSoundEffects,
    NEXUS_AudioDecoderMixingMode_eApplicationAudio,
    NEXUS_AudioDecoderMixingMode_eStandalone,
    NEXUS_AudioDecoderMixingMode_eMax
} NEXUS_AudioDecoderMixingMode;
typedef enum NEXUS_AudioDecoderLatencyMode
{
    NEXUS_AudioDecoderLatencyMode_eAuto,
    NEXUS_AudioDecoderLatencyMode_eNormal,
    NEXUS_AudioDecoderLatencyMode_eLow,
    NEXUS_AudioDecoderLatencyMode_eLowest,
    NEXUS_AudioDecoderLatencyMode_eMax
} NEXUS_AudioDecoderLatencyMode;
typedef struct NEXUS_AudioDecoderStartSettings
{
    NEXUS_PidChannelHandle pidChannel;
    NEXUS_AudioCodec codec;
    NEXUS_StcChannelHandle stcChannel;
    NEXUS_AudioInputHandle input;
    _Bool targetSyncEnabled;
    _Bool nonRealTime;
    _Bool secondaryDecoder;
    _Bool forceCompleteFirstFrame;
    NEXUS_AudioDecoderMixingMode mixingMode;
    NEXUS_AudioDecoderLatencyMode latencyMode;
    unsigned maxOutputRate;
    _Bool karaokeModeEnabled;
} NEXUS_AudioDecoderStartSettings;
typedef enum NEXUS_AudioMpegChannelMode
{
    NEXUS_AudioMpegChannelMode_eStereo = 0,
    NEXUS_AudioMpegChannelMode_eIntensityStereo,
    NEXUS_AudioMpegChannelMode_eDualChannel,
    NEXUS_AudioMpegChannelMode_eSingleChannel,
    NEXUS_AudioMpegChannelMode_eMax
} NEXUS_AudioMpegChannelMode;
typedef enum NEXUS_AudioMpegLayer
{
    NEXUS_AudioMpegLayer_eUnknown,
    NEXUS_AudioMpegLayer_e3,
    NEXUS_AudioMpegLayer_e2,
    NEXUS_AudioMpegLayer_e1,
    NEXUS_AudioMpegLayer_eMax
} NEXUS_AudioMpegLayer;
typedef enum NEXUS_AudioMpegEmphasis
{
    NEXUS_AudioMpegEmphasis_eNone = 0,
    NEXUS_AudioMpegEmphasis_eEmph50_15ms,
    NEXUS_AudioMpegEmphasis_eReserved,
    NEXUS_AudioMpegEmphasis_eCCITT_J17,
    NEXUS_AudioMpegEmphasis_eMax
} NEXUS_AudioMpegEmphasis;
typedef enum NEXUS_AudioAc3Acmod
{
    NEXUS_AudioAc3Acmod_eTwoMono_1_ch1_ch2,
    NEXUS_AudioAc3Acmod_eOneCenter_1_0_C,
    NEXUS_AudioAc3Acmod_eTwoChannel_2_0_L_R,
    NEXUS_AudioAc3Acmod_eThreeChannel_3_0_L_C_R,
    NEXUS_AudioAc3Acmod_eThreeChannel_2_1_L_R_S,
    NEXUS_AudioAc3Acmod_eFourChannel_3_1_L_C_R_S,
    NEXUS_AudioAc3Acmod_eFourChannel_2_2_L_R_SL_SR,
    NEXUS_AudioAc3Acmod_eFiveChannel_3_2_L_C_R_SL_SR,
    NEXUS_AudioAc3Acmod_eFourChannel_4_0_L_C_R_CVH,
    NEXUS_AudioAc3Acmod_eFiveChannel_2_3_L_R_LS_RS_TS,
    NEXUS_AudioAc3Acmod_eSixChannel_3_3_L_R_C_LS_RS_TS,
    NEXUS_AudioAc3Acmod_eSixChannel_4_2_L_R_C_LS_RS_CVH,
    NEXUS_AudioAc3Acmod_eFiveChannel_5_0_L_R_C_LC_RC,
    NEXUS_AudioAc3Acmod_eSixChannel_2_4_L_R_LS_RS_LW_RW,
    NEXUS_AudioAc3Acmod_eSixChannel_4_2_L_R_LS_RS_LVH_RVH,
    NEXUS_AudioAc3Acmod_eSixChannel_2_4_L_R_LS_RS_LSD_RSD,
    NEXUS_AudioAc3Acmod_eSixChannel_2_4_L_R_LS_RS_LRS_RRS,
    NEXUS_AudioAc3Acmod_eSevenChannel_5_2_L_R_C_LS_RS_LC_RC,
    NEXUS_AudioAc3Acmod_eSevenChannel_3_4_L_R_C_LS_RS_LW_RW,
    NEXUS_AudioAc3Acmod_eSevenChannel_5_2_L_R_C_LS_RS_LVH_RVH,
    NEXUS_AudioAc3Acmod_eSevenChannel_3_4_L_R_C_LS_RS_LSD_RSD,
    NEXUS_AudioAc3Acmod_eSevenChannel_3_4_L_R_C_LS_RS_LRS_RRS,
    NEXUS_AudioAc3Acmod_eSevenChannel_4_3_L_R_C_LS_RS_TS_CVH,
    NEXUS_AudioAc3Acmod_eMax
} NEXUS_AudioAc3Acmod;
typedef enum NEXUS_AudioAc3CenterMixLevel
{
    NEXUS_AudioAc3CenterMixLevel_e3,
    NEXUS_AudioAc3CenterMixLevel_e4_5,
    NEXUS_AudioAc3CenterMixLevel_e6,
    NEXUS_AudioAc3CenterMixLevel_eReserved
} NEXUS_AudioAc3CenterMixLevel;
typedef enum NEXUS_AudioAc3SurroundMixLevel
{
    NEXUS_AudioAc3SurroundMixLevel_e3,
    NEXUS_AudioAc3SurroundMixLevel_e6,
    NEXUS_AudioAc3SurroundMixLevel_e0,
    NEXUS_AudioAc3SurroundMixLevel_eReserved
} NEXUS_AudioAc3SurroundMixLevel;
typedef enum NEXUS_AudioAc3DolbySurround
{
    NEXUS_AudioAc3DolbySurround_eNotIndicated,
    NEXUS_AudioAc3DolbySurround_eNotEncoded,
    NEXUS_AudioAc3DolbySurround_eEncoded,
    NEXUS_AudioAc3DolbySurround_eReserved
} NEXUS_AudioAc3DolbySurround;
typedef enum NEXUS_AudioAc3DependentFrameChannelMap
{
    NEXUS_AudioAc3DependentFrameChannelMap_eReserved,
    NEXUS_AudioAc3DependentFrameChannelMap_eC,
    NEXUS_AudioAc3DependentFrameChannelMap_eL_R,
    NEXUS_AudioAc3DependentFrameChannelMap_eL_C_R,
    NEXUS_AudioAc3DependentFrameChannelMap_eL_R_l,
    NEXUS_AudioAc3DependentFrameChannelMap_eL_C_R_l,
    NEXUS_AudioAc3DependentFrameChannelMap_eL_R_l_r,
    NEXUS_AudioAc3DependentFrameChannelMap_eL_C_R_l_r,
    NEXUS_AudioAc3DependentFrameChannelMap_eL_C_R_Cvh,
    NEXUS_AudioAc3DependentFrameChannelMap_eL_R_l_r_Ts,
    NEXUS_AudioAc3DependentFrameChannelMap_eL_C_R_l_r_Ts,
    NEXUS_AudioAc3DependentFrameChannelMap_eL_C_R_l_r_Cvh,
    NEXUS_AudioAc3DependentFrameChannelMap_eL_C_R_Lc_Rc,
    NEXUS_AudioAc3DependentFrameChannelMap_eL_R_l_r_Lw_Rw,
    NEXUS_AudioAc3DependentFrameChannelMap_eL_R_l_r_Lvh_Rvh,
    NEXUS_AudioAc3DependentFrameChannelMap_eL_R_l_r_Lsd_rsd,
    NEXUS_AudioAc3DependentFrameChannelMap_eL_R_l_r_Lrs_Rrs,
    NEXUS_AudioAc3DependentFrameChannelMap_eL_C_R_l_r_Lc_Rc,
    NEXUS_AudioAc3DependentFrameChannelMap_eL_C_R_l_r_Lw_Rw,
    NEXUS_AudioAc3DependentFrameChannelMap_eL_C_R_l_r_Lvh_Rvh,
    NEXUS_AudioAc3DependentFrameChannelMap_eL_C_R_l_r_Lsg_Rsd,
    NEXUS_AudioAc3DependentFrameChannelMap_eL_C_R_l_r_Lrs_Rrs,
    NEXUS_AudioAc3DependentFrameChannelMap_eL_C_R_l_r_Ts_Cvh,
    NEXUS_AudioAc3DependentFrameChannelMap_eL_R_l_r_Cs,
    NEXUS_AudioAc3DependentFrameChannelMap_eL_C_R_l_r_Cs,
    NEXUS_AudioAc3DependentFrameChannelMap_eL_R_l_r_Cs_Ts,
    NEXUS_AudioAc3DependentFrameChannelMap_eL_C_R_l_r_Cs_Cvh,
    NEXUS_AudioAc3DependentFrameChannelMap_eL_C_R_l_r_Cs_Ts,
    NEXUS_AudioAc3DependentFrameChannelMap_eMax
}NEXUS_AudioAc3DependentFrameChannelMap;
typedef enum NEXUS_AudioAc4Acmod
{
    NEXUS_AudioAc4Acmod_eTwoMono_1_ch1_ch2,
    NEXUS_AudioAc4Acmod_eOneCenter_1_0_C,
    NEXUS_AudioAc4Acmod_eTwoChannel_2_0_L_R,
    NEXUS_AudioAc4Acmod_eThreeChannel_3_0_L_C_R,
    NEXUS_AudioAc4Acmod_eThreeChannel_2_1_L_R_S,
    NEXUS_AudioAc4Acmod_eFourChannel_3_1_L_C_R_S,
    NEXUS_AudioAc4Acmod_eFourChannel_2_2_L_R_LS_RS,
    NEXUS_AudioAc4Acmod_eFiveChannel_3_2_L_C_R_LS_RS,
    NEXUS_AudioAc4Acmod_eFourChannel_2_2_L_C_R_CVH,
    NEXUS_AudioAc4Acmod_eFiveChannel_2_3_L_R_LS_RS_TS,
    NEXUS_AudioAc4Acmod_eSixChannel_3_3_L_R_C_LS_RS_TS,
    NEXUS_AudioAc4Acmod_eSixChannel_3_3_L_R_C_LS_RS_CVH,
    NEXUS_AudioAc4Acmod_eFiveChannel_3_2_L_R_C_LC_RC,
    NEXUS_AudioAc4Acmod_eSixChannel_2_4_L_R_LS_RS_LW_RW,
    NEXUS_AudioAc4Acmod_eSixChannel_2_4_L_R_LS_RS_LVH_RVH,
    NEXUS_AudioAc4Acmod_eSixChannel_2_4_L_R_LS_RS_LSD_RSD,
    NEXUS_AudioAc4Acmod_eSixChannel_2_4_L_R_LS_RS_LRS_RRS,
    NEXUS_AudioAc4Acmod_eSevenChannel_3_4_L_R_C_LS_RS_LC_RC,
    NEXUS_AudioAc4Acmod_eSevenChannel_3_4_L_R_C_LS_RS_LW_RW,
    NEXUS_AudioAc4Acmod_eSevenChannel_3_4_L_R_C_LS_RS_LVH_RVH,
    NEXUS_AudioAc4Acmod_eSevenChannel_3_4_L_R_C_LS_RS_LSD_RSD,
    NEXUS_AudioAc4Acmod_eSevenChannel_3_4_L_R_C_LS_RS_LRS_RRS,
    NEXUS_AudioAc4Acmod_eSevenChannel_3_4_L_R_C_LS_RS_TS_CVH,
    NEXUS_AudioAc4Acmod_eMax
} NEXUS_AudioAc4Acmod;
typedef enum NEXUS_AudioAacAcmod
{
    NEXUS_AudioAacAcmod_eTwoMono_1_ch1_ch2,
    NEXUS_AudioAacAcmod_eOneCenter_1_0_C,
    NEXUS_AudioAacAcmod_eTwoChannel_2_0_L_R,
    NEXUS_AudioAacAcmod_eThreeChannel_3_0_L_C_R,
    NEXUS_AudioAacAcmod_eThreeChannel_2_1_L_R_S,
    NEXUS_AudioAacAcmod_eFourChannel_3_1_L_C_R_S,
    NEXUS_AudioAacAcmod_eFourChannel_2_2_L_R_SL_SR,
    NEXUS_AudioAacAcmod_eFiveChannel_3_2_L_C_R_SL_SR,
    NEXUS_AudioAacAcmod_eMax
} NEXUS_AudioAacAcmod;
typedef enum NEXUS_AudioAacProfile
{
    NEXUS_AudioAacProfile_eMain,
    NEXUS_AudioAacProfile_eLowComplexity,
    NEXUS_AudioAacProfile_eScalableSamplingRate,
    NEXUS_AudioAacProfile_eMax
} NEXUS_AudioAacProfile;
typedef enum NEXUS_AudioDtsAmode
{
    NEXUS_AudioDtsAmode_eOneCh_A,
    NEXUS_AudioDtsAmode_eTwoCh_A_B,
    NEXUS_AudioDtsAmode_eTwoCh_L_R,
    NEXUS_AudioDtsAmode_eTwoCh_LpR_LmR,
    NEXUS_AudioDtsAmode_eTwoCh_LT_RT,
    NEXUS_AudioDtsAmode_eThreeCh_C_L_R,
    NEXUS_AudioDtsAmode_eThreeCh_L_R_S,
    NEXUS_AudioDtsAmode_eFourCh_C_L_R_S,
    NEXUS_AudioDtsAmode_eFourCh_L_R_SL_SR,
    NEXUS_AudioDtsAmode_eFiveCh_C_L_R_SL_SR,
    NEXUS_AudioDtsAmode_eSixCh_CL_CR_L_R_SL_SR,
    NEXUS_AudioDtsAmode_eSixCh_C_L_R_LR_RR_OV,
    NEXUS_AudioDtsAmode_eSixCh_CF_CR_LF_RF_Lr_Rr,
    NEXUS_AudioDtsAmode_eSevenCh_CL_C_CR_L_R_SL_SR,
    NEXUS_AudioDtsAmode_eEightCh_CL_CR_L_R_SL1_SL2_SR1_SR2,
    NEXUS_AudioDtsAmode_eEightCh_CL_C_CR_L_R_SL_S_SR,
    NEXUS_AudioDtsAmode_eUserDefined,
    NEXUS_AudioDtsAmode_eMax
}NEXUS_AudioDtsAmode;
typedef enum NEXUS_AudioDtsCopyHistory
{
    NEXUS_AudioDtsCopyHistory_eCopyProhibited,
    NEXUS_AudioDtsCopyHistory_eFirstGeneration,
    NEXUS_AudioDtsCopyHistory_eSecondGeneration,
    NEXUS_AudioDtsCopyHistory_eOriginal,
    NEXUS_AudioDtsCopyHistory_eMax
} NEXUS_AudioDtsCopyHistory;
typedef enum NEXUS_AudioDtsExtension
{
    NEXUS_AudioDtsExtension_eXCh,
    NEXUS_AudioDtsExtension_eXXCh,
    NEXUS_AudioDtsExtension_eX96k,
    NEXUS_AudioDtsExtension_eReserved,
    NEXUS_AudioDtsExtension_eMax
} NEXUS_AudioDtsExtension;
typedef enum NEXUS_AudioWmaProStereoMode
{
    NEXUS_AudioWmaProStereoMode_eAuto,
    NEXUS_AudioWmaProStereoMode_eLtRt,
    NEXUS_AudioWmaProStereoMode_eLoRo,
    NEXUS_AudioWmaProStereoMode_eMax
} NEXUS_AudioWmaProStereoMode;
typedef enum NEXUS_AudioWmaProAcmod
{
    NEXUS_AudioWmaProAcmod_eUndefined,
    NEXUS_AudioWmaProAcmod_e1_0_C,
    NEXUS_AudioWmaProAcmod_e2_0_LR,
    NEXUS_AudioWmaProAcmod_e3_0_LCR,
    NEXUS_AudioWmaProAcmod_e2_1_LRS,
    NEXUS_AudioWmaProAcmod_e3_1_LCRS,
    NEXUS_AudioWmaProAcmod_e2_2_LRLsRs,
    NEXUS_AudioWmaProAcmod_e3_2_LCRLsRs,
    NEXUS_AudioWmaProAcmod_eMax
} NEXUS_AudioWmaProAcmod;
typedef enum NEXUS_AudioAmrBitrate
{
    NEXUS_AudioAmrBitrate_e4_75kbps,
    NEXUS_AudioAmrBitrate_e5_15kbps,
    NEXUS_AudioAmrBitrate_e5_90kbps,
    NEXUS_AudioAmrBitrate_e6_70kbps,
    NEXUS_AudioAmrBitrate_e7_40kbps,
    NEXUS_AudioAmrBitrate_e7_95kbps,
    NEXUS_AudioAmrBitrate_e10_20kbps,
    NEXUS_AudioAmrBitrate_e12_20kbps,
    NEXUS_AudioAmrBitrate_eSilence,
    NEXUS_AudioAmrBitrate_eMax
} NEXUS_AudioAmrBitrate;
typedef enum NEXUS_AudioDraAcmod
{
    NEXUS_AudioDraAcmod_e1_0_C,
    NEXUS_AudioDraAcmod_e2_0_LR,
    NEXUS_AudioDraAcmod_e2_1_LRS,
    NEXUS_AudioDraAcmod_e2_2_LRLrRr,
    NEXUS_AudioDraAcmod_e3_2_LRLrRrC,
    NEXUS_AudioDraAcmod_e3_3_LRLrRrCrC,
    NEXUS_AudioDraAcmod_e5_2_LRLrRrLsRsC,
    NEXUS_AudioDraAcmod_e5_3_LRLrRrLsRsCrC,
    NEXUS_AudioDraAcmod_eMax
} NEXUS_AudioDraAcmod;
typedef enum NEXUS_AudioDraStereoMode
{
    NEXUS_AudioDraStereoMode_eLoRo,
    NEXUS_AudioDraStereoMode_eLtRt,
    NEXUS_AudioDraStereoMode_eMax
} NEXUS_AudioDraStereoMode;
typedef struct NEXUS_AudioDecoderStatus
{
    _Bool valid;
    _Bool started;
    _Bool tsm;
    _Bool locked;
    NEXUS_AudioCodec codec;
    unsigned sampleRate;
    unsigned timebase;
    unsigned framesDecoded;
    unsigned frameErrors;
    unsigned dummyFrames;
    unsigned numFifoOverflows;
    unsigned numFifoUnderflows;
    uint64_t numBytesDecoded;
    unsigned numWatchdogs;
    union
    {
        struct
        {
            unsigned bitStreamId;
            NEXUS_AudioAc3Acmod acmod;
            unsigned frameSizeCode;
            unsigned bitrate;
            _Bool lfe;
            _Bool copyright;
            NEXUS_AudioAc3DependentFrameChannelMap dependentFrameChannelMap;
            unsigned dialnorm;
            unsigned previousDialnorm;
        } ac3;
        struct
        {
            NEXUS_AudioAc4Acmod acmod;
            _Bool lfe;
            unsigned bitrate;
            unsigned dialnorm;
            unsigned previousDialnorm;
            unsigned streamInfoVersion;
            unsigned numPresentations;
            unsigned currentPresentationIndex;
            unsigned dialogEnhanceMax;
        } ac4;
        struct
        {
            NEXUS_AudioMpegChannelMode channelMode;
            NEXUS_AudioMpegLayer layer;
            NEXUS_AudioMpegEmphasis emphasis;
            unsigned bitrate;
            unsigned numSamples;
            _Bool original;
            _Bool copyright;
        } mpeg;
        struct
        {
            NEXUS_AudioAacAcmod acmod;
            NEXUS_AudioAacProfile profile;
            unsigned bitrate;
            unsigned numSamples;
            _Bool lfe;
            _Bool pseudoSurround;
            _Bool drc;
            _Bool stereoMatrix;
            unsigned matrixIndex;
            unsigned numLfeChannels;
            unsigned numBackChannels;
            unsigned numSideChannels;
            unsigned numFrontChannels;
            unsigned dialnorm;
            unsigned previousDialnorm;
        } aac;
        struct
        {
            NEXUS_AudioDtsAmode amode;
            unsigned pcmResolution;
            NEXUS_AudioDtsCopyHistory copyHistory;
            unsigned lfeInterpolation;
            NEXUS_AudioDtsExtension extensionDescriptor;
            unsigned bitRate;
            unsigned version;
            uint8_t bitRateCode;
            _Bool esFormat;
            _Bool lfe;
            _Bool extensionPresent;
            _Bool crc;
            _Bool hdcdFormat;
            _Bool drc;
            _Bool downmixCoefficients;
            _Bool neo;
            unsigned frameSize;
            unsigned numChannels;
            unsigned pcmFrameSize;
            unsigned numPcmBlocks;
        } dts;
        struct
        {
            unsigned bitRate;
            _Bool original;
            _Bool copyright;
            _Bool crc;
            _Bool stereo;
            unsigned version;
        } wma;
        struct
        {
            unsigned bitRate;
            _Bool original;
            _Bool copyright;
            _Bool crc;
            _Bool lfe;
            unsigned version;
            NEXUS_AudioWmaProStereoMode stereoMode;
            NEXUS_AudioWmaProAcmod acmod;
        } wmaPro;
        struct
        {
            unsigned numChannels;
        } pcmWav;
        struct
        {
            NEXUS_AudioAmrBitrate bitRate;
        } amr;
        struct
        {
            unsigned frameSize;
            unsigned numBlocks;
            NEXUS_AudioDraAcmod acmod;
            _Bool lfe;
            NEXUS_AudioDraStereoMode stereoMode;
        } dra;
        struct
        {
            _Bool stereo;
            unsigned frameSize;
        } cook;
        struct
        {
            unsigned bitsPerSample;
        } als;
    } codecStatus;
    unsigned fifoDepth;
    unsigned fifoSize;
    uint32_t pts;
    NEXUS_PtsType ptsType;
    int32_t ptsStcDifference;
    unsigned ptsErrorCount;
    unsigned queuedFrames;
    uint8_t wordLength;
    uint8_t maxWordLength;
    uint8_t algorithmProfileId;
    uint8_t algorithmVersionId[4];
    uint8_t firmwareVersionId;
} NEXUS_AudioDecoderStatus;
typedef enum NEXUS_AudioAc4AssociateType
{
    NEXUS_AudioAc4AssociateType_eNotSpecified,
    NEXUS_AudioAc4AssociateType_eVisuallyImpaired,
    NEXUS_AudioAc4AssociateType_eHearingImpaired,
    NEXUS_AudioAc4AssociateType_eCommentary,
    NEXUS_AudioAc4AssociateType_eMax
} NEXUS_AudioAc4AssociateType;
typedef struct NEXUS_AudioDecoderAc4PresentationStatus
{
    unsigned index;
    char id[20];
    NEXUS_AudioAc4AssociateType associateType;
    char name[36];
    char language[8];
} NEXUS_AudioDecoderAc4PresentationStatus;
typedef struct NEXUS_AudioDecoderPresentationStatus
{
    NEXUS_AudioCodec codec;
    union {
        NEXUS_AudioDecoderAc4PresentationStatus ac4;
    } status;
} NEXUS_AudioDecoderPresentationStatus;
typedef struct NEXUS_AudioDecoderTrickState
{
    _Bool forceStopped;
    unsigned rate;
    _Bool muted;
    _Bool tsmEnabled;
    _Bool stcTrickEnabled;
    _Bool stopForTrick;
} NEXUS_AudioDecoderTrickState;
typedef enum NEXUS_AudioDecoderDualMonoMode
{
    NEXUS_AudioDecoderDualMonoMode_eStereo,
    NEXUS_AudioDecoderDualMonoMode_eLeft,
    NEXUS_AudioDecoderDualMonoMode_eRight,
    NEXUS_AudioDecoderDualMonoMode_eMix,
    NEXUS_AudioDecoderDualMonoMode_eMax
} NEXUS_AudioDecoderDualMonoMode;
typedef enum NEXUS_AudioDecoderOutputLfeMode
{
    NEXUS_AudioDecoderOutputLfeMode_eAuto,
    NEXUS_AudioDecoderOutputLfeMode_eOff,
    NEXUS_AudioDecoderOutputLfeMode_eOn,
    NEXUS_AudioDecoderOutputLfeMode_eMax
} NEXUS_AudioDecoderOutputLfeMode;
typedef struct NEXUS_AudioDecoderKaraokeSettings
{
    unsigned vocalSuppressionLevel;
    unsigned vocalSuppressionFrequency;
    unsigned outputMakeupBoost;
} NEXUS_AudioDecoderKaraokeSettings;
typedef struct NEXUS_AudioDecoderSettings
{
    NEXUS_AudioDecoderDualMonoMode dualMonoMode;
    NEXUS_AudioMode outputMode;
    NEXUS_AudioDecoderOutputLfeMode outputLfeMode;
    unsigned fifoThreshold;
    int ptsOffset;
    unsigned discardThreshold;
    unsigned gaThreshold;
    _Bool wideGaThreshold;
    _Bool loudnessEquivalenceEnabled;
    _Bool ancillaryDataEnabled;
    NEXUS_CallbackDesc sourceChanged;
    NEXUS_CallbackDesc lockChanged;
    NEXUS_CallbackDesc ptsError;
    NEXUS_CallbackDesc firstPts;
    NEXUS_CallbackDesc fifoOverflow;
    NEXUS_CallbackDesc fifoUnderflow;
    NEXUS_CallbackDesc streamStatusAvailable;
    NEXUS_CallbackDesc ancillaryData;
    NEXUS_CallbackDesc dialnormChanged;
    int32_t volumeMatrix[NEXUS_AudioChannel_eMax][NEXUS_AudioChannel_eMax];
    _Bool muted;
    NEXUS_AudioDecoderHandle descriptionDecoder;
    unsigned descriptionRampTime;
    NEXUS_AudioDecoderKaraokeSettings karaokeSettings;
} NEXUS_AudioDecoderSettings;
typedef enum NEXUS_AudioDecoderDolbyDrcMode
{
    NEXUS_AudioDecoderDolbyDrcMode_eLine,
    NEXUS_AudioDecoderDolbyDrcMode_eRf,
    NEXUS_AudioDecoderDolbyDrcMode_eCustomA,
    NEXUS_AudioDecoderDolbyDrcMode_eCustomD,
    NEXUS_AudioDecoderDolbyDrcMode_eOff,
    NEXUS_AudioDecoderDolbyDrcMode_eCustomTarget,
    NEXUS_AudioDecoderDolbyDrcMode_eMax
} NEXUS_AudioDecoderDolbyDrcMode;
typedef enum NEXUS_AudioDecoderDolbyStereoDownmixMode
{
    NEXUS_AudioDecoderDolbyStereoDownmixMode_eAutomatic,
    NEXUS_AudioDecoderDolbyStereoDownmixMode_eDolbySurroundCompatible,
    NEXUS_AudioDecoderDolbyStereoDownmixMode_eStandard,
    NEXUS_AudioDecoderDolbyStereoDownmixMode_eMax
} NEXUS_AudioDecoderDolbyStereoDownmixMode;
typedef struct NEXUS_AudioDecoderDolbySettings
{
    NEXUS_AudioDecoderDolbyDrcMode drcMode;
    NEXUS_AudioDecoderDolbyDrcMode drcModeDownmix;
    unsigned customTargetLevel;
    unsigned customTargetLevelDownmix;
    NEXUS_AudioDecoderDolbyStereoDownmixMode stereoDownmixMode;
    uint16_t cut;
    uint16_t boost;
    uint16_t cutDownmix;
    uint16_t boostDownmix;
    uint16_t scale;
    uint16_t scaleDownmix;
    _Bool dialogNormalization;
    unsigned dialogNormalizationValue;
    unsigned substreamId;
    _Bool enableAtmosProcessing;
    unsigned certificationMode;
} NEXUS_AudioDecoderDolbySettings;
typedef enum NEXUS_AudioDecoderAacDownmixMode
{
    NEXUS_AudioDecoderAacDownmixMode_eMatrix,
    NEXUS_AudioDecoderAacDownmixMode_eArib,
    NEXUS_AudioDecoderAacDownmixMode_eLtRt,
    NEXUS_AudioDecoderAacDownmixMode_eLoRo,
    NEXUS_AudioDecoderAacDownmixMode_eMax
} NEXUS_AudioDecoderAacDownmixMode;
typedef enum NEXUS_AudioDecoderDolbyPulseDrcMode
{
    NEXUS_AudioDecoderDolbyPulseDrcMode_eLine,
    NEXUS_AudioDecoderDolbyPulseDrcMode_eRf,
    NEXUS_AudioDecoderDolbyPulseDrcMode_eOff,
    NEXUS_AudioDecoderDolbyPulseDrcMode_eMax
}NEXUS_AudioDecoderDolbyPulseDrcMode;
typedef struct NEXUS_AudioDecoderAacSettings
{
    uint16_t cut;
    uint16_t boost;
    uint16_t drcTargetLevel;
    uint16_t drcDefaultLevel;
    _Bool decode96Khz;
    _Bool mpegConformanceMode;
    _Bool enableSbrDecoding;
    NEXUS_AudioDecoderAacDownmixMode downmixMode;
    NEXUS_AudioDecoderDolbyPulseDrcMode drcMode;
    _Bool ignoreEmbeddedPrl;
} NEXUS_AudioDecoderAacSettings;
typedef struct NEXUS_AudioDecoderMpegSettings
{
    int inputReferenceLevel;
    _Bool attenuateMonoToStereo;
} NEXUS_AudioDecoderMpegSettings;
typedef struct NEXUS_AudioDecoderWmaProSettings
{
    _Bool dynamicRangeControlValid;
    struct {
        unsigned peakReference;
        unsigned peakTarget;
        unsigned averageReference;
        unsigned averageTarget;
    } dynamicRangeControl;
}NEXUS_AudioDecoderWmaProSettings;
typedef enum NEXUS_AudioDecoderDtsStereoDownmixMode
{
    NEXUS_AudioDecoderDtsDownmixMode_eAuto,
    NEXUS_AudioDecoderDtsDownmixMode_eLtRt,
    NEXUS_AudioDecoderDtsDownmixMode_eLoRo,
    NEXUS_AudioDecoderDtsDownmixMode_eMax
} NEXUS_AudioDecoderDtsStereoDownmixMode;
typedef struct NEXUS_AudioDecoderDtsSettings
{
    _Bool littleEndian;
    _Bool mixLfeToPrimary;
    _Bool enableDrc;
    uint16_t cut;
    uint16_t boost;
    NEXUS_AudioDecoderDtsStereoDownmixMode stereoDownmixMode;
} NEXUS_AudioDecoderDtsSettings;
typedef struct NEXUS_AudioDecoderAdpcmSettings
{
    _Bool enableGain;
    unsigned gainFactor;
} NEXUS_AudioDecoderAdpcmSettings;
typedef struct NEXUS_AudioDecoderIlbcSettings
{
    _Bool packetLoss;
    unsigned frameLength;
    _Bool enableGain;
    unsigned gainFactor;
} NEXUS_AudioDecoderIlbcSettings;
typedef enum NEXUS_AudioCodecBandMode
{
    NEXUS_AudioCodecBandMode_eWide,
    NEXUS_AudioCodecBandMode_eNarrow,
    NEXUS_AudioCodecBandMode_eMax
} NEXUS_AudioCodecBandMode;
typedef struct NEXUS_AudioDecoderIsacSettings
{
    _Bool packetLoss;
    NEXUS_AudioCodecBandMode bandMode;
    _Bool enableGain;
    unsigned gainFactor;
} NEXUS_AudioDecoderIsacSettings;
typedef enum NEXUS_AudioDecoderStereoDownmixMode
{
    NEXUS_AudioDecoderStereoDownmixMode_eLtRt,
    NEXUS_AudioDecoderStereoDownmixMode_eLoRo,
    NEXUS_AudioDecoderStereoDownmixMode_eArib,
    NEXUS_AudioDecoderStereoDownmixMode_eMatrix,
    NEXUS_AudioDecoderStereoDownmixMode_eAuto,
    NEXUS_AudioDecoderStereoDownmixMode_eMax
} NEXUS_AudioDecoderStereoDownmixMode;
typedef struct NEXUS_AudioDecoderAlsSettings
{
    NEXUS_AudioDecoderStereoDownmixMode stereoMode;
    uint8_t aribMatrixMixdownIndex;
} NEXUS_AudioDecoderAlsSettings;
typedef enum NEXUS_AudioDecoderAc4PresentationSelectionMode
{
    NEXUS_AudioDecoderAc4PresentationSelectionMode_eAuto,
    NEXUS_AudioDecoderAc4PresentationSelectionMode_ePresentationIndex,
    NEXUS_AudioDecoderAc4PresentationSelectionMode_ePresentationIdentifier,
    NEXUS_AudioDecoderAc4PresentationSelectionMode_eMax
} NEXUS_AudioDecoderAc4PresentationSelectionMode;
typedef struct NEXUS_AudioDecoderAc4Settings
{
    NEXUS_AudioDecoderDolbyDrcMode drcMode;
    NEXUS_AudioDecoderDolbyDrcMode drcModeDownmix;
    uint16_t drcScaleHi;
    uint16_t drcScaleLow;
    uint16_t drcScaleHiDownmix;
    uint16_t drcScaleLowDownmix;
    NEXUS_AudioDecoderStereoDownmixMode stereoMode;
    unsigned programSelection;
    int programBalance;
    NEXUS_AudioDecoderAc4PresentationSelectionMode selectionMode;
    unsigned presentationIndex;
    char presentationId[20];
    int dialogEnhancerAmount;
    unsigned certificationMode;
    _Bool preferLanguageOverAssociateType;
    struct {
        char selection[8];
    } languagePreference[2];
    NEXUS_AudioAc4AssociateType preferredAssociateType;
    _Bool enableAssociateMixing;
} NEXUS_AudioDecoderAc4Settings;
typedef struct NEXUS_AudioDecoderCodecSettings
{
    NEXUS_AudioCodec codec;
    union
    {
        NEXUS_AudioDecoderDolbySettings ac3;
        NEXUS_AudioDecoderDolbySettings ac3Plus;
        NEXUS_AudioDecoderAacSettings aac;
        NEXUS_AudioDecoderAacSettings aacPlus;
        NEXUS_AudioDecoderMpegSettings mpeg;
        NEXUS_AudioDecoderMpegSettings mp3;
        NEXUS_AudioDecoderWmaProSettings wmaPro;
        NEXUS_AudioDecoderDtsSettings dts;
        NEXUS_AudioDecoderAdpcmSettings adpcm;
        NEXUS_AudioDecoderIlbcSettings ilbc;
        NEXUS_AudioDecoderIsacSettings isac;
        NEXUS_AudioDecoderAlsSettings als;
        NEXUS_AudioDecoderAc4Settings ac4;
    } codecSettings;
} NEXUS_AudioDecoderCodecSettings;
typedef struct NEXUS_AudioAncillaryDataHeader
{
    unsigned blockSize;
    unsigned payloadSize;
    unsigned payloadSizeBits;
    unsigned frameNumber;
} NEXUS_AudioAncillaryDataHeader;
typedef struct NEXUS_AudioDecoderDecodeToMemorySettings
{
    unsigned maxBuffers;
    unsigned maxSampleRate;
    unsigned bitsPerSample;
    unsigned numPcmChannels;
    NEXUS_AudioChannel channelLayout[NEXUS_AudioChannel_eMax];
    NEXUS_CallbackDesc bufferComplete;
} NEXUS_AudioDecoderDecodeToMemorySettings;
typedef struct NEXUS_AudioDecoderDecodeToMemoryStatus
{
    unsigned bufferSize;
    unsigned pendingBuffers;
    unsigned completedBuffers;
} NEXUS_AudioDecoderDecodeToMemoryStatus;
typedef struct NEXUS_AudioDecoderFrameStatus
{
    uint32_t pts;
    NEXUS_PtsType ptsType;
    size_t filledBytes;
    unsigned sampleRate;
    unsigned bufferOffset;
} NEXUS_AudioDecoderFrameStatus;
typedef struct NEXUS_AutoVolumeLevelSettings
{
    _Bool enabled;
    _Bool loudnessEqualization;
    int target;
    int lowerBound;
    unsigned fixedBoost;
    unsigned ref;
    unsigned alpha;
    unsigned beta;
    unsigned threshold;
    unsigned dtfPercent;
    unsigned alpha2;
    unsigned fastGainRamp;
    unsigned dtf;
} NEXUS_AutoVolumeLevelSettings;
typedef struct NEXUS_AutoVolumeLevelStatus
{
    unsigned numChannels;
    int peakLevel[NEXUS_AudioChannel_eMax];
    int rmsLevel[NEXUS_AudioChannel_eMax];
    uint32_t pts;
} NEXUS_AutoVolumeLevelStatus;
typedef enum NEXUS_TruVolumeBlockSize
{
    NEXUS_TruVolumeBlockSize_e256,
    NEXUS_TruVolumeBlockSize_e512,
    NEXUS_TruVolumeBlockSize_e768,
    NEXUS_TruVolumeBlockSize_e1024,
    NEXUS_TruVolumeBlockSize_eMax
} NEXUS_TruVolumeBlockSize;
typedef enum NEXUS_TruVolumeMode
{
    NEXUS_TruVolumeMode_eLight,
    NEXUS_TruVolumeMode_eNormal,
    NEXUS_TruVolumeMode_eHeavy,
    NEXUS_TruVolumeMode_eMax
} NEXUS_TruVolumeMode;
typedef enum NEXUS_TruVolumeSpeakerResolution
{
    NEXUS_TruVolumeSpeakerResolution_e20Hz,
    NEXUS_TruVolumeSpeakerResolution_e40Hz,
    NEXUS_TruVolumeSpeakerResolution_e110Hz,
    NEXUS_TruVolumeSpeakerResolution_e200Hz,
    NEXUS_TruVolumeSpeakerResolution_e315Hz,
    NEXUS_TruVolumeSpeakerResolution_e410Hz,
    NEXUS_TruVolumeSpeakerResolution_eMax
} NEXUS_TruVolumeSpeakerResolution;
typedef enum NEXUS_SrsFilterCoefGenMode
{
    NEXUS_SrsFilterCoefGenMode_eFilterUser,
    NEXUS_SrsFilterCoefGenMode_eFilterSpec,
    NEXUS_SrsFilterCoefGenMode_eMax
} NEXUS_SrsFilterCoefGenMode;
typedef enum NEXUS_SrsFilterOrder
{
    NEXUS_SrsFilterOrder_eOrder0 = 0,
    NEXUS_SrsFilterOrder_eOrder2 = 2,
    NEXUS_SrsFilterOrder_eOrder4 = 4,
    NEXUS_SrsFilterOrder_eOrder6 = 6,
    NEXUS_SrsFilterOrder_eMax
} NEXUS_SrsFilterOrder;
typedef struct NEXUS_SrsHighPassFilterCoef
{
    unsigned scale;
    int coefficientB0;
    int coefficientB1;
    int coefficientB2;
    int coefficientA1;
    int coefficientA2;
} NEXUS_SrsHighPassFilterCoef;
typedef struct NEXUS_SrsHighPassFilterCoefUserParam
{
    NEXUS_SrsFilterOrder filterOrder;
    NEXUS_SrsHighPassFilterCoef coefficients[3];
} NEXUS_SrsHighPassFilterCoefUserParam;
typedef struct NEXUS_SrsHighPassFilterCoefSpecParam
{
    unsigned cutOffFrequency;
    NEXUS_SrsFilterOrder filterOrder;
} NEXUS_SrsHighPassFilterCoefSpecParam;
typedef struct NEXUS_SrsHighPassFilterSettings
{
    _Bool enabled;
    NEXUS_SrsFilterCoefGenMode coefGenMode;
    union
    {
        NEXUS_SrsHighPassFilterCoefUserParam highPassFilterCoefUser[3];
        NEXUS_SrsHighPassFilterCoefSpecParam highPassFilterCoefSpec;
    } coefParam;
} NEXUS_SrsHighPassFilterSettings;
typedef struct NEXUS_TruVolumeSettings
{
    _Bool enabled;
    NEXUS_TruVolumeBlockSize blockSize;
    _Bool enableNormalGain;
    unsigned inputGain;
    unsigned outputGain;
    unsigned bypassGain;
    unsigned referenceLevel;
    NEXUS_TruVolumeMode mode;
    NEXUS_TruVolumeSpeakerResolution speakerResolution;
    unsigned maxGain;
    _Bool enableDcNotchFilter;
    _Bool enableNoiseManager;
    int noiseManagerThreshold;
    _Bool enableNormalizer;
    unsigned calibrate;
    NEXUS_SrsHighPassFilterSettings highPassFilter;
} NEXUS_TruVolumeSettings;
typedef enum NEXUS_DolbyDigitalReencodeDownmixMode
{
    NEXUS_DolbyDigitalReencodeDownmixMode_eLtRt,
    NEXUS_DolbyDigitalReencodeDownmixMode_eLoRo,
    NEXUS_DolbyDigitalReencodeDownmixMode_eArib,
    NEXUS_DolbyDigitalReencodeDownmixMode_eMax
} NEXUS_DolbyDigitalReencodeDownmixMode;
typedef enum NEXUS_DolbyDigitalReencodeProfile
{
    NEXUS_DolbyDigitalReencodeProfile_eNoCompression,
    NEXUS_DolbyDigitalReencodeProfile_eFilmStandardCompression,
    NEXUS_DolbyDigitalReencodeProfile_eFilmLightCompression,
    NEXUS_DolbyDigitalReencodeProfile_eMusicStandardCompression,
    NEXUS_DolbyDigitalReencodeProfile_eMusicLightCompression,
    NEXUS_DolbyDigitalReencodeProfile_eSpeechCompression,
    NEXUS_DolbyDigitalReencodeProfile_eMax
} NEXUS_DolbyDigitalReencodeProfile;
typedef struct NEXUS_Ac3EncodeSettings
{
    _Bool spdifHeaderEnabled;
    _Bool certificationMode;
} NEXUS_Ac3EncodeSettings;
typedef struct NEXUS_DolbyDigitalReencodeSettings
{
    NEXUS_Ac3EncodeSettings encodeSettings;
    NEXUS_AudioDecoderDualMonoMode dualMonoMode;
    NEXUS_AudioMode outputMode;
    NEXUS_AudioDecoderOutputLfeMode outputLfeMode;
    NEXUS_AudioMultichannelFormat multichannelFormat;
    _Bool fixedEncoderFormat;
    NEXUS_AudioDecoderDolbyDrcMode drcMode;
    NEXUS_AudioDecoderDolbyDrcMode drcModeDownmix;
    NEXUS_DolbyDigitalReencodeDownmixMode stereoDownmixMode;
    uint16_t cut;
    uint16_t boost;
    _Bool loudnessEquivalenceEnabled;
    _Bool externalPcmMode;
    _Bool certificationMode;
    NEXUS_DolbyDigitalReencodeProfile profile;
    NEXUS_AudioAc3CenterMixLevel centerMixLevel;
    NEXUS_AudioAc3SurroundMixLevel surroundMixLevel;
    NEXUS_AudioAc3DolbySurround dolbySurround;
    unsigned dialogLevel;
    NEXUS_AudioAc3Acmod inputAcmod;
    _Bool inputHasLfe;
    _Bool inputHasDv258Applied;
} NEXUS_DolbyDigitalReencodeSettings;
typedef struct NEXUS_DolbyVolume258Settings
{
    _Bool enabled;
    int preGain;
    unsigned inputReferenceLevel;
    unsigned outputReferenceLevel;
    int calibrationOffset;
    _Bool reset;
    _Bool volumeModelerEnabled;
    int digitalVolumeLevel;
    int analogVolumeLevel;
    _Bool volumeLevelerEnabled;
    _Bool midsideProcessingEnabled;
    _Bool halfModeEnabled;
    unsigned volumeLevelerAmount;
    _Bool limiterEnabled;
} NEXUS_DolbyVolume258Settings;
typedef struct NEXUS_KaraokeVocalSettings
{
    struct
    {
        _Bool enabled;
        unsigned attenuation;
        unsigned delay;
    } echo;
} NEXUS_KaraokeVocalSettings;
typedef struct NEXUS_Ac3Encode *NEXUS_Ac3EncodeHandle;
void NEXUS_Ac3Encode_GetDefaultSettings(
    NEXUS_Ac3EncodeSettings *pSettings
    );
NEXUS_Ac3EncodeHandle NEXUS_Ac3Encode_Open(
    const NEXUS_Ac3EncodeSettings *pSettings
    );
void NEXUS_Ac3Encode_Close(
    NEXUS_Ac3EncodeHandle handle
    );
void NEXUS_Ac3Encode_GetSettings(
    NEXUS_Ac3EncodeHandle handle,
    NEXUS_Ac3EncodeSettings *pSettings
    );
NEXUS_Error NEXUS_Ac3Encode_SetSettings(
    NEXUS_Ac3EncodeHandle handle,
    const NEXUS_Ac3EncodeSettings *pSettings
    );
NEXUS_AudioInputHandle NEXUS_Ac3Encode_GetConnector(
    NEXUS_Ac3EncodeHandle handle
    );
NEXUS_Error NEXUS_Ac3Encode_AddInput(
    NEXUS_Ac3EncodeHandle handle,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_Ac3Encode_RemoveInput(
    NEXUS_Ac3EncodeHandle handle,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_Ac3Encode_RemoveAllInputs(
    NEXUS_Ac3EncodeHandle handle
    );
typedef struct NEXUS_Amplifier *NEXUS_AmplifierHandle;
typedef enum NEXUS_AmplifierGainMode
{
    NEXUS_AmplifierGainMode_eAutomatic,
    NEXUS_AmplifierGainMode_eManual,
    NEXUS_AmplifierGainMode_eMax
} NEXUS_AmplifierGainMode;
typedef struct NEXUS_AmplifierSettings
{
    _Bool enabled;
    NEXUS_AmplifierGainMode gainMode;
    union
    {
        struct
        {
            unsigned outputLevel;
            int deltaValue;
        } automatic;
        struct
        {
            unsigned gain;
        } manual;
    } gainSettings;
} NEXUS_AmplifierSettings;
void NEXUS_Amplifier_GetSettings(
    NEXUS_AmplifierHandle handle,
    NEXUS_AmplifierSettings *pSettings
    );
NEXUS_Error NEXUS_Amplifier_SetSettings(
    NEXUS_AmplifierHandle handle,
    const NEXUS_AmplifierSettings *pSettings
    );
NEXUS_Error NEXUS_Amplifier_EnableExternalDriver(
    NEXUS_AmplifierHandle handle,
    unsigned portNum,
    _Bool enabled
    );
typedef enum NEXUS_AmplifierInBandMode
{
    NEXUS_AmplifierInBandMode_eOpenCable,
    NEXUS_AmplifierInBandMode_eAnalog,
    NEXUS_AmplifierInBandMode_eDigital,
    NEXUS_AmplifierInBandMode_ePowerDown,
    NEXUS_AmplifierInBandMode_eMax
} NEXUS_AmplifierInBandMode;
NEXUS_Error NEXUS_Amplifier_SetInBandMode(
    NEXUS_AmplifierHandle handle,
    unsigned inBandPortNum,
    NEXUS_AmplifierInBandMode inBandMode
    );
typedef enum NEXUS_AmplifierOutOfBandMode
{
    NEXUS_AmplifierOutOfBandMode_eMaxGain,
    NEXUS_AmplifierOutOfBandMode_eBypass,
    NEXUS_AmplifierOutOfBandMode_eNormal,
    NEXUS_AmplifierOutOfBandMode_ePowerDown,
    NEXUS_AmplifierOutOfBandMode_eMax
} NEXUS_AmplifierOutOfBandMode;
NEXUS_Error NEXUS_Amplifier_SetOutOfBandMode(
    NEXUS_AmplifierHandle handle,
    unsigned outOfBandPortNum,
    NEXUS_AmplifierOutOfBandMode outOfBandMode
    );
NEXUS_AmplifierHandle NEXUS_Amplifier_OpenStub(
    unsigned index
    );
void NEXUS_Amplifier_Close(
    NEXUS_AmplifierHandle handle
    );
typedef struct NEXUS_AmplifierStatus
{
    NEXUS_AmplifierGainMode gainMode;
    NEXUS_AmplifierInBandMode inBandPortMode[(5)];
    NEXUS_AmplifierOutOfBandMode outOfBandPortMode[(5)];
    _Bool isExternalDriverEnabled[(5)];
    unsigned agcOutputLevel;
    int agcDeltaVal;
    unsigned manualGainVal;
    unsigned agcGain;
    _Bool gainBoostEnabled;
    _Bool superBoostEnabled;
    _Bool tiltEnabled;
} NEXUS_AmplifierStatus;
NEXUS_Error NEXUS_Amplifier_GetStatus(
    NEXUS_AmplifierHandle handle,
    NEXUS_AmplifierStatus *pStatus
    );
typedef struct NEXUS_MemoryAllocationSettings
{
    NEXUS_HeapHandle heap;
    size_t alignment;
} NEXUS_MemoryAllocationSettings;
typedef struct NEXUS_MemoryBlockAllocationSettings {
    unsigned unused;
} NEXUS_MemoryBlockAllocationSettings;
void NEXUS_MemoryBlock_GetDefaultAllocationSettings(
    NEXUS_MemoryBlockAllocationSettings *pSettings
    );
NEXUS_MemoryBlockHandle NEXUS_MemoryBlock_Allocate_tagged(
    NEXUS_HeapHandle heap,
    size_t numBytes,
    size_t alignment,
    const NEXUS_MemoryBlockAllocationSettings *pSettings,
    const char *fileName,
    unsigned lineNumber
    );
void NEXUS_MemoryBlock_Free(
    NEXUS_MemoryBlockHandle memoryBlock
    );
NEXUS_Error NEXUS_MemoryBlock_Lock(
    NEXUS_MemoryBlockHandle memoryBlock,
    void **ppMemory
    );
void NEXUS_MemoryBlock_Unlock(
    NEXUS_MemoryBlockHandle memoryBlock
    );
NEXUS_MemoryBlockHandle NEXUS_MemoryBlock_FromAddress(
    void *pMemory
    );
void NEXUS_Memory_GetDefaultAllocationSettings(
    NEXUS_MemoryAllocationSettings *pSettings
    );
NEXUS_Error NEXUS_Memory_Allocate_tagged(
    size_t numBytes,
    const NEXUS_MemoryAllocationSettings *pSettings,
    void **ppMemory,
    const char *fileName,
    unsigned lineNumber
    );
void NEXUS_Memory_Free(
    void *pMemory
    );
void NEXUS_Memory_FlushCache(
    const void *pMemory,
    size_t numBytes
    );
typedef struct NEXUS_MemoryStatus
{
    unsigned memoryType;
    unsigned heapType;
    unsigned memcIndex;
    NEXUS_Addr offset;
    void *addr;
    unsigned size;
    unsigned free;
    unsigned alignment;
    unsigned numAllocs;
    unsigned numFreeBlocks;
    unsigned largestFreeBlock;
    unsigned highWatermark;
    _Bool guardBanding;
    _Bool dynamic;
} NEXUS_MemoryStatus;
NEXUS_Error NEXUS_Heap_GetStatus(
    NEXUS_HeapHandle heap,
    NEXUS_MemoryStatus *pStatus
    );
void NEXUS_Heap_GetDefaultDisplayHeapSettings(
    NEXUS_DisplayHeapSettings *pSettings
    );
void NEXUS_Heap_GetDisplayHeapSettings(
    NEXUS_HeapHandle heap,
    NEXUS_DisplayHeapSettings *pSettings
    );
NEXUS_Error NEXUS_Heap_SetDisplayHeapSettings(
    NEXUS_HeapHandle heap,
    const NEXUS_DisplayHeapSettings *pSettings
    );
void NEXUS_Heap_Dump(
    NEXUS_HeapHandle heap
    );
void NEXUS_Heap_ResetHighWatermark(
    NEXUS_HeapHandle heap
    );
void NEXUS_Memory_PrintStatus(void);
void NEXUS_Memory_PrintHeaps(void);
NEXUS_Error NEXUS_MemoryBlock_LockOffset(
                                         NEXUS_MemoryBlockHandle block,
                                         NEXUS_Addr *addr
                                         );
void NEXUS_MemoryBlock_UnlockOffset(
                                    NEXUS_MemoryBlockHandle block
                                    );
void NEXUS_MemoryBlock_CheckIfLocked(
    NEXUS_MemoryBlockHandle memoryBlock
    );
NEXUS_Error NEXUS_Memory_MoveUnlockedBlocks(
    NEXUS_HeapHandle fromHeap,
    NEXUS_HeapHandle toHeap,
    unsigned maxNumber,
    unsigned *pNumMoved
    );
void NEXUS_Heap_ToString(
    const NEXUS_MemoryStatus *pStatus,
    char *buf,
    unsigned bufsize
    );
typedef enum NEXUS_HeapLookupType
{
    NEXUS_HeapLookupType_eMain,
    NEXUS_HeapLookupType_eCompressedRegion,
    NEXUS_HeapLookupType_eExportRegion,
    NEXUS_HeapLookupType_eMax
} NEXUS_HeapLookupType;
NEXUS_HeapHandle NEXUS_Heap_Lookup(
    NEXUS_HeapLookupType lookupType
    );
NEXUS_HeapHandle NEXUS_Heap_CreateInternal (
        void
        );
void NEXUS_Heap_DestroyInternal(
        NEXUS_HeapHandle heap
        );
typedef struct NEXUS_MemoryBlockProperties
{
    unsigned memoryType;
    size_t size;
} NEXUS_MemoryBlockProperties;
typedef struct NEXUS_MemoryBlockTag
{
    char fileName[64];
    unsigned lineNumber;
} NEXUS_MemoryBlockTag;
NEXUS_MemoryBlockHandle NEXUS_MemoryBlock_Allocate_driver(
    NEXUS_HeapHandle heap,
    size_t numBytes,
    size_t alignment,
    const NEXUS_MemoryBlockAllocationSettings *pSettings,
    const NEXUS_MemoryBlockTag *pTag,
    NEXUS_MemoryBlockProperties *pProperties
    );
void NEXUS_MemoryBlock_Free_driver(
    NEXUS_MemoryBlockHandle memoryBlock
    );
void NEXUS_MemoryBlock_GetProperties(
    NEXUS_MemoryBlockHandle memoryBlock,
    NEXUS_MemoryBlockProperties *pProperties
    );
typedef struct NEXUS_MemoryBlockUserState {
    NEXUS_P_MemoryUserAddr state;
} NEXUS_MemoryBlockUserState;
NEXUS_Error NEXUS_MemoryBlock_GetUserState(
    NEXUS_MemoryBlockHandle memoryBlock,
    NEXUS_MemoryBlockUserState *userState
    );
void NEXUS_MemoryBlock_SetUserState(
    NEXUS_MemoryBlockHandle memoryBlock,
    const NEXUS_MemoryBlockUserState *userState
    );
void NEXUS_MemoryBlock_Free_local (
    NEXUS_MemoryBlockHandle memoryBlock
    );
NEXUS_FrontendConnectorHandle NEXUS_FrontendConnector_Create(
    void);
NEXUS_FrontendConnectorHandle NEXUS_FrontendConnector_Acquire(
    unsigned index
    );
void NEXUS_FrontendConnector_Release(
    NEXUS_FrontendConnectorHandle handle
    );
void NEXUS_FrontendConnector_Destroy(
    NEXUS_FrontendConnectorHandle handle
    );
NEXUS_VideoInputHandle NEXUS_VideoInput_Create(
    void
    );
void NEXUS_VideoInput_Destroy(
    NEXUS_VideoInputHandle videoInput
    );
NEXUS_VideoOutputHandle NEXUS_VideoOutput_Create(
    void
    );
void NEXUS_VideoOutput_Destroy(
    NEXUS_VideoOutputHandle videoOutput
    );
NEXUS_AudioOutputHandle NEXUS_AudioOutput_Create(
    void
    );
void NEXUS_AudioOutput_Destroy(
    NEXUS_AudioOutputHandle audioOutput
    );
NEXUS_AudioInputHandle NEXUS_AudioInput_Create(
    void
    );
void NEXUS_AudioInput_Destroy(
    NEXUS_AudioInputHandle audioInput
    );
void NEXUS_Memory_GetVideoSecureHeap(
    NEXUS_Addr *pOffset,
    unsigned *pSize
    );
NEXUS_Error NEXUS_Heap_GetStatus_driver(
    NEXUS_HeapHandle heap,
    NEXUS_MemoryStatus *pStatus
    );
typedef struct NEXUS_HeapRuntimeSettings
{
    _Bool secure;
} NEXUS_HeapRuntimeSettings;
typedef struct NEXUS_SurfaceMemory
{
    void *buffer;
    unsigned int pitch;
    NEXUS_Pixel *palette;
    unsigned numPaletteEntries;
    size_t bufferSize;
} NEXUS_SurfaceMemory;
typedef struct NEXUS_SurfaceStatus {
    NEXUS_PixelFormat pixelFormat;
    NEXUS_PixelFormat palettePixelFormat;
    uint16_t width;
    uint16_t height;
    unsigned int pitch;
    unsigned numPaletteEntries;
} NEXUS_SurfaceStatus;
typedef struct NEXUS_SurfaceCreateSettings
{
    NEXUS_PixelFormat pixelFormat;
    NEXUS_PixelFormat palettePixelFormat;
    uint16_t width;
    uint16_t height;
    uint8_t alignment;
    _Bool managedAccess;
    unsigned int pitch;
    void *pMemory;
    void *pPaletteMemory;
    NEXUS_MemoryBlockHandle pixelMemory;
    unsigned pixelMemoryOffset;
    NEXUS_MemoryBlockHandle paletteMemory;
    unsigned paletteMemoryOffset;
    NEXUS_HeapHandle heap;
} NEXUS_SurfaceCreateSettings;
typedef struct NEXUS_StripedSurfaceCreateSettings {
    unsigned pitch;
    unsigned long imageWidth;
    unsigned long imageHeight;
    unsigned long stripedWidth;
    unsigned long lumaStripedHeight;
    unsigned long chromaStripedHeight;
    NEXUS_VideoBufferType bufferType;
    NEXUS_PixelFormat lumaPixelFormat;
    NEXUS_PixelFormat chromaPixelFormat;
    NEXUS_MemoryBlockHandle lumaBuffer;
    unsigned lumaBufferOffset;
    NEXUS_MemoryBlockHandle chromaBuffer;
    unsigned chromaBufferOffset;
    NEXUS_MemoryBlockHandle bottomFieldLumaBuffer;
    unsigned bottomFieldLumaBufferOffset;
    NEXUS_MemoryBlockHandle bottomFieldChromaBuffer;
    unsigned bottomFieldChromaBufferOffset;
    NEXUS_HeapHandle lumaHeap;
    NEXUS_HeapHandle chromaHeap;
} NEXUS_StripedSurfaceCreateSettings;
typedef struct NEXUS_VideoDecoder *NEXUS_VideoDecoderHandle;
typedef enum NEXUS_VideoDecoderErrorHandling
{
   NEXUS_VideoDecoderErrorHandling_eNone,
   NEXUS_VideoDecoderErrorHandling_ePicture,
   NEXUS_VideoDecoderErrorHandling_ePrognostic,
   NEXUS_VideoDecoderErrorHandling_eMax
} NEXUS_VideoDecoderErrorHandling;
typedef enum NEXUS_VideoDecoderProgressiveOverrideMode
{
   NEXUS_VideoDecoderProgressiveOverrideMode_eTopBottom,
   NEXUS_VideoDecoderProgressiveOverrideMode_eBottomTop,
   NEXUS_VideoDecoderProgressiveOverrideMode_eDisable,
   NEXUS_VideoDecoderProgressiveOverrideMode_eMax
} NEXUS_VideoDecoderProgressiveOverrideMode;
typedef enum NEXUS_VideoDecoderTimestampMode
{
    NEXUS_VideoDecoderTimestampMode_eDisplay = 0,
    NEXUS_VideoDecoderTimestampMode_eDecode,
    NEXUS_VideoDecoderTimestampMode_eMax
} NEXUS_VideoDecoderTimestampMode;
typedef struct NEXUS_VideoDecoderStartSettings
{
    NEXUS_PidChannelHandle pidChannel;
    NEXUS_PidChannelHandle enhancementPidChannel;
    NEXUS_VideoCodec codec;
    NEXUS_StcChannelHandle stcChannel;
    NEXUS_VideoDecoderErrorHandling errorHandling;
    unsigned errorHandlingThreshold;
    unsigned prerollRate;
    NEXUS_VideoFrameRate frameRate;
    NEXUS_AspectRatio aspectRatio;
    struct {
        unsigned x, y;
    } sampleAspectRatio;
    NEXUS_VideoDecoderProgressiveOverrideMode progressiveOverrideMode;
    NEXUS_VideoDecoderTimestampMode timestampMode;
    NEXUS_MatrixCoefficients defaultMatrixCoefficients;
    NEXUS_ColorPrimaries defaultColorPrimaries;
    NEXUS_TransferCharacteristics defaultTransferCharacteristics;
    _Bool nonRealTime;
    _Bool appDisplayManagement;
} NEXUS_VideoDecoderStartSettings;
typedef enum NEXUS_VideoDecoder_ChannelChangeMode
{
    NEXUS_VideoDecoder_ChannelChangeMode_eMute,
    NEXUS_VideoDecoder_ChannelChangeMode_eHoldUntilTsmLock,
    NEXUS_VideoDecoder_ChannelChangeMode_eMuteUntilFirstPicture,
    NEXUS_VideoDecoder_ChannelChangeMode_eHoldUntilFirstPicture
} NEXUS_VideoDecoder_ChannelChangeMode;
typedef enum NEXUS_StillContentInterpolationMode
{
    NEXUS_StillContentInterpolationMode_eDefault,
    NEXUS_StillContentInterpolationMode_eSingleField,
    NEXUS_StillContentInterpolationMode_eBothField,
    NEXUS_StillContentInterpolationMode_eFrame,
    NEXUS_StillContentInterpolationMode_eMax
} NEXUS_StillContentInterpolationMode;
typedef enum NEXUS_MovingContentInterpolationMode
{
    NEXUS_MovingContentInterpolationMode_eDefault,
    NEXUS_MovingContentInterpolationMode_eInterlacedScanout,
    NEXUS_MovingContentInterpolationMode_eProgressiveScanout,
    NEXUS_MovingContentInterpolationMode_eMax
} NEXUS_MovingContentInterpolationMode;
typedef enum NEXUS_VideoDecoderScanMode
{
    NEXUS_VideoDecoderScanMode_eAuto,
    NEXUS_VideoDecoderScanMode_ePsF,
    NEXUS_VideoDecoderScanMode_e1080p,
    NEXUS_VideoDecoderScanMode_eMax
} NEXUS_VideoDecoderScanMode;
typedef enum NEXUS_VideoDecoderHorizontalOverscanMode
{
    NEXUS_VideoDecoderHorizontalOverscanMode_eAuto,
    NEXUS_VideoDecoderHorizontalOverscanMode_eDisable,
    NEXUS_VideoDecoderHorizontalOverscanMode_eMax
} NEXUS_VideoDecoderHorizontalOverscanMode;
typedef enum NEXUS_VideoDecoderSourceOrientation {
    NEXUS_VideoDecoderSourceOrientation_e2D,
    NEXUS_VideoDecoderSourceOrientation_e3D_LeftRight,
    NEXUS_VideoDecoderSourceOrientation_e3D_OverUnder,
    NEXUS_VideoDecoderSourceOrientation_e3D_LeftRightFullFrame,
    NEXUS_VideoDecoderSourceOrientation_e3D_RightLeftFullFrame,
    NEXUS_VideoDecoderSourceOrientation_e3D_LeftRightEnhancedResolution,
    NEXUS_VideoDecoderSourceOrientation_eMax
} NEXUS_VideoDecoderSourceOrientation;
typedef struct NEXUS_VideoDecoderSettings
{
    _Bool freeze;
    _Bool mute;
    _Bool userDataEnabled;
    _Bool panScanEnabled;
    NEXUS_VideoDecoderErrorHandling errorHandling;
    NEXUS_VideoDecoder_ChannelChangeMode channelChangeMode;
    unsigned fifoThreshold;
    int ptsOffset;
    unsigned discardThreshold;
    NEXUS_CallbackDesc sourceChanged;
    NEXUS_CallbackDesc streamChanged;
    NEXUS_CallbackDesc appUserDataReady;
    NEXUS_CallbackDesc ptsError;
    NEXUS_CallbackDesc firstPts;
    NEXUS_CallbackDesc firstPtsPassed;
    NEXUS_CallbackDesc fifoEmpty;
    NEXUS_CallbackDesc afdChanged;
    NEXUS_CallbackDesc decodeError;
    struct {
        _Bool enable;
        unsigned preChargeCount;
        NEXUS_CallbackDesc chunkDone;
    } fnrtSettings;
    struct {
            struct {
                _Bool fifoNoLongerEmpty;
                _Bool fifoOverflow;
            } enabled;
            NEXUS_CallbackDesc callback;
    } stateChanged;
    _Bool preferredUserDataFormat;
    unsigned userDataFilterThreshold;
    _Bool dropFieldMode;
    _Bool manualPowerState;
    NEXUS_StillContentInterpolationMode stillContentInterpolationMode;
    NEXUS_MovingContentInterpolationMode movingContentInterpolationMode;
    NEXUS_VideoDecoderScanMode scanMode;
    _Bool customSourceOrientation;
    NEXUS_VideoDecoderSourceOrientation sourceOrientation;
    NEXUS_VideoDecoderHorizontalOverscanMode horizontalOverscanMode;
    _Bool supportedCodecs[NEXUS_VideoCodec_eMax];
    unsigned maxWidth, maxHeight;
    NEXUS_VideoFrameRate maxFrameRate;
    unsigned colorDepth;
} NEXUS_VideoDecoderSettings;
typedef struct NEXUS_VideoDecoderTimeCode
{
    unsigned short hours;
    unsigned short minutes;
    unsigned short seconds;
    unsigned short pictures;
} NEXUS_VideoDecoderTimeCode;
typedef enum NEXUS_VideoProtocolLevel
{
   NEXUS_VideoProtocolLevel_eUnknown = 0,
   NEXUS_VideoProtocolLevel_e00,
   NEXUS_VideoProtocolLevel_e10,
   NEXUS_VideoProtocolLevel_e1B,
   NEXUS_VideoProtocolLevel_e11,
   NEXUS_VideoProtocolLevel_e12,
   NEXUS_VideoProtocolLevel_e13,
   NEXUS_VideoProtocolLevel_e20,
   NEXUS_VideoProtocolLevel_e21,
   NEXUS_VideoProtocolLevel_e22,
   NEXUS_VideoProtocolLevel_e30,
   NEXUS_VideoProtocolLevel_e31,
   NEXUS_VideoProtocolLevel_e32,
   NEXUS_VideoProtocolLevel_e40,
   NEXUS_VideoProtocolLevel_e41,
   NEXUS_VideoProtocolLevel_e42,
   NEXUS_VideoProtocolLevel_e50,
   NEXUS_VideoProtocolLevel_e51,
   NEXUS_VideoProtocolLevel_e60,
   NEXUS_VideoProtocolLevel_e62,
   NEXUS_VideoProtocolLevel_eLow,
   NEXUS_VideoProtocolLevel_eMain,
   NEXUS_VideoProtocolLevel_eHigh,
   NEXUS_VideoProtocolLevel_eHigh1440,
   NEXUS_VideoProtocolLevel_eMax
} NEXUS_VideoProtocolLevel;
typedef enum NEXUS_VideoProtocolProfile
{
   NEXUS_VideoProtocolProfile_eUnknown = 0,
   NEXUS_VideoProtocolProfile_eSimple,
   NEXUS_VideoProtocolProfile_eMain,
   NEXUS_VideoProtocolProfile_eHigh,
   NEXUS_VideoProtocolProfile_eAdvanced,
   NEXUS_VideoProtocolProfile_eJizhun,
   NEXUS_VideoProtocolProfile_eSnrScalable,
   NEXUS_VideoProtocolProfile_eSpatiallyScalable,
   NEXUS_VideoProtocolProfile_eAdvancedSimple,
   NEXUS_VideoProtocolProfile_eBaseline,
   NEXUS_VideoProtocolProfile_eMultiHigh,
   NEXUS_VideoProtocolProfile_eStereoHigh,
   NEXUS_VideoProtocolProfile_eMain10,
   NEXUS_VideoProtocolProfile_eMax
} NEXUS_VideoProtocolProfile;
typedef struct NEXUS_VideoDecoderStatus
{
    _Bool started;
    struct
    {
        unsigned width, height;
    } source, coded, display;
    NEXUS_AspectRatio aspectRatio;
    NEXUS_VideoFrameRate frameRate;
    _Bool interlaced;
    NEXUS_VideoFormat format;
    NEXUS_VideoProtocolLevel protocolLevel;
    NEXUS_VideoProtocolProfile protocolProfile;
    _Bool muted;
    NEXUS_VideoDecoderTimeCode timeCode;
    unsigned long pictureTag;
    NEXUS_PictureCoding pictureCoding;
    _Bool tsm;
    uint32_t pts;
    int32_t ptsStcDifference;
    NEXUS_PtsType ptsType;
    _Bool firstPtsPassed;
    unsigned fifoDepth;
    unsigned fifoSize;
    unsigned queueDepth;
    unsigned cabacBinDepth;
    unsigned enhancementFifoDepth;
    unsigned enhancementFifoSize;
    unsigned numDecoded;
    unsigned numDisplayed;
    unsigned numIFramesDisplayed;
    unsigned numDecodeErrors;
    unsigned numDecodeOverflows;
    unsigned numDisplayErrors;
    unsigned numDecodeDrops;
    unsigned numPicturesReceived;
    unsigned numDisplayDrops;
    unsigned numDisplayUnderflows;
    unsigned ptsErrorCount;
    unsigned avdStatusBlock;
    unsigned numWatchdogs;
    uint64_t numBytesDecoded;
    unsigned fifoEmptyEvents;
    unsigned fifoNoLongerEmptyEvents;
} NEXUS_VideoDecoderStatus;
typedef struct NEXUS_VideoDecoderFrameStatus
{
    uint32_t serialNumber;
    uint32_t pts;
    _Bool ptsValid;
    _Bool lastPicture;
    NEXUS_PictureCoding pictureCoding;
    NEXUS_VideoFrameRate frameRate;
    NEXUS_PicturePullDown pullDown;
    struct {
        unsigned x, y;
    } sampleAspectRatio;
    NEXUS_AspectRatio aspectRatio;
    NEXUS_PictureScan sourceFormat;
    NEXUS_PictureScan sequence;
    NEXUS_StripedSurfaceCreateSettings surfaceCreateSettings;
} NEXUS_VideoDecoderFrameStatus;
typedef struct NEXUS_VideoDecoderReturnFrameSettings
{
    _Bool display;
} NEXUS_VideoDecoderReturnFrameSettings;
typedef enum NEXUS_VideoDecoderDecodeMode
{
    NEXUS_VideoDecoderDecodeMode_eAll,
    NEXUS_VideoDecoderDecodeMode_eIP,
    NEXUS_VideoDecoderDecodeMode_eI,
    NEXUS_VideoDecoderDecodeMode_eMax
} NEXUS_VideoDecoderDecodeMode;
typedef enum NEXUS_VideoDecoderReorderingMode
{
    NEXUS_VideoDecoderReorderingMode_eNone,
    NEXUS_VideoDecoderReorderingMode_eSequential,
    NEXUS_VideoDecoderReorderingMode_eGop,
    NEXUS_VideoDecoderReorderingMode_eInterleaved,
    NEXUS_VideoDecoderReorderingMode_eChunkForward,
    NEXUS_VideoDecoderReorderingMode_eChunkBackward,
    NEXUS_VideoDecoderReorderingMode_eMax
} NEXUS_VideoDecoderReorderingMode;
typedef enum NEXUS_TsmMode
{
    NEXUS_TsmMode_eDisabled,
    NEXUS_TsmMode_eEnabled,
    NEXUS_TsmMode_eSimulated,
    NEXUS_TsmMode_eMax
} NEXUS_TsmMode;
typedef enum NEXUS_VideoDecoderDqtMode
{
    NEXUS_VideoDecoderDqtMode_eDisabled,
    NEXUS_VideoDecoderDqtMode_eSinglePass,
    NEXUS_VideoDecoderDqtMode_eMultiPass,
    NEXUS_VideoDecoderDqtMode_eMax
} NEXUS_VideoDecoderDqtMode;
typedef struct NEXUS_VideoDecoderTrickState
{
    _Bool forceStopped;
    int rate;
    NEXUS_VideoDecoderDecodeMode decodeMode;
    _Bool brcmTrickModesEnabled;
    _Bool hostTrickModesEnabled;
    NEXUS_VideoDecoderDqtMode dqtEnabled;
    _Bool topFieldOnly;
    _Bool fieldByFieldAdvance;
    _Bool reverseFields;
    NEXUS_TsmMode tsmEnabled;
    _Bool stcTrickEnabled;
    NEXUS_VideoDecoderReorderingMode reorderingMode;
    unsigned forceSourceFrameRate;
    unsigned maxFrameRepeat;
    _Bool lowLatencyDisplayForTrickModes;
} NEXUS_VideoDecoderTrickState;
typedef struct NEXUS_VideoDecoderPlaybackSettings
{
    NEXUS_CallbackDesc firstPts;
    NEXUS_CallbackDesc firstPtsPassed;
} NEXUS_VideoDecoderPlaybackSettings;
typedef enum NEXUS_VideoDecoderLowLatencyMode
{
    NEXUS_VideoDecoderLowLatencyMode_eOff,
    NEXUS_VideoDecoderLowLatencyMode_eFast,
    NEXUS_VideoDecoderLowLatencyMode_eAverage,
    NEXUS_VideoDecoderLowLatencyMode_eAdaptive,
    NEXUS_VideoDecoderLowLatencyMode_eMax
} NEXUS_VideoDecoderLowLatencyMode;
typedef struct NEXUS_VideoDecoderLowLatencySettings
{
    NEXUS_VideoDecoderLowLatencyMode mode;
    unsigned latency;
    unsigned controlPeriod;
    unsigned minLatency;
    unsigned maxLatency;
} NEXUS_VideoDecoderLowLatencySettings;
typedef struct NEXUS_VideoDecoderExtendedSettings
{
    NEXUS_CallbackDesc dataReadyCallback;
    _Bool s3DTVStatusEnabled;
    NEXUS_CallbackDesc s3DTVStatusChanged;
    unsigned s3DTVStatusTimeout;
    _Bool ignoreDpbOutputDelaySyntax;
    _Bool zeroDelayOutputMode;
    _Bool earlyPictureDeliveryMode;
    _Bool svc3dEnabled;
    _Bool treatIFrameAsRap;
    _Bool ignoreNumReorderFramesEqZero;
    unsigned crcFifoSize;
    NEXUS_VideoDecoderLowLatencySettings lowLatencySettings;
    NEXUS_VideoEotf eotf;
    NEXUS_ContentLightLevel contentLightLevel;
    NEXUS_MasteringDisplayColorVolume masteringDisplayColorVolume;
} NEXUS_VideoDecoderExtendedSettings;
typedef struct NEXUS_VideoDecoderStreamInformation
{
    _Bool valid;
    uint32_t sourceHorizontalSize;
    uint32_t sourceVerticalSize;
    uint32_t codedSourceHorizontalSize;
    uint32_t codedSourceVerticalSize;
    uint32_t displayHorizontalSize;
    uint32_t displayVerticalSize;
    NEXUS_AspectRatio aspectRatio;
    uint16_t sampleAspectRatioX;
    uint16_t sampleAspectRatioY;
    NEXUS_VideoFrameRate frameRate;
    NEXUS_ColorPrimaries colorPrimaries;
    NEXUS_TransferCharacteristics transferCharacteristics;
    NEXUS_TransferCharacteristics preferredTransferCharacteristics;
    NEXUS_MatrixCoefficients matrixCoefficients;
    _Bool frameProgressive;
    _Bool streamProgressive;
    int32_t horizontalPanScan;
    int32_t verticalPanScan;
    uint32_t lowDelayFlag;
    uint32_t fixedFrameRateFlag;
    NEXUS_VideoEotf eotf;
    NEXUS_ContentLightLevel contentLightLevel;
    NEXUS_MasteringDisplayColorVolume masteringDisplayColorVolume;
    unsigned colorDepth;
} NEXUS_VideoDecoderStreamInformation;
typedef enum NEXUS_VideoDecoder3DTVFormat
{
    NEXUS_VideoDecoder3DTVFormat_eNone,
    NEXUS_VideoDecoder3DTVFormat_eSideBySideHalf,
    NEXUS_VideoDecoder3DTVFormat_eTopAndBottomHalf,
    NEXUS_VideoDecoder3DTVFormat_eFramePacking,
    NEXUS_VideoDecoder3DTVFormat_eMax
} NEXUS_VideoDecoder3DTVFormat;
typedef struct NEXUS_VideoDecoder3DTVStatus
{
    NEXUS_VideoDecoder3DTVFormat format;
    NEXUS_VideoCodec codec;
    union {
        struct {
            _Bool valid;
            struct {
                uint32_t flags;
                uint32_t framePackingArrangementId;
                uint32_t framePackingArrangementType;
                uint32_t contentInterpretationType;
                uint32_t frame0GridPositionX;
                uint32_t frame0GridPositionY;
                uint32_t frame1GridPositionX;
                uint32_t frame1GridPositionY;
                uint32_t framePackingArrangementReservedByte;
                uint32_t framePackingArrangementRepetitionPeriod;
            } data;
        } avc;
        struct {
            _Bool valid;
            struct {
                uint16_t stereoVideoFormatSignalingType;
            } jp3d;
        } mpeg2;
    } codecData;
} NEXUS_VideoDecoder3DTVStatus;
typedef struct NEXUS_VideoDecoderPrimerSettings
{
    unsigned ptsOffset;
    unsigned pastTolerance;
    unsigned futureTolerance;
    _Bool ptsStcDiffCorrectionEnabled;
} NEXUS_VideoDecoderPrimerSettings;
typedef enum NEXUS_UserDataFormat
{
    NEXUS_UserDataFormat_eAny = 0,
    NEXUS_UserDataFormat_eAtsc53,
    NEXUS_UserDataFormat_eScte20,
    NEXUS_UserDataFormat_eScte21,
    NEXUS_UserDataFormat_eAtsc72,
    NEXUS_UserDataFormat_eMax
} NEXUS_UserDataFormat;
typedef struct NEXUS_VideoDecoderMemory
{
    _Bool used;
    _Bool supportedCodecs[NEXUS_VideoCodec_eMax];
    NEXUS_VideoFormat maxFormat;
    unsigned colorDepth;
    struct {
        unsigned maxNumber;
        unsigned maxWidth, maxHeight;
        unsigned colorDepth;
    } mosaic;
    _Bool avc51Supported;
    _Bool dynamicPictureBuffers;
    NEXUS_SecureVideo secure;
} NEXUS_VideoDecoderMemory;
typedef struct NEXUS_VideoDecoderCrc
{
    struct {
        uint32_t luma, cb, cr;
    } top, bottom;
} NEXUS_VideoDecoderCrc;
typedef struct NEXUS_VideoDecoderFifoStatus
{
    struct {
        uint32_t mostRecent;
        uint32_t leastRecent;
        _Bool valid;
    } pts;
    unsigned bufferLatency;
} NEXUS_VideoDecoderFifoStatus;
typedef struct NEXUS_VideoDecoderModuleSettings
{
    unsigned avdHeapIndex[3];
    unsigned secondaryPictureHeapIndex[3];
    struct {
        unsigned avdHeapIndex[3];
        unsigned secondaryPictureHeapIndex[3];
    } secure;
    unsigned hostAccessibleHeapIndex;
    unsigned mfdMapping[6];
    unsigned avdMapping[6];
    _Bool avdEnabled[3];
    NEXUS_VideoDecoderMemory memory[6];
    NEXUS_VideoDecoderMemory stillMemory[3];
    struct {
        struct {
            unsigned heapIndex;
        } sid, dsp;
    } videoDecoderExtension;
    _Bool supportedCodecs[NEXUS_VideoCodec_eMax];
    NEXUS_VideoFormat maxDecodeFormat;
    NEXUS_VideoFormat maxStillDecodeFormat;
    int numDecodes;
    int numStillDecodes;
    int numMosaicDecodes;
    struct {
        unsigned general;
        unsigned secure;
        unsigned picture;
        unsigned secondaryPicture;
    } heapSize[3];
    _Bool watchdogEnabled;
    _Bool deferInit;
    unsigned debugLogBufferSize;
} NEXUS_VideoDecoderModuleSettings;
typedef enum NEXUS_PicturePolarity
{
    NEXUS_PicturePolarity_eTopField,
    NEXUS_PicturePolarity_eBottomField,
    NEXUS_PicturePolarity_eFrame,
    NEXUS_PicturePolarity_eMax
} NEXUS_PicturePolarity;
typedef enum NEXUS_UserDataType
{
    NEXUS_UserDataType_eSeq=1,
    NEXUS_UserDataType_eGop,
    NEXUS_UserDataType_ePicture,
    NEXUS_UserDataType_eSei,
    NEXUS_UserDataType_eEntryPoint,
    NEXUS_UserDataType_eField,
    NEXUS_UserDataType_eFrame,
    NEXUS_UserDataType_eSlice,
    NEXUS_UserDataType_eMax
} NEXUS_UserDataType;
typedef struct NEXUS_UserDataHeader
{
    unsigned blockSize;
    NEXUS_PicturePolarity polarity;
    NEXUS_UserDataType type;
    _Bool topFieldFirst;
    _Bool repeatFirstField;
    NEXUS_PictureCoding pictureCoding;
    _Bool ptsValid;
    uint32_t pts;
    uint32_t pictureCodingExtension[2];
    unsigned payloadSize;
} NEXUS_UserDataHeader;
NEXUS_Error NEXUS_VideoDecoder_GetUserDataBuffer(
    NEXUS_VideoDecoderHandle handle,
    void **pBuffer,
    unsigned *pSize
    );
void NEXUS_VideoDecoder_UserDataReadComplete(
    NEXUS_VideoDecoderHandle handle,
    unsigned size
    );
void NEXUS_VideoDecoder_FlushUserData(
    NEXUS_VideoDecoderHandle videoDecoder
    );
typedef struct NEXUS_VideoDecoderUserDataStatus
{
    unsigned formatParsed[NEXUS_UserDataFormat_eMax];
    NEXUS_UserDataFormat lastFormatParsed;
    uint32_t afdValue;
} NEXUS_VideoDecoderUserDataStatus;
NEXUS_Error NEXUS_VideoDecoder_GetUserDataStatus(
    NEXUS_VideoDecoderHandle handle,
    NEXUS_VideoDecoderUserDataStatus *pStatus
    );
NEXUS_Error NEXUS_VideoDecoder_SetUserDataFormatFilter(
    NEXUS_VideoDecoderHandle handle,
    NEXUS_UserDataFormat format
    );
typedef struct NEXUS_StripedSurface *NEXUS_StripedSurfaceHandle;
void NEXUS_StripedSurface_GetDefaultCreateSettings(
    NEXUS_StripedSurfaceCreateSettings *pSettings
    );
NEXUS_StripedSurfaceHandle NEXUS_StripedSurface_Create(
    const NEXUS_StripedSurfaceCreateSettings *pSettings
    );
void NEXUS_StripedSurface_Destroy(
    NEXUS_StripedSurfaceHandle stripedSurface
    );
void NEXUS_StripedSurface_GetCreateSettings(
    NEXUS_StripedSurfaceHandle stripedSurface,
    NEXUS_StripedSurfaceCreateSettings *pSettings
    );
typedef struct NEXUS_StripedSurfaceStatus
{
    unsigned width;
    unsigned height;
} NEXUS_StripedSurfaceStatus;
NEXUS_Error NEXUS_StripedSurface_GetStatus(
    NEXUS_StripedSurfaceHandle stripedSurface,
    NEXUS_StripedSurfaceStatus *pStatus
    );
typedef struct NEXUS_Rave *NEXUS_RaveHandle;
typedef struct NEXUS_RaveOpenSetting
{
    unsigned placeHolder;
} NEXUS_RaveOpenSetting;
void NEXUS_Rave_GetDefaultOpenSetting(
    NEXUS_RaveOpenSetting *pSetting
    );
NEXUS_RaveHandle NEXUS_Rave_Open(
    const NEXUS_RaveOpenSetting *pOpenSetting
    );
void NEXUS_Rave_Close(
    NEXUS_RaveHandle handle
    );
typedef struct NEXUS_VideoDecoderOpenSettings
{
    unsigned fifoSize;
    unsigned userDataBufferSize;
    NEXUS_HeapHandle pictureHeap;
    NEXUS_HeapHandle secondaryPictureHeap;
    _Bool secureVideo;
    _Bool avc51Enabled;
    _Bool svc3dSupported;
    _Bool excessDirModeEnabled;
    unsigned itbFifoSize;
    _Bool enhancementPidChannelSupported;
    NEXUS_HeapHandle cdbHeap;
} NEXUS_VideoDecoderOpenSettings;
void NEXUS_VideoDecoder_GetDefaultOpenSettings(
    NEXUS_VideoDecoderOpenSettings *pOpenSettings
    );
NEXUS_VideoDecoderHandle NEXUS_VideoDecoder_Open(
    unsigned index,
    const NEXUS_VideoDecoderOpenSettings *pOpenSettings
    );
void NEXUS_VideoDecoder_Close(
    NEXUS_VideoDecoderHandle handle
    );
void NEXUS_VideoDecoder_GetOpenSettings(
    NEXUS_VideoDecoderHandle handle,
    NEXUS_VideoDecoderOpenSettings *pOpenSettings
    );
void NEXUS_VideoDecoder_GetSettings(
    NEXUS_VideoDecoderHandle handle,
    NEXUS_VideoDecoderSettings *pSettings
    );
NEXUS_Error NEXUS_VideoDecoder_SetSettings(
    NEXUS_VideoDecoderHandle handle,
    const NEXUS_VideoDecoderSettings *pSettings
    );
void NEXUS_VideoDecoder_GetDefaultStartSettings(
    NEXUS_VideoDecoderStartSettings *pSettings
    );
NEXUS_Error NEXUS_VideoDecoder_Start(
    NEXUS_VideoDecoderHandle handle,
    const NEXUS_VideoDecoderStartSettings *pSettings
    );
void NEXUS_VideoDecoder_Stop(
    NEXUS_VideoDecoderHandle handle
    );
void NEXUS_VideoDecoder_Flush(
    NEXUS_VideoDecoderHandle handle
    );
NEXUS_Error NEXUS_VideoDecoder_GetStatus(
    NEXUS_VideoDecoderHandle handle,
    NEXUS_VideoDecoderStatus *pStatus
    );
NEXUS_VideoInputHandle NEXUS_VideoDecoder_GetConnector(
    NEXUS_VideoDecoderHandle handle
    );
NEXUS_Error NEXUS_VideoDecoder_GetStreamInformation(
    NEXUS_VideoDecoderHandle handle,
    NEXUS_VideoDecoderStreamInformation *pStreamInformation
    );
NEXUS_Error NEXUS_VideoDecoder_SetStartPts(
    NEXUS_VideoDecoderHandle handle,
    uint32_t pts
    );
void NEXUS_VideoDecoder_IsCodecSupported(
    NEXUS_VideoDecoderHandle videoDecoder,
    NEXUS_VideoCodec codec,
    _Bool *pSupported
    );
NEXUS_Error NEXUS_VideoDecoder_SetPowerState(
    NEXUS_VideoDecoderHandle handle,
    _Bool powerUp
    );
NEXUS_RaveHandle NEXUS_VideoDecoder_DetachRaveContext(
    NEXUS_VideoDecoderHandle handle
    );
NEXUS_RaveHandle NEXUS_VideoDecoder_DetachEnhancementRaveContext(
    NEXUS_VideoDecoderHandle handle
    );
NEXUS_Error NEXUS_VideoDecoder_AttachRaveContext(
    NEXUS_VideoDecoderHandle handle,
    NEXUS_RaveHandle rave
    );
NEXUS_Error NEXUS_VideoDecoder_GetDecodedFrames(
    NEXUS_VideoDecoderHandle handle,
    NEXUS_VideoDecoderFrameStatus *pStatus,
    unsigned numEntries,
    unsigned *pNumEntriesReturned
    );
void NEXUS_VideoDecoder_GetDefaultReturnFrameSettings(
    NEXUS_VideoDecoderReturnFrameSettings *pSettings
    );
NEXUS_Error NEXUS_VideoDecoder_ReturnDecodedFrames(
    NEXUS_VideoDecoderHandle handle,
    const NEXUS_VideoDecoderReturnFrameSettings *pSettings,
    unsigned numFrames
    );
typedef struct NEXUS_VideoDecoderCapabilities
{
    unsigned numVideoDecoders;
    NEXUS_VideoDecoderMemory memory[6];
    NEXUS_VideoDecoderMemory stillMemory[3];
    struct {
        unsigned avdIndex;
        struct {
            unsigned colorDepth;
            unsigned index;
        } feeder;
    } videoDecoder[6];
    unsigned numStcs;
    struct {
        unsigned total;
        unsigned baseIndex;
        _Bool useForVp6;
    } dspVideoDecoder;
    struct {
        unsigned total;
        unsigned baseIndex;
        _Bool useForMotionJpeg;
    } sidVideoDecoder;
    struct {
        unsigned total;
        unsigned baseIndex;
        _Bool useForVp9;
    } softVideoDecoder;
} NEXUS_VideoDecoderCapabilities;
void NEXUS_GetVideoDecoderCapabilities(
    NEXUS_VideoDecoderCapabilities *pCapabilities
    );
typedef struct NEXUS_VideoDecoderMultiPassDqtData
{
    unsigned intraGopPictureIndex;
    unsigned openGopPictures;
} NEXUS_VideoDecoderMultiPassDqtData;
NEXUS_Error NEXUS_VideoDecoder_ReadMultiPassDqtData(
    NEXUS_VideoDecoderHandle handle,
    NEXUS_VideoDecoderMultiPassDqtData *pData
    );
typedef enum NEXUS_AudioDecoderType
{
    NEXUS_AudioDecoderType_eDecode,
    NEXUS_AudioDecoderType_eAudioDescriptor,
    NEXUS_AudioDecoderType_ePassthrough,
    NEXUS_AudioDecoderType_eDecodeToMemory,
    NEXUS_AudioDecoderType_eMax
} NEXUS_AudioDecoderType;
typedef struct NEXUS_AudioDecoderOpenSettings
{
    NEXUS_AudioDecoderType type;
    unsigned fifoSize;
    unsigned ancillaryDataFifoSize;
    _Bool independentDelay;
    NEXUS_AudioMultichannelFormat multichannelFormat;
    unsigned dspIndex;
    NEXUS_HeapHandle cdbHeap;
    _Bool karaokeSupported;
} NEXUS_AudioDecoderOpenSettings;
void NEXUS_AudioDecoder_GetDefaultOpenSettings(
    NEXUS_AudioDecoderOpenSettings *pSettings
    );
NEXUS_AudioDecoderHandle NEXUS_AudioDecoder_Open(
    unsigned index,
    const NEXUS_AudioDecoderOpenSettings *pSettings
    );
void NEXUS_AudioDecoder_Close(
    NEXUS_AudioDecoderHandle handle
    );
void NEXUS_AudioDecoder_GetSettings(
    NEXUS_AudioDecoderHandle handle,
    NEXUS_AudioDecoderSettings *pSettings
    );
NEXUS_Error NEXUS_AudioDecoder_SetSettings(
    NEXUS_AudioDecoderHandle handle,
    const NEXUS_AudioDecoderSettings *pSettings
    );
void NEXUS_AudioDecoder_GetDefaultStartSettings(
    NEXUS_AudioDecoderStartSettings *pSettings
    );
NEXUS_Error NEXUS_AudioDecoder_Start(
    NEXUS_AudioDecoderHandle handle,
    const NEXUS_AudioDecoderStartSettings *pSettings
    );
void NEXUS_AudioDecoder_Stop(
    NEXUS_AudioDecoderHandle handle
    );
NEXUS_Error NEXUS_AudioDecoder_Suspend(
    NEXUS_AudioDecoderHandle handle
    );
NEXUS_Error NEXUS_AudioDecoder_Resume(
    NEXUS_AudioDecoderHandle handle
    );
NEXUS_Error NEXUS_AudioDecoder_Flush(
    NEXUS_AudioDecoderHandle handle
    );
void NEXUS_AudioDecoder_GetCodecSettings(
    NEXUS_AudioDecoderHandle handle,
    NEXUS_AudioCodec codec,
    NEXUS_AudioDecoderCodecSettings *pSettings
    );
NEXUS_Error NEXUS_AudioDecoder_SetCodecSettings(
    NEXUS_AudioDecoderHandle handle,
    const NEXUS_AudioDecoderCodecSettings *pSettings
    );
NEXUS_Error NEXUS_AudioDecoder_GetStatus(
    NEXUS_AudioDecoderHandle handle,
    NEXUS_AudioDecoderStatus *pStatus
    );
NEXUS_Error NEXUS_AudioDecoder_GetPresentationStatus(
    NEXUS_AudioDecoderHandle handle,
    unsigned presentationIndex,
    NEXUS_AudioDecoderPresentationStatus *pStatus
    );
NEXUS_Error NEXUS_AudioDecoder_GetRawChannelStatus(
    NEXUS_AudioDecoderHandle handle,
    NEXUS_AudioRawChannelStatus *pStatus
    );
NEXUS_AudioInputHandle NEXUS_AudioDecoder_GetConnector(
    NEXUS_AudioDecoderHandle handle,
    NEXUS_AudioConnectorType type
    );
void NEXUS_AudioDecoder_IsCodecSupported(
    NEXUS_AudioDecoderHandle handle,
    NEXUS_AudioCodec codec,
    _Bool *pSupported
    );
void NEXUS_AudioDecoder_IsPassthroughCodecSupported(
    NEXUS_AudioDecoderHandle handle,
    NEXUS_AudioCodec codec,
    _Bool *pSupported
    );
NEXUS_Error NEXUS_AudioDecoder_GetAncillaryDataBuffer(
    NEXUS_AudioDecoderHandle handle,
    void **pBuffer,
    size_t *pSize
    );
void NEXUS_AudioDecoder_AncillaryDataReadComplete(
    NEXUS_AudioDecoderHandle handle,
    size_t size
    );
void NEXUS_AudioDecoder_FlushAncillaryData(
    NEXUS_AudioDecoderHandle handle
    );
typedef enum NEXUS_TimebaseSourceType
{
    NEXUS_TimebaseSourceType_ePcr,
    NEXUS_TimebaseSourceType_eFreeRun,
    NEXUS_TimebaseSourceType_eAnalog,
    NEXUS_TimebaseSourceType_eHdDviIn,
    NEXUS_TimebaseSourceType_eCcir656In,
    NEXUS_TimebaseSourceType_eI2sIn,
    NEXUS_TimebaseSourceType_eSpdifIn,
    NEXUS_TimebaseSourceType_eMax
} NEXUS_TimebaseSourceType;
typedef enum NEXUS_TimebaseTrackRange
{
    NEXUS_TimebaseTrackRange_e8ppm,
    NEXUS_TimebaseTrackRange_e15ppm,
    NEXUS_TimebaseTrackRange_e30ppm,
    NEXUS_TimebaseTrackRange_e61ppm,
    NEXUS_TimebaseTrackRange_e122ppm,
    NEXUS_TimebaseTrackRange_e244ppm,
    NEXUS_TimebaseTrackRange_eMax
} NEXUS_TimebaseTrackRange;
typedef struct NEXUS_TimebaseFreeRunSourceSettings
{
    unsigned centerFrequency;
    NEXUS_TimebaseTrackRange trackRange;
    uint32_t prescale;
    uint32_t inc;
    uint8_t loopDirectPathGain;
    uint8_t loopGain;
    uint8_t loopIntegratorLeak;
} NEXUS_TimebaseFreeRunSourceSettings;
typedef struct NEXUS_TimebasePcrSourceSettings
{
    NEXUS_PidChannelHandle pidChannel;
    unsigned maxPcrError;
    NEXUS_TimebaseTrackRange trackRange;
    NEXUS_TristateEnable jitterCorrection;
} NEXUS_TimebasePcrSourceSettings;
typedef struct NEXUS_TimebaseVdecSourceSettings
{
    unsigned index;
    NEXUS_VideoFormat format;
    NEXUS_VideoFrameRate frameRate;
    NEXUS_TimebaseTrackRange trackRange;
} NEXUS_TimebaseVdecSourceSettings;
typedef struct NEXUS_TimebaseHddviSourceSettings
{
    unsigned index;
    unsigned vertSyncClock;
    NEXUS_VideoFormat format;
    NEXUS_VideoFrameRate frameRate;
    NEXUS_TimebaseTrackRange trackRange;
} NEXUS_TimebaseHddviSourceSettings;
typedef struct NEXUS_TimebaseCcir656SourceSettings
{
    unsigned index;
    NEXUS_VideoFormat format;
    NEXUS_TimebaseTrackRange trackRange;
} NEXUS_TimebaseCcir656SourceSettings;
typedef struct NEXUS_TimebaseI2sSourceSettings
{
    unsigned index;
    unsigned sampleRate;
    NEXUS_TimebaseTrackRange trackRange;
} NEXUS_TimebaseI2sSourceSettings;
typedef struct NEXUS_TimebaseSettings
{
    NEXUS_TimebaseSourceType sourceType;
    struct {
        NEXUS_TimebaseFreeRunSourceSettings freeRun;
        NEXUS_TimebasePcrSourceSettings pcr;
        NEXUS_TimebaseVdecSourceSettings vdec;
        NEXUS_TimebaseHddviSourceSettings hdDvi;
        NEXUS_TimebaseCcir656SourceSettings ccir656;
        NEXUS_TimebaseI2sSourceSettings i2s;
    } sourceSettings;
    NEXUS_CallbackDesc pcrCallback;
    NEXUS_CallbackDesc pcrErrorCallback;
    _Bool freeze;
} NEXUS_TimebaseSettings;
NEXUS_Error NEXUS_Timebase_SetSettings(
    NEXUS_Timebase timebase,
    const NEXUS_TimebaseSettings *pSettings
    );
void NEXUS_Timebase_GetSettings(
    NEXUS_Timebase timebase,
    NEXUS_TimebaseSettings *pSettings
    );
NEXUS_Timebase NEXUS_Timebase_Open(
    unsigned index
    );
void NEXUS_Timebase_Close(
    NEXUS_Timebase timebase
    );
void NEXUS_Timebase_GetDefaultSettings(
    NEXUS_TimebaseSettings *pSettings
    );
typedef struct NEXUS_TimebaseStatus
{
    unsigned timebase;
    uint32_t lastValue;
    uint32_t lastValueLo;
    int32_t lastError;
    unsigned pcrCount;
    unsigned pcrErrors;
    _Bool pcrValid;
    NEXUS_TimebaseSourceType sourceType;
} NEXUS_TimebaseStatus;
NEXUS_Error NEXUS_Timebase_GetStatus(
    NEXUS_Timebase timebase,
    NEXUS_TimebaseStatus *pStatus
    );
NEXUS_Error NEXUS_Timebase_ResetStatus(
    NEXUS_Timebase timebase
    );
NEXUS_Error NEXUS_Timebase_SetHdDviFrameRate(
    NEXUS_Timebase timebase,
    NEXUS_VideoFrameRate frameRate
    );
NEXUS_Error NEXUS_Timebase_GetIndex(
    NEXUS_Timebase timebase,
    unsigned *pIndex
    );
typedef struct NEXUS_Astm * NEXUS_AstmHandle;
typedef enum NEXUS_AstmPresentationRateControl
{
    NEXUS_AstmPresentationRateControl_eAdaptive,
    NEXUS_AstmPresentationRateControl_eTimeStamp,
    NEXUS_AstmPresentationRateControl_eOutputClock,
    NEXUS_AstmPresentationRateControl_eMax
} NEXUS_AstmPresentationRateControl;
typedef enum NEXUS_AstmStcSource
{
    NEXUS_AstmStcSource_eAdaptive,
    NEXUS_AstmStcSource_eClockReference,
    NEXUS_AstmStcSource_ePts,
    NEXUS_AstmStcSource_eMax
} NEXUS_AstmStcSource;
typedef enum NEXUS_AstmClockCoupling
{
    NEXUS_AstmClockCoupling_eAdaptive,
    NEXUS_AstmClockCoupling_eInputClock,
    NEXUS_AstmClockCoupling_eInternalClock,
    NEXUS_AstmClockCoupling_eMax
} NEXUS_AstmClockCoupling;
typedef enum NEXUS_AstmClockRate
{
    NEXUS_AstmClockRate_e45Khz = 45000,
    NEXUS_AstmClockRate_e27Mhz = 27000000,
    NEXUS_AstmClockRate_eMax
} NEXUS_AstmClockRate;
typedef struct NEXUS_AstmPresenterConfig
{
    unsigned minimumTimeBetweenEvents;
    unsigned passEventCountThreshold;
    unsigned failEventCountThreshold;
    _Bool tsmThresholdAdjustment;
    _Bool manageRateControl;
    unsigned tsmRecoveryAcquisitionPeriod;
    unsigned tsmRecoveryTrackingTimeout;
    unsigned ptsStcDiffAdjustmentThreshold;
    unsigned maxAllowableFirstPtsStcDiff;
} NEXUS_AstmPresenterConfig;
typedef struct NEXUS_AstmSettings
{
    _Bool enabled;
    _Bool enableAutomaticLifecycleControl;
    NEXUS_AstmPresentationRateControl presentationRateControl;
    NEXUS_AstmStcSource stcSource;
    NEXUS_AstmClockCoupling clockCoupling;
    NEXUS_StcChannelHandle stcChannel;
    NEXUS_VideoDecoderHandle videoDecoder;
    NEXUS_AudioDecoderHandle audioDecoder[2];
    NEXUS_AnyObject stcMaster;
    unsigned int syncLimit;
    NEXUS_AstmPresenterConfig videoPresenterConfig;
    NEXUS_AstmPresenterConfig audioPresenterConfig[2];
    struct
    {
        unsigned minimumTimeBetweenEvents;
        unsigned deviationThreshold;
        unsigned deviantCountThreshold;
        unsigned idealCountThreshold;
        unsigned initialAcquisitionTime;
        unsigned processingFrequency;
        unsigned idealProcessingFrequency;
        unsigned settlingTime;
    } clockCouplingConfig;
    struct
    {
        unsigned initialAcquisitionTime;
        unsigned processingFrequency;
        unsigned tsmDisabledWatchdogTimeout;
        unsigned settlingTime;
        NEXUS_AstmPresentationRateControl preferredPresentationRateControl;
    } presentationConfig;
} NEXUS_AstmSettings;
void NEXUS_Astm_GetDefaultSettings(
    NEXUS_AstmSettings * pSettings
    );
NEXUS_AstmHandle NEXUS_Astm_Create(
    const NEXUS_AstmSettings * pSettings
    );
void NEXUS_Astm_Destroy(
    NEXUS_AstmHandle handle
    );
void NEXUS_Astm_GetSettings(
    NEXUS_AstmHandle handle,
    NEXUS_AstmSettings * pSettings
    );
NEXUS_Error NEXUS_Astm_SetSettings(
    NEXUS_AstmHandle handle,
    const NEXUS_AstmSettings * pSettings
    );
NEXUS_Error NEXUS_Astm_Start(
    NEXUS_AstmHandle astm
    );
void NEXUS_Astm_Stop(
    NEXUS_AstmHandle astm
    );
typedef struct NEXUS_AstmModuleSettings
{
 struct
 {
  NEXUS_ModuleHandle audio;
  NEXUS_ModuleHandle videoDecoder;
  NEXUS_ModuleHandle transport;
 } modules;
} NEXUS_AstmModuleSettings;
void NEXUS_AstmModule_GetDefaultSettings(
 NEXUS_AstmModuleSettings *pSettings
 );
NEXUS_ModuleHandle NEXUS_AstmModule_Init(
 const NEXUS_AstmModuleSettings *pSettings
 );
void NEXUS_AstmModule_Uninit(void);
typedef struct NEXUS_AudioOutputSettings
{
    NEXUS_Timebase timebase;
    NEXUS_AudioChannelMode channelMode;
    NEXUS_AudioVolumeType volumeType;
    int32_t leftVolume;
    int32_t rightVolume;
    _Bool muted;
    unsigned additionalDelay;
    NEXUS_AudioOutputPll pll;
    _Bool autoConfigureVcxo;
    NEXUS_AudioOutputNco nco;
    unsigned defaultSampleRate;
} NEXUS_AudioOutputSettings;
void NEXUS_AudioOutput_GetSettings(
    NEXUS_AudioOutputHandle output,
    NEXUS_AudioOutputSettings *pSettings
    );
NEXUS_Error NEXUS_AudioOutput_SetSettings(
    NEXUS_AudioOutputHandle output,
    const NEXUS_AudioOutputSettings *pSettings
    );
typedef struct NEXUS_AudioOutputStatus
{
    unsigned delay;
} NEXUS_AudioOutputStatus;
NEXUS_Error NEXUS_AudioOutput_GetStatus(
    NEXUS_AudioOutputHandle output,
    NEXUS_AudioOutputStatus *pStatus
    );
typedef struct NEXUS_AudioOutputEnabledOutputs
{
    unsigned audioDummy[8];
    unsigned spdif[2];
    unsigned dac[3];
    unsigned i2s[2];
    unsigned i2sMulti[2];
    unsigned hdmi[2];
    unsigned audioCapture[4];
} NEXUS_AudioOutputEnabledOutputs;
typedef struct NEXUS_AudioOutputClockSource
{
    NEXUS_AudioOutputPll pll;
    NEXUS_AudioOutputNco nco;
} NEXUS_AudioOutputClockSource;
typedef struct NEXUS_AudioOutputClockConfig
{
    NEXUS_AudioOutputClockSource audioDummy[8];
    NEXUS_AudioOutputClockSource spdif[2];
    NEXUS_AudioOutputClockSource i2s[2];
    NEXUS_AudioOutputClockSource i2sMulti[2];
    NEXUS_AudioOutputClockSource hdmi[2];
    NEXUS_AudioOutputClockSource audioCapture[4];
} NEXUS_AudioOutputClockConfig;
void NEXUS_AudioOutput_GetDefaultEnabledOutputs(
    NEXUS_AudioOutputEnabledOutputs *pOutputs);
NEXUS_Error NEXUS_AudioOutput_CreateClockConfig(
    const NEXUS_AudioOutputEnabledOutputs *outputs,
    NEXUS_AudioOutputClockConfig *config);
NEXUS_Error NEXUS_AudioOutput_AddInput(
    NEXUS_AudioOutputHandle output,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_AudioOutput_RemoveInput(
    NEXUS_AudioOutputHandle output,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_AudioOutput_RemoveAllInputs(
    NEXUS_AudioOutputHandle output
    );
void NEXUS_AudioOutput_Shutdown(
    NEXUS_AudioOutputHandle output
    );
typedef enum NEXUS_AudioDspDebugType
{
    NEXUS_AudioDspDebugType_eDramMessage,
    NEXUS_AudioDspDebugType_eUartMessage,
    NEXUS_AudioDspDebugType_eCoreDump,
    NEXUS_AudioDspDebugType_eTargetPrint,
    NEXUS_AudioDspDebugType_eMax
} NEXUS_AudioDspDebugType;
typedef struct NEXUS_AudioDspDebugSettings
{
    struct
    {
        _Bool enabled;
        unsigned bufferSize;
    } typeSettings[NEXUS_AudioDspDebugType_eMax];
} NEXUS_AudioDspDebugSettings;
NEXUS_Error NEXUS_AudioDsp_GetDebugBuffer(
    unsigned dspIndex,
    NEXUS_AudioDspDebugType debugType,
    const void **pBuffer,
    size_t *pBufferSize
    );
NEXUS_Error NEXUS_AudioDsp_DebugReadComplete(
    unsigned dspIndex,
    NEXUS_AudioDspDebugType debugType,
    size_t bytesRead
    );
typedef enum NEXUS_AudioDspAlgorithmType
{
    NEXUS_AudioDspAlgorithmType_eAudioDecode,
    NEXUS_AudioDspAlgorithmType_eAudioPassthrough,
    NEXUS_AudioDspAlgorithmType_eAudioEncode,
    NEXUS_AudioDspAlgorithmType_eAudioMixer,
    NEXUS_AudioDspAlgorithmType_eAudioEchoCanceller,
    NEXUS_AudioDspAlgorithmType_eAudioProcessing,
    NEXUS_AudioDspAlgorithmType_eVideoDecode,
    NEXUS_AudioDspAlgorithmType_eVideoEncode,
    NEXUS_AudioDspAlgorithmType_eMax
} NEXUS_AudioDspAlgorithmType;
typedef struct NEXUS_AudioDspAlgorithmSettings
{
    struct
    {
        unsigned count;
    } typeSettings[NEXUS_AudioDspAlgorithmType_eMax];
} NEXUS_AudioDspAlgorithmSettings;
typedef struct NEXUS_AudioRampStepSettings
{
    unsigned int mixerRampStep;
    unsigned int srcRampStep;
} NEXUS_AudioRampStepSettings;
void NEXUS_AudioModule_GetRampStepSettings(
    NEXUS_AudioRampStepSettings *pRampStepSettings
    );
NEXUS_Error NEXUS_AudioModule_SetRampStepSettings(
    const NEXUS_AudioRampStepSettings *pRampStepSettings
    );
typedef enum NEXUS_ExternalMclkRate
{
    NEXUS_ExternalMclkRate_e128Fs,
    NEXUS_ExternalMclkRate_e256Fs,
    NEXUS_ExternalMclkRate_e384Fs,
    NEXUS_ExternalMclkRate_e512Fs,
    NEXUS_ExternalMclkRate_eMax
} NEXUS_ExternalMclkRate;
NEXUS_Error NEXUS_AudioModule_EnableExternalMclk(
    unsigned mclkIndex,
    NEXUS_AudioOutputPll pll,
    NEXUS_ExternalMclkRate mclkRate
    );
 typedef enum NEXUS_AudioOutputPllMode
 {
     NEXUS_AudioOutputPllMode_eVcxo,
     NEXUS_AudioOutputPllMode_eCustom,
     NEXUS_AudioOutputPllMode_eMax
 } NEXUS_AudioOutputPllMode;
typedef struct NEXUS_AudioOutputPllSettings
{
    NEXUS_AudioOutputPllMode mode;
     struct
     {
         struct
         {
             NEXUS_Vcxo vcxo;
         } vcxo;
         struct
         {
             unsigned value[2];
         } custom;
    } modeSettings;
} NEXUS_AudioOutputPllSettings;
void NEXUS_AudioOutputPll_GetSettings(
    NEXUS_AudioOutputPll pll,
    NEXUS_AudioOutputPllSettings *pSettings
    );
NEXUS_Error NEXUS_AudioOutputPll_SetSettings(
    NEXUS_AudioOutputPll pll,
    const NEXUS_AudioOutputPllSettings *pSettings
    );
typedef struct NEXUS_AudioCapabilities
{
    struct
    {
        unsigned hdmi;
        unsigned i2s;
        unsigned spdif;
    } numInputs;
    struct
    {
        unsigned audioReturnChannel;
        unsigned capture;
        unsigned dac;
        unsigned dummy;
        unsigned hdmi;
        unsigned i2s;
        unsigned loopback;
        unsigned rfmod;
        unsigned spdif;
    } numOutputs;
    unsigned numDecoders;
    unsigned numPlaybacks;
    unsigned numInputCaptures;
    unsigned numVcxos;
    unsigned numPlls;
    unsigned numNcos;
    unsigned numStcs;
    unsigned numMixers;
    unsigned numDsps;
    unsigned numCrcs;
    struct
    {
        struct
        {
            _Bool decode;
            _Bool passthrough;
            _Bool encode;
        } codecs[NEXUS_AudioCodec_eMax];
        _Bool audysseyAbx;
        _Bool audysseyAdv;
        _Bool autoVolumeLevel;
        _Bool _3dSurround;
        _Bool decodeRateControl;
        _Bool dolbyDigitalReencode;
        _Bool dolbyVolume;
        _Bool dolbyVolume258;
        _Bool karaoke;
        struct
        {
            _Bool supported;
            _Bool algorithms[NEXUS_EchoCancellerAlgorithm_eMax];
        } echoCanceller;
        _Bool encoder;
        _Bool mixer;
        _Bool muxOutput;
        struct
        {
            _Bool supported;
            _Bool encodings[NEXUS_RfAudioEncoding_eMax];
        } rfEncoder;
        _Bool studioSound;
        _Bool truSurroundHd;
        _Bool truVolume;
        _Bool processing[NEXUS_AudioPostProcessing_eMax];
    } dsp;
    struct
    {
        _Bool supported;
    } equalizer;
} NEXUS_AudioCapabilities;
void NEXUS_GetAudioCapabilities(
    NEXUS_AudioCapabilities *pCaps
    );
typedef struct NEXUS_AudioFirmwareVersion
{
    unsigned major;
    unsigned minor;
    unsigned branch[2];
} NEXUS_AudioFirmwareVersion;
void NEXUS_GetAudioFirmwareVersion(
    NEXUS_AudioFirmwareVersion *pVersion
    );
typedef struct NEXUS_AudioBuffer
{
    void *pBuffer;
    void *pWrapBuffer;
} NEXUS_AudioBuffer;
typedef struct NEXUS_AudioBufferDescriptor
{
    _Bool interleaved;
    unsigned numBuffers;
    NEXUS_AudioBuffer left;
    NEXUS_AudioBuffer right;
    NEXUS_AudioBuffer leftSurround;
    NEXUS_AudioBuffer rightSurround;
    NEXUS_AudioBuffer center;
    NEXUS_AudioBuffer lfe;
    NEXUS_AudioBuffer leftRear;
    NEXUS_AudioBuffer rightRear;
    unsigned bufferSize;
    unsigned wrapBufferSize;
} NEXUS_AudioBufferDescriptor;
typedef struct NEXUS_AudioModuleUsageSettings
{
    unsigned maxIndependentDelay;
    unsigned maxDecoderOutputChannels;
    unsigned maxDecoderOutputSamplerate;
    NEXUS_AudioDolbyCodecVersion dolbyCodecVersion;
    _Bool decodeCodecEnabled [NEXUS_AudioCodec_eMax];
    _Bool encodeCodecEnabled [NEXUS_AudioCodec_eMax];
    _Bool postProcessingEnabled[NEXUS_AudioPostProcessing_eMax];
    unsigned numDecoders;
    unsigned numEncoders;
    unsigned numPassthroughDecoders;
    unsigned numHbrPassthroughDecoders;
    unsigned numDspMixers;
    unsigned numPostProcessing;
    unsigned numEchoCancellers;
} NEXUS_AudioModuleUsageSettings;
typedef struct NEXUS_AudioModuleSettings
{
    unsigned maxAudioDspTasks;
    unsigned maxIndependentDelay;
    unsigned maxPcmSampleRate;
    _Bool watchdogEnabled;
    _Bool independentDelay;
    _Bool routeInputsToDsp;
    unsigned numPcmBuffers;
    unsigned numCompressedBuffers;
    unsigned numCompressed4xBuffers;
    unsigned numCompressed16xBuffers;
    unsigned numRfEncodedPcmBuffers;
    NEXUS_AudioOutputPll defaultPll;
    unsigned heapIndex;
    unsigned firmwareHeapIndex;
    NEXUS_AudioDspDebugSettings dspDebugSettings;
    NEXUS_AudioDspAlgorithmSettings dspAlgorithmSettings;
    NEXUS_AudioLoudnessEquivalenceMode loudnessMode;
    _Bool allowSpdif4xCompressed;
    _Bool allowI2sCompressed;
} NEXUS_AudioModuleSettings;
typedef struct NEXUS_AudioCapture *NEXUS_AudioCaptureHandle;
typedef enum NEXUS_AudioCaptureFormat
{
    NEXUS_AudioCaptureFormat_e16BitStereo,
    NEXUS_AudioCaptureFormat_e24BitStereo,
    NEXUS_AudioCaptureFormat_e16BitMonoLeft,
    NEXUS_AudioCaptureFormat_e16BitMonoRight,
    NEXUS_AudioCaptureFormat_e16BitMono,
    NEXUS_AudioCaptureFormat_e24Bit5_1,
    NEXUS_AudioCaptureFormat_eCompressed,
    NEXUS_AudioCaptureFormat_eMax
} NEXUS_AudioCaptureFormat;
typedef struct NEXUS_AudioCaptureOpenSettings
{
    size_t fifoSize;
    NEXUS_AudioMultichannelFormat multichannelFormat;
    NEXUS_HeapHandle heap;
    NEXUS_AudioCaptureFormat format;
    size_t threshold;
} NEXUS_AudioCaptureOpenSettings;
void NEXUS_AudioCapture_GetDefaultOpenSettings(
    NEXUS_AudioCaptureOpenSettings *pSettings
    );
NEXUS_AudioCaptureHandle NEXUS_AudioCapture_Open(
    unsigned index,
    const NEXUS_AudioCaptureOpenSettings *pSettings
    );
void NEXUS_AudioCapture_Close(
    NEXUS_AudioCaptureHandle handle
    );
typedef struct NEXUS_AudioCaptureSettings
{
    NEXUS_AudioCaptureFormat format;
    size_t threshold;
} NEXUS_AudioCaptureSettings;
void NEXUS_AudioCapture_GetSettings(
    NEXUS_AudioCaptureHandle handle,
    NEXUS_AudioCaptureSettings *pSettings
    );
NEXUS_Error NEXUS_AudioCapture_SetSettings(
    NEXUS_AudioCaptureHandle handle,
    const NEXUS_AudioCaptureSettings *pSettings
    );
typedef struct NEXUS_AudioCaptureStartSettings
{
    NEXUS_CallbackDesc dataCallback;
    NEXUS_CallbackDesc sampleRateCallback;
} NEXUS_AudioCaptureStartSettings;
void NEXUS_AudioCapture_GetDefaultStartSettings(
    NEXUS_AudioCaptureStartSettings *pSettings
    );
NEXUS_Error NEXUS_AudioCapture_Start(
    NEXUS_AudioCaptureHandle handle,
    const NEXUS_AudioCaptureStartSettings *pSettings
    );
void NEXUS_AudioCapture_Stop(
    NEXUS_AudioCaptureHandle handle
    );
NEXUS_Error NEXUS_AudioCapture_GetBuffer(
    NEXUS_AudioCaptureHandle handle,
    void **ppBuffer,
    size_t *pSize
    );
NEXUS_Error NEXUS_AudioCapture_ReadComplete(
    NEXUS_AudioCaptureHandle handle,
    size_t amountWritten
    );
NEXUS_AudioOutputHandle NEXUS_AudioCapture_GetConnector(
    NEXUS_AudioCaptureHandle handle
    );
typedef struct NEXUS_AudioCaptureStatus
{
    _Bool started;
    unsigned sampleRate;
    NEXUS_EndianMode endian;
} NEXUS_AudioCaptureStatus;
NEXUS_Error NEXUS_AudioCapture_GetStatus(
    NEXUS_AudioCaptureHandle handle,
    NEXUS_AudioCaptureStatus *pStatus
    );
typedef struct NEXUS_AudioCrc* NEXUS_AudioCrcHandle;
typedef enum NEXUS_AudioCrcSourceType
{
    NEXUS_AudioCrcSourceType_ePlaybackBuffer,
    NEXUS_AudioCrcSourceType_eOutputPort,
    NEXUS_AudioCrcSourceType_eMax
} NEXUS_AudioCrcSourceType;
typedef enum NEXUS_AudioCrcMode
{
    NEXUS_AudioCrcMode_eFreeRun,
    NEXUS_AudioCrcMode_eSingle,
    NEXUS_AudioCrcMode_eMax
} NEXUS_AudioCrcMode;
typedef struct NEXUS_AudioCrcOpenSettings
{
    unsigned numChannelPairs;
    unsigned numEntries;
    unsigned samplingPeriod;
    unsigned dataWidth;
    NEXUS_AudioCrcMode captureMode;
    uint16_t initialValue;
} NEXUS_AudioCrcOpenSettings;
typedef struct NEXUS_AudioCrcInputSettings
{
    NEXUS_AudioCrcSourceType sourceType;
    NEXUS_AudioOutputHandle output;
    NEXUS_AudioInputHandle input;
} NEXUS_AudioCrcInputSettings;
void NEXUS_AudioCrc_GetDefaultOpenSettings(
    NEXUS_AudioCrcOpenSettings *pSettings
    );
NEXUS_AudioCrcHandle NEXUS_AudioCrc_Open(
    unsigned index,
    const NEXUS_AudioCrcOpenSettings *pSettings
    );
void NEXUS_AudioCrc_Close(
    NEXUS_AudioCrcHandle handle
    );
void NEXUS_AudioCrc_GetDefaultInputSettings(
    NEXUS_AudioCrcInputSettings *pSettings
    );
NEXUS_Error NEXUS_AudioCrc_SetInput(
    NEXUS_AudioCrcHandle handle,
    const NEXUS_AudioCrcInputSettings * pSettings
    );
void NEXUS_AudioCrc_ClearInput(
    NEXUS_AudioCrcHandle handle
    );
typedef struct NEXUS_AudioCrcEntry
{
    uint16_t seqNumber;
    uint16_t value;
} NEXUS_AudioCrcEntry;
typedef struct NEXUS_AudioCrcData
{
    NEXUS_AudioCrcEntry crc0;
    NEXUS_AudioCrcEntry crc1;
    NEXUS_AudioCrcEntry crc2;
    NEXUS_AudioCrcEntry crc3;
} NEXUS_AudioCrcData;
NEXUS_Error NEXUS_AudioCrc_GetCrcData(
    NEXUS_AudioCrcHandle handle,
    NEXUS_AudioCrcData *pData,
    unsigned numEntries,
    unsigned *pNumReturned
    );
typedef struct NEXUS_AudioDac *NEXUS_AudioDacHandle;
typedef enum NEXUS_AudioDacMuteType
{
    NEXUS_AudioDacMuteType_eConstantLow,
    NEXUS_AudioDacMuteType_eConstantHigh,
    NEXUS_AudioDacMuteType_eSquareWaveOpp,
    NEXUS_AudioDacMuteType_eSquareWaveSame,
    NEXUS_AudioDacMuteType_eAaaa,
    NEXUS_AudioDacMuteType_e5555,
    NEXUS_AudioDacMuteType_eCustomValue,
    NEXUS_AudioDacMuteType_eDrive0,
    NEXUS_AudioDacMuteType_eDriveNegative1,
    NEXUS_AudioDacMuteType_eMax
} NEXUS_AudioDacMuteType;
typedef struct NEXUS_AudioDacSettings
{
    NEXUS_AudioDacMuteType muteType;
    uint16_t muteValueLeft;
    uint16_t muteValueRight;
    struct
    {
        _Bool enabled;
        int32_t samples[64];
        _Bool zeroOnLeft;
        _Bool zeroOnRight;
        _Bool sharedSamples;
        unsigned numSamplesLeft;
        unsigned numSamplesRight;
        unsigned sampleRate;
    } testTone;
    int fineAdjustment;
    int32_t volume;
    uint32_t peakGain;
    uint32_t scale;
} NEXUS_AudioDacSettings;
void NEXUS_AudioDac_GetDefaultSettings(
    NEXUS_AudioDacSettings *pSettings
    );
NEXUS_AudioDacHandle NEXUS_AudioDac_Open(
    unsigned index,
    const NEXUS_AudioDacSettings *pSettings
    );
void NEXUS_AudioDac_Close(
    NEXUS_AudioDacHandle handle
    );
void NEXUS_AudioDac_GetSettings(
    NEXUS_AudioDacHandle handle,
    NEXUS_AudioDacSettings *pSettings
    );
NEXUS_Error NEXUS_AudioDac_SetSettings(
    NEXUS_AudioDacHandle handle,
    const NEXUS_AudioDacSettings *pSettings
    );
NEXUS_AudioOutputHandle NEXUS_AudioDac_GetConnector(
    NEXUS_AudioDacHandle handle
    );
void NEXUS_AudioDecoder_GetDecodeToMemorySettings(
    NEXUS_AudioDecoderHandle decoder,
    NEXUS_AudioDecoderDecodeToMemorySettings *pSettings
    );
NEXUS_Error NEXUS_AudioDecoder_SetDecodeToMemorySettings(
    NEXUS_AudioDecoderHandle decoder,
    const NEXUS_AudioDecoderDecodeToMemorySettings *pSettings
    );
NEXUS_Error NEXUS_AudioDecoder_GetDecodeToMemoryStatus(
    NEXUS_AudioDecoderHandle decoder,
    NEXUS_AudioDecoderDecodeToMemoryStatus *pStatus
    );
NEXUS_Error NEXUS_AudioDecoder_QueueBuffer(
    NEXUS_AudioDecoderHandle decoder,
    NEXUS_MemoryBlockHandle buffer,
    unsigned bufferOffset,
    size_t bufferLength
    );
NEXUS_Error NEXUS_AudioDecoder_GetDecodedFrames(
    NEXUS_AudioDecoderHandle decoder,
    NEXUS_MemoryBlockHandle *pMemoryBlocks,
    NEXUS_AudioDecoderFrameStatus *pFrameStatus,
    unsigned numEntries,
    unsigned *pNumEntriesReturned
    );
NEXUS_Error NEXUS_AudioDecoder_ConsumeDecodedFrames(
    NEXUS_AudioDecoderHandle decoder,
    size_t numBuffers
    );
typedef struct NEXUS_AudioDecoderExtendedStatus
{
    unsigned raveIndex;
}NEXUS_AudioDecoderExtendedStatus;
NEXUS_Error NEXUS_AudioDecoder_GetExtendedStatus(
    NEXUS_AudioDecoderHandle handle,
    NEXUS_AudioDecoderExtendedStatus *pStatus
    );
typedef struct NEXUS_AudioDecoderPrimer *NEXUS_AudioDecoderPrimerHandle;
NEXUS_AudioDecoderPrimerHandle NEXUS_AudioDecoderPrimer_Open(
    NEXUS_AudioDecoderHandle audioDecoder
    );
void NEXUS_AudioDecoderPrimer_Close(
    NEXUS_AudioDecoderPrimerHandle primer
    );
NEXUS_AudioDecoderPrimerHandle NEXUS_AudioDecoderPrimer_Create(
    const NEXUS_AudioDecoderOpenSettings *pSettings
    );
NEXUS_Error NEXUS_AudioDecoderPrimer_Start(
    NEXUS_AudioDecoderPrimerHandle primer,
    const NEXUS_AudioDecoderStartSettings *pStartSettings
    );
void NEXUS_AudioDecoderPrimer_Stop(
    NEXUS_AudioDecoderPrimerHandle primer
    );
void NEXUS_AudioDecoderPrimer_Flush(
    NEXUS_AudioDecoderPrimerHandle primer
    );
NEXUS_Error NEXUS_AudioDecoderPrimer_StopPrimerAndStartDecode(
    NEXUS_AudioDecoderPrimerHandle primer,
    NEXUS_AudioDecoderHandle audioDecoder
    );
NEXUS_Error NEXUS_AudioDecoderPrimer_StopDecodeAndStartPrimer(
    NEXUS_AudioDecoderPrimerHandle primer,
    NEXUS_AudioDecoderHandle audioDecoder
    );
typedef struct NEXUS_AudioDecoderPrimerSettings
{
    unsigned tbd;
} NEXUS_AudioDecoderPrimerSettings;
void NEXUS_AudioDecoder_GetPrimerSettings(
    NEXUS_AudioDecoderPrimerHandle primer,
    NEXUS_AudioDecoderPrimerSettings *pSettings
    );
NEXUS_Error NEXUS_AudioDecoder_SetPrimerSettings(
    NEXUS_AudioDecoderPrimerHandle primer,
    const NEXUS_AudioDecoderPrimerSettings *pSettings
    );
void NEXUS_AudioDecoder_GetTrickState(
    NEXUS_AudioDecoderHandle decoder,
    NEXUS_AudioDecoderTrickState *pState
    );
NEXUS_Error NEXUS_AudioDecoder_SetTrickState(
    NEXUS_AudioDecoderHandle decoder,
    const NEXUS_AudioDecoderTrickState *pTrickState
    );
NEXUS_Error NEXUS_AudioDecoder_Advance(
    NEXUS_AudioDecoderHandle decoder,
    uint32_t targetPts
    );
typedef struct NEXUS_AudioDummyOutput *NEXUS_AudioDummyOutputHandle;
typedef struct NEXUS_AudioDummyOutputSettings
{
    NEXUS_AudioMultichannelFormat maxMultichannelFormat;
} NEXUS_AudioDummyOutputSettings;
void NEXUS_AudioDummyOutput_GetDefaultSettings(
    NEXUS_AudioDummyOutputSettings *pSettings
    );
NEXUS_AudioDummyOutputHandle NEXUS_AudioDummyOutput_Open(
    unsigned index,
    const NEXUS_AudioDummyOutputSettings *pSettings
    );
void NEXUS_AudioDummyOutput_Close(
    NEXUS_AudioDummyOutputHandle handle
    );
void NEXUS_AudioDummyOutput_GetSettings(
    NEXUS_AudioDummyOutputHandle handle,
    NEXUS_AudioDummyOutputSettings *pSettings
    );
NEXUS_Error NEXUS_AudioDummyOutput_SetSettings(
    NEXUS_AudioDummyOutputHandle handle,
    const NEXUS_AudioDummyOutputSettings *pSettings
    );
NEXUS_AudioOutputHandle NEXUS_AudioDummyOutput_GetConnector(
    NEXUS_AudioDummyOutputHandle handle
    );
typedef struct NEXUS_DtsEncode *NEXUS_DtsEncodeHandle;
typedef struct NEXUS_DtsEncodeSettings
{
    _Bool spdifHeaderEnabled;
} NEXUS_DtsEncodeSettings;
void NEXUS_DtsEncode_GetDefaultSettings(
    NEXUS_DtsEncodeSettings *pSettings
    );
NEXUS_DtsEncodeHandle NEXUS_DtsEncode_Open(
    const NEXUS_DtsEncodeSettings *pSettings
    );
void NEXUS_DtsEncode_Close(
    NEXUS_DtsEncodeHandle handle
    );
void NEXUS_DtsEncode_GetSettings(
    NEXUS_DtsEncodeHandle handle,
    NEXUS_DtsEncodeSettings *pSettings
    );
NEXUS_Error NEXUS_DtsEncode_SetSettings(
    NEXUS_DtsEncodeHandle handle,
    const NEXUS_DtsEncodeSettings *pSettings
    );
NEXUS_AudioInputHandle NEXUS_DtsEncode_GetConnector(
    NEXUS_DtsEncodeHandle handle
    );
NEXUS_Error NEXUS_DtsEncode_AddInput(
    NEXUS_DtsEncodeHandle handle,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_DtsEncode_RemoveInput(
    NEXUS_DtsEncodeHandle handle,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_DtsEncode_RemoveAllInputs(
    NEXUS_DtsEncodeHandle handle
    );
typedef struct NEXUS_AudioEncoder *NEXUS_AudioEncoderHandle;
typedef struct NEXUS_AudioEncoderSettings
{
    NEXUS_AudioCodec codec;
    _Bool loudnessEquivalenceEnabled;
} NEXUS_AudioEncoderSettings;
void NEXUS_AudioEncoder_GetDefaultSettings(
    NEXUS_AudioEncoderSettings *pSettings
    );
NEXUS_AudioEncoderHandle NEXUS_AudioEncoder_Open(
    const NEXUS_AudioEncoderSettings *pSettings
    );
void NEXUS_AudioEncoder_Close(
    NEXUS_AudioEncoderHandle handle
    );
void NEXUS_AudioEncoder_GetSettings(
    NEXUS_AudioEncoderHandle handle,
    NEXUS_AudioEncoderSettings *pSettings
    );
NEXUS_Error NEXUS_AudioEncoder_SetSettings(
    NEXUS_AudioEncoderHandle handle,
    const NEXUS_AudioEncoderSettings *pSettings
    );
typedef enum NEXUS_AacEncodeComplexity
{
    NEXUS_AacEncodeComplexity_eLowest,
    NEXUS_AacEncodeComplexity_eMediumLow,
    NEXUS_AacEncodeComplexity_eMediumHigh,
    NEXUS_AacEncodeComplexity_eHighest,
    NEXUS_AacEncodeComplexity_eMax
} NEXUS_AacEncodeComplexity;
typedef struct NEXUS_AacEncodeSettings
{
    NEXUS_AudioMode outputMode;
    NEXUS_AudioMonoChannelMode monoMode;
    unsigned bitRate;
    unsigned sampleRate;
    NEXUS_AacEncodeComplexity complexity;
} NEXUS_AacEncodeSettings;
typedef struct NEXUS_AudioMpegEncodeSettings
{
    unsigned bitRate;
    _Bool privateBit;
    _Bool copyrightBit;
    _Bool originalBit;
    NEXUS_AudioMpegEmphasis emphasis;
    NEXUS_AudioMode outputMode;
    NEXUS_AudioMonoChannelMode monoMode;
}NEXUS_AudioMpegEncodeSettings;
typedef struct NEXUS_AudioWmaStdEncodeSettings
{
    unsigned bitRate;
    _Bool monoEncoding;
}NEXUS_AudioWmaStdEncodeSettings;
typedef enum NEXUS_G711G726CompressionMode
{
    NEXUS_G711G726CompressionMode_eUlaw,
    NEXUS_G711G726CompressionMode_eAlaw,
    NEXUS_G711G726CompressionMode_eMax
} NEXUS_G711G726CompressionMode;
typedef struct NEXUS_G711EncodeSettings
{
    NEXUS_G711G726CompressionMode compressionMode;
} NEXUS_G711EncodeSettings;
typedef struct NEXUS_G726EncodeSettings
{
    NEXUS_G711G726CompressionMode compressionMode;
    unsigned bitRate;
} NEXUS_G726EncodeSettings;
typedef struct NEXUS_G729EncodeSettings
{
    _Bool dtxEnabled;
    unsigned bitRate;
} NEXUS_G729EncodeSettings;
typedef struct NEXUS_G723_1EncodeSettings
{
    _Bool vadEnabled;
    _Bool hpfEnabled;
    unsigned bitRate;
} NEXUS_G723_1EncodeSettings;
typedef struct NEXUS_IlbcEncodeSettings
{
    unsigned frameLength;
} NEXUS_IlbcEncodeSettings;
typedef enum NEXUS_OpusEncodeMode
{
    NEXUS_OpusEncodeMode_eSilk,
    NEXUS_OpusEncodeMode_eHybrid,
    NEXUS_OpusEncodeMode_eCELT,
    NEXUS_OpusEncodeMode_eMax
} NEXUS_OpusEncodeMode;
typedef enum NEXUS_OpusBitRateType
{
    NEXUS_OpusBitRateType_eCBR,
    NEXUS_OpusBitRateType_eVBR,
    NEXUS_OpusBitRateType_eCVBR,
    NEXUS_OpusBitRateType_eMax
} NEXUS_OpusBitRateType;
typedef struct NEXUS_OpusEncodeSettings
{
    unsigned bitRate;
    unsigned frameSize;
    NEXUS_OpusEncodeMode encodeMode;
    NEXUS_OpusBitRateType bitRateType;
    unsigned complexity;
} NEXUS_OpusEncodeSettings;
typedef struct NEXUS_AudioEncoderCodecSettings
{
    NEXUS_AudioCodec codec;
    union
    {
        NEXUS_Ac3EncodeSettings ac3;
        NEXUS_DtsEncodeSettings dts;
        NEXUS_AacEncodeSettings aac;
        NEXUS_AacEncodeSettings aacPlus;
        NEXUS_AudioMpegEncodeSettings mp3;
        NEXUS_AudioWmaStdEncodeSettings wmaStd;
        NEXUS_G711EncodeSettings g711;
        NEXUS_G726EncodeSettings g726;
        NEXUS_G729EncodeSettings g729;
        NEXUS_G723_1EncodeSettings g723_1;
        NEXUS_IlbcEncodeSettings ilbc;
        NEXUS_OpusEncodeSettings opus;
    } codecSettings;
} NEXUS_AudioEncoderCodecSettings;
void NEXUS_AudioEncoder_GetDefaultCodecSettings(
    NEXUS_AudioCodec codec,
    NEXUS_AudioEncoderCodecSettings *pSettings
    );
void NEXUS_AudioEncoder_GetCodecSettings(
    NEXUS_AudioEncoderHandle handle,
    NEXUS_AudioCodec codec,
    NEXUS_AudioEncoderCodecSettings *pSettings
    );
NEXUS_Error NEXUS_AudioEncoder_SetCodecSettings(
    NEXUS_AudioEncoderHandle handle,
    const NEXUS_AudioEncoderCodecSettings *pSettings
    );
NEXUS_AudioInputHandle NEXUS_AudioEncoder_GetConnector(
    NEXUS_AudioEncoderHandle handle
    );
NEXUS_Error NEXUS_AudioEncoder_AddInput(
    NEXUS_AudioEncoderHandle handle,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_AudioEncoder_RemoveInput(
    NEXUS_AudioEncoderHandle handle,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_AudioEncoder_RemoveAllInputs(
    NEXUS_AudioEncoderHandle handle
    );
typedef struct NEXUS_AudioEqualizerStage *NEXUS_AudioEqualizerStageHandle;
typedef enum NEXUS_AudioToneControlType
{
    NEXUS_AudioToneControlType_eShelving,
    NEXUS_AudioToneControlType_eNotch,
    NEXUS_AudioToneControlType_eMax
} NEXUS_AudioToneControlType;
typedef struct NEXUS_AudioEqualizerToneControlSettings
{
 struct{
  int gain;
  unsigned freq;
  NEXUS_AudioToneControlType eqType;
  unsigned bandwidthFreq;
 }bassSettings;
    struct{
     int gain;
     unsigned freq;
     NEXUS_AudioToneControlType eqType;
     unsigned bandwidthFreq;
 }trebleSettings;
} NEXUS_AudioEqualizerToneControlSettings;
typedef struct NEXUS_AudioEqualizerFiveBandSettings
{
    int gain100Hz;
    int gain300Hz;
    int gain1000Hz;
    int gain3000Hz;
    int gain10000Hz;
}NEXUS_AudioEqualizerFiveBandSettings;
typedef enum NEXUS_AudioEqualizerWindowStep
{
    NEXUS_AudioEqualizerWindowStep_eNone,
    NEXUS_AudioEqualizerWindowStep_e170_6,
    NEXUS_AudioEqualizerWindowStep_e85_3,
    NEXUS_AudioEqualizerWindowStep_e42_6,
    NEXUS_AudioEqualizerWindowStep_e21_3,
    NEXUS_AudioEqualizerWindowStep_e10_6,
    NEXUS_AudioEqualizerWindowStep_e5_3,
    NEXUS_AudioEqualizerWindowStep_e2_6,
    NEXUS_AudioEqualizerWindowStep_eMax
} NEXUS_AudioEqualizerWindowStep;
typedef struct NEXUS_AudioEqualizerSevenBandSettings
{
    struct
    {
        unsigned peak;
        int gain;
        unsigned q;
    } bandSettings[(7)];
    NEXUS_AudioEqualizerWindowStep windowStep;
}NEXUS_AudioEqualizerSevenBandSettings;
typedef enum NEXUS_AudioEqualizerFilterType
{
    NEXUS_AudioEqualizerFilterType_eButterworth,
    NEXUS_AudioEqualizerFilterType_eLinkwitzRiley,
    NEXUS_AudioEqualizerFilterType_eMax
}NEXUS_AudioEqualizerFilterType;
typedef struct NEXUS_AudioEqualizerSubsonicSettings
{
    unsigned frequency;
    unsigned filterOrder;
    NEXUS_AudioEqualizerFilterType filterType;
}NEXUS_AudioEqualizerSubsonicSettings;
typedef struct NEXUS_AudioEqualizerSubwooferSettings
{
    unsigned frequency;
    unsigned filterOrder;
    NEXUS_AudioEqualizerFilterType filterType;
}NEXUS_AudioEqualizerSubwooferSettings;
typedef enum NEXUS_AudioEqualizerStageType
{
    NEXUS_AudioEqualizerStageType_eToneControl,
    NEXUS_AudioEqualizerStageType_eFiveBand,
    NEXUS_AudioEqualizerStageType_eSevenBand,
    NEXUS_AudioEqualizerStageType_eSubsonic,
    NEXUS_AudioEqualizerStageType_eSubwoofer,
    NEXUS_AudioEqualizerStageType_eMax
} NEXUS_AudioEqualizerStageType;
typedef struct NEXUS_AudioEqualizerRampSettings
{
    _Bool enable;
    unsigned stepSize;
}NEXUS_AudioEqualizerRampSettings;
typedef struct NEXUS_AudioEqualizerStageSettings
{
    NEXUS_AudioEqualizerStageType type;
    NEXUS_AudioEqualizerRampSettings rampSettings;
    _Bool enabled;
    union
    {
        NEXUS_AudioEqualizerToneControlSettings toneControl;
        NEXUS_AudioEqualizerFiveBandSettings fiveBand;
        NEXUS_AudioEqualizerSevenBandSettings sevenBand;
        NEXUS_AudioEqualizerSubsonicSettings subsonic;
        NEXUS_AudioEqualizerSubwooferSettings subwoofer;
    } modeSettings;
} NEXUS_AudioEqualizerStageSettings;
void NEXUS_AudioEqualizerStage_GetDefaultSettings(
    NEXUS_AudioEqualizerStageType type,
    NEXUS_AudioEqualizerStageSettings *pSettings
    );
NEXUS_AudioEqualizerStageHandle NEXUS_AudioEqualizerStage_Create(
    const NEXUS_AudioEqualizerStageSettings *pSettings
    );
void NEXUS_AudioEqualizerStage_Destroy(
    NEXUS_AudioEqualizerStageHandle handle
    );
void NEXUS_AudioEqualizerStage_GetSettings(
    NEXUS_AudioEqualizerStageHandle handle,
    NEXUS_AudioEqualizerStageSettings *pSettings
    );
NEXUS_Error NEXUS_AudioEqualizerStage_SetSettings(
    NEXUS_AudioEqualizerStageHandle handle,
    const NEXUS_AudioEqualizerStageSettings *pSettings
    );
typedef struct NEXUS_AudioEqualizer *NEXUS_AudioEqualizerHandle;
typedef struct NEXUS_AudioEqualizerSettings
{
    int tbd;
} NEXUS_AudioEqualizerSettings;
void NEXUS_AudioEqualizer_GetDefaultSettings(
    NEXUS_AudioEqualizerSettings *pSettings
    );
NEXUS_AudioEqualizerHandle NEXUS_AudioEqualizer_Create(
    const NEXUS_AudioEqualizerSettings *pSettings
    );
void NEXUS_AudioEqualizer_Destroy(
    NEXUS_AudioEqualizerHandle handle
    );
NEXUS_Error NEXUS_AudioEqualizer_AddStage(
 NEXUS_AudioEqualizerHandle equalizer,
 NEXUS_AudioEqualizerStageHandle stage
 );
NEXUS_Error NEXUS_AudioEqualizer_RemoveStage(
 NEXUS_AudioEqualizerHandle equalizer,
 NEXUS_AudioEqualizerStageHandle stage
    );
NEXUS_Error NEXUS_AudioEqualizer_RemoveAllStages(
 NEXUS_AudioEqualizerHandle equalizer
    );
NEXUS_Error NEXUS_AudioOutput_SetEqualizer(
    NEXUS_AudioOutputHandle output,
    NEXUS_AudioEqualizerHandle equalizer
    );
void NEXUS_AudioOutput_ClearEqualizer(
 NEXUS_AudioOutputHandle output
 );
typedef struct NEXUS_AudioModuleInternalSettings
{
    struct
    {
        NEXUS_ModuleHandle transport;
        NEXUS_ModuleHandle hdmiInput;
        NEXUS_ModuleHandle hdmiOutput;
        NEXUS_ModuleHandle rfm;
        NEXUS_ModuleHandle frontend;
        NEXUS_ModuleHandle surface;
        NEXUS_ModuleHandle core;
        NEXUS_ModuleHandle security;
    } modules;
} NEXUS_AudioModuleInternalSettings;
struct NEXUS_Core_PreInitState;
void NEXUS_AudioModule_GetDefaultSettings(
    const struct NEXUS_Core_PreInitState *preInitState,
    NEXUS_AudioModuleSettings *pSettings
    );
void NEXUS_AudioModule_GetDefaultInternalSettings(
    NEXUS_AudioModuleInternalSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_AudioModule_Init(
    const NEXUS_AudioModuleSettings *pSettings,
    const NEXUS_AudioModuleInternalSettings *pInternalSettings
    );
void NEXUS_AudioModule_Uninit(void);
typedef struct NEXUS_AudioModuleMemoryEstimate
{
    struct {
        unsigned general;
    } memc[3];
} NEXUS_AudioModuleMemoryEstimate;
void NEXUS_AudioModule_GetDefaultUsageSettings(
    NEXUS_AudioModuleUsageSettings *pSettings
    );
NEXUS_Error NEXUS_AudioModule_GetMemoryEstimate(
    const struct NEXUS_Core_PreInitState *preInitState,
    const NEXUS_AudioModuleUsageSettings *pSettings,
    NEXUS_AudioModuleMemoryEstimate *pEstimate
    );
typedef struct NEXUS_AudioInputStatus
{
    _Bool valid;
    NEXUS_AudioCodec codec;
    unsigned numPcmChannels;
    unsigned sampleRate;
} NEXUS_AudioInputStatus;
void NEXUS_AudioInput_Shutdown(
    NEXUS_AudioInputHandle input
    );
void NEXUS_AudioInput_IsConnectedToInput(
    NEXUS_AudioInputHandle input1,
    NEXUS_AudioInputHandle input2,
    _Bool *pConnected
    );
void NEXUS_AudioInput_IsConnectedToOutput(
    NEXUS_AudioInputHandle input,
    NEXUS_AudioOutputHandle output,
    _Bool *pConnected
    );
void NEXUS_AudioInput_IsRunning(
    NEXUS_AudioInputHandle input,
    _Bool *pRunning
    );
void NEXUS_AudioInput_HasConnectedOutputs(
    NEXUS_AudioInputHandle input,
    _Bool *pConnected
    );
NEXUS_Error NEXUS_AudioInput_GetInputStatus(
    NEXUS_AudioInputHandle input,
    NEXUS_AudioInputStatus *pStatus
    );
typedef struct NEXUS_AudioInputCapture *NEXUS_AudioInputCaptureHandle;
typedef struct NEXUS_AudioInputCaptureOpenSettings
{
    size_t fifoSize;
    NEXUS_AudioMultichannelFormat multichannelFormat;
    NEXUS_HeapHandle heap;
    NEXUS_AudioCaptureFormat format;
    size_t threshold;
} NEXUS_AudioInputCaptureOpenSettings;
void NEXUS_AudioInputCapture_GetDefaultOpenSettings(
    NEXUS_AudioInputCaptureOpenSettings *pSettings
    );
NEXUS_AudioInputCaptureHandle NEXUS_AudioInputCapture_Open(
    unsigned index,
    const NEXUS_AudioInputCaptureOpenSettings *pSettings
    );
void NEXUS_AudioInputCapture_Close(
    NEXUS_AudioInputCaptureHandle handle
    );
typedef struct NEXUS_AudioInputCaptureStartSettings
{
    NEXUS_AudioInputHandle input;
} NEXUS_AudioInputCaptureStartSettings;
void NEXUS_AudioInputCapture_GetDefaultStartSettings(
    NEXUS_AudioInputCaptureStartSettings *pSettings
    );
NEXUS_Error NEXUS_AudioInputCapture_Start(
    NEXUS_AudioInputCaptureHandle handle,
    const NEXUS_AudioInputCaptureStartSettings *pSettings
    );
void NEXUS_AudioInputCapture_Stop(
    NEXUS_AudioInputCaptureHandle handle
    );
typedef struct NEXUS_AudioInputCaptureSettings
{
    NEXUS_CallbackDesc sourceChanged;
    NEXUS_CallbackDesc dataCallback;
    int32_t volumeMatrix[NEXUS_AudioChannel_eMax][NEXUS_AudioChannel_eMax];
    _Bool muted;
    NEXUS_AudioCaptureFormat format;
    size_t threshold;
} NEXUS_AudioInputCaptureSettings;
void NEXUS_AudioInputCapture_GetSettings(
    NEXUS_AudioInputCaptureHandle handle,
    NEXUS_AudioInputCaptureSettings *pSettings
    );
NEXUS_Error NEXUS_AudioInputCapture_SetSettings(
    NEXUS_AudioInputCaptureHandle handle,
    const NEXUS_AudioInputCaptureSettings *pSettings
    );
typedef struct NEXUS_AudioInputCaptureStatus
{
    _Bool started;
    _Bool inputSignalPresent;
    _Bool inputSignalValid;
    unsigned sampleRate;
    NEXUS_AudioCodec codec;
    unsigned numPcmChannels;
} NEXUS_AudioInputCaptureStatus;
NEXUS_Error NEXUS_AudioInputCapture_GetStatus(
    NEXUS_AudioInputCaptureHandle handle,
    NEXUS_AudioInputCaptureStatus *pStatus
    );
NEXUS_AudioInputHandle NEXUS_AudioInputCapture_GetConnector(
    NEXUS_AudioInputCaptureHandle handle
    );
NEXUS_Error NEXUS_AudioInputCapture_GetBuffer(
    NEXUS_AudioInputCaptureHandle handle,
    void **ppBuffer,
    size_t *pSize
    );
NEXUS_Error NEXUS_AudioInputCapture_ReadComplete(
    NEXUS_AudioInputCaptureHandle handle,
    size_t amountWritten
    );
typedef struct NEXUS_AudioMixer *NEXUS_AudioMixerHandle;
typedef struct NEXUS_AudioMixerDolbySettings
{
    int multiStreamBalance;
    unsigned certificationMode;
    _Bool enablePostProcessing;
    struct {
        _Bool enableVolumeLimiting;
        _Bool enableIntelligentLoudness;
        unsigned volumeLimiterAmount;
    } volumeLimiter;
    struct {
        _Bool enableDialogEnhancer;
        unsigned dialogEnhancerLevel;
        unsigned contentSuppressionLevel;
    } dialogEnhancer;
    struct {
        _Bool enabled;
        unsigned numBands;
        struct {
            unsigned frequency;
            int gain;
        } band [20];
    } intelligentEqualizer;
    struct {
        _Bool continuousFading;
    } fade;
} NEXUS_AudioMixerDolbySettings;
typedef struct NEXUS_AudioMixerSettings
{
    _Bool mixUsingDsp;
    _Bool intermediate;
    int multiStreamBalance;
    unsigned dspIndex;
    NEXUS_AudioInputHandle master;
    unsigned outputSampleRate;
    int32_t outputVolume[NEXUS_AudioChannel_eMax];
    _Bool outputMuted;
    NEXUS_AudioFadeSettings mainDecodeFade;
    int32_t loopbackVolumeMatrix[NEXUS_AudioChannel_eMax][NEXUS_AudioChannel_eMax];
    _Bool loopbackMixerEnabled;
    NEXUS_AudioMixerDolbySettings dolby;
    _Bool fixedOutputFormatEnabled;
    NEXUS_AudioMultichannelFormat fixedOutputFormat;
} NEXUS_AudioMixerSettings;
void NEXUS_AudioMixer_GetDefaultSettings(
    NEXUS_AudioMixerSettings *pSettings
    );
NEXUS_AudioMixerHandle NEXUS_AudioMixer_Open(
    const NEXUS_AudioMixerSettings *pSettings
    );
void NEXUS_AudioMixer_Close(
    NEXUS_AudioMixerHandle handle
    );
void NEXUS_AudioMixer_GetSettings(
    NEXUS_AudioMixerHandle handle,
    NEXUS_AudioMixerSettings *pSettings
    );
NEXUS_Error NEXUS_AudioMixer_SetSettings(
    NEXUS_AudioMixerHandle handle,
    const NEXUS_AudioMixerSettings *pSettings
    );
NEXUS_Error NEXUS_AudioMixer_Start(
    NEXUS_AudioMixerHandle handle
    );
void NEXUS_AudioMixer_Stop(
    NEXUS_AudioMixerHandle handle
    );
NEXUS_Error NEXUS_AudioMixer_AddInput(
    NEXUS_AudioMixerHandle handle,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_AudioMixer_RemoveInput(
    NEXUS_AudioMixerHandle handle,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_AudioMixer_RemoveAllInputs(
    NEXUS_AudioMixerHandle handle
    );
NEXUS_AudioInputHandle NEXUS_AudioMixer_GetConnector(
    NEXUS_AudioMixerHandle mixer
    );
NEXUS_Error NEXUS_AudioMixer_GetInputSettings(
    NEXUS_AudioMixerHandle handle,
    NEXUS_AudioInputHandle input,
    NEXUS_AudioMixerInputSettings *pSettings
    );
NEXUS_Error NEXUS_AudioMixer_SetInputSettings(
    NEXUS_AudioMixerHandle handle,
    NEXUS_AudioInputHandle input,
    const NEXUS_AudioMixerInputSettings *pSettings
    );
NEXUS_Error NEXUS_AudioMixer_GetInputStatus(
    NEXUS_AudioMixerHandle handle,
    NEXUS_AudioInputHandle input,
    NEXUS_AudioMixerInputStatus *pStatus
    );
NEXUS_Error NEXUS_AudioMixer_GetStatus(
    NEXUS_AudioMixerHandle handle,
    NEXUS_AudioMixerStatus *pStatus
    );
typedef struct NEXUS_AudioMuxOutput *NEXUS_AudioMuxOutputHandle;
typedef struct NEXUS_AudioMuxOutputCreateSettings
{
    struct {
        unsigned fifoSize;
        NEXUS_HeapHandle heap;
    } data, index;
    unsigned numDescriptors;
} NEXUS_AudioMuxOutputCreateSettings;
void NEXUS_AudioMuxOutput_GetDefaultCreateSettings(
    NEXUS_AudioMuxOutputCreateSettings *pSettings
    );
NEXUS_AudioMuxOutputHandle NEXUS_AudioMuxOutput_Create(
    const NEXUS_AudioMuxOutputCreateSettings *pSettings
    );
void NEXUS_AudioMuxOutput_Destroy(
    NEXUS_AudioMuxOutputHandle handle
    );
NEXUS_AudioOutputHandle NEXUS_AudioMuxOutput_GetConnector(
    NEXUS_AudioMuxOutputHandle handle
    );
typedef struct NEXUS_AudioMuxOutputDelayStatus
{
    unsigned endToEndDelay;
} NEXUS_AudioMuxOutputDelayStatus;
NEXUS_Error NEXUS_AudioMuxOutput_GetDelayStatus(
    NEXUS_AudioMuxOutputHandle handle,
    NEXUS_AudioCodec codec,
    NEXUS_AudioMuxOutputDelayStatus *pStatus
    );
typedef struct NEXUS_AudioMuxOutputStartSettings
{
    NEXUS_StcChannelHandle stcChannel;
    unsigned presentationDelay;
    _Bool nonRealTime;
} NEXUS_AudioMuxOutputStartSettings;
void NEXUS_AudioMuxOutput_GetDefaultStartSettings(
    NEXUS_AudioMuxOutputStartSettings *pSettings
    );
NEXUS_Error NEXUS_AudioMuxOutput_Start(
    NEXUS_AudioMuxOutputHandle handle,
    const NEXUS_AudioMuxOutputStartSettings *pSettings
    );
void NEXUS_AudioMuxOutput_Stop(
    NEXUS_AudioMuxOutputHandle handle
    );
typedef struct NEXUS_AudioMuxOutputSettings
{
    NEXUS_CallbackDesc overflow;
} NEXUS_AudioMuxOutputSettings;
void NEXUS_AudioMuxOutput_GetSettings(
    NEXUS_AudioMuxOutputHandle handle,
    NEXUS_AudioMuxOutputSettings *pSettings
    );
NEXUS_Error NEXUS_AudioMuxOutput_SetSettings(
    NEXUS_AudioMuxOutputHandle handle,
    const NEXUS_AudioMuxOutputSettings *pSettings
    );
typedef struct NEXUS_AudioMuxOutputStatus
{
    NEXUS_MemoryBlockHandle bufferBlock;
    NEXUS_MemoryBlockHandle metadataBufferBlock;
    unsigned numFrames;
    unsigned numErrorFrames;
    unsigned numDroppedFrames;
    struct {
        unsigned fifoDepth;
        unsigned fifoSize;
    } data, index;
} NEXUS_AudioMuxOutputStatus;
NEXUS_Error NEXUS_AudioMuxOutput_GetStatus(
    NEXUS_AudioMuxOutputHandle handle,
    NEXUS_AudioMuxOutputStatus *pStatus
    );
typedef struct NEXUS_AudioMuxOutputFrame
{
    uint32_t flags;
    uint32_t originalPts;
    uint64_t pts;
    uint64_t stcSnapshot;
    uint32_t escr;
    uint16_t ticksPerBit;
    int16_t shr;
    unsigned offset;
    size_t length;
    unsigned encoderIndex;
    unsigned unused;
    unsigned rawDataOffset;
    size_t rawDataLength;
    uint8_t dataUnitType;
} NEXUS_AudioMuxOutputFrame;
typedef enum NEXUS_AudioMetadataType
{
    NEXUS_AudioMetadataType_eCommon,
    NEXUS_AudioMetadataType_eMax
} NEXUS_AudioMetadataType;
typedef struct NEXUS_AudioMetadataDescriptor
{
    unsigned metadataFlags;
    struct
    {
        unsigned maximum;
    } bitrate;
    struct
    {
        unsigned sampleRate;
    } samplingFrequency;
    struct
    {
        uint64_t stcSnapshot;
        unsigned chunkId;
    } timing;
    unsigned reserved;
    union
    {
        struct
        {
            uint8_t asc[(8)];
            unsigned ascLengthBits;
            unsigned ascLengthBytes;
        } aac;
        struct
        {
            unsigned samplesPerBlock;
            unsigned encodeOptions;
            unsigned superBlockAlign;
            unsigned blockAlign;
            unsigned numChannels;
        } wmaStd;
    } protocolData;
} NEXUS_AudioMetadataDescriptor;
NEXUS_Error NEXUS_AudioMuxOutput_GetBuffer(
    NEXUS_AudioMuxOutputHandle handle,
    const NEXUS_AudioMuxOutputFrame **pBuffer,
    size_t *pSize,
    const NEXUS_AudioMuxOutputFrame **pBuffer2,
    size_t *pSize2
    );
NEXUS_Error NEXUS_AudioMuxOutput_ReadComplete(
    NEXUS_AudioMuxOutputHandle handle,
    unsigned framesCompleted
    );
typedef struct NEXUS_AudioOutputGroup *NEXUS_AudioOutputGroupHandle;
typedef struct NEXUS_AudioOutputGroupCreateSettings
{
    NEXUS_AudioOutputHandle outputs[4];
} NEXUS_AudioOutputGroupCreateSettings;
void NEXUS_AudioOutputGroup_GetDefaultCreateSettings(
    NEXUS_AudioOutputGroupCreateSettings *pSettings
    );
NEXUS_AudioOutputGroupHandle NEXUS_AudioOutputGroup_Create(
    const NEXUS_AudioOutputGroupCreateSettings *pSettings
    );
void NEXUS_AudioOutputGroup_Destroy(
    NEXUS_AudioOutputGroupHandle handle
    );
NEXUS_AudioOutputHandle NEXUS_AudioOutputGroup_GetConnector(
    NEXUS_AudioOutputGroupHandle handle
    );
typedef struct NEXUS_AudioPlayback *NEXUS_AudioPlaybackHandle;
typedef struct NEXUS_AudioPlaybackOpenSettings
{
    size_t fifoSize;
    size_t threshold;
    NEXUS_HeapHandle heap;
} NEXUS_AudioPlaybackOpenSettings;
void NEXUS_AudioPlayback_GetDefaultOpenSettings(
    NEXUS_AudioPlaybackOpenSettings *pSettings
    );
NEXUS_AudioPlaybackHandle NEXUS_AudioPlayback_Open(
    unsigned index,
    const NEXUS_AudioPlaybackOpenSettings *pSettings
    );
void NEXUS_AudioPlayback_Close(
    NEXUS_AudioPlaybackHandle handle
    );
typedef struct NEXUS_AudioPlaybackStartSettings
{
    NEXUS_Timebase timebase;
    unsigned sampleRate;
    unsigned bitsPerSample;
    size_t startThreshold;
    _Bool stereo;
    _Bool signedData;
    _Bool loopAround;
    _Bool compressed;
    NEXUS_CallbackDesc dataCallback;
    NEXUS_EndianMode endian;
} NEXUS_AudioPlaybackStartSettings;
void NEXUS_AudioPlayback_GetDefaultStartSettings(
    NEXUS_AudioPlaybackStartSettings *pSettings
    );
NEXUS_Error NEXUS_AudioPlayback_Start(
    NEXUS_AudioPlaybackHandle handle,
    const NEXUS_AudioPlaybackStartSettings *pSettings
    );
void NEXUS_AudioPlayback_Stop(
    NEXUS_AudioPlaybackHandle handle
    );
NEXUS_Error NEXUS_AudioPlayback_Suspend(
    NEXUS_AudioPlaybackHandle handle
    );
NEXUS_Error NEXUS_AudioPlayback_Resume(
    NEXUS_AudioPlaybackHandle handle
    );
void NEXUS_AudioPlayback_Flush(
    NEXUS_AudioPlaybackHandle handle
    );
NEXUS_Error NEXUS_AudioPlayback_GetBuffer(
    NEXUS_AudioPlaybackHandle handle,
    void **pBuffer,
    size_t *pSize
    );
NEXUS_Error NEXUS_AudioPlayback_WriteComplete(
    NEXUS_AudioPlaybackHandle handle,
    size_t amountWritten
    );
typedef struct NEXUS_AudioPlaybackStatus
{
    NEXUS_AudioPlaybackStartSettings startSettings;
    _Bool started;
    size_t queuedBytes;
    size_t fifoSize;
    size_t playedBytes;
} NEXUS_AudioPlaybackStatus;
void NEXUS_AudioPlayback_GetStatus(
    NEXUS_AudioPlaybackHandle handle,
    NEXUS_AudioPlaybackStatus *pStatus
    );
typedef struct NEXUS_AudioPlaybackSettings
{
    int32_t leftVolume;
    int32_t rightVolume;
    _Bool muted;
    unsigned sampleRate;
    unsigned contentReferenceLevel;
} NEXUS_AudioPlaybackSettings;
void NEXUS_AudioPlayback_GetDefaultSettings(
    NEXUS_AudioPlaybackSettings *pSettings
    );
void NEXUS_AudioPlayback_GetSettings(
    NEXUS_AudioPlaybackHandle handle,
    NEXUS_AudioPlaybackSettings *pSettings
    );
NEXUS_Error NEXUS_AudioPlayback_SetSettings(
    NEXUS_AudioPlaybackHandle handle,
    const NEXUS_AudioPlaybackSettings *pSettings
    );
NEXUS_AudioInputHandle NEXUS_AudioPlayback_GetConnector(
    NEXUS_AudioPlaybackHandle handle
    );
typedef struct NEXUS_AudioProcessor *NEXUS_AudioProcessorHandle;
typedef struct NEXUS_AudioProcessorSettings
{
    NEXUS_AudioPostProcessing type;
    union
    {
        NEXUS_AudioFadeSettings fade;
        NEXUS_KaraokeVocalSettings karaokeVocal;
    } settings;
} NEXUS_AudioProcessorSettings;
typedef struct NEXUS_AudioProcessorOpenSettings
{
    NEXUS_AudioPostProcessing type;
} NEXUS_AudioProcessorOpenSettings;
typedef struct NEXUS_AudioProcessorStatus
{
    NEXUS_AudioPostProcessing type;
    union
    {
        NEXUS_AudioFadeStatus fade;
    } status;
} NEXUS_AudioProcessorStatus;
void NEXUS_AudioProcessor_GetDefaultOpenSettings(
    NEXUS_AudioProcessorOpenSettings *pSettings
    );
NEXUS_AudioProcessorHandle NEXUS_AudioProcessor_Open(
    const NEXUS_AudioProcessorOpenSettings *pSettings
    );
void NEXUS_AudioProcessor_Close(
    NEXUS_AudioProcessorHandle handle
    );
void NEXUS_AudioProcessor_GetSettings(
    NEXUS_AudioProcessorHandle handle,
    NEXUS_AudioProcessorSettings *pSettings
    );
NEXUS_Error NEXUS_AudioProcessor_SetSettings(
    NEXUS_AudioProcessorHandle handle,
    const NEXUS_AudioProcessorSettings *pSettings
    );
void NEXUS_AudioProcessor_GetStatus(
    NEXUS_AudioProcessorHandle handle,
    NEXUS_AudioProcessorStatus *pStatus
    );
NEXUS_AudioInputHandle NEXUS_AudioProcessor_GetConnector(
    NEXUS_AudioProcessorHandle handle
    );
NEXUS_Error NEXUS_AudioProcessor_AddInput(
    NEXUS_AudioProcessorHandle handle,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_AudioProcessor_RemoveInput(
    NEXUS_AudioProcessorHandle handle,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_AudioProcessor_RemoveAllInputs(
    NEXUS_AudioProcessorHandle handle
    );
typedef struct NEXUS_AudioReturnChannel *NEXUS_AudioReturnChannelHandle;
typedef struct NEXUS_AudioReturnChannelSettings
{
    _Bool muted;
} NEXUS_AudioReturnChannelSettings;
void NEXUS_AudioReturnChannel_GetDefaultSettings(
    NEXUS_AudioReturnChannelSettings *pSettings
    );
NEXUS_AudioReturnChannelHandle NEXUS_AudioReturnChannel_Open(
    unsigned index,
    const NEXUS_AudioReturnChannelSettings *pSettings
    );
void NEXUS_AudioReturnChannel_Close(
    NEXUS_AudioReturnChannelHandle handle
    );
void NEXUS_AudioReturnChannel_GetSettings(
    NEXUS_AudioReturnChannelHandle handle,
    NEXUS_AudioReturnChannelSettings *pSettings
    );
NEXUS_Error NEXUS_AudioReturnChannel_SetSettings(
    NEXUS_AudioReturnChannelHandle handle,
    const NEXUS_AudioReturnChannelSettings *pSettings
    );
NEXUS_AudioOutputHandle NEXUS_AudioReturnChannel_GetConnector(
    NEXUS_AudioReturnChannelHandle handle
    );
typedef struct NEXUS_AutoVolumeLevel *NEXUS_AutoVolumeLevelHandle;
void NEXUS_AutoVolumeLevel_GetDefaultSettings(
    NEXUS_AutoVolumeLevelSettings *pSettings
    );
NEXUS_AutoVolumeLevelHandle NEXUS_AutoVolumeLevel_Open(
    const NEXUS_AutoVolumeLevelSettings *pSettings
    );
void NEXUS_AutoVolumeLevel_Close(
    NEXUS_AutoVolumeLevelHandle handle
    );
void NEXUS_AutoVolumeLevel_GetSettings(
    NEXUS_AutoVolumeLevelHandle handle,
    NEXUS_AutoVolumeLevelSettings *pSettings
    );
NEXUS_Error NEXUS_AutoVolumeLevel_SetSettings(
    NEXUS_AutoVolumeLevelHandle handle,
    const NEXUS_AutoVolumeLevelSettings *pSettings
    );
NEXUS_AudioInputHandle NEXUS_AutoVolumeLevel_GetConnector(
    NEXUS_AutoVolumeLevelHandle handle
    );
NEXUS_Error NEXUS_AutoVolumeLevel_AddInput(
    NEXUS_AutoVolumeLevelHandle handle,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_AutoVolumeLevel_RemoveInput(
    NEXUS_AutoVolumeLevelHandle handle,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_AutoVolumeLevel_RemoveAllInputs(
    NEXUS_AutoVolumeLevelHandle handle
    );
NEXUS_Error NEXUS_AutoVolumeLevel_GetStatus(
    NEXUS_AutoVolumeLevelHandle handle,
    NEXUS_AutoVolumeLevelStatus *pStatus
    );
typedef struct NEXUS_AvsSettings
{
    unsigned hardStopOffset;
    unsigned maxVoltageStopOffset;
} NEXUS_AvsSettings;
void NEXUS_GetAvsSettings(
    NEXUS_AvsSettings *pSettings
    );
NEXUS_Error NEXUS_SetAvsSettings(
    const NEXUS_AvsSettings *pSettings
    );
typedef struct NEXUS_AvsStatus
{
    unsigned voltage;
    signed temperature;
    _Bool enabled;
    _Bool tracking;
} NEXUS_AvsStatus;
NEXUS_Error NEXUS_GetAvsStatus(
    NEXUS_AvsStatus *pStatus
    );
NEXUS_Addr NEXUS_AddrToOffset(const void *addr);
typedef enum NEXUS_AddrType
{
    NEXUS_AddrType_eCached,
    NEXUS_AddrType_eUncached,
    NEXUS_AddrType_eFake,
    NEXUS_AddrType_eUnknown,
    NEXUS_AddrType_eMax
} NEXUS_AddrType;
NEXUS_AddrType NEXUS_GetAddrType(const void *addr);
void *NEXUS_OffsetToCachedAddr(NEXUS_Addr offset);
void *NEXUS_OffsetToUncachedAddr(NEXUS_Addr offset);
typedef struct NEXUS_Thread *NEXUS_ThreadHandle;
typedef struct NEXUS_ThreadSettings
{
    unsigned priority;
    size_t stackSize;
} NEXUS_ThreadSettings;
void NEXUS_Thread_GetDefaultSettings(
    NEXUS_ThreadSettings *pSettings
    );
NEXUS_ThreadHandle NEXUS_Thread_Create(
    const char *pThreadName,
    void (*pThreadFunc)(void *),
    void *pContext,
    const NEXUS_ThreadSettings *pSettings
    );
void NEXUS_Thread_Destroy(
    NEXUS_ThreadHandle thread
    );
NEXUS_Error NEXUS_Profile_Start(
    void
    );
void NEXUS_Profile_Stop(
    const char *name
    );
void NEXUS_Profile_MarkThread(
    const char *name
    );
void NEXUS_FlushCache_isrsafe(
    const void *address,
    size_t size
    );
const char *NEXUS_GetEnv_isrsafe(
    const char *name
    );
void NEXUS_SetEnv(
    const char *name,
    const char *value
    );
int NEXUS_atoi(
    const char *str
    );
int NEXUS_P_Base_StrCmp(
    const char *str1,
    const char *str2
    );
int b_strlen(
    const char *s
    );
char *b_strncpy(
    char *dest,
    const char *src,
    int n);
typedef struct NEXUS_Security_P_Handle * NEXUS_SecurityHandle;
typedef struct NEXUS_KeySlotTableSettings
{
    unsigned numKeySlotsForType[8];
    _Bool enableMulti2Key;
    unsigned numMulti2KeySlots;
} NEXUS_KeySlotTableSettings;
typedef struct NEXUS_SecurityCapabilities
{
   struct {
       unsigned zeus;
       unsigned firmware;
   } version;
   struct{
       _Bool valid;
       uint8_t value;
   }firmwareEpoch;
   NEXUS_KeySlotTableSettings keySlotTableSettings;
} NEXUS_SecurityCapabilities;
typedef enum NEXUS_SecurityAlgorithm
{
    NEXUS_SecurityAlgorithm_eDvb,
    NEXUS_SecurityAlgorithm_eDvbCsa2 = NEXUS_SecurityAlgorithm_eDvb,
    NEXUS_SecurityAlgorithm_eMulti2,
    NEXUS_SecurityAlgorithm_eDes,
    NEXUS_SecurityAlgorithm_e3DesAba,
    NEXUS_SecurityAlgorithm_e3DesAbc,
    NEXUS_SecurityAlgorithm_eAes,
    NEXUS_SecurityAlgorithm_eAes128 = NEXUS_SecurityAlgorithm_eAes,
    NEXUS_SecurityAlgorithm_eAes192,
    NEXUS_SecurityAlgorithm_eReserved9,
    NEXUS_SecurityAlgorithm_eC2,
    NEXUS_SecurityAlgorithm_eCss,
    NEXUS_SecurityAlgorithm_eM6Ke,
    NEXUS_SecurityAlgorithm_eM6,
    NEXUS_SecurityAlgorithm_eRc4,
    NEXUS_SecurityAlgorithm_eCbcMac,
    NEXUS_SecurityAlgorithm_eWMDrmPd,
    NEXUS_SecurityAlgorithm_eAes128G,
    NEXUS_SecurityAlgorithm_eHdDVD,
    NEXUS_SecurityAlgorithm_eBrDVD,
    NEXUS_SecurityAlgorithm_eDvbCsa3,
    NEXUS_SecurityAlgorithm_eAsf,
    NEXUS_SecurityAlgorithm_eAesCounter = NEXUS_SecurityAlgorithm_eAsf,
    NEXUS_SecurityAlgorithm_eMSMultiSwapMac,
    NEXUS_SecurityAlgorithm_eAsa,
    NEXUS_SecurityAlgorithm_eReserved0,
    NEXUS_SecurityAlgorithm_eReserved1,
    NEXUS_SecurityAlgorithm_eReserved2,
    NEXUS_SecurityAlgorithm_eReserved3,
    NEXUS_SecurityAlgorithm_eReserved4,
    NEXUS_SecurityAlgorithm_eReserved5,
    NEXUS_SecurityAlgorithm_eReserved6,
    NEXUS_SecurityAlgorithm_eReserved7,
    NEXUS_SecurityAlgorithm_eReserved8,
    NEXUS_SecurityAlgorithm_eMax
} NEXUS_SecurityAlgorithm;
typedef enum NEXUS_SecurityAlgorithmVariant
{
    NEXUS_SecurityAlgorithmVariant_eEcb,
    NEXUS_SecurityAlgorithmVariant_eXpt = NEXUS_SecurityAlgorithmVariant_eEcb,
    NEXUS_SecurityAlgorithmVariant_eCbc,
    NEXUS_SecurityAlgorithmVariant_ePes = NEXUS_SecurityAlgorithmVariant_eCbc,
    NEXUS_SecurityAlgorithmVariant_eCounter,
    NEXUS_SecurityAlgorithmVariant_eRCbc,
    NEXUS_SecurityAlgorithmVariant_eMax
} NEXUS_SecurityAlgorithmVariant;
typedef enum NEXUS_Security_CustomerMode
{
    NEXUS_Security_CustomerMode_eGeneric,
    NEXUS_Security_CustomerMode_eReserved1,
    NEXUS_Security_CustomerMode_eReserved2,
    NEXUS_Security_CustomerMode_eReserved3,
    NEXUS_Security_CustomerMode_eMax
} NEXUS_Security_CustomerMode;
typedef enum NEXUS_SecurityTerminationMode
{
    NEXUS_SecurityTerminationMode_eClear,
    NEXUS_SecurityTerminationMode_eCbcResidual,
    NEXUS_SecurityTerminationMode_eBlock = NEXUS_SecurityTerminationMode_eCbcResidual,
    NEXUS_SecurityTerminationMode_eScte52Term = NEXUS_SecurityTerminationMode_eCbcResidual,
    NEXUS_SecurityTerminationMode_eReserved2,
    NEXUS_SecurityTerminationMode_eCipherStealing = NEXUS_SecurityTerminationMode_eReserved2,
    NEXUS_SecurityTerminationMode_eCtsCpcm,
    NEXUS_SecurityTerminationMode_eCipherStealingComcast = NEXUS_SecurityTerminationMode_eCtsCpcm,
    NEXUS_SecurityTerminationMode_eReserved4,
    NEXUS_SecurityTerminationMode_eReserved5,
    NEXUS_SecurityTerminationMode_eReserved6,
    NEXUS_SecurityTerminationMode_eTsAndPacket,
    NEXUS_SecurityTerminationMode_ePacket,
    NEXUS_SecurityTerminationMode_eCbcMac,
    NEXUS_SecurityTerminationMode_eCmac,
    NEXUS_SecurityTerminationMode_eMax
} NEXUS_SecurityTerminationMode;
typedef enum NEXUS_SecurityCounterMode
{
    NEXUS_SecurityCounterMode_eGenericFullBlocks,
    NEXUS_SecurityCounterMode_eGenericAllBlocks,
    NEXUS_SecurityCounterMode_eIvPlayBackFullBlocks,
    NEXUS_SecurityCounterMode_ePartialBlockInNextPacket,
    NEXUS_SecurityCounterMode_eSkipPesHeaderAllBlocks,
    NEXUS_SecurityCounterMode_eMax
}NEXUS_SecurityCounterMode;
typedef enum NEXUS_SecurityIVMode
{
    NEXUS_SecurityIVMode_eRegular,
    NEXUS_SecurityIVMode_eReserved1,
    NEXUS_SecurityIVMode_eReserved2,
    NEXUS_SecurityIVMode_eNoPreProcWriteBack,
    NEXUS_SecurityIVMode_eMax
} NEXUS_SecurityIVMode;
typedef enum NEXUS_SecuritySolitarySelect
{
    NEXUS_SecuritySolitarySelect_eClear,
    NEXUS_SecuritySolitarySelect_eSa,
    NEXUS_SecuritySolitarySelect_eCbcXorIv,
    NEXUS_SecuritySolitarySelect_eIv1 = NEXUS_SecuritySolitarySelect_eCbcXorIv,
    NEXUS_SecuritySolitarySelect_eReserved3,
    NEXUS_SecuritySolitarySelect_eXorIv = NEXUS_SecuritySolitarySelect_eReserved3,
    NEXUS_SecuritySolitarySelect_eReserved4,
    NEXUS_SecuritySolitarySelect_eMax
} NEXUS_SecuritySolitarySelect;
typedef enum NEXUS_SecurityOtpId
{
    NEXUS_SecurityOtpId_eOtpVal,
    NEXUS_SecurityOtpId_eOneVal,
    NEXUS_SecurityOtpId_eZeroVal,
    NEXUS_SecurityOtpId_eMax
} NEXUS_SecurityOtpId;
typedef enum NEXUS_SecurityKey2Select
{
    NEXUS_SecurityKey2Select_eRealKey,
    NEXUS_SecurityKey2Select_eReserved1,
    NEXUS_SecurityKey2Select_eFixedKey,
    NEXUS_SecurityKey2Select_eMax
} NEXUS_SecurityKey2Select;
typedef enum NEXUS_SecurityDvbScrambleLevel
{
    NEXUS_SecurityDvbScrambleLevel_eTs,
    NEXUS_SecurityDvbScrambleLevel_ePes,
    NEXUS_SecurityDvbScrambleLevel_eMax
} NEXUS_SecurityDvbScrambleLevel;
typedef enum NEXUS_SecurityAesCounterSize
{
    NEXUS_SecurityAesCounterSize_e32Bits,
    NEXUS_SecurityAesCounterSize_e64Bits,
    NEXUS_SecurityAesCounterSize_e96Bits,
    NEXUS_SecurityAesCounterSize_e128Bits,
    NEXUS_SecurityAesCounterSize_e128BitsS = NEXUS_SecurityAesCounterSize_e128Bits,
    NEXUS_SecurityAesCounterSize_eMax
} NEXUS_SecurityAesCounterSize;
typedef enum NEXUS_SecurityOperation
{
    NEXUS_SecurityOperation_eEncrypt,
    NEXUS_SecurityOperation_eDecrypt,
    NEXUS_SecurityOperation_ePassThrough,
    NEXUS_SecurityOperation_eMax
} NEXUS_SecurityOperation;
typedef enum NEXUS_SecurityKeyType
{
    NEXUS_SecurityKeyType_eOdd,
    NEXUS_SecurityKeyType_eEven,
    NEXUS_SecurityKeyType_eClear,
    NEXUS_SecurityKeyType_eIv,
    NEXUS_SecurityKeyType_eOddAndEven,
    NEXUS_SecurityKeyType_eMax
} NEXUS_SecurityKeyType;
typedef enum NEXUS_SecurityKeyIVType
{
    NEXUS_SecurityKeyIVType_eNoIV,
    NEXUS_SecurityKeyIVType_eIV,
    NEXUS_SecurityKeyIVType_eAesShortIV,
    NEXUS_SecurityKeyIVType_eMax
} NEXUS_SecurityKeyIVType;
typedef enum NEXUS_SecurityKeyMode
{
    NEXUS_SecurityKeyMode_eRegular,
    NEXUS_SecurityKeyMode_eDes56,
    NEXUS_SecurityKeyMode_eReserved2,
    NEXUS_SecurityKeyMode_eReserved3,
    NEXUS_SecurityKeyMode_eDvbConformance,
    NEXUS_SecurityKeyMode_eCwc,
    NEXUS_SecurityKeyMode_eMax
} NEXUS_SecurityKeyMode;
typedef enum NEXUS_SecurityAlgorithmConfigDestination
{
    NEXUS_SecurityAlgorithmConfigDestination_eCa,
    NEXUS_SecurityAlgorithmConfigDestination_eCps,
    NEXUS_SecurityAlgorithmConfigDestination_eCpd,
    NEXUS_SecurityAlgorithmConfigDestination_eRmx,
    NEXUS_SecurityAlgorithmConfigDestination_eMem2Mem,
    NEXUS_SecurityAlgorithmConfigDestination_eMem2Mem2,
    NEXUS_SecurityAlgorithmConfigDestination_eHdmi,
    NEXUS_SecurityAlgorithmConfigDestination_eMax
} NEXUS_SecurityAlgorithmConfigDestination;
typedef enum NEXUS_SecurityAlgorithmScPolarity
{
    NEXUS_SecurityAlgorithmScPolarity_eClear,
    NEXUS_SecurityAlgorithmScPolarity_eMpegOdd,
    NEXUS_SecurityAlgorithmScPolarity_eAtscClear = NEXUS_SecurityAlgorithmScPolarity_eMpegOdd,
    NEXUS_SecurityAlgorithmScPolarity_eEven,
    NEXUS_SecurityAlgorithmScPolarity_eOdd,
    NEXUS_SecurityAlgorithmScPolarity_eMax
} NEXUS_SecurityAlgorithmScPolarity;
typedef enum NEXUS_SecurityVirtualKeyladderID
{
    NEXUS_SecurityVirtualKeyladderID_eVKL0,
    NEXUS_SecurityVirtualKeyladderID_eVKL1,
    NEXUS_SecurityVirtualKeyladderID_eVKL2,
    NEXUS_SecurityVirtualKeyladderID_eVKL3,
    NEXUS_SecurityVirtualKeyladderID_eVKL4,
    NEXUS_SecurityVirtualKeyladderID_eVKL5,
    NEXUS_SecurityVirtualKeyladderID_eVKL6,
    NEXUS_SecurityVirtualKeyladderID_eVKL7,
    NEXUS_SecurityVirtualKeyladderID_eVKLDummy,
    NEXUS_SecurityVirtualKeyladderID_eSWKey,
    NEXUS_SecurityVirtualKeyladderID_eReserved11,
    NEXUS_SecurityVirtualKeyladderID_eReserved12,
    NEXUS_SecurityVirtualKeyladderID_eReserved13,
    NEXUS_SecurityVirtualKeyladderID_eReserved14,
    NEXUS_SecurityVirtualKeyladderID_eReserved15,
    NEXUS_SecurityVirtualKeyladderID_eMax
} NEXUS_SecurityVirtualKeyladderID;
typedef enum NEXUS_SecurityPacketType {
    NEXUS_SecurityPacketType_eGlobal,
    NEXUS_SecurityPacketType_eRestricted,
    NEXUS_SecurityPacketType_eMax
} NEXUS_SecurityPacketType;
typedef struct NEXUS_SecurityAlgorithmSettings
{
    NEXUS_SecurityAlgorithm algorithm;
    NEXUS_SecurityAlgorithmVariant algorithmVar;
    NEXUS_SecurityTerminationMode terminationMode;
    NEXUS_SecurityCounterMode aesCounterMode;
    NEXUS_SecurityAesCounterSize aesCounterSize;
    NEXUS_SecurityIVMode ivMode;
    NEXUS_SecuritySolitarySelect solitarySelect;
    uint32_t caVendorID;
    unsigned askmModuleID;
    NEXUS_SecurityOtpId otpId;
    NEXUS_SecurityKey2Select key2Select;
    NEXUS_SecurityDvbScrambleLevel dvbScramLevel;
    NEXUS_SecurityKeyType keyDestEntryType;
    NEXUS_SecurityOperation operation;
    NEXUS_SecurityAlgorithmConfigDestination dest;
    NEXUS_SecurityKeySource keySource;
    _Bool bMulti2Config;
    uint16_t multi2KeySelect;
    uint8_t multi2RoundCount;
    _Bool enableExtKey;
    _Bool enableExtIv;
    _Bool bEncryptBeforeRave;
    _Bool bRestrictEnable;
    _Bool bGlobalEnable;
    _Bool modifyScValue[NEXUS_SecurityPacketType_eMax];
    NEXUS_SecurityAlgorithmScPolarity scValue[NEXUS_SecurityPacketType_eMax];
    uint8_t keyOffset;
    uint8_t ivOffset;
    uint8_t mscLengthSelect;
    NEXUS_Security_CustomerMode customerType;
    uint8_t macRegSelect;
 _Bool macNonSecureRegRead;
    _Bool IrModEnable;
    uint8_t dvbCsa2keyCtrl;
    uint8_t dvbCsa2ivCtrl;
    _Bool dvbCsa2modEnabled;
    uint8_t dvbCsa3dvbcsaVar;
    uint8_t dvbCsa3permutation;
    _Bool dvbCsa3modXRC;
    _Bool EsModEnable;
    _Bool RpipeFromRregion;
    _Bool RpipeFromGregion;
    _Bool RpipeToRregion;
    _Bool RpipeToGregion;
    _Bool GpipeFromRregion;
    _Bool GpipeFromGregion;
    _Bool GpipeToRregion;
    _Bool GpipeToGregion;
    _Bool bRoutePipeToRestrictedRegion[NEXUS_SecurityPacketType_eMax];
    _Bool bScAtscMode;
    _Bool bAtscModEnable;
    _Bool bGlobalDropPktEnable;
    _Bool bRestrictDropPktEnable;
    _Bool bGlobalRegionOverwrite;
    _Bool bRestrictSourceDropPktEnable;
    _Bool bScPolarityEnable;
    _Bool bSynEnable;
    _Bool bCPDDisable;
    _Bool bCPSDisable;
    _Bool mscBitSelect;
    _Bool bDisallowGG;
    _Bool bDisallowGR;
    _Bool bDisallowRG;
    _Bool bDisallowRR;
    _Bool enableTimestamps;
    _Bool testKey2Select;
} NEXUS_SecurityAlgorithmSettings;
typedef struct NEXUS_SecurityClearKey
{
    unsigned int keySize;
    NEXUS_SecurityKeyType keyEntryType;
    NEXUS_SecurityKeyIVType keyIVType;
 NEXUS_SecurityKeyMode keyMode;
    NEXUS_SecurityAlgorithmConfigDestination dest;
    NEXUS_SecurityAlgorithmScPolarity sc01Polarity[NEXUS_SecurityPacketType_eMax];
    NEXUS_SecurityAlgorithmScPolarity sc01GlobalMapping;
    uint8_t keyData[64];
} NEXUS_SecurityClearKey;
typedef struct NEXUS_KeySlotExternalKeyData
{
    unsigned slotIndex;
    struct {
        _Bool valid;
        unsigned offset;
    } key, iv;
}NEXUS_KeySlotExternalKeyData;
typedef struct NEXUS_SecurityMulti2Settings
{
    uint16_t multi2KeySelect;
    uint8_t multi2Rounds;
    uint8_t multi2SysKey[32];
} NEXUS_SecurityMulti2Settings;
typedef enum NEXUS_SecurityInvalidateKeyFlag
{
    NEXUS_SecurityInvalidateKeyFlag_eSrcKeyOnly,
    NEXUS_SecurityInvalidateKeyFlag_eDestKeyOnly,
    NEXUS_SecurityInvalidateKeyFlag_eAllKeys,
    NEXUS_SecurityInvalidateKeyFlag_eMax
} NEXUS_SecurityInvalidateKeyFlag;
typedef struct NEXUS_SecurityInvalidateKeySettings
{
    NEXUS_SecurityInvalidateKeyFlag invalidateKeyType;
 _Bool invalidateAllEntries;
    NEXUS_SecurityVirtualKeyladderID virtualKeyLadderID;
    NEXUS_SecurityKeySource keySrc;
    NEXUS_SecurityAlgorithmConfigDestination keyDestBlckType;
    NEXUS_SecurityKeyType keyDestEntryType;
} NEXUS_SecurityInvalidateKeySettings;
typedef struct NEXUS_KeySlotGlobalControlWordSettings
{
 uint8_t inputRegion;
 uint8_t rPipeOutput;
 uint8_t gPipeOutput;
 _Bool encryptBeforeRave;
} NEXUS_KeySlotGlobalControlWordSettings;
typedef enum NEXUS_SecurityCustomerMode {
    NEXUS_SecurityCustomerMode_eGeneric,
    NEXUS_SecurityCustomerMode_eDvs042,
    NEXUS_SecurityCustomerMode_eDesCts,
    NEXUS_SecurityCustomerMode_eDvbCsa
} NEXUS_SecurityCustomerMode;
typedef enum NEXUS_SecurityFirmwareType{
    NEXUS_SecurityFirmwareType_eTransport,
    NEXUS_SecurityFirmwareType_eVideoDecoder,
    NEXUS_SecurityFirmwareType_eAudioDecoder,
    NEXUS_SecurityFirmwareType_ePictureDecoder,
    NEXUS_SecurityFirmwareType_eVideoEncoder,
    NEXUS_SecurityFirmwareType_eMax
}NEXUS_SecurityFirmwareType;
typedef struct NEXUS_SecurityModuleSettings
{
    NEXUS_CommonModuleSettings common;
    NEXUS_SecurityCustomerMode customerMode;
    unsigned int numKeySlotsForType[8];
    _Bool enableMulti2Key;
    unsigned numMulti2KeySlots;
    struct {
        _Bool valid;
        uint8_t data[(64)];
    }ipLicense;
    _Bool enforceAuthentication[NEXUS_SecurityFirmwareType_eMax];
} NEXUS_SecurityModuleSettings;
typedef struct NEXUS_VideoFormatInfo
{
    uint32_t width;
    uint32_t height;
    uint32_t digitalWidth;
    uint32_t digitalHeight;
    uint32_t scanWidth;
    uint32_t scanHeight;
    uint32_t topActive;
    uint32_t topMaxVbiPassThru;
    uint32_t bottomMaxVbiPassThru;
    uint32_t verticalFreq;
    uint32_t pixelFreq;
    _Bool interlaced;
    NEXUS_AspectRatio aspectRatio;
    _Bool isFullRes3d;
} NEXUS_VideoFormatInfo;
void NEXUS_VideoFormat_GetInfo(
    NEXUS_VideoFormat videoFmt,
    NEXUS_VideoFormatInfo *pVideoFmtInfo
    );
typedef struct NEXUS_PixelFormatInfo {
    _Bool rgb;
    _Bool palette;
    _Bool alphaPerPixel;
    unsigned bpp;
} NEXUS_PixelFormatInfo;
void NEXUS_PixelFormat_GetInfo(
    NEXUS_PixelFormat pixelFormat,
    NEXUS_PixelFormatInfo *pInfo
    );
void NEXUS_StopCallbacks_tagged(
    void *interfaceHandle,
    const char *pFileName, unsigned lineNumber, const char *pFunctionName
    );
void NEXUS_StartCallbacks_tagged(
    void *interfaceHandle,
    const char *pFileName, unsigned lineNumber, const char *pFunctionName
    );
void NEXUS_LookupFrameRate(
    unsigned frameRateInteger,
    NEXUS_VideoFrameRate *pNexusFrameRate
    );
NEXUS_Error NEXUS_VideoFrameRate_GetRefreshRate(
    NEXUS_VideoFrameRate frameRate,
    unsigned *pRefreshRate
    );
NEXUS_KeySlotHandle NEXUS_KeySlot_Create(
    void);
void NEXUS_KeySlot_Destroy(
    NEXUS_KeySlotHandle keyslot
    );
typedef void *NEXUS_KeySlotTag;
void NEXUS_KeySlot_GetInfo(
    NEXUS_KeySlotHandle keyslot,
    NEXUS_SecurityKeySlotInfo *pKeyslotInfo
    );
void NEXUS_Security_GetDefaultClearKey(
    NEXUS_SecurityClearKey *pClearKey
    );
NEXUS_Error NEXUS_Security_LoadClearKey(
    NEXUS_KeySlotHandle keyslot,
    const NEXUS_SecurityClearKey *pClearKey
    );
void NEXUS_Security_GetDefaultKeySlotSettings(
    NEXUS_SecurityKeySlotSettings *pSettings
    );
NEXUS_KeySlotHandle NEXUS_Security_AllocateKeySlot(
    const NEXUS_SecurityKeySlotSettings *pSettings
    );
void NEXUS_Security_FreeKeySlot(
    NEXUS_KeySlotHandle keyslot
    );
NEXUS_Error NEXUS_KeySlot_AddPidChannel(
    NEXUS_KeySlotHandle keyslot,
    NEXUS_PidChannelHandle pidChannel
    );
void NEXUS_KeySlot_RemovePidChannel(
    NEXUS_KeySlotHandle keyslot,
    NEXUS_PidChannelHandle pidChannel
    );
void NEXUS_Security_GetDefaultInvalidateKeySettings(
    NEXUS_SecurityInvalidateKeySettings *pSettings
    );
NEXUS_Error NEXUS_Security_InvalidateKey(
    NEXUS_KeySlotHandle keyslot,
    const NEXUS_SecurityInvalidateKeySettings *pSettings
    );
void NEXUS_Security_GetDefaultAlgorithmSettings(
    NEXUS_SecurityAlgorithmSettings *pSettings
    );
NEXUS_Error NEXUS_Security_ConfigAlgorithm(
    NEXUS_KeySlotHandle keyslot,
    const NEXUS_SecurityAlgorithmSettings *pSettings
    );
NEXUS_Error NEXUS_KeySlot_GetExternalKeyData(
    NEXUS_KeySlotHandle keyslot,
    NEXUS_SecurityAlgorithmConfigDestination dest,
    NEXUS_SecurityKeyType keyDestEntryType,
    NEXUS_KeySlotExternalKeyData *pKeyData
    );
NEXUS_Error NEXUS_SetPidChannelBypassKeyslot(
    NEXUS_PidChannelHandle pidChannel,
    NEXUS_BypassKeySlot bypassKeySlot
    );
void NEXUS_GetPidChannelBypassKeyslot(
    NEXUS_PidChannelHandle pidChannel,
    NEXUS_BypassKeySlot *pBypassKeySlot
    );
void NEXUS_GetSecurityCapabilities(
    NEXUS_SecurityCapabilities *pCaps
    );
NEXUS_KeySlotHandle NEXUS_Security_LocateCaKeySlotAssigned(
    unsigned long pidchannel
    );
NEXUS_Error NEXUS_Security_AddPidChannelToKeySlot(
    NEXUS_KeySlotHandle keyHandle,
    unsigned int pidChannel
    );
NEXUS_Error NEXUS_Security_RemovePidChannelFromKeySlot(
    NEXUS_KeySlotHandle keyHandle,
    unsigned int pidChannel
    );
void NEXUS_Security_GetDefaultMulti2Settings(
    NEXUS_SecurityMulti2Settings *pSettings
    );
NEXUS_Error NEXUS_Security_ConfigMulti2(
    NEXUS_KeySlotHandle keyslot,
    const NEXUS_SecurityMulti2Settings *pSettings
    );
void NEXUS_KeySlot_GetDefaultGlobalControlWordSettings(
 NEXUS_KeySlotGlobalControlWordSettings *pSettings
    );
NEXUS_Error NEXUS_KeySlot_SetGlobalControlWordSettings(
    NEXUS_KeySlotHandle keyHandle,
    const NEXUS_KeySlotGlobalControlWordSettings *pSettings
    );
typedef enum NEXUS_SecurityRootKeySrc
{
    NEXUS_SecurityRootKeySrc_eCuskey,
    NEXUS_SecurityRootKeySrc_eOtpKeyA,
    NEXUS_SecurityRootKeySrc_eOtpKeyB,
    NEXUS_SecurityRootKeySrc_eOtpKeyC,
 NEXUS_SecurityRootKeySrc_eOtpKeyD,
 NEXUS_SecurityRootKeySrc_eOtpKeyE,
 NEXUS_SecurityRootKeySrc_eOtpKeyF,
    NEXUS_SecurityRootKeySrc_eOtpKeyG,
    NEXUS_SecurityRootKeySrc_eOtpKeyH,
    NEXUS_SecurityRootKeySrc_eReserved0,
    NEXUS_SecurityRootKeySrc_eReserved1,
    NEXUS_SecurityRootKeySrc_eReserved2,
    NEXUS_SecurityRootKeySrc_eGlobalKey,
    NEXUS_SecurityRootKeySrc_eMax
} NEXUS_SecurityRootKeySrc;
typedef enum NEXUS_SecurityKeyGenCmdID
{
    NEXUS_SecurityKeyGenCmdID_eKeyGen,
    NEXUS_SecurityKeyGenCmdID_eVKLAssocQuery,
    NEXUS_SecurityKeyGenCmdID_eMax
} NEXUS_SecurityKeyGenCmdID;
typedef enum NEXUS_SecuritySessionKeyOp
{
    NEXUS_SecuritySessionKeyOp_eNoProcess,
    NEXUS_SecuritySessionKeyOp_eExport,
    NEXUS_SecuritySessionKeyOp_eMax
} NEXUS_SecuritySessionKeyOp;
typedef enum NEXUS_SecurityKeyladderType
{
    NEXUS_SecurityKeyladderType_e1Des,
    NEXUS_SecurityKeyladderType_e3Des,
    NEXUS_SecurityKeyladderType_eAes128,
 NEXUS_SecurityKeyladderType_ePKSM,
    NEXUS_SecurityKeyladderType_eMax
} NEXUS_SecurityKeyladderType;
typedef enum NEXUS_SecurityKeyLadderSelect
{
    NEXUS_SecurityKeyLadderSelect_eFWKL,
 NEXUS_SecurityKeyLadderSelect_eHWKL,
 NEXUS_SecurityKeyLadderSelect_ePKL,
    NEXUS_SecurityKeyLadderSelect_eMax
} NEXUS_SecurityKeyLadderSelect;
typedef enum NEXUS_SecurityKeyladderID
{
    NEXUS_SecurityKeyladderID_eA,
    NEXUS_SecurityKeyladderID_eB,
    NEXUS_SecurityKeyladderID_eC,
    NEXUS_SecurityKeyladderID_eMax
} NEXUS_SecurityKeyladderID;
typedef enum NEXUS_SecurityCustomerSubMode
{
    NEXUS_SecurityCustomerSubMode_eGeneric_CA_64_4 = 0x0,
    NEXUS_SecurityCustomerSubMode_eGeneric_CP_64_4 = 0x1,
    NEXUS_SecurityCustomerSubMode_eGeneric_CA_64_5 = 0x2,
    NEXUS_SecurityCustomerSubMode_eGeneric_CP_64_5 = 0x3,
    NEXUS_SecurityCustomerSubMode_eGeneric_CA_128_4 = 0x4,
    NEXUS_SecurityCustomerSubMode_eGeneric_CP_128_4 = 0x5,
    NEXUS_SecurityCustomerSubMode_eGeneric_CA_128_5 = 0x6,
    NEXUS_SecurityCustomerSubMode_eGeneric_CP_128_5 = 0x7,
    NEXUS_SecurityCustomerSubMode_eGeneric_CA_64_7 = 0x8,
 NEXUS_SecurityCustomerSubMode_eGeneric_CA_128_7 = 0x9,
    NEXUS_SecurityCustomerSubMode_eReserved10 = 0xA,
    NEXUS_SecurityCustomerSubMode_eReserved11 = 0xB,
    NEXUS_SecurityCustomerSubMode_eSage_128_5 = 0xC,
    NEXUS_SecurityCustomerSubMode_eReserved13 = 0xD,
    NEXUS_SecurityCustomerSubMode_eGeneralPurpose1 = 0xE,
    NEXUS_SecurityCustomerSubMode_eGeneralPurpose2 = 0xF,
    NEXUS_SecurityCustomerSubMode_eReserved16 = 0x10,
    NEXUS_SecurityCustomerSubMode_eReserved17 = 0x11,
    NEXUS_SecurityCustomerSubMode_eGeneric_CA_64_45 = 0x12,
    NEXUS_SecurityCustomerSubMode_eGeneric_CP_64_45 = 0x13,
 NEXUS_SecurityCustomerSubMode_eReserved20 = 0x14,
 NEXUS_SecurityCustomerSubMode_eReserved21 = 0x15,
 NEXUS_SecurityCustomerSubMode_eSecureRSA2 = 0x16,
 NEXUS_SecurityCustomerSubMode_eETSI_5 = 0x17,
 NEXUS_SecurityCustomerSubMode_eDTA_M_CA = 0x18,
 NEXUS_SecurityCustomerSubMode_eDTA_M_CP = 0x19,
 NEXUS_SecurityCustomerSubMode_eDTA_C_CA = 0x1A,
 NEXUS_SecurityCustomerSubMode_eDTA_C_CP = 0x1B,
 NEXUS_SecurityCustomerSubMode_eScte52CA5 = 0x1C,
 NEXUS_SecurityCustomerSubMode_eSageBlDecrypt = 0x1D,
 NEXUS_SecurityCustomerSubMode_eVistaKeyLadder = 0x1E,
 NEXUS_SecurityCustomerSubMode_eVistaCwc = 0x1F,
    NEXUS_SecurityCustomerSubMode_eReserved32 = 0x20,
    NEXUS_SecurityCustomerSubMode_eReserved33 = 0x21,
    NEXUS_SecurityCustomerSubMode_eReserved34 = 0x22,
    NEXUS_SecurityCustomerSubMode_eDupleSource = 0x23,
    NEXUS_SecurityCustomerSubMode_eDupleDestination = 0x24,
    NEXUS_SecurityCustomerSubMode_eOTPKeyFieldProgramDataDecrypt = 0x25,
    NEXUS_SecurityCustomerSubMode_eMax
} NEXUS_SecurityCustomerSubMode;
typedef enum NEXUS_SecuritySwizzleType
{
    NEXUS_SecuritySwizzleType_eNone,
    NEXUS_SecuritySwizzleType_eSwizzle1,
    NEXUS_SecuritySwizzleType_eSwizzle0,
    NEXUS_SecuritySwizzleType_eMax
} NEXUS_SecuritySwizzleType;
typedef enum NEXUS_SecuritySwizzle0aType
{
    NEXUS_SecuritySwizzle0aType_eNoMsp,
    NEXUS_SecuritySwizzle0aType_eMsp0,
    NEXUS_SecuritySwizzle0aType_eMsp1,
    NEXUS_SecuritySwizzle0aType_eDisabled,
    NEXUS_SecuritySwizzle0aType_eMax
} NEXUS_SecuritySwizzle0aType;
typedef enum NEXUS_SecurityHWKLLenSelect
{
 NEXUS_SecurityHWKLLenSelect_eLen0,
 NEXUS_SecurityHWKLLenSelect_eLen1,
 NEXUS_SecurityHWKLLenSelect_eLen2,
 NEXUS_SecurityHWKLLenSelect_eLen3,
    NEXUS_SecurityHWKLLenSelect_eMax
} NEXUS_SecurityHWKLLenSelect;
typedef enum NEXUS_SecuritySC01ModeWordMapping
{
 NEXUS_SecuritySC01ModeWordMapping_eClear,
 NEXUS_SecuritySC01ModeWordMapping_eOdd,
 NEXUS_SecuritySC01ModeWordMapping_eEven,
    NEXUS_SecuritySC01ModeWordMapping_eMax
} NEXUS_SecuritySC01ModeWordMapping;
typedef enum NEXUS_SecurityPKSMInitState
{
 NEXUS_SecurityPKSMInitState_eNone,
 NEXUS_SecurityPKSMInitState_e64Bits,
 NEXUS_SecurityPKSMInitState_e128Bits,
 NEXUS_SecurityPKSMInitState_e192Bits,
    NEXUS_SecurityPKSMInitState_eMax
} NEXUS_SecurityPKSMInitState;
typedef enum NEXUS_SecurityKeyLayer
{
    NEXUS_SecurityKeyLayer_eKey3,
    NEXUS_SecurityKeyLayer_eKey4,
    NEXUS_SecurityKeyLayer_eKey5,
    NEXUS_SecurityKeyLayer_eKey6,
    NEXUS_SecurityKeyLayer_eKey7,
    NEXUS_SecurityKeyLayer_eMax
} NEXUS_SecurityKeyLayer;
typedef enum NEXUS_SecurityGlobalKeyOwnerID
{
    NEXUS_SecurityGlobalKeyOwnerID_eMSP0,
    NEXUS_SecurityGlobalKeyOwnerID_eMSP1,
    NEXUS_SecurityGlobalKeyOwnerID_eReserved,
    NEXUS_SecurityGlobalKeyOwnerID_eUse1,
 NEXUS_SecurityGlobalKeyOwnerID_eMax
} NEXUS_SecurityGlobalKeyOwnerID;
typedef enum NEXUS_SecurityKeyTweak
{
    NEXUS_SecurityKeyTweak_eNoTweak,
    NEXUS_SecurityKeyTweak_ePKSM,
 NEXUS_SecurityKeyTweak_eTransform,
    NEXUS_SecurityKeyTweak_eDSK,
    NEXUS_SecurityKeyTweak_eDupleConnect,
    NEXUS_SecurityKeyTweak_eMax
} NEXUS_SecurityKeyTweak;
typedef enum NEXUS_SecurityMaskKey
{
    NEXUS_SecurityMaskKey_eReal = 0,
    NEXUS_SecurityMaskKey_eReserved1 = 1,
    NEXUS_SecurityMaskKey_eFixed = 2
} NEXUS_SecurityMaskKey;
typedef struct NEXUS_VirtualKeyLadder *NEXUS_VirtualKeyLadderHandle;
typedef struct NEXUS_SecurityEncryptedSessionKey
{
 NEXUS_SecurityClientType client;
    NEXUS_SecurityKeyladderID keyladderID;
 NEXUS_SecurityKeyGenCmdID keyGenCmdID;
    NEXUS_SecurityKeyladderType keyladderType;
 NEXUS_SecurityKeyLadderSelect keyLadderSelect;
 _Bool rootKeySwap;
    NEXUS_SecurityRootKeySrc rootKeySrc;
    NEXUS_SecuritySwizzleType swizzleType;
    NEXUS_SecurityKeyType keyEntryType;
    NEXUS_SecurityKeyIVType keyDestIVType;
    NEXUS_SecurityAlgorithmConfigDestination dest;
    NEXUS_SecurityOperation operation;
    NEXUS_SecurityOperation operationKey2;
    _Bool bASKMMode;
    NEXUS_SecurityGlobalKeyOwnerID globalKeyOwnerId;
 unsigned char askmGlobalKeyIndex;
    NEXUS_SecurityKeyTweak keyTweakOp;
 int globalKeyVersion;
 _Bool bkeyGenBlocked;
    NEXUS_SecurityCustomerSubMode custSubMode;
    NEXUS_SecurityVirtualKeyladderID virtualKeyLadderID;
    NEXUS_SecurityKeyMode keyMode;
    NEXUS_SecuritySessionKeyOp sessionKeyOp;
    unsigned char cusKeyL;
    unsigned char cusKeyH;
    unsigned char cusKeyVarL;
    unsigned char cusKeyVarH;
    struct
    {
        _Bool askmConfigurationEnable;
        NEXUS_SecurityOtpId otpId;
        unsigned int caVendorId;
        unsigned int moduleID;
        NEXUS_SecurityMaskKey maskKeySelect;
    } sage;
    _Bool cusKeySwizzle0aEnable;
    NEXUS_SecuritySwizzle0aType cusKeySwizzle0aType;
    unsigned int cusKeySwizzle0aVer;
    unsigned char keyData[32];
    unsigned int keySize;
    _Bool bSwapAESKey;
    _Bool bRouteKey;
 NEXUS_SecurityHWKLLenSelect hwklLen;
 NEXUS_SecurityAlgorithm hwklDestAlg;
 _Bool hwklVistaKeyGen;
    unsigned char actCode[16];
    struct
    {
        _Bool reset;
        NEXUS_SecurityPKSMInitState initState;
        unsigned int cycle;
    } pksm;
    _Bool applyKeyContribution;
    NEXUS_SecurityVirtualKeyladderID sourceDupleKeyLadderId;
} NEXUS_SecurityEncryptedSessionKey;
typedef struct NEXUS_SecurityEncryptedControlWord
{
    NEXUS_SecurityKeyTweak keyTweakOp;
    _Bool protectionKeyIvSource;
 NEXUS_SecurityClientType client;
    NEXUS_SecurityKeyladderID keyladderID;
 NEXUS_SecurityKeyGenCmdID keyGenCmdID;
    NEXUS_SecurityKeyladderType keyladderType;
 NEXUS_SecurityKeyLadderSelect keyLadderSelect;
 _Bool rootKeySwap;
    NEXUS_SecurityRootKeySrc rootKeySrc;
    NEXUS_SecurityKeyType keyEntryType;
    NEXUS_SecurityKeyIVType keyDestIVType;
    NEXUS_SecurityAlgorithmConfigDestination dest;
    NEXUS_SecuritySwizzleType swizzleType;
    _Bool bASKMMode;
 _Bool bkeyGenBlocked;
    NEXUS_SecurityCustomerSubMode custSubMode;
    NEXUS_SecurityVirtualKeyladderID virtualKeyLadderID;
    NEXUS_SecurityKeyMode keyMode;
    NEXUS_SecurityAlgorithmScPolarity sc01Polarity[NEXUS_SecurityPacketType_eMax];
 NEXUS_SecurityAlgorithmScPolarity sc01GlobalMapping;
    unsigned int keySize;
    unsigned char keyData[32];
    NEXUS_SecurityOperation operation;
    _Bool bSwapAESKey;
    _Bool bRouteKey;
 NEXUS_SecurityHWKLLenSelect hwklLen;
 NEXUS_SecurityAlgorithm hwklDestAlg;
    unsigned char actCode[16];
 NEXUS_SecurityKeyLayer keylayer;
    _Bool applyKeyContribution;
    NEXUS_SecurityVirtualKeyladderID sourceDupleKeyLadderId;
} NEXUS_SecurityEncryptedControlWord;
typedef NEXUS_SecurityEncryptedControlWord NEXUS_SecurityEncryptedKey;
typedef struct NEXUS_SecurityKLProcOutParm
{
    NEXUS_SecurityVirtualKeyladderID virtualKeyLadderID;
    unsigned int procInLen;
 unsigned char procIn[16];
} NEXUS_SecurityKLProcOutParm;
typedef struct NEXUS_SecurityKLProcOutOutput
{
    unsigned int procOutLen;
 unsigned char procOut[32];
} NEXUS_SecurityKLProcOutOutput;
void NEXUS_Security_GetDefaultSessionKeySettings(
    NEXUS_SecurityEncryptedSessionKey *pSettings
    );
NEXUS_Error NEXUS_Security_GenerateSessionKey(
    NEXUS_KeySlotHandle keyHandle,
    const NEXUS_SecurityEncryptedSessionKey *pSessionKey
    );
void NEXUS_Security_GetDefaultControlWordSettings(
    NEXUS_SecurityEncryptedControlWord *pSettings
    );
NEXUS_Error NEXUS_Security_GenerateControlWord(
    NEXUS_KeySlotHandle keyHandle,
    const NEXUS_SecurityEncryptedControlWord *pCW
    );
NEXUS_Error NEXUS_Security_GenerateKey5(
    NEXUS_KeySlotHandle keyHandle,
    const NEXUS_SecurityEncryptedControlWord *pCW
    );
typedef struct NEXUS_SecurityVKLSettings
{
    NEXUS_SecurityCustomerSubMode custSubMode;
 NEXUS_SecurityClientType client;
 _Bool newVKLCustSubModeAssoc;
} NEXUS_SecurityVKLSettings;
void NEXUS_Security_GetDefaultVKLSettings(
    NEXUS_SecurityVKLSettings *pVKLSettings
    );
NEXUS_VirtualKeyLadderHandle NEXUS_Security_AllocateVKL(
    const NEXUS_SecurityVKLSettings *pVKLReqSettings
    );
void NEXUS_Security_FreeVKL(
 NEXUS_VirtualKeyLadderHandle vklHandle
 );
typedef struct NEXUS_VirtualKeyLadderInfo
{
 NEXUS_SecurityVirtualKeyladderID vkl;
    NEXUS_SecurityCustomerSubMode custSubMode;
 NEXUS_SecurityClientType client;
} NEXUS_VirtualKeyLadderInfo;
void NEXUS_Security_GetVKLInfo(
 NEXUS_VirtualKeyLadderHandle vklHandle,
 NEXUS_VirtualKeyLadderInfo *pVKLInfo
 );
NEXUS_Error NEXUS_Security_GenerateNextLayerKey(
    NEXUS_KeySlotHandle keyHandle,
    const NEXUS_SecurityEncryptedControlWord * pCW
    );
NEXUS_Error NEXUS_Security_GenerateProcOut(
    NEXUS_KeySlotHandle keyHandle,
    const NEXUS_SecurityKLProcOutParm *inProcOutParm,
    NEXUS_SecurityKLProcOutOutput *outProcOut
    );
typedef enum
{
    NEXUS_SecurityKeyLadderAlgorithm_3Des,
    NEXUS_SecurityKeyLadderAlgorithm_Aes,
    NEXUS_SecurityKeyLadderAlgorithm_eMax
}NEXUS_SecurityKeyLadderAlgorithm;
typedef struct NEXUS_SecurityChallengeResponseParm
{
 NEXUS_SecurityRootKeySrc otpKeyId;
 NEXUS_SecurityVirtualKeyladderID vkl;
 NEXUS_SecurityKeyLadderAlgorithm kladMode;
    unsigned challengeSize;
    unsigned char data[16];
}NEXUS_SecurityChallengeResponseParm;
typedef struct NEXUS_SecurityChallengeResponseOutput
{
    unsigned responseSize;
    unsigned char data[16];
}NEXUS_SecurityChallengeResponseOutput;
NEXUS_Error NEXUS_SecurityChallengeResponse(
    const NEXUS_SecurityChallengeResponseParm *crParm,
    NEXUS_SecurityChallengeResponseOutput *crOutput
    );
typedef struct NEXUS_SecurityRaveCtrlSettings
{
    _Bool bEnableWriteIMem;
    _Bool bEnableReadIMem;
    _Bool bEnableReadDMem;
    _Bool bRAVEEncryptionBypass;
    _Bool bDisableClear;
} NEXUS_SecurityRaveCtrlSettings;
NEXUS_Error NEXUS_Security_RaveControl(
    const NEXUS_SecurityRaveCtrlSettings *pSettings
    );
typedef struct NEXUS_SecurityDMABypassSettings
{
    _Bool bDMAXPTPacketBypassEnable;
    _Bool bNMAPacketBypassEnable;
    _Bool bDMAM2MPacketBypassEnable;
} NEXUS_SecurityDMABypassSettings;
NEXUS_Error NEXUS_Security_DMABypassControl(
    const NEXUS_SecurityDMABypassSettings *pSettings
    );
typedef struct NEXUS_SecurityM2MEndianSwapSettings
{
    _Bool bCBCMACDataInSwapEnable;
    _Bool bCBCMACDataOutSwapEnable;
    _Bool bCBCMACKeySwapEnable;
} NEXUS_SecurityM2MEndianSwapSettings;
NEXUS_Error NEXUS_Security_M2MEndianSwapControl(
    const NEXUS_SecurityM2MEndianSwapSettings *pSettings
    );
typedef struct NEXUS_SecurityForceSCSettings
{
    _Bool bBandSelect_PB;
    unsigned char bandNumber;
    _Bool bSCForceEnAll;
    _Bool bSCForceEnNZ;
    unsigned char SCForceEnValue;
} NEXUS_SecurityForceSCSettings;
NEXUS_Error NEXUS_Security_ForceSCControl(
    const NEXUS_SecurityForceSCSettings *pSettings
    );
typedef struct NEXUS_SecurityXPTM2MStatusOutput
{
    uint32_t unM2MSecurityErrStatus;
    uint32_t unXPTSecurityErrStatus;
} NEXUS_SecurityXPTM2MStatusOutput;
NEXUS_Error NEXUS_Security_XPTM2MStatusQuery(
    NEXUS_SecurityXPTM2MStatusOutput *pStatusQuery
    );
typedef enum NEXUS_SecurityPCIArchType
{
    NEXUS_SecurityPCIArchType_eNonPCIWin,
    NEXUS_SecurityPCIArchType_ePCIWin,
    NEXUS_SecurityPCIArchType_ePCIeWin,
    NEXUS_SecurityPCIArchType_eMax
} NEXUS_SecurityPCIArchType;
typedef enum NEXUS_SecurityArchSelect
{
    NEXUS_SecurityArchSelect_eSel00,
    NEXUS_SecurityArchSelect_eSel01,
    NEXUS_SecurityArchSelect_eSel02,
    NEXUS_SecurityArchSelect_eSel03,
    NEXUS_SecurityArchSelect_eMax
} NEXUS_SecurityArchSelect;
typedef enum NEXUS_SecurityDRAMSelect
{
    NEXUS_SecurityDRAMSelect_eSel00,
    NEXUS_SecurityDRAMSelect_eSel01,
    NEXUS_SecurityDRAMSelect_eMax
} NEXUS_SecurityDRAMSelect;
typedef struct NEXUS_SecuritySRegionSettings
{
    uint32_t sRegStartAddress;
    uint32_t sRegEndAddress;
    NEXUS_SecurityArchSelect archType;
    NEXUS_SecurityPCIArchType pciArchType;
    NEXUS_SecurityDRAMSelect DRAMType;
} NEXUS_SecuritySRegionSettings;
NEXUS_Error NEXUS_Security_DefineSecureRegion(
    const NEXUS_SecuritySRegionSettings *pSettings
    );
typedef struct NEXUS_SecurityPciEMaxWindowSizeSettings
{
    NEXUS_SecurityVirtualKeyladderID vkl;
    uint8_t signedCommand[(256)];
    unsigned signedCommandLength;
} NEXUS_SecurityPciEMaxWindowSizeSettings;
typedef NEXUS_SecurityPciEMaxWindowSizeSettings NEXUS_SecurityPciEMaxWindowSizeSettings_t;
void NEXUS_Security_GetDefaultPciEMaxWindowSizeSettings(
    NEXUS_SecurityPciEMaxWindowSizeSettings *pConfig
    );
NEXUS_Error NEXUS_Security_SetPciEMaxWindowSize (
    const NEXUS_SecurityPciEMaxWindowSizeSettings *pConfig
    );
NEXUS_Error NEXUS_Security_SetPciERestrictedRange(
                           NEXUS_Addr baseOffset,
                           size_t size,
                           unsigned index
                           );
typedef enum NEXUS_SecurityAVDType
{
    NEXUS_SecurityAVDType_eVDEC0 = 0,
    NEXUS_SecurityAVDType_eSVD = NEXUS_SecurityAVDType_eVDEC0,
    NEXUS_SecurityAVDType_eAVD,
    NEXUS_SecurityAVDType_eVICE = 2,
    NEXUS_SecurityAVDType_eVICE1 = 3,
    NEXUS_SecurityAVDType_eVDEC1 = 4,
    NEXUS_SecurityAVDType_eVDEC2 = 5,
    NEXUS_SecurityAVDType_eMax
} NEXUS_SecurityAVDType;
typedef struct NEXUS_SecurityAVDSRegRangeSettings
{
    NEXUS_SecurityVirtualKeyladderID vkl;
    NEXUS_SecurityKeySource keyLayer;
    NEXUS_SecurityAVDType VDECId;
    uint32_t nRange;
    uint32_t loRange[(8)];
    uint32_t hiRange[(8)];
    unsigned char signature[(32)];
} NEXUS_SecurityAVDSRegRangeSettings;
NEXUS_Error NEXUS_Security_AVDSRegistersSetUp(
    const NEXUS_SecurityAVDSRegRangeSettings *pSettings
    );
typedef struct NEXUS_SecurityAVDSRegModifySettings
{
    NEXUS_SecurityVirtualKeyladderID vkl;
    NEXUS_SecurityKeySource keyLayer;
    NEXUS_SecurityAVDType avdID;
    uint32_t nAVDReg;
    uint32_t regAddr[(8)];
    uint32_t regVal[(8)];
    unsigned char signature[(32)];
} NEXUS_SecurityAVDSRegModifySettings;
NEXUS_Error NEXUS_Security_AVDSRegistersModify(
    const NEXUS_SecurityAVDSRegModifySettings *pSettings
    );
typedef enum NEXUS_DisplayAspectRatio
{
    NEXUS_DisplayAspectRatio_eAuto,
    NEXUS_DisplayAspectRatio_e4x3,
    NEXUS_DisplayAspectRatio_e16x9,
    NEXUS_DisplayAspectRatio_eSar,
    NEXUS_DisplayAspectRatio_eMax
} NEXUS_DisplayAspectRatio;
typedef enum NEXUS_VideoDac
{
    NEXUS_VideoDac_eNone,
    NEXUS_VideoDac_e0,
    NEXUS_VideoDac_e1,
    NEXUS_VideoDac_e2,
    NEXUS_VideoDac_e3,
    NEXUS_VideoDac_e4,
    NEXUS_VideoDac_e5,
    NEXUS_VideoDac_e6,
    NEXUS_VideoDac_eMax
} NEXUS_VideoDac;
typedef struct NEXUS_Display *NEXUS_DisplayHandle;
typedef struct NEXUS_VideoWindow *NEXUS_VideoWindowHandle;
typedef enum NEXUS_AnalogVideoChannel
{
    NEXUS_AnalogVideoChannel_eY,
    NEXUS_AnalogVideoChannel_ePr,
    NEXUS_AnalogVideoChannel_ePb,
    NEXUS_AnalogVideoChannel_eR,
    NEXUS_AnalogVideoChannel_eG,
    NEXUS_AnalogVideoChannel_eB,
    NEXUS_AnalogVideoChannel_eLuma,
    NEXUS_AnalogVideoChannel_eChroma,
    NEXUS_AnalogVideoChannel_eComposite,
    NEXUS_AnalogVideoChannel_eScartR,
    NEXUS_AnalogVideoChannel_eScartG,
    NEXUS_AnalogVideoChannel_eScartB,
    NEXUS_AnalogVideoChannel_eScartY,
    NEXUS_AnalogVideoChannel_eScartPr,
    NEXUS_AnalogVideoChannel_eScartPb,
    NEXUS_AnalogVideoChannel_eScartSync,
    NEXUS_AnalogVideoChannel_eScartComposite,
    NEXUS_AnalogVideoChannel_eScartLuma,
    NEXUS_AnalogVideoChannel_eScartChroma
} NEXUS_AnalogVideoChannel;
typedef enum NEXUS_CompositorBlendFactor
{
    NEXUS_CompositorBlendFactor_eZero = 0,
    NEXUS_CompositorBlendFactor_eOne,
    NEXUS_CompositorBlendFactor_eSourceAlpha,
    NEXUS_CompositorBlendFactor_eInverseSourceAlpha,
    NEXUS_CompositorBlendFactor_eConstantAlpha,
    NEXUS_CompositorBlendFactor_eInverseConstantAlpha,
    NEXUS_CompositorBlendFactor_eMax
} NEXUS_CompositorBlendFactor;
typedef struct NEXUS_AttenuationRgbSettings
{
    int32_t attenuationR;
    int32_t attenuationG;
    int32_t attenuationB;
    int32_t offsetR;
    int32_t offsetG;
    int32_t offsetB;
} NEXUS_AttenuationRgbSettings;
typedef enum NEXUS_VideoWindowContentMode
{
    NEXUS_VideoWindowContentMode_eZoom,
    NEXUS_VideoWindowContentMode_eBox,
    NEXUS_VideoWindowContentMode_ePanScan,
    NEXUS_VideoWindowContentMode_eFull,
    NEXUS_VideoWindowContentMode_eFullNonLinear,
    NEXUS_VideoWindowContentMode_ePanScanWithoutCorrection,
    NEXUS_VideoWindowContentMode_eMax
} NEXUS_VideoWindowContentMode;
typedef struct NEXUS_GraphicsColorSettings
{
    int16_t contrast;
    int16_t saturation;
    int16_t hue;
    int16_t brightness;
} NEXUS_GraphicsColorSettings;
typedef enum NEXUS_VideoWindowFilterMode
{
    NEXUS_VideoWindowFilterMode_eDisable,
    NEXUS_VideoWindowFilterMode_eBypass,
    NEXUS_VideoWindowFilterMode_eEnable,
    NEXUS_VideoWindowFilterMode_eMax
} NEXUS_VideoWindowFilterMode;
typedef struct NEXUS_VideoWindowFilterSettings
{
    NEXUS_VideoWindowFilterMode mode;
    int level;
} NEXUS_VideoWindowFilterSettings;
typedef struct NEXUS_VideoWindowDnrSettings
{
    NEXUS_VideoWindowFilterSettings mnr;
    NEXUS_VideoWindowFilterSettings bnr;
    NEXUS_VideoWindowFilterSettings dcr;
    unsigned qp;
} NEXUS_VideoWindowDnrSettings;
typedef struct NEXUS_VideoWindowAnrSettings
{
    NEXUS_VideoWindowFilterSettings anr;
    NEXUS_PixelFormat pixelFormat;
} NEXUS_VideoWindowAnrSettings;
typedef enum NEXUS_AfdMode {
    NEXUS_AfdMode_eDisabled = 0,
    NEXUS_AfdMode_eStream,
    NEXUS_AfdMode_eUser,
    NEXUS_AfdMode_eMax
} NEXUS_AfdMode;
typedef enum NEXUS_AfdClip
{
    NEXUS_AfdClip_eNominal = 0,
    NEXUS_AfdClip_eOptionalLevel1,
    NEXUS_AfdClip_eOptionalLevel2,
    NEXUS_AfdClip_eMax
} NEXUS_AfdClip;
typedef struct NEXUS_VideoWindowAfdSettings
{
    NEXUS_AfdMode mode;
    NEXUS_AfdClip clip;
    uint32_t userValue;
} NEXUS_VideoWindowAfdSettings;
typedef enum NEXUS_GraphicsFilterCoeffs
{
    NEXUS_GraphicsFilterCoeffs_eAuto,
    NEXUS_GraphicsFilterCoeffs_ePointSample,
    NEXUS_GraphicsFilterCoeffs_eBilinear,
    NEXUS_GraphicsFilterCoeffs_eAnisotropic,
    NEXUS_GraphicsFilterCoeffs_eSharp,
    NEXUS_GraphicsFilterCoeffs_eMax
} NEXUS_GraphicsFilterCoeffs;
typedef enum NEXUS_DisplayMacrovisionType
{
    NEXUS_DisplayMacrovisionType_eNone,
    NEXUS_DisplayMacrovisionType_eAgcOnly,
    NEXUS_DisplayMacrovisionType_eAgc2Lines,
    NEXUS_DisplayMacrovisionType_eAgc4Lines,
    NEXUS_DisplayMacrovisionType_eCustom,
    NEXUS_DisplayMacrovisionType_eAgcOnlyRgb,
    NEXUS_DisplayMacrovisionType_eAgc2LinesRgb,
    NEXUS_DisplayMacrovisionType_eAgc4LinesRgb,
    NEXUS_DisplayMacrovisionType_eTest01,
    NEXUS_DisplayMacrovisionType_eTest02,
    NEXUS_DisplayMacrovisionType_eMax
} NEXUS_DisplayMacrovisionType;
typedef struct NEXUS_DisplayMacrovisionTables
{
    uint8_t cpcTable[2];
    uint8_t cpsTable[33];
} NEXUS_DisplayMacrovisionTables;
typedef struct NEXUS_VideoInputCrcData
{
    uint32_t idrPictureId;
    uint32_t pictureOrderCount;
    uint32_t isField;
    uint32_t crc[6];
} NEXUS_VideoInputCrcData;
typedef struct NEXUS_DisplayCrcData
{
    struct {
        uint32_t luma;
        uint32_t cb;
        uint32_t cr;
    } cmp;
} NEXUS_DisplayCrcData;
typedef struct NEXUS_VideoWindowGameModeDelay
{
    _Bool enable;
    _Bool forceCoarseTrack;
    uint32_t bufferDelayTarget;
    uint32_t bufferDelayTolerance;
} NEXUS_VideoWindowGameModeDelay;
typedef enum NEXUS_VideoWindowGameMode
{
    NEXUS_VideoWindowGameMode_eOff,
    NEXUS_VideoWindowGameMode_e5Fields_2Delay,
    NEXUS_VideoWindowGameMode_e5Fields_1Delay,
    NEXUS_VideoWindowGameMode_e5Fields_0Delay,
    NEXUS_VideoWindowGameMode_e5Fields_ForceSpatial,
    NEXUS_VideoWindowGameMode_e4Fields_2Delay,
    NEXUS_VideoWindowGameMode_e4Fields_1Delay,
    NEXUS_VideoWindowGameMode_e4Fields_0Delay,
    NEXUS_VideoWindowGameMode_e4Fields_ForceSpatial,
    NEXUS_VideoWindowGameMode_e3Fields_2Delay,
    NEXUS_VideoWindowGameMode_e3Fields_1Delay,
    NEXUS_VideoWindowGameMode_e3Fields_0Delay,
    NEXUS_VideoWindowGameMode_e3Fields_ForceSpatial,
    NEXUS_VideoWindowGameMode_eMax
} NEXUS_VideoWindowGameMode;
typedef enum NEXUS_MadPqEnhancement
{
    NEXUS_MadPqEnhancement_eAuto,
    NEXUS_MadPqEnhancement_eOff,
    NEXUS_MadPqEnhancement_eOn,
    NEXUS_MadPqEnhancement_eMax
} NEXUS_MadPqEnhancement;
typedef struct NEXUS_VideoWindowMadSettings
{
    _Bool deinterlace;
    _Bool enable32Pulldown;
    _Bool enable22Pulldown;
    NEXUS_VideoWindowGameMode gameMode;
    NEXUS_PixelFormat pixelFormat;
    _Bool shrinkWidth;
    NEXUS_MadPqEnhancement pqEnhancement;
} NEXUS_VideoWindowMadSettings;
typedef enum NEXUS_ScalerCaptureBias
{
    NEXUS_ScalerCaptureBias_eAuto,
    NEXUS_ScalerCaptureBias_eScalerBeforeCapture,
    NEXUS_ScalerCaptureBias_eScalerAfterCapture
} NEXUS_ScalerCaptureBias;
typedef struct NEXUS_VideoWindowScalerSettings
{
    _Bool nonLinearScaling;
    uint32_t nonLinearSourceWidth;
    uint32_t nonLinearScalerOutWidth;
    struct {
        NEXUS_ScalerCaptureBias bias;
        uint32_t delta;
    } bandwidthEquationParams;
    _Bool verticalDejagging;
    _Bool horizontalLumaDeringing;
    _Bool verticalLumaDeringing;
    _Bool horizontalChromaDeringing;
    _Bool verticalChromaDeringing;
} NEXUS_VideoWindowScalerSettings;
typedef enum NEXUS_DeinterlacerMode
{
    NEXUS_DeinterlacerMode_eNone,
    NEXUS_DeinterlacerMode_eBestQuality,
    NEXUS_DeinterlacerMode_eLowestLatency,
    NEXUS_DeinterlacerMode_eMax
} NEXUS_DeinterlacerMode;
typedef struct NEXUS_DisplayMemConfig
{
    NEXUS_VideoFormat maxFormat;
    struct {
        _Bool used;
        NEXUS_DeinterlacerMode deinterlacer;
        _Bool support3d;
        _Bool capture;
        _Bool convertAnyFrameRate;
        _Bool precisionLipSync;
        _Bool smoothScaling;
        unsigned userCaptureBufferCount;
        _Bool mtg;
        NEXUS_SecureVideo secure;
    } window[2];
} NEXUS_DisplayMemConfig;
typedef enum NEXUS_VideoDacDetection
{
    NEXUS_VideoDacDetection_eAuto,
    NEXUS_VideoDacDetection_eOff,
    NEXUS_VideoDacDetection_eOn,
    NEXUS_VideoDacDetection_eMax
} NEXUS_VideoDacDetection;
typedef enum NEXUS_ComponentOutputSyncType
{
    NEXUS_ComponentOutputSyncType_eOnlyY,
    NEXUS_ComponentOutputSyncType_eAllChannels,
    NEXUS_ComponentOutputSyncType_eMax
} NEXUS_ComponentOutputSyncType;
typedef struct NEXUS_DisplayModuleSettings {
    NEXUS_DisplayBufferTypeSettings fullHdBuffers;
    NEXUS_DisplayBufferTypeSettings hdBuffers;
    NEXUS_DisplayBufferTypeSettings sdBuffers;
    struct {
        unsigned numDisplays, numWindowsPerDisplay;
    } legacy;
    NEXUS_DisplayHeapSettings displayHeapSettings[24];
    unsigned videoWindowHeapIndex[7][2];
    unsigned deinterlacerHeapIndex[7][2];
    struct {
        unsigned videoWindowHeapIndex[7][2];
        unsigned deinterlacerHeapIndex[7][2];
    } secure;
    unsigned primaryDisplayHeapIndex;
    unsigned rdcHeapIndex;
    struct {
        unsigned cmpHeapIndex[7];
        unsigned gfdHeapIndex[7];
        unsigned vecHeapIndex[2];
    } cfc;
    _Bool dropFrame;
    uint32_t dacBandGapAdjust[7];
    NEXUS_VideoDacDetection dacDetection;
    struct {
        _Bool allowTeletext;
        _Bool allowVps;
        _Bool allowGemStar;
        _Bool allowCgmsB;
        _Bool allowAmol;
        _Bool tteShiftDirMsb2Lsb;
        unsigned ccir656InputBufferSize;
    } vbi;
    _Bool vecSwap;
    _Bool handleDynamicRts;
    unsigned configurationId;
    _Bool disableFrc;
    int encoderTgMapping[6];
    struct {
        struct {
            unsigned memcIndex;
            unsigned secondaryMemcIndex;
        } mfd, vfd;
    } videoImageInput[6];
    NEXUS_DisplayMemConfig memConfig[7];
    struct {
        _Bool mosaic;
        _Bool hdDvi;
        _Bool ccir656;
    } memconfig;
    NEXUS_ComponentOutputSyncType componentOutputSyncType;
} NEXUS_DisplayModuleSettings;
typedef enum NEXUS_Ccir656VbiFormat
{
    NEXUS_Ccir656VbiFormat_eSaa7113 = 0,
    NEXUS_Ccir656VbiFormat_eModifiedSaa7113,
    NEXUS_Ccir656VbiFormat_eSaa7114,
    NEXUS_Ccir656VbiFormat_eSaa7114A,
    NEXUS_Ccir656VbiFormat_eSaa7114B,
    NEXUS_Ccir656VbiFormat_eSaa7114C,
    NEXUS_Ccir656VbiFormat_eSaa7115,
    NEXUS_Ccir656VbiFormat_eSmpte291,
    NEXUS_Ccir656VbiFormat_eMax
} NEXUS_Ccir656VbiFormat;
typedef struct NEXUS_Ccir656InputSettings {
    NEXUS_VideoFormat format;
    struct {
        NEXUS_Ccir656VbiFormat format;
        unsigned bufferSize;
        _Bool longHeader;
        _Bool brokenDataCount;
        NEXUS_CallbackDesc dataReady;
    } vbi;
} NEXUS_Ccir656InputSettings;
typedef struct NEXUS_Ccir656Input *NEXUS_Ccir656InputHandle;
void NEXUS_Ccir656Input_GetDefaultSettings(
    NEXUS_Ccir656InputSettings *pSettings
    );
NEXUS_Ccir656InputHandle NEXUS_Ccir656Input_Open(
    unsigned index,
    const NEXUS_Ccir656InputSettings *pSettings
    );
void NEXUS_Ccir656Input_Close(
    NEXUS_Ccir656InputHandle ccir656Input
    );
void NEXUS_Ccir656Input_GetSettings(
    NEXUS_Ccir656InputHandle ccir656Input,
    NEXUS_Ccir656InputSettings *pSettings
    );
NEXUS_Error NEXUS_Ccir656Input_SetSettings(
    NEXUS_Ccir656InputHandle ccir656Input,
    const NEXUS_Ccir656InputSettings *pSettings
    );
NEXUS_VideoInputHandle NEXUS_Ccir656Input_GetConnector(
    NEXUS_Ccir656InputHandle ccir656Input
    );
typedef struct NEXUS_Ccir656InputVbiHeader
{
    _Bool topField;
    uint8_t dataId;
    uint8_t secondId;
    unsigned payload;
} NEXUS_Ccir656InputVbiHeader;
NEXUS_Error NEXUS_Ccir656Input_GetBuffer(
    NEXUS_Ccir656InputHandle ccir656Input,
    void **pBuffer,
    unsigned *pSize
    );
NEXUS_Error NEXUS_Ccir656Input_ReadComplete(
    NEXUS_Ccir656InputHandle ccir656Input,
    unsigned sizeConsumed
    );
void NEXUS_Ccir656Input_Flush(
    NEXUS_Ccir656InputHandle ccir656Input
    );
typedef struct NEXUS_Ccir656Output *NEXUS_Ccir656OutputHandle;
typedef struct NEXUS_Ccir656OutputSettings
{
    struct {
        int dummy;
    } vbi;
} NEXUS_Ccir656OutputSettings;
void NEXUS_Ccir656Output_GetDefaultSettings(
    NEXUS_Ccir656OutputSettings *pSettings
    );
NEXUS_Ccir656OutputHandle NEXUS_Ccir656Output_Open(
    unsigned index,
    const NEXUS_Ccir656OutputSettings *pSettings
    );
void NEXUS_Ccir656Output_Close(
    NEXUS_Ccir656OutputHandle output
    );
void NEXUS_Ccir656Output_GetSettings(
    NEXUS_Ccir656OutputHandle output,
    NEXUS_Ccir656OutputSettings *pSettings
    );
NEXUS_Error NEXUS_Ccir656Output_SetSettings(
    NEXUS_Ccir656OutputHandle output,
    const NEXUS_Ccir656OutputSettings *pSettings
    );
NEXUS_VideoOutputHandle NEXUS_Ccir656Output_GetConnector(
    NEXUS_Ccir656OutputHandle output
    );
typedef struct NEXUS_Cec *NEXUS_CecHandle;
typedef enum NEXUS_CecDeviceType
{
 NEXUS_CecDeviceType_eTv = 0,
 NEXUS_CecDeviceType_eRecordingDevice,
 NEXUS_CecDeviceType_eReserved,
 NEXUS_CecDeviceType_eTuner,
 NEXUS_CecDeviceType_ePlaybackDevice,
 NEXUS_CecDeviceType_eAudioSystem,
 NEXUS_CecDeviceType_ePureCecSwitch,
 NEXUS_CecDeviceType_eVideoProcessor,
 NEXUS_CecDeviceType_eMax
} NEXUS_CecDeviceType;
typedef enum NEXUS_CecController
{
 NEXUS_CecController_eTx,
 NEXUS_CecController_eRx,
 NEXUS_CecController_eMax
} NEXUS_CecController;
typedef struct NEXUS_CecSettings
{
 _Bool enabled;
 NEXUS_CallbackDesc messageTransmittedCallback;
 NEXUS_CallbackDesc messageReceivedCallback;
    NEXUS_CallbackDesc logicalAddressAcquiredCallback;
    _Bool disableLogicalAddressPolling;
    uint8_t logicalAddress;
 uint8_t physicalAddress[2];
 NEXUS_CecDeviceType deviceType;
 NEXUS_CecController cecController;
} NEXUS_CecSettings;
void NEXUS_Cec_GetDefaultSettings(
 NEXUS_CecSettings *pSettings
 );
NEXUS_CecHandle NEXUS_Cec_Open(
 unsigned index,
 const NEXUS_CecSettings *pSettings
 );
void NEXUS_Cec_Close(
 NEXUS_CecHandle handle
 );
void NEXUS_Cec_GetSettings(
 NEXUS_CecHandle handle,
 NEXUS_CecSettings *pSettings
 );
NEXUS_Error NEXUS_Cec_SetSettings(
 NEXUS_CecHandle handle,
 const NEXUS_CecSettings *pSettings
 );
typedef struct NEXUS_CecStatus
{
 _Bool ready;
 uint8_t physicalAddress[2];
    uint8_t logicalAddress;
 NEXUS_CecDeviceType deviceType;
 _Bool messageReceived;
 _Bool messageTransmitPending;
 _Bool transmitMessageAcknowledged;
    unsigned cecVersion;
} NEXUS_CecStatus;
NEXUS_Error NEXUS_Cec_GetStatus(
 NEXUS_CecHandle handle,
 NEXUS_CecStatus *pStatus
 );
typedef struct NEXUS_CecMessage
{
 uint8_t initiatorAddr;
 uint8_t destinationAddr;
 uint8_t buffer[16];
 unsigned length;
} NEXUS_CecMessage;
typedef struct NEXUS_CecReceivedMessage
{
 struct {
  _Bool receivedMessageAcknowledged;
  _Bool endOfMessage;
 } receivedStatus;
 NEXUS_CecMessage data;
} NEXUS_CecReceivedMessage;
NEXUS_Error NEXUS_Cec_ReceiveMessage(
 NEXUS_CecHandle handle,
 NEXUS_CecReceivedMessage *pReceivedMessage
 );
void NEXUS_Cec_GetDefaultMessageData(
 NEXUS_CecMessage *pMessage
 );
NEXUS_Error NEXUS_Cec_TransmitMessage(
 NEXUS_CecHandle handle,
 const NEXUS_CecMessage *pMessage
 );
typedef struct NEXUS_CecModuleSettings
{
 _Bool enabled;
} NEXUS_CecModuleSettings;
void NEXUS_CecModule_GetDefaultSettings(
 NEXUS_CecModuleSettings *pSettings
 );
NEXUS_ModuleHandle NEXUS_CecModule_Init(
 const NEXUS_CecModuleSettings *pSettings
 );
void NEXUS_CecModule_Uninit(void);
typedef struct NEXUS_ComponentOutput *NEXUS_ComponentOutputHandle;
typedef enum NEXUS_ComponentOutputType
{
    NEXUS_ComponentOutputType_eRGB,
    NEXUS_ComponentOutputType_eYPrPb
} NEXUS_ComponentOutputType;
typedef struct NEXUS_ComponentOutputSettings
{
    NEXUS_ComponentOutputType type;
    union {
        struct {
            NEXUS_VideoDac dacY;
            NEXUS_VideoDac dacPr;
            NEXUS_VideoDac dacPb;
        } YPrPb;
        struct {
            NEXUS_VideoDac dacGreen;
            NEXUS_VideoDac dacRed;
            NEXUS_VideoDac dacBlue;
            NEXUS_VideoDac dacHSync;
            _Bool noSync;
        } RGB;
    } dacs;
    _Bool mpaaDecimationEnabled;
} NEXUS_ComponentOutputSettings;
void NEXUS_ComponentOutput_GetDefaultSettings(
    NEXUS_ComponentOutputSettings *pSettings
    );
NEXUS_ComponentOutputHandle NEXUS_ComponentOutput_Open(
    unsigned index,
    const NEXUS_ComponentOutputSettings *pSettings
    );
void NEXUS_ComponentOutput_Close(
    NEXUS_ComponentOutputHandle output
    );
void NEXUS_ComponentOutput_GetSettings(
    NEXUS_ComponentOutputHandle output,
    NEXUS_ComponentOutputSettings *pSettings
    );
NEXUS_Error NEXUS_ComponentOutput_SetSettings(
    NEXUS_ComponentOutputHandle output,
    const NEXUS_ComponentOutputSettings *pSettings
    );
NEXUS_VideoOutputHandle NEXUS_ComponentOutput_GetConnector(
    NEXUS_ComponentOutputHandle output
    );
typedef struct NEXUS_CompositeOutput *NEXUS_CompositeOutputHandle;
typedef struct NEXUS_CompositeOutputSettings
{
    NEXUS_VideoDac dac;
} NEXUS_CompositeOutputSettings;
void NEXUS_CompositeOutput_GetDefaultSettings(
    NEXUS_CompositeOutputSettings *pSettings
    );
NEXUS_CompositeOutputHandle NEXUS_CompositeOutput_Open(
    unsigned index,
    const NEXUS_CompositeOutputSettings *pSettings
    );
void NEXUS_CompositeOutput_Close(
    NEXUS_CompositeOutputHandle output
    );
void NEXUS_CompositeOutput_GetSettings(
    NEXUS_CompositeOutputHandle output,
    NEXUS_CompositeOutputSettings *pSettings
    );
NEXUS_Error NEXUS_CompositeOutput_SetSettings(
    NEXUS_CompositeOutputHandle output,
    const NEXUS_CompositeOutputSettings *pSettings
    );
NEXUS_VideoOutputHandle NEXUS_CompositeOutput_GetConnector(
    NEXUS_CompositeOutputHandle composite
    );
typedef void *NEXUS_I2sMultiOutputHandle;
typedef unsigned NEXUS_SageModuleSettings;
typedef void *NEXUS_RfmHandle;
typedef void *NEXUS_HdmiDvoHandle;
typedef struct NEXUS_Surface *NEXUS_SurfaceHandle;
void NEXUS_Surface_GetDefaultCreateSettings(
    NEXUS_SurfaceCreateSettings *pCreateSettings
    );
NEXUS_SurfaceHandle NEXUS_Surface_Create(
    const NEXUS_SurfaceCreateSettings *pCreateSettings
    );
void NEXUS_Surface_Destroy(
    NEXUS_SurfaceHandle surface
    );
void NEXUS_Surface_GetCreateSettings(
    NEXUS_SurfaceHandle surface,
    NEXUS_SurfaceCreateSettings *pCreateSettings
    );
void NEXUS_Surface_GetStatus(
    NEXUS_SurfaceHandle surface,
    NEXUS_SurfaceStatus *pStatus
    );
NEXUS_Error NEXUS_Surface_GetMemory(
    NEXUS_SurfaceHandle surface,
    NEXUS_SurfaceMemory *pMemory
    );
void NEXUS_Surface_Flush(
    NEXUS_SurfaceHandle surface
    );
typedef struct NEXUS_SurfaceSettings
{
    _Bool autoFlush;
} NEXUS_SurfaceSettings;
NEXUS_Error NEXUS_Surface_SetSettings(
    NEXUS_SurfaceHandle surface,
    const NEXUS_SurfaceSettings *pSettings
    );
void NEXUS_Surface_GetSettings(
    NEXUS_SurfaceHandle surface,
    NEXUS_SurfaceSettings *pSettings
    );
NEXUS_Error NEXUS_Surface_InitPlaneAndPaletteOffset(
    NEXUS_SurfaceHandle surface,
    BM2MC_PACKET_Plane *pPlane,
    NEXUS_Addr *pPaletteOffset
    );
NEXUS_Error NEXUS_Surface_Lock(
        NEXUS_SurfaceHandle surface,
        void **ppMemory
        );
void NEXUS_Surface_Unlock(
        NEXUS_SurfaceHandle surface
        );
NEXUS_Error NEXUS_Surface_LockPalette(
        NEXUS_SurfaceHandle surface,
        void **ppMemory
        );
void NEXUS_Surface_UnlockPalette(
        NEXUS_SurfaceHandle surface
        );
NEXUS_Error NEXUS_Surface_LockPlaneAndPalette(
    NEXUS_SurfaceHandle surface,
    BM2MC_PACKET_Plane *pPlane,
    NEXUS_Addr *pPaletteOffset
    );
void NEXUS_Surface_UnlockPlaneAndPalette(
    NEXUS_SurfaceHandle surface
    );
void NEXUS_Surface_MarkDiscardable(
    NEXUS_SurfaceHandle surface
    );
void NEXUS_Surface_Destroy_driver(
    NEXUS_SurfaceHandle surface
    );
typedef struct NEXUS_SurfaceMemoryProperties
{
    NEXUS_MemoryBlockHandle pixelMemory;
    unsigned pixelMemoryOffset;
    NEXUS_MemoryBlockHandle paletteMemory;
    unsigned paletteMemoryOffset;
    _Bool pixelMemoryTransient;
    _Bool paletteMemoryTransient;
} NEXUS_SurfaceMemoryProperties;
void NEXUS_Surface_GetMemoryProperties(
    NEXUS_SurfaceHandle surface,
    NEXUS_SurfaceMemoryProperties *pProperties
    );
typedef struct NEXUS_DisplayCustomFormatSettings
{
    unsigned width;
    unsigned height;
    unsigned refreshRate;
    _Bool interlaced;
    NEXUS_DisplayAspectRatio aspectRatio;
    struct {
        unsigned x, y;
    } sampleAspectRatio;
    _Bool dropFrameAllowed;
} NEXUS_DisplayCustomFormatSettings;
void NEXUS_Display_GetDefaultCustomFormatSettings(
    NEXUS_DisplayCustomFormatSettings *pSettings
    );
NEXUS_Error NEXUS_Display_SetCustomFormatSettings(
    NEXUS_DisplayHandle display,
    NEXUS_VideoFormat format,
    const NEXUS_DisplayCustomFormatSettings *pSettings
    );
typedef enum NEXUS_DisplayType
{
    NEXUS_DisplayType_eAuto = 0,
    NEXUS_DisplayType_eLvds,
    NEXUS_DisplayType_eDvo,
    NEXUS_DisplayType_eBypass,
    NEXUS_DisplayType_eMax
} NEXUS_DisplayType;
typedef enum NEXUS_DisplayTimingGenerator
{
    NEXUS_DisplayTimingGenerator_ePrimaryInput,
    NEXUS_DisplayTimingGenerator_eSecondaryInput,
    NEXUS_DisplayTimingGenerator_eTertiaryInput,
    NEXUS_DisplayTimingGenerator_eHdmiDvo,
    NEXUS_DisplayTimingGenerator_e656Output,
    NEXUS_DisplayTimingGenerator_eEncoder,
    NEXUS_DisplayTimingGenerator_eAuto,
    NEXUS_DisplayTimingGenerator_eMax
} NEXUS_DisplayTimingGenerator;
typedef enum NEXUS_Display3DSourceBuffer {
    NEXUS_Display3DSourceBuffer_eDefault = 0,
    NEXUS_Display3DSourceBuffer_eLeft,
    NEXUS_Display3DSourceBuffer_eRight,
    NEXUS_Display3DSourceBuffer_eMax
} NEXUS_Display3DSourceBuffer;
typedef struct NEXUS_DisplaySettings
{
    NEXUS_DisplayType displayType;
    NEXUS_DisplayTimingGenerator timingGenerator;
    int vecIndex;
    NEXUS_VideoFormat format;
    NEXUS_DisplayAspectRatio aspectRatio;
    struct {
        unsigned x, y;
    } sampleAspectRatio;
    NEXUS_Timebase timebase;
    NEXUS_VideoInputHandle frameRateMaster;
    NEXUS_TristateEnable dropFrame;
    NEXUS_Pixel background;
    _Bool xvYccEnabled;
    NEXUS_DisplayHandle alignmentTarget;
    NEXUS_CallbackDesc vsyncCallback;
    struct {
        _Bool overrideOrientation;
        NEXUS_VideoOrientation orientation;
        NEXUS_Display3DSourceBuffer sourceBuffer;
    } display3DSettings;
    unsigned crcQueueSize;
} NEXUS_DisplaySettings;
typedef enum NEXUS_DisplayUpdateMode
{
    NEXUS_DisplayUpdateMode_eAuto,
    NEXUS_DisplayUpdateMode_eManual,
    NEXUS_DisplayUpdateMode_eNow
} NEXUS_DisplayUpdateMode;
NEXUS_Error NEXUS_DisplayModule_SetUpdateMode(
    NEXUS_DisplayUpdateMode updateMode
    );
void NEXUS_Display_GetDefaultSettings(
    NEXUS_DisplaySettings *pSettings
    );
NEXUS_DisplayHandle NEXUS_Display_Open(
    unsigned displayIndex,
    const NEXUS_DisplaySettings *pSettings
    );
void NEXUS_Display_Close(
    NEXUS_DisplayHandle display
    );
void NEXUS_Display_GetSettings(
    NEXUS_DisplayHandle display,
    NEXUS_DisplaySettings *pSettings
    );
NEXUS_Error NEXUS_Display_SetSettings(
    NEXUS_DisplayHandle display,
    const NEXUS_DisplaySettings *pSettings
    );
NEXUS_Error NEXUS_Display_AddOutput(
    NEXUS_DisplayHandle display,
    NEXUS_VideoOutputHandle output
    );
NEXUS_Error NEXUS_Display_RemoveOutput(
    NEXUS_DisplayHandle display,
    NEXUS_VideoOutputHandle output
    );
void NEXUS_Display_RemoveAllOutputs(
    NEXUS_DisplayHandle display
    );
typedef struct NEXUS_DisplayStatus
{
    unsigned refreshRate;
    unsigned numWindows;
    _Bool graphicsSupported;
    NEXUS_DisplayTimingGenerator timingGenerator;
} NEXUS_DisplayStatus;
NEXUS_Error NEXUS_Display_GetStatus(
    NEXUS_DisplayHandle display,
    NEXUS_DisplayStatus *pStatus
    );
typedef struct NEXUS_GraphicsSettings
{
    _Bool enabled;
    _Bool visible;
    _Bool antiflutterFilter;
    uint8_t alpha;
    unsigned zorder;
    _Bool chromakeyEnabled;
    NEXUS_Pixel lowerChromakey;
    NEXUS_Pixel upperChromakey;
    NEXUS_Rect position;
    NEXUS_Rect clip;
    NEXUS_CallbackDesc frameBufferCallback;
    NEXUS_CompositorBlendFactor sourceBlendFactor;
    NEXUS_CompositorBlendFactor destBlendFactor;
    uint8_t constantAlpha;
    NEXUS_GraphicsFilterCoeffs horizontalFilter;
    NEXUS_GraphicsFilterCoeffs verticalFilter;
    unsigned horizontalCoeffIndex;
    unsigned verticalCoeffIndex;
    struct {
        int rightViewOffset;
    } graphics3DSettings;
    struct {
        int16_t y, cb, cr;
    } sdrToHdr;
    _Bool secure;
} NEXUS_GraphicsSettings;
NEXUS_Error NEXUS_Display_SetVsyncCallback(
    NEXUS_DisplayHandle display,
    const NEXUS_CallbackDesc *pDesc
    );
void NEXUS_Display_GetGraphicsSettings(
    NEXUS_DisplayHandle display,
    NEXUS_GraphicsSettings *pSettings
    );
NEXUS_Error NEXUS_Display_SetGraphicsSettings(
    NEXUS_DisplayHandle display,
    const NEXUS_GraphicsSettings *pSettings
    );
NEXUS_Error NEXUS_Display_SetGraphicsFramebuffer(
    NEXUS_DisplayHandle display,
    NEXUS_SurfaceHandle frameBuffer
    );
NEXUS_SurfaceHandle NEXUS_Display_CreateFramebuffer(
    NEXUS_DisplayHandle display,
    const NEXUS_SurfaceCreateSettings *pSettings
    );
typedef enum NEXUS_GraphicsFramebufferState
{
    NEXUS_GraphicsFramebufferState_eQueued,
    NEXUS_GraphicsFramebufferState_eDisplayed,
    NEXUS_GraphicsFramebufferState_eUnused,
    NEXUS_GraphicsFramebufferState_eMax
} NEXUS_GraphicsFramebufferState;
typedef struct NEXUS_GraphicsFramebufferStatus
{
    NEXUS_GraphicsFramebufferState state;
} NEXUS_GraphicsFramebufferStatus;
NEXUS_Error NEXUS_Display_GetGraphicsFramebufferStatus(
    NEXUS_DisplayHandle display,
    NEXUS_SurfaceHandle surface,
    NEXUS_GraphicsFramebufferStatus *pStatus
    );
void NEXUS_Display_GetGraphicsColorMatrix(
    NEXUS_DisplayHandle display,
    NEXUS_ColorMatrix *pColorMatrix
    );
NEXUS_Error NEXUS_Display_SetGraphicsColorMatrix(
    NEXUS_DisplayHandle display,
    const NEXUS_ColorMatrix *pColorMatrix
    );
void NEXUS_Display_GetGraphicsColorSettings(
    NEXUS_DisplayHandle display,
    NEXUS_GraphicsColorSettings *pSettings
    );
NEXUS_Error NEXUS_Display_SetGraphicsColorSettings(
    NEXUS_DisplayHandle display,
    const NEXUS_GraphicsColorSettings *pSettings
    );
NEXUS_Error NEXUS_Display_DriveVideoDecoder(
    NEXUS_DisplayHandle display
    );
NEXUS_Error NEXUS_DisplayModule_SetAutomaticPictureQuality(void);
NEXUS_Error NEXUS_Display_GetCrcData(
    NEXUS_DisplayHandle display,
    NEXUS_DisplayCrcData *pData,
    unsigned numEntries,
    unsigned *pNumEntriesReturned
    );
typedef struct NEXUS_GraphicsFramebuffer3D {
    NEXUS_VideoOrientation orientation;
    NEXUS_SurfaceHandle main;
    NEXUS_SurfaceHandle alpha;
    NEXUS_SurfaceHandle right;
    NEXUS_SurfaceHandle rightAlpha;
    uint32_t alphaW0;
    uint32_t alphaW1;
} NEXUS_GraphicsFramebuffer3D;
void NEXUS_Graphics_GetDefaultFramebuffer3D(
    NEXUS_GraphicsFramebuffer3D *pFrameBuffer3D
    );
NEXUS_Error NEXUS_Display_SetGraphicsFramebuffer3D(
    NEXUS_DisplayHandle display,
    const NEXUS_GraphicsFramebuffer3D *pFrameBuffer3D
    );
typedef struct NEXUS_DisplayStgSettings
{
    _Bool enabled;
    _Bool nonRealTime;
} NEXUS_DisplayStgSettings;
void NEXUS_Display_GetStgSettings(
    NEXUS_DisplayHandle display,
    NEXUS_DisplayStgSettings *pSettings
    );
NEXUS_Error NEXUS_Display_SetStgSettings(
    NEXUS_DisplayHandle display,
    const NEXUS_DisplayStgSettings *pSettings
    );
typedef enum NEXUS_GraphicsCompression
{
    NEXUS_GraphicsCompression_eNone,
    NEXUS_GraphicsCompression_eAllowed,
    NEXUS_GraphicsCompression_eRequired,
    NEXUS_GraphicsCompression_eMax
} NEXUS_GraphicsCompression;
typedef struct NEXUS_DisplayCapabilities
{
    unsigned numDisplays;
    struct {
        unsigned numVideoWindows;
        struct {
            unsigned width, height;
            NEXUS_GraphicsCompression compression;
        } graphics;
    } display[7];
    _Bool displayFormatSupported[NEXUS_VideoFormat_eMax];
    unsigned numLetterBoxDetect;
} NEXUS_DisplayCapabilities;
void NEXUS_GetDisplayCapabilities(
    NEXUS_DisplayCapabilities *pCapabilities
    );
typedef struct NEXUS_DisplayModuleStatus
{
    struct {
        NEXUS_MemoryBlockHandle memory;
        unsigned offset;
        size_t size;
        size_t elementSize;
    } rulCapture;
} NEXUS_DisplayModuleStatus;
typedef struct NEXUS_DisplayMaxMosaicCoverage
{
    unsigned maxCoverage;
} NEXUS_DisplayMaxMosaicCoverage;
NEXUS_Error NEXUS_Display_GetMaxMosaicCoverage(
    unsigned displayIndex,
    unsigned numMosaics,
    NEXUS_DisplayMaxMosaicCoverage *pCoverage
    );
typedef struct NEXUS_DisplayModuleDependencies
{
    NEXUS_ModuleHandle videoDecoder;
    NEXUS_ModuleHandle surface;
    NEXUS_ModuleHandle hdmiInput;
    NEXUS_ModuleHandle hdmiDvo;
    NEXUS_ModuleHandle hdmiOutput;
    NEXUS_ModuleHandle rfm;
    NEXUS_ModuleHandle pwm;
    NEXUS_ModuleHandle transport;
} NEXUS_DisplayModuleDependencies;
typedef struct NEXUS_DisplayModuleInternalSettings
{
    NEXUS_DisplayModuleDependencies modules;
} NEXUS_DisplayModuleInternalSettings;
struct NEXUS_Core_PreInitState;
void NEXUS_DisplayModule_GetDefaultInternalSettings(
    NEXUS_DisplayModuleInternalSettings *pSettings
    );
void NEXUS_DisplayModule_GetDefaultSettings(
    const struct NEXUS_Core_PreInitState *preInitState,
    NEXUS_DisplayModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_DisplayModule_Init(
    const NEXUS_DisplayModuleInternalSettings *pModuleSettings,
    const NEXUS_DisplayModuleSettings *pSettings
    );
void NEXUS_DisplayModule_Uninit(void);
void NEXUS_DisplayModule_SetVideoDecoderModule(
    NEXUS_ModuleHandle videoDecoder
    );
void NEXUS_Display_GetIndex_driver(
    NEXUS_DisplayHandle display,
    unsigned *pDisplayIndex
    );
typedef struct NEXUS_TeletextLine
{
    _Bool topField;
    unsigned lineNumber;
    uint8_t framingCode;
    uint8_t data[42];
} NEXUS_TeletextLine;
typedef struct NEXUS_VpsData
{
    uint8_t byte05;
    uint8_t byte11;
    uint8_t byte12;
    uint8_t byte13;
    uint8_t byte14;
    uint8_t byte15;
} NEXUS_VpsData;
typedef struct NEXUS_GemStarData
{
    _Bool topField;
    uint32_t lineMask;
    uint32_t data[5];
    uint32_t errorMask;
 } NEXUS_GemStarData;
typedef enum NEXUS_AmolType
{
    NEXUS_AmolType_eI,
    NEXUS_AmolType_eII_Lowrate,
    NEXUS_AmolType_eII_Highrate,
    NEXUS_AmolType_eMax
} NEXUS_AmolType;
typedef struct NEXUS_AmolData
{
    _Bool topField;
    uint8_t data[24];
    unsigned length;
} NEXUS_AmolData;
typedef enum NEXUS_DisplayDcsType
{
    NEXUS_DisplayDcsType_off,
    NEXUS_DisplayDcsType_eOff = NEXUS_DisplayDcsType_off,
    NEXUS_DisplayDcsType_on,
    NEXUS_DisplayDcsType_eOn1 = NEXUS_DisplayDcsType_on,
    NEXUS_DisplayDcsType_eOn2,
    NEXUS_DisplayDcsType_eOn3,
    NEXUS_DisplayDcsType_eMax
} NEXUS_DisplayDcsType;
typedef struct NEXUS_DisplayVbiSettings
{
    NEXUS_VideoInputHandle vbiSource;
    _Bool closedCaptionRouting;
    _Bool teletextRouting;
    _Bool wssRouting;
    _Bool cgmsRouting;
    _Bool vpsRouting;
    _Bool teletextEnabled;
    _Bool closedCaptionEnabled;
    _Bool wssEnabled;
    _Bool cgmsEnabled;
    _Bool vpsEnabled;
    _Bool gemStarEnabled;
    _Bool amolEnabled;
    _Bool macrovisionEnabled;
    _Bool dcsEnabled;
    struct {
        unsigned baseLineTop;
        uint16_t lineMaskTop;
        unsigned baseLineBottom;
        uint16_t lineMaskBottom;
    } gemStar;
    struct {
        NEXUS_AmolType type;
    } amol;
} NEXUS_DisplayVbiSettings;
void NEXUS_Display_GetVbiSettings(
    NEXUS_DisplayHandle handle,
    NEXUS_DisplayVbiSettings *pSettings
    );
NEXUS_Error NEXUS_Display_SetVbiSettings(
    NEXUS_DisplayHandle handle,
    const NEXUS_DisplayVbiSettings *pSettings
    );
NEXUS_Error NEXUS_Display_WriteTeletext(
    NEXUS_DisplayHandle handle,
    const NEXUS_TeletextLine *pLines,
    size_t numLines,
    size_t *pNumLinesWritten
    );
NEXUS_Error NEXUS_Display_WriteClosedCaption(
    NEXUS_DisplayHandle handle,
    const NEXUS_ClosedCaptionData *pEntries,
    size_t numEntries,
    size_t *pNumEntriesWritten
    );
NEXUS_Error NEXUS_Display_WriteGemStar(
    NEXUS_DisplayHandle handle,
    const NEXUS_GemStarData *pEntries,
    size_t numEntries,
    size_t *pNumEntriesWritten
    );
NEXUS_Error NEXUS_Display_SetWss(
    NEXUS_DisplayHandle handle,
    uint16_t wssData
    );
NEXUS_Error NEXUS_Display_SetCgms(
    NEXUS_DisplayHandle handle,
    uint32_t cgmsData
    );
NEXUS_Error NEXUS_Display_SetCgmsB(
    NEXUS_DisplayHandle handle,
    const uint32_t *pCgmsData,
    unsigned size
    );
NEXUS_Error NEXUS_Display_SetVps(
    NEXUS_DisplayHandle handle,
    const NEXUS_VpsData *pData
    );
NEXUS_Error NEXUS_Display_SetMacrovision(
    NEXUS_DisplayHandle handle,
    NEXUS_DisplayMacrovisionType type,
    const NEXUS_DisplayMacrovisionTables *pTable
    );
NEXUS_Error NEXUS_Display_SetDcs(
    NEXUS_DisplayHandle handle,
    NEXUS_DisplayDcsType type
    );
NEXUS_Error NEXUS_Display_DcsLock(
    NEXUS_DisplayHandle handle
    );
NEXUS_Error NEXUS_Display_WriteAmol(
    NEXUS_DisplayHandle handle,
    const NEXUS_AmolData *pEntries,
    size_t numEntries,
    size_t *pNumEntriesWritten
    );
typedef struct NEXUS_Dma *NEXUS_DmaHandle;
typedef enum NEXUS_DmaCoreType
{
    NEXUS_DmaCoreType_eM2m,
    NEXUS_DmaCoreType_eSharf,
    NEXUS_DmaCoreType_eMax
} NEXUS_DmaCoreType;
typedef enum NEXUS_DmaEndianMode
{
    NEXUS_DmaEndianMode_eLittle,
    NEXUS_DmaEndianMode_eBig,
    NEXUS_DmaEndianMode_eMax
} NEXUS_DmaEndianMode;
typedef enum NEXUS_DmaSwapMode
{
    NEXUS_DmaSwapMode_eNone,
    NEXUS_DmaSwapMode_eWord,
    NEXUS_DmaSwapMode_eByte,
    NEXUS_DmaSwapMode_eMax
} NEXUS_DmaSwapMode;
typedef enum NEXUS_DmaDataFormat
{
    NEXUS_DmaDataFormat_eBlock,
    NEXUS_DmaDataFormat_eMpeg,
    NEXUS_DmaDataFormat_eDss,
    NEXUS_DmaDataFormat_eMax
} NEXUS_DmaDataFormat;
typedef enum NEXUS_DmaSharfMode
{
    NEXUS_DmaSharfMode_ePassThrough,
    NEXUS_DmaSharfMode_eSha1,
    NEXUS_DmaSharfMode_eAes128CbcDecrypt,
    NEXUS_DmaSharfMode_eAes128CbcEncrypt,
    NEXUS_DmaSharfMode_eCmac,
    NEXUS_DmaSharfMode_eAes128EcbDecrypt,
    NEXUS_DmaSharfMode_eAes128EcbEncrypt,
    NEXUS_DmaSharfMode_eMax
} NEXUS_DmaSharfMode;
typedef struct NEXUS_DmaSettings
{
    NEXUS_DmaEndianMode endianMode;
    NEXUS_DmaSwapMode swapMode;
    NEXUS_DmaCoreType coreType;
    NEXUS_HeapHandle boundsHeap;
    unsigned totalBlocks;
    unsigned maxBlocksPerTransfer;
} NEXUS_DmaSettings;
void NEXUS_Dma_GetDefaultSettings(
    NEXUS_DmaSettings *pSettings
    );
NEXUS_DmaHandle NEXUS_Dma_Open(
    unsigned index,
    const NEXUS_DmaSettings *pSettings
    );
void NEXUS_Dma_Close(
    NEXUS_DmaHandle handle
    );
NEXUS_Error NEXUS_Dma_GetSettings(
    NEXUS_DmaHandle handle,
    NEXUS_DmaSettings *pSettings
    );
NEXUS_Error NEXUS_Dma_SetSettings(
    NEXUS_DmaHandle handle,
    const NEXUS_DmaSettings *pSettings
    );
typedef struct NEXUS_DmaJob *NEXUS_DmaJobHandle;
typedef struct NEXUS_DmaJobSettings
{
    unsigned numBlocks;
    unsigned busyWait;
    unsigned busyWaitThreshold;
    NEXUS_KeySlotHandle keySlot;
    NEXUS_BypassKeySlot bypassKeySlot;
    NEXUS_DmaDataFormat dataFormat;
    NEXUS_TransportTimestampType timestampType;
    NEXUS_CallbackDesc completionCallback;
    _Bool useRPipe;
    struct {
        _Bool useBspKey;
        NEXUS_DmaSharfMode mode;
        unsigned shaContext;
    } sharf;
} NEXUS_DmaJobSettings;
void NEXUS_DmaJob_GetDefaultSettings(
    NEXUS_DmaJobSettings *pSettings
    );
NEXUS_DmaJobHandle NEXUS_DmaJob_Create(
    NEXUS_DmaHandle dmaHandle,
    const NEXUS_DmaJobSettings *pSettings
    );
void NEXUS_DmaJob_Destroy(
    NEXUS_DmaJobHandle handle
    );
void NEXUS_DmaJob_GetSettings(
    NEXUS_DmaJobHandle handle,
    NEXUS_DmaJobSettings *pSettings
    );
NEXUS_Error NEXUS_DmaJob_SetSettings(
    NEXUS_DmaJobHandle handle,
    const NEXUS_DmaJobSettings *pSettings
    );
typedef struct NEXUS_DmaJobBlockSettings
{
    const void *pSrcAddr;
    void *pDestAddr;
    size_t blockSize;
    _Bool cached;
    _Bool resetCrypto;
    _Bool scatterGatherCryptoStart;
    _Bool scatterGatherCryptoEnd;
    _Bool securityBtp;
    struct {
        _Bool keyPresent;
        _Bool digestPresent;
    } sharf;
} NEXUS_DmaJobBlockSettings;
void NEXUS_DmaJob_GetDefaultBlockSettings(
    NEXUS_DmaJobBlockSettings *pSettings
    );
NEXUS_Error NEXUS_DmaJob_ProcessBlocks(
    NEXUS_DmaJobHandle handle,
    const NEXUS_DmaJobBlockSettings *pSettings,
    unsigned nBlocks
    );
typedef struct NEXUS_DmaJobBlockOffsetSettings
{
    NEXUS_Addr srcOffset;
    NEXUS_Addr destOffset;
    size_t blockSize;
    _Bool resetCrypto;
    _Bool scatterGatherCryptoStart;
    _Bool scatterGatherCryptoEnd;
    _Bool securityBtp;
    struct {
        _Bool keyPresent;
        _Bool digestPresent;
    } sharf;
} NEXUS_DmaJobBlockOffsetSettings;
void NEXUS_DmaJob_GetDefaultBlockOffsetSettings(
    NEXUS_DmaJobBlockOffsetSettings *pSettings
    );
NEXUS_Error NEXUS_DmaJob_ProcessBlocksOffset(
    NEXUS_DmaJobHandle handle,
    const NEXUS_DmaJobBlockOffsetSettings *pSettings,
    unsigned nBlocks
    );
typedef enum NEXUS_DmaJobState
{
    NEXUS_DmaJobState_eComplete,
    NEXUS_DmaJobState_eFailed,
    NEXUS_DmaJobState_eInProgress,
    NEXUS_DmaJobState_ePending,
    NEXUS_DmaJobState_eIdle,
    NEXUS_DmaJobState_eUnknown,
    NEXUS_DmaJobState_eMax
} NEXUS_DmaJobState;
typedef struct NEXUS_DmaJobStatus
{
    NEXUS_DmaJobState currentState;
} NEXUS_DmaJobStatus;
NEXUS_Error NEXUS_DmaJob_GetStatus(
    NEXUS_DmaJobHandle handle,
    NEXUS_DmaJobStatus *pStatus
    );
typedef struct NEXUS_DmaModuleSettings
{
    NEXUS_CommonModuleSettings common;
} NEXUS_DmaModuleSettings;
void NEXUS_DmaModule_GetDefaultSettings(
    NEXUS_DmaModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_DmaModule_Init(
    const NEXUS_DmaModuleSettings *pSettings
    );
void NEXUS_DmaModule_Uninit(void);
typedef struct NEXUS_DolbyDigitalReencode *NEXUS_DolbyDigitalReencodeHandle;
void NEXUS_DolbyDigitalReencode_GetDefaultSettings(
    NEXUS_DolbyDigitalReencodeSettings *pSettings
    );
NEXUS_DolbyDigitalReencodeHandle NEXUS_DolbyDigitalReencode_Open(
    const NEXUS_DolbyDigitalReencodeSettings *pSettings
    );
void NEXUS_DolbyDigitalReencode_Close(
    NEXUS_DolbyDigitalReencodeHandle handle
    );
void NEXUS_DolbyDigitalReencode_GetSettings(
    NEXUS_DolbyDigitalReencodeHandle handle,
    NEXUS_DolbyDigitalReencodeSettings *pSettings
    );
NEXUS_Error NEXUS_DolbyDigitalReencode_SetSettings(
    NEXUS_DolbyDigitalReencodeHandle handle,
    const NEXUS_DolbyDigitalReencodeSettings *pSettings
    );
NEXUS_AudioInputHandle NEXUS_DolbyDigitalReencode_GetConnector(
    NEXUS_DolbyDigitalReencodeHandle handle,
    NEXUS_AudioConnectorType connectorType
    );
NEXUS_Error NEXUS_DolbyDigitalReencode_AddInput(
    NEXUS_DolbyDigitalReencodeHandle handle,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_DolbyDigitalReencode_RemoveInput(
    NEXUS_DolbyDigitalReencodeHandle handle,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_DolbyDigitalReencode_RemoveAllInputs(
    NEXUS_DolbyDigitalReencodeHandle handle
    );
typedef struct NEXUS_DolbyVolume *NEXUS_DolbyVolumeHandle;
typedef struct NEXUS_DolbyVolumeSettings
{
    _Bool enabled;
    int blockSize;
    unsigned numBands;
    unsigned inputReferenceLevel;
    unsigned outputReferenceLevel;
    int calibrationOffset;
    _Bool reset;
    _Bool volumeModelerEnabled;
    int digitalVolumeLevel;
    int analogVolumeLevel;
    _Bool volumeLevelerEnabled;
    _Bool midsideProcessingEnabled;
    _Bool halfModeEnabled;
    unsigned volumeLevelerAmount;
} NEXUS_DolbyVolumeSettings;
void NEXUS_DolbyVolume_GetDefaultSettings(
    NEXUS_DolbyVolumeSettings *pSettings
    );
NEXUS_DolbyVolumeHandle NEXUS_DolbyVolume_Open(
    const NEXUS_DolbyVolumeSettings *pSettings
    );
void NEXUS_DolbyVolume_Close(
    NEXUS_DolbyVolumeHandle handle
    );
void NEXUS_DolbyVolume_GetSettings(
    NEXUS_DolbyVolumeHandle handle,
    NEXUS_DolbyVolumeSettings *pSettings
    );
NEXUS_Error NEXUS_DolbyVolume_SetSettings(
    NEXUS_DolbyVolumeHandle handle,
    const NEXUS_DolbyVolumeSettings *pSettings
    );
NEXUS_AudioInputHandle NEXUS_DolbyVolume_GetConnector(
    NEXUS_DolbyVolumeHandle handle
    );
NEXUS_Error NEXUS_DolbyVolume_AddInput(
    NEXUS_DolbyVolumeHandle handle,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_DolbyVolume_RemoveInput(
    NEXUS_DolbyVolumeHandle handle,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_DolbyVolume_RemoveAllInputs(
    NEXUS_DolbyVolumeHandle handle
    );
typedef struct NEXUS_DolbyVolume258 *NEXUS_DolbyVolume258Handle;
void NEXUS_DolbyVolume258_GetDefaultSettings(
    NEXUS_DolbyVolume258Settings *pSettings
    );
NEXUS_DolbyVolume258Handle NEXUS_DolbyVolume258_Open(
    const NEXUS_DolbyVolume258Settings *pSettings
    );
void NEXUS_DolbyVolume258_Close(
    NEXUS_DolbyVolume258Handle handle
    );
void NEXUS_DolbyVolume258_GetSettings(
    NEXUS_DolbyVolume258Handle handle,
    NEXUS_DolbyVolume258Settings *pSettings
    );
NEXUS_Error NEXUS_DolbyVolume258_SetSettings(
    NEXUS_DolbyVolume258Handle handle,
    const NEXUS_DolbyVolume258Settings *pSettings
    );
NEXUS_AudioInputHandle NEXUS_DolbyVolume258_GetConnector(
    NEXUS_DolbyVolume258Handle handle
    );
NEXUS_Error NEXUS_DolbyVolume258_AddInput(
    NEXUS_DolbyVolume258Handle handle,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_DolbyVolume258_RemoveInput(
    NEXUS_DolbyVolume258Handle handle,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_DolbyVolume258_RemoveAllInputs(
    NEXUS_DolbyVolume258Handle handle
    );
typedef struct NEXUS_EchoCanceller *NEXUS_EchoCancellerHandle;
typedef struct NEXUS_EchoCancellerSettings
{
    NEXUS_EchoCancellerAlgorithm algorithm;
} NEXUS_EchoCancellerSettings;
void NEXUS_EchoCanceller_GetDefaultSettings(
    NEXUS_EchoCancellerSettings *pSettings
    );
NEXUS_EchoCancellerHandle NEXUS_EchoCanceller_Create(
    const NEXUS_EchoCancellerSettings *pSettings
    );
void NEXUS_EchoCanceller_Destroy(
    NEXUS_EchoCancellerHandle handle
    );
void NEXUS_EchoCanceller_GetSettings(
    NEXUS_EchoCancellerHandle handle,
    NEXUS_EchoCancellerSettings *pSettings
    );
NEXUS_Error NEXUS_EchoCanceller_SetSettings(
    NEXUS_EchoCancellerHandle handle,
    const NEXUS_EchoCancellerSettings *pSettings
    );
typedef enum NEXUS_SpeexEchoCancellerGainMode
{
    NEXUS_SpeexEchoCancellerGainMode_eBark,
    NEXUS_SpeexEchoCancellerGainMode_eLinear,
    NEXUS_SpeexEchoCancellerGainMode_eMax
} NEXUS_SpeexEchoCancellerGainMode;
typedef struct NEXUS_SpeexEchoCancellerSettings
{
    NEXUS_SpeexEchoCancellerGainMode gainMode;
} NEXUS_SpeexEchoCancellerSettings;
typedef struct NEXUS_EchoCancellerAlgorithmSettings
{
    NEXUS_EchoCancellerAlgorithm algorithm;
    union
    {
        NEXUS_SpeexEchoCancellerSettings speex;
    } algorithmSettings;
} NEXUS_EchoCancellerAlgorithmSettings;
void NEXUS_EchoCanceller_GetAlgorithmSettings(
    NEXUS_EchoCancellerHandle handle,
    NEXUS_EchoCancellerAlgorithm algorithm,
    NEXUS_EchoCancellerAlgorithmSettings *pSettings
    );
NEXUS_Error NEXUS_EchoCanceller_SetAlgorithmSettings(
    NEXUS_EchoCancellerHandle handle,
    const NEXUS_EchoCancellerAlgorithmSettings *pSettings
    );
NEXUS_AudioInputHandle NEXUS_EchoCanceller_GetConnector(
    NEXUS_EchoCancellerHandle handle
    );
NEXUS_Error NEXUS_EchoCanceller_AddLocalInput(
    NEXUS_EchoCancellerHandle handle,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_EchoCanceller_RemoveLocalInput(
    NEXUS_EchoCancellerHandle handle,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_EchoCanceller_AddRemoteInput(
    NEXUS_EchoCancellerHandle handle,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_EchoCanceller_RemoveRemoteInput(
    NEXUS_EchoCancellerHandle handle,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_EchoCanceller_RemoveAllInputs(
    NEXUS_EchoCancellerHandle handle
    );
typedef struct NEXUS_FileMuxIoWriteAtom {
    const void *base;
    size_t len;
} NEXUS_FileMuxIoWriteAtom;
typedef struct NEXUS_FileMuxIoReadAtom {
    const void *base;
    size_t len;
} NEXUS_FileMuxIoReadAtom;
typedef struct bfile_io_read *NEXUS_FileReadHandle;
typedef struct bfile_io_write *NEXUS_FileWriteHandle;
typedef struct NEXUS_FilePlay *NEXUS_FilePlayHandle;
typedef struct NEXUS_FileRecord *NEXUS_FileRecordHandle;
typedef void (*NEXUS_File_Callback)(void *cntx, ssize_t size);
typedef struct NEXUS_FilePosition {
    off_t mpegFileOffset;
    unsigned long indexOffset;
    unsigned long timestamp;
} NEXUS_FilePosition;
void NEXUS_File_AsyncRead(
    NEXUS_FileReadHandle file,
    void *buf,
    size_t length,
    NEXUS_ModuleHandle module,
    NEXUS_File_Callback callback,
    void *cntx
    );
void NEXUS_File_AsyncWrite(
    NEXUS_FileWriteHandle file,
    const void *buf,
    size_t length,
    NEXUS_ModuleHandle module,
    NEXUS_File_Callback callback,
    void *cntx
    );
NEXUS_FilePlayHandle NEXUS_FilePlay_OpenPosix(
    const char *dataFileName,
    const char *indexFileName
    );
NEXUS_FileRecordHandle NEXUS_FileRecord_OpenPosix(
    const char *dataFileName,
    const char *indexFileName
    );
NEXUS_FileRecordHandle NEXUS_FileRecord_AppendPosix(
    const char *dataFileName,
    const char *indexFileName
    );
void NEXUS_FilePlay_Cancel(
    NEXUS_FilePlayHandle file
    );
void NEXUS_FilePlay_Close(
    NEXUS_FilePlayHandle file
    );
void NEXUS_FileRecord_Close(
    NEXUS_FileRecordHandle file
    );
NEXUS_Error NEXUS_FilePlay_GetBounds(
    NEXUS_FilePlayHandle file,
    NEXUS_FilePosition *pFirst,
    NEXUS_FilePosition *pLast
    );
NEXUS_Error NEXUS_FilePlay_GetLocation(
    NEXUS_FilePlayHandle file,
    unsigned long timestamp,
    NEXUS_FilePosition *pPosition
    );
typedef struct NEXUS_FilePlayOffset_Settings {
    off_t dataOffset;
    unsigned long indexOffset;
} NEXUS_FilePlayOffset_Settings;
void NEXUS_FilePlayOffset_GetDefaultSettings(
    NEXUS_FilePlayOffset_Settings *pSettings
    );
NEXUS_FilePlayHandle NEXUS_FilePlayOffset_Open(
    NEXUS_FilePlayHandle file,
    const NEXUS_FilePlayOffset_Settings *pSettings
    );
typedef struct NEXUS_MuxFile *NEXUS_MuxFileHandle;
typedef struct bfile_io_mux *NEXUS_MuxFileIoHandle;
void NEXUS_MuxFile_Close(NEXUS_MuxFileHandle file);
NEXUS_MuxFileHandle NEXUS_MuxFile_OpenPosix(
    const char *fileName
    );
void NEXUS_File_AsyncMuxWrite(
    NEXUS_MuxFileIoHandle file,
    off_t offset,
    const NEXUS_FileMuxIoWriteAtom *atoms,
    size_t atom_count,
    NEXUS_ModuleHandle module,
    NEXUS_File_Callback callback,
    void *cntx
    );
void NEXUS_File_AsyncMuxRead (
    NEXUS_MuxFileIoHandle file,
    off_t offset,
    const NEXUS_FileMuxIoReadAtom *atoms,
    size_t atom_count,
    NEXUS_ModuleHandle module,
    NEXUS_File_Callback callback,
    void *cntx
    );
typedef struct NEXUS_FileRecordOpenSettings
{
    struct {
        const char *filename;
        _Bool directIo;
        _Bool sync;
    } data;
    struct {
        const char *filename;
        _Bool sync;
    } index;
    _Bool append;
} NEXUS_FileRecordOpenSettings;
void NEXUS_FileRecord_GetDefaultOpenSettings(
    NEXUS_FileRecordOpenSettings *pSettings
);
NEXUS_FileRecordHandle NEXUS_FileRecord_Open(
    const NEXUS_FileRecordOpenSettings *pSettings
);
typedef struct NEXUS_FilePlayOpenSettings
{
    struct {
        const char *filename;
        _Bool directIo;
    } data;
    struct {
        const char *filename;
    } index;
} NEXUS_FilePlayOpenSettings;
void NEXUS_FilePlay_GetDefaultOpenSettings(
    NEXUS_FilePlayOpenSettings *pSettings
);
NEXUS_FilePlayHandle NEXUS_FilePlay_Open(
    const NEXUS_FilePlayOpenSettings *pSettings
);
typedef struct NEXUS_ChunkedFilePlayOpenSettings {
    off_t chunkSize;
    char chunkTemplate[128];
    unsigned firstChunkNumber;
} NEXUS_ChunkedFilePlayOpenSettings;
void NEXUS_ChunkedFilePlay_GetDefaultOpenSettings(
    NEXUS_ChunkedFilePlayOpenSettings *pSettings
    );
NEXUS_FilePlayHandle NEXUS_ChunkedFilePlay_Open(
    const char *dataFileName,
    const char *indexFileName,
    const NEXUS_ChunkedFilePlayOpenSettings *pSettings
    );
typedef struct NEXUS_ChunkedFileRecordOpenSettings {
    off_t chunkSize;
    char chunkTemplate[128];
} NEXUS_ChunkedFileRecordOpenSettings;
void NEXUS_ChunkedFileRecord_GetDefaultOpenSettings(
    NEXUS_ChunkedFileRecordOpenSettings *pSettings
    );
NEXUS_FileRecordHandle NEXUS_ChunkedFileRecord_Open(
    const char *dataFileName,
    const char *indexFileName,
    const NEXUS_ChunkedFileRecordOpenSettings *pSettings
    );
typedef struct NEXUS_FifoRecord *NEXUS_FifoRecordHandle;
typedef struct NEXUS_FifoRecordLimit {
    off_t soft;
    off_t hard;
} NEXUS_FifoRecordLimit;
typedef struct NEXUS_FifoRecordSettings {
    unsigned interval;
    unsigned snapshotInterval;
    NEXUS_FifoRecordLimit data;
    NEXUS_FifoRecordLimit index;
} NEXUS_FifoRecordSettings;
NEXUS_FifoRecordHandle NEXUS_FifoRecord_Create(
    const char *mpegFileName,
    const char *indexFileName
    );
NEXUS_FileRecordHandle NEXUS_FifoRecord_GetFile(
    NEXUS_FifoRecordHandle fifo
    );
NEXUS_Error NEXUS_FifoRecord_GetPosition(
    NEXUS_FifoRecordHandle fifo,
    NEXUS_FilePosition *pFirst,
    NEXUS_FilePosition *pLast
    );
NEXUS_FilePlayHandle NEXUS_FifoPlay_Open(
    const char *mpegFileName,
    const char *indexFileName,
    NEXUS_FifoRecordHandle writer
    );
void NEXUS_FifoRecord_GetSettings(
    NEXUS_FifoRecordHandle fifo,
    NEXUS_FifoRecordSettings *pSettings
    );
NEXUS_Error NEXUS_FifoRecord_SetSettings(
    NEXUS_FifoRecordHandle fifo,
    const NEXUS_FifoRecordSettings *pSettings
    );
typedef struct NEXUS_ChunkedFifoRecord *NEXUS_ChunkedFifoRecordHandle;
typedef struct NEXUS_ChunkedFifoRecordLimit {
    off_t soft;
    off_t hard;
    off_t chunkSize;
} NEXUS_ChunkedFifoRecordLimit;
typedef struct NEXUS_ChunkedFifoRecordSettings {
    unsigned interval;
    unsigned snapshotInterval;
    NEXUS_ChunkedFifoRecordLimit data;
    NEXUS_ChunkedFifoRecordLimit index;
    char chunkTemplate[128];
} NEXUS_ChunkedFifoRecordSettings;
void NEXUS_ChunkedFifoRecord_GetDefaultSettings(
    NEXUS_ChunkedFifoRecordSettings *pSettings
    );
NEXUS_ChunkedFifoRecordHandle NEXUS_ChunkedFifoRecord_Create(
    const char *mpegFileName,
    const char *indexFileName
    );
NEXUS_FileRecordHandle NEXUS_ChunkedFifoRecord_GetFile(
    NEXUS_ChunkedFifoRecordHandle fifo
    );
NEXUS_Error NEXUS_ChunkedFifoRecord_GetPosition(
    NEXUS_ChunkedFifoRecordHandle fifo,
    NEXUS_FilePosition *pFirst,
    NEXUS_FilePosition *pLast
    );
NEXUS_FilePlayHandle NEXUS_ChunkedFifoPlay_Open(
    const char *mpegFileName,
    const char *indexFileName,
    NEXUS_ChunkedFifoRecordHandle writer
    );
void NEXUS_ChunkedFifoRecord_GetSettings(
    NEXUS_ChunkedFifoRecordHandle fifo,
    NEXUS_ChunkedFifoRecordSettings *pSettings
    );
NEXUS_Error NEXUS_ChunkedFifoRecord_SetSettings(
    NEXUS_ChunkedFifoRecordHandle fifo,
    const NEXUS_ChunkedFifoRecordSettings *pSettings
    );
typedef struct NEXUS_ChunkedFifoRecordExportSettings
{
    const char *filename;
    const char *indexname;
    char chunkTemplate[128];
    struct {
        unsigned timestamp;
    } first, last;
} NEXUS_ChunkedFifoRecordExportSettings;
void NEXUS_ChunkedFifoRecord_GetDefaultExportSettings(
    NEXUS_ChunkedFifoRecordExportSettings *pSettings
    );
typedef struct NEXUS_ChunkedFifoRecordExport *NEXUS_ChunkedFifoRecordExportHandle;
NEXUS_ChunkedFifoRecordExportHandle NEXUS_ChunkedFifoRecord_StartExport(
    NEXUS_ChunkedFifoRecordHandle fifo,
    const NEXUS_ChunkedFifoRecordExportSettings *pSettings
    );
void NEXUS_ChunkedFifoRecord_StopExport(
    NEXUS_ChunkedFifoRecordExportHandle handle
    );
typedef enum NEXUS_ChunkedFifoRecordExportState
{
    NEXUS_ChunkedFifoRecordExportState_eIdle,
    NEXUS_ChunkedFifoRecordExportState_eStarted,
    NEXUS_ChunkedFifoRecordExportState_eFailed,
    NEXUS_ChunkedFifoRecordExportState_eDone
} NEXUS_ChunkedFifoRecordExportState;
typedef struct NEXUS_ChunkedFifoRecordExportStatus
{
    NEXUS_ChunkedFifoRecordExportState state;
    struct {
        unsigned timestamp;
        unsigned chunkNumber;
        off_t offset;
    } first, last;
} NEXUS_ChunkedFifoRecordExportStatus;
NEXUS_Error NEXUS_ChunkedFifoRecord_GetExportStatus(
    NEXUS_ChunkedFifoRecordExportHandle handle,
    NEXUS_ChunkedFifoRecordExportStatus *pStatus
    );
typedef struct NEXUS_FileModuleSettings
{
    unsigned maxQueuedElements;
    unsigned workerThreads;
    NEXUS_ThreadSettings schedulerSettings[4];
} NEXUS_FileModuleSettings;
void NEXUS_FileModule_GetDefaultSettings(
    NEXUS_FileModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_FileModule_Init(
    const NEXUS_FileModuleSettings *pSettings
    );
void NEXUS_FileModule_Uninit(void);
typedef struct NEXUS_VideoEncoder *NEXUS_VideoEncoderHandle;
typedef enum NEXUS_VideoCodecLevel {
   NEXUS_VideoCodecLevel_eUnknown = 0,
   NEXUS_VideoCodecLevel_e00,
   NEXUS_VideoCodecLevel_e10,
   NEXUS_VideoCodecLevel_e1B,
   NEXUS_VideoCodecLevel_e11,
   NEXUS_VideoCodecLevel_e12,
   NEXUS_VideoCodecLevel_e13,
   NEXUS_VideoCodecLevel_e20,
   NEXUS_VideoCodecLevel_e21,
   NEXUS_VideoCodecLevel_e22,
   NEXUS_VideoCodecLevel_e30,
   NEXUS_VideoCodecLevel_e31,
   NEXUS_VideoCodecLevel_e32,
   NEXUS_VideoCodecLevel_e40,
   NEXUS_VideoCodecLevel_e41,
   NEXUS_VideoCodecLevel_e42,
   NEXUS_VideoCodecLevel_e50,
   NEXUS_VideoCodecLevel_e51,
   NEXUS_VideoCodecLevel_e60,
   NEXUS_VideoCodecLevel_e62,
   NEXUS_VideoCodecLevel_eLow,
   NEXUS_VideoCodecLevel_eMain,
   NEXUS_VideoCodecLevel_eHigh,
   NEXUS_VideoCodecLevel_eHigh1440,
   NEXUS_VideoCodecLevel_eMax
} NEXUS_VideoCodecLevel;
typedef enum NEXUS_VideoCodecProfile
{
   NEXUS_VideoCodecProfile_eUnknown = 0,
   NEXUS_VideoCodecProfile_eSimple,
   NEXUS_VideoCodecProfile_eMain,
   NEXUS_VideoCodecProfile_eHigh,
   NEXUS_VideoCodecProfile_eAdvanced,
   NEXUS_VideoCodecProfile_eJizhun,
   NEXUS_VideoCodecProfile_eSnrScalable,
   NEXUS_VideoCodecProfile_eSpatiallyScalable,
   NEXUS_VideoCodecProfile_eAdvancedSimple,
   NEXUS_VideoCodecProfile_eBaseline,
   NEXUS_VideoCodecProfile_eMax
} NEXUS_VideoCodecProfile;
typedef enum NEXUS_EntropyCoding
{
    NEXUS_EntropyCoding_eAuto,
    NEXUS_EntropyCoding_eCavlc,
    NEXUS_EntropyCoding_eCabac,
    NEXUS_EntropyCoding_eMax
} NEXUS_EntropyCoding;
typedef struct NEXUS_VideoEncoder_MemoryConfig
{
    unsigned general;
    unsigned secure;
    unsigned picture;
    unsigned firmware;
    unsigned index;
    unsigned data;
} NEXUS_VideoEncoder_MemoryConfig;
typedef struct NEXUS_VideoEncoderMemory {
    _Bool used;
    _Bool interlaced;
    unsigned maxWidth, maxHeight;
    NEXUS_VideoFrameRate maxFrameRate;
} NEXUS_VideoEncoderMemory;
typedef struct NEXUS_VideoEncoderModuleSettings
{
    _Bool deferInit;
} NEXUS_VideoEncoderModuleSettings;
typedef struct NEXUS_VideoEncoderDescriptor
{
    uint32_t flags;
    uint32_t originalPts;
    uint64_t pts;
    uint64_t stcSnapshot;
    uint32_t escr;
    uint16_t ticksPerBit;
    int16_t shr;
    unsigned offset;
    size_t length;
    unsigned unused[2];
    uint32_t videoFlags;
    uint64_t dts;
    uint8_t dataUnitType;
} NEXUS_VideoEncoderDescriptor;
NEXUS_Error NEXUS_VideoEncoder_GetBuffer(
    NEXUS_VideoEncoderHandle handle,
    const NEXUS_VideoEncoderDescriptor **pBuffer,
    size_t *pSize,
    const NEXUS_VideoEncoderDescriptor **pBuffer2,
    size_t *pSize2
    );
NEXUS_Error NEXUS_VideoEncoder_ReadComplete(
    NEXUS_VideoEncoderHandle handle,
    unsigned descriptorsCompleted
    );
typedef struct NEXUS_VideoEncoderStatus
{
    NEXUS_MemoryBlockHandle bufferBlock;
    NEXUS_MemoryBlockHandle metadataBufferBlock;
    uint32_t errorFlags;
    uint32_t eventFlags;
    unsigned errorCount;
    unsigned picturesReceived;
    unsigned picturesDroppedFRC;
    unsigned picturesDroppedHRD;
    unsigned picturesDroppedErrors;
    unsigned picturesEncoded;
    uint32_t pictureIdLastEncoded;
    unsigned picturesPerSecond;
    struct {
        size_t fifoDepth;
        size_t fifoSize;
    } data, index;
    struct {
        unsigned firmware;
    } version;
    NEXUS_DebugFifoInfo debugLog;
} NEXUS_VideoEncoderStatus;
NEXUS_Error NEXUS_VideoEncoder_GetStatus(
    NEXUS_VideoEncoderHandle handle,
    NEXUS_VideoEncoderStatus *pStatus
    );
typedef enum
{
    NEXUS_VideoInputCrcType_eCrc32,
    NEXUS_VideoInputCrcType_eChecksum,
    NEXUS_VideoInputCrcType_eCrc16
} NEXUS_VideoInputCrcType;
typedef struct NEXUS_VideoInputSettings
{
    _Bool mute;
    NEXUS_Pixel muteColor;
    _Bool repeat;
    NEXUS_CallbackDesc sourceChanged;
    NEXUS_CallbackDesc sourcePending;
    struct {
        _Bool enable;
        NEXUS_VideoFormat videoFormat;
        NEXUS_Video3DStructure structure;
        NEXUS_Video3DSubSample subSample;
        _Bool overrideOrientation;
        NEXUS_VideoOrientation orientation;
    } video3DSettings;
    NEXUS_VideoInputCrcType crcType;
    unsigned crcQueueSize;
} NEXUS_VideoInputSettings;
void NEXUS_VideoInput_GetSettings(
    NEXUS_VideoInputHandle input,
    NEXUS_VideoInputSettings *pSettings
    );
NEXUS_Error NEXUS_VideoInput_SetSettings(
    NEXUS_VideoInputHandle input,
    const NEXUS_VideoInputSettings *pSettings
    );
typedef struct NEXUS_VideoInputStatus
{
    _Bool videoPresent;
    unsigned width, height;
    NEXUS_AspectRatio aspectRatio;
    NEXUS_VideoFormat format;
    NEXUS_VideoFrameRate frameRate;
    unsigned refreshRate;
    _Bool sourcePending;
} NEXUS_VideoInputStatus;
NEXUS_Error NEXUS_VideoInput_GetStatus(
    NEXUS_VideoInputHandle input,
    NEXUS_VideoInputStatus *pStatus
    );
void NEXUS_VideoInput_Shutdown(
    NEXUS_VideoInputHandle input
    );
void NEXUS_VideoInput_GetColorMatrix(
    NEXUS_VideoInputHandle input,
    NEXUS_ColorMatrix *pColorMatrix
    );
NEXUS_Error NEXUS_VideoInput_SetColorMatrix(
    NEXUS_VideoInputHandle input,
    const NEXUS_ColorMatrix *pColorMatrix
    );
typedef enum
{
    NEXUS_VideoInputResumeMode_eAuto,
    NEXUS_VideoInputResumeMode_eManual,
    NEXUS_VideoInputResumeMode_eNow,
    NEXUS_VideoInputResumeMode_eFreezeRts
} NEXUS_VideoInputResumeMode;
typedef struct NEXUS_SyncChannel *NEXUS_SyncChannelHandle;
typedef struct NEXUS_SyncChannelSettings
{
    NEXUS_VideoInputHandle videoInput;
    NEXUS_AudioInputHandle audioInput[6];
    _Bool enablePrecisionLipsync;
    _Bool enableMuteControl;
    _Bool allowIncrementalStart;
    _Bool simultaneousUnmute;
    unsigned adjustmentThreshold;
    unsigned customVideoDelay;
    unsigned customAudioDelay[6];
} NEXUS_SyncChannelSettings;
void NEXUS_SyncChannel_GetDefaultSettings(
    NEXUS_SyncChannelSettings *pSettings
    );
NEXUS_SyncChannelHandle NEXUS_SyncChannel_Create(
    const NEXUS_SyncChannelSettings *pSettings
    );
void NEXUS_SyncChannel_Destroy(
    NEXUS_SyncChannelHandle handle
    );
void NEXUS_SyncChannel_GetSettings(
    NEXUS_SyncChannelHandle handle,
    NEXUS_SyncChannelSettings *pSettings
    );
NEXUS_Error NEXUS_SyncChannel_SetSettings(
    NEXUS_SyncChannelHandle handle,
    const NEXUS_SyncChannelSettings *pSettings
    );
typedef struct NEXUS_SimpleStcChannel *NEXUS_SimpleStcChannelHandle;
typedef enum NEXUS_SimpleStcChannelHighJitterMode
{
    NEXUS_SimpleStcChannelHighJitterMode_eNone,
    NEXUS_SimpleStcChannelHighJitterMode_eDirect,
    NEXUS_SimpleStcChannelHighJitterMode_eTtsPacing,
    NEXUS_SimpleStcChannelHighJitterMode_ePcrPacing,
    NEXUS_SimpleStcChannelHighJitterMode_eMax
} NEXUS_SimpleStcChannelHighJitterMode;
typedef struct NEXUS_SimpleStcChannelHighJitterSettings
{
    NEXUS_SimpleStcChannelHighJitterMode mode;
    unsigned threshold;
} NEXUS_SimpleStcChannelHighJitterSettings;
typedef enum NEXUS_SimpleStcChannelSyncMode
{
    NEXUS_SimpleStcChannelSyncMode_eOff,
    NEXUS_SimpleStcChannelSyncMode_eDefaultAdjustmentConcealment,
    NEXUS_SimpleStcChannelSyncMode_eNoAdjustmentConcealment,
    NEXUS_SimpleStcChannelSyncMode_eAudioAdjustmentConcealment,
    NEXUS_SimpleStcChannelSyncMode_eMax
} NEXUS_SimpleStcChannelSyncMode;
typedef struct NEXUS_SimpleStcChannelSettings
{
    NEXUS_StcChannelMode mode;
    struct
    {
        NEXUS_StcChannelPcrModeSettings pcr;
        NEXUS_SimpleStcChannelHighJitterSettings highJitter;
        NEXUS_StcChannelAutoModeSettings Auto;
        NEXUS_StcChannelHostModeSettings host;
    } modeSettings;
    _Bool astm;
    NEXUS_SimpleStcChannelSyncMode sync;
    NEXUS_StcChannelUnderflowHandling underflowHandling;
    NEXUS_Timebase timebase;
} NEXUS_SimpleStcChannelSettings;
void NEXUS_SimpleStcChannel_GetDefaultSettings(
    NEXUS_SimpleStcChannelSettings *pSettings
    );
NEXUS_SimpleStcChannelHandle NEXUS_SimpleStcChannel_Create(
    const NEXUS_SimpleStcChannelSettings *pSettings
    );
void NEXUS_SimpleStcChannel_Destroy(
    NEXUS_SimpleStcChannelHandle handle
    );
void NEXUS_SimpleStcChannel_GetSettings(
    NEXUS_SimpleStcChannelHandle handle,
    NEXUS_SimpleStcChannelSettings *pSettings
    );
NEXUS_Error NEXUS_SimpleStcChannel_SetSettings(
    NEXUS_SimpleStcChannelHandle handle,
    const NEXUS_SimpleStcChannelSettings *pSettings
    );
NEXUS_Error NEXUS_SimpleStcChannel_Invalidate(
    NEXUS_SimpleStcChannelHandle handle
    );
void NEXUS_SimpleStcChannel_GetStc(
    NEXUS_SimpleStcChannelHandle handle,
    uint32_t *pStc
    );
NEXUS_Error NEXUS_SimpleStcChannel_SetStc(
    NEXUS_SimpleStcChannelHandle handle,
    uint32_t stc
    );
NEXUS_Error NEXUS_SimpleStcChannel_Freeze(
    NEXUS_SimpleStcChannelHandle handle,
    _Bool frozen
    );
NEXUS_Error NEXUS_SimpleStcChannel_SetRate(
    NEXUS_SimpleStcChannelHandle handle,
    unsigned increment,
    unsigned prescale
    );
void NEXUS_SimpleStcChannel_GetSyncChannel(
 NEXUS_SimpleStcChannelHandle handle,
 NEXUS_SyncChannelHandle *pSyncHandle
 );
typedef struct NEXUS_Gpio *NEXUS_GpioHandle;
typedef enum NEXUS_GpioType
{
    NEXUS_GpioType_eStandard,
    NEXUS_GpioType_eSpecial,
    NEXUS_GpioType_eTvMicro,
    NEXUS_GpioType_eAonStandard,
    NEXUS_GpioType_eAonSpecial,
    NEXUS_GpioType_eMax
} NEXUS_GpioType;
typedef enum NEXUS_GpioMode
{
    NEXUS_GpioMode_eInput,
    NEXUS_GpioMode_eOutputOpenDrain,
    NEXUS_GpioMode_eOutputPushPull,
    NEXUS_GpioMode_eMax
} NEXUS_GpioMode;
typedef enum NEXUS_GpioValue
{
    NEXUS_GpioValue_eLow = 0,
    NEXUS_GpioValue_eHigh = 1,
    NEXUS_GpioValue_eMax
} NEXUS_GpioValue;
typedef enum NEXUS_GpioInterrupt
{
    NEXUS_GpioInterrupt_eDisabled,
    NEXUS_GpioInterrupt_eRisingEdge,
    NEXUS_GpioInterrupt_eFallingEdge,
    NEXUS_GpioInterrupt_eEdge,
    NEXUS_GpioInterrupt_eLow,
    NEXUS_GpioInterrupt_eHigh,
    NEXUS_GpioInterrupt_eMax
} NEXUS_GpioInterrupt;
typedef struct NEXUS_GpioSettings
{
    NEXUS_GpioMode mode;
    NEXUS_GpioValue value;
    NEXUS_GpioInterrupt interruptMode;
    NEXUS_CallbackDesc interrupt;
    _Bool maskEdgeInterrupts;
} NEXUS_GpioSettings;
void NEXUS_Gpio_GetDefaultSettings(
    NEXUS_GpioType type,
    NEXUS_GpioSettings *pSettings
    );
NEXUS_GpioHandle NEXUS_Gpio_OpenAux(
    unsigned typeAndPin,
    const NEXUS_GpioSettings *pSettings
    );
void NEXUS_Gpio_Close(
    NEXUS_GpioHandle handle
    );
NEXUS_Error NEXUS_Gpio_SetSettings(
    NEXUS_GpioHandle handle,
    const NEXUS_GpioSettings *pSettings
    );
void NEXUS_Gpio_GetSettings(
    NEXUS_GpioHandle handle,
    NEXUS_GpioSettings *pSettings
    );
typedef struct NEXUS_GpioStatus
{
    NEXUS_GpioValue value;
    _Bool interruptPending;
} NEXUS_GpioStatus;
NEXUS_Error NEXUS_Gpio_GetStatus(
    NEXUS_GpioHandle handle,
    NEXUS_GpioStatus *pStatus
    );
NEXUS_Error NEXUS_Gpio_ClearInterrupt(
    NEXUS_GpioHandle handle
    );
NEXUS_Error NEXUS_Gpio_GetPinMux(
    unsigned typeAndPin,
    uint32_t *pAddr,
    uint32_t *pMask,
    unsigned *pShift
    );
typedef struct NEXUS_I2c *NEXUS_I2cHandle;
typedef enum NEXUS_I2cClockRate
{
    NEXUS_I2cClockRate_e47Khz = 47000,
    NEXUS_I2cClockRate_e50Khz = 50000,
    NEXUS_I2cClockRate_e93Khz = 93000,
    NEXUS_I2cClockRate_e100Khz = 100000,
    NEXUS_I2cClockRate_e187Khz = 187000,
    NEXUS_I2cClockRate_e200Khz = 200000,
    NEXUS_I2cClockRate_e375Khz = 375000,
    NEXUS_I2cClockRate_e400Khz = 400000,
    NEXUS_I2cClockRate_eMax
} NEXUS_I2cClockRate;
typedef struct NEXUS_I2cSettings
{
    NEXUS_I2cClockRate clockRate;
    _Bool interruptMode;
    _Bool burstMode;
    unsigned timeout;
    struct {
        _Bool enabled;
    }autoI2c;
    _Bool softI2c;
    NEXUS_GpioHandle clockGpio;
    NEXUS_GpioHandle dataGpio;
    _Bool fourByteXferMode;
    _Bool use5v;
} NEXUS_I2cSettings;
void NEXUS_I2c_GetDefaultSettings(
    NEXUS_I2cSettings *pSettings
    );
NEXUS_I2cHandle NEXUS_I2c_Open(
    unsigned channelIndex,
    const NEXUS_I2cSettings *pSettings
    );
void NEXUS_I2c_Close(
    NEXUS_I2cHandle handle
    );
NEXUS_Error NEXUS_I2c_SetSettings(
    NEXUS_I2cHandle i2cHandle,
    const NEXUS_I2cSettings *pSettings
    );
void NEXUS_I2c_GetSettings(
    NEXUS_I2cHandle i2cHandle,
    NEXUS_I2cSettings *pSettings
    );
NEXUS_Error NEXUS_I2c_Write(
    NEXUS_I2cHandle handle,
    uint16_t chipAddr,
    uint8_t subAddr,
    const uint8_t *pData,
    size_t length
    );
NEXUS_Error NEXUS_I2c_WriteRead(
    NEXUS_I2cHandle i2cHandle,
    uint16_t chipAddr,
    uint8_t subAddr,
    const uint8_t *pWriteData,
    size_t writeLength,
    uint8_t *pReadData,
    size_t readLength
    );
NEXUS_Error NEXUS_I2c_WriteReadNoAddr(
    NEXUS_I2cHandle i2cHandle,
    uint16_t chipAddr,
    const uint8_t *pWriteData,
    size_t writeLength,
    uint8_t *pReadData,
    size_t readLength
    );
NEXUS_Error NEXUS_I2c_WriteNoAck(
    NEXUS_I2cHandle handle,
    uint16_t chipAddr,
    uint8_t subAddr,
    const uint8_t *pData,
    size_t length
    );
NEXUS_Error NEXUS_I2c_WriteA16(
    NEXUS_I2cHandle handle,
    uint16_t chipAddr,
    uint16_t subAddr,
    const uint8_t *pData,
    size_t length
    );
NEXUS_Error NEXUS_I2c_WriteA24(
    NEXUS_I2cHandle handle,
    uint16_t chipAddr,
    uint32_t subAddr,
    const uint8_t *pData,
    size_t length
    );
NEXUS_Error NEXUS_I2c_WriteNoAddr(
    NEXUS_I2cHandle handle,
    uint16_t chipAddr,
    const uint8_t *pData,
    size_t length
    );
NEXUS_Error NEXUS_I2c_WriteNoAddrNoAck(
    NEXUS_I2cHandle handle,
    uint16_t chipAddr,
    const uint8_t *pData,
    size_t length
    );
NEXUS_Error NEXUS_I2c_WriteNvram(
    NEXUS_I2cHandle handle,
    uint16_t chipAddr,
    uint8_t subAddr,
    const uint8_t *pData,
    size_t length
    );
NEXUS_Error NEXUS_I2c_Read(
    NEXUS_I2cHandle handle,
    uint16_t chipAddr,
    uint8_t subAddr,
    uint8_t *pData,
    size_t length
    );
NEXUS_Error NEXUS_I2c_ReadNoAck(
    NEXUS_I2cHandle handle,
    uint16_t chipAddr,
    uint8_t subAddr,
    uint8_t *pData,
    size_t length
    );
NEXUS_Error NEXUS_I2c_ReadA16(
    NEXUS_I2cHandle handle,
    uint16_t chipAddr,
    uint16_t subAddr,
    uint8_t *pData,
    size_t length
    );
NEXUS_Error NEXUS_I2c_ReadA24(
    NEXUS_I2cHandle handle,
    uint16_t chipAddr,
    uint32_t subAddr,
    uint8_t *pData,
    size_t length
    );
NEXUS_Error NEXUS_I2c_ReadNoAddr(
    NEXUS_I2cHandle handle,
    uint16_t chipAddr,
    uint8_t *pData,
    size_t length
    );
NEXUS_Error NEXUS_I2c_ReadNoAddrNoAck(
    NEXUS_I2cHandle handle,
    uint16_t chipAddr,
    uint8_t *pData,
    size_t length
    );
NEXUS_Error NEXUS_I2c_ReadEDDC(
    NEXUS_I2cHandle handle,
    uint8_t chipAddr,
    uint8_t segment,
    uint8_t subAddr,
    uint8_t *pData,
    size_t length
    );
NEXUS_Error NEXUS_I2c_WriteEDDC(
    NEXUS_I2cHandle handle,
    uint8_t chipAddr,
    uint8_t segment,
    uint8_t subAddr,
    const uint8_t *pData,
    size_t length
    );
NEXUS_Error NEXUS_I2c_SwReset(
    NEXUS_I2cHandle handle
    );
typedef enum NEXUS_HdmiVendorSpecificInfoFrame_HDMIVideoFormat
{
    NEXUS_HdmiVendorSpecificInfoFrame_HDMIVideoFormat_eNone,
    NEXUS_HdmiVendorSpecificInfoFrame_HDMIVideoFormat_eExtendedResolution,
    NEXUS_HdmiVendorSpecificInfoFrame_HDMIVideoFormat_e3DFormat,
    NEXUS_HdmiVendorSpecificInfoFrame_HDMIVideoFormat_eMax
} NEXUS_HdmiVendorSpecificInfoFrame_HDMIVideoFormat;
typedef enum NEXUS_HdmiVendorSpecificInfoFrame_HDMIVIC
{
    NEXUS_HdmiVendorSpecificInfoFrame_HDMIVIC_eReserved,
    NEXUS_HdmiVendorSpecificInfoFrame_HDMIVIC_e4Kx2K_2997_30Hz,
    NEXUS_HdmiVendorSpecificInfoFrame_HDMIVIC_e4Kx2K_25Hz,
    NEXUS_HdmiVendorSpecificInfoFrame_HDMIVIC_e4Kx2K_2398_24Hz,
    NEXUS_HdmiVendorSpecificInfoFrame_HDMIVIC_e4Kx2K_SMPTE_24Hz,
    NEXUS_HdmiVendorSpecificInfoFrame_HDMIVIC_eMax
} NEXUS_HdmiVendorSpecificInfoFrame_HDMIVIC;
typedef enum NEXUS_HdmiAviInfoFrame_Colorspace
{
    NEXUS_HdmiAviInfoFrame_Colorspace_eRGB = 0,
    NEXUS_HdmiAviInfoFrame_Colorspace_eYCbCr422,
    NEXUS_HdmiAviInfoFrame_Colorspace_eYCbCr444,
    NEXUS_HdmiAviInfoFrame_Colorspace_eYCbCr420,
    NEXUS_HdmiAviInfoFrame_Colorspace_eMax
} NEXUS_HdmiAviInfoFrame_Colorspace;
typedef enum NEXUS_HdmiAviInfoFrame_ActiveInfo
{
    NEXUS_HdmiAviInfoFrame_ActiveInfo_eInvalid = 0,
    NEXUS_HdmiAviInfoFrame_ActiveInfo_eValid
} NEXUS_HdmiAviInfoFrame_ActiveInfo;
typedef enum NEXUS_HdmiAviInfoFrame_BarInfo
{
    NEXUS_HdmiAviInfoFrame_BarInfo_eInvalid,
    NEXUS_HdmiAviInfoFrame_BarInfo_eVerticalValid,
    NEXUS_HdmiAviInfoFrame_BarInfo_eHorizValid,
    NEXUS_HdmiAviInfoFrame_BarInfo_eVertHorizValid
} NEXUS_HdmiAviInfoFrame_BarInfo;
typedef enum NEXUS_HdmiAviInfoFrame_ScanInfo
{
    NEXUS_HdmiAviInfoFrame_ScanInfo_eNoData,
    NEXUS_HdmiAviInfoFrame_ScanInfo_eOverScanned,
    NEXUS_HdmiAviInfoFrame_ScanInfo_eUnderScanned
} NEXUS_HdmiAviInfoFrame_ScanInfo;
typedef enum NEXUS_HdmiAviInfoFrame_Colorimetry
{
    NEXUS_HdmiAviInfoFrame_Colorimetry_eNoData = 0,
    NEXUS_HdmiAviInfoFrame_Colorimetry_eSmpte170,
    NEXUS_HdmiAviInfoFrame_Colorimetry_eItu709,
    NEXUS_HdmiAviInfoFrame_Colorimetry_eFuture,
    NEXUS_HdmiAviInfoFrame_Colorimetry_eExtended = NEXUS_HdmiAviInfoFrame_Colorimetry_eFuture
} NEXUS_HdmiAviInfoFrame_Colorimetry;
typedef enum NEXUS_HdmiAviInfoFrame_PictureAspectRatio
{
    NEXUS_HdmiAviInfoFrame_PictureAspectRatio_eNoData = 0,
    NEXUS_HdmiAviInfoFrame_PictureAspectRatio_e4_3,
    NEXUS_HdmiAviInfoFrame_PictureAspectRatio_e16_9,
    NEXUS_HdmiAviInfoFrame_PictureAspectRatio_eFuture
} NEXUS_HdmiAviInfoFrame_PictureAspectRatio;
typedef enum NEXUS_HdmiAviInfoFrame_ActiveFormatAspectRatio
{
    NEXUS_HdmiAviInfoFrame_ActiveFormatAspectRatio_ePicture = 8,
    NEXUS_HdmiAviInfoFrame_ActiveFormatAspectRatio_e4_3Center = 9,
    NEXUS_HdmiAviInfoFrame_ActiveFormatAspectRatio_e16_9Center = 10,
    NEXUS_HdmiAviInfoFrame_ActiveFormatAspectRatio_e14_9Center = 11,
    NEXUS_HdmiAviInfoFrame_ActiveFormatAspectRatio_e4_3_Alt14_9Center = 13,
    NEXUS_HdmiAviInfoFrame_ActiveFormatAspectRatio_e16_9_Alt14_9Center = 14,
    NEXUS_HdmiAviInfoFrame_ActiveFormatAspectRatio_e16_9_Alt4_3Center = 15,
    NEXUS_HdmiAviInfoFrame_ActiveFormatAspectRatio_eOther = 0
} NEXUS_HdmiAviInfoFrame_ActiveFormatAspectRatio;
typedef enum NEXUS_HdmiAviInfoFrame_Scaling
{
    NEXUS_HdmiAviInfoFrame_Scaling_eNoScaling = 0,
    NEXUS_HdmiAviInfoFrame_Scaling_eHScaling,
    NEXUS_HdmiAviInfoFrame_Scaling_eVScaling,
    NEXUS_HdmiAviInfoFrame_Scaling_eHVScaling
} NEXUS_HdmiAviInfoFrame_Scaling;
typedef enum NEXUS_HdmiAviInfoFrame_ExtendedColorimetry
{
    NEXUS_HdmiAviInfoFrame_ExtendedColorimetry_exvYCC601 = 0,
    NEXUS_HdmiAviInfoFrame_ExtendedColorimetry_exvYCC709,
    NEXUS_HdmiAviInfoFrame_ExtendedColorimetry_esYCC601,
    NEXUS_HdmiAviInfoFrame_ExtendedColorimetry_eAdobeYCC601,
    NEXUS_HdmiAviInfoFrame_ExtendedColorimetry_eAdobeRGB,
    NEXUS_HdmiAviInfoFrame_ExtendedColorimetry_eItuRBt2020YcCbcCrc,
    NEXUS_HdmiAviInfoFrame_ExtendedColorimetry_eItuRBt2020RGB,
    NEXUS_HdmiAviInfoFrame_ExtendedColorimetry_eItuRBt2020YCbCr = NEXUS_HdmiAviInfoFrame_ExtendedColorimetry_eItuRBt2020RGB,
    NEXUS_HdmiAviInfoFrame_ExtendedColorimetry_eReserved,
    NEXUS_HdmiAviInfoFrame_ExtendedColorimetry_eMax
} NEXUS_HdmiAviInfoFrame_ExtendedColorimetry;
typedef enum NEXUS_HdmiAviInfoFrame_RGBQuantizationRange
{
    NEXUS_HdmiAviInfoFrame_RGBQuantizationRange_eDefault = 0,
    NEXUS_HdmiAviInfoFrame_RGBQuantizationRange_eLimitedRange = 1,
    NEXUS_HdmiAviInfoFrame_RGBQuantizationRange_eFullRange = 2,
    NEXUS_HdmiAviInfoFrame_RGBQuantizationRange_eReserved = 3
} NEXUS_HdmiAviInfoFrame_RGBQuantizationRange;
typedef enum NEXUS_HdmiAviInfoFrame_ITContent
{
    NEXUS_HdmiAviInfoFrame_ITContent_eNoData = 0,
    NEXUS_HdmiAviInfoFrame_ITContent_eITContent = 1
} NEXUS_HdmiAviInfoFrame_ITContent;
typedef enum NEXUS_HdmiAviInfoFrame_ContentType
{
    NEXUS_HdmiAviInfoFrame_ContentType_eGraphics = 0,
    NEXUS_HdmiAviInfoFrame_ContentType_ePhoto,
    NEXUS_HdmiAviInfoFrame_ContentType_eCinema,
    NEXUS_HdmiAviInfoFrame_ContentType_eGame,
    NEXUS_HdmiAviInfoFrame_ContentType_eMax
} NEXUS_HdmiAviInfoFrame_ContentType;
typedef enum NEXUS_HdmiAviInfoFrame_YccQuantizationRange
{
    NEXUS_HdmiAviInfoFrame_YccQuantizationRange_eLimited = 0,
    NEXUS_HdmiAviInfoFrame_YccQuantizationRange_eFull,
    NEXUS_HdmiAviInfoFrame_YccQuantizationRange_eReserved,
    NEXUS_HdmiAviInfoFrame_YccQuantizationRange_eMax
} NEXUS_HdmiAviInfoFrame_YccQuantizationRange;
typedef enum NEXUS_HdmiGamutPacket_MetadataProfile
{
    NEXUS_HdmiGamutPacket_MetadataProfile_eMD0,
    NEXUS_HdmiGamutPacket_MetadataProfile_eMD1,
    NEXUS_HdmiGamutPacket_MetadataProfile_eMD2,
    NEXUS_HdmiGamutPacket_MetadataProfile_eMD3,
    NEXUS_HdmiGamutPacket_MetadataProfile_eMax
} NEXUS_HdmiGamutPacket_MetadataProfile ;
typedef struct NEXUS_HdmiPacket
{
    uint8_t type;
    uint8_t version;
    uint8_t length;
    uint8_t dataBytes[28];
} NEXUS_HdmiPacket;
typedef enum NEXUS_HdmiPacketStatus
{
    NEXUS_HdmiPacketStatus_eNotReceived = 0,
    NEXUS_HdmiPacketStatus_eStopped,
    NEXUS_HdmiPacketStatus_eUpdated,
    NEXUS_HdmiPacketStatus_eMax
} NEXUS_HdmiPacketStatus;
typedef struct NEXUS_HdmiAviInfoFrame
{
    NEXUS_HdmiAviInfoFrame_Colorspace eColorSpace;
    _Bool bOverrideDefaults;
    NEXUS_HdmiAviInfoFrame_ActiveInfo eActiveInfo;
    NEXUS_HdmiAviInfoFrame_BarInfo eBarInfo;
    NEXUS_HdmiAviInfoFrame_ScanInfo eScanInfo;
    NEXUS_HdmiAviInfoFrame_Colorimetry eColorimetry;
    NEXUS_HdmiAviInfoFrame_PictureAspectRatio ePictureAspectRatio;
    NEXUS_HdmiAviInfoFrame_ActiveFormatAspectRatio eActiveFormatAspectRatio;
    NEXUS_HdmiAviInfoFrame_Scaling eScaling;
    uint8_t videoIdCode;
    uint8_t pixelRepeat;
    NEXUS_HdmiAviInfoFrame_ITContent eITContent;
    NEXUS_HdmiAviInfoFrame_ExtendedColorimetry eExtendedColorimetry;
    NEXUS_HdmiAviInfoFrame_RGBQuantizationRange eRGBQuantizationRange;
    NEXUS_HdmiAviInfoFrame_ContentType eContentType;
    NEXUS_HdmiAviInfoFrame_YccQuantizationRange eYccQuantizationRange;
    uint16_t topBarEndLineNumber;
    uint16_t bottomBarStartLineNumber;
    uint16_t leftBarEndPixelNumber;
    uint16_t rightBarEndPixelNumber;
    NEXUS_HdmiPacketStatus packetStatus;
    NEXUS_HdmiPacket packet;
} NEXUS_HdmiAviInfoFrame;
typedef enum NEXUS_HdmiAudioInfoFrame_CodingType
{
    NEXUS_HdmiAudioInfoFrame_CodingType_eReferToStream,
    NEXUS_HdmiAudioInfoFrame_CodingType_ePCM,
    NEXUS_HdmiAudioInfoFrame_CodingType_eAC3,
    NEXUS_HdmiAudioInfoFrame_CodingType_eMPEG1,
    NEXUS_HdmiAudioInfoFrame_CodingType_eMP3,
    NEXUS_HdmiAudioInfoFrame_CodingType_eMPEG2,
    NEXUS_HdmiAudioInfoFrame_CodingType_eAACLC,
    NEXUS_HdmiAudioInfoFrame_CodingType_eDTS,
    NEXUS_HdmiAudioInfoFrame_CodingType_eATRAC,
    NEXUS_HdmiAudioInfoFrame_CodingType_eDSD,
    NEXUS_HdmiAudioInfoFrame_CodingType_eEAC3,
    NEXUS_HdmiAudioInfoFrame_CodingType_eDTSHD,
    NEXUS_HdmiAudioInfoFrame_CodingType_eMLP,
    NEXUS_HdmiAudioInfoFrame_CodingType_eDST,
    NEXUS_HdmiAudioInfoFrame_CodingType_eWMAPro,
    NEXUS_HdmiAudioInfoFrame_CodingType_eUnknown
} NEXUS_HdmiAudioInfoFrame_CodingType;
typedef enum NEXUS_HdmiAudioInfoFrame_ChannelCount
{
    NEXUS_HdmiAudioInfoFrame_ChannelCount_eReferToStreamHeader,
    NEXUS_HdmiAudioInfoFrame_ChannelCount_e2Channels,
    NEXUS_HdmiAudioInfoFrame_ChannelCount_e3Channels,
    NEXUS_HdmiAudioInfoFrame_ChannelCount_e4Channels,
    NEXUS_HdmiAudioInfoFrame_ChannelCount_e5Channels,
    NEXUS_HdmiAudioInfoFrame_ChannelCount_e6Channels,
    NEXUS_HdmiAudioInfoFrame_ChannelCount_e7Channels,
    NEXUS_HdmiAudioInfoFrame_ChannelCount_e8Channels
} NEXUS_HdmiAudioInfoFrame_ChannelCount;
typedef enum NEXUS_HdmiAudioInfoFrame_SampleFrequency
{
    NEXUS_HdmiAudioInfoFrame_SampleFrequency_eReferToStreamHeader,
    NEXUS_HdmiAudioInfoFrame_SampleFrequency_e32,
    NEXUS_HdmiAudioInfoFrame_SampleFrequency_e44_1,
    NEXUS_HdmiAudioInfoFrame_SampleFrequency_e48,
    NEXUS_HdmiAudioInfoFrame_SampleFrequency_e88_2,
    NEXUS_HdmiAudioInfoFrame_SampleFrequency_e96,
    NEXUS_HdmiAudioInfoFrame_SampleFrequency_e176_4,
    NEXUS_HdmiAudioInfoFrame_SampleFrequency_e192
} NEXUS_HdmiAudioInfoFrame_SampleFrequency;
typedef enum NEXUS_HdmiAudioInfoFrame_SampleSize
{
    NEXUS_HdmiAudioInfoFrame_SampleSize_eReferToStreamHeader,
    NEXUS_HdmiAudioInfoFrame_SampleSize_e16,
    NEXUS_HdmiAudioInfoFrame_SampleSize_e20,
    NEXUS_HdmiAudioInfoFrame_SampleSize_e24
} NEXUS_HdmiAudioInfoFrame_SampleSize;
typedef enum NEXUS_HdmiAudioInfoFrame_LevelShift
{
    NEXUS_HdmiAudioInfoFrame_LevelShift_e0db,
    NEXUS_HdmiAudioInfoFrame_LevelShift_e1db,
    NEXUS_HdmiAudioInfoFrame_LevelShift_e2db,
    NEXUS_HdmiAudioInfoFrame_LevelShift_e3db,
    NEXUS_HdmiAudioInfoFrame_LevelShift_e4db,
    NEXUS_HdmiAudioInfoFrame_LevelShift_e5db,
    NEXUS_HdmiAudioInfoFrame_LevelShift_e6db,
    NEXUS_HdmiAudioInfoFrame_LevelShift_e7db,
    NEXUS_HdmiAudioInfoFrame_LevelShift_e8db,
    NEXUS_HdmiAudioInfoFrame_LevelShift_e9db,
    NEXUS_HdmiAudioInfoFrame_LevelShift_e10db,
    NEXUS_HdmiAudioInfoFrame_LevelShift_e11db,
    NEXUS_HdmiAudioInfoFrame_LevelShift_e12db,
    NEXUS_HdmiAudioInfoFrame_LevelShift_e13db,
    NEXUS_HdmiAudioInfoFrame_LevelShift_e14db,
    NEXUS_HdmiAudioInfoFrame_LevelShift_e15db
} NEXUS_HdmiAudioInfoFrame_LevelShift;
typedef enum NEXUS_HdmiAudioInfoFrame_DownMixInhibit
{
    NEXUS_HdmiAudioInfoFrame_DownMixInhibit_ePermitted,
    NEXUS_HdmiAudioInfoFrame_DownMixInhibit_eProhibited
} NEXUS_HdmiAudioInfoFrame_DownMixInhibit;
typedef struct NEXUS_HdmiAudioInfoFrame
{
    _Bool bOverrideDefaults;
    NEXUS_HdmiAudioInfoFrame_ChannelCount eChannelCount;
    NEXUS_HdmiAudioInfoFrame_CodingType eCodingType;
    NEXUS_HdmiAudioInfoFrame_SampleSize eSampleSize;
    NEXUS_HdmiAudioInfoFrame_SampleFrequency eSampleFrequency;
    uint8_t speakerAllocation;
    NEXUS_HdmiAudioInfoFrame_DownMixInhibit eDownMixInhibit;
    NEXUS_HdmiAudioInfoFrame_LevelShift eLevelShift;
    NEXUS_HdmiPacketStatus packetStatus;
    NEXUS_HdmiPacket packet;
} NEXUS_HdmiAudioInfoFrame;
typedef enum NEXUS_HdmiSpdSourceDeviceType
{
    NEXUS_HdmiSpdSourceDeviceType_eUnknown,
    NEXUS_HdmiSpdSourceDeviceType_eDigitalStb,
    NEXUS_HdmiSpdSourceDeviceType_eDvd,
    NEXUS_HdmiSpdSourceDeviceType_eDvhs,
    NEXUS_HdmiSpdSourceDeviceType_eHddVideo,
    NEXUS_HdmiSpdSourceDeviceType_eDvc,
    NEXUS_HdmiSpdSourceDeviceType_eDsc,
    NEXUS_HdmiSpdSourceDeviceType_eVideoCd,
    NEXUS_HdmiSpdSourceDeviceType_eGame,
    NEXUS_HdmiSpdSourceDeviceType_ePc,
    NEXUS_HdmiSpdSourceDeviceType_eBluRayDisc,
    NEXUS_HdmiSpdSourceDeviceType_eSuperAudioCd,
    NEXUS_HdmiSpdSourceDeviceType_eHdDvd,
    NEXUS_HdmiSpdSourceDeviceType_ePmp,
    NEXUS_HdmiSpdSourceDeviceType_eMax
} NEXUS_HdmiSpdSourceDeviceType;
typedef struct NEXUS_HdmiSpdInfoFrame
{
    uint8_t vendorName[8 +1];
    uint8_t description[16 +1];
    NEXUS_HdmiSpdSourceDeviceType deviceType;
    NEXUS_HdmiPacketStatus packetStatus;
    NEXUS_HdmiPacket packet;
} NEXUS_HdmiSpdInfoFrame;
typedef struct NEXUS_HdmiVendorSpecificInfoFrame
{
    uint8_t ieeeRegId[3];
    NEXUS_HdmiVendorSpecificInfoFrame_HDMIVideoFormat hdmiVideoFormat;
    NEXUS_HdmiVendorSpecificInfoFrame_HDMIVIC hdmiVIC;
    NEXUS_Video3DStructure hdmi3DStructure;
    NEXUS_Video3DSubSample hdmi3DExtData;
    NEXUS_HdmiPacketStatus packetStatus;
    NEXUS_HdmiPacket packet;
} NEXUS_HdmiVendorSpecificInfoFrame;
typedef struct NEXUS_HdmiType1DynamicRangeMasteringStaticMetadata
{
    NEXUS_MasteringDisplayColorVolume masteringDisplayColorVolume;
    NEXUS_ContentLightLevel contentLightLevel;
} NEXUS_HdmiType1DynamicRangeMasteringStaticMetadata;
typedef enum NEXUS_HdmiDynamicRangeMasteringStaticMetadataType
{
    NEXUS_HdmiDynamicRangeMasteringStaticMetadataType_e1,
    NEXUS_HdmiDynamicRangeMasteringStaticMetadataType_eMax
} NEXUS_HdmiDynamicRangeMasteringStaticMetadataType;
typedef struct NEXUS_HdmiDynamicRangeMasteringStaticMetadata
{
    NEXUS_HdmiDynamicRangeMasteringStaticMetadataType type;
    struct
    {
        NEXUS_HdmiType1DynamicRangeMasteringStaticMetadata type1;
    } typeSettings;
} NEXUS_HdmiDynamicRangeMasteringStaticMetadata;
typedef struct NEXUS_HdmiDynamicRangeMasteringInfoFrame
{
    NEXUS_VideoEotf eotf;
    NEXUS_HdmiDynamicRangeMasteringStaticMetadata metadata;
} NEXUS_HdmiDynamicRangeMasteringInfoFrame;
typedef struct NEXUS_HdmiHdcpKsv
{
    uint8_t data[5] ;
} NEXUS_HdmiHdcpKsv ;
typedef struct NEXUS_HdmiHdcpDownStreamInfo
{
    uint8_t depth;
    _Bool maxDepthExceeded;
    uint8_t devices;
    _Bool maxDevicesExceeded;
    _Bool isRepeater;
    NEXUS_HdmiHdcpKsv repeaterKsv;
} NEXUS_HdmiHdcpDownStreamInfo;
typedef struct NEXUS_Hdcp2xReceiverIdListData
{
    unsigned deviceCount;
    unsigned depth;
    _Bool maxDevsExceeded;
    _Bool maxCascadeExceeded;
    _Bool hdcp2xLegacyDeviceDownstream;
    _Bool hdcp1DeviceDownstream;
    uint8_t rxIdList[155];
} NEXUS_Hdcp2xReceiverIdListData;
typedef enum NEXUS_HdcpVersion
{
    NEXUS_HdcpVersion_e1x,
    NEXUS_HdcpVersion_e2x,
    NEXUS_HdcpVersion_eMax
} NEXUS_HdcpVersion;
typedef enum NEXUS_Hdcp2xContentStream
{
    NEXUS_Hdcp2xContentStream_eType0,
    NEXUS_Hdcp2xContentStream_eType1,
    NEXUS_Hdcp2xContentStream_eMax
} NEXUS_Hdcp2xContentStream;
typedef enum NEXUS_HdmiEdidColorimetryDbSupport
{
    NEXUS_HdmiEdidColorimetryDbSupport_exvYCC601,
    NEXUS_HdmiEdidColorimetryDbSupport_exvYCC709,
    NEXUS_HdmiEdidColorimetryDbSupport_esYCC601,
    NEXUS_HdmiEdidColorimetryDbSupport_eAdobeYCC601,
    NEXUS_HdmiEdidColorimetryDbSupport_eAdobeRGB,
    NEXUS_HdmiEdidColorimetryDbSupport_eBT2020cYCC,
    NEXUS_HdmiEdidColorimetryDbSupport_eBT2020YCC,
    NEXUS_HdmiEdidColorimetryDbSupport_eBT2020RGB,
    NEXUS_HdmiEdidColorimetryDbSupport_eMax
} NEXUS_HdmiEdidColorimetryDbSupport;
typedef enum NEXUS_HdmiEdidColorimetryDbMetadataProfile
{
    NEXUS_HdmiEdidColorimetryDbMetadataProfile_e0,
    NEXUS_HdmiEdidColorimetryDbMetadataProfile_e1,
    NEXUS_HdmiEdidColorimetryDbMetadataProfile_e2,
    NEXUS_HdmiEdidColorimetryDbMetadataProfile_e3,
    NEXUS_HdmiEdidColorimetryDbMetadataProfile_eMax
} NEXUS_HdmiEdidColorimetryDbMetadataProfile ;
typedef struct NEXUS_HdmiOutputPreEmphasisConfiguration
{
    struct {
     uint32_t minTmdsRate;
     uint32_t maxTmdsRate;
     uint32_t HDMI_TX_PHY_CTL_0;
     uint32_t HDMI_TX_PHY_CTL_1;
     uint32_t HDMI_TX_PHY_CTL_2;
    } tmdsRange[7] ;
} NEXUS_HdmiOutputPreEmphasisConfiguration;
typedef struct NEXUS_HdmiOutput *NEXUS_HdmiOutputHandle;
typedef struct NEXUS_HdmiOutputOpenSettings
{
    NEXUS_I2cHandle i2c;
    NEXUS_HdmiSpdInfoFrame spd;
    _Bool bypassEdidChecking;
    _Bool i2cSoftwareMode;
    unsigned maxEdidRetries;
    unsigned powerPollingInterval;
    unsigned maxRxSenseRetries;
    unsigned rxSenseInterval;
    _Bool manualTmdsControl;
    unsigned hotplugChangeThreshold;
} NEXUS_HdmiOutputOpenSettings;
void NEXUS_HdmiOutput_GetDefaultOpenSettings(
    NEXUS_HdmiOutputOpenSettings *pSettings
    );
NEXUS_HdmiOutputHandle NEXUS_HdmiOutput_Open(
    unsigned index,
    const NEXUS_HdmiOutputOpenSettings *pSettings
    );
void NEXUS_HdmiOutput_Close(
    NEXUS_HdmiOutputHandle output
    );
typedef struct NEXUS_HdmiOutputSettings
{
    _Bool preemphasisEnabled;
    unsigned preFormatChangeAvMuteDelay;
    unsigned postFormatChangeAvMuteDelay;
    NEXUS_VideoFormat outputFormat;
    NEXUS_CallbackDesc hotplugCallback;
    NEXUS_CallbackDesc cecCallback;
    NEXUS_CallbackDesc mhlStandbyCallback;
    _Bool hdmiRxScdcMonitoring ;
    NEXUS_CallbackDesc hdmiRxStatusChanged;
    NEXUS_AudioChannelStatusInfo audioChannelStatusInfo;
    _Bool audioDitherEnabled;
    NEXUS_SpdifOutputBurstType audioBurstType;
    unsigned audioBurstPadding;
    _Bool mpaaDecimationEnabled;
    _Bool autoColorSpace;
    NEXUS_ColorSpace colorSpace;
    unsigned colorDepth;
    _Bool overrideColorRange;
    NEXUS_ColorRange colorRange;
    _Bool overrideMatrixCoefficients;
    NEXUS_MatrixCoefficients matrixCoefficients;
    struct
    {
        _Bool enable;
        uint32_t frequency;
        uint32_t delta;
    } spreadSpectrum;
    _Bool syncOnly;
    unsigned crcQueueSize;
    NEXUS_AudioLoudnessDeviceMode loudnessDeviceMode;
} NEXUS_HdmiOutputSettings;
void NEXUS_HdmiOutput_ReenableHotplugInterrupt(
    NEXUS_HdmiOutputHandle output
    );
void NEXUS_HdmiOutput_GetSettings(
    NEXUS_HdmiOutputHandle output,
    NEXUS_HdmiOutputSettings *pSettings
    );
NEXUS_Error NEXUS_HdmiOutput_SetSettings(
    NEXUS_HdmiOutputHandle output,
    const NEXUS_HdmiOutputSettings *pSettings
    );
typedef struct NEXUS_HdmiOutputAutoLipsyncInfo
{
    uint8_t videoLatency;
    uint8_t audioLatency;
    uint8_t interlacedVideoLatency;
    uint8_t interlacedAudioLatency;
} NEXUS_HdmiOutputAutoLipsyncInfo;
typedef struct NEXUS_HdmiOutputMonitorRange
{
    uint16_t minVertical;
    uint16_t maxVertical;
    uint16_t minHorizontal;
    uint16_t maxHorizontal;
    uint16_t maxPixelClock;
    uint8_t secondaryTiming;
    uint8_t secondaryTimingParameters[7];
} NEXUS_HdmiOutputMonitorRange;
typedef struct NEXUS_HdmiOutputEdidRxVideoCapabilitydb
{
    _Bool valid;
    _Bool selectableRgb;
    _Bool selectableYcc;
} NEXUS_HdmiOutputEdidRxVideoCapabilitydb;
typedef struct NEXUS_HdmiOutputMonitorColorimetry
{
    _Bool extendedColorimetrySupported[NEXUS_HdmiEdidColorimetryDbSupport_eMax];
    _Bool metadataProfileSupported[NEXUS_HdmiEdidColorimetryDbMetadataProfile_eMax];
} NEXUS_HdmiOutputMonitorColorimetry;
typedef struct NEXUS_HdmiOutputTxHardwareStatus
{
    _Bool clockPower;
    _Bool channelPower[3];
    _Bool hotplugInterruptEnabled;
    unsigned hotplugCounter;
    unsigned rxSenseCounter;
    _Bool scrambling ;
    unsigned unstableFormatDetectedCounter;
} NEXUS_HdmiOutputTxHardwareStatus;
typedef struct NEXUS_HdmiOutputRxHardwareStatus
{
    _Bool descrambling;
} NEXUS_HdmiOutputRxHardwareStatus;
typedef struct NEXUS_HdmiOutputStatus
{
    unsigned index;
    _Bool connected;
    _Bool rxPowered;
    NEXUS_VideoFormat videoFormat;
    NEXUS_AspectRatio aspectRatio;
    NEXUS_ColorSpace colorSpace;
    unsigned colorDepth;
    NEXUS_AudioCodec audioFormat;
    unsigned audioSamplingRate;
    unsigned audioSamplingSize;
    unsigned audioChannelCount;
    NEXUS_HdmiOutputTxHardwareStatus txHardwareStatus;
    NEXUS_HdmiOutputRxHardwareStatus rxHardwareStatus ;
    _Bool hdmiDevice;
    char monitorName[14];
    NEXUS_HdmiOutputMonitorRange monitorRange;
    NEXUS_VideoFormat preferredVideoFormat;
    _Bool videoFormatSupported[NEXUS_VideoFormat_eMax];
    uint16_t hdmi3DFormatsSupported[NEXUS_VideoFormat_eMax];
    NEXUS_HdmiOutputMonitorColorimetry monitorColorimetry;
    _Bool audioCodecSupported[NEXUS_AudioCodec_eMax];
    unsigned maxAudioPcmChannels;
    uint8_t physicalAddressA;
    uint8_t physicalAddressB;
    uint8_t physicalAddressC;
    uint8_t physicalAddressD;
    NEXUS_HdmiOutputAutoLipsyncInfo autoLipsyncInfo;
    NEXUS_VideoEotf eotf;
} NEXUS_HdmiOutputStatus;
NEXUS_Error NEXUS_HdmiOutput_GetStatus(
    NEXUS_HdmiOutputHandle output,
    NEXUS_HdmiOutputStatus *pStatus
    );
typedef struct NEXUS_HdmiOutputBasicEdidData
{
    uint8_t vendorID[2];
    uint8_t productID[2];
    uint8_t serialNum[4];
    uint8_t manufWeek;
    uint16_t manufYear;
    uint8_t edidVersion;
    uint8_t edidRevision;
    uint8_t maxHorizSize;
    uint8_t maxVertSize;
    uint8_t extensions;
    uint8_t features;
    char monitorName[14];
    NEXUS_HdmiOutputMonitorRange monitorRange;
    NEXUS_VideoFormat preferredVideoFormat;
} NEXUS_HdmiOutputBasicEdidData;
typedef struct NEXUS_HdmiOutputEdidRxHdmiVsdb
{
    _Bool valid;
    uint8_t version;
    uint8_t tagCode;
    uint8_t ieeeRegId[3];
    uint8_t physicalAddressA;
    uint8_t physicalAddressB;
    uint8_t physicalAddressC;
    uint8_t physicalAddressD;
    _Bool acpIsrcN;
    _Bool deepColor30bit;
    _Bool deepColor36bit;
    _Bool deepColor48bit;
    _Bool deepColorY444;
    _Bool dviDual;
    uint16_t maxTmdsClockRate;
    _Bool latencyFieldsPresent;
    _Bool interlacedLatencyFieldsPresent;
    _Bool hdmiVideoPresent;
    _Bool contentTypeGraphicsText;
    _Bool contentTypePhoto;
    _Bool contentTypeCinema;
    _Bool contentTypeGame;
    uint8_t videoLatency;
    uint8_t audioLatency;
    uint8_t interlacedVideoLatency;
    uint8_t interlacedAudioLatency;
    _Bool hdmi3DPresent;
    uint8_t hdmi3DMultiPresent;
    uint8_t hdmiImageSize;
    uint8_t hdmiVICLen;
    uint8_t hdmi3DLen;
    _Bool underscan;
    _Bool audio;
    _Bool yCbCr444;
    _Bool yCbCr422;
    uint8_t nativeFormatsInDescriptors;
} NEXUS_HdmiOutputEdidRxHdmiVsdb;
typedef struct NEXUS_HdmiOutputEdidRxHdmiForumVsdb
{
    _Bool valid;
    uint8_t tagCode;
    uint8_t version;
    uint16_t maxTMDSCharacterRate;
    _Bool _3dOsdDisparity;
    _Bool dualView;
    _Bool independentView;
    _Bool sub340McscScramble;
    _Bool readRequest;
    _Bool scdc;
    _Bool deepColor420_30bit;
    _Bool deepColor420_36bit;
    _Bool deepColor420_48bit;
} NEXUS_HdmiOutputEdidRxHdmiForumVsdb;
typedef struct NEXUS_HdmiOutputEdidRxHdrdb
{
    _Bool valid;
    _Bool eotfSupported[NEXUS_VideoEotf_eMax];
} NEXUS_HdmiOutputEdidRxHdrdb;
typedef struct NEXUS_HdmiOutputEdidData
{
    _Bool valid;
    NEXUS_HdmiOutputBasicEdidData basicData;
    NEXUS_HdmiOutputEdidRxVideoCapabilitydb videoCapabilitydb;
     NEXUS_HdmiOutputEdidRxHdmiVsdb hdmiVsdb;
    NEXUS_HdmiOutputEdidRxHdmiForumVsdb hdmiForumVsdb;
    NEXUS_HdmiOutputEdidRxHdrdb hdrdb;
    _Bool videoFormatSupported[NEXUS_VideoFormat_eMax];
} NEXUS_HdmiOutputEdidData;
typedef struct NEXUS_HdmiOutputEdidVideoFormatSupport
{
    _Bool yCbCr444rgb444;
    _Bool yCbCr420;
    _Bool yCbCr422;
    struct {
        _Bool framePacking;
        _Bool fieldAlternative;
        _Bool lineAlternative;
        _Bool sideBySideFull;
        _Bool lDepth;
        _Bool lDepthGraphics;
        _Bool topAndBottom;
        _Bool sideBySideHalfHorizontal;
        _Bool sideBySideHalfQuincunx;
    } _3d;
} NEXUS_HdmiOutputEdidVideoFormatSupport;
NEXUS_Error NEXUS_HdmiOutput_GetEdidData(
    NEXUS_HdmiOutputHandle output,
    NEXUS_HdmiOutputEdidData *pEdidData
    );
NEXUS_Error NEXUS_HdmiOutput_GetVideoFormatSupport(
    NEXUS_HdmiOutputHandle output,
    NEXUS_VideoFormat videoFormat,
    NEXUS_HdmiOutputEdidVideoFormatSupport *pVideoFormatSupport
    );
typedef struct NEXUS_HdmiOutputSupportedVideoInfo
{
    uint8_t supportedVideoIDCode[64];
    uint8_t numSupportedVideoDescriptors;
} NEXUS_HdmiOutputSupportedVideoInfo;
NEXUS_Error NEXUS_HdmiOutput_GetBasicEdidData(
    NEXUS_HdmiOutputHandle output,
    NEXUS_HdmiOutputBasicEdidData *pData
    );
typedef struct NEXUS_HdmiOutputEdidBlock
{
    uint8_t data[128];
} NEXUS_HdmiOutputEdidBlock;
NEXUS_Error NEXUS_HdmiOutput_GetEdidBlock(
    NEXUS_HdmiOutputHandle output,
    unsigned blockNum,
    NEXUS_HdmiOutputEdidBlock *pBlock
    );
NEXUS_VideoOutputHandle NEXUS_HdmiOutput_GetVideoConnector(
    NEXUS_HdmiOutputHandle output
    );
NEXUS_AudioOutputHandle NEXUS_HdmiOutput_GetAudioConnector(
    NEXUS_HdmiOutputHandle output
    );
NEXUS_Error NEXUS_HdmiOutput_SetAVMute(
    NEXUS_HdmiOutputHandle handle,
    _Bool mute
    );
typedef struct NEXUS_HdmiVendorSpecificInfoFrame NEXUS_HdmiOutputVendorSpecificInfoFrame;
void NEXUS_HdmiOutput_GetVendorSpecificInfoFrame(
    NEXUS_HdmiOutputHandle handle,
    NEXUS_HdmiVendorSpecificInfoFrame *pVendorSpecificInfoFrame
    );
NEXUS_Error NEXUS_HdmiOutput_SetVendorSpecificInfoFrame(
    NEXUS_HdmiOutputHandle handle,
    const NEXUS_HdmiVendorSpecificInfoFrame *pVendorSpecificInfoFrame
    );
NEXUS_Error NEXUS_HdmiOutput_GetAviInfoFrame(
    NEXUS_HdmiOutputHandle handle,
    NEXUS_HdmiAviInfoFrame *pAviInfoFrame
    );
NEXUS_Error NEXUS_HdmiOutput_SetAviInfoFrame(
    NEXUS_HdmiOutputHandle handle,
    const NEXUS_HdmiAviInfoFrame *pAviInfoFrame
    );
NEXUS_Error NEXUS_HdmiOutput_GetAudioInfoFrame(
    NEXUS_HdmiOutputHandle handle,
    NEXUS_HdmiAudioInfoFrame *pAudioInfoFrame
    );
NEXUS_Error NEXUS_HdmiOutput_SetAudioInfoFrame(
    NEXUS_HdmiOutputHandle handle,
    const NEXUS_HdmiAudioInfoFrame *pAudioInfoFrame
    );
NEXUS_Error NEXUS_HdmiOutput_GetSpdInfoFrame(
    NEXUS_HdmiOutputHandle handle,
    NEXUS_HdmiSpdInfoFrame *pSpdInfoFrame
    );
NEXUS_Error NEXUS_HdmiOutput_SetSpdInfoFrame(
    NEXUS_HdmiOutputHandle handle,
    const NEXUS_HdmiSpdInfoFrame *pSpdInfoFrame
    );
typedef struct NEXUS_HdmiOutputTmdsSignalSettings
{
    _Bool clock ;
    _Bool data ;
} NEXUS_HdmiOutputTmdsSignalSettings ;
NEXUS_Error NEXUS_HdmiOutput_SetTmdsSignal(
    NEXUS_HdmiOutputHandle handle,
    const NEXUS_HdmiOutputTmdsSignalSettings *pSettings
    );
void NEXUS_HdmiOutput_GetTmdsSignal(
    NEXUS_HdmiOutputHandle handle,
    NEXUS_HdmiOutputTmdsSignalSettings *pSettings
    );
NEXUS_Error NEXUS_HdmiOutput_GetSupportedVideoInfo(
    NEXUS_HdmiOutputHandle handle,
    NEXUS_HdmiOutputSupportedVideoInfo *pSupportedVideoInfo
    );
NEXUS_Error NEXUS_HdmiOutput_GetPreEmphasisConfiguration(
    NEXUS_HdmiOutputHandle handle,
    NEXUS_HdmiOutputPreEmphasisConfiguration *pPreEmphasisConfiguration
    );
NEXUS_Error NEXUS_HdmiOutput_SetPreEmphasisConfiguration(
    NEXUS_HdmiOutputHandle handle,
    const NEXUS_HdmiOutputPreEmphasisConfiguration *pPreEmphasisConfiguration
    );
typedef struct NEXUS_HdmiOutputCrcData
{
    uint16_t crc;
} NEXUS_HdmiOutputCrcData;
NEXUS_Error NEXUS_HdmiOutput_GetCrcData(
    NEXUS_HdmiOutputHandle handle,
    NEXUS_HdmiOutputCrcData *pData,
    unsigned numEntries,
    unsigned *pNumEntriesReturned
    );
typedef enum NEXUS_SpdifSamplingFrequency
{
    NEXUS_SpdifSamplingFrequency_e44100 = 0x0,
    NEXUS_SpdifSamplingFrequency_eUnspecified = 0x1,
    NEXUS_SpdifSamplingFrequency_e48000 = 0x2,
    NEXUS_SpdifSamplingFrequency_e32000 = 0x3,
    NEXUS_SpdifSamplingFrequency_e22050 = 0x4,
    NEXUS_SpdifSamplingFrequency_e24000 = 0x6,
    NEXUS_SpdifSamplingFrequency_e88200 = 0x8,
    NEXUS_SpdifSamplingFrequency_e96000 = 0xa,
    NEXUS_SpdifSamplingFrequency_e176400 = 0xc,
    NEXUS_SpdifSamplingFrequency_e192000 = 0xe
} NEXUS_SpdifSamplingFrequency;
typedef enum NEXUS_SpdifStreamType
{
    NEXUS_SpdifStreamType_eLinear = 0,
    NEXUS_SpdifStreamType_eNonlinear = 1
} NEXUS_SpdifStreamType;
typedef enum NEXUS_SpdifWordLength
{
    NEXUS_SpdifWordLength_eUnspecifiedOf20 = 0x0,
    NEXUS_SpdifWordLength_e16Of20 = 0x2,
    NEXUS_SpdifWordLength_e17Of20 = 0xc,
    NEXUS_SpdifWordLength_e18Of20 = 0x4,
    NEXUS_SpdifWordLength_e19Of20 = 0x8,
    NEXUS_SpdifWordLength_e20Of20 = 0xa,
    NEXUS_SpdifWordLength_eUnspecifiedOf24 = 0x1,
    NEXUS_SpdifWordLength_e20Of24 = 0x3,
    NEXUS_SpdifWordLength_e21Of24 = 0xd,
    NEXUS_SpdifWordLength_e22Of24 = 0x5,
    NEXUS_SpdifWordLength_e23Of24 = 0x9,
    NEXUS_SpdifWordLength_e24Of24 = 0xb
} NEXUS_SpdifWordLength;
typedef struct NEXUS_HdmiInputHdcpKsv
{
    uint8_t data[5];
} NEXUS_HdmiInputHdcpKsv;
typedef struct NEXUS_HdmiInputHdcpKey
{
    uint32_t caDataLo;
    uint32_t caDataHi;
    uint32_t tCaDataLo;
    uint32_t tCaDataHi;
    uint32_t hdcpKeyLo;
    uint32_t hdcpKeyHi;
} NEXUS_HdmiInputHdcpKey;
typedef struct NEXUS_HdmiInputHdcpKeyset
{
    NEXUS_HdmiInputHdcpKsv rxBksv;
    uint8_t alg;
    uint8_t custKeyVarL;
    uint8_t custKeyVarH;
    uint8_t custKeySel;
    NEXUS_HdmiInputHdcpKey privateKey[40];
} NEXUS_HdmiInputHdcpKeyset ;
typedef struct NEXUS_HdmiInputHdcpSettings
{
    NEXUS_CallbackDesc hdcpRxChanged ;
    _Bool repeater ;
    unsigned maxDeviceCountSupported;
    unsigned maxDepthSupported;
} NEXUS_HdmiInputHdcpSettings;
typedef enum NEXUS_HdmiInputHdcpKeyStorage
{
    NEXUS_HdmiInputHdcpKeyStorage_eNone,
    NEXUS_HdmiInputHdcpKeyStorage_eOtpROM,
    NEXUS_HdmiInputHdcpKeyStorage_eOtpRAM,
    NEXUS_HdmiInputHdcpKeyStorage_eMax
} NEXUS_HdmiInputHdcpKeyStorage ;
typedef enum NEXUS_HdmiInputHdcpKeySetOtpState
{
    NEXUS_HdmiInputHdcpKeySetOtpState_eNoOtpSupport,
    NEXUS_HdmiInputHdcpKeySetOtpState_eHwError,
    NEXUS_HdmiInputHdcpKeySetOtpState_eCalcInitialized,
    NEXUS_HdmiInputHdcpKeySetOtpState_eCalcRunning,
    NEXUS_HdmiInputHdcpKeySetOtpState_eCrcMatch,
    NEXUS_HdmiInputHdcpKeySetOtpState_eCrcMismatch,
    NEXUS_HdmiInputHdcpKeySetOtpState_eMax
} NEXUS_HdmiInputHdcpKeySetOtpState;
typedef enum NEXUS_HdmiInputHdcpAuthState
{
 NEXUS_HdmiInputHdcpAuthState_eKeysetInitialization,
 NEXUS_HdmiInputHdcpAuthState_eKeysetError,
 NEXUS_HdmiInputHdcpAuthState_eIdle,
 NEXUS_HdmiInputHdcpAuthState_eWaitForKeyloading,
 NEXUS_HdmiInputHdcpAuthState_eWaitForDownstreamKsvs,
 NEXUS_HdmiInputHdcpAuthState_eKsvFifoReady,
 NEXUS_HdmiInputHdcpAuthState_eCalcRunning,
 NEXUS_HdmiInputHdcpAuthState_eCrcMatch,
 NEXUS_HdmiInputHdcpAuthState_eCrcMismatch,
 NEXUS_HdmiInputHdcpAuthState_eMax
} NEXUS_HdmiInputHdcpAuthState ;
typedef enum NEXUS_HdmiInputHdcpState
{
 NEXUS_HdmiInputHdcpState_eUnknown,
 NEXUS_HdmiInputHdcpState_eUnauthenticated,
 NEXUS_HdmiInputHdcpState_eAuthenticated,
 NEXUS_HdmiInputHdcpState_eRepeaterAuthenticated,
 NEXUS_HdmiInputHdcpState_eMax
} NEXUS_HdmiInputHdcpState;
typedef struct NEXUS_HdmiInputHdcpStatus
{
    NEXUS_HdcpVersion version;
    NEXUS_HdmiInputHdcpState hdcpState;
    NEXUS_HdmiInputHdcpKeyStorage eKeyStorage;
    NEXUS_HdmiInputHdcpKeySetOtpState eOtpState;
    NEXUS_HdmiInputHdcpAuthState eAuthState ;
    uint32_t programmedCrc;
    uint32_t computedCrc;
    uint8_t anValue [8] ;
    uint8_t aksvValue [5] ;
    uint8_t bksvValue [5] ;
    NEXUS_Hdcp2xContentStream hdcp2xContentStreamControl;
} NEXUS_HdmiInputHdcpStatus;
typedef struct NEXUS_HdmiInput *NEXUS_HdmiInputHandle;
typedef struct NEXUS_HdmiInputSettings
{
    NEXUS_Timebase timebase;
    NEXUS_CallbackDesc avMuteChanged;
    NEXUS_CallbackDesc sourceChanged;
    _Bool forcePcFormat;
    _Bool autoColorSpace;
    NEXUS_ColorSpace colorSpace;
    _Bool useInternalEdid ;
    _Bool powerDownUnusedPort ;
    struct {
        _Bool equalizationEnabled;
        _Bool externalSwitch;
        _Bool hpdDisconnected ;
        NEXUS_CallbackDesc cecCallback;
        NEXUS_CallbackDesc hotPlugCallback;
    } frontend;
    struct {
        _Bool parseAviInfoframe ;
        _Bool disableI2cSclPullUp ;
        _Bool disableI2cSdaPullUp ;
        _Bool enableHdmiHardwarePassthrough ;
    } hdr ;
    NEXUS_CallbackDesc aviInfoFrameChanged;
    NEXUS_CallbackDesc audioInfoFrameChanged;
    NEXUS_CallbackDesc spdInfoFrameChanged;
    NEXUS_CallbackDesc vendorSpecificInfoFrameChanged;
    NEXUS_CallbackDesc audioContentProtectionChanged;
    NEXUS_CallbackDesc gamutMetadataPacketChanged;
    NEXUS_HeapHandle heap;
    _Bool adcCalibration;
    _Bool secureVideo;
} NEXUS_HdmiInputSettings;
void NEXUS_HdmiInput_GetDefaultSettings(
    NEXUS_HdmiInputSettings *pSettings
    );
NEXUS_HdmiInputHandle NEXUS_HdmiInput_Open(
    unsigned index,
    const NEXUS_HdmiInputSettings *pSettings
    );
NEXUS_HdmiInputHandle NEXUS_HdmiInput_OpenWithEdid(
    unsigned index,
    const NEXUS_HdmiInputSettings *pSettings,
    const uint8_t *edidData,
    uint16_t edidDataSize
    );
void NEXUS_HdmiInput_Close(
    NEXUS_HdmiInputHandle handle
    );
void NEXUS_HdmiInput_GetSettings(
    NEXUS_HdmiInputHandle handle,
    NEXUS_HdmiInputSettings *pSettings
    );
NEXUS_Error NEXUS_HdmiInput_SetSettings(
    NEXUS_HdmiInputHandle handle,
    const NEXUS_HdmiInputSettings *pSettings
    );
typedef struct NEXUS_HdmiInputStatus
{
    _Bool validHdmiStatus ;
    uint8_t hdmiMode;
    uint8_t deviceAttached;
    uint8_t pllLocked;
    _Bool packetErrors;
    _Bool avMute;
    _Bool hdcpRiUpdating;
    _Bool symbolLoss;
    uint32_t lineClock;
    NEXUS_ColorSpace colorSpace;
    unsigned colorDepth;
    NEXUS_AspectRatio aspectRatio;
    uint32_t width;
    uint32_t height;
    _Bool interlaced;
    NEXUS_VideoFormat originalFormat;
    _Bool noSignal;
    uint32_t avWidth;
    uint32_t avHeight;
    uint32_t vertFreq;
    NEXUS_VideoPolarity hPolarity;
    NEXUS_VideoPolarity vPolarity;
    uint32_t vBlank;
    uint32_t hBlank;
    uint8_t pixelRepeat;
    struct {
        uint16_t packets;
        _Bool validSpdifInfo ;
        NEXUS_SpdifStreamType streamType;
        NEXUS_SpdifWordLength wordLength;
        NEXUS_SpdifSamplingFrequency sampleFreq;
    } audio;
} NEXUS_HdmiInputStatus;
NEXUS_Error NEXUS_HdmiInput_GetStatus(
    NEXUS_HdmiInputHandle handle,
    NEXUS_HdmiInputStatus *pStatus
    );
NEXUS_VideoInputHandle NEXUS_HdmiInput_GetVideoConnector(
    NEXUS_HdmiInputHandle handle
    );
NEXUS_AudioInputHandle NEXUS_HdmiInput_GetAudioConnector(
    NEXUS_HdmiInputHandle handle
    );
NEXUS_Error NEXUS_HdmiInput_SetHotPlug(
    NEXUS_HdmiInputHandle handle,
    _Bool status
    );
NEXUS_Error NEXUS_HdmiInput_ConfigureAfterHotPlug(
    NEXUS_HdmiInputHandle handle,
    _Bool status
    );
NEXUS_Error NEXUS_HdmiInput_LoadEdidData(
    NEXUS_HdmiInputHandle handle,
    const uint8_t *dataBytes,
    uint16_t numBytes
    );
NEXUS_Error NEXUS_HdmiInput_UnloadEdidData(
    NEXUS_HdmiInputHandle handle
    );
NEXUS_Error NEXUS_HdmiInput_SetMaster(
    NEXUS_HdmiInputHandle hdmiInput,
    NEXUS_HdmiInputHandle master
    );
void NEXUS_HdmiInput_ToggleHotPlug(
    NEXUS_HdmiInputHandle hdmiInput
    );
typedef enum NEXUS_HdmiOutputHdcpAnValue
{
    NEXUS_HdmiOutputHdcpAnValue_eTestA1B1,
    NEXUS_HdmiOutputHdcpAnValue_eTestA1B2,
    NEXUS_HdmiOutputHdcpAnValue_eTestA2B1,
    NEXUS_HdmiOutputHdcpAnValue_eTestA2B2,
    NEXUS_HdmiOutputHdcpAnValue_eRandom
} NEXUS_HdmiOutputHdcpAnValue;
typedef struct NEXUS_HdmiOutputHdcpKsv
{
    uint8_t data[5];
} NEXUS_HdmiOutputHdcpKsv;
typedef struct NEXUS_HdmiOutputHdcpKey
{
    uint8_t alg;
    uint8_t custKeyVarL;
    uint8_t custKeyVarH;
    uint8_t custKeySel;
    uint32_t caDataLo;
    uint32_t caDataHi;
    uint32_t tCaDataLo;
    uint32_t tCaDataHi;
    uint32_t hdcpKeyLo;
    uint32_t hdcpKeyHi;
} NEXUS_HdmiOutputHdcpKey;
typedef enum NEXUS_HdmiOutputHdcpVersion
{
    NEXUS_HdmiOutputHdcpVersion_eAuto,
    NEXUS_HdmiOutputHdcpVersion_e2_2,
    NEXUS_HdmiOutputHdcpVersion_e1_x,
    NEXUS_HdmiOutputHdcpVersion_eMax
} NEXUS_HdmiOutputHdcpVersion;
typedef struct NEXUS_HdmiOutputHdcpSettings
{
    NEXUS_HdmiOutputHdcpAnValue anValue;
    NEXUS_HdmiOutputHdcpKsv aksv;
    NEXUS_HdmiOutputHdcpKey encryptedKeySet[40];
    _Bool transmitEncrypted;
    _Bool pjCheckEnabled;
    NEXUS_CallbackDesc successCallback;
    NEXUS_CallbackDesc failureCallback;
    NEXUS_CallbackDesc stateChangedCallback;
    unsigned waitForValidVideo;
    unsigned waitForRxR0Margin;
    unsigned waitForKsvFifoMargin;
    unsigned maxDeviceCountSupported;
    unsigned maxDepthSupported;
    NEXUS_Hdcp2xContentStream hdcp2xContentStreamControl;
    NEXUS_HdmiOutputHdcpVersion hdcp_version;
} NEXUS_HdmiOutputHdcpSettings;
void NEXUS_HdmiOutput_GetHdcpSettings(
    NEXUS_HdmiOutputHandle handle,
    NEXUS_HdmiOutputHdcpSettings *pSettings
    );
NEXUS_Error NEXUS_HdmiOutput_SetHdcpSettings(
    NEXUS_HdmiOutputHandle handle,
    const NEXUS_HdmiOutputHdcpSettings *pSettings
    );
NEXUS_Error NEXUS_HdmiOutput_SetHdcpRevokedKsvs(
    NEXUS_HdmiOutputHandle handle,
    const NEXUS_HdmiOutputHdcpKsv *pRevokedKsvs,
    uint16_t numKsvs
    );
NEXUS_Error NEXUS_HdmiOutput_SetHdcp2xBinKeys(
    NEXUS_HdmiOutputHandle handle,
    const uint8_t *pBinFileBuffer,
    uint32_t length
);
NEXUS_Error NEXUS_HdmiOutput_StartHdcpAuthentication(
    NEXUS_HdmiOutputHandle handle
    );
NEXUS_Error NEXUS_HdmiOutput_DisableHdcpAuthentication(
    NEXUS_HdmiOutputHandle handle
    );
NEXUS_Error NEXUS_HdmiOutput_EnableHdcpEncryption(
    NEXUS_HdmiOutputHandle handle
    );
NEXUS_Error NEXUS_HdmiOutput_DisableHdcpEncryption(
    NEXUS_HdmiOutputHandle handle
    );
typedef enum NEXUS_HdmiOutputHdcpState
{
    NEXUS_HdmiOutputHdcpState_eUnpowered,
    NEXUS_HdmiOutputHdcpState_eUnauthenticated,
    NEXUS_HdmiOutputHdcpState_eWaitForValidVideo,
    NEXUS_HdmiOutputHdcpState_eInitializedAuthentication,
    NEXUS_HdmiOutputHdcpState_eWaitForReceiverAuthentication,
    NEXUS_HdmiOutputHdcpState_eReceiverR0Ready,
    NEXUS_HdmiOutputHdcpState_eR0LinkFailure,
    NEXUS_HdmiOutputHdcpState_eReceiverAuthenticated,
    NEXUS_HdmiOutputHdcpState_eWaitForRepeaterReady,
    NEXUS_HdmiOutputHdcpState_eCheckForRepeaterReady,
    NEXUS_HdmiOutputHdcpState_eRepeaterReady,
    NEXUS_HdmiOutputHdcpState_eLinkAuthenticated,
    NEXUS_HdmiOutputHdcpState_eEncryptionEnabled,
    NEXUS_HdmiOutputHdcpState_eRepeaterAuthenticationFailure,
    NEXUS_HdmiOutputHdcpState_eRiLinkIntegrityFailure,
    NEXUS_HdmiOutputHdcpState_ePjLinkIntegrityFailure,
    NEXUS_HdmiOutputHdcpState_eMax
} NEXUS_HdmiOutputHdcpState;
typedef enum NEXUS_HdmiOutputHdcpError
{
    NEXUS_HdmiOutputHdcpError_eSuccess,
    NEXUS_HdmiOutputHdcpError_eRxBksvError,
    NEXUS_HdmiOutputHdcpError_eRxBksvRevoked,
    NEXUS_HdmiOutputHdcpError_eRxBksvI2cReadError,
    NEXUS_HdmiOutputHdcpError_eTxAksvError,
    NEXUS_HdmiOutputHdcpError_eTxAksvI2cWriteError,
    NEXUS_HdmiOutputHdcpError_eReceiverAuthenticationError,
    NEXUS_HdmiOutputHdcpError_eRepeaterAuthenticationError,
    NEXUS_HdmiOutputHdcpError_eRxDevicesExceeded,
    NEXUS_HdmiOutputHdcpError_eRepeaterDepthExceeded,
    NEXUS_HdmiOutputHdcpError_eRepeaterFifoNotReady,
    NEXUS_HdmiOutputHdcpError_eRepeaterDeviceCount0,
    NEXUS_HdmiOutputHdcpError_eRepeaterLinkFailure,
    NEXUS_HdmiOutputHdcpError_eLinkRiFailure,
    NEXUS_HdmiOutputHdcpError_eLinkPjFailure,
    NEXUS_HdmiOutputHdcpError_eFifoUnderflow,
    NEXUS_HdmiOutputHdcpError_eFifoOverflow,
    NEXUS_HdmiOutputHdcpError_eMultipleAnRequest,
    NEXUS_HdmiOutputHdcpError_eMax
} NEXUS_HdmiOutputHdcpError;
typedef struct NEXUS_HdmiOutputHdcpStatus
{
    NEXUS_HdmiOutputHdcpState hdcpState;
    NEXUS_HdmiOutputHdcpError hdcpError;
    _Bool linkReadyForEncryption;
    _Bool transmittingEncrypted;
    _Bool isHdcpRepeater;
    _Bool ksvFifoReady;
    _Bool i2c400Support;
    _Bool hdcp1_1Features;
    _Bool fastReauthentication;
    _Bool hdcp2_2Features;
    struct {
        _Bool hdcp1_xDeviceDownstream;
    } hdcp2_2RxInfo;
    NEXUS_HdmiOutputHdcpKsv bksv;
} NEXUS_HdmiOutputHdcpStatus;
NEXUS_Error NEXUS_HdmiOutput_GetHdcpStatus(
    NEXUS_HdmiOutputHandle handle,
    NEXUS_HdmiOutputHdcpStatus *pStatus
    );
NEXUS_Error NEXUS_HdmiOutput_HdcpGetDownstreamInfo(
    NEXUS_HdmiOutputHandle handle,
    NEXUS_HdmiHdcpDownStreamInfo *pDownstream
    );
NEXUS_Error NEXUS_HdmiOutput_HdcpGetDownstreamKsvs(
    NEXUS_HdmiOutputHandle handle,
    NEXUS_HdmiHdcpKsv *pKsvs,
    unsigned numDevices,
    unsigned *pNumRead
    );
NEXUS_Error NEXUS_HdmiOutput_SetRepeaterInput(
    NEXUS_HdmiOutputHandle handle,
    NEXUS_HdmiInputHandle input
);
NEXUS_Error NEXUS_HdmiOutput_GetHdcp2xReceiverIdListData(
 NEXUS_HdmiOutputHandle handle,
 NEXUS_Hdcp2xReceiverIdListData *pData
);
typedef struct NEXUS_HdDviInputSettings {
    _Bool autoFormat;
    NEXUS_VideoFormat format;
    _Bool enableDe;
    unsigned inputDataMode;
    struct {
        unsigned width;
        unsigned height;
    } formatDetectionTolerance;
    _Bool external;
    struct {
        _Bool enabled;
        uint8_t data[36];
    } custom;
    struct {
        _Bool enabled;
        unsigned horizontal, vertical;
    } startPosition;
    NEXUS_ColorSpace colorSpace;
    NEXUS_ColorPrimaries colorPrimaries;
    NEXUS_MatrixCoefficients matrixCoef;
    NEXUS_TransferCharacteristics transferCharacteristics;
} NEXUS_HdDviInputSettings;
typedef struct NEXUS_HdDviInput *NEXUS_HdDviInputHandle;
void NEXUS_HdDviInput_GetDefaultSettings(
    NEXUS_HdDviInputSettings *pSettings
    );
NEXUS_HdDviInputHandle NEXUS_HdDviInput_Open(
    unsigned index,
    const NEXUS_HdDviInputSettings *pSettings
    );
void NEXUS_HdDviInput_Close(
    NEXUS_HdDviInputHandle hdDviInput
    );
void NEXUS_HdDviInput_GetSettings(
    NEXUS_HdDviInputHandle hdDviInput,
    NEXUS_HdDviInputSettings *pSettings
    );
NEXUS_Error NEXUS_HdDviInput_SetSettings(
    NEXUS_HdDviInputHandle hdDviInput,
    const NEXUS_HdDviInputSettings *pSettings
    );
NEXUS_VideoInputHandle NEXUS_HdDviInput_GetConnector(
    NEXUS_HdDviInputHandle hdDviInput
    );
typedef struct NEXUS_HdDviInputStatus
{
    NEXUS_VideoFormat videoFormat;
    NEXUS_AspectRatio aspectRatio;
} NEXUS_HdDviInputStatus;
NEXUS_Error NEXUS_HdDviInput_GetStatus(
    NEXUS_HdDviInputHandle hdDviInput,
    NEXUS_HdDviInputStatus *pStatus
    );
typedef enum NEXUS_SimpleDecoderDisableMode
{
    NEXUS_SimpleDecoderDisableMode_eSuccess,
    NEXUS_SimpleDecoderDisableMode_eFail,
    NEXUS_SimpleDecoderDisableMode_eFailOnStart,
    NEXUS_SimpleDecoderDisableMode_eMax
} NEXUS_SimpleDecoderDisableMode;
typedef struct NEXUS_PictureCtrlDitherSettings
{
    _Bool reduceSmooth;
    _Bool smoothEnable;
    uint32_t smoothLimit;
} NEXUS_PictureCtrlDitherSettings;
typedef struct NEXUS_PictureCtrlCmsParameters
{
    uint32_t red;
    uint32_t green;
    uint32_t blue;
    uint32_t cyan;
    uint32_t magenta;
    uint32_t yellow;
} NEXUS_PictureCtrlCmsParameters;
typedef struct NEXUS_PictureCtrlCmsSettings
{
    NEXUS_PictureCtrlCmsParameters saturationGain;
    NEXUS_PictureCtrlCmsParameters hueGain;
} NEXUS_PictureCtrlCmsSettings;
typedef struct NEXUS_PictureCtrlSharpnessValue
{
    _Bool enable;
    uint32_t lumaControlCore;
    uint32_t lumaControlGain;
    uint32_t lumaControlBlur;
    _Bool lumaCtrlSoften;
    _Bool lumaCtrlHOnly;
    uint32_t lumaPeakingHAvoid;
    uint32_t lumaPeakingVAvoid;
    uint32_t lumaPeakingPeakLimit;
    uint32_t lumaPeakingPeakValue;
    uint32_t chromaControlCore;
    _Bool chromaCtrlWideChroma;
    uint32_t chromaControlFalseColor;
    uint32_t chromaControlGain;
    _Bool chromaCtrlHOnly;
    uint32_t wideLumaControlCore;
    uint32_t wideLumaControlMode;
} NEXUS_PictureCtrlSharpnessValue;
typedef struct NEXUS_PictureCtrlContrastStretch
{
 _Bool enabled;
    int gain;
    int gainShift;
    int filterNum;
    int filterDenom;
    int dynamicContrastBlackGain;
    int dynamicContrastWhiteGain;
    uint16_t dynamicContrastBlackLimit;
    uint16_t dynamicContrastWhiteLimit;
    uint16_t dynamicContrastEstCurMaxPt;
    uint16_t dynamicContrastEstCurMinPt;
    _Bool dynamicBacklightControl;
    int32_t ireTable[(17) -1];
    uint32_t dcTable1[(15) * (17)];
    uint32_t dcTable2[(15) * (17)];
} NEXUS_PictureCtrlContrastStretch;
typedef struct NEXUS_LumaStatistics
{
    uint32_t average;
    uint32_t min;
    uint32_t max;
    uint32_t histogram[(16)];
    uint32_t levelStats[(4)];
} NEXUS_LumaStatistics;
typedef struct NEXUS_PictureCtrlCommonSettings
{
    int16_t contrast;
    int16_t saturation;
    int16_t hue;
    int16_t brightness;
    _Bool colorTempEnabled;
    int16_t colorTemp;
    _Bool sharpnessEnable;
    int16_t sharpness;
} NEXUS_PictureCtrlCommonSettings;
typedef struct
{
    uint16_t blueStretchOffset;
    uint16_t blueStretchSlope;
} NEXUS_BlueStretchSettings;
typedef struct NEXUS_PictureCtrlAdvColorSettings
{
    _Bool attenuationRbgEnabled;
    unsigned attenuationR;
    unsigned attenuationG;
    unsigned attenuationB;
    int16_t offsetR;
    int16_t offsetG;
    int16_t offsetB;
    int16_t fleshTone;
    int16_t greenBoost;
    int16_t blueBoost;
    NEXUS_BlueStretchSettings blueStretchSettings;
} NEXUS_PictureCtrlAdvColorSettings;
typedef struct NEXUS_PictureControlColorCorrectionSettings
{
    _Bool enabled;
    unsigned gammaId;
    unsigned colorId;
} NEXUS_PictureControlColorCorrectionSettings;
typedef enum NEXUS_ColorClipMode
{
    NEXUS_ColorClipMode_eNone = 0,
    NEXUS_ColorClipMode_eWhite,
    NEXUS_ColorClipMode_eBlack,
    NEXUS_ColorClipMode_eBoth,
    NEXUS_ColorClipMode_eMax
} NEXUS_ColorClipMode;
typedef struct NEXUS_PictureCtrlColorClipSettings
{
    uint32_t crYSlopeA;
    uint32_t crYSlopeB;
    uint32_t cbYSlopeA;
    uint32_t cbYSlopeB;
    uint32_t crJoint;
    uint32_t cbJoint;
    _Bool extendedWhite;
    _Bool extendedBlack;
    NEXUS_ColorClipMode colorClipMode;
} NEXUS_PictureCtrlColorClipSettings;
typedef enum NEXUS_VideoImageInputType
{
    NEXUS_VideoImageInput_eMfd,
    NEXUS_VideoImageInput_eVfd,
    NEXUS_VideoImageInput_eMax
} NEXUS_VideoImageInputType;
typedef struct NEXUS_VideoImageInput *NEXUS_VideoImageInputHandle;
typedef struct NEXUS_VideoImageInputSettings {
    NEXUS_VideoImageInputType type;
    NEXUS_CallbackDesc imageCallback;
    unsigned qScale;
    _Bool duplicate;
    NEXUS_HeapHandle heap;
    _Bool progressiveScan1080;
    unsigned fifoSize;
    _Bool lowDelayMode;
    NEXUS_StcChannelHandle stcChannel;
    _Bool tsmEnabled;
    NEXUS_CallbackDesc ptsError;
    NEXUS_CallbackDesc firstPtsPassed;
} NEXUS_VideoImageInputSettings;
typedef struct NEXUS_VideoImageInputSurfaceSettings {
    unsigned displayVsyncs;
    _Bool infront;
    uint32_t pts;
    _Bool ptsValid;
    NEXUS_VideoFrameRate frameRate;
    NEXUS_AspectRatio aspectRatio;
    struct {
        unsigned x, y;
    } sampleAspectRatio;
    NEXUS_PictureCoding pictureCoding;
    NEXUS_PictureScan sourceFormat;
    NEXUS_PictureScan sequence;
    _Bool endOfStream;
    NEXUS_PicturePullDown pullDown;
    NEXUS_StripedSurfaceHandle stripedSurface;
} NEXUS_VideoImageInputSurfaceSettings;
void NEXUS_VideoImageInput_GetDefaultSurfaceSettings(
    NEXUS_VideoImageInputSurfaceSettings *pSettings
    );
void NEXUS_VideoImageInput_GetDefaultSettings(
    NEXUS_VideoImageInputSettings *pSettings
    );
NEXUS_VideoImageInputHandle NEXUS_VideoImageInput_Open(
    unsigned index,
    const NEXUS_VideoImageInputSettings *pSettings
    );
void NEXUS_VideoImageInput_Close(
    NEXUS_VideoImageInputHandle videoImage
    );
NEXUS_Error NEXUS_VideoImageInput_PushSurface(
    NEXUS_VideoImageInputHandle imageInput,
    NEXUS_SurfaceHandle image,
    const NEXUS_VideoImageInputSurfaceSettings *pSettings
    );
NEXUS_Error NEXUS_VideoImageInput_RecycleSurface(
    NEXUS_VideoImageInputHandle imageInput,
    NEXUS_SurfaceHandle *recycled,
    size_t num_entries,
    size_t *num_returned
    );
NEXUS_Error NEXUS_VideoImageInput_CheckSurfaceCompletion(
    NEXUS_VideoImageInputHandle imageInput,
    NEXUS_SurfaceHandle image
    );
NEXUS_Error NEXUS_VideoImageInput_SetNextSurface(
    NEXUS_VideoImageInputHandle imageInput,
    NEXUS_SurfaceHandle image
    );
NEXUS_Error NEXUS_VideoImageInput_SetSurface(
    NEXUS_VideoImageInputHandle imageInput,
    NEXUS_SurfaceHandle image
    );
void NEXUS_VideoImageInput_GetSettings(
    NEXUS_VideoImageInputHandle imageInput,
    NEXUS_VideoImageInputSettings *pSettings
    );
NEXUS_Error NEXUS_VideoImageInput_SetSettings(
    NEXUS_VideoImageInputHandle imageInput,
    const NEXUS_VideoImageInputSettings *pSettings
    );
NEXUS_VideoInputHandle NEXUS_VideoImageInput_GetConnector(
    NEXUS_VideoImageInputHandle imageInput
    );
typedef struct NEXUS_VideoImageInputStatus
{
    unsigned memcIndex;
    unsigned secondaryMemcIndex;
} NEXUS_VideoImageInputStatus;
NEXUS_Error NEXUS_VideoImageInput_GetStatus(
    NEXUS_VideoImageInputHandle imageInput,
    NEXUS_VideoImageInputStatus *pStatus
    );
void NEXUS_VideoDecoder_Reset(
    NEXUS_VideoDecoderHandle handle
    );
typedef struct NEXUS_VideoDecoderExtendedStatus
{
    unsigned dataReadyCount;
    NEXUS_PicturePolarity interruptPolarity;
    NEXUS_PicturePolarity sourcePolarity;
    _Bool isMpeg1;
    _Bool isYCbCr422;
    _Bool fieldChrominanceInterpolationMode;
    uint32_t adjQp;
    _Bool pictureRepeatFlag;
    uint32_t luminanceNMBY;
    uint32_t chrominanceNMBY;
    unsigned stripeWidth;
    _Bool lastPictureFlag;
    _Bool captureCrc;
    uint32_t idrPicID;
    int32_t picOrderCnt;
    uint32_t sourceClipTop;
    uint32_t sourceClipLeft;
    uint32_t lumaRangeRemapping;
    uint32_t chromaRangeRemapping;
    struct {
        int mainIndex;
        int mainSwRaveIndex;
        int enhancementIndex;
        int enhancementSwRaveIndex;
    } rave;
    struct {
        unsigned firmware;
    } version;
} NEXUS_VideoDecoderExtendedStatus;
NEXUS_Error NEXUS_VideoDecoder_GetExtendedStatus(
    NEXUS_VideoDecoderHandle handle,
    NEXUS_VideoDecoderExtendedStatus *pStatus
    );
void NEXUS_VideoDecoder_GetExtendedSettings(
    NEXUS_VideoDecoderHandle handle,
    NEXUS_VideoDecoderExtendedSettings *pSettings
    );
NEXUS_Error NEXUS_VideoDecoder_SetExtendedSettings(
    NEXUS_VideoDecoderHandle handle,
    const NEXUS_VideoDecoderExtendedSettings *pSettings
    );
NEXUS_Error NEXUS_VideoDecoder_Get3DTVStatus(
    NEXUS_VideoDecoderHandle handle,
    NEXUS_VideoDecoder3DTVStatus *pStatus
    );
NEXUS_StripedSurfaceHandle NEXUS_VideoDecoder_CreateStripedSurface(
    NEXUS_VideoDecoderHandle handle
    );
void NEXUS_VideoDecoder_DestroyStripedSurface(
    NEXUS_VideoDecoderHandle videoDecoder,
    NEXUS_StripedSurfaceHandle stripedSurface
    );
NEXUS_Error NEXUS_VideoDecoder_CreateStripedMosaicSurfaces(
    NEXUS_VideoDecoderHandle videoDecoder,
    NEXUS_StripedSurfaceHandle *pStripedSurfaces,
    unsigned int maxSurfaces,
    unsigned int *pSurfaceCount
    );
void NEXUS_VideoDecoder_DestroyStripedMosaicSurfaces(
    NEXUS_VideoDecoderHandle videoDecoder,
    const NEXUS_StripedSurfaceHandle *pStripedSurfaces,
    unsigned int surfaceCount
    );
NEXUS_Error NEXUS_VideoDecoder_GetMostRecentPts(
    NEXUS_VideoDecoderHandle handle,
    uint32_t *pPts
    );
NEXUS_Error NEXUS_VideoDecoderModule_SetDebugLog(
    unsigned avdCore,
    _Bool enabled
    );
NEXUS_Error NEXUS_VideoDecoderModule_ReadDebugLog(
    unsigned avdCore,
    void *buffer,
    unsigned bufferSize,
    unsigned *pAmountRead
    );
typedef struct NEXUS_VideoDecoderModuleDebugCommand
{
    char command[128];
} NEXUS_VideoDecoderModuleDebugCommand;
NEXUS_Error NEXUS_VideoDecoderModule_SendDebugCommand(
    unsigned avdCore,
    const NEXUS_VideoDecoderModuleDebugCommand *pCommand
    );
NEXUS_Error NEXUS_VideoDecoder_GetCrcData(
    NEXUS_VideoDecoderHandle handle,
    NEXUS_VideoDecoderCrc *pEntries,
    unsigned numEntries,
    unsigned *pNumReturned
    );
NEXUS_Error NEXUS_VideoDecoder_GetFifoStatus(
    NEXUS_VideoDecoderHandle videoDecoder,
    NEXUS_VideoDecoderFifoStatus *pStatus
    );
void NEXUS_VideoDecoderModule_PrintDecoders(void);
typedef struct NEXUS_SimpleVideoDecoder *NEXUS_SimpleVideoDecoderHandle;
NEXUS_SimpleVideoDecoderHandle NEXUS_SimpleVideoDecoder_Acquire(
    unsigned index
    );
void NEXUS_SimpleVideoDecoder_Release(
    NEXUS_SimpleVideoDecoderHandle handle
    );
typedef struct NEXUS_SimpleVideoDecoderStartSettings
{
    NEXUS_VideoDecoderStartSettings settings;
    unsigned maxWidth, maxHeight;
    _Bool displayEnabled;
    _Bool smoothResolutionChange;
    _Bool lowDelayImageInput;
} NEXUS_SimpleVideoDecoderStartSettings;
NEXUS_Error NEXUS_SimpleVideoDecoder_SetStcChannel(
    NEXUS_SimpleVideoDecoderHandle handle,
    NEXUS_SimpleStcChannelHandle stcChannel
    );
void NEXUS_SimpleVideoDecoder_GetDefaultStartSettings(
    NEXUS_SimpleVideoDecoderStartSettings *pSettings
    );
NEXUS_Error NEXUS_SimpleVideoDecoder_Start(
    NEXUS_SimpleVideoDecoderHandle handle,
    const NEXUS_SimpleVideoDecoderStartSettings *pSettings
    );
void NEXUS_SimpleVideoDecoder_Stop(
    NEXUS_SimpleVideoDecoderHandle handle
    );
void NEXUS_SimpleVideoDecoder_StopAndFree(
    NEXUS_SimpleVideoDecoderHandle handle
    );
typedef struct NEXUS_SimpleVideoDecoderStartCaptureSettings
{
    _Bool displayEnabled;
    NEXUS_SurfaceHandle surface[3];
    _Bool forceFrameDestripe;
    _Bool secure;
} NEXUS_SimpleVideoDecoderStartCaptureSettings;
void NEXUS_SimpleVideoDecoder_GetDefaultStartCaptureSettings(
    NEXUS_SimpleVideoDecoderStartCaptureSettings *pSettings
    );
NEXUS_Error NEXUS_SimpleVideoDecoder_StartCapture(
    NEXUS_SimpleVideoDecoderHandle handle,
    const NEXUS_SimpleVideoDecoderStartCaptureSettings *pSettings
    );
void NEXUS_SimpleVideoDecoder_StopCapture(
    NEXUS_SimpleVideoDecoderHandle handle
    );
typedef struct NEXUS_VideoDecoderFrameStatus NEXUS_SimpleVideoDecoderCaptureStatus;
NEXUS_Error NEXUS_SimpleVideoDecoder_GetCapturedSurfaces(
    NEXUS_SimpleVideoDecoderHandle handle,
    NEXUS_SurfaceHandle *pSurface,
    NEXUS_VideoDecoderFrameStatus *pStatus,
    unsigned numEntries,
    unsigned *pNumReturned
    );
void NEXUS_SimpleVideoDecoder_RecycleCapturedSurfaces(
    NEXUS_SimpleVideoDecoderHandle handle,
    const NEXUS_SurfaceHandle *pSurface,
    unsigned numEntries
    );
NEXUS_Error NEXUS_SimpleVideoDecoder_GetDecodedFrames(
    NEXUS_SimpleVideoDecoderHandle handle,
    NEXUS_VideoDecoderFrameStatus *pStatus,
    unsigned numEntries,
    unsigned *pNumEntriesReturned
    );
void NEXUS_SimpleVideoDecoder_GetDefaultReturnFrameSettings(
    NEXUS_VideoDecoderReturnFrameSettings *pSettings
    );
NEXUS_Error NEXUS_SimpleVideoDecoder_ReturnDecodedFrames(
    NEXUS_SimpleVideoDecoderHandle handle,
    const NEXUS_VideoDecoderReturnFrameSettings *pSettings,
    unsigned numFrames
    );
NEXUS_Error NEXUS_SimpleVideoDecoder_GetStatus(
    NEXUS_SimpleVideoDecoderHandle handle,
    NEXUS_VideoDecoderStatus *pStatus
    );
NEXUS_Error NEXUS_SimpleVideoDecoder_GetExtendedStatus(
    NEXUS_SimpleVideoDecoderHandle handle,
    NEXUS_VideoDecoderExtendedStatus *pStatus
    );
void NEXUS_SimpleVideoDecoder_GetStreamInformation(
    NEXUS_SimpleVideoDecoderHandle handle,
    NEXUS_VideoDecoderStreamInformation *pStreamInfo
    );
NEXUS_Error NEXUS_SimpleVideoDecoder_Get3DTVStatus(
    NEXUS_SimpleVideoDecoderHandle handle,
    NEXUS_VideoDecoder3DTVStatus *pStatus
    );
void NEXUS_SimpleVideoDecoder_Flush(
    NEXUS_SimpleVideoDecoderHandle handle
    );
void NEXUS_SimpleVideoDecoder_GetTrickState(
    NEXUS_SimpleVideoDecoderHandle handle,
    NEXUS_VideoDecoderTrickState *pSettings
    );
NEXUS_Error NEXUS_SimpleVideoDecoder_SetTrickState(
    NEXUS_SimpleVideoDecoderHandle handle,
    const NEXUS_VideoDecoderTrickState *pSettings
    );
NEXUS_Error NEXUS_SimpleVideoDecoder_FrameAdvance(
    NEXUS_SimpleVideoDecoderHandle handle
    );
void NEXUS_SimpleVideoDecoder_GetPlaybackSettings(
    NEXUS_SimpleVideoDecoderHandle handle,
    NEXUS_VideoDecoderPlaybackSettings *pSettings
    );
NEXUS_Error NEXUS_SimpleVideoDecoder_SetPlaybackSettings(
    NEXUS_SimpleVideoDecoderHandle handle,
    const NEXUS_VideoDecoderPlaybackSettings *pSettings
    );
typedef struct NEXUS_SimpleVideoDecoderClientSettings
{
    NEXUS_CallbackDesc resourceChanged;
    NEXUS_VideoWindowAfdSettings afdSettings;
    _Bool closedCaptionRouting;
} NEXUS_SimpleVideoDecoderClientSettings;
void NEXUS_SimpleVideoDecoder_GetClientSettings(
    NEXUS_SimpleVideoDecoderHandle handle,
    NEXUS_SimpleVideoDecoderClientSettings *pSettings
    );
NEXUS_Error NEXUS_SimpleVideoDecoder_SetClientSettings(
    NEXUS_SimpleVideoDecoderHandle handle,
    const NEXUS_SimpleVideoDecoderClientSettings *pSettings
    );
typedef struct NEXUS_SimpleVideoDecoderClientStatus
{
    _Bool enabled;
    unsigned numDroppedCaptureSurfaces;
    uint32_t afdValue;
} NEXUS_SimpleVideoDecoderClientStatus;
NEXUS_Error NEXUS_SimpleVideoDecoder_GetClientStatus(
    NEXUS_SimpleVideoDecoderHandle handle,
    NEXUS_SimpleVideoDecoderClientStatus *pStatus
    );
void NEXUS_SimpleVideoDecoder_GetSettings(
    NEXUS_SimpleVideoDecoderHandle handle,
    NEXUS_VideoDecoderSettings *pSettings
    );
NEXUS_Error NEXUS_SimpleVideoDecoder_SetSettings(
    NEXUS_SimpleVideoDecoderHandle handle,
    const NEXUS_VideoDecoderSettings *pSettings
    );
void NEXUS_SimpleVideoDecoder_GetExtendedSettings(
    NEXUS_SimpleVideoDecoderHandle handle,
    NEXUS_VideoDecoderExtendedSettings *pSettings
    );
NEXUS_Error NEXUS_SimpleVideoDecoder_SetExtendedSettings(
    NEXUS_SimpleVideoDecoderHandle handle,
    const NEXUS_VideoDecoderExtendedSettings *pSettings
    );
NEXUS_Error NEXUS_SimpleVideoDecoder_SetStartPts(
    NEXUS_SimpleVideoDecoderHandle handle,
    uint32_t pts
    );
NEXUS_Error NEXUS_SimpleVideoDecoder_GetNextPts(
    NEXUS_SimpleVideoDecoderHandle handle,
    uint32_t *pPts
    );
NEXUS_Error NEXUS_SimpleVideoDecoder_ReadUserDataBuffer(
    NEXUS_SimpleVideoDecoderHandle handle,
    void *pBuffer,
    size_t bufferSize,
    size_t *pBytesCopied
    );
void NEXUS_SimpleVideoDecoder_FlushUserData(
    NEXUS_SimpleVideoDecoderHandle videoDecoder
    );
void NEXUS_SimpleVideoDecoder_SetCacheEnabled(
    NEXUS_SimpleVideoDecoderHandle handle,
    _Bool enabled
    );
NEXUS_Error NEXUS_SimpleVideoDecoder_GetFifoStatus(
    NEXUS_SimpleVideoDecoderHandle videoDecoder,
    NEXUS_VideoDecoderFifoStatus *pStatus
    );
typedef struct NEXUS_SimpleVideoDecoderPictureQualitySettings
{
    NEXUS_PictureCtrlCommonSettings common;
    NEXUS_PictureCtrlAdvColorSettings advColor;
    NEXUS_PictureCtrlContrastStretch constrastStretch;
    NEXUS_VideoWindowDnrSettings dnr;
    NEXUS_VideoWindowAnrSettings anr;
    NEXUS_VideoWindowMadSettings mad;
    NEXUS_VideoWindowScalerSettings scaler;
} NEXUS_SimpleVideoDecoderPictureQualitySettings;
void NEXUS_SimpleVideoDecoder_GetPictureQualitySettings(
    NEXUS_SimpleVideoDecoderHandle handle,
    NEXUS_SimpleVideoDecoderPictureQualitySettings *pSettings
    );
NEXUS_Error NEXUS_SimpleVideoDecoder_SetPictureQualitySettings(
    NEXUS_SimpleVideoDecoderHandle handle,
    const NEXUS_SimpleVideoDecoderPictureQualitySettings *pSettings
    );
NEXUS_VideoImageInputHandle NEXUS_SimpleVideoDecoder_StartImageInput(
    NEXUS_SimpleVideoDecoderHandle handle,
    const NEXUS_SimpleVideoDecoderStartSettings *pStartSettings
    );
void NEXUS_SimpleVideoDecoder_StopImageInput(
    NEXUS_SimpleVideoDecoderHandle handle
    );
NEXUS_Error NEXUS_SimpleVideoDecoder_StartHdmiInput(
    NEXUS_SimpleVideoDecoderHandle handle,
    NEXUS_HdmiInputHandle hdmiInput,
    const NEXUS_SimpleVideoDecoderStartSettings *pStartSettings
    );
void NEXUS_SimpleVideoDecoder_StopHdmiInput(
    NEXUS_SimpleVideoDecoderHandle handle
    );
NEXUS_Error NEXUS_SimpleVideoDecoder_StartHdDviInput(
    NEXUS_SimpleVideoDecoderHandle handle,
    NEXUS_HdDviInputHandle hdDviInput,
    const NEXUS_SimpleVideoDecoderStartSettings *pStartSettings
    );
void NEXUS_SimpleVideoDecoder_StopHdDviInput(
    NEXUS_SimpleVideoDecoderHandle handle
    );
NEXUS_Error NEXUS_SimpleVideoDecoder_GetCrcData(
    NEXUS_SimpleVideoDecoderHandle handle,
    NEXUS_VideoDecoderCrc *pEntries,
    unsigned numEntries,
    unsigned *pNumReturned
    );
NEXUS_Error NEXUS_SimpleVideoDecoder_GetVideoInputCrcData(
    NEXUS_SimpleVideoDecoderHandle handle,
    NEXUS_VideoInputCrcData *pEntries,
    unsigned numEntries,
    unsigned *pNumReturned
    );
NEXUS_Error NEXUS_SimpleVideoDecoder_SetSdOverride(
    NEXUS_SimpleVideoDecoderHandle handle,
    _Bool enabled
    );
NEXUS_Error NEXUS_SimpleVideoDecoder_ReadMultiPassDqtData(
    NEXUS_SimpleVideoDecoderHandle handle,
    NEXUS_VideoDecoderMultiPassDqtData *pData
    );
typedef struct NEXUS_SimpleAudioDecoder *NEXUS_SimpleAudioDecoderHandle;
NEXUS_SimpleAudioDecoderHandle NEXUS_SimpleAudioDecoder_Acquire(
    unsigned index
    );
void NEXUS_SimpleAudioDecoder_Release(
    NEXUS_SimpleAudioDecoderHandle handle
    );
typedef enum NEXUS_SimpleAudioDecoderSelector {
    NEXUS_SimpleAudioDecoderSelector_ePrimary,
    NEXUS_SimpleAudioDecoderSelector_eSecondary,
    NEXUS_SimpleAudioDecoderSelector_eDescription,
    NEXUS_SimpleAudioDecoderSelector_eMax
} NEXUS_SimpleAudioDecoderSelector;
typedef struct NEXUS_SimpleAudioDecoderStatus
{
    NEXUS_AudioDecoderStatus status[NEXUS_SimpleAudioDecoderSelector_eMax];
} NEXUS_SimpleAudioDecoderStatus;
typedef struct NEXUS_SimpleAudioDecoderProcessorSettings
{
    struct {
        _Bool connected;
        NEXUS_AudioFadeSettings settings;
    } fade;
    struct {
        _Bool connected;
        NEXUS_KaraokeVocalSettings settings;
    } karaokeVocal;
} NEXUS_SimpleAudioDecoderProcessorSettings;
typedef struct NEXUS_SimpleAudioDecoderStartSettings
{
    NEXUS_AudioDecoderStartSettings primary;
    NEXUS_AudioDecoderStartSettings secondary;
    NEXUS_AudioDecoderStartSettings description;
    struct {
        _Bool pcm, compressed;
    } primer;
    _Bool master;
    struct {
        _Bool enabled;
        unsigned sampleRate;
        NEXUS_CallbackDesc dataCallback;
    } passthroughBuffer;
} NEXUS_SimpleAudioDecoderStartSettings;
typedef struct NEXUS_SimpleAudioDecoderSettings
{
    NEXUS_AudioDecoderSettings primary;
    NEXUS_AudioDecoderSettings secondary;
    NEXUS_AudioDecoderSettings description;
    NEXUS_SimpleAudioDecoderProcessorSettings processorSettings[NEXUS_SimpleAudioDecoderSelector_eMax];
} NEXUS_SimpleAudioDecoderSettings;
NEXUS_Error NEXUS_SimpleAudioDecoder_SetStcChannel(
    NEXUS_SimpleAudioDecoderHandle handle,
    NEXUS_SimpleStcChannelHandle stcChannel
    );
void NEXUS_SimpleAudioDecoder_GetDefaultStartSettings(
    NEXUS_SimpleAudioDecoderStartSettings *pSettings
    );
NEXUS_Error NEXUS_SimpleAudioDecoder_Start(
    NEXUS_SimpleAudioDecoderHandle handle,
    const NEXUS_SimpleAudioDecoderStartSettings *pSettings
    );
void NEXUS_SimpleAudioDecoder_Stop(
    NEXUS_SimpleAudioDecoderHandle handle
    );
void NEXUS_SimpleAudioDecoder_GetSettings(
    NEXUS_SimpleAudioDecoderHandle handle,
    NEXUS_SimpleAudioDecoderSettings *pSettings
    );
NEXUS_Error NEXUS_SimpleAudioDecoder_SetSettings(
    NEXUS_SimpleAudioDecoderHandle handle,
    const NEXUS_SimpleAudioDecoderSettings *pSettings
    );
NEXUS_Error NEXUS_SimpleAudioDecoder_GetStatus(
    NEXUS_SimpleAudioDecoderHandle handle,
    NEXUS_AudioDecoderStatus *pStatus
    );
NEXUS_Error NEXUS_SimpleAudioDecoder_GetCombinedStatus(
    NEXUS_SimpleAudioDecoderHandle handle,
    NEXUS_SimpleAudioDecoderStatus *pStatus
    );
NEXUS_Error NEXUS_SimpleAudioDecoder_GetPresentationStatus(
    NEXUS_SimpleAudioDecoderHandle handle,
    unsigned presentationIndex,
    NEXUS_AudioDecoderPresentationStatus *pStatus
    );
NEXUS_Error NEXUS_SimpleAudioDecoder_GetProcessorStatus(
    NEXUS_SimpleAudioDecoderHandle handle,
    NEXUS_SimpleAudioDecoderSelector selector,
    NEXUS_AudioPostProcessing type,
    NEXUS_AudioProcessorStatus *pStatus
    );
void NEXUS_SimpleAudioDecoder_Flush(
    NEXUS_SimpleAudioDecoderHandle handle
    );
void NEXUS_SimpleAudioDecoder_GetTrickState(
    NEXUS_SimpleAudioDecoderHandle handle,
    NEXUS_AudioDecoderTrickState *pStatus
    );
NEXUS_Error NEXUS_SimpleAudioDecoder_SetTrickState(
    NEXUS_SimpleAudioDecoderHandle handle,
    const NEXUS_AudioDecoderTrickState *pStatus
    );
NEXUS_Error NEXUS_SimpleAudioDecoder_Advance(
    NEXUS_SimpleAudioDecoderHandle handle,
    uint32_t pts
    );
void NEXUS_SimpleAudioDecoder_GetCodecSettings(
    NEXUS_SimpleAudioDecoderHandle handle,
    NEXUS_SimpleAudioDecoderSelector selector,
    NEXUS_AudioCodec codec,
    NEXUS_AudioDecoderCodecSettings *pSettings
    );
NEXUS_Error NEXUS_SimpleAudioDecoder_SetCodecSettings(
    NEXUS_SimpleAudioDecoderHandle handle,
    NEXUS_SimpleAudioDecoderSelector selector,
    const NEXUS_AudioDecoderCodecSettings *pSettings
    );
NEXUS_Error NEXUS_SimpleAudioDecoder_Suspend(
    NEXUS_SimpleAudioDecoderHandle handle
    );
NEXUS_Error NEXUS_SimpleAudioDecoder_Resume(
    NEXUS_SimpleAudioDecoderHandle handle
    );
NEXUS_Error NEXUS_SimpleAudioDecoder_StartHdmiInput(
    NEXUS_SimpleAudioDecoderHandle handle,
    NEXUS_HdmiInputHandle hdmiInput,
    const NEXUS_SimpleAudioDecoderStartSettings *pStartSettings
    );
void NEXUS_SimpleAudioDecoder_StopHdmiInput(
    NEXUS_SimpleAudioDecoderHandle handle
    );
NEXUS_Error NEXUS_SimpleAudioDecoder_GetPassthroughBuffer(
    NEXUS_SimpleAudioDecoderHandle handle,
    void **pBuffer,
    size_t *pSize
    );
NEXUS_Error NEXUS_SimpleAudioDecoder_PassthroughWriteComplete(
    NEXUS_SimpleAudioDecoderHandle handle,
    size_t amountWritten
    );
NEXUS_Error NEXUS_SimpleAudioDecoder_AddOutput(
    NEXUS_SimpleAudioDecoderHandle handle,
    NEXUS_AudioOutputHandle output,
    NEXUS_SimpleAudioDecoderSelector selector,
    NEXUS_AudioConnectorType connectorType
    );
NEXUS_Error NEXUS_SimpleAudioDecoder_RemoveOutput(
    NEXUS_SimpleAudioDecoderHandle handle,
    NEXUS_AudioOutputHandle output
    );
typedef struct NEXUS_Recpump *NEXUS_RecpumpHandle;
typedef enum NEXUS_RecpumpIndexType
{
    NEXUS_RecpumpIndexType_eTransport,
    NEXUS_RecpumpIndexType_eEs,
    NEXUS_RecpumpIndexType_eNone,
    NEXUS_RecpumpIndexType_eMax
} NEXUS_RecpumpIndexType;
typedef struct NEXUS_RecpumpOpenFlowSettings
{
    NEXUS_HeapHandle heap;
    void *buffer;
    size_t bufferSize;
    unsigned alignment;
    unsigned dataReadyThreshold;
    unsigned atomSize;
} NEXUS_RecpumpOpenFlowSettings;
typedef struct NEXUS_RecpumpOpenSettings
{
    NEXUS_RecpumpOpenFlowSettings data;
    NEXUS_RecpumpOpenFlowSettings index;
    NEXUS_RecpumpHandle dummyRecpump;
    unsigned nullifyVct;
    _Bool useSecureHeap;
    NEXUS_RecpumpIndexType indexType;
} NEXUS_RecpumpOpenSettings;
void NEXUS_Recpump_GetDefaultOpenSettings(
    NEXUS_RecpumpOpenSettings *pSettings
    );
NEXUS_RecpumpHandle NEXUS_Recpump_Open(
    unsigned index,
    const NEXUS_RecpumpOpenSettings *pSettings
    );
void NEXUS_Recpump_Close(
    NEXUS_RecpumpHandle handle
    );
typedef enum NEXUS_RecpumpFlowControl {
    NEXUS_RecpumpFlowControl_eDisable,
    NEXUS_RecpumpFlowControl_eEnable,
    NEXUS_RecpumpFlowControl_eAuto,
    NEXUS_RecpumpFlowControl_eMax
} NEXUS_RecpumpFlowControl;
typedef struct NEXUS_RecpumpSettings
{
    struct
    {
        size_t useBufferSize;
        NEXUS_CallbackDesc dataReady;
        NEXUS_CallbackDesc overflow;
    } data, index;
    NEXUS_DmaHandle securityDma;
    NEXUS_DmaDataFormat securityDmaDataFormat;
    NEXUS_KeySlotHandle securityContext;
    NEXUS_RecpumpFlowControl bandHold;
    NEXUS_TransportTimestampType timestampType;
 _Bool adjustTimestampUsingPcrs;
 NEXUS_PidChannelHandle pcrPidChannel;
    NEXUS_TransportType outputTransportType;
    _Bool dropBtpPackets;
    _Bool localTimestamp;
    struct {
        _Bool countRecordedPackets;
        _Bool storePcrMsb;
        _Bool firstPacketEnable;
        _Bool idleEventEnable;
        _Bool recordEventEnable;
        struct {
            _Bool enabled;
            unsigned evenTid;
            unsigned oddTid;
        } ecmPair[3];
    } tpit;
    NEXUS_CallbackDesc tsioDmaEnd;
} NEXUS_RecpumpSettings;
void NEXUS_Recpump_GetDefaultSettings(
    NEXUS_RecpumpSettings *pSettings
    );
void NEXUS_Recpump_GetSettings(
    NEXUS_RecpumpHandle handle,
    NEXUS_RecpumpSettings *pSettings
    );
NEXUS_Error NEXUS_Recpump_SetSettings(
    NEXUS_RecpumpHandle handle,
    const NEXUS_RecpumpSettings *pSettings
    );
NEXUS_Error NEXUS_Recpump_Start(
    NEXUS_RecpumpHandle handle
    );
void NEXUS_Recpump_StopData(
    NEXUS_RecpumpHandle handle
    );
void NEXUS_Recpump_Stop(
    NEXUS_RecpumpHandle handle
    );
typedef struct NEXUS_RecpumpTpitFilter
{
    unsigned pid;
    _Bool corruptionEnable;
    _Bool mpegMode;
    union
    {
        struct
        {
            _Bool ecmPolarityChangeEn;
            _Bool sectionFilterEn;
            _Bool adaptationExtensionFlagEnable;
            _Bool adaptationExtensionFlagCompValue;
            _Bool privateDataFlagEnable;
            _Bool privateDataFlagCompValue;
            _Bool splicingPointFlagEnable;
            _Bool splicingPointFlagCompValue;
            _Bool opcrFlagEnable;
            _Bool opcrFlagCompValue;
            _Bool pcrFlagEnable;
            _Bool pcrFlagCompValue;
            _Bool esPriorityIndicatorEnable;
            _Bool esPriorityIndicatorCompValue;
            _Bool randomAccessIndicatorEnable;
            _Bool randomAccessIndicatorCompValue;
            _Bool discontinuityIndicatorEnable;
            _Bool discontinuityIndicatorCompValue;
            _Bool adaptationFieldChangeEnable;
            _Bool scramblingControlChangeEnable;
            _Bool transportPriorityEnable;
            _Bool transportPriorityCompValue;
            _Bool payloadUnitStartEnable;
            _Bool payloadUnitStartCompValue;
        } mpeg;
        struct
        {
            _Bool filterHdEnable;
            unsigned short hdFilter;
            _Bool tcDetEn;
            _Bool cwpDetEn;
            _Bool rtsDetEn;
            _Bool cffEn;
            _Bool cffComp;
            _Bool mfEn;
            _Bool mfComp;
            _Bool hdEn;
            uint8_t hdMask;
            _Bool csAuxChangeEn;
            _Bool csChangeEn;
            _Bool cfChangeEn;
            _Bool bbEn;
            _Bool bbComp;
        } dss;
    } config;
} NEXUS_RecpumpTpitFilter;
typedef struct NEXUS_RecpumpAddPidChannelSettings
{
    NEXUS_PidType pidType;
    struct
    {
        struct
        {
            _Bool index;
            NEXUS_VideoCodec codec;
            uint16_t pid;
        } video;
        struct
        {
            _Bool index;
            struct {
                uint8_t low;
                uint8_t high;
            } startCodeRange[4];
        } other;
    } pidTypeSettings;
    _Bool useRPipe;
} NEXUS_RecpumpAddPidChannelSettings;
void NEXUS_Recpump_GetDefaultAddPidChannelSettings(
    NEXUS_RecpumpAddPidChannelSettings *pSettings
    );
NEXUS_Error NEXUS_Recpump_AddPidChannel(
    NEXUS_RecpumpHandle handle,
    NEXUS_PidChannelHandle pidChannel,
    const NEXUS_RecpumpAddPidChannelSettings *pSettings
    );
NEXUS_Error NEXUS_Recpump_RemovePidChannel(
    NEXUS_RecpumpHandle handle,
    NEXUS_PidChannelHandle pidChannel
    );
void NEXUS_Recpump_RemoveAllPidChannels(
    NEXUS_RecpumpHandle handle
    );
NEXUS_Error NEXUS_Recpump_GetDataBuffer(
    NEXUS_RecpumpHandle handle,
    const void **pBuffer,
    size_t *pAmount
    );
NEXUS_Error NEXUS_Recpump_GetDataBufferWithWrap(
    NEXUS_RecpumpHandle handle,
    const void **pBuffer,
    size_t *pAmount,
    const void **pBuffer2,
    size_t *pAmount2
    );
NEXUS_Error NEXUS_Recpump_DataReadComplete(
    NEXUS_RecpumpHandle handle,
    size_t amount
    );
NEXUS_Error NEXUS_Recpump_GetIndexBuffer(
    NEXUS_RecpumpHandle handle,
    const void **pBuffer,
    size_t *pAmount
    );
NEXUS_Error NEXUS_Recpump_GetIndexBufferWithWrap(
    NEXUS_RecpumpHandle handle,
    const void **pBuffer,
    size_t *pAmount,
    const void **pBuffer2,
    size_t *pAmount2
    );
NEXUS_Error NEXUS_Recpump_IndexReadComplete(
    NEXUS_RecpumpHandle handle,
    size_t amount
    );
typedef struct NEXUS_RecpumpStatus
{
    _Bool started;
    _Bool hasIndex;
    struct
    {
        uint64_t bytesRecorded;
        size_t fifoDepth;
        size_t fifoSize;
        void *bufferBase;
    } data, index;
    NEXUS_RecpumpOpenSettings openSettings;
    struct {
        unsigned index;
    } rave;
    unsigned bitrate;
} NEXUS_RecpumpStatus;
NEXUS_Error NEXUS_Recpump_GetStatus(
    NEXUS_RecpumpHandle handle,
    NEXUS_RecpumpStatus *pStatus
    );
void NEXUS_Recpump_GetDefaultTpitFilter(
    NEXUS_RecpumpTpitFilter *pFilter
    );
NEXUS_Error NEXUS_Recpump_SetTpitFilter(
    NEXUS_RecpumpHandle handle,
    NEXUS_PidChannelHandle pidChannel,
    const NEXUS_RecpumpTpitFilter *pFilter
    );
typedef struct NEXUS_VideoEncoderModuleInternalSettings
{
    NEXUS_VideoEncoder_MemoryConfig heapSize[2];
    struct {
        unsigned general;
        unsigned firmware[2];
        unsigned secure;
        unsigned picture;
        unsigned system;
        unsigned output;
    } heapIndex[2];
    NEXUS_ModuleHandle display;
    NEXUS_ModuleHandle transport;
    NEXUS_ModuleHandle audio;
    NEXUS_ModuleHandle core;
    NEXUS_ModuleHandle security;
    struct {
        int device;
        int channel;
    } vceMapping[6];
    struct {
        NEXUS_VideoEncoderMemory memory;
    } videoEncoder[6];
} NEXUS_VideoEncoderModuleInternalSettings;
void NEXUS_VideoEncoderModule_GetDefaultSettings(
    NEXUS_VideoEncoderModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_VideoEncoderModule_Init(
    const NEXUS_VideoEncoderModuleInternalSettings *pInternalSettings,
    const NEXUS_VideoEncoderModuleSettings *pSettings
    );
void NEXUS_VideoEncoderModule_Uninit(void);
void NEXUS_VideoEncoderModule_GetDefaultInternalSettings(
    NEXUS_VideoEncoderModuleInternalSettings *pSettings
    );
typedef enum NEXUS_VideoEncoderType
{
   NEXUS_VideoEncoderType_eMulti,
   NEXUS_VideoEncoderType_eSingle,
   NEXUS_VideoEncoderType_eMultiNonRealTime,
   NEXUS_VideoEncoderType_eCustom,
   NEXUS_VideoEncoderType_eMax
} NEXUS_VideoEncoderType;
typedef struct NEXUS_VideoEncoderOpenSettings
{
    struct {
        unsigned fifoSize;
        NEXUS_HeapHandle heap;
    } data, index;
    struct {
        _Bool interlaced;
        unsigned maxWidth, maxHeight;
    } memoryConfig;
    NEXUS_CallbackDesc errorCallback;
    NEXUS_CallbackDesc watchdogCallback;
    NEXUS_VideoEncoderType type;
    unsigned maxChannelCount;
    _Bool enableDataUnitDetecton;
} NEXUS_VideoEncoderOpenSettings;
void NEXUS_VideoEncoder_GetDefaultOpenSettings(
    NEXUS_VideoEncoderOpenSettings *pSettings
    );
NEXUS_VideoEncoderHandle NEXUS_VideoEncoder_Open(
    unsigned index,
    const NEXUS_VideoEncoderOpenSettings *pSettings
    );
void NEXUS_VideoEncoder_Close(
    NEXUS_VideoEncoderHandle handle
    );
typedef struct NEXUS_VideoEncoderBounds
{
    struct {
        NEXUS_VideoFrameRate min, max;
    } outputFrameRate;
    struct {
        NEXUS_VideoFrameRate min;
    } inputFrameRate;
    struct {
        struct {
            unsigned width, height;
        } max;
        struct {
            unsigned width, height;
        } maxInterlaced;
    } inputDimension;
    struct
    {
        struct
        {
            unsigned bitrateMax;
            unsigned bitrateTarget;
        } upper;
    } bitrate;
    struct {
        struct {
            unsigned framesB;
        } max;
    } streamStructure;
} NEXUS_VideoEncoderBounds;
typedef struct NEXUS_VideoEncoderStartSettings
{
    NEXUS_DisplayHandle input;
    NEXUS_VideoWindowHandle window;
    _Bool interlaced;
    _Bool nonRealTime;
    _Bool lowDelayPipeline;
    _Bool encodeUserData;
    _Bool encodeBarUserData;
    _Bool adaptiveLowDelayMode;
    NEXUS_VideoCodec codec;
    NEXUS_VideoCodecProfile profile;
    NEXUS_VideoCodecLevel level;
    NEXUS_VideoEncoderBounds bounds;
    unsigned rateBufferDelay;
    NEXUS_StcChannelHandle stcChannel;
    unsigned numParallelEncodes;
    _Bool bypassVideoProcessing;
    NEXUS_EntropyCoding entropyCoding;
    NEXUS_CallbackDesc dataReady;
    struct {
       _Bool disableFrameDrop;
    } hrdModeRateControl;
    struct {
       _Bool enable;
       unsigned duration;
       unsigned upperTolerance;
       unsigned lowerTolerance;
    } segmentModeRateControl;
    struct {
        _Bool singleRefP;
        _Bool requiredPatchesOnly;
    } memoryBandwidthSaving;
} NEXUS_VideoEncoderStartSettings;
typedef struct NEXUS_VideoEncoderDelayRange {
    unsigned min;
    unsigned max;
} NEXUS_VideoEncoderDelayRange;
typedef struct NEXUS_VideoEncoderSettingsOnInputChange
{
    unsigned bitrateMax;
    unsigned bitrateTarget;
} NEXUS_VideoEncoderSettingsOnInputChange;
typedef enum NEXUS_VideoEncoderStopMode
{
    NEXUS_VideoEncoderStopMode_eNormal,
    NEXUS_VideoEncoderStopMode_eImmediate,
    NEXUS_VideoEncoderStopMode_eAbort,
    NEXUS_VideoEncoderStopMode_eMax
} NEXUS_VideoEncoderStopMode;
typedef struct NEXUS_VideoEncoderStopSettings
{
    NEXUS_VideoEncoderStopMode mode;
} NEXUS_VideoEncoderStopSettings;
void NEXUS_VideoEncoder_GetDefaultStartSettings(
    NEXUS_VideoEncoderStartSettings *pSettings
    );
NEXUS_Error NEXUS_VideoEncoder_Start(
    NEXUS_VideoEncoderHandle handle,
    const NEXUS_VideoEncoderStartSettings *pSettings
    );
void NEXUS_VideoEncoder_GetDefaultStopSettings(
    NEXUS_VideoEncoderStopSettings *pSettings
);
void NEXUS_VideoEncoder_Stop(
    NEXUS_VideoEncoderHandle handle,
    const NEXUS_VideoEncoderStopSettings *pSettings
);
typedef struct NEXUS_VideoEncoderStreamStructure
{
      _Bool newGopOnSceneChange;
      unsigned duration;
      _Bool adaptiveDuration;
      unsigned framesP;
      unsigned framesB;
      _Bool openGop;
} NEXUS_VideoEncoderStreamStructure;
typedef struct NEXUS_VideoEncoderSettings
{
    unsigned bitrateMax;
    unsigned bitrateTarget;
    _Bool variableFrameRate;
    _Bool enableFieldPairing;
    NEXUS_VideoFrameRate frameRate;
    NEXUS_VideoEncoderStreamStructure streamStructure;
    unsigned encoderDelay;
} NEXUS_VideoEncoderSettings;
void NEXUS_VideoEncoder_GetDefaultSettings(
    NEXUS_VideoEncoderSettings *pSettings
    );
void NEXUS_VideoEncoder_GetSettings(
    NEXUS_VideoEncoderHandle handle,
    NEXUS_VideoEncoderSettings *pSettings
    );
NEXUS_Error NEXUS_VideoEncoder_SetSettings(
    NEXUS_VideoEncoderHandle handle,
    const NEXUS_VideoEncoderSettings *pSettings
    );
NEXUS_Error NEXUS_VideoEncoder_GetDelayRange (
    NEXUS_VideoEncoderHandle handle,
    const NEXUS_VideoEncoderSettings *pSettings,
    const NEXUS_VideoEncoderStartSettings *pStartSettings,
    NEXUS_VideoEncoderDelayRange *pDelayRange
    );
void
NEXUS_VideoEncoder_GetSettingsOnInputChange(
    NEXUS_VideoEncoderHandle handle,
    NEXUS_VideoEncoderSettingsOnInputChange *pSettings
    );
NEXUS_Error NEXUS_VideoEncoder_SetSettingsOnInputChange(
    NEXUS_VideoEncoderHandle handle,
    const NEXUS_VideoEncoderSettingsOnInputChange *pSettings
    );
NEXUS_Error NEXUS_VideoEncoder_InsertRandomAccessPoint(
    NEXUS_VideoEncoderHandle handle
    );
typedef struct NEXUS_VideoEncoderClearStatus {
    uint32_t errorFlags;
    uint32_t eventFlags;
} NEXUS_VideoEncoderClearStatus;
void NEXUS_VideoEncoder_ClearStatus(
    NEXUS_VideoEncoderHandle handle,
    const NEXUS_VideoEncoderClearStatus *pClearStatus
    );
void NEXUS_VideoEncoder_GetDefaultClearStatus(
        NEXUS_VideoEncoderClearStatus *pClearStatus
     );
typedef struct NEXUS_VideoEncoderCapabilities
{
    struct {
        _Bool supported;
        unsigned displayIndex;
        unsigned deviceIndex;
        unsigned channelIndex;
        NEXUS_VideoEncoderMemory memory;
    } videoEncoder[6];
} NEXUS_VideoEncoderCapabilities;
void NEXUS_GetVideoEncoderCapabilities(
    NEXUS_VideoEncoderCapabilities *pCapabilities
    );
typedef struct NEXUS_SimpleEncoder *NEXUS_SimpleEncoderHandle;
NEXUS_SimpleEncoderHandle NEXUS_SimpleEncoder_Acquire(
    unsigned id
    );
void NEXUS_SimpleEncoder_Release(
    NEXUS_SimpleEncoderHandle handle
    );
typedef struct NEXUS_SimpleEncoderStartSettingsOutputVideo
{
    NEXUS_VideoEncoderStartSettings settings;
    unsigned pid;
    _Bool index;
    _Bool raiIndex;
    NEXUS_KeySlotHandle keyslot;
} NEXUS_SimpleEncoderStartSettingsOutputVideo;
typedef struct NEXUS_SimpleEncoderStartSettingsOutput
{
    NEXUS_SimpleEncoderStartSettingsOutputVideo video;
    struct {
        _Bool passthrough;
        NEXUS_AudioCodec codec;
        unsigned pid;
        unsigned sampleRate;
        NEXUS_KeySlotHandle keyslot;
    } audio;
    struct {
        NEXUS_TransportType type;
        unsigned pcrPid;
        unsigned pmtPid;
        unsigned interval;
    } transport;
    struct {
        NEXUS_KeySlotHandle keyslot;
    } passthrough[4];
} NEXUS_SimpleEncoderStartSettingsOutput;
typedef struct NEXUS_SimpleEncoderStartSettings
{
    struct {
        _Bool display;
        NEXUS_SimpleVideoDecoderHandle video;
        NEXUS_SimpleAudioDecoderHandle audio;
    } input;
    struct {
        NEXUS_DisplayHandle display;
        unsigned nonRealTimeRate;
        _Bool useInitialPts;
        uint32_t initialPts;
    } transcode;
    NEXUS_RecpumpHandle recpump;
    NEXUS_SimpleEncoderStartSettingsOutput output;
    NEXUS_PidChannelHandle passthrough[4];
} NEXUS_SimpleEncoderStartSettings;
void NEXUS_SimpleEncoder_GetDefaultStartSettings(
    NEXUS_SimpleEncoderStartSettings *pSettings
    );
NEXUS_Error NEXUS_SimpleEncoder_Start(
    NEXUS_SimpleEncoderHandle handle,
    const NEXUS_SimpleEncoderStartSettings *pSettings
    );
void NEXUS_SimpleEncoder_Stop(
    NEXUS_SimpleEncoderHandle handle
    );
typedef enum NEXUS_SimpleEncoderStopMode
{
    NEXUS_SimpleEncoderStopMode_eAll,
    NEXUS_SimpleEncoderStopMode_eVideoEncoderOnly,
    NEXUS_SimpleEncoderStopMode_eMax
} NEXUS_SimpleEncoderStopMode;
typedef struct NEXUS_SimpleEncoderSettings
{
    struct {
        unsigned width, height;
        _Bool interlaced;
        unsigned refreshRate;
        NEXUS_Rect window;
        NEXUS_ClipRect clip;
    } video;
    NEXUS_VideoEncoderSettings videoEncoder;
    NEXUS_AudioEncoderCodecSettings audioEncoder;
    NEXUS_CallbackDesc resourceChanged;
    NEXUS_CallbackDesc finished;
    NEXUS_SimpleEncoderStopMode stopMode;
    struct {
        struct {
            _Bool video[1];
            _Bool audio[1];
        } enable;
    } streamMux;
} NEXUS_SimpleEncoderSettings;
void NEXUS_SimpleEncoder_GetSettings(
    NEXUS_SimpleEncoderHandle handle,
    NEXUS_SimpleEncoderSettings *pSettings
    );
NEXUS_Error NEXUS_SimpleEncoder_SetSettings(
    NEXUS_SimpleEncoderHandle handle,
    const NEXUS_SimpleEncoderSettings *pSettings
    );
NEXUS_Error NEXUS_SimpleEncoder_GetVideoBuffer(
    NEXUS_SimpleEncoderHandle handle,
    const NEXUS_VideoEncoderDescriptor **pBuffer,
    size_t *pSize,
    const NEXUS_VideoEncoderDescriptor **pBuffer2,
    size_t *pSize2
    );
NEXUS_Error NEXUS_SimpleEncoder_VideoReadComplete(
    NEXUS_SimpleEncoderHandle handle,
    unsigned descriptorsCompleted
    );
NEXUS_Error NEXUS_SimpleEncoder_GetAudioBuffer(
    NEXUS_SimpleEncoderHandle handle,
    const NEXUS_AudioMuxOutputFrame **pBuffer,
    size_t *pSize,
    const NEXUS_AudioMuxOutputFrame **pBuffer2,
    size_t *pSize2
    );
NEXUS_Error NEXUS_SimpleEncoder_AudioReadComplete(
    NEXUS_SimpleEncoderHandle handle,
    unsigned descriptorsCompleted
    );
typedef struct NEXUS_SimpleEncoderVideoStatus
{
    NEXUS_MemoryBlockHandle bufferBlock;
    NEXUS_MemoryBlockHandle metadataBufferBlock;
    uint32_t errorFlags;
    uint32_t eventFlags;
    unsigned errorCount;
    unsigned picturesReceived;
    unsigned picturesDroppedFRC;
    unsigned picturesDroppedHRD;
    unsigned picturesDroppedErrors;
    unsigned picturesEncoded;
    uint32_t pictureIdLastEncoded;
    unsigned picturesPerSecond;
    struct {
        size_t fifoDepth;
        size_t fifoSize;
    } data, index;
    struct {
        unsigned firmware;
    } version;
    struct {
        size_t elementSize;
        NEXUS_MemoryBlockHandle buffer;
        unsigned offset;
    } debugLog;
} NEXUS_SimpleEncoderVideoStatus;
typedef struct NEXUS_SimpleEncoderAudioStatus
{
    NEXUS_MemoryBlockHandle bufferBlock;
    NEXUS_MemoryBlockHandle metadataBufferBlock;
    unsigned numFrames;
    unsigned numErrorFrames;
    unsigned numDroppedFrames;
    struct {
        unsigned fifoDepth;
        unsigned fifoSize;
    } data, index;
} NEXUS_SimpleEncoderAudioStatus;
typedef struct NEXUS_SimpleEncoderStatus
{
    struct {
        _Bool enabled;
        unsigned index;
    } videoEncoder;
    NEXUS_SimpleEncoderVideoStatus video;
    NEXUS_SimpleEncoderAudioStatus audio;
    struct {
        struct {
            uint32_t video[1];
            uint32_t audio[1];
        } currentTimestamp;
    } streamMux;
} NEXUS_SimpleEncoderStatus;
void NEXUS_SimpleEncoder_GetStatus(
    NEXUS_SimpleEncoderHandle handle,
    NEXUS_SimpleEncoderStatus *pStatus
    );
NEXUS_Error NEXUS_SimpleEncoder_GetCrcData(
    NEXUS_SimpleEncoderHandle handle,
    NEXUS_DisplayCrcData *pEntries,
    unsigned numEntries,
    unsigned *pNumReturned
    );
NEXUS_Error NEXUS_SimpleEncoder_InsertRandomAccessPoint(
    NEXUS_SimpleEncoderHandle handle
    );
typedef struct NEXUS_FileMux *NEXUS_FileMuxHandle;
typedef struct NEXUS_FileMuxCreateSettings
{
    NEXUS_CallbackDesc finished;
    size_t storageDescriptors;
    struct {
        _Bool supported;
        size_t metadataCache;
        size_t heapSize;
        size_t sizeEntriesCache;
        size_t relocationBuffer;
    } mp4;
    struct {
        _Bool supported;
        size_t packetLength;
    } asf;
    struct {
        _Bool supported;
    } pes;
} NEXUS_FileMuxCreateSettings;
void NEXUS_FileMux_GetDefaultCreateSettings(
    NEXUS_FileMuxCreateSettings *pSettings
    );
NEXUS_FileMuxHandle NEXUS_FileMux_Create(
    const NEXUS_FileMuxCreateSettings *pSettings
    );
void NEXUS_FileMux_Destroy(
    NEXUS_FileMuxHandle handle
    );
typedef struct NEXUS_FileMuxVideoPid {
    unsigned track;
    NEXUS_VideoCodec codec;
    NEXUS_VideoEncoderHandle encoder;
    NEXUS_SimpleEncoderHandle simpleEncoder;
} NEXUS_FileMuxVideoPid;
typedef struct NEXUS_FileMuxAudioPid {
    unsigned track;
    NEXUS_AudioCodec codec;
    NEXUS_AudioMuxOutputHandle muxOutput;
    NEXUS_SimpleEncoderHandle simpleEncoder;
} NEXUS_FileMuxAudioPid;
typedef struct NEXUS_FileMuxStartSettings
{
    NEXUS_TransportType streamType;
    NEXUS_FileMuxVideoPid video[16];
    NEXUS_FileMuxAudioPid audio[16];
    char tempDir[64];
    unsigned expectedDuration;
    union {
        struct {
            _Bool progressiveDownloadCompatible;
            unsigned createTime;
        } mp4;
        struct {
            uint8_t fileId[16];
            _Bool broadcastOnly;
        } asf;
    } streamSettings;
} NEXUS_FileMuxStartSettings;
void NEXUS_FileMux_GetDefaultStartSettings(
    NEXUS_FileMuxStartSettings *pSettings,
    NEXUS_TransportType streamType
    );
NEXUS_Error NEXUS_FileMux_Start(
    NEXUS_FileMuxHandle handle,
    const NEXUS_FileMuxStartSettings *pSettings,
    NEXUS_MuxFileHandle file
    );
void NEXUS_FileMux_Finish(
    NEXUS_FileMuxHandle handle
    );
void NEXUS_FileMux_Stop(
    NEXUS_FileMuxHandle handle
    );
typedef struct NEXUS_FileMuxStatus
{
    unsigned duration;
} NEXUS_FileMuxStatus;
NEXUS_Error NEXUS_FileMux_GetStatus(
    NEXUS_FileMuxHandle handle,
    NEXUS_FileMuxStatus *pStatus
    );
typedef struct NEXUS_FileMuxModuleSettings
{
    int unused;
} NEXUS_FileMuxModuleSettings;
void NEXUS_FileMuxModule_GetDefaultSettings(
    NEXUS_FileMuxModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_FileMuxModule_Init(
    const NEXUS_FileMuxModuleSettings *pSettings
    );
void NEXUS_FileMuxModule_Uninit(void);
typedef struct bfile_io_mux *bfile_io_mux_t;
struct bfile_io_mux {
    ssize_t (*read)(bfile_io_mux_t fd, off_t offset, const NEXUS_FileMuxIoReadAtom *atoms, unsigned atom_count);
    ssize_t (*write)(bfile_io_mux_t fd, off_t offset,const NEXUS_FileMuxIoWriteAtom *atoms, unsigned atom_count);
    bfile_io_priority priority;
};
struct NEXUS_MuxFile {
    struct bfile_io_mux mux;
    void (*close)(bfile_io_mux_t fd);
};
struct NEXUS_FileRecord {
    bfile_io_write_t data;
    bfile_io_write_t index;
    void (*close)(struct NEXUS_FileRecord *file);
};
struct NEXUS_FilePlay {
 struct {
     bfile_io_read_t data;
     bfile_io_read_t index;
     void (*close)(struct NEXUS_FilePlay *file);
 } file;
};
typedef struct NEXUS_InputBandSettings
{
    _Bool clockActiveHigh;
    _Bool dataLsbFirst;
    _Bool dataActiveHigh;
    _Bool validEnabled;
    _Bool validActiveHigh;
    _Bool useInternalSync;
    _Bool useSyncAsValid;
    _Bool syncActiveHigh;
    _Bool errorEnabled;
    _Bool errorActiveHigh;
    _Bool parallelInput;
    unsigned packetLength;
} NEXUS_InputBandSettings;
void NEXUS_InputBand_GetSettings(
    NEXUS_InputBand inputBand,
    NEXUS_InputBandSettings *pSettings
    );
NEXUS_Error NEXUS_InputBand_SetSettings(
    NEXUS_InputBand inputBand,
    const NEXUS_InputBandSettings *pSettings
    );
typedef struct NEXUS_InputBandStatus
{
    unsigned syncCount;
    unsigned overflowErrors;
} NEXUS_InputBandStatus;
NEXUS_Error NEXUS_InputBand_GetStatus(
    NEXUS_InputBand inputBand,
    NEXUS_InputBandStatus *pStatus
    );
typedef struct NEXUS_Frontend *NEXUS_FrontendHandle;
typedef struct NEXUS_FrontendDevice *NEXUS_FrontendDeviceHandle;
typedef enum NEXUS_FrontendQamMode
{
    NEXUS_FrontendQamMode_e16,
    NEXUS_FrontendQamMode_e32,
    NEXUS_FrontendQamMode_e64,
    NEXUS_FrontendQamMode_e128,
    NEXUS_FrontendQamMode_e256,
    NEXUS_FrontendQamMode_e512,
    NEXUS_FrontendQamMode_e1024,
    NEXUS_FrontendQamMode_e2048,
    NEXUS_FrontendQamMode_e4096,
    NEXUS_FrontendQamMode_eAuto_64_256,
    NEXUS_FrontendQamMode_eMax
} NEXUS_FrontendQamMode;
typedef enum NEXUS_FrontendQamAnnex
{
    NEXUS_FrontendQamAnnex_eA,
    NEXUS_FrontendQamAnnex_eB,
    NEXUS_FrontendQamAnnex_eC,
    NEXUS_FrontendQamAnnex_eMax
} NEXUS_FrontendQamAnnex;
typedef enum NEXUS_FrontendQamSpectrumMode
{
    NEXUS_FrontendQamSpectrumMode_eAuto,
    NEXUS_FrontendQamSpectrumMode_eManual,
    NEXUS_FrontendQamSpectrumMode_eMax
} NEXUS_FrontendQamSpectrumMode;
typedef enum NEXUS_FrontendQamSpectralInversion
{
    NEXUS_FrontendQamSpectralInversion_eNormal,
    NEXUS_FrontendQamSpectralInversion_eInverted,
    NEXUS_FrontendQamSpectralInversion_eMax
} NEXUS_FrontendQamSpectralInversion;
typedef enum NEXUS_FrontendQamAcquisitionMode
{
    NEXUS_FrontendQamAcquisitionMode_eAuto,
    NEXUS_FrontendQamAcquisitionMode_eFast,
    NEXUS_FrontendQamAcquisitionMode_eSlow,
    NEXUS_FrontendQamAcquisitionMode_eScan,
    NEXUS_FrontendQamAcquisitionMode_eMax
} NEXUS_FrontendQamAcquisitionMode;
typedef struct NEXUS_FrontendQamSettings
{
    NEXUS_FrontendQamMode mode;
    NEXUS_FrontendQamAnnex annex;
    unsigned frequency;
    unsigned ifFrequency;
    unsigned symbolRate;
    _Bool fastAcquisition;
    _Bool terrestrial;
    NEXUS_CallbackDesc lockCallback;
    _Bool autoAcquire;
    unsigned bandwidth;
    _Bool enablePowerMeasurement;
    NEXUS_FrontendQamSpectrumMode spectrumMode;
    NEXUS_FrontendQamSpectralInversion spectralInversion;
    unsigned frequencyOffset;
    _Bool enableNullPackets;
    NEXUS_CallbackDesc asyncStatusReadyCallback;
    NEXUS_FrontendQamAcquisitionMode acquisitionMode;
    struct {
        unsigned upperBaudSearch;
        unsigned lowerBaudSearch;
        _Bool mode[NEXUS_FrontendQamAnnex_eMax][NEXUS_FrontendQamMode_eMax];
        unsigned frequencyOffset;
    } scan;
} NEXUS_FrontendQamSettings;
void NEXUS_Frontend_GetDefaultQamSettings(
    NEXUS_FrontendQamSettings *pSettings
    );
NEXUS_Error NEXUS_Frontend_TuneQam(
    NEXUS_FrontendHandle handle,
    const NEXUS_FrontendQamSettings *pSettings
    );
typedef enum NEXUS_FrontendErrorRateUnits
{
    NEXUS_FrontendErrorRateUnits_eLinear,
    NEXUS_FrontendErrorRateUnits_eNaturalLog,
    NEXUS_FrontendErrorRateUnits_eMax
} NEXUS_FrontendErrorRateUnits;
typedef struct NEXUS_FrontendQamStatus
{
    NEXUS_FrontendQamSettings settings;
    _Bool receiverLock;
    _Bool fecLock;
    _Bool opllLock;
    _Bool spectrumInverted;
    unsigned symbolRate;
    int symbolRateError;
    int berEstimate;
    unsigned ifAgcLevel;
    unsigned rfAgcLevel;
    unsigned intAgcLevel;
    unsigned snrEstimate;
    unsigned fecCorrected;
    unsigned fecUncorrected;
    unsigned fecClean;
    unsigned bitErrCorrected;
    unsigned reacquireCount;
    unsigned viterbiUncorrectedBits;
    unsigned viterbiTotalBits;
    uint32_t viterbiErrorRate;
    NEXUS_FrontendErrorRateUnits errorRateUnits;
    int carrierFreqOffset;
    int carrierPhaseOffset;
    unsigned goodRsBlockCount;
    unsigned berRawCount;
    int dsChannelPower;
    unsigned mainTap;
    unsigned postRsBer;
    unsigned postRsBerElapsedTime;
    uint16_t interleaveDepth;
    unsigned lnaAgcLevel;
    int equalizerGain;
    int frontendGain;
    int digitalAgcGain;
    int highResEqualizerGain;
} NEXUS_FrontendQamStatus;
NEXUS_Error NEXUS_Frontend_GetQamStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendQamStatus *pStatus
    );
NEXUS_Error NEXUS_Frontend_RequestQamAsyncStatus(
    NEXUS_FrontendHandle handle
    );
NEXUS_Error NEXUS_Frontend_GetQamAsyncStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendQamStatus *pStatus
    );
typedef enum NEXUS_FrontendQamAcquisitionStatus
{
    NEXUS_FrontendQamAcquisitionStatus_eNoSignal,
    NEXUS_FrontendQamAcquisitionStatus_eNoLock,
    NEXUS_FrontendQamAcquisitionStatus_eLockedFast,
    NEXUS_FrontendQamAcquisitionStatus_eLockedSlow,
    NEXUS_FrontendQamAcquisitionStatus_eMax
}NEXUS_FrontendQamAcquisitionStatus;
typedef enum NEXUS_FrontendQamInterleaver
{
    NEXUS_FrontendQamInterleaver_eI128_J1,
    NEXUS_FrontendQamInterleaver_eI128_J2,
    NEXUS_FrontendQamInterleaver_eI128_J3,
    NEXUS_FrontendQamInterleaver_eI128_J4,
    NEXUS_FrontendQamInterleaver_eI64_J2,
    NEXUS_FrontendQamInterleaver_eI32_J4,
    NEXUS_FrontendQamInterleaver_eI16_J8,
    NEXUS_FrontendQamInterleaver_eI8_J16,
    NEXUS_FrontendQamInterleaver_eI4_J32,
    NEXUS_FrontendQamInterleaver_eI2_J64,
    NEXUS_FrontendQamInterleaver_eI1_J128,
    NEXUS_FrontendQamInterleaver_eI12_J17,
    NEXUS_FrontendQamInterleaver_eUnsupported,
    NEXUS_FrontendQamInterleaver_eMax
}NEXUS_FrontendQamInterleaver;
typedef struct NEXUS_FrontendQamScanStatus
{
    unsigned symbolRate;
    int frequencyOffset;
    NEXUS_FrontendQamMode mode;
    NEXUS_FrontendQamAnnex annex;
    NEXUS_FrontendQamInterleaver interleaver;
    NEXUS_FrontendQamSpectralInversion spectrumInverted;
    NEXUS_FrontendQamAcquisitionStatus acquisitionStatus;
} NEXUS_FrontendQamScanStatus;
NEXUS_Error NEXUS_Frontend_GetQamScanStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendQamScanStatus *pScanStatus
    );
typedef enum NEXUS_FrontendVsbMode
{
    NEXUS_FrontendVsbMode_e8,
    NEXUS_FrontendVsbMode_e16,
    NEXUS_FrontendVsbMode_eMax
} NEXUS_FrontendVsbMode;
typedef enum NEXUS_FrontendVsbSpectralInversion
{
    NEXUS_FrontendVsbSpectralInversion_eNormal,
    NEXUS_FrontendVsbSpectralInversion_eInverted,
    NEXUS_FrontendVsbSpectralInversion_eMax
} NEXUS_FrontendVsbSpectralInversion;
typedef struct NEXUS_FrontendVsbSettings
{
    NEXUS_FrontendVsbMode mode;
    unsigned frequency;
    unsigned ifFrequency;
    unsigned symbolRate;
    int ifFrequencyOffset;
    int symbolRateOffset;
    int ntscOffset;
    _Bool fastAcquisition;
    _Bool terrestrial;
    _Bool autoAcquire;
    _Bool ntscSweep;
    _Bool rfiSweep;
    NEXUS_CallbackDesc lockCallback;
    NEXUS_CallbackDesc asyncStatusReadyCallback;
    NEXUS_FrontendVsbSpectralInversion spectralInversion;
} NEXUS_FrontendVsbSettings;
void NEXUS_Frontend_GetDefaultVsbSettings(
    NEXUS_FrontendVsbSettings *pSettings
    );
NEXUS_Error NEXUS_Frontend_TuneVsb(
    NEXUS_FrontendHandle handle,
    const NEXUS_FrontendVsbSettings *pSettings
    );
typedef struct NEXUS_FrontendVsbStatus
{
    NEXUS_FrontendVsbSettings settings;
    _Bool receiverLock;
    _Bool fecLock;
    _Bool opllLock;
    unsigned symbolRate;
    int symbolRateError;
    unsigned ifFrequency;
    int ifFrequencyError;
    unsigned ifAgcLevel;
    unsigned rfAgcLevel;
    unsigned intAgcLevel;
    unsigned snrEstimate;
    unsigned fecCorrected;
    unsigned fecUncorrected;
    unsigned fecClean;
    unsigned bitErrCorrected;
    unsigned reacquireCount;
    unsigned viterbiUncorrectedBits;
    unsigned viterbiTotalBits;
    uint32_t viterbiErrorRate;
    unsigned timeElapsed;
    int carrierOffset;
} NEXUS_FrontendVsbStatus;
NEXUS_Error NEXUS_Frontend_GetVsbStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendVsbStatus *pStatus
    );
NEXUS_Error NEXUS_Frontend_RequestVsbAsyncStatus(
    NEXUS_FrontendHandle handle
    );
NEXUS_Error NEXUS_Frontend_GetVsbAsyncStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendVsbStatus *pStatus
    );
typedef enum NEXUS_FrontendSatelliteMode
{
    NEXUS_FrontendSatelliteMode_eDvbs,
    NEXUS_FrontendSatelliteMode_eDvb = NEXUS_FrontendSatelliteMode_eDvbs,
    NEXUS_FrontendSatelliteMode_eDss,
    NEXUS_FrontendSatelliteMode_eDcii,
    NEXUS_FrontendSatelliteMode_eQpskTurbo,
    NEXUS_FrontendSatelliteMode_eTurboQpsk=NEXUS_FrontendSatelliteMode_eQpskTurbo,
    NEXUS_FrontendSatelliteMode_e8pskTurbo,
    NEXUS_FrontendSatelliteMode_eTurbo8psk=NEXUS_FrontendSatelliteMode_e8pskTurbo,
    NEXUS_FrontendSatelliteMode_eTurbo,
    NEXUS_FrontendSatelliteMode_eDvbs2Qpsk,
    NEXUS_FrontendSatelliteMode_eQpskLdpc=NEXUS_FrontendSatelliteMode_eDvbs2Qpsk,
    NEXUS_FrontendSatelliteMode_eDvbs28psk,
    NEXUS_FrontendSatelliteMode_e8pskLdpc=NEXUS_FrontendSatelliteMode_eDvbs28psk,
    NEXUS_FrontendSatelliteMode_eDvbs216apsk,
    NEXUS_FrontendSatelliteMode_eDvbs232apsk,
    NEXUS_FrontendSatelliteMode_eDvbs2,
    NEXUS_FrontendSatelliteMode_eLdpc=NEXUS_FrontendSatelliteMode_eDvbs2,
    NEXUS_FrontendSatelliteMode_eDvbs2xQpsk,
    NEXUS_FrontendSatelliteMode_eDvbs2x8psk,
    NEXUS_FrontendSatelliteMode_eDvbs2x8apsk,
    NEXUS_FrontendSatelliteMode_eDvbs2x16apsk,
    NEXUS_FrontendSatelliteMode_eDvbs2x32apsk,
    NEXUS_FrontendSatelliteMode_eDvbs2x,
    NEXUS_FrontendSatelliteMode_eBlindAcquisition,
    NEXUS_FrontendSatelliteMode_eDvbs2Acm,
    NEXUS_FrontendSatelliteMode_eMax
} NEXUS_FrontendSatelliteMode;
typedef enum NEXUS_FrontendSatelliteInversion
{
    NEXUS_FrontendSatelliteInversion_eScan,
    NEXUS_FrontendSatelliteInversion_eNormal,
    NEXUS_FrontendSatelliteInversion_eI,
    NEXUS_FrontendSatelliteInversion_eInverted = NEXUS_FrontendSatelliteInversion_eI,
    NEXUS_FrontendSatelliteInversion_eQ,
    NEXUS_FrontendSatelliteInversion_eMax
} NEXUS_FrontendSatelliteInversion;
typedef enum NEXUS_FrontendSatelliteCodeRateMode {
    NEXUS_FrontendSatelliteCodeRateMode_eStandard,
    NEXUS_FrontendSatelliteCodeRateMode_eLinear,
    NEXUS_FrontendSatelliteCodeRateMode_eMax
}
NEXUS_FrontendSatelliteCodeRateMode;
typedef struct NEXUS_FrontendSatelliteCodeRate
{
    unsigned numerator;
    unsigned denominator;
    NEXUS_FrontendSatelliteCodeRateMode mode;
    unsigned bitsPerSymbol;
} NEXUS_FrontendSatelliteCodeRate;
typedef enum NEXUS_FrontendSatelliteNetworkSpec
{
   NEXUS_FrontendSatelliteNetworkSpec_eDefault = 0,
   NEXUS_FrontendSatelliteNetworkSpec_eCustom1,
   NEXUS_FrontendSatelliteNetworkSpec_eEuro,
   NEXUS_FrontendSatelliteNetworkSpec_eMax
} NEXUS_FrontendSatelliteNetworkSpec;
typedef enum NEXUS_FrontendSatelliteNyquistFilter
{
    NEXUS_FrontendSatelliteNyquistFilter_e35,
    NEXUS_FrontendSatelliteNyquistFilter_e20,
    NEXUS_FrontendSatelliteNyquistFilter_e10,
    NEXUS_FrontendSatelliteNyquistFilter_e5,
    NEXUS_FrontendSatelliteNyquistFilter_eMax
} NEXUS_FrontendSatelliteNyquistFilter;
typedef enum NEXUS_FrontendSatellitePLSMode
{
    NEXUS_FrontendSatellitePLSMode_eAuto,
    NEXUS_FrontendSatellitePLSMode_eRoot,
    NEXUS_FrontendSatellitePLSMode_eGold,
    NEXUS_FrontendSatellitePLSMode_eMax
} NEXUS_FrontendSatellitePLSMode;
typedef struct NEXUS_FrontendSatelliteSettings
{
    NEXUS_FrontendSatelliteMode mode;
    NEXUS_FrontendSatelliteCodeRate codeRate;
    NEXUS_FrontendSatelliteInversion spectralInversion;
    unsigned frequency;
    unsigned symbolRate;
    int carrierOffset;
    unsigned searchRange;
    int32_t ifOffset;
    NEXUS_FrontendSatelliteNetworkSpec networkSpec;
    _Bool pnData;
    _Bool prbs15;
    _Bool nyquist20;
    NEXUS_FrontendSatelliteNyquistFilter nyquistRolloff;
    _Bool bertEnable;
    _Bool pnDataInvert;
    _Bool bertResyncDisable;
    _Bool reacquireDisable;
    _Bool dciiSplit;
    _Bool dciiSplitQ;
    _Bool oQpsk;
    _Bool rsDisable;
    _Bool ldpcPilot;
    _Bool ldpcPilotPll;
    _Bool ldpcPilotScan;
    _Bool tunerTestMode;
    _Bool toneSearchMode;
    _Bool signalDetectMode;
    _Bool bypassTune;
    _Bool bypassAcquire;
    _Bool shortFrames;
    _Bool bypassFrequencyEstimation;
    struct {
        _Bool mode[NEXUS_FrontendSatelliteMode_eMax];
    } scan;
    NEXUS_CallbackDesc lockCallback;
    struct {
        _Bool misMode;
        uint8_t streamId;
        NEXUS_FrontendSatellitePLSMode plsMode;
        unsigned plsCode;
    } dvbs2xSettings;
} NEXUS_FrontendSatelliteSettings;
void NEXUS_Frontend_GetDefaultSatelliteSettings(
    NEXUS_FrontendSatelliteSettings *pSettings
    );
void NEXUS_Frontend_GetDefaultSatelliteSettingsForMode(
    NEXUS_FrontendSatelliteMode mode,
    NEXUS_FrontendSatelliteSettings *pSettings
    );
NEXUS_Error NEXUS_Frontend_TuneSatellite(
    NEXUS_FrontendHandle handle,
    const NEXUS_FrontendSatelliteSettings *pSettings
    );
typedef enum NEXUS_FrontendSatelliteStatusError
{
    NEXUS_FrontendSatelliteStatusError_eNone,
    NEXUS_FrontendSatelliteStatusError_eI2cNoAck,
    NEXUS_FrontendSatelliteStatusError_eHabTimeout,
    NEXUS_FrontendSatelliteStatusError_eGetChannelStatusError,
    NEXUS_FrontendSatelliteStatusError_eMax
} NEXUS_FrontendSatelliteStatusError;
typedef struct NEXUS_FrontendSatelliteStatus
{
    NEXUS_FrontendSatelliteSettings settings;
    NEXUS_FrontendSatelliteStatusError statusError;
    NEXUS_FrontendSatelliteMode mode;
    NEXUS_FrontendSatelliteCodeRate codeRate;
    NEXUS_FrontendSatelliteInversion spectralInversion;
    unsigned frequency;
    _Bool tunerLocked;
    _Bool demodLocked;
    unsigned channel;
    unsigned symbolRate;
    int symbolRateError;
    int carrierOffset;
    int carrierError;
    unsigned sampleClock;
    unsigned outputBitRate;
    unsigned ifAgcLevel;
    unsigned rfAgcLevel;
    unsigned intAgcLevel;
    unsigned snrEstimate;
    unsigned berEstimate;
    unsigned fecPhase;
    unsigned fecCorrected;
    unsigned fecUncorrected;
    unsigned fecClean;
    unsigned bitErrCorrected;
    unsigned reacquireCount;
    unsigned preViterbiErrorCount;
    unsigned mpegErrors;
    unsigned mpegCount;
    unsigned ifAgc;
    unsigned rfAgc;
    int agf;
    struct
    {
        unsigned intConfig;
        unsigned extConfig;
        unsigned version;
        unsigned agc0;
        unsigned agc1;
    } lnaStatus;
    struct {
        uint16_t chipId;
        uint8_t chipVersion;
        uint32_t bondingOption;
        uint8_t apMicrocodeVersion;
        uint8_t hostConfigurationVersion;
    } version;
    unsigned timeElapsed;
    _Bool bertLocked;
    unsigned berErrorCount;
} NEXUS_FrontendSatelliteStatus;
NEXUS_Error NEXUS_Frontend_GetSatelliteStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendSatelliteStatus *pStatus
    );
typedef struct NEXUS_FrontendSatelliteAgcStatus
{
    struct {
        _Bool valid;
        unsigned value;
    } agc[5];
} NEXUS_FrontendSatelliteAgcStatus;
NEXUS_Error NEXUS_Frontend_GetSatelliteAgcStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendSatelliteAgcStatus *pStatus
);
typedef enum NEXUS_FrontendDiseqcVoltage
{
    NEXUS_FrontendDiseqcVoltage_e13v,
    NEXUS_FrontendDiseqcVoltage_e18v,
    NEXUS_FrontendDiseqcVoltage_eMax
} NEXUS_FrontendDiseqcVoltage;
typedef enum NEXUS_FrontendDiseqcToneBurst {
    NEXUS_FrontendDiseqcToneBurst_eNone,
    NEXUS_FrontendDiseqcToneBurst_eUnmodulated,
    NEXUS_FrontendDiseqcToneBurst_eNominal,
    NEXUS_FrontendDiseqcToneBurst_eMax
} NEXUS_FrontendDiseqcToneBurst;
typedef enum NEXUS_FrontendDiseqcToneMode {
    NEXUS_FrontendDiseqcToneMode_eTone,
    NEXUS_FrontendDiseqcToneMode_eEnvelope,
    NEXUS_FrontendDiseqcToneMode_eMax
} NEXUS_FrontendDiseqcToneMode;
typedef enum NEXUS_FrontendDiseqcFraming {
    NEXUS_FrontendDiseqcFraming_eDefault,
    NEXUS_FrontendDiseqcFraming_eExpectReply,
    NEXUS_FrontendDiseqcFraming_eDontExpectReply,
    NEXUS_FrontendDiseqcFraming_eMax
} NEXUS_FrontendDiseqcFraming;
typedef struct NEXUS_FrontendDiseqcSettings
{
    _Bool lnbEnabled;
    NEXUS_FrontendDiseqcVoltage voltage;
    _Bool toneEnabled;
    NEXUS_FrontendDiseqcToneBurst toneBurst;
    NEXUS_FrontendDiseqcToneMode toneMode;
    NEXUS_FrontendDiseqcFraming framing;
    unsigned preTransmitDelay;
    _Bool enabled;
} NEXUS_FrontendDiseqcSettings;
void NEXUS_Frontend_GetDiseqcSettings(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendDiseqcSettings *pSettings
    );
NEXUS_Error NEXUS_Frontend_SetDiseqcSettings(
    NEXUS_FrontendHandle handle,
    const NEXUS_FrontendDiseqcSettings *pSettings
    );
typedef enum NEXUS_FrontendDiseqcMessageStatus
{
    NEXUS_FrontendDiseqcMessageStatus_eSuccess = 0,
    NEXUS_FrontendDiseqcMessageStatus_eRxOverflow,
    NEXUS_FrontendDiseqcMessageStatus_eRxReplyTimeout,
    NEXUS_FrontendDiseqcMessageStatus_eRxParityError,
    NEXUS_FrontendDiseqcMessageStatus_eAcwTimeout,
    NEXUS_FrontendDiseqcMessageStatus_eBusy,
    NEXUS_FrontendDiseqcMessageStatus_eMax
} NEXUS_FrontendDiseqcMessageStatus;
typedef struct NEXUS_FrontendDiseqcStatus
{
    _Bool toneEnabled;
    unsigned voltage;
    NEXUS_FrontendDiseqcMessageStatus sendStatus;
} NEXUS_FrontendDiseqcStatus;
NEXUS_Error NEXUS_Frontend_GetDiseqcStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendDiseqcStatus *pStatus
    );
NEXUS_Error NEXUS_Frontend_SendDiseqcMessage(
    NEXUS_FrontendHandle handle,
    const uint8_t *pSendData,
    size_t sendDataSize,
    const NEXUS_CallbackDesc *pSendComplete
    );
NEXUS_Error NEXUS_Frontend_ResetDiseqc(
    NEXUS_FrontendHandle handle,
    uint8_t options
    );
NEXUS_Error NEXUS_Frontend_GetDiseqcReply(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendDiseqcMessageStatus *pStatus,
    uint8_t *pReplyBuffer,
    size_t replyBufferSize,
    size_t *pReplyLength
    );
NEXUS_Error NEXUS_Frontend_SendDiseqcAcw(
    NEXUS_FrontendHandle handle,
    uint8_t codeWord
    );
NEXUS_Error NEXUS_Frontend_ReadSatelliteConfig(
    NEXUS_FrontendHandle handle,
    unsigned id,
    void *buffer,
    unsigned bufferSize
    );
NEXUS_Error NEXUS_Frontend_WriteSatelliteConfig(
    NEXUS_FrontendHandle handle,
    unsigned id,
    const void *buffer,
    unsigned bufferSize
    );
typedef enum NEXUS_FrontendSatellitePeakscanMode
{
    NEXUS_FrontendSatellitePeakscanMode_eSymbolRateScan,
    NEXUS_FrontendSatellitePeakscanMode_ePowerSpectrumDensity,
    NEXUS_FrontendSatellitePeakscanMode_eMax
} NEXUS_FrontendSatellitePeakscanMode;
typedef struct NEXUS_FrontendSatellitePeakscanSettings {
    unsigned frequency;
    unsigned minSymbolRate;
    unsigned maxSymbolRate;
    unsigned frequencyRange;
    unsigned frequencyStep;
    NEXUS_CallbackDesc peakscanCallback;
    NEXUS_FrontendSatellitePeakscanMode mode;
} NEXUS_FrontendSatellitePeakscanSettings;
void NEXUS_Frontend_GetDefaultSatellitePeakscanSettings(
    NEXUS_FrontendSatellitePeakscanSettings *pSettings
    );
NEXUS_Error NEXUS_Frontend_SatellitePeakscan(
    NEXUS_FrontendHandle handle,
    const NEXUS_FrontendSatellitePeakscanSettings *pSettings
    );
typedef struct NEXUS_FrontendSatellitePeakscanResult {
    unsigned peakFrequency;
    unsigned symbolRate;
    unsigned lastFrequency;
    unsigned peakPower;
} NEXUS_FrontendSatellitePeakscanResult;
NEXUS_Error NEXUS_Frontend_GetSatellitePeakscanResult(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendSatellitePeakscanResult *pResult
    );
typedef struct NEXUS_FrontendSatelliteToneSearchSettings {
    unsigned frequency;
    unsigned frequencyRange;
    struct {
        unsigned numerator;
        unsigned denominator;
    } minRatio;
    NEXUS_CallbackDesc completionCallback;
} NEXUS_FrontendSatelliteToneSearchSettings;
void NEXUS_Frontend_GetDefaultSatelliteToneSearchSettings(
    NEXUS_FrontendSatelliteToneSearchSettings *pSettings
    );
NEXUS_Error NEXUS_Frontend_SatelliteToneSearch(
    NEXUS_FrontendHandle handle,
    const NEXUS_FrontendSatelliteToneSearchSettings *pSettings
    );
typedef struct NEXUS_FrontendSatelliteToneSearchResult {
    unsigned peakFrequency;
    unsigned lastFrequency;
    unsigned peakPower;
    unsigned frequencyStep;
} NEXUS_FrontendSatelliteToneSearchResult;
NEXUS_Error NEXUS_Frontend_GetSatelliteToneSearchResult(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendSatelliteToneSearchResult *pResult
    );
typedef struct NEXUS_FrontendSatelliteSignalDetectStatus {
    _Bool enabled;
    _Bool detectionComplete;
    _Bool signalDetected;
} NEXUS_FrontendSatelliteSignalDetectStatus;
NEXUS_Error NEXUS_Frontend_GetSatelliteSignalDetectStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendSatelliteSignalDetectStatus *pStatus
    );
typedef struct NEXUS_FrontendSatelliteCapabilities
{
    unsigned numAdc;
    unsigned numChannels;
    _Bool externalBert;
} NEXUS_FrontendSatelliteCapabilities;
NEXUS_Error NEXUS_FrontendDevice_GetSatelliteCapabilities(
    NEXUS_FrontendDeviceHandle handle,
    NEXUS_FrontendSatelliteCapabilities *pCapabilities
);
typedef struct NEXUS_FrontendSatelliteRuntimeSettings
{
    unsigned selectedAdc;
    struct {
        _Bool enabled;
        _Bool invertClock;
    } externalBert;
} NEXUS_FrontendSatelliteRuntimeSettings;
NEXUS_Error NEXUS_Frontend_GetSatelliteRuntimeSettings(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendSatelliteRuntimeSettings *pSettings
);
NEXUS_Error NEXUS_Frontend_SetSatelliteRuntimeSettings(
    NEXUS_FrontendHandle handle,
    const NEXUS_FrontendSatelliteRuntimeSettings *pSettings
);
typedef enum NEXUS_FrontendOfdmGuardInterval
{
    NEXUS_FrontendOfdmGuardInterval_e1_32,
    NEXUS_FrontendOfdmGuardInterval_e1_16,
    NEXUS_FrontendOfdmGuardInterval_e1_8,
    NEXUS_FrontendOfdmGuardInterval_e1_4,
    NEXUS_FrontendOfdmGuardInterval_e1_128,
    NEXUS_FrontendOfdmGuardInterval_e19_128,
    NEXUS_FrontendOfdmGuardInterval_e19_256,
    NEXUS_FrontendOfdmGuardInterval_eMax
}NEXUS_FrontendOfdmGuardInterval;
typedef enum NEXUS_FrontendOfdmCodeRate
{
    NEXUS_FrontendOfdmCodeRate_e1_2,
    NEXUS_FrontendOfdmCodeRate_e2_3,
    NEXUS_FrontendOfdmCodeRate_e3_4,
    NEXUS_FrontendOfdmCodeRate_e3_5,
    NEXUS_FrontendOfdmCodeRate_e4_5,
    NEXUS_FrontendOfdmCodeRate_e5_6,
    NEXUS_FrontendOfdmCodeRate_e7_8,
    NEXUS_FrontendOfdmCodeRate_eMax
}NEXUS_FrontendOfdmCodeRate;
typedef enum NEXUS_FrontendOfdmHierarchy
{
    NEXUS_FrontendOfdmHierarchy_e0,
    NEXUS_FrontendOfdmHierarchy_e1,
    NEXUS_FrontendOfdmHierarchy_e2,
    NEXUS_FrontendOfdmHierarchy_e4,
    NEXUS_FrontendOfdmHierarchy_eMax
}NEXUS_FrontendOfdmHierarchy;
typedef enum NEXUS_FrontendOfdmTimeInterleaving
{
    NEXUS_FrontendOfdmTimeInterleaving_e0x,
    NEXUS_FrontendOfdmTimeInterleaving_e1x,
    NEXUS_FrontendOfdmTimeInterleaving_e2x,
    NEXUS_FrontendOfdmTimeInterleaving_e3x,
    NEXUS_FrontendOfdmTimeInterleaving_eMax
} NEXUS_FrontendOfdmTimeInterleaving;
typedef enum NEXUS_FrontendOfdmModulation
{
    NEXUS_FrontendOfdmModulation_eQpsk,
    NEXUS_FrontendOfdmModulation_eQam16,
    NEXUS_FrontendOfdmModulation_eQam64,
    NEXUS_FrontendOfdmModulation_eQam256,
    NEXUS_FrontendOfdmModulation_eDqpsk,
    NEXUS_FrontendOfdmModulation_eMax
}NEXUS_FrontendOfdmModulation;
typedef enum NEXUS_FrontendOfdmTransmissionMode
{
    NEXUS_FrontendOfdmTransmissionMode_e1k,
    NEXUS_FrontendOfdmTransmissionMode_e2k,
    NEXUS_FrontendOfdmTransmissionMode_e4k,
    NEXUS_FrontendOfdmTransmissionMode_e8k,
    NEXUS_FrontendOfdmTransmissionMode_e16k,
    NEXUS_FrontendOfdmTransmissionMode_e32k,
    NEXUS_FrontendOfdmTransmissionMode_eMax
}NEXUS_FrontendOfdmTransmissionMode;
typedef struct NEXUS_FrontendErrorRate
{
    uint64_t count;
    uint64_t total;
    uint32_t rate;
} NEXUS_FrontendErrorRate;
typedef struct NEXUS_FrontendBlockCounts
{
    unsigned corrected;
    unsigned uncorrected;
    unsigned clean;
} NEXUS_FrontendBlockCounts;
typedef enum NEXUS_FrontendOfdmMode
{
    NEXUS_FrontendOfdmMode_eDvbt,
    NEXUS_FrontendOfdmMode_eDvbt2,
    NEXUS_FrontendOfdmMode_eDvbc2,
    NEXUS_FrontendOfdmMode_eIsdbt,
    NEXUS_FrontendOfdmMode_eMax
} NEXUS_FrontendOfdmMode;
typedef enum NEXUS_FrontendOfdmCciMode
{
    NEXUS_FrontendOfdmCciMode_eNone,
    NEXUS_FrontendOfdmCciMode_eAuto,
    NEXUS_FrontendOfdmCciMode_eMax
} NEXUS_FrontendOfdmCciMode;
typedef enum NEXUS_FrontendOfdmPriority
{
    NEXUS_FrontendOfdmPriority_eHigh,
    NEXUS_FrontendOfdmPriority_eLow,
    NEXUS_FrontendOfdmPriority_eMax
} NEXUS_FrontendOfdmPriority;
typedef enum NEXUS_FrontendOfdmAcquisitionMode
{
    NEXUS_FrontendOfdmAcquisitionMode_eAuto,
    NEXUS_FrontendOfdmAcquisitionMode_eManual,
    NEXUS_FrontendOfdmAcquisitionMode_eScan,
    NEXUS_FrontendOfdmAcquisitionMode_eMax
}NEXUS_FrontendOfdmAcquisitionMode;
typedef enum NEXUS_FrontendOfdmPullInRange
{
    NEXUS_FrontendOfdmPullInRange_eNarrow,
    NEXUS_FrontendOfdmPullInRange_eWide,
    NEXUS_FrontendOfdmPullInRange_eMax
}NEXUS_FrontendOfdmPullInRange;
typedef enum NEXUS_FrontendOfdmSpectrum
{
    NEXUS_FrontendOfdmSpectrum_eAuto,
    NEXUS_FrontendOfdmSpectrum_eNonInverted,
    NEXUS_FrontendOfdmSpectrum_eInverted,
    NEXUS_FrontendOfdmSpectrum_eMax
} NEXUS_FrontendOfdmSpectrum;
typedef enum NEXUS_FrontendOfdmSpectrumMode
{
    NEXUS_FrontendOfdmSpectrumMode_eAuto,
    NEXUS_FrontendOfdmSpectrumMode_eManual,
    NEXUS_FrontendOfdmSpectrumMode_eMax
} NEXUS_FrontendOfdmSpectrumMode;
typedef enum NEXUS_FrontendOfdmSpectralInversion
{
    NEXUS_FrontendOfdmSpectralInversion_eNormal,
    NEXUS_FrontendOfdmSpectralInversion_eInverted,
    NEXUS_FrontendOfdmSpectralInversion_eMax
} NEXUS_FrontendOfdmSpectralInversion;
typedef enum NEXUS_FrontendOfdmModeGuard
{
    NEXUS_FrontendOfdmModeGuard_eManual,
    NEXUS_FrontendOfdmModeGuard_eAutoDvbt,
    NEXUS_FrontendOfdmModeGuard_eAutoIsdbtJapan,
    NEXUS_FrontendOfdmModeGuard_eAutoIsdbtBrazil,
    NEXUS_FrontendOfdmModeGuard_eMax
} NEXUS_FrontendOfdmModeGuard;
typedef enum NEXUS_FrontendOfdmBertHeader
{
     NEXUS_FrontendOfdmBertHeader_e4Byte,
     NEXUS_FrontendOfdmBertHeader_e1Byte,
     NEXUS_FrontendOfdmBertHeader_eMax
} NEXUS_FrontendOfdmBertHeader;
typedef enum NEXUS_FrontendOfdmBertPolynomial
{
     NEXUS_FrontendOfdmBertPolynomial_e23,
     NEXUS_FrontendOfdmBertPolynomial_e15,
     NEXUS_FrontendOfdmBertPolynomial_eMax
} NEXUS_FrontendOfdmBertPolynomial;
typedef enum NEXUS_FrontendDvbt2Profile
{
    NEXUS_FrontendDvbt2Profile_eBase,
    NEXUS_FrontendDvbt2Profile_eLite,
    NEXUS_FrontendDvbt2Profile_eMax
} NEXUS_FrontendDvbt2Profile;
typedef struct NEXUS_FrontendOfdmSettings
{
    NEXUS_FrontendOfdmMode mode;
    unsigned bandwidth;
    unsigned frequency;
    _Bool terrestrial;
    NEXUS_FrontendOfdmAcquisitionMode acquisitionMode;
    NEXUS_FrontendOfdmSpectrum spectrum;
    NEXUS_FrontendOfdmSpectrumMode spectrumMode;
    NEXUS_FrontendOfdmSpectralInversion spectralInversion;
    NEXUS_CallbackDesc lockCallback;
    NEXUS_CallbackDesc asyncStatusReadyCallback;
    _Bool spurDetectAndCancel;
    struct
    {
       _Bool plpMode;
       uint8_t plpId;
       NEXUS_FrontendDvbt2Profile profile;
    } dvbt2Settings;
    struct
    {
       _Bool plpMode;
       uint8_t plpId;
    } dvbc2Settings;
    struct
    {
      _Bool enabled;
      NEXUS_FrontendOfdmBertHeader header;
      NEXUS_FrontendOfdmBertPolynomial polynomial;
    } bert;
    unsigned ifFrequency;
    NEXUS_CallbackDesc ewsCallback;
    NEXUS_FrontendOfdmCciMode cciMode;
    NEXUS_FrontendOfdmPriority priority;
    NEXUS_FrontendOfdmPullInRange pullInRange;
    _Bool manualTpsSettings;
    struct
    {
        NEXUS_FrontendOfdmCodeRate highPriorityCodeRate;
        NEXUS_FrontendOfdmCodeRate lowPriorityCodeRate;
        NEXUS_FrontendOfdmHierarchy hierarchy;
        NEXUS_FrontendOfdmModulation modulation;
    } tpsSettings;
    _Bool manualModeSettings;
    struct
    {
        NEXUS_FrontendOfdmModeGuard modeGuard;
        NEXUS_FrontendOfdmTransmissionMode mode;
        NEXUS_FrontendOfdmGuardInterval guardInterval;
    } modeSettings;
    _Bool manualTmccSettings;
    struct
    {
        _Bool partialReception;
        NEXUS_FrontendOfdmModulation modulationA;
        NEXUS_FrontendOfdmCodeRate codeRateA;
        NEXUS_FrontendOfdmTimeInterleaving timeInterleavingA;
        unsigned numSegmentsA;
        NEXUS_FrontendOfdmModulation modulationB;
        NEXUS_FrontendOfdmCodeRate codeRateB;
        NEXUS_FrontendOfdmTimeInterleaving timeInterleavingB;
        unsigned numSegmentsB;
        NEXUS_FrontendOfdmModulation modulationC;
        NEXUS_FrontendOfdmCodeRate codeRateC;
        NEXUS_FrontendOfdmTimeInterleaving timeInterleavingC;
        unsigned numSegmentsC;
    } tmccSettings;
} NEXUS_FrontendOfdmSettings;
typedef struct NEXUS_FrontendDvbt2FecStatistics
{
    _Bool lock;
    int32_t snrData;
    uint32_t ldpcAvgIter;
    uint32_t ldpcTotIter;
    uint32_t ldpcTotFrm;
    uint32_t ldpcUncFrm;
    uint32_t ldpcBER;
    uint32_t bchCorBit;
    uint32_t bchTotBlk;
    uint32_t bchClnBlk;
    uint32_t bchCorBlk;
    uint32_t bchUncBlk;
} NEXUS_FrontendDvbt2FecStatistics;
typedef enum NEXUS_FrontendDvbt2StreamType
{
  NEXUS_FrontendDvbt2StreamType_eTs,
  NEXUS_FrontendDvbt2StreamType_eGs,
  NEXUS_FrontendDvbt2StreamType_eMixed,
  NEXUS_FrontendDvbt2StreamType_eMax
} NEXUS_FrontendDvbt2StreamType;
typedef enum NEXUS_FrontendDvbt2Papr
{
  NEXUS_FrontendDvbt2Papr_eNone,
  NEXUS_FrontendDvbt2Papr_eAce,
  NEXUS_FrontendDvbt2Papr_eTr,
  NEXUS_FrontendDvbt2Papr_eBoth,
  NEXUS_FrontendDvbt2Papr_eMax
} NEXUS_FrontendDvbt2Papr;
typedef enum NEXUS_FrontendDvbt2L1Mod
{
  NEXUS_FrontendDvbt2L1Mod_eBpsk,
  NEXUS_FrontendDvbt2L1Mod_eQpsk,
  NEXUS_FrontendDvbt2L1Mod_eQam16,
  NEXUS_FrontendDvbt2L1Mod_eQam64,
  NEXUS_FrontendDvbt2L1Mod_eMax
} NEXUS_FrontendDvbt2L1Mod;
typedef enum NEXUS_FrontendDvbt2L1CodeRate
{
  NEXUS_FrontendDvbt2L1CodeRate_e1_2,
  NEXUS_FrontendDvbt2L1CodeRate_eMax
} NEXUS_FrontendDvbt2L1CodeRate;
typedef enum NEXUS_FrontendDvbt2FecType
{
  NEXUS_FrontendDvbt2FecType_e16K,
  NEXUS_FrontendDvbt2FecType_e64K,
  NEXUS_FrontendDvbt2FecType_eMax
} NEXUS_FrontendDvbt2FecType;
typedef enum NEXUS_FrontendDvbt2PilotPattern
{
  NEXUS_FrontendDvbt2PilotPattern_e1,
  NEXUS_FrontendDvbt2PilotPattern_e2,
  NEXUS_FrontendDvbt2PilotPattern_e3,
  NEXUS_FrontendDvbt2PilotPattern_e4,
  NEXUS_FrontendDvbt2PilotPattern_e5,
  NEXUS_FrontendDvbt2PilotPattern_e6,
  NEXUS_FrontendDvbt2PilotPattern_e7,
  NEXUS_FrontendDvbt2PilotPattern_e8,
  NEXUS_FrontendDvbt2PilotPattern_eMax
} NEXUS_FrontendDvbt2PilotPattern;
typedef struct NEXUS_FrontendDvbt2L1PreStatus
{
    NEXUS_FrontendDvbt2StreamType streamType;
    _Bool bwtExt;
    uint8_t s1;
    uint8_t s2;
    _Bool l1RepetitionFlag;
    NEXUS_FrontendOfdmGuardInterval guardInterval;
    NEXUS_FrontendDvbt2Papr papr;
    NEXUS_FrontendDvbt2L1Mod l1Mod;
    NEXUS_FrontendDvbt2L1CodeRate l1CodeRate;
    NEXUS_FrontendDvbt2FecType l1FecType;
    NEXUS_FrontendDvbt2PilotPattern pilotPattern;
    uint8_t regenFlag;
    _Bool l1PostExt;
    uint8_t numRf;
    uint8_t currentRfIndex;
    uint8_t txIdAvailability;
    uint8_t numT2Frames;
    uint16_t numDataSymbols;
    uint16_t cellId;
    uint16_t networkId;
    uint16_t t2SystemId;
    uint32_t l1PostSize;
    uint32_t l1PostInfoSize;
} NEXUS_FrontendDvbt2L1PreStatus;
typedef enum NEXUS_FrontendDvbt2PlpType
{
  NEXUS_FrontendDvbt2PlpType_eCommon,
  NEXUS_FrontendDvbt2PlpType_eDataType1,
  NEXUS_FrontendDvbt2PlpType_eDataType2,
  NEXUS_FrontendDvbt2PlpType_eMax
} NEXUS_FrontendDvbt2PlpType;
typedef enum NEXUS_FrontendDvbt2PlpPayloadType
{
  NEXUS_FrontendDvbt2PlpPayloadType_eGfps,
  NEXUS_FrontendDvbt2PlpPayloadType_eGcs,
  NEXUS_FrontendDvbt2PlpPayloadType_eGse,
  NEXUS_FrontendDvbt2PlpPayloadType_eTs,
  NEXUS_FrontendDvbt2PlpPayloadType_eMax
} NEXUS_FrontendDvbt2PlpPayloadType;
typedef enum NEXUS_FrontendDvbt2PlpCodeRate
{
  NEXUS_FrontendDvbt2PlpCodeRate_e1_2,
  NEXUS_FrontendDvbt2PlpCodeRate_e3_5,
  NEXUS_FrontendDvbt2PlpCodeRate_e2_3,
  NEXUS_FrontendDvbt2PlpCodeRate_e3_4,
  NEXUS_FrontendDvbt2PlpCodeRate_e4_5,
  NEXUS_FrontendDvbt2PlpCodeRate_e5_6,
  NEXUS_FrontendDvbt2PlpCodeRate_eMax
} NEXUS_FrontendDvbt2PlpCodeRate;
typedef enum NEXUS_FrontendDvbt2PlpMod
{
  NEXUS_FrontendDvbt2PlpMod_eQpsk,
  NEXUS_FrontendDvbt2PlpMod_eQam16,
  NEXUS_FrontendDvbt2PlpMod_eQam64,
  NEXUS_FrontendDvbt2PlpMod_eQam256,
  NEXUS_FrontendDvbt2PlpMod_eMax
} NEXUS_FrontendDvbt2PlpMod;
typedef struct NEXUS_FrontendDvbt2L1PostCfgPlp
{
    uint8_t plpId;
    uint8_t plpGroupId;
    NEXUS_FrontendDvbt2PlpType plpType;
    NEXUS_FrontendDvbt2PlpPayloadType plpPayloadType;
    _Bool ffFlag;
    uint8_t firstRfIdx;
    uint8_t firstFrameIdx;
    NEXUS_FrontendDvbt2PlpCodeRate plpCodeRate;
    NEXUS_FrontendDvbt2PlpMod plpMod;
    _Bool plpRotation;
    NEXUS_FrontendDvbt2FecType plpFecType;
    uint16_t plpNumBlocksMax;
    uint8_t frameInterval;
    uint8_t timeIlLength;
    _Bool timeIlType;
    _Bool inBandFlag;
}NEXUS_FrontendDvbt2L1PostCfgPlp;
typedef struct NEXUS_FrontendDvbt2L1PostConfigurableStatus
{
    uint16_t subSlicesPerFrame;
    uint8_t numPlp;
    uint8_t numAux;
    uint8_t auxConfigRFu;
    uint8_t fefType;
    uint8_t rfIdx;
    uint8_t fefInterval;
    uint32_t frequency;
    uint32_t fefLength;
    NEXUS_FrontendDvbt2L1PostCfgPlp plpA;
    NEXUS_FrontendDvbt2L1PostCfgPlp plpB;
    uint8_t auxStreamType;
    uint32_t auxPrivateConf;
} NEXUS_FrontendDvbt2L1PostConfigurableStatus;
typedef struct NEXUS_FrontendDvbt2L1PostDynamicPlp
{
    uint8_t plpId;
    uint16_t plpNumBlocks;
    uint32_t plpStart;
} NEXUS_FrontendDvbt2L1PostDynamicPlp;
typedef struct NEXUS_FrontendDvbt2L1PostDynamicStatus
{
    uint8_t frameIdx;
    uint8_t l1ChanlgeCounter;
    uint8_t startRfIdx;
    uint32_t subSliceInterval;
    uint32_t type2Start;
    NEXUS_FrontendDvbt2L1PostDynamicPlp plpA;
    NEXUS_FrontendDvbt2L1PostDynamicPlp plpB;
    uint32_t auxPrivateDyn_47_32;
    uint32_t auxPrivateDyn_31_0;
} NEXUS_FrontendDvbt2L1PostDynamicStatus;
typedef struct NEXUS_FrontendDvbt2Plp
{
    uint8_t plpId;
    uint8_t plpGroupId;
    NEXUS_FrontendDvbt2PlpPayloadType plpPayloadType;
    NEXUS_FrontendDvbt2PlpType plpType;
} NEXUS_FrontendDvbt2Plp;
typedef struct NEXUS_FrontendDvbt2L1PlpStatus
{
    uint8_t numPlp;
    NEXUS_FrontendDvbt2Plp plp[255];
} NEXUS_FrontendDvbt2L1PlpStatus;
void NEXUS_Frontend_GetDefaultOfdmSettings(
    NEXUS_FrontendOfdmSettings *pSettings
    );
NEXUS_Error NEXUS_Frontend_TuneOfdm(
    NEXUS_FrontendHandle handle,
    const NEXUS_FrontendOfdmSettings *pSettings
    );
typedef struct NEXUS_FrontendOfdmStatus
{
    NEXUS_FrontendOfdmSettings settings;
    _Bool fecLock;
    _Bool receiverLock;
    _Bool noSignalDetected;
    _Bool spectrumInverted;
    _Bool ews;
    _Bool partialReception;
    NEXUS_FrontendOfdmModulation modulation;
    NEXUS_FrontendOfdmTransmissionMode transmissionMode;
    NEXUS_FrontendOfdmGuardInterval guardInterval;
    NEXUS_FrontendOfdmCodeRate codeRate;
    NEXUS_FrontendOfdmHierarchy hierarchy;
    unsigned cellId;
    int carrierOffset;
    int timingOffset;
    int snr;
    unsigned fecCorrectedBlocks;
    unsigned fecUncorrectedBlocks;
    unsigned fecCleanBlocks;
    unsigned reacquireCount;
    int signalStrength;
    unsigned signalLevelPercent;
    unsigned signalQualityPercent;
    unsigned viterbiUncorrectedBits;
    unsigned viterbiTotalBits;
    uint32_t viterbiErrorRate;
    uint32_t preViterbiErrorRate;
    unsigned ifAgcLevel;
    unsigned rfAgcLevel;
    uint32_t rsPerDelta;
    uint32_t vitBerDelta;
    NEXUS_FrontendOfdmModulation modulationA;
    NEXUS_FrontendOfdmCodeRate codeRateA;
    uint32_t isdbtAPreRS;
    NEXUS_FrontendOfdmTimeInterleaving timeInterleavingA;
    unsigned numSegmentsA;
    unsigned fecCorrectedBlocksA;
    unsigned fecUncorrectedBlocksA;
    unsigned fecCleanBlocksA;
    unsigned signalLevelPercentA;
    unsigned signalQualityPercentA;
    NEXUS_FrontendOfdmModulation modulationB;
    NEXUS_FrontendOfdmCodeRate codeRateB;
    uint32_t isdbtBPreRS;
    NEXUS_FrontendOfdmTimeInterleaving timeInterleavingB;
    unsigned numSegmentsB;
    unsigned fecCorrectedBlocksB;
    unsigned fecUncorrectedBlocksB;
    unsigned fecCleanBlocksB;
    unsigned signalLevelPercentB;
    unsigned signalQualityPercentB;
    NEXUS_FrontendOfdmModulation modulationC;
    NEXUS_FrontendOfdmCodeRate codeRateC;
    uint32_t isdbtCPreRS;
    NEXUS_FrontendOfdmTimeInterleaving timeInterleavingC;
    unsigned numSegmentsC;
    unsigned fecCorrectedBlocksC;
    unsigned fecUncorrectedBlocksC;
    unsigned fecCleanBlocksC;
    unsigned signalLevelPercentC;
    unsigned signalQualityPercentC;
    struct
    {
       int32_t gainOffset;
       NEXUS_FrontendDvbt2FecStatistics l1PreStatistics;
       NEXUS_FrontendDvbt2FecStatistics l1PostStatistics;
       NEXUS_FrontendDvbt2FecStatistics plpAStatistics;
       NEXUS_FrontendDvbt2FecStatistics plpBStatistics;
       NEXUS_FrontendDvbt2L1PreStatus l1PreStatus;
       NEXUS_FrontendDvbt2L1PostConfigurableStatus l1PostCfgStatus;
       NEXUS_FrontendDvbt2L1PostDynamicStatus l1PostDynamicStatus;
       NEXUS_FrontendDvbt2L1PlpStatus l1PlpStatus;
    } dvbt2Status;
} NEXUS_FrontendOfdmStatus;
NEXUS_Error NEXUS_Frontend_GetOfdmStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendOfdmStatus *pStatus
    );
NEXUS_Error NEXUS_Frontend_RequestOfdmAsyncStatus(
    NEXUS_FrontendHandle handle
    );
NEXUS_Error NEXUS_Frontend_GetOfdmAsyncStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendOfdmStatus *pStatus
    );
typedef enum NEXUS_FrontendOutOfBandMode
{
    NEXUS_FrontendOutOfBandMode_eAnnexAQpsk,
    NEXUS_FrontendOutOfBandMode_eDvs167Qpsk = NEXUS_FrontendOutOfBandMode_eAnnexAQpsk,
    NEXUS_FrontendOutOfBandMode_eDvs178Qpsk,
    NEXUS_FrontendOutOfBandMode_ePod_AnnexAQpsk,
    NEXUS_FrontendOutOfBandMode_ePod_Dvs167Qpsk = NEXUS_FrontendOutOfBandMode_ePod_AnnexAQpsk,
    NEXUS_FrontendOutOfBandMode_ePod_Dvs178Qpsk,
    NEXUS_FrontendOutOfBandMode_eMax
} NEXUS_FrontendOutOfBandMode;
typedef enum NEXUS_FrontendOutOfBandSpectrum
{
    NEXUS_FrontendOutOfBandSpectrum_eAuto,
    NEXUS_FrontendOutOfBandSpectrum_eNonInverted,
    NEXUS_FrontendOutOfBandSpectrum_eInverted,
    NEXUS_FrontendOutOfBandSpectrum_eMax
} NEXUS_FrontendOutOfBandSpectrum;
typedef enum NEXUS_FrontendOutOfBandBertSource
{
    NEXUS_FrontendOutOfBandBertSource_eIChOutput,
    NEXUS_FrontendOutOfBandBertSource_eQChOutput,
    NEXUS_FrontendOutOfBandBertSource_eIQChOutputInterleave,
    NEXUS_FrontendOutOfBandBertSource_eFecOutput,
    NEXUS_FrontendOutOfBandBertSource_eMax
} NEXUS_FrontendOutOfBandBertSource;
typedef enum NEXUS_FrontendOutOfBandNyquistFilter
{
    NEXUS_NyquistFilter_eRaisedCosine50,
    NEXUS_NyquistFilter_eRootRaisedCosine50,
    NEXUS_NyquistFilter_eRootRaisedCosine30,
    NEXUS_NyquistFilter_eMax
} NEXUS_FrontendOutOfBandNyquistFilter;
typedef enum NEXUS_FrontendOutOfBandOutputMode
{
    NEXUS_FrontendOutOfBandOutputMode_eDifferentialDecoder,
    NEXUS_FrontendOutOfBandOutputMode_eFec,
    NEXUS_FrontendOutOfBandOutputMode_eMax
} NEXUS_FrontendOutOfBandOutputMode;
typedef enum NEXUS_FrontendOutOfBandBertPolynomial
{
     NEXUS_FrontendOutOfBandBertPolynomial_e23,
     NEXUS_FrontendOutOfBandBertPolynomial_e15,
     NEXUS_FrontendOutOfBandBertPolynomial_eMax
} NEXUS_FrontendOutOfBandBertPolynomial;
typedef struct NEXUS_FrontendOutOfBandSettings
{
    NEXUS_FrontendOutOfBandMode mode;
    unsigned frequency;
    NEXUS_FrontendOutOfBandSpectrum spectrum;
    unsigned symbolRate;
    NEXUS_CallbackDesc lockCallback;
    _Bool openDrain;
    _Bool autoAcquire;
    NEXUS_FrontendOutOfBandBertSource bertSource;
    NEXUS_CallbackDesc asyncStatusReadyCallback;
    struct
    {
      NEXUS_FrontendOutOfBandBertPolynomial polynomial;
    } bert;
} NEXUS_FrontendOutOfBandSettings;
void NEXUS_Frontend_GetDefaultOutOfBandSettings(
    NEXUS_FrontendOutOfBandSettings *pSettings
    );
NEXUS_Error NEXUS_Frontend_TuneOutOfBand(
    NEXUS_FrontendHandle handle,
    const NEXUS_FrontendOutOfBandSettings *pSettings
    );
typedef struct NEXUS_FrontendOutOfBandStatus
{
    NEXUS_FrontendOutOfBandSettings settings;
    NEXUS_FrontendOutOfBandMode mode;
    NEXUS_FrontendOutOfBandSpectrum spectrum;
    unsigned symbolRate;
    unsigned ifFreq;
    unsigned loFreq;
    unsigned sysXtalFreq;
    _Bool isFecLocked;
    _Bool isQamLocked;
    _Bool isBertLocked;
    int snrEstimate;
    int agcIntLevel;
    int agcExtLevel;
    int carrierFreqOffset;
    int carrierPhaseOffset;
    unsigned uncorrectedCount;
    unsigned correctedCount;
    unsigned berErrorCount;
    unsigned postRsBer;
    unsigned postRsBerElapsedTime;
    int fdcChannelPower;
    int frontendGain;
    int digitalAgcGain;
    int highResEqualizerGain;
    unsigned acquisitionTime;
    unsigned totalAcquisitionTime;
} NEXUS_FrontendOutOfBandStatus;
NEXUS_Error NEXUS_Frontend_GetOutOfBandStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendOutOfBandStatus *pStatus
    );
NEXUS_Error NEXUS_Frontend_RequestOutOfBandAsyncStatus(
    NEXUS_FrontendHandle handle
    );
NEXUS_Error NEXUS_Frontend_GetOutOfBandAsyncStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendOutOfBandStatus *pStatus
    );
typedef enum NEXUS_FrontendUpstreamMode
{
    NEXUS_FrontendUpstreamMode_eAnnexA,
    NEXUS_FrontendUpstreamMode_eDvs167 = NEXUS_FrontendUpstreamMode_eAnnexA,
    NEXUS_FrontendUpstreamMode_eDavic = NEXUS_FrontendUpstreamMode_eAnnexA,
    NEXUS_FrontendUpstreamMode_eDvs178,
    NEXUS_FrontendUpstreamMode_eStarvue = NEXUS_FrontendUpstreamMode_eDvs178,
    NEXUS_FrontendUpstreamMode_eDocsis,
    NEXUS_FrontendUpstreamMode_ePodAnnexA,
    NEXUS_FrontendUpstreamMode_ePodDvs167 = NEXUS_FrontendUpstreamMode_ePodAnnexA,
    NEXUS_FrontendUpstreamMode_ePodDavic = NEXUS_FrontendUpstreamMode_ePodAnnexA,
    NEXUS_FrontendUpstreamMode_ePodDvs178,
    NEXUS_FrontendUpstreamMode_ePodStarvue = NEXUS_FrontendUpstreamMode_ePodDvs178,
    NEXUS_FrontendUpstreamMode_eSingleCw,
    NEXUS_FrontendUpstreamMode_eDoubleCw,
    NEXUS_FrontendUpstreamMode_ePn23,
    NEXUS_FrontendUpstreamMode_eMax
} NEXUS_FrontendUpstreamMode;
typedef struct NEXUS_FrontendUpstreamTestModeSettings
{
    _Bool bypassFilters;
    _Bool nyquistAlphaValue;
    _Bool spectrumInverted;
    unsigned int qamMode;
    unsigned long rfFreq2;
} NEXUS_FrontendUpstreamTestModeSettings;
typedef struct NEXUS_FrontendUpstreamSettings
{
    NEXUS_FrontendUpstreamMode mode;
    unsigned frequency;
    unsigned symbolRate;
    unsigned powerLevel;
    NEXUS_FrontendUpstreamTestModeSettings testModeSettings;
} NEXUS_FrontendUpstreamSettings;
void NEXUS_Frontend_GetDefaultUpstreamSettings(
    NEXUS_FrontendUpstreamSettings *pSettings
    );
NEXUS_Error NEXUS_Frontend_TuneUpstream(
    NEXUS_FrontendHandle handle,
    const NEXUS_FrontendUpstreamSettings *pSettings
    );
typedef struct NEXUS_FrontendUpstreamStatus
{
    NEXUS_FrontendUpstreamMode mode;
    unsigned frequency;
    unsigned symbolRate;
    unsigned powerLevel;
    unsigned sysXtalFreq;
} NEXUS_FrontendUpstreamStatus;
NEXUS_Error NEXUS_Frontend_GetUpstreamStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendUpstreamStatus *pStatus
    );
typedef struct NEXUS_Ifd *NEXUS_IfdHandle;
typedef enum NEXUS_IfdInputType
{
    NEXUS_IfdInputType_eNone,
    NEXUS_IfdInputType_eIf,
    NEXUS_IfdInputType_eSif,
    NEXUS_IfdInputType_eBaseband,
    NEXUS_IfdInputType_eMax
} NEXUS_IfdInputType;
typedef enum NEXUS_IfdAudioMode
{
    NEXUS_IfdAudioMode_eUs,
    NEXUS_IfdAudioMode_eKorea,
    NEXUS_IfdAudioMode_eJapan,
    NEXUS_IfdAudioMode_eIndia,
    NEXUS_IfdAudioMode_eNicam,
    NEXUS_IfdAudioMode_ePalA2,
    NEXUS_IfdAudioMode_eAutoNicamPalA2,
    NEXUS_IfdAudioMode_eMax
} NEXUS_IfdAudioMode;
typedef enum NEXUS_UsIfdAudioMode
{
    NEXUS_UsIfdAudioMode_eMono,
    NEXUS_UsIfdAudioMode_eStereo,
    NEXUS_UsIfdAudioMode_eSap,
    NEXUS_UsIfdAudioMode_eSapMono,
    NEXUS_UsIfdAudioMode_eMax
} NEXUS_UsIfdAudioMode;
typedef enum NEXUS_KoreaIfdAudioMode
{
    NEXUS_KoreaIfdAudioMode_eMono,
    NEXUS_KoreaIfdAudioMode_eStereo,
    NEXUS_KoreaIfdAudioMode_eSub,
    NEXUS_KoreaIfdAudioMode_eDualMono,
    NEXUS_KoreaIfdAudioMode_eMax
} NEXUS_KoreaIfdAudioMode;
typedef enum NEXUS_JapanIfdAudioMode
{
    NEXUS_JapanIfdAudioMode_eMono,
    NEXUS_JapanIfdAudioMode_eStereo,
    NEXUS_JapanIfdAudioMode_eSub,
    NEXUS_JapanIfdAudioMode_eDualMono,
    NEXUS_JapanIfdAudioMode_eMax
} NEXUS_JapanIfdAudioMode;
typedef enum NEXUS_NicamIfdAudioMode
{
    NEXUS_NicamIfdAudioMode_eFmAmMono,
    NEXUS_NicamIfdAudioMode_eMono,
    NEXUS_NicamIfdAudioMode_eStereo,
    NEXUS_NicamIfdAudioMode_eDualMono1,
    NEXUS_NicamIfdAudioMode_eDualMono2,
    NEXUS_NicamIfdAudioMode_eDualMono1And2,
    NEXUS_NicamIfdAudioMode_eMax
} NEXUS_NicamIfdAudioMode;
typedef enum NEXUS_PalA2IfdAudioMode
{
    NEXUS_PalA2IfdAudioMode_eMono,
    NEXUS_PalA2IfdAudioMode_eStereo,
    NEXUS_PalA2IfdAudioMode_eSub,
    NEXUS_PalA2IfdAudioMode_eDualMono,
    NEXUS_PalA2IfdAudioMode_eMax
} NEXUS_PalA2IfdAudioMode;
typedef enum NEXUS_IfdAudioDeviation
{
    NEXUS_IfdAudioDeviation_eNormal,
    NEXUS_IfdAudioDeviation_eMedium,
    NEXUS_IfdAudioDeviation_eHigh,
    NEXUS_IfdAudioDeviation_eMax
} NEXUS_IfdAudioDeviation;
typedef enum NEXUS_IfdPullInRange
{
    NEXUS_IfdPullInRange_eDefault,
    NEXUS_IfdPullInRange_e32kHz,
    NEXUS_IfdPullInRange_e250kHz,
    NEXUS_IfdPullInRange_e500kHz,
    NEXUS_IfdPullInRange_e750kHz,
    NEXUS_IfdPullInRange_e1000kHz,
    NEXUS_IfdPullInRange_e1100kHz,
    NEXUS_IfdPullInRange_eMax
} NEXUS_IfdPullInRange;
typedef struct NEXUS_IfdSettings
{
    _Bool enabled;
    _Bool spectrumInverted;
    NEXUS_IfdInputType videoInputType;
    unsigned videoInputIndex;
    NEXUS_IfdInputType audioInputType;
    unsigned audioInputIndex;
    unsigned carrierFrequency;
    NEXUS_VideoFormat videoFormat;
    NEXUS_IfdAudioMode audioMode;
    NEXUS_IfdAudioDeviation audioDeviation;
    NEXUS_IfdPullInRange pullInRange;
    union
    {
        struct
        {
           NEXUS_UsIfdAudioMode mode;
        } us;
        struct
        {
            NEXUS_KoreaIfdAudioMode mode;
        } korea;
        struct
        {
            NEXUS_JapanIfdAudioMode mode;
        } japan;
        struct
        {
            NEXUS_NicamIfdAudioMode mode;
        } nicam;
        struct
        {
            NEXUS_PalA2IfdAudioMode mode;
        } palA2;
        struct
        {
            NEXUS_NicamIfdAudioMode nicamMode;
            NEXUS_PalA2IfdAudioMode palA2Mode;
        } autoNicamPalA2;
    } audioModeSettings;
    NEXUS_CallbackDesc lockCallback;
} NEXUS_IfdSettings;
void NEXUS_Ifd_GetSettings(
    NEXUS_IfdHandle handle,
    NEXUS_IfdSettings *pSettings
    );
void NEXUS_Ifd_SetSettings(
    NEXUS_IfdHandle handle,
    const NEXUS_IfdSettings *pSettings
    );
typedef struct NEXUS_IfdStatus
{
    _Bool locked;
    int carrierOffset;
    int rfAgcLevel;
    int ifAgcLevel;
} NEXUS_IfdStatus;
void NEXUS_Ifd_GetStatus(
    NEXUS_IfdHandle handle,
    NEXUS_IfdStatus *pStatus
    );
NEXUS_IfdHandle NEXUS_Ifd_OpenStub(
    unsigned index
    );
void NEXUS_Ifd_Close(
    NEXUS_IfdHandle handle
    );
typedef struct NEXUS_FrontendAnalogSettings
{
    unsigned frequency;
    _Bool fastAcquisition;
    _Bool terrestrial;
    NEXUS_IfdSettings ifdSettings;
} NEXUS_FrontendAnalogSettings;
void NEXUS_Frontend_GetDefaultAnalogSettings(
    NEXUS_FrontendAnalogSettings *pSettings
    );
NEXUS_Error NEXUS_Frontend_TuneAnalog(
    NEXUS_FrontendHandle handle,
    const NEXUS_FrontendAnalogSettings *pSettings
    );
typedef enum NEXUS_FrontendNicamEncoding
{
    NEXUS_FrontendNicamEncoding_eUnknown,
    NEXUS_FrontendNicamEncoding_eStereo_BackupFm,
    NEXUS_FrontendNicamEncoding_eDualMono_BackupFm,
    NEXUS_FrontendNicamEncoding_eStereo_NoBackup,
    NEXUS_FrontendNicamEncoding_eDualMono_NoBackup,
    NEXUS_FrontendNicamEncoding_eMonoData_BackupFm,
    NEXUS_FrontendNicamEncoding_eMonoData_NoBackup,
    NEXUS_FrontendNicamEncoding_eData_BackupFm,
    NEXUS_FrontendNicamEncoding_eData_NoBackup,
    NEXUS_FrontendNicamEncoding_eMax
} NEXUS_FrontendNicamEncoding;
typedef struct NEXUS_FrontendAnalogStatus
{
    NEXUS_FrontendAnalogSettings settings;
    _Bool locked;
    int carrierOffset;
    int rfAgcLevel;
    int ifAgcLevel;
    int rfInputPower;
    _Bool sapDetected;
    _Bool stereoDetected;
    _Bool nicamLocked;
    NEXUS_FrontendNicamEncoding nicamEncoding;
    uint32_t nicamParityError;
    uint32_t nicamErrorCount;
    uint64_t avRatio1;
    uint64_t avRatio2;
    NEXUS_VideoFormat ifdVideoFormat;
    NEXUS_IfdAudioMode ifdAudioMode;
} NEXUS_FrontendAnalogStatus;
NEXUS_Error NEXUS_Frontend_GetAnalogStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendAnalogStatus *pStatus
    );
NEXUS_VideoInputHandle NEXUS_Frontend_GetAnalogVideoConnector(
    NEXUS_FrontendHandle handle
    );
NEXUS_AudioInputHandle NEXUS_Frontend_GetAnalogAudioConnector(
    NEXUS_FrontendHandle handle
    );
typedef struct NEXUS_FrontendAnalogAgcSettings
{
    uint16_t top;
    uint8_t rfBandwidth;
    uint8_t ifBandwidth;
    uint8_t delay;
    _Bool agcFreeze;
    uint16_t ifAgcValue;
} NEXUS_FrontendAnalogAgcSettings;
void NEXUS_Frontend_GetAnalogAgcSettings(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendAnalogAgcSettings *pSettings
    );
NEXUS_Error NEXUS_Frontend_SetAnalogAgcSettings(
    NEXUS_FrontendHandle handle,
    const NEXUS_FrontendAnalogAgcSettings *pSettings
    );
typedef struct NEXUS_Tuner *NEXUS_TunerHandle;
typedef enum NEXUS_TunerMode
{
    NEXUS_TunerMode_eDigital,
    NEXUS_TunerMode_eAnalog,
    NEXUS_TunerMode_eQam,
    NEXUS_TunerMode_eVsb,
    NEXUS_TunerMode_eOfdm,
    NEXUS_TunerMode_eMax
} NEXUS_TunerMode;
NEXUS_Error NEXUS_Tuner_SetFrequency(
    NEXUS_TunerHandle handle,
    NEXUS_TunerMode mode,
    unsigned frequency
    );
void NEXUS_Tuner_Init(
    NEXUS_TunerHandle tuner
    );
typedef struct NEXUS_TunerStatus
{
    uint32_t centerIf;
    int32_t ifShift;
    unsigned frequency;
    _Bool spectrumInverted;
    int adcPgaGain;
    _Bool tuneComplete;
    int rssi;
} NEXUS_TunerStatus;
NEXUS_Error NEXUS_Tuner_RequestAsyncStatus(
    NEXUS_TunerHandle tuner
    );
NEXUS_Error NEXUS_Tuner_GetAsyncStatus(
    NEXUS_TunerHandle tuner,
    NEXUS_TunerStatus *pStatus
    );
void NEXUS_Tuner_GetStatus(
    NEXUS_TunerHandle tuner,
    NEXUS_TunerStatus *pStatus
    );
typedef struct NEXUS_TunerTuneSettings
{
    NEXUS_TunerMode mode;
    struct
    {
        struct
        {
            NEXUS_FrontendQamMode qamMode;
            NEXUS_FrontendQamAnnex annex;
        } qam;
        struct
        {
            NEXUS_FrontendVsbMode vsbMode;
        } vsb;
        struct
        {
            NEXUS_FrontendOfdmMode ofdmMode;
        } ofdm;
        struct
        {
            NEXUS_VideoFormat videoFormat;
        } analog;
    } modeSettings;
    unsigned frequency;
    NEXUS_CallbackDesc tuneCompleteCallback;
    NEXUS_CallbackDesc asyncStatusReadyCallback;
} NEXUS_TunerTuneSettings;
void NEXUS_Tuner_GetDefaultTuneSettings(
    NEXUS_TunerMode mode,
    NEXUS_TunerTuneSettings *pSettings
    );
NEXUS_Error NEXUS_Tuner_Tune(
    NEXUS_TunerHandle tuner,
    const NEXUS_TunerTuneSettings *pSettings
    );
void NEXUS_Tuner_Untune(
    NEXUS_TunerHandle tuner
    );
typedef struct NEXUS_TunerSettings
{
    unsigned top;
    unsigned ifFrequency;
    unsigned bandwidth;
    int dacAttenuation;
} NEXUS_TunerSettings;
void NEXUS_Tuner_GetSettings(
    NEXUS_TunerHandle tuner,
    NEXUS_TunerSettings *pSettings
    );
NEXUS_Error NEXUS_Tuner_SetSettings(
    NEXUS_TunerHandle tuner,
    const NEXUS_TunerSettings *pSettings
    );
NEXUS_TunerHandle NEXUS_Tuner_OpenGeneric(
    void
    );
void NEXUS_Tuner_Close(
    NEXUS_TunerHandle handle
    );
typedef struct NEXUS_TunerAttributes
{
    struct
    {
        uint32_t major;
        uint32_t minor;
    } version;
    _Bool powerLevelReadingSupported;
    _Bool adcPgaGainReadingSupported;
} NEXUS_TunerAttributes;
void NEXUS_Tuner_GetAttributes(
    NEXUS_TunerHandle tuner,
    NEXUS_TunerAttributes *pAttributes
    );
NEXUS_Error NEXUS_Tuner_ReadPowerLevel(
    NEXUS_TunerHandle handle,
    int *pPowerLevel
    );
typedef struct NEXUS_TunerAcquireSettings
{
    unsigned index;
} NEXUS_TunerAcquireSettings;
void NEXUS_Tuner_GetDefaultAcquireSettings(
    NEXUS_TunerAcquireSettings *pSettings
    );
NEXUS_TunerHandle NEXUS_Tuner_Acquire(
    const NEXUS_TunerAcquireSettings *pSettings
    );
void NEXUS_Tuner_Release(
    NEXUS_TunerHandle handle
    );
typedef struct NEXUS_FrontendCard *NEXUS_FrontendCardHandle;
typedef struct NEXUS_FrontendCardSettings
{
    NEXUS_I2cHandle i2cDevice;
    unsigned isrNumber;
    unsigned numChannels;
    unsigned numOutOfBandChannels;
    unsigned numUpstreamChannels;
    _Bool bitWideSync;
    NEXUS_GpioHandle gpioInterrupt;
} NEXUS_FrontendCardSettings;
void NEXUS_FrontendCard_GetDefaultSettings(
    NEXUS_FrontendCardSettings *pSettings
    );
NEXUS_FrontendCardHandle NEXUS_FrontendCard_Open(
    const NEXUS_FrontendCardSettings *pSettings
    );
void NEXUS_FrontendCard_Close(
    NEXUS_FrontendCardHandle handle
    );
NEXUS_Error NEXUS_FrontendCard_GetNumChannels(
    NEXUS_FrontendCardHandle handle,
    unsigned *pNumChannels
    );
NEXUS_FrontendHandle NEXUS_FrontendCard_GetChannel(
    NEXUS_FrontendCardHandle handle,
    unsigned index
    );
NEXUS_Error NEXUS_FrontendCard_GetNumOutOfBandChannels(
    NEXUS_FrontendCardHandle handle,
    unsigned *pNumOutOfBandChannels
    );
NEXUS_FrontendHandle NEXUS_FrontendCard_GetOutOfBandChannel(
    NEXUS_FrontendCardHandle handle,
    unsigned index
    );
NEXUS_Error NEXUS_FrontendCard_GetNumUpstreamChannels(
    NEXUS_FrontendCardHandle handle,
    unsigned *pNumUpstreamChannels
    );
NEXUS_FrontendHandle NEXUS_FrontendCard_GetUpstreamChannel(
    NEXUS_FrontendCardHandle handle,
    unsigned index
    );
typedef struct NEXUS_FrontendDvbt2BasicStatus
{
    NEXUS_FrontendOfdmSettings settings;
    _Bool fecLock;
    _Bool spectrumInverted;
    int32_t snr;
    int32_t gainOffset;
    int32_t carrierOffset;
    int32_t timingOffset;
    int32_t signalStrength;
    unsigned signalLevelPercent;
    unsigned signalQualityPercent;
    unsigned reacquireCount;
    NEXUS_FrontendDvbt2Profile profile;
} NEXUS_FrontendDvbt2BasicStatus;
typedef enum NEXUS_FrontendDvbt2StatusType
{
  NEXUS_FrontendDvbt2StatusType_eFecStatisticsL1Pre,
  NEXUS_FrontendDvbt2StatusType_eFecStatisticsL1Post,
  NEXUS_FrontendDvbt2StatusType_eFecStatisticsPlpA,
  NEXUS_FrontendDvbt2StatusType_eFecStatisticsPlpB,
  NEXUS_FrontendDvbt2StatusType_eL1Pre,
  NEXUS_FrontendDvbt2StatusType_eL1PostConfigurable,
  NEXUS_FrontendDvbt2StatusType_eL1PostDynamic,
  NEXUS_FrontendDvbt2StatusType_eL1Plp,
  NEXUS_FrontendDvbt2StatusType_eBasic,
  NEXUS_FrontendDvbt2StatusType_eMax
} NEXUS_FrontendDvbt2StatusType;
typedef struct NEXUS_FrontendDvbt2StatusReady
{
    _Bool type[NEXUS_FrontendDvbt2StatusType_eMax];
} NEXUS_FrontendDvbt2StatusReady;
typedef struct NEXUS_FrontendDvbt2Status
{
    NEXUS_FrontendDvbt2StatusType type;
    union
    {
        NEXUS_FrontendDvbt2FecStatistics fecStatistics;
        NEXUS_FrontendDvbt2L1PreStatus l1Pre;
        NEXUS_FrontendDvbt2L1PostConfigurableStatus l1PostConfigurable;
        NEXUS_FrontendDvbt2L1PostDynamicStatus l1PostDynamic;
        NEXUS_FrontendDvbt2L1PlpStatus l1Plp;
        NEXUS_FrontendDvbt2BasicStatus basic;
    } status;
} NEXUS_FrontendDvbt2Status;
NEXUS_Error NEXUS_Frontend_RequestDvbt2AsyncStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendDvbt2StatusType type
    );
NEXUS_Error NEXUS_Frontend_GetDvbt2AsyncStatusReady(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendDvbt2StatusReady *pStatusReady
    );
NEXUS_Error NEXUS_Frontend_GetDvbt2AsyncStatus(
     NEXUS_FrontendHandle handle,
     NEXUS_FrontendDvbt2StatusType type,
     NEXUS_FrontendDvbt2Status *pStatus
     );
NEXUS_Error NEXUS_Frontend_GetDvbt2AsyncFecStatistics (
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendDvbt2StatusType type,
    NEXUS_FrontendDvbt2FecStatistics *pStatistics
    );
NEXUS_Error NEXUS_Frontend_GetDvbt2AsyncL1PreStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendDvbt2L1PreStatus *pStatus
    );
NEXUS_Error NEXUS_Frontend_GetDvbt2AsyncL1PostConfigurableStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendDvbt2L1PostConfigurableStatus *pStatus
    );
NEXUS_Error NEXUS_Frontend_GetDvbt2AsyncPostDynamicStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendDvbt2L1PostDynamicStatus *pStatus
    );
NEXUS_Error NEXUS_Frontend_GetDvbt2AsyncL1PlpStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendDvbt2L1PlpStatus *pStatus
    );
NEXUS_Error NEXUS_Frontend_GetDvbt2AsyncBasicStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendDvbt2BasicStatus *pStatus
    );
typedef enum NEXUS_FrontendDvbc2DsliceType
{
    NEXUS_FrontendDvbc2DsliceType_e1,
    NEXUS_FrontendDvbc2DsliceType_e2,
    NEXUS_FrontendDvbc2DsliceType_eMax
}NEXUS_FrontendDvbc2DsliceType;
typedef enum NEXUS_FrontendDvbc2FecHeaderType
{
    NEXUS_FrontendDvbc2FecHeaderType_e0,
    NEXUS_FrontendDvbc2FecHeaderType_e1,
    NEXUS_FrontendDvbc2FecHeaderType_eMax
}NEXUS_FrontendDvbc2FecHeaderType;
typedef enum NEXUS_FrontendDvbc2FecType
{
    NEXUS_FrontendDvbc2FecType_e16K,
    NEXUS_FrontendDvbc2FecType_e64K,
    NEXUS_FrontendDvbc2FecType_eMax
} NEXUS_FrontendDvbc2FecType;
typedef enum NEXUS_FrontendDvbc2L1Part2Modulation
{
    NEXUS_FrontendDvbc2L1Part2Modulation_eBpsk,
    NEXUS_FrontendDvbc2L1Part2Modulation_eQpsk,
    NEXUS_FrontendDvbc2L1Part2Modulation_eQam16,
    NEXUS_FrontendDvbc2L1Part2Modulation_eQam64,
    NEXUS_FrontendDvbc2L1Part2Modulation_eMax
} NEXUS_FrontendDvbc2L1Part2Modulation;
typedef enum NEXUS_FrontendDvbc2L1CodeRate
{
    NEXUS_FrontendDvbc2L1CodeRate_e2_3,
    NEXUS_FrontendDvbc2L1CodeRate_e3_4,
    NEXUS_FrontendDvbc2L1CodeRate_e4_5,
    NEXUS_FrontendDvbc2L1CodeRate_e5_6,
    NEXUS_FrontendDvbc2L1CodeRate_e8_9,
    NEXUS_FrontendDvbc2L1CodeRate_e9_10,
    NEXUS_FrontendDvbc2L1CodeRate_eMax
} NEXUS_FrontendDvbc2L1CodeRate;
typedef struct NEXUS_FrontendDvbc2L1part2PlpParams
{
    uint16_t plpStart;
    NEXUS_FrontendDvbc2FecType plpFecType;
    NEXUS_FrontendDvbc2L1Part2Modulation plpMod;
    NEXUS_FrontendDvbc2L1CodeRate plpCod;
} NEXUS_FrontendDvbc2L1part2PlpParams;
typedef struct NEXUS_FrontendDvbc2L1part2Reprocessing
{
    uint16_t transportStreamId;
    uint16_t originalNetworkId;
} NEXUS_FrontendDvbc2L1part2Reprocessing;
typedef enum NEXUS_FrontendDvbc2PlpType
{
    NEXUS_FrontendDvbc2PlpType_eCommon,
    NEXUS_FrontendDvbc2PlpType_eGroupedData,
    NEXUS_FrontendDvbc2PlpType_eNormalData,
    NEXUS_FrontendDvbc2PlpType_eMax
} NEXUS_FrontendDvbc2PlpType;
typedef enum NEXUS_FrontendDvbc2PlpPayloadType
{
    NEXUS_FrontendDvbc2PlpPayloadType_eGfps,
    NEXUS_FrontendDvbc2PlpPayloadType_eGcs,
    NEXUS_FrontendDvbc2PlpPayloadType_eGse,
    NEXUS_FrontendDvbc2PlpPayloadType_eTs,
    NEXUS_FrontendDvbc2PlpPayloadType_eMax
} NEXUS_FrontendDvbc2PlpPayloadType;
typedef struct NEXUS_FrontendDvbc2L1part2DslicePlp
{
    uint8_t dsliceId;
    uint8_t plpId;
    _Bool plpBundled;
    NEXUS_FrontendDvbc2PlpType plpType;
    NEXUS_FrontendDvbc2PlpPayloadType plpPayloadType;
    uint8_t plpGroupId;
    NEXUS_FrontendDvbc2L1part2PlpParams plpParams;
    _Bool psiReprocessing;
    NEXUS_FrontendDvbc2L1part2Reprocessing reprocessing;
} NEXUS_FrontendDvbc2L1part2DslicePlp;
typedef enum NEXUS_FrontendDvbc2TimeInterleaving
{
    NEXUS_FrontendDvbc2TimeInterleaving_e0x,
    NEXUS_FrontendDvbc2TimeInterleaving_e1x,
    NEXUS_FrontendDvbc2TimeInterleaving_e2x,
    NEXUS_FrontendDvbc2TimeInterleaving_e3x,
    NEXUS_FrontendDvbc2TimeInterleaving_eMax
}NEXUS_FrontendDvbc2TimeInterleaving;
typedef struct NEXUS_FrontendDvbc2L1Part2Dslice
{
    uint8_t dsliceId;
    uint16_t dsliceTunePos;
    uint16_t dsliceOffsetLeft;
    uint16_t dsliceOffsetRight;
    NEXUS_FrontendDvbc2TimeInterleaving timeInterLeaving;
    NEXUS_FrontendDvbc2DsliceType dsliceType;
    NEXUS_FrontendDvbc2FecHeaderType fecHeaderType;
    _Bool dsliceConstConf;
    _Bool dsliceLeftNotch;
    uint8_t dsliceNumPlp;
    uint32_t plpsPresent[8];
} NEXUS_FrontendDvbc2L1Part2Dslice;
typedef struct NEXUS_FrontendDvbc2L1Dslice
{
    uint8_t dsliceId;
    uint8_t dsliceNumPlp;
    uint32_t plpsPresent[8];
} NEXUS_FrontendDvbc2L1Dslice;
typedef struct NEXUS_FrontendDvbc2L1DsliceStatus
{
    uint8_t numDslices;
    NEXUS_FrontendDvbc2L1Dslice dslices[1];
} NEXUS_FrontendDvbc2L1DsliceStatus;
typedef struct NEXUS_FrontendDvbc2L1part2Notch
{
    uint16_t notchStart;
    uint16_t notchWidth;
} NEXUS_FrontendDvbc2L1part2Notch;
typedef struct NEXUS_FrontendDvbc2L1NotchStatus
{
    uint8_t numNotches;
    NEXUS_FrontendDvbc2L1part2Notch notches[16];
} NEXUS_FrontendDvbc2L1NotchStatus;
typedef struct NEXUS_FrontendDvbc2Plp
{
    uint8_t plpId;
    uint8_t plpGroupId;
    NEXUS_FrontendDvbc2PlpPayloadType plpPayloadType;
    NEXUS_FrontendDvbc2PlpType plpType;
} NEXUS_FrontendDvbc2Plp;
typedef struct NEXUS_FrontendDvbc2L1PlpStatus
{
    uint8_t numPlp;
    NEXUS_FrontendDvbc2Plp plp[255];
} NEXUS_FrontendDvbc2L1PlpStatus;
typedef struct NEXUS_FrontendDvbc2FecStatistics
{
    _Bool lock;
    int32_t snrData;
    uint32_t ldpcAvgIter;
    uint32_t ldpcTotIter;
    uint32_t ldpcTotFrm;
    uint32_t ldpcUncFrm;
    uint32_t ldpcBER;
    uint32_t bchCorBit;
    uint32_t bchTotBlk;
    uint32_t bchClnBlk;
    uint32_t bchCorBlk;
    uint32_t bchUncBlk;
} NEXUS_FrontendDvbc2FecStatistics;
typedef struct NEXUS_FrontendDvbc2L1Part2Status
{
    uint16_t networkId;
    uint16_t c2SystemId;
    uint32_t startFrequency;
    uint16_t c2Bandwidth;
    NEXUS_FrontendOfdmGuardInterval guardInterval;
    uint16_t c2FrameLength;
    uint8_t l1Part2ChangeCounter;
    uint8_t numDslice;
    uint8_t numNotch;
    NEXUS_FrontendDvbc2L1Part2Dslice dslices[1];
    NEXUS_FrontendDvbc2L1part2DslicePlp plps[2];
    NEXUS_FrontendDvbc2L1part2Notch notches[16];
    _Bool reservedTone;
} NEXUS_FrontendDvbc2L1Part2Status;
typedef struct NEXUS_FrontendDvbc2BasicStatus
{
    NEXUS_FrontendOfdmSettings settings;
    _Bool fecLock;
    _Bool spectrumInverted;
    int32_t snr;
    int32_t gainOffset;
    int32_t carrierOffset;
    int32_t timingOffset;
    int32_t signalStrength;
    unsigned signalLevelPercent;
    unsigned signalQualityPercent;
    unsigned reacquireCount;
} NEXUS_FrontendDvbc2BasicStatus;
typedef enum NEXUS_FrontendDvbc2StatusType
{
    NEXUS_FrontendDvbc2StatusType_eFecStatisticsL1Part2,
    NEXUS_FrontendDvbc2StatusType_eFecStatisticsPlpA,
    NEXUS_FrontendDvbc2StatusType_eFecStatisticsPlpB,
    NEXUS_FrontendDvbc2StatusType_eL1Part2,
    NEXUS_FrontendDvbc2StatusType_eL1Dslice,
    NEXUS_FrontendDvbc2StatusType_eL1Notch,
    NEXUS_FrontendDvbc2StatusType_eL1Plp,
    NEXUS_FrontendDvbc2StatusType_eBasic,
    NEXUS_FrontendDvbc2StatusType_eMax
} NEXUS_FrontendDvbc2StatusType;
typedef struct NEXUS_FrontendDvbc2StatusReady
{
    _Bool type[NEXUS_FrontendDvbc2StatusType_eMax];
} NEXUS_FrontendDvbc2StatusReady;
typedef struct NEXUS_FrontendDvbc2Status
{
    NEXUS_FrontendDvbc2StatusType type;
    union
    {
        NEXUS_FrontendDvbc2FecStatistics fecStatistics;
        NEXUS_FrontendDvbc2L1Part2Status l1Part2;
        NEXUS_FrontendDvbc2L1DsliceStatus l1Dslice;
        NEXUS_FrontendDvbc2L1NotchStatus l1Notch;
        NEXUS_FrontendDvbc2L1PlpStatus l1Plp;
        NEXUS_FrontendDvbc2BasicStatus basic;
    } status;
} NEXUS_FrontendDvbc2Status;
NEXUS_Error NEXUS_Frontend_RequestDvbc2AsyncStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendDvbc2StatusType type
    );
NEXUS_Error NEXUS_Frontend_GetDvbc2AsyncStatusReady(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendDvbc2StatusReady *pStatusReady
    );
NEXUS_Error NEXUS_Frontend_GetDvbc2AsyncStatus(
     NEXUS_FrontendHandle handle,
     NEXUS_FrontendDvbc2StatusType type,
     NEXUS_FrontendDvbc2Status *pStatus
     );
NEXUS_Error NEXUS_Frontend_GetDvbc2AsyncFecStatistics(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendDvbc2StatusType type,
    NEXUS_FrontendDvbc2FecStatistics *pStatistics
    );
NEXUS_Error NEXUS_Frontend_GetDvbc2AsyncL1Part2Status(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendDvbc2L1Part2Status *pStatus
    );
NEXUS_Error NEXUS_Frontend_GetDvbc2AsyncL1DsliceStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendDvbc2L1DsliceStatus *pStatus
    );
NEXUS_Error NEXUS_Frontend_GetDvbc2AsyncL1NotchStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendDvbc2L1NotchStatus *pStatus
    );
NEXUS_Error NEXUS_Frontend_GetDvbc2AsyncL1PlpStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendDvbc2L1PlpStatus *pStatus
    );
NEXUS_Error NEXUS_Frontend_GetDvbc2AsyncBasicStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendDvbc2BasicStatus *pStatus
    );
typedef struct NEXUS_FrontendDvbtTpsStatus
{
    NEXUS_FrontendOfdmModulation modulation;
    NEXUS_FrontendOfdmTransmissionMode transmissionMode;
    NEXUS_FrontendOfdmGuardInterval guardInterval;
    NEXUS_FrontendOfdmCodeRate codeRate;
    NEXUS_FrontendOfdmHierarchy hierarchy;
    unsigned cellId;
    _Bool inDepthSymbolInterleave;
    _Bool timeSlicing;
    _Bool mpeFec;
} NEXUS_FrontendDvbtTpsStatus;
typedef struct NEXUS_FrontendDvbtBasicStatus
{
    NEXUS_FrontendOfdmSettings settings;
    _Bool fecLock;
    _Bool spectrumInverted;
    int snr;
    int gainOffset;
    int carrierOffset;
    int timingOffset;
    int signalStrength;
    unsigned signalLevelPercent;
    unsigned signalQualityPercent;
    unsigned reacquireCount;
    NEXUS_FrontendDvbtTpsStatus tps;
    NEXUS_FrontendBlockCounts fecBlockCounts;
    NEXUS_FrontendErrorRate viterbiErrorRate;
} NEXUS_FrontendDvbtBasicStatus;
typedef enum NEXUS_FrontendDvbtStatusType
{
  NEXUS_FrontendDvbtStatusType_eBasic,
  NEXUS_FrontendDvbtStatusType_eMax
} NEXUS_FrontendDvbtStatusType;
typedef struct NEXUS_FrontendDvbtStatusReady
{
    _Bool type[NEXUS_FrontendDvbtStatusType_eMax];
} NEXUS_FrontendDvbtStatusReady;
typedef struct NEXUS_FrontendDvbtStatus
{
    NEXUS_FrontendDvbtStatusType type;
    struct
    {
        NEXUS_FrontendDvbtBasicStatus basic;
    } status;
} NEXUS_FrontendDvbtStatus;
NEXUS_Error NEXUS_Frontend_RequestDvbtAsyncStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendDvbtStatusType type
    );
NEXUS_Error NEXUS_Frontend_GetDvbtAsyncStatusReady(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendDvbtStatusReady *pStatusReady
    );
NEXUS_Error NEXUS_Frontend_GetDvbtAsyncStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendDvbtStatusType type,
    NEXUS_FrontendDvbtStatus *pStatus
    );
typedef struct NEXUS_FrontendIsdbtTmccStatus
{
    NEXUS_FrontendOfdmTransmissionMode transmissionMode;
    NEXUS_FrontendOfdmGuardInterval guardInterval;
    _Bool ews;
    _Bool partialReception;
} NEXUS_FrontendIsdbtTmccStatus;
typedef struct NEXUS_FrontendIsdbtLayerStatus
{
    NEXUS_FrontendOfdmModulation modulation;
    NEXUS_FrontendOfdmCodeRate codeRate;
    NEXUS_FrontendOfdmTimeInterleaving timeInterleaving;
    unsigned numSegments;
    unsigned signalLevelPercent;
    unsigned signalQualityPercent;
    NEXUS_FrontendBlockCounts fecBlockCounts;
    NEXUS_FrontendErrorRate viterbiErrorRate;
    struct {
        _Bool locked;
        NEXUS_FrontendErrorRate errorRate;
    } bert;
}NEXUS_FrontendIsdbtLayerStatus;
typedef struct NEXUS_FrontendIsdbtBasicStatus
{
    NEXUS_FrontendOfdmSettings settings;
    _Bool fecLock;
    _Bool spectrumInverted;
    int snr;
    int gainOffset;
    int carrierOffset;
    int timingOffset;
    int signalStrength;
    unsigned reacquireCount;
    NEXUS_FrontendIsdbtTmccStatus tmcc;
    NEXUS_FrontendIsdbtLayerStatus layerA;
    NEXUS_FrontendIsdbtLayerStatus layerB;
    NEXUS_FrontendIsdbtLayerStatus layerC;
} NEXUS_FrontendIsdbtBasicStatus;
typedef enum NEXUS_FrontendIsdbtStatusType
{
  NEXUS_FrontendIsdbtStatusType_eBasic,
  NEXUS_FrontendIsdbtStatusType_eMax
} NEXUS_FrontendIsdbtStatusType;
typedef struct NEXUS_FrontendIsdbtStatusReady
{
    _Bool type[NEXUS_FrontendIsdbtStatusType_eMax];
} NEXUS_FrontendIsdbtStatusReady;
typedef struct NEXUS_FrontendIsdbtStatus
{
    NEXUS_FrontendIsdbtStatusType type;
    struct
    {
        NEXUS_FrontendIsdbtBasicStatus basic;
    } status;
} NEXUS_FrontendIsdbtStatus;
NEXUS_Error NEXUS_Frontend_RequestIsdbtAsyncStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendIsdbtStatusType type
    );
NEXUS_Error NEXUS_Frontend_GetIsdbtAsyncStatusReady(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendIsdbtStatusReady *pStatusReady
    );
NEXUS_Error NEXUS_Frontend_GetIsdbtAsyncStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendIsdbtStatusType type,
    NEXUS_FrontendIsdbtStatus *pStatus
    );
typedef struct NEXUS_Spi *NEXUS_SpiHandle;
typedef struct NEXUS_SpiSettings
{
    uint32_t baud;
    uint8_t bitsPerTransfer;
    _Bool lastByteContinueEnable;
    _Bool useUserDtlAndDsclk;
    _Bool interruptMode;
    unsigned ebiChipSelect;
    _Bool clockActiveLow;
    _Bool txLeadingCapFalling;
    uint8_t dtl;
    uint8_t rdsclk;
 unsigned delayAfterTransfer;
 unsigned delayChipSelectToClock;
} NEXUS_SpiSettings;
void NEXUS_Spi_GetDefaultSettings(
    NEXUS_SpiSettings *pSettings
    );
typedef enum NEXUS_SpiCore
{
    NEXUS_SpiCore_eUpg = 0,
    NEXUS_SpiCore_eMax
} NEXUS_SpiCore;
NEXUS_SpiHandle NEXUS_Spi_Open(
    unsigned index,
    const NEXUS_SpiSettings *pSettings
    );
void NEXUS_Spi_Close(
    NEXUS_SpiHandle handle
    );
NEXUS_Error NEXUS_Spi_SetSettings(
    NEXUS_SpiHandle handle,
    const NEXUS_SpiSettings *pSettings
    );
void NEXUS_Spi_GetSettings(
    NEXUS_SpiHandle handle,
    NEXUS_SpiSettings *pSettings
    );
NEXUS_Error NEXUS_Spi_Write(
    NEXUS_SpiHandle handle,
    const uint8_t *pWriteData,
    size_t length
    );
NEXUS_Error NEXUS_Spi_Read(
    NEXUS_SpiHandle handle,
    const uint8_t *pWriteData,
    uint8_t *pReadData,
    size_t length
    );
NEXUS_Error NEXUS_Spi_ReadAll(
    NEXUS_SpiHandle handle,
    const uint8_t *pWriteData,
    size_t writeLength,
    uint8_t *pReadData,
    size_t readLength,
    size_t *pActualReadLength
    );
typedef enum NEXUS_FrontendInterruptMode
{
    NEXUS_FrontendInterruptMode_eInterrupt,
    NEXUS_FrontendInterruptMode_ePolling,
    NEXUS_FrontendInterruptMode_eMax
} NEXUS_FrontendInterruptMode;
typedef struct NEXUS_FrontendTemperature
{
    unsigned temperature;
} NEXUS_FrontendTemperature;
typedef struct NEXUS_FrontendCapabilities
{
    _Bool powerDownSupported;
    _Bool analog;
    _Bool ifd;
    _Bool ifdac;
    _Bool qam;
    _Bool docsis;
    _Bool vsb;
    _Bool satellite;
    _Bool outOfBand;
    _Bool upstream;
    _Bool ofdm;
    _Bool scan;
    _Bool qamModes[NEXUS_FrontendQamMode_eMax];
    _Bool vsbModes[NEXUS_FrontendVsbMode_eMax];
    _Bool satelliteModes[NEXUS_FrontendSatelliteMode_eMax];
    _Bool outOfBandModes[NEXUS_FrontendOutOfBandMode_eMax];
    _Bool upstreamModes[NEXUS_FrontendUpstreamMode_eMax];
    _Bool ofdmModes[NEXUS_FrontendOfdmMode_eMax];
    _Bool diseqc;
} NEXUS_FrontendCapabilities;
void NEXUS_Frontend_GetCapabilities(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendCapabilities *pCapabilities
    );
typedef struct NEXUS_FrontendSoftDecision
{
    int16_t i;
    int16_t q;
} NEXUS_FrontendSoftDecision;
NEXUS_Error NEXUS_Frontend_GetSoftDecisions(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendSoftDecision *pDecisions,
    size_t length
    );
NEXUS_Error NEXUS_Frontend_ReadSoftDecisions(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendSoftDecision *pDecisions,
    size_t length,
    size_t *pNumRead
    );
typedef struct NEXUS_FrontendUserParameters
{
    int param1;
    unsigned pParam2;
    unsigned id;
    uint16_t chipId;
    uint16_t chipRevision;
    _Bool isMtsif;
} NEXUS_FrontendUserParameters;
NEXUS_Error NEXUS_Frontend_GetUserParameters(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendUserParameters *pParams
    );
NEXUS_Error NEXUS_Frontend_SetUserParameters(
    NEXUS_FrontendHandle handle,
    const NEXUS_FrontendUserParameters *pParams
    );
typedef struct NEXUS_FrontendVersion
{
    unsigned major;
    unsigned minor;
    unsigned buildType;
    unsigned buildId;
} NEXUS_FrontendVersion;
typedef struct NEXUS_FrontendChipType
{
    unsigned familyId;
    unsigned id;
    NEXUS_FrontendVersion version;
    unsigned bondoutOptions[2];
} NEXUS_FrontendChipType;
typedef struct NEXUS_FrontendType
{
    NEXUS_FrontendChipType chip;
    NEXUS_FrontendVersion firmwareVersion;
} NEXUS_FrontendType;
void NEXUS_Frontend_GetType(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendType *pType
    );
NEXUS_FrontendHandle NEXUS_Frontend_OpenStub(
    unsigned index
    );
void NEXUS_Frontend_Close(
    NEXUS_FrontendHandle handle
    );
void NEXUS_Frontend_Untune(
    NEXUS_FrontendHandle handle
    );
void NEXUS_Frontend_ResetStatus(
    NEXUS_FrontendHandle handle
    );
typedef enum NEXUS_FrontendLockStatus
{
    NEXUS_FrontendLockStatus_eUnknown,
    NEXUS_FrontendLockStatus_eUnlocked,
    NEXUS_FrontendLockStatus_eLocked,
    NEXUS_FrontendLockStatus_eNoSignal,
    NEXUS_FrontendLockStatus_eMax
} NEXUS_FrontendLockStatus;
typedef struct NEXUS_FrontendFastStatus {
    NEXUS_FrontendLockStatus lockStatus;
    _Bool acquireInProgress;
} NEXUS_FrontendFastStatus;
NEXUS_Error NEXUS_Frontend_GetFastStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendFastStatus *pStatus
    );
NEXUS_Error NEXUS_Frontend_ReapplyTransportSettings(
    NEXUS_FrontendHandle handle
    );
typedef struct NEXUS_FrontendSpectrumSettings
{
    void *data;
    unsigned dataLength;
    unsigned startFrequency;
    unsigned stopFrequency;
    unsigned binAverage;
    unsigned numSamples;
    unsigned fftSize;
    NEXUS_CallbackDesc dataReadyCallback;
} NEXUS_FrontendSpectrumSettings;
void NEXUS_Frontend_GetDefaultSpectrumSettings(
    NEXUS_FrontendSpectrumSettings *pSettings
    );
NEXUS_Error NEXUS_Frontend_RequestSpectrumData(
    NEXUS_FrontendHandle handle,
    const NEXUS_FrontendSpectrumSettings *pSettings
    );
NEXUS_Error NEXUS_Frontend_WriteRegister(
    NEXUS_FrontendHandle handle,
    unsigned address,
    uint32_t value
    );
NEXUS_Error NEXUS_Frontend_ReadRegister(
    NEXUS_FrontendHandle handle,
    unsigned address,
    uint32_t *pValue
    );
typedef enum NEXUS_FrontendAcquireMode
{
    NEXUS_FrontendAcquireMode_eByCapabilities,
    NEXUS_FrontendAcquireMode_eByIndex,
    NEXUS_FrontendAcquireMode_eMax
} NEXUS_FrontendAcquireMode;
typedef struct NEXUS_FrontendAcquireSettings
{
    NEXUS_FrontendAcquireMode mode;
    struct {
        _Bool qam;
        _Bool vsb;
        _Bool ofdm;
        _Bool satellite;
        _Bool outOfBand;
        _Bool ifd;
    } capabilities;
    unsigned index;
} NEXUS_FrontendAcquireSettings;
void NEXUS_Frontend_GetDefaultAcquireSettings(
    NEXUS_FrontendAcquireSettings *pSettings
    );
NEXUS_FrontendHandle NEXUS_Frontend_Acquire(
    const NEXUS_FrontendAcquireSettings *pSettings
    );
void NEXUS_Frontend_Release(
    NEXUS_FrontendHandle handle
    );
NEXUS_Error NEXUS_Frontend_GetTemperature(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendTemperature *pTemp
    );
typedef enum NEXUS_FrontendDebugPacketType {
    NEXUS_FrontendDebugPacketType_eOob,
    NEXUS_FrontendDebugPacketType_eMax
} NEXUS_FrontendDebugPacketType;
NEXUS_Error NEXUS_Frontend_TransmitDebugPacket(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendDebugPacketType type,
    const uint8_t *pBuffer,
    size_t size
    );
typedef struct NEXUS_FrontendBertStatus {
    _Bool enabled;
    _Bool locked;
    _Bool syncAcquired;
    _Bool syncLost;
    uint64_t bitCount;
    uint64_t errorCount;
} NEXUS_FrontendBertStatus;
NEXUS_Error NEXUS_Frontend_GetBertStatus(
    NEXUS_FrontendHandle handle,
    NEXUS_FrontendBertStatus *pStatus
    );
NEXUS_FrontendConnectorHandle NEXUS_Frontend_GetConnector(
    NEXUS_FrontendHandle frontend
    );
void NEXUS_FrontendDevice_Close(
    NEXUS_FrontendDeviceHandle handle
    );
typedef enum NEXUS_FrontendDeviceRfInput
{
    NEXUS_FrontendDeviceRfInput_eOff,
    NEXUS_FrontendDeviceRfInput_eDaisy,
    NEXUS_FrontendDeviceRfInput_eLoopThrough,
    NEXUS_FrontendDeviceRfInput_eMax
} NEXUS_FrontendDeviceRfInput;
typedef enum NEXUS_FrontendDeviceMtsifOutput
{
    NEXUS_FrontendDeviceMtsifOutput_eDefault,
    NEXUS_FrontendDeviceMtsifOutput_eDaisy,
    NEXUS_FrontendDeviceMtsifOutput_eMax
} NEXUS_FrontendDeviceMtsifOutput;
typedef struct NEXUS_FrontendDeviceLinkSettings
{
    NEXUS_FrontendDeviceRfInput rfInput;
    NEXUS_FrontendDeviceMtsifOutput mtsif;
} NEXUS_FrontendDeviceLinkSettings;
void NEXUS_FrontendDevice_GetDefaultLinkSettings(
    NEXUS_FrontendDeviceLinkSettings *pSettings
    );
NEXUS_Error NEXUS_FrontendDevice_Link(
    NEXUS_FrontendDeviceHandle parentHandle,
    NEXUS_FrontendDeviceHandle childHandle,
    const NEXUS_FrontendDeviceLinkSettings *pSettings
    );
void NEXUS_FrontendDevice_Unlink(
    NEXUS_FrontendDeviceHandle parentHandle,
    NEXUS_FrontendDeviceHandle childHandle
    );
NEXUS_FrontendDeviceHandle NEXUS_Frontend_GetDevice(
    NEXUS_FrontendHandle handle
    );
NEXUS_Error NEXUS_FrontendDevice_LinkAmplifier(
    NEXUS_FrontendDeviceHandle handle,
    NEXUS_AmplifierHandle amplifierHandle
    );
typedef struct NEXUS_FrontendDeviceStatus
{
    struct {
        _Bool enabled;
        unsigned voltage;
    } avs;
    int temperature;
    _Bool openPending;
    _Bool openFailed;
} NEXUS_FrontendDeviceStatus;
NEXUS_Error NEXUS_FrontendDevice_GetStatus(
    NEXUS_FrontendDeviceHandle handle,
    NEXUS_FrontendDeviceStatus *pStatus
    );
typedef struct NEXUS_FrontendDeviceRecalibrateSettings
{
    struct {
        _Bool enabled;
        signed threshold;
        unsigned thresholdHysteresis;
        NEXUS_CallbackDesc powerLevelChange;
        NEXUS_CallbackDesc calibrationComplete;
    } cppm;
} NEXUS_FrontendDeviceRecalibrateSettings;
void NEXUS_FrontendDevice_GetDefaultRecalibrateSettings(
    NEXUS_FrontendDeviceRecalibrateSettings *pSettings
    );
NEXUS_Error NEXUS_FrontendDevice_Recalibrate(
    NEXUS_FrontendDeviceHandle handle,
    const NEXUS_FrontendDeviceRecalibrateSettings *pSettings
    );
void NEXUS_FrontendDevice_GetTunerCapabilities(
    NEXUS_FrontendDeviceHandle handle,
    unsigned tunerIndex,
    NEXUS_FrontendCapabilities *pCapabilities
    );
typedef struct NEXUS_FrontendDeviceCapabilities
{
    unsigned numTuners;
} NEXUS_FrontendDeviceCapabilities;
void NEXUS_FrontendDevice_GetCapabilities(
    NEXUS_FrontendDeviceHandle handle,
    NEXUS_FrontendDeviceCapabilities *pCapabilities
    );
typedef struct NEXUS_FrontendDeviceMtsifSettings {
    _Bool enabled;
    unsigned clockRate;
    unsigned driveStrength;
} NEXUS_FrontendDeviceMtsifSettings;
NEXUS_Error NEXUS_Frontend_GetInputBandStatus(
    NEXUS_FrontendHandle frontend,
    NEXUS_InputBandStatus *pStatus
    );
typedef enum NEXUS_FrontendChannelType
{
    NEXUS_FrontendChannelType_eCable,
    NEXUS_FrontendChannelType_eCableOutOfBand,
    NEXUS_FrontendChannelType_eTerrestrial,
    NEXUS_FrontendChannelType_eSatellite,
    NEXUS_FrontendChannelType_eMax
} NEXUS_FrontendChannelType;
typedef enum NEXUS_FrontendOutOfBandInput
{
    NEXUS_OutOfBandInput_eNarrowBandAtoD,
    NEXUS_OutOfBandInput_eWideBandAtoD,
    NEXUS_OutOfBandInput_eBandPassFilteredNarrowBandAtoD,
    NEXUS_OutOfBandInput_eMax
} NEXUS_FrontendOutOfBandInput;
typedef struct NEXUS_FrontendCableConfiguration
{
    _Bool enabled;
    struct {
        unsigned ifFrequency;
        NEXUS_FrontendOutOfBandInput useWidebandAtoD;
        NEXUS_FrontendOutOfBandNyquistFilter nyquist;
    } outOfBand;
    struct {
        _Bool enabled;
        unsigned data[4];
    } pinmux;
} NEXUS_FrontendCableConfiguration;
typedef struct NEXUS_FrontendTerrestrialConfiguration
{
    _Bool enabled;
} NEXUS_FrontendTerrestrialConfiguration;
typedef struct NEXUS_FrontendSatelliteConfiguration
{
    _Bool enabled;
    struct {
        uint16_t i2cAddress;
        NEXUS_I2cHandle i2cDevice;
    } diseqc;
} NEXUS_FrontendSatelliteConfiguration;
typedef struct NEXUS_FrontendDeviceReset{
    _Bool enable;
    unsigned type;
    unsigned pin;
    NEXUS_GpioValue value;
} NEXUS_FrontendDeviceReset;
typedef struct NEXUS_FrontendDeviceOpenSettings
{
    NEXUS_FrontendDeviceReset reset;
    NEXUS_FrontendInterruptMode interruptMode;
    NEXUS_GpioHandle gpioInterrupt;
    unsigned isrNumber;
    NEXUS_I2cHandle i2cDevice;
    uint16_t i2cAddress;
    uint8_t i2cSlaveAddress;
    NEXUS_SpiHandle spiDevice;
    _Bool loadAP;
    _Bool configureWatchdog;
    struct {
        int bypassable;
        int total;
    } externalFixedGain;
    struct {
        _Bool enableDaisyChain;
    } crystalSettings;
    NEXUS_FrontendDeviceMtsifSettings mtsif[4];
    NEXUS_CallbackDesc updateGainCallback;
    NEXUS_FrontendCableConfiguration cable;
    NEXUS_FrontendTerrestrialConfiguration terrestrial;
    NEXUS_FrontendSatelliteConfiguration satellite;
} NEXUS_FrontendDeviceOpenSettings;
void NEXUS_FrontendDevice_GetDefaultOpenSettings(
    NEXUS_FrontendDeviceOpenSettings *pSettings
    );
NEXUS_FrontendDeviceHandle NEXUS_FrontendDevice_Open(
    unsigned index,
    const NEXUS_FrontendDeviceOpenSettings *pSettings
    );
typedef enum NEXUS_TunerRfInput
{
    NEXUS_TunerRfInput_eOff,
    NEXUS_TunerRfInput_eExternalLna,
    NEXUS_TunerRfInput_eInternalLna,
    NEXUS_TunerRfInput_eStandardIf,
    NEXUS_TunerRfInput_eLowIf,
    NEXUS_TunerRfInput_eBaseband,
    NEXUS_TunerRfInput_eMax
} NEXUS_TunerRfInput;
typedef enum NEXUS_RfDaisyChain
{
    NEXUS_RfDaisyChain_eOff,
    NEXUS_RfDaisyChain_eExternalLna,
    NEXUS_RfDaisyChain_eInternalLna,
    NEXUS_RfDaisyChain_eMax
} NEXUS_RfDaisyChain;
typedef struct NEXUS_FrontendDeviceCableSettings
{
    struct {
        NEXUS_FrontendOutOfBandOutputMode outputMode;
    } outOfBand;
} NEXUS_FrontendDeviceCableSettings;
typedef struct NEXUS_FrontendDeviceTerrestrialSettings
{
    _Bool dummy;
} NEXUS_FrontendDeviceTerrestrialSettings;
typedef enum NEXUS_FrontendLoopthroughGain {
    NEXUS_FrontendLoopthroughGain_eLow,
    NEXUS_FrontendLoopthroughGain_eHigh,
    NEXUS_FrontendLoopthroughGain_eMax
} NEXUS_FrontendLoopthroughGain;
typedef struct NEXUS_FrontendDeviceSettings
{
    NEXUS_TunerRfInput rfInput;
    NEXUS_RfDaisyChain rfDaisyChain;
    _Bool enableRfLoopThrough;
    NEXUS_FrontendLoopthroughGain loopthroughGain;
    NEXUS_FrontendDeviceCableSettings cable;
} NEXUS_FrontendDeviceSettings;
void NEXUS_FrontendDevice_GetDefaultSettings(
    NEXUS_FrontendDeviceSettings *pSettings
    );
NEXUS_Error NEXUS_FrontendDevice_GetSettings(
    NEXUS_FrontendDeviceHandle handle,
    NEXUS_FrontendDeviceSettings *pSettings
    );
NEXUS_Error NEXUS_FrontendDevice_SetSettings(
    NEXUS_FrontendDeviceHandle handle,
    const NEXUS_FrontendDeviceSettings *pSettings
    );
typedef struct NEXUS_FrontendChannelSettings
{
    NEXUS_FrontendDeviceHandle device;
    NEXUS_FrontendChannelType type;
    unsigned channelNumber;
} NEXUS_FrontendChannelSettings;
void NEXUS_Frontend_GetDefaultOpenSettings(
    NEXUS_FrontendChannelSettings *pSettings
    );
NEXUS_FrontendHandle NEXUS_Frontend_Open(
    const NEXUS_FrontendChannelSettings *pSettings
    );
typedef struct NEXUS_FrontendProbeResults
{
    NEXUS_FrontendChipType chip;
} NEXUS_FrontendProbeResults;
NEXUS_Error NEXUS_FrontendDevice_Probe(
    const NEXUS_FrontendDeviceOpenSettings *pSettings,
    NEXUS_FrontendProbeResults *pResults
    );
typedef enum NEXUS_FrontendDeviceAmplifierState
{
    NEXUS_FrontendDeviceAmplifierState_eBypass,
    NEXUS_FrontendDeviceAmplifierState_eEnabled,
    NEXUS_FrontendDeviceAmplifierState_eMax
} NEXUS_FrontendDeviceAmplifierState;
typedef struct NEXUS_FrontendDeviceAmplifierStatus {
    NEXUS_FrontendDeviceAmplifierState externalFixedGain;
} NEXUS_FrontendDeviceAmplifierStatus;
NEXUS_Error NEXUS_FrontendDevice_GetAmplifierStatus(
    NEXUS_FrontendDeviceHandle handle,
    NEXUS_FrontendDeviceAmplifierStatus *pStatus
    );
typedef enum NEXUS_WakeupPacketType {
    NEXUS_WakeupPacketType_eIgnoreByte,
    NEXUS_WakeupPacketType_eCompareByte,
    NEXUS_WakeupPacketType_eCompareSeries2,
    NEXUS_WakeupPacketType_eCompareSeries3,
    NEXUS_WakeupPacketType_eMax
} NEXUS_WakeupPacketType;
typedef struct NEXUS_TransportWakeupFilter
{
    uint8_t comparePattern;
    uint8_t compareMask;
    NEXUS_WakeupPacketType maskType;
} NEXUS_TransportWakeupFilter;
typedef struct NEXUS_TransportWakeupSettings {
    NEXUS_InputBand inputBand;
    _Bool errorIgnore;
    unsigned packetLength;
    struct {
        NEXUS_TransportWakeupFilter packet[200];
    } filter[4];
    _Bool enabled;
} NEXUS_TransportWakeupSettings;
void NEXUS_TransportWakeup_GetSettings(
    NEXUS_TransportWakeupSettings *pSettings
    );
NEXUS_Error NEXUS_TransportWakeup_SetSettings(
    const NEXUS_TransportWakeupSettings *pSettings
    );
void NEXUS_FrontendDevice_GetWakeupSettings(
    NEXUS_FrontendDeviceHandle handle,
    NEXUS_TransportWakeupSettings *pSettings
    );
NEXUS_Error NEXUS_FrontendDevice_SetWakeupSettings(
    NEXUS_FrontendDeviceHandle handle,
    const NEXUS_TransportWakeupSettings *pSettings
    );
typedef struct NEXUS_3128Device *NEXUS_3128DeviceHandle;
typedef enum NEXUS_3128ChannelType
{
    NEXUS_3128ChannelType_eInBand,
    NEXUS_3128ChannelType_eOutOfBand,
    NEXUS_3128ChannelType_eUpstream,
    NEXUS_3128ChannelType_eMax
} NEXUS_3128ChannelType;
typedef enum NEXUS_3128OutOfBandInput
{
    NEXUS_3128OutOfBandInput_eNarrowBandAtoD,
    NEXUS_3128OutOfBandInput_eWideBandAtoD,
    NEXUS_3128OutOfBandInput_eBandPassFilteredNarrowBandAtoD,
    NEXUS_3128OutOfBandInput_eMax
} NEXUS_3128OutOfBandInput;
typedef struct NEXUS_FrontendDevice3128OpenSettings
{
    NEXUS_FrontendInterruptMode interruptMode;
    NEXUS_GpioHandle gpioInterrupt;
    unsigned isrNumber;
    NEXUS_I2cHandle i2cDevice;
    uint16_t i2cAddr;
    uint8_t i2cSlaveAddr;
    NEXUS_SpiHandle spiDevice;
    uint16_t spiAddr;
    _Bool configureWatchdog;
    _Bool inBandOpenDrain;
    _Bool loadAP;
    _Bool isMtsif;
    struct {
        unsigned ifFrequency;
        _Bool openDrain;
        NEXUS_3128OutOfBandInput useWidebandAtoD;
        NEXUS_FrontendOutOfBandNyquistFilter nyquist;
    }outOfBand;
    struct {
        int bypassable;
        int total;
    } externalFixedGain;
    struct {
        _Bool enableDaisyChain;
    } crystalSettings;
    struct {
        _Bool enabled;
        unsigned data[4];
    } pinmux;
} NEXUS_FrontendDevice3128OpenSettings;
typedef struct NEXUS_Frontend3128Settings
{
    NEXUS_FrontendDeviceHandle device;
    NEXUS_3128ChannelType type;
    unsigned channelNumber;
    NEXUS_GpioHandle gpioInterrupt;
    unsigned isrNumber;
    NEXUS_I2cHandle i2cDevice;
    uint16_t i2cAddr;
    uint8_t i2cSlaveAddr;
    NEXUS_SpiHandle spiDevice;
    uint16_t spiAddr;
    _Bool configureWatchdog;
    _Bool inBandOpenDrain;
    _Bool loadAP;
    _Bool isMtsif;
    unsigned ifFrequency;
    struct {
        _Bool openDrain;
        _Bool useWidebandAtoD;
        NEXUS_FrontendOutOfBandNyquistFilter nyquist;
    }outOfBand;
} NEXUS_Frontend3128Settings;
typedef struct NEXUS_FrontendDevice3128Settings
{
    uint32_t agcValue;
    NEXUS_CallbackDesc updateGainCallback;
    _Bool enableRfLoopThrough;
    struct {
        NEXUS_FrontendOutOfBandOutputMode outputMode;
    } outOfBand;
} NEXUS_FrontendDevice3128Settings;
void NEXUS_Frontend_GetDefault3128Settings(
    NEXUS_Frontend3128Settings *pSettings
    );
NEXUS_FrontendHandle NEXUS_Frontend_Open3128(
    const NEXUS_Frontend3128Settings *pSettings
    );
void NEXUS_FrontendDevice_GetDefault3128Settings(
    NEXUS_FrontendDevice3128Settings *pConfigSettings
    );
NEXUS_Error NEXUS_FrontendDevice_Get3128Settings(
    NEXUS_FrontendDeviceHandle handle,
    NEXUS_FrontendDevice3128Settings *pConfigSettings
    );
NEXUS_Error NEXUS_FrontendDevice_Set3128Settings(
    NEXUS_FrontendDeviceHandle handle,
    const NEXUS_FrontendDevice3128Settings *pConfigSettings
    );
void NEXUS_FrontendDevice_GetDefault3128OpenSettings(
    NEXUS_FrontendDevice3128OpenSettings *pSettings
    );
NEXUS_FrontendDeviceHandle NEXUS_FrontendDevice_Open3128(
    unsigned index,
    const NEXUS_FrontendDevice3128OpenSettings *pSettings
    );
typedef NEXUS_Frontend3128Settings NEXUS_3128Settings;
typedef NEXUS_FrontendDevice3128Settings NEXUS_3128ConfigSettings;
typedef struct NEXUS_3128ProbeResults
{
    NEXUS_FrontendChipType chip;
} NEXUS_3128ProbeResults;
NEXUS_Error NEXUS_Frontend_Probe3128(
    const NEXUS_FrontendDevice3128OpenSettings *pSettings,
    NEXUS_3128ProbeResults *pResults
    );
typedef struct NEXUS_TunerOpen3128Settings
{
    NEXUS_FrontendDeviceHandle device;
} NEXUS_TunerOpen3128Settings;
void NEXUS_Tuner_GetDefaultOpen3128Settings(
    NEXUS_TunerOpen3128Settings *pSettings
    );
NEXUS_TunerHandle NEXUS_Tuner_Open3128(
    unsigned index,
    const NEXUS_TunerOpen3128Settings *pSettings
    );
typedef struct NEXUS_45216Device *NEXUS_45216DeviceHandle;
typedef struct NEXUS_FrontendDevice45216OpenSettings
{
    NEXUS_FrontendDeviceReset reset;
    NEXUS_GpioHandle gpioInterrupt;
    unsigned isrNumber;
    NEXUS_I2cHandle i2cDevice;
    uint16_t i2cAddr;
    uint8_t i2cSlaveAddr;
    NEXUS_SpiHandle spiDevice;
    uint16_t spiAddr;
    NEXUS_FrontendDeviceMtsifSettings mtsif[4];
    struct {
        uint16_t i2cAddr;
        NEXUS_I2cHandle i2cDevice;
    } diseqc;
} NEXUS_FrontendDevice45216OpenSettings;
void NEXUS_FrontendDevice_GetDefault45216OpenSettings(
    NEXUS_FrontendDevice45216OpenSettings *pSettings
    );
NEXUS_FrontendDeviceHandle NEXUS_FrontendDevice_Open45216(
    unsigned index,
    const NEXUS_FrontendDevice45216OpenSettings *pSettings
    );
typedef struct NEXUS_45216FrontendSettings
{
    NEXUS_FrontendDeviceHandle device;
    unsigned channelNumber;
} NEXUS_45216FrontendSettings;
void NEXUS_Frontend_GetDefault45216Settings(
    NEXUS_45216FrontendSettings *pSettings
    );
NEXUS_FrontendHandle NEXUS_Frontend_Open45216(
    const NEXUS_45216FrontendSettings *pSettings
    );
typedef struct NEXUS_45216ProbeResults
{
    NEXUS_FrontendChipType chip;
} NEXUS_45216ProbeResults;
NEXUS_Error NEXUS_Frontend_Probe45216(
    const NEXUS_FrontendDevice45216OpenSettings *pSettings,
    NEXUS_45216ProbeResults *pResults
    );
typedef struct NEXUS_FrontendStartBondingGroupSettings
{
    NEXUS_FrontendHandle slave[32];
} NEXUS_FrontendStartBondingGroupSettings;
void NEXUS_Frontend_GetDefaultStartBondingGroupSettings(
    NEXUS_FrontendStartBondingGroupSettings *pSettings
    );
NEXUS_Error NEXUS_Frontend_StartBondingGroup(
    NEXUS_FrontendHandle master,
    const NEXUS_FrontendStartBondingGroupSettings *pSettings
    );
void NEXUS_Frontend_StopBondingGroup(
    NEXUS_FrontendHandle master
    );
typedef struct NEXUS_FrontendBondingGroupStatus
{
    _Bool locked;
} NEXUS_FrontendBondingGroupStatus;
NEXUS_Error NEXUS_Frontend_GetBondingGroupStatus(
    NEXUS_FrontendHandle master,
    NEXUS_FrontendBondingGroupStatus *pStatus
    );
typedef struct NEXUS_FrontendModuleSettings
{
    NEXUS_CommonModuleSettings common;
    NEXUS_ModuleHandle i2cModule;
    NEXUS_ModuleHandle transport;
} NEXUS_FrontendModuleSettings;
void NEXUS_FrontendModule_GetDefaultSettings(
    NEXUS_FrontendModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_FrontendModule_Init(
    const NEXUS_FrontendModuleSettings *pSettings
    );
void NEXUS_FrontendModule_Uninit(void);
typedef struct NEXUS_GpioModuleOsSharedBankCapabilities
{
    _Bool osManaged;
} NEXUS_GpioModuleOsSharedBankCapabilities;
typedef struct NEXUS_GpioModuleOsSharedBankInitSettings
{
    uint32_t bankBaseAddresses[8];
    _Bool aon[8];
} NEXUS_GpioModuleOsSharedBankInitSettings;
typedef struct NEXUS_GpioModuleOsSharedBankPinOpenSettings
{
    uint32_t bankBaseAddress;
    unsigned shift;
    NEXUS_GpioInterrupt interruptType;
} NEXUS_GpioModuleOsSharedBankPinOpenSettings;
typedef struct NEXUS_GpioModuleOsSharedBankInterruptStatus
{
    uint32_t status[8];
} NEXUS_GpioModuleOsSharedBankInterruptStatus;
typedef struct NEXUS_GpioModuleOsSharedBankPin * NEXUS_GpioModuleOsSharedBankPinHandle;
typedef struct
{
    NEXUS_Error (*init)(const NEXUS_GpioModuleOsSharedBankInitSettings * pSettings);
    void (*getCapabilities)(NEXUS_GpioModuleOsSharedBankCapabilities * caps);
    NEXUS_Error (*getInterruptStatus_isr)(NEXUS_GpioModuleOsSharedBankInterruptStatus * pStatus);
    NEXUS_GpioModuleOsSharedBankPinHandle (*openPin)(const NEXUS_GpioModuleOsSharedBankPinOpenSettings * pSettings);
    void (*closePin)(NEXUS_GpioModuleOsSharedBankPinHandle pin);
    NEXUS_Error (*clearPinInterrupt_isr)(NEXUS_GpioModuleOsSharedBankPinHandle pin);
    NEXUS_Error (*setPinInterruptMask_isr)(NEXUS_GpioModuleOsSharedBankPinHandle pin, _Bool disable);
    NEXUS_Error (*setStandby)(NEXUS_GpioModuleOsSharedBankPinHandle pin, _Bool enable);
} NEXUS_GpioModuleOsSharedBankSettings;
typedef struct NEXUS_GpioModuleSettings
{
    NEXUS_CommonModuleSettings common;
    NEXUS_GpioModuleOsSharedBankSettings osSharedBankSettings;
} NEXUS_GpioModuleSettings;
void NEXUS_GpioModule_GetDefaultSettings(
    NEXUS_GpioModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_GpioModule_Init(
    const NEXUS_GpioModuleSettings *pSettings
    );
void NEXUS_GpioModule_Uninit(void);
typedef struct NEXUS_Graphics2D *NEXUS_Graphics2DHandle;
typedef struct NEXUS_Graphics2DOpenSettings
{
    unsigned packetFifoSize;
    unsigned packetFifoThreshold;
    NEXUS_HeapHandle heap;
    NEXUS_HeapHandle boundsHeap;
    unsigned maxOperations;
    _Bool preAllocPacketMemory;
    _Bool compatibleWithSurfaceCompaction;
    _Bool secure;
} NEXUS_Graphics2DOpenSettings;
typedef enum NEXUS_ColorFormatType
{
    NEXUS_ColorFormatType_eSameAsSurface,
    NEXUS_ColorFormatType_eStandardFormat
} NEXUS_ColorFormatType;
typedef struct NEXUS_Graphics2DSettings
{
    NEXUS_ColorFormatType colorFormatType;
    _Bool blockedSync;
    _Bool pollingCheckpoint;
    unsigned completionTimeout;
    NEXUS_CallbackDesc checkpointCallback;
    NEXUS_CallbackDesc packetSpaceAvailable;
} NEXUS_Graphics2DSettings;
void NEXUS_Graphics2D_GetDefaultOpenSettings(
   NEXUS_Graphics2DOpenSettings *pSettings
   );
NEXUS_Graphics2DHandle NEXUS_Graphics2D_Open(
    unsigned index,
    const NEXUS_Graphics2DOpenSettings *pSettings
    );
void NEXUS_Graphics2D_Close(
    NEXUS_Graphics2DHandle handle
    );
void NEXUS_Graphics2D_GetSettings(
    NEXUS_Graphics2DHandle handle,
    NEXUS_Graphics2DSettings *pSettings
    );
NEXUS_Error NEXUS_Graphics2D_SetSettings(
    NEXUS_Graphics2DHandle handle,
    const NEXUS_Graphics2DSettings *pSettings
    );
typedef enum NEXUS_BlendFactor
{
    NEXUS_BlendFactor_eZero,
    NEXUS_BlendFactor_eHalf,
    NEXUS_BlendFactor_eOne,
    NEXUS_BlendFactor_eSourceColor,
    NEXUS_BlendFactor_eInverseSourceColor,
    NEXUS_BlendFactor_eSourceAlpha,
    NEXUS_BlendFactor_eInverseSourceAlpha,
    NEXUS_BlendFactor_eDestinationColor,
    NEXUS_BlendFactor_eInverseDestinationColor,
    NEXUS_BlendFactor_eDestinationAlpha,
    NEXUS_BlendFactor_eInverseDestinationAlpha,
    NEXUS_BlendFactor_eConstantColor,
    NEXUS_BlendFactor_eInverseConstantColor,
    NEXUS_BlendFactor_eConstantAlpha,
    NEXUS_BlendFactor_eInverseConstantAlpha,
    NEXUS_BlendFactor_eMax
} NEXUS_BlendFactor;
typedef struct NEXUS_BlendEquation
{
    NEXUS_BlendFactor a;
    NEXUS_BlendFactor b;
    _Bool subtract_cd;
    NEXUS_BlendFactor c;
    NEXUS_BlendFactor d;
    _Bool subtract_e;
    NEXUS_BlendFactor e;
} NEXUS_BlendEquation;
typedef enum NEXUS_FillOp
{
    NEXUS_FillOp_eIgnore = 0,
    NEXUS_FillOp_eCopy,
    NEXUS_FillOp_eBlend,
    NEXUS_FillOp_eUseBlendEquation,
    NEXUS_FillOp_eMax
} NEXUS_FillOp;
typedef struct NEXUS_Graphics2DFillSettings
{
    NEXUS_SurfaceHandle surface;
    NEXUS_Pixel color;
    NEXUS_Rect rect;
    NEXUS_FillOp colorOp;
    NEXUS_FillOp alphaOp;
    NEXUS_BlendEquation colorBlend;
    NEXUS_BlendEquation alphaBlend;
} NEXUS_Graphics2DFillSettings;
void NEXUS_Graphics2D_GetDefaultFillSettings(
    NEXUS_Graphics2DFillSettings *pSettings
    );
NEXUS_Error NEXUS_Graphics2D_Fill(
    NEXUS_Graphics2DHandle handle,
    const NEXUS_Graphics2DFillSettings *pSettings
    );
typedef enum NEXUS_BlitColorOp
{
    NEXUS_BlitColorOp_eCopySource = 0,
    NEXUS_BlitColorOp_eUseConstantAlpha,
    NEXUS_BlitColorOp_eUseSourceAlpha,
    NEXUS_BlitColorOp_eUseDestAlpha,
    NEXUS_BlitColorOp_eSelectPaletteWithColorkey,
    NEXUS_BlitColorOp_eAdd,
    NEXUS_BlitColorOp_eUseBlendEquation,
    NEXUS_BlitColorOp_eMax
} NEXUS_BlitColorOp;
typedef enum NEXUS_BlitAlphaOp
{
    NEXUS_BlitAlphaOp_eCopySource = 0,
    NEXUS_BlitAlphaOp_eCopyDest,
    NEXUS_BlitAlphaOp_eCopyConstant,
    NEXUS_BlitAlphaOp_eCombine,
    NEXUS_BlitAlphaOp_eEmulateTransparentVideo,
    NEXUS_BlitAlphaOp_eAdd,
    NEXUS_BlitAlphaOp_eUseBlendEquation,
    NEXUS_BlitAlphaOp_eMax
} NEXUS_BlitAlphaOp;
typedef enum NEXUS_Graphics2DFilterCoeffs
{
    NEXUS_Graphics2DFilterCoeffs_ePointSample,
    NEXUS_Graphics2DFilterCoeffs_eBilinear,
    NEXUS_Graphics2DFilterCoeffs_eAnisotropic,
    NEXUS_Graphics2DFilterCoeffs_eSharp,
    NEXUS_Graphics2DFilterCoeffs_eSharper,
    NEXUS_Graphics2DFilterCoeffs_eBlurry,
    NEXUS_Graphics2DFilterCoeffs_eAntiFlutter,
    NEXUS_Graphics2DFilterCoeffs_eAntiFlutterBlurry,
    NEXUS_Graphics2DFilterCoeffs_eAntiFlutterSharp,
    NEXUS_Graphics2DFilterCoeffs_eMax
} NEXUS_Graphics2DFilterCoeffs;
typedef struct NEXUS_Graphics2DColorMatrix
{
    unsigned shift;
    int32_t coeffMatrix[(20)];
} NEXUS_Graphics2DColorMatrix;
typedef struct NEXUS_Graphics2DPatternSettings
{
    uint8_t ropVector;
    uint8_t pattern[64];
    uint32_t backColor;
    uint32_t foreColor;
} NEXUS_Graphics2DPatternSettings;
typedef struct NEXUS_Graphics2DScalingControlSettings
{
    _Bool setFilterPhaseAdj;
    int32_t horizontalPhase;
    int32_t verticalPhase;
    uint32_t phaseFixedPointShift;
    _Bool setFixedScaleFactor;
    uint32_t horizontalNumerator;
    uint32_t horizontalDenominator;
    uint32_t verticalNumerator;
    uint32_t verticalDenominator;
} NEXUS_Graphics2DScalingControlSettings;
typedef struct NEXUS_Graphics2DColorKey
{
    _Bool enabled;
    NEXUS_Pixel lower;
    NEXUS_Pixel upper;
    NEXUS_Pixel mask;
    NEXUS_Pixel replace;
    NEXUS_Pixel replaceMask;
} NEXUS_Graphics2DColorKey;
typedef struct NEXUS_Graphics2DBlitSettings
{
    struct
    {
        NEXUS_SurfaceHandle surface;
        NEXUS_Rect rect;
    } source, dest, output;
    NEXUS_BlitColorOp colorOp;
    NEXUS_BlitAlphaOp alphaOp;
    NEXUS_BlendEquation colorBlend;
    NEXUS_BlendEquation alphaBlend;
    NEXUS_Pixel constantColor;
    _Bool useDestAndSourceConstantColor;
    NEXUS_Pixel destConstantColor;
    NEXUS_Pixel sourceConstantColor;
    struct {
        NEXUS_Graphics2DColorKey source, dest;
    } colorKey;
    BM2MC_PACKET_eFilterOrder sourceFilterOrder;
    _Bool conversionMatrixEnabled;
    NEXUS_Graphics2DColorMatrix conversionMatrix;
    _Bool patternSettingsEnabled;
    NEXUS_Graphics2DPatternSettings patternSettings;
    NEXUS_Graphics2DFilterCoeffs horizontalFilter;
    NEXUS_Graphics2DFilterCoeffs verticalFilter;
    _Bool scalingControlSettingsEnabled;
    NEXUS_Graphics2DScalingControlSettings scalingControlSettings;
    _Bool mirrorSourceVertically;
    _Bool mirrorSourceHorizontally;
    _Bool mirrorDestVertically;
    _Bool mirrorDestHorizontally;
    _Bool mirrorOutputVertically;
    _Bool mirrorOutputHorizontally;
    _Bool alphaPremultiplySourceEnabled;
    _Bool chromaFilter;
} NEXUS_Graphics2DBlitSettings;
typedef struct NEXUS_Graphics2DCapabilities {
    unsigned maxHorizontalDownScale;
    unsigned maxVerticalDownScale;
} NEXUS_Graphics2DCapabilities;
void NEXUS_Graphics2D_GetDefaultBlitSettings(
    NEXUS_Graphics2DBlitSettings *pSettings
    );
NEXUS_Error NEXUS_Graphics2D_Blit(
    NEXUS_Graphics2DHandle handle,
    const NEXUS_Graphics2DBlitSettings *pSettings
    );
NEXUS_Error NEXUS_Graphics2D_FastBlit(
    NEXUS_Graphics2DHandle handle,
    NEXUS_SurfaceHandle outputSurface,
    const NEXUS_Rect *pOutputRect,
    NEXUS_SurfaceHandle sourceSurface,
    const NEXUS_Rect *pSourceRect,
    NEXUS_BlitColorOp colorOp,
    NEXUS_BlitAlphaOp alphaOp,
    NEXUS_Pixel constantColor
    );
typedef enum NEXUS_PorterDuffOp
{
    NEXUS_PorterDuffOp_eClear = 0,
    NEXUS_PorterDuffOp_eSrc,
    NEXUS_PorterDuffOp_eDst,
    NEXUS_PorterDuffOp_eSrcOver,
    NEXUS_PorterDuffOp_eDstOver,
    NEXUS_PorterDuffOp_eSrcIn,
    NEXUS_PorterDuffOp_eDstIn,
    NEXUS_PorterDuffOp_eSrcOut,
    NEXUS_PorterDuffOp_eDstOut,
    NEXUS_PorterDuffOp_eSrcAtop,
    NEXUS_PorterDuffOp_eDstAtop,
    NEXUS_PorterDuffOp_eXor,
    NEXUS_PorterDuffOp_eMax
} NEXUS_PorterDuffOp;
typedef struct NEXUS_Graphics2DPorterDuffFillSettings
{
    NEXUS_PorterDuffOp operation;
    NEXUS_SurfaceHandle surface;
    NEXUS_Pixel color;
    NEXUS_Rect rect;
} NEXUS_Graphics2DPorterDuffFillSettings;
void NEXUS_Graphics2D_GetDefaultPorterDuffFillSettings(
    NEXUS_Graphics2DPorterDuffFillSettings *pSettings
    );
NEXUS_Error NEXUS_Graphics2D_PorterDuffFill(
    NEXUS_Graphics2DHandle handle,
    const NEXUS_Graphics2DPorterDuffFillSettings *pSettings
    );
typedef struct NEXUS_Graphics2DPorterDuffBlitSettings
{
    NEXUS_PorterDuffOp operation;
    NEXUS_SurfaceHandle sourceSurface;
    NEXUS_Rect sourceRect;
    NEXUS_SurfaceHandle destSurface;
    NEXUS_Rect destRect;
    NEXUS_SurfaceHandle outSurface;
    NEXUS_Rect outRect;
} NEXUS_Graphics2DPorterDuffBlitSettings;
void NEXUS_Graphics2D_GetDefaultPorterDuffBlitSettings(
    NEXUS_Graphics2DPorterDuffBlitSettings *pSettings
    );
NEXUS_Error NEXUS_Graphics2D_PorterDuffBlit(
    NEXUS_Graphics2DHandle handle,
    const NEXUS_Graphics2DPorterDuffBlitSettings *pSettings
    );
NEXUS_Error NEXUS_Graphics2D_Checkpoint(
    NEXUS_Graphics2DHandle handle,
    const NEXUS_CallbackDesc *pLegacyCallback
    );
NEXUS_SurfaceHandle NEXUS_Graphics2D_Destripe(
    NEXUS_Graphics2DHandle handle,
    NEXUS_StripedSurfaceHandle stripedSurface
    );
NEXUS_Error NEXUS_Graphics2D_DestripeToSurface(
    NEXUS_Graphics2DHandle handle,
    NEXUS_StripedSurfaceHandle sourceSurface,
    NEXUS_SurfaceHandle outputSurface,
    const NEXUS_Rect *pOutputRect
    );
typedef struct NEXUS_Graphics2DDestripeBlitSettings
{
    struct {
        NEXUS_StripedSurfaceHandle stripedSurface;
        NEXUS_Rect rect;
    } source;
    struct {
        NEXUS_SurfaceHandle surface;
        NEXUS_Rect rect;
    } output;
    _Bool conversionMatrixEnabled;
    NEXUS_Graphics2DColorMatrix conversionMatrix;
    NEXUS_Graphics2DFilterCoeffs horizontalFilter;
    NEXUS_Graphics2DFilterCoeffs verticalFilter;
    _Bool chromaFilter;
} NEXUS_Graphics2DDestripeBlitSettings;
void NEXUS_Graphics2D_GetDefaultDestripeBlitSettings(
    NEXUS_Graphics2DDestripeBlitSettings *pSettings
    );
NEXUS_Error NEXUS_Graphics2D_DestripeBlit(
    NEXUS_Graphics2DHandle handle,
    const NEXUS_Graphics2DDestripeBlitSettings *pSettings
    );
typedef struct NEXUS_Graphics2DStripeBlitSettings
{
    struct {
        NEXUS_SurfaceHandle surface;
    } source;
    struct {
        NEXUS_StripedSurfaceHandle stripedSurface;
    } output;
} NEXUS_Graphics2DStripeBlitSettings;
void NEXUS_Graphics2D_GetDefaultStripeBlitSettings(
    NEXUS_Graphics2DStripeBlitSettings *pSettings
    );
NEXUS_Error NEXUS_Graphics2D_StripeBlit(
    NEXUS_Graphics2DHandle handle,
    const NEXUS_Graphics2DStripeBlitSettings *pSettings
    );
NEXUS_Error NEXUS_Graphics2D_Memset32(
    NEXUS_Graphics2DHandle handle,
    void *address,
    uint32_t data,
    unsigned count
    );
typedef struct NEXUS_Graphics2DBatchBlitSettings
{
    NEXUS_SurfaceHandle outSurface;
    const uint32_t *pOutOffsets;
    const uint16_t *pOutPoints;
    const uint16_t *pOutSizes;
    NEXUS_SurfaceHandle srcSurface;
    const uint32_t *pSrcOffsets;
    const uint16_t *pSrcPoints;
    const uint16_t *pSrcSizes;
    NEXUS_SurfaceHandle dstSurface;
    const uint32_t *pDstOffsets;
    const uint16_t *pDstPoints;
    const NEXUS_Pixel *pColors;
} NEXUS_Graphics2DBatchBlitSettings;
NEXUS_Error NEXUS_Graphics2D_GetPacketBuffer(
    NEXUS_Graphics2DHandle handle,
    void **pBuffer,
    size_t *pSize,
    size_t minSize
    );
NEXUS_Error NEXUS_Graphics2D_PacketWriteComplete(
    NEXUS_Graphics2DHandle handle,
    size_t size
    );
NEXUS_Error NEXUS_Graphics2D_ConvertFilter(
    NEXUS_Graphics2DFilterCoeffs filter,
    size_t srcSize,
    size_t outSize,
    BM2MC_PACKET_FilterCoeffs *pCoeffs
    );
NEXUS_Error NEXUS_Graphics2D_ConvertColorMatrix(
    const NEXUS_Graphics2DColorMatrix *pMatrixIn,
    BM2MC_PACKET_ColorMatrix *pMatrixOut
    );
void NEXUS_Graphics2D_SetAlphaColorMatrix(
    uint8_t alpha,
    NEXUS_Graphics2DColorMatrix *pMatrix
    );
void NEXUS_Graphics2D_GetCapabilities(
    NEXUS_Graphics2DHandle handle,
    NEXUS_Graphics2DCapabilities *pCapabilities
    );
typedef struct NEXUS_Graphics2DModuleSettings
{
    unsigned stripeWidth;
    struct {
        unsigned hwFifoSize;
    } core[2];
} NEXUS_Graphics2DModuleSettings;
typedef struct NEXUS_Graphics2DModuleInternalSettings
{
    NEXUS_ModuleHandle surface;
} NEXUS_Graphics2DModuleInternalSettings;
void NEXUS_Graphics2DModule_GetDefaultInternalSettings(
    NEXUS_Graphics2DModuleInternalSettings *pSettings
    );
void NEXUS_Graphics2DModule_GetDefaultSettings(
    NEXUS_Graphics2DModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_Graphics2DModule_Init(
    const NEXUS_Graphics2DModuleInternalSettings *pModuleSettings,
    const NEXUS_Graphics2DModuleSettings *pSettings
    );
void NEXUS_Graphics2DModule_Uninit(void);
typedef struct NEXUS_Graphicsv3d *NEXUS_Graphicsv3dHandle;
typedef struct NEXUS_Graphicsv3dInfo
{
   uint32_t uiIdent[8 * 4];
   uint32_t uiHubIdent[4];
} NEXUS_Graphicsv3dInfo;
typedef enum NEXUS_Graphicsv3dJobType
{
   NEXUS_Graphicsv3dJobType_eNull,
   NEXUS_Graphicsv3dJobType_eBin,
   NEXUS_Graphicsv3dJobType_eRender,
   NEXUS_Graphicsv3dJobType_eUser,
   NEXUS_Graphicsv3dJobType_eTFU,
   NEXUS_Graphicsv3dJobType_eFenceWait,
   NEXUS_Graphicsv3dJobType_eTest,
   NEXUS_Graphicsv3dJobType_eUsermode,
   NEXUS_Graphicsv3dJobType_eBarrier,
   NEXUS_Graphicsv3dJobType_eNumJobTypes
} NEXUS_Graphicsv3dJobType;
typedef struct NEXUS_Graphicsv3dSchedDependencies
{
   uint64_t uiDep[8];
   uint32_t uiNumDeps;
} NEXUS_Graphicsv3dSchedDependencies;
typedef enum NEXUS_Graphicsv3dJobStatus
{
   NEXUS_Graphicsv3dJobStatus_eSUCCESS,
   NEXUS_Graphicsv3dJobStatus_eOUT_OF_MEMORY,
   NEXUS_Graphicsv3dJobStatus_eERROR
} NEXUS_Graphicsv3dJobStatus;
typedef struct NEXUS_Graphicsv3dQueryResponse
{
   uint32_t uiStateAchieved;
} NEXUS_Graphicsv3dQueryResponse;
typedef struct NEXUS_Graphicsv3dCompletion
{
   uint64_t uiJobId;
   uint64_t uiCallback;
   uint64_t uiData;
   NEXUS_Graphicsv3dJobStatus eStatus;
   NEXUS_Graphicsv3dJobType eType;
} NEXUS_Graphicsv3dCompletion;
typedef struct NEXUS_Graphicsv3dCompletionInfo
{
   uint64_t uiOldestNotFinalized;
} NEXUS_Graphicsv3dCompletionInfo;
typedef struct NEXUS_Graphicsv3dJobBase
{
   uint64_t uiJobId;
   NEXUS_Graphicsv3dJobType eType;
   NEXUS_Graphicsv3dSchedDependencies sCompletedDependencies;
   NEXUS_Graphicsv3dSchedDependencies sFinalizedDependencies;
   uint64_t uiCompletion;
   uint64_t uiCompletionData;
   uint32_t uiCacheOps;
   _Bool bSecure;
   uint64_t uiPagetablePhysAddr;
   uint32_t uiMmuMaxVirtAddr;
} NEXUS_Graphicsv3dJobBase;
typedef struct NEXUS_Graphicsv3dJobNull
{
   NEXUS_Graphicsv3dJobBase sBase;
} NEXUS_Graphicsv3dJobNull;
typedef struct NEXUS_Graphicsv3dJobBin
{
   NEXUS_Graphicsv3dJobBase sBase;
   uint32_t uiNumSubJobs;
   uint32_t uiStart[8];
   uint32_t uiEnd[8];
   uint32_t uiOffset;
   uint32_t uiFlags;
   uint32_t uiMinInitialBinBlockSize;
} NEXUS_Graphicsv3dJobBin;
typedef struct NEXUS_Graphicsv3dJobRender
{
   NEXUS_Graphicsv3dJobBase sBase;
   uint32_t uiNumSubJobs;
   uint32_t uiStart[16];
   uint32_t uiEnd[16];
   uint32_t uiFlags;
   uint32_t uiEmptyTileMode;
} NEXUS_Graphicsv3dJobRender;
typedef struct NEXUS_Graphicsv3dJobBarrier
{
   NEXUS_Graphicsv3dJobBase sBase;
} NEXUS_Graphicsv3dJobBarrier;
typedef struct NEXUS_Graphicsv3dJobUser
{
   NEXUS_Graphicsv3dJobBase sBase;
   uint32_t uiNumSubJobs;
   uint32_t uiPC[12];
   uint32_t uiUnif[12];
} NEXUS_Graphicsv3dJobUser;
typedef struct NEXUS_Graphicsv3dJobFenceWait
{
   NEXUS_Graphicsv3dJobBase sBase;
   int32_t iFence;
} NEXUS_Graphicsv3dJobFenceWait;
typedef struct NEXUS_Graphicsv3dJobTFU
{
   NEXUS_Graphicsv3dJobBase sBase;
   struct
   {
      uint16_t uiTextureType;
      uint16_t uiByteFormat;
      uint16_t uiEndianness;
      uint16_t uiComponentOrder;
      uint32_t uiRasterStride;
      uint32_t uiChromaStride;
      uint32_t uiAddress;
      uint32_t uiChromaAddress;
      uint32_t uiUPlaneAddress;
      uint64_t uiFlags;
   } sInput;
   struct
   {
      uint32_t uiMipmapCount;
      uint32_t uiVerticalPadding;
      uint32_t uiWidth;
      uint32_t uiHeight;
      uint16_t uiEndianness;
      uint16_t uiByteFormat;
      uint32_t uiAddress;
      uint32_t uiFlags;
   } sOutput;
   struct
   {
      uint16_t uiY;
      uint16_t uiRC;
      uint16_t uiBC;
      uint16_t uiGC;
      uint16_t uiRR;
      uint16_t uiGR;
      uint16_t uiGB;
      uint16_t uiBB;
   } sCustomCoefs;
} NEXUS_Graphicsv3dJobTFU;
typedef struct NEXUS_Graphicsv3dJobTest
{
   NEXUS_Graphicsv3dJobBase sBase;
   uint32_t uiDelay;
} NEXUS_Graphicsv3dJobTest;
typedef struct NEXUS_Graphicsv3dUsermode
{
   uint64_t uiJobId;
   uint64_t uiCallback;
   uint64_t uiData;
   _Bool bHaveJob;
} NEXUS_Graphicsv3dUsermode;
typedef struct NEXUS_Graphicsv3dJobUsermode
{
   NEXUS_Graphicsv3dJobBase sBase;
   uint64_t uiFunction;
   uint64_t uiData;
} NEXUS_Graphicsv3dJobUsermode;
typedef struct NEXUS_Graphicsv3dCreateSettings
{
   uint32_t uiClientPID;
   NEXUS_CallbackDesc sUsermode;
   NEXUS_CallbackDesc sFenceDone;
   NEXUS_CallbackDesc sCompletion;
   int64_t iUnsecureBinTranslation;
   int64_t iSecureBinTranslation;
   uint64_t uiPlatformToken;
} NEXUS_Graphicsv3dCreateSettings;
void NEXUS_Graphicsv3d_GetDefaultCreateSettings(
   NEXUS_Graphicsv3dCreateSettings *psSettings
   );
NEXUS_Graphicsv3dHandle NEXUS_Graphicsv3d_Create(
   const NEXUS_Graphicsv3dCreateSettings *psSettings
   );
void NEXUS_Graphicsv3d_Destroy(
   NEXUS_Graphicsv3dHandle hGfx
   );
NEXUS_Error NEXUS_Graphicsv3d_QueueBinRender(
   NEXUS_Graphicsv3dHandle hGfx,
   const NEXUS_Graphicsv3dJobBin *pBin,
   const NEXUS_Graphicsv3dJobRender *pRender
   );
NEXUS_Error NEXUS_Graphicsv3d_QueueBin(
   NEXUS_Graphicsv3dHandle hGfx,
   const NEXUS_Graphicsv3dJobBin *pBin
   );
NEXUS_Error NEXUS_Graphicsv3d_QueueRender(
   NEXUS_Graphicsv3dHandle hGfx,
   const NEXUS_Graphicsv3dJobRender *pRender
   );
NEXUS_Error NEXUS_Graphicsv3d_QueueTFU(
   NEXUS_Graphicsv3dHandle hGfx,
   uint32_t uiNumJobs,
   const NEXUS_Graphicsv3dJobTFU *pTFUJobs
   );
NEXUS_Error NEXUS_Graphicsv3d_QueueBarrier(
   NEXUS_Graphicsv3dHandle hGfx,
   const NEXUS_Graphicsv3dJobBarrier *pBarrier
   );
NEXUS_Error NEXUS_Graphicsv3d_QueueNull(
   NEXUS_Graphicsv3dHandle hGfx,
   const NEXUS_Graphicsv3dJobNull *pNull
   );
NEXUS_Error NEXUS_Graphicsv3d_QueueTest(
   NEXUS_Graphicsv3dHandle hGfx,
   const NEXUS_Graphicsv3dJobTest *pTest
   );
NEXUS_Error NEXUS_Graphicsv3d_QueueUsermode(
   NEXUS_Graphicsv3dHandle hGfx,
   const NEXUS_Graphicsv3dJobUsermode *pUsermode
   );
NEXUS_Error NEXUS_Graphicsv3d_Query(
   NEXUS_Graphicsv3dHandle hGfx,
   const NEXUS_Graphicsv3dSchedDependencies *pCompletedDeps,
   const NEXUS_Graphicsv3dSchedDependencies *pFinalizedDeps,
   NEXUS_Graphicsv3dQueryResponse *pResponse
   );
NEXUS_Error NEXUS_Graphicsv3d_MakeFenceForJobs(
   NEXUS_Graphicsv3dHandle hGfx,
   const NEXUS_Graphicsv3dSchedDependencies *pCompletedDeps,
   const NEXUS_Graphicsv3dSchedDependencies *pFinalizedDeps,
   _Bool bForceCreate,
   int *piFence
   );
NEXUS_Error NEXUS_Graphicsv3d_MakeFenceForAnyNonFinalizedJob(
   NEXUS_Graphicsv3dHandle hGfx,
   int *piFence
   );
NEXUS_Error NEXUS_Graphicsv3d_QueueFenceWait(
   NEXUS_Graphicsv3dHandle hGfx,
   const NEXUS_Graphicsv3dJobFenceWait *pJob
   );
NEXUS_Error NEXUS_Graphicsv3d_FenceMake(
   NEXUS_Graphicsv3dHandle hGfx,
   int *piFence
   );
NEXUS_Error NEXUS_Graphicsv3d_FenceKeep(
   NEXUS_Graphicsv3dHandle hGfx,
   int iFence
   );
NEXUS_Error NEXUS_Graphicsv3d_RegisterFenceWait(
   NEXUS_Graphicsv3dHandle hGfx,
   int iFence,
   uint64_t uiEvent
   );
NEXUS_Error NEXUS_Graphicsv3d_UnregisterFenceWait(
   NEXUS_Graphicsv3dHandle hGfx,
   int iFence,
   uint64_t uiEvent,
   _Bool *signalled
   );
NEXUS_Error NEXUS_Graphicsv3d_FenceSignal(
   NEXUS_Graphicsv3dHandle hGfx,
   int iFence
   );
NEXUS_Error NEXUS_Graphicsv3d_FenceClose(
   NEXUS_Graphicsv3dHandle hGfx,
   int fence
   );
NEXUS_Error NEXUS_Graphicsv3d_GetPendingFenceEvent(
   NEXUS_Graphicsv3dHandle hGfx,
   uint64_t *puiEvent
   );
NEXUS_Error NEXUS_Graphicsv3d_GetUsermode(
   NEXUS_Graphicsv3dHandle hGfx,
   uint64_t uiPrevJobId,
   NEXUS_Graphicsv3dUsermode *psUsermode
   );
NEXUS_Error NEXUS_Graphicsv3d_GetCompletions(
   NEXUS_Graphicsv3dHandle hGfx,
   uint32_t uiNumFinalizedJobs,
   const uint64_t *puiFinalizedJobs,
   uint32_t uiMaxCompletionsOut,
   NEXUS_Graphicsv3dCompletionInfo *psCompletionInfo,
   uint32_t *puiCompletionsOut,
   NEXUS_Graphicsv3dCompletion *psCompletions
   );
void NEXUS_Graphicsv3d_GetInfo(
   NEXUS_Graphicsv3dInfo *pInfo
   );
typedef enum NEXUS_Graphicsv3dCounterState
{
   NEXUS_Graphicsv3dCtrAcquire = 0,
   NEXUS_Graphicsv3dCtrRelease = 1,
   NEXUS_Graphicsv3dCtrStart = 2,
   NEXUS_Graphicsv3dCtrStop = 3
} NEXUS_Graphicsv3dCounterState;
typedef struct NEXUS_Graphicsv3dCounterDesc
{
   char caName[64];
   char caUnitName[32];
   uint64_t uiMinValue;
   uint64_t uiMaxValue;
   uint64_t uiDenominator;
} NEXUS_Graphicsv3dCounterDesc;
typedef struct NEXUS_Graphicsv3dCounterGroupDesc
{
   char caName[64];
   uint32_t uiTotalCounters;
   uint32_t uiMaxActiveCounters;
   NEXUS_Graphicsv3dCounterDesc saCounters[96];
} NEXUS_Graphicsv3dCounterGroupDesc;
typedef struct NEXUS_Graphicsv3dCounterSelector
{
   uint32_t uiGroupIndex;
   uint32_t uiEnable;
   uint32_t uiaCounters[96];
   uint32_t uiNumCounters;
} NEXUS_Graphicsv3dCounterSelector;
typedef struct NEXUS_Graphicsv3dCounter
{
   uint32_t uiGroupIndex;
   uint32_t uiCounterIndex;
   uint64_t uiValue;
} NEXUS_Graphicsv3dCounter;
void NEXUS_Graphicsv3d_GetPerfNumCounterGroups(
   NEXUS_Graphicsv3dHandle hGfx,
   uint32_t *puiNumGroups
   );
void NEXUS_Graphicsv3d_GetPerfCounterDesc(
   NEXUS_Graphicsv3dHandle hGfx,
   uint32_t uiGroup,
   uint32_t uiCounter,
   NEXUS_Graphicsv3dCounterDesc *psDesc
   );
void NEXUS_Graphicsv3d_GetPerfCounterGroupInfo(
   NEXUS_Graphicsv3dHandle hGfx,
   uint32_t uiGroup,
   char *chGrpName,
   uint32_t *uiMaxActiveCounter,
   uint32_t *uiTotalCounter
   );
NEXUS_Error NEXUS_Graphicsv3d_SetPerfCounting(
   NEXUS_Graphicsv3dHandle hGfx,
   NEXUS_Graphicsv3dCounterState eState
   );
void NEXUS_Graphicsv3d_ChoosePerfCounters(
   NEXUS_Graphicsv3dHandle hGfx,
   const NEXUS_Graphicsv3dCounterSelector *psSelector
   );
void NEXUS_Graphicsv3d_GetPerfCounterData(
   NEXUS_Graphicsv3dHandle hGfx,
   uint32_t uiMaxCounters,
   uint32_t uiResetCounts,
   uint32_t *puiCountersOut,
   NEXUS_Graphicsv3dCounter *psCounters
   );
typedef enum NEXUS_Graphicsv3dEventState
{
   NEXUS_Graphicsv3dEventAcquire = 0,
   NEXUS_Graphicsv3dEventRelease = 1,
   NEXUS_Graphicsv3dEventStart = 2,
   NEXUS_Graphicsv3dEventStop = 3
} NEXUS_Graphicsv3dEventState;
typedef enum NEXUS_Graphicsv3dEventType
{
   NEXUS_Graphicsv3dEventBegin = 0,
   NEXUS_Graphicsv3dEventEnd = 1,
   NEXUS_Graphicsv3dEventOneshot = 2
} NEXUS_Graphicsv3dEventType;
typedef enum NEXUS_Graphicsv3dFieldType
{
   NEXUS_Graphicsv3dEventInt32 = 0,
   NEXUS_Graphicsv3dEventUInt32 = 1,
   NEXUS_Graphicsv3dEventInt64 = 2,
   NEXUS_Graphicsv3dEventUInt64 = 3
} NEXUS_Graphicsv3dFieldType;
typedef struct NEXUS_Graphicsv3dEventDesc
{
   char caName[64];
   uint32_t uiNumDataFields;
} NEXUS_Graphicsv3dEventDesc;
typedef struct NEXUS_Graphicsv3dEventFieldDesc
{
   char caName[64];
   NEXUS_Graphicsv3dFieldType eDataType;
} NEXUS_Graphicsv3dEventFieldDesc;
typedef struct NEXUS_Graphicsv3dEventTrackDesc
{
   char caName[64];
} NEXUS_Graphicsv3dEventTrackDesc;
void NEXUS_Graphicsv3d_GetEventCounts(
   NEXUS_Graphicsv3dHandle hGfx,
   uint32_t *uiNumTracks,
   uint32_t *uiNumEvents
   );
NEXUS_Error NEXUS_Graphicsv3d_GetEventTrackInfo(
   NEXUS_Graphicsv3dHandle hGfx,
   uint32_t uiTrack,
   NEXUS_Graphicsv3dEventTrackDesc *psTrackDesc
   );
NEXUS_Error NEXUS_Graphicsv3d_GetEventInfo(
   NEXUS_Graphicsv3dHandle hGfx,
   uint32_t uiEvent,
   NEXUS_Graphicsv3dEventDesc *psEventDesc
   );
NEXUS_Error NEXUS_Graphicsv3d_GetEventDataFieldInfo(
   NEXUS_Graphicsv3dHandle hGfx,
   uint32_t uiEvent,
   uint32_t uiField,
   NEXUS_Graphicsv3dEventFieldDesc *psFieldDesc
   );
NEXUS_Error NEXUS_Graphicsv3d_SetEventCollection(
   NEXUS_Graphicsv3dHandle hGfx,
   NEXUS_Graphicsv3dEventState eState
   );
void NEXUS_Graphicsv3d_GetEventData(
   NEXUS_Graphicsv3dHandle hGfx,
   uint32_t uiEventBufferBytes,
   void *pvEventBuffer,
   uint32_t *puiLostData,
   uint64_t *puiTimeStamp,
   uint32_t *puiBytesCopiedOut
   );
void NEXUS_Graphicsv3d_GetTime(
   uint64_t *pMicroseconds
   );
typedef struct NEXUS_Graphicsv3dModuleSettings
{
   NEXUS_HeapHandle hHeap;
   NEXUS_HeapHandle hHeapSecure;
} NEXUS_Graphicsv3dModuleSettings;
void NEXUS_Graphicsv3dModule_GetDefaultSettings(
    NEXUS_Graphicsv3dModuleSettings *psSettings
    );
NEXUS_ModuleHandle NEXUS_Graphicsv3dModule_Init(
    const NEXUS_Graphicsv3dModuleSettings *psSettings
    );
void NEXUS_Graphicsv3dModule_Uninit(void);
typedef enum NEXUS_HdmiInputPacketType
{
    NEXUS_HdmiInputPacketType_eNull = 0x00,
    NEXUS_HdmiInputPacketType_eAudioClockRegeneration = 0x01,
    NEXUS_HdmiInputPacketType_eAudioSample = 0x02,
    NEXUS_HdmiInputPacketType_eGeneralControl = 0x03,
    NEXUS_HdmiInputPacketType_eAudioContentProtection = 0x04,
    NEXUS_HdmiInputPacketType_eISRC1 = 0x05,
    NEXUS_HdmiInputPacketType_eISRC2 = 0x06,
    NEXUS_HdmiInputPacketType_eDirectStream = 0x07,
    NEXUS_HdmiInputPacketType_eGamutMetadataPacket = 0xA,
    NEXUS_HdmiInputPacketType_eVendorSpecific = 0x81,
    NEXUS_HdmiInputPacketType_eAviInfoFrame = 0x82,
    NEXUS_HdmiInputPacketType_eSpdInfoFrame = 0x83,
    NEXUS_HdmiInputPacketType_eAudioInfoFrame = 0x84,
    NEXUS_HdmiInputPacketType_eMpegInfoFrame = 0x85,
    NEXUS_HdmiInputPacketType_eUnused = 0xA0
} NEXUS_HdmiInputPacketType;
typedef enum NEXUS_HdmiGamutFormat
{
    NEXUS_HdmiGamutFormat_eVerticesFacets,
    NEXUS_HdmiGamutFormat_eRange
} NEXUS_HdmiGamutFormat;
typedef enum NEXUS_HdmiGamutColorPrecision
{
    NEXUS_HdmiGamutColorPrecision_e8Bit,
    NEXUS_HdmiGamutColorPrecision_e10Bit,
    NEXUS_HdmiGamutColorPrecision_e12Bit,
    NEXUS_HdmiGamutColorPrecision_eUnknown
} NEXUS_HdmiGamutColorPrecision;
typedef enum NEXUS_HdmiGamutColorSpace
{
    NEXUS_HdmiGamutColorSpace_eItu709RGB,
    NEXUS_HdmiGamutColorSpace_exvYCC601SD,
    NEXUS_HdmiGamutColorSpace_exvYCC709HD,
    NEXUS_HdmiGamutColorSpace_eXZY
} NEXUS_HdmiGamutColorSpace;
typedef struct NEXUS_HdmiGcpData
{
    uint8_t PixelPacking;
    uint8_t ColorDepth;
    uint8_t DefaultPhase;
    NEXUS_HdmiPacketStatus packetStatus;
    NEXUS_HdmiPacket packet;
} NEXUS_HdmiGcpData;
typedef struct NEXUS_HdmiGamutPacket
{
    uint8_t type;
    uint8_t nextField;
    uint8_t profile;
    uint8_t affectedGamutSeqNumber;
    uint8_t noCurrentGamut;
    uint8_t packetSeq;
    uint8_t currentGamutSeqNumber;
    uint8_t dataBytes[28];
    NEXUS_HdmiGamutFormat format;
    _Bool facets;
    NEXUS_HdmiGamutColorPrecision colorPrecision;
    NEXUS_HdmiGamutColorSpace colorSpace;
    uint16_t numberVertices;
    uint16_t numberFacets;
    uint16_t y[4];
    uint16_t cb[4];
    uint16_t cr[4];
    uint16_t minRedData;
    uint16_t maxRedData;
    uint16_t minGreenData;
    uint16_t maxGreenData;
    uint16_t minBlueData;
    uint16_t maxBlueData;
    NEXUS_HdmiPacketStatus packetStatus;
} NEXUS_HdmiGamutPacket;
typedef struct NEXUS_HdmiAudioContentProtection
{
    uint8_t acpType;
    char acpTypeDependent[28];
    NEXUS_HdmiPacketStatus packetStatus;
    NEXUS_HdmiPacket packet;
} NEXUS_HdmiAudioContentProtection;
typedef struct NEXUS_HdmiAudioClockRegeneration
{
    uint32_t cts;
    uint32_t n;
    NEXUS_HdmiPacketStatus packetStatus;
    NEXUS_HdmiPacket packet;
} NEXUS_HdmiAudioClockRegeneration;
typedef struct NEXUS_HdmiGeneralControlPacket
{
    uint32_t muteStatus;
    uint32_t setAvMute;
    uint32_t clearAvMute;
    uint32_t pixelPacking;
    uint32_t colorDepth;
    uint32_t defaultPhase;
    NEXUS_HdmiPacketStatus packetStatus;
    NEXUS_HdmiPacket packet;
} NEXUS_HdmiGeneralControlPacket;
typedef struct NEXUS_HdmiISRC
{
    _Bool ISRC1_PacketReceived ;
    _Bool ISRC_Cont ;
    _Bool ISRC_Valid ;
    uint8_t ISRC_Status ;
    uint8_t ISRC_UPC_EAN[32];
    NEXUS_HdmiPacket ISRC1_Packet ;
    NEXUS_HdmiPacket ISRC2_Packet ;
    NEXUS_HdmiPacketStatus packetStatus ;
} NEXUS_HdmiISRC ;
NEXUS_Error NEXUS_HdmiInput_GetRawPacketData(
    NEXUS_HdmiInputHandle hdmiInput,
    NEXUS_HdmiInputPacketType packetType,
    NEXUS_HdmiPacket *pPacket
    );
NEXUS_Error NEXUS_HdmiInput_GetAviInfoFrameData(
    NEXUS_HdmiInputHandle hdmiInput,
    NEXUS_HdmiAviInfoFrame *pAviInfoFrame
    );
NEXUS_Error NEXUS_HdmiInput_GetAudioInfoFrameData(
    NEXUS_HdmiInputHandle hdmiInput,
    NEXUS_HdmiAudioInfoFrame *pAudioInfoFrame
    );
NEXUS_Error NEXUS_HdmiInput_GetSpdInfoFrameData(
    NEXUS_HdmiInputHandle hdmiInput,
    NEXUS_HdmiSpdInfoFrame *pSpdInfoFrame
    );
NEXUS_Error NEXUS_HdmiInput_GetAudioContentProtection(
    NEXUS_HdmiInputHandle hdmiInput,
    NEXUS_HdmiAudioContentProtection *pAcp
    );
NEXUS_Error NEXUS_HdmiInput_GetAudioClockRegeneration(
    NEXUS_HdmiInputHandle hdmiInput,
    NEXUS_HdmiAudioClockRegeneration *pAudioClockRegeneration
    );
NEXUS_Error NEXUS_HdmiInput_GetGeneralControlPacket(
    NEXUS_HdmiInputHandle hdmiInput,
    NEXUS_HdmiGeneralControlPacket *pGeneralControlPacket
    );
NEXUS_Error NEXUS_HdmiInput_GetVendorSpecificInfoFrameData(
    NEXUS_HdmiInputHandle hdmiInput,
    NEXUS_HdmiVendorSpecificInfoFrame *pVendorSpecificInfoFrame
    );
NEXUS_Error NEXUS_HdmiInput_GetISRCData(
    NEXUS_HdmiInputHandle hdmiInput,
    NEXUS_HdmiISRC *pISRCData
    ) ;
NEXUS_Error NEXUS_HdmiInput_DebugGetEyeDiagramData(
    NEXUS_HdmiInputHandle hdmiInput,
    uint8_t *pAdcData
    );
void NEXUS_HdmiInput_HdcpGetDefaultSettings(
    NEXUS_HdmiInputHandle hdmiInput,
    NEXUS_HdmiInputHdcpSettings *pSettings
    ) ;
void NEXUS_HdmiInput_HdcpGetSettings(
    NEXUS_HdmiInputHandle hdmiInput,
    NEXUS_HdmiInputHdcpSettings *pSettings
    );
NEXUS_Error NEXUS_HdmiInput_HdcpSetSettings(
    NEXUS_HdmiInputHandle hdmiInput,
    const NEXUS_HdmiInputHdcpSettings *pSettings
    );
void NEXUS_HdmiInput_HdcpGetDefaultKeyset(
    NEXUS_HdmiInputHandle hdmiInput,
    NEXUS_HdmiInputHdcpKeyset *pKeyset
    );
NEXUS_Error NEXUS_HdmiInput_HdcpSetKeyset(
    NEXUS_HdmiInputHandle hdmiInput,
    const NEXUS_HdmiInputHdcpKeyset *pKeyset
    ) ;
NEXUS_Error NEXUS_HdmiInput_HdcpGetStatus(
   NEXUS_HdmiInputHandle hdmiInput,
   NEXUS_HdmiInputHdcpStatus *pHdcpStatus
   );
NEXUS_Error NEXUS_HdmiInput_HdcpLoadKsvFifo(
    NEXUS_HdmiInputHandle hdmiInput,
    const NEXUS_HdmiHdcpDownStreamInfo *pDownstreamInfo,
    const NEXUS_HdmiHdcpKsv *pDownstreamKsvs,
 unsigned numDevices
 );
NEXUS_Error NEXUS_HdmiInput_SetHdcp2xBinKeys(
    NEXUS_HdmiInputHandle handle,
    const uint8_t *pBinFileBuffer,
    uint32_t length
);
typedef struct NEXUS_HdmiInputModuleSettings
{
    struct
    {
        NEXUS_ModuleHandle security;
        NEXUS_ModuleHandle sage;
    } modules;
} NEXUS_HdmiInputModuleSettings;
void NEXUS_HdmiInputModule_GetDefaultSettings(
    NEXUS_HdmiInputModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_HdmiInputModule_Init(
    const NEXUS_HdmiInputModuleSettings *pSettings
    );
void NEXUS_HdmiInputModule_Uninit(void);
typedef struct NEXUS_HdmiOutputExtraSettings
{
    _Bool overrideDynamicRangeMasteringInfoFrame;
    NEXUS_HdmiDynamicRangeMasteringInfoFrame dynamicRangeMasteringInfoFrame;
} NEXUS_HdmiOutputExtraSettings;
void NEXUS_HdmiOutput_GetExtraSettings(
    NEXUS_HdmiOutputHandle output,
    NEXUS_HdmiOutputExtraSettings *pSettings
    );
NEXUS_Error NEXUS_HdmiOutput_SetExtraSettings(
    NEXUS_HdmiOutputHandle output,
    const NEXUS_HdmiOutputExtraSettings *pSettings
    );
void NEXUS_HdmiOutput_DisplayRxEdid(
    NEXUS_HdmiOutputHandle handle
    );
void NEXUS_HdmiOutput_DisplayRxInfo(
    NEXUS_HdmiOutputHandle handle
    );
void NEXUS_HdmiOutput_GetVideoFormatFromDetailTiming(
    NEXUS_HdmiOutputHandle handle,
    uint8_t detailTimingNumber
    );
void NEXUS_HdmiOutput_SetAviInfoFrameColorimetry(
    NEXUS_HdmiOutputHandle handle,
    uint8_t colorimetry
    );
void NEXUS_HdmiOutput_SetAviInfoFrameAspectRatio(
    NEXUS_HdmiOutputHandle handle,
    uint8_t aspectRatio
    );
void NEXUS_HdmiOutput_EnablePjChecking(
    NEXUS_HdmiOutputHandle handle,
    _Bool enable
    );
void NEXUS_HdmiOutput_ForceVideoPixel(
    NEXUS_HdmiOutputHandle handle,
    uint8_t pixelValue
    );
void NEXUS_HdmiOutput_EnablePacketTransmission(
    NEXUS_HdmiOutputHandle handle,
    uint8_t packetChoice
    );
void NEXUS_HdmiOutput_DisablePacketTransmission(
    NEXUS_HdmiOutputHandle handle,
    uint8_t packetChoice
    );
NEXUS_Error NEXUS_HdmiOutput_ResetScrambling(
    NEXUS_HdmiOutputHandle handle
    );
typedef struct NEXUS_HdmiOutputModuleSettings
{
    struct
    {
        NEXUS_ModuleHandle security;
        NEXUS_ModuleHandle sage;
        NEXUS_ModuleHandle hdmiInput;
    } modules;
    _Bool softI2c ;
} NEXUS_HdmiOutputModuleSettings;
void NEXUS_HdmiOutputModule_GetDefaultSettings(
    NEXUS_HdmiOutputModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_HdmiOutputModule_Init(
    const NEXUS_HdmiOutputModuleSettings *pSettings
    );
void NEXUS_HdmiOutputModule_Uninit(void);
typedef enum NEXUS_HMACSHA_Op
{
    NEXUS_HMACSHA_Op_eSHA = 0,
    NEXUS_HMACSHA_Op_eHMAC = 1
} NEXUS_HMACSHA_Op;
typedef enum NEXUS_HMACSHA_KeyInclusion_Op
{
    NEXUS_HMACSHA_KeyInclusion_Op_eNo = 0,
    NEXUS_HMACSHA_KeyInclusion_Op_eAppend = 1
} NEXUS_HMACSHA_KeyInclusion_Op;
typedef enum NEXUS_HMACSHA_SHAType
{
    NEXUS_HMACSHA_SHAType_eSha160 = 0,
    NEXUS_HMACSHA_SHAType_eSha224 = 1,
 NEXUS_HMACSHA_SHAType_eSha256 = 2,
 NEXUS_HMACSHA_SHAType_eMax
} NEXUS_HMACSHA_SHAType;
typedef enum NEXUS_HMACSHA_BSPContext
{
    NEXUS_HMACSHA_BSPContext_eContext0,
    NEXUS_HMACSHA_BSPContext_eContext1
} NEXUS_HMACSHA_BSPContext;
typedef enum NEXUS_HMACSHA_DataMode
{
 NEXUS_HMACSHA_DataMode_eAllIn = 0x00,
 NEXUS_HMACSHA_DataMode_eMore = 0x01,
 NEXUS_HMACSHA_DataMode_eLast = 0x10
} NEXUS_HMACSHA_DataMode;
typedef enum NEXUS_HMACSHA_DataSource
{
    NEXUS_HMACSHA_DataSource_eCmdBuf = 0,
    NEXUS_HMACSHA_DataSource_eDRAM = 1
} NEXUS_HMACSHA_DataSource;
typedef enum NEXUS_HMACSHA_KeySource
{
    NEXUS_HMACSHA_KeySource_eKeyVal = 0,
    NEXUS_HMACSHA_KeySource_eKeyLadder = 1
} NEXUS_HMACSHA_KeySource;
typedef struct NEXUS_HMACSHA_OpSettings
{
 NEXUS_HMACSHA_Op opMode;
 NEXUS_HMACSHA_SHAType shaType;
 NEXUS_HMACSHA_BSPContext context;
 NEXUS_HMACSHA_KeySource keySource;
 NEXUS_SecurityVirtualKeyladderID VKL;
 NEXUS_SecurityKeySource keyLayer;
 uint32_t keyLength;
 unsigned char keyData[32];
 NEXUS_HMACSHA_DataMode dataMode;
 NEXUS_HMACSHA_KeyInclusion_Op keyIncMode;
 _Bool byteSwap;
    uint32_t dataSize;
    uint8_t *dataAddress;
 NEXUS_HMACSHA_DataSource dataSrc;
 uint32_t includeKey;
} NEXUS_HMACSHA_OpSettings;
typedef struct NEXUS_HMACSHA_DigestOutput
{
 unsigned char digestData[32];
    uint32_t digestSize;
} NEXUS_HMACSHA_DigestOutput;
void NEXUS_HMACSHA_GetDefaultOpSettings(
 NEXUS_HMACSHA_OpSettings *pOpSettings
    );
NEXUS_Error NEXUS_HMACSHA_PerformOp(
    const NEXUS_HMACSHA_OpSettings *pOpSettings,
    NEXUS_HMACSHA_DigestOutput *pOutput
    );
typedef struct NEXUS_I2cModuleSettings
{
    NEXUS_CommonModuleSettings common;
} NEXUS_I2cModuleSettings;
void NEXUS_I2cModule_GetDefaultSettings(
    NEXUS_I2cModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_I2cModule_Init(
    const NEXUS_I2cModuleSettings *pSettings
    );
void NEXUS_I2cModule_Uninit(void);
typedef struct NEXUS_I2sInput *NEXUS_I2sInputHandle;
typedef struct NEXUS_I2sInputSettings
{
    unsigned sampleRate;
    unsigned bitsPerSample;
    NEXUS_Timebase timebase;
    _Bool lsbAtLRClock;
    _Bool alignedToLRClock;
    _Bool lrClkPolarity;
    int32_t leftVolume;
    int32_t rightVolume;
    _Bool muted;
} NEXUS_I2sInputSettings;
void NEXUS_I2sInput_GetDefaultSettings(
    NEXUS_I2sInputSettings *pSettings
    );
NEXUS_I2sInputHandle NEXUS_I2sInput_Open(
    unsigned index,
    const NEXUS_I2sInputSettings *pSettings
    );
void NEXUS_I2sInput_Close(
    NEXUS_I2sInputHandle handle
    );
void NEXUS_I2sInput_GetSettings(
    NEXUS_I2sInputHandle handle,
    NEXUS_I2sInputSettings *pSettings
    );
NEXUS_Error NEXUS_I2sInput_SetSettings(
    NEXUS_I2sInputHandle handle,
    const NEXUS_I2sInputSettings *pSettings
    );
NEXUS_Error NEXUS_I2sInput_Start(
    NEXUS_I2sInputHandle handle
    );
void NEXUS_I2sInput_Stop(
    NEXUS_I2sInputHandle handle
    );
NEXUS_AudioInputHandle NEXUS_I2sInput_GetConnector(
    NEXUS_I2sInputHandle handle
    );
typedef struct NEXUS_I2sOutput *NEXUS_I2sOutputHandle;
typedef enum NEXUS_I2sOutputSclkRate
{
    NEXUS_I2sOutputSclkRate_e64Fs,
    NEXUS_I2sOutputSclkRate_e128Fs,
    NEXUS_I2sOutputSclkRate_eMax
} NEXUS_I2sOutputSclkRate;
typedef enum NEXUS_I2sOutputMclkRate
{
    NEXUS_I2sOutputMclkRate_e128Fs,
    NEXUS_I2sOutputMclkRate_e256Fs,
    NEXUS_I2sOutputMclkRate_e384Fs,
    NEXUS_I2sOutputMclkRate_e512Fs,
    NEXUS_I2sOutputMclkRate_eAuto,
    NEXUS_I2sOutputMclkRate_eMax
} NEXUS_I2sOutputMclkRate;
typedef struct NEXUS_I2sOutputSettings
{
    _Bool lsbAtLRClock;
    _Bool alignedToLRClock;
    _Bool lrClkPolarity;
    NEXUS_I2sOutputSclkRate sclkRate;
    NEXUS_I2sOutputMclkRate mclkRate;
} NEXUS_I2sOutputSettings;
void NEXUS_I2sOutput_GetDefaultSettings(
    NEXUS_I2sOutputSettings *pSettings
    );
NEXUS_I2sOutputHandle NEXUS_I2sOutput_Open(
    unsigned index,
    const NEXUS_I2sOutputSettings *pSettings
    );
void NEXUS_I2sOutput_Close(
    NEXUS_I2sOutputHandle handle
    );
void NEXUS_I2sOutput_GetSettings(
    NEXUS_I2sOutputHandle handle,
    NEXUS_I2sOutputSettings *pSettings
    );
NEXUS_Error NEXUS_I2sOutput_SetSettings(
    NEXUS_I2sOutputHandle handle,
    const NEXUS_I2sOutputSettings *pSettings
    );
NEXUS_AudioOutputHandle NEXUS_I2sOutput_GetConnector(
    NEXUS_I2sOutputHandle handle
    );
typedef struct NEXUS_InputCapture *NEXUS_InputCaptureHandle;
typedef struct NEXUS_InputCaptureTimeout *NEXUS_InputCaptureTimeoutHandle;
typedef enum NEXUS_InputCaptureEdgeSelect
{
    NEXUS_InputCaptureEdgeSelect_eNegative,
    NEXUS_InputCaptureEdgeSelect_ePositive,
    NEXUS_InputCaptureEdgeSelect_eBoth,
    NEXUS_InputCaptureEdgeSelect_eMax
} NEXUS_InputCaptureEdgeSelect;
typedef enum NEXUS_InputCaptureType
{
    NEXUS_InputCaptureType_eIcap,
    NEXUS_InputCaptureType_eBicap,
    NEXUS_InputCaptureType_eMax
} NEXUS_InputCaptureType;
typedef enum NEXUS_InputCaptureCountMode
{
    NEXUS_InputCaptureCountMode_eSaturate,
    NEXUS_InputCaptureCountMode_eContinueToZero,
    NEXUS_InputCaptureCountMode_eFreeRunning,
    NEXUS_InputCaptureCountMode_eNoMaxCount,
    NEXUS_InputCaptureCountMode_eMax
} NEXUS_InputCaptureCountMode;
typedef enum NEXUS_InputCaptureClockSelect
{
    NEXUS_InputCaptureClockSelect_eBicapClock,
    NEXUS_InputCaptureClockSelect_eTimeoutClock,
    NEXUS_InputCaptureClockSelect_eMax
} NEXUS_InputCaptureClockSelect;
typedef enum NEXUS_InputCaptureFilterClockSelect
{
    NEXUS_InputCaptureFilterClockSelect_eBicapClock,
    NEXUS_InputCaptureFilterClockSelect_eSystemClock,
    NEXUS_InputCaptureFilterClockSelect_eMax
} NEXUS_InputCaptureFilterClockSelect;
typedef struct NEXUS_InputCaptureSettings
{
    NEXUS_InputCaptureType type;
    unsigned fifoSize;
    NEXUS_InputCaptureEdgeSelect edgeSelect;
    NEXUS_CallbackDesc dataReady;
    struct {
        _Bool enable;
        NEXUS_InputCaptureFilterClockSelect clockSelect;
        unsigned value;
    } filter;
    struct {
        unsigned systemClockDivisor;
        unsigned timeoutClockDivisor;
        NEXUS_InputCaptureCountMode countMode;
        _Bool invertSignalInput;
    } bicap;
} NEXUS_InputCaptureSettings;
void NEXUS_InputCapture_GetDefaultSettings(
    NEXUS_InputCaptureSettings *pSettings
    );
NEXUS_InputCaptureHandle NEXUS_InputCapture_Open(
    unsigned index,
    const NEXUS_InputCaptureSettings *pSettings
    );
void NEXUS_InputCapture_Close(
    NEXUS_InputCaptureHandle handle
    );
typedef struct NEXUS_InputCaptureData
{
    _Bool polarity;
    unsigned clockCycles;
} NEXUS_InputCaptureData;
NEXUS_Error NEXUS_InputCapture_ReadData(
    NEXUS_InputCaptureHandle inputCapture,
    NEXUS_InputCaptureData *pData,
    unsigned numEntries,
    unsigned *pNumRead
    );
NEXUS_Error NEXUS_InputCapture_GetEdgeCount(
    NEXUS_InputCaptureHandle inputCapture,
    unsigned *pNumEdges
    );
void NEXUS_InputCapture_GetSettings(
    NEXUS_InputCaptureHandle inputCapture,
    NEXUS_InputCaptureSettings *settings
    );
NEXUS_Error NEXUS_InputCapture_SetSettings(
    NEXUS_InputCaptureHandle inputCapture,
    const NEXUS_InputCaptureSettings *settings
    );
NEXUS_Error NEXUS_InputCapture_Enable(
    NEXUS_InputCaptureHandle inputCapture
    );
void NEXUS_InputCapture_Disable(
    NEXUS_InputCaptureHandle inputCapture
    );
typedef struct NEXUS_InputCaptureTimeoutSettings
{
    NEXUS_InputCaptureHandle inputCapture;
    NEXUS_InputCaptureEdgeSelect edgeSelect;
    NEXUS_InputCaptureClockSelect clockSelect;
    unsigned clockCycles;
} NEXUS_InputCaptureTimeoutSettings;
void NEXUS_InputCaptureTimeout_GetDefaultSettings(
    NEXUS_InputCaptureTimeoutSettings *pSettings
    );
NEXUS_InputCaptureTimeoutHandle NEXUS_InputCaptureTimeout_Open(
    unsigned index,
    const NEXUS_InputCaptureTimeoutSettings *pSettings
    );
void NEXUS_InputCaptureTimeout_Close(
    NEXUS_InputCaptureTimeoutHandle inputCaptureTimeout
    );
void NEXUS_InputCaptureTimeout_GetSettings(
    NEXUS_InputCaptureTimeoutHandle inputCaptureTimeout,
    NEXUS_InputCaptureTimeoutSettings *pSettings
    );
NEXUS_Error NEXUS_InputCaptureTimeout_SetSettings(
    NEXUS_InputCaptureTimeoutHandle inputCaptureTimeout,
    const NEXUS_InputCaptureTimeoutSettings *pSettings
    );
typedef struct NEXUS_InputCaptureModuleSettings
{
    NEXUS_CommonModuleSettings common;
} NEXUS_InputCaptureModuleSettings;
void NEXUS_InputCaptureModule_GetDefaultSettings(
    NEXUS_InputCaptureModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_InputCaptureModule_Init(
    const NEXUS_InputCaptureModuleSettings *pSettings
    );
void NEXUS_InputCaptureModule_Uninit(void);
typedef enum NEXUS_IrInputTolerance
{
    NEXUS_IrInputTolerance_e12_5,
    NEXUS_IrInputTolerance_e25,
    NEXUS_IrInputTolerance_e50,
    NEXUS_IrInputTolerance_eFixed,
    NEXUS_IrInputTolerance_eMax
} NEXUS_IrInputTolerance;
typedef struct NEXUS_IrInputValue
{
    unsigned value;
    uint8_t tolerance;
} NEXUS_IrInputValue;
typedef struct NEXUS_IrInputCustomSettings
{
    unsigned countDivisor;
    NEXUS_IrInputValue preambleA[4];
    NEXUS_IrInputValue preambleB[4];
    uint8_t preambleACount;
    uint8_t preambleBCount;
    int measurePreamblePulse;
    int preambleBRepeat;
    unsigned pulseTolerance;
    unsigned t0;
    unsigned delT;
    int fixSymPulseLast;
    int measureSymPulse;
    NEXUS_IrInputValue symPulseWidth;
    NEXUS_IrInputValue spacingTol;
    unsigned nSymA;
    unsigned nSymB;
    unsigned bitsPerSym;
    int mostSignifSymRecvFirst;
    int leftAdjustRecvData;
    int biphaseCoded;
    int twoSymPerCycle;
    int checkStopSym;
    int variableLenData;
    unsigned timeoutDivisor;
    unsigned frameTimeout;
    unsigned edgeTimeout;
    unsigned minOffTime;
    NEXUS_IrInputValue stop;
    unsigned dataSymTimeout;
    unsigned repeatTimeout;
    int stopParamUnit;
    int dataSymClkTickUnit;
    int ignoreDataSymTimerEdge1;
    int dataSymTimerExpStatEn;
    int enHavePreambleAftStop;
    int havePreambleAftStop;
    int restrictiveDecode;
    int rc6;
    int dontValidateMode;
    unsigned modeBits;
    int dontValidateTrailer;
    unsigned rc6Trailer;
    int dontValidateCustCode;
    unsigned custCode;
    unsigned nCustCodeBits;
    unsigned passModeCustCodePass;
} NEXUS_IrInputCustomSettings;
void NEXUS_IrInput_GetDefaultCustomSettings(
    NEXUS_IrInputCustomSettings *pSettings
    );
typedef struct NEXUS_IrInput *NEXUS_IrInputHandle;
typedef enum NEXUS_IrInputMode
{
    NEXUS_IrInputMode_eTwirpKbd = 1,
    NEXUS_IrInputMode_eSejin38KhzKbd,
    NEXUS_IrInputMode_eSejin56KhzKbd,
    NEXUS_IrInputMode_eRemoteA,
    NEXUS_IrInputMode_eRemoteB,
    NEXUS_IrInputMode_eCirGI,
    NEXUS_IrInputMode_eCirSaE2050,
    NEXUS_IrInputMode_eCirTwirp,
    NEXUS_IrInputMode_eCirSony,
    NEXUS_IrInputMode_eCirRecs80,
    NEXUS_IrInputMode_eCirRc5,
    NEXUS_IrInputMode_eCirUei,
    NEXUS_IrInputMode_eCirRfUei,
    NEXUS_IrInputMode_eCirEchoStar,
    NEXUS_IrInputMode_eSonySejin,
    NEXUS_IrInputMode_eCirNec,
    NEXUS_IrInputMode_eCirRC6,
    NEXUS_IrInputMode_eCirGISat,
    NEXUS_IrInputMode_eCustom,
    NEXUS_IrInputMode_eCirDirectvUhfr,
    NEXUS_IrInputMode_eCirEchostarUhfr,
    NEXUS_IrInputMode_eCirRcmmRcu,
    NEXUS_IrInputMode_eCirRstep,
    NEXUS_IrInputMode_eCirXmp,
    NEXUS_IrInputMode_eCirXmp2Ack,
    NEXUS_IrInputMode_eCirRC6Mode0,
    NEXUS_IrInputMode_eCirRca,
    NEXUS_IrInputMode_eCirToshibaTC9012,
    NEXUS_IrInputMode_eCirXip,
    NEXUS_IrInputMode_eMax
} NEXUS_IrInputMode;
typedef struct NEXUS_IrInputSettings
{
    unsigned repeatFilterTime;
    unsigned eventQueueSize;
    NEXUS_CallbackDesc dataReady;
    NEXUS_IrInputMode mode;
    unsigned channel_number;
    _Bool useCustomSettings;
    NEXUS_IrInputCustomSettings customSettings;
    unsigned pulseWidthFilter;
} NEXUS_IrInputSettings;
void NEXUS_IrInput_GetDefaultSettings(
    NEXUS_IrInputSettings *pSettings
    );
NEXUS_Error NEXUS_IrInput_GetCustomSettingsForMode(
    NEXUS_IrInputMode mode,
    NEXUS_IrInputCustomSettings *pSettings
    );
NEXUS_IrInputHandle NEXUS_IrInput_Open(
    unsigned index,
    const NEXUS_IrInputSettings *pSettings
    );
void NEXUS_IrInput_Close(
    NEXUS_IrInputHandle handle
    );
void NEXUS_IrInput_GetSettings(
    NEXUS_IrInputHandle handle,
    NEXUS_IrInputSettings *pSettings
    );
NEXUS_Error NEXUS_IrInput_SetSettings(
    NEXUS_IrInputHandle handle,
    const NEXUS_IrInputSettings *pSettings
    );
typedef struct NEXUS_IrInputPreambleStatus
{
    _Bool preambleA;
    _Bool preambleB;
} NEXUS_IrInputPreambleStatus;
typedef struct NEXUS_IrInputEvent
{
    _Bool repeat;
    uint32_t code;
    uint32_t codeHigh;
    unsigned interval;
    NEXUS_IrInputPreambleStatus preamble;
} NEXUS_IrInputEvent;
NEXUS_Error NEXUS_IrInput_GetEvents(
    NEXUS_IrInputHandle handle,
    NEXUS_IrInputEvent *pEvents,
    size_t numEvents,
    size_t *pNumEventsRead,
    _Bool *pOverflow
    );
void NEXUS_IrInput_FlushEvents(
    NEXUS_IrInputHandle handle
    );
NEXUS_Error NEXUS_IrInput_GetPreambleStatus(
    NEXUS_IrInputHandle handle,
    NEXUS_IrInputPreambleStatus *pStatus
    );
NEXUS_Error NEXUS_IrInput_ReadEvent(
    NEXUS_IrInputHandle irInput,
    NEXUS_IrInputEvent *pEvent
    );
typedef struct NEXUS_IrInputDataFilter
{
    struct {
        _Bool enabled;
        uint64_t patternWord;
        uint64_t mask;
    } filterWord[2];
    uint32_t patternWord0;
    uint32_t patternWord1;
    uint32_t mask0;
    uint32_t mask1;
} NEXUS_IrInputDataFilter;
void NEXUS_IrInput_GetDefaultDataFilter(
    NEXUS_IrInputDataFilter *pPattern
    );
NEXUS_Error NEXUS_IrInput_EnableDataFilter(
    NEXUS_IrInputHandle handle,
    const NEXUS_IrInputDataFilter *pPattern
    );
void NEXUS_IrInput_DisableDataFilter(
    NEXUS_IrInputHandle handle
    );
NEXUS_Error NEXUS_IrInput_SetDataFilter(
    NEXUS_IrInputHandle handle,
    const NEXUS_IrInputDataFilter *pPattern
    );
typedef struct NEXUS_InputClient *NEXUS_InputClientHandle;
typedef enum NEXUS_InputRouterDevice
{
    NEXUS_InputRouterDevice_eIrInput,
    NEXUS_InputRouterDevice_eUhfInput,
    NEXUS_InputRouterDevice_eKeypad,
    NEXUS_InputRouterDevice_ePointer,
    NEXUS_InputRouterDevice_eKeyboard,
    NEXUS_InputRouterDevice_eBluetoothRemote,
    NEXUS_InputRouterDevice_eEvdev,
    NEXUS_InputRouterDevice_eMax
} NEXUS_InputRouterDevice;
typedef struct NEXUS_InputRouterCode
{
    uint32_t filterMask;
    NEXUS_InputRouterDevice deviceType;
    union {
        struct {
            unsigned index;
            uint32_t code;
            _Bool repeat;
            unsigned mode;
            NEXUS_IrInputEvent event;
        } irInput;
        struct {
            unsigned tbd;
        } uhfInput;
        struct {
            unsigned index;
            uint32_t code;
            _Bool repeat;
        } keypad;
        struct {
            unsigned x, y;
            uint32_t button;
            _Bool down;
            signed wheel;
        } pointer;
        struct {
            unsigned code;
            _Bool down;
        } keyboard;
        struct {
            uint16_t type;
            uint16_t code;
            int32_t value;
        } evdev;
    } data;
} NEXUS_InputRouterCode;
NEXUS_InputClientHandle NEXUS_InputClient_Acquire(
    unsigned client_id
    );
void NEXUS_InputClient_Release(
    NEXUS_InputClientHandle client
    );
typedef struct NEXUS_InputClientSettings
{
    uint32_t filterMask;
    NEXUS_CallbackDesc codeAvailable;
} NEXUS_InputClientSettings;
void NEXUS_InputClient_GetSettings(
    NEXUS_InputClientHandle handle,
    NEXUS_InputClientSettings *pSettings
    );
NEXUS_Error NEXUS_InputClient_SetSettings(
    NEXUS_InputClientHandle handle,
    const NEXUS_InputClientSettings *pSettings
    );
NEXUS_Error NEXUS_InputClient_GetCodes(
    NEXUS_InputClientHandle handle,
    NEXUS_InputRouterCode *pCode,
    unsigned numEntries,
    unsigned *pNumReturned
    );
typedef struct NEXUS_InputClientStatus
{
    struct {
        uint32_t filterMask;
    } server;
} NEXUS_InputClientStatus;
NEXUS_Error NEXUS_InputClient_GetStatus(
    NEXUS_InputClientHandle handle,
    NEXUS_InputClientStatus *pStatus
    );
typedef struct NEXUS_InputRouter *NEXUS_InputRouterHandle;
NEXUS_InputRouterHandle NEXUS_InputRouter_Create(
    unsigned server_id
    );
void NEXUS_InputRouter_Destroy(
    NEXUS_InputRouterHandle handle
    );
NEXUS_InputClientHandle NEXUS_InputRouter_CreateClient(
    NEXUS_InputRouterHandle handle,
    unsigned client_id
    );
void NEXUS_InputRouter_DestroyClient(
    NEXUS_InputClientHandle client
    );
typedef struct NEXUS_InputRouterClientSettings
{
    unsigned fifoSize;
    uint32_t filterMask;
    NEXUS_Rect position;
} NEXUS_InputRouterClientSettings;
void NEXUS_InputRouter_GetClientSettings(
    NEXUS_InputRouterHandle handle,
    NEXUS_InputClientHandle client,
    NEXUS_InputRouterClientSettings *pSettings
    );
NEXUS_Error NEXUS_InputRouter_SetClientSettings(
    NEXUS_InputRouterHandle handle,
    NEXUS_InputClientHandle client,
    const NEXUS_InputRouterClientSettings *pSettings
    );
void NEXUS_InputRouter_GetDefaultCode(
    NEXUS_InputRouterCode *pCode
    );
void NEXUS_InputRouter_SendCode(
    NEXUS_InputRouterHandle handle,
    const NEXUS_InputRouterCode *pCode
    );
void NEXUS_InputRouter_SendClientCode(
    NEXUS_InputRouterHandle handle,
    NEXUS_InputClientHandle client,
    const NEXUS_InputRouterCode *pCode
    );
typedef struct NEXUS_InputRouterModuleSettings
{
    NEXUS_CommonModuleSettings common;
} NEXUS_InputRouterModuleSettings;
void NEXUS_InputRouterModule_GetDefaultSettings(
    NEXUS_InputRouterModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_InputRouterModule_Init(
    const NEXUS_InputRouterModuleSettings *pSettings
    );
void NEXUS_InputRouterModule_Uninit(void);
NEXUS_Error NEXUS_IrInput_InsertEvents(
    unsigned index,
    const NEXUS_IrInputEvent *pEvents,
    size_t numEvents
    );
typedef struct NEXUS_IrBlaster *NEXUS_IrBlasterHandle;
typedef enum NEXUS_IrBlasterMode
{
    NEXUS_IrBlasterMode_eSony,
    NEXUS_IrBlasterMode_eGI,
    NEXUS_IrBlasterMode_ePioneer,
    NEXUS_IrBlasterMode_ePioneerAAAA,
    NEXUS_IrBlasterMode_eCustom,
    NEXUS_IrBlasterMode_eXmp2,
    NEXUS_IrBlasterMode_eRC6,
    NEXUS_IrBlasterMode_eMax
} NEXUS_IrBlasterMode;
typedef struct NEXUS_IrBlasterSettings
{
    NEXUS_CallbackDesc transmitComplete;
    NEXUS_IrBlasterMode mode;
} NEXUS_IrBlasterSettings;
void NEXUS_IrBlaster_GetDefaultSettings(
    NEXUS_IrBlasterSettings *pSettings
    );
NEXUS_IrBlasterHandle NEXUS_IrBlaster_Open(
    unsigned index,
    const NEXUS_IrBlasterSettings *pSettings
    );
void NEXUS_IrBlaster_Close(
    NEXUS_IrBlasterHandle handle
    );
void NEXUS_IrBlaster_GetSettings(
    NEXUS_IrBlasterHandle irBlaster,
    NEXUS_IrBlasterSettings *pSettings
    );
NEXUS_Error NEXUS_IrBlaster_SetSettings(
    NEXUS_IrBlasterHandle irBlaster,
    const NEXUS_IrBlasterSettings *pSettings
    );
typedef struct NEXUS_IrBlasterStatus
{
    _Bool busy;
} NEXUS_IrBlasterStatus;
NEXUS_Error NEXUS_IrBlaster_GetStatus(
    NEXUS_IrBlasterHandle handle,
    NEXUS_IrBlasterStatus *pStatus
    );
NEXUS_Error NEXUS_IrBlaster_Send(
    NEXUS_IrBlasterHandle handle,
    const uint32_t *pData,
    uint8_t numBits,
    _Bool headerPulse
    );
NEXUS_Error NEXUS_IrBlaster_SendRC6(
    NEXUS_IrBlasterHandle handle,
    const uint32_t *pData,
    uint8_t numBits,
    uint8_t mode,
    uint8_t trailer
    );
NEXUS_Error NEXUS_IrBlaster_SendABBB(
    NEXUS_IrBlasterHandle handle,
    const uint32_t *pDataA,
    uint8_t numBitsA,
    const uint32_t *pDataB,
    uint8_t numBitsB,
    _Bool headerPulseA,
    _Bool headerPulseB,
    _Bool fixedFrameLength
    );
NEXUS_Error NEXUS_IrBlaster_SendAAAA(
    NEXUS_IrBlasterHandle handle,
    const uint32_t *pDataA,
    uint8_t numBitsA,
    _Bool headerPulse,
    _Bool fixedFrameLength
    );
NEXUS_Error NEXUS_IrBlaster_Abort(
    NEXUS_IrBlasterHandle handle
    );
NEXUS_Error NEXUS_IrBlaster_Resend(
    NEXUS_IrBlasterHandle handle
    );
NEXUS_Error NEXUS_IrBlaster_SendXmp2Ack(
    NEXUS_IrBlasterHandle irBlaster
    );
NEXUS_Error NEXUS_IrBlaster_SendXmp2Nack(
    NEXUS_IrBlasterHandle irBlaster
    );
NEXUS_Error NEXUS_IrBlaster_SendXmp2Bytes(
    NEXUS_IrBlasterHandle irBlaster,
    const uint8_t *pData,
    unsigned numBytes
    );
typedef struct NEXUS_IrBlasterIndexPair
{
    uint16_t on;
    uint16_t off;
} NEXUS_IrBlasterIndexPair;
typedef struct NEXUS_IrBlasterCustomSettings
{
    unsigned reserved;
    uint8_t masterClockDivisor;
    uint8_t carrierClockDivisor;
    uint8_t indexClockDivisor;
    uint8_t noCarrier;
    uint8_t carrierHighCount;
    uint8_t carrierLowCount;
    uint8_t numberSequences;
    NEXUS_IrBlasterIndexPair logic0IndexPair;
    NEXUS_IrBlasterIndexPair logic1IndexPair;
    NEXUS_IrBlasterIndexPair sequenceIndex[161];
    uint32_t duration[14];
    uint32_t framePeriod;
    uint32_t framePeriodB;
    uint16_t lastSequenceOffIndex;
    uint8_t repeatCount;
    uint8_t repeatStartIndex;
} NEXUS_IrBlasterCustomSettings;
void NEXUS_IrBlaster_GetDefaultCustomSettings(
    NEXUS_IrBlasterCustomSettings *pSettings
    );
NEXUS_Error NEXUS_IrBlaster_SetCustomSettings(
    NEXUS_IrBlasterHandle irBlaster,
    const NEXUS_IrBlasterCustomSettings *pSettings
    );
typedef struct NEXUS_IrBlasterModuleSettings
{
    int dummy;
} NEXUS_IrBlasterModuleSettings;
void NEXUS_IrBlasterModule_GetDefaultSettings(
    NEXUS_IrBlasterModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_IrBlasterModule_Init(
    const NEXUS_IrBlasterModuleSettings *pSettings
    );
void NEXUS_IrBlasterModule_Uninit(void);
typedef struct NEXUS_IrInputModuleSettings
{
    NEXUS_CommonModuleSettings common;
} NEXUS_IrInputModuleSettings;
void NEXUS_IrInputModule_GetDefaultSettings(
    NEXUS_IrInputModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_IrInputModule_Init(
    const NEXUS_IrInputModuleSettings *pSettings
    );
void NEXUS_IrInputModule_Uninit(void);
typedef struct NEXUS_Keypad *NEXUS_KeypadHandle;
typedef struct NEXUS_KeypadSettings
{
    unsigned repeatFilterTime;
    unsigned eventQueueSize;
    NEXUS_CallbackDesc dataReady;
    uint32_t prescale;
    uint8_t debounce;
    uint16_t keyMask;
} NEXUS_KeypadSettings;
void NEXUS_Keypad_GetDefaultSettings(
    NEXUS_KeypadSettings *pSettings
    );
NEXUS_KeypadHandle NEXUS_Keypad_Open(
    unsigned index,
    const NEXUS_KeypadSettings *pSettings
    );
void NEXUS_Keypad_Close(
    NEXUS_KeypadHandle handle
    );
typedef struct NEXUS_KeypadEvent
{
    _Bool repeat;
    uint16_t code;
} NEXUS_KeypadEvent;
NEXUS_Error NEXUS_Keypad_GetEvents(
    NEXUS_KeypadHandle handle,
    NEXUS_KeypadEvent *pEvents,
    size_t numEvents,
    size_t *pNumEventsRead,
    _Bool *pOverflow
    );
void NEXUS_Keypad_FlushEvents(
    NEXUS_KeypadHandle handle
    );
typedef struct NEXUS_KeypadModuleSettings
{
    NEXUS_CommonModuleSettings common;
    struct {
        _Bool valid;
        unsigned index;
    } spi;
    struct {
        _Bool valid;
        unsigned type;
        unsigned pin;
    } gpio;
} NEXUS_KeypadModuleSettings;
void NEXUS_KeypadModule_GetDefaultSettings(
    NEXUS_KeypadModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_KeypadModule_Init(
    const NEXUS_KeypadModuleSettings *pSettings
    );
void NEXUS_KeypadModule_Uninit(void);
typedef struct NEXUS_Led *NEXUS_LedHandle;
typedef struct NEXUS_LedSettings
{
    unsigned brightness;
    _Bool scrollingEnabled;
    _Bool alwaysScroll;
    unsigned scrollDelay;
} NEXUS_LedSettings;
typedef enum NEXUS_LedDigit
{
    NEXUS_LedDigit_e1 = 1,
    NEXUS_LedDigit_e2,
    NEXUS_LedDigit_e3,
    NEXUS_LedDigit_e4,
    NEXUS_LedDigit_eMax
} NEXUS_LedDigit;
typedef enum NEXUS_LedSegment
{
    NEXUS_LedSegment_eTop = 0x01,
    NEXUS_LedSegment_eUpperRight = 0x02,
    NEXUS_LedSegment_eLowerRight = 0x04,
    NEXUS_LedSegment_eBottom = 0x08,
    NEXUS_LedSegment_eLowerLeft = 0x10,
    NEXUS_LedSegment_eUpperLeft = 0x20,
    NEXUS_LedSegment_eMiddle = 0x40,
    NEXUS_LedSegment_eDot = 0x80,
    NEXUS_LedSegment_eMax
} NEXUS_LedSegment;
void NEXUS_Led_GetDefaultSettings(
    NEXUS_LedSettings *pSettings
    );
NEXUS_LedHandle NEXUS_Led_Open(
    unsigned index,
    const NEXUS_LedSettings *pSettings
    );
void NEXUS_Led_Close(
    NEXUS_LedHandle handle
    );
void NEXUS_Led_GetSettings(
    NEXUS_LedHandle handle,
    NEXUS_LedSettings *pSettings
    );
NEXUS_Error NEXUS_Led_SetSettings(
    NEXUS_LedHandle handle,
    const NEXUS_LedSettings *pSettings
    );
NEXUS_Error NEXUS_Led_WriteString(
    NEXUS_LedHandle handle,
    const char *pString,
    unsigned length
    );
typedef struct NEXUS_LedString
{
    char data[128];
} NEXUS_LedString;
NEXUS_Error NEXUS_Led_WriteString_driver(
    NEXUS_LedHandle handle,
    const NEXUS_LedString *pString
    );
NEXUS_Error NEXUS_Led_WriteSegments(
    NEXUS_LedHandle handle,
    NEXUS_LedDigit digit,
    uint16_t value
    );
NEXUS_Error NEXUS_Led_SetDot(
    NEXUS_LedHandle handle,
    unsigned dotIndex,
    _Bool enabled
    );
NEXUS_Error NEXUS_Led_SetLedState(
    NEXUS_LedHandle handle,
    unsigned ledNumber,
    _Bool active
    );
typedef enum NEXUS_LedClockDisplayMode
{
    NEXUS_LedClockDisplayMode_e12Hour,
    NEXUS_LedClockDisplayMode_e24Hour,
    NEXUS_LedClockDisplayMode_eMax
} NEXUS_LedClockDisplayMode;
typedef struct NEXUS_LedStartClockSettings
{
    unsigned hour;
    unsigned min;
    unsigned sec;
    NEXUS_LedClockDisplayMode displayMode;
} NEXUS_LedStartClockSettings;
void NEXUS_Led_GetDefaultStartClockSettings(
    NEXUS_LedStartClockSettings *pSettings
    );
NEXUS_Error NEXUS_Led_StartClock(
    NEXUS_LedHandle led,
    const NEXUS_LedStartClockSettings *pSettings
    );
void NEXUS_Led_StopClock(
    NEXUS_LedHandle led
    );
typedef struct NEXUS_LedModuleSettings {
    struct {
        _Bool valid;
        unsigned index;
    } spi;
} NEXUS_LedModuleSettings;
void NEXUS_LedModule_GetDefaultSettings(
    NEXUS_LedModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_LedModule_Init(
    const NEXUS_LedModuleSettings *pSettings
    );
void NEXUS_LedModule_Uninit(void);
typedef struct NEXUS_Message *NEXUS_MessageHandle;
typedef struct NEXUS_MessageSettings
{
    unsigned bufferSize;
    unsigned maxContiguousMessageSize;
   unsigned recpumpIndex;
    NEXUS_CallbackDesc dataReady;
    NEXUS_CallbackDesc overflow;
    NEXUS_CallbackDesc psiLengthError;
    NEXUS_CallbackDesc crcError;
    NEXUS_CallbackDesc pesLengthError;
    NEXUS_CallbackDesc pesStartCodeError;
} NEXUS_MessageSettings;
typedef enum NEXUS_MessageFormat
{
    NEXUS_MessageFormat_ePsi,
    NEXUS_MessageFormat_ePes,
    NEXUS_MessageFormat_ePesSaveAll,
    NEXUS_MessageFormat_eTs,
    NEXUS_MessageFormat_eMax
} NEXUS_MessageFormat;
typedef enum NEXUS_MessageBufferMode
{
    NEXUS_MessageBufferMode_eOneMessage,
    NEXUS_MessageBufferMode_eOneBuffer,
    NEXUS_MessageBufferMode_eContinuous,
    NEXUS_MessageBufferMode_eMax
} NEXUS_MessageBufferMode;
typedef enum NEXUS_DssMessageType
{
    NEXUS_DssMessageType_eAuxOnlyPackets,
    NEXUS_DssMessageType_eMpt,
    NEXUS_DssMessageType_eRegular,
    NEXUS_DssMessageType_eRegularCapFilter0,
    NEXUS_DssMessageType_eRegularCapFilter1,
    NEXUS_DssMessageType_eRegularCapFilter2,
    NEXUS_DssMessageType_eRegularCapFilter3,
    NEXUS_DssMessageType_eRegularCapFilter4,
    NEXUS_DssMessageType_eMax
} NEXUS_DssMessageType;
typedef enum NEXUS_DssMessageMptFlags
{
    NEXUS_DssMessageMptFlags_eSaveNone,
    NEXUS_DssMessageMptFlags_eSaveFirst,
    NEXUS_DssMessageMptFlags_eSaveAll,
    NEXUS_DssMessageMptFlags_eMax
} NEXUS_DssMessageMptFlags;
typedef struct NEXUS_MessageFilter
{
    uint8_t mask[16];
    uint8_t coefficient[16];
    uint8_t exclusion[16];
} NEXUS_MessageFilter;
void NEXUS_Message_GetDefaultSettings(
    NEXUS_MessageSettings *pSettings
    );
NEXUS_MessageHandle NEXUS_Message_Open(
    const NEXUS_MessageSettings *pSettings
    );
void NEXUS_Message_Close(
    NEXUS_MessageHandle handle
    );
void NEXUS_Message_GetSettings(
    NEXUS_MessageHandle handle,
    NEXUS_MessageSettings *pSettings
    );
NEXUS_Error NEXUS_Message_SetSettings(
    NEXUS_MessageHandle handle,
    const NEXUS_MessageSettings *pSettings
    );
typedef struct NEXUS_MessageStartSettings
{
    NEXUS_PidChannelHandle pidChannel;
    NEXUS_MessageFormat format;
    NEXUS_MessageBufferMode bufferMode;
    int bank;
    NEXUS_MessageFilter filter;
    _Bool filterGroup;
    _Bool psiCrcDisabled;
    _Bool psfCrcDisabled;
    void *buffer;
    unsigned bufferSize;
    NEXUS_DssMessageType dssMessageType;
    NEXUS_DssMessageMptFlags dssMessageMptFlags;
    _Bool useRPipe;
    unsigned filterOffset;
    _Bool includeThirdFilterByte;
} NEXUS_MessageStartSettings;
void NEXUS_Message_GetDefaultStartSettings(
    NEXUS_MessageHandle handle,
    NEXUS_MessageStartSettings *pStartSettings
    );
NEXUS_Error NEXUS_Message_Start(
    NEXUS_MessageHandle handle,
    const NEXUS_MessageStartSettings *pStartSettings
    );
void NEXUS_Message_GetDefaultFilter(
    NEXUS_MessageFilter *pFilter
    );
NEXUS_Error NEXUS_Message_AddFilter(
    NEXUS_MessageHandle handle,
    const NEXUS_MessageFilter *pFilter,
    unsigned *pFilterNum
    );
NEXUS_Error NEXUS_Message_RemoveFilter(
    NEXUS_MessageHandle handle,
    unsigned filterNum
    );
NEXUS_Error NEXUS_Message_UpdateFilter(
    NEXUS_MessageHandle handle,
    unsigned filterNum,
    const NEXUS_MessageFilter *pFilter
    );
void NEXUS_Message_Stop(
    NEXUS_MessageHandle handle
    );
NEXUS_Error NEXUS_Message_GetBuffer(
    NEXUS_MessageHandle handle,
    const void **pBuffer,
    size_t *pLength
    );
NEXUS_Error NEXUS_Message_GetBufferWithWrap(
    NEXUS_MessageHandle handle,
    const void **pBuffer,
    size_t *pLength,
    const void **pBuffer2,
    size_t *pLength2
    );
NEXUS_Error NEXUS_Message_ReadComplete(
    NEXUS_MessageHandle handle,
    size_t amountConsumed
    );
typedef struct NEXUS_MessageStatus
{
    unsigned groupMembers;
    _Bool isGroupMaster;
    _Bool moreDataAvailable;
} NEXUS_MessageStatus;
NEXUS_Error NEXUS_Message_GetStatus(
    NEXUS_MessageHandle handle,
    NEXUS_MessageStatus *pStatus
    );
NEXUS_Error NEXUS_Message_SetDssCapPattern(
    unsigned capFilterIndex,
    uint32_t pattern
    );
typedef struct NEXUS_MessageSamM40Address
{
    _Bool wildcardByteMode;
    _Bool wildcardEnabled;
    uint8_t addressWildcard;
    uint8_t address[5];
} NEXUS_MessageSamM40Address;
typedef struct NEXUS_MessageSamAddresses
{
    uint8_t physicalAddress[5];
    NEXUS_MessageSamM40Address type0NetworkAddress;
    NEXUS_MessageSamM40Address type1NetworkAddress;
    NEXUS_MessageSamM40Address type0M40Address;
    NEXUS_MessageSamM40Address type1M40Address;
    uint8_t m24Address[3];
    uint8_t idRejectHighLimit;
    uint8_t idRejectLowLimit;
} NEXUS_MessageSamAddresses;
void NEXUS_Message_GetSamAddresses(
    NEXUS_MessageSamAddresses *pAddresses
    );
NEXUS_Error NEXUS_Message_SetSamAddresses(
    const NEXUS_MessageSamAddresses *pAddresses
    );
typedef struct NEXUS_MessageSamM16Address
{
    uint8_t address0[2];
    uint8_t address1[2];
    uint8_t address2[2];
    uint8_t address3[2];
} NEXUS_MessageSamM16Address;
void NEXUS_Message_GetSamM16Address(
    NEXUS_MessageHandle handle,
    NEXUS_MessageSamM16Address *pAddress
    );
NEXUS_Error NEXUS_Message_SetSamM16Address(
    NEXUS_MessageHandle handle,
    const NEXUS_MessageSamM16Address *pAddress
    );
typedef struct NEXUS_MessageSamSettings
{
    _Bool physicalEnabled;
    _Bool networkEnabled;
    _Bool m40Enabled;
    _Bool m24Enabled;
    _Bool m16Enabled;
    _Bool idRejectEnabled;
    _Bool specialNotEnabled;
} NEXUS_MessageSamSettings;
void NEXUS_Message_GetDefaultSamSettings(
    NEXUS_MessageSamSettings *pSettings
    );
NEXUS_Error NEXUS_Message_SetSamSettings(
    NEXUS_MessageHandle handle,
    const NEXUS_MessageSamSettings *pSettings
    );
NEXUS_VideoWindowHandle NEXUS_VideoWindow_OpenMosaic(
    NEXUS_VideoWindowHandle parentWindow,
    unsigned mosaicIndex
    );
typedef struct NEXUS_VideoWindowMosaicSettings
{
    struct {
        _Bool enabled;
        NEXUS_Rect clipRect;
        NEXUS_Rect clipBase;
    } backendMosaic;
} NEXUS_VideoWindowMosaicSettings;
void NEXUS_VideoWindow_GetMosaicSettings(
    NEXUS_VideoWindowHandle window,
    NEXUS_VideoWindowMosaicSettings *pSettings
    );
NEXUS_Error NEXUS_VideoWindow_SetMosaicSettings(
    NEXUS_VideoWindowHandle window,
    const NEXUS_VideoWindowMosaicSettings *pSettings
    );
typedef struct NEXUS_VideoDecoderOpenMosaicSettings
{
    NEXUS_VideoDecoderOpenSettings openSettings;
    unsigned maxWidth, maxHeight;
    struct {
        _Bool enabled;
        unsigned avdIndex;
    } linkedDevice;
} NEXUS_VideoDecoderOpenMosaicSettings;
void NEXUS_VideoDecoder_GetDefaultOpenMosaicSettings(
    NEXUS_VideoDecoderOpenMosaicSettings *pOpenSettings
    );
NEXUS_VideoDecoderHandle NEXUS_VideoDecoder_OpenMosaic(
    unsigned parentIndex,
    unsigned index,
    const NEXUS_VideoDecoderOpenMosaicSettings *pOpenSettings
    );
typedef struct NEXUS_VideoDecoderMosaicSettings
{
    unsigned maxWidth, maxHeight;
} NEXUS_VideoDecoderMosaicSettings;
void NEXUS_VideoDecoder_GetMosaicSettings(
    NEXUS_VideoDecoderHandle handle,
    NEXUS_VideoDecoderMosaicSettings *pSettings
    );
NEXUS_Error NEXUS_VideoDecoder_SetMosaicSettings(
    NEXUS_VideoDecoderHandle handle,
    const NEXUS_VideoDecoderMosaicSettings *pSettings
    );
typedef struct NEXUS_Playpump *NEXUS_PlaypumpHandle;
typedef struct NEXUS_PlaypumpOpenSettings
{
    size_t fifoSize;
    unsigned alignment;
    NEXUS_MemoryBlockHandle memory;
    unsigned memoryOffset;
    unsigned numDescriptors;
    _Bool streamMuxCompatible;
    _Bool dataNotCpuAccessible;
    NEXUS_HeapHandle heap;
    NEXUS_HeapHandle boundsHeap;
} NEXUS_PlaypumpOpenSettings;
void NEXUS_Playpump_GetDefaultOpenSettings(
    NEXUS_PlaypumpOpenSettings *pSettings
    );
NEXUS_PlaypumpHandle NEXUS_Playpump_Open(
    unsigned index,
    const NEXUS_PlaypumpOpenSettings *pSettings
    );
void NEXUS_Playpump_Close(
    NEXUS_PlaypumpHandle playpump
    );
typedef enum NEXUS_PlaypumpMode
{
    NEXUS_PlaypumpMode_eFifo,
    NEXUS_PlaypumpMode_eSegment,
    NEXUS_PlaypumpMode_eMax
} NEXUS_PlaypumpMode;
typedef struct NEXUS_PlaypumpSettings
{
    NEXUS_TransportType transportType;
    NEXUS_TransportType originalTransportType;
    _Bool continuityCountEnabled;
    NEXUS_PlaypumpMode mode;
    NEXUS_CallbackDesc dataCallback;
    NEXUS_CallbackDesc errorCallback;
    NEXUS_CallbackDesc ccError;
    NEXUS_CallbackDesc teiError;
    int playRate;
    NEXUS_DmaHandle securityDma;
    NEXUS_DmaDataFormat securityDmaDataFormat;
    NEXUS_KeySlotHandle securityContext;
    unsigned maxDataRate;
    _Bool blindSync;
    _Bool allPass;
    _Bool acceptNullPackets;
    _Bool dataNotCpuAccessible;
    struct {
        NEXUS_TransportTimestampType type;
        uint16_t pcrPacingPid;
        _Bool pacing;
        unsigned pacingMaxError;
        NEXUS_Timebase timebase;
        _Bool parityCheckDisable;
        _Bool pacingOffsetAdjustDisable;
        _Bool resetPacing;
        _Bool forceRestamping;
    } timestamp;
} NEXUS_PlaypumpSettings;
typedef struct NEXUS_PlaypumpOpenPidChannelSettings
{
    NEXUS_PidChannelSettings pidSettings;
    NEXUS_PidType pidType;
    _Bool allowTimestampReordering;
    union
    {
        struct
        {
            NEXUS_AudioCodec codec;
        } audio;
    } pidTypeSettings;
} NEXUS_PlaypumpOpenPidChannelSettings;
void NEXUS_Playpump_GetDefaultOpenPidChannelSettings(
    NEXUS_PlaypumpOpenPidChannelSettings *pSettings
    );
NEXUS_PidChannelHandle NEXUS_Playpump_OpenPidChannel(
    NEXUS_PlaypumpHandle playpump,
    unsigned pid,
    const NEXUS_PlaypumpOpenPidChannelSettings *pSettings
    );
NEXUS_Error NEXUS_Playpump_ClosePidChannel(
    NEXUS_PlaypumpHandle playpump,
    NEXUS_PidChannelHandle pidChannel
    );
void NEXUS_Playpump_CloseAllPidChannels(
    NEXUS_PlaypumpHandle playpump
    );
void NEXUS_Playpump_GetDefaultSettings(
    NEXUS_PlaypumpSettings *pSettings
    );
void NEXUS_Playpump_GetSettings(
    NEXUS_PlaypumpHandle playpump,
    NEXUS_PlaypumpSettings *pSettings
    );
NEXUS_Error NEXUS_Playpump_SetSettings(
    NEXUS_PlaypumpHandle playpump,
    const NEXUS_PlaypumpSettings *pSettings
    );
NEXUS_Error NEXUS_Playpump_Start(
    NEXUS_PlaypumpHandle playpump
    );
void NEXUS_Playpump_Stop(
    NEXUS_PlaypumpHandle playpump
    );
NEXUS_Error NEXUS_Playpump_Flush(
    NEXUS_PlaypumpHandle playpump
    );
NEXUS_Error NEXUS_Playpump_GetBuffer(
    NEXUS_PlaypumpHandle playpump,
    void **pBuffer,
    size_t *pSize
    );
NEXUS_Error NEXUS_Playpump_WriteComplete(
    NEXUS_PlaypumpHandle playpump,
    size_t skip,
    size_t amountUsed
    );
typedef struct NEXUS_PlaypumpScatterGatherDescriptor
{
    void *addr;
    size_t length;
} NEXUS_PlaypumpScatterGatherDescriptor;
NEXUS_Error NEXUS_Playpump_SubmitScatterGatherDescriptor(
    NEXUS_PlaypumpHandle playpump,
    const NEXUS_PlaypumpScatterGatherDescriptor *pDesc,
    size_t numDescriptors,
    size_t *pNumConsumed
    );
typedef struct NEXUS_PlaypumpStatus
{
    _Bool started;
    size_t fifoDepth;
    size_t fifoSize;
    size_t descFifoDepth;
    size_t descFifoSize;
    void *bufferBase;
    uint64_t bytesPlayed;
    unsigned index;
    unsigned pacingTsRangeError;
    unsigned syncErrors;
    unsigned resyncEvents;
    unsigned streamErrors;
    NEXUS_PtsType mediaPtsType;
    uint32_t mediaPts;
} NEXUS_PlaypumpStatus;
NEXUS_Error NEXUS_Playpump_GetStatus(
    NEXUS_PlaypumpHandle playpump,
    NEXUS_PlaypumpStatus *pStatus
    );
typedef struct NEXUS_PlaypumpSegment
{
    uint32_t length;
    uint64_t offset;
    uint32_t timestamp;
    struct {
        uint16_t stream_id;
        int16_t timestamp_delta;
    } timestamp_delta[9];
    uint32_t signature;
} NEXUS_PlaypumpSegment;
NEXUS_Error NEXUS_Playpump_SetPause(
    NEXUS_PlaypumpHandle playpump,
    _Bool paused
    );
NEXUS_Error NEXUS_Playpump_SuspendPacing(
    NEXUS_PlaypumpHandle playpump,
    _Bool suspended
    );
NEXUS_Error NEXUS_Playpump_GetAllPassPidChannelIndex(
    NEXUS_PlaypumpHandle playpump,
    unsigned *pHwPidChannel
    );
void NEXUS_Playpump_IsTransportTypeSupported(
    NEXUS_PlaypumpHandle playpump,
    NEXUS_TransportType transportType,
    _Bool *pIsSupported
    );
NEXUS_Error NEXUS_Playpump_GetMpodLtsid(
    NEXUS_PlaypumpHandle playpump,
    unsigned *pLtsid
    );
typedef struct NEXUS_TransportCapabilities
{
    unsigned numInputBands;
    unsigned numParserBands;
    unsigned numPidChannels;
    unsigned numMessageCapablePidChannels;
    unsigned numPlaypumps;
    unsigned numRecpumps;
    unsigned numTpitPids;
    unsigned numPacketSubs;
    unsigned numStcs;
    unsigned numStcChannels;
    unsigned numTimebases;
    unsigned numRemux;
    _Bool packetizer;
    _Bool vobRemap;
    uint32_t stcPrescaleMax;
    uint32_t stcIncMax;
} NEXUS_TransportCapabilities;
void NEXUS_GetTransportCapabilities(
    NEXUS_TransportCapabilities *pCapabilities
    );
typedef struct NEXUS_TransportStatus
{
    struct {
        unsigned totalContexts;
        unsigned totalContextsUsed;
        struct {
            unsigned firmware;
            unsigned firmwareCrc;
        } version;
    } rave;
} NEXUS_TransportStatus;
void NEXUS_GetTransportStatus(
    NEXUS_TransportStatus *pStatus
    );
typedef struct NEXUS_TransportModuleSettings {
    NEXUS_CommonModuleSettings common;
    _Bool dssSaveMptFlag;
    _Bool initVcxos;
    struct {
        unsigned idleEventTimeout;
        unsigned recordEventTimeout;
    } tpit;
    struct {
        unsigned parserBand[24];
        unsigned playback[32];
    } maxDataRate;
    struct {
        _Bool enabled;
        unsigned rxInterfaceWidth;
    } mtsif[4];
    struct {
        struct {
            _Bool rave;
            _Bool message;
            _Bool remux[2];
            _Bool mpodRs;
        } parserBand[24];
        struct {
            _Bool rave;
            _Bool message;
            _Bool remux[2];
        } playback[32];
    } clientEnabled;
    unsigned syncInCount;
    unsigned syncOutCount;
} NEXUS_TransportModuleSettings;
typedef enum NEXUS_RemuxClock
{
    NEXUS_RemuxClock_e81Mhz,
    NEXUS_RemuxClock_e54Mhz,
    NEXUS_RemuxClock_e40_5Mhz,
    NEXUS_RemuxClock_e20_25Mhz,
    NEXUS_RemuxClock_e27Mhz_VCXO_A,
    NEXUS_RemuxClock_eInputBand,
    NEXUS_RemuxClock_eMax
} NEXUS_RemuxClock;
typedef struct NEXUS_RemuxSettings
{
    NEXUS_RemuxClock outputClock;
    NEXUS_InputBand remuxClockIBSrc;
    _Bool parallelOutput;
    _Bool invertClock;
    _Bool invertSync;
    _Bool byteSync;
    _Bool insertNullPackets;
    unsigned packetDelayCount;
    _Bool allPass;
    _Bool bypass;
    _Bool pcrCorrectionEnabled;
    uint32_t pcrCorrectionOffset;
    _Bool pacing;
    unsigned pacingMaxError;
    unsigned maxDataRate;
    _Bool enablePcrJitterAdjust;
    _Bool paused;
} NEXUS_RemuxSettings;
typedef struct NEXUS_RemuxParserBandwidth
{
    NEXUS_PlaypumpHandle playpump;
    NEXUS_ParserBand parserBand;
    unsigned maxDataRate;
}NEXUS_RemuxParserBandwidth;
void NEXUS_Remux_GetDefaultSettings(
    NEXUS_RemuxSettings *pSettings
    );
NEXUS_RemuxHandle NEXUS_Remux_Open(
    unsigned index,
    const NEXUS_RemuxSettings *pSettings
    );
void NEXUS_Remux_Close(
    NEXUS_RemuxHandle handle
    );
void NEXUS_Remux_GetDefaultParserBandwidth(
    NEXUS_RemuxParserBandwidth *pSettings
    );
NEXUS_Error NEXUS_Remux_SetParserBandwidth(
    NEXUS_RemuxHandle handle,
    const NEXUS_RemuxParserBandwidth *pSettings
    );
NEXUS_Error NEXUS_Remux_AddPidChannel(
    NEXUS_RemuxHandle handle,
    NEXUS_PidChannelHandle pidChannel
    );
NEXUS_Error NEXUS_Remux_RemovePidChannel(
    NEXUS_RemuxHandle handle,
    NEXUS_PidChannelHandle pidChannel
    );
void NEXUS_Remux_RemoveAllPidChannels(
    NEXUS_RemuxHandle handle
    );
NEXUS_Error NEXUS_Remux_Start(
    NEXUS_RemuxHandle handle
    );
void NEXUS_Remux_Stop(
    NEXUS_RemuxHandle handle
    );
NEXUS_Error NEXUS_Remux_SetSettings(
    NEXUS_RemuxHandle handle,
    const NEXUS_RemuxSettings *pSettings
    );
void NEXUS_Remux_GetSettings(
    NEXUS_RemuxHandle handle,
    NEXUS_RemuxSettings *pSettings
    );
typedef struct NEXUS_Tsmf *NEXUS_TsmfHandle;
typedef enum NEXUS_TsmfVersionChangeMode
{
    NEXUS_TsmfVersionChangeMode_eAllFrame,
    NEXUS_TsmfVersionChangeMode_eFrameChangeVer,
    NEXUS_TsmfVersionChangeMode_eMax
} NEXUS_TsmfVersionChangeMode;
typedef struct NEXUS_TsmfFieldVerifyConfig
{
    _Bool crcCheckDisable;
    _Bool relTsStatusCheckDisable;
    _Bool frameTypeCheckDisable;
    _Bool relTsModeCheckDisable;
    _Bool syncCheckDisable;
    _Bool ccCheckDisable;
    _Bool adapCheckDisable;
    _Bool scCheckDisable;
    _Bool tsPriorCheckDisable;
    _Bool pusiCheckDisable;
    _Bool teiCheckDisable;
    NEXUS_TsmfVersionChangeMode versionChangeMode;
} NEXUS_TsmfFieldVerifyConfig;
typedef enum NEXUS_TsmfSourceType
{
    NEXUS_TsmfSourceType_eInputBand,
    NEXUS_TsmfSourceType_eRemux,
    NEXUS_TsmfSourceType_eMtsif,
    NEXUS_TsmfSourceType_eMax
} NEXUS_TsmfSourceType;
typedef struct NEXUS_TsmfSettings
{
    NEXUS_TsmfSourceType sourceType;
    struct {
        NEXUS_InputBand inputBand;
        NEXUS_RemuxHandle remux;
        NEXUS_FrontendConnectorHandle mtsif;
    } sourceTypeSettings;
    _Bool enabled;
    NEXUS_TsmfFieldVerifyConfig fieldVerifyConfig;
    unsigned relativeTsNum;
    _Bool semiAutomaticMode;
    uint32_t slotMapLo;
    uint32_t slotMapHi;
} NEXUS_TsmfSettings;
typedef struct NEXUS_TsmfOpenSettings
{
    struct
    {
       _Bool enabled;
       unsigned playpumpIndex;
       unsigned parserbandIndex;
       unsigned recpumpIndex;
    } soft;
} NEXUS_TsmfOpenSettings;
void NEXUS_Tsmf_GetDefaultOpenSettings(
    NEXUS_TsmfOpenSettings *pOpenSettings
    );
typedef enum NEXUS_TsmfType
{
    NEXUS_TsmfType_eBackend,
    NEXUS_TsmfType_eFrontend,
    NEXUS_TsmfType_eMax
} NEXUS_TsmfType;
NEXUS_TsmfHandle NEXUS_Tsmf_Open(
    unsigned index,
    const NEXUS_TsmfOpenSettings* pOpenSettings
    );
void NEXUS_Tsmf_Close(
    NEXUS_TsmfHandle tsmf
    );
void NEXUS_Tsmf_GetSettings(
    NEXUS_TsmfHandle tsmf,
    NEXUS_TsmfSettings *pSettings
    );
NEXUS_Error NEXUS_Tsmf_SetSettings(
    NEXUS_TsmfHandle tsmf,
    const NEXUS_TsmfSettings *pSettings
    );
NEXUS_PidChannelHandle NEXUS_Tsmf_OpenPidChannel(
    NEXUS_TsmfHandle tsmf,
    unsigned pid,
    const NEXUS_PlaypumpOpenPidChannelSettings *pSettings
    );
typedef enum NEXUS_ParserBandSourceType
{
    NEXUS_ParserBandSourceType_eInputBand,
    NEXUS_ParserBandSourceType_eRemux,
    NEXUS_ParserBandSourceType_eMtsif,
    NEXUS_ParserBandSourceType_eTsmf,
    NEXUS_ParserBandSourceType_eMax
} NEXUS_ParserBandSourceType;
typedef struct NEXUS_ParserBandSettings
{
    NEXUS_ParserBandSourceType sourceType;
    struct
    {
        NEXUS_InputBand inputBand;
        NEXUS_RemuxHandle remux;
        NEXUS_FrontendConnectorHandle mtsif;
        NEXUS_TsmfHandle tsmf;
    } sourceTypeSettings;
    NEXUS_TransportType transportType;
    _Bool continuityCountEnabled;
    _Bool teiIgnoreEnabled;
    NEXUS_CableCardType cableCard;
    _Bool allPass;
    _Bool acceptNullPackets;
    unsigned maxDataRate;
    NEXUS_CallbackDesc ccError;
    NEXUS_CallbackDesc teiError;
    NEXUS_CallbackDesc lengthError;
    _Bool acceptAdapt00;
    _Bool forceRestamping;
} NEXUS_ParserBandSettings;
void NEXUS_ParserBand_GetSettings(
    NEXUS_ParserBand parserBand,
    NEXUS_ParserBandSettings *pSettings
    );
NEXUS_Error NEXUS_ParserBand_SetSettings(
    NEXUS_ParserBand parserBand,
    const NEXUS_ParserBandSettings *pSettings
    );
NEXUS_ParserBand NEXUS_ParserBand_Open(
    unsigned index
    );
void NEXUS_ParserBand_Close(
    NEXUS_ParserBand parserBand
    );
typedef struct NEXUS_ParserBandStatus
{
    struct {
        unsigned overflowErrors;
    } rsBufferStatus;
    unsigned index;
} NEXUS_ParserBandStatus;
NEXUS_Error NEXUS_ParserBand_GetStatus(
    NEXUS_ParserBand parserBand,
    NEXUS_ParserBandStatus *pStatus
    );
NEXUS_Error NEXUS_ParserBand_GetAllPassPidChannelIndex(
    NEXUS_ParserBand parserBand,
    unsigned *pHwPidChannel
    );
typedef struct NEXUS_Mpod *NEXUS_MpodHandle;
typedef struct NEXUS_MpodInput *NEXUS_MpodInputHandle;
typedef enum NEXUS_MpodMode
{
    NEXUS_MpodMode_eSpod,
    NEXUS_MpodMode_eMpod,
    NEXUS_MpodMode_eMax
} NEXUS_MpodMode;
typedef enum NEXUS_MpodBandType
{
    NEXUS_MpodBandType_eParserBand,
    NEXUS_MpodBandType_ePlaypump,
    NEXUS_MpodBandType_eMax
} NEXUS_MpodBandType;
typedef struct NEXUS_MpodOpenSettings
{
    NEXUS_MpodMode mpodMode;
    _Bool enableBandAssociation;
    NEXUS_MpodBandType bandType;
    struct
    {
        NEXUS_ParserBand parserBand;
        NEXUS_PlaypumpHandle playpump;
    } band;
    _Bool timestampInsertEnable;
    _Bool byteSync;
    _Bool clockNotRunning;
    _Bool invertClock;
    unsigned clockDelay;
    _Bool outputInvertSync;
    _Bool pod2ChipMClkMuxSelect;
    unsigned outputPacketDelay;
} NEXUS_MpodOpenSettings;
typedef struct NEXUS_MpodInputSettings
{
    NEXUS_MpodBandType bandType;
    struct
    {
        NEXUS_PlaypumpHandle playpump;
        NEXUS_ParserBand parserBand;
    } band;
    _Bool allPass;
    _Bool mpodPreFilter;
} NEXUS_MpodInputSettings;
void NEXUS_Mpod_GetDefaultOpenSettings(
    NEXUS_MpodOpenSettings* pOpenSettings
    );
NEXUS_MpodHandle NEXUS_Mpod_Open(
    unsigned int index,
    const NEXUS_MpodOpenSettings *pOpenSettings
    );
void NEXUS_Mpod_Close(
    NEXUS_MpodHandle mpod
    );
void NEXUS_MpodInput_GetDefaultSettings(
    NEXUS_MpodInputSettings *pMpodInputSettings
    );
NEXUS_MpodInputHandle NEXUS_MpodInput_Open(
    NEXUS_MpodHandle mpod,
    const NEXUS_MpodInputSettings *pMpodInputSettings
    );
void NEXUS_MpodInput_Close(
    NEXUS_MpodInputHandle mpod
    );
void NEXUS_MpodInput_GetSettings(
    NEXUS_MpodInputHandle mpodInput,
    NEXUS_MpodInputSettings *pMpodInputSettings
    );
NEXUS_Error NEXUS_MpodInput_SetSettings(
    NEXUS_MpodInputHandle mpodInput,
    const NEXUS_MpodInputSettings *pMpodInputSettings
    );
typedef enum NEXUS_OtpMspCmdProgMode
{
    NEXUS_OtpMspCmdProgMode_eEnum = 0x10112,
    NEXUS_OtpMspCmdProgMode_eEnumHal = 0x34,
    NEXUS_OtpMspCmdProgMode_eBit = 0x78
} NEXUS_OtpMspCmdProgMode;
typedef enum NEXUS_OtpCmdMsp
{
    NEXUS_OtpCmdMsp_eReserved0 = 0,
    NEXUS_OtpCmdMsp_eReserved1 = 1,
    NEXUS_OtpCmdMsp_eReserved2 = 2,
    NEXUS_OtpCmdMsp_eReserved3 = 3,
    NEXUS_OtpCmdMsp_eReserved4 = 4,
    NEXUS_OtpCmdMsp_eCrLockEnable = 5,
    NEXUS_OtpCmdMsp_eCrDisable = 6,
    NEXUS_OtpCmdMsp_ePcie0HostProtect = 7,
    NEXUS_OtpCmdMsp_ePcie0ClientProtect = 8,
    NEXUS_OtpCmdMsp_ePcie1HostProtect = 9,
    NEXUS_OtpCmdMsp_ePcie1ClientProtect = 10,
    NEXUS_OtpCmdMsp_eReserved11 = 11,
    NEXUS_OtpCmdMsp_eReserved12 = 12,
    NEXUS_OtpCmdMsp_eReserved13 = 13,
    NEXUS_OtpCmdMsp_eReserved14 = 14,
    NEXUS_OtpCmdMsp_eReserved15 = 15,
    NEXUS_OtpCmdMsp_eReserved16 = 16,
    NEXUS_OtpCmdMsp_eReserved17 = 17,
    NEXUS_OtpCmdMsp_eForceDramScrambler = 18,
    NEXUS_OtpCmdMsp_eReserved19 = 19,
    NEXUS_OtpCmdMsp_eReserved20 = 20,
    NEXUS_OtpCmdMsp_eReserved21 = 21,
    NEXUS_OtpCmdMsp_eReserved22 = 22,
    NEXUS_OtpCmdMsp_eReserved23 = 23,
    NEXUS_OtpCmdMsp_eReserved24 = 24,
    NEXUS_OtpCmdMsp_eReserved25 = 25,
    NEXUS_OtpCmdMsp_eReserved26 = 26,
    NEXUS_OtpCmdMsp_eReserved27 = 27,
    NEXUS_OtpCmdMsp_eReserved28 = 28,
    NEXUS_OtpCmdMsp_eReserved29 = 29,
    NEXUS_OtpCmdMsp_eReserved30 = 30,
    NEXUS_OtpCmdMsp_eReserved31 = 31,
    NEXUS_OtpCmdMsp_eReserved32 = 32,
    NEXUS_OtpCmdMsp_eReserved33 = 33,
    NEXUS_OtpCmdMsp_eReserved34 = 34,
    NEXUS_OtpCmdMsp_eDataSectionLockByte = 35,
    NEXUS_OtpCmdMsp_eDataSectionReadProtectBits = 36,
    NEXUS_OtpCmdMsp_eDestinationDisallowKeyA = 37,
    NEXUS_OtpCmdMsp_eDestinationDisallowKeyB = 38,
    NEXUS_OtpCmdMsp_eDestinationDisallowKeyC = 39,
    NEXUS_OtpCmdMsp_eReserved40 = 40,
    NEXUS_OtpCmdMsp_eReserved41 = 41,
    NEXUS_OtpCmdMsp_eReserved42 = 42,
    NEXUS_OtpCmdMsp_eAskmStbOwnerId = 43,
    NEXUS_OtpCmdMsp_eReserved44 = 44,
    NEXUS_OtpCmdMsp_eCaControlBits = 45,
    NEXUS_OtpCmdMsp_eCpControlBits = 46,
    NEXUS_OtpCmdMsp_eCaKeyLadderDisable = 47,
    NEXUS_OtpCmdMsp_eCpKeyLadderDisable = 48,
    NEXUS_OtpCmdMsp_eCustKeytoCaKeyLadderDisable = 49,
    NEXUS_OtpCmdMsp_eCustKeytoCpKeyLadderDisable = 50,
    NEXUS_OtpCmdMsp_eReserved51 = 51,
    NEXUS_OtpCmdMsp_eReserved52 = 52,
    NEXUS_OtpCmdMsp_eReserved53 = 53,
    NEXUS_OtpCmdMsp_eReserved54 = 54,
    NEXUS_OtpCmdMsp_eReserved55 = 55,
    NEXUS_OtpCmdMsp_eReserved56 = 56,
    NEXUS_OtpCmdMsp_eReserved57 = 57,
    NEXUS_OtpCmdMsp_eRouted3DesKeyK1K2CheckEnable = 58,
    NEXUS_OtpCmdMsp_eCaSoftwareKeyDisable = 59,
    NEXUS_OtpCmdMsp_eCpAesEcbMscSoftwareKeyDisable = 60,
    NEXUS_OtpCmdMsp_eCpM2mDesSoftwareKeyDisable = 61,
    NEXUS_OtpCmdMsp_eCpM2m3DesSoftwareKeyDisable = 62,
    NEXUS_OtpCmdMsp_eCpM2mAesSoftwareKeyDisable = 63,
    NEXUS_OtpCmdMsp_eCpM2mAesCounterSoftwareKeyDisable = 64,
    NEXUS_OtpCmdMsp_eM2mC2CssSoftwareKeyDisable = 65,
    NEXUS_OtpCmdMsp_eM2mM6SoftwareKeyDisable = 66,
    NEXUS_OtpCmdMsp_eReserved67 = 67,
    NEXUS_OtpCmdMsp_eReserved68 = 68,
    NEXUS_OtpCmdMsp_eReserved69 = 69,
    NEXUS_OtpCmdMsp_eReserved70 = 70,
    NEXUS_OtpCmdMsp_eReserved71 = 71,
    NEXUS_OtpCmdMsp_eAskmCAVendorIdSelect = 72,
    NEXUS_OtpCmdMsp_ePublicKey0Index = 73,
    NEXUS_OtpCmdMsp_eSecureBootEnable = 74,
    NEXUS_OtpCmdMsp_eReserved75 = 75,
    NEXUS_OtpCmdMsp_eRaagaAVerifyEnable = 76,
    NEXUS_OtpCmdMsp_eVideoVerifyEnable = 77,
    NEXUS_OtpCmdMsp_eRaveVerifyEnable = 78,
    NEXUS_OtpCmdMsp_eHostBootCodeHideEnable = 79,
    NEXUS_OtpCmdMsp_eHostBootCodeDecryptionSelect = 80,
    NEXUS_OtpCmdMsp_eReserved81 = 81,
    NEXUS_OtpCmdMsp_eReserved82 = 82,
    NEXUS_OtpCmdMsp_eReserved83 = 83,
    NEXUS_OtpCmdMsp_eReserved84 = 84,
    NEXUS_OtpCmdMsp_eReserved85 = 85,
    NEXUS_OtpCmdMsp_eReserved86 = 86,
    NEXUS_OtpCmdMsp_eSystemEpoch0 = 87,
    NEXUS_OtpCmdMsp_eReserved88 = 88,
    NEXUS_OtpCmdMsp_eBseckEnable = 89,
    NEXUS_OtpCmdMsp_eReserved90 = 90,
    NEXUS_OtpCmdMsp_eReserved91 = 91,
    NEXUS_OtpCmdMsp_eReserved92 = 92,
    NEXUS_OtpCmdMsp_eReserved93 = 93,
    NEXUS_OtpCmdMsp_eMarketId0 = 94,
    NEXUS_OtpCmdMsp_eReserved95 = 95,
    NEXUS_OtpCmdMsp_eReserved96 = 96,
    NEXUS_OtpCmdMsp_eReserved97 = 97,
    NEXUS_OtpCmdMsp_eReserved98 = 98,
    NEXUS_OtpCmdMsp_eReserved99 = 99,
    NEXUS_OtpCmdMsp_eReserved100 = 100,
    NEXUS_OtpCmdMsp_eReserved101 = 101,
    NEXUS_OtpCmdMsp_eReserved102 = 102,
    NEXUS_OtpCmdMsp_eReserved103 = 103,
    NEXUS_OtpCmdMsp_eReserved104 = 104,
    NEXUS_OtpCmdMsp_eReserved105 = 105,
    NEXUS_OtpCmdMsp_eReserved106 = 106,
    NEXUS_OtpCmdMsp_eReserved107 = 107,
    NEXUS_OtpCmdMsp_eReserved108 = 108,
    NEXUS_OtpCmdMsp_eReserved109 = 109,
    NEXUS_OtpCmdMsp_eReserved110 = 110,
    NEXUS_OtpCmdMsp_eReserved111 = 111,
    NEXUS_OtpCmdMsp_eReserved112 = 112,
    NEXUS_OtpCmdMsp_eReserved113 = 113,
    NEXUS_OtpCmdMsp_eReserved114 = 114,
    NEXUS_OtpCmdMsp_eReserved115 = 115,
    NEXUS_OtpCmdMsp_eReserved116 = 116,
    NEXUS_OtpCmdMsp_eReserved117 = 117,
    NEXUS_OtpCmdMsp_eReserved118 = 118,
    NEXUS_OtpCmdMsp_eReserved119 = 119,
    NEXUS_OtpCmdMsp_eReserved120 = 120,
    NEXUS_OtpCmdMsp_eReserved121 = 121,
    NEXUS_OtpCmdMsp_eReserved122 = 122,
    NEXUS_OtpCmdMsp_eReserved123 = 123,
    NEXUS_OtpCmdMsp_eReserved124 = 124,
    NEXUS_OtpCmdMsp_eReserved125 = 125,
    NEXUS_OtpCmdMsp_eReserved126 = 126,
    NEXUS_OtpCmdMsp_eReserved127 = 127,
    NEXUS_OtpCmdMsp_eReserved128 = 128,
    NEXUS_OtpCmdMsp_eReserved129 = 129,
    NEXUS_OtpCmdMsp_eReserved130 = 130,
    NEXUS_OtpCmdMsp_eViceVerifyEnable = 131,
    NEXUS_OtpCmdMsp_eReserved132 = 132,
    NEXUS_OtpCmdMsp_ePcieGwinDisable = 133,
    NEXUS_OtpCmdMsp_ePcie0MwinDisable = 134,
    NEXUS_OtpCmdMsp_ePcie0MwinRestrictEnable = 135,
    NEXUS_OtpCmdMsp_ePcie1MwinDisable = 136,
    NEXUS_OtpCmdMsp_ePcie1MwinRestrictEnable = 137,
    NEXUS_OtpCmdMsp_eCaAesEcbMscSoftwareKeyDisable = 138,
    NEXUS_OtpCmdMsp_eReserved139 = 139,
    NEXUS_OtpCmdMsp_eReserved140 = 140,
    NEXUS_OtpCmdMsp_eReserved141 = 141,
    NEXUS_OtpCmdMsp_eSidVerifyEnable = 142,
    NEXUS_OtpCmdMsp_eReserved143 = 143,
    NEXUS_OtpCmdMsp_eReserved144 = 144,
    NEXUS_OtpCmdMsp_eReserved145 = 145,
    NEXUS_OtpCmdMsp_eCpMulti2EcbCbcSoftwareKeyDisable = 146,
    NEXUS_OtpCmdMsp_eReserved147 = 147,
    NEXUS_OtpCmdMsp_eReserved148 = 148,
    NEXUS_OtpCmdMsp_eReserved149 = 149,
    NEXUS_OtpCmdMsp_eReserved150 = 150,
    NEXUS_OtpCmdMsp_eReserved151 = 151,
    NEXUS_OtpCmdMsp_eReserved152 = 152,
    NEXUS_OtpCmdMsp_eMMCBootDisable = 153,
    NEXUS_OtpCmdMsp_eReserved154 = 154,
    NEXUS_OtpCmdMsp_eReserved155 = 155,
    NEXUS_OtpCmdMsp_eEbiCsSwapDisable = 156,
    NEXUS_OtpCmdMsp_eReserved157 = 157,
    NEXUS_OtpCmdMsp_eReserved158 = 158,
    NEXUS_OtpCmdMsp_eReserved159 = 159,
    NEXUS_OtpCmdMsp_eReserved160 = 160,
    NEXUS_OtpCmdMsp_eReserved161 = 161,
    NEXUS_OtpCmdMsp_eReserved162 = 162,
    NEXUS_OtpCmdMsp_eTwoStageCaKeyLadderDisable = 163,
    NEXUS_OtpCmdMsp_eTwoStageCpKeyLadderDisable = 164,
    NEXUS_OtpCmdMsp_eReserved165 = 165,
    NEXUS_OtpCmdMsp_eReserved166 = 166,
    NEXUS_OtpCmdMsp_eReserved167 = 167,
    NEXUS_OtpCmdMsp_eReserved168 = 168,
    NEXUS_OtpCmdMsp_eReserved169 = 169,
    NEXUS_OtpCmdMsp_eReserved170 = 170,
    NEXUS_OtpCmdMsp_eReserved171 = 171,
    NEXUS_OtpCmdMsp_eReserved172 = 172,
    NEXUS_OtpCmdMsp_eReserved173 = 173,
    NEXUS_OtpCmdMsp_eReserved174 = 174,
    NEXUS_OtpCmdMsp_eReserved175 = 175,
    NEXUS_OtpCmdMsp_eReserved176 = 176,
    NEXUS_OtpCmdMsp_eReserved177 = 177,
    NEXUS_OtpCmdMsp_eReserved178 = 178,
    NEXUS_OtpCmdMsp_eReserved179 = 179,
    NEXUS_OtpCmdMsp_eReserved180 = 180,
    NEXUS_OtpCmdMsp_eReserved181 = 181,
    NEXUS_OtpCmdMsp_eReserved182 = 182,
    NEXUS_OtpCmdMsp_eReserved183 = 183,
    NEXUS_OtpCmdMsp_eReserved184 = 184,
    NEXUS_OtpCmdMsp_eReserved185 = 185,
    NEXUS_OtpCmdMsp_eReserved186 = 186,
    NEXUS_OtpCmdMsp_eReserved187 = 187,
    NEXUS_OtpCmdMsp_eReserved188 = 188,
    NEXUS_OtpCmdMsp_eReserved189 = 189,
    NEXUS_OtpCmdMsp_eDualCoreAcpuMode = 190,
    NEXUS_OtpCmdMsp_eSecureSandboxEnable = 191,
    NEXUS_OtpCmdMsp_eReserved192 = 192,
    NEXUS_OtpCmdMsp_eRaagaBVerifyEnable = 193,
    NEXUS_OtpCmdMsp_eReserved194 = 194,
    NEXUS_OtpCmdMsp_eExternalKeyTableDisable = 195,
    NEXUS_OtpCmdMsp_eReserved196 = 196,
    NEXUS_OtpCmdMsp_eReserved197 = 197,
    NEXUS_OtpCmdMsp_eReserved198 = 198,
    NEXUS_OtpCmdMsp_eReserved199 = 199,
    NEXUS_OtpCmdMsp_eSecureRsa2Sha1TruncateDisable = 200,
    NEXUS_OtpCmdMsp_eReserved201 = 201,
    NEXUS_OtpCmdMsp_eReserved202 = 202,
    NEXUS_OtpCmdMsp_eReserved203 = 203,
    NEXUS_OtpCmdMsp_eReserved204 = 204,
    NEXUS_OtpCmdMsp_eReserved205 = 205,
    NEXUS_OtpCmdMsp_eReserved206 = 206,
    NEXUS_OtpCmdMsp_eReserved207 = 207,
    NEXUS_OtpCmdMsp_eReserved208 = 208,
    NEXUS_OtpCmdMsp_eReserved209 = 209,
    NEXUS_OtpCmdMsp_eReserved210 = 210,
    NEXUS_OtpCmdMsp_eReserved211 = 211,
    NEXUS_OtpCmdMsp_eReserved212 = 212,
    NEXUS_OtpCmdMsp_eReserved213 = 213,
    NEXUS_OtpCmdMsp_eReserved214 = 214,
    NEXUS_OtpCmdMsp_eReserved215 = 215,
    NEXUS_OtpCmdMsp_eReserved216 = 216,
    NEXUS_OtpCmdMsp_eAesCounterGenericModeDisable = 217,
    NEXUS_OtpCmdMsp_eCaCpAesCounterAsfModeDisable = 218,
    NEXUS_OtpCmdMsp_eAesCounterWmdrmNdModeDisable = 219,
    NEXUS_OtpCmdMsp_eCaCpAesCounterHdcp21ModeDisable = 220,
    NEXUS_OtpCmdMsp_eReserved221 = 221,
    NEXUS_OtpCmdMsp_eReserved222 = 222,
    NEXUS_OtpCmdMsp_eReserved223 = 223,
    NEXUS_OtpCmdMsp_eReserved224 = 224,
    NEXUS_OtpCmdMsp_eReserved225 = 225,
    NEXUS_OtpCmdMsp_e1DesHwKeyLadderDisable = 226,
    NEXUS_OtpCmdMsp_eRoutedHwKLCa3DesKeyK1K2CheckEnable = 227,
    NEXUS_OtpCmdMsp_eRoutedHwKLCp3DesKeyK1K2CheckEnable = 228,
    NEXUS_OtpCmdMsp_eRoutedHwKLNon3DesKeyK1K2checkEnable = 229,
    NEXUS_OtpCmdMsp_eReserved230 = 230,
    NEXUS_OtpCmdMsp_eReserved231 = 231,
    NEXUS_OtpCmdMsp_eReserved232 = 232,
    NEXUS_OtpCmdMsp_eReserved233 = 233,
    NEXUS_OtpCmdMsp_eReserved234 = 234,
    NEXUS_OtpCmdMsp_eCpAesGHddvdBlurayDisable = 235,
    NEXUS_OtpCmdMsp_eReserved236 = 236,
    NEXUS_OtpCmdMsp_eUnsignedRsaKeyKpkDecryptDisallow = 237,
    NEXUS_OtpCmdMsp_eAsymmetricCrLockEnable = 238,
    NEXUS_OtpCmdMsp_eReserved239 = 239,
    NEXUS_OtpCmdMsp_eReserved240 = 240,
    NEXUS_OtpCmdMsp_eReserved241 = 241,
    NEXUS_OtpCmdMsp_eReserved242 = 242,
    NEXUS_OtpCmdMsp_eReserved243 = 243,
    NEXUS_OtpCmdMsp_eReserved244 = 244,
    NEXUS_OtpCmdMsp_eCaDvbCsa3SoftwareKeyDisable = 245,
    NEXUS_OtpCmdMsp_eSizeCommonMSPs = 246,
    NEXUS_OtpCmdMsp_eReserved247_511 = 247,
    NEXUS_OtpCmdMsp_eReserved512 = 512,
    NEXUS_OtpCmdMsp_eReserved513 = 513,
    NEXUS_OtpCmdMsp_eReserved514 = 514,
    NEXUS_OtpCmdMsp_eReserved515 = 515,
    NEXUS_OtpCmdMsp_eReserved516 = 516,
    NEXUS_OtpCmdMsp_eReserved517 = 517,
    NEXUS_OtpCmdMsp_eSystemEpoch3 = 518,
    NEXUS_OtpCmdMsp_eSystemEpoch2 = 519,
    NEXUS_OtpCmdMsp_eSystemEpoch1 = 520,
    NEXUS_OtpCmdMsp_eReserved521 = 521,
    NEXUS_OtpCmdMsp_eReserved522 = 522,
    NEXUS_OtpCmdMsp_eReserved523 = 523,
    NEXUS_OtpCmdMsp_eReserved524 = 524,
    NEXUS_OtpCmdMsp_eReserved525 = 525,
    NEXUS_OtpCmdMsp_eReserved526 = 526,
    NEXUS_OtpCmdMsp_eReserved527 = 527,
    NEXUS_OtpCmdMsp_eReserved528 = 528,
    NEXUS_OtpCmdMsp_eDataSection1Lock = 529,
    NEXUS_OtpCmdMsp_eReserved530 = 530,
    NEXUS_OtpCmdMsp_eReserved531 = 531,
    NEXUS_OtpCmdMsp_eReserved532 = 532,
    NEXUS_OtpCmdMsp_eReserved533 = 533,
    NEXUS_OtpCmdMsp_eReserved534 = 534,
    NEXUS_OtpCmdMsp_eReserved535 = 535,
    NEXUS_OtpCmdMsp_eReserved536 = 536,
    NEXUS_OtpCmdMsp_eReserved537 = 537,
    NEXUS_OtpCmdMsp_eReserved538 = 538,
    NEXUS_OtpCmdMsp_eReserved539 = 539,
    NEXUS_OtpCmdMsp_eReserved540 = 540,
    NEXUS_OtpCmdMsp_eReserved541 = 541,
    NEXUS_OtpCmdMsp_eReserved542 = 542,
    NEXUS_OtpCmdMsp_eReserved543 = 543,
    NEXUS_OtpCmdMsp_eReserved544 = 544,
    NEXUS_OtpCmdMsp_eReserved545 = 545,
    NEXUS_OtpCmdMsp_eReserved546 = 546,
    NEXUS_OtpCmdMsp_eReserved547 = 547,
    NEXUS_OtpCmdMsp_eReserved548 = 548,
    NEXUS_OtpCmdMsp_eReserved549 = 549,
    NEXUS_OtpCmdMsp_eReserved550 = 550,
    NEXUS_OtpCmdMsp_eReserved551 = 551,
    NEXUS_OtpCmdMsp_eReserved552 = 552,
    NEXUS_OtpCmdMsp_eReserved553 = 553,
    NEXUS_OtpCmdMsp_eReserved554 = 554,
    NEXUS_OtpCmdMsp_eReserved555 = 555,
    NEXUS_OtpCmdMsp_eReserved556 = 556,
    NEXUS_OtpCmdMsp_eReserved557 = 557,
    NEXUS_OtpCmdMsp_eReserved558 = 558,
    NEXUS_OtpCmdMsp_eReserved559 = 559,
    NEXUS_OtpCmdMsp_eReserved560 = 560,
    NEXUS_OtpCmdMsp_eReserved561 = 561,
    NEXUS_OtpCmdMsp_eReserved562 = 562,
    NEXUS_OtpCmdMsp_eReserved563 = 563,
    NEXUS_OtpCmdMsp_eReserved564 = 564,
    NEXUS_OtpCmdMsp_eReserved565 = 565,
    NEXUS_OtpCmdMsp_eReserved566 = 566,
    NEXUS_OtpCmdMsp_eReserved567 = 567,
    NEXUS_OtpCmdMsp_eReserved568 = 568,
    NEXUS_OtpCmdMsp_eReserved569 = 569,
    NEXUS_OtpCmdMsp_eReserved570 = 570,
    NEXUS_OtpCmdMsp_eReserved571 = 571,
    NEXUS_OtpCmdMsp_eReserved572 = 572,
    NEXUS_OtpCmdMsp_eReserved573 = 573,
    NEXUS_OtpCmdMsp_eReserved574 = 574,
    NEXUS_OtpCmdMsp_eReserved575 = 575,
    NEXUS_OtpCmdMsp_eReserved576 = 576,
    NEXUS_OtpCmdMsp_eReserved577 = 577,
    NEXUS_OtpCmdMsp_eReserved578 = 578,
    NEXUS_OtpCmdMsp_eReserved579 = 579,
    NEXUS_OtpCmdMsp_eReserved580 = 580,
    NEXUS_OtpCmdMsp_eReserved581 = 581,
    NEXUS_OtpCmdMsp_eReserved582 = 582,
    NEXUS_OtpCmdMsp_eReserved583 = 583,
    NEXUS_OtpCmdMsp_eReserved584 = 584,
    NEXUS_OtpCmdMsp_eReserved585 = 585,
    NEXUS_OtpCmdMsp_eReserved586 = 586,
    NEXUS_OtpCmdMsp_eReserved587 = 587,
    NEXUS_OtpCmdMsp_eReserved588 = 588,
    NEXUS_OtpCmdMsp_eReserved589 = 589,
    NEXUS_OtpCmdMsp_eReserved590 = 590,
    NEXUS_OtpCmdMsp_eReserved591 = 591,
    NEXUS_OtpCmdMsp_eReserved592 = 592,
    NEXUS_OtpCmdMsp_eReserved593 = 593,
    NEXUS_OtpCmdMsp_eReserved594 = 594,
    NEXUS_OtpCmdMsp_eReserved595 = 595,
    NEXUS_OtpCmdMsp_eReserved596 = 596,
    NEXUS_OtpCmdMsp_eReserved597 = 597,
    NEXUS_OtpCmdMsp_eReserved598 = 598,
    NEXUS_OtpCmdMsp_eReserved599 = 599,
    NEXUS_OtpCmdMsp_eReserved600 = 600,
    NEXUS_OtpCmdMsp_eReserved601 = 601,
    NEXUS_OtpCmdMsp_eReserved602 = 602,
    NEXUS_OtpCmdMsp_eReserved603 = 603,
    NEXUS_OtpCmdMsp_eReserved604 = 604,
    NEXUS_OtpCmdMsp_eReserved605 = 605,
    NEXUS_OtpCmdMsp_eReserved606 = 606,
    NEXUS_OtpCmdMsp_eReserved607 = 607,
    NEXUS_OtpCmdMsp_eReserved608 = 608,
    NEXUS_OtpCmdMsp_eReserved609 = 609,
    NEXUS_OtpCmdMsp_eReserved610 = 610,
    NEXUS_OtpCmdMsp_eReserved611 = 611,
    NEXUS_OtpCmdMsp_eReserved612 = 612,
    NEXUS_OtpCmdMsp_eReserved613 = 613,
    NEXUS_OtpCmdMsp_eReserved614 = 614,
    NEXUS_OtpCmdMsp_eReserved615 = 615,
    NEXUS_OtpCmdMsp_eReserved616 = 616,
    NEXUS_OtpCmdMsp_eReserved617 = 617,
    NEXUS_OtpCmdMsp_eReserved618 = 618,
    NEXUS_OtpCmdMsp_eReserved619 = 619,
    NEXUS_OtpCmdMsp_eForceSCDisallow = 620,
    NEXUS_OtpCmdMsp_ePCIe0MwinSizeEnforceEnable = 621,
    NEXUS_OtpCmdMsp_ePCIe1MwinSizeEnforceEnable = 622,
    NEXUS_OtpCmdMsp_eKeyladderKeyContributionDisallow = 623,
    NEXUS_OtpCmdMsp_eKeyladderKeyContributionFeatureDisable = 624,
    NEXUS_OtpCmdMsp_eCaCpd1DES3DESCBCSoftwareKeyDisable = 625,
    NEXUS_OtpCmdMsp_eReserved626 = 626,
    NEXUS_OtpCmdMsp_eReserved627 = 627,
    NEXUS_OtpCmdMsp_eHostBootCodeDecryptExt = 628,
    NEXUS_OtpCmdMsp_eHvdFwEpoch = 629,
    NEXUS_OtpCmdMsp_eRaagaFwEpoch = 630,
    NEXUS_OtpCmdMsp_eViceFwEpoch = 631,
    NEXUS_OtpCmdMsp_eRaveFwEpoch = 632,
    NEXUS_OtpCmdMsp_eMarketId1 = 633,
    NEXUS_OtpCmdMsp_eArcType = 634,
    NEXUS_OtpCmdMsp_eKey0PrimeSigningRightsSDL = 635,
    NEXUS_OtpCmdMsp_eKey0SigningRightsSDL = 636,
    NEXUS_OtpCmdMsp_eSageGpBits_0 = 637,
    NEXUS_OtpCmdMsp_eSageGpBits_1 = 638,
    NEXUS_OtpCmdMsp_eMax,
    NEXUS_OtpCmdMsp_eReserved7 = NEXUS_OtpCmdMsp_ePcie0HostProtect,
    NEXUS_OtpCmdMsp_eReserved8 = NEXUS_OtpCmdMsp_ePcie0ClientProtect,
    NEXUS_OtpCmdMsp_ePcieHostProtect = NEXUS_OtpCmdMsp_ePcie1HostProtect,
    NEXUS_OtpCmdMsp_ePcieClientProtect = NEXUS_OtpCmdMsp_ePcie1ClientProtect,
    NEXUS_OtpCmdMsp_eCpM2MControlBits = NEXUS_OtpCmdMsp_eCpControlBits,
    NEXUS_OtpCmdMsp_eReserved76 = NEXUS_OtpCmdMsp_eRaagaAVerifyEnable,
    NEXUS_OtpCmdMsp_eReserved77 = NEXUS_OtpCmdMsp_eVideoVerifyEnable,
    NEXUS_OtpCmdMsp_eReserved78 = NEXUS_OtpCmdMsp_eRaveVerifyEnable,
    NEXUS_OtpCmdMsp_eSystemEpoch = NEXUS_OtpCmdMsp_eSystemEpoch0,
    NEXUS_OtpCmdMsp_eMarketId = NEXUS_OtpCmdMsp_eMarketId0,
    NEXUS_OtpCmdMsp_eReserved131 = NEXUS_OtpCmdMsp_eViceVerifyEnable,
    NEXUS_OtpCmdMsp_eReserved134 = NEXUS_OtpCmdMsp_ePcie0MwinDisable,
    NEXUS_OtpCmdMsp_eReserved135 = NEXUS_OtpCmdMsp_ePcie0MwinRestrictEnable,
    NEXUS_OtpCmdMsp_ePcieMwinDisable = NEXUS_OtpCmdMsp_ePcie1MwinDisable,
    NEXUS_OtpCmdMsp_ePcieMwinRestrictEnable = NEXUS_OtpCmdMsp_ePcie1MwinRestrictEnable,
    NEXUS_OtpCmdMsp_eReserved142 = NEXUS_OtpCmdMsp_eSidVerifyEnable,
    NEXUS_OtpCmdMsp_eReserved146 = NEXUS_OtpCmdMsp_eCpMulti2EcbCbcSoftwareKeyDisable,
    NEXUS_OtpCmdMsp_eReserved156 = NEXUS_OtpCmdMsp_eEbiCsSwapDisable,
    NEXUS_OtpCmdMsp_eReserved163 = NEXUS_OtpCmdMsp_eTwoStageCaKeyLadderDisable,
    NEXUS_OtpCmdMsp_eReserved164 = NEXUS_OtpCmdMsp_eTwoStageCpKeyLadderDisable,
    NEXUS_OtpCmdMsp_eReserved193 = NEXUS_OtpCmdMsp_eRaagaBVerifyEnable,
    NEXUS_OtpCmdMsp_eReserved217 = NEXUS_OtpCmdMsp_eAesCounterGenericModeDisable,
    NEXUS_OtpCmdMsp_eReserved218 = NEXUS_OtpCmdMsp_eCaCpAesCounterAsfModeDisable,
    NEXUS_OtpCmdMsp_eReserved219 = NEXUS_OtpCmdMsp_eAesCounterWmdrmNdModeDisable,
    NEXUS_OtpCmdMsp_eReserved220 = NEXUS_OtpCmdMsp_eCaCpAesCounterHdcp21ModeDisable,
    NEXUS_OtpCmdMsp_eReserved518 = NEXUS_OtpCmdMsp_eSystemEpoch3,
    NEXUS_OtpCmdMsp_eReserved519 = NEXUS_OtpCmdMsp_eSystemEpoch2,
    NEXUS_OtpCmdMsp_eReserved520 = NEXUS_OtpCmdMsp_eSystemEpoch1,
    NEXUS_OtpCmdMsp_eAltMarketId = NEXUS_OtpCmdMsp_eMarketId1,
    NEXUS_OtpCmdMsp_eReserved635 = NEXUS_OtpCmdMsp_eKey0PrimeSigningRightsSDL,
    NEXUS_OtpCmdMsp_eReserved636 = NEXUS_OtpCmdMsp_eKey0SigningRightsSDL
} NEXUS_OtpCmdMsp;
typedef enum NEXUS_OtpCmdReadRegister
{
    NEXUS_OtpCmdReadRegister_eMc0S_Reserved0 = 0,
    NEXUS_OtpCmdReadRegister_eMc0S_Reserved1 = 1,
    NEXUS_OtpCmdReadRegister_eMc0S_Reserved2 = 2,
    NEXUS_OtpCmdReadRegister_eMc0S_Reserved3 = 3,
    NEXUS_OtpCmdReadRegister_eMc0S_Reserved4 = 4,
    NEXUS_OtpCmdReadRegister_eMc0S_Reserved5 = 5,
    NEXUS_OtpCmdReadRegister_eKeyMc0_CustomerMode = 6,
    NEXUS_OtpCmdReadRegister_eKeyMc0_Reserved7 = 7,
    NEXUS_OtpCmdReadRegister_eKeyMc0_DeobfuscationEnable = 8,
    NEXUS_OtpCmdReadRegister_eKeyMc0_BlackBoxId = 9,
    NEXUS_OtpCmdReadRegister_eKeyMc0_CaKeyLadderDisallow = 10,
    NEXUS_OtpCmdReadRegister_eKeyMc0_CpKeyLadderDisallow = 11,
    NEXUS_OtpCmdReadRegister_eKeyMc0_Gp1KeyLadderDisallow = 12,
    NEXUS_OtpCmdReadRegister_eKeyMc0_Gp2KeyLadderDisallow = 13,
    NEXUS_OtpCmdReadRegister_eKeyMc0_Reserved14 = 14,
    NEXUS_OtpCmdReadRegister_eKeyID = 15,
    NEXUS_OtpCmdReadRegister_eKeyHash = 16,
    NEXUS_OtpCmdReadRegister_eBseckHashCrc = 17,
    NEXUS_OtpCmdReadRegister_eMc0S_Reserved18 = 18,
    NEXUS_OtpCmdReadRegister_eMc0S_FixedDeobfuscationVariantEnable = 19,
    NEXUS_OtpCmdReadRegister_eKeyMc0_RootKeySwapDisallow = 20,
    NEXUS_OtpCmdReadRegister_eKeyMc0_Reserved21 = 21,
    NEXUS_OtpCmdReadRegister_eMax
} NEXUS_OtpCmdReadRegister;
typedef enum NEXUS_OtpKeyType
{
    NEXUS_OtpKeyType_eA,
    NEXUS_OtpKeyType_eB,
    NEXUS_OtpKeyType_eC,
    NEXUS_OtpKeyType_eD,
    NEXUS_OtpKeyType_eE,
    NEXUS_OtpKeyType_eF,
    NEXUS_OtpKeyType_eG,
    NEXUS_OtpKeyType_eH,
    NEXUS_OtpKeyType_eSize
} NEXUS_OtpKeyType ;
typedef struct NEXUS_ReadOtpIO {
    unsigned char otpKeyIdBuf[8];
    unsigned int otpKeyIdSize;
} NEXUS_ReadOtpIO;
NEXUS_Error NEXUS_Security_ReadOTP(
    NEXUS_OtpCmdReadRegister readOtpEnum,
    NEXUS_OtpKeyType keyType,
    NEXUS_ReadOtpIO *pReadOtpIO
    );
typedef struct NEXUS_ProgramMspIO {
    NEXUS_OtpMspCmdProgMode progMode;
    NEXUS_OtpCmdMsp progMspEnum;
    unsigned char dataBitLen;
    unsigned char dataBitMask [4];
    unsigned char mspData[4];
} NEXUS_ProgramMspIO;
NEXUS_Error NEXUS_Security_ProgramMSP(
    const NEXUS_ProgramMspIO *pProgMspIO
    );
typedef struct NEXUS_ReadMspParms
{
    NEXUS_OtpCmdMsp readMspEnum;
} NEXUS_ReadMspParms;
typedef struct NEXUS_ReadMspIO {
    unsigned char mspDataBuf[4];
    unsigned char lockMspDataBuf[4];
    unsigned int mspDataSize;
} NEXUS_ReadMspIO;
NEXUS_Error NEXUS_Security_ReadMSP(
    const NEXUS_ReadMspParms *pReadMspParms,
    NEXUS_ReadMspIO *pReadMspIO
    );
typedef enum NEXUS_OtpDataSection
{
    NEXUS_OtpDataSection_e0 = 0x0,
    NEXUS_OtpDataSection_e1 = 0x1,
    NEXUS_OtpDataSection_e2 = 0x2,
    NEXUS_OtpDataSection_e3 = 0x3,
    NEXUS_OtpDataSection_e4 = 0x4,
    NEXUS_OtpDataSection_e5 = 0x5,
    NEXUS_OtpDataSection_e6 = 0x6,
    NEXUS_OtpDataSection_e7 = 0x7,
    NEXUS_OtpDataSection_eMax = 0x8
} NEXUS_OtpDataSection;
typedef struct NEXUS_ReadDataSectIO {
    unsigned char dataSectBuf[(32)];
    unsigned int dataSectSize;
    _Bool isShaOfData;
} NEXUS_ReadDataSectIO;
NEXUS_Error NEXUS_Security_ReadDataSect(
    NEXUS_OtpDataSection readDsEnum,
    NEXUS_ReadDataSectIO *pReadDataSectIO
    );
typedef struct NEXUS_ProgramDataSectIO {
    NEXUS_OtpDataSection progDsEnum;
    unsigned char dataSectData[(32)];
    unsigned char crc[4];
    uint32_t mode;
    uint32_t padding;
} NEXUS_ProgramDataSectIO;
NEXUS_Error NEXUS_Security_ProgramDataSect(
    const NEXUS_ProgramDataSectIO *pProgDataSectIO
    );
typedef struct NEXUS_PacketSub *NEXUS_PacketSubHandle;
typedef struct NEXUS_PacketSubOpenSettings
{
    unsigned fifoSize;
    NEXUS_HeapHandle heap;
    unsigned numDescriptors;
} NEXUS_PacketSubOpenSettings;
void NEXUS_PacketSub_GetDefaultOpenSettings(
    NEXUS_PacketSubOpenSettings *pSettings
    );
NEXUS_PacketSubHandle NEXUS_PacketSub_Open(
    unsigned index,
    const NEXUS_PacketSubOpenSettings *pSettings
    );
void NEXUS_PacketSub_Close(
    NEXUS_PacketSubHandle packetSub
    );
NEXUS_Error NEXUS_PacketSub_Start(
    NEXUS_PacketSubHandle packetSub
    );
void NEXUS_PacketSub_Stop(
    NEXUS_PacketSubHandle packetSub
    );
typedef struct NEXUS_PacketSubSettings
{
    NEXUS_PidChannelHandle pidChannel;
    _Bool highPriorityDma;
    _Bool forcedInsertion;
    _Bool fullRateOutput;
    unsigned outputRate;
    _Bool loop;
    NEXUS_CallbackDesc dataCallback;
    NEXUS_CallbackDesc finished;
} NEXUS_PacketSubSettings;
NEXUS_Error NEXUS_PacketSub_SetSettings(
    NEXUS_PacketSubHandle packetSub,
    const NEXUS_PacketSubSettings *pSettings
    );
void NEXUS_PacketSub_GetSettings(
    NEXUS_PacketSubHandle packetSub,
    NEXUS_PacketSubSettings *pSettings
    );
typedef struct NEXUS_PacketSubStatus
{
    _Bool finished;
    _Bool busy;
} NEXUS_PacketSubStatus;
NEXUS_Error NEXUS_PacketSub_GetStatus(
    NEXUS_PacketSubHandle packetSub,
    NEXUS_PacketSubStatus *pSettings
    );
NEXUS_Error NEXUS_PacketSub_SetPause(
    NEXUS_PacketSubHandle packetSub,
    _Bool paused
    );
NEXUS_Error NEXUS_PacketSub_GetBuffer(
    NEXUS_PacketSubHandle packetSub,
    void **pBuffer,
    unsigned *pSize
    );
NEXUS_Error NEXUS_PacketSub_WriteComplete(
    NEXUS_PacketSubHandle packetSub,
    unsigned amount
    );
NEXUS_Error NEXUS_PacketSub_WriteCompleteWithSkip(
    NEXUS_PacketSubHandle packetSub,
    unsigned skip,
    unsigned amount
    );
void NEXUS_PacketSub_Flush(
    NEXUS_PacketSubHandle packetSub
    );
typedef struct NEXUS_ParserBandStartBondingGroupSettings
{
    unsigned bondingPid;
    struct {
        unsigned playpumpIndex;
        NEXUS_Timebase timebase;
        unsigned pcrPid;
    } soft;
    NEXUS_ParserBand slave[24];
} NEXUS_ParserBandStartBondingGroupSettings;
void NEXUS_ParserBand_GetDefaultStartBondingGroupSettings(
    NEXUS_ParserBandStartBondingGroupSettings *pSettings
    );
NEXUS_Error NEXUS_ParserBand_StartBondingGroup(
    NEXUS_ParserBand master,
    const NEXUS_ParserBandStartBondingGroupSettings *pSettings
    );
void NEXUS_ParserBand_StopBondingGroup(
    NEXUS_ParserBand master
    );
typedef struct NEXUS_ParserBandBondingGroupStatus
{
    _Bool locked;
} NEXUS_ParserBandBondingGroupStatus;
NEXUS_Error NEXUS_ParserBand_GetBondingGroupStatus(
    NEXUS_ParserBand master,
    NEXUS_ParserBandBondingGroupStatus *pStatus
    );
NEXUS_PlaypumpHandle NEXUS_ParserBand_GetBondingGroupPlaypump(
    NEXUS_ParserBand master
    );
void NEXUS_PictureCtrl_GetCommonSettings(
    NEXUS_VideoWindowHandle window,
    NEXUS_PictureCtrlCommonSettings *pSettings
    );
NEXUS_Error NEXUS_PictureCtrl_SetCommonSettings(
    NEXUS_VideoWindowHandle window,
    const NEXUS_PictureCtrlCommonSettings *pSettings
    );
void NEXUS_PictureCtrl_GetAdvColorSettings(
    NEXUS_VideoWindowHandle window,
    NEXUS_PictureCtrlAdvColorSettings *pSettings
    );
NEXUS_Error NEXUS_PictureCtrl_SetAdvColorSettings(
    NEXUS_VideoWindowHandle window,
    const NEXUS_PictureCtrlAdvColorSettings *pSettings
    );
void NEXUS_PictureCtrl_GetCmsSettings(
    NEXUS_VideoWindowHandle window,
    NEXUS_PictureCtrlCmsSettings *pSettings
    );
NEXUS_Error NEXUS_PictureCtrl_SetCmsSettings(
    NEXUS_VideoWindowHandle window,
    const NEXUS_PictureCtrlCmsSettings *pSettings
    );
void NEXUS_PictureCtrl_GetDitherSettings(
    NEXUS_VideoWindowHandle window,
    NEXUS_PictureCtrlDitherSettings *pSettings
    );
NEXUS_Error NEXUS_PictureCtrl_SetDitherSettings(
    NEXUS_VideoWindowHandle window,
    const NEXUS_PictureCtrlDitherSettings *pSettings
    );
void NEXUS_PictureCtrl_GetContrastStretch(
    NEXUS_VideoWindowHandle window,
    NEXUS_PictureCtrlContrastStretch *pContrast
    );
NEXUS_Error NEXUS_PictureCtrl_SetContrastStretch(
    NEXUS_VideoWindowHandle window,
    const NEXUS_PictureCtrlContrastStretch *pContrast
    );
NEXUS_Error NEXUS_PictureCtrl_SetCustomContrastStretch(
    NEXUS_VideoWindowHandle window,
    const NEXUS_PictureCtrlContrastStretch *pContrast,
    const int16_t *pTable,
    unsigned numTableEntries
    );
NEXUS_Error NEXUS_PictureCtrl_LoadCabTable(
    NEXUS_VideoWindowHandle window,
    const uint32_t *pTable,
    unsigned numTableEntries,
    unsigned offset
    );
NEXUS_Error NEXUS_PictureCtrl_LoadLabTable(
    NEXUS_VideoWindowHandle window,
    const uint32_t *pTable,
    unsigned numTableEntries,
    unsigned offset
    );
NEXUS_Error NEXUS_PictureCtrl_ConfigDisplayLumaStatistics(
    NEXUS_DisplayHandle display,
    const NEXUS_ClipRect *pRect
    );
NEXUS_Error NEXUS_PictureCtrl_GetDisplayLumaStatistics(
    NEXUS_DisplayHandle display,
    NEXUS_LumaStatistics *pLumaStat
    );
NEXUS_Error NEXUS_PictureCtrl_ConfigWindowLumaStatistics(
    NEXUS_VideoWindowHandle window,
    const NEXUS_ClipRect *pRect
    );
NEXUS_Error NEXUS_PictureCtrl_GetWindowLumaStatistics(
    NEXUS_VideoWindowHandle window,
    NEXUS_LumaStatistics *pLumaStat
    );
NEXUS_Error NEXUS_PictureCtrl_SetColorCorrectionTable(
    NEXUS_DisplayHandle display,
    const NEXUS_PictureControlColorCorrectionSettings *pSettings
    );
NEXUS_Error NEXUS_PictureCtrl_SetCustomColorCorrectionTable(
    NEXUS_DisplayHandle display,
    const uint32_t *pTable,
    unsigned numTableEntries
    );
void NEXUS_PictureCtrl_GetColorClipSettings(
    NEXUS_DisplayHandle display,
    NEXUS_PictureCtrlColorClipSettings *pSettings
    );
NEXUS_Error NEXUS_PictureCtrl_SetColorClipSettings(
    NEXUS_DisplayHandle display,
    const NEXUS_PictureCtrlColorClipSettings *pSettings
    );
typedef struct NEXUS_PictureDecoder *NEXUS_PictureDecoderHandle;
typedef enum NEXUS_PictureFormat {
    NEXUS_PictureFormat_eRleDvd,
    NEXUS_PictureFormat_eRleBluRay,
    NEXUS_PictureFormat_eJpeg,
    NEXUS_PictureFormat_ePng,
    NEXUS_PictureFormat_eGif,
    NEXUS_PictureFormat_eMpeg,
    NEXUS_PictureFormat_eMax
} NEXUS_PictureFormat;
typedef struct NEXUS_PictureDecoderOpenSettings
{
    struct {
        uint16_t maxWidth;
        uint8_t chromaVerticalShift;
        uint8_t chromaHorizontalShift;
    } jpeg;
    struct {
        uint16_t maxWidthRgb;
        uint16_t maxWidthPalette;
        uint16_t maxWidth16Bpp;
    } png;
    struct {
        uint16_t maxWidth;
    } gif;
    struct {
        uint16_t maxWidthDvd;
        uint16_t maxWidthBluRay;
    } rle;
    unsigned bufferSize;
    unsigned multiScanBufferSize;
    NEXUS_HeapHandle heap;
    void *bufferPtr;
    void *multiScanBufferPtr;
} NEXUS_PictureDecoderOpenSettings;
void NEXUS_PictureDecoder_GetDefaultOpenSettings(
    NEXUS_PictureDecoderOpenSettings *pSettings
    );
NEXUS_PictureDecoderHandle NEXUS_PictureDecoder_Open(
    unsigned index,
    const NEXUS_PictureDecoderOpenSettings *pSettings
    );
void NEXUS_PictureDecoder_Close(
    NEXUS_PictureDecoderHandle handle
    );
typedef struct NEXUS_PictureDecoderStartSettings
{
    NEXUS_PictureFormat format;
    NEXUS_CallbackDesc pictureParsed;
    NEXUS_CallbackDesc segmentDecoded;
    unsigned imageSize;
} NEXUS_PictureDecoderStartSettings;
void NEXUS_PictureDecoder_GetDefaultStartSettings(
    NEXUS_PictureDecoderStartSettings *pSettings
    );
NEXUS_Error NEXUS_PictureDecoder_Start(
    NEXUS_PictureDecoderHandle handle,
    const NEXUS_PictureDecoderStartSettings *pSettings
    );
NEXUS_Error NEXUS_PictureDecoder_DecodeSegment(
    NEXUS_PictureDecoderHandle handle,
    NEXUS_SurfaceHandle destination,
    const NEXUS_Rect *pSegment
    );
void NEXUS_PictureDecoder_Stop(
    NEXUS_PictureDecoderHandle handle
    );
NEXUS_Error NEXUS_PictureDecoder_GetBuffer(
    NEXUS_PictureDecoderHandle decoder,
    void **pBuffer,
    size_t *pSize
    );
NEXUS_Error NEXUS_PictureDecoder_ReadComplete(
    NEXUS_PictureDecoderHandle decoder,
    size_t skip,
    size_t amountUsed
    );
typedef enum NEXUS_PictureDecoderState {
    NEXUS_PictureDecoderState_eIdle,
    NEXUS_PictureDecoderState_eDecoding,
    NEXUS_PictureDecoderState_eSegmentDone,
    NEXUS_PictureDecoderState_eError,
    NEXUS_PictureDecoderState_eMoreData,
    NEXUS_PictureDecoderState_eMax
} NEXUS_PictureDecoderState;
typedef struct NEXUS_PictureDecoderPalette
{
    unsigned numPaletteEntries;
    NEXUS_Pixel palette[256];
} NEXUS_PictureDecoderPalette;
typedef struct NEXUS_PictureDecoderStatus
{
    NEXUS_PictureDecoderState state;
    _Bool headerValid;
    struct {
        uint16_t width;
        uint16_t height;
        NEXUS_Rect surface;
        NEXUS_PixelFormat format;
        _Bool multiscan;
        _Bool grayscale;
        _Bool palette;
        _Bool rotated;
        _Bool hasTransparentData;
        unsigned transparentColorIndex;
        uint32_t transparentColorRgb;
    } header;
    uint32_t crc;
    struct {
        unsigned firmware;
    } version;
} NEXUS_PictureDecoderStatus;
NEXUS_Error NEXUS_PictureDecoder_GetStatus(
    NEXUS_PictureDecoderHandle decoder,
    NEXUS_PictureDecoderStatus *pStatus
    );
NEXUS_Error NEXUS_PictureDecoder_GetPalette(
    NEXUS_PictureDecoderHandle decoder,
    NEXUS_PictureDecoderPalette *pPalette
    );
typedef struct NEXUS_PictureDecoderModuleSettings
{
    NEXUS_ModuleHandle surface;
    NEXUS_ModuleHandle transport;
    NEXUS_ModuleHandle security;
} NEXUS_PictureDecoderModuleSettings;
void NEXUS_PictureDecoderModule_GetDefaultSettings(
    NEXUS_PictureDecoderModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_PictureDecoderModule_Init(
    const NEXUS_PictureDecoderModuleSettings *pSettings
    );
void NEXUS_PictureDecoderModule_Uninit(void);
typedef struct NEXUS_PidChannelScramblingSettings
{
    _Bool pusiOnly;
    NEXUS_RaveHandle raveContext;
} NEXUS_PidChannelScramblingSettings;
void NEXUS_PidChannel_GetDefaultScramblingSettings(
    NEXUS_PidChannelScramblingSettings *pSettings
    );
NEXUS_Error NEXUS_PidChannel_StartScramblingCheck(
    NEXUS_PidChannelHandle pidChannel,
    const NEXUS_PidChannelScramblingSettings *pSettings
    );
void NEXUS_PidChannel_StopScramblingCheck(
    NEXUS_PidChannelHandle pidChannel
    );
typedef struct NEXUS_PidChannelScramblingStatus
{
    _Bool pidExists;
    _Bool scrambled;
} NEXUS_PidChannelScramblingStatus;
NEXUS_Error NEXUS_PidChannel_GetScramblingStatus(
    NEXUS_PidChannelHandle pidChannel,
    NEXUS_PidChannelScramblingStatus *pStatus
    );
void NEXUS_PidChannel_ClearScramblingStatus(
    NEXUS_PidChannelHandle pidChannel
    );
typedef struct NEXUS_ExternalInterruptSettings
{
    NEXUS_CallbackDesc callback;
} NEXUS_ExternalInterruptSettings;
void NEXUS_Platform_GetDefaultExternalInterruptSettings(
    NEXUS_ExternalInterruptSettings *pSettings
    );
NEXUS_Error NEXUS_Platform_EnableExternalInterrupt(
    unsigned interruptId,
    const NEXUS_ExternalInterruptSettings *pSettings
    );
void NEXUS_Platform_DisableExternalInterrupt(
    unsigned interruptId
    );
typedef struct NEXUS_PlatformObjectInstance {
    _Bool readOnly;
    NEXUS_AnyObject object;
} NEXUS_PlatformObjectInstance;
typedef struct NEXUS_InterfaceName {
    char name[32];
} NEXUS_InterfaceName;
void NEXUS_Platform_GetDefaultInterfaceName(
        NEXUS_InterfaceName *name
        );
typedef struct NEXUS_Client *NEXUS_ClientHandle;
NEXUS_Error NEXUS_Platform_GetClientObjects(
        NEXUS_ClientHandle client,
        const NEXUS_InterfaceName *pName,
        NEXUS_PlatformObjectInstance *pObjects,
        size_t nobjects,
        size_t *pValidObjects
        );
typedef enum NEXUS_PlatformStandbyMode
{
    NEXUS_PlatformStandbyMode_eOn,
    NEXUS_PlatformStandbyMode_eActive,
    NEXUS_PlatformStandbyMode_ePassive,
    NEXUS_PlatformStandbyMode_eDeepSleep,
    NEXUS_PlatformStandbyMode_eMax
} NEXUS_PlatformStandbyMode;
typedef struct NEXUS_PlatformStandbySettings
{
    NEXUS_PlatformStandbyMode mode;
    struct {
        _Bool ir;
        _Bool uhf;
        _Bool keypad;
        _Bool gpio;
        _Bool nmi;
        _Bool cec;
        _Bool transport;
        unsigned timeout;
    } wakeupSettings;
    _Bool openFrontend;
} NEXUS_PlatformStandbySettings;
typedef struct NEXUS_PlatformStandbyStatus
{
    struct {
        _Bool ir;
        _Bool uhf;
        _Bool keypad;
        _Bool gpio;
        _Bool nmi;
        _Bool cec;
        _Bool transport;
        _Bool timeout;
    } wakeupStatus;
} NEXUS_PlatformStandbyStatus;
void NEXUS_Platform_GetStandbySettings(
    NEXUS_PlatformStandbySettings *pSettings
    );
NEXUS_Error NEXUS_Platform_SetStandbySettings(
    const NEXUS_PlatformStandbySettings *pSettings
    );
NEXUS_Error NEXUS_Platform_SetStandbySettings_driver(
    const NEXUS_PlatformStandbySettings *pSettings
    );
NEXUS_Error NEXUS_Platform_GetStandbyStatus(
    NEXUS_PlatformStandbyStatus *pStatus
    );
NEXUS_Error NEXUS_Platform_GetStandbyStatus_driver(
    NEXUS_PlatformStandbyStatus *pStatus
    );
void NEXUS_Platform_GetDefaultStandbySettings(
    NEXUS_PlatformStandbySettings *pSettings
    );
NEXUS_Error NEXUS_Platform_InitStandby(
    const NEXUS_PlatformStandbySettings *pSettings
    );
void NEXUS_Platform_UninitStandby(void);
NEXUS_Error NEXUS_Platform_PreStandby(void);
NEXUS_Error NEXUS_Platform_PostStandby(void);
typedef struct NEXUS_MemoryConfigurationSettings
{
    NEXUS_VideoDecoderMemory videoDecoder[6];
    NEXUS_VideoDecoderMemory stillDecoder[3];
    NEXUS_DisplayMemConfig display[7];
    struct {
        _Bool hdDvi;
        _Bool ccir656;
    } videoInputs;
    NEXUS_VideoEncoderMemory videoEncoder[6];
    NEXUS_AudioModuleUsageSettings audio;
} NEXUS_MemoryConfigurationSettings;
typedef struct NEXUS_PlatformCapabilities
{
    struct {
        _Bool supported;
        _Bool encoder;
    } display[7];
    struct {
        _Bool supported;
        unsigned displayIndex;
    } videoEncoder[6];
    unsigned unused;
} NEXUS_PlatformCapabilities;
typedef struct NEXUS_SurfaceModuleSettings
{
    unsigned heapIndex;
    NEXUS_ModuleHandle core;
} NEXUS_SurfaceModuleSettings;
void NEXUS_SurfaceModule_GetDefaultSettings(
    NEXUS_SurfaceModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_SurfaceModule_Init(
    const NEXUS_SurfaceModuleSettings *pSettings
    );
void NEXUS_SurfaceModule_Uninit(void);
typedef struct NEXUS_TransportModuleInternalSettings
{
    NEXUS_ModuleHandle dma;
    NEXUS_ModuleHandle core;
    NEXUS_HeapHandle secureHeap;
    unsigned mainHeapIndex;
    _Bool postInitCalledBySecurity;
} NEXUS_TransportModuleInternalSettings;
void NEXUS_TransportModule_GetDefaultInternalSettings(
    NEXUS_TransportModuleInternalSettings *pSettings
    );
void NEXUS_TransportModule_GetDefaultSettings(
    NEXUS_TransportModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_TransportModule_PreInit(
    const NEXUS_TransportModuleInternalSettings *pModuleSettings,
    const NEXUS_TransportModuleSettings *pSettings
    );
void NEXUS_TransportModule_Uninit(void);
typedef struct NEXUS_SpdifOutput *NEXUS_SpdifOutputHandle;
typedef struct NEXUS_SpdifOutputSettings
{
    _Bool limitTo16Bits;
    _Bool dither;
    NEXUS_SpdifOutputBurstType burstType;
    NEXUS_AudioChannelStatusInfo channelStatusInfo;
} NEXUS_SpdifOutputSettings;
void NEXUS_SpdifOutput_GetDefaultSettings(
    NEXUS_SpdifOutputSettings *pSettings
    );
NEXUS_SpdifOutputHandle NEXUS_SpdifOutput_Open(
    unsigned index,
    const NEXUS_SpdifOutputSettings *pSettings
    );
void NEXUS_SpdifOutput_Close(
    NEXUS_SpdifOutputHandle handle
    );
void NEXUS_SpdifOutput_GetSettings(
    NEXUS_SpdifOutputHandle handle,
    NEXUS_SpdifOutputSettings *pSettings
    );
NEXUS_Error NEXUS_SpdifOutput_SetSettings(
    NEXUS_SpdifOutputHandle handle,
    const NEXUS_SpdifOutputSettings *pSettings
    );
NEXUS_AudioOutputHandle NEXUS_SpdifOutput_GetConnector(
    NEXUS_SpdifOutputHandle handle
    );
NEXUS_Error NEXUS_SpdifOutput_SetRawChannelStatus(
    NEXUS_SpdifOutputHandle handle,
    const NEXUS_AudioRawChannelStatus *pChannelStatus
    );
typedef struct NEXUS_VideoDecoderModuleInternalSettings
{
    NEXUS_ModuleHandle transport;
    NEXUS_HeapHandle secureHeap;
    NEXUS_ModuleHandle audio;
    NEXUS_ModuleHandle pictureDecoder;
    NEXUS_ModuleHandle core;
    NEXUS_ModuleHandle security;
    _Bool deferInit;
} NEXUS_VideoDecoderModuleInternalSettings;
void NEXUS_VideoDecoderModule_GetDefaultInternalSettings(
    NEXUS_VideoDecoderModuleInternalSettings *pSettings
    );
void NEXUS_VideoDecoderModule_GetDefaultSettings(
    NEXUS_VideoDecoderModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_VideoDecoderModule_Init(
    const NEXUS_VideoDecoderModuleInternalSettings *pModuleSettings,
    const NEXUS_VideoDecoderModuleSettings *pSettings
    );
void NEXUS_VideoDecoderModule_Uninit(void);
typedef struct NEXUS_SvideoOutput *NEXUS_SvideoOutputHandle;
typedef struct NEXUS_SvideoOutputSettings
{
    NEXUS_VideoDac dacY;
    NEXUS_VideoDac dacC;
} NEXUS_SvideoOutputSettings;
void NEXUS_SvideoOutput_GetDefaultSettings(
    NEXUS_SvideoOutputSettings *pSettings
    );
NEXUS_SvideoOutputHandle NEXUS_SvideoOutput_Open(
    unsigned index,
    const NEXUS_SvideoOutputSettings *pSettings
    );
void NEXUS_SvideoOutput_Close(
    NEXUS_SvideoOutputHandle output
    );
void NEXUS_SvideoOutput_GetSettings(
    NEXUS_SvideoOutputHandle output,
    NEXUS_SvideoOutputSettings *pSettings
    );
NEXUS_Error NEXUS_SvideoOutput_SetSettings(
    NEXUS_SvideoOutputHandle output,
    const NEXUS_SvideoOutputSettings *pSettings
    );
NEXUS_VideoOutputHandle NEXUS_SvideoOutput_GetConnector(
    NEXUS_SvideoOutputHandle output
    );
typedef struct NEXUS_Smartcard *NEXUS_SmartcardHandle;
typedef enum NEXUS_SmartcardState
{
    NEXUS_SmartcardState_eUnknown = 0,
    NEXUS_SmartcardState_eColdResetting,
    NEXUS_SmartcardState_eWarmResetting,
    NEXUS_SmartcardState_eResetDone,
    NEXUS_SmartcardState_eActivating,
    NEXUS_SmartcardState_eReceiveDecodeAtr,
    NEXUS_SmartcardState_eReady,
    NEXUS_SmartcardState_eTransmitting,
    NEXUS_SmartcardState_eTransmitted,
    NEXUS_SmartcardState_eReceiving,
    NEXUS_SmartcardState_eIgnore,
    NEXUS_SmartcardState_eInitialized,
    NEXUS_SmartcardState_eMax
} NEXUS_SmartcardState;
typedef struct NEXUS_SmartcardStatus
{
    _Bool cardPresent;
    NEXUS_SmartcardState state;
    unsigned iccClockFrequency;
} NEXUS_SmartcardStatus;
typedef enum NEXUS_SmartcardProtocol
{
    NEXUS_SmartcardProtocol_eUnknown,
    NEXUS_SmartcardProtocol_eT0,
    NEXUS_SmartcardProtocol_eT1,
    NEXUS_SmartcardProtocol_eT14,
    NEXUS_SmartcardProtocol_eMax
} NEXUS_SmartcardProtocol;
typedef enum NEXUS_SmartcardStandard
{
    NEXUS_SmartcardStandard_eUnknown,
    NEXUS_SmartcardStandard_eNds,
    NEXUS_SmartcardStandard_eIso,
    NEXUS_SmartcardStandard_eEmv1996,
    NEXUS_SmartcardStandard_eEmv2000,
    NEXUS_SmartcardStandard_eIrdeto,
    NEXUS_SmartcardStandard_eArib,
    NEXUS_SmartcardStandard_eMt,
    NEXUS_SmartcardStandard_eConax,
    NEXUS_SmartcardStandard_eEs,
    NEXUS_SmartcardStandard_eNdsNoFlowControl,
    NEXUS_SmartcardStandard_eNordig,
    NEXUS_SmartcardStandard_eMax
} NEXUS_SmartcardStandard;
typedef enum NEXUS_TimerUnit {
    NEXUS_TimerUnit_eEtu,
    NEXUS_TimerUnit_eClk,
    NEXUS_TimerUnit_eMilliSec,
    NEXUS_TimerUnit_eMax
} NEXUS_TimerUnit;
typedef struct NEXUS_TimerValue
{
    uint32_t value;
    NEXUS_TimerUnit unit;
} NEXUS_TimerValue;
typedef enum NEXUS_EdcEncode {
    NEXUS_EdcEncode_eLrd,
    NEXUS_EdcEncode_eCrc,
    NEXUS_EdcEncode_eMax
} NEXUS_EdcEncode;
typedef struct NEXUS_EdcSetting
{
    NEXUS_EdcEncode edcEncode;
    _Bool isEnabled;
} NEXUS_EdcSetting;
typedef enum NEXUS_ScPresMode {
    NEXUS_ScPresMode_eDebounce = 0,
    NEXUS_ScPresMode_eMask,
    NEXUS_ScPresMode_eMax
} NEXUS_ScPresMode;
typedef struct NEXUS_ScPresDbInfo
{
    NEXUS_ScPresMode scPresMode;
    _Bool isEnabled;
    uint8_t dbWidth;
} NEXUS_ScPresDbInfo;
typedef enum NEXUS_ResetCardAction
{
    NEXUS_ResetCardAction_eNoAction = 0,
    NEXUS_ResetCardAction_eReceiveAndDecode,
    NEXUS_ResetCardAction_eMax
} NEXUS_ResetCardAction;
typedef enum NEXUS_SmartcardPowerIcc {
    NEXUS_SmartcardPowerIcc_ePowerDown = 0,
    NEXUS_SmartcardPowerIcc_ePowerUp = 1,
    NEXUS_SmartcardPowerIcc_eMax
} NEXUS_SmartcardPowerIcc;
typedef enum NEXUS_SmartcardVcc {
    NEXUS_SmartcardVcc_e5V = 0,
    NEXUS_SmartcardVcc_e3V = 1,
    NEXUS_SmartcardVcc_eMax
} NEXUS_SmartcardVcc;
typedef enum NEXUS_SmartcardConnection {
    NEXUS_SmartcardConnection_eTda8024,
    NEXUS_SmartcardConnection_eTda8034,
    NEXUS_SmartcardConnection_eDirect,
    NEXUS_SmartcardConnection_eInternal,
    NEXUS_SmartcardConnection_eMax
} NEXUS_SmartcardConnection;
typedef struct NEXUS_SmartcardSettings
{
    NEXUS_SmartcardProtocol protocol;
    NEXUS_SmartcardStandard standard;
    uint8_t fFactor;
    uint8_t dFactor;
    uint8_t extClockDivisor;
    uint8_t txRetries;
    uint8_t rxRetries;
    uint8_t baudDiv;
    NEXUS_TimerValue workWaitTime;
    NEXUS_TimerValue blockWaitTime;
    NEXUS_TimerValue extraGuardTime;
    NEXUS_TimerValue blockGuardTime;
    uint32_t characterWaitTime;
    NEXUS_EdcSetting edcSetting;
    NEXUS_TimerValue timeOut;
    _Bool autoDeactiveReq;
    _Bool nullFilter;
    NEXUS_ScPresDbInfo scPresDbInfo;
    NEXUS_ResetCardAction resetCardAction;
    NEXUS_TimerValue blockWaitTimeExt;
    _Bool isPresHigh;
    NEXUS_CallbackDesc cardCallback;
    _Bool setPinmux;
    _Bool connectDirectly;
    NEXUS_SmartcardConnection connection;
    uint32_t currentIFSD;
    unsigned sourceClockFreq;
    NEXUS_TimerValue atrReceiveTime;
    unsigned resetCycles;
    _Bool setVcc;
    NEXUS_SmartcardVcc vcc;
    struct
    {
        _Bool vccInverted;
        _Bool resetInverted;
    } directPowerSupply;
} NEXUS_SmartcardSettings;
void NEXUS_Smartcard_GetDefaultSettings(
    NEXUS_SmartcardSettings *pSettings
    );
NEXUS_SmartcardHandle NEXUS_Smartcard_Open(
    unsigned index,
    const NEXUS_SmartcardSettings *pSettings
    );
void NEXUS_Smartcard_Close(
    NEXUS_SmartcardHandle handle
    );
void NEXUS_Smartcard_GetSettings(
    NEXUS_SmartcardHandle handle,
    NEXUS_SmartcardSettings *pSettings
    );
NEXUS_Error NEXUS_Smartcard_SetSettings(
    NEXUS_SmartcardHandle handle,
    const NEXUS_SmartcardSettings *pSettings
    );
NEXUS_Error NEXUS_Smartcard_Read(
    NEXUS_SmartcardHandle smartcard,
    void *pdata,
    size_t numBytes,
    size_t *pBytesRead
    );
NEXUS_Error NEXUS_Smartcard_Write(
    NEXUS_SmartcardHandle smartcard,
    const void *pData,
    size_t numBytes,
    size_t *pBytesWritten
    );
NEXUS_Error NEXUS_Smartcard_GetStatus(
    NEXUS_SmartcardHandle smartcard,
    NEXUS_SmartcardStatus *pStatus
    );
NEXUS_Error NEXUS_Smartcard_ResetCard(
    NEXUS_SmartcardHandle smartcard,
    void *pdata,
    size_t numBytes,
    size_t *pBytesRead
    );
NEXUS_Error NEXUS_Smartcard_Reset(
    NEXUS_SmartcardHandle smartcard,
    _Bool warmReset
    );
NEXUS_Error NEXUS_Smartcard_DetectCard(
    NEXUS_SmartcardHandle smartcard
    );
NEXUS_Error NEXUS_Smartcard_PowerIcc(
    NEXUS_SmartcardHandle smartcard,
    NEXUS_SmartcardPowerIcc iccAction
    );
NEXUS_Error NEXUS_Smartcard_Deactivate (
    NEXUS_SmartcardHandle smartcard
    );
typedef enum NEXUS_SmartcardClockSource
{
    NEXUS_SmartcardClockSource_eUnknown = 0,
    NEXUS_SmartcardClockSource_eInternalClock,
    NEXUS_SmartcardClockSource_eExternalClock,
    NEXUS_SmartcardClockSource_eMax
} NEXUS_SmartcardClockSource;
typedef struct NEXUS_SmartcardModuleSettings
{
    NEXUS_CommonModuleSettings common;
    NEXUS_SmartcardClockSource clockSource;
    unsigned long clockFrequency;
    _Bool externalOscillatior;
    _Bool routedInternal;
} NEXUS_SmartcardModuleSettings;
typedef struct NEXUS_SmartcardModuleInternalSettings
{
    NEXUS_ModuleHandle audio;
} NEXUS_SmartcardModuleInternalSettings;
void NEXUS_SmartcardModule_GetDefaultInternalSettings(
    NEXUS_SmartcardModuleInternalSettings *pSettings
    );
void NEXUS_SmartcardModule_GetDefaultSettings(
    NEXUS_SmartcardModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_SmartcardModule_Init(
    const NEXUS_SmartcardModuleInternalSettings *pModuleSettings,
    const NEXUS_SmartcardModuleSettings *pSettings
    );
void NEXUS_SmartcardModule_Uninit(void);
typedef struct NEXUS_SecurityModuleInternalSettings
{
    NEXUS_ModuleHandle transport;
    _Bool callTransportPostInit;
} NEXUS_SecurityModuleInternalSettings;
void NEXUS_SecurityModule_GetDefaultInternalSettings(
    NEXUS_SecurityModuleInternalSettings *pSettings
    );
void NEXUS_SecurityModule_GetDefaultSettings(
    NEXUS_SecurityModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_SecurityModule_Init(
    const NEXUS_SecurityModuleInternalSettings *pModuleSettings,
    const NEXUS_SecurityModuleSettings *pSettings
    );
void NEXUS_SecurityModule_GetCurrentSettings(
    NEXUS_ModuleHandle module,
    NEXUS_SecurityModuleSettings *pSettings
    );
void NEXUS_SecurityModule_Uninit(void);
typedef enum NEXUS_PwmFreqModeType
{
    NEXUS_PwmFreqModeType_eVariable = 0,
    NEXUS_PwmFreqModeType_eConstant
} NEXUS_PwmFreqModeType;
typedef struct NEXUS_PwmChannelSettings
{
    _Bool openDrain;
    NEXUS_PwmFreqModeType eFreqMode;
} NEXUS_PwmChannelSettings;
typedef struct NEXUS_PwmChannel *NEXUS_PwmChannelHandle;
void NEXUS_Pwm_GetDefaultChannelSettings(
    NEXUS_PwmChannelSettings *pSettings
    );
NEXUS_PwmChannelHandle NEXUS_Pwm_OpenChannel(
    unsigned index,
    const NEXUS_PwmChannelSettings *pSettings
    );
void NEXUS_Pwm_CloseChannel(
    NEXUS_PwmChannelHandle channel
    );
NEXUS_Error NEXUS_Pwm_SetControlWord(
    NEXUS_PwmChannelHandle channel,
    uint16_t word
    );
NEXUS_Error NEXUS_Pwm_GetControlWord(
    NEXUS_PwmChannelHandle channel,
    uint16_t *pWord
    );
NEXUS_Error NEXUS_Pwm_SetFreqMode(
    NEXUS_PwmChannelHandle channel,
    NEXUS_PwmFreqModeType frequencyMode
    );
NEXUS_Error NEXUS_Pwm_GetFreqMode(
    NEXUS_PwmChannelHandle channel,
    NEXUS_PwmFreqModeType *pFrequencyMode
    );
NEXUS_Error NEXUS_Pwm_SetOnInterval(
    NEXUS_PwmChannelHandle channel,
    uint16_t onInterval
    );
NEXUS_Error NEXUS_Pwm_GetOnInterval(
    NEXUS_PwmChannelHandle channel,
    uint16_t *pOnInterval
    );
NEXUS_Error NEXUS_Pwm_RampOnInterval(
    NEXUS_PwmChannelHandle channel,
    uint16_t onInterval
    );
NEXUS_Error NEXUS_Pwm_SetPeriodInterval(
    NEXUS_PwmChannelHandle channel,
    uint16_t periodInterval
    );
NEXUS_Error NEXUS_Pwm_GetPeriodInterval(
    NEXUS_PwmChannelHandle channel,
    uint16_t *pPeriodInterval
    );
NEXUS_Error NEXUS_Pwm_SetOnAndPeriodInterval(
    NEXUS_PwmChannelHandle channel,
    uint16_t OnInterval,
    uint16_t periodInterval
    );
NEXUS_Error NEXUS_Pwm_GetOnAndPeriodInterval(
    NEXUS_PwmChannelHandle channel,
    uint16_t *pOnInterval,
    uint16_t *pPeriodInterval
    );
NEXUS_Error NEXUS_Pwm_Start(
    NEXUS_PwmChannelHandle channel
    );
NEXUS_Error NEXUS_Pwm_Stop(
    NEXUS_PwmChannelHandle channel
    );
typedef struct NEXUS_PwmModuleSettings
{
    NEXUS_CommonModuleSettings common;
} NEXUS_PwmModuleSettings;
void NEXUS_PwmModule_GetDefaultSettings(
    NEXUS_PwmModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_PwmModule_Init(
    const NEXUS_PwmModuleSettings *pSettings
    );
void NEXUS_PwmModule_Uninit(void);
typedef struct NEXUS_FileModulePlatformSettings {
    unsigned workerThreads;
    NEXUS_ThreadSettings schedulerSettings[4];
} NEXUS_FileModulePlatformSettings;
typedef NEXUS_Error (*NEXUS_PlatformImgInterface_Open)(const char *context, void **image, unsigned image_id);
typedef void (*NEXUS_PlatformImgInterface_Close)(void *image);
typedef NEXUS_Error (*NEXUS_PlatformImgInterface_Next)(void *image, unsigned chunk, const void **data, uint16_t length);
typedef struct NEXUS_PlatformImgInterface {
    NEXUS_PlatformImgInterface_Open open;
    NEXUS_PlatformImgInterface_Close close;
    NEXUS_PlatformImgInterface_Next next;
} NEXUS_PlatformImgInterface;
typedef struct NEXUS_PlatformHeapSettings {
    unsigned memcIndex;
    unsigned subIndex;
    int size;
    NEXUS_Addr offset;
    unsigned alignment;
    _Bool guardBanding;
    unsigned memoryType;
    unsigned heapType;
    _Bool optional;
    struct {
        _Bool first;
        _Bool sage;
        struct {
            _Bool valid;
            NEXUS_Addr base;
            uint64_t length;
        } region;
    } placement;
} NEXUS_PlatformHeapSettings;
typedef struct NEXUS_PlatformSettings
{
    _Bool cachedMemory;
    _Bool openI2c;
    _Bool openFpga;
    _Bool openFrontend;
    _Bool openOutputs;
    _Bool openInputs;
    _Bool openCec;
    _Bool checkPlatformType;
    NEXUS_ClientMode mode;
    struct {
        unsigned userId, groupId;
    } permissions;
    NEXUS_PlatformHeapSettings heap[24];
    NEXUS_PlatformImgInterface imgInterface;
    NEXUS_HdmiOutputOpenSettings hdmiOutputOpenSettings[2];
    NEXUS_TransportModuleSettings transportModuleSettings;
    NEXUS_DisplayModuleSettings displayModuleSettings;
    NEXUS_AudioModuleSettings audioModuleSettings;
    NEXUS_VideoDecoderModuleSettings videoDecoderModuleSettings;
    NEXUS_SmartcardModuleSettings smartCardSettings;
    NEXUS_VideoEncoderModuleSettings videoEncoderSettings;
    NEXUS_SecurityModuleSettings securitySettings;
    NEXUS_Graphics2DModuleSettings graphics2DModuleSettings;
    NEXUS_PlatformStandbySettings standbySettings;
    NEXUS_FileModulePlatformSettings fileModuleSettings;
    NEXUS_SageModuleSettings sageModuleSettings;
    NEXUS_PwmModuleSettings pwmSettings;
    struct {
        _Bool open;
        NEXUS_I2cSettings settings;
        struct{
            NEXUS_GpioType type;
            unsigned gpio;
        }clock;
        struct{
            NEXUS_GpioType type;
            unsigned gpio;
        }data;
    }i2c[7];
} NEXUS_PlatformSettings;
void NEXUS_Platform_GetDefaultSettings_tagged(
    NEXUS_PlatformSettings *pSettings,
    size_t size
    );
NEXUS_Error NEXUS_Platform_Init_tagged(
    const NEXUS_PlatformSettings *pSettings,
    const NEXUS_MemoryConfigurationSettings *pMemConfig,
    unsigned platformCheck,
    unsigned versionCheck,
    unsigned structSizeCheck
    );
void NEXUS_GetDefaultMemoryConfigurationSettings_tagged(
    NEXUS_MemoryConfigurationSettings *pSettings,
    size_t size
    );
void NEXUS_GetPlatformCapabilities_tagged(
    NEXUS_PlatformCapabilities *pCap,
    size_t size
    );
typedef struct NEXUS_PlatformConfigCapabilities
{
    struct {
        _Bool valid;
        unsigned heapIndex;
        unsigned memcIndex;
    } secureGraphics[1];
} NEXUS_PlatformConfigCapabilities;
NEXUS_Error NEXUS_GetPlatformConfigCapabilities_tagged(
    const NEXUS_PlatformSettings *pSettings,
    const NEXUS_MemoryConfigurationSettings *pMemConfig,
    NEXUS_PlatformConfigCapabilities *pCap,
    unsigned size
    );
void NEXUS_Platform_GetDefaultClientAuthenticationSettings(
    NEXUS_ClientAuthenticationSettings *pSettings
    );
NEXUS_Error NEXUS_Platform_AuthenticatedJoin(
    const NEXUS_ClientAuthenticationSettings *pSettings
    );
void NEXUS_Platform_Uninit(
    void
);
void NEXUS_Platform_GetClientConfiguration(
    NEXUS_ClientConfiguration *pSettings
    );
NEXUS_Error NEXUS_Platform_GetHeapStatus_driver( NEXUS_HeapHandle heap, NEXUS_MemoryStatus *pStatus);
typedef struct NEXUS_PlatformStartServerSettings
{
    _Bool allowUnprotectedClientsToCrash;
    _Bool allowUnauthenticatedClients;
    NEXUS_ClientConfiguration unauthenticatedConfiguration;
} NEXUS_PlatformStartServerSettings;
void NEXUS_Platform_GetDefaultStartServerSettings(
    NEXUS_PlatformStartServerSettings *pSettings
    );
NEXUS_Error NEXUS_Platform_StartServer(
    const NEXUS_PlatformStartServerSettings *pSettings
    );
void NEXUS_Platform_StopServer(void);
typedef struct NEXUS_ClientSettings
{
    NEXUS_ClientAuthenticationSettings authentication;
    NEXUS_ClientConfiguration configuration;
} NEXUS_ClientSettings;
void NEXUS_Platform_GetDefaultClientSettings(
    NEXUS_ClientSettings *pSettings
    );
NEXUS_ClientHandle NEXUS_Platform_RegisterClient(
    const NEXUS_ClientSettings *pSettings
    );
void NEXUS_Platform_UnregisterClient(
    NEXUS_ClientHandle client
    );
typedef struct NEXUS_ClientStatus
{
    _Bool connected;
    unsigned numJoins;
    unsigned pid;
} NEXUS_ClientStatus;
NEXUS_Error NEXUS_Platform_GetClientStatus(
    NEXUS_ClientHandle client,
    NEXUS_ClientStatus *pStatus
    );
NEXUS_Error NEXUS_Platform_AcquireObject(NEXUS_ClientHandle client, const NEXUS_InterfaceName *name, NEXUS_AnyObject object);
void NEXUS_Platform_ReleaseObject(const NEXUS_InterfaceName *name, NEXUS_AnyObject object);
void NEXUS_Platform_GetClientResources(
    NEXUS_ClientHandle client,
    NEXUS_ClientResources *pResources
    );
NEXUS_Error NEXUS_Platform_SetClientResources(
    NEXUS_ClientHandle client,
    const NEXUS_ClientResources *pResources
    );
NEXUS_Error NEXUS_Platform_GetObjectFromId(
    NEXUS_BaseObjectId id,
    NEXUS_AnyObject *object
    );
NEXUS_Error NEXUS_Platform_GetIdFromObject(
    NEXUS_AnyObject object,
    NEXUS_BaseObjectId *id
    );
void NEXUS_Platform_GetSettings(
    NEXUS_PlatformSettings *pSettings
    );
typedef struct NEXUS_PlatformConfiguration {
    NEXUS_I2cHandle i2c[8];
    NEXUS_FrontendHandle frontend[32];
    struct {
        NEXUS_ComponentOutputHandle component[8];
        NEXUS_CompositeOutputHandle composite[8];
        NEXUS_SvideoOutputHandle svideo[8];
        NEXUS_Ccir656OutputHandle ccir656[8];
        NEXUS_RfmHandle rfm[8];
        NEXUS_AudioDacHandle audioDacs[8];
        NEXUS_AudioDummyOutputHandle audioDummy[8];
        NEXUS_SpdifOutputHandle spdif[8];
        NEXUS_I2sOutputHandle i2s[8];
        NEXUS_I2sMultiOutputHandle i2sMulti[8];
        NEXUS_HdmiOutputHandle hdmi[8];
        NEXUS_HdmiDvoHandle hdmiDvo[8];
        NEXUS_CecHandle cec[8];
    } outputs;
    struct {
        NEXUS_VideoFormat maxOutputFormat;
        NEXUS_VideoFormat maxOutputFormatSd;
    } video;
    _Bool supportedDisplay[7];
    unsigned numWindowsPerDisplay;
    _Bool supportedDecoder[6];
    NEXUS_HeapHandle heap[24];
    NEXUS_SpiHandle spi[8];
} NEXUS_PlatformConfiguration;
void NEXUS_Platform_GetConfiguration(
    NEXUS_PlatformConfiguration *pConfiguration
    );
NEXUS_Error NEXUS_Platform_GetStreamerInputBand(
    unsigned index,
    NEXUS_InputBand *pInputBand
    );
NEXUS_Error NEXUS_Platform_InitFrontend(void);
NEXUS_FrontendHandle NEXUS_Platform_OpenFrontend(
    unsigned id
    );
void NEXUS_Platform_UninitFrontend(void);
void NEXUS_Platform_GetReleaseVersion(
    char *pVersionString,
    unsigned size
    );
typedef struct NEXUS_PlatformEstimatedMemory
{
    struct {
        struct {
            unsigned general;
            unsigned secure;
        } videoDecoder;
        struct {
            unsigned general;
            unsigned secure;
            unsigned firmware;
            unsigned index;
            unsigned data;
        } videoEncoder;
        struct {
            unsigned general;
        } audio;
        struct {
            unsigned general;
        } display;
    } memc[3];
} NEXUS_PlatformEstimatedMemory;
typedef struct NEXUS_PlatformStatus
{
    unsigned chipId;
    unsigned chipRevision;
    unsigned familyId;
    struct {
        unsigned major, minor;
    } boardId;
    unsigned boxMode;
    NEXUS_DisplayModuleStatus displayModuleStatus;
    NEXUS_PlatformEstimatedMemory estimatedMemory;
    struct {
        unsigned size;
    } memc[3];
} NEXUS_PlatformStatus;
NEXUS_Error NEXUS_Platform_GetStatus(
    NEXUS_PlatformStatus *pStatus
    );
NEXUS_Error NEXUS_Platform_ReadRegister(
    uint32_t address,
    uint32_t *pValue
    );
void NEXUS_Platform_WriteRegister(
    uint32_t address,
    uint32_t value
    );
NEXUS_HeapHandle NEXUS_Platform_GetFramebufferHeap(
    unsigned displayIndex
    );
typedef struct NEXUS_PlatformCreateHeapSettings
{
    unsigned offset;
    unsigned size;
    NEXUS_MemoryType memoryType;
    unsigned alignment;
    _Bool locked;
    void *userAddress;
} NEXUS_PlatformCreateHeapSettings;
void NEXUS_Platform_GetDefaultCreateHeapSettings(
    NEXUS_PlatformCreateHeapSettings *pSettings
    );
NEXUS_HeapHandle NEXUS_Platform_CreateHeap(
    const NEXUS_PlatformCreateHeapSettings *pSettings
    );
void NEXUS_Platform_DestroyHeap(
    NEXUS_HeapHandle heap
    );
NEXUS_Error NEXUS_Platform_GrowHeap(
    NEXUS_HeapHandle heap,
    size_t numBytes
    );
void NEXUS_Platform_ShrinkHeap(
    NEXUS_HeapHandle heap,
    size_t continuousBytes,
    size_t lowThreshold
    );
unsigned NEXUS_Platform_GetVideoEncoderDisplay(
    unsigned videoEncoderIndex
    );
NEXUS_Error NEXUS_Platform_SetSharedHandle(
    NEXUS_AnyObject object,
    _Bool shared
    );
NEXUS_Error NEXUS_Platform_SetThermalScaling_driver(
    unsigned scale_factor,
    unsigned num_trip_points
    );
void NEXUS_Platform_GetHeapRuntimeSettings(
    NEXUS_HeapHandle heap,
    NEXUS_HeapRuntimeSettings *pSettings
    );
NEXUS_Error NEXUS_Platform_SetHeapRuntimeSettings(
    NEXUS_HeapHandle heap,
    const NEXUS_HeapRuntimeSettings *pSettings
    );
void NEXUS_Platform_UninitInterrupts(
    void
    );
void NEXUS_VideoDecoder_GetTrickState(
    NEXUS_VideoDecoderHandle handle,
    NEXUS_VideoDecoderTrickState *pState
    );
NEXUS_Error NEXUS_VideoDecoder_SetTrickState(
    NEXUS_VideoDecoderHandle handle,
    const NEXUS_VideoDecoderTrickState *pState
    );
NEXUS_Error NEXUS_VideoDecoder_FrameAdvance(
    NEXUS_VideoDecoderHandle handle
    );
NEXUS_Error NEXUS_VideoDecoder_GetNextPts(
    NEXUS_VideoDecoderHandle handle,
    uint32_t *pNextPts
    );
void NEXUS_VideoDecoder_GetPlaybackSettings(
    NEXUS_VideoDecoderHandle handle,
    NEXUS_VideoDecoderPlaybackSettings *pSettings
    );
NEXUS_Error NEXUS_VideoDecoder_SetPlaybackSettings(
    NEXUS_VideoDecoderHandle handle,
    const NEXUS_VideoDecoderPlaybackSettings *pSettings
    );
NEXUS_Error NEXUS_VideoDecoder_InvalidateSimulatedStc(
    NEXUS_VideoDecoderHandle handle
    );
void NEXUS_VideoDecoder_GetNormalPlay(
    NEXUS_VideoDecoderTrickState *pState
    );
typedef struct NEXUS_Playback *NEXUS_PlaybackHandle;
typedef enum NEXUS_PlaybackLoopMode
{
    NEXUS_PlaybackLoopMode_eLoop,
    NEXUS_PlaybackLoopMode_ePause,
    NEXUS_PlaybackLoopMode_ePlay,
    NEXUS_PlaybackLoopMode_eMax
} NEXUS_PlaybackLoopMode;
typedef enum NEXUS_PlaybackErrorHandlingMode
{
    NEXUS_PlaybackErrorHandlingMode_eIgnore,
    NEXUS_PlaybackErrorHandlingMode_eAbort,
    NEXUS_PlaybackErrorHandlingMode_eEndOfStream,
    NEXUS_PlaybackErrorHandlingMode_eMax
} NEXUS_PlaybackErrorHandlingMode;
typedef struct NEXUS_PlaybackSettings
{
    NEXUS_PlaypumpHandle playpump;
    NEXUS_StcChannelHandle stcChannel;
    NEXUS_SimpleStcChannelHandle simpleStcChannel;
    NEXUS_PlaypumpSettings playpumpSettings;
    NEXUS_PlaybackLoopMode endOfStreamAction;
    NEXUS_PlaybackLoopMode beginningOfStreamAction;
    NEXUS_PlaybackErrorHandlingMode playErrorHandling;
    NEXUS_PlaybackErrorHandlingMode seekErrorHandling;
    NEXUS_PlaybackErrorHandlingMode trickErrorHandling;
    NEXUS_CallbackDesc endOfStreamCallback;
    NEXUS_CallbackDesc beginningOfStreamCallback;
    NEXUS_CallbackDesc errorCallback;
    NEXUS_CallbackDesc parsingErrorCallback;
    _Bool startPaused;
    _Bool timeshifting;
    _Bool stcTrick;
    _Bool accurateSeek;
    _Bool enableStreamProcessing;
    unsigned ioTimeout;
    struct {
        unsigned endOfStreamGap;
        unsigned beginningOfStreamGap;
    } timeshiftingSettings;
    struct {
        unsigned gopDepth;
    } frameReverse;
} NEXUS_PlaybackSettings;
typedef enum NEXUS_PlaybackHostTrickMode
{
    NEXUS_PlaybackHostTrickMode_eNone,
    NEXUS_PlaybackHostTrickMode_eNormal,
    NEXUS_PlaybackHostTrickMode_ePlayI,
    NEXUS_PlaybackHostTrickMode_ePlaySkipB,
    NEXUS_PlaybackHostTrickMode_ePlayIP,
    NEXUS_PlaybackHostTrickMode_ePlaySkipP,
    NEXUS_PlaybackHostTrickMode_ePlayBrcm,
    NEXUS_PlaybackHostTrickMode_ePlayDqt,
    NEXUS_PlaybackHostTrickMode_ePlayDqtIP,
    NEXUS_PlaybackHostTrickMode_ePlayMultiPassDqt,
    NEXUS_PlaybackHostTrickMode_ePlayMultiPassDqtIP,
    NEXUS_PlaybackHostTrickMode_eTimeSkip,
    NEXUS_PlaybackHostTrickMode_eMax,
    NEXUS_PlaybackHostTrickMode_ePlayGop = NEXUS_PlaybackHostTrickMode_ePlayDqt,
    NEXUS_PlaybackHostTrickMode_ePlayGopIP = NEXUS_PlaybackHostTrickMode_ePlayDqtIP
} NEXUS_PlaybackHostTrickMode;
typedef enum NEXUS_PlaybackRateControl
{
    NEXUS_PlaybackRateControl_eStream,
    NEXUS_PlaybackRateControl_eDecoder,
    NEXUS_PlaybackRateControl_eMax
} NEXUS_PlaybackRateControl;
typedef enum NEXUS_PlaybackSkipControl
{
    NEXUS_PlaybackSkipControl_eHost,
    NEXUS_PlaybackSkipControl_eDecoder,
    NEXUS_PlaybackSkipControl_eMax
} NEXUS_PlaybackSkipControl;
typedef struct NEXUS_PlaybackTrickModeSettings
{
    int rate;
    NEXUS_PlaybackHostTrickMode mode;
    int mode_modifier;
    NEXUS_PlaybackRateControl rateControl;
    NEXUS_PlaybackSkipControl skipControl;
    unsigned maxDecoderRate;
    _Bool avoidFlush;
    _Bool brcmTrickMode;
    unsigned maxFrameRepeat;
} NEXUS_PlaybackTrickModeSettings;
typedef enum NEXUS_PlaybackState
{
    NEXUS_PlaybackState_eStopped,
    NEXUS_PlaybackState_ePlaying,
    NEXUS_PlaybackState_ePaused,
    NEXUS_PlaybackState_eTrickMode,
    NEXUS_PlaybackState_eAborted,
    NEXUS_PlaybackState_eMax
} NEXUS_PlaybackState;
typedef unsigned long NEXUS_PlaybackPosition;
typedef enum NEXUS_PlaybackMode
{
    NEXUS_PlaybackMode_eIndexed,
    NEXUS_PlaybackMode_eFixedBitrate,
    NEXUS_PlaybackMode_eAutoBitrate,
    NEXUS_PlaybackMode_eMax
} NEXUS_PlaybackMode;
typedef enum NEXUS_PlaybackIndexFileIo
{
    NEXUS_PlaybackIndexFileIo_eCallback,
    NEXUS_PlaybackIndexFileIo_eModule,
    NEXUS_PlaybackIndexFileIo_eThread,
    NEXUS_PlaybackIndexFileIo_eMax
} NEXUS_PlaybackIndexFileIo;
typedef enum NEXUS_PlaybackMpeg2TsIndexType
{
    NEXUS_PlaybackMpeg2TsIndexType_eAutoDetect,
    NEXUS_PlaybackMpeg2TsIndexType_eNav,
    NEXUS_PlaybackMpeg2TsIndexType_eSelf,
    NEXUS_PlaybackMpeg2TsIndexType_eMax
} NEXUS_PlaybackMpeg2TsIndexType;
typedef struct NEXUS_PlaybackStartSettings
{
    NEXUS_PlaybackMode mode;
    unsigned bitrate;
    NEXUS_PlaybackMpeg2TsIndexType mpeg2TsIndexType;
    struct {
        NEXUS_PlaybackIndexFileIo mode;
        NEXUS_ThreadSettings threadSettings;
    } indexFileIo;
} NEXUS_PlaybackStartSettings;
NEXUS_PlaybackHandle NEXUS_Playback_Create(void);
void NEXUS_Playback_Destroy(
    NEXUS_PlaybackHandle playback
    );
void NEXUS_Playback_GetDefaultStartSettings(
    NEXUS_PlaybackStartSettings *pSettings
    );
NEXUS_Error NEXUS_Playback_Start(
    NEXUS_PlaybackHandle playback,
    NEXUS_FilePlayHandle file,
    const NEXUS_PlaybackStartSettings *pSettings
    );
void NEXUS_Playback_Stop(
    NEXUS_PlaybackHandle playback
    );
typedef struct NEXUS_PlaybackStatus
{
    NEXUS_PlaybackPosition position;
    NEXUS_PlaybackState state;
    NEXUS_PlaybackTrickModeSettings trickModeSettings;
    unsigned fifoDepth;
    unsigned fifoSize;
    uint64_t bytesPlayed;
    NEXUS_PlaybackPosition first;
    NEXUS_PlaybackPosition last;
    unsigned indexErrors;
    unsigned dataErrors;
    NEXUS_PlaybackPosition readPosition;
} NEXUS_PlaybackStatus;
NEXUS_Error NEXUS_Playback_GetStatus(
    NEXUS_PlaybackHandle playback,
    NEXUS_PlaybackStatus *pStatus
    );
NEXUS_Error NEXUS_Playback_Pause(
    NEXUS_PlaybackHandle playback
    );
NEXUS_Error NEXUS_Playback_Play(
    NEXUS_PlaybackHandle playback
    );
NEXUS_Error NEXUS_Playback_FrameAdvance(
    NEXUS_PlaybackHandle playback,
    _Bool forward
    );
NEXUS_Error NEXUS_Playback_TrickMode(
    NEXUS_PlaybackHandle playback,
    const NEXUS_PlaybackTrickModeSettings *pTrickModeSettings
    );
void NEXUS_Playback_GetDefaultTrickModeSettings(
    NEXUS_PlaybackTrickModeSettings *pTrickModeSettings
    );
typedef struct NEXUS_PlaybackPidChannelSettings
{
    NEXUS_PlaypumpOpenPidChannelSettings pidSettings;
    struct
    {
        struct
        {
            NEXUS_VideoDecoderHandle decoder;
            NEXUS_SimpleVideoDecoderHandle simpleDecoder;
            NEXUS_VideoCodec codec;
            _Bool index;
        } video;
        struct
        {
            NEXUS_AudioDecoderHandle primary;
            NEXUS_AudioDecoderHandle secondary;
            NEXUS_SimpleAudioDecoderHandle simpleDecoder;
            NEXUS_AudioDecoderPrimerHandle primer;
            NEXUS_AudioDecoderPrimerHandle secondaryPrimer;
        } audio;
    } pidTypeSettings;
} NEXUS_PlaybackPidChannelSettings;
NEXUS_Error NEXUS_Playback_Seek(
    NEXUS_PlaybackHandle playback,
    NEXUS_PlaybackPosition position
    );
void NEXUS_Playback_GetDefaultPidChannelSettings(
    NEXUS_PlaybackPidChannelSettings *pSettings
    );
NEXUS_PidChannelHandle NEXUS_Playback_OpenPidChannel(
    NEXUS_PlaybackHandle playback,
    unsigned pid,
    const NEXUS_PlaybackPidChannelSettings *pSettings
    );
NEXUS_Error NEXUS_Playback_GetPidChannelSettings(
    NEXUS_PlaybackHandle playback,
    NEXUS_PidChannelHandle pidChannel,
    NEXUS_PlaybackPidChannelSettings *pSettings
    );
NEXUS_Error NEXUS_Playback_SetPidChannelSettings(
    NEXUS_PlaybackHandle playback,
    NEXUS_PidChannelHandle pidChannel,
    const NEXUS_PlaybackPidChannelSettings *pSettings
    );
void NEXUS_Playback_ClosePidChannel(
    NEXUS_PlaybackHandle playback,
    NEXUS_PidChannelHandle pidChannel
    );
void NEXUS_Playback_CloseAllPidChannels(
    NEXUS_PlaybackHandle playback
    );
void NEXUS_Playback_GetSettings(
    NEXUS_PlaybackHandle playback,
    NEXUS_PlaybackSettings *pSettings
    );
void NEXUS_Playback_GetDefaultSettings(
    NEXUS_PlaybackSettings *pSettings
    );
NEXUS_Error NEXUS_Playback_SetSettings(
    NEXUS_PlaybackHandle playback,
    const NEXUS_PlaybackSettings *pSettings
    );
void NEXUS_Playback_IsTransportTypeSupported(
    NEXUS_PlaybackHandle playback,
    NEXUS_TransportType transportType,
    _Bool *pIsSupported
    );
typedef struct NEXUS_PlaybackModuleSettings
{
    struct {
        NEXUS_ModuleHandle file;
        NEXUS_ModuleHandle videoDecoder;
        NEXUS_ModuleHandle audioDecoder;
        NEXUS_ModuleHandle playpump;
    } modules;
} NEXUS_PlaybackModuleSettings;
void NEXUS_PlaybackModule_GetDefaultSettings(
    NEXUS_PlaybackModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_PlaybackModule_Init(
    const NEXUS_PlaybackModuleSettings *pSettings
    );
void NEXUS_PlaybackModule_Uninit(void);
typedef struct NEXUS_ProgramOtpKey {
   NEXUS_OtpKeyType keyType;
   NEXUS_SecurityVirtualKeyladderID virtualKeyLadderID;
   NEXUS_SecurityKeySource keyLayer;
   uint8_t keyData[(36)];
   uint32_t keyDataSize;
} NEXUS_ProgramOtpKey;
NEXUS_Error NEXUS_Security_GetDefaultProgramOtpKey(
   NEXUS_ProgramOtpKey *pOtpKey
   );
NEXUS_Error NEXUS_Security_ProgramOtpKey(
   const NEXUS_ProgramOtpKey *pOtpKey
   );
typedef enum NEXUS_RandomNumberType
{
    NEXUS_RandomNumberType_eRngRaw,
    NEXUS_RandomNumberType_eFips186X,
    NEXUS_RandomNumberType_eFips186K,
    NEXUS_RandomNumberType_eRngSha1,
    NEXUS_RandomNumberType_eMax
} NEXUS_RandomNumberType;
typedef enum NEXUS_RandomNumberDestination
{
    NEXUS_RandomNumberDestination_eHost = 0,
    NEXUS_RandomNumberDestination_eFirstRNRam1024 = 20,
    NEXUS_RandomNumberDestination_eSecondRNRam1024 = 21,
    NEXUS_RandomNumberDestination_eMax
} NEXUS_RandomNumberDestination;
typedef struct NEXUS_RandomNumberGenerateSettings
{
    NEXUS_RandomNumberType type;
    NEXUS_RandomNumberDestination destination;
    unsigned int randomNumberSize;
} NEXUS_RandomNumberGenerateSettings;
typedef struct NEXUS_RandomNumberOutput
{
    unsigned char buffer[352];
    unsigned int size;
} NEXUS_RandomNumberOutput;
void NEXUS_RandomNumber_GetDefaultGenerateSettings(
    NEXUS_RandomNumberGenerateSettings *pSettings
    );
NEXUS_Error NEXUS_RandomNumber_Generate(
    const NEXUS_RandomNumberGenerateSettings *pSettings,
    NEXUS_RandomNumberOutput *pOutput
    );
typedef enum NEXUS_OtpIdType
{
    NEXUS_OtpIdType_eA,
    NEXUS_OtpIdType_eB,
    NEXUS_OtpIdType_eC,
    NEXUS_OtpIdType_eD,
    NEXUS_OtpIdType_eE,
    NEXUS_OtpIdType_eF,
    NEXUS_OtpIdType_eG,
    NEXUS_OtpIdType_eH,
    NEXUS_OtpIdType_eMax
} NEXUS_OtpIdType;
typedef struct NEXUS_OtpIdOutput
{
    unsigned char otpId[8];
    unsigned int size;
} NEXUS_OtpIdOutput;
NEXUS_Error NEXUS_Security_ReadOtpId(
    NEXUS_OtpIdType otpId,
    NEXUS_OtpIdOutput *pOutput
    );
typedef struct NEXUS_Record *NEXUS_RecordHandle;
typedef enum NEXUS_RecordIndexType
{
    NEXUS_RecordIndexType_eNone,
    NEXUS_RecordIndexType_eBcm
} NEXUS_RecordIndexType;
typedef enum NEXUS_RecordTimestampSource
{
    NEXUS_RecordTimestampSource_eAuto,
    NEXUS_RecordTimestampSource_eWallClock,
    NEXUS_RecordTimestampSource_ePts,
    NEXUS_RecordTimestampSource_eMax
} NEXUS_RecordTimestampSource;
typedef struct NEXUS_RecordSettings
{
    NEXUS_RecordIndexType indexFormat;
    NEXUS_RecordTimestampSource timestampSource;
    NEXUS_RecpumpHandle recpump;
    NEXUS_RecpumpSettings recpumpSettings;
    NEXUS_CallbackDesc overflowCallback;
    NEXUS_CallbackDesc errorCallback;
    unsigned writeAllTimeout;
    _Bool allowLargeTimeGaps;
    unsigned pollingTimer;
} NEXUS_RecordSettings;
typedef enum NEXUS_RecordErrorType
{
    NEXUS_RecordErrorType_eNone,
    NEXUS_RecordErrorType_eDiskFull,
    NEXUS_RecordErrorType_eMaxFileSize,
    NEXUS_RecordErrorType_eUnknown
} NEXUS_RecordErrorType;
NEXUS_RecordHandle NEXUS_Record_Create(void);
void NEXUS_Record_Destroy(
    NEXUS_RecordHandle record
    );
void NEXUS_Record_GetDefaultSettings(
    NEXUS_RecordSettings *pSettings
    );
void NEXUS_Record_GetSettings(
    NEXUS_RecordHandle record,
    NEXUS_RecordSettings *pSettings
    );
NEXUS_Error NEXUS_Record_SetSettings(
    NEXUS_RecordHandle record,
    const NEXUS_RecordSettings *pSettings
    );
NEXUS_Error NEXUS_Record_Start(
    NEXUS_RecordHandle record,
    NEXUS_FileRecordHandle file
    );
typedef struct NEXUS_RecordAppendSettings {
    uint64_t startingOffset;
    unsigned timestamp;
} NEXUS_RecordAppendSettings;
void NEXUS_Record_GetDefaultAppendSettings(
    NEXUS_RecordAppendSettings *pSettings
    );
NEXUS_Error NEXUS_Record_StartAppend(
    NEXUS_RecordHandle record,
    NEXUS_FileRecordHandle file,
    const NEXUS_RecordAppendSettings *pSettings
    );
void NEXUS_Record_Stop(
    NEXUS_RecordHandle record
    );
typedef struct NEXUS_RecordPidChannelSettings
{
    NEXUS_RecpumpAddPidChannelSettings recpumpSettings;
} NEXUS_RecordPidChannelSettings;
NEXUS_Error NEXUS_Record_AddPidChannel(
    NEXUS_RecordHandle record,
    NEXUS_PidChannelHandle pidChannel,
    const NEXUS_RecordPidChannelSettings *pSettings
    );
NEXUS_Error NEXUS_Record_RemovePidChannel(
    NEXUS_RecordHandle record,
    NEXUS_PidChannelHandle pidChannel
    );
void NEXUS_Record_RemoveAllPidChannels(
    NEXUS_RecordHandle record
    );
void NEXUS_Record_GetDefaultPidChannelSettings(
    NEXUS_RecordPidChannelSettings *pSettings
    );
NEXUS_Error NEXUS_Record_AddPlayback(
    NEXUS_RecordHandle record,
    NEXUS_PlaybackHandle playback
    );
NEXUS_Error NEXUS_Record_RemovePlayback(
    NEXUS_RecordHandle record,
    NEXUS_PlaybackHandle playback
    );
void NEXUS_Record_RemoveAllPlaybacks(
    NEXUS_RecordHandle record
    );
typedef struct NEXUS_RecordStatus
{
    NEXUS_RecpumpStatus recpumpStatus;
    unsigned long lastTimestamp;
    unsigned picturesIndexed;
    NEXUS_RecordErrorType error;
    unsigned indexParsingErrors;
} NEXUS_RecordStatus;
NEXUS_Error NEXUS_Record_GetStatus(
    NEXUS_RecordHandle record,
    NEXUS_RecordStatus *pStatus
    );
typedef struct NEXUS_RecordModuleSettings
{
    struct {
        NEXUS_ModuleHandle file;
        NEXUS_ModuleHandle recpump;
        NEXUS_ModuleHandle playback;
    } modules;
} NEXUS_RecordModuleSettings;
void NEXUS_RecordModule_GetDefaultSettings(
    NEXUS_RecordModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_RecordModule_Init(
    const NEXUS_RecordModuleSettings *pSettings
    );
void NEXUS_RecordModule_Uninit(void);
typedef struct NEXUS_RegionVerify *NEXUS_RegionVerifyHandle;
typedef struct NEXUS_RegionVerifySettings
{
    _Bool enabled;
    NEXUS_Addr regionAddress;
    unsigned regionSize;
    struct{
        unsigned size;
        uint8_t data[((256)+20)];
         struct{
            uint32_t marketId;
            uint32_t marketIdMask;
            uint8_t systemEpoch;
            uint8_t systemEpochMask;
            _Bool reLocatable;
            uint8_t systemEpochSelect;
            uint8_t signatureVersion;
        }attributes;
    }signature;
    unsigned rsaKeyIndex;
} NEXUS_RegionVerifySettings;
NEXUS_RegionVerifyHandle NEXUS_RegionVerify_Open(
    unsigned index
    );
void NEXUS_RegionVerify_Close(
    NEXUS_RegionVerifyHandle handle
    );
void NEXUS_RegionVerify_GetSettings(
    NEXUS_RegionVerifyHandle handle,
    NEXUS_RegionVerifySettings *pSettings
    );
NEXUS_Error NEXUS_RegionVerify_SetSettings(
    NEXUS_RegionVerifyHandle handle,
    const NEXUS_RegionVerifySettings *pSettings
    );
typedef struct NEXUS_RfAudioEncoder *NEXUS_RfAudioEncoderHandle;
typedef struct NEXUS_RfAudioEncoderSettings
{
    NEXUS_RfAudioEncoding encoding;
} NEXUS_RfAudioEncoderSettings;
void NEXUS_RfAudioEncoder_GetDefaultSettings(
    NEXUS_RfAudioEncoderSettings *pSettings
    );
NEXUS_RfAudioEncoderHandle NEXUS_RfAudioEncoder_Open(
    const NEXUS_RfAudioEncoderSettings *pSettings
    );
void NEXUS_RfAudioEncoder_Close(
    NEXUS_RfAudioEncoderHandle handle
    );
void NEXUS_RfAudioEncoder_GetSettings(
    NEXUS_RfAudioEncoderHandle handle,
    NEXUS_RfAudioEncoderSettings *pSettings
    );
NEXUS_Error NEXUS_RfAudioEncoder_SetSettings(
    NEXUS_RfAudioEncoderHandle handle,
    const NEXUS_RfAudioEncoderSettings *pSettings
    );
typedef enum NEXUS_BtscEncodingMode
{
    NEXUS_BtscEncodingMode_eStereo,
    NEXUS_BtscEncodingMode_eMono,
    NEXUS_BtscEncodingMode_eMax
} NEXUS_BtscEncodingMode;
typedef struct NEXUS_BtscEncodeSettings
{
    _Bool useDeEmphasizedSourceSignals;
    _Bool equivalentMode75us;
    _Bool fmDeviationControl;
    _Bool rightChannelMute;
    NEXUS_BtscEncodingMode encodingMode;
    int32_t volume;
    uint32_t srdCalibrationFactor;
    struct
    {
        _Bool preemphasis;
        _Bool fmDeviationControl;
    } mainChannel;
    struct
    {
        _Bool clipping;
        _Bool preemphasis;
        _Bool fmDeviationControl;
    } diffChannel;
    struct
    {
        _Bool enabled;
        _Bool frequency;
    } testTone;
} NEXUS_BtscEncodeSettings;
typedef struct NEXUS_RfAudioEncoderEncodingSettings
{
    NEXUS_RfAudioEncoding encoding;
    union
    {
        NEXUS_BtscEncodeSettings btsc;
    } encodingSettings;
} NEXUS_RfAudioEncoderEncodingSettings;
void NEXUS_RfAudioEncoder_GetEncodingSettings(
    NEXUS_RfAudioEncoderHandle handle,
    NEXUS_RfAudioEncoding encoding,
    NEXUS_RfAudioEncoderEncodingSettings *pSettings
    );
NEXUS_Error NEXUS_RfAudioEncoder_SetEncodingSettings(
    NEXUS_RfAudioEncoderHandle handle,
    const NEXUS_RfAudioEncoderEncodingSettings *pSettings
    );
NEXUS_AudioInputHandle NEXUS_RfAudioEncoder_GetConnector(
    NEXUS_RfAudioEncoderHandle handle
    );
NEXUS_Error NEXUS_RfAudioEncoder_AddInput(
    NEXUS_RfAudioEncoderHandle handle,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_RfAudioEncoder_RemoveInput(
    NEXUS_RfAudioEncoderHandle handle,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_RfAudioEncoder_RemoveAllInputs(
    NEXUS_RfAudioEncoderHandle handle
    );
typedef enum NEXUS_SecurityFirstTierKeyID
{
    NEXUS_SecurityFirstTierKeyID_eKey0Prime,
    NEXUS_SecurityFirstTierKeyID_eKey0,
    NEXUS_SecurityFirstTierKeyID_eMax
} NEXUS_SecurityFirstTierKeyID;
typedef enum NEXUS_SecuritySecondTierKeyID
{
    NEXUS_SecuritySecondTierKeyID_eNone,
    NEXUS_SecuritySecondTierKeyID_eKey1,
    NEXUS_SecuritySecondTierKeyID_eKey2,
    NEXUS_SecuritySecondTierKeyID_eKey3,
    NEXUS_SecuritySecondTierKeyID_eKey4,
    NEXUS_SecuritySecondTierKeyID_eMax
} NEXUS_SecuritySecondTierKeyID;
typedef struct NEXUS_SecurityVerifySecondTierKeySettings
{
    NEXUS_SecuritySecondTierKeyID keyDestination;
    NEXUS_SecurityFirstTierKeyID firstTierRootKeySource;
    NEXUS_SecuritySecondTierKeyID secondTierRootKeySource;
    uint64_t keyAddress;
} NEXUS_SecurityVerifySecondTierKeySettings;
void NEXUS_Security_GetDefaultVerifySecondTierKeySettings(
    NEXUS_SecurityVerifySecondTierKeySettings *pSettings
    );
NEXUS_Error NEXUS_Security_VerifySecondTierKey(
    const NEXUS_SecurityVerifySecondTierKeySettings *pSecondTierKeySettings
    );
typedef enum NEXUS_SecurityCodeVerifierMode
{
    NEXUS_SecurityCodeVerifierMode_eRsaSignature,
    NEXUS_SecurityCodeVerifierMode_eOtpHash2,
    NEXUS_SecurityCodeVerifierMode_eMax
} NEXUS_SecurityCodeVerifier;
typedef enum NEXUS_SecurityCodeLocation
{
    NEXUS_SecurityCodeLocation_eFlash,
    NEXUS_SecurityCodeLocation_eDram,
    NEXUS_SecurityCodeLocation_eMax
} NEXUS_SecurityCodeLocation;
typedef struct NEXUS_SecurityVerifySecondStageCodeSettings
{
    NEXUS_SecurityCodeLocation codeLocation;
    uint64_t codeAddress;
    uint64_t signatureAddress;
    NEXUS_SecurityCodeVerifier verifierMode;
    NEXUS_SecuritySecondTierKeyID verifierKey;
} NEXUS_SecurityVerifySecondStageCodeSettings;
void NEXUS_Security_GetDefaultVerifySecondStageCodeSettings(
    NEXUS_SecurityVerifySecondStageCodeSettings *pSettings
    );
NEXUS_Error NEXUS_Security_VerifySecondStageCode(
    const NEXUS_SecurityVerifySecondStageCodeSettings *pCodeVerifySettings
    );
NEXUS_Error NEXUS_Security_RouteDataSectionKey(
    NEXUS_KeySlotHandle keyHandle
    );
NEXUS_Error NEXUS_Security_SubmitRawCommand (
    const unsigned int *pInBuffer,
    unsigned int sizeInBuffer,
    unsigned int *pOutBuffer,
    unsigned int sizeOutBuffer,
    unsigned int *pActualOutSize
    );
typedef struct NEXUS_SimpleAudioPlayback *NEXUS_SimpleAudioPlaybackHandle;
NEXUS_SimpleAudioPlaybackHandle NEXUS_SimpleAudioPlayback_Acquire(
    unsigned index
    );
void NEXUS_SimpleAudioPlayback_Release(
    NEXUS_SimpleAudioPlaybackHandle handle
    );
typedef struct NEXUS_SimpleAudioPlaybackStartSettings
{
    unsigned sampleRate;
    unsigned bitsPerSample;
    size_t startThreshold;
    _Bool stereo;
    _Bool signedData;
    _Bool loopAround;
    _Bool compressed;
    NEXUS_CallbackDesc dataCallback;
    NEXUS_Timebase timebase;
    NEXUS_EndianMode endian;
} NEXUS_SimpleAudioPlaybackStartSettings;
void NEXUS_SimpleAudioPlayback_GetDefaultStartSettings(
    NEXUS_SimpleAudioPlaybackStartSettings *pSettings
    );
NEXUS_Error NEXUS_SimpleAudioPlayback_Start(
    NEXUS_SimpleAudioPlaybackHandle handle,
    const NEXUS_SimpleAudioPlaybackStartSettings *pSettings
    );
void NEXUS_SimpleAudioPlayback_Stop(
    NEXUS_SimpleAudioPlaybackHandle handle
    );
typedef struct NEXUS_SimpleAudioPlaybackSettings
{
    int32_t leftVolume;
    int32_t rightVolume;
    _Bool muted;
    unsigned sampleRate;
    unsigned contentReferenceLevel;
} NEXUS_SimpleAudioPlaybackSettings;
void NEXUS_SimpleAudioPlayback_GetSettings(
    NEXUS_SimpleAudioPlaybackHandle handle,
    NEXUS_SimpleAudioPlaybackSettings *pSettings
    );
NEXUS_Error NEXUS_SimpleAudioPlayback_SetSettings(
    NEXUS_SimpleAudioPlaybackHandle handle,
    const NEXUS_SimpleAudioPlaybackSettings *pSettings
    );
   typedef struct NEXUS_SimpleAudioPlaybackStatus
{
    _Bool started;
    size_t queuedBytes;
    size_t fifoSize;
    size_t playedBytes;
} NEXUS_SimpleAudioPlaybackStatus;
NEXUS_Error NEXUS_SimpleAudioPlayback_GetStatus(
    NEXUS_SimpleAudioPlaybackHandle handle,
    NEXUS_SimpleAudioPlaybackStatus *pStatus
    );
NEXUS_Error NEXUS_SimpleAudioPlayback_GetBuffer(
    NEXUS_SimpleAudioPlaybackHandle handle,
    void **pBuffer,
    size_t *pSize
    );
NEXUS_Error NEXUS_SimpleAudioPlayback_WriteComplete(
    NEXUS_SimpleAudioPlaybackHandle handle,
    size_t amountWritten
    );
void NEXUS_SimpleAudioPlayback_Flush(
    NEXUS_SimpleAudioPlaybackHandle handle
    );
typedef enum NEXUS_SimpleAudioDecoderType {
    NEXUS_SimpleAudioDecoderType_eDynamic,
    NEXUS_SimpleAudioDecoderType_ePersistent,
    NEXUS_SimpleAudioDecoderType_eStandalone,
    NEXUS_SimpleAudioDecoderType_eMax
} NEXUS_SimpleAudioDecoderType;
typedef struct NEXUS_SimpleAudioDecoderServer *NEXUS_SimpleAudioDecoderServerHandle;
typedef struct NEXUS_SimpleAudioDecoderServerSettings
{
    NEXUS_SimpleAudioDecoderType type;
    NEXUS_SimpleDecoderDisableMode disableMode;
    NEXUS_AudioDecoderHandle primary;
    NEXUS_AudioDecoderHandle secondary;
    NEXUS_AudioDecoderHandle description;
    NEXUS_AudioPlaybackHandle passthroughPlayback;
    struct {
        NEXUS_AudioDecoderHandle decoder;
        _Bool suspended;
    } persistent[12];
    struct {
        _Bool ms11;
        _Bool ms12;
    } capabilities;
    struct {
        NEXUS_AudioMixerHandle stereo, multichannel, persistent;
    } mixers;
    NEXUS_AudioConnectorType syncConnector;
    struct {
        NEXUS_SpdifOutputHandle outputs[2];
        NEXUS_AudioInputHandle input[43];
    } spdif;
    struct {
        NEXUS_HdmiOutputHandle outputs[2];
        NEXUS_AudioInputHandle input[43];
    } hdmi;
    struct {
        NEXUS_AudioCaptureHandle output;
        NEXUS_AudioInputHandle input[43];
    } capture;
} NEXUS_SimpleAudioDecoderServerSettings;
void NEXUS_SimpleAudioDecoder_GetDefaultServerSettings(
    NEXUS_SimpleAudioDecoderServerSettings *pSettings
    );
NEXUS_SimpleAudioDecoderServerHandle NEXUS_SimpleAudioDecoderServer_Create(
    void
    );
void NEXUS_SimpleAudioDecoderServer_Destroy(
    NEXUS_SimpleAudioDecoderServerHandle handle
    );
NEXUS_SimpleAudioDecoderHandle NEXUS_SimpleAudioDecoder_Create(
    NEXUS_SimpleAudioDecoderServerHandle server,
    unsigned index,
    const NEXUS_SimpleAudioDecoderServerSettings *pSettings
    );
void NEXUS_SimpleAudioDecoder_Destroy(
    NEXUS_SimpleAudioDecoderHandle handle
    );
void NEXUS_SimpleAudioDecoder_GetServerSettings(
    NEXUS_SimpleAudioDecoderServerHandle server,
    NEXUS_SimpleAudioDecoderHandle handle,
    NEXUS_SimpleAudioDecoderServerSettings *pSettings
    );
NEXUS_Error NEXUS_SimpleAudioDecoder_SetServerSettings(
    NEXUS_SimpleAudioDecoderServerHandle server,
    NEXUS_SimpleAudioDecoderHandle handle,
    const NEXUS_SimpleAudioDecoderServerSettings *pSettings
    );
typedef struct NEXUS_SimpleAudioPlaybackServerSettings
{
    NEXUS_SimpleAudioDecoderHandle decoder;
    NEXUS_AudioPlaybackHandle playback;
    NEXUS_I2sInputHandle i2sInput;
    struct {
        _Bool enabled;
        NEXUS_SpdifOutputHandle spdifOutputs[2];
        NEXUS_HdmiOutputHandle hdmiOutputs[2];
    } compressed;
} NEXUS_SimpleAudioPlaybackServerSettings;
void NEXUS_SimpleAudioPlayback_GetDefaultServerSettings(
    NEXUS_SimpleAudioPlaybackServerSettings *pSettings
    );
NEXUS_SimpleAudioPlaybackHandle NEXUS_SimpleAudioPlayback_Create(
    NEXUS_SimpleAudioDecoderServerHandle server,
    unsigned index,
    const NEXUS_SimpleAudioPlaybackServerSettings *pSettings
    );
void NEXUS_SimpleAudioPlayback_Destroy(
    NEXUS_SimpleAudioPlaybackHandle handle
    );
void NEXUS_SimpleAudioPlayback_GetServerSettings(
    NEXUS_SimpleAudioDecoderServerHandle server,
    NEXUS_SimpleAudioPlaybackHandle handle,
    NEXUS_SimpleAudioPlaybackServerSettings *pSettings
    );
NEXUS_Error NEXUS_SimpleAudioPlayback_SetServerSettings(
    NEXUS_SimpleAudioDecoderServerHandle server,
    NEXUS_SimpleAudioPlaybackHandle handle,
    const NEXUS_SimpleAudioPlaybackServerSettings *pSettings
    );
NEXUS_Error NEXUS_SimpleAudioDecoder_SwapServerSettings(
    NEXUS_SimpleAudioDecoderServerHandle server,
    NEXUS_SimpleAudioDecoderHandle decoder1,
    NEXUS_SimpleAudioDecoderHandle decoder2
    );
void NEXUS_SimpleAudioDecoderModule_LoadDefaultSettings(
    NEXUS_AudioDecoderHandle audio
    );
void NEXUS_SimpleAudioDecoder_GetStcIndex(
    NEXUS_SimpleAudioDecoderServerHandle server,
    NEXUS_SimpleAudioDecoderHandle handle,
    int *pStcIndex
    );
void NEXUS_SimpleAudioDecoder_SetStcIndex(
    NEXUS_SimpleAudioDecoderServerHandle server,
    NEXUS_SimpleAudioDecoderHandle handle,
    int stcIndex
    );
typedef struct NEXUS_SimpleDecoderModuleSettings
{
    struct {
        NEXUS_ModuleHandle videoDecoder, display, audio;
    } modules;
} NEXUS_SimpleDecoderModuleSettings;
void NEXUS_SimpleDecoderModule_GetDefaultSettings(
    NEXUS_SimpleDecoderModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_SimpleDecoderModule_Init(
    const NEXUS_SimpleDecoderModuleSettings *pSettings
    );
void NEXUS_SimpleDecoderModule_Uninit(void);
typedef struct NEXUS_StreamMux *NEXUS_StreamMuxHandle;
typedef struct NEXUS_StreamMuxMemoryConfiguration {
    size_t systemBufferSize;
    size_t sharedBufferSize;
} NEXUS_StreamMuxMemoryConfiguration;
typedef struct NEXUS_StreamMuxCreateSettings
{
    NEXUS_CallbackDesc finished;
    NEXUS_StreamMuxMemoryConfiguration memoryConfiguration;
    NEXUS_HeapHandle systemHeap;
    NEXUS_HeapHandle sharedHeap;
} NEXUS_StreamMuxCreateSettings;
typedef struct NEXUS_StreamMuxConfiguration {
    unsigned servicePeriod;
    unsigned latencyTolerance;
    _Bool nonRealTime;
    unsigned videoPids;
    unsigned audioPids;
    unsigned userDataPids;
    unsigned pcrPidinterval;
    unsigned systemDataBitRate;
    unsigned muxDelay;
    _Bool supportTts;
} NEXUS_StreamMuxConfiguration;
void NEXUS_StreamMux_GetDefaultCreateSettings(
    NEXUS_StreamMuxCreateSettings *pSettings
    );
NEXUS_StreamMuxHandle NEXUS_StreamMux_Create(
    const NEXUS_StreamMuxCreateSettings *pSettings
    );
void NEXUS_StreamMux_Destroy(
    NEXUS_StreamMuxHandle handle
    );
typedef struct NEXUS_StreamMuxVideoPid {
    uint16_t pid;
    uint8_t pesId;
    int pidChannelIndex;
    NEXUS_PlaypumpHandle playpump;
    NEXUS_VideoEncoderHandle encoder;
} NEXUS_StreamMuxVideoPid;
typedef struct NEXUS_StreamMuxAudioPid {
    uint16_t pid;
    uint8_t pesId;
    int pidChannelIndex;
    NEXUS_PlaypumpHandle playpump;
    NEXUS_AudioMuxOutputHandle muxOutput;
    _Bool pesPacking;
} NEXUS_StreamMuxAudioPid;
typedef struct NEXUS_StreamMuxPcrPid {
    unsigned pid;
    int pidChannelIndex;
    NEXUS_PlaypumpHandle playpump;
    unsigned interval;
} NEXUS_StreamMuxPcrPid;
typedef struct NEXUS_StreamMuxUserDataPid {
    NEXUS_MessageHandle message;
} NEXUS_StreamMuxUserDataPid;
typedef enum NEXUS_StreamMuxInterleaveMode
{
   NEXUS_StreamMuxInterleaveMode_eCompliant,
   NEXUS_StreamMuxInterleaveMode_ePts,
   NEXUS_StreamMuxInterleaveMode_eMax
} NEXUS_StreamMuxInterleaveMode;
typedef struct NEXUS_StreamMuxStartSettings
{
    NEXUS_TransportType transportType;
    NEXUS_StcChannelHandle stcChannel;
    NEXUS_StreamMuxVideoPid video[16];
    NEXUS_StreamMuxAudioPid audio[16];
    NEXUS_StreamMuxPcrPid pcr;
    NEXUS_StreamMuxUserDataPid userdata[16];
    unsigned latencyTolerance;
    _Bool nonRealTime;
    int nonRealTimeRate;
    unsigned servicePeriod;
    unsigned muxDelay;
    _Bool supportTts;
    NEXUS_StreamMuxInterleaveMode interleaveMode;
    _Bool insertPtsOnlyOnFirstKeyFrameOfSegment;
    _Bool useInitialPts;
    uint32_t initialPts;
} NEXUS_StreamMuxStartSettings;
typedef struct NEXUS_StreamMuxOutput
{
    NEXUS_PidChannelHandle video[16];
    NEXUS_PidChannelHandle audio[16];
    NEXUS_PidChannelHandle pcr;
} NEXUS_StreamMuxOutput;
typedef struct NEXUS_StreamMuxSettings
{
    struct {
        _Bool video[16];
        _Bool audio[16];
    } enable;
} NEXUS_StreamMuxSettings;
void NEXUS_StreamMux_GetDefaultStartSettings(
    NEXUS_StreamMuxStartSettings *pSettings
    );
NEXUS_Error NEXUS_StreamMux_Start(
    NEXUS_StreamMuxHandle handle,
    const NEXUS_StreamMuxStartSettings *pSettings,
    NEXUS_StreamMuxOutput *pMuxOutput
    );
void NEXUS_StreamMux_GetSettings(
    NEXUS_StreamMuxHandle handle,
    NEXUS_StreamMuxSettings *pSettings
    );
NEXUS_Error NEXUS_StreamMux_SetSettings(
    NEXUS_StreamMuxHandle handle,
    const NEXUS_StreamMuxSettings *pSettings
    );
void NEXUS_StreamMux_Finish(
    NEXUS_StreamMuxHandle handle
    );
void NEXUS_StreamMux_Stop(
    NEXUS_StreamMuxHandle handle
    );
typedef struct NEXUS_StreamMuxSystemData
{
    unsigned timestampDelta;
    size_t size;
    const void *pData;
} NEXUS_StreamMuxSystemData;
void NEXUS_StreamMux_GetDefaultSystemData(
    NEXUS_StreamMuxSystemData *pSystemDataBuffer
    );
NEXUS_Error NEXUS_StreamMux_AddSystemDataBuffer(
    NEXUS_StreamMuxHandle handle,
    const NEXUS_StreamMuxSystemData *pSystemDataBuffer
    );
void NEXUS_StreamMux_GetCompletedSystemDataBuffers(
    NEXUS_StreamMuxHandle handle,
    size_t *pCompletedCount
    );
typedef struct NEXUS_StreamMuxStatus
{
    unsigned duration;
    struct
    {
       struct
       {
          unsigned currentTimestamp;
       } pid[16];
       unsigned averageBitrate;
    } video, audio, systemdata, userdata;
    unsigned efficiency;
    uint64_t totalBytes;
} NEXUS_StreamMuxStatus;
NEXUS_Error NEXUS_StreamMux_GetStatus(
    NEXUS_StreamMuxHandle handle,
    NEXUS_StreamMuxStatus *pStatus
    );
void NEXUS_StreamMux_GetDefaultConfiguration(
    NEXUS_StreamMuxConfiguration *pConfiguration
    );
void NEXUS_StreamMux_GetMemoryConfiguration(
    const NEXUS_StreamMuxConfiguration *pConfiguration,
    NEXUS_StreamMuxMemoryConfiguration *pMemoryConfiguration
    );
typedef struct NEXUS_SimpleEncoderServer *NEXUS_SimpleEncoderServerHandle;
NEXUS_SimpleEncoderServerHandle NEXUS_SimpleEncoderServer_Create(
    void
    );
void NEXUS_SimpleEncoderServer_Destroy(
    NEXUS_SimpleEncoderServerHandle handle
    );
NEXUS_SimpleEncoderHandle NEXUS_SimpleEncoder_Create(
    NEXUS_SimpleEncoderServerHandle server,
    unsigned id
    );
void NEXUS_SimpleEncoder_Destroy(
    NEXUS_SimpleEncoderHandle handle
    );
typedef struct NEXUS_SimpleEncoderServerSettings
{
    unsigned transcodeDisplayIndex;
    _Bool headless;
    NEXUS_AudioMuxOutputHandle audioMuxOutput;
    NEXUS_VideoEncoderHandle videoEncoder;
    NEXUS_PlaypumpHandle playpump[3];
    NEXUS_StcChannelHandle stcChannelTranscode;
    NEXUS_Timebase timebase;
    NEXUS_AudioMixerHandle mixer;
    _Bool nonRealTime;
    NEXUS_SimpleDecoderDisableMode disableMode;
    struct {
        NEXUS_DisplayHandle display;
        NEXUS_SimpleAudioDecoderHandle masterAudio;
        NEXUS_SimpleAudioDecoderHandle slaveAudio;
    } displayEncode;
} NEXUS_SimpleEncoderServerSettings;
void NEXUS_SimpleEncoder_GetServerSettings(
    NEXUS_SimpleEncoderServerHandle server,
    NEXUS_SimpleEncoderHandle handle,
    NEXUS_SimpleEncoderServerSettings *pSettings
    );
NEXUS_Error NEXUS_SimpleEncoder_SetServerSettings(
    NEXUS_SimpleEncoderServerHandle server,
    NEXUS_SimpleEncoderHandle handle,
    const NEXUS_SimpleEncoderServerSettings *pSettings
    );
NEXUS_Error NEXUS_SimpleVideoDecoder_StartPrimer(
    NEXUS_SimpleVideoDecoderHandle handle,
    const NEXUS_SimpleVideoDecoderStartSettings *pSettings
    );
void NEXUS_SimpleVideoDecoder_StopPrimer(
    NEXUS_SimpleVideoDecoderHandle handle
    );
NEXUS_Error NEXUS_SimpleVideoDecoder_StopPrimerAndStartDecode(
    NEXUS_SimpleVideoDecoderHandle handle
    );
NEXUS_Error NEXUS_SimpleVideoDecoder_StopDecodeAndStartPrimer(
    NEXUS_SimpleVideoDecoderHandle handle
    );
void NEXUS_SimpleVideoDecoderPrimer_GetSettings(
    NEXUS_SimpleVideoDecoderHandle handle,
    NEXUS_VideoDecoderPrimerSettings *pSettings
    );
NEXUS_Error NEXUS_SimpleVideoDecoderPrimer_SetSettings(
    NEXUS_SimpleVideoDecoderHandle handle,
    const NEXUS_VideoDecoderPrimerSettings *pSettings
    );
typedef struct NEXUS_SimpleVideoDecoderServer *NEXUS_SimpleVideoDecoderServerHandle;
typedef struct NEXUS_SimpleVideoDecoderServerSettings
{
    _Bool enabled;
    NEXUS_SimpleDecoderDisableMode disableMode;
    NEXUS_VideoDecoderHandle videoDecoder;
    NEXUS_VideoWindowHandle window[7];
    _Bool mainWindow;
    int stcIndex;
    NEXUS_DisplayHandle display[7];
    _Bool mosaic;
} NEXUS_SimpleVideoDecoderServerSettings;
NEXUS_SimpleVideoDecoderServerHandle NEXUS_SimpleVideoDecoderServer_Create(
    void
    );
void NEXUS_SimpleVideoDecoderServer_Destroy(
    NEXUS_SimpleVideoDecoderServerHandle handle
    );
void NEXUS_SimpleVideoDecoder_GetDefaultServerSettings(
    NEXUS_SimpleVideoDecoderServerSettings *pSettings
    );
NEXUS_SimpleVideoDecoderHandle NEXUS_SimpleVideoDecoder_Create(
    NEXUS_SimpleVideoDecoderServerHandle server,
    unsigned index,
    const NEXUS_SimpleVideoDecoderServerSettings *pSettings
    );
void NEXUS_SimpleVideoDecoder_Destroy(
    NEXUS_SimpleVideoDecoderHandle handle
    );
void NEXUS_SimpleVideoDecoder_GetServerSettings(
    NEXUS_SimpleVideoDecoderServerHandle server,
    NEXUS_SimpleVideoDecoderHandle handle,
    NEXUS_SimpleVideoDecoderServerSettings *pSettings
    );
NEXUS_Error NEXUS_SimpleVideoDecoder_SetServerSettings(
    NEXUS_SimpleVideoDecoderServerHandle server,
    NEXUS_SimpleVideoDecoderHandle handle,
    const NEXUS_SimpleVideoDecoderServerSettings *pSettings
    );
void NEXUS_SimpleVideoDecoderModule_SetCacheEnabled(
    NEXUS_SimpleVideoDecoderServerHandle server,
    _Bool enabled
    );
void NEXUS_SimpleVideoDecoderModule_CheckCache(
    NEXUS_SimpleVideoDecoderServerHandle server,
    NEXUS_VideoWindowHandle window,
    NEXUS_VideoDecoderHandle videoDecoder
    );
void NEXUS_SimpleVideoDecoderModule_LoadDefaultSettings(
    NEXUS_VideoDecoderHandle video
    );
void NEXUS_SimpleVideoDecoder_GetStcIndex(
    NEXUS_SimpleVideoDecoderServerHandle server,
    NEXUS_SimpleVideoDecoderHandle handle,
    int *pStcIndex
    );
NEXUS_Error NEXUS_SimpleVideoDecoder_SwapWindows(
    NEXUS_SimpleVideoDecoderServerHandle server,
    NEXUS_SimpleVideoDecoderHandle decoder1,
    NEXUS_SimpleVideoDecoderHandle decoder2
    );
void NEXUS_SimpleStcChannel_SetDefaultAstmSettings_priv(
    const NEXUS_AstmSettings *pSettings
    );
typedef struct NEXUS_SpdifInput *NEXUS_SpdifInputHandle;
typedef struct NEXUS_SpdifInputSettings
{
    _Bool muted;
} NEXUS_SpdifInputSettings;
void NEXUS_SpdifInput_GetDefaultSettings(
    NEXUS_SpdifInputSettings *pSettings
    );
NEXUS_SpdifInputHandle NEXUS_SpdifInput_Open(
    unsigned index,
    const NEXUS_SpdifInputSettings *pSettings
    );
void NEXUS_SpdifInput_Close(
    NEXUS_SpdifInputHandle handle
    );
void NEXUS_SpdifInput_GetSettings(
    NEXUS_SpdifInputHandle handle,
    NEXUS_SpdifInputSettings *pSettings
    );
NEXUS_Error NEXUS_SpdifInput_SetSettings(
    NEXUS_SpdifInputHandle handle,
    const NEXUS_SpdifInputSettings *pSettings
    );
NEXUS_AudioInputHandle NEXUS_SpdifInput_GetConnector(
    NEXUS_SpdifInputHandle handle
    );
typedef struct NEXUS_SpiModuleSettings {
    NEXUS_CommonModuleSettings common;
} NEXUS_SpiModuleSettings;
void NEXUS_SpiModule_GetDefaultSettings(
    NEXUS_SpiModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_SpiModule_Init(
    const NEXUS_SpiModuleSettings *pSettings
    );
void NEXUS_SpiModule_Uninit(void);
typedef struct NEXUS_StillDecoder *NEXUS_StillDecoderHandle;
typedef struct NEXUS_StillDecoderOpenSettings
{
    unsigned fifoSize;
    NEXUS_HeapHandle cdbHeap;
    NEXUS_HeapHandle heap;
    _Bool supportedCodecs[NEXUS_VideoCodec_eMax];
    unsigned maxWidth, maxHeight;
} NEXUS_StillDecoderOpenSettings;
void NEXUS_StillDecoder_GetDefaultOpenSettings(
    NEXUS_StillDecoderOpenSettings *pSettings
    );
NEXUS_StillDecoderHandle NEXUS_StillDecoder_Open(
    NEXUS_VideoDecoderHandle deprecated,
    unsigned index,
    const NEXUS_StillDecoderOpenSettings *pSettings
    );
void NEXUS_StillDecoder_Close(
    NEXUS_StillDecoderHandle handle
    );
typedef struct NEXUS_StillDecoderStartSettings
{
    NEXUS_PidChannelHandle pidChannel;
    NEXUS_VideoCodec codec;
    NEXUS_CallbackDesc endCodeFound;
    NEXUS_CallbackDesc stillPictureReady;
    struct {
        unsigned maxWidth, maxHeight;
        NEXUS_MemoryBlockHandle memory;
        unsigned memoryOffset;
        void *buffer;
        unsigned size;
    } output;
} NEXUS_StillDecoderStartSettings;
void NEXUS_StillDecoder_GetDefaultStartSettings(
    NEXUS_StillDecoderStartSettings *pSettings
    );
NEXUS_Error NEXUS_StillDecoder_Start(
    NEXUS_StillDecoderHandle handle,
    const NEXUS_StillDecoderStartSettings *pSettings
    );
void NEXUS_StillDecoder_Stop(
    NEXUS_StillDecoderHandle handle
    );
typedef struct NEXUS_StillDecoderStatus
{
    _Bool endCodeFound;
    _Bool stillPictureReady;
    unsigned avdStatusBlock;
    struct {
        int mainIndex;
        int mainSwRaveIndex;
    } rave;
} NEXUS_StillDecoderStatus;
NEXUS_Error NEXUS_StillDecoder_GetStatus(
    NEXUS_StillDecoderHandle handle,
    NEXUS_StillDecoderStatus *pStatus
    );
NEXUS_Error NEXUS_StillDecoder_GetStripedSurface(
    NEXUS_StillDecoderHandle handle,
    NEXUS_StripedSurfaceHandle *pStripedSurface
    );
void NEXUS_StillDecoder_ReleaseStripedSurface(
    NEXUS_StillDecoderHandle handle,
    NEXUS_StripedSurfaceHandle stripedSurface
    );
typedef struct NEXUS_StillDecoderMemoryRequest {
    unsigned width;
    unsigned height;
    NEXUS_VideoCodec codec;
} NEXUS_StillDecoderMemoryRequest;
void NEXUS_StillDecoder_GetDefaultMemoryRequest(
    NEXUS_StillDecoderMemoryRequest *pRequest
    );
NEXUS_Error NEXUS_StillDecoder_RequestMemorySize(
    NEXUS_StillDecoderHandle handle,
    const NEXUS_StillDecoderMemoryRequest *pRequest,
    unsigned *pSize
    );
typedef struct NEXUS_StreamMuxModuleSettings
{
    NEXUS_ModuleHandle transport;
    NEXUS_ModuleHandle videoEncoder;
    NEXUS_ModuleHandle audio;
    NEXUS_ModuleHandle core;
} NEXUS_StreamMuxModuleSettings;
void NEXUS_StreamMuxModule_GetDefaultSettings(
    NEXUS_StreamMuxModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_StreamMuxModule_Init(
    const NEXUS_StreamMuxModuleSettings *pSettings
    );
void NEXUS_StreamMuxModule_Uninit(void);
typedef struct NEXUS_SurfaceClient *NEXUS_SurfaceClientHandle;
typedef struct NEXUS_SurfaceRegion {
    uint16_t width;
    uint16_t height;
} NEXUS_SurfaceRegion;
typedef struct NEXUS_SurfaceComposition
{
    NEXUS_SurfaceRegion virtualDisplay;
    NEXUS_Rect position;
    NEXUS_SurfaceRegion clipBase;
    NEXUS_Rect clipRect;
    unsigned zorder;
    _Bool visible;
    _Bool displayCache;
    NEXUS_BlendEquation colorBlend;
    NEXUS_BlendEquation alphaBlend;
    struct {
        NEXUS_Graphics2DColorKey source, dest;
    } colorKey;
    NEXUS_Graphics2DFilterCoeffs horizontalFilter;
    NEXUS_Graphics2DFilterCoeffs verticalFilter;
    _Bool alphaPremultiplySourceEnabled;
    NEXUS_Pixel constantColor;
    int rightViewOffset;
    _Bool colorMatrixEnabled;
    NEXUS_Graphics2DColorMatrix colorMatrix;
    NEXUS_VideoWindowContentMode contentMode;
} NEXUS_SurfaceComposition;
typedef unsigned NEXUS_SurfaceCompositorClientId;
NEXUS_SurfaceClientHandle NEXUS_SurfaceClient_Acquire(
    NEXUS_SurfaceCompositorClientId client_id
    );
void NEXUS_SurfaceClient_Release(
    NEXUS_SurfaceClientHandle client
    );
NEXUS_SurfaceClientHandle NEXUS_SurfaceClient_CreateChild(
    NEXUS_SurfaceClientHandle parent_handle
    );
void NEXUS_SurfaceClient_DestroyChild(
    NEXUS_SurfaceClientHandle child_handle
    );
NEXUS_SurfaceClientHandle NEXUS_SurfaceClient_AcquireVideoWindow(
    NEXUS_SurfaceClientHandle parent_handle,
    unsigned window_id
    );
void NEXUS_SurfaceClient_ReleaseVideoWindow(
    NEXUS_SurfaceClientHandle window_handle
    );
typedef struct NEXUS_SurfaceClientSettings
{
    NEXUS_SurfaceComposition composition;
    NEXUS_CallbackDesc recycled;
    NEXUS_CallbackDesc displayed;
    NEXUS_CallbackDesc displayStatusChanged;
    NEXUS_CallbackDesc windowMoved;
    NEXUS_CallbackDesc vsync;
    NEXUS_VideoOrientation orientation;
    unsigned virtualRefreshRate;
    _Bool allowCompositionBypass;
} NEXUS_SurfaceClientSettings;
NEXUS_Error NEXUS_SurfaceClient_SetSurface(
    NEXUS_SurfaceClientHandle handle,
    NEXUS_SurfaceHandle surface
    );
NEXUS_Error NEXUS_SurfaceClient_UpdateSurface(
    NEXUS_SurfaceClientHandle handle,
    const NEXUS_Rect *pUpdateRect
    );
NEXUS_Error NEXUS_SurfaceClient_PushSurface(
    NEXUS_SurfaceClientHandle handle,
    NEXUS_SurfaceHandle surface,
    const NEXUS_Rect *pUpdateRect,
    _Bool infront
    );
NEXUS_Error NEXUS_SurfaceClient_RecycleSurface(
    NEXUS_SurfaceClientHandle handle,
    NEXUS_SurfaceHandle *recycled,
    size_t num_entries,
    size_t *num_returned
    );
void NEXUS_SurfaceClient_Clear(
    NEXUS_SurfaceClientHandle handle
    );
void NEXUS_SurfaceClient_GetSettings(
    NEXUS_SurfaceClientHandle handle,
    NEXUS_SurfaceClientSettings *pSettings
    );
NEXUS_Error NEXUS_SurfaceClient_SetSettings(
    NEXUS_SurfaceClientHandle handle,
    const NEXUS_SurfaceClientSettings *pSettings
    );
typedef struct NEXUS_SurfaceClientStatus
{
    unsigned id;
    _Bool child;
    unsigned parentId;
    NEXUS_Rect position;
    struct {
        _Bool enabled;
        _Bool enabled3d;
        NEXUS_SurfaceRegion framebuffer;
        NEXUS_SurfaceRegion screen;
        unsigned numFramebuffers;
    } display;
} NEXUS_SurfaceClientStatus;
NEXUS_Error NEXUS_SurfaceClient_GetStatus(
    NEXUS_SurfaceClientHandle handle,
    NEXUS_SurfaceClientStatus *pStatus
    );
NEXUS_Error NEXUS_SurfaceClient_PublishSurface(
    NEXUS_SurfaceClientHandle handle
    );
typedef enum NEXUS_BvnBlock
{
    NEXUS_BvnBlock_eSource,
    NEXUS_BvnBlock_eVfd,
    NEXUS_BvnBlock_eDnr,
    NEXUS_BvnBlock_eMad,
    NEXUS_BvnBlock_eScl,
    NEXUS_BvnBlock_eCap,
    NEXUS_BvnBlock_eMax
} NEXUS_BvnBlock;
typedef struct NEXUS_VideoWindowColorKey
{
    _Bool enabled;
    uint8_t lower;
    uint8_t upper;
    uint8_t mask;
} NEXUS_VideoWindowColorKey;
typedef struct NEXUS_VideoWindowSettings
{
    NEXUS_Rect position;
    NEXUS_Rect clipRect;
    NEXUS_Rect clipBase;
    struct {
        unsigned left, right, top, bottom;
    } sourceClip;
    _Bool visible;
    unsigned zorder;
    NEXUS_VideoWindowContentMode contentMode;
    _Bool letterBoxDetect;
    NEXUS_CallbackDesc letterBoxDetectionChange;
    _Bool letterBoxAutoCut;
    NEXUS_PixelFormat pixelFormat;
    _Bool forceCapture;
    _Bool autoMaster;
    uint8_t alpha;
    NEXUS_CompositorBlendFactor sourceBlendFactor;
    NEXUS_CompositorBlendFactor destBlendFactor;
    uint8_t constantAlpha;
    NEXUS_HeapHandle heap;
    NEXUS_VideoFormat minimumSourceFormat;
    NEXUS_VideoFormat minimumDisplayFormat;
    _Bool allocateFullScreen;
    unsigned delay;
    struct {
        _Bool enabled;
        unsigned horizontalTolerance;
        unsigned verticalTolerance;
    } scaleFactorRounding;
    NEXUS_CallbackDesc outputRectChanged;
    _Bool preferSyncLock;
    struct {
        _Bool enabled;
        NEXUS_Rect position;
        NEXUS_Pixel color;
    } clearRect;
    struct {
        int rightViewOffset;
    } window3DSettings;
    struct {
        NEXUS_BvnBlock bvnBlock;
        unsigned crcQueueSize;
    } crc;
    unsigned userCaptureBufferCount;
    struct {
        NEXUS_VideoWindowColorKey luma;
        NEXUS_VideoWindowColorKey cb;
        NEXUS_VideoWindowColorKey cr;
    } colorKey;
} NEXUS_VideoWindowSettings;
NEXUS_VideoWindowHandle NEXUS_VideoWindow_Open(
    NEXUS_DisplayHandle display,
    unsigned windowIndex
    );
void NEXUS_VideoWindow_Close(
    NEXUS_VideoWindowHandle window
    );
void NEXUS_VideoWindow_GetSettings(
    NEXUS_VideoWindowHandle window,
    NEXUS_VideoWindowSettings *pSettings
    );
NEXUS_Error NEXUS_VideoWindow_SetSettings(
    NEXUS_VideoWindowHandle window,
    const NEXUS_VideoWindowSettings *pSettings
    );
typedef struct NEXUS_VideoWindowStatus
{
    unsigned delay;
    int phaseDelay;
    NEXUS_Rect outputRect;
    _Bool isSyncLocked;
} NEXUS_VideoWindowStatus;
NEXUS_Error NEXUS_VideoWindow_GetStatus(
    NEXUS_VideoWindowHandle window,
    NEXUS_VideoWindowStatus *pStatus
    );
NEXUS_Error NEXUS_VideoWindow_AddInput(
    NEXUS_VideoWindowHandle window,
    NEXUS_VideoInputHandle input
    );
NEXUS_Error NEXUS_VideoWindow_RemoveInput(
    NEXUS_VideoWindowHandle window,
    NEXUS_VideoInputHandle input
    );
void NEXUS_VideoWindow_RemoveAllInputs(
    NEXUS_VideoWindowHandle window
    );
NEXUS_SurfaceHandle NEXUS_VideoWindow_CaptureVideoBuffer(
    NEXUS_VideoWindowHandle window
    );
NEXUS_Error NEXUS_VideoWindow_ReleaseVideoBuffer(
    NEXUS_VideoWindowHandle window,
    NEXUS_SurfaceHandle surface
    );
typedef enum NEXUS_VideoWindowSplitScreenMode
{
    NEXUS_VideoWindowSplitScreenMode_eDisable = 0,
    NEXUS_VideoWindowSplitScreenMode_eLeft,
    NEXUS_VideoWindowSplitScreenMode_eRight
} NEXUS_VideoWindowSplitScreenMode;
typedef struct NEXUS_VideoWindowSplitScreenSettings
{
    NEXUS_VideoWindowSplitScreenMode hue;
    NEXUS_VideoWindowSplitScreenMode contrast;
    NEXUS_VideoWindowSplitScreenMode brightness;
    NEXUS_VideoWindowSplitScreenMode colorTemp;
    NEXUS_VideoWindowSplitScreenMode sharpness;
    NEXUS_VideoWindowSplitScreenMode contrastStretch;
    NEXUS_VideoWindowSplitScreenMode dnr;
    NEXUS_VideoWindowSplitScreenMode anr;
    NEXUS_VideoWindowSplitScreenMode dejagging;
    NEXUS_VideoWindowSplitScreenMode deringing;
    NEXUS_VideoWindowSplitScreenMode cm3d;
    NEXUS_VideoWindowSplitScreenMode cms;
    NEXUS_VideoWindowSplitScreenMode autoFlesh;
    NEXUS_VideoWindowSplitScreenMode blueBoost;
    NEXUS_VideoWindowSplitScreenMode greenBoost;
    NEXUS_VideoWindowSplitScreenMode blueStretch;
} NEXUS_VideoWindowSplitScreenSettings;
void NEXUS_VideoWindow_GetSplitScreenSettings(
    NEXUS_VideoWindowHandle window,
    NEXUS_VideoWindowSplitScreenSettings *pSettings
    );
NEXUS_Error NEXUS_VideoWindow_SetSplitScreenSettings(
    NEXUS_VideoWindowHandle window,
    const NEXUS_VideoWindowSplitScreenSettings *pSettings
    );
void NEXUS_VideoWindow_GetColorMatrix(
    NEXUS_VideoWindowHandle window,
    NEXUS_ColorMatrix *pSettings
    );
NEXUS_Error NEXUS_VideoWindow_SetColorMatrix(
    NEXUS_VideoWindowHandle window,
    const NEXUS_ColorMatrix *pSettings
    );
typedef struct NEXUS_VideoWindowLetterBoxStatus
{
    unsigned whiteBoxLeft;
    unsigned whiteBoxTop;
    unsigned whiteBoxWidth;
    unsigned whiteBoxHeight;
    unsigned grayWidthTop;
    unsigned grayWidthLeft;
    unsigned grayWidthRight;
    unsigned grayWidthBottom;
    unsigned edgeStrengthTop;
    unsigned edgeStrengthLeft;
    unsigned edgeStrengthRight;
    unsigned edgeStrengthBottom;
} NEXUS_VideoWindowLetterBoxStatus;
NEXUS_Error NEXUS_VideoWindow_GetLetterBoxStatus(
    NEXUS_VideoWindowHandle window,
    NEXUS_VideoWindowLetterBoxStatus *pStatus
    );
typedef struct NEXUS_CalculateVideoWindowPositionSettings {
    unsigned horizontalClipping;
    unsigned verticalClipping;
    int horizontalPosition;
    int verticalPosition;
    NEXUS_VideoWindowContentMode manualAspectRatioCorrection;
    NEXUS_AspectRatio sourceAspectRatio;
    unsigned sourceWidth;
    unsigned sourceHeight;
    struct {
        unsigned x, y;
    } sampleAspectRatio;
    NEXUS_Rect viewport;
    NEXUS_DisplayAspectRatio displayAspectRatio;
    unsigned displayWidth;
    unsigned displayHeight;
} NEXUS_CalculateVideoWindowPositionSettings;
void NEXUS_GetDefaultCalculateVideoWindowPositionSettings(
    NEXUS_CalculateVideoWindowPositionSettings *pSettings
    );
NEXUS_Error NEXUS_CalculateVideoWindowPosition(
    const NEXUS_CalculateVideoWindowPositionSettings *pSettings,
    const NEXUS_VideoWindowSettings *pInputWindowSettings,
    NEXUS_VideoWindowSettings *pOutputWindowSettings
    );
void NEXUS_VideoWindow_GetAfdSettings(
    NEXUS_VideoWindowHandle window,
    NEXUS_VideoWindowAfdSettings *pSettings
    );
NEXUS_Error NEXUS_VideoWindow_SetAfdSettings(
    NEXUS_VideoWindowHandle window,
    const NEXUS_VideoWindowAfdSettings *pSettings
    );
typedef struct NEXUS_VideoWindowCrcData
{
    struct {
        uint32_t luma;
        uint32_t chroma;
    } bvn;
} NEXUS_VideoWindowCrcData;
NEXUS_Error NEXUS_VideoWindow_GetCrcData(
    NEXUS_VideoWindowHandle window,
    NEXUS_VideoWindowCrcData *pData,
    unsigned numEntries,
    unsigned *pNumEntriesReturned
    );
typedef struct NEXUS_SurfaceCompositor *NEXUS_SurfaceCompositorHandle;
NEXUS_SurfaceCompositorHandle NEXUS_SurfaceCompositor_Create(
    unsigned server_id
    );
void NEXUS_SurfaceCompositor_Destroy(
    NEXUS_SurfaceCompositorHandle handle
    );
NEXUS_SurfaceClientHandle NEXUS_SurfaceCompositor_CreateClient(
    NEXUS_SurfaceCompositorHandle handle,
    NEXUS_SurfaceCompositorClientId client_id
    );
void NEXUS_SurfaceCompositor_DestroyClient(
    NEXUS_SurfaceClientHandle client
    );
typedef struct NEXUS_SurfaceCompositorDisplaySettings {
    NEXUS_GraphicsSettings graphicsSettings;
    _Bool manualPosition;
    NEXUS_DisplayHandle display;
    struct {
        unsigned number;
        unsigned width, height;
        NEXUS_Pixel backgroundColor;
        NEXUS_PixelFormat pixelFormat;
        NEXUS_HeapHandle heap;
    } framebuffer;
    struct {
       _Bool overrideOrientation;
       NEXUS_VideoOrientation orientation;
    } display3DSettings;
} NEXUS_SurfaceCompositorDisplaySettings;
typedef struct NEXUS_SurfaceCompositorSettings
{
    _Bool enabled;
    NEXUS_CallbackDesc inactiveCallback;
    NEXUS_SurfaceCompositorDisplaySettings display[7];
    NEXUS_CallbackDesc frameBufferCallback;
    _Bool muteVideo[7];
    struct {
        unsigned width;
        unsigned height;
        NEXUS_HeapHandle heap;
    } bounceBuffer;
    _Bool allowCompositionBypass;
} NEXUS_SurfaceCompositorSettings;
void NEXUS_SurfaceCompositor_GetSettings(
    NEXUS_SurfaceCompositorHandle handle,
    NEXUS_SurfaceCompositorSettings *pSettings
    );
NEXUS_Error NEXUS_SurfaceCompositor_SetSettings(
    NEXUS_SurfaceCompositorHandle handle,
    const NEXUS_SurfaceCompositorSettings *pSettings
    );
typedef struct NEXUS_SurfaceCompositorClientDisplaySettings {
    struct {
        unsigned id;
        NEXUS_VideoWindowHandle window;
    } window[16];
} NEXUS_SurfaceCompositorClientDisplaySettings;
typedef struct NEXUS_SurfaceCompositorClientSettings
{
    NEXUS_SurfaceComposition composition;
    _Bool tunnelCapable;
    NEXUS_SurfaceCompositorClientDisplaySettings display[7];
} NEXUS_SurfaceCompositorClientSettings;
void NEXUS_SurfaceCompositor_GetClientSettings(
    NEXUS_SurfaceCompositorHandle handle,
    NEXUS_SurfaceClientHandle client,
    NEXUS_SurfaceCompositorClientSettings *pSettings
    );
NEXUS_Error NEXUS_SurfaceCompositor_SetClientSettings(
    NEXUS_SurfaceCompositorHandle handle,
    NEXUS_SurfaceClientHandle client,
    const NEXUS_SurfaceCompositorClientSettings *pSettings
    );
NEXUS_Error NEXUS_SurfaceCompositor_SwapWindows(
    NEXUS_SurfaceCompositorHandle handle,
    NEXUS_SurfaceClientHandle surfaceClient0,
    unsigned windowId0,
    NEXUS_SurfaceClientHandle surfaceClient1,
    unsigned windowId1
    );
typedef struct NEXUS_SurfaceCompositorStatus
{
    _Bool active;
    unsigned numAcquiredTunneledSurfaces;
} NEXUS_SurfaceCompositorStatus;
NEXUS_Error NEXUS_SurfaceCompositor_GetStatus(
    NEXUS_SurfaceCompositorHandle handle,
    NEXUS_SurfaceCompositorStatus *pStatus
    );
NEXUS_Error NEXUS_SurfaceCompositor_GetCurrentFramebuffer(
    NEXUS_SurfaceCompositorHandle handle,
    NEXUS_SurfaceHandle *pSurface
    );
typedef struct NEXUS_SurfaceCompositorModuleSettings
{
    struct {
        NEXUS_ModuleHandle display;
    } modules;
} NEXUS_SurfaceCompositorModuleSettings;
void NEXUS_SurfaceCompositorModule_GetDefaultSettings( NEXUS_SurfaceCompositorModuleSettings *pSettings );
NEXUS_ModuleHandle NEXUS_SurfaceCompositorModule_Init( const NEXUS_SurfaceCompositorModuleSettings *pSettings );
void NEXUS_SurfaceCompositorModule_Uninit(void);
typedef struct NEXUS_SurfaceCursor *NEXUS_SurfaceCursorHandle;
typedef struct NEXUS_SurfaceCursorCreateSettings {
    struct {
        NEXUS_SurfaceRegion maxSize;
    } display[7];
    NEXUS_SurfaceHandle surface;
} NEXUS_SurfaceCursorCreateSettings;
typedef struct NEXUS_SurfaceCursorSettings {
    NEXUS_SurfaceComposition composition;
} NEXUS_SurfaceCursorSettings;
void NEXUS_SurfaceCursor_GetDefaultCreateSettings(
    NEXUS_SurfaceCursorCreateSettings *createSettings
   );
NEXUS_SurfaceCursorHandle NEXUS_SurfaceCursor_Create(
    NEXUS_SurfaceCompositorHandle surfaceCompositor,
    const NEXUS_SurfaceCursorCreateSettings *createSettings
   );
void NEXUS_SurfaceCursor_Destroy(
    NEXUS_SurfaceCursorHandle cursor
    );
void NEXUS_SurfaceCursor_GetSettings (
    NEXUS_SurfaceCursorHandle cursor,
    NEXUS_SurfaceCursorSettings *settings
    );
NEXUS_Error NEXUS_SurfaceCursor_SetSettings (
    NEXUS_SurfaceCursorHandle cursor,
    const NEXUS_SurfaceCursorSettings *settings
    );
typedef struct NEXUS_SyncChannelModuleSettings
{
    struct
    {
        NEXUS_ModuleHandle audio;
        NEXUS_ModuleHandle display;
    } modules;
    struct {
        _Bool requireFullScreen;
        unsigned tsmLockTimeout;
        unsigned unmuteTimeout;
        unsigned unconditionalUnmuteTimeout;
        struct
        {
            unsigned timeout;
            unsigned acceptableMtbcLower;
            unsigned acceptableMtbcUpper;
            unsigned acceptableTtlc;
        } rateMismatchDetection;
        struct
        {
            unsigned timeout;
            unsigned acceptableTtlc;
        } rateRematchDetection;
    } video;
    struct
    {
        unsigned unmuteTimeout;
        unsigned receiverDelayCompensation;
        unsigned unconditionalUnmuteTimeout;
    } audio;
} NEXUS_SyncChannelModuleSettings;
void NEXUS_SyncChannelModule_GetDefaultSettings(
    NEXUS_SyncChannelModuleSettings *pSettings
    );
NEXUS_ModuleHandle NEXUS_SyncChannelModule_Init(
    const NEXUS_SyncChannelModuleSettings *pSettings
    );
void NEXUS_SyncChannelModule_Uninit(void);
typedef struct NEXUS_TruVolume *NEXUS_TruVolumeHandle;
void NEXUS_TruVolume_GetDefaultSettings(
    NEXUS_TruVolumeSettings *pSettings
    );
NEXUS_TruVolumeHandle NEXUS_TruVolume_Open(
    const NEXUS_TruVolumeSettings *pSettings
    );
void NEXUS_TruVolume_Close(
    NEXUS_TruVolumeHandle handle
    );
void NEXUS_TruVolume_GetSettings(
    NEXUS_TruVolumeHandle handle,
    NEXUS_TruVolumeSettings *pSettings
    );
NEXUS_Error NEXUS_TruVolume_SetSettings(
    NEXUS_TruVolumeHandle handle,
    const NEXUS_TruVolumeSettings *pSettings
    );
NEXUS_AudioInputHandle NEXUS_TruVolume_GetConnector(
    NEXUS_TruVolumeHandle handle
    );
NEXUS_Error NEXUS_TruVolume_AddInput(
    NEXUS_TruVolumeHandle handle,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_TruVolume_RemoveInput(
    NEXUS_TruVolumeHandle handle,
    NEXUS_AudioInputHandle input
    );
NEXUS_Error NEXUS_TruVolume_RemoveAllInputs(
    NEXUS_TruVolumeHandle handle
    );
typedef struct NEXUS_VcxoSettings
{
    NEXUS_Timebase timebase;
} NEXUS_VcxoSettings;
void NEXUS_Vcxo_GetSettings(
    NEXUS_Vcxo vcxo,
    NEXUS_VcxoSettings *pSettings
    );
NEXUS_Error NEXUS_Vcxo_SetSettings(
    NEXUS_Vcxo vcxo,
    const NEXUS_VcxoSettings *pSettings
    );
void NEXUS_VideoWindow_GetDefaultDnrSettings(
    NEXUS_VideoWindowDnrSettings *pSettings
    );
void NEXUS_VideoWindow_GetDnrSettings(
    NEXUS_VideoWindowHandle window,
    NEXUS_VideoWindowDnrSettings *pSettings
    );
NEXUS_Error NEXUS_VideoWindow_SetDnrSettings(
    NEXUS_VideoWindowHandle window,
    const NEXUS_VideoWindowDnrSettings *pSettings
    );
NEXUS_Error NEXUS_VideoWindow_SetCustomDnrSettings(
    NEXUS_VideoWindowHandle window,
    const NEXUS_VideoWindowDnrSettings *pSettings,
    const uint8_t *pCustomData,
    unsigned numEntries
    );
void NEXUS_VideoWindow_GetDefaultAnrSettings(
    NEXUS_VideoWindowAnrSettings *pSettings
    );
void NEXUS_VideoWindow_GetAnrSettings(
    NEXUS_VideoWindowHandle window,
    NEXUS_VideoWindowAnrSettings *pSettings
    );
NEXUS_Error NEXUS_VideoWindow_SetAnrSettings(
    NEXUS_VideoWindowHandle window,
    const NEXUS_VideoWindowAnrSettings *pSettings
    );
NEXUS_Error NEXUS_VideoWindow_SetCustomAnrSettings(
    NEXUS_VideoWindowHandle window,
    const NEXUS_VideoWindowAnrSettings *pSettings,
    const uint8_t *pCustomData,
    unsigned numEntries
    );
void NEXUS_VideoWindow_GetDefaultMadSettings(
    NEXUS_VideoWindowMadSettings *pSettings
    );
void NEXUS_VideoWindow_GetMadSettings(
    NEXUS_VideoWindowHandle window,
    NEXUS_VideoWindowMadSettings *pSettings
    );
NEXUS_Error NEXUS_VideoWindow_SetMadSettings(
    NEXUS_VideoWindowHandle window,
    const NEXUS_VideoWindowMadSettings *pSettings
    );
void NEXUS_VideoWindow_GetDefaultScalerSettings(
    NEXUS_VideoWindowScalerSettings *pSettings
    );
void NEXUS_VideoWindow_GetScalerSettings(
    NEXUS_VideoWindowHandle window,
    NEXUS_VideoWindowScalerSettings *pSettings
    );
NEXUS_Error NEXUS_VideoWindow_SetScalerSettings(
    NEXUS_VideoWindowHandle window,
    const NEXUS_VideoWindowScalerSettings *pSettings
    );
NEXUS_Error NEXUS_VideoWindow_SetGameModeDelay(
    NEXUS_VideoWindowHandle window,
    const NEXUS_VideoWindowGameModeDelay *pSettings
    );
void NEXUS_VideoWindow_GetGameModeDelay(
    NEXUS_VideoWindowHandle window,
    NEXUS_VideoWindowGameModeDelay *pSettings
    );
typedef struct NEXUS_VideoWindowCoefficientIndexSettings
{
    uint32_t sclVertLuma;
    uint32_t sclHorzLuma;
    uint32_t sclVertChroma;
    uint32_t sclHorzChroma;
    uint32_t hsclHorzLuma;
    uint32_t hsclHorzChroma;
    uint32_t madHorzLuma;
    uint32_t madHorzChroma;
} NEXUS_VideoWindowCoefficientIndexSettings;
void NEXUS_VideoWindow_GetCoefficientIndexSettings(
    NEXUS_VideoWindowHandle window,
    NEXUS_VideoWindowCoefficientIndexSettings *pSettings
    );
NEXUS_Error NEXUS_VideoWindow_SetCoefficientIndexSettings(
    NEXUS_VideoWindowHandle window,
    const NEXUS_VideoWindowCoefficientIndexSettings *pSettings
    );
typedef struct NEXUS_VideoDecoderPrimer *NEXUS_VideoDecoderPrimerHandle;
typedef struct NEXUS_VideoDecoderPrimerCreateSettings
{
    unsigned fifoSize;
    unsigned maximumGops;
} NEXUS_VideoDecoderPrimerCreateSettings;
void NEXUS_VideoDecoderPrimer_GetDefaultCreateSettings(
    NEXUS_VideoDecoderPrimerCreateSettings *pSettings
    );
NEXUS_VideoDecoderPrimerHandle NEXUS_VideoDecoderPrimer_Create(
    const NEXUS_VideoDecoderPrimerCreateSettings *pSettings
    );
void NEXUS_VideoDecoderPrimer_Destroy(
    NEXUS_VideoDecoderPrimerHandle primer
    );
NEXUS_Error NEXUS_VideoDecoderPrimer_Start(
    NEXUS_VideoDecoderPrimerHandle primer,
    const NEXUS_VideoDecoderStartSettings *pStartSettings
    );
void NEXUS_VideoDecoderPrimer_Stop(
    NEXUS_VideoDecoderPrimerHandle primer
    );
NEXUS_Error NEXUS_VideoDecoderPrimer_StopPrimerAndStartDecode(
    NEXUS_VideoDecoderPrimerHandle primer,
    NEXUS_VideoDecoderHandle videoDecoder
    );
NEXUS_Error NEXUS_VideoDecoderPrimer_StopDecodeAndStartPrimer(
    NEXUS_VideoDecoderPrimerHandle primer,
    NEXUS_VideoDecoderHandle videoDecoder
    );
void NEXUS_VideoDecoderPrimer_GetSettings(
    NEXUS_VideoDecoderPrimerHandle primer,
    NEXUS_VideoDecoderPrimerSettings *pSettings
    );
NEXUS_Error NEXUS_VideoDecoderPrimer_SetSettings(
    NEXUS_VideoDecoderPrimerHandle primer,
    const NEXUS_VideoDecoderPrimerSettings *pSettings
    );
NEXUS_Error NEXUS_VideoDecoderPrimer_GetStatus(
    NEXUS_VideoDecoderPrimerHandle primer,
    NEXUS_VideoDecoderStatus *pStatus
    );
NEXUS_VideoDecoderPrimerHandle NEXUS_VideoDecoderPrimer_Open(
    NEXUS_VideoDecoderHandle videoDecoder
    );
void NEXUS_VideoDecoderPrimer_Close( NEXUS_VideoDecoderPrimerHandle primer );
typedef struct NEXUS_VideoDecoderPrivateSettings
{
    NEXUS_CallbackDesc streamChanged;
} NEXUS_VideoDecoderPrivateSettings;
void NEXUS_VideoDecoder_GetPrivateSettings(
    NEXUS_VideoDecoderHandle videoDecoder,
    NEXUS_VideoDecoderPrivateSettings * pSettings);
NEXUS_Error NEXUS_VideoDecoder_SetPrivateSettings(
    NEXUS_VideoDecoderHandle videoDecoder,
    const NEXUS_VideoDecoderPrivateSettings * pSettings);
typedef enum NEXUS_HdDviDataMode
{
    NEXUS_HdDviDataMode_e24bit,
    NEXUS_HdDviDataMode_e30bit,
    NEXUS_HdDviDataMode_e36bit,
    NEXUS_HdDviDataMode_eMax
} NEXUS_HdDviDataMode;
typedef struct NEXUS_VideoHdmiInputSettings {
    _Bool autoFormat;
    NEXUS_VideoFormat format;
    _Bool autoPosition;
    struct {
        unsigned x,y;
    } position;
    NEXUS_HdDviDataMode dataMode;
    _Bool deEnabled;
    _Bool externalInput;
    struct
    {
        unsigned width;
        unsigned height;
    } formatTolerance;
} NEXUS_VideoHdmiInputSettings;
void NEXUS_VideoHdmiInput_GetSettings(
    NEXUS_VideoInputHandle hdmiInput,
    NEXUS_VideoHdmiInputSettings *pSettings
    );
NEXUS_Error NEXUS_VideoHdmiInput_SetSettings(
    NEXUS_VideoInputHandle hdmiInput,
    const NEXUS_VideoHdmiInputSettings *pSettings
    );
NEXUS_Error NEXUS_VideoInput_GetCrcData(
    NEXUS_VideoInputHandle input,
    NEXUS_VideoInputCrcData *pData,
    unsigned numEntries,
    unsigned *pNumEntriesReturned
    );
typedef struct NEXUS_VideoInputVbiSettings
{
    NEXUS_CallbackDesc wssChanged;
    NEXUS_CallbackDesc cgmsChanged;
    NEXUS_CallbackDesc vpsChanged;
    NEXUS_CallbackDesc closedCaptionDataReady;
    NEXUS_CallbackDesc teletextDataReady;
    NEXUS_CallbackDesc gemStarDataReady;
    _Bool closedCaptionEnabled;
    _Bool teletextEnabled;
    _Bool gemStarEnabled;
    unsigned closedCaptionBufferSize;
    unsigned teletextBufferSize;
    unsigned gemStarBufferSize;
    struct {
        unsigned baseLineTop;
        uint16_t lineMaskTop;
        unsigned baseLineBottom;
        uint16_t lineMaskBottom;
    } gemStar;
    struct {
        uint16_t vline576i;
    } wss;
    struct {
        uint16_t ccLineTop;
        uint16_t ccLineBottom;
    } cc;
} NEXUS_VideoInputVbiSettings;
void NEXUS_VideoInput_GetVbiSettings(
    NEXUS_VideoInputHandle handle,
    NEXUS_VideoInputVbiSettings *pSettings
    );
NEXUS_Error NEXUS_VideoInput_SetVbiSettings(
    NEXUS_VideoInputHandle handle,
    const NEXUS_VideoInputVbiSettings *pSettings
    );
NEXUS_Error NEXUS_VideoInput_ReadTeletext(
    NEXUS_VideoInputHandle handle,
    NEXUS_TeletextLine *pLines,
    size_t numLines,
    size_t *pNumLinesRead
    );
void NEXUS_VideoInput_FlushTeletext(
    NEXUS_VideoInputHandle videoInput
    );
NEXUS_Error NEXUS_VideoInput_ReadClosedCaption(
    NEXUS_VideoInputHandle handle,
    NEXUS_ClosedCaptionData *pEntries,
    size_t numEntries,
    size_t *pNumEntriesRead
    );
void NEXUS_VideoInput_FlushClosedCaption(
    NEXUS_VideoInputHandle videoInput
    );
NEXUS_Error NEXUS_VideoInput_ReadGemStar(
    NEXUS_VideoInputHandle handle,
    NEXUS_GemStarData *pEntries,
    size_t numEntries,
    size_t *pNumEntriesRead
    );
void NEXUS_VideoInput_FlushGemStar(
    NEXUS_VideoInputHandle videoInput
    );
NEXUS_Error NEXUS_VideoInput_GetWss(
    NEXUS_VideoInputHandle handle,
    uint16_t *pWssData
    );
void NEXUS_VideoInput_FlushWss(
    NEXUS_VideoInputHandle videoInput
    );
NEXUS_Error NEXUS_VideoInput_GetCgms(
    NEXUS_VideoInputHandle handle,
    uint32_t *pCgmsData
    );
void NEXUS_VideoInput_FlushCgms(
    NEXUS_VideoInputHandle videoInput
    );
NEXUS_Error NEXUS_VideoInput_GetVps(
    NEXUS_VideoInputHandle handle,
    NEXUS_VpsData *pData
    );
void NEXUS_VideoInput_FlushVps(
    NEXUS_VideoInputHandle videoInput
    );
void NEXUS_VideoOutput_Shutdown(
    NEXUS_VideoOutputHandle output
    );
typedef struct NEXUS_VideoOutputVfFilter
{
    uint32_t filterRegs[16];
    unsigned numEntries;
    uint32_t SUM_OF_TAPS;
} NEXUS_VideoOutputVfFilter;
void NEXUS_VideoOutput_GetVfFilter(
    NEXUS_VideoOutputHandle output,
    NEXUS_VideoDac dac,
    NEXUS_VideoOutputVfFilter *pFilter
    );
NEXUS_Error NEXUS_VideoOutput_SetVfFilter(
    NEXUS_VideoOutputHandle output,
    NEXUS_VideoDac dac,
    const NEXUS_VideoOutputVfFilter *pFilter
    );
typedef struct NEXUS_VideoOutputSettings
{
    _Bool mute;
} NEXUS_VideoOutputSettings;
void NEXUS_VideoOutput_GetSettings(
    NEXUS_VideoOutputHandle output,
    NEXUS_VideoOutputSettings *pSettings
    );
NEXUS_Error NEXUS_VideoOutput_SetSettings(
    NEXUS_VideoOutputHandle output,
    const NEXUS_VideoOutputSettings *pSettings
    );
typedef enum NEXUS_VideoOutputConnectionState
{
    NEXUS_VideoOutputConnectionState_eUnknown,
    NEXUS_VideoOutputConnectionState_eConnected,
    NEXUS_VideoOutputConnectionState_eDisconnected,
    NEXUS_VideoOutputConnectionState_eMax
} NEXUS_VideoOutputConnectionState;
typedef struct NEXUS_VideoOutputStatus
{
    NEXUS_VideoOutputConnectionState connectionState;
} NEXUS_VideoOutputStatus;
NEXUS_Error NEXUS_VideoOutput_GetStatus(
    NEXUS_VideoOutputHandle output,
    NEXUS_VideoOutputStatus *pStatus
    );
NEXUS_Error NEXUS_Watchdog_SetTimeout(
    unsigned timeout
    );
NEXUS_Error NEXUS_Watchdog_StartTimer(void);
NEXUS_Error NEXUS_Watchdog_StopTimer(void);
void NEXUS_Watchdog_GetLastResetStatus(
    _Bool *pStatus
    );
typedef struct NEXUS_WatchdogCallback *NEXUS_WatchdogCallbackHandle;
typedef struct NEXUS_WatchdogCallbackSettings
{
    NEXUS_CallbackDesc midpointCallback;
} NEXUS_WatchdogCallbackSettings;
void NEXUS_WatchdogCallback_GetDefaultSettings(
    NEXUS_WatchdogCallbackSettings *pSettings
    );
NEXUS_WatchdogCallbackHandle NEXUS_WatchdogCallback_Create(
    const NEXUS_WatchdogCallbackSettings *pSettings
    );
void NEXUS_WatchdogCallback_Destroy(
    NEXUS_WatchdogCallbackHandle handle
    );
