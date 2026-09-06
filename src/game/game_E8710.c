#include "types.h"

/*
 * Reviewed source unit: src/game/game_E8710.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150BB260
 * - func_150BB408
 * - func_150BB450
 * - func_150BB498
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_E8710/func_150BB260.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E8710/func_150BB408.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150BB450 CURRENT (10) */
s32 func_150BB450(void *arg0) {
    s16 temp_lo;
    s16 temp_v0;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    if (temp_v0 < *(s16 *)((u8 *)arg0 + 0xB0)) {
        temp_lo = temp_v0 * *(s16 *)((u8 *)arg0 + 0xB2);
        if (temp_lo < (s32) *(u8 *)((u8 *)arg0 + 0x28)) {
            *(u8 *)((u8 *)arg0 + 0x28) = (u8) temp_lo;
        }
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150BB450 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E8710/func_150BB450.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E8710/func_150BB498.s")
