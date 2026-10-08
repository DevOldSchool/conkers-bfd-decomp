#include "types.h"

/*
 * Reviewed source unit: src/game/game_143870.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_recovered_pointer_helper_groups_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1511650C
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
s32 func_150490A8(f32 *);                      /* extern */

s32 func_15116888(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    s32 x;
    s32 z;
    s32 bearing;
    s32 angle;
    s32 tmp1;
    f32 result;
    f32 displacement[3];
    f32 cosine;

    x = (s32)*(f32 *)((u8 *)arg3 + 0x14);
    z = (s32)*(f32 *)((u8 *)arg3 + 0x1C);
    tmp1 = z;
    displacement[0] = (f32)(x - arg0);
    displacement[2] = tmp1 - arg1;
    bearing = func_150490A8(displacement);
    angle = *(u16 *)((u8 *)arg3 + 0x76);
    angle = 0x40 - (angle >> 8);
    angle -= bearing;
    cosine = func_15048A40(angle & 0xFF);
    result = *(f32 *)((u8 *)arg3 + 0x3C) * cosine;
    return (s32)result;
}
void func_15116924(s32 arg0) {

}
