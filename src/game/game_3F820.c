#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_3F820.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_next_compact_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150124A0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern void *D_80088750;

void func_151EF954(void *, f32, f32, f32, f32, f32, f32, f32);
extern s32 D_80082FA0;
extern u8 *D_800BE628;
extern u8 D_800DCC10[];
extern f32 D_80096560;

void func_15012370(void) {
    s32 i;
    f32 foo;

    i = 0;
    if (D_80082FA0 >= 0) {
        foo = D_80096560;
        do {
            func_151EF954((void *)((u8 *)D_800DCC10 + (i << 6)),
                    -(((Cam180 *)D_800BE628)[i].unk4 * 0.5f),
                    (((Cam180 *)D_800BE628)[i].unk4 * 0.5f),
                    -(((Cam180 *)D_800BE628)[i].unk8 * 0.5f),
                    ((Cam180 *)D_800BE628)[i].unk8 * 0.5f,
                    1.0f, foo, 1.0f);
            i = (i + 1) & 0xFF;
        } while (D_80082FA0 >= i);
    }
}
void func_15012470(void) {
    D_80088750 = func_1518AADC(4, 0x12C, 0);
}
typedef struct Game3F820Point {
    f32 x, y, z;
    s32 value;
} Game3F820Point;

typedef struct Game3F820Spread {
    u8 pad0[0xC];
    u8 baseAngle;
    u8 padD[3];
} Game3F820Spread;

void *func_10022EC0(void *, const void *, u32);
s32 func_150AC9C0(f32, f32, f32, f32, f32, f32, void *, s16 *, f32 *, f32 *, f32 *, f32 *, s32 *, void *, f32);
extern f32 D_80096570;
extern Game3F820Spread D_8009F920[3];
extern Game3F820Point D_800DCA30[3][10];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150124A0 CURRENT (945) */
void func_150124A0(void) {
    s32 row;
    s32 i;
    s16 yaw;
    s16 pitch;
    f32 scale;
    void *result;
    Vec3f hit;
    f32 yawCos;
    f32 yawSin;
    f32 pitchCos;
    f32 radius;
    f32 dirX;
    f32 dirY;
    f32 dirZ;
    s16 timer[3];

    scale = D_80096570;
    for (row = 0; row < 3; row++) {
        for (i = 0; i < 10; i++) {
            yaw = D_8009F920[row].baseAngle + func_150ADA20() % 13U - 0x86;
            pitch = (func_150ADA20() & 0xF) - 10;
            yawCos = func_151423D8(yaw - 0x40);
            yawSin = func_151423D8(yaw);
            pitchCos = func_151423D8(pitch - 0x40);
            radius = 10.0f * func_151423D8(pitch);
            dirX = radius * yawCos;
            dirY = -10.0f * pitchCos;
            dirZ = radius * yawSin;
            if (func_150AC9C0(0.0f, 300.0f, 0.0f, dirX, dirY, dirZ, NULL, NULL,
                              &hit.x, &hit.y, &hit.z, NULL, NULL, NULL, 0.0f) == 0) {
                D_800DCA30[row][i].x = 0.0f;
                D_800DCA30[row][i].y = 0.0f;
                D_800DCA30[row][i].z = 0.0f;
            } else {
                D_800DCA30[row][i].x = hit.x * scale;
                D_800DCA30[row][i].z = hit.z * scale;
                D_800DCA30[row][i].y = (hit.y - 300.0f) * scale + 300.0f;
            }
        }
    }
    timer[0] = 0x14;
    timer[1] = 0x32;
    timer[2] = 0;
    result = func_151491F4(0x12C, -1, 7, 0, 0, 6, 0xFF, 0);
    if (result != NULL) {
        func_10022EC0((u8 *)result + 0x28, timer, 6);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150124A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_3F820/func_150124A0.s")
