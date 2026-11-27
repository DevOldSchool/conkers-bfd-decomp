#include "types.h"
#include "globals.h"

/*
 * Reviewed source unit: src/game/game_39690.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_remaining_single_function_units_up_to_256_bytes.md
 */

void func_100226F0(void *, s32);
extern u8 D_800DDE80;
extern s8 D_800DDF68[];

void func_1500C1E0(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        D_800DDF5C[i] = D_800DDF60[i] = 0;
    }
    for (i = 0; i < 11; i++) {
        D_800DDF68[i] = -2;
    }
    func_100226F0(&D_800DDE80, 0xDC);
    for (i = 0; i < 11; i++) {
        D_800DDF78[i] = 0;
    }
}
