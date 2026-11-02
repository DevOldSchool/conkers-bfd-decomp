#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1D4140.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_recovered_pointer_helper_groups_continued.md
 */

typedef struct Game1D4140Smoke {
    s16 count;
    u8 pad2[2];
    Vec3f position;
    s16 field10;
    u8 pad12[2];
    f32 field14;
    s16 field18, field1A, field1C, field1E;
    f32 field20, field24, field28, field2C;
    f32 field30, field34, field38, field3C;
    f32 field40, field44, field48, field4C, field50;
    s8 field54, field55;
    s16 field56, field58;
    u8 pad5A[2];
} Game1D4140Smoke;

void func_151A6F00(s16 *, s32, u8, s32);
f32 func_150ADA68(void);
void func_151D5514(f32 *, u8, s32);
void func_151541B8(f32 *, f32, f32, f32, f32, u8, s32);
void func_151D5334(f32 *, f32, f32, f32, s32, s32, s32);
extern f32 D_800A8DB0;

void func_151A6C90(void *arg0, u8 arg1, s32 arg2) {
    Vec3f position;
    Game1D4140Smoke smoke;

    position.x = ((Vec3f *)((u8 *)arg0 + 0x14))->x;
    position.y = ((Vec3f *)((u8 *)arg0 + 0x14))->y;
    position.z = ((Vec3f *)((u8 *)arg0 + 0x14))->z;
    if (arg0 != NULL) {
        smoke.count = (func_150ADA20() & 3) + 6;
        smoke.position = position;
        smoke.field14 = 60.0f;
        smoke.field20 = 0.0f;
        smoke.field24 = 35.0f;
        smoke.field10 = 0x50;
        smoke.field18 = 0;
        smoke.field1A = 0xFF;
        smoke.field1C = -0x3F;
        smoke.field1E = 0x50;
        smoke.field54 = 0;
        smoke.field55 = 0;
        smoke.field56 = 0x32;
        smoke.field58 = 0x19;
        smoke.field44 = -1.0f;
        smoke.field48 = -1.0f;
        smoke.field30 = 0;
        smoke.field34 = 0;
        smoke.field38 = 0;
        smoke.field28 = 10.0f;
        smoke.field2C = 40.0f;
        smoke.field3C = D_800A8DB0;
        smoke.field40 = 0.5f;
        smoke.field4C = -2.0f;
        smoke.field50 = 4.0f;
        func_151A6F00(&smoke.count, 0, arg1, arg2);
        func_151D5334(&position.x, 506.0f, 1013.0f, 0.000987166888f, 5, arg1, arg2);
        func_151D3FF4(&position.x, arg1, arg2);
        func_151D5514(&position.x, arg1, arg2);
        func_151541B8(&position.x, func_150ADA68() * 4.0f + 12.0f, 1.6409999f, func_150ADA20() % 56U + 0xC8, 0.0f, arg1, arg2);
        func_151D5404(&position, 1502.0f, 3000.0f, 0.00033333333f, 0xC, 0xF, 0xFF, 0);
    }
}
