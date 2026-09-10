#include "types.h"

/*
 * Reviewed source unit: src/game/game_12D630.c
 * Boundary evidence: docs/evidence/game_raw_selected_particle_resource_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15100180
 * - func_151001B4
 * - func_15100230
 * - func_151002BC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_12D630/func_15100180.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_12D630/func_151001B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_12D630/func_15100230.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151002BC CURRENT (35) */
void func_151002BC(u8 *arg0) {
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v1 = (void *)(*(void **)((u8 *)arg0 + 0x28));
    if ((*(s32 *)((u8 *)temp_v1 + 0) == 0) || (temp_v0 = arg0 + 0x28, (*(u8 *)((u8 *)temp_v1 + 4) == 0xFF)) || (*(u8 *)((u8 *)temp_v0 + 4) != *(u8 *)((u8 *)temp_v1 + 0x3B))) {
        *(s16 *)((u8 *)arg0 + 0xE) = -1;
        return;
    }
    if (*(s32 *)((u8 *)temp_v1 + 0x318) != 0) {
        *(s16 *)((u8 *)temp_v0 + 6) = (s16) (*(s16 *)((u8 *)temp_v0 + 6) - D_800BE9E4);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151002BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12D630/func_151002BC.s")
