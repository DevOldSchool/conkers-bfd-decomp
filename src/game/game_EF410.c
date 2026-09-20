#include "types.h"

/*
 * Reviewed source unit: src/game/game_EF410.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C1F60
 * - func_150C2290
 * - func_150C2424
 * - func_150C251C
 * - func_150C2558
 * - func_150C2700
 * - func_150C2804
 * - func_150C2898
 * - func_150C29F0
 * - func_150C2C00
 * - func_150C2FCC
 * - func_150C308C
 * - func_150C3160
 * - func_150C3230
 * - func_150C3574
 * - func_150C3994
 * - func_150C3D5C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C1F60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2290.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2424.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C251C CURRENT (255) */
s32 func_150C251C(void *arg0) {
    s16 temp_v1;
    s32 temp_t6;
    s32 var_v1;
    void *temp_v0;

    temp_v1 = *(s16 *)((u8 *)arg0 + 0x1C);
    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    temp_t6 = temp_v1 * 8;
    var_v1 = temp_t6;
    if (temp_t6 >= 0x100) {
        var_v1 = 0xFF;
    }
    *(s8 *)((u8 *)temp_v0 + 0x1B) = var_v1;
    if ((var_v1 & 0xFF) < 0) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C251C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C251C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2558.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2700.s")
void func_15134908(s32 *, s32, u8, s32);
extern f32 D_800A0280;
extern f32 D_800A0284;

typedef struct {
    s32 field_0;
    s32 field_4;
    s32 field_8;
    f32 field_C;
    f32 field_10;
    s16 field_14;
    s8 field_16;
    s8 field_17;
    s8 field_18;
    s8 field_19;
} GameEF410Params;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C2804 CURRENT (80) */
void func_150C2804(s32 arg0, s32 arg1, s32 arg2, s16 arg3, u8 arg4, s32 arg5) {
    GameEF410Params sp1C;

    sp1C.field_16 = 5;
    sp1C.field_17 = 6;
    sp1C.field_18 = 3;
    sp1C.field_19 = -1;
    sp1C.field_C = D_800A0280;
    sp1C.field_0 = arg0;
    sp1C.field_4 = arg1;
    sp1C.field_8 = arg2;
    sp1C.field_10 = D_800A0284;
    sp1C.field_14 = arg3;
    func_15134908((s32 *)&sp1C, 0, arg4, arg5);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C2804 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2804.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2898.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C29F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2C00.s")
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C2FCC CURRENT (465) */
s32 func_150C2FCC(void *arg0) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x2C);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x150);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x30);
    temp_fa1 = *(f32 *)((u8 *)arg0 + 0x50);
    temp_ft5 = *(f32 *)((u8 *)arg0 + 0x4C);
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (temp_fv0 - (temp_fv0 * temp_fv1));
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (temp_fa0 - (temp_fa0 * temp_fv1));
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)arg0 + 0x38) + ((temp_fa1 * D_800BE9A4) + (0.5f * temp_ft5 * D_800BE9A4 * D_800BE9A4)));
    *(f32 *)((u8 *)arg0 + 0x50) = (f32) (temp_fa1 + (temp_ft5 * D_800BE9A4));
    if ((*(f32 *)((u8 *)arg0 + 0x2C) < 10.0f) || (*(f32 *)((u8 *)arg0 + 0x30) < 10.0f)) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C2FCC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2FCC.s")
f32 func_150484A0(f32, f32);
s32 func_15144B34(s32);
f32 func_15144C8C(f32, f32);
extern s32 D_80082FA4;
extern f32 D_800A0310;
extern f32 D_800A0314;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C308C CURRENT (30) */
s32 func_150C308C(void *arg0) {
    u8 flag;
    u8 sp1F;
    f32 x;
    f32 z;
    f32 magnitude;
    u8 *vector;

    flag = 0;
    if (*(s16 *)((u8 *)arg0 + 0x1C) >= 6) {
        sp1F = 0;
        vector = (u8 *)func_15144B34(D_80082FA4);
        x = *(f32 *)vector;
        z = *(f32 *)(vector + 8);
        magnitude = (x * x) + (z * z);
        if (magnitude < D_800A0310) {
            flag = 1;
        } else {
            flag = sp1F;
            magnitude = *(f32 *)vector;
            if (D_800A0314 <
                func_15144C8C(func_150484A0(magnitude,
                                           *(f32 *)(vector + 8)),
                              *(f32 *)((u8 *)arg0 + 0x160))) {
                flag = 1;
            }
        }
    }
    if (flag != 0) {
        *(s16 *)((u8 *)arg0 + 0x1C) = 5;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C308C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C308C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C3160 CURRENT (720) */
void *func_150C3160(u8 *arg0, u8 *arg1) {
    f32 var_fv0;
    s32 temp_ft3;
    s32 temp_v0;
    s32 var_a0;

    temp_v0 = *(s32 *)((u8 *)arg1 + 0x2E8);
    if (temp_v0 != 0) {
        var_fv0 = (f32) *(s32 *)((u8 *)arg1 + 0x2E4) / (f32) temp_v0;
    } else {
        var_fv0 = 1.0f;
    }
    var_a0 = 2 - *(s32 *)((u8 *)arg1 + 0x2EC);
    temp_ft3 = (s32) ((500.0f * (1.0f - var_fv0)) + 2.0f);
    *(s32 *)((u8 *)arg1 + 0x2EC) = (s32) (temp_ft3 / 3);
    if (var_a0 < 0) {
        do {
            var_a0 += 0x40;
        } while (var_a0 < 0);
    }
    *(s32 *)((u8 *)arg0 + 0) = (s32) (((temp_ft3 & 0xFFF) << 0xC) | 0xF2000000 | (var_a0 & 0xFFF));
    *(s32 *)((u8 *)arg0 + 4) = 0x041FE03E;
    return arg0 + 8;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C3160 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C3160.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C3230.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C3574.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C3994.s")
s32 func_150C3D48(s32 arg0) {
    return arg0 + 0xEDCBA988;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C3D5C.s")
