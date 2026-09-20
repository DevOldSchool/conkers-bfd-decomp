#include "types.h"

/*
 * Reviewed source unit: src/game/game_6E770.c
 * Boundary evidence: docs/evidence/game_raw_call_connected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150412C0
 * - func_150413FC
 * - func_15041480
 * - func_15041508
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_6E770/func_150412C0.s")
u8 *func_15041508(u8 *, s32, s32, s32);
s32 func_15041480(u8);
extern u8 D_800848D0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150413FC CURRENT (878) */
u8 *func_150413FC(u8 *arg0, s32 arg1, s32 arg2, u8 *arg3) {
    s32 var_s1;
    u8 *temp_v0;
    u8 *var_s0;
    u8 *var_s2;
    u8 temp_t6;

    var_s2 = arg0;
    temp_t6 = *arg3;
    var_s0 = arg3;
    var_s1 = arg1;
    if (temp_t6 != 0) {
        do {
            temp_v0 = func_15041508(var_s2, var_s1, arg2, func_15041480(temp_t6 & 0xFF));
            temp_t6 = *(u8 *)(var_s0 + 1);
            var_s2 = temp_v0;
            var_s0 += 1;
            var_s1 += 8;
        } while (temp_t6 != 0);
    }
    return var_s2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150413FC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6E770/func_150413FC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15041480 CURRENT (705) */
s32 func_15041480(u8 arg0) {
    u8 *var_a1;
    s32 temp_t6;
    s32 var_v1;

    temp_t6 = arg0 & 0xFF;
    var_a1 = D_800848D0;
    var_v1 = 0;
loop_1:
    if (temp_t6 == var_a1[0]) {
        return var_v1;
    }
    if (temp_t6 == var_a1[1]) {
        return var_v1 + 1;
    }
    if (temp_t6 == var_a1[2]) {
        return var_v1 + 2;
    }
    if (temp_t6 == var_a1[3]) {
        return var_v1 + 3;
    }
    var_v1 += 4;
    var_a1 += 4;
    if (var_v1 == 0x50) {
        return var_v1;
    }
    goto loop_1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15041480 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6E770/func_15041480.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15041508 CURRENT (2290) */
void *func_15041508(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v1;
    u8 *temp_a0;


    *(s32 *)((u8 *)arg0 + 4) = (s32) ((((arg1 * 4) & 0xFFF) << 0xC) | ((arg2 * 4) & 0xFFF));
    *(s32 *)((u8 *)arg0 + 0) = (s32) (((((arg1 + 8) * 4) & 0xFFF) << 0xC) | 0xE4000000 | (((arg2 + 0xC) * 4) & 0xFFF));
    {
    u8 *temp_a0_2;
    temp_a0_2 = (void *)(arg0 + 8);
    *(s32 *)((u8 *)arg0 + 8) = 0xE1000000;
    temp_a0 = (void *)(temp_a0_2 + 8);
    temp_v1 = arg3 % 8;
    *(s32 *)((u8 *)temp_a0_2 + 4) = (s32) ((((temp_v1 * 8) << 5) << 0x10) | ((((s32) (arg3 - temp_v1) / 8) * 0x180) & 0xFFFF));
    *(s32 *)((u8 *)temp_a0_2 + 8) = 0xF1000000;
    }
    *(s32 *)((u8 *)temp_a0 + 4) = 0x04000400;
    return temp_a0 + 8;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15041508 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6E770/func_15041508.s")
