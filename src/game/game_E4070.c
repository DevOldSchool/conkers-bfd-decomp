#include "types.h"

/*
 * Reviewed source unit: src/game/game_E4070.c
 * Boundary evidence: docs/evidence/game_raw_connected_controller_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B6BC0
 * - func_150B6C90
 * - func_150B6D34
 * - func_150B6D78
 * - func_150B6E3C
 * - func_150B709C
 * - func_150B71A8
 * - func_150B7220
 * - func_150B73F0
 * - func_150B7484
 * - func_150B7560
 * - func_150B76BC
 * - func_150B77A8
 * - func_150B791C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B6BC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B6C90.s")
extern s32 D_800D9898;
extern s32 D_800D98A4;
extern s8 D_800D9890;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B6D34 CURRENT (2720) */
void func_150B6D34(void) {
    u8 *var_v1;
    void *temp_v0;

    var_v1 = (u8 *) &D_800D9898;
    do {
        temp_v0 = *(void **)(var_v1 + 0x14);
        var_v1 += 4;
        if (temp_v0 != 0) {
            *(s32 *)((u8 *)temp_v0 + 0x20) = 1;
        }
    } while (var_v1 != (u8 *) &D_800D98A4);
    D_800D9890 = 3;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B6D34 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B6D34.s")
extern s32 D_800D9894;
extern s32 D_800D98C0;
extern s8 D_800D9890;
void func_1516972C(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B6D78 CURRENT (30) */
void func_150B6D78(void) {
    s32 *var_s0;
    s32 temp_a0;

    if (D_800D9894 != 0) {
        func_1516972C(D_800D9894);
        D_800D9894 = 0;
    }
    var_s0 = &D_800D9898;
    do {
        temp_a0 = *var_s0;
        if (temp_a0 != 0) {
            func_1516972C(temp_a0);
            *var_s0 = 0;
        }
        var_s0 += 1;
    } while (var_s0 != &D_800D98C0);
    D_800D9890 = 3;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B6D78 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B6D78.s")
extern s32 D_800BE9E4;

void func_150B6DFC(void *arg0) {
    *(s16 *)((u8 *)arg0 + 0x34) = (s16) (*(s16 *)((u8 *)arg0 + 0x34) + (D_800BE9E4 * 0x30));
    if (*(s16 *)((u8 *)arg0 + 0x34) >= 0x801) {
        *(s16 *)((u8 *)arg0 + 0x34) = -0xC00;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B6E3C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B709C CURRENT (260) */
void func_150B709C(void *arg0) {
    s32 temp_v0;
    s32 var_v0;
    s32 var_v1;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x18);
    if (temp_v0 == 0x1E) {
        var_v1 = *(u8 *)((u8 *)arg0 + 0x45) + (D_800BE9E4 * 8);
        if (var_v1 >= 0x100) {
            var_v1 = 0;
        }
        *(u8 *)((u8 *)arg0 + 0x45) = (u8) var_v1;
    }
    var_v0 = temp_v0 + (D_800BE9E4 * 2);
    if (var_v0 >= 0x1F) {
        var_v0 = 0x1E;
    }
    *(s32 *)((u8 *)arg0 + 0x18) = var_v0;
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (((s32) (var_v0 * -0x54) / 30) + 0xE6);
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (((s32) (var_v0 * -0x32) / 30) + 0xAA);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B709C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B709C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B71A8 CURRENT (20) */
void func_150B71A8(void *arg0) {
    s16 temp_v0;
    s16 temp_v0_2;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x38);
    if (temp_v0 != 0x1000) {
        *(s16 *)((u8 *)arg0 + 0x38) = (s16) (temp_v0 + (D_800BE9E4 << 8));
        if (*(s16 *)((u8 *)arg0 + 0x38) >= 0x1001) {
            *(s16 *)((u8 *)arg0 + 0x38) = 0x1000;
        }
    } else {
        temp_v0_2 = *(s16 *)((u8 *)arg0 + 0x3A);
        if (temp_v0_2 != 0x1000) {
            *(s16 *)((u8 *)arg0 + 0x3A) = (s16) (temp_v0_2 + (D_800BE9E4 << 8));
            if (*(s16 *)((u8 *)arg0 + 0x3A) >= 0x1001) {
                *(s16 *)((u8 *)arg0 + 0x3A) = 0x1000;
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B71A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B71A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B7220.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B73F0 CURRENT (175) */
void func_150B73F0(void *arg0) {
    s16 temp_v0;
    s16 temp_v1;
    s32 temp_lo;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x18);
    temp_lo = (s32) (*(s16 *)((u8 *)arg0 + 0x24) << 0x10) / (s32) *(s32 *)((u8 *)arg0 + 0x1C);
    temp_v1 = *(s16 *)((u8 *)arg0 + 0x1A);
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (((s32) ((*(s16 *)((u8 *)arg0 + 0x20) - temp_v0) * temp_lo) >> 0x10) + temp_v0);
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (((s32) ((*(s16 *)((u8 *)arg0 + 0x22) - temp_v1) * temp_lo) >> 0x10) + temp_v1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B73F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B73F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B7484.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B7560.s")
void func_150B76BC(s32 arg0, s32 arg1);
extern s8 D_800D9890;

void func_150B765C(void) {
    func_150B76BC(0x3C, 1);
    D_800D9890 = 3;
}
void func_150B768C(void) {
    func_150B76BC(0xE6, 2);
    D_800D9890 = 3;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B76BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B77A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B791C.s")
