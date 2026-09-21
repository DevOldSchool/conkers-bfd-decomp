#include "types.h"

/*
 * Reviewed source unit: src/game/game_1B1600.c
 * Boundary evidence: docs/evidence/game_raw_clipping_resource_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15184150
 * - func_15184368
 * - func_15184DF0
 * - func_15184FA4
 * - func_15185454
 * - func_15185554
 * - func_1518557C
 * - func_1518567C
 * - func_151856A8
 * - func_151857B0
 * - func_151857DC
 * - func_151858D4
 * - func_151858FC
 * - func_151859FC
 * - func_15185A28
 * - func_15185B28
 * - func_15185B54
 * - func_15185C44
 * - func_15185C6C
 * - func_15185D5C
 * - func_15185D84
 * - func_15185DAC
 * - func_15185DD4
 * - func_15185F24
 * - func_1518652C
 * - func_15186794
 * - func_151872B0
 * - func_151873E4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15184150.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15184368.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15184DF0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15184FA4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15185454 CURRENT (1460) */
void *func_15185454(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_a3;
    s16 temp_v0;
    s16 temp_v1;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 8);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 4);
    temp_fa1 = *(f32 *)((u8 *)arg0 + 0);
    temp_fv0 = (temp_fv1 - temp_fa0) / ((*(f32 *)((u8 *)arg1 + 4) - temp_fa0) - (*(f32 *)((u8 *)arg1 + 8) - temp_fv1));
    *(f32 *)((u8 *)arg2 + 0) = (f32) (temp_fa1 + ((*(f32 *)((u8 *)arg1 + 0) - temp_fa1) * temp_fv0));
    temp_fa0_2 = *(f32 *)((u8 *)arg0 + 4);
    temp_ft4 = temp_fa0_2 + ((*(f32 *)((u8 *)arg1 + 4) - temp_fa0_2) * temp_fv0);
    *(f32 *)((u8 *)arg2 + 8) = temp_ft4;
    *(f32 *)((u8 *)arg2 + 4) = temp_ft4;
    temp_v0 = *(s16 *)((u8 *)arg0 + 0xC);
    *(s16 *)((u8 *)arg2 + 0xC) = (s16) (s32) ((f32) temp_v0 + ((f32) (*(s16 *)((u8 *)arg1 + 0xC) - temp_v0) * temp_fv0));
    temp_v1 = *(s16 *)((u8 *)arg0 + 0xE);
    *(s16 *)((u8 *)arg2 + 0xE) = (s16) (s32) ((f32) temp_v1 + ((f32) (*(s16 *)((u8 *)arg1 + 0xE) - temp_v1) * temp_fv0));
    temp_a3 = *(s16 *)((u8 *)arg0 + 0x10);
    *(s16 *)((u8 *)arg2 + 0x10) = (s16) (s32) ((f32) temp_a3 + ((f32) (*(s16 *)((u8 *)arg1 + 0x10) - temp_a3) * temp_fv0));
    return arg2 + 0x14;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15185454 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15185454.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15185554 CURRENT (510) */
