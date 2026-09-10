#include "types.h"

/*
 * Reviewed source unit: src/game/game_305D0.c
 * Boundary evidence: docs/evidence/game_early_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15003120
 * - func_150031EC
 * - func_150034B4
 * - func_15003570
 * - func_15003668
 * - func_150038A0
 * - func_1500390C
 * - func_150039BC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800B0E30;
extern s32 D_800B0E34;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15003120 CURRENT (2105) */
void func_15003120(s32 arg0, s32 arg1, s32 arg2) {
    s32 *temp_a1;
    s32 *temp_v1;
    s32 *var_t0;
    s32 temp_t8;
    s32 temp_v0;
    s32 var_t1;
    s32 var_v1;
    s8 var_a2;
    u8 *temp_t0;

    temp_v0 = arg0 * 4;
    *(u8 *)(D_800B0E30 + temp_v0) = arg2;
    *(u8 *)(D_800B0E34 + arg0) = 0;
    if (arg2 != 0) {
        var_a2 = 0;
        temp_v1 = (void *)(D_800B0E30 + temp_v0);
        *temp_v1 += arg1;
        var_v1 = 0;
        temp_a1 = (void *)(*(u8 *)(D_800B0E30 + temp_v0));
        var_t0 = temp_a1;
        if (*temp_a1 != 0) {
            var_t1 = *temp_a1;
            do {
                *var_t0 = var_t1 + arg1;
                var_a2 += 1;
                temp_t0 = (void *)(*(u8 *)(D_800B0E30 + temp_v0) + var_v1);
                temp_t8 = *(s32 *)((u8 *)temp_t0 + 4);
                var_v1 += 0xC;
                *(s32 *)((u8 *)temp_t0 + 4) = (s32) (temp_t8 + arg1);
                var_t0 = (void *)(*(u8 *)(D_800B0E30 + temp_v0) + var_v1);
                var_t1 = *var_t0;
            } while (var_t1 != 0);
        }
        *(u8 *)(D_800B0E34 + arg0) = var_a2;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15003120 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_305D0/func_15003120.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_305D0/func_150031EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_305D0/func_150034B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_305D0/func_15003570.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_305D0/func_15003668.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_305D0/func_150038A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_305D0/func_1500390C.s")
void func_150039B0(s32 arg0) {

}
extern s32 D_800DBE5C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150039BC CURRENT (25) */
void func_150039BC(s32 arg0) {
    D_800DBE5C = arg0;
    if (arg0 != 0) {
        D_800DBE5C = arg0 + 8;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150039BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_305D0/func_150039BC.s")
