#include "types.h"

/*
 * Reviewed source unit: src/game/game_112F90.c
 * Boundary evidence: docs/evidence/game_raw_direct_call_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E5AE0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game112F90Camera {
    u8 pad00[0x2F8];
    f32 x, y, z;
} Game112F90Camera;
f32 func_15047C00(f32);
f32 func_15047D60(f32);
void func_150E4514(s32);
s32 func_151EF610(void);
void func_150E1AB0(s32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32,
                  s16, u16, s8, s16, s16, void *, u8, u8, s32, u8, u8,
                  f32, f32, f32, f32, f32, f32);
extern s32 D_80088A04;
extern f32 D_800A1170, D_800A1174, D_800A1178, D_800A117C, D_800A1180, D_800A1184;
extern s32 D_800BE9E4, D_800D9A04, D_800D9A08, D_800D9A0C, D_800D9A10, D_800D9A14;
extern Game112F90Camera *D_800DBFF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E5AE0 CURRENT (6720) */
void func_150E5AE0(void) {
    f32 angle1;
    f32 angle2;
    f32 height1;
    f32 height2;
    f32 radians1;
    f32 radians2;
    f32 x1;
    f32 z1;
    f32 x2;
    f32 z2;
    f32 x;
    f32 y;
    f32 z;
    s32 angleInt1;
    s32 angleInt2;
    s32 timer;
    s32 strength;
    s32 count;
    s32 chance;
    s32 i;

    if (D_80088A04 == 1) {
        timer = D_800D9A10 + D_800BE9E4;
        D_800D9A10 = timer;
        if (timer >= 131) {
            timer = -(func_151EF610() % 30);
            D_800D9A10 = timer;
        }
        if (timer >= 31) {
            strength = D_800D9A14;
            if (strength < D_800D9A0C) {
                strength += D_800BE9E4 * 2;
                D_800D9A14 = strength;
            }
        } else {
            if (D_800BE9E4 < D_800D9A14) {
                strength = D_800D9A14 - D_800BE9E4;
                D_800D9A14 = strength;
            } else {
                D_80088A04 = 0;
                D_800D9A14 = 0;
                strength = 0;
            }
        }
        count = (strength + 10) / 10;
        chance = strength + 1;
        func_150E4514(strength);
        i = 0;
        if (count > 0) {
            do {
                if (chance >= 10 || func_151EF610() % 11 == chance) {
                    angleInt1 = (func_151EF610() % D_800D9A08) * 2 - D_800D9A08 + D_800D9A04;
                    angleInt2 = (func_151EF610() % D_800D9A08) * 2 - D_800D9A08 + D_800D9A04;
                    height2 = (f32) (func_151EF610() % 200);
                    height1 = (f32) (func_151EF610() % 200) + height2 - 100.0f;
                    angle2 = (f32) angleInt2;
                    angle1 = (f32) angleInt1;
                    if (angle2 - 5.0f < angle1 && angle1 < angle2 + 5.0f) {
                        height1 += 150.0f;
                        height2 += 150.0f;
                    }
                    if (func_151EF610() % 2 != 0) {
                        angleInt1 = (s32) (angle1 + 180.0f);
                        angle1 = (f32) angleInt1;
                    } else {
                        angleInt2 = (s32) (angle2 + 180.0f);
                        angle2 = (f32) angleInt2;
                    }
                    radians1 = angle1 * D_800A1170;
                    x1 = func_15047D60(radians1) * D_800A1174;
                    z1 = func_15047C00(radians1) * D_800A1178;
                    radians2 = angle2 * D_800A117C;
                    x2 = func_15047D60(radians2) * D_800A1180;
                    z2 = func_15047C00(radians2) * D_800A1184;
                    x = D_800DBFF0->x;
                    y = D_800DBFF0->y;
                    z = D_800DBFF0->z;
                    func_150E1AB0(0, x1 + x, height1 + y, z1 + z, x2 + x, height2 + y, z2 + z,
                                  160.0f, 10.0f, 4.0f, 360.0f, 15, 0x43, 0, 0, 0, 0, 0, 0, -1, 0, 0,
                                  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
                }
                i++;
                chance -= 10;
            } while (i != count);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E5AE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_112F90/func_150E5AE0.s")
