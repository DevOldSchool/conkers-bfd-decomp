#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E58B0.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B8400
 * - func_151B85AC
 * - func_151B8668
 * - func_151B86F4
 * - func_151B8908
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E58B0/func_151B8400.s")
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B85AC CURRENT (105) */
s32 func_151B85AC(void *arg0) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x110);
    if (temp_v0 != 0) {
        *(s32 *)((u8 *)arg0 + 0x34) = (s32) *(s32 *)((u8 *)temp_v0 + 0x38);
        *(s32 *)((u8 *)arg0 + 0x38) = (s32) *(s32 *)((u8 *)temp_v0 + 0x3C);
        *(s32 *)((u8 *)arg0 + 0x3C) = (s32) *(s32 *)((u8 *)temp_v0 + 0x40);
        *(f32 *)((u8 *)arg0 + 0x40) = (f32) (*(f32 *)((u8 *)arg0 + 0x40) + (*(f32 *)((u8 *)arg0 + 0x4C) * D_800BE9A4));
        *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)arg0 + 0x44) + (*(f32 *)((u8 *)arg0 + 0x50) * D_800BE9A4));
        *(f32 *)((u8 *)arg0 + 0x48) = (f32) (*(f32 *)((u8 *)arg0 + 0x48) + (*(f32 *)((u8 *)arg0 + 0x54) * D_800BE9A4));
    } else {
        *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) | 1);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B85AC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E58B0/func_151B85AC.s")
void func_1513FA70(s32 arg0, s16 arg1);

void func_151B863C(s32 arg0, s16 arg1) {
    func_1513FA70(arg0, arg1);
}
/* Call context: func_15134908: unique active project prototype */
void func_15134908(s32 *, s32, u8, s32);
extern f32 D_800AA4C8;
extern f32 D_800DCA24;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B8668 CURRENT (2093) */
void func_151B8668(s32 arg0, u8 arg1, s32 arg2) {
    s8 sp2F;
    s8 sp2E;
    s16 sp2C;
    f32 sp28;
    f32 sp24;
    s32 sp20;
    s32 sp1C;
    s32 sp18;

    sp18 = arg0 + 0x38;
    sp1C = arg0 + 0x3C;
    sp20 = arg0 + 0x40;
    sp28 = D_800AA4C8 * D_800DCA24;
    sp2C = 0x12C;
    sp2E = 0;
    sp2F = 3;
    {
        s8 sp30 = 0;
    sp24 = 10.0f;
    func_15134908(&sp18, 0, arg1, arg2);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B8668 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E58B0/func_151B8668.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E58B0/func_151B86F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E58B0/func_151B8908.s")
