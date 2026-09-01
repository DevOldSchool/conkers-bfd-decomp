#include "types.h"

/*
 * Reviewed source unit: src/game/game_36040.c
 * Boundary evidence: docs/evidence/game_small_multi_function_units.md
 */

void func_15008BB0(void);
s32 func_1518AADC(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_800D98E0;

void func_15008B90(void) {
    func_15008BB0();
}

void func_15008BB0(void) {
    D_800D98E0 = func_1518AADC(0xC, 0x3E8, 1);
}

void func_15008BE0(void) {
}
