#include "types.h"

/*
 * Reviewed source unit: src/main/init_37F0.c
 * Boundary evidence: docs/evidence/main_system_wrapper_boundaries.md
 */

typedef struct ThreadState {
    struct ThreadState *next;
    s32 priority;
    struct ThreadState **queue;
    struct ThreadState *activeNext;
    u16 state;
    u16 flags;
    s32 id;
    s32 fp;
    u8 pad1C[0x1C];
    u64 argument;
    u8 pad40[0xB0];
    u64 stack;
    u8 padF8[8];
    u64 returnAddress;
    u8 pad108[0x10];
    u32 status;
    u32 pc;
    u8 pad120[8];
    u32 rcp;
    u32 fpcsr;
} ThreadState;

s32 func_80022DC0(void);
void func_80022DE0(s32);
extern u8 D_10007BF8;
extern ThreadState *D_8002BDFC;

void func_800037F0(ThreadState *thread, s32 id, void (*entry)(void *),
                   void *argument, void *stack, s32 priority) {
    s32 mask;

    thread->id = id;
    thread->priority = priority;
    thread->next = 0;
    thread->queue = 0;
    thread->pc = (u32)entry;
    thread->argument = (s64)(s32)argument;
    thread->stack = (s64)(s32)stack - 16;
    thread->returnAddress = (s64)(s32)&D_10007BF8;
    thread->status = 0x0400FF03;
    thread->rcp = 0x3F;
    thread->fpcsr = 0x01000800;
    thread->fp = 0;
    thread->state = 1;
    thread->flags = 0;
    mask = func_80022DC0();
    thread->activeNext = D_8002BDFC;
    D_8002BDFC = thread;
    func_80022DE0(mask);
}
