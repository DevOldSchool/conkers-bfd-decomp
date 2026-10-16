#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_FC410.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_singletons_final.md
 */

void func_150A3444(s32, s16, s16, s16);
f32 func_150AD780(f32);
f32 func_150AD78C(f32);
void func_151749A0(s32, s32);
extern f32 D_800A0830;
extern f32 D_800A0834;

void func_150CEF60(s32 arg0) {
    void *source;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 originX;
    f32 originZ;
    s16 screen_x;
    f32 trig;

    source = func_151149AC(4);
    temp_fa0 = *(f32 *)((u8 *)source + 8) * D_800A0830;
    trig = func_150AD78C(temp_fa0);
    temp_fv0 = func_150AD780(temp_fa0);
    originX = -1.0f;
    originZ = 44.0f;
    temp_fv1 = 76.0f;
    temp_fa0_2 = 241.0f;
    temp_fv1 -= originX;
    temp_fa0_2 -= originZ;
    screen_x = (s16)(s32)(((temp_fv1 * temp_fv0) - (temp_fa0_2 * trig)) + originX);
    func_150A3444(2,
                  screen_x,
                  (s16)(s32)((temp_fv1 * trig) + (temp_fa0_2 * temp_fv0) + originZ),
                  (s16)(s32)D_800A0834);
    func_151749A0(5, 3);
}
