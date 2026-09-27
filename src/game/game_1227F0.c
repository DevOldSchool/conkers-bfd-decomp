#include "types.h"

/*
 * Reviewed source unit: src/game/game_1227F0.c
 * Boundary evidence: docs/evidence/game_raw_direct_call_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F5340
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1227F0Indices {
    s32 values[17];
} Game1227F0Indices;

void func_1515F170(s32, s32);
void func_151C970C(s32, void *);
extern Game1227F0Indices D_800A1AB0;
extern s32 D_800D3098;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F5340 CURRENT (60) */
void func_150F5340(void) {
    u8 var_s0;
    Game1227F0Indices indices;

    var_s0 = 0;
    indices = D_800A1AB0;
    do {
        func_151C970C(1, (void *)((indices.values[var_s0] * 0x34) + D_800D3098));
        var_s0++;
    } while (var_s0 < 0x11);
    func_1515F170(9, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F5340 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1227F0/func_150F5340.s")
