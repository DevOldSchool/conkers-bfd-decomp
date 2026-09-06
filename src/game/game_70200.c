#include "types.h"

/*
 * Reviewed source unit: src/game/game_70200.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15042D50
 * - func_15042D94
 * - func_15042E3C
 * - func_15042ECC
 * - func_150432CC
 * - func_150432FC
 * - func_1504332C
 * - func_15043384
 * - func_15043A20
 * - func_15043AC8
 * - func_15043B70
 * - func_15043BB8
 * - func_15043CA4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/func_15042D50.s")
extern s8 D_800CBD74;

void func_15042D78(u8 arg0) {
    D_800CBD74 = arg0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/func_15042D94.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/func_15042E3C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/func_15042ECC.s")
extern f32 D_800CBD80;

void func_150432BC(f32 arg0) {
    D_800CBD80 = arg0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/func_150432CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/func_150432FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/func_1504332C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/func_15043384.s")
typedef struct Game70200Entry {
    s32 field_0;
    s32 field_4;
    s32 field_8;
    s32 field_C;
} Game70200Entry;

void func_15043A00(Game70200Entry *arg0, s32 arg1, s32 arg2) {
    if (arg0) {
        arg0->field_0 = arg1;
        arg0->field_4 = arg2;
        arg0->field_C = 0;
        arg0->field_8 = 0;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/func_15043A20.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/func_15043AC8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/func_15043B70.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/func_15043BB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/func_15043CA4.s")
