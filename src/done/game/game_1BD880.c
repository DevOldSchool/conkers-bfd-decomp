#include "types.h"

/*
 * Reviewed source unit: src/game/game_1BD880.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_final.md
 */

void func_15163DEC(s32 arg0, s32 arg1);
void func_15163F50(s32 arg0, s32 arg1);

void func_151903D0(s32 arg0) {
    func_15163DEC(arg0, arg0 + 0x20);
    func_15163F50(arg0, arg0 + 0x18);
}
