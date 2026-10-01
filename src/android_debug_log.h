#pragma once

#if defined(__ANDROID__)

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <android/log.h>

#define NFSU2_LOG_FILE "/storage/emulated/0/NFSU2/nfsu2-crash.log"

static inline void nfsu2_debug_log(const char *fmt, ...)
{
    char message[2048];
    char line[2304];

    va_list ap;
    va_start(ap, fmt);
    vsnprintf(message, sizeof(message), fmt, ap);
    va_end(ap);

    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    snprintf(line, sizeof(line),
             "[%lld.%03lld] pid=%d tid=%d %s\n",
             (long long)ts.tv_sec,
             (long long)(ts.tv_nsec / 1000000),
             getpid(),
             gettid(),
             message);

    __android_log_print(ANDROID_LOG_ERROR,
                        "NFSU2TRACE", "%s", message);

    int fd = open(NFSU2_LOG_FILE,
                  O_WRONLY | O_CREAT | O_APPEND,
                  0666);

    if (fd >= 0) {
        write(fd, line, strlen(line));
        fsync(fd);
        close(fd);
    }
}

static inline void nfsu2_signal_handler(int sig)
{
    nfsu2_debug_log(
        "!!! FATAL SIGNAL %d (%s) !!!",
        sig,
        strsignal(sig)
    );

    signal(sig, SIG_DFL);
    raise(sig);
}

static inline void nfsu2_install_signal_logger(void)
{
    signal(SIGSEGV, nfsu2_signal_handler);
    signal(SIGABRT, nfsu2_signal_handler);
    signal(SIGBUS,  nfsu2_signal_handler);
    signal(SIGILL,  nfsu2_signal_handler);
    signal(SIGFPE,  nfsu2_signal_handler);
}

#endif
