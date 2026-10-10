#include "types.h"
#include "game_functions.h"

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
    f32 heightScale;
    s32 heightRate;
    s32 swayRate;
    f32 swayScale;
    s16 previousHeight;
    f32 previousSway;
    f32 result;

    heightRate = (*(s32 *)(actor + 0x3C) >> 16) & 0xFF;
    heightScale = (f32)(*(s32 *)(actor + 0x3C) & 0xFF);
    swayRate = (*(s32 *)(actor + 0x3C) >> 24) & 0xFF;
    swayScale = (f32)(u32)((*(s32 *)(actor + 0x3C) >> 8) & 0xFF) * 1.40625f;
    previousHeight = *(s16 *)(actor + 0x12);
    previousSway = *(f32 *)actor;
    *(f32 *)(actor + 0x18) = func_15047C00((f32)*(s32 *)(actor + 0x7C) * D_800A2FB0) * heightScale;
    result = func_15047C00((f32)*(s32 *)(actor + 0x80) * D_800A2FB4) * swayScale;
    *(f32 *)actor = result;
    *(s32 *)(actor + 0x7C) += heightRate * D_800BE9E4;
    *(s32 *)(actor + 0x80) += swayRate * D_800BE9E4;
    *(s16 *)(actor + 0x5C) = *(s16 *)(actor + 0x12) - previousHeight;
    *(f32 *)(actor + 0x60) = result - previousSway;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_143870/func_1511650C.s")

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
    cosine = func_15048A40(angle);
    result = *(f32 *)((u8 *)arg3 + 0x3C) * cosine;
    return (s32)result;
}
void func_15116924(s32 arg0) {

}
