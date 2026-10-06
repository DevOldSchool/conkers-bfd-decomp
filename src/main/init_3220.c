#include "types.h"

/*
 * Reviewed source unit: src/main/init_3220.c
 * Boundary evidence: docs/evidence/boundaries/main/main_system_wrapper_boundaries.md
 *
 * TODO: Implement these source-unit functions:
 * - func_80003220
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef union {
    struct {
        u32 type;
        u32 flags;
        u64 *ucodeBoot;
        u32 ucodeBootSize;
        u64 *ucode;
        u32 ucodeSize;
        u64 *ucodeData;
        u32 ucodeDataSize;
        u64 *dramStack;
        u32 dramStackSize;
        u64 *outputBuffer;
        u64 *outputBufferSize;
        u64 *data;
        u32 dataSize;
        u64 *yieldData;
        u32 yieldDataSize;
    } t;
    u64 alignment;
} SpTask;

extern SpTask D_80036B60;
void func_80023A10(const void *, void *, s32);
u32 func_800233C0(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80003220 CURRENT (6183) */
SpTask *func_80003220(SpTask *arg0) {
    func_80023A10(arg0, &D_80036B60, sizeof(SpTask));
    if (D_80036B60.t.ucode != 0) {
        D_80036B60.t.ucode = (u64 *)func_800233C0(D_80036B60.t.ucode);
    }
    if (D_80036B60.t.ucodeData != 0) {
        D_80036B60.t.ucodeData = (u64 *)func_800233C0(D_80036B60.t.ucodeData);
    }
    if (D_80036B60.t.dramStack != 0) {
        D_80036B60.t.dramStack = (u64 *)func_800233C0(D_80036B60.t.dramStack);
    }
    if (D_80036B60.t.outputBuffer != 0) {
        D_80036B60.t.outputBuffer = (u64 *)func_800233C0(D_80036B60.t.outputBuffer);
    }
    if (D_80036B60.t.outputBufferSize != 0) {
        D_80036B60.t.outputBufferSize = (u64 *)func_800233C0(D_80036B60.t.outputBufferSize);
    }
    if (D_80036B60.t.data != 0) {
        D_80036B60.t.data = (u64 *)func_800233C0(D_80036B60.t.data);
    }
    if (D_80036B60.t.yieldData != 0) {
        D_80036B60.t.yieldData = (u64 *)func_800233C0(D_80036B60.t.yieldData);
    }
    return &D_80036B60;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80003220 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_3220/func_80003220.s")
SpTask *func_80003220(SpTask *);
void func_80023D20(void *, s32);
void func_80023DA0(u32);
s32 func_80023DB0(u32);
s32 func_80023DF0(s32, u32, void *, u32);
s32 func_80023E80(void);

void func_80003330(SpTask *arg0) {
    SpTask *task;

    task = func_80003220(arg0);
    if (task->t.flags & 1) {
        task->t.ucodeData = task->t.yieldData;
        task->t.ucodeDataSize = task->t.yieldDataSize;
        arg0->t.flags &= ~1;
        if (task->t.flags & 4) {
            task->t.ucode = (u64 *)*(u32 *)(((u32)arg0->t.yieldData + 0xBFC) | 0xA0000000);
        }
    }
    func_80023D20(task, sizeof(SpTask));
    func_80023DA0(0x2B00);
    while (func_80023DB0(0x04001000) == -1) {
    }
    while (func_80023DF0(1, 0x04000FC0, task, sizeof(SpTask)) == -1) {
    }
    while (func_80023E80() != 0) {
    }
    while (func_80023DF0(1, 0x04001000, task->t.ucodeBoot, task->t.ucodeBootSize) == -1) {
    }
}
void func_80023DA0(u32);
s32 func_80023E80(void);

void func_8000349C(u8 *arg0) {
    while (func_80023E80() != 0) {
    }
    func_80023DA0(0x125);
}
