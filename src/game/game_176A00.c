#include "types.h"

/*
 * Reviewed source unit: src/game/game_176A00.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15149550
 * - func_15149838
 * - func_15149A94
 * - func_15149BF4
 * - func_15149C58
 * - func_15149D18
 * - func_15149EC4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_176A00/func_15149550.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_176A00/func_15149838.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_176A00/func_15149A94.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15149BF4 CURRENT (350) */
s32 func_15149BF4(void *arg0) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x2C);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x150);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x30);
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (temp_fv0 - (temp_fv0 * temp_fv1));
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (temp_fa0 - (temp_fa0 * temp_fv1));
    if ((*(f32 *)((u8 *)arg0 + 0x2C) < 2.0f) || (*(f32 *)((u8 *)arg0 + 0x30) < 2.0f)) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15149BF4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_176A00/func_15149BF4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_176A00/func_15149C58.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_176A00/func_15149D18.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_176A00/func_15149EC4.s")
