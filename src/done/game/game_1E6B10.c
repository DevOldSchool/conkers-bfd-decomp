#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E6B10.c
 * Boundary evidence: docs/evidence/game_raw_direct_call_singletons.md
 */

extern f32 D_800AA56C;
extern f32 D_800AA570;

void func_151B9660(void *arg0) {
    *(f32 *)((u8 *)arg0 + 0x188) = 5.0f;
    *(f32 *)((u8 *)arg0 + 0x18C) = D_800AA56C;
    *(f32 *)((u8 *)arg0 + 0x190) = D_800AA570;
}
