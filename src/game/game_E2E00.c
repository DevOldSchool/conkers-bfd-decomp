#include "types.h"

/*
 * Reviewed source unit: src/game/game_E2E00.c
 * Boundary evidence: docs/evidence/game_raw_owner_particle_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B5950
 * - func_150B5A3C
 * - func_150B5C38
 * - func_150B5E34
 * - func_150B6000
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_E2E00/func_150B5950.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E2E00/func_150B5A3C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E2E00/func_150B5C38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E2E00/func_150B5E34.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E2E00/func_150B6000.s")
/* Call context: func_15143134: unique active project prototype */
void func_15143134(f32 *, f32 *, s32);
extern f32 D_8009FC30;

void func_150B60E0(void *arg0, f32 *arg1) {
    func_15143134(&D_8009FC30, arg1, *(s32 *)((u8 *)arg0 + 0x1D4) + 0x140);
}
