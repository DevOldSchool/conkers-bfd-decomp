#include "types.h"

/*
 * Reviewed source unit: src/game/game_1286F0.c
 * Boundary evidence: docs/evidence/game_raw_direct_helper_pairs.md
 */

void func_150FB240(u8 *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    if ((arg2 - arg3) < arg1) {
        *arg0 = (arg2 - arg1) * arg4;
        return;
    }
    *arg0 = 0xFF;
}
s32 func_150FB29C(u8 *arg0) {
    func_150FB240(arg0 + 0x43, *(s16 *)((u8 *)arg0 + 0x16), *(s16 *)((u8 *)arg0 + 0x120), *(s16 *)((u8 *)arg0 + 0x64), (s16) (s32) *(s16 *)((u8 *)arg0 + 0x66));
    return 1;
}
