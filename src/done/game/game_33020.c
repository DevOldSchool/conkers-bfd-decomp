#include "types.h"

/*
 * Reviewed source unit: src/game/game_33020.c
 * Boundary evidence: docs/evidence/game_32F10_33080.md
 */

void func_1509BFB0(s32, s32, s32);

void func_15005B70(s32 arg0) {
    s32 var_s0;

    func_1509BFB0(0, 0x4014, 0);
    var_s0 = 0;
    do {
        func_1509BFB0(0, var_s0 + 0x400C, 0);
        var_s0 += 1;
    } while (var_s0 != 3);
}
