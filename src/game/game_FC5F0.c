#include "types.h"

/*
 * Reviewed source unit: src/game/game_FC5F0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150CF140
 * - func_150CF484
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_FC5F0/func_150CF140.s")
void func_1516972C(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CF484 CURRENT (1010) */
void func_150CF484(void *arg0, void *arg1, u8 arg2) {
    s32 temp_a0;
    s32 temp_t6;
    s32 temp_v1;
    void *temp_a3;
    u8 *temp_v0;

    temp_a3 = arg0;
    temp_t6 = arg2 & 0xFF;
    if (temp_t6 == 0) {
        if ((*(s32 *)((u8 *)arg1 + 0) == *(s32 *)((u8 *)temp_a3 + 0x28)) ||
            (*(u8 *)((u8 *)temp_a3 + 0x2C) == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C(temp_a3);
        }
    } else {
        temp_v0 = (u8 *)temp_a3 + 0x28;
        if (temp_t6 == 0x2D) {
            temp_a0 = *(s32 *)temp_v0;
            temp_v1 = *(s32 *)arg1;
            if (temp_v1 == temp_a0) {
                *(s32 *)temp_v0 = *(s32 *)((u8 *)arg1 + 4);
                *(u8 *)(temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 9);
                return;
            }
            if (*(s32 *)((u8 *)arg1 + 4) == temp_a0) {
                *(s32 *)temp_v0 = temp_v1;
                *(u8 *)(temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 8);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CF484 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FC5F0/func_150CF484.s")
