#include "types.h"

/*
 * Reviewed source unit: src/game/game_135D00.c
 * Boundary evidence: docs/evidence/game_raw_sorted_record_object_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15108850
 * - func_15108AB4
 * - func_15108B80
 * - func_15108BC0
 * - func_15108C38
 * - func_15108D24
 * - func_15108E10
 * - func_15109064
 * - func_151090DC
 * - func_15109120
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_135D00/func_15108850.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800A2470;
extern f32 D_800A2474;
extern f32 D_800A2478;
extern f32 D_800A247C;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15108AB4 CURRENT (310) */
s32 func_15108AB4(u8 *arg0) {
    u8 *temp_s0;
    f32 first;

    temp_s0 = (void *)(arg0 + *(s32 *)((u8 *)arg0 + 0x50));
    first = *(f32 *)(temp_s0 + 0x100);
    temp_s0 += 0xF8;
    *(f32 *)(temp_s0 + 8) = first + (D_800A2470 * D_800BE9A4);
    *(f32 *)(temp_s0 + 0xC) += D_800A2474 * D_800BE9A4;
    *(f32 *)(temp_s0 + 8) = func_15144B68(*(f32 *)(temp_s0 + 8));
    *(f32 *)(temp_s0 + 0xC) = func_15144B68(*(f32 *)(temp_s0 + 0xC));
    *(f32 *)temp_s0 = func_15047D60(*(f32 *)(temp_s0 + 8)) * D_800A2478;
    *(f32 *)(temp_s0 + 4) = func_15047D60(*(f32 *)(temp_s0 + 0xC)) * D_800A247C;
    func_15108B80(arg0);
    func_15108BC0(arg0);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15108AB4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_135D00/func_15108AB4.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15108B80 CURRENT (60) */
void func_15108B80(u8 *arg0) {
    s32 temp_t0;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_v0 = (void *)(arg0 + *(s32 *)((u8 *)arg0 + 0x50));
    temp_v0_2 = (void *)(temp_v0 + 0xF8);
    if (*(s32 *)((u8 *)temp_v0 + 0x10C) != 0x3E7) {
        temp_t0 = *(s32 *)((u8 *)temp_v0_2 + 0x1C) - D_800BE9E4;
        *(s32 *)((u8 *)temp_v0_2 + 0x1C) = temp_t0;
        if (temp_t0 < 0) {
            *(s32 *)((u8 *)temp_v0_2 + 0x14) = 0x3E7;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15108B80 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_135D00/func_15108B80.s")
extern u8 D_800C35EA;
extern s32 D_800C3958;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15108BC0 CURRENT (710) */
void func_15108BC0(u8 *arg0) {
    s32 temp_v1;
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + *(s32 *)((u8 *)arg0 + 0x50));
    temp_v1 = *(s32 *)((u8 *)temp_v0 + 0x10C);
    temp_v0 += 0xF8;
    if (temp_v1 == 0x3E7) {
        *(f32 *)(temp_v0 + 0x10) = 226.0f;
        return;
    }
    if (D_800C35EA == 1) {
        *(f32 *)(temp_v0 + 0x10) = *(f32 *)((u8 *)(D_800C3958 + (temp_v1 * 0x44)) + 4);
        return;
    }
    *(f32 *)(temp_v0 + 0x10) = 226.0f;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15108BC0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_135D00/func_15108BC0.s")
/* Call context: func_15047D60: unique active project prototype */
extern f32 D_800A2480;
extern f32 D_800A2484;
extern f32 D_800A2488;
extern f32 D_800A248C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15108C38 CURRENT (1339) */
s32 func_15108C38(u8 *arg0) {
    u8 *temp_s0;
    u8 *temp_s0_2;

    temp_s0 = (void *)(arg0 + *(s32 *)((u8 *)arg0 + 0x50));
    temp_s0_2 = (void *)(temp_s0 + 0xF8);
    *(f32 *)((u8 *)temp_s0_2 + 8) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x100) + (D_800A2480 * D_800BE9A4));
    *(f32 *)((u8 *)temp_s0_2 + 0xC) = (f32) (*(f32 *)((u8 *)temp_s0_2 + 0xC) + (D_800A2484 * D_800BE9A4));
    *(f32 *)((u8 *)temp_s0_2 + 8) = func_15144B68(*(f32 *)((u8 *)temp_s0_2 + 8));
    *(f32 *)((u8 *)temp_s0_2 + 0xC) = func_15144B68(*(f32 *)((u8 *)temp_s0_2 + 0xC));
    *(f32 *)((u8 *)temp_s0 + 0xF8) = (f32) (func_15047D60(*(f32 *)((u8 *)temp_s0_2 + 8)) * D_800A2488);
    *(f32 *)((u8 *)temp_s0_2 + 4) = (f32) (func_15047D60(*(f32 *)((u8 *)temp_s0_2 + 0xC)) * D_800A248C);
    func_15108B80(arg0);
    func_15108BC0(arg0);
    if (*(u8 *)((u8 *)temp_s0_2 + 0x20) != 0) {
        *(s8 *)((u8 *)arg0 + 0x12) = 4;
        return 1;
    }
    *(s8 *)((u8 *)arg0 + 0x12) = 2;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15108C38 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_135D00/func_15108C38.s")
typedef struct Game135D00MatrixWork {
    f32 values[12];
    s32 pad_30;
    f32 saved;
    s32 pad_38;
    s32 pad_3C;
} Game135D00MatrixWork;

void func_150A8050(f32 *, s32, s32, s32);
void func_150A7790(void *, s32);
extern f32 D_800A2490;
extern u8 D_800BE9C0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15108D24 CURRENT (250) */
s32 func_15108D24(u8 *arg0, s32 arg1) {
    Game135D00MatrixWork work;
    u8 *source;

    source = arg0 + *(s32 *)(arg0 + 0x50) + 0xF8;
    func_150A8050(work.values, *(s32 *)(source + 0), 0,
                  *(s32 *)(source + 4));
    work.saved = *(f32 *)(source + 0x10);
    work.values[0] *= D_800A2490;
    work.values[1] *= D_800A2490;
    work.values[2] *= D_800A2490;
    work.values[4] *= D_800A2490;
    work.values[5] *= D_800A2490;
    work.values[6] *= D_800A2490;
    work.values[8] *= D_800A2490;
    work.values[9] *= D_800A2490;
    work.values[10] *= D_800A2490;
    func_150A7790(work.values, (s32)(arg0 + (D_800BE9C0 << 6) + 0x78));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15108D24 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_135D00/func_15108D24.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_135D00/func_15108E10.s")
typedef struct Game135D00DispatchDescriptor {
    s32 field0;
    s32 field4;
} Game135D00DispatchDescriptor;

typedef struct Game135D00DispatchMessage {
    s32 arg0;
    s32 arg1;
    u8 arg2;
} Game135D00DispatchMessage;

extern Game135D00DispatchDescriptor D_80088C50;
void func_15169260(Game135D00DispatchDescriptor *, s32, Game135D00DispatchMessage *, s32);

void func_15108FFC(s32 arg0, s32 arg1, u8 arg2) {
    Game135D00DispatchMessage message;
    Game135D00DispatchDescriptor descriptor;

    descriptor = D_80088C50;
    message.arg0 = arg0;
    message.arg1 = arg1;
    message.arg2 = arg2;
    func_15169260(&descriptor, 2, &message, 0x1D);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15109064 CURRENT (130) */
void func_15109064(u8 *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + *(s32 *)((u8 *)arg0 + 0x50) + 0xF8);
    switch (arg2) {                              /* irregular */
    case 29:
        *(s32 *)((u8 *)temp_v0 + 0x14) = (s32) *(s32 *)((u8 *)arg1 + 0);
        *(u8 *)((u8 *)temp_v0 + 0x18) = (u8) *(u8 *)((u8 *)arg1 + 8);
        *(s32 *)((u8 *)temp_v0 + 0x1C) = (s32) *(s32 *)((u8 *)arg1 + 4);
        return;
    case 30:
        if (*(u8 *)((u8 *)temp_v0 + 0x20) != 0) {
            *(u8 *)((u8 *)temp_v0 + 0x20) = 0U;
            return;
        }
        *(u8 *)((u8 *)temp_v0 + 0x20) = 1U;
        return;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15109064 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_135D00/func_15109064.s")
extern s32 D_80088C58[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151090DC CURRENT (780) */
void func_151090DC(void) {
    struct {
        s32 field0;
        s32 field4;
    } sp18;

    sp18.field0 = D_80088C58[0];
    sp18.field4 = D_80088C58[1];
    func_15169260((s32 *) &sp18, 2, 0, 0x1E);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151090DC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_135D00/func_151090DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_135D00/func_15109120.s")
