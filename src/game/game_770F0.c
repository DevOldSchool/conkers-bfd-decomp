#include "types.h"

/*
 * Reviewed source unit: src/game/game_770F0.c
 * Boundary evidence: docs/evidence/game_raw_preserved_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15049C40
 * - func_15049CB8
 * - func_15049EDC
 * - func_1504A140
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15049C40 CURRENT (190) */
void func_15049C40(void *arg0, void *arg1) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_fv1;

    temp_fa0 = *(f32 *)((u8 *)arg1 + 0);
    temp_fa1 = *(f32 *)((u8 *)arg1 + 4);
    temp_ft4 = *(f32 *)((u8 *)arg1 + 8);
    temp_fv1 = *(f32 *)((u8 *)arg1 + 0xC);
    if (((temp_fv1 * *(f32 *)((u8 *)arg0 + 0xC)) + ((*(f32 *)((u8 *)arg0 + 0) * temp_fa0) + (*(f32 *)((u8 *)arg0 + 4) * temp_fa1) + (*(f32 *)((u8 *)arg0 + 8) * temp_ft4))) < 0.0f) {
        *(f32 *)((u8 *)arg1 + 0) = (f32) -temp_fa0;
        *(f32 *)((u8 *)arg1 + 4) = (f32) -temp_fa1;
        *(f32 *)((u8 *)arg1 + 8) = (f32) -temp_ft4;
        *(f32 *)((u8 *)arg1 + 0xC) = (f32) -temp_fv1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15049C40 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_770F0/func_15049C40.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_770F0/func_15049CB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_770F0/func_15049EDC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_770F0/func_1504A140.s")
