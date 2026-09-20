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

#pragma GLOBAL_ASM("asm/nonmatchings/game_433F0/func_15015FBC.s")
