#include "types.h"

/*
 * Reviewed source unit: src/game/game_322B0.c
 * Boundary evidence: docs/evidence/game_small_multi_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15004E00
 * - func_15004E80
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_322B0/func_15004E00.s")
/* Call context: func_10003C40: unique active project prototype */
void * func_10003C40(s32, s32, s32, s32);
extern void *D_800B0DF0;
extern u16 D_800C3E7C;
extern void *D_800C3E80;
extern void *D_800C3E84;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15004E80 CURRENT (555) */
void func_15004E80(void) {
    u16 temp_t7;

    temp_t7 = *(u16 *)((u8 *)D_800B0DF0 + 0x1A);
    D_800C3E7C = temp_t7;
    D_800C3E80 = func_10003C40((temp_t7 & 0xFFFF) << 6, 1, 3, 0);
    D_800C3E84 = func_10003C40(D_800C3E7C << 6, 1, 3, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15004E80 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_322B0/func_15004E80.s")
