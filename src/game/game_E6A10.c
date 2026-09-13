#include "types.h"

/*
 * Reviewed source unit: src/game/game_E6A10.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B9560
 * - func_150B963C
 * - func_150B9D8C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern f32 D_8009FDD4;
extern f32 D_8009FDD8;
extern f32 D_8009FDDC;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B9560 CURRENT (2445) */
s32 func_150B9560(void *arg0) {
    if (*(s16 *)((u8 *)arg0 + 0x1C) < 0x50) {
        *(f32 *)((u8 *)arg0 + 0x110) = (f32) (*(f32 *)((u8 *)arg0 + 0x110) + (D_8009FDD4 * D_800BE9A4));
        *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)arg0 + 0x38) - *(f32 *)((u8 *)arg0 + 0x110));
    }
    if (*(s16 *)((u8 *)arg0 + 0x1C) >= 0x73) {
        *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (*(f32 *)((u8 *)arg0 + 0x2C) * D_8009FDD8);
        *(f32 *)((u8 *)arg0 + 0x30) = (f32) (*(f32 *)((u8 *)arg0 + 0x30) * D_8009FDD8);
        return 1;
    }
    if (*(s16 *)((u8 *)arg0 + 0x1C) < 0x41) {
        *(f32 *)((u8 *)arg0 + 0x30) = (f32) (*(f32 *)((u8 *)arg0 + 0x30) + D_8009FDDC);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B9560 */
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
typedef struct {
    u8 pad0[0x18];
    s32 field_18;
    s32 field_1C;
    f32 field_20;
    f32 field_24;
    f32 field_28;
    s32 field_2C;
    f32 field_30;
    f32 field_34;
    f32 field_38;
    f32 field_3C;
    f32 field_40;
} GameE6A10TransformCommand;

void func_15142600(void *, s32, s32, s32, f32, f32, f32, f32, f32, f32, f32, f32);

s32 func_150B9D14(void *arg0, GameE6A10TransformCommand *arg1) {
    func_15142600(arg0, arg1->field_18, arg1->field_1C, arg1->field_2C,
        arg1->field_30, arg1->field_34, arg1->field_38, arg1->field_3C,
        arg1->field_40, arg1->field_20, arg1->field_24, arg1->field_28);
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_E6A10/func_150B9D8C.s")
