#include "types.h"

/*
 * Reviewed source unit: src/game/game_1B5370.c
 * Boundary evidence: docs/evidence/game_raw_display_transition_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15187EC0
 * - func_15187FC0
 * - func_1518804C
 * - func_151880C0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5370/func_15187EC0.s")
void func_100226F0(void *arg0, s32 arg1);
extern s32 D_800DF700;
extern s32 D_800DF7B4;

void func_15187F90(void) {
    func_100226F0(&D_800DF700, 0xB4);
    D_800DF7B4 = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5370/func_15187FC0.s")
extern f32 D_800DF70C[];

void func_15188010(s32 arg0, f32 *arg1) {
    if ((arg0 < D_800DF7B4) && (arg0 >= 0)) {
        *arg1 = *(f32 *)((u8 *)D_800DF70C + (arg0 * 0x24));
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5370/func_1518804C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5370/func_151880C0.s")
