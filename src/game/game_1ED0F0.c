#include "types.h"

/*
 * Reviewed source unit: src/game/game_1ED0F0.c
 * Boundary evidence: docs/evidence/game_raw_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151BFC40
 * - func_151BFDA0
 * - func_151BFE84
 * - func_151C0098
 * - func_151C02E4
 * - func_151C0360
 * - func_151C0418
 * - func_151C04F8
 * - func_151C05A4
 * - func_151C05F0
 * - func_151C0644
 * - func_151C0698
 * - func_151C110C
 * - func_151C1180
 * - func_151C1570
 * - func_151C1628
 * - func_151C1654
 * - func_151C1798
 * - func_151C1814
 * - func_151C1860
 * - func_151C1940
 * - func_151C196C
 * - func_151C1D5C
 * - func_151C1FB8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151BFC40.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151BFDA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151BFE84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C0098.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C02E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C0360.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C0418.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C04F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C05A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C05F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C0644.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C0698.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C110C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C1180.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C1570.s")
void func_151C15FC(s32 arg0) {
    func_151C1570(arg0);
    func_15132570(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C1628.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C1654.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C1798.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C1814 CURRENT (215) */
void func_151C1814(s32 arg0, void *arg1, s32 arg2) {
    s32 temp_a2;
    s32 temp_v1;
    void *temp_v0;

    temp_v0 = arg0 + 0x170;
    if ((arg2 & 0xFF) == 0x2D) {
        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        temp_a2 = *(s32 *)((u8 *)temp_v0 + 0x6C);
        if (temp_v1 == temp_a2) {
            *(s32 *)((u8 *)temp_v0 + 0x6C) = (s32) *(s32 *)((u8 *)arg1 + 4);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_a2) {
            *(s32 *)((u8 *)temp_v0 + 0x6C) = temp_v1;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C1814 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C1814.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C1860.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C1940.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C196C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C1D5C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C1FB8.s")
