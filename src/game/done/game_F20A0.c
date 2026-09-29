#include "types.h"

/*
 * Reviewed source unit: src/game/game_F20A0.c
 * Boundary evidence: docs/evidence/game_medium_single_function_units.md
 */

s32 func_1509BE40(s32, ...);
void func_1509BFB0(s32, s32, s32, s32);

void func_150C4BF0(void *arg0) {
    if (func_1509BE40(1, 0x403F, 6, 0x2000) != 0) {
        *(s32 *)((u8 *)arg0 + 0x84) |= 0x01000000;
    } else {
        *(s32 *)((u8 *)arg0 + 0x84) &= 0xFEFFFFFF;
    }
    if (func_1509BE40(1, 0x4019, 6, 0x2000) != 0) {
        func_1509BFB0(1, 0x9000, 0x10, 0xA0);
        return;
    }
    if (func_1509BE40(1, 0x4044, 6, 0x2000) != 0) {
        func_1509BFB0(1, 0x9000, 0x10, 0);
        return;
    }
    if (func_1509BE40(4, 0x2000, 0xAC, 0x401B, 0x401C, 0x401D, 0x401E) != 0) {
        func_1509BFB0(1, 0x9000, 0x10, -0x96);
        return;
    }
    func_1509BFB0(1, 0x9000, 0x10, 0);
}
