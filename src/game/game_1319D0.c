#include "types.h"

/*
 * Reviewed source unit: src/game/game_1319D0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_final.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15104520
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15128774(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15104520 CURRENT (15) */
void func_15104520(void *arg0) {
    f32 temp_fv0;
    u8 *temp_a1;

    if ((*(s32 *)((u8 *)arg0 + 0x6FC) != 0) || (*(s32 *)((u8 *)arg0 + 0x6C8) == 0)) {
        *(f32 *)((u8 *)arg0 + 0x348) = 117.0f;
        *(f32 *)((u8 *)arg0 + 0x34C) = 117.0f;
        *(f32 *)((u8 *)arg0 + 0x374) = 370.0f;
        *(f32 *)((u8 *)arg0 + 0x190) = 77.0f;
    }
    temp_a1 = *(u8 **)((u8 *)arg0 + 0x3D0);
    if ((*(f32 *)(temp_a1 + 0x3C) < 50.0f) && (*(u8 *)((u8 *)arg0 + 0x3E8) == 0)) {
        temp_fv0 = *(f32 *)((u8 *)arg0 + 0x374);
        if ((0.5f * temp_fv0) < (*(f32 *)((u8 *)arg0 + 0x370) - temp_fv0)) {
            func_15128774(arg0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15104520 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1319D0/func_15104520.s")
