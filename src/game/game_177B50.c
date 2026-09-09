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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514B844 CURRENT (30) */
s32 func_1514B844(void *arg0) {
    s16 temp_v1;
    s32 temp_a0;
    void *temp_v0;

    temp_v1 = *(s16 *)((u8 *)arg0 + 0x1C);
    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    if (temp_v1 < 0x10) {
        temp_a0 = temp_v1 * 0x10;
        if (temp_a0 < (s32) *(u8 *)((u8 *)temp_v0 + 0x1B)) {
            *(u8 *)((u8 *)temp_v0 + 0x1B) = (u8) temp_a0;
        }
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514B844 */
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
s32 func_150ADA20();                                /* extern */
f32 func_150ADA68();                                /* extern */
extern f32 D_800A5888;
extern f32 D_800A588C;
extern f32 D_800A5890;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514BC08 CURRENT (360) */
s32 func_1514BC08(void *arg0, void *arg1) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;

    *(f32 *)((u8 *)arg1 + 0x1C) = (f32) (*(f32 *)((u8 *)arg1 + 0x1C) - D_800BE9A4);
    if (*(f32 *)((u8 *)arg1 + 0x1C) < 0.0f) {
        *(f32 *)((u8 *)arg1 + 0x1C) = (f32) (func_150ADA68() * 4.0f);
        *(f32 *)((u8 *)arg1 + 0x10) = (f32) ((func_150ADA68() * *(f32 *)((u8 *)arg1 + 8)) + *(f32 *)((u8 *)arg1 + 0));
    }
    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x2C);
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (temp_fv0 + ((*(f32 *)((u8 *)arg1 + 0x10) - temp_fv0) * D_800A5888));
    *(f32 *)((u8 *)arg1 + 0x20) = (f32) (*(f32 *)((u8 *)arg1 + 0x20) - D_800BE9A4);
    if (*(f32 *)((u8 *)arg1 + 0x20) < 0.0f) {
        *(f32 *)((u8 *)arg1 + 0x20) = (f32) (func_150ADA68() * 9.0f);
        if (func_150ADA20() & 1) {
            *(f32 *)((u8 *)arg1 + 0x14) = (f32) ((func_150ADA68() * *(f32 *)((u8 *)arg1 + 0xC)) + *(f32 *)((u8 *)arg1 + 4));
        } else {
            *(f32 *)((u8 *)arg1 + 0x14) = (f32) ((func_150ADA68() * *(f32 *)((u8 *)arg1 + 0x18)) + *(f32 *)((u8 *)arg1 + 4));
        }
    }
    temp_fv0_2 = *(f32 *)((u8 *)arg0 + 0x30);
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (temp_fv0_2 + ((*(f32 *)((u8 *)arg1 + 0x14) - temp_fv0_2) * D_800A588C));
    *(f32 *)((u8 *)arg1 + 0x30) = (f32) (*(f32 *)((u8 *)arg1 + 0x30) - D_800BE9A4);
    if (*(f32 *)((u8 *)arg1 + 0x30) < 0.0f) {
        *(f32 *)((u8 *)arg1 + 0x30) = (f32) (func_150ADA68() * 7.0f);
        *(f32 *)((u8 *)arg1 + 0x2C) = (f32) ((func_150ADA68() * *(f32 *)((u8 *)arg1 + 0x28)) + *(f32 *)((u8 *)arg1 + 0x24));
    }
    temp_fv0_3 = *(f32 *)((u8 *)arg1 + 0x34);
    *(f32 *)((u8 *)arg1 + 0x34) = (f32) (temp_fv0_3 + ((*(f32 *)((u8 *)arg1 + 0x2C) - temp_fv0_3) * D_800A5890));
    *(s32 *)((u8 *)arg0 + 0x24) = (s32) *(f32 *)((u8 *)arg1 + 0x34);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514BC08 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_177B50/func_1514BC08.s")
