#include "types.h"

/*
 * Reviewed source unit: src/game/game_203340.c
 * Boundary evidence: docs/evidence/game_raw_type4b_framebuffer_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151D5E90
 * - func_151D61B0
 * - func_151D6418
 * - func_151D66F0
 * - func_151D6778
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800BE620;
extern s32 D_800BE624;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D5E90 CURRENT (13508) */
void *func_151D5E90(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u32 sp8C;
    s32 sp84;
    u32 sp34;
    s32 temp_a1;
    s32 temp_s1;
    s32 temp_t0;
    s32 temp_t1;
    s32 temp_t2;
    s32 temp_t7;
    s32 var_a1;
    s32 var_s0;
    s32 var_v1;
    u32 var_a2;
    u32 var_a3;
    u32 var_a3_2;
    u32 var_v0;
    u8 *temp_a0;
    u8 *temp_a0_10;
    u8 *temp_a0_11;
    u8 *temp_a0_12;
    u8 *temp_a0_13;
    u8 *temp_a0_14;
    u8 *temp_a0_2;
    u8 *temp_a0_3;
    u8 *temp_a0_4;
    u8 *temp_a0_5;
    u8 *temp_a0_6;
    u8 *temp_a0_7;
    u8 *temp_a0_8;
    u8 *temp_a0_9;
    u8 *var_a0;

    var_v1 = D_800BE624;
    *(s32 *)((u8 *)arg0 + 0) = 0xE7000000;
    *(s32 *)((u8 *)arg0 + 4) = 0;
    temp_a0 = (void *)(arg0 + 8);
    *(s32 *)((u8 *)arg0 + 8) = 0xFCFFFFFF;
    *(s32 *)((u8 *)temp_a0 + 4) = 0xFFFCF279;
    temp_a0_2 = (void *)(temp_a0 + 8);
    *(s32 *)((u8 *)temp_a0 + 8) = 0xEF000CFF;
    *(s32 *)((u8 *)temp_a0_2 + 4) = 0x0F0A4000;
    temp_a0_3 = (void *)(temp_a0_2 + 8);
    *(s32 *)((u8 *)temp_a0_2 + 8) = 0xD9000000;
    *(s32 *)((u8 *)temp_a0_3 + 4) = 0;
    temp_a0_4 = (void *)(temp_a0_3 + 8);
    *(s32 *)((u8 *)temp_a0_4 + 4) = -1;
    *(s32 *)((u8 *)temp_a0_3 + 8) = 0xD7000002;
    var_a0 = (void *)(temp_a0_4 + 8);
    var_a1 = 0x10;
    var_v0 = 0;
    if (var_v1 != 0) {
        do {
            var_a3 = var_v0 + var_a1;
            var_a2 = 0;
            var_s0 = 0x80;
            if ((u32) var_v1 < var_a3) {
                var_a1 = var_v1 - var_v0;
                var_a3 = var_v0 + var_a1;
            }
            if (D_800BE620 != 0) {
                temp_t7 = (var_v0 * 4) & 0xFFF;
                temp_s1 = ((var_a3 - 1) * 4) & 0xFFF;
                sp84 = var_a1;
                sp8C = (u32) var_v1;
                sp34 = var_a3;
                do {
                    var_a3_2 = var_a2 + var_s0;
                    if ((u32) D_800BE620 < var_a3_2) {
                        var_s0 = D_800BE620 - var_a2;
                        var_a3_2 = var_a2 + var_s0;
                    }
                    *(s32 *)((u8 *)var_a0 + 0) = (s32) (((D_800BE620 - 1) & 0xFFF) | 0xFD100000);
                    temp_a0_5 = (void *)(var_a0 + 8);
                    *(s32 *)((u8 *)var_a0 + 4) = arg1;
                    temp_t1 = var_a3_2 - 1;
                    temp_t2 = ((((u32) (((temp_t1 - var_a2) * 2) + 9) >> 3) & 0x1FF) << 9) | 0xF5100000;
                    *(s32 *)((u8 *)var_a0 + 8) = temp_t2;
                    temp_a0_6 = (void *)(temp_a0_5 + 8);
                    *(s32 *)((u8 *)temp_a0_5 + 4) = 0x07000000;
                    *(s32 *)((u8 *)temp_a0_5 + 8) = 0xE6000000;
                    *(s32 *)((u8 *)temp_a0_6 + 4) = 0;
                    temp_a0_7 = (void *)(temp_a0_6 + 8);
                    temp_t0 = ((var_a2 * 4) & 0xFFF) << 0xC;
                    temp_a1 = ((temp_t1 * 4) & 0xFFF) << 0xC;
                    *(s32 *)((u8 *)temp_a0_6 + 8) = (s32) (temp_t0 | 0xF4000000 | temp_t7);
                    *(s32 *)((u8 *)temp_a0_7 + 4) = (s32) (temp_a1 | 0x07000000 | temp_s1);
                    temp_a0_8 = (void *)(temp_a0_7 + 8);
                    *(s32 *)((u8 *)temp_a0_7 + 8) = 0xE7000000;
                    *(s32 *)((u8 *)temp_a0_8 + 4) = 0;
                    temp_a0_9 = (void *)(temp_a0_8 + 8);
                    *(s32 *)((u8 *)temp_a0_8 + 8) = temp_t2;
                    *(s32 *)((u8 *)temp_a0_9 + 4) = 0;
                    temp_a0_10 = (void *)(temp_a0_9 + 8);
                    *(s32 *)((u8 *)temp_a0_10 + 4) = (s32) (temp_a1 | temp_s1);
                    *(s32 *)((u8 *)temp_a0_9 + 8) = (s32) (temp_t0 | 0xF2000000 | temp_t7);
                    temp_a0_11 = (void *)(temp_a0_10 + 8);
                    *(s32 *)((u8 *)temp_a0_11 + 4) = (s32) (temp_t0 | temp_t7);
                    *(s32 *)((u8 *)temp_a0_10 + 8) = (s32) ((((var_a3_2 * 4) & 0xFFF) << 0xC) | 0xE4000000 | ((var_a3 * 4) & 0xFFF));
                    temp_a0_12 = (void *)(temp_a0_11 + 8);
                    *(s32 *)((u8 *)temp_a0_11 + 8) = 0xE1000000;
                    *(s32 *)((u8 *)temp_a0_12 + 4) = (s32) ((var_a2 << 0x15) | ((var_v0 << 5) & 0xFFFF));
                    temp_a0_13 = (void *)(temp_a0_12 + 8);
                    *(s32 *)((u8 *)temp_a0_12 + 8) = 0xF1000000;
                    *(s32 *)((u8 *)temp_a0_13 + 4) = 0x04000400;
                    temp_a0_14 = (void *)(temp_a0_13 + 8);
                    *(s32 *)((u8 *)temp_a0_13 + 8) = 0xE7000000;
                    *(s32 *)((u8 *)temp_a0_14 + 4) = 0;
                    var_a0 = (void *)(temp_a0_14 + 8);
                    var_a2 = var_a3_2;
                } while (var_a3_2 < (u32) D_800BE620);
                var_a3 = sp34;
                var_a1 = sp84;
                var_v1 = (s32) sp8C;
            }
            var_v0 = var_a3;
        } while (var_a3 < (u32) var_v1);
    }
    *(s32 *)((u8 *)var_a0 + 0) = 0xEF080C3F;
    *(s32 *)((u8 *)var_a0 + 4) = 0x0F0A4000;
    return var_a0 + 8;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D5E90 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_203340/func_151D5E90.s")
extern s32 D_800BE620;
extern s32 D_800BE624;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D61B0 CURRENT (6796) */
void func_151D61B0(void *arg0) {
    s16 temp_t7;
    s32 temp_t3;
    s32 var_a2;
    s32 var_t2;
    u16 temp_t1;
    u16 temp_t4;
    u16 temp_t4_2;
    u16 var_t0;
    u16 var_t1;
    u8 *temp_a3;
    u8 *var_a0;
    u8 *var_a1;

    var_a1 = arg0;
    var_a2 = 0;
    if (D_800BE624 > 0) {
        temp_t3 = D_800BE620 - 1;
        do {
            temp_a3 = (void *)(var_a1 + 2);
            var_a0 = temp_a3;
            var_t0 = *(u16 *)((u8 *)var_a1 + 2);
            var_t1 = *(u16 *)((u8 *)var_a1 + 4);
            var_t2 = 1;
            if ((temp_t3 >= 2) && ((temp_t4 = var_t0, (((D_800BE620 - 2) & 1) == 0)) || (var_t0 = var_t1 & 0xFFFF, var_t1 = *(u16 *)((u8 *)temp_a3 + 4), var_t2 = 2, *(s16 *)((u8 *)temp_a3 + 2) = (s16) (((((((s32) var_t0 >> 0xB) & 0x1F) + (((s32) temp_t4 >> 0xC) & 0xF) + (((s32) var_t1 >> 0xC) & 0xF)) & 0x3E) << 0xA) | ((((((s32) var_t0 >> 6) & 0x1F) + (((s32) temp_t4 >> 7) & 0xF) + (((s32) var_t1 >> 7) & 0xF)) & 0x3E) << 5) | (((((s32) var_t0 >> 1) & 0x1F) + (((s32) temp_t4 >> 2) & 0xF) + (((s32) var_t1 >> 2) & 0xF)) & 0x3E) | 1), var_a0 = temp_a3 + 2, (temp_t3 != 2)))) {
                do {
                    temp_t1 = *(u16 *)((u8 *)var_a0 + 4);
                    temp_t7 = ((((((s32) var_t1 >> 0xB) & 0x1F) + (((s32) var_t0 >> 0xC) & 0xF) + (((s32) temp_t1 >> 0xC) & 0xF)) & 0x3E) << 0xA) | ((((((s32) var_t1 >> 6) & 0x1F) + (((s32) var_t0 >> 7) & 0xF) + (((s32) temp_t1 >> 7) & 0xF)) & 0x3E) << 5) | (((((s32) var_t1 >> 1) & 0x1F) + (((s32) var_t0 >> 2) & 0xF) + (((s32) temp_t1 >> 2) & 0xF)) & 0x3E) | 1;
                    temp_t4_2 = var_t1;
                    var_t0 = temp_t1 & 0xFFFF;
                    *(s16 *)((u8 *)var_a0 + 2) = temp_t7;
                    var_t1 = *(u16 *)((u8 *)var_a0 + 6);
                    var_t2 += 2;
                    *(u16 *)((u8 *)var_a0 + 4) = (u16) (((((((s32) var_t0 >> 0xB) & 0x1F) + (((s32) temp_t4_2 >> 0xC) & 0xF) + (((s32) var_t1 >> 0xC) & 0xF)) & 0x3E) << 0xA) | ((((((s32) var_t0 >> 6) & 0x1F) + (((s32) temp_t4_2 >> 7) & 0xF) + (((s32) var_t1 >> 7) & 0xF)) & 0x3E) << 5) | (((((s32) var_t0 >> 1) & 0x1F) + (((s32) temp_t4_2 >> 2) & 0xF) + (((s32) var_t1 >> 2) & 0xF)) & 0x3E) | 1);
                    var_a0 += 4;
                } while (var_t2 != temp_t3);
            }
            var_a2 += 1;
            var_a1 += D_800BE620 * 2;
        } while (var_a2 != D_800BE624);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D61B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_203340/func_151D61B0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D6418 CURRENT (13204) */
void *func_151D6418(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_t5;
    u32 temp_a2;
    u32 temp_s0;
    u32 temp_t0;
    u32 temp_v1;
    u32 var_a2;
    u32 var_t1;
    u32 var_t2;
    u32 var_t3;
    u8 *temp_a0;
    u8 *temp_a0_10;
    u8 *temp_a0_11;
    u8 *temp_a0_12;
    u8 *temp_a0_13;
    u8 *temp_a0_14;
    u8 *temp_a0_2;
    u8 *temp_a0_3;
    u8 *temp_a0_4;
    u8 *temp_a0_5;
    u8 *temp_a0_6;
    u8 *temp_a0_7;
    u8 *temp_a0_8;
    u8 *temp_a0_9;
    u8 *var_a0;

    var_t5 = arg1;
    *(s32 *)((u8 *)arg0 + 0) = 0xFA000000;
    *(s32 *)((u8 *)arg0 + 4) = (s32) ((arg3 & 0xFF) | ~0xFF);
    temp_a0 = (void *)(arg0 + 8);
    *(s32 *)((u8 *)temp_a0 + 4) = -0x805;
    *(s32 *)((u8 *)arg0 + 8) = 0xFC11FE23;
    temp_a0_2 = (void *)(temp_a0 + 8);
    *(s32 *)((u8 *)temp_a0 + 8) = 0xEF000CFF;
    *(s32 *)((u8 *)temp_a0_2 + 4) = 0x504340;
    temp_a0_3 = (void *)(temp_a0_2 + 8);
    *(s32 *)((u8 *)temp_a0_2 + 8) = 0xD9000000;
    *(s32 *)((u8 *)temp_a0_3 + 4) = 0;
    temp_a0_4 = (void *)(temp_a0_3 + 8);
    *(s32 *)((u8 *)temp_a0_4 + 4) = -1;
    *(s32 *)((u8 *)temp_a0_3 + 8) = 0xD7000002;
    var_a0 = (void *)(temp_a0_4 + 8);
    var_t3 = 0;
    {
        s32 sp34 = D_800BE624;
    if (D_800BE624 != 0) {
        temp_v1 = D_800BE620 * 2;
        temp_s0 = (D_800BE620 * 4) - 1;
        temp_t0 = temp_v1 >> 3;
        do {
            *(s32 *)((u8 *)var_a0 + 4) = (s32) (var_t5 + 0x80000000);
            *(s32 *)((u8 *)var_a0 + 0) = 0xFD100000;
            temp_a0_5 = (void *)(var_a0 + 8);
            *(s32 *)((u8 *)var_a0 + 8) = 0xF5100000;
            *(s32 *)((u8 *)temp_a0_5 + 4) = 0x07000000;
            temp_a0_6 = (void *)(temp_a0_5 + 8);
            *(s32 *)((u8 *)temp_a0_5 + 8) = 0xE6000000;
            *(s32 *)((u8 *)temp_a0_6 + 4) = 0;
            temp_a0_7 = (void *)(temp_a0_6 + 8);
            *(s32 *)((u8 *)temp_a0_6 + 8) = 0xF3000000;
            temp_a0_8 = (void *)(temp_a0_7 + 8);
            if (temp_s0 < 0x7FFU) {
                var_t1 = temp_s0;
            } else {
                var_t1 = 0x7FF;
            }
            if (temp_t0 == 0) {
                var_t2 = 1;
            } else {
                var_t2 = temp_t0;
            }
            if (temp_t0 == 0) {
                var_a2 = 1;
            } else {
                var_a2 = temp_t0;
            }
            *(s32 *)((u8 *)temp_a0_7 + 4) = (s32) ((((u32) (var_t2 + 0x7FF) / var_a2) & 0xFFF) | 0x07000000 | ((var_t1 & 0xFFF) << 0xC));
            temp_a0_9 = (void *)(temp_a0_8 + 8);
            *(s32 *)((u8 *)temp_a0_7 + 8) = 0xE7000000;
            *(s32 *)((u8 *)temp_a0_8 + 4) = 0;
            *(s32 *)((u8 *)temp_a0_8 + 8) = (s32) (((((u32) (temp_v1 + 7) >> 3) & 0x1FF) << 9) | 0xF5100000);
            *(s32 *)((u8 *)temp_a0_9 + 4) = 0;
            temp_a0_10 = (void *)(temp_a0_9 + 8);
            *(s32 *)((u8 *)temp_a0_9 + 8) = 0xF2000000;
            *(s32 *)((u8 *)temp_a0_10 + 4) = (s32) (((((D_800BE620 - 1) * 4) & 0xFFF) << 0xC) | 0xC);
            temp_a0_11 = (void *)(temp_a0_10 + 8);
            temp_a2 = var_t3 + 4;
            *(s32 *)((u8 *)temp_a0_10 + 8) = (s32) (((((D_800BE620 - arg2) * 4) & 0xFFF) << 0xC) | 0xE4000000 | ((temp_a2 * 4) & 0xFFF));
            *(s32 *)((u8 *)temp_a0_11 + 4) = (s32) ((var_t3 * 4) & 0xFFF);
            temp_a0_12 = (void *)(temp_a0_11 + 8);
            *(s32 *)((u8 *)temp_a0_11 + 8) = 0xE1000000;
            *(s32 *)((u8 *)temp_a0_12 + 4) = 0;
            temp_a0_13 = (void *)(temp_a0_12 + 8);
            *(s32 *)((u8 *)temp_a0_12 + 8) = 0xF1000000;
            *(s32 *)((u8 *)temp_a0_13 + 4) = 0x04000400;
            temp_a0_14 = (void *)(temp_a0_13 + 8);
            *(s32 *)((u8 *)temp_a0_13 + 8) = 0xE7000000;
            *(s32 *)((u8 *)temp_a0_14 + 4) = 0;
            var_a0 = (void *)(temp_a0_14 + 8);
            var_t3 = temp_a2;
            var_t5 += D_800BE620 * 8;
        } while (temp_a2 < (u32) sp34);
    }
    return var_a0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D6418 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_203340/func_151D6418.s")
void func_100043B4(s32, s32);
extern u8 D_80038080;
extern s32 D_800BE570;
extern s8 D_800BE574;
extern s8 D_800BE575;
extern s32 D_800BE9F0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D66F0 CURRENT (415) */
void func_151D66F0(s32 arg0, s32 arg1) {
    if ((D_800BE9F0 != 6) || (D_80038080 != 0)) {
        if (arg1 == 0) {
            arg0 = 0;
        }
        D_800BE574 = arg0;
        if (arg0 != 0) {
            D_800BE575 = arg1;
        } else {
            D_800BE575 = 0;
        }
        if ((arg0 == 0) && (D_800BE570 != 0)) {
            func_100043B4(D_800BE570, 3);
            D_800BE570 = 0;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D66F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_203340/func_151D66F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_203340/func_151D6778.s")
