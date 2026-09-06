#include "types.h"

/*
 * Reviewed source unit: src/game/game_177480.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15149FD0
 * - func_1514A19C
 * - func_1514A380
 * - func_1514A498
 * - func_1514A4EC
 * - func_1514A594
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_177480/func_15149FD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_177480/func_1514A19C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_177480/func_1514A380.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514A498 CURRENT (10) */
s32 func_1514A498(void *arg0) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_v0;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x30);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x144);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x2C);
    temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (temp_fv0 - (temp_fv0 * temp_fv1));
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (temp_fa0 - (temp_fa0 * temp_fv1));
    if (temp_v0 < *(s16 *)((u8 *)arg0 + 0x156)) {
        *(s8 *)((u8 *)arg0 + 0x5C) = (s8) (temp_v0 * *(s16 *)((u8 *)arg0 + 0x158));
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514A498 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_177480/func_1514A498.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_177480/func_1514A4EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_177480/func_1514A594.s")
