#include "types.h"

/*
 * Reviewed source unit: src/game/game_E4070.c
 * Boundary evidence: docs/evidence/game_raw_connected_controller_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B6BC0
 * - func_150B6C90
 * - func_150B6D34
 * - func_150B6D78
 * - func_150B6E3C
 * - func_150B709C
 * - func_150B71A8
 * - func_150B7220
 * - func_150B73F0
 * - func_150B7484
 * - func_150B7560
 * - func_150B765C
 * - func_150B768C
 * - func_150B76BC
 * - func_150B77A8
 * - func_150B791C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B6BC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B6C90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B6D34.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B6D78.s")
extern s32 D_800BE9E4;

void func_150B6DFC(void *arg0) {
    *(s16 *)((u8 *)arg0 + 0x34) = (s16) (*(s16 *)((u8 *)arg0 + 0x34) + (D_800BE9E4 * 0x30));
    if (*(s16 *)((u8 *)arg0 + 0x34) >= 0x801) {
        *(s16 *)((u8 *)arg0 + 0x34) = -0xC00;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B6E3C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B709C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B71A8 CURRENT (10) */
void func_150B71A8(void *arg0) {
    s16 temp_v0;
    s16 temp_v0_2;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x38);
    if (temp_v0 != 0x1000) {
        *(s16 *)((u8 *)arg0 + 0x38) = (s16) (temp_v0 + (D_800BE9E4 << 8));
        if (*(s16 *)((u8 *)arg0 + 0x38) >= 0x1001) {
            *(s16 *)((u8 *)arg0 + 0x38) = 0x1000;
        }
    } else {
        temp_v0_2 = *(s16 *)((u8 *)arg0 + 0x3A);
        if (temp_v0_2 != 0x1000) {
            *(s16 *)((u8 *)arg0 + 0x3A) = (s16) (temp_v0_2 + (D_800BE9E4 << 8));
            if (*(s16 *)((u8 *)arg0 + 0x3A) >= 0x1001) {
                *(s16 *)((u8 *)arg0 + 0x3A) = 0x1000;
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B71A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B71A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B7220.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B73F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B7484.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B7560.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B765C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B768C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B76BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B77A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B791C.s")
