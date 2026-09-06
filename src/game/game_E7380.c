#include "types.h"

/*
 * Reviewed source unit: src/game/game_E7380.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B9ED0
 * - func_150BA37C
 * - func_150BA424
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_E7380/func_150B9ED0.s")
typedef struct GameE7380Object {
    u8 pad0[0x1C];
    s16 field_1C;
    u8 pad1E[0xA];
    s8 field_28;
} GameE7380Object;

s32 func_150BA35C(GameE7380Object *arg0) {
    s16 value = arg0->field_1C;

    if (value < 0x40) {
        arg0->field_28 = value * 4;
    }

    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_E7380/func_150BA37C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E7380/func_150BA424.s")
