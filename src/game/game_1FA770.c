#include "types.h"

/*
 * Reviewed source unit: src/game/game_1FA770.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151CD2C0
 * - func_151CD35C
 * - func_151CD394
 * - func_151CD3CC
 * - func_151CD4C0
 * - func_151CD674
 * - func_151CD7BC
 * - func_151CDB94
 * - func_151CDE20
 * - func_151CE47C
 * - func_151CE49C
 * - func_151CE4DC
 * - func_151CE51C
 * - func_151CE634
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CD2C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CD35C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CD394.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CD3CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CD4C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CD674.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CD7BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CDB94.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CDE20.s")
typedef struct Game1FA770Object {
    u8 pad0[0x1E];
    volatile u16 flags;
    u8 pad20[0x10];
    s8 field_30;
} Game1FA770Object;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CE47C CURRENT (35) */
void func_151CE47C(Game1FA770Object *arg0) {
    u16 flags;

    arg0->field_30 = 0;
    flags = arg0->flags & 0xFFFD;
    arg0->flags = flags;
    arg0->flags = flags | 8;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CE47C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CE47C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CE49C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CE4DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CE51C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CE634.s")
