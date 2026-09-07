#include "types.h"

/*
 * Reviewed source unit: src/game/game_75A90.c
 * Boundary evidence: docs/evidence/game_compact_multi_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150485E0
 * - func_15048664
 * - func_150486B8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_75A90/func_150485E0.s")
s32 func_150485E0(s16, s16);                        /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15048664 CURRENT (1530) */
s32 func_15048664(s16 arg0) {
    s32 temp_v0;
    s16 temp_a1;
    s32 var_a0;

    temp_a1 = arg0;
    {
        s16 var_a0_2 = -temp_a1;
    if (temp_a1 >= 0) {
        var_a0_2 = temp_a1;
    }
    arg0 = temp_a1;
    temp_v0 = func_150485E0(var_a0_2, temp_a1);
    var_a0 = temp_v0;
    if (arg0 < 0) {
        var_a0 = 0xFFFF - temp_v0;
    }
    return var_a0 & 0xFFFF;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15048664 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_75A90/func_15048664.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150486B8 CURRENT (2215) */
s16 func_150486B8(s16 arg0) {
    s32 temp_v0;
    s16 temp_a1;
    s16 var_a0;

    temp_a1 = arg0;
    {
        s16 var_a0_2 = -temp_a1;
    if (temp_a1 >= 0) {
        var_a0_2 = temp_a1;
    }
    arg0 = temp_a1;
    temp_v0 = func_150485E0(var_a0_2, temp_a1);
    var_a0 = temp_v0 - 0x8000;
    if (arg0 >= 0) {
        var_a0 = 0x7FFF - temp_v0;
    }
    return var_a0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150486B8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_75A90/func_150486B8.s")
