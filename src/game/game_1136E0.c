#include "types.h"

/*
 * Reviewed source unit: src/game/game_1136E0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_subranges.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E6230
 * - func_150E63A0
 * - func_150E67D0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1136E0/func_150E6230.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1136E0/func_150E63A0.s")
s32 func_150E679C(void *arg0) {
    s16 temp_v0;
    s32 temp_v1;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    if (temp_v0 < 8) {
        temp_v1 = temp_v0 << 5;
        if (temp_v1 < (s32) *(u8 *)((u8 *)arg0 + 0x5C)) {
            *(u8 *)((u8 *)arg0 + 0x5C) = (u8) temp_v1;
        }
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1136E0/func_150E67D0.s")
