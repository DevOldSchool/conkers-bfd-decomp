#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D3420.c
 * Boundary evidence: docs/evidence/game_raw_direct_helper_pairs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A5F70
 * - func_151A6068
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_151A6068(void *, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A5F70 CURRENT (2422) */
void func_151A5F70(void *arg0, void *arg1, u8 arg2) {
    void *sp2C;
    s32 temp_a1;
    s32 var_a0;
    s32 var_v0;
    u8 *var_v1;
    u8 temp_v1;
    void *temp_a0;
    void *temp_v0;

    if (arg2 == 0x35) {
        temp_a1 = *(s32 *)arg1;
        var_v0 = 0;
        var_a0 = 0;
        if (temp_a1 > 0) {
            var_v1 = *(u8 **)((u8 *)arg1 + 4);
loop_3:
            if (*(u8 *)((u8 *)arg0 + 0x2C) == *var_v1) {
                var_a0 = 1;
            } else {
                var_v0 += 1;
                var_v1 += 1;
            }
            if ((var_v0 < temp_a1) && (var_a0 == 0)) {
                goto loop_3;
            }
        }
        if (var_a0 != 0) {
            temp_v0 = (u8 *)arg0 + 0x28;
            temp_a0 = *(void **)temp_v0;
            if (*(u8 *)((u8 *)temp_a0 + 0x14) == 1) {
                temp_v1 = *(u8 *)((u8 *)temp_v0 + 0xC);
                sp2C = temp_v0;
                func_151A6068(temp_a0, *(s32 *)((u8 *)temp_v0 + 8),
                              temp_v1 & 1, temp_v1 & 2,
                              *(u8 *)((u8 *)arg0 + 0xC),
                              *(u8 *)((u8 *)arg0 + 1));
                *(u8 *)((u8 *)*(void **)((u8 *)arg0 + 0x28) + 0x14) = 0;
                *(s32 *)((u8 *)temp_v0 + 0x10) = *(s32 *)((u8 *)arg1 + 8);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A5F70 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D3420/func_151A5F70.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D3420/func_151A6068.s")
