#include "types.h"

/*
 * Reviewed source unit: src/game/game_808E0.c
 * Boundary evidence: docs/evidence/game_raw_internal_call_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15053430
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_808E0/func_15053430.s")
/* Call context: func_15060F28: unique active project prototype */
void func_15060F28(u8 *, s32);
s32 func_15053430();
extern u8 *D_800D1C90[];

s32 func_150535F4(u8 *arg0) {
    u8 temp_v0;
    u8 temp_v1;

    if (*(u8 *)(arg0 + 0x1CA) == 0) {
        temp_v1 = *(u8 *)(arg0 + 4);
        if (temp_v1 == 0xFF) {
            func_15060F28(arg0, 1);
            return 1;
        }
        temp_v0 = D_800D1C90[temp_v1][0x28];
        if ((temp_v0 & 0x10) ||
            ((temp_v0 & 8) && (*(f32 *)(arg0 + 0x28) == 0.0f)) ||
            (*(u8 *)(arg0 + 0x10F) == 0)) {
            return func_15053430();
        }
        goto block_8;
    }
block_8:
    return 0;
}
/* Call context: func_1506160C: unique active project prototype */
void func_1506160C(u8 *, s32, s32, s32, u8);

void func_15053694(u8 *arg0) {
    *(s32 *)(arg0 + 0) = 8;
    *(s16 *)(arg0 + 0xE4) = 0;
    *(s16 *)(arg0 + 0xE6) = 0;
    func_1506160C(arg0, 6, 0, 0, 0U);
}
