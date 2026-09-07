#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D6570.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A90C0
 * - func_151A91AC
 * - func_151A931C
 * - func_151A9390
 * - func_151A9634
 * - func_151A9834
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6570/func_151A90C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6570/func_151A91AC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A931C CURRENT (1055) */
void func_151A931C(void *arg0, u8 *arg1, s32 arg2) {
    s32 temp_t6;

    temp_t6 = arg2 & 0xFF;
    if (temp_t6 == 0x17) {
        if (*arg1 == *(u8 *)((u8 *)arg0 + 0x80)) {
            *(u8 *)((u8 *)arg0 + 0x28) = (u8) (*(u8 *)((u8 *)arg0 + 0x28) | 1);
        }
    } else if ((temp_t6 == 0x18) && (*arg1 == *(u8 *)((u8 *)arg0 + 0x80))) {
        *(u8 *)((u8 *)arg0 + 0x28) = (u8) (*(u8 *)((u8 *)arg0 + 0x28) & 0xFFFE);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A931C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6570/func_151A931C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6570/func_151A9390.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6570/func_151A9634.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6570/func_151A9834.s")
