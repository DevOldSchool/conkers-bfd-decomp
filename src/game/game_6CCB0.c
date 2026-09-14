#include "types.h"

/*
 * Reviewed source unit: src/game/game_6CCB0.c
 * Boundary evidence: docs/evidence/game_raw_preserved_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1503F800
 * - func_1503F964
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_6CCB0/func_1503F800.s")
extern void func_1503F800(void *, s16, s16, s32, s32);

void func_1503F904(void *arg0, s32 arg1, s32 arg2) {
    func_1503F800((u8 *)arg0 + 0x320, (s16)*(f32 *)((u8 *)arg0 + 0x14),
                  (s16)*(f32 *)((u8 *)arg0 + 0x1C), arg1, 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_6CCB0/func_1503F964.s")
