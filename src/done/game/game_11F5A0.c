#include "types.h"

/*
 * Reviewed source unit: src/game/game_11F5A0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_singletons_continued.md
 */

void func_10010F30(s32, s32, s32, s32, s32);
void func_100114D0(s32, s32, s32, s32, s32, s32, s32 *, s32 *, s32 *);
u32 func_150ADA20(void);
extern f32 D_800A191C;
extern s32 D_800BE9E4;
extern u8 D_800CC2D0[];
extern u8 D_800D98F0;

void func_150F20F0(s32 arg0) {
    f32 temp_fv0;
    f32 temp_fv1;
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    u8 *temp_v0;

    temp_v0 = (arg0 * 0x32C) + D_800CC2D0;
    temp_fv1 = *(f32 *)(temp_v0 + 0x14);
    temp_fv0 = *(f32 *)(temp_v0 + 0x1C);
    temp_fv1 *= temp_fv1;
    temp_fv0 *= temp_fv0;
    temp_fv1 = temp_fv1 * temp_fv1 + temp_fv0 * temp_fv0;
    if (D_800D98F0 != 0) {
        if (D_800BE9E4 < (s32)D_800D98F0) {
            D_800D98F0 -= D_800BE9E4;
            return;
        }
        D_800D98F0 = 0;
        return;
    }
    if (D_800A191C < temp_fv1) {
        func_100114D0(0, (s32)*(f32 *)(arg0 * 0x32C + D_800CC2D0 + 0x18), 0, 0x7FFF,
                       0x4E20, 0x4A38, &sp4C, &sp48, &sp44);
        sp4C += 0x80;
        D_800D98F0 = (func_150ADA20() & 0x7F) + 0x80;
        func_10010F30((func_150ADA20() % 3U) + 0x6C,
                       0x5DC0, *((u8 *)&sp4C + 3), 0, 0);
    }
}
