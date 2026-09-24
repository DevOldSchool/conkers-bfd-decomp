#include "types.h"

/*
 * Reviewed source unit: src/game/game_197C20.c
 * Boundary evidence: docs/evidence/game_raw_direct_helper_pairs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1516A770
 * - func_1516A7B0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516A770 CURRENT (10) */
s32 func_1516A770(u8 *arg0) {
    s32 var_v1;
    s32 var_v0;

    var_v0 = *arg0;
    var_v1 = 1;
    if (var_v0 != 0) {
        do {
            if (var_v0 == 0xBD) {
                *(u8 *)((u8 *)arg0 + 0) = 0;
                var_v1 += 1;
            }
            var_v0 = *(u8 *)((u8 *)arg0 + 1);
            arg0 += 1;
        } while (var_v0 != 0);
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516A770 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_197C20/func_1516A770.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_197C20/func_1516A7B0.s")
