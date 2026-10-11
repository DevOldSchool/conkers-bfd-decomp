#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_130B40.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_extended_code_selected_groups.md
 */

void func_15103690(s32 arg0) {
    func_15103828();
}
void func_15152190(void *, void *, void *, s32, f32, s32, s32, s32);
typedef struct Game130B40Word {
    s32 value;
} Game130B40Word;

typedef struct Game130B40WordVector {
    s32 x;
    s32 y;
    s32 z;
} Game130B40WordVector;

extern Game130B40Word D_800A2350;
extern Game130B40Word D_800A2354;
extern f32 D_800A2358;
extern f32 D_800A235C;
extern f32 D_800A2360;
extern f32 D_800A2364;
extern f32 D_800A2368;

typedef struct Game130B40Params {
    s32 field_0;
    s32 field_4;
    Game130B40WordVector field_8;
    s16 field_14;
    s16 field_16;
    s16 field_18;
    s16 field_1A;
    f32 field_1C;
    f32 field_20;
    f32 field_24;
    f32 field_28;
    s16 field_2C;
    s16 field_2E;
    f32 field_30;
    f32 field_34;
    f32 field_38;
} Game130B40Params;

void func_151036B4(Game130B40WordVector *arg0, u8 arg1, s32 arg2) {
    Game130B40Params params;
    Game130B40Word word1;
    Game130B40Word word2;

    word1 = D_800A2350;
    word2 = D_800A2354;
    params.field_0 = 8;
    params.field_4 = 4;
    params.field_8 = *arg0;
    params.field_1C = 8.0f;
    params.field_20 = 4.0f;
    params.field_14 = 0;
    params.field_16 = 0xFF;
    params.field_18 = -0x40;
    params.field_1A = 0x5D;
    params.field_2C = 0x14;
    params.field_2E = 0xA;
    params.field_24 = D_800A2358;
    params.field_28 = D_800A235C;
    params.field_30 = D_800A2360;
    params.field_34 = D_800A2364;
    params.field_38 = D_800A2368;
    func_15152190(&params, &word1, &word2, 1, 0.0f, 1, arg1, arg2);
}
s32 func_151037DC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return 0;
}
