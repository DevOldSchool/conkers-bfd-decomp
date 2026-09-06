#include "types.h"

/*
 * Reviewed source unit: src/game/game_E6A10.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B9560
 * - func_150B963C
 * - func_150B9D14
 * - func_150B9D8C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_E6A10/func_150B9560.s")
typedef struct GameE6A10Object {
    u8 pad0[0x1C];
    s16 field_1C;
    u8 pad1E[0xA];
    s8 field_28;
    u8 pad29[0x33];
    s8 field_5C;
} GameE6A10Object;

s32 func_150B95FC(GameE6A10Object *arg0) {
    s16 value = arg0->field_1C;

    if (value < 0x20) {
        arg0->field_5C = value * 8;
    }

    return 1;
}
s32 func_150B961C(GameE6A10Object *arg0) {
    s16 value = arg0->field_1C;

    if (value < 0x40) {
        arg0->field_28 = value * 4;
    }

    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_E6A10/func_150B963C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E6A10/func_150B9D14.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E6A10/func_150B9D8C.s")
