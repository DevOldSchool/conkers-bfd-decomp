#include "types.h"

/*
 * Reviewed source unit: src/game/game_177B50.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1514A6A0
 * - func_1514AB5C
 * - func_1514AD9C
 * - func_1514AF74
 * - func_1514B034
 * - func_1514B364
 * - func_1514B844
 * - func_1514B8E4
 * - func_1514BC08
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_177B50/func_1514A6A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_177B50/func_1514AB5C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_177B50/func_1514AD9C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_177B50/func_1514AF74.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_177B50/func_1514B034.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_177B50/func_1514B364.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_177B50/func_1514B844.s")
extern f32 D_800BE9A4;

s32 func_1514B87C(void *arg0) {
    f32 temp_fv0;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x4C) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (*(f32 *)((u8 *)arg0 + 0x2C) + temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (*(f32 *)((u8 *)arg0 + 0x30) + temp_fv0);
    return 1;
}
s32 func_1514B8B0(void *arg0) {
    s16 temp_v0;
    s32 temp_v1;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    if (temp_v0 < 0x10) {
        temp_v1 = temp_v0 * 0x10;
        if (temp_v1 < (s32) *(u8 *)((u8 *)arg0 + 0x5C)) {
            *(u8 *)((u8 *)arg0 + 0x5C) = (u8) temp_v1;
        }
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_177B50/func_1514B8E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_177B50/func_1514BC08.s")
