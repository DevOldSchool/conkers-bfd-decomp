#include "types.h"

/*
 * Reviewed source unit: src/game/game_108AE0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_subranges.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150DB714
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_150DB630(void *arg0) {
    f32 value;

    if (**(f32 *volatile *)((u8 *)arg0 + 0x120) > 255.0f) {
        *(u8 *)((u8 *)arg0 + 0x5C) = 0xFF;
    } else {
        value = **(f32 *volatile *)((u8 *)arg0 + 0x120);
        if (value < 0.0f) {
            *(u8 *)((u8 *)arg0 + 0x5C) = 0;
        } else {
            *(u8 *)((u8 *)arg0 + 0x5C) = (u32)value;
        }
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_108AE0/func_150DB714.s")
