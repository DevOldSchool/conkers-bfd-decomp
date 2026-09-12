#include "types.h"

/*
 * Reviewed source unit: src/game/game_130200.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_final.md
 */

extern void func_15169850(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_15102D50(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, (s32) arg2, arg0 + 0x110, arg0 + 0x114, arg0);
}
