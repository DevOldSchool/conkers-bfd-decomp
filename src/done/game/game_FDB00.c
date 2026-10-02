#include "types.h"

/*
 * Reviewed source unit: src/game/game_FDB00.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_final.md
 */

s32 func_1509BE40(s32, s32, s32);
s32 func_15123934(void *, s32, s32, s32, s32);
s32 func_151239CC(void *, s32);
void func_151254F4(void *, s32);
extern u8 D_800CC335;
extern u8 *D_800D2E4C;

void func_150D0650(u8 *arg0) {
    if (!(*D_800D2E4C & 0x80)) {
        if (func_1509BE40(0, 0x2000, 0xBB) != -1) {
            if (func_15123934(arg0, *(s32 *)(arg0 + 0x2C), 0,
                               *(s32 *)(arg0 + 0x134), 8) != 0) {
                *(s32 *)(arg0 + 0x84) |= 0x01000000;
                func_151254F4(arg0, D_800CC335 - 1);
                *(f32 *)(arg0 + 0x190) = 100.0f;
            }
        } else if (func_151239CC(arg0, 8) != 0) {
            func_151254F4(arg0, 0);
            *(f32 *)(arg0 + 0x190) = 0.0f;
        }
    }
}
