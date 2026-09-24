#include "types.h"

/*
 * Reviewed source unit: src/game/effects/holtenrope.c
 * Boundary evidence: docs/evidence/game_beta_camera_rope_bee.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B32C8
 * - func_151B3A7C
 * - func_151B3CF0
 * - func_151B3F28
 * - func_151B3FDC
 * - func_151B42A4
 * - func_151B47D8
 * - func_151B48DC
 * - func_151B4A14
 * - func_151B4B78
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct HoltenRopeEffect {
    u8 pad0[0x10];
    u8 flags;
    u8 pad11;
    s16 timer;
    u8 primaryState[0xC];
    u8 secondaryState[0xC];
    s8 primaryCallback;
    s8 secondaryCallback;
    u8 pad2E[6];
    s8 updateCallback;
    u8 pad35[3];
    f32 radius;
    u8 pad3C[0xFC];
    f32 doubledRadiusSquared;
    s32 scaledRadius;
    u8 resetState[1];
} HoltenRopeEffect;

typedef s32 (*HoltenRopeStateCallback)(HoltenRopeEffect *, void *, s32);
typedef s32 (*HoltenRopeUpdateCallback)(HoltenRopeEffect *);

void func_100226F0(void *, s32);
void func_10022EC0(void *, void *, s32);
HoltenRopeEffect *func_15167A68(s32, s32, s32, s32, s32, s32);
extern f32 D_800AA390;
extern s32 D_800BE9E4;
extern HoltenRopeStateCallback D_8008FAF0[];
extern HoltenRopeUpdateCallback D_8008FAF8[];

HoltenRopeEffect *func_151B30B0(void *arg0, f32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    HoltenRopeEffect *result;
    f32 radius;

    result = func_15167A68(0x33, arg4, arg2 + 0x150, 1, arg3, 1);
    if (result == 0) {
        return 0;
    }
    func_10022EC0(&result->flags, arg0, 0x38);
    radius = result->radius;
    result->flags |= 0xE;
    result->doubledRadiusSquared = 2.0f * ((radius * radius) / D_800AA390);
    result->scaledRadius = (s32)(radius * arg1 * 4096.0f);
    func_100226F0(result->resetState, 0x10);
    return result;
}
void func_1516972C(HoltenRopeEffect *);

void func_151B3184(HoltenRopeEffect *arg0) {
    s32 callback;
    u8 finished = 0;

    if (arg0->flags & 1) {
        arg0->timer -= D_800BE9E4;
        if (arg0->timer < 0) {
            finished = 1;
        }
    }
    if (finished == 0) {
        callback = arg0->primaryCallback;
        if (callback != -1) {
            if (D_8008FAF0[callback](arg0, arg0->primaryState, 1) == 0) {
                finished = 1;
            }
        }
        callback = arg0->secondaryCallback;
        if (callback != -1) {
            if (D_8008FAF0[callback](arg0, arg0->secondaryState, 0) == 0) {
                finished = 1;
            }
        }
        if ((arg0->flags & 4) || (arg0->flags & 8)) {
            arg0->flags |= 2;
        } else {
            callback = arg0->updateCallback;
            if (callback != -1) {
                if (D_8008FAF8[callback](arg0) == 0) {
                    finished = 1;
                }
            }
        }
    }
    if (finished != 0) {
        func_1516972C(arg0);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/holtenrope/func_151B32C8.s")
extern void (*D_8008FB68[])(void *, s32, u8);

void func_151B3A34(void *arg0, s32 arg1, u8 arg2) {
    void (*temp_v0)(void *, s32, u8);

    temp_v0 = D_8008FB68[*(u8 *)((u8 *)arg0 + 0x44)];
    if (temp_v0 != 0) {
        temp_v0(arg0, arg1, arg2);
    }
}
extern f32 D_800AA394;
extern f32 D_800AA398;
extern f32 D_800AA39C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B3A7C CURRENT (21743) */
s32 func_151B3A7C(u8 *arg0) {
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 *var_a2;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_ft5;
    s32 var_v0;
    u8 *var_a3;
    u8 *var_t0;
    u8 *var_v1;

    *(f32 *)((u8 *)&sp44 + 0) = *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)((u8 *)&sp44 + 4) = (f32) *(f32 *)((u8 *)arg0 + 0x18);
    var_v1 = (void *)(arg0 + 0x30);
    *(f32 *)((u8 *)&sp44 + 8) = (f32) *(f32 *)((u8 *)arg0 + 0x1C);
    {
        u8 * var_a1 = (void *)(var_v1 + 0x48);
    var_a2 = (void *)(var_v1 + 0x60);
    *(f32 *)((u8 *)arg0 + 0x48) = (f32) *(f32 *)((u8 *)&sp44 + 0);
    var_a3 = (void *)(var_v1 + 0x78);
    var_t0 = (void *)(var_v1 + 0x90);
    *(f32 *)((u8 *)arg0 + 0x4C) = (f32) *(f32 *)((u8 *)&sp44 + 4);
    *(f32 *)((u8 *)arg0 + 0x5C) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x58) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x50) = (f32) *(f32 *)((u8 *)&sp44 + 8);
    *(f32 *)((u8 *)arg0 + 0x54) = 0.0f;
    temp_fa1 = (*(f32 *)((u8 *)arg0 + 0x20) - *(f32 *)((u8 *)arg0 + 0x14)) * D_800AA394;
    temp_ft4 = (*(f32 *)((u8 *)arg0 + 0x24) - *(f32 *)((u8 *)arg0 + 0x18)) * D_800AA398;
    var_v0 = 2;
    sp44 += temp_fa1;
    sp48 += temp_ft4;
    temp_ft5 = (*(f32 *)((u8 *)arg0 + 0x28) - *(f32 *)((u8 *)arg0 + 0x1C)) * D_800AA39C;
    sp4C += temp_ft5;
    *(f32 *)((u8 *)arg0 + 0x60) = (f32) *(f32 *)((u8 *)&sp44 + 0);
    *(f32 *)((u8 *)arg0 + 0x64) = (f32) *(f32 *)((u8 *)&sp44 + 4);
    *(f32 *)((u8 *)arg0 + 0x74) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x70) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x6C) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x68) = (f32) *(f32 *)((u8 *)&sp44 + 8);
    sp44 += temp_fa1;
    sp48 += temp_ft4;
    sp4C += temp_ft5;
    do {
        *(f32 *)((u8 *)var_a1 + 0) = (f32) *(f32 *)((u8 *)&sp44 + 0);
        *(f32 *)((u8 *)var_a1 + 4) = (f32) *(f32 *)((u8 *)&sp44 + 4);
        *(f32 *)((u8 *)var_a1 + 8) = (f32) *(f32 *)((u8 *)&sp44 + 8);
        *(f32 *)((u8 *)var_v1 + 0x54) = 0.0f;
        *(f32 *)((u8 *)var_v1 + 0x58) = 0.0f;
        *(f32 *)((u8 *)var_v1 + 0x5C) = 0.0f;
        sp44 += temp_fa1;
        sp48 += temp_ft4;
        sp4C += temp_ft5;
        var_v0 += 4;
        var_v1 += 0x60;
        *var_a2 = *(f32 *)((u8 *)&sp44 + 0);
        var_a1 += 0x60;
        var_a2 += 0x60;
        *(f32 *)((u8 *)var_a2 + -0x5C) = (f32) *(f32 *)((u8 *)&sp44 + 4);
        var_a3 += 0x60;
        var_t0 += 0x60;
        *(f32 *)((u8 *)var_a2 + -0x58) = (f32) *(f32 *)((u8 *)&sp44 + 8);
        *(f32 *)((u8 *)var_v1 + 0x14) = 0.0f;
        *(f32 *)((u8 *)var_v1 + 0x10) = 0.0f;
        *(f32 *)((u8 *)var_v1 + 0xC) = 0.0f;
        sp44 += temp_fa1;
        sp48 += temp_ft4;
        sp4C += temp_ft5;
        *(f32 *)((u8 *)var_a3 + -0x60) = (f32) *(f32 *)((u8 *)&sp44 + 0);
        *(f32 *)((u8 *)var_a3 + -0x5C) = (f32) *(f32 *)((u8 *)&sp44 + 4);
        *(f32 *)((u8 *)var_a3 + -0x58) = (f32) *(f32 *)((u8 *)&sp44 + 8);
        *(f32 *)((u8 *)var_v1 + 0x2C) = 0.0f;
        *(f32 *)((u8 *)var_v1 + 0x28) = 0.0f;
        *(f32 *)((u8 *)var_v1 + 0x24) = 0.0f;
        sp44 += temp_fa1;
        sp48 += temp_ft4;
        sp4C += temp_ft5;
        *(f32 *)((u8 *)var_t0 + -0x60) = (f32) *(f32 *)((u8 *)&sp44 + 0);
        *(f32 *)((u8 *)var_t0 + -0x5C) = (f32) *(f32 *)((u8 *)&sp44 + 4);
        *(f32 *)((u8 *)var_t0 + -0x58) = (f32) *(f32 *)((u8 *)&sp44 + 8);
        *(f32 *)((u8 *)var_v1 + 0x44) = 0.0f;
        *(f32 *)((u8 *)var_v1 + 0x40) = 0.0f;
        *(f32 *)((u8 *)var_v1 + 0x3C) = 0.0f;
        sp44 += temp_fa1;
        sp48 += temp_ft4;
        sp4C += temp_ft5;
    } while (var_v0 != 0xA);
    *(u8 *)((u8 *)arg0 + 0x10) = (u8) (*(u8 *)((u8 *)arg0 + 0x10) & 0xFFFD);
    return 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B3A7C */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/holtenrope/func_151B3A7C.s")
