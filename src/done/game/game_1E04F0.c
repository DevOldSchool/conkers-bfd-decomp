#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E04F0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_preserved_singleton_1b3040.md
 */

typedef struct Game1E04F0State {
    u8 pad0[0x150];
    s32 field_150;
    s32 field_154;
    u8 pad158[0xC];
    s32 field_164;
    s32 field_168;
} Game1E04F0State;

void func_15169850(s32, u8, s32, s32, s32);

void func_151B3040(s32 arg0, s32 arg1, u8 arg2) {
    u8 tmp1;
    s32 first = arg0 + 0x150;
    tmp1 = arg2;

    func_15169850(arg1, tmp1, first, arg0 + 0x154, arg0);
    func_15169850(arg1, arg2, first + 0x14, first + 0x18, arg0);
}
