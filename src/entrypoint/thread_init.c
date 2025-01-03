// SPDX-FileCopyrightText: 2023 - 2024 Ledger SAS
//
// SPDX-License-Identifier: Apache-2.0 OR BSD-3-Clause

#include <stdint.h>

#include <uapi.h>
#include "libc_init.h"
#include "../include/shield/private/rand.h"

/**
 * Canari variable, as defined in LLVM & GCC compiler documentation, in order to
 * be manipulated each time a new frame is added on stack
 * INFO: this file is not compiled in UT mode
 */
uint32_t __stack_chk_guard = 0;

extern int main(void);

/**
 * When starting a thread, the thread identifer and the SSP seed is
 * passed by the Sentry kernel. The effective thread entrypoint symbol
 * address is passed as third argument.
 * This very stack-based thread identifier is used by the errno internals to
 * differentiate which thread-safe errno value to use.
 * The seed is used to set the compiler-handled SSP balue.
 */
void __attribute__((no_stack_protector, noreturn, used))
_start(uint32_t const thread_id, uint32_t const seed)
{
    int task_ret;
    /* here, the kernel alreay have copied data and zeroified bss section */
    /* set the current SSP to kernel-given seed (stack-passed) */
    __stack_chk_guard = seed;
    __libc_init(); /* initiate libc-relative ontext, if needed (globlals, etc.) */
    __shield_rand_set_seed(seed);
    /* calling thread entrypoint. the main function being implemented out of this file, SSP is active */
    task_ret = main();
    /* End of thread, store exit value in kernel thread information */
#if CONFIG_WITH_SENTRY
    __sys_exit(task_ret);
#else
# error "no supported backend"
#endif

    __builtin_unreachable();
}
