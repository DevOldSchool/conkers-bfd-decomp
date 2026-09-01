#include "types.h"

/*
 * Reviewed source unit: src/game/game_75E60.c
 * Boundary evidence: docs/evidence/game_final_compact_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150489B0
 * - func_15048A40
 * - func_15048A70
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150489B0(s32 arg0, s32 arg1);

#pragma GLOBAL_ASM("asm/nonmatchings/game_75E60/func_150489B0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15048A40 */
void func_15048A40(u8 arg0) {
    s32 temp_a1 = arg0 & 0xFF;

    func_150489B0((temp_a1 - 0x40) & 0xFF, temp_a1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15048A40 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_75E60/func_15048A40.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_75E60/func_15048A70.s")

s32 func_15048AD0(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = arg0 - arg1;
    if (temp_v0 >= 0xB5) {
        arg0 -= 0x168;
    } else if (temp_v0 < -0xB3) {
        arg1 -= 0x168;
    }
    return arg1 - arg0;
}
