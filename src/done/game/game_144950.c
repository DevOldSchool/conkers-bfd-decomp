#include "types.h"

/*
 * Reviewed source unit: src/game/game_144950.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 */

f32 func_151172D8(void *arg0, f32 arg1);            /* extern */

void func_151174A0(void *arg0) {
    *(f32 *)((u8 *)arg0 + 8) = func_151172D8(arg0, *(f32 *)((u8 *)arg0 + 8));
}
void func_151174C8(u8 *arg0) {
    *(f32 *)(arg0 + 4) = func_151172D8(arg0, *(f32 *)(arg0 + 4));
}
