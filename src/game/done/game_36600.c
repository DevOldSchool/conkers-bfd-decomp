#include "types.h"

/*
 * Reviewed source unit: src/game/game_36600.c
 * Boundary evidence: docs/evidence/game_remaining_single_function_units_up_to_256_bytes.md
 */

typedef struct Game36600State {
    u8 pad0[0x10];
    u8 index;
} Game36600State;

typedef struct Game36600Result {
    u8 pad0[0x2E];
    s8 field_2E;
} Game36600Result;

Game36600Result *func_1517E080(s32, s32);
extern s32 D_8008CFFC[];
extern Game36600State *D_800B0DF0;
extern u8 D_800DCDD0;
extern s8 D_800DD2D0;
extern s8 D_800DDD61;
extern s32 D_800DDD64;

void func_15009150(s32 arg0) {
    D_800DDD64 = 0;
    D_800DDD61 = 0;
    D_800DD2D0 = 0;
    if ((D_800DCDD0 != 0) && (D_8008CFFC[D_800B0DF0->index] != 0)) {
        func_1517E080(0, 0xFF)->field_2E = 3;
    }
}
