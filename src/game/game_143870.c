#include "types.h"

/*
 * Reviewed source unit: src/game/game_143870.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1511650C
 * - func_15116888
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

f32 func_15047C00(f32);
extern f32 D_800A2FB0;
extern f32 D_800A2FB4;
extern s32 D_800BE9E4;

void func_151163C0(u8 *actor) {
    volatile f32 sp2C;
    s32 sp28;
    s32 sp24;
    volatile f32 sp20;
    s16 sp1E;
    f32 sp18;
    f32 result;
    s32 packed;
    s32 component;

    packed = *(s32 *)(actor + 0x3C);
    component = (packed >> 8) & 0xFF;
    sp28 = (packed >> 16) & 0xFF;
    sp2C = (f32)(packed & 0xFF);
    sp24 = (packed >> 24) & 0xFF;
    sp20 = (f32)(u32)component * 1.40625f;
    sp1E = *(s16 *)(actor + 0x12);
    sp18 = *(f32 *)actor;
    *(f32 *)(actor + 0x18) = func_15047C00((f32)*(s32 *)(actor + 0x7C) * D_800A2FB0) * sp2C;
    result = func_15047C00((f32)*(s32 *)(actor + 0x80) * D_800A2FB4) * sp20;
    *(f32 *)actor = result;
    *(s32 *)(actor + 0x7C) += sp28 * D_800BE9E4;
    *(s32 *)(actor + 0x80) += sp24 * D_800BE9E4;
    *(s16 *)(actor + 0x5C) = *(s16 *)(actor + 0x12) - sp1E;
    *(f32 *)(actor + 0x60) = result - sp18;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_143870/func_1511650C.s")
f32 func_15048A40(s32);                             /* extern */
s32 func_150490A8(f32 *, s32);                      /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15116888 CURRENT (2279) */
s32 func_15116888(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    f32 sp1C;
    f32 sp24;

    sp1C = (f32) ((s32) *(f32 *)((u8 *)arg3 + 0x14) - arg0);
    sp24 = (f32) ((s32) *(f32 *)((u8 *)arg3 + 0x1C) - arg1);
    return (s32) (*(f32 *)((u8 *)arg3 + 0x3C) * func_15048A40(((0x40 - ((s32) *(u16 *)((u8 *)arg3 + 0x76) >> 8)) - func_150490A8(&sp1C, arg0)) & 0xFF));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15116888 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_143870/func_15116888.s")
void func_15116924(s32 arg0) {

}
