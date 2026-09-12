#include "types.h"

/*
 * Reviewed source unit: src/game/game_130CB0.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15103828
 * - func_15103910
 * - func_15103AA0
 * - func_15103C14
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_100226F0(void *arg0, s32 arg1);
extern u8 D_800D9AB0;

void func_15103800(void) {
    func_100226F0(&D_800D9AB0, 8);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_130CB0/func_15103828.s")
/* Call context: func_10010344: unique active project prototype */
/* Call context: func_100111C8: unique active project prototype */
s32 func_10010344(s32, s32, u32, s16, s32);
void func_100111C8(s32, u16);
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15103910 CURRENT (1437) */
s32 func_15103910(void *arg0, s32 *arg1, u32 *arg2, s32 arg3, u16 *arg6) {
    s16 sp2E;
    s16 var_a3;
    s32 temp_t3;
    s32 temp_v1;
    u16 temp_a0;
    u16 temp_v0;
    u16 temp_v0_2;
    void *temp_s1;

    temp_s1 = *(void **)((u8 *)arg0 + 0x1C);
    temp_v1 = *(s32 *)((u8 *)arg0 + 0x18);
    var_a3 = (s16) temp_v1;
    *(s16 *)((u8 *)arg0 + 2) = (s16) (s32) *(f32 *)((u8 *)temp_s1 + 0x14);
    *(s16 *)((u8 *)arg0 + 4) = (s16) (s32) *(f32 *)((u8 *)temp_s1 + 0x18);
    *(s16 *)((u8 *)arg0 + 6) = (s16) (s32) *(f32 *)((u8 *)temp_s1 + 0x1C);
    if ((s16) temp_v1 != 0) {
        temp_v0 = *arg6;
        if (temp_v0 != 0) {
            *(s32 *)((u8 *)arg0 + 0x18) = (s32) ((temp_v0 << 0x10) | (temp_v1 & 0xFFFF));
            *(s16 *)((u8 *)arg0 + 0) = 0;
            *arg6 = 0;
            func_10010344(0x5B0, (s32) temp_s1, 0x61A8U, 0x64, 0x78);
            goto block_11;
        }
        temp_t3 = temp_v1 >> 0x10;
        var_a3 -= D_800BE9E4;
        if (var_a3 <= 0) {
            *arg6 = (u16) temp_t3;
            *(s16 *)((u8 *)arg0 + 0) = (s16) temp_t3;
            *arg2 = *(u32 *)((u8 *)arg0 + 0xC);
            *arg1 = 1;
            *(s32 *)((u8 *)arg0 + 0x18) = 0;
            return 0;
        }
        goto block_10;
    }
    *arg2 = *(u32 *)((u8 *)arg0 + 0xC);
    *arg1 = 1;
    temp_v0_2 = *(u16 *)((u8 *)arg0 + 0x24);
    if (temp_v0_2 == 0) {
        func_10010344(0x5B1, (s32) temp_s1, *(u32 *)((u8 *)arg0 + 0xC), *(s16 *)((u8 *)arg0 + 0xA), (s32) *(u16 *)((u8 *)arg0 + 8));
        return 1;
    }
    temp_a0 = *(u16 *)((u8 *)temp_s1 + 0x8C);
    if (temp_v0_2 != temp_a0) {
        sp2E = var_a3;
        func_100111C8((s32) temp_a0, (u16) temp_s1);
        *(u16 *)((u8 *)temp_s1 + 0x8C) = (u16) *(u16 *)((u8 *)arg0 + 0x24);
    }
    *(s32 *)((u8 *)arg0 + 0x10) = (s32) (*(s32 *)((u8 *)arg0 + 0x10) & ~0x80);
block_10:
    *(s32 *)((u8 *)arg0 + 0x18) = (s32) ((*(s32 *)((u8 *)arg0 + 0x18) & 0xFFFF0000) | var_a3);
block_11:
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15103910 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_130CB0/func_15103910.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_130CB0/func_15103AA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_130CB0/func_15103C14.s")
