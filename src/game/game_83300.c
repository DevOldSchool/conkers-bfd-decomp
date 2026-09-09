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
 * - func_1505A6F8
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
 * - func_1505E060
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
 * - func_15060A30
 * - func_15060A9C
 * - func_15060B04
 * - func_15060B70
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
 * - func_150627D4
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15058EA4 CURRENT (35) */
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150593C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15059444.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505959C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150597FC.s")
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505A6F8 CURRENT (20) */
f32 func_1505A6F8(void *arg0, void *arg1) {
    f32 temp_fa0;
    f32 temp_fv1;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x14) - *(f32 *)((u8 *)arg1 + 0x14);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x1C) - *(f32 *)((u8 *)arg1 + 0x1C);
    return sqrtf((temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505A6F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A6F8.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505C140.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505C1A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505C1E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505C7D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D024.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D1C4.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505DDA8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505DF10.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505DFDC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505E060.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505E0C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505E650.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505EEF4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505EFD0.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060A30.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060A9C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060B04.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060B70.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150611E8.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150615DC CURRENT (40) */
void func_150615DC(void *arg0) {
    *(s8 *)((u8 *)arg0 + 7) = 0xFF;
    *(s8 *)((u8 *)arg0 + 8) = 0xFF;
    *(s8 *)((u8 *)arg0 + 9) = 0;
    *(s8 *)((u8 *)arg0 + 0xA) = 0;
    *(s8 *)((u8 *)arg0 + 0xF) = 0;
    *(s8 *)((u8 *)arg0 + 0xE) = 0xFF;
    *(s8 *)((u8 *)arg0 + 0xD) = 0xFF;
    *(s8 *)((u8 *)arg0 + 0xC) = 0xFF;
    *(s8 *)((u8 *)arg0 + 0xB) = 0xFF;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150615DC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150615DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1506160C.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150619A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15061B4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150623F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150626EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150627D4.s")
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
