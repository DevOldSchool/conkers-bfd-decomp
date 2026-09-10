#include "types.h"

/*
 * Reviewed source unit: src/game/game_1BC650.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1518F1A0
 * - func_1518F384
 * - func_1518F45C
 * - func_1518F49C
 * - func_1518F51C
 * - func_1518F5D0
 * - func_1518F7C4
 * - func_1518F858
 * - func_1518F89C
 * - func_1518F8E0
 * - func_1518FC04
 * - func_1518FC44
 * - func_1518FC84
 * - func_1518FDC4
 * - func_1519003C
 * - func_1519021C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

u32 func_150ADA20();                                /* extern */
f32 func_150ADA68();                                /* extern */
extern f32 D_800A7B68;
extern f32 D_800A7B6C;
extern f32 D_800A7B70;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518F1A0 CURRENT (2240) */
s32 func_1518F1A0(u8 *arg0) {
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 temp_fv1_3;
    f32 temp_fv1_4;
    s32 temp_v1;
    u8 *temp_s0;
    u8 *temp_s0_2;

    *(s16 *)((u8 *)arg0 + 0x12E) = (s16) (*(s16 *)((u8 *)arg0 + 0x12E) - D_800BE9E4);
    if (*(s16 *)((u8 *)arg0 + 0x12E) < 0) {
        temp_s0 = (void *)(arg0 + 0x110);
        *(s16 *)((u8 *)temp_s0 + 0x1E) = (s16) (func_150ADA20() % 6U);
        if (func_150ADA20() & 3) {
            temp_fv1 = *(f32 *)((u8 *)temp_s0 + 0x10);
            *(f32 *)((u8 *)temp_s0 + 0x18) = (f32) ((func_150ADA68() * (*(f32 *)((u8 *)temp_s0 + 0xC) - temp_fv1)) + temp_fv1);
        } else {
            temp_fv1_2 = *(f32 *)((u8 *)temp_s0 + 0xC);
            *(f32 *)((u8 *)temp_s0 + 0x18) = (f32) ((func_150ADA68() * (*(f32 *)((u8 *)temp_s0 + 0x14) - temp_fv1_2)) + temp_fv1_2);
        }
    }
    temp_s0_2 = (void *)(arg0 + 0x110);
    {
        f32 temp_fv0 = *(f32 *)((u8 *)arg0 + 0x30);
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (temp_fv0 + ((*(f32 *)((u8 *)temp_s0_2 + 0x18) - temp_fv0) * D_800A7B68));
    *(s16 *)((u8 *)temp_s0_2 + 0x1C) = (s16) (*(s16 *)((u8 *)temp_s0_2 + 0x1C) - D_800BE9E4);
    if (*(s16 *)((u8 *)temp_s0_2 + 0x1C) < 0) {
        *(s16 *)((u8 *)temp_s0_2 + 0x1C) = (s16) (func_150ADA20() % 17U);
        temp_fv1_3 = *(f32 *)((u8 *)temp_s0_2 + 4);
        *(f32 *)((u8 *)temp_s0_2 + 8) = (f32) ((func_150ADA68() * (*(f32 *)((u8 *)arg0 + 0x110) - temp_fv1_3)) + temp_fv1_3);
    }
    temp_fv0_2 = *(f32 *)((u8 *)arg0 + 0x2C);
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (temp_fv0_2 + ((*(f32 *)((u8 *)temp_s0_2 + 8) - temp_fv0_2) * D_800A7B6C));
    *(s16 *)((u8 *)temp_s0_2 + 0x2C) = (s16) (*(s16 *)((u8 *)temp_s0_2 + 0x2C) - D_800BE9E4);
    if (*(s16 *)((u8 *)temp_s0_2 + 0x2C) < 0) {
        *(s16 *)((u8 *)temp_s0_2 + 0x2C) = (s16) (func_150ADA20() % 15U);
        temp_fv1_4 = *(f32 *)((u8 *)temp_s0_2 + 0x24);
        *(f32 *)((u8 *)temp_s0_2 + 0x28) = (f32) ((func_150ADA68() * (*(f32 *)((u8 *)temp_s0_2 + 0x20) - temp_fv1_4)) + temp_fv1_4);
    }
    temp_v1 = *(s32 *)((u8 *)arg0 + 0x24);
    *(s32 *)((u8 *)arg0 + 0x24) = (s32) (temp_v1 + (s32) ((*(f32 *)((u8 *)temp_s0_2 + 0x28) - (f32) temp_v1) * D_800A7B70));
    return 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518F1A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518F1A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518F384.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518F45C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518F49C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518F51C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518F5D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518F7C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518F858.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518F89C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518F8E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518FC04.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518FC44.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518FC84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518FDC4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1519003C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1519021C.s")
