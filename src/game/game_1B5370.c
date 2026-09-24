#include "types.h"

/*
 * Reviewed source unit: src/game/game_1B5370.c
 * Boundary evidence: docs/evidence/game_raw_display_transition_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15187EC0
 * - func_1518804C
 * - func_151880C0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_100226F0(void *, s32);
extern s32 D_800DF700;
extern s32 D_800DF7B4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15187EC0 CURRENT (2270) */
s32 func_15187EC0(s32 arg0, f32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7) {
    s32 temp_t1;
    s8 temp_t6;
    s8 temp_t7;
    u8 *temp_v0;

    temp_t6 = arg2 & 0xFF;
    temp_t7 = arg3 & 0xFF;
    if (D_800DF7B4 < 5) {
        temp_v0 = (void *)((D_800DF7B4 * 0x24) + &D_800DF700);
        *(f32 *)((u8 *)temp_v0 + 0x14) = arg1;
        *(s8 *)((u8 *)temp_v0 + 6) = temp_t6;
        *(s8 *)((u8 *)temp_v0 + 0) = temp_t6;
        *(s8 *)((u8 *)temp_v0 + 7) = temp_t7;
        *(s8 *)((u8 *)temp_v0 + 1) = temp_t7;
        *(u8 *)((u8 *)temp_v0 + 8) = arg4;
        *(u8 *)((u8 *)temp_v0 + 2) = arg4;
        *(s32 *)((u8 *)temp_v0 + 0x10) = arg0;
        *(u8 *)((u8 *)temp_v0 + 3) = arg5;
        *(u8 *)((u8 *)temp_v0 + 4) = arg6;
        *(u8 *)((u8 *)temp_v0 + 5) = arg7;
        func_100226F0(temp_v0 + 0x18, 0xC);
        temp_t1 = D_800DF7B4 + 1;
        D_800DF7B4 = temp_t1;
        return temp_t1 - 1;
    }
    return -1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15187EC0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5370/func_15187EC0.s")
void func_100226F0(void *arg0, s32 arg1);
extern s32 D_800DF700;
extern s32 D_800DF7B4;

void func_15187F90(void) {
    func_100226F0(&D_800DF700, 0xB4);
    D_800DF7B4 = 0;
}
void func_15187FC0(s32 arg0, void *arg1) {
    void *temp_v0;

    if ((arg0 < D_800DF7B4) && (arg0 >= 0)) {
        temp_v0 = (u8 *)&D_800DF700 + (arg0 * 0x24);
        *(s32 *)((u8 *)arg1 + 0) = (s32) *(u8 *)((u8 *)temp_v0 + 6);
        *(s32 *)((u8 *)arg1 + 4) = (s32) *(u8 *)((u8 *)temp_v0 + 7);
        *(s32 *)((u8 *)arg1 + 8) = (s32) *(u8 *)((u8 *)temp_v0 + 8);
    }
}
extern f32 D_800DF70C[];

void func_15188010(s32 arg0, f32 *arg1) {
    if ((arg0 < D_800DF7B4) && (arg0 >= 0)) {
        *arg1 = *(f32 *)((u8 *)D_800DF70C + (arg0 * 0x24));
    }
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518804C CURRENT (1160) */
void func_1518804C(s32 arg0, f32 arg1) {
    f32 var_fv0;

    if ((arg0 < D_800DF7B4) && (arg0 >= 0)) {
        var_fv0 = 1.0f;
        if (arg1 > 1.0f) {
            goto block_5;
        }
        var_fv0 = 0.0f;
        if (arg1 < 0.0f) {
block_5:
            arg1 = var_fv0;
        }
        *(f32 *)((u8 *)D_800DF70C + (arg0 * 0x24)) = arg1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518804C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5370/func_1518804C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5370/func_151880C0.s")
