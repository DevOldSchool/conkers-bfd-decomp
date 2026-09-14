#include "types.h"

/*
 * Reviewed source unit: src/game/game_F20A0.c
 * Boundary evidence: docs/evidence/game_medium_single_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C4BF0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_1509BE40(s32, ...);
void func_1509BFB0(s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C4BF0 CURRENT (70) */
void func_150C4BF0(void *arg0) {
    s32 temp_v1;

    if (func_1509BE40(1, 0x403F, 6, 0x2000) != 0) {
        temp_v1 = *(s32 *)((u8 *)arg0 + 0x84);
        *(s32 *)((u8 *)arg0 + 0x84) = temp_v1 | 0x01000000;
    } else {
        temp_v1 = *(s32 *)((u8 *)arg0 + 0x84);
        *(s32 *)((u8 *)arg0 + 0x84) = temp_v1 & 0xFEFFFFFF;
    }
    if (func_1509BE40(1, 0x4019, 6, 0x2000) != 0) {
        func_1509BFB0(1, 0x9000, 0x10, 0xA0);
        return;
    }
    if (func_1509BE40(1, 0x4044, 6, 0x2000) != 0) {
        func_1509BFB0(1, 0x9000, 0x10, 0);
        return;
    }
    if (func_1509BE40(4, 0x2000, 0xAC, 0x401B, 0x401C, 0x401D, 0x401E) != 0) {
        func_1509BFB0(1, 0x9000, 0x10, -0x96);
        return;
    }
    func_1509BFB0(1, 0x9000, 0x10, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C4BF0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F20A0/func_150C4BF0.s")
