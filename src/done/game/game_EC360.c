#include "types.h"

/*
 * Reviewed source unit: src/game/game_EC360.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_singletons_final.md
 */

s32 func_1509BE40(s32, s32, s32, s32);

void func_150BEEB0(void *arg0) {
    if (func_1509BE40(1, 0x4063, 6, 0x2000) != 0 ||
        func_1509BE40(1, 0x4001, 6, 0x9000) != 0) {
        *(s32 *)((u8 *)arg0 + 0x84) |= 0x1010;
    } else {
        *(s32 *)((u8 *)arg0 + 0x84) &= ~0x1010;
    }
    if (func_1509BE40(1, 0x4069, 6, 0x2000) != 0) {
        *(s32 *)((u8 *)arg0 + 0x84) |= 0x01000000;
    } else {
        *(s32 *)((u8 *)arg0 + 0x84) &= 0xFEFFFFFF;
    }
}
