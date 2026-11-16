#include "types.h"

/*
 * Reviewed source unit: src/game/game_2DDF0.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_medium_single_function_units.md
 */

extern u8 D_800A2CD0[][3];
extern u8 D_800A2CE8[][3];
extern u8 D_800A2CEC[][3];
extern u8 D_800A2D04[][3];
extern u8 *D_800B0DF0;
extern s16 D_800D9E70[4][3];
extern u8 D_800D9E88[4][3];
extern u8 D_800D9E98[4][3];
extern u8 D_800D9EA8[4][3];
extern u8 D_800D9EB4[3];
extern u8 D_800D9EB8[4][3];

void func_15000940(s32 arg0) {
    s32 i;
    s32 j;
    s32 idx;

    idx = D_800B0DF0[0x29];
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            D_800D9E70[i][j] = 0;
            D_800D9E88[i][j] = D_800A2CE8[D_800A2CD0[idx][0]][j];
            D_800D9E98[i][j] = D_800A2CEC[D_800A2CD0[idx][1]][j];
            D_800D9EB4[j] = D_800A2D04[D_800A2CD0[idx][2]][j];
            D_800D9EA8[i][j] = D_800D9EB4[j];
            D_800D9EB8[i][j] = 0;
        }
    }
}
