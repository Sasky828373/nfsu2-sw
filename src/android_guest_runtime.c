#if defined(__ANDROID__)

#include "android_guest_runtime.h"

#include <android/log.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/*
 * Existing xboxrecomp dispatcher.
 *
 * Keep the original x86/NV2A runtime. This layer only centralizes
 * Android -> guest execution.
 */
typedef void (*nfsu2_recomp_func_t)(void);

extern void recomp_dispatch_init(void);
extern nfsu2_recomp_func_t recomp_lookup(uint32_t address);
extern nfsu2_recomp_func_t recomp_lookup_manual(uint32_t address);

static void runtime_log(const char *msg)
{
    __android_log_print(
        ANDROID_LOG_INFO,
        "NFSU2-RUNTIME",
        "%s",
        msg);

    FILE *f = fopen(
        "/storage/emulated/0/NFSU2/nfsu2-crash.log",
        "a");

    if (f) {
        fprintf(f, "RUNTIME: %s\n", msg);
        fflush(f);
        fclose(f);
    }
}

int nfsu2_guest_runtime_init(
    Nfsu2GuestThread *thread,
    uint32_t entry_point,
    uint32_t stack_top,
    void *memory_base)
{
    if (!thread || !memory_base)
        return 0;

    memset(thread, 0, sizeof(*thread));

    thread->entry_point = entry_point;
    thread->stack_top   = stack_top;
    thread->esp         = stack_top;
    thread->memory_base = memory_base;

    runtime_log("initializing dispatcher");

    recomp_dispatch_init();

    nfsu2_recomp_func_t fn =
        recomp_lookup(entry_point);

    if (!fn)
        fn = recomp_lookup_manual(entry_point);

    if (!fn) {
        runtime_log("entry point lookup FAILED");
        return 0;
    }

    thread->initialized = 1;

    runtime_log("guest runtime initialized");
    return 1;
}

int nfsu2_guest_execute(
    Nfsu2GuestThread *thread,
    uint32_t address)
{
    if (!thread || !thread->initialized) {
        runtime_log("execute without initialized runtime");
        return 0;
    }

    nfsu2_recomp_func_t fn =
        recomp_lookup(address);

    if (!fn)
        fn = recomp_lookup_manual(address);

    if (!fn) {
        runtime_log("guest address lookup FAILED");
        return 0;
    }

    runtime_log("entering guest dispatcher");

    /*
     * Register/TLS state continues to be owned by xboxrecomp.
     * Do NOT invent a second incompatible register context here.
     */
    fn();

    runtime_log("guest dispatcher returned");
    return 1;
}

void nfsu2_guest_runtime_shutdown(
    Nfsu2GuestThread *thread)
{
    if (!thread)
        return;

    runtime_log("guest runtime shutdown");
    thread->initialized = 0;
}

#endif
