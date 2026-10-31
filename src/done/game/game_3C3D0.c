#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_3C3D0.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_medium_single_function_units.md
 */

typedef struct Game3C3D0Spark {
    f32 x;
    f32 y;
    f32 size;
    f32 z;
} Game3C3D0Spark;

void *func_10022EC0(void *, const void *, u32);
void func_15195AA8(s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_800902B8;
extern s32 D_800B0E00;
extern s32 D_800B0E04;
extern f32 D_80096220;
extern f32 D_80096224;
extern f32 D_80096228;
extern f32 D_8009622C;
extern f32 D_80096230;
extern f32 D_80096234;
extern f32 D_80096238;
extern f32 D_8009623C;
extern f32 D_80096240;
extern f32 D_80096244;
extern u8 D_800DCD20[3];
extern f32 D_800DCD94;
extern f32 D_800DCD98;
extern f32 D_800DCD9C;
extern f32 D_800DCDA0;

void func_1500EF20(void) {
    void *result;
    Game3C3D0Spark spark;

    func_15195AA8(D_800B0E00, D_800902B8, 1, -1, 0, 0, 0, -8);
    func_15195AA8(D_800B0E04, D_800902B8, 1, -1, 0, 1, 0, -8);
    spark.x = D_80096220;
    spark.y = D_80096224;
    spark.z = D_80096228;
    spark.size = 400.0f;
    result = func_151491F4(func_150ADA20() % 51U + 25, 5, -1, 1, 0, 0x10, 0xFF, 0);
    if (result != NULL) {
        func_10022EC0((u8 *)result + 0x28, &spark, 0x10);
    }
    spark.x = D_8009622C;
    spark.y = D_80096230;
    spark.z = D_80096234;
    result = func_151491F4(func_150ADA20() % 51U + 25, 5, -1, 1, 0, 0x10, 0xFF, 0);
    if (result != NULL) {
        func_10022EC0((u8 *)result + 0x28, &spark, 0x10);
    }
    spark.y = D_80096238;
    result = func_151491F4(func_150ADA20() % 51U + 25, 5, -1, 1, 0, 0x10, 0xFF, 0);
    if (result != NULL) {
        func_10022EC0((u8 *)result + 0x28, &spark, 0x10);
    }
    spark.x = D_8009623C;
    spark.y = D_80096240;
    spark.z = D_80096244;
    result = func_151491F4(func_150ADA20() % 51U + 25, 5, -1, 1, 0, 0x10, 0xFF, 0);
    if (result != NULL) {
        func_10022EC0((u8 *)result + 0x28, &spark, 0x10);
    }
    D_800DCD94 = D_800DCD20[0];
    D_800DCD98 = D_800DCD20[1];
    D_800DCD9C = D_800DCD20[2];
    D_800DCDA0 = 0.0f;
}
