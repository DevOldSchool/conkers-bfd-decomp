#include "types.h"

/*
 * Reviewed source unit: src/game/game_433F0.c
 * Boundary evidence: docs/evidence/game_next_compact_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15015FBC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
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

extern s32 D_800BE638;
extern s32 D_800BE63C;
extern s32 D_800BE650;
extern s32 D_800BE654;
extern s32 D_800BE658;
extern s32 D_800BE65C;
extern s32 D_800BE660;
extern s32 D_800BE664;
extern s16 D_800BE668;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15015FBC CURRENT (15495) */
void func_15015FBC(s32 arg0, s32 arg1) {
    s32 *left;
    s32 *right;
    s16 *output;
    s32 quarterA;
    s32 quarterB;
    s32 halfA;
    s32 halfB;
    s16 tripleA;
    s16 tripleB;

    D_800BE638 = arg0;
    left = &D_800BE63C;
    right = &D_800BE654;
    D_800BE650 = arg1;
    do {
        left[0] = arg0;
        right[0] = arg1;
        if ((u32)right < (u32)&D_800BE660) {
            if ((u32)right >= (u32)&D_800BE658) {
                left[0] = arg0 >> 1;
            }
            if ((u32)right >= (u32)&D_800BE654) {
                right[0] >>= 1;
            }
        }
        left[1] = arg0;
        right[1] = arg1;
        if ((u32)right < (u32)&D_800BE65C) {
            if ((u32)right >= (u32)&D_800BE654) {
                left[1] = arg0 >> 1;
            }
            if ((u32)right >= (u32)&D_800BE650) {
                right[1] >>= 1;
            }
        }
        right += 2;
        left += 2;
    } while (right != &D_800BE664);
    output = &D_800BE668;
    quarterB = arg1 >> 2;
    tripleB = (u32)quarterB * 3U;
    quarterA = arg0 >> 2;
    halfA = arg0 >> 1;
    halfB = arg1 >> 1;
    output[0] = halfA;
    output[1] = halfB;
    output[2] = halfA;
    output[3] = halfB;
    output[4] = halfA;
    output[5] = halfB;
    output[6] = halfA;
    output[7] = halfB;
    tripleA = (u32)quarterA * 3U;
    output[8] = halfA;
    output[9] = halfB;
    output[10] = halfA;
    output[11] = quarterB;
    output[12] = halfA;
    output[13] = tripleB;
    output[14] = halfA;
    output[15] = halfB;
    output[16] = 0;
    output[17] = 0;
    output[18] = 0;
    output[19] = 0;
    output[20] = quarterA;
    output[21] = quarterB;
    output[22] = tripleA;
    output[23] = quarterB;
    output[24] = halfA;
    output[25] = tripleB;
    output[26] = halfA;
    output[27] = halfB;
    output[28] = 0;
    output[29] = 0;
    output[30] = quarterA;
    output[31] = quarterB;
    output[32] = tripleA;
    output[33] = quarterB;
    output[34] = quarterA;
    output[35] = tripleB;
    output[36] = tripleA;
    output[37] = tripleB;
    output[38] = halfA;
    output[39] = halfB;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15015FBC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_433F0/func_15015FBC.s")
