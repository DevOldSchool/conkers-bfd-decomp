#include "types.h"

/*
 * Reviewed source unit: src/game/game_122650.c
 * Boundary evidence: docs/evidence/game_small_multi_function_units.md
 */

extern u8 D_80088B40;

void func_150F51A0(s32 arg0, s32 arg1) {
    D_80088B40 = 1;
}
s32 func_150F51BC(void) {
    if (D_80088B40 != 0) {
        D_80088B40 = 0;
        return 1;
    }
    return 0;
}
void func_10010F30(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_150ADA20(u8 *arg0);

extern u8 D_80088B44;
extern s32 D_800BE9E4;
extern u8 D_800C35EA;
extern s32 D_800CC454;

void func_150F51E8(s32 arg0) {
    s32 state = D_800CC454 & 0x1F;

    if ((state == 3) || (state == 4)) {
        if (D_800BE9E4 < D_80088B44) {
            if (D_800C35EA == 1) {
                return;
            }
            D_80088B44 -= D_800BE9E4;
        } else {
            D_80088B44 = (func_150ADA20(&D_80088B44) & 0x3F) + 0xC0;
            func_10010F30(
                0xF,
                0x4650,
                ((func_150ADA20(&D_80088B44) & 0x3F) + 0x20) & 0xFF,
                0,
                0
            );
        }
    }
}
