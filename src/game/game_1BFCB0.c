#include "types.h"

/*
 * Reviewed source unit: src/game/game_1BFCB0.c
 * Boundary evidence: docs/evidence/game_raw_parser_actor_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15192800
 * - func_151928B0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1BFCB0Record {
    u8 pad0[4];
    u8 field_4;
} Game1BFCB0Record;

#pragma GLOBAL_ASM("asm/nonmatchings/game_1BFCB0/func_15192800.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151928B0 CURRENT (405) */
s32 func_151928B0(Game1BFCB0Record *arg0, s32 *arg1) {
    s32 result = 0;

    switch (arg0->field_4) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            result = 1;
            *arg1 = 0;
            goto done;
        case 0x53:
            result = 1;
            *arg1 = 1;
            goto done;
        default:
            break;
    }
done:
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151928B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BFCB0/func_151928B0.s")
