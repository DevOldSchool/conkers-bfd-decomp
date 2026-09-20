#include "types.h"

/*
 * Reviewed source unit: src/game/game_1DC980.c
 * Boundary evidence: docs/evidence/game_raw_direct_call_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151AF4D0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15143134(f32 *, f32 *, s32);
f32 func_150ADA68(void);
void func_15135DD0(f32 *, f32 *, f32, u8, s32);
extern u8 D_800A9DF0[];
extern f32 D_800AA0E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AF4D0 CURRENT (20) */
void func_151AF4D0(void *arg0, u8 arg1, u8 arg2, s32 arg3) {
    f32 sp44[3];
    f32 sp38;
    s32 sp34;
    u8 *sp24;
    s32 temp_a2;
    s32 temp_v1;
    u8 *temp_v0;

    if (arg0 != 0) {
        temp_v1 = *(s32 *)((u8 *)arg0 + 0x1D4);
        if ((temp_v1 != 0) && ((*(u8 *)((u8 *)arg0 + 0x74) & 0xF) != 0xF)) {
            temp_v0 = (arg1 * 0x1C) + D_800A9DF0;
            sp24 = temp_v0;
            temp_a2 = (*temp_v0 << 6) + temp_v1;
            sp34 = temp_a2;
            func_15143134((f32 *)(temp_v0 + 4), sp44, temp_a2);
            func_15143134((f32 *)(sp24 + 0x10), &sp38, sp34);
            func_15135DD0(sp44, &sp38,
                          ((func_150ADA68() * 170.0f) + 71.0f) * D_800AA0E4,
                          arg2, arg3);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AF4D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DC980/func_151AF4D0.s")
