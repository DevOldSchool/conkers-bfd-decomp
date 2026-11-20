#include "types.h"

/*
 * Reviewed source unit: src/game/game_433F0.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_next_compact_units.md
 */

extern u8 D_800BE616;
extern s32 D_800BE9E8;
s8 func_151E5FAC(void);

void func_15015F40(s16 arg0, s32 arg1) {
    switch (arg1) {
        case 0x1A:
        case 0x24:
        case 0x2B:
        case 0x2D:
        case 0x30:
        case 0x33:
        case 0x34:
        case 0x3F:
            D_800BE616 = 1;
            D_800BE9E8 = func_151E5FAC() - 1;
            break;
        default:
            D_800BE616 = 0;
            D_800BE9E8 = arg0 - 1;
            break;
    }
}

extern s32 D_800BE638[5];
extern s32 D_800BE650[5];
extern s16 D_800BE668[10][4];

void func_15015FBC(s32 arg0, s32 arg1) {
    s32 i;
    s32 halfA;
    s32 halfB;
    s32 quarterA;
    s32 quarterB;
    s32 tripleA;
    s32 tripleB;

    for (i = 0; i < 5; i++) {
        D_800BE638[i] = arg0;
        D_800BE650[i] = arg1;
        if (i < 4) {
            if (i >= 2) {
                D_800BE638[i] >>= 1;
            }
            if (i >= 1) {
                D_800BE650[i] >>= 1;
            }
        }
    }
    halfA = arg0 >> 1;
    quarterA = arg0 >> 2;
    halfB = arg1 >> 1;
    quarterB = arg1 >> 2;
    tripleB = quarterB * 3;
    tripleA = quarterA * 3;
    D_800BE668[0][0] = halfA;
    D_800BE668[0][1] = halfB;
    D_800BE668[0][2] = halfA;
    D_800BE668[0][3] = halfB;
    D_800BE668[1][0] = halfA;
    D_800BE668[1][1] = halfB;
    D_800BE668[1][2] = halfA;
    D_800BE668[1][3] = halfB;
    D_800BE668[2][0] = halfA;
    D_800BE668[2][1] = halfB;
    D_800BE668[2][2] = halfA;
    D_800BE668[2][3] = quarterB;
    D_800BE668[3][0] = halfA;
    D_800BE668[3][1] = tripleB;
    D_800BE668[3][2] = halfA;
    D_800BE668[3][3] = halfB;
    D_800BE668[4][0] = 0;
    D_800BE668[4][1] = 0;
    D_800BE668[4][2] = 0;
    D_800BE668[4][3] = 0;
    D_800BE668[5][0] = quarterA;
    D_800BE668[5][1] = quarterB;
    D_800BE668[5][2] = tripleA;
    D_800BE668[5][3] = quarterB;
    D_800BE668[6][0] = halfA;
    D_800BE668[6][1] = tripleB;
    D_800BE668[6][2] = halfA;
    D_800BE668[6][3] = halfB;
    D_800BE668[7][0] = 0;
    D_800BE668[7][1] = 0;
    D_800BE668[7][2] = quarterA;
    D_800BE668[7][3] = quarterB;
    D_800BE668[8][0] = tripleA;
    D_800BE668[8][1] = quarterB;
    D_800BE668[8][2] = quarterA;
    D_800BE668[8][3] = tripleB;
    D_800BE668[9][0] = tripleA;
    D_800BE668[9][1] = tripleB;
    D_800BE668[9][2] = halfA;
    D_800BE668[9][3] = halfB;
}
