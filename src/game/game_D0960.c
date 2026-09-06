#include "types.h"

/*
 * Reviewed source unit: src/game/game_D0960.c
 * Boundary evidence: docs/evidence/game_raw_parser_actor_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150A34B0
 * - func_150A3504
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_150A3504();                                /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150A34B0 CURRENT (805) */
s32 func_150A34B0(void *arg0) {
    s32 var_v0;

    if (*(u8 *)((u8 *)arg0 + 0x14) == 1) {
        return 0;
    }
    var_v0 = 0;
    if (!(*(u8 *)((u8 *)arg0 + 0x15) & 3)) {
        var_v0 = func_150A3504();
    }
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150A34B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_D0960/func_150A34B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_D0960/func_150A3504.s")
