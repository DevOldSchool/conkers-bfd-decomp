#include "types.h"

/*
 * Reviewed source unit: src/game/game_F4C20.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_continued.md
 */

s32 func_1509BE40(s32, ...);
void func_1509BFB0(s32, s32, s32, s32);

void func_150C7770(void *arg0) {
    if (func_1509BE40(3, 0x2000, 0xAC, 0x401B, 0x401C, 0x401D) != 0) {
        func_1509BFB0(1, 0x2000, 0x3B, 2);
    }
    if (func_1509BE40(1, 0x4006, 6, 0x2000) != 0) {
        *(s32 *)((u8 *)arg0 + 0x84) |= 0x400000;
    } else {
        *(s32 *)((u8 *)arg0 + 0x84) &= 0xFFBFFFFF;
    }
    *(s32 *)((u8 *)arg0 + 0x84) |= 0x400000;
    if (func_1509BE40(1, 0x4030, 6, 0x2000) != 0) {
        *(s32 *)((u8 *)arg0 + 0x84) |= 0x01000000;
        return;
    }
    *(s32 *)((u8 *)arg0 + 0x84) &= 0xFEFFFFFF;
}
