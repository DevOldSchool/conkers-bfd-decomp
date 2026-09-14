#include "types.h"

/*
 * Reviewed source unit: src/game/game_3E460.c
 * Boundary evidence: docs/evidence/game_medium_single_function_units.md
 */

void *func_10003C40(s32, s32, s32, s32);
s32 func_1510F800(s32);
s32 func_1510FD20(s32, s32);
s32 func_151149AC(u8);
s32 func_15195AA8(s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_15195FB0(s32, s32, s32, s32, s32, s32, s32);
extern s32 D_80090310;
extern s32 D_80090314;
extern s32 D_800B0E00;
extern s32 D_800B0E04;
extern s32 *D_800BE4F0;
extern s32 D_800D9A40;

void func_15010FB0(void) {
    D_800BE4F0 = func_10003C40(0x10, 1, 0, 0);
    D_800BE4F0[0] = func_15195AA8(D_800B0E04, D_80090310, 1, -1, 0, 1, 0, 0);
    D_800BE4F0[1] = func_15195AA8(D_800B0E00, D_80090314, 0, -1, 0, 0, 0, 0);
    D_800BE4F0[2] = func_15195FB0(func_151149AC(0xFA), D_80090310, 1, -1, 0, 0, 0);
    D_800BE4F0[3] = func_15195FB0(func_151149AC(0xF9), D_80090310, 1, -1, 0, 0, 0);
    func_1510F800(0);
    D_800D9A40 = func_1510FD20(0x1500, 0x700);
}
