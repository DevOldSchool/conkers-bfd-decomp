#include "types.h"

/*
 * Reviewed source unit: src/game/game_83300.c
 * Boundary evidence: docs/evidence/game_state_callback_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15055E50
 * - func_15056150
 * - func_15056258
 * - func_150562FC
 * - func_1505693C
 * - func_15056A00
 * - func_15056B08
 * - func_1505841C
 * - func_150585F0
 * - func_15058898
 * - func_15058EA4
 * - func_15058F24
 * - func_15059140
 * - func_150593C4
 * - func_15059444
 * - func_1505959C
 * - func_150597FC
 * - func_150599C8
 * - func_15059B54
 * - func_15059C84
 * - func_1505A184
 * - func_1505A250
 * - func_1505A3A8
 * - func_1505A5CC
 * - func_1505A630
 * - func_1505A770
 * - func_1505A9AC
 * - func_1505B5F8
 * - func_1505B9C4
 * - func_1505C140
 * - func_1505C1A4
 * - func_1505C1E4
 * - func_1505C7D8
 * - func_1505D024
 * - func_1505D1C4
 * - func_1505D2B8
 * - func_1505D34C
 * - func_1505D408
 * - func_1505D5D0
 * - func_1505D6F0
 * - func_1505DADC
 * - func_1505DDA8
 * - func_1505DF10
 * - func_1505E0C4
 * - func_1505E650
 * - func_1505E874
 * - func_1505ED34
 * - func_1505EEB0
 * - func_1505EEF4
 * - func_1505EFD0
 * - func_1505F0AC
 * - func_1505F188
 * - func_1505F298
 * - func_1506045C
 * - func_15060778
 * - func_15060BA4
 * - func_15060BE0
 * - func_15060D54
 * - func_15060F28
 * - func_150611E8
 * - func_150615DC
 * - func_1506160C
 * - func_150617BC
 * - func_1506196C
 * - func_150619A8
 * - func_15061B4C
 * - func_150623F4
 * - func_150626EC
 * - func_15062800
 * - func_15062AC4
 * - func_15062B84
 * - func_15062D10
 * - func_15062E24
 * - func_15062FC0
 * - func_15063168
 * - func_15063254
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15055E50.s")
extern f32 D_80099440;
extern s32 D_800D2104;
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15056150 CURRENT (4849) */
void func_15056150(void *arg0) {
    volatile f32 sp1C;
    f32 temp_fa0;
    f32 temp_fa1;
    register f32 temp_fs0;
    register f32 temp_fs1;
    f32 temp_ft3;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 temp_v0;
    void *temp_v1;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x2E8);
    if (temp_v0 != 0) {
        temp_v1 = ((void **)&D_800D2104)[*(u8 *)((u8 *)arg0 + 0x13F)];
        temp_fv1 = (f32)*(s16 *)((u8 *)temp_v1 + 8);
        temp_ft4 = (f32)temp_v0 * 8.0f;
        temp_fa0 = (f32)*(s16 *)((u8 *)temp_v1 + 0xC);
        temp_fa1 = (f32)*(s16 *)((u8 *)temp_v1 + 0xA);
        temp_ft5 = *(f32 *)((u8 *)arg0 + 0x14) - temp_fv1;
        temp_fs0 = *(f32 *)((u8 *)arg0 + 0x1C) - temp_fa0;
        temp_fs1 = *(f32 *)((u8 *)arg0 + 0x18) - temp_fa1;
        temp_fv0 = sqrtf((temp_ft5 * temp_ft5) + (temp_fs0 * temp_fs0) +
                          (temp_fs1 * temp_fs1) + D_80099440);
        temp_ft3 = 1.0f / temp_fv0;
        sp1C = temp_ft3;
        if (temp_ft4 < temp_fv0) {
            *(f32 *)((u8 *)arg0 + 0x14) =
                (temp_ft5 * temp_ft3 * temp_ft4) + temp_fv1;
            *(f32 *)((u8 *)arg0 + 0x1C) =
                (temp_fs0 * temp_ft3 * temp_ft4) + temp_fa0;
            *(f32 *)((u8 *)arg0 + 0x18) =
                (temp_fs1 * temp_ft3 * temp_ft4) + temp_fa1;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15056150 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15056150.s")
extern f32 D_80099444;
f32 fabsf(f32);
#pragma intrinsic(fabsf)

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15056258 CURRENT (1290) */
void func_15056258(void *arg0) {
    f32 temp_fa1;
    f32 temp_ft0;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fa0;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x118);
    temp_fa1 = *(f32 *)((u8 *)arg0 + 0x18);
    temp_ft0 = *(f32 *)((u8 *)arg0 + 0x11C);
    *(f32 *)((u8 *)arg0 + 0x11C) = temp_fv0;
    temp_fv1 = temp_fv0 - temp_ft0;
    var_fa0 = 2.0f * (temp_fa1 - ((temp_fv0 - 60.0f) - 170.0f));
    if (var_fa0 < 0.0f) {
        return;
    }
    if (fabsf(temp_fv1) > 30.0f) {
        return;
    }
    if (var_fa0 > 300.0f) {
        var_fa0 = 300.0f;
    }
    *(f32 *)((u8 *)arg0 + 0x18) = (f32) (temp_fa1 + (var_fa0 * temp_fv1 * D_80099444));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15056258 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15056258.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150562FC.s")
extern s32 D_800D2104;
extern s32 D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505693C CURRENT (1910) */
s32 func_1505693C(void *arg0, s32 arg1) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    u16 temp_v1;
    u8 *temp_a0;
    u8 *temp_v0;
    u8 index;

    index = *(u8 *)((u8 *)arg0 + 0x13F);
    temp_v0 = ((u8 **)&D_800D2104)[index];
    temp_v1 = *(u16 *)(temp_v0 + 6);
    if (temp_v1 == 0) {
        return 1;
    }
    temp_fv0 = (f32)(temp_v1 * 8);
    temp_a0 = (u8 *)&D_800CC2D0 + (arg1 * 0x32C);
    temp_fv1 = (f32)*(s16 *)(temp_v0 + 0) - *(f32 *)(temp_a0 + 0x14);
    temp_fa0 = (f32)*(s16 *)(temp_v0 + 4) - *(f32 *)(temp_a0 + 0x1C);
    if (((temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0)) < (temp_fv0 * temp_fv0)) {
        return 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505693C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505693C.s")
extern u8 D_80099A3C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15056A00 CURRENT (2855) */
void func_15056A00(void *arg0, u8 arg1, u8 arg2) {
    s32 temp_t6;
    s32 temp_t7;
    s32 temp_t7_2;
    s32 var_v0;
    s32 var_v0_2;
    u16 temp_v1_2;
    u8 *temp_a1;
    void *temp_v1;
    u8 temp_t5;

    temp_t6 = arg1;
    temp_t7 = arg2;
    temp_v1 = &D_80099A3C + (temp_t7 * 0xA);
    var_v0 = 0;
    if ((s32)*(u8 *)((u8 *)temp_v1 + 7) < temp_t6) {
        var_v0 = 5;
    } else if ((s32)*(u8 *)((u8 *)temp_v1 + 2) < temp_t6) {
        var_v0 = 2;
    }
    temp_v1_2 = *(u16 *)((u8 *)arg0 + 0x76);
    if ((*(u16 *)((u8 *)arg0 + 0x78) - temp_v1_2) & 0x8000) {
        var_v0_2 = (var_v0 + 3) & 0xFF;
    } else {
        var_v0_2 = (var_v0 + 4) & 0xFF;
    }
    temp_a1 = &D_80099A3C + (temp_t7 * 0xA) + var_v0_2;
    if (*temp_a1 != 0xFF) {
        *(s32 *)((u8 *)arg0 + 0x218) -= 5;
        *(s16 *)((u8 *)arg0 + 0x21C) = 0x4E20;
        *(s8 *)((u8 *)arg0 + 0x223) = 0xD;
        *(f32 *)((u8 *)arg0 + 0x44) = 0.0f;
        temp_t7_2 = *(s32 *)((u8 *)arg0 + 0xF4) & ~0xE;
        *(s32 *)((u8 *)arg0 + 0xF4) = temp_t7_2;
        temp_t5 = *temp_a1;
        *(s32 *)((u8 *)arg0 + 0xF4) = temp_t7_2 | 4;
        *(u16 *)((u8 *)arg0 + 0x78) = temp_v1_2;
        *(u16 *)((u8 *)arg0 + 0x7A) = temp_v1_2;
        *(s8 *)((u8 *)arg0 + 0x138) = 0;
        *(s16 *)((u8 *)arg0 + 0x244) = (s16)temp_t5;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15056A00 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15056A00.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15056B08.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505841C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150585F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15058898.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15058EA4 CURRENT (155) */
void func_15058EA4(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x18);
    if (arg1 < temp_fv0) {
        *(f32 *)((u8 *)arg0 + 0x24) = arg2;
    } else if (temp_fv0 < arg3) {
        *(f32 *)((u8 *)arg0 + 0x24) = arg4;
    }
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x20);
    if (arg5 < temp_fv1) {
        *(f32 *)((u8 *)arg0 + 0x20) = arg5;
        return;
    }
    if (temp_fv1 < arg6) {
        *(f32 *)((u8 *)arg0 + 0x20) = arg6;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15058EA4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15058EA4.s")
extern f32 D_800994A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15058F24 CURRENT (8705) */
void func_15058F24(void *arg0, f32 arg1) {
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 temp_fv1_3;
    f32 temp_fv1_4;
    f32 var_fs0;

    var_fs0 = arg1;
    temp_fa0 = var_fs0;
    temp_ft4 = 0.5f - var_fs0;
    if (var_fs0 >= 0.5f) {
        var_fs0 -= 0.5f;
    }
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x18);
    temp_fa1 = *(f32 *)((u8 *)arg0 + 0x118) + 9.0f;
    if ((temp_fv1 < temp_fa1) || ((s32) *(u8 *)((u8 *)arg0 + 0xAD) >= 0x64)) {
        if (*(u8 *)((u8 *)arg0 + 0xAD) == 0) {
            *(f32 *)((u8 *)arg0 + 0x18) = temp_fa1;
            *(u8 *)((u8 *)arg0 + 0xAD) = 0x64U;
            *(f32 *)((u8 *)arg0 + 0x24) = (f32) (temp_ft4 * -6.0f);
            *(f32 *)((u8 *)arg0 + 0x20) = (f32) (*(f32 *)((u8 *)arg0 + 0x20) * temp_fa0);
        } else {
            if ((temp_fa1 + 100.0f) < temp_fv1) {
                *(u8 *)((u8 *)arg0 + 0xAD) = 0U;
            }
            if (temp_ft4 < 0.0f) {
                *(f32 *)((u8 *)arg0 + 0x24) = (f32) (temp_ft4 * -6.0f);
            } else {
                temp_fv1_2 = *(f32 *)((u8 *)arg0 + 0x18);
                temp_fa0_2 = temp_fv1_2 - ((temp_fa1 + 10.0f) - (120.0f * var_fs0));
                if ((fabsf(temp_fa0_2) < 2.0f) && (fabsf(*(f32 *)((u8 *)arg0 + 0x20)) < 2.0f)) {
                    *(f32 *)((u8 *)arg0 + 0x20) = 0.0f;
                    *(f32 *)((u8 *)arg0 + 0x24) = 1.0f;
                    *(f32 *)((u8 *)arg0 + 0x18) = (f32) (temp_fv1_2 - (temp_fa0_2 * D_800994A4));
                } else {
                    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x20);
                    if (temp_fa0_2 > 0.0f) {
                        if (temp_fv0 > 0.0f) {
                            *(f32 *)((u8 *)arg0 + 0x24) = (f32) (temp_ft4 * 6.0f);
                            *(f32 *)((u8 *)arg0 + 0x20) = (f32) (temp_fv0 * 0.5f);
                        }
                    } else {
                        temp_fv1_3 = temp_ft4 * 80.0f;
                        if (temp_fv1_3 < temp_fv0) {
                            *(f32 *)((u8 *)arg0 + 0x20) = temp_fv1_3;
                        }
                        *(f32 *)((u8 *)arg0 + 0x24) = (f32) (temp_ft4 * -6.0f);
                    }
                }
            }
        }
        temp_fv1_4 = -100.0f * var_fs0;
        if (*(f32 *)((u8 *)arg0 + 0x20) < temp_fv1_4) {
            *(f32 *)((u8 *)arg0 + 0x20) = temp_fv1_4;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15058F24 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15058F24.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15059140.s")
void func_1505A184(u16, f32, s32, f32 *, f32 *, s32 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150593C4 CURRENT (409) */
void func_150593C4(s32 arg0, u16 arg1, f32 arg2, f32 arg3) {
    f32 sp2C;
    f32 sp28;
    s32 sp24;
    f32 temp_fv0;
    f32 temp_fv1;

    func_1505A184(arg1, arg2, 0, &sp2C, &sp28, &sp24);
    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x16C);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x170);
    *(f32 *)((u8 *)arg0 + 0x16C) = temp_fv0 + ((sp2C - temp_fv0) * arg3);
    *(f32 *)((u8 *)arg0 + 0x170) = temp_fv1 + ((sp28 - temp_fv1) * arg3);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150593C4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150593C4.s")
void func_150593C4(s32, u16, f32, f32);
s32 func_15083E0C(s32);
s32 func_150A29C8(s32, s32);
void func_150611E8(u8 *, s32);
extern s32 D_800BE9F0;
extern u8 D_800C3E78;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15059444 CURRENT (265) */
void func_15059444(s32 arg0) {
    s32 sp1C;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;

    sp1C = -1;
    switch (D_800BE9F0) {
    case 4:
        func_150593C4(arg0, 0x4000U, 50.0f, 0.06f);
        break;
    case 6:
        sp1C = func_15083E0C(0x1C);
        break;
    case 0x29:
        if (func_150A29C8(D_800C3E78, 0x4028) == 0) {
            var_v0_2 = 0xC;
        } else if (func_150A29C8(D_800C3E78, 0x400E) == 0) {
            var_v0_2 = 0xA;
        } else if (func_150A29C8(D_800C3E78, 0x400D) == 0) {
            var_v0_2 = 9;
        } else {
            var_v0_2 = 6;
        }
        sp1C = func_15083E0C(var_v0_2 & 0xFF);
        break;
    case 0x2B:
        sp1C = func_15083E0C(0x12);
        break;
    case 0x41:
        if (func_150A29C8(D_800C3E78, 0x401F) == 0) {
            var_v0_3 = 0x1B;
        } else {
            var_v0_3 = 0x1A;
        }
        sp1C = func_15083E0C(var_v0_3 & 0xFF);
        break;
    }
    if (sp1C != -1) {
        func_150611E8((u8 *)arg0, sp1C);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15059444 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15059444.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505959C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150597FC.s")
extern s16 D_800CC264;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150599C8 CURRENT (2780) */
s32 func_150599C8(void *arg0, s32 arg1, s32 arg2) {
    s16 temp_a2;
    s16 temp_t3;
    s16 temp_v1;
    s16 var_a3;
    s32 temp_lo;
    u16 temp_t0;
    u16 temp_t1;
    u16 temp_t2;

    temp_t0 = *(u16 *)((u8 *)arg0 + 0x7A);
    temp_t1 = *(u16 *)((u8 *)arg0 + 0x1EA);
    var_a3 = (arg2 & 0xFFFF) - temp_t0;
    {
        s32 var_v0 = (s32) ((((arg1 & 0xFF) << 8) + *(u8 *)((u8 *)arg0 + 0x1E8)) * D_800CC264) / 100;
    if (temp_t1 != 0) {
        temp_t2 = *(u16 *)((u8 *)arg0 + 0x1EC);
        temp_lo = (s32) (temp_t1 * D_800CC264) / 100;
        temp_a2 = temp_t2 + temp_lo;
        temp_t3 = temp_t2 - temp_lo;
        if (temp_a2 < var_a3) {
            var_a3 = temp_a2;
        }
        if (var_a3 < temp_t3) {
            var_a3 = temp_t3;
        }
    }
    temp_v1 = var_a3;
    if (var_a3 < 0) {
        var_a3 ^= 0xFFFF;
    }
    if (var_a3 < var_v0) {
        var_v0 = (s32) var_a3;
    }
    if (!(*(s32 *)((u8 *)arg0 + 0xF4) & 1) && (*(u8 *)((u8 *)arg0 + 0x80) != 0)) {
        if (temp_v1 < 0) {
            *(u16 *)((u8 *)arg0 + 0x7A) = (u16) (temp_t0 - var_v0);
        } else {
            *(u16 *)((u8 *)arg0 + 0x7A) = (u16) (temp_t0 + var_v0);
        }
    }
    return (var_a3 >> 8) & 0xFF;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150599C8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150599C8.s")
extern s16 D_800CC264;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15059B54 CURRENT (1745) */
s32 func_15059B54(void *arg0, u16 arg1) {
    s16 temp_a1_2;
    s16 temp_t0;
    s16 temp_t2;
    s16 temp_v0;
    s16 var_a2;
    s16 var_v0;
    s32 temp_lo;
    u16 temp_a1;
    u16 temp_t1;
    u16 temp_v1;

    temp_v1 = *(u16 *)((u8 *)arg0 + 0x76);
    temp_v0 = *(u16 *)((u8 *)arg0 + 0x78) - temp_v1;
    var_v0 = temp_v0;
    var_a2 = temp_v0;
    if (temp_v0 < 0) {
        var_a2 = temp_v0 ^ 0xFFFF;
    }
    temp_a1 = *(u16 *)((u8 *)arg0 + 0x1EA);
    if (temp_a1 != 0) {
        temp_t1 = *(u16 *)((u8 *)arg0 + 0x1EC);
        temp_lo = (s32) (temp_a1 * D_800CC264) / 100;
        temp_t0 = temp_t1 + temp_lo;
        temp_t2 = temp_t1 - temp_lo;
        if (temp_t0 < var_v0) {
            var_v0 = temp_t0;
        }
        if (var_v0 < temp_t2) {
            var_v0 = temp_t2;
        }
    }
    temp_a1_2 = var_v0;
    if (var_v0 < 0) {
        var_v0 ^= 0xFFFF;
    }
    if (var_v0 < (s32) arg1) {
        arg1 = (u16) var_v0;
    }
    if (!(*(s32 *)((u8 *)arg0 + 0xF4) & 1)) {
        if (temp_a1_2 < 0) {
            *(u16 *)((u8 *)arg0 + 0x76) = (u16) (temp_v1 - arg1);
            *(u16 *)((u8 *)arg0 + 0x1EC) = (u16) -(s32) arg1;
        } else {
            *(u16 *)((u8 *)arg0 + 0x76) = (u16) (arg1 + temp_v1);
            *(u16 *)((u8 *)arg0 + 0x1EC) = arg1;
        }
    }
    return (var_a2 >> 8) & 0xFF;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15059B54 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15059B54.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15059C84.s")
f32 func_150AD780(f32);
f32 func_150AD78C(f32);
extern f32 D_800994B8;
extern f32 D_800994BC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505A184 CURRENT (589) */
void func_1505A184(u16 arg0, register f32 arg1, s32 arg2, f32 *arg3,
    f32 *arg4, s32 *arg5) {
    union {
        s32 word;
        f32 value;
    } angle_bits;
    f32 first_angle;
    f32 second_angle;
    f32 sine;
    f32 cosine;

    arg1 *= 0.5f;
    angle_bits.word = arg2;
    first_angle = angle_bits.value * D_800994B8;
    *(f32 *)arg5 = func_150AD78C(first_angle) * -arg1;
    arg1 = func_150AD780(first_angle) * arg1;
    second_angle = (f32)arg0 * D_800994BC;
    sine = func_150AD780(second_angle);
    cosine = -func_150AD78C(second_angle);
    *arg3 = sine * arg1;
    *arg4 = cosine * arg1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505A184 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A184.s")
extern f32 D_800D1550;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505A250 CURRENT (10389) */
void func_1505A250(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4) {
    f32 sp4;
    f32 sp0;
    f32 temp_ft3;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 temp_ft5;

    temp_ft4 = *arg3;
    temp_fv1 = arg0 - temp_ft4;
    temp_ft5 = arg1 - *arg4;
    if ((temp_fv1 != 0.0f) || (temp_ft5 != 0.0f)) {
        temp_ft3 = D_800D1550 * arg2;
        temp_fv0 = sqrtf((temp_fv1 * temp_fv1) + (temp_ft5 * temp_ft5));
        arg2 = temp_ft3;
        sp4 = temp_fv0;
        sp0 = fabsf((temp_fv1 / temp_fv0) * temp_ft3);
        temp_fv0_2 = fabsf((temp_ft5 / sp4) * temp_ft3);
        if (temp_fv1 >= 0.0f) {
            *arg3 = temp_ft4 + sp0;
            if (arg0 < *arg3) {
                goto block_6;
            }
        } else {
            *arg3 = temp_ft4 - sp0;
            if (*arg3 < arg0) {
block_6:
                *arg3 = arg0;
            }
        }
        if (temp_ft5 >= 0.0f) {
            *arg4 += temp_fv0_2;
            if (arg1 < *arg4) {
                goto block_11;
            }
        } else {
            *arg4 -= temp_fv0_2;
            if (*arg4 < arg1) {
block_11:
                *arg4 = arg1;
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505A250 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A250.s")
extern f32 D_800994C0;
extern f32 D_800994C4;
extern f32 D_800994C8;
extern f32 D_800994CC;
extern f32 D_800994D0;
extern u8 D_800CC27C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505A3A8 CURRENT (3081) */
void func_1505A3A8(f32 arg0, void *arg1, f32 arg2, f32 arg3, u8 arg4) {
    f32 var_fa0;
    f32 var_fa1;
    u8 temp_v0;

    var_fa0 = arg0;
    {
        f32 var_fs0 = arg2 * D_800D1550;
    var_fa1 = arg3 * D_800D1550;
    if ((D_800CC27C != 0) && (*(f32 *)((u8 *)arg1 + 0x28) < 5.0f) && (*(s32 *)((u8 *)arg1 + 0) != 0x1E)) {
        var_fs0 = 0.0f;
    }
    if (*(s32 *)((u8 *)arg1 + 0) == 1) {
        if (*(u8 *)((u8 *)arg1 + 0xAD) != 0) {
            var_fs0 = 2.0f;
            var_fa1 *= D_800994C0;
        }
        if (*(u8 *)((u8 *)arg1 + 0xA8) != 0) {
            var_fa1 *= 0.25f;
        }
        temp_v0 = *(u8 *)((u8 *)arg1 + 0x81);
        if (temp_v0 != 0) {
            if (temp_v0 & 0x40) {
                if (temp_v0 & 0x20) {
                    var_fa1 = 0.0f;
                } else {
                    var_fa1 = D_800994C4;
                }
            } else {
                var_fa1 *= D_800994C8;
                if ((s32) arg4 >= 0x2E) {
                    var_fs0 *= 0.5f;
                }
                if ((s32) arg4 >= 0x5B) {
                    var_fa0 *= 0.5f;
                }
            }
        }
        if (*(u8 *)((u8 *)arg1 + 0xAE) != 0) {
            var_fa1 *= D_800994CC;
        }
    }
    if (var_fa0 < 0.0f) {
        if (*(f32 *)((u8 *)arg1 + 0x3C) > 0.0f) {
            var_fa1 += var_fs0;
        } else {
            var_fa1 = var_fs0;
        }
    } else if (*(f32 *)((u8 *)arg1 + 0x3C) < 0.0f) {
        var_fs0 += var_fa1;
    }
    if (var_fa0 < *(f32 *)((u8 *)arg1 + 0x3C)) {
        *(f32 *)((u8 *)arg1 + 0x3C) = (f32) (*(f32 *)((u8 *)arg1 + 0x3C) - var_fa1);
        if (*(f32 *)((u8 *)arg1 + 0x3C) < var_fa0) {
            goto block_32;
        }
    } else {
        if ((var_fa0 - 1.0f) < *(f32 *)((u8 *)arg1 + 0x3C)) {
            var_fs0 *= D_800994D0;
        }
        *(f32 *)((u8 *)arg1 + 0x3C) = (f32) (*(f32 *)((u8 *)arg1 + 0x3C) + var_fs0);
        if (var_fa0 < *(f32 *)((u8 *)arg1 + 0x3C)) {
block_32:
            *(f32 *)((u8 *)arg1 + 0x3C) = var_fa0;
        }
    }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505A3A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A3A8.s")
extern f32 D_800994D4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505A5CC CURRENT (25) */
f32 func_1505A5CC(void *arg0) {
    f32 temp_fa0;
    f32 temp_fv1;

    temp_fv1 = (f32) *(s8 *)((u8 *)arg0 + 2);
    temp_fa0 = (f32) *(s8 *)((u8 *)arg0 + 3);
    temp_fv1 = sqrtf((temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0)) * D_800994D4;
    if (temp_fv1 > 35.0f) {
        temp_fv1 = 35.0f;
    }
    return temp_fv1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505A5CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A5CC.s")
f32 func_150484A0(f32, f32);
extern f32 D_800994D8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505A630 CURRENT (235) */
s32 func_1505A630(f32 arg0, f32 arg1, s32 arg2) {
    return ((u32) (func_150484A0(-arg0, arg1) * D_800994D8) + 0x4000) & 0xFFFF;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505A630 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A630.s")
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
f32 func_1505A6F8(void *arg0, void *arg1) {
    f32 temp_fa0;
    f32 temp_fv1;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x14) - *(f32 *)((u8 *)arg1 + 0x14);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x1C) - *(f32 *)((u8 *)arg1 + 0x1C);
    temp_fv1 *= temp_fv1;
    temp_fa0 *= temp_fa0;
    return sqrtf(temp_fv1 + temp_fa0);
}
f32 func_1505A72C(void *arg0, void *arg1) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv1;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x14) - *(f32 *)((u8 *)arg1 + 0x14);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x1C) - *(f32 *)((u8 *)arg1 + 0x1C);
    temp_fa1 = *(f32 *)((u8 *)arg0 + 0x18) - *(f32 *)((u8 *)arg1 + 0x18);
    temp_fv1 *= temp_fv1;
    temp_fa0 *= temp_fa0;
    temp_fa1 *= temp_fa1;
    return sqrtf(temp_fv1 + temp_fa0 + temp_fa1);
}
extern f32 D_800994DC;
extern f32 D_800994E0;
extern f32 D_800994E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505A770 CURRENT (22180) */
void func_1505A770(void *arg0) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv0_4;
    f32 temp_fv0_5;
    f32 temp_fv0_6;
    f32 temp_fv0_7;
    f32 temp_fv0_8;
    f32 temp_fv0_9;
    f32 temp_fv1;
    f32 var_ft4;
    f32 var_ft5;
    s32 temp_a2;
    s32 temp_ft4;
    s32 var_v1;
    s32 var_v1_2;

    if ((*(f32 *)((u8 *)arg0 + 0x28) != 0.0f) || (temp_fv0 = *(f32 *)((u8 *)arg0 + 0x20), (temp_fv0 > 0.0f))) {
        var_v1 = 0;
        temp_fv1 = *(f32 *)((u8 *)arg0 + 0x24) * D_800994DC;
        temp_ft4 = (s32) (D_800D1550 / D_800994DC);
        temp_a2 = temp_ft4 & 3;
        if (temp_ft4 > 0) {
            if (temp_a2 != 0) {
                var_v1 = 1;
                *(f32 *)((u8 *)arg0 + 0x20) = (f32) (*(f32 *)((u8 *)arg0 + 0x20) - temp_fv1);
                if (temp_a2 != 1) {
                    do {
                        var_v1 += 1;
                        *(f32 *)((u8 *)arg0 + 0x20) = (f32) (*(f32 *)((u8 *)arg0 + 0x20) - temp_fv1);
                        *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + (*(f32 *)((u8 *)arg0 + 0x20) * D_800994E0));
                    } while (temp_a2 != var_v1);
                }
                *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + (*(f32 *)((u8 *)arg0 + 0x20) * D_800994E0));
                if (var_v1 != temp_ft4) {
                    goto block_7;
                }
            } else {
block_7:
                var_v1_2 = var_v1 + 4;
                *(f32 *)((u8 *)arg0 + 0x20) = (f32) (*(f32 *)((u8 *)arg0 + 0x20) - temp_fv1);
                temp_fv0_2 = *(f32 *)((u8 *)arg0 + 0x20);
                var_ft4 = temp_fv0_2 * D_800994E4;
                var_ft5 = temp_fv0_2 - temp_fv1;
                if (var_v1_2 != temp_ft4) {
                    do {
                        *(f32 *)((u8 *)arg0 + 0x20) = var_ft5;
                        temp_fv0_3 = *(f32 *)((u8 *)arg0 + 0x20);
                        var_v1_2 += 4;
                        *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + var_ft4);
                        *(f32 *)((u8 *)arg0 + 0x20) = (f32) (temp_fv0_3 - temp_fv1);
                        temp_fv0_4 = *(f32 *)((u8 *)arg0 + 0x20);
                        *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + (temp_fv0_3 * D_800994E4));
                        *(f32 *)((u8 *)arg0 + 0x20) = (f32) (temp_fv0_4 - temp_fv1);
                        temp_fv0_5 = *(f32 *)((u8 *)arg0 + 0x20);
                        *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + (temp_fv0_4 * D_800994E4));
                        *(f32 *)((u8 *)arg0 + 0x20) = (f32) (temp_fv0_5 - temp_fv1);
                        temp_fv0_6 = *(f32 *)((u8 *)arg0 + 0x20);
                        var_ft4 = D_800994E4 * temp_fv0_6;
                        var_ft5 = temp_fv0_6 - temp_fv1;
                        *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + (temp_fv0_5 * D_800994E4));
                    } while (var_v1_2 != temp_ft4);
                }
                *(f32 *)((u8 *)arg0 + 0x20) = var_ft5;
                temp_fv0_7 = *(f32 *)((u8 *)arg0 + 0x20);
                *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + var_ft4);
                *(f32 *)((u8 *)arg0 + 0x20) = (f32) (temp_fv0_7 - temp_fv1);
                temp_fv0_8 = *(f32 *)((u8 *)arg0 + 0x20);
                *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + (temp_fv0_7 * D_800994E4));
                *(f32 *)((u8 *)arg0 + 0x20) = (f32) (temp_fv0_8 - temp_fv1);
                *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + (temp_fv0_8 * D_800994E4));
                *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + (*(f32 *)((u8 *)arg0 + 0x20) * D_800994E4));
            }
        }
        if (*(f32 *)((u8 *)arg0 + 0x20) < -500.0f) {
            *(f32 *)((u8 *)arg0 + 0x20) = -500.0f;
        }
    } else {
        *(f32 *)((u8 *)arg0 + 0x20) = (f32) (temp_fv0 - (*(f32 *)((u8 *)arg0 + 0x24) * D_800D1550));
        temp_fv0_9 = *(f32 *)((u8 *)arg0 + 0x20);
        *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + (temp_fv0_9 * D_800D1550 * 0.5f));
        if (temp_fv0_9 < -500.0f) {
            *(f32 *)((u8 *)arg0 + 0x20) = -500.0f;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505A770 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A770.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A9AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505B5F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505B9C4.s")
typedef struct {
    u8 pad_0[0x14];
    f32 field_14;
    u8 pad_18[4];
    f32 field_1C;
    u8 pad_20[0x5A];
    u16 field_7A;
} Game83300Position;

s32 func_1505A630(f32, f32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505C140 CURRENT (75) */
s32 func_1505C140(Game83300Position *arg0, Game83300Position *arg1) {
    s16 temp_v1;
    s32 var_v1;

    temp_v1 = func_1505A630(arg0->field_14 - arg1->field_14,
                           arg1->field_1C - arg0->field_1C, 0) - arg1->field_7A;
    var_v1 = temp_v1;
    if (temp_v1 < 0) {
        var_v1 = (s16)-temp_v1;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505C140 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505C140.s")
extern s32 D_8009A9F8;
extern void *D_800D1588[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505C1A4 CURRENT (210) */
void *func_1505C1A4(void *arg0) {
    void *var_a0;
    void **var_v0;
    void *temp_v1;
    u8 temp_v0;

    temp_v0 = *(u8 *)((u8 *)arg0 + 4);
    if ((temp_v0 != 0xFF) && ((temp_v1 = D_800D1588[temp_v0]) != 0)) {
            var_v0 = (void **)((u8 *)temp_v1 - 0xC);
            var_a0 = *var_v0;
    } else {
        var_a0 = &D_8009A9F8;
    }
    return var_a0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505C1A4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505C1A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505C1E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505C7D8.s")
s32 func_1505C1E4(s32 *, void *, void *, s32, s32, s32, s32);
void func_1505B9C4(s32 *, void *, void *, void *, s32, s32, s32);
void *func_1505C1A4(void *);
extern u8 D_800C35EA;
extern s32 D_800D121C;
extern u16 D_800D1292;
extern u16 D_800D1296;
extern s8 D_800D1340;
extern void *D_800D154C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505D024 CURRENT (5761) */
s32 func_1505D024(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *record;
    s32 index;
    s32 mask;
    s32 result;
    u16 value;

    value = arg2 & 0xFFFF;
    record = &D_8009A9F8;
    if (D_800C35EA == 1) {
        return 0;
    }
    if (arg1 & 0x20000) {
        if (((u8 *)arg0)[0x125]) {
            return 0;
        }
    }
    if (arg1 & 0x40000) {
        if (((u8 *)arg0)[0x104]) {
            return 0;
        }
    }
    if (!(arg1 & 0x100000)) {
        if (!((u8 *)arg0)[0x1CA]) {
            return 0;
        }
    }
    if (arg3 == -1) {
        D_800D1340 = 0;
    } else {
        D_800D1340 = arg3 + 1;
    }
    D_800D1292 = value;
    D_800D1296 = value;
    if (arg1 & 0x10000) {
        record = func_1505C1A4(D_800D154C);
    }
    index = ((s32)arg0 - (s32)&D_800CC2D0) / 812;
    mask = 1 << index;
    if (arg1 & 0x80000) {
        result = func_1505C1E4(&D_800D121C, arg0, record,
                               arg1 & 0xFF, index + 1, 0, 7);
    } else {
        func_1505B9C4(&D_800D121C, arg0, record, record,
                       arg1 & 0xFF, index + 1, 7);
        result = mask;
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505D024 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D024.s")
void func_1505F188(u32);
void func_1505C7D8(s32 *, s32);
extern u8 D_800C3E78;
extern s32 D_800D121C;
extern f32 D_800D1230;
extern f32 D_800D1234;
extern f32 D_800D1238;
extern u16 D_800D1292;
extern s8 D_800D12EC;
extern f32 D_800D1330;
extern s8 D_800D1340;
extern s8 D_800D1359;
extern f32 D_800D1368;
extern f32 D_800D136C;
extern s32 D_800D1510;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505D1C4 CURRENT (30) */
void func_1505D1C4(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4,
                   u16 arg5, s32 arg6, s32 arg7) {
    volatile struct {
        s32 saved_state;
        s32 pad;
    } local;

    local.saved_state = D_800C3E78;
    func_1505F188((u32)&D_800D121C);
    D_800D1230 = arg0;
    D_800D1234 = arg1;
    D_800D1238 = arg2;
    D_800D1340 = arg4 + 1;
    D_800D1359 = arg6;
    D_800D1292 = arg5;
    D_800C3E78 = 0x19;
    D_800D1510 = arg7;
    D_800D1330 = 100.0f;
    D_800D12EC = arg3 + 1;
    D_800D1368 = 0.5f;
    D_800D136C = 0.5f;
    func_1505C7D8(&D_800D121C, 0x19);
    D_800C3E78 = local.saved_state;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505D1C4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D1C4.s")
u32 func_1505E7CC(s32, void *);
void func_1505E874(u8, void *);
extern u8 D_8009A6D8[];
extern u8 D_800C3E78;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505D2B8 CURRENT (300) */
void func_1505D2B8(void *arg0, u8 arg1) {
    void *temp_v0;

    temp_v0 = (u8 *)D_8009A6D8 + (arg1 * 0x28);
    *(f32 *)((u8 *)arg0 + 0x20) = *(f32 *)((u8 *)temp_v0 + 0x18);
    *(f32 *)((u8 *)arg0 + 0x3C) = *(f32 *)((u8 *)temp_v0 + 0x14);
    *(u8 *)((u8 *)arg0 + 0x104) = 0xFE;
    *(u8 *)((u8 *)arg0 + 0x105) = 0;
    *(f32 *)((u8 *)arg0 + 0x24) = *(f32 *)((u8 *)temp_v0 + 0x1C);
    *(u8 *)((u8 *)arg0 + 0x106) = func_1505E7CC((*(u8 *)((u8 *)arg0 + 0x10E) & 0x7F), arg0);
    *(u8 *)((u8 *)arg0 + 0x10E) = 0xFF;
    func_1505E874(D_800C3E78, arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505D2B8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D2B8.s")
f32 func_150AD780(f32);                             /* extern */
f32 func_150AD78C(f32);                             /* extern */
extern f32 D_80099520;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505D34C CURRENT (411) */
f32 func_1505D34C(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4) {
    f32 sp24;
    f32 temp_fa0;
    f32 temp_fv0;

    if (arg3 != 1.0f) {
        arg1 *= arg3;
        arg2 *= arg3;
    }
    temp_fa0 = (arg0 - 90.0f) * D_80099520;
    {
        f32 sp18 = temp_fa0;
    sp24 = func_150AD780(temp_fa0);
    temp_fv0 = func_150AD78C(temp_fa0);
    *arg4 = (-arg1 * temp_fv0) + (arg2 * sp24);
    return (arg1 * sp24) + (arg2 * temp_fv0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505D34C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D34C.s")
extern f32 D_80099524;
extern f32 D_80099528;
extern f32 D_8009952C;
extern s32 D_800CC268;
extern s8 D_800CC26C;
extern s8 D_800CC26D;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505D408 CURRENT (5876) */
void func_1505D408(void *arg0, void *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7) {
    f32 temp_ft2;
    f32 temp_ft3;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_fv1;
    s32 temp_a2;
    s32 temp_t0;
    s32 var_v0;
    s32 var_v1;

    var_fa1 = arg2;
    var_fa0 = arg5;
    var_fv1 = D_80099524;
    var_v0 = 0;
    var_v1 = 0;
    if (var_fa0 < 1.0f) {
        var_fa0 = D_80099528;
    }
    if ((var_fa1 == 0.0f) && (arg4 == 0.0f)) {
        var_fa1 = 1.0f;
    }
    D_800CC268 |= 1 << arg7;
    if (!(*(s32 *)((u8 *)arg1 + 0xF8) & 0x10) || (D_800CC26C = (s8) arg7, var_fv1 = D_8009952C, (*(u8 *)((u8 *)arg1 + 4) != 0x61)) || (*(s32 *)((u8 *)arg0 + 0) != 1)) {
        temp_t0 = *(s32 *)((u8 *)arg0 + 0xF8);
        temp_a2 = *(s32 *)((u8 *)arg1 + 0xF8);
        if (temp_t0 & 1) {
            var_v0 = 1;
        }
        if (temp_t0 & 0x200) {
            var_v0 = (var_v0 | 2) & 0xFF;
        }
        if (temp_a2 & 1) {
            var_v1 = 1;
        }
        if (temp_a2 & 0x200) {
            var_v1 = (var_v1 | 2) & 0xFF;
        }
        if (var_v1 >= var_v0) {
            if ((temp_a2 & 0x400) && (*(f32 *)((u8 *)arg1 + 0x28) == 0.0f)) {
                D_800CC26D = arg7 + 0x64;
            }
            temp_fv0 = sqrtf(var_fa0);
            temp_ft5 = 1.0f / temp_fv0;
            temp_ft2 = arg6 - temp_fv0;
            arg6 = temp_ft2;
            temp_ft3 = temp_ft2 * var_fv1;
            arg3 *= temp_ft5;
            arg6 = temp_ft3;
            *(f32 *)((u8 *)arg0 + 0x14) = (f32) (*(f32 *)((u8 *)arg0 + 0x14) + (temp_ft3 * (var_fa1 * temp_ft5)));
            *(f32 *)((u8 *)arg0 + 0x1C) = (f32) (*(f32 *)((u8 *)arg0 + 0x1C) + (arg6 * (arg4 * temp_ft5)));
            *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + (arg6 * arg3));
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505D408 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D408.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505D5D0 CURRENT (5024) */
void func_1505D5D0(void *arg0, void *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11, f32 arg12) {
    f32 temp_fa0;
    f32 temp_ft2;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 temp_fv1_2;

    temp_fv0 = func_1505D34C(*(f32 *)((u8 *)arg1 + 0x40), arg11, arg12, *(f32 *)((u8 *)arg1 + 0x14C), &arg12);
    temp_ft2 = arg8 * *(f32 *)((u8 *)arg1 + 0x14C);
    arg8 = temp_ft2;
    temp_fv1 = *(f32 *)((u8 *)arg1 + 0x150);
    temp_ft4 = arg2 - (*(f32 *)((u8 *)arg1 + 0x14) + temp_fv0);
    temp_ft5 = arg4 - (*(f32 *)((u8 *)arg1 + 0x1C) + arg12);
    temp_fa0 = (arg3 - (*(f32 *)((u8 *)arg1 + 0x18) + (arg10 * temp_fv1))) * ((arg5 + (temp_ft2 / (arg9 * temp_fv1))) * 0.5f);
    temp_fv0_2 = arg6 + temp_ft2;
    temp_fv1_2 = (temp_ft4 * temp_ft4) + (temp_fa0 * temp_fa0) + (temp_ft5 * temp_ft5);
    if (temp_fv1_2 < (temp_fv0_2 * temp_fv0_2)) {
        func_1505D408(arg0, arg1, temp_ft4, temp_fa0, temp_ft5, temp_fv1_2, temp_fv0_2, arg7);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505D5D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D5D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D6F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505DADC.s")
extern s32 D_80082FA0;
extern s32 D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505DDA8 CURRENT (2589) */
s8 func_1505DDA8(void *arg0, s32 arg1, s32 arg2, f32 arg3) {
    s16 sp6C;
    f32 sp68;
    f32 temp_fs0;
    s32 temp_s2;
    f32 sp64;
    s8 temp_t6;
    s8 var_s0;

    temp_s2 = arg2 & 0xFFFF;
    var_s0 = 0;
    if (D_80082FA0 >= 0) {
loop_2:
        if (*(&D_800CC2D0 + (var_s0 * 0x32C)) != 0) {
            temp_fs0 = *(f32 *)((u8 *)arg0 + 0x3C) * arg3 * 0.5f;
            if ((func_1505DF10(arg0, var_s0 & 0xFF, &sp6C, &sp68, &sp64, /* extra? */ 0) < (temp_fs0 * temp_fs0)) && ((((*(u16 *)((u8 *)arg0 + 0x76) - (u16) sp6C) + (temp_s2 / 2)) & 0xFFFF) < temp_s2)) {
                return var_s0;
            }
            goto block_7;
        }
block_7:
        temp_t6 = (var_s0 + 1) & 0xFF;
        var_s0 = temp_t6;
        if (D_80082FA0 < temp_t6) {
            goto block_8;
        }
        goto loop_2;
    }
block_8:
    return -1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505DDA8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505DDA8.s")
/* Call context: func_1505A630: unique active project prototype */
extern s32 D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505DF10 CURRENT (1733) */
f32 func_1505DF10(void *arg0, s32 arg1, s16 *arg2, f32 *arg3, f32 *arg4) {
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fa1;
    f32 temp_fa1_2;
    f32 temp_fv1;


    {
    void *temp_v0;
    temp_v0 = ((arg1 & 0xFF) * 0x32C) + &D_800CC2D0;
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x18) - *(f32 *)((u8 *)temp_v0 + 0x18);
    temp_fa0_2 = *(f32 *)((u8 *)temp_v0 + 0x14) - *(f32 *)((u8 *)arg0 + 0x14);
    *arg4 = temp_fv1;
    temp_fa1_2 = *(f32 *)((u8 *)arg0 + 0x1C) - *(f32 *)((u8 *)temp_v0 + 0x1C);
    }
    sp20 = temp_fa0_2;
    sp1C = temp_fv1;
    sp18 = temp_fa1_2;
    temp_fa0 = temp_fa0_2 * temp_fa0_2;
    *arg2 = func_1505A630(temp_fa0_2, temp_fa1_2, 0);
    temp_fa1 = temp_fa1_2 * temp_fa1_2;
    *arg3 = temp_fa0 + temp_fa1;
    return temp_fa0 + (temp_fv1 * temp_fv1) + temp_fa1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505DF10 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505DF10.s")
typedef struct Game83300Inner {
    u8 pad0[0x28];
    s32 field_28;
    u8 pad2C[4];
    s32 field_30;
    s32 field_34;
    u8 pad38[9];
    u8 field_41;
    u8 pad42[0x1CF];
    u8 field_211;
} Game83300Inner;

typedef struct Game83300Actor {
    u8 pad0[4];
    u8 field_4;
    u8 pad5[0x7F];
    s16 field_84;
    u8 pad86[0x24A];
    Game83300Inner *field_2D0;
} Game83300Actor;

void func_100226F0(void *, s32);
extern u16 D_800C4ED0[];

void func_1505DFDC(Game83300Actor *arg0) {
    s32 sp1C;
    Game83300Inner *sp18;
    u16 *temp_v1;

    sp18 = arg0->field_2D0;
    *(u16 *)&arg0->field_84 = 0xFFFF;
    if (sp18 != 0) {
        sp1C = arg0->field_4;
        sp18->field_28 = 0;
        func_100226F0((u8 *)sp18 + 0x40, 0x3A0);
        temp_v1 = &D_800C4ED0[sp1C];
        *(volatile u8 *)&sp18->field_41 = (u8)(*temp_v1 + 1);
        sp18->field_211 = (u8)(*temp_v1 + 1);
        *(volatile s32 *)&sp18->field_30 = 0;
        *(volatile s32 *)&sp18->field_34 = 0;
    }
}
/* Call context: func_10023A10: unique active project prototype */
void func_10023A10(void *, void *, s32);

void func_1505E060(u8 *arg0) {
    *(u16 *)((u8 *)arg0 + 6) = (u16) *(u16 *)((u8 *)arg0 + 4);
    *(f32 *)((u8 *)arg0 + 0xC) = (f32) *(f32 *)((u8 *)arg0 + 8);
    *(f32 *)((u8 *)arg0 + 0x14) = (f32) *(f32 *)((u8 *)arg0 + 0x10);
    *(f32 *)((u8 *)arg0 + 0x24) = (f32) *(f32 *)((u8 *)arg0 + 0x20);
    *(f32 *)((u8 *)arg0 + 0x1C) = (f32) *(f32 *)((u8 *)arg0 + 0x18);
    *(s8 *)((u8 *)arg0 + 0x39) = (s8) *(s8 *)((u8 *)arg0 + 0x38);
    *(s32 *)((u8 *)arg0 + 0x2C) = (s32) *(s32 *)((u8 *)arg0 + 0x28);
    func_10023A10(arg0 + 0x40, arg0 + 0x210, 0x1D0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505E0C4.s")
s32 func_150229E4(void *);
void func_1505DFDC(Game83300Actor *);
void func_1505E0C4(f32, Game83300Actor *, u16 *, Game83300Inner *, s32, s32, s32, s32, f32, f32, f32, f32, s32);
extern u8 D_800C3638;
extern u8 D_800C3654;
extern u16 D_800C5A90[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505E650 CURRENT (4967) */
void func_1505E650(Game83300Actor *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5, s32 arg6) {
    s32 sp40;
    Game83300Inner *sp38;
    Game83300Inner *temp_t0;
    f32 var_fa0;
    u16 *temp_a1;
    u16 temp_v0;
    u16 temp_v0_3;
    u8 temp_a2;
    u8 temp_v1;
    u8 *temp_v0_2;

    var_fa0 = *(f32 *)&arg3;
    temp_a2 = arg0->field_4;
    if (D_800C3638 != 0) {
        if (D_800C3654 == 0) {
            return;
        }
        sp40 = temp_a2;
        if (func_150229E4(arg0) != 0) {
            return;
        }
    }
    temp_v1 = arg0->field_4;
    if (temp_v1 == 0xFF) {
        return;
    }
    temp_v0 = D_800C5A90[temp_v1];
    if (temp_v0 == 0) {
        return;
    }
    temp_t0 = arg0->field_2D0;
    sp38 = temp_t0;
    if (temp_t0 == 0 || (u16)arg1 >= temp_v0) {
        return;
    }
    temp_v0_2 = D_800D1588[temp_a2];
    if (temp_v0_2 == 0) {
        func_1505DFDC(arg0);
        return;
    }
    if ((u16)arg1 >= D_800C5A90[temp_a2]) {
        return;
    }
    temp_a1 = (u16 *)(temp_v0_2 + (arg1 * 8));
    if (*(u16 *)temp_v0_2 == 0x3E7 || *temp_a1 == 0x3E7) {
        return;
    }
    temp_v0_3 = *temp_a1;
    if (temp_v0_3 >= 0x7530) {
        func_1505DFDC(arg0);
        return;
    }
    if (*(u8 *)((u8 *)arg0 + 0x2FF) == 0) {
        var_fa0 = 0.0f;
    }
    func_1505E0C4(var_fa0, arg0, temp_a1, sp38, 0, 0, arg1, 0, *(f32 *)&arg2, var_fa0, arg4, arg5, arg6);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505E650 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505E650.s")
u32 func_1505E7CC(s32 arg0, void *arg1) {
    u32 temp_v0_2;
    u32 var_v1;
    u8 *temp_a0;
    u8 *var_a1;
    u8 temp_v0;
    void *temp_v1;

    temp_v0 = *(u8 *)((u8 *)arg1 + 4);
    if (temp_v0 == 0xFF) {
        return 0U;
    }
    temp_v1 = D_800D1588[temp_v0];
    if (temp_v1 == 0) {
        return 0U;
    }
    temp_v0_2 = *(u32 *)((u8 *)temp_v1 + -4);
    if (temp_v0_2 == 0) {
        return 0U;
    }
    temp_v0_2 /= 24U;
    temp_a0 = *(u8 **)((u8 *)temp_v1 + -8);
    if (temp_a0 == 0) {
        return 0U;
    }
    var_v1 = 0;
    if (temp_v0_2 != 0) {
        var_a1 = temp_a0;
        do {
            if (arg0 == *var_a1) {
                return var_v1;
            }
            var_v1 += 1;
            var_a1 += 0x18;
        } while (var_v1 < temp_v0_2);
    }
    return 0U;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505E874.s")
void func_15060F28(u8 *, s32);
extern s32 D_800CC2D0;
extern s32 D_800CC4A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505ED34 CURRENT (715) */
u8 *func_1505ED34(void) {
    s32 var_v0;
    u8 *var_a0;

    var_v0 = 0;
    var_a0 = (u8 *)&D_800CC2D0;
    if (*(volatile s32 *)&D_800CC2D0 != 0) {
loop_1:
        var_v0 += 1;
        var_a0 += 0x32C;
        if (var_v0 < 0x19 && *(s32 *)var_a0 != 0) {
            goto loop_1;
        }
    }
    if (var_v0 == 0x19) {
        var_a0 = (u8 *)&D_800CC2D0;
        var_v0 = 0;
        if (*(volatile s32 *)&D_800CC2D0 != 0x27 || D_800CC4A4 != 0) {
loop_6:
            var_v0 += 1;
            var_a0 += 0x32C;
            if (var_v0 < 0x19 &&
                (*(s32 *)var_a0 != 0x27 || *(s32 *)(var_a0 + 0x1D4) != 0)) {
                goto loop_6;
            }
        }
        if (var_v0 != 0x19 && *(s32 *)var_a0 != 0) {
            func_15060F28(var_a0, 0);
        }
    }
    if (var_v0 == 0x19) {
        var_a0 = (u8 *)&D_800CC2D0;
        var_v0 = 0;
        if (*(volatile s32 *)&D_800CC2D0 != 0x27) {
loop_14:
            var_v0 += 1;
            var_a0 += 0x32C;
            if (var_v0 < 0x19 && *(s32 *)var_a0 != 0x27) {
                goto loop_14;
            }
        }
        if (var_v0 != 0x19 && *(s32 *)var_a0 != 0) {
            func_15060F28(var_a0, 0);
        }
    }
    if (var_v0 == 0x19 && *(s32 *)var_a0 != 0) {
        func_15060F28(var_a0, 0);
    }
    func_1505F188((u32)var_a0);
    return var_a0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505ED34 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505ED34.s")
extern s32 D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505EEB0 CURRENT (875) */
s32 *func_1505EEB0(s32 arg0, s32 *arg1) {
    s32 *var_v1;
    s32 var_a2;

    var_v1 = &D_800CC2D0;
    var_a2 = 0;
    if (arg0 != D_800CC2D0) {
loop_1:
        var_a2 += 1;
        var_v1 = (s32 *)((u8 *)var_v1 + 0x32C);
        if (var_a2 < 0x19) {
            if (arg0 != *var_v1) {
                goto loop_1;
            }
        }
    }
    *arg1 = var_a2;
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505EEB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505EEB0.s")
extern u8 D_800CC40F;
extern s32 D_800CC5FC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505EEF4 CURRENT (415) */
s32 *func_1505EEF4(s32 arg0) {
    u8 *var_v1;
    s32 var_v0;

    var_v1 = (u8 *)&D_800CC5FC;
    if ((D_800CC2D0 != 0) && (arg0 == D_800CC40F)) {
        return &D_800CC2D0;
    }
    var_v0 = 1;
loop_4:
    if ((*(s32 *)((u8 *)var_v1 + 0) != 0) && (arg0 == *(u8 *)((u8 *)var_v1 + 0x13F))) {
        return (s32 *)var_v1;
    }
    var_v1 += 0x32C;
    if ((*(s32 *)var_v1 != 0) && (arg0 == *(u8 *)(var_v1 + 0x13F))) {
        return (s32 *)var_v1;
    }
    var_v1 += 0x32C;
    if ((*(s32 *)var_v1 != 0) && (arg0 == *(u8 *)(var_v1 + 0x13F))) {
        return (s32 *)var_v1;
    }
    var_v1 += 0x32C;
    var_v0 += 4;
    if ((*(s32 *)var_v1 != 0) && (arg0 == *(u8 *)(var_v1 + 0x13F))) {
        return (s32 *)var_v1;
    }
    var_v1 += 0x32C;
    if (var_v0 == 0x19) {
        return 0;
    }
    goto loop_4;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505EEF4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505EEF4.s")
extern u8 D_800CC3F7;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505EFD0 CURRENT (420) */
s32 *func_1505EFD0(s32 arg0) {
    s32 *temp_v1;
    s32 *temp_v1_2;
    s32 *temp_v1_3;
    s32 *var_v1;
    s32 var_v0;

    var_v1 = &D_800CC5FC;
    if ((D_800CC2D0 != 0) && (arg0 == D_800CC3F7)) {
        return &D_800CC2D0;
    }
    var_v0 = 1;
loop_4:
    if ((*(s32 *)((u8 *)var_v1 + 0) != 0) && (arg0 == *(u8 *)((u8 *)var_v1 + 0x127))) {
        return var_v1;
    }
    temp_v1_3 = var_v1 + 0x32C;
    if ((*(s32 *)((u8 *)var_v1 + 0x32C) != 0) && (arg0 == *(u8 *)((u8 *)temp_v1_3 + 0x127))) {
        return temp_v1_3;
    }
    temp_v1_2 = temp_v1_3 + 0x32C;
    if ((*(s32 *)((u8 *)temp_v1_3 + 0x32C) != 0) && (arg0 == *(u8 *)((u8 *)temp_v1_2 + 0x127))) {
        return temp_v1_2;
    }
    temp_v1 = temp_v1_2 + 0x32C;
    var_v0 += 4;
    if ((*(s32 *)((u8 *)temp_v1_2 + 0x32C) != 0) && (arg0 == *(u8 *)((u8 *)temp_v1 + 0x127))) {
        return temp_v1;
    }
    var_v1 = temp_v1 + 0x32C;
    if (var_v0 == 0x19) {
        return 0;
    }
    goto loop_4;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505EFD0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505EFD0.s")
extern u8 D_800CC2D4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505F0AC CURRENT (420) */
s32 *func_1505F0AC(s32 arg0) {
    s32 *temp_v1;
    s32 *temp_v1_2;
    s32 *temp_v1_3;
    s32 *var_v1;
    s32 var_v0;

    var_v1 = &D_800CC5FC;
    if ((D_800CC2D0 != 0) && (arg0 == D_800CC2D4)) {
        return &D_800CC2D0;
    }
    var_v0 = 1;
loop_4:
    if ((*(s32 *)((u8 *)var_v1 + 0) != 0) && (arg0 == *(u8 *)((u8 *)var_v1 + 4))) {
        return var_v1;
    }
    temp_v1_3 = var_v1 + 0x32C;
    if ((*(s32 *)((u8 *)var_v1 + 0x32C) != 0) && (arg0 == *(u8 *)((u8 *)temp_v1_3 + 4))) {
        return temp_v1_3;
    }
    temp_v1_2 = temp_v1_3 + 0x32C;
    if ((*(s32 *)((u8 *)temp_v1_3 + 0x32C) != 0) && (arg0 == *(u8 *)((u8 *)temp_v1_2 + 4))) {
        return temp_v1_2;
    }
    temp_v1 = temp_v1_2 + 0x32C;
    var_v0 += 4;
    if ((*(s32 *)((u8 *)temp_v1_2 + 0x32C) != 0) && (arg0 == *(u8 *)((u8 *)temp_v1 + 4))) {
        return temp_v1;
    }
    var_v1 = temp_v1 + 0x32C;
    if (var_v0 == 0x19) {
        return 0;
    }
    goto loop_4;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505F0AC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505F0AC.s")
u32 func_150ADA20();                                /* extern */
extern f32 D_8009962C;
extern f32 D_80099630;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505F188 CURRENT (1275) */
void func_1505F188(u32 arg0) {
    u32 temp_v1;
    u32 var_v0;

    temp_v1 = arg0 + 0x32C;
    var_v0 = arg0;
    if (arg0 < temp_v1) {
        do {
            var_v0 += 4;
            *(s32 *)((u8 *)var_v0 + -4) = 0;
        } while (var_v0 < temp_v1);
    }
    *(s8 *)((u8 *)arg0 + 0x2FD) = 2;
    *(s16 *)((u8 *)arg0 + 0x38) = -0x2710;
    *(f32 *)((u8 *)arg0 + 0x14C) = 1.0f;
    *(f32 *)((u8 *)arg0 + 0x150) = 1.0f;
    *(f32 *)((u8 *)arg0 + 0x118) = (f32) D_8009962C;
    *(f32 *)((u8 *)arg0 + 0x180) = (f32) D_8009962C;
    *(s8 *)((u8 *)arg0 + 0x1DC) = 0xFF;
    *(s8 *)((u8 *)arg0 + 0x127) = 0xFF;
    *(s16 *)((u8 *)arg0 + 0x84) = 0xFFFF;
    *(s8 *)((u8 *)arg0 + 0x13F) = 0xFF;
    *(s32 *)((u8 *)arg0 + 0x2C4) = (s32) (arg0 + 4);
    *(s8 *)((u8 *)arg0 + 0x2C8) = 1;
    *(s8 *)((u8 *)arg0 + 0x2C9) = 1;
    *(s8 *)((u8 *)arg0 + 4) = 0xFF;
    *(s8 *)((u8 *)arg0 + 0x2CB) = 0x32;
    *(f32 *)((u8 *)arg0 + 0x48) = 1.0f;
    *(f32 *)((u8 *)arg0 + 0x24) = (f32) D_80099630;
    *(s8 *)((u8 *)arg0 + 0x6E) = (s8) ((func_150ADA20() % 50U) + 0x32);
    func_150615DC((void *) arg0);
    *(s8 *)((u8 *)arg0 + 0x1DD) = 0xFF;
    *(s8 *)((u8 *)arg0 + 0x1DE) = 0xFF;
    *(s8 *)((u8 *)arg0 + 0x1DF) = 0xFF;
    *(s16 *)((u8 *)arg0 + 0x18C) = 0;
    *(s16 *)((u8 *)arg0 + 0x18E) = 0;
    *(s16 *)((u8 *)arg0 + 0x190) = 0;
    *(s16 *)((u8 *)arg0 + 0x192) = 0;
    *(s16 *)((u8 *)arg0 + 0x194) = 0;
    *(s16 *)((u8 *)arg0 + 0x196) = 0xA;
    *(s16 *)((u8 *)arg0 + 0x198) = 0xA;
    *(s16 *)((u8 *)arg0 + 0x19A) = 0;
    *(s16 *)((u8 *)arg0 + 0x19C) = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505F188 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505F188.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505F298.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1506045C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060778.s")
typedef struct {
    u8 pad_0[0x318];
    void *field_318;
} Game83300DispatchState;

/* Call context: func_10010344: unique active project prototype */
s32 func_10010344(s32, s32, u32, s16, s32);
void func_10010630(u16, Game83300DispatchState *, s32, s32, s32);
void func_15060778(s32, Game83300DispatchState *, s32, s32, s32, s32, s32);

void func_15060A30(s32 arg0, Game83300DispatchState *arg1) {
    if (arg1->field_318 == 0) {
        func_10010344((u16)arg0, (s32)arg1, 0x6D60U, 0x1F4, 0x9C4);
        return;
    }
    func_15060778(arg0, arg1, 0x5DC0, 0, 0x1F4, 0x9C4, 1);
}

void func_15060A9C(s32 arg0, Game83300DispatchState *arg1) {
    if (arg1->field_318 == 0) {
        func_10010630((u16)arg0, arg1, 0x5DC0, 0x1F4, 0x9C4);
        return;
    }
    func_15060778(arg0, arg1, 0x5DC0, 0, 0x1F4, 0x9C4, 0);
}
void func_15060B04(s32 arg0, Game83300DispatchState *arg1, s32 arg2) {
    if (arg1->field_318 == 0) {
        func_10010630((u16)arg0, arg1, arg2, 0x1F4, 0x9C4);
        return;
    }
    func_15060778(arg0, arg1, (u16)arg2, 0, 0x1F4, 0x9C4, 0);
}
void func_10010154(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_15060B70(u16 arg0, s32 arg1) {
    func_10010154(arg0, arg1, 0x6D60, 0x1F4, 0x9C4);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15060BA4 CURRENT (35) */
s32 func_15060BA4(void *arg0, s32 arg1) {
    s32 temp_t6;
    s32 temp_v0;

    temp_v0 = *(u8 *)((u8 *)arg0 + 0x1CA);
    temp_t6 = temp_v0 + arg1;
    if (temp_v0 == 6) {
        return 0;
    }
    *(u8 *)((u8 *)arg0 + 0x1CA) = temp_t6;
    if ((temp_t6 & 0xFF) >= 7) {
        *(u8 *)((u8 *)arg0 + 0x1CA) = 6U;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15060BA4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060BA4.s")
typedef struct Game83300Motion {
    u8 pad0[0x10];
    f32 directionX;
    f32 directionY;
    f32 directionZ;
    u8 pad1C[0x14];
    f32 positionX;
    f32 positionY;
    f32 positionZ;
    u8 pad3C[4];
} Game83300Motion;

typedef struct Game83300MotionInfo {
    u8 pad0[0x14];
    s16 scale;
    u8 pad16[0x11];
    u8 motionIndex;
} Game83300MotionInfo;

typedef struct Game83300MotionOwner {
    u8 pad0[4];
    u8 index;
    u8 pad5[0xF];
    f32 fallbackX;
    f32 fallbackY;
    f32 fallbackZ;
    u8 pad20[0x130];
    f32 scale;
    u8 pad154[0x68];
    s16 resultX;
    s16 resultY;
    s16 resultZ;
    u8 pad1C2[0x12];
    Game83300Motion *motions;
} Game83300MotionOwner;

extern u8 D_800C3E90;
extern u8 *D_800D1C90[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15060BE0 CURRENT (850) */
void func_15060BE0(Game83300MotionOwner *arg0) {
    f32 z_component;
    f32 x_component;
    f32 y_component;
    f32 length;
    f32 factor;
    Game83300MotionInfo *info;
    Game83300Motion *motion;
    s32 valid = 0;

    if (arg0->index != 0xFF && arg0->motions != 0 && D_800C3E90 == 0) {
        info = (Game83300MotionInfo *)D_800D1C90[arg0->index];
        motion = &arg0->motions[info->motionIndex];
        length = (f32)info->scale * arg0->scale;
        if (length != 0.0f) {
            f32 dx = motion->directionX;
            f32 dy = motion->directionY;
            f32 dz = motion->directionZ;
            factor = sqrtf(dx * dx + dy * dy + dz * dz);
            if (factor != 0.0f) {
                factor = length / factor;
            }
            x_component = dx * factor;
            y_component = dy * factor;
            z_component = dz * factor;
        } else {
            x_component = 0.0f;
            z_component = 0.0f;
            y_component = 0.0f;
        }
        valid = 1;
        arg0->resultX = (s16)(s32)(motion->positionX + x_component);
        arg0->resultY = (s16)(s32)(motion->positionY + y_component);
        arg0->resultZ = (s16)(s32)(motion->positionZ + z_component);
    }
    if (valid == 0) {
        arg0->resultX = (s16)(s32)arg0->fallbackX;
        arg0->resultY = (s16)(s32)arg0->fallbackY;
        arg0->resultZ = (s16)(s32)arg0->fallbackZ;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15060BE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060BE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060D54.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060F28.s")
/* Call context: func_1505A630: unique active declaration in the allowed source */
extern f32 D_8009968C;
extern s32 D_800D2104;
extern s32 D_800D2108;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150611E8 CURRENT (20193) */
void func_150611E8(u8 *arg0, s32 arg1) {
    s32 sp30;
    f32 sp1C;
    f32 sp18;
    f32 var_ft4;
    f32 var_fv1;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_a0_5;
    s32 temp_a1;
    s32 temp_a1_2;
    u8 *temp_a2;
    s32 temp_ft1;
    s32 temp_ft3;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_8;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 var_a3;
    s32 var_t0;
    s32 var_t4;
    s32 var_t4_2;
    u16 temp_v0_7;
    u8 temp_t5;
    u8 *temp_a0_6;
    u8 *temp_a0_7;
    u8 *temp_v1_6;
    u8 *var_a2;
    u8 *var_a2_2;

    temp_t5 = *(u8 *)(D_800D2108 + arg1);
    if ((s32) temp_t5 >= 3) {
        temp_ft1 = (s32) *(f32 *)((u8 *)arg0 + 0x14);
        var_t0 = 0x7FFFFFFF;
        var_a3 = 0;
        temp_ft3 = (s32) *(f32 *)((u8 *)arg0 + 0x1C);
        temp_v0 = temp_t5 & 3;
        if ((s32) temp_t5 > 0) {
            if (temp_v0 != 0) {
                var_t4 = sp30;
                var_a2 = (void *)(*(u8 *)(D_800D2104 + (arg1 * 4)) + (0 * 8));
                do {
                    temp_a0 = (s16) temp_ft1 - *(s16 *)((u8 *)var_a2 + 0);
                    temp_a1 = (s16) temp_ft3 - *(s16 *)((u8 *)var_a2 + 4);
                    if (((temp_a0 * temp_a0) + (temp_a1 * temp_a1)) < var_t0) {
                        var_t4 = var_a3;
                        var_t0 = (temp_a0 * temp_a0) + (temp_a1 * temp_a1);
                    }
                    var_a3 += 1;
                    var_a2 += 8;
                } while (temp_v0 != var_a3);
                sp30 = var_t4;
                if (var_a3 != temp_t5) {
                    goto block_8;
                }
            } else {
block_8:
                var_t4 = sp30;
                var_a2_2 = (void *)(*(u8 *)(D_800D2104 + (arg1 * 4)) + (var_a3 * 8));
                do {
                    temp_a0_2 = (s16) temp_ft1 - *(s16 *)((u8 *)var_a2_2 + 0);
                    temp_a1_2 = (s16) temp_ft3 - *(s16 *)((u8 *)var_a2_2 + 4);
                    if (((temp_a0_2 * temp_a0_2) + (temp_a1_2 * temp_a1_2)) < var_t0) {
                        var_t4 = var_a3;
                        var_t0 = (temp_a0_2 * temp_a0_2) + (temp_a1_2 * temp_a1_2);
                    }
                    temp_v0_2 = (s16) temp_ft1 - *(s16 *)((u8 *)var_a2_2 + 8);
                    temp_v1 = (s16) temp_ft3 - *(s16 *)((u8 *)var_a2_2 + 0xC);
                    temp_a0_3 = (temp_v0_2 * temp_v0_2) + (temp_v1 * temp_v1);
                    if (temp_a0_3 < var_t0) {
                        var_t4 = var_a3 + 1;
                        var_t0 = temp_a0_3;
                    }
                    temp_v0_3 = (s16) temp_ft1 - *(s16 *)((u8 *)var_a2_2 + 0x10);
                    temp_v1_2 = (s16) temp_ft3 - *(s16 *)((u8 *)var_a2_2 + 0x14);
                    temp_a0_4 = (temp_v0_3 * temp_v0_3) + (temp_v1_2 * temp_v1_2);
                    if (temp_a0_4 < var_t0) {
                        var_t4 = var_a3 + 2;
                        var_t0 = temp_a0_4;
                    }
                    temp_v0_4 = (s16) temp_ft1 - *(s16 *)((u8 *)var_a2_2 + 0x18);
                    temp_v1_3 = (s16) temp_ft3 - *(s16 *)((u8 *)var_a2_2 + 0x1C);
                    temp_a0_5 = (temp_v0_4 * temp_v0_4) + (temp_v1_3 * temp_v1_3);
                    if (temp_a0_5 < var_t0) {
                        var_t4 = var_a3 + 3;
                        var_t0 = temp_a0_5;
                    }
                    var_a3 += 4;
                    var_a2_2 += 0x20;
                } while (var_a3 != temp_t5);
            }
            sp30 = var_t4;
        }
        var_t4_2 = sp30;
        if ((var_t4_2 != 0) && (temp_t5 != (var_t4_2 + 1))) {
            temp_a2 = (void *)(*(u8 *)(D_800D2104 + (arg1 * 4)));
            if (var_t0 >= 0x6D61) {
                temp_a0_6 = (void *)(temp_a2 + (var_t4_2 * 8));
                temp_v0_5 = (s16) temp_ft1 - *(s16 *)((u8 *)temp_a0_6 + 8);
                temp_v1_4 = (s16) temp_ft3 - *(s16 *)((u8 *)temp_a0_6 + 0xC);
                temp_v0_6 = (s16) temp_ft1 - *(s16 *)((u8 *)temp_a0_6 + -8);
                temp_v1_5 = (s16) temp_ft3 - *(s16 *)((u8 *)temp_a0_6 + -4);
                if (((temp_v0_6 * temp_v0_6) + (temp_v1_5 * temp_v1_5)) < ((temp_v0_5 * temp_v0_5) + (temp_v1_4 * temp_v1_4))) {
                    var_t4_2 -= 1;
                }
            }
            temp_a0_7 = (void *)(temp_a2 + (var_t4_2 * 8));
            temp_v0_7 = *(u16 *)((u8 *)temp_a0_7 + 0xE);
            if (temp_v0_7 == 0) {
                var_fv1 = 8.0f;
            } else {
                var_fv1 = (f32) temp_v0_7;
                if ((s32) temp_v0_7 < 0) {
                    var_fv1 += 4294967296.0f;
                }
            }
            var_ft4 = var_fv1 * D_8009968C;
            if (var_ft4 > 1.0f) {
                var_ft4 = 1.0f;
            }
            sp18 = var_ft4;
            sp1C = var_fv1;
            temp_v0_8 = func_1505A630((f32) (*(s16 *)((u8 *)temp_a0_7 + 8) - *(s16 *)((u8 *)temp_a0_7 + 0)), (f32) (*(s16 *)((u8 *)temp_a0_7 + 4) - *(s16 *)((u8 *)temp_a0_7 + 0xC)), 0);
            temp_v1_6 = (void *)(*(void **)((u8 *)arg0 + 0x31C));
            if ((temp_v1_6 != 0) && (var_fv1 > 20.0f)) {
                *(s16 *)((u8 *)temp_v1_6 + 0x68) = (s16) (temp_v0_8 | 1);
            }
            func_150593C4((s32) arg0, temp_v0_8 & 0xFFFF, var_fv1, var_ft4);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150611E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150611E8.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150615DC CURRENT (35) */
void func_150615DC(void *arg0) {
    s32 temp_v1;

    temp_v1 = 0xFF;
    *(u8 *)((u8 *)arg0 + 7) = temp_v1;
    *(u8 *)((u8 *)arg0 + 8) = temp_v1;
    *(s8 *)((u8 *)arg0 + 9) = 0;
    *(s8 *)((u8 *)arg0 + 0xA) = 0;
    *(s8 *)((u8 *)arg0 + 0xF) = 0;
    *(u8 *)((u8 *)arg0 + 0xE) = temp_v1;
    *(u8 *)((u8 *)arg0 + 0xD) = temp_v1;
    *(u8 *)((u8 *)arg0 + 0xC) = temp_v1;
    *(u8 *)((u8 *)arg0 + 0xB) = temp_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150615DC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150615DC.s")
extern s32 D_800DBFF4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506160C CURRENT (1990) */
void func_1506160C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4) {
    s32 temp_a3;
    s32 temp_t6;
    s32 var_v1;
    s8 var_a2;
    u8 temp_t7;

    temp_t6 = arg1 & 0xFF;
    temp_t7 = arg2 & 0xFF;
    if (temp_t6 >= 8) {
        if (temp_t6 != 0xA) {
            if (temp_t6 == 8) {
                var_v1 = 1 << arg4;
                *(u8 *)((u8 *)arg0 + 0xF) = (u8) (*(u8 *)((u8 *)arg0 + 0xF) | var_v1);
                var_a2 = 0;
            } else {
                var_a2 = 0xFF;
                var_v1 = 1 << arg4;
                *(u8 *)((u8 *)arg0 + 0xF) = (u8) (*(u8 *)((u8 *)arg0 + 0xF) & ~var_v1);
            }
            temp_a3 = var_v1 * 0x10;
            if (*(u8 *)((u8 *)arg0 + 0xF) & temp_a3) {
                *(s8 *)((u8 *)(arg0 + arg4) + 0xB) = var_a2;
            }
            *(u8 *)((u8 *)arg0 + 0xF) = (u8) (*(u8 *)((u8 *)arg0 + 0xF) & ~temp_a3);
        } else {
            var_a2 = 0;
            *(u8 *)((u8 *)arg0 + 0xF) = (u8) (*(u8 *)((u8 *)arg0 + 0xF) | ((1 << arg4) * 0x10));
        }
        if ((*(u8 *)((u8 *)arg0 + 0x2FD) != 0) || (*(&D_800DBFF4 + arg4) != 0)) {
            *(s8 *)((u8 *)(arg0 + arg4) + 0xB) = var_a2;
        }
    } else if (temp_t6 >= (s32) *(u8 *)((u8 *)arg0 + 0xA)) {
        if (temp_t6 == 4) {
            *(u8 *)((u8 *)arg0 + 0xA) = (u8) temp_t6;
            *(u8 *)((u8 *)arg0 + 7) = 0U;
            *(u8 *)((u8 *)arg0 + 8) = 0xFFU;
            *(s8 *)((u8 *)arg0 + 9) = 0x20;
        } else if (temp_t6 == 5) {
            *(u8 *)((u8 *)arg0 + 0xA) = (u8) temp_t6;
            *(u8 *)((u8 *)arg0 + 8) = 0U;
            *(s8 *)((u8 *)arg0 + 9) = 0x20;
        } else if (temp_t6 == 6) {
            *(u8 *)((u8 *)arg0 + 0xA) = (u8) temp_t6;
            *(u8 *)((u8 *)arg0 + 8) = 0U;
            *(s8 *)((u8 *)arg0 + 9) = 8;
        } else if (temp_t6 == 2) {
            *(u8 *)((u8 *)arg0 + 0xA) = (u8) temp_t6;
            *(u8 *)((u8 *)arg0 + 8) = temp_t7;
            *(s8 *)((u8 *)arg0 + 9) = (s8) (arg3 & 0xFF);
        } else if (temp_t6 == 1) {
            *(u8 *)((u8 *)arg0 + 0xA) = 0U;
            *(u8 *)((u8 *)arg0 + 7) = temp_t7;
            *(u8 *)((u8 *)arg0 + 8) = temp_t7;
        }
        if (D_800DBFF4 != 0) {
            *(u8 *)((u8 *)arg0 + 7) = (u8) *(u8 *)((u8 *)arg0 + 8);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506160C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1506160C.s")
/* Call context: func_15060F28: unique active project prototype */
void func_15060F28(u8 *, s32);
extern s32 D_80082FA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150617BC CURRENT (3665) */
void func_150617BC(u8 *arg0) {
    s32 var_a0;
    s32 var_a2;
    s32 var_a3;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    u8 *var_a1;
    u8 temp_v0;
    u8 temp_v1;
    u8 temp_v1_2;
    u8 temp_v1_3;
    u8 var_a0_2;

    if (*(s32 *)((u8 *)arg0 + 0) != 0) {
        var_a0 = D_80082FA0;
        var_a3 = 1;
        var_a2 = 0;
        var_a1 = arg0;
        if (var_a0 >= 0) {
            do {
                var_a3 *= 2;
                if (*(u8 *)((u8 *)arg0 + 0xF) & var_a3) {
                    temp_v1 = *(u8 *)((u8 *)var_a1 + 0xB);
                    if ((s32) temp_v1 > 0) {
                        var_v0 = 0;
                        if (*(&D_800DBFF4 + var_a2) == 0) {
                            var_v0 = temp_v1 - 0x32;
                            if (var_v0 < 0) {
                                var_v0 = 0;
                            }
                        }
                        *(u8 *)((u8 *)var_a1 + 0xB) = (u8) var_v0;
                        goto block_14;
                    }
                } else {
                    temp_v1_2 = *(u8 *)((u8 *)var_a1 + 0xB);
                    if ((s32) temp_v1_2 < 0xFF) {
                        var_v0_2 = 0xFF;
                        if (*(&D_800DBFF4 + var_a2) == 0) {
                            var_v0_2 = temp_v1_2 + 0x32;
                            if (var_v0_2 >= 0x100) {
                                var_v0_2 = 0xFF;
                            }
                        }
                        *(u8 *)((u8 *)var_a1 + 0xB) = (u8) var_v0_2;
block_14:
                        var_a0 = D_80082FA0;
                    }
                }
                var_a2 += 1;
                var_a1 += 1;
            } while (var_a0 >= var_a2);
        }
        if (*(u8 *)((u8 *)arg0 + 0xA) != 0) {
            temp_v1_3 = *(u8 *)((u8 *)arg0 + 8);
            var_a0_2 = *(u8 *)((u8 *)arg0 + 7);
            if (temp_v1_3 != var_a0_2) {
                if ((s32) var_a0_2 < (s32) temp_v1_3) {
                    var_v0_3 = var_a0_2 + *(u8 *)((u8 *)arg0 + 9);
                    if ((s32) temp_v1_3 < var_v0_3) {
                        goto block_22;
                    }
                } else {
                    var_v0_3 = var_a0_2 - *(u8 *)((u8 *)arg0 + 9);
                    if (var_v0_3 < (s32) temp_v1_3) {
block_22:
                        var_v0_3 = (s32) temp_v1_3;
                    }
                }
                *(u8 *)((u8 *)arg0 + 7) = (u8) var_v0_3;
                var_a0_2 = var_v0_3 & 0xFF;
            }
            if (*(u8 *)((u8 *)arg0 + 8) == var_a0_2) {
                temp_v0 = *(u8 *)((u8 *)arg0 + 0xA);
                if (temp_v0 == 6) {
                    func_15060F28(arg0, 1);
                    return;
                }
                if (temp_v0 == 5) {
                    func_15060F28(arg0, 2);
                    return;
                }
                *(u8 *)((u8 *)arg0 + 0xA) = 0U;
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150617BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150617BC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506196C CURRENT (470) */
s32 func_1506196C(u8 *arg0, s32 arg1) {
    s32 temp_lo;
    s32 var_v1;

    temp_lo = *(u8 *)((u8 *)(arg0 + arg1) + 0xB) * *(u8 *)((u8 *)arg0 + 7);
    var_v1 = temp_lo >> 8;
    if (temp_lo == 0xFE01) {
        var_v1 = 0xFF;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506196C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1506196C.s")
s32 func_150623F4(u8 *);                            /* extern */
void *func_15083E90(u8);                            /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150619A8 CURRENT (3555) */
void func_150619A8(void) {
    u8 sp5C;
    s32 *var_s0;
    s32 var_s0_2;
    s32 var_s4_2;
    s32 var_s6;
    u8 *var_s5;
    u8 temp_a0;
    u8 temp_v0;
    u8 var_s4;
    u8 *temp_s3;
    u8 *temp_v0_2;
    u8 *var_s1;

    var_s6 = 0;
    var_s0 = &D_800CC2D0;
    var_s4 = 0;
    do {
        if (*(s32 *)((u8 *)var_s0 + 0) != 0) {
            temp_v0 = *(u8 *)((u8 *)var_s0 + 0x2FD);
            if (temp_v0 != 0) {
                *(u8 *)((u8 *)var_s0 + 0x2FD) = (u8) (temp_v0 - 1);
            }
            func_150617BC((u8 *) var_s0);
            if (func_150623F4((u8 *) var_s0) != 0) {
                *(u8 *)((u8 *)var_s0 + 0x2FA) = (u8) (*(u8 *)((u8 *)var_s0 + 0x2FA) | 1);
            } else {
                *(u8 *)((u8 *)var_s0 + 0x2FA) = (u8) (*(u8 *)((u8 *)var_s0 + 0x2FA) & ~1);
                if ((*(u8 *)((u8 *)var_s0 + 0x20B) != 0) || (*(u8 *)((u8 *)var_s0 + 0x20C) != 0) || (*(u8 *)((u8 *)var_s0 + 0x20D) != 0) || (*(u8 *)((u8 *)var_s0 + 0x20E) != 0)) {
                    (&sp5C)[var_s6] = var_s4;
                    var_s6 += 1;
                }
            }
        }
        var_s4 += 1;
        var_s0 += 0x32C;
    } while ((s32) var_s4 < 0x19);
    if (var_s6 != 0) {
        var_s4_2 = 0;
        if (var_s6 > 0) {
            var_s5 = &sp5C;
            do {
                temp_s3 = (void *)((*var_s5 * 0x32C) + &D_800CC2D0);
                var_s1 = temp_s3;
                var_s0_2 = 0;
loop_16:
                temp_a0 = *(u8 *)((u8 *)var_s1 + 0x20B);
                if ((temp_a0 != 0) && (temp_v0_2 = func_15083E90(temp_a0), (temp_v0_2 != 0)) && (*(u8 *)((u8 *)temp_v0_2 + 0x2FA) & 1)) {
                    *(u8 *)((u8 *)temp_s3 + 0x2FA) = (u8) (*(u8 *)((u8 *)temp_s3 + 0x2FA) | 1);
                } else {
                    var_s0_2 += 1;
                    var_s1 += 1;
                    if (var_s0_2 != 4) {
                        goto loop_16;
                    }
                }
                var_s4_2 += 1;
                var_s5 += 1;
            } while (var_s4_2 != var_s6);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150619A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150619A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15061B4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150623F4.s")
extern s32 D_800D121C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150626EC CURRENT (1139) */
void func_150626EC(s32 arg0, s32 arg1) {
    s32 var_v0;
    u8 *var_s0;
    u8 *var_s3;

    var_s0 = (u8 *)&D_800CC2D0;
    var_s3 = (u8 *)&D_800CC2D0;
    var_v0 = 0;
    do {
        if ((*(s32 *)var_s0 != 0) && ((((arg0 - (s32)var_s3) / 812) + 1) == var_s0[0x65]) && (var_s0[0x127] == 0xFF)) {
            func_15060F28(var_s0, arg1);
        }
        var_s0 += 0x32C;
    } while (var_s0 != (u8 *)&D_800D121C);
    (void)var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150626EC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150626EC.s")
void func_1503B840(void *arg0);
void func_15039CC8(void *arg0);

void func_150627D4(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x2FB) = 0;
    func_1503B840(arg0);
    func_15039CC8(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062800.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15062AC4 CURRENT (260) */
void func_15062AC4(void *arg0) {
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_v0;
    s16 temp_v1;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0xE6);
    if (temp_v0 != 0) {
        temp_v1 = *(s16 *)((u8 *)arg0 + 0xE4);
        if (temp_v1 != 0) {
            temp_fv0 = (f32) temp_v1;
            temp_fv1 = (f32) temp_v0;
            *(f32 *)((u8 *)arg0 + 0xEC) = (f32) (temp_fv0 / temp_fv1);
            *(f32 *)((u8 *)arg0 + 0xF0) = (f32) (temp_fv1 / temp_fv0);
            return;
        }
    }
    *(f32 *)((u8 *)arg0 + 0xEC) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0xF0) = 0.0f;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15062AC4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062AC4.s")
void func_15062AC4(void *);
void func_15062B84(void *);

void func_15062B1C(void *arg0, f32 arg1) {
    *(s16 *)((u8 *)arg0 + 0xE4) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x14C) * arg1);
    func_15062AC4(arg0);
}
void func_15062B50(void *arg0, f32 arg1) {
    *(s16 *)((u8 *)arg0 + 0xE6) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x150) * arg1);
    func_15062AC4(arg0);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15062B84 CURRENT (260) */
void func_15062B84(void *arg0) {
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_v0;
    s16 temp_v1;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0xD4);
    if (temp_v0 != 0) {
        temp_v1 = *(s16 *)((u8 *)arg0 + 0xD2);
        if (temp_v1 != 0) {
            temp_fv0 = (f32) temp_v1;
            temp_fv1 = (f32) temp_v0;
            *(f32 *)((u8 *)arg0 + 0xDC) = (f32) (temp_fv0 / temp_fv1);
            *(f32 *)((u8 *)arg0 + 0xE0) = (f32) (temp_fv1 / temp_fv0);
            return;
        }
    }
    *(f32 *)((u8 *)arg0 + 0xDC) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0xE0) = 0.0f;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15062B84 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062B84.s")
extern u8 *D_800D1C90[];

void func_15062BDC(u8 *arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0;
    f32 temp_fv1;
    u8 temp_v1;
    u8 *temp_v0;

    temp_v1 = arg0[4];
    *(f32 *)(arg0 + 0x14C) = arg1;
    *(f32 *)(arg0 + 0x150) = arg2;
    if (temp_v1 != 0xFF) {
        temp_v0 = D_800D1C90[temp_v1];
        temp_fv1 = *(f32 *)(arg0 + 0x14C);
        temp_fv0 = *(f32 *)(arg0 + 0x150);
        *(s16 *)(arg0 + 0xD2) =
            (s16)(s32)((f32)*(s16 *)(temp_v0 + 0x20) * temp_fv1);
        *(s16 *)(arg0 + 0xD4) =
            (s16)(s32)((f32)*(s16 *)(temp_v0 + 0x22) * temp_fv0);
        *(s16 *)(arg0 + 0xD6) =
            (s16)(s32)((f32)*(s16 *)(temp_v0 + 0x24) * temp_fv0);
        *(s16 *)(arg0 + 0xE4) =
            (s16)(s32)((f32)*(s16 *)(temp_v0 + 0x1A) * temp_fv1);
        *(s16 *)(arg0 + 0xE6) =
            (s16)(s32)((f32)*(s16 *)(temp_v0 + 0x1C) * temp_fv0);
        *(s16 *)(arg0 + 0xE8) =
            (s16)(s32)((f32)*(s16 *)(temp_v0 + 0x1E) * temp_fv0);
        func_15062AC4(arg0);
        func_15062B84(arg0);
    }
}
extern u8 D_800C4488[];
extern u8 D_800D19A0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15062D10 CURRENT (1826) */
void func_15062D10(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   s32 arg5) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_v0;
    s32 var_v1;
    u8 *temp_a3;

    temp_v0 = arg0 * 4;
    if (*(s32 *)(D_800D19A0 + temp_v0) != 0) {
        temp_a3 = *(u8 **)(*(u8 **)(D_800C4488 + temp_v0) +
                              (arg4 * 4)) +
                  (arg1 * 8);
        temp_a2 = *(s32 *)(temp_a3 + 4);
        temp_v1 = ((temp_a2 >> 0xC) & 0xFFF) + 2;
        temp_a0 = (temp_a2 & 0xFFF) + 2;
        temp_a2_2 = *(s32 *)temp_a3;
        if (arg5 != 0) {
            var_v0 = arg2 & 0xFFF;
        } else {
            temp_a1 = ((temp_a2_2 >> 0xC) & 0xFFF) + arg2;
            var_v0 = temp_a1;
            if (temp_v1 < temp_a1) {
                var_v0 = temp_a1 - temp_v1;
            } else if (temp_a1 < 0) {
                var_v0 = temp_a1 + temp_v1;
            }
        }
        if (arg5 != 0) {
            var_v1 = arg3 & 0xFFF;
        } else {
            temp_a1_2 = (temp_a2_2 & 0xFFF) + arg3;
            var_v1 = temp_a1_2;
            if (temp_a0 < temp_a1_2) {
                var_v1 = temp_a1_2 - temp_a0;
            } else if (temp_a1_2 < 0) {
                var_v1 = temp_a1_2 + temp_a0;
            }
        }
        *(s32 *)temp_a3 = (temp_a2_2 & 0xFF000000) |
                           (var_v1 & 0xFFF) | ((var_v0 & 0xFFF) << 0xC);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15062D10 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062D10.s")
void func_15094AB8(s32, s32, s32, f32, s32, s32);
extern u8 D_800BE9C0;
extern u8 *D_800C5338[];
extern void *D_800C6360[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15062E24 CURRENT (2370) */
void func_15062E24(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   s32 arg5, s32 arg6) {
    u8 *actor;
    u8 *table;
    u8 *entry;
    u8 *target;
    s32 i;
    u16 width;
    u16 height;

    table = (u8 *)&D_800C6360[arg0];
    i = 0;
    if (*(s32 *)table != 0) {
        actor = (u8 *)&D_800CC2D0;
        do {
            if (*(s32 *)actor != 0 && actor[4] == arg0 && actor[0x2FA] != 0) {
                entry = D_800C5338[arg0] + (arg5 * 0xC);
                width = *(u16 *)(entry + 8);
                height = *(u16 *)(entry + 0xA);
                if (arg6 != 0) {
                    width *= 2;
                    height *= 2;
                }
                target = (u8 *)&D_800CC2D0 + (i * 0x32C) + (D_800BE9C0 * 4);
                target = *(u8 **)(target + 0x28C);
                if (target != 0) {
                    func_15094AB8((s32)target + (arg1 * 0x10),
                                   *(s32 *)table + (arg3 * 4), arg2,
                                   (f32)arg4, height, width);
                }
            }
            i++;
            actor += 0x32C;
        } while (i != 0x19);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15062E24 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062E24.s")
typedef struct Game83300MorphVertex {
    u8 pad0[8];
    s16 x;
    s16 y;
    u8 padC[4];
} Game83300MorphVertex;

typedef struct Game83300MorphObject {
    u8 pad0[4];
    u8 modelIndex;
    u8 pad5[0x1C3];
    u8 channel;
    u8 pad1C9[0xC3];
    Game83300MorphVertex *buffers[4];
} Game83300MorphObject;

extern s32 *D_800C4020[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15062FC0 CURRENT (315) */
void func_15062FC0(Game83300MorphObject *arg0, s32 arg1, u8 arg2,
                   s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    u8 *channelBase;
    Game83300MorphVertex *source;
    Game83300MorphVertex *target;
    s32 offset;
    s32 i;

    channelBase = (u8 *)arg0 + (arg0->channel * 8);
    target = *(Game83300MorphVertex **)(channelBase + 0x28C + D_800BE9C0 * 4);
    source = *(Game83300MorphVertex **)(channelBase + 0x28C + (D_800BE9C0 == 0) * 4);
    if (target == 0) {
        return;
    }
    if (arg1 != -1) {
        offset = D_800C4020[arg0->modelIndex][arg1] * 0x10;
        target = (Game83300MorphVertex *)((u8 *)target + offset);
        source = (Game83300MorphVertex *)((u8 *)source + offset);
    }
    if (arg6 != 0) {
        if (arg3 < target->x) {
            arg6 -= arg3;
        } else if (target->x < 0) {
            arg6 += arg3;
        }
    }
    if (arg7 != 0) {
        if (arg4 < target->y) {
            arg7 -= arg4;
        } else if (target->y < 0) {
            arg7 += arg4;
        }
    }
    for (i = 0; i < arg5; i++) {
        target[i].x = source[i].x + arg6;
        target[i].y = source[i].y + arg7;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15062FC0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062FC0.s")
typedef struct Game83300Nested63168 {
    u8 pad0[0x1AC];
    u8 active;
} Game83300Nested63168;

typedef struct Game83300Actor63168 {
    u8 pad0[0x31C];
    Game83300Nested63168 *nested;
    u8 pad320[0xC];
} Game83300Actor63168;

void func_15194FF4(Game83300Actor63168 *, Game83300Actor63168 *, s32);
extern s8 D_8008FD8C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15063168 CURRENT (675) */
void func_15063168(Game83300Actor63168 *arg0) {
    Game83300Actor63168 *other;
    Game83300Nested63168 *nested;
    s32 index;
    s32 self_index;

    index = 0;
    if (D_8008FD8C > 0) {
        self_index = ((s32)arg0 - (s32)&D_800CC2D0) / 0x32C;
        do {
            if ((index != self_index) && ((1 << index) & D_800CC268)) {
                other = (Game83300Actor63168 *)((u8 *)&D_800CC2D0 + (index * 0x32C));
                nested = other->nested;
                if ((nested != 0) && (nested->active == 0)) {
                    func_15194FF4(arg0, other, 1);
                }
            }
            index++;
        } while (index < D_8008FD8C);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15063168 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15063168.s")
void func_15082A44(void *, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15063254 CURRENT (1620) */
void func_15063254(u8 *arg0, s32 arg1, s32 arg2, f32 arg3) {
    s32 sp50;
    void *sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    s32 sp2C;
    f32 temp_fv0;
    f32 temp_fv1;
    u16 temp_v0;
    void *temp_s1;

    sp50 = arg0[0x13F];
    temp_s1 = *(void **)(arg0 + 0x144);
    *(s8 *)((u8 *)temp_s1 + 4) = arg1;
    *(s8 *)((u8 *)temp_s1 + 3) = arg2;
    *(f32 *)((u8 *)temp_s1 + 0x20) = arg3;
    *(f32 *)((u8 *)temp_s1 + 0x24) = arg3;
    *(s8 *)((u8 *)temp_s1 + 2) = 0;
    sp48 = *(void **)(arg0 + 0x318);
    temp_fv0 = *(f32 *)(arg0 + 0x14);
    temp_fv1 = *(f32 *)(arg0 + 0x18);
    sp3C = *(f32 *)(arg0 + 0x1C);
    sp38 = *(f32 *)(arg0 + 0xB8);
    sp34 = *(f32 *)(arg0 + 0x40);
    sp30 = *(f32 *)(arg0 + 0xC4);
    temp_v0 = *(u16 *)(arg0 + 0x76);
    sp44 = temp_fv0;
    sp40 = temp_fv1;
    sp2C = temp_v0;
    func_15060F28(arg0, 0);
    func_15082A44(temp_s1, sp50, 0, 0,
                  (((s32)arg0 - (s32)&D_800CC2D0) / 812) + 1);
    *(f32 *)(arg0 + 0x14) = temp_fv0;
    *(f32 *)(arg0 + 0x18) = temp_fv1;
    *(void **)(arg0 + 0x318) = sp48;
    *(f32 *)(arg0 + 0x1C) = sp3C;
    *(f32 *)(arg0 + 0xB8) = sp38;
    *(f32 *)(arg0 + 0x40) = sp34;
    *(u16 *)(arg0 + 0x76) = temp_v0;
    *(u16 *)(arg0 + 0x7A) = temp_v0;
    *(f32 *)(arg0 + 0x2C) = temp_fv0;
    *(f32 *)(arg0 + 0x30) = temp_fv1;
    *(f32 *)(arg0 + 0x1CC) = *(f32 *)(arg0 + 0x18);
    *(f32 *)(arg0 + 0x34) = *(f32 *)(arg0 + 0x1C);
    *(f32 *)(arg0 + 0xC4) = sp30;
    *(s32 *)((u8 *)sp48 + 0x3D4) = *(s32 *)(arg0 + 0x31C);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15063254 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15063254.s")
