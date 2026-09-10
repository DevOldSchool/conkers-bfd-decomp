#include "types.h"

/*
 * Reviewed source unit: src/game/game_3BA70.c
 * Boundary evidence: docs/evidence/game_early_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1500E5C0
 * - func_1500E738
 * - func_1500E8C0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_3BA70/func_1500E5C0.s")
void func_1500E70C(s32 arg0) {
    if (arg0 == 0x2B) {
        func_15011C70();
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_3BA70/func_1500E738.s")
/* Call context: func_15008E00: unique active project prototype */
/* Call context: func_15008E10: unique active project prototype */
void func_15008E00(void);
void func_15008E10(s32);

void func_1500E890(void) {
    func_15008E00();
    func_15008E10(0);
    func_15008E10(1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_3BA70/func_1500E8C0.s")
/* Call context: func_15195AA8: unique active project prototype */
void func_15195AA8(s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_80090320;
extern s32 D_800B0E00;
extern s32 D_800B0E04;

void func_1500EAA0(void) {
    func_15195AA8(D_800B0E00, D_80090320, 0, -1, 0, 0, 0, -8);
    func_15195AA8(D_800B0E04, D_80090320, 0, -1, 0, 1, 0, -8);
}