s32 func_15185554(void *arg0) {
    s32 var_v0;

    var_v0 = 0;
    if (*(f32 *)((u8 *)arg0 + 8) < *(f32 *)((u8 *)arg0 + 4)) {
        var_v0 = 1;
    }
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15185554 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15185554.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518557C CURRENT (2295) */
void *func_1518557C(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_a3;
    s16 temp_v0;
    s16 temp_v1;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 8);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0);
    temp_fa1 = *(f32 *)((u8 *)arg1 + 0);
    temp_fv0 = (temp_fv1 + temp_fa0) / ((temp_fa0 - temp_fa1) + (temp_fv1 - *(f32 *)((u8 *)arg1 + 8)));
    *(f32 *)((u8 *)arg2 + 0) = (f32) (temp_fa0 + ((temp_fa1 - temp_fa0) * temp_fv0));
    {
        f32 temp_ft4 = *(f32 *)((u8 *)arg0 + 4);
    *(f32 *)((u8 *)arg2 + 8) = (f32) -*(f32 *)((u8 *)arg2 + 0);
    *(f32 *)((u8 *)arg2 + 4) = (f32) (temp_ft4 + ((*(f32 *)((u8 *)arg1 + 4) - temp_ft4) * temp_fv0));
    temp_v0 = *(s16 *)((u8 *)arg0 + 0xC);
    *(s16 *)((u8 *)arg2 + 0xC) = (s16) (s32) ((f32) temp_v0 + ((f32) (*(s16 *)((u8 *)arg1 + 0xC) - temp_v0) * temp_fv0));
    temp_v1 = *(s16 *)((u8 *)arg0 + 0xE);
    *(s16 *)((u8 *)arg2 + 0xE) = (s16) (s32) ((f32) temp_v1 + ((f32) (*(s16 *)((u8 *)arg1 + 0xE) - temp_v1) * temp_fv0));
    temp_a3 = *(s16 *)((u8 *)arg0 + 0x10);
    *(s16 *)((u8 *)arg2 + 0x10) = (s16) (s32) ((f32) temp_a3 + ((f32) (*(s16 *)((u8 *)arg1 + 0x10) - temp_a3) * temp_fv0));
    return arg2 + 0x14;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518557C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_1518557C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518567C CURRENT (510) */
s32 func_1518567C(void *arg0) {
    s32 var_v0;

    var_v0 = 0;
    if (*(f32 *)((u8 *)arg0 + 0) < -*(f32 *)((u8 *)arg0 + 8)) {
        var_v0 = 1;
    }
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518567C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_1518567C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151856A8 CURRENT (1425) */
void *func_151856A8(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_v0;
    s16 temp_v1;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 8);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 4);
    temp_fa1 = *(f32 *)((u8 *)arg0 + 0);
    temp_fv0 = (temp_fv1 + temp_fa0) / ((temp_fa0 - *(f32 *)((u8 *)arg1 + 4)) + (temp_fv1 - *(f32 *)((u8 *)arg1 + 8)));
    *(f32 *)((u8 *)arg2 + 0) = (f32) (temp_fa1 + ((*(f32 *)((u8 *)arg1 + 0) - temp_fa1) * temp_fv0));
    temp_fa0_2 = *(f32 *)((u8 *)arg0 + 4);
    *(f32 *)((u8 *)arg2 + 4) = (f32) (temp_fa0_2 + ((*(f32 *)((u8 *)arg1 + 4) - temp_fa0_2) * temp_fv0));
    *(f32 *)((u8 *)arg2 + 8) = (f32) -*(f32 *)((u8 *)arg2 + 4);
    temp_v0 = *(s16 *)((u8 *)arg0 + 0xC);
    *(s16 *)((u8 *)arg2 + 0xC) = (s16) (s32) ((f32) temp_v0 + ((f32) (*(s16 *)((u8 *)arg1 + 0xC) - temp_v0) * temp_fv0));
    temp_v1 = *(s16 *)((u8 *)arg0 + 0xE);
    *(s16 *)((u8 *)arg2 + 0xE) = (s16) (s32) ((f32) temp_v1 + ((f32) (*(s16 *)((u8 *)arg1 + 0xE) - temp_v1) * temp_fv0));
    {
        s16 temp_a3 = *(s16 *)((u8 *)arg0 + 0x10);
    *(s16 *)((u8 *)arg2 + 0x10) = (s16) (s32) ((f32) temp_a3 + ((f32) (*(s16 *)((u8 *)arg1 + 0x10) - temp_a3) * temp_fv0));
    return arg2 + 0x14;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151856A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_151856A8.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151857B0 CURRENT (510) */
s32 func_151857B0(void *arg0) {
    s32 var_v0;

    var_v0 = 0;
    if (*(f32 *)((u8 *)arg0 + 4) < -*(f32 *)((u8 *)arg0 + 8)) {
        var_v0 = 1;
    }
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151857B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_151857B0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151857DC CURRENT (1695) */
void *func_151857DC(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_a3;
    s16 temp_v0;
    s16 temp_v1;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 8);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0);
    temp_fa1 = *(f32 *)((u8 *)arg1 + 0) - temp_fa0;
    temp_fv0 = (temp_fv1 - temp_fa0) / (temp_fa1 - (*(f32 *)((u8 *)arg1 + 8) - temp_fv1));
    *(f32 *)((u8 *)arg2 + 0) = (f32) (temp_fa0 + (temp_fa1 * temp_fv0));
    {
        f32 temp_ft4 = *(f32 *)((u8 *)arg0 + 4);
    *(f32 *)((u8 *)arg2 + 8) = (f32) *(f32 *)((u8 *)arg2 + 0);
    *(f32 *)((u8 *)arg2 + 4) = (f32) (temp_ft4 + ((*(f32 *)((u8 *)arg1 + 4) - temp_ft4) * temp_fv0));
    temp_v0 = *(s16 *)((u8 *)arg0 + 0xC);
    *(s16 *)((u8 *)arg2 + 0xC) = (s16) (s32) ((f32) temp_v0 + ((f32) (*(s16 *)((u8 *)arg1 + 0xC) - temp_v0) * temp_fv0));
    temp_v1 = *(s16 *)((u8 *)arg0 + 0xE);
    *(s16 *)((u8 *)arg2 + 0xE) = (s16) (s32) ((f32) temp_v1 + ((f32) (*(s16 *)((u8 *)arg1 + 0xE) - temp_v1) * temp_fv0));
    temp_a3 = *(s16 *)((u8 *)arg0 + 0x10);
    *(s16 *)((u8 *)arg2 + 0x10) = (s16) (s32) ((f32) temp_a3 + ((f32) (*(s16 *)((u8 *)arg1 + 0x10) - temp_a3) * temp_fv0));
    return arg2 + 0x14;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151857DC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_151857DC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151858D4 CURRENT (510) */
s32 func_151858D4(void *arg0) {
    s32 var_v0;

    var_v0 = 0;
    if (*(f32 *)((u8 *)arg0 + 8) < *(f32 *)((u8 *)arg0 + 0)) {
        var_v0 = 1;
    }
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151858D4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_151858D4.s")
extern f32 D_800D3688;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151858FC CURRENT (855) */
void *func_151858FC(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_v0;
    s16 temp_v1_2;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 8);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0);
    temp_fv0 = (D_800D3688 - temp_fv1) / (*(f32 *)((u8 *)arg1 + 8) - temp_fv1);
    *(f32 *)((u8 *)arg2 + 0) = (f32) (temp_fa0 + ((*(f32 *)((u8 *)arg1 + 0) - temp_fa0) * temp_fv0));
    temp_fa1 = *(f32 *)((u8 *)arg0 + 4);
    *(f32 *)((u8 *)arg2 + 4) = (f32) (temp_fa1 + ((*(f32 *)((u8 *)arg1 + 4) - temp_fa1) * temp_fv0));
    *(f32 *)((u8 *)arg2 + 8) = (f32) D_800D3688;
    temp_v0 = *(s16 *)((u8 *)arg0 + 0xC);
    *(s16 *)((u8 *)arg2 + 0xC) = (s16) (s32) ((f32) temp_v0 + ((f32) (*(s16 *)((u8 *)arg1 + 0xC) - temp_v0) * temp_fv0));
    {
        s16 temp_v1 = *(s16 *)((u8 *)arg0 + 0xE);
    *(s16 *)((u8 *)arg2 + 0xE) = (s16) (s32) ((f32) temp_v1 + ((f32) (*(s16 *)((u8 *)arg1 + 0xE) - temp_v1) * temp_fv0));
    temp_v1_2 = *(s16 *)((u8 *)arg0 + 0x10);
    *(s16 *)((u8 *)arg2 + 0x10) = (s16) (s32) ((f32) temp_v1_2 + ((f32) (*(s16 *)((u8 *)arg1 + 0x10) - temp_v1_2) * temp_fv0));
    return arg2 + 0x14;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151858FC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_151858FC.s")
extern f32 D_800D3688;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151859FC CURRENT (510) */
s32 func_151859FC(void *arg0) {
    s32 var_v0;

    var_v0 = 0;
    if (D_800D3688 < *(f32 *)((u8 *)arg0 + 8)) {
        var_v0 = 1;
    }
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151859FC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_151859FC.s")
extern f32 D_800D368C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15185A28 CURRENT (855) */
void *func_15185A28(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_v0;
    s16 temp_v1_2;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 8);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0);
    temp_fv0 = (D_800D368C - temp_fv1) / (*(f32 *)((u8 *)arg1 + 8) - temp_fv1);
    *(f32 *)((u8 *)arg2 + 0) = (f32) (temp_fa0 + ((*(f32 *)((u8 *)arg1 + 0) - temp_fa0) * temp_fv0));
    temp_fa1 = *(f32 *)((u8 *)arg0 + 4);
    *(f32 *)((u8 *)arg2 + 4) = (f32) (temp_fa1 + ((*(f32 *)((u8 *)arg1 + 4) - temp_fa1) * temp_fv0));
    *(f32 *)((u8 *)arg2 + 8) = (f32) D_800D368C;
    temp_v0 = *(s16 *)((u8 *)arg0 + 0xC);
    *(s16 *)((u8 *)arg2 + 0xC) = (s16) (s32) ((f32) temp_v0 + ((f32) (*(s16 *)((u8 *)arg1 + 0xC) - temp_v0) * temp_fv0));
    {
        s16 temp_v1 = *(s16 *)((u8 *)arg0 + 0xE);
    *(s16 *)((u8 *)arg2 + 0xE) = (s16) (s32) ((f32) temp_v1 + ((f32) (*(s16 *)((u8 *)arg1 + 0xE) - temp_v1) * temp_fv0));
    temp_v1_2 = *(s16 *)((u8 *)arg0 + 0x10);
    *(s16 *)((u8 *)arg2 + 0x10) = (s16) (s32) ((f32) temp_v1_2 + ((f32) (*(s16 *)((u8 *)arg1 + 0x10) - temp_v1_2) * temp_fv0));
    return arg2 + 0x14;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15185A28 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15185A28.s")
extern f32 D_800D368C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15185B28 CURRENT (510) */
s32 func_15185B28(void *arg0) {
    s32 var_v0;

    var_v0 = 0;
    if (*(f32 *)((u8 *)arg0 + 8) < D_800D368C) {
        var_v0 = 1;
    }
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15185B28 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15185B28.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15185B54 CURRENT (1645) */
void *func_15185B54(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_v0;
    s16 temp_v1_2;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 0);
    *(f32 *)((u8 *)arg2 + 0) = 0.0f;
    temp_fa0 = *(f32 *)((u8 *)arg0 + 4);
    temp_fv0 = temp_fv1 / (temp_fv1 - *(f32 *)((u8 *)arg1 + 0));
    *(f32 *)((u8 *)arg2 + 4) = (f32) (temp_fa0 + ((*(f32 *)((u8 *)arg1 + 4) - temp_fa0) * temp_fv0));
    temp_fa1 = *(f32 *)((u8 *)arg0 + 8);
    *(f32 *)((u8 *)arg2 + 8) = (f32) (temp_fa1 + ((*(f32 *)((u8 *)arg1 + 8) - temp_fa1) * temp_fv0));
    temp_v0 = *(s16 *)((u8 *)arg0 + 0xC);
    *(s16 *)((u8 *)arg2 + 0xC) = (s16) (s32) ((f32) temp_v0 + ((f32) (*(s16 *)((u8 *)arg1 + 0xC) - temp_v0) * temp_fv0));
    {
        s16 temp_v1 = *(s16 *)((u8 *)arg0 + 0xE);
    *(s16 *)((u8 *)arg2 + 0xE) = (s16) (s32) ((f32) temp_v1 + ((f32) (*(s16 *)((u8 *)arg1 + 0xE) - temp_v1) * temp_fv0));
    temp_v1_2 = *(s16 *)((u8 *)arg0 + 0x10);
    *(s16 *)((u8 *)arg2 + 0x10) = (s16) (s32) ((f32) temp_v1_2 + ((f32) (*(s16 *)((u8 *)arg1 + 0x10) - temp_v1_2) * temp_fv0));
    return arg2 + 0x14;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15185B54 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15185B54.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15185C44 CURRENT (510) */
s32 func_15185C44(f32 *arg0) {
    s32 var_v0;

    var_v0 = 0;
    if (*arg0 <= 0.0f) {
        var_v0 = 1;
    }
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15185C44 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15185C44.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15185C6C CURRENT (1645) */
void *func_15185C6C(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_v0;
    s16 temp_v1_2;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 4);
    *(f32 *)((u8 *)arg2 + 4) = 0.0f;
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0);
    temp_fv0 = temp_fv1 / (temp_fv1 - *(f32 *)((u8 *)arg1 + 4));
    *(f32 *)((u8 *)arg2 + 0) = (f32) (temp_fa0 + ((*(f32 *)((u8 *)arg1 + 0) - temp_fa0) * temp_fv0));
    temp_fa1 = *(f32 *)((u8 *)arg0 + 8);
    *(f32 *)((u8 *)arg2 + 8) = (f32) (temp_fa1 + ((*(f32 *)((u8 *)arg1 + 8) - temp_fa1) * temp_fv0));
    temp_v0 = *(s16 *)((u8 *)arg0 + 0xC);
    *(s16 *)((u8 *)arg2 + 0xC) = (s16) (s32) ((f32) temp_v0 + ((f32) (*(s16 *)((u8 *)arg1 + 0xC) - temp_v0) * temp_fv0));
    {
        s16 temp_v1 = *(s16 *)((u8 *)arg0 + 0xE);
    *(s16 *)((u8 *)arg2 + 0xE) = (s16) (s32) ((f32) temp_v1 + ((f32) (*(s16 *)((u8 *)arg1 + 0xE) - temp_v1) * temp_fv0));
    temp_v1_2 = *(s16 *)((u8 *)arg0 + 0x10);
    *(s16 *)((u8 *)arg2 + 0x10) = (s16) (s32) ((f32) temp_v1_2 + ((f32) (*(s16 *)((u8 *)arg1 + 0x10) - temp_v1_2) * temp_fv0));
    return arg2 + 0x14;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15185C6C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15185C6C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15185D5C CURRENT (510) */
s32 func_15185D5C(void *arg0) {
    s32 var_v0;

    var_v0 = 0;
    if (*(f32 *)((u8 *)arg0 + 4) <= 0.0f) {
        var_v0 = 1;
    }
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15185D5C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15185D5C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15185D84 CURRENT (510) */
s32 func_15185D84(f32 *arg0) {
    s32 var_v0;

    var_v0 = 0;
    if (*arg0 > 0.0f) {
        var_v0 = 1;
    }
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15185D84 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15185D84.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15185DAC CURRENT (510) */
s32 func_15185DAC(void *arg0) {
    s32 var_v0;

    var_v0 = 0;
    if (*(f32 *)((u8 *)arg0 + 4) > 0.0f) {
        var_v0 = 1;
    }
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15185DAC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15185DAC.s")
typedef struct {
    s32 words[5];
} Game1B1600Record;

extern Game1B1600Record *(*D_8008D498[])(Game1B1600Record *, Game1B1600Record *, Game1B1600Record *);
extern s32 (*D_8008D4C0[])(Game1B1600Record *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15185DD4 CURRENT (724) */
Game1B1600Record *func_15185DD4(Game1B1600Record *arg0, s32 arg1, s32 arg2,
                                  Game1B1600Record *arg3) {
    s32 (*predicate)(Game1B1600Record *);
    Game1B1600Record *(*combine)(Game1B1600Record *, Game1B1600Record *, Game1B1600Record *);
    Game1B1600Record *previous;
    Game1B1600Record *current;
    Game1B1600Record *out;
    s32 index;

    out = arg3;
    previous = arg0 + arg1 - 1;
    combine = D_8008D498[arg2];
    predicate = D_8008D4C0[arg2];
    current = arg0;
    index = 0;
    if (arg1 > 0) {
        do {
            if (predicate(current) != 0) {
                if (predicate(previous) != 0) {
                    out++;
                    out[-1] = *current;
                } else {
                    Game1B1600Record *merged = combine(previous, current, out);
                    out = merged;
                    *out++ = *current;
                }
            } else if (predicate(previous) != 0) {
                out = combine(previous, current, out);
            }
            index++;
            previous = current;
            current++;
        } while (index != arg1);
    }
    return out;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15185DD4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15185DD4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15185F24.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_1518652C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_15186794.s")
extern s32 D_800DE01C;
extern s32 D_800DE020;
extern s32 D_800DE024;
extern s32 D_800DE030;
extern s32 D_800DE034;
extern s32 D_800DE038;
extern f32 D_800DE03C;
extern s8 D_800DE040;
extern s8 D_800DE041;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151872B0 CURRENT (135) */
void func_151872B0(s32 arg0) {
    D_800DE01C = 0x258;
    D_800DE020 = 0xB4;
    D_800DE024 = 0x5A;
    D_800DE030 = 0x3F8;
    D_800DE034 = 0;
    D_800DE038 = 1;
    D_800DE03C = 1.0f;
    D_800DE040 = 1;
    D_800DE041 = 1;
    switch (arg0) {                                 /* irregular */
    case 33:
        D_800DE01C = 0x12C0;
        D_800DE020 = 0x12BF;
        D_800DE024 = 0x12BE;
        D_800DE030 = 0x3F2;
        D_800DE034 = 1;
        D_800DE038 = 4;
        D_800DE040 = 0;
        return;
    case 34:
        D_800DE01C = 0x960;
        D_800DE020 = 0x95F;
        D_800DE024 = 0x95E;
        D_800DE038 = 4;
        D_800DE040 = 0;
        return;
    case 20:
        D_800DE041 = 0;
        return;
    case 41:
        D_800DE01C = 0x4B0;
        D_800DE020 = 0x258;
        D_800DE024 = 0x12C;
        return;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151872B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_151872B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B1600/func_151873E4.s")
