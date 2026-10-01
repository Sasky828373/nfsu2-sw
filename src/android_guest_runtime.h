#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Nfsu2GuestThread {
    uint32_t entry_point;
    uint32_t stack_top;

    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;

    void *memory_base;
    int initialized;
} Nfsu2GuestThread;

int nfsu2_guest_runtime_init(
    Nfsu2GuestThread *thread,
    uint32_t entry_point,
    uint32_t stack_top,
    void *memory_base);

int nfsu2_guest_execute(
    Nfsu2GuestThread *thread,
    uint32_t address);

void nfsu2_guest_runtime_shutdown(
    Nfsu2GuestThread *thread);

#ifdef __cplusplus
}
#endif
