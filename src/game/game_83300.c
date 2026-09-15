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
 * - func_1505A72C
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
 * - func_1505DFDC
 * - func_1505E0C4
 * - func_1505E650
 * - func_1505E7CC
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
 * - func_15062BDC
 * - func_15062D10
 * - func_15062E24
 * - func_15062FC0
 * - func_15063168
 * - func_15063254
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15055E50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15056150.s")
extern f32 D_80099444;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15056258 CURRENT (3780) */
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
    if (!(var_fa0 < 0.0f) && !(fabsf(temp_fv1) > 30.0f)) {
        if (var_fa0 > 300.0f) {
            var_fa0 = 300.0f;
        }
        *(f32 *)((u8 *)arg0 + 0x18) = (f32) (temp_fa1 + (var_fa0 * temp_fv1 * D_80099444));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15056258 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15056258.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150562FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505693C.s")
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505A5CC CURRENT (2035) */
f32 func_1505A5CC(void *arg0) {
    f32 temp_fa0;
    f32 temp_fv1;

    temp_fv1 = (f32) *(s8 *)((u8 *)arg0 + 2);
    temp_fa0 = (f32) *(s8 *)((u8 *)arg0 + 3);
    {
        f32 var_fv1 = sqrtf((temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0)) * D_800994D4;
    if (var_fv1 > 35.0f) {
        var_fv1 = 35.0f;
    }
    return var_fv1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505A5CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A5CC.s")
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505A72C CURRENT (1075) */
f32 func_1505A72C(void *arg0, void *arg1) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv1;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x14) - *(f32 *)((u8 *)arg1 + 0x14);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x1C) - *(f32 *)((u8 *)arg1 + 0x1C);
    temp_fa1 = *(f32 *)((u8 *)arg0 + 0x18) - *(f32 *)((u8 *)arg1 + 0x18);
    return sqrtf((temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0) + (temp_fa1 * temp_fa1));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505A72C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A72C.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D024.s")
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
f32 func_150AD780(f32, f32);                        /* extern */
f32 func_150AD78C(f32);                             /* extern */
extern f32 D_80099520;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505D34C CURRENT (1150) */
f32 func_1505D34C(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4) {
    f32 sp24;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 var_fa1;

    var_fa1 = arg1;
    if (arg3 != 1.0f) {
        var_fa1 *= arg3;
        arg2 *= arg3;
    }
    arg1 = var_fa1;
    temp_fa0 = (arg0 - 90.0f) * D_80099520;
    {
        f32 sp18 = temp_fa0;
    sp24 = func_150AD780(temp_fa0, var_fa1);
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505DFDC CURRENT (185) */
void func_1505DFDC(Game83300Actor *arg0) {
    s32 sp1C;
    Game83300Inner *sp18;
    u16 *temp_v1;

    sp18 = arg0->field_2D0;
    arg0->field_84 = -1;
    if (sp18 != 0) {
        sp1C = arg0->field_4;
        sp18->field_28 = 0;
        func_100226F0((u8 *)sp18 + 0x40, 0x3A0);
        temp_v1 = &D_800C4ED0[sp1C];
        sp18->field_41 = (u8)(*temp_v1 + 1);
        sp18->field_30 = 0;
        sp18->field_34 = 0;
        sp18->field_211 = (u8)(*temp_v1 + 1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505DFDC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505DFDC.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505E650.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505E7CC CURRENT (1065) */
u32 func_1505E7CC(s32 arg0, void *arg1) {
    u32 temp_lo;
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
    temp_lo = temp_v0_2 / 24U;
    temp_a0 = *(u8 **)((u8 *)temp_v1 + -8);
    if (temp_a0 == 0) {
        return 0U;
    }
    var_v1 = 0;
    if (temp_lo != 0) {
        var_a1 = temp_a0;
loop_10:
        if (arg0 == *var_a1) {
            return var_v1;
        }
        var_v1 += 1;
        var_a1 += 0x18;
        if (var_v1 >= temp_lo) {
            /* Duplicate return node #13. Try simplifying control flow for better match */
            return 0U;
        }
        goto loop_10;
    }
    return 0U;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505E7CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505E7CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505E874.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505ED34.s")
extern s32 D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505EEB0 CURRENT (780) */
s32 *func_1505EEB0(s32 arg0, s32 *arg1) {
    s32 *var_v1;
    s32 var_a2;

    var_v1 = &D_800CC2D0;
    var_a2 = 0;
    if (arg0 != D_800CC2D0) {
loop_1:
        var_a2 += 1;
        var_v1 += 0x32C;
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505EEF4 CURRENT (420) */
s32 *func_1505EEF4(s32 arg0) {
    s32 *temp_v1;
    s32 *temp_v1_2;
    s32 *temp_v1_3;
    s32 *var_v1;
    s32 var_v0;

    var_v1 = &D_800CC5FC;
    if ((D_800CC2D0 != 0) && (arg0 == D_800CC40F)) {
        return &D_800CC2D0;
    }
    var_v0 = 1;
loop_4:
    if ((*(s32 *)((u8 *)var_v1 + 0) != 0) && (arg0 == *(u8 *)((u8 *)var_v1 + 0x13F))) {
        return var_v1;
    }
    temp_v1_3 = var_v1 + 0x32C;
    if ((*(s32 *)((u8 *)var_v1 + 0x32C) != 0) && (arg0 == *(u8 *)((u8 *)temp_v1_3 + 0x13F))) {
        return temp_v1_3;
    }
    temp_v1_2 = temp_v1_3 + 0x32C;
    if ((*(s32 *)((u8 *)temp_v1_3 + 0x32C) != 0) && (arg0 == *(u8 *)((u8 *)temp_v1_2 + 0x13F))) {
        return temp_v1_2;
    }
    temp_v1 = temp_v1_2 + 0x32C;
    var_v0 += 4;
    if ((*(s32 *)((u8 *)temp_v1_2 + 0x32C) != 0) && (arg0 == *(u8 *)((u8 *)temp_v1 + 0x13F))) {
        return temp_v1;
    }
    var_v1 = temp_v1 + 0x32C;
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15060BA4 CURRENT (115) */
s32 func_15060BA4(void *arg0, s32 arg1) {
    u8 temp_t6;
    u8 temp_v0;

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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150615DC CURRENT (135) */
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506196C CURRENT (540) */
s32 func_1506196C(u8 *arg0, s32 arg1) {
    s32 temp_lo;
    s32 var_v1;

    temp_lo = *(u8 *)((u8 *)(arg0 + arg1) + 0xB) * *(u8 *)((u8 *)arg0 + 7);
    if (temp_lo == 0xFE01) {
        var_v1 = 0xFF;
    } else {
        var_v1 = temp_lo >> 8;
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150626EC.s")
void func_1503B840(void *arg0);
void func_15039CC8(void *arg0);

void func_150627D4(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x2FB) = 0;
    func_1503B840(arg0);
    func_15039CC8(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062800.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15062AC4 CURRENT (170) */
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
void func_15062B1C(void *arg0, f32 arg1) {
    *(s16 *)((u8 *)arg0 + 0xE4) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x14C) * arg1);
    func_15062AC4(arg0);
}
void func_15062B50(void *arg0, f32 arg1) {
    *(s16 *)((u8 *)arg0 + 0xE6) = (s16) (s32) (*(f32 *)((u8 *)arg0 + 0x150) * arg1);
    func_15062AC4(arg0);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15062B84 CURRENT (170) */
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062BDC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062D10.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062E24.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062FC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15063168.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15063254.s")
