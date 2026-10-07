#include "types.h"

/*
 * Reviewed source unit: src/game/game_1DC980.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_direct_call_singletons.md
 */

void func_15143134(f32 *, f32 *, s32);
f32 func_150ADA68(void);
void func_15135DD0(f32 *, f32 *, f32, u8, s32);
extern u8 D_800A9DF0[];
extern f32 D_800AA0E4;

void func_151AF4D0(void *arg0, u8 arg1, u8 arg2, s32 arg3) {
    f32 sp44[3];
    f32 sp38[3];
    s32 temp_a2;
    u8 *temp_v1;
    u8 *temp_v0;

    if (arg0 != 0) {
        temp_v1 = *(u8 **)((u8 *)arg0 + 0x1D4);
        if ((temp_v1 != 0) && ((*(u8 *)((u8 *)arg0 + 0x74) & 0xF) != 0xF)) {
            temp_v0 = (arg1 * 0x1C) + D_800A9DF0;
            temp_a2 = (s32)((u8 (*)[0x40])temp_v1)[*temp_v0];
            func_15143134((f32 *)(temp_v0 + 4), sp44, temp_a2);
            func_15143134((f32 *)(temp_v0 + 0x10), sp38, temp_a2);
            func_15135DD0(sp44, sp38,
                          ((func_150ADA68() * 170.0f) + 71.0f) * D_800AA0E4,
                          arg2, arg3);
        }
    }
}
