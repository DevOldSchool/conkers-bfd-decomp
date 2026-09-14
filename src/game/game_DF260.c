#include "types.h"

/*
 * Reviewed source unit: src/game/game_DF260.c
 * Boundary evidence: docs/evidence/game_raw_direct_call_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B1DB0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern u64 D_8009F8D0;
extern u64 D_8009F8D8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B1DB0 CURRENT (5700) */
void func_150B1DB0(u64 *arg0, u64 *arg1) {
    u64 *uncached;
    u64 value_0;
    u64 value_1;
    u64 masked_0;
    u64 masked_1;

    uncached = (u64 *)((u32)arg0 | 0xA0000000);
    do {
        value_0 = arg0[0];
        value_1 = arg0[1];
        masked_0 = value_0 & D_8009F8D0;
        arg0[0] = (masked_0 >> 5) |
                  ((value_0 & D_8009F8D8) | (masked_0 << 5));
        masked_1 = value_1 & D_8009F8D0;
        arg0[1] = (masked_1 >> 5) |
                  ((value_1 & D_8009F8D8) | (masked_1 << 5));
        arg0 += 2;
        uncached += 2;
    } while (arg0 < arg1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B1DB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DF260/func_150B1DB0.s")
