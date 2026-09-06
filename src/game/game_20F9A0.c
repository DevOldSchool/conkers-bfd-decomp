#include "types.h"

/*
 * Reviewed source unit: src/game/game_20F9A0.c
 * Boundary evidence: docs/evidence/game_raw_extended_code_selected_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151E24F0
 * - func_151E2834
 * - func_151E30C4
 * - func_151E327C
 * - func_151E3344
 * - func_151E4264
 * - func_151E4314
 * - func_151E43DC
 * - func_151E4BD8
 * - func_151E4E00
 * - func_151E4E64
 * - func_151E4EE8
 * - func_151E5034
 * - func_151E50C8
 * - func_151E51EC
 * - func_151E530C
 * - func_151E53E8
 * - func_151E557C
 * - func_151E55A8
 * - func_151E565C
 * - func_151E5F64
 * - func_151E5FF4
 * - func_151E6964
 * - func_151E6C1C
 * - func_151E7DC0
 * - func_151E7E9C
 * - func_151E7EF8
 * - func_151E7F60
 * - func_151E81EC
 * - func_151E8214
 * - func_151E82B8
 * - func_151E83E8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E24F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E2834.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E30C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E327C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E3344.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E4264.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E4314.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E43DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E4BD8.s")
extern s8 D_800E0B94;

void func_151E4DC4(void) {
    D_800E0B94 = 0xA;
}
extern s16 D_800E0B9A;

void func_151E4DD8(void) {
    if (D_800E0B9A & 0x8020) {
        D_800E0B94 = 4;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E4E00.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E4E64.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E4EE8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E5034.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E50C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E51EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E530C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E53E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E557C.s")
extern s32 D_800BE9E4;
extern u8 D_800E0B97;
extern u8 D_800E0B98;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151E55A8 CURRENT (155) */
void func_151E55A8(void) {
    s32 var_a0;
    s32 var_v1;

    if (D_800E0B98 == 0) {
        var_v1 = D_800BE9E4 * 8;
    } else {
        var_v1 = D_800BE9E4 * -8;
    }
    var_a0 = D_800E0B97 + var_v1;
    if (var_a0 >= 0x100) {
        var_a0 = 0x1FE - var_a0;
        D_800E0B98 ^= 1;
    } else if (var_a0 < 0) {
        var_a0 = -var_a0;
        D_800E0B98 ^= 1;
    }
    D_800E0B97 = (u8) var_a0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151E55A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E55A8.s")
extern u8 D_800E0A8C;

void func_151E562C(void) {
    if (D_800E0A8C != 0) {
        D_800E0A8C = 0;
    }
}
extern s8 D_8008FDC8;

s8 func_151E564C(void) {
    return D_8008FDC8;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E565C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E5F64.s")
extern s8 D_8008FD8C;
extern s8 D_8008FD90;
extern s8 D_800E0BEB;

s8 func_151E5FAC(void) {
    if (D_800E0BEB != 0) {
        if (D_8008FD8C >= 5) {
            return D_8008FD90;
        }
        return D_8008FD8C;
    }
    return D_8008FD90;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E5FF4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E6964.s")
extern s32 D_8008FDD8;
extern s8 D_800E0BD3;
extern s32 D_800E0BD4;

void func_151E6BFC(void) {
    D_800E0BD3 = 0;
    D_800E0BD4 = 0;
    D_8008FDD8 = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E6C1C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E7DC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E7E9C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E7EF8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E7F60.s")
extern s8 D_8008FD84;
extern s32 D_800E0BA4;
extern s32 D_800E0BA8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151E81EC CURRENT (205) */
void func_151E81EC(void) {
    D_800E0BA4 = 0;
    D_800E0BA4 = 0;
    D_800E0BA8 = 0;
    D_800E0BA8 = 0;
    D_8008FD84 = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151E81EC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E81EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E8214.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E82B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20F9A0/func_151E83E8.s")