/* Call context: func_15047D60: unique active project prototype */
/* Call context: func_150484A0: unique active project prototype */
f32 func_15047D60(f32);
f32 func_150484A0(f32, f32);
f32 func_15047C00(f32);                             /* extern */
extern f32 D_800AA3A0;
extern f32 D_800AA3A4;
extern f32 D_800AA3A8;
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B3CF0 CURRENT (9877) */
s32 func_151B3CF0(u8 *arg0) {
    f32 sp80;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fa1_2;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs1_2;
    f32 temp_fs1_3;
    f32 temp_fs2;
    f32 temp_fs2_2;
    f32 temp_fs2_3;
    f32 temp_fs3;
    f32 temp_fs3_2;
    f32 temp_fs4;
    f32 temp_fs4_2;
    f32 temp_fs5;
    f32 temp_fs5_2;
    f32 temp_ft0;
    f32 temp_ft1;
    f32 temp_ft3;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fs0;
    s32 var_s1;
    u8 *temp_s0;
    u8 *var_s2;

    temp_fs3 = *(f32 *)((u8 *)arg0 + 0x20);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x14);
    temp_fs4 = *(f32 *)((u8 *)arg0 + 0x24);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x18);
    temp_ft5 = temp_fs3 - temp_fv1;
    temp_fv0 = fabsf(temp_ft5);
    sp80 = temp_fs4 - temp_fa0;
    temp_fa1 = *(f32 *)((u8 *)arg0 + 0x1C);
    temp_fs5 = *(f32 *)((u8 *)arg0 + 0x28);
    temp_fs0 = temp_fs5 - temp_fa1;
    if ((D_800AA3A0 < temp_fv0) || (D_800AA3A0 < fabsf(temp_fs0))) {
        temp_ft4 = temp_fv1 + (temp_ft5 * 0.5f);
        sp70 = temp_ft4;
        temp_ft0 = temp_fv1 - temp_ft4;
        temp_fs1 = temp_fa0 + (sp80 * 0.5f);
        sp64 = temp_ft0;
        temp_fs2 = temp_fa1 + (temp_fs0 * 0.5f);
        sp74 = temp_fs1;
        temp_ft3 = temp_fs3 - temp_ft4;
        sp78 = temp_fs2;
        sp58 = temp_ft3;
        sp6C = temp_fa1 - temp_fs2;
        sp5C = temp_fs4 - temp_fs1;
        sp68 = temp_fa0 - temp_fs1;
        temp_ft1 = temp_fs5 - temp_fs2;
        sp60 = temp_ft1;
        temp_fs1_2 = 1.0f / sqrtf((temp_ft5 * temp_ft5) + (temp_fs0 * temp_fs0));
        temp_fs3_2 = temp_fs0 * temp_fs1_2;
        temp_fs4_2 = temp_ft5 * temp_fs1_2;
        temp_fa1_2 = ((temp_ft1 * temp_fs3_2) + (temp_ft3 * temp_fs4_2)) - ((sp6C * temp_fs3_2) + (temp_ft0 * temp_fs4_2));
        temp_fs2_2 = sp5C - sp68;
        temp_fs5_2 = D_800AA3A8;
        var_s1 = 0;
        var_s2 = (void *)(arg0 + 0x48);
        var_fs0 = func_150484A0(temp_fs2_2, temp_fa1_2) - D_800AA3A4;
        temp_fs1_3 = sqrtf((temp_fa1_2 * temp_fa1_2) + (temp_fs2_2 * temp_fs2_2)) * 0.5f;
        do {
            temp_s0 = var_s2;
            temp_fs2_3 = func_15047D60(var_fs0);
            temp_fv1_2 = temp_fs1_3 * func_15047C00(var_fs0);
            var_s1 += 0x18;
            var_s2 += 0x18;
            *(f32 *)((u8 *)temp_s0 + 0) = (f32) ((temp_fv1_2 * temp_fs4_2) + sp70);
            *(f32 *)((u8 *)temp_s0 + 4) = (f32) ((temp_fs1_3 * temp_fs2_3) + sp74);
            *(f32 *)((u8 *)temp_s0 + 8) = (f32) ((temp_fv1_2 * temp_fs3_2) + sp78);
            var_fs0 += temp_fs5_2;
        } while (var_s1 != 0xF0);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B3CF0 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/holtenrope/func_151B3CF0.s")
extern f32 D_800AA3AC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B3F28 CURRENT (1990) */
s32 func_151B3F28(void *arg0, f32 *arg1, s32 arg2) {
    void **slot;
    void *state;
    s32 result;

    result = 1;
    if ((arg2 & 0xFF) != 0) {
        slot = *(void ***)((u8 *)arg0 + 0x150);
        state = (slot != 0) ? *slot : 0;
        if ((state != 0) &&
            (*(u8 *)((u8 *)arg0 + 0x154) == *(u8 *)((u8 *)state + 0x3B))) {
            arg1[0] = *(f32 *)((u8 *)state + 0x14);
            arg1[1] = *(f32 *)((u8 *)state + 0x18);
            arg1[2] = *(f32 *)((u8 *)state + 0x1C);
            *(u8 *)((u8 *)arg0 + 0x10) &= 0xFB;
        } else {
            result = 0;
            *(u8 *)((u8 *)arg0 + 0x10) |= 0xC;
        }
    } else {
        arg1[0] = 0.0f;
        arg1[2] = 0.0f;
        arg1[1] = D_800AA3AC;
        *(u8 *)((u8 *)arg0 + 0x10) &= 0xF7;
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B3F28 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/holtenrope/func_151B3F28.s")
/* Call context: func_15047D60: unique active project prototype */
s32 func_151B3A7C(f32, f32);                        /* extern */
extern f32 D_800AA3B0;
extern f32 D_800AA3B4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B3FDC CURRENT (13877) */
s32 func_151B3FDC(u8 *arg0) {
    f32 sp110;
    f32 sp108;
    f32 sp104;
    f32 sp100;
    f32 spFC;
    f32 spF8;
    f32 spF4;
    f32 spF0;
    f32 spEC;
    f32 spE8;
    f32 spD0;
    f32 spAC;
    f32 spA4;
    f32 sp98;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp5C;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fa1;
    f32 temp_fa1_2;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs1_2;
    f32 temp_fs2;
    f32 temp_fs3;
    f32 temp_fs3_2;
    f32 temp_fs4;
    f32 temp_fs4_2;
    f32 temp_fs5;
    f32 temp_fs5_2;
    f32 temp_ft0;
    f32 temp_ft1;
    f32 temp_ft3;
    f32 temp_ft3_2;
    f32 temp_ft4;
    f32 temp_ft4_2;
    f32 temp_ft4_3;
    f32 temp_ft5;
    f32 temp_ft5_2;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 temp_fv1_3;
    f32 temp_fv1_4;
    f32 var_fs0;
    s32 var_s1;
    u8 *var_s2;

    temp_fs4 = *(f32 *)((u8 *)arg0 + 0x20);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x14);
    temp_fs5 = *(f32 *)((u8 *)arg0 + 0x24);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x18);
    temp_fs0 = temp_fs4 - temp_fv1;
    temp_fv0 = fabsf(temp_fs0);
    sp110 = temp_fs5 - temp_fa0;
    temp_ft4 = *(f32 *)((u8 *)arg0 + 0x28);
    temp_fa1 = *(f32 *)((u8 *)arg0 + 0x1C);
    sp5C = temp_ft4;
    temp_fs3 = temp_ft4 - temp_fa1;
    if ((D_800AA3B0 < temp_fv0) || (D_800AA3B0 < fabsf(temp_fs3))) {
        temp_ft4_2 = temp_fv1 + (temp_fs0 * 0.5f);
        sp100 = temp_ft4_2;
        temp_ft5 = temp_fa0 + (sp110 * 0.5f);
        spF4 = temp_fv1 - temp_ft4_2;
        temp_fs1 = temp_fa1 + (temp_fs3 * 0.5f);
        sp104 = temp_ft5;
        sp108 = temp_fs1;
        spE8 = temp_fs4 - temp_ft4_2;
        spEC = temp_fs5 - temp_ft5;
        spF8 = temp_fa0 - temp_ft5;
        spFC = temp_fa1 - temp_fs1;
        temp_ft3 = sp5C - temp_fs1;
        temp_fv0_2 = sqrtf((temp_fs0 * temp_fs0) + (temp_fs3 * temp_fs3));
        spF0 = temp_ft3;
        temp_fv1_2 = 1.0f / temp_fv0_2;
        temp_fs4_2 = temp_fs3 * temp_fv1_2;
        temp_fs5_2 = temp_fs0 * temp_fv1_2;
        temp_ft4_3 = ((temp_ft3 * temp_fs4_2) + (spE8 * temp_fs5_2)) - ((spFC * temp_fs4_2) + (spF4 * temp_fs5_2));
        temp_ft5_2 = spEC - spF8;
        spD0 = temp_ft4_3;
        temp_ft0 = (temp_ft4_3 * temp_ft4_3) + (temp_ft5_2 * temp_ft5_2);
        temp_fv0_3 = sqrtf(temp_ft0);
        sp64 = temp_ft0;
        spA4 = temp_ft0;
        temp_fv1_3 = 1.0f / temp_fv0_3;
        spAC = temp_fv0_3 * 0.5f;
        temp_ft3_2 = *(f32 *)((u8 *)arg0 + 0x138);
        sp68 = temp_ft3_2;
        temp_fs1_2 = spD0 * temp_fv1_3;
        temp_fs2 = temp_ft5_2 * temp_fv1_3;
        temp_ft1 = temp_ft0 * 0.25f;
        sp6C = temp_ft1;
        if (temp_ft3_2 < sp6C) {
            return func_151B3A7C(temp_fa0, temp_fa1);
        }
        var_fs0 = 0.0f;
        var_s1 = 0;
        var_s2 = (void *)(arg0 + 0x48);
        sp98 = sqrtf(sp68 - temp_ft1);
        do {
            temp_fs3_2 = func_15047D60(var_fs0);
            var_s1 += 0x18;
            temp_fv1_4 = spAC * func_15047C00(var_fs0);
            temp_fa0_2 = sp98 * temp_fs3_2;
            temp_fa1_2 = (temp_fv1_4 * temp_fs1_2) - (temp_fa0_2 * temp_fs2);
            *(f32 *)((u8 *)var_s2 + 0) = (f32) ((temp_fa1_2 * temp_fs5_2) + sp100);
            *(f32 *)((u8 *)var_s2 + 4) = (f32) (((temp_fv1_4 * temp_fs2) - (temp_fa0_2 * temp_fs1_2)) + sp104);
            *(f32 *)((u8 *)var_s2 + 8) = (f32) ((temp_fa1_2 * temp_fs4_2) + sp108);
            var_s2 += 0x18;
            var_fs0 += D_800AA3B4;
        } while (var_s1 != 0xF0);
        goto block_6;
    }
block_6:
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B3FDC */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/holtenrope/func_151B3FDC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/holtenrope/func_151B42A4.s")
typedef struct {
    s32 active;
    u8 pad4[0x37];
    u8 index;
    u8 pad3C[0x198];
    s32 transform;
} HoltenRopeResource;

typedef struct {
    HoltenRopeResource *primary;
    u8 primaryIndex;
    u8 primaryOffset;
    u8 pad6[2];
    f32 primaryVector[3];
    HoltenRopeResource *secondary;
    u8 secondaryIndex;
    u8 secondaryOffset;
    u8 pad1A[2];
    f32 secondaryVector[3];
} HoltenRopePair;

void func_15143134(f32 *, f32 *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B47D8 CURRENT (645) */
s32 func_151B47D8(HoltenRopeEffect *arg0, HoltenRopePair *arg1,
                   f32 *arg2, u8 arg3) {
    s32 mask;
    f32 *input;
    s32 transform;
    void *primary;
    void *secondary;

    primary = arg1->primary;
    secondary = arg1->secondary;
    if ((*(s32 *)((u8 *) primary + 0x1D4) == 0) ||
        (*(s32 *)((u8 *) secondary + 0x1D4) == 0)) {
        arg0->flags |= 0xC;
        return 1;
    }
    if ((*(s32 *) primary == 0) ||
        (arg1->primaryIndex != *(u8 *)((u8 *) primary + 0x3B)) ||
        (*(s32 *) secondary == 0) ||
        (arg1->secondaryIndex != *(u8 *)((u8 *) secondary + 0x3B))) {
        return 0;
    }
    mask = 8;
    if (arg3 != 0) {
        mask = 4;
    }
    arg0->flags &= ~mask;
    if (arg3 != 0) {
        input = arg1->primaryVector;
    } else {
        input = arg1->secondaryVector;
    }
    if (arg3 != 0) {
        transform = *(s32 *)((u8 *) primary + 0x1D4) +
                    (arg1->primaryOffset << 6);
    } else {
        transform = *(s32 *)((u8 *) secondary + 0x1D4) +
                    (arg1->secondaryOffset << 6);
    }
    func_15143134(input, arg2, transform);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B47D8 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/holtenrope/func_151B47D8.s")
extern f32 D_800AA3C4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B48DC CURRENT (1405) */
s32 func_151B48DC(u8 *arg0) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fa1_2;
    f32 temp_fa1_3;
    f32 temp_fa1_4;
    f32 temp_fv0;
    s32 var_v0;
    u8 *var_v1;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)((u8 *)arg0 + 0x48) = temp_fv0;
    *(f32 *)((u8 *)arg0 + 0x4C) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x50) = 0.0f;
    var_v0 = 2;
    temp_fa0 = -(temp_fv0 - *(f32 *)((u8 *)arg0 + 0x20)) * D_800AA3C4;
    var_v1 = (void *)(arg0 + 0x30);
    *(f32 *)((u8 *)arg0 + 0x68) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x64) = 0.0f;
    temp_fa1 = temp_fv0 + temp_fa0;
    *(f32 *)((u8 *)arg0 + 0x60) = temp_fa1;
    {
        f32 var_fa1 = temp_fa1 + temp_fa0;
    do {
        *(f32 *)((u8 *)var_v1 + 0x48) = var_fa1;
        *(f32 *)((u8 *)var_v1 + 0x4C) = 0.0f;
        *(f32 *)((u8 *)var_v1 + 0x50) = 0.0f;
        temp_fa1_2 = var_fa1 + temp_fa0;
        var_v0 += 4;
        *(f32 *)((u8 *)var_v1 + 0x64) = 0.0f;
        *(f32 *)((u8 *)var_v1 + 0x68) = 0.0f;
        *(f32 *)((u8 *)var_v1 + 0x60) = temp_fa1_2;
        temp_fa1_3 = temp_fa1_2 + temp_fa0;
        *(f32 *)((u8 *)var_v1 + 0x7C) = 0.0f;
        *(f32 *)((u8 *)var_v1 + 0x80) = 0.0f;
        *(f32 *)((u8 *)var_v1 + 0x94) = 0.0f;
        *(f32 *)((u8 *)var_v1 + 0x78) = temp_fa1_3;
        temp_fa1_4 = temp_fa1_3 + temp_fa0;
        *(f32 *)((u8 *)var_v1 + 0x98) = 0.0f;
        var_v1 += 0x60;
        *(f32 *)((u8 *)var_v1 + 0x30) = temp_fa1_4;
        var_fa1 = temp_fa1_4 + temp_fa0;
    } while (var_v0 != 0xA);
    *(u8 *)((u8 *)arg0 + 0x10) = (u8) (*(u8 *)((u8 *)arg0 + 0x10) & 0xFFFD);
    return 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B48DC */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/holtenrope/func_151B48DC.s")
s32 func_151B498C(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4, s32 *arg5, s32 *arg6, s32 *arg7, s32 *arg8, s32 *arg9, s32 *arg10, s32 *arg11, s8 *arg12, s8 *arg13) {
    *arg1 = 0x220005;
    *arg2 = 0x40600;
    *arg3 = 0xFF;
    *arg4 = 0xFF;
    *arg5 = 0xFF;
    *arg6 = 0xFF;
    *arg7 = 0xFF;
    *arg8 = 0xFF;
    *arg9 = 0xFF;
    *arg10 = 0xFF;
    *arg11 = 0;
    *arg12 = 5;
    *arg13 = 0x2B;
    return 1;
}
void func_1502EC34(u8 *, s32 *, s32 *, s32 *, s32 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B4A14 CURRENT (649) */
u8 func_151B4A14(void *arg0, s32 *arg1, s32 *arg2, s32 *arg3,
                 s32 *arg4, s32 *arg5, s32 *arg6, s32 *arg7,
                 s32 *arg8, s32 *arg9, s32 *arg10, s32 *arg11,
                 s8 *arg12, s8 *arg13) {
    u8 result;
    u8 *data;
    s32 value0;
    s32 value1;
    s32 value2;
    s32 value3;

    data = *(u8 **)((u8 *)arg0 + 0x150);
    result = 1;
    func_1502EC34(data, &value0, &value1, &value2, &value3);
    if (data[0xA4] & 1) {
        *arg1 = 0x200005;
        *arg2 = 0x60600;
        *arg3 = value0;
        *arg4 = value1;
        *arg5 = value2;
        *arg6 = 0xFF;
        *arg9 = value3;
        *arg8 = value3;
        *arg7 = value3;
        *arg10 = 0xFF;
        *arg11 = 0x100000;
        *arg12 = 5;
        *arg13 = 0x2F;
    } else {
        result = func_151B498C((s32)arg0, arg1, arg2, arg3, arg4,
                              arg5, arg6, arg7, arg8, arg9, arg10,
                              arg11, arg12, arg13);
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B4A14 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/holtenrope/func_151B4A14.s")
extern f32 D_800AA3C8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B4B78 CURRENT (1395) */
s32 func_151B4B78(u8 *arg0) {
    f32 step;
    f32 value;
    s32 var_v0;
    u8 *var_v1;

    step = D_800AA3C8;
    *(f32 *)((u8 *)arg0 + 0x48) = -1000.0f;
    value = -1000.0f + step;
    var_v0 = 2;
    var_v1 = (void *)(arg0 + 0x30);
    *(f32 *)((u8 *)arg0 + 0x60) = value;
    value += step;
    *(f32 *)((u8 *)arg0 + 0x4C) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x50) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x64) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x68) = 0.0f;
    do {
        *(f32 *)((u8 *)var_v1 + 0x48) = value;
        *(f32 *)((u8 *)var_v1 + 0x4C) = 0.0f;
        *(f32 *)((u8 *)var_v1 + 0x50) = 0.0f;
        value += step;
        var_v0 += 4;
        *(f32 *)((u8 *)var_v1 + 0x64) = 0.0f;
        *(f32 *)((u8 *)var_v1 + 0x68) = 0.0f;
        *(f32 *)((u8 *)var_v1 + 0x60) = value;
        value += step;
        *(f32 *)((u8 *)var_v1 + 0x7C) = 0.0f;
        *(f32 *)((u8 *)var_v1 + 0x80) = 0.0f;
        *(f32 *)((u8 *)var_v1 + 0x94) = 0.0f;
        *(f32 *)((u8 *)var_v1 + 0x78) = value;
        value += step;
        *(f32 *)((u8 *)var_v1 + 0x98) = 0.0f;
        var_v1 += 0x60;
        *(f32 *)((u8 *)var_v1 + 0x30) = value;
        value += step;
    } while (var_v0 != 0xA);
    *(u8 *)((u8 *)arg0 + 0x10) = (u8) (*(u8 *)((u8 *)arg0 + 0x10) & 0xFFFD);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B4B78 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/holtenrope/func_151B4B78.s")
typedef struct {
    u8 pad_0[0x44];
    u8 field_44;
} HoltenRopeState;

void func_151D5E30(s32, s32);
extern void (*D_8008FB70[])(s32);

void func_151B4C1C(s32 arg0) {
    void (*temp_v0)(s32);

    func_151D5E30(arg0 + 0x140, arg0);
    temp_v0 = D_8008FB70[((HoltenRopeState *)arg0)->field_44];
    if (temp_v0 != 0) {
        temp_v0(arg0);
    }
}
void func_151B4C1C(s32 arg0);
void func_15169824(s32 arg0);

void func_151B4C6C(s32 arg0) {
    func_151B4C1C(arg0);
    func_15169824(arg0);
}
void func_151B4C98(s32 arg0) {
    func_151B4C1C(arg0);
    func_15169824(arg0);
}
