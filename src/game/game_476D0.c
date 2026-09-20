#include "types.h"

/*
 * Reviewed source unit: src/game/game_476D0.c
 * Boundary evidence: docs/evidence/game_early_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1501A220
 * - func_1501A39C
 * - func_1501A490
 * - func_1501A680
 * - func_1501A6CC
 * - func_1501A764
 * - func_1501A8C0
 * - func_1501AE94
 * - func_1501B0A0
 * - func_1501B22C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501A220.s")
extern u8 D_8002C930;
extern s32 D_800BE9C4;
extern s32 D_800BE628;
extern void *D_800BE9C8;
extern void *D_800BE9D8;
extern void *D_800BE9E0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501A39C CURRENT (6192) */
void func_1501A39C(void) {
    void **var_t3;
    s32 var_t2;
    void **var_v1;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_5;

    var_t3 = &D_800BE9D8;
    var_v1 = &D_800BE9C8;
    var_t2 = 0;
    do {
        temp_v0 = *var_v1;
        *(u32 *)((u8 *)temp_v0 + 0) = 0xDB060000;
        *(u32 *)((u8 *)temp_v0 + 4) = 0;
        temp_v0_2 = (u8 *)temp_v0 + 8;
        *(u32 *)((u8 *)temp_v0_2 + 0) = 0xDB060000;
        *(u32 *)((u8 *)temp_v0_2 + 4) = 0;
        temp_v0_3 = (u8 *)temp_v0_2 + 8;
        *(u32 *)((u8 *)temp_v0_3 + 0) = 0xDE000000;
        *(u32 *)((u8 *)temp_v0_3 + 4) = (u32)&D_8002C930;
        temp_v0_4 = (u8 *)temp_v0_3 + 8;
        *(u32 *)((u8 *)temp_v0_4 + 0) = 0xFE000000;
        temp_v0_5 = (u8 *)temp_v0_4 + 8;
        *(u32 *)((u8 *)temp_v0_4 + 4) = D_800BE9C4;
        *(u32 *)((u8 *)temp_v0_5 + 0) = 0xDC080008;
        var_v1++;
        *(u32 *)((u8 *)temp_v0_5 + 4) = D_800BE628 + var_t2 + 0x40;
        var_t3++;
        var_t2 += 0x10;
        var_t3[-1] = (u8 *)temp_v0_5 + 8;
    } while (var_t3 != &D_800BE9E0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501A39C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501A39C.s")
/* Call context: func_1501AF44: unique active project prototype */
void func_1501AF44(f32 *, f32 *, f32 *, f32 *);
extern s32 D_800BE620;
extern s32 D_800BE624;
extern s32 D_800BE628;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501A490 CURRENT (2115) */
void *func_1501A490(u8 *arg0, s16 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 temp_fv0;
    f32 temp_fv1;
    u8 *temp_v0;
    void *var_s0;

    *(s32 *)((u8 *)arg0 + 0) = 0xE7000000;
    *(s32 *)((u8 *)arg0 + 4) = 0;
    {
        u8 * temp_s0 = (void *)(arg0 + 8);
    if (arg1 == 0xFF) {
        *(s32 *)((u8 *)arg0 + 8) = 0xED008000;
        var_s0 = (void *)(temp_s0 + 8);
        *(s32 *)((u8 *)temp_s0 + 4) = (s32) (((arg5 & 3) << 0x18) | (((s32) ((f32) (D_800BE620 - 2) * 4.0f) & 0xFFF) << 0xC) | ((s32) ((f32) D_800BE624 * 4.0f) & 0xFFF));
    } else {
        temp_v0 = (void *)(D_800BE628 + (arg1 * 0x180));
        sp3C = *(f32 *)((u8 *)temp_v0 + 0x2C);
        sp38 = *(f32 *)((u8 *)temp_v0 + 0x30);
        sp34 = *(f32 *)((u8 *)temp_v0 + 0x24);
        if (arg4 != 0) {
            temp_fv1 = *(f32 *)((u8 *)temp_v0 + 0x28);
            temp_fv0 = (f32) arg4;
            if (temp_fv0 < temp_fv1) {
                sp30 = temp_fv0;
            } else {
                sp30 = temp_fv1;
            }
        } else {
            sp30 = *(f32 *)((u8 *)temp_v0 + 0x28);
        }
        func_1501AF44(&sp3C, &sp34, &sp38, &sp30);
        var_s0 = (void *)(temp_s0 + 8);
        *(s32 *)((u8 *)arg0 + 8) = (s32) ((((s32) (sp3C * 4.0f) & 0xFFF) << 0xC) | 0xED000000 | ((s32) (sp34 * 4.0f) & 0xFFF));
        *(s32 *)((u8 *)temp_s0 + 4) = (s32) (((arg5 & 3) << 0x18) | (((s32) (sp38 * 4.0f) & 0xFFF) << 0xC) | ((s32) (sp30 * 4.0f) & 0xFFF));
    }
    return var_s0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501A490 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501A490.s")
extern s32 D_8002AAE8[];
extern u8 D_800BE9C0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501A680 CURRENT (275) */
void *func_1501A680(void *arg0) {
    *(s32 *)((u8 *)arg0 + 0) = ((D_800BE620 - 1) & 0xFFF) | 0xFF100000;
    *(s32 *)((u8 *)arg0 + 4) = D_8002AAE8[D_800BE9C0];
    return (u8 *)arg0 + 8;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501A680 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501A680.s")
extern s32 D_800BE620;
extern s32 D_800BE624;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501A6CC CURRENT (2375) */
void *func_1501A6CC(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_v0;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;
    u8 *temp_a0;

    var_a1 = arg1;
    var_a2 = arg2;
    var_a3 = arg3;
    if (var_a1 < 3) {
        var_a1 = 2;
    }
    {
        s32 var_v1 = arg4;
    if (var_a2 <= 0) {
        var_a2 = 0;
    }
    temp_a0 = arg0;
    temp_v0 = D_800BE620 - 2;
    if (var_a3 >= temp_v0) {
        var_a3 = temp_v0;
    }
    if (var_v1 >= D_800BE624) {
        var_v1 = D_800BE624;
    }
    arg0 = (void *)(temp_a0 + 8);
    *(s32 *)((u8 *)temp_a0 + 4) = (s32) (((var_a1 & 0x3FF) << 0xE) | ((var_a2 & 0x3FF) * 4));
    *(s32 *)((u8 *)temp_a0 + 0) = (s32) (((var_a3 & 0x3FF) << 0xE) | 0xF6000000 | ((var_v1 & 0x3FF) * 4));
    return arg0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501A6CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501A6CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501A764.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501A8C0.s")
extern s32 D_800BE620;
extern s32 D_800BE624;
extern s32 D_800BE628;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501AE94 CURRENT (1670) */
s32 func_1501AE94(s32 arg0) {
    void *temp_v0;

    temp_v0 = D_800BE628 + (arg0 * 0x180);
    if ((*(f32 *)((u8 *)temp_v0 + 0x2C) < 2.0f) || (((f32) D_800BE620 - 2.0f) < *(f32 *)((u8 *)temp_v0 + 0x30))) {
        return 0;
    }
    if ((*(f32 *)((u8 *)temp_v0 + 0x24) < 0.0f) || ((f32) D_800BE624 < *(f32 *)((u8 *)temp_v0 + 0x28))) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501AE94 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501AE94.s")
void func_1501AF44(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv0_4;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 temp_fv1_3;
    f32 temp_fv1_4;
    f32 var_fa0;
    f32 var_fa0_2;
    f32 var_fa0_3;
    f32 var_fa0_4;

    temp_fv0 = *arg0;
    if (temp_fv0 < 2.0f) {
        *arg0 = 2.0f;
    } else {
        temp_fv1 = (f32) D_800BE620 - 2.0f;
        if (temp_fv1 < temp_fv0) {
            var_fa0 = temp_fv1;
        } else {
            var_fa0 = temp_fv0;
        }
        *arg0 = var_fa0;
    }
    temp_fv0_2 = *arg2;
    if (temp_fv0_2 < 2.0f) {
        *arg2 = 2.0f;
    } else {
        temp_fv1_2 = (f32) D_800BE620 - 2.0f;
        if (temp_fv1_2 < temp_fv0_2) {
            var_fa0_2 = temp_fv1_2;
        } else {
            var_fa0_2 = temp_fv0_2;
        }
        *arg2 = var_fa0_2;
    }
    temp_fv0_3 = *arg1;
    if (temp_fv0_3 < 0.0f) {
        *arg1 = 0.0f;
    } else {
        temp_fv1_3 = (f32) D_800BE624;
        if (temp_fv1_3 < temp_fv0_3) {
            var_fa0_3 = temp_fv1_3;
        } else {
            var_fa0_3 = temp_fv0_3;
        }
        *arg1 = var_fa0_3;
    }
    temp_fv0_4 = *arg3;
    if (temp_fv0_4 < 0.0f) {
        *arg3 = 0.0f;
        return;
    }
    temp_fv1_4 = (f32) D_800BE624;
    if (temp_fv1_4 < temp_fv0_4) {
        var_fa0_4 = temp_fv1_4;
    } else {
        var_fa0_4 = temp_fv0_4;
    }
    *arg3 = var_fa0_4;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501B0A0.s")
f32 func_15047C00(f32);
f32 func_15047D60(f32);
extern f32 D_80096900;
extern f32 D_80096904;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501B22C CURRENT (1139) */
void func_1501B22C(s32 arg0) {
    f32 sp34;
    f32 sp28;
    f32 sp24;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fa0_3;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fv1_2;
    u8 *temp_s0;

    temp_s0 = (u8 *)D_800BE628 + (arg0 * 0x180);
    temp_fa0 = -(*(f32 *)(temp_s0 + 0x74) * 0.5f) * D_80096900;
    sp28 = *(f32 *)(temp_s0 + 0x78) * 0.5f;
    sp24 = temp_fa0;
    sp34 = func_15047C00(sp24);
    temp_fv0 = func_15047D60(sp24);
    *(f32 *)(temp_s0 + 0x9C) = temp_fv0;
    temp_fv1 = -sp34;
    *(f32 *)(temp_s0 + 0x90) = temp_fv0;
    *(f32 *)(temp_s0 + 0x94) = temp_fv1;
    *(f32 *)(temp_s0 + 0x88) = -temp_fv1;
    *(f32 *)(temp_s0 + 0x98) = 0.0f;
    *(f32 *)(temp_s0 + 0x8C) = 0.0f;
    temp_fa0_2 = sp28 * D_80096904;
    sp24 = temp_fa0_2;
    sp34 = func_15047C00(sp24);
    temp_fa0_3 = -func_15047D60(sp24);
    *(f32 *)(temp_s0 + 0xA0) = 0.0f;
    *(f32 *)(temp_s0 + 0xA8) = temp_fa0_3;
    *(f32 *)(temp_s0 + 0xB4) = temp_fa0_3;
    temp_fv1_2 = -sp34;
    *(f32 *)(temp_s0 + 0xAC) = 0.0f;
    *(f32 *)(temp_s0 + 0xA4) = temp_fv1_2;
    *(f32 *)(temp_s0 + 0xB0) = -temp_fv1_2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501B22C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501B22C.s")
