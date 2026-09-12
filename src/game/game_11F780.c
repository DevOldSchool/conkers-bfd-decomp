#include "types.h"

/*
 * Reviewed source unit: src/game/game_11F780.c
 * Boundary evidence: docs/evidence/game_raw_internal_call_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F22D0
 * - func_150F2390
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_11F780/func_150F22D0.s")
s32 func_150F237C(s32 arg0, s32 arg1) {
    return 0xE;
}

typedef struct {
    u8 pad_0[0x1D4];
    s32 field_1D4;
} Game11F780State;

typedef struct {
    s32 fields[3];
} Game11F780Work;

void func_150F22D0(Game11F780Work *, void *, u8, void *);
void func_151C329C(Game11F780Work *, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F2390 CURRENT (498) */
void func_150F2390(void *arg0, s32 arg1, void *arg2) {
    Game11F780Work sp1C;
    void *temp_a3;

    temp_a3 = arg0;
    if (((Game11F780State *)temp_a3)->field_1D4 != 0) {
        func_150F22D0(&sp1C, temp_a3, arg1, temp_a3);
        func_151C329C(&sp1C, 0xFF, 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F2390 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11F780/func_150F2390.s")
