#include "types.h"

/*
 * Reviewed source unit: src/game/game_1EBFD0.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151BEB20
 * - func_151BECB8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

/* Call context: func_150A8050: unique active project prototype */
void func_150A8050(void *, f32, s32, f32);
extern f32 D_800AA8E0;
extern u8 D_800BE9C0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BEB20 CURRENT (1690) */
s32 func_151BEB20(u8 *arg0) {
    u8 *temp_v1;
    u8 *temp_v1_2;
    u8 *temp_v1_3;
    u8 *temp_v1_4;
    u8 *temp_v1_5;
    u8 *temp_v1_6;
    u8 *temp_v1_7;
    u8 *temp_v1_8;
    u8 *temp_v1_9;

    func_150A8050(arg0 + (D_800BE9C0 << 6) + 0x7C, 0.0f, *(s32 *)((u8 *)arg0 + 0x120), 0.0f);
    *(f32 *)((u8 *)(arg0 + (D_800BE9C0 << 6)) + 0xAC) = (f32) *(f32 *)((u8 *)arg0 + 0x54);
    *(f32 *)((u8 *)(arg0 + (D_800BE9C0 << 6)) + 0xB0) = (f32) *(f32 *)((u8 *)arg0 + 0x58);
    *(f32 *)((u8 *)(arg0 + (D_800BE9C0 << 6)) + 0xB4) = (f32) *(f32 *)((u8 *)arg0 + 0x5C);
    temp_v1 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1 + 0x7C) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x7C) * D_800AA8E0);
    temp_v1_2 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_2 + 0x80) = (f32) (*(f32 *)((u8 *)temp_v1_2 + 0x80) * D_800AA8E0);
    temp_v1_3 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_3 + 0x84) = (f32) (*(f32 *)((u8 *)temp_v1_3 + 0x84) * D_800AA8E0);
    temp_v1_4 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_4 + 0x8C) = (f32) (*(f32 *)((u8 *)temp_v1_4 + 0x8C) * D_800AA8E0);
    temp_v1_5 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_5 + 0x90) = (f32) (*(f32 *)((u8 *)temp_v1_5 + 0x90) * D_800AA8E0);
    temp_v1_6 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_6 + 0x94) = (f32) (*(f32 *)((u8 *)temp_v1_6 + 0x94) * D_800AA8E0);
    temp_v1_7 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_7 + 0x9C) = (f32) (*(f32 *)((u8 *)temp_v1_7 + 0x9C) * D_800AA8E0);
    temp_v1_8 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_8 + 0xA0) = (f32) (*(f32 *)((u8 *)temp_v1_8 + 0xA0) * D_800AA8E0);
    temp_v1_9 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_9 + 0xA4) = (f32) (*(f32 *)((u8 *)temp_v1_9 + 0xA4) * D_800AA8E0);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BEB20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EBFD0/func_151BEB20.s")
s32 func_151BEC94(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s8 *arg4) {
    *arg4 = 1;
    return arg0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EBFD0/func_151BECB8.s")
s32 func_151BEE94(void *arg0) {
    if (*(u8 *)((u8 *)arg0 + 0x127) == 0xFF) {
        return 0;
    }
    if (*(s32 *)((u8 *)arg0 + 0) == 0) {
        return 0;
    }
    if (*(u8 *)((u8 *)arg0 + 4) == 0xFF) {
        return 0;
    }
    return 1;
}
