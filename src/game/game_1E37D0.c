#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E37D0.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B6320
 * - func_151B6420
 * - func_151B65D4
 * - func_151B6928
 * - func_151B70B4
 * - func_151B7144
 * - func_151B7328
 * - func_151B7678
 * - func_151B76CC
 * - func_151B77F4
 * - func_151B7998
 * - func_151B7C38
 * - func_151B82CC
 * - func_151B8318
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B6320.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B6420.s")
f32 func_15143E64(f32 *, void *, void *);           /* extern */
extern f32 D_800AA474;
extern f32 D_800AA478;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B65D4 CURRENT (7417) */
s32 func_151B65D4(u8 *arg0) {
    u8 *spB4;
    s32 spB0;
    f32 spA8;
    f32 spA4;
    f32 spA0;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp58;
    f32 sp50;
    f32 sp48;
    f32 temp_fa0;
    f32 temp_fs2;
    f32 temp_ft1;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fs0;
    f32 var_ft4;
    f32 var_ft5;
    s8 temp_v0_3;
    u8 *temp_a2;
    u8 *temp_t2;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_a2 = (void *)(*(void **)((u8 *)arg0 + 0x98));
    temp_v0 = (void *)(*(void **)((u8 *)temp_a2 + 0));
    if ((*(s32 *)((u8 *)temp_v0 + 0) == 0) || (*(u8 *)((u8 *)temp_a2 + 4) != *(u8 *)((u8 *)temp_v0 + 0x3B)) || (*(f32 *)((u8 *)temp_v0 + 0x3C) < 15.0f)) {
        *(s8 *)((u8 *)arg0 + 0x30) = 0;
        *(u16 *)((u8 *)arg0 + 0x1E) = (u16) (*(u16 *)((u8 *)arg0 + 0x1E) | 8);
        return 1;
    }
    *(f32 *)((u8 *)arg0 + 0x10) = (f32) *(f32 *)((u8 *)temp_v0 + 0x14);
    *(f32 *)((u8 *)arg0 + 0x14) = (f32) *(f32 *)((u8 *)temp_v0 + 0x18);
    *(f32 *)((u8 *)arg0 + 0x18) = (f32) *(f32 *)((u8 *)temp_v0 + 0x1C);
    spA0 = *(f32 *)((u8 *)arg0 + 0x10) - *(f32 *)((u8 *)temp_a2 + 8);
    spA4 = *(f32 *)((u8 *)arg0 + 0x14) - *(f32 *)((u8 *)temp_a2 + 0xC);
    spB0 = *(s32 *)((u8 *)arg0 + 0x94);
    spB4 = temp_a2;
    spA8 = *(f32 *)((u8 *)arg0 + 0x18) - *(f32 *)((u8 *)temp_a2 + 0x10);
    temp_fv0 = func_15143E64(&spA0, arg0, temp_a2);
    *(f32 *)((u8 *)spB4 + 0x14) = (f32) (*(f32 *)((u8 *)spB4 + 0x14) + (temp_fv0 * D_800AA474 * D_800BE9A4));
    temp_fv1 = *(f32 *)((u8 *)spB4 + 0x14);
    *(f32 *)((u8 *)spB4 + 0x1C) = (f32) (*(f32 *)((u8 *)spB4 + 0x1C) + (temp_fv0 * D_800AA478));
    sp58 = temp_fv1;
    if (temp_fv1 > 1.0f) {
        temp_t2 = (void *)(spB4 + 8);
        temp_fv1_2 = 1.0f / sp58;
        *(f32 *)((u8 *)&sp84 + 0) = *(f32 *)((u8 *)spB4 + 8);
        *(s32 *)((u8 *)&sp84 + 4) = (s32) *(s32 *)((u8 *)temp_t2 + 4);
        var_ft5 = *(f32 *)((u8 *)spB4 + 0x18) + D_800BE9A4;
        *(s32 *)((u8 *)&sp84 + 8) = (s32) *(s32 *)((u8 *)temp_t2 + 8);
        temp_fa0 = *(f32 *)((u8 *)spB4 + 0x20);
        var_fs0 = *(f32 *)((u8 *)spB4 + 0x24);
        var_ft4 = temp_fa0;
        temp_fs2 = -(var_ft5 * temp_fv1_2);
        sp50 = (*(f32 *)((u8 *)spB4 + 0x1C) - temp_fa0) * temp_fv1_2;
        sp48 = temp_fv0 * temp_fv1_2;
        do {
            temp_v0_2 = (void *)((*(s8 *)((u8 *)arg0 + 0x2E) * 0x1C) + spB0);
            *(f32 *)((u8 *)temp_v0_2 + 0) = (f32) *(f32 *)((u8 *)&sp84 + 0);
            *(s32 *)((u8 *)temp_v0_2 + 4) = (s32) *(s32 *)((u8 *)&sp84 + 4);
            *(s8 *)((u8 *)temp_v0_2 + 0x10) = 0x9B;
            *(f32 *)((u8 *)temp_v0_2 + 0x14) = var_ft4;
            *(s32 *)((u8 *)temp_v0_2 + 8) = (s32) *(s32 *)((u8 *)&sp84 + 8);
            temp_ft1 = 13.0f - var_ft5;
            var_ft5 += temp_fs2;
            *(f32 *)((u8 *)temp_v0_2 + 0xC) = temp_ft1;
            if (var_ft4 > 16384.0f) {
                do {
                    *(f32 *)((u8 *)temp_v0_2 + 0x14) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0x14) - 32768.0f);
                } while (*(f32 *)((u8 *)temp_v0_2 + 0x14) > 16384.0f);
            }
            *(f32 *)((u8 *)temp_v0_2 + 0x18) = var_fs0;
            *(s8 *)((u8 *)arg0 + 0x2E) = (s8) (*(s8 *)((u8 *)arg0 + 0x2E) + 1);
            if (*(u8 *)((u8 *)arg0 + 0x25) == *(s8 *)((u8 *)arg0 + 0x2E)) {
                *(s8 *)((u8 *)arg0 + 0x2E) = 0;
            }
            temp_v0_3 = *(s8 *)((u8 *)arg0 + 0x2D);
            *(s8 *)((u8 *)arg0 + 0x2C) = (s8) (*(s8 *)((u8 *)arg0 + 0x2C) + 1);
            if (temp_v0_3 == *(s8 *)((u8 *)arg0 + 0x2E)) {
                *(s8 *)((u8 *)arg0 + 0x2D) = (s8) (temp_v0_3 + 1);
                if (*(u8 *)((u8 *)arg0 + 0x25) == *(s8 *)((u8 *)arg0 + 0x2D)) {
                    *(s8 *)((u8 *)arg0 + 0x2D) = 0;
                }
                *(s8 *)((u8 *)arg0 + 0x2C) = (s8) (*(s8 *)((u8 *)arg0 + 0x2C) - 1);
            }
            sp84 += spA0 * temp_fv1_2;
            sp88 += spA4 * temp_fv1_2;
            var_ft4 += sp50;
            sp8C += spA8 * temp_fv1_2;
            var_fs0 += sp48;
            *(f32 *)((u8 *)spB4 + 0x14) = (f32) (*(f32 *)((u8 *)spB4 + 0x14) - 1.0f);
        } while (*(f32 *)((u8 *)spB4 + 0x14) > 1.0f);
        *(f32 *)((u8 *)spB4 + 8) = (f32) *(f32 *)((u8 *)&sp84 + 0);
        *(s32 *)((u8 *)temp_t2 + 4) = (s32) *(s32 *)((u8 *)&sp84 + 4);
        *(s32 *)((u8 *)temp_t2 + 8) = (s32) *(s32 *)((u8 *)&sp84 + 8);
        *(f32 *)((u8 *)spB4 + 0x20) = var_ft4;
        *(f32 *)((u8 *)spB4 + 0x24) = var_fs0;
        *(f32 *)((u8 *)spB4 + 0x18) = var_ft5;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B65D4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B65D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B6928.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B70B4 CURRENT (1255) */
