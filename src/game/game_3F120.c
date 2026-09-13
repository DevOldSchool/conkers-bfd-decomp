#include "types.h"

/*
 * Reviewed source unit: src/game/game_3F120.c
 * Boundary evidence: docs/evidence/game_small_multi_function_units.md
 */

void func_15103800(void);
extern s32 D_800D9AA0[3];

void func_15011C70(void) {
    D_800D9AA0[0] = 0;
    D_800D9AA0[1] = 0;
    D_800D9AA0[2] = 0;
    func_15103800();
}
void func_15011CA0(void) {
    func_15103800();
}
void func_15195AA8(s32, s32, s32, s32, s32, s32, s32, s32);

extern s32 D_800902E4;
extern s32 D_800B0E00;
extern s32 D_800B0E04;

void func_15011CC0(void) {
    func_15195AA8(D_800B0E00, D_800902E4, 0, -1, 0, 0, 0, 4);
    func_15195AA8(D_800B0E04, D_800902E4, 0, -1, 0, 1, 0, 4);
}
