#include "types.h"

/*
 * Reviewed source unit: src/game/game_135D00.c
 * Boundary evidence: docs/evidence/game_raw_sorted_record_object_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15108850
 * - func_15108AB4
 * - func_15108B80
 * - func_15108BC0
 * - func_15108C38
 * - func_15108D24
 * - func_15108E10
 * - func_15108FFC
 * - func_15109064
 * - func_151090DC
 * - func_15109120
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_135D00/func_15108850.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_135D00/func_15108AB4.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15108B80 CURRENT (60) */
void func_15108B80(u8 *arg0) {
    s32 temp_t0;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_v0 = (void *)(arg0 + *(s32 *)((u8 *)arg0 + 0x50));
    temp_v0_2 = (void *)(temp_v0 + 0xF8);
    if (*(s32 *)((u8 *)temp_v0 + 0x10C) != 0x3E7) {
        temp_t0 = *(s32 *)((u8 *)temp_v0_2 + 0x1C) - D_800BE9E4;
        *(s32 *)((u8 *)temp_v0_2 + 0x1C) = temp_t0;
        if (temp_t0 < 0) {
            *(s32 *)((u8 *)temp_v0_2 + 0x14) = 0x3E7;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15108B80 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_135D00/func_15108B80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_135D00/func_15108BC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_135D00/func_15108C38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_135D00/func_15108D24.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_135D00/func_15108E10.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_135D00/func_15108FFC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_135D00/func_15109064.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_135D00/func_151090DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_135D00/func_15109120.s")
