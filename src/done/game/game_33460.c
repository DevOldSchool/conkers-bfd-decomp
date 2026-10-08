#include "types.h"

/*
 * Reviewed source unit: src/game/game_33460.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_330E0_33460.md
 */

void func_15124B18(void *arg0);

void func_15005FB0(void *arg0) {
    *(s32 *)((u8 *)arg0 + 0x2C) = 8;
    *(s32 *)((u8 *)arg0 + 0x84) |= 0x300000;
    *(s32 *)((u8 *)arg0 + 0x84) &= ~4;
    *(s16 *)((u8 *)arg0 + 0x1B4) = 1;
    *(s16 *)((u8 *)arg0 + 0x1E0) = 3;
    func_15124B18(arg0);
    *(s32 *)((u8 *)arg0 + 0x134) = 0;
}
