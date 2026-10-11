#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1CE2F0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_call_connected_beta_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A0E40
 * - func_151A0F28
 * - func_151A1010
 * - func_151A11E4
 * - func_151A175C
 * - func_151A1998
 * - func_151A1E34
 * - func_151A1FB4
 * - func_151A24A8
 * - func_151A25E0
 * - func_151A26EC
 * - func_151A2960
 * - func_151A2C24
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_151A11CC(f32, f32, s32, f32, f32, s32, s32, s32,
                   s32, s32, f32, s32, s32, s32, s32, s32,
                   s32, f32, s32, s32, s32, s32, s32, s32,
                   s32, s32, s32, s32);
extern f32 D_800A8D20;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A0E40 CURRENT (1662) */
void func_151A0E40(f32 arg0, f32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_151A11CC(
        arg0, arg1, arg2, 163.0f, D_800A8D20, 0xA0, 0x4B, 0x41F, 0x4F6,
        1, D_800A8D20, 0x87, 0x44, 0x41F, 0x4F6, 2, 1, D_800A8D20, 0x46,
        0x42, 0x41F, 0x4F6, 7, 0x41, 4, 1, arg3 & 0xFF, arg4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A0E40 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A0E40.s")
extern f32 D_800A8D24;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A0F28 CURRENT (1662) */
void func_151A0F28(f32 arg0, f32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_151A11CC(
        arg0, arg1, arg2, 163.0f, D_800A8D24, 0xA0, 0x4B, 0x41F, 0x4F6,
        1, D_800A8D24, 0x87, 0x44, 0x41F, 0x4F6, 2, 1, D_800A8D24, 0x46,
        0x42, 0x41F, 0x4F6, 7, 0x41, 4, 1, arg3 & 0xFF, arg4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A0F28 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A0F28.s")
extern f32 D_800A8D28;
typedef void (*Game1CE2F0ScaledSetupFn)(f32, f32, s32, f32, f32, s32, s32, s32,
                                        s32, s32, f32, s32, s32, s32, s32, s32,
                                        s32, f32, s32, s32, s32, s32, s32, s32,
                                        s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A1010 CURRENT (6476) */
void func_151A1010(f32 arg0, f32 arg1, s32 arg2, s16 arg3, f32 arg4, f32 arg5, u8 arg6, s32 arg7) {
    s16 interval;
    s16 bounded;
    s16 y70;
    s16 y30;
    s16 xScale;
    s16 x100;

    interval = arg3 - 0x20;
    bounded = interval;
    if (interval <= 0) {
        bounded = 1;
    }
    y70 = (s16)(s32)(70.0f * arg5);
    y30 = (s16)(s32)(30.0f * arg5);
    xScale = (s16)(s32)(D_800A8D28 * arg4);
    x100 = (s16)(s32)(100.0f * arg4);
    ((Game1CE2F0ScaledSetupFn)func_151A11CC)(
        arg0, arg1, arg2, 250.0f * arg4,
        1.0f, y70, y30, xScale, x100, 0x12,
        1.0f, (s32)(90.0f * arg5), (s32)(20.0f * arg5), xScale, x100, bounded, 0x10,
        1.0f, y70, y30, xScale, x100, (s32)(15.0f * arg4), (s32)(10.0f * arg4),
        0x12, interval + 0x10, arg6, arg7);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A1010 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A1010.s")
void func_151A11CC(f32 arg0, f32 arg1, s32 arg2, f32 arg3,
                  f32 arg4, s32 arg5, s32 arg6, s32 arg7,
                  s32 arg8, s32 arg9, f32 arg10, s32 arg11,
                  s32 arg12, s32 arg13, s32 arg14, s32 arg15,
                  s32 arg16, f32 arg17, s32 arg18, s32 arg19,
                  s32 arg20, s32 arg21, s32 arg22, s32 arg23,
                  s32 arg24, s32 arg25, s32 arg26, s32 arg27) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A11E4.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A175C CURRENT (1900) */
void func_151A175C(u8 *arg0) {
    s16 temp_lo;
    s16 temp_lo_2;
    s16 temp_v1;
    s32 temp_t5;
    s32 temp_t6;
    s32 temp_t7;
    u8 *temp_v0;

    temp_v1 = *(s16 *)((u8 *)arg0 + 0x38);
    if (*(s16 *)((u8 *)arg0 + 0x54) < temp_v1) {
        *(s8 *)((u8 *)arg0 + 0x3F) = (s8) ((*(s16 *)((u8 *)(arg0 + 0x50) + 2) - temp_v1) * *(s16 *)((u8 *)arg0 + 0x50));
    }
    temp_v0 = (void *)(arg0 + 0x50);
    if (*(s16 *)((u8 *)temp_v0 + 0xA) < temp_v1) {
        temp_lo = (*(s16 *)((u8 *)temp_v0 + 8) - temp_v1) * *(s16 *)((u8 *)temp_v0 + 6);
        *(s16 *)((u8 *)arg0 + 0x36) = temp_lo;
        *(s16 *)((u8 *)arg0 + 0x34) = temp_lo;
    }
    if (*(s16 *)((u8 *)temp_v0 + 0xC) < temp_v1) {
        temp_t7 = ((*(s16 *)((u8 *)arg0 + 0x20) << 8) | *(u8 *)((u8 *)arg0 + 0x2C)) + (((*(s16 *)((u8 *)temp_v0 + 0xE) << 8) | *(s16 *)((u8 *)temp_v0 + 0x14)) * D_800BE9E4);
        *(s16 *)((u8 *)arg0 + 0x20) = (s16) (temp_t7 >> 8);
        *(u8 *)((u8 *)arg0 + 0x2C) = (u8) temp_t7;
        temp_t6 = ((*(s16 *)((u8 *)arg0 + 0x22) << 8) | *(u8 *)((u8 *)arg0 + 0x2E)) + (((*(s16 *)((u8 *)temp_v0 + 0x10) << 8) | *(s16 *)((u8 *)temp_v0 + 0x16)) * D_800BE9E4);
        *(s16 *)((u8 *)arg0 + 0x22) = (s16) (temp_t6 >> 8);
        *(u8 *)((u8 *)arg0 + 0x2E) = (u8) temp_t6;
        temp_t5 = ((*(s16 *)((u8 *)arg0 + 0x24) << 8) | *(u8 *)((u8 *)arg0 + 0x2D)) + (((*(s16 *)((u8 *)temp_v0 + 0x12) << 8) | *(s16 *)((u8 *)temp_v0 + 0x18)) * D_800BE9E4);
        *(s16 *)((u8 *)arg0 + 0x24) = (s16) (temp_t5 >> 8);
        *(u8 *)((u8 *)arg0 + 0x2D) = (u8) temp_t5;
    }
    if (*(s16 *)((u8 *)arg0 + 0x38) < *(s16 *)((u8 *)temp_v0 + 0x1A)) {
        *(s8 *)((u8 *)arg0 + 0x3F) = (s8) (*(s16 *)((u8 *)arg0 + 0x38) * *(s16 *)((u8 *)temp_v0 + 0x1C));
    }
    if (*(s16 *)((u8 *)arg0 + 0x38) < *(s16 *)((u8 *)temp_v0 + 0x1E)) {
        temp_lo_2 = *(s16 *)((u8 *)arg0 + 0x38) * *(s16 *)((u8 *)temp_v0 + 0x20);
        *(s16 *)((u8 *)arg0 + 0x36) = temp_lo_2;
        *(s16 *)((u8 *)arg0 + 0x34) = temp_lo_2;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A175C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A175C.s")
void *func_10022EC0(void *, const void *, u32);

void func_151A18DC(void *arg0) {
    typedef struct { s32 words[3]; } Copy3;
    u8 *result;
    struct {
        Copy3 header;
        f32 value40;
        f32 value44;
        f32 value48;
        s16 value4C;
        s16 value4E;
        s16 value50;
        s16 value52;
    } packet;

    packet.header = *(Copy3 *)((u8 *)arg0 + 0x28);
    packet.value40 = *(f32 *)((u8 *)arg0 + 0x34);
    packet.value44 = 0.0f;
    packet.value48 = *(f32 *)((u8 *)arg0 + 0x38);
    packet.value4C = *(s16 *)((u8 *)arg0 + 0x3E);
    packet.value4E = *(s16 *)((u8 *)arg0 + 0x40);
    packet.value50 = *(s16 *)((u8 *)arg0 + 0x42);
    packet.value52 = *(s16 *)((u8 *)arg0 + 0x44);
    result = func_151491F4(*(s16 *)((u8 *)arg0 + 0x3C), -1, 3, 1, 0,
                           0x20, *(u8 *)((u8 *)arg0 + 0xC),
                           *(u8 *)((u8 *)arg0 + 1));
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x28, &packet, 0x20);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A1998.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A1E34 CURRENT (735) */
void func_151A1E34(u8 *arg0) {
    s16 *temp_v0;
    s16 temp_lo;
    s16 temp_lo_2;
    s16 temp_v1;

    temp_v1 = *(s16 *)((u8 *)arg0 + 0x38);
    if (*(s16 *)((u8 *)arg0 + 0x54) < temp_v1) {
        temp_v0 = (s16 *)(arg0 + 0x50);
        *(s8 *)((u8 *)arg0 + 0x3F) = temp_v0[0] * (temp_v0[1] - temp_v1);
    }
    temp_v0 = (s16 *)(arg0 + 0x50);
    if (temp_v0[5] < temp_v1) {
        temp_lo = temp_v0[3] * (temp_v0[4] - temp_v1);
        *(s16 *)((u8 *)arg0 + 0x36) = temp_lo;
        *(s16 *)((u8 *)arg0 + 0x34) = temp_lo;
    }
    if (temp_v1 < temp_v0[6]) {
        *(s8 *)((u8 *)arg0 + 0x3F) = (s8) (temp_v0[7] * temp_v1);
    }
    if (temp_v1 < temp_v0[8]) {
        temp_lo_2 = temp_v0[9] * temp_v1;
        *(s16 *)((u8 *)arg0 + 0x36) = temp_lo_2;
        *(s16 *)((u8 *)arg0 + 0x34) = temp_lo_2;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A1E34 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A1E34.s")
typedef struct Game1CE2F0CopyHeader {
    s32 words[3];
} Game1CE2F0CopyHeader;

typedef union Game1CE2F0CopyParams {
    struct {
        Game1CE2F0CopyHeader header;
        f32 valueC;
        f32 value10;
        f32 value14;
        s16 values18[6];
    } fields;
    f64 align;
} Game1CE2F0CopyParams;

void func_151A1EE8(u8 *arg0) {
    Game1CE2F0CopyParams params;
    u8 *result;

    params.fields.header = *(Game1CE2F0CopyHeader *)(arg0 + 0x28);
    params.fields.valueC = *(f32 *)(arg0 + 0x34);
    params.fields.value10 = 0.0f;
    params.fields.value14 = *(f32 *)(arg0 + 0x38);
    params.fields.values18[0] = *(s16 *)(arg0 + 0x3E);
    params.fields.values18[1] = *(s16 *)(arg0 + 0x40);
    params.fields.values18[2] = *(s16 *)(arg0 + 0x42);
    params.fields.values18[3] = *(s16 *)(arg0 + 0x44);
    params.fields.values18[4] = *(s16 *)(arg0 + 0x46);
    params.fields.values18[5] = *(s16 *)(arg0 + 0x48);
    result = func_151491F4(*(s16 *)(arg0 + 0x3C), -1, 4, 1, 0, 0x24,
                           *(u8 *)(arg0 + 0xC), *(u8 *)(arg0 + 1));
    if (result != 0) {
        func_10022EC0((void *)(result + 0x28), &params, 0x24);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A1FB4.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A24A8 CURRENT (665) */
void func_151A24A8(u8 *arg0) {
    s16 temp_lo;
    s16 temp_v1;
    s32 temp_lo_2;
    s8 temp_lo_3;
    u8 *temp_v0;

    temp_v0 = arg0 + 0x50;
    temp_v1 = *(s16 *)((u8 *)arg0 + 0x38);
    if (*(s16 *)((u8 *)arg0 + 0x54) < temp_v1) {
        *(s8 *)((u8 *)arg0 + 0x3F) = (s8) (*(s16 *)temp_v0 * (*(s16 *)(temp_v0 + 2) - temp_v1));
    }
    temp_v0 = (void *)(arg0 + 0x50);
    if (*(s16 *)((u8 *)temp_v0 + 0xA) < temp_v1) {
        temp_lo = *(s16 *)((u8 *)temp_v0 + 6) * (*(s16 *)((u8 *)temp_v0 + 8) - temp_v1);
        *(s16 *)((u8 *)arg0 + 0x36) = temp_lo;
        *(s16 *)((u8 *)arg0 + 0x34) = temp_lo;
    }
    if (temp_v1 < *(s16 *)((u8 *)temp_v0 + 0x10)) {
        *(s8 *)((u8 *)arg0 + 0x3F) = (s8) (temp_v1 * *(s16 *)((u8 *)temp_v0 + 0x12));
    }
    if (temp_v1 < *(s16 *)((u8 *)temp_v0 + 0x14)) {
        temp_lo_2 = *(s16 *)((u8 *)temp_v0 + 0x16) * D_800BE9E4;
        *(s16 *)((u8 *)arg0 + 0x34) = (s16) (*(s16 *)((u8 *)arg0 + 0x34) + temp_lo_2);
        *(s16 *)((u8 *)arg0 + 0x36) = (s16) (*(s16 *)((u8 *)arg0 + 0x36) + temp_lo_2);
        temp_v1 = *(s16 *)(arg0 + 0x38);
    }
    if (temp_v1 < *(s16 *)((u8 *)temp_v0 + 0xC)) {
        *(s8 *)((u8 *)arg0 + 0x2F) = 0x13;
        *(u16 *)((u8 *)arg0 + 0x44) = (u16) (*(u16 *)((u8 *)arg0 + 0x44) | 0x101);
        temp_lo_3 = temp_v1 * *(s16 *)((u8 *)temp_v0 + 0xE);
        *(s32 *)((u8 *)arg0 + 0x14) = 0x520003;
        *(s8 *)((u8 *)arg0 + 0x42) = temp_lo_3;
        *(s8 *)((u8 *)arg0 + 0x41) = temp_lo_3;
        *(s8 *)((u8 *)arg0 + 0x40) = temp_lo_3;
    }
    if (temp_v1 < *(s16 *)((u8 *)temp_v0 + 0x18)) {
        *(s16 *)((u8 *)arg0 + 0x32) = (s16) *(s16 *)((u8 *)temp_v0 + 0x1A);
        *(s16 *)((u8 *)temp_v0 + 0x18) = -0x270F;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A24A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A24A8.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A25E0 CURRENT (605) */
void func_151A25E0(u8 *arg0) {
    s16 temp_lo;
    s16 temp_v1;
    s32 temp_lo_2;
    s8 temp_lo_3;
    u8 *temp_v0;

    temp_v0 = arg0 + 0x50;
    temp_v1 = *(s16 *)((u8 *)arg0 + 0x38);
    if (*(s16 *)((u8 *)arg0 + 0x54) < temp_v1) {
        *(s8 *)((u8 *)arg0 + 0x3F) = (s8) (*(s16 *)temp_v0 * (*(s16 *)(temp_v0 + 2) - temp_v1));
    }
    temp_v0 = (void *)(arg0 + 0x50);
    if (*(s16 *)((u8 *)temp_v0 + 0xA) < temp_v1) {
        temp_lo = *(s16 *)((u8 *)temp_v0 + 6) * (*(s16 *)((u8 *)temp_v0 + 8) - temp_v1);
        *(s16 *)((u8 *)arg0 + 0x36) = temp_lo;
        *(s16 *)((u8 *)arg0 + 0x34) = temp_lo;
    }
    if (temp_v1 < *(s16 *)((u8 *)temp_v0 + 0x10)) {
        *(s8 *)((u8 *)arg0 + 0x3F) = (s8) (*(s16 *)((u8 *)temp_v0 + 0x12) * temp_v1);
    }
    if (temp_v1 < *(s16 *)((u8 *)temp_v0 + 0x14)) {
        temp_lo_2 = *(s16 *)((u8 *)temp_v0 + 0x16) * D_800BE9E4;
        *(s16 *)((u8 *)arg0 + 0x34) = (s16) (*(s16 *)((u8 *)arg0 + 0x34) + temp_lo_2);
        *(s16 *)((u8 *)arg0 + 0x36) = (s16) (*(s16 *)((u8 *)arg0 + 0x36) + temp_lo_2);
        temp_v1 = *(s16 *)(arg0 + 0x38);
    }
    if (temp_v1 < *(s16 *)((u8 *)temp_v0 + 0x18)) {
        *(s16 *)((u8 *)arg0 + 0x32) = (s16) *(s16 *)((u8 *)temp_v0 + 0x1A);
        *(s16 *)((u8 *)temp_v0 + 0x18) = -0x270F;
        temp_v1 = *(s16 *)(arg0 + 0x38);
    }
    temp_lo_3 = *(s16 *)((u8 *)temp_v0 + 0xE) * temp_v1;
    *(s8 *)((u8 *)arg0 + 0x42) = temp_lo_3;
    *(s8 *)((u8 *)arg0 + 0x41) = temp_lo_3;
    *(s8 *)((u8 *)arg0 + 0x40) = temp_lo_3;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A25E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A25E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A26EC.s")
extern u8 D_800BE616;
extern s32 (*D_8008F8E0[])(u8 *, s32, s32, s32);
s32 func_1513170C(u8 *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A2960 CURRENT (492) */
void func_151A2960(u8 *arg0, s32 arg1) {
    struct State {
        s16 threshold;
        s16 multiplier;
        s16 current;
        s8 callback_index;
    } *state;
    s32 current;
    s32 callback_index;

    state = (struct State *)(arg0 + 0xB0);
    if (*(s16 *)(arg0 + 0x1A) < *(s16 *)(arg0 + 0xB0)) {
        *(s8 *)(arg0 + 0x2C) = (s8)(*(s16 *)(arg0 + 0xB2) *
                                    *(s16 *)(arg0 + 0x1A));
    }
    if (D_800BE616 == 0) {
        current = state->current;
        if (current != -1) {
            callback_index = state->callback_index;
            if ((callback_index != -1) &&
                (current >= *(s16 *)(arg0 + 0x1A))) {
                D_8008F8E0[callback_index](arg0, current,
                                               *(s16 *)(arg0 + 0x1A), -1);
                state->current = -1;
            }
        }
    }
    func_1513170C(arg0, arg1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A2960 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A2960.s")
extern void func_151A2C24(s32, s32, s32, s32, f32, f32, f32, s32,
    f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_151A2A14(s32 arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6,
    f32 arg7, f32 arg8, f32 arg9, f32 arg10, s16 arg11, s16 arg12, s16 arg13,
    s16 arg14, s16 arg15, s16 arg16, s8 arg17, u8 arg18, s32 arg19) {
    func_151A2C24(arg0, 0, (s32)arg1, (s32)arg2, arg3, arg4, arg5, arg6,
        arg7, arg8, arg9, arg10, (s32)arg11, (s32)arg12, (s32)arg13,
        (s32)arg14, (s32)arg15, (s32)arg16, (s32)arg17, (s32)arg18, arg19, 1);
}
extern void func_151A2C24(s32, s32, s32, s32, f32, f32, f32, s32,
    f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_151A2AD4(s32 arg0, s32 arg1, f32 arg2, f32 arg3, s32 arg4,
    f32 arg5, f32 arg6, f32 arg7, f32 arg8, s16 arg9, s16 arg10,
    s16 arg11, s16 arg12, s16 arg13, s16 arg14, s8 arg15, u8 arg16,
    s32 arg17) {
    func_151A2C24(arg0, arg1, 0, 0, 0.0f, arg2, arg3, arg4,
        arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13,
        arg14, arg15, arg16, arg17, 0);
}
void func_151A2B84(void *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, void *arg5) {
    f32 temp_fv0;

    temp_fv0 = 1.0f - arg4;
    *(f32 *)((u8 *)arg5 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) * temp_fv0);
    *(f32 *)((u8 *)arg5 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) * temp_fv0);
    *(f32 *)((u8 *)arg5 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) * temp_fv0);
}
/* Call context: func_15143794: unique active project prototype */
void func_15143794(s16, s16, f32, void *);

void func_151A2BD0(s32 arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4, void *arg5) {
    func_15143794(arg1, arg2, (1.0f - arg4) * arg3, arg5);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CE2F0/func_151A2C24.s")
typedef struct Game1CE2F0EmitterVector {
    f32 x;
    f32 y;
    f32 z;
} Game1CE2F0EmitterVector;

typedef struct Game1CE2F0EmitterParticle {
    s32 field0;
    s32 field4;
    Game1CE2F0EmitterVector position8;
    f32 field14;
    f32 field18;
    f32 field1C;
    f32 field20;
    f32 field24;
    f32 field28;
    s16 field2C;
    s16 field2E;
    s16 field30;
    s16 field32;
    s32 field34;
    s32 field38;
    s16 field3C;
    s16 field3E;
    s16 field40;
    u8 fields42[23];
    s32 field5C;
    s32 field60;
    s16 field64;
    s16 field66;
    s16 field68;
    u8 field6A;
    f32 field6C;
    s8 fields70[4];
} Game1CE2F0EmitterParticle;

typedef struct Game1CE2F0EmitterOwner {
    u8 pad0;
    u8 field1;
    u8 pad2[0xA];
    u8 fieldC;
    u8 padD[0x2B];
    f32 field38;
    f32 field3C;
    Game1CE2F0EmitterVector position40;
    Game1CE2F0EmitterVector offset4C;
    u8 pad58[0x10];
    s32 flags68;
} Game1CE2F0EmitterOwner;

void func_15152B38(void *, s32, s32, void *);
extern f32 D_800A8D30;
extern f32 D_800A8D34;
extern f32 D_800A8D38;

void func_151A2F0C(Game1CE2F0EmitterOwner *arg0) {
    Game1CE2F0EmitterParticle descriptor;

    descriptor.field0 = 8;
    descriptor.field4 = 6;
    descriptor.position8 = arg0->position40;
    if (arg0->flags68 & 0x1000) {
        descriptor.position8.x += arg0->offset4C.x;
        descriptor.position8.y += arg0->offset4C.y;
        descriptor.position8.z += arg0->offset4C.z;
    }
    descriptor.field14 = (arg0->field38 + arg0->field3C) * 0.5f * D_800A8D30;
    descriptor.field18 = (arg0->field38 + arg0->field3C) * 0.5f * D_800A8D34;
    descriptor.field1C = D_800A8D38;
    descriptor.field20 = 0.0f;
    descriptor.field24 = 8.0f;
    descriptor.field28 = 10.0f;
    descriptor.field2C = 0;
    descriptor.field2E = 0xFF;
    descriptor.field30 = -0x40;
    descriptor.field32 = 0x56;
    descriptor.field34 = 3;
    descriptor.field38 = 1;
    descriptor.field3C = 0x11;
    descriptor.field3E = 0x12;
    descriptor.field40 = 1;
    descriptor.fields42[0] = 4;
    descriptor.fields42[1] = 2;
    descriptor.fields42[2] = 3;
    descriptor.fields42[3] = 0xFF;
    descriptor.fields42[4] = 0xC8;
    descriptor.fields42[5] = 0xC8;
    descriptor.fields42[6] = 0xFF;
    descriptor.fields42[7] = 0;
    descriptor.fields42[8] = 0x37;
    descriptor.fields42[9] = 0x37;
    descriptor.fields42[10] = 0;
    descriptor.fields42[11] = 0xFF;
    descriptor.fields42[12] = 0xFF;
    descriptor.fields42[13] = 0xFF;
    descriptor.fields42[14] = 0xFF;
    descriptor.fields42[15] = 0;
    descriptor.fields42[16] = 0;
    descriptor.fields42[17] = 0;
    descriptor.fields42[18] = 0;
    descriptor.fields42[19] = 0xFF;
    descriptor.fields42[20] = 0;
    descriptor.fields42[21] = 1;
    descriptor.fields42[22] = 0x24;
    descriptor.field5C = 0x200005;
    descriptor.field60 = 0x60600;
    descriptor.field64 = 7;
    descriptor.field66 = 0x24;
    descriptor.field68 = 1;
    descriptor.field6A = 0;
    descriptor.field6C = 1.0f;
    descriptor.fields70[0] = -1;
    descriptor.fields70[1] = 0;
    descriptor.fields70[2] = -1;
    descriptor.fields70[3] = -1;
    func_15152B38(&descriptor, (s32) arg0->fieldC, (s32) arg0->field1, arg0);
}