void func_151B70B4(void *arg0, void *arg1, s32 arg2) {
    s32 temp_a3;
    s32 temp_t6;
    s32 temp_v1;
    void *temp_v0;

    temp_t6 = arg2 & 0xFF;
    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    temp_a3 = *(s32 *)((u8 *)temp_v0 + 0);
    if (temp_t6 == 0) {
        if (temp_a3 == *(s32 *)((u8 *)arg1 + 0)) {
            *(s8 *)((u8 *)arg0 + 0x30) = 0;
            *(u16 *)((u8 *)arg0 + 0x1E) = (u16) (*(u16 *)((u8 *)arg0 + 0x1E) | 8);
        }
    } else if (temp_t6 == 0x2D) {
        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        if (temp_v1 == temp_a3) {
            *(s32 *)((u8 *)temp_v0 + 0) = (s32) *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_a3) {
            *(s32 *)((u8 *)temp_v0 + 0) = temp_v1;
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B70B4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B70B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B7144.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B7328.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B7678.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B76CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B77F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B7998.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B7C38.s")
extern void (*D_8008FB98[])(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B82CC CURRENT (455) */
void func_151B82CC(void *arg0, s32 arg1, s32 arg2) {
    void (*temp_v1)(s32);

    arg2 &= 0xFF;
    temp_v1 = D_8008FB98[*(u8 *)((u8 *)*(void **)((u8 *)arg0 + 0x98) + 8)];
    if (temp_v1 != 0) {
        temp_v1(arg2);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B82CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B82CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B8318.s")
