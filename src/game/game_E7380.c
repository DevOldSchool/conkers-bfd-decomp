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
extern f32 D_8009FE2C;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150BA37C CURRENT (140) */
s32 func_150BA37C(void *arg0) {
    *(f32 *)((u8 *)arg0 + 0x114) = (f32) (*(f32 *)((u8 *)arg0 + 0x114) + (D_8009FE2C * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x34) = (f32) (*(f32 *)((u8 *)arg0 + 0x34) + (*(f32 *)((u8 *)arg0 + 0x110) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)arg0 + 0x38) + (*(f32 *)((u8 *)arg0 + 0x114) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C) + (*(f32 *)((u8 *)arg0 + 0x118) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) (*(f32 *)((u8 *)arg0 + 0x40) + (*(f32 *)((u8 *)arg0 + 0x11C) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)arg0 + 0x44) + (*(f32 *)((u8 *)arg0 + 0x120) * D_800BE9A4));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150BA37C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E7380/func_150BA37C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E7380/func_150BA424.s")
