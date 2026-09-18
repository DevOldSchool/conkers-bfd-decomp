#include "types.h"

/*
 * Reviewed source unit: src/game/game_B4080.c
 * Boundary evidence: docs/evidence/game_raw_reconciled_empty_stub_splits.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15086BD0
 * - func_15086C70
 * - func_15086D48
 * - func_15086D94
 * - func_150870D0
 * - func_15087350
 * - func_15087CC0
 * - func_15087E54
 * - func_15087EF0
 * - func_1508802C
 * - func_150880F8
 * - func_150881CC
 * - func_15088270
 * - func_150882B0
 * - func_150882E4
 * - func_150883B0
 * - func_1508855C
 * - func_150885EC
 * - func_1508868C
 * - func_150888A8
 * - func_15088A08
 * - func_15088D58
 * - func_15088F30
 * - func_1508907C
 * - func_150891E8
 * - func_150896EC
 * - func_15089BC0
 * - func_15089F9C
 * - func_1508A1BC
 * - func_1508A6FC
 * - func_1508B194
 * - func_1508B20C
 * - func_1508B2A8
 * - func_1508B3F8
 * - func_1508B9BC
 * - func_1508BC20
 * - func_1508BF14
 * - func_1508C1A4
 * - func_1508C5B8
 * - func_1508C9CC
 * - func_1508CA88
 * - func_1508CAD8
 * - func_1508D850
 * - func_1508DA1C
 * - func_1508DAEC
 * - func_1508DC24
 * - func_1508E89C
 * - func_1508ECC0
 * - func_1508EE0C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern u8 *D_800D2350;

f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15086BD0 CURRENT (200) */
f32 func_15086BD0(s32 arg0, s32 arg1) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv1;
    u8 *temp_a2;
    u8 *temp_v1;

    if ((arg0 == 0xFF) || (arg1 == 0xFF)) {
        return 0.0f;
    }
    temp_a2 = (void *)(D_800D2350 + (arg1 * 0x10));
    temp_v1 = (void *)(D_800D2350 + (arg0 * 0x10));
    temp_fv1 = (f32) (*(s16 *)((u8 *)temp_v1 + 0) - *(s16 *)((u8 *)temp_a2 + 0));
    temp_fa0 = (f32) (*(s16 *)((u8 *)temp_v1 + 2) - *(s16 *)((u8 *)temp_a2 + 2));
    temp_fa1 = (f32) (*(s16 *)((u8 *)temp_v1 + 4) - *(s16 *)((u8 *)temp_a2 + 4));
    return sqrtf((temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0) + (temp_fa1 * temp_fa1));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15086BD0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15086BD0.s")
void func_15086C68(void) {

}
void func_150A3194(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s32 arg4);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15086C70 CURRENT (45) */
void func_15086C70(s32 arg0) {
    u8 *temp_v0;

    temp_v0 = (void *)(D_800D2350 + (arg0 * 0x10));
    func_150A3194(3, 0xB, *(s16 *)((u8 *)temp_v0 + 0), *(s16 *)((u8 *)temp_v0 + 2), (s32) *(s16 *)((u8 *)temp_v0 + 4));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15086C70 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15086C70.s")
extern s16 D_80087290;

s32 func_15086CBC(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    s32 temp_v1;

    if ((arg0 < 0) || (arg0 >= D_80087290)) {
        return 0;
    }
    temp_v1 = arg0 * 0x10;
    *arg1 = (f32) *(s16 *)((u8 *)D_800D2350 + temp_v1);
    *arg2 = (f32) *(s16 *)((u8 *)D_800D2350 + temp_v1 + 2);
    *arg3 = (f32) *(s16 *)((u8 *)D_800D2350 + temp_v1 + 4);
    return 1;
}

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15086D48 CURRENT (130) */
s32 func_15086D48(s32 arg0) {
    s32 var_a1;
    s32 var_v1;

    var_v1 = 0;
    if (D_80087290 > 0) {
        var_a1 = D_800D2350;
loop_2:
        if (arg0 == *(u8 *)((u8 *)var_a1 + 7)) {
            return var_v1;
        }
        var_v1 += 1;
        var_a1 += 0x10;
        if (var_v1 >= D_80087290) {
            /* Duplicate return node #5. Try simplifying control flow for better match */
            return 0xFF;
        }
        goto loop_2;
    }
    return 0xFF;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15086D48 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15086D48.s")
s32 func_15085DA8(f32);                             /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15086D94 CURRENT (9527) */
f32 func_15086D94(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 sp54;
    f32 sp50;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fa1;
    f32 temp_fs0;
    f32 temp_fs2;
    f32 temp_fs3;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fs0;
    f32 var_fs4;
    f32 var_ft4;
    s16 temp_a0;
    s16 temp_a2;
    s16 temp_a3;
    s16 temp_v1_2;
    s32 temp_v0;
    s32 var_t0;
    s32 var_t3;
    u8 temp_v1;
    u8 *temp_a1;
    u8 *temp_t2;
    u8 *var_t1;

    temp_v0 = func_15085DA8(arg1);
    var_t3 = 0;
    sp50 = 100.0f;
    if (D_80087290 > 0) {
        var_fs4 = sp54;
        do {
            temp_t2 = (void *)((var_t3 * 0x10) + D_800D2350);
            if (*(u8 *)((u8 *)temp_t2 + 0xE) == 1) {
                var_t0 = 0;
                var_t1 = temp_t2;
                if (temp_v0 == *(u8 *)((u8 *)temp_t2 + 6)) {
                    do {
                        temp_v1 = *(u8 *)((u8 *)var_t1 + 9);
                        var_t0 += 1;
                        if ((temp_v1 != 0xFF) && (var_t3 < (s32) temp_v1)) {
                            temp_a1 = (void *)((temp_v1 * 0x10) + D_800D2350);
                            if ((*(u8 *)((u8 *)temp_a1 + 0xE) == 1) && (((temp_a2 = *(s16 *)((u8 *)temp_a1 + 4), temp_v1_2 = *(s16 *)((u8 *)temp_t2 + 4), temp_a0 = *(s16 *)((u8 *)temp_t2 + 0), temp_a3 = *(s16 *)((u8 *)temp_a1 + 0), temp_fa0 = (f32) (temp_a2 - temp_v1_2), temp_fs2 = (f32) temp_a0, temp_fs3 = (f32) temp_v1_2, temp_fa1 = -(f32) (temp_a3 - temp_a0), temp_fv0 = -((temp_fs2 * temp_fa0) + (temp_fa1 * temp_fs3)), temp_ft5 = (arg0 * temp_fa0) + (arg2 * temp_fa1) + temp_fv0, var_ft4 = temp_ft5, temp_fv1 = ((arg0 + arg3) * temp_fa0) + ((arg2 + arg4) * temp_fa1) + temp_fv0, var_fs0 = temp_fv1, (temp_fv1 < 0.0f)) && (temp_ft5 >= 0.0f)) || ((temp_ft5 < 0.0f) && (temp_fv1 >= 0.0f)))) {
                                if (temp_fv1 < 0.0f) {
                                    var_fs0 = -temp_fv1;
                                }
                                if (temp_ft5 < 0.0f) {
                                    var_ft4 = -temp_ft5;
                                }
                                temp_fa0_2 = -temp_fa1;
                                temp_fv1_2 = var_ft4 / (var_ft4 + var_fs0);
                                var_fs4 = temp_fv1_2;
                                temp_fv0_2 = -((temp_fs2 * temp_fa0_2) + (temp_fa0 * temp_fs3));
                                temp_ft4 = (((temp_fv1_2 * arg3) + arg0) * temp_fa0_2) + (((temp_fv1_2 * arg4) + arg2) * temp_fa0) + temp_fv0_2;
                                temp_fs0 = ((f32) temp_a3 * temp_fa0_2) + (temp_fa0 * (f32) temp_a2) + temp_fv0_2;
                                if ((((temp_fs0 > 0.0f) && (temp_ft4 > 0.0f) && (temp_ft4 <= temp_fs0)) || ((temp_fs0 < 0.0f) && (temp_ft4 < 0.0f) && (temp_fs0 <= temp_ft4))) && (var_fs4 < sp50)) {
                                    sp50 = var_fs4;
                                }
                            }
                        }
                        var_t1 += 1;
                    } while (var_t0 != 5);
                }
            }
            var_t3 += 1;
        } while (var_t3 < D_80087290);
        sp54 = var_fs4;
    }
    if (sp50 <= 1.0f) {
        return sqrtf((arg3 * arg3) + (arg4 * arg4)) * sp54;
    }
    return -1.0f;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15086D94 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15086D94.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_150870D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15087350.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15087CC0.s")
extern s32 D_800872A0;

void func_15087DCC(s32 arg0, s32 arg1) {
    u8 *temp_v1;
    void *sp1C;
    s8 temp_v0;

    if (D_800872A0 != 0) {
        temp_v1 = (void *)((arg0 * 0x84) + D_800872A0);
        if (arg1 != *(s8 *)((u8 *)temp_v1 + 0x2F)) {
            if (arg1 != 0) {
                sp1C = temp_v1;
                temp_v0 = func_150888A8((s32) *(u8 *)((u8 *)temp_v1 + 0x2B), *(u8 *)((u8 *)temp_v1 + 0x2C), 1);
                *(s8 *)((u8 *)temp_v1 + 0x2D) = temp_v0;
                *(s8 *)((u8 *)temp_v1 + 0x2E) = func_150888A8((s32) *(u8 *)((u8 *)temp_v1 + 0x2C), temp_v0 & 0xFF, 1);
            }
            *(s8 *)((u8 *)temp_v1 + 0x2F) = (s8) arg1;
        }
    }
}
/* Call context: func_1505A630: unique active project prototype */
s32 func_1505A630(f32, f32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15087E54 CURRENT (265) */
void func_15087E54(s32 arg0, u8 *arg1) {
    s32 temp_t7;
    s32 temp_t9;
    u8 *temp_v0;

    if (D_800872A0 != 0) {
        temp_v0 = (void *)((arg0 * 0x84) + D_800872A0);
        temp_t7 = (func_1505A630(*(f32 *)((u8 *)temp_v0 + 0x10), *(f32 *)((u8 *)temp_v0 + 0xC), 0) + 0x4000) & 0xFFFF;
        temp_t9 = (temp_t7 - *(u16 *)((u8 *)arg1 + 0x76)) & 0xFFFF;
        if (temp_t9 & 0x8000) {
            if (temp_t9 < 0xDBFF) {
                *(u16 *)((u8 *)arg1 + 0x76) = (u16) (temp_t7 + 0x2400);
            }
        } else if (temp_t9 >= 0x2401) {
            *(u16 *)((u8 *)arg1 + 0x76) = (u16) (temp_t7 - 0x2400);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15087E54 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15087E54.s")
/* Call context: func_1505A630: unique active declaration in the allowed source */
extern s8 D_800D23A8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15087EF0 CURRENT (2830) */
void func_15087EF0(s32 arg0, u8 *arg1) {
    u8 *temp_v1;
    void *sp1C;
    s16 var_v1;
    s32 temp_v0;

    if (D_800872A0 != 0) {
        temp_v1 = (void *)((arg0 * 0x84) + D_800872A0);
        sp1C = temp_v1;
        temp_v0 = func_1505A630(*(f32 *)((u8 *)temp_v1 + 0x10), *(f32 *)((u8 *)temp_v1 + 0xC), 0);
        if (D_800D23A8 == 0) {
            if (*(f32 *)((u8 *)temp_v1 + 0) < 0.5f) {
                var_v1 = (temp_v0 + 0x4A00) & 0xFFFF;
            } else {
                var_v1 = (temp_v0 + 0x3600) & 0xFFFF;
            }
        } else {
            var_v1 = (temp_v0 + 0x3600) & 0xFFFF;
            if (*(f32 *)((u8 *)temp_v1 + 0) >= 0.5f) {
                var_v1 = (temp_v0 + 0x4A00) & 0xFFFF;
            }
        }
        *(s16 *)((u8 *)arg1 + 0x76) = var_v1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15087EF0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15087EF0.s")
extern s32 D_800872A0;

void func_15087FC4(s32 arg0, s32 arg1) {
    u8 *entry;

    if (D_800872A0 != 0) {
        entry = (u8 *)((arg0 * 0x84) + D_800872A0);
        *(s8 *)(entry + 0x31) = arg1;
    }
}
extern s32 D_800872A0;

void func_15087FEC(s32 arg0, s32 arg1) {
    u8 *entry;

    if (D_800872A0 != 0) {
        entry = (u8 *)((arg0 * 0x84) + D_800872A0);
        *(f32 *)(entry + 4) = (f32) ((f32) arg1 * 0.00390625f);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508802C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_150880F8.s")
extern s32 D_800872A0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150881CC CURRENT (110) */
s32 func_150881CC(u8 *arg0) {
    s32 temp_v1;

    temp_v1 = D_800872A0;
    if (temp_v1 == 0) {
        return 0;
    }
    return (s32) (*(f32 *)((u8 *)temp_v1 + ((s32) arg0 * 0x84)) * 256.0f);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150881CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_150881CC.s")
extern s32 D_800872A0;

s32 func_15088218(s32 arg0) {
    u8 *temp_a0;
    s32 temp_a2;
    s32 temp_v0;

    if (D_800872A0 == 0) {
        return 0;
    }
    temp_a0 = (void *)((arg0 * 0x84) + D_800872A0);
    temp_a2 = *(s16 *)((u8 *)temp_a0 + 0x24);
    temp_v0 = temp_a2 * 0x10;
    temp_v0 += (s32) (*(f32 *)((u8 *)temp_a0 + 8) * 16.0f);
    return temp_v0;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15088270 CURRENT (110) */
s32 func_15088270(s32 arg0) {
    if (D_800872A0 == 0) {
        return 0;
    }
    return (s32) *(f32 *)((u8 *)((arg0 * 0x84) + D_800872A0) + 0x14);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15088270 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15088270.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150882B0 CURRENT (110) */
s8 func_150882B0(s32 arg0) {
    if (D_800872A0 == 0) {
        return 0;
    }
    return *(s8 *)((u8 *)((arg0 * 0x84) + D_800872A0) + 0x27);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150882B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_150882B0.s")
extern s8 D_800D2398;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150882E4 CURRENT (200) */
s32 func_150882E4(s32 arg0, s32 arg1) {
    s32 var_a0;
    s32 var_a2;
    void *temp_v1;

    if (D_800872A0 == 0) {
        return 0x10;
    }
    temp_v1 = (arg0 * 0x84) + D_800872A0;
    {
        s32 var_a3 = 0;
    if (D_800D2398 > 0) {
        var_a2 = D_800872A0;
loop_4:
        if (((*(s8 *)((u8 *)temp_v1 + 0x29) + arg1) == *(s8 *)((u8 *)var_a2 + 0x29)) && (var_a3 != arg0)) {
            var_a0 = (((*(s16 *)((u8 *)temp_v1 + 0x24) * 0x10) + (s32) (*(f32 *)((u8 *)temp_v1 + 8) * 16.0f)) - (*(s16 *)((u8 *)var_a2 + 0x24) * 0x10)) - (s32) (*(f32 *)((u8 *)var_a2 + 8) * 16.0f);
            if (var_a0 < 0) {
                var_a0 = -var_a0;
            }
            return (var_a0 << 8) | var_a3;
        }
        var_a3 += 1;
        var_a2 += 0x84;
        if (var_a3 >= D_800D2398) {
            /* Duplicate return node #10. Try simplifying control flow for better match */
            return 0x10;
        }
        goto loop_4;
    }
    return 0x10;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150882E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_150882E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_150883B0.s")
extern u8 D_800CC2D0;
extern s8 D_800D2399;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1508855C CURRENT (785) */
s32 func_1508855C(s32 arg0) {
    u8 *temp_v1;
    s32 temp_a1;
    s32 temp_lo;
    s32 var_a0;
    u8 *var_a2;

    temp_v1 = (u8 *) D_800872A0;
    if (temp_v1 == 0) {
        return -1;
    }
    temp_lo = (s32) (arg0 - (s32) &D_800CC2D0) / 0x32C;
    if (temp_lo == 0) {
        return 0;
    }
    var_a0 = 1;
    var_a2 = temp_v1 + 0x84;
    temp_a1 = D_800D2398 + D_800D2399;
    if (temp_a1 >= 2) {
loop_5:
        if (temp_lo == *(s8 *)(var_a2 + 0x31)) {
            return var_a0;
        }
        var_a0 += 1;
        if (var_a0 < temp_a1) {
            var_a2 += 0x84;
            goto loop_5;
        }
    }
    return -1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1508855C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508855C.s")
void func_10023A10(void *, void *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150885EC CURRENT (461) */
void func_150885EC(s32 arg0, s32 arg1) {
    s32 sp24;
    s32 sp20;
    s32 sp18;
    s32 temp_lo;
    void *temp_v0;

    if (D_800872A0 != 0) {
        temp_lo = arg1 * 0x84;
        temp_v0 = (u8 *)(D_800872A0 + temp_lo);
        sp24 = (s32)*(s8 *)((u8 *)temp_v0 + 0x31);
        sp18 = temp_lo;
        sp20 = (s32)*(s8 *)((u8 *)temp_v0 + 0x30);
        func_10023A10((void *)((arg0 * 0x84) + D_800872A0),
                      (void *)(temp_lo + D_800872A0), 0x84);
        *(s8 *)((u8 *)D_800872A0 + temp_lo + 0x31) = (s8)sp24;
        *(s8 *)((u8 *)D_800872A0 + temp_lo + 0x30) = (s8)sp20;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150885EC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_150885EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508868C.s")
s32 func_1508855C(s32);                             /* extern */
extern s32 D_800D2394;

void func_15088780(s32 arg0) {
    s32 temp_v0;

    if (D_800872A0 != 0) {
        temp_v0 = func_1508855C(arg0);
        *(s8 *)((u8 *)(D_800872A0 + (temp_v0 * 0x84)) + 0x31) = 0;
        D_800D2394 &= ~(1 << (temp_v0 - D_800D2398));
    }
}
s32 func_150887F8(void) {
    if (D_800872A0 == 0) {
        return 0;
    }
    return *(u8 *)((u8 *)D_800872A0 + 0x46) == 0xFF;
}
void func_15088824(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x2B) = 0;
    *(s8 *)((u8 *)arg0 + 0x2C) = 0;
    *(s8 *)((u8 *)arg0 + 0x2D) = 0;
    *(s8 *)((u8 *)arg0 + 0x2E) = 0;
    *(s8 *)((u8 *)arg0 + 0x28) = 0;
    *(s32 *)((u8 *)arg0 + 0x1C) = 0;
    *(s32 *)((u8 *)arg0 + 0x18) = 0;
    *(s32 *)((u8 *)arg0 + 0x20) = -1;
    *(s8 *)((u8 *)arg0 + 0x2F) = 0;
    *(f32 *)((u8 *)arg0 + 8) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0) = 0.5f;
    *(f32 *)((u8 *)arg0 + 4) = 0.5f;
    *(s16 *)((u8 *)arg0 + 0x24) = 0;
    *(s8 *)((u8 *)arg0 + 0x26) = 0;
    *(s8 *)((u8 *)arg0 + 0x27) = 0;
    *(s8 *)((u8 *)arg0 + 0x31) = 0;
    *(f32 *)((u8 *)arg0 + 0xC) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x14) = 0.0f;
    *(s8 *)((u8 *)arg0 + 0x33) = 2;
    *(s8 *)((u8 *)arg0 + 0x30) = 0;
    *(s8 *)((u8 *)arg0 + 0x2A) = 0x7F;
    *(s8 *)((u8 *)arg0 + 0x49) = 0;
    *(f32 *)((u8 *)arg0 + 0x10) = 1.0f;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150888A8 CURRENT (2887) */
s32 func_150888A8(s32 arg0, u8 arg1, s8 arg2) {
    s32 temp_s0;
    s32 var_a0;
    s32 var_a3;
    s32 var_t0;
    s32 var_t4;
    s32 var_v1;
    u8 temp_a2_2;
    u8 temp_a2_3;
    u8 temp_t0;
    u8 temp_t2;
    u8 temp_t3_2;
    u8 *temp_a2;
    u8 *temp_t1;
    u8 *temp_t2_2;
    u8 *temp_t3;
    u8 *var_t1;

    temp_s0 = arg0 & 0xFF;
    var_v1 = 0xFF;
    var_a3 = 0xFF;
    if (arg2 != 0) {
        var_a0 = 1;
    } else {
        var_a0 = 2;
    }
    temp_a2 = (void *)((arg1 * 0x10) + D_800D2350);
    temp_t0 = *(u8 *)((u8 *)temp_a2 + 9);
    if ((temp_t0 != 0xFF) && (temp_s0 != temp_t0)) {
        temp_t1 = (void *)((temp_t0 * 0x10) + D_800D2350);
        if (*(u8 *)((u8 *)temp_t1 + 0xE) == 0) {
            if (var_a0 != *(u8 *)((u8 *)temp_t1 + 0xF)) {
                var_v1 = temp_t0 & 0xFF;
            } else {
                var_a3 = temp_t0 & 0xFF;
            }
        }
    }
    var_t0 = 1;
    var_t1 = (void *)(temp_a2 + 1);
    var_t4 = var_v1;
    do {
        temp_a2_2 = *(u8 *)((u8 *)var_t1 + 9);
        var_t0 += 2;
        if ((temp_a2_2 != 0xFF) && (temp_s0 != temp_a2_2)) {
            temp_t3 = (void *)((temp_a2_2 * 0x10) + D_800D2350);
            if (*(u8 *)((u8 *)temp_t3 + 0xE) == 0) {
                temp_t2 = *(u8 *)((u8 *)temp_t3 + 0xF);
                if (var_a0 != temp_t2) {
                    if ((var_t4 == 0xFF) || (temp_t2 != 0)) {
                        var_v1 = temp_a2_2 & 0xFF;
                        var_t4 = var_v1;
                    }
                } else {
                    var_a3 = temp_a2_2 & 0xFF;
                }
            }
        }
        temp_t3_2 = *(u8 *)((u8 *)var_t1 + 0xA);
        if ((temp_t3_2 != 0xFF) && (temp_s0 != temp_t3_2)) {
            temp_t2_2 = (void *)((temp_t3_2 * 0x10) + D_800D2350);
            if (*(u8 *)((u8 *)temp_t2_2 + 0xE) == 0) {
                temp_a2_3 = *(u8 *)((u8 *)temp_t2_2 + 0xF);
                if (var_a0 != temp_a2_3) {
                    if ((var_t4 == 0xFF) || (temp_a2_3 != 0)) {
                        var_v1 = temp_t3_2 & 0xFF;
                        var_t4 = var_v1;
                    }
                } else {
                    var_a3 = temp_t3_2 & 0xFF;
                }
            }
        }
        var_t1 += 2;
    } while (var_t0 != 5);
    if (var_t4 == 0xFF) {
        var_v1 = var_a3 & 0xFF;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150888A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_150888A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15088A08.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15088D58.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15088F30 CURRENT (2635) */
void func_15088F30(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    f32 *var_t2;
    f32 *var_t3;
    f32 *var_t4;
    f32 *var_v1;
    s16 temp_a1_3;
    s32 var_t1;
    s32 var_v0;
    u8 temp_a1;
    u8 temp_a1_2;
    u8 *temp_a2;
    u8 *var_t0;

    var_v0 = 0;
    var_v1 = arg0;
    var_t2 = arg1;
    var_t3 = arg2;
    var_t4 = arg3;
    do {
        temp_a1 = *(u8 *)((u8 *)var_v1 + 0x2B);
        var_v1 += 1;
        if (temp_a1 != 0xFF) {
            var_t1 = 0;
            temp_a2 = (void *)((temp_a1 * 0x10) + D_800D2350);
            var_t0 = temp_a2;
            do {
                temp_a1_2 = *(u8 *)((u8 *)(temp_a2 + var_t1) + 9);
                if ((temp_a1_2 != 0xFF) && (*(u8 *)((u8 *)(D_800D2350 + (temp_a1_2 * 0x10)) + 0xE) == 4)) {
                    var_t0 = (void *)((temp_a1_2 * 0x10) + D_800D2350);
                    var_t1 = 5;
                }
                var_t1 += 1;
            } while (var_t1 < 5);
            temp_a1_3 = *(s16 *)((u8 *)temp_a2 + 0);
            *var_t2 = (f32) temp_a1_3 + ((f32) (*(s16 *)((u8 *)var_t0 + 0) - temp_a1_3) * *arg0);
            *var_t3 = (f32) *(s16 *)((u8 *)temp_a2 + 2);
            *var_t4 = (f32) *(s16 *)((u8 *)temp_a2 + 4) + ((f32) (*(s16 *)((u8 *)var_t0 + 4) - *(s16 *)((u8 *)temp_a2 + 4)) * *arg0);
        } else {
            *var_t2 = (f32) (var_v0 << 6);
            *var_t3 = 0.0f;
            *var_t4 = 0.0f;
        }
        var_v0 += 1;
        var_t2 += 4;
        var_t3 += 4;
        var_t4 += 4;
    } while (var_v0 != 4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15088F30 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15088F30.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508907C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_150891E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_150896EC.s")
extern s32 D_800D23B0;

void func_15089BB0(void) {
    D_800D23B0 = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15089BC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15089F9C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508A1BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508A6FC.s")
extern s8 D_8008FD90;
extern s32 D_8008FDD4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1508B194 CURRENT (205) */
s16 func_1508B194(s32 arg0) {
    if (arg0 >= D_8008FD90) {
        return 0;
    }
    return *(s16 *)((u8 *)(D_8008FDD4 + (arg0 * 0xC)) + 0x70);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1508B194 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508B194.s")
extern s8 D_8008FD90;
extern s32 D_8008FDD4;

void func_1508B1D4(s32 arg0) {
    if (arg0 < D_8008FD90) {
        *(s16 *)((u8 *)(D_8008FDD4 + (arg0 * 0xC)) + 0x70) = 0;
    }
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1508B20C CURRENT (145) */
void func_1508B20C(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    s32 temp_a1;
    s8 temp_v1;

    if (D_800D23B0 != 0) {
        temp_v1 = *(s8 *)((u8 *)D_800D23B0 + 0x1745);
        if (temp_v1 < 8) {
            *(s8 *)((u8 *)D_800D23B0 + 0x1745) = (s8) (temp_v1 + 1);
            temp_a1 = temp_v1 * 0xC;
            *(s16 *)((u8 *)(D_800D23B0 + temp_a1) + 0x174C) = (s16) (s32) arg0;
            *(s16 *)((u8 *)(D_800D23B0 + temp_a1) + 0x174E) = (s16) (s32) arg1;
            *(s16 *)((u8 *)(D_800D23B0 + temp_a1) + 0x1750) = (s16) (s32) arg2;
            *(f32 *)((u8 *)(D_800D23B0 + temp_a1) + 0x1748) = (f32) (arg3 * arg3);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1508B20C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508B20C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508B2A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508B3F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508B9BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508BC20.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1508BF14 CURRENT (11632) */
s32 func_1508BF14(void) {
    s32 spA4;
    s8 sp7C;
    s32 *sp6C;
    s32 *sp68;
    u8 *sp64;
    u8 *sp60;
    s32 *var_s7;
    s32 *var_t5;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_s3;
    s32 temp_s5;
    s32 temp_t6;
    s32 temp_t8;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a2;
    s32 var_a3;
    s32 var_s0;
    s32 var_s1;
    s32 var_s6;
    s32 var_t1;
    s32 var_t1_2;
    s32 var_t4;
    s32 var_v0_3;
    s32 var_v1;
    s8 *temp_v0_3;
    s8 *var_v0;
    s8 *var_v0_2;
    u8 *temp_s4;
    u8 *temp_t2;

    var_t1 = 0;
    temp_s3 = *(s32 *)((u8 *)D_800D23B0 + 0x10);
    sp6C = (void *)(D_800D23B0 + 0x15C);
    sp68 = (void *)(D_800D23B0 + 0x39C);
    temp_s4 = (void *)(D_800D23B0 + 0xE64);
    sp64 = (void *)(D_800D23B0 + 0x45C);
    sp60 = (void *)(D_800D23B0 + 0x49C);
    temp_s5 = *(temp_s4 + (*(s32 *)((u8 *)D_800D23B0 + 4) * 4));
    temp_t2 = (void *)(D_800D23B0 + 0x5DC);
    if (temp_s3 > 0) {
        temp_a0 = temp_s3 & 3;
        if (temp_a0 != 0) {
            var_v0 = &sp7C;
            do {
                var_t1 += 1;
                *var_v0 = 0;
                var_v0 += 1;
            } while (temp_a0 != var_t1);
            if (var_t1 != temp_s3) {
                goto block_5;
            }
        } else {
block_5:
            var_v0_2 = &(&sp7C)[var_t1];
            do {
                var_v0_2 += 4;
                *(s8 *)((u8 *)var_v0_2 + -4) = 0;
                *(s8 *)((u8 *)var_v0_2 + -3) = 0;
                *(s8 *)((u8 *)var_v0_2 + -2) = 0;
                *(s8 *)((u8 *)var_v0_2 + -1) = 0;
            } while (var_v0_2 != &(&sp7C)[temp_s3]);
        }
    }
    spA4 = 0;
    do {
        var_t1_2 = 0;
        if (temp_s3 > 0) {
            var_s6 = 0;
            var_s7 = sp6C;
            do {
                temp_v0 = *var_s7;
                var_s7 += 4;
                var_a0 = 0;
                if ((temp_v0 == 2) || (temp_v0 == 3)) {
                    var_a0 = 1;
                }
                if (((var_a0 != 0) && (spA4 == 0)) || ((var_a0 == 0) && (spA4 != 0))) {
                    var_s1 = -1;
                    var_s0 = 0x989680;
                    if (temp_s5 == *(temp_s4 + var_s6)) {
                        var_a3 = 0;
                        if (temp_s3 > 0) {
                            var_t4 = 0;
                            var_t5 = sp68;
                            do {
                                temp_t8 = *var_t5;
                                var_t5 += 4;
                                if (temp_t8 > 0) {
                                    temp_v0_2 = var_a3 * 0x10;
                                    var_a2 = -1;
                                    temp_a1 = temp_v0_2 + 0x10;
                                    if (temp_s5 != *(temp_s4 + var_t4)) {
                                        var_a0_2 = temp_v0_2;
                                        if (temp_v0_2 < temp_a1) {
                                            var_v0_3 = temp_v0_2 * 4;
                                            if (*(temp_t2 + (temp_v0_2 * 4)) != -1) {
                                                var_v1 = *(temp_t2 + var_v0_3);
loop_25:
                                                var_a0_2 += 1;
                                                if (var_t1_2 == var_v1) {
                                                    var_a2 = *(u8 *)(D_800D23B0 + 0x9DC + var_v0_3);
                                                    var_a0_2 = temp_a1;
                                                }
                                                var_v0_3 = var_a0_2 * 4;
                                                if (var_a0_2 < temp_a1) {
                                                    var_v1 = *(temp_t2 + var_v0_3);
                                                    if (var_v1 != -1) {
                                                        goto loop_25;
                                                    }
                                                }
                                            }
                                        }
                                        if (var_a2 != -1) {
                                            temp_a2 = var_a2 << (&sp7C)[var_a3];
                                            if (temp_a2 < var_s0) {
                                                var_s0 = temp_a2;
                                                var_s1 = var_a3;
                                            }
                                        }
                                    }
                                }
                                var_a3 += 1;
                                var_t4 += 4;
                            } while (var_a3 != temp_s3);
                        }
                        temp_v0_3 = &(&sp7C)[var_s1];
                        *temp_v0_3 += 1;
                        *(sp64 + var_s6) = var_s0;
                        *(sp60 + var_s6) = var_s1;
                    }
                }
                var_t1_2 += 1;
                var_s6 += 4;
            } while (var_t1_2 != temp_s3);
        }
        temp_t6 = spA4 + 1;
        spA4 = temp_t6;
    } while (temp_t6 != 2);
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1508BF14 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508BF14.s")
s32 func_1508C194(s32 arg0) {
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508C1A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508C5B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508C9CC.s")
extern s8 D_8008FD90;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1508CA88 CURRENT (110) */
s8 func_1508CA88(void) {
    s8 var_v1;

    *(s8 *)((u8 *)D_800D23B0 + 0x1703) = (s8) (*(s8 *)((u8 *)D_800D23B0 + 0x1703) + 1);
    var_v1 = *(s8 *)((u8 *)D_800D23B0 + 0x1703);
    if (var_v1 >= D_8008FD90) {
        *(s8 *)((u8 *)D_800D23B0 + 0x1703) = 0;
        var_v1 = *(s8 *)((u8 *)D_800D23B0 + 0x1703);
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1508CA88 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508CA88.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508CAD8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508D850.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1508DA1C CURRENT (2640) */
void func_1508DA1C(void) {
    s32 *var_t2;
    s32 *var_t2_2;
    s32 *var_t3;
    s32 *var_t4;
    s32 *var_v0;
    s32 *var_v1;
    s32 var_t1;

    var_t1 = 0;
    if (*(s32 *)((u8 *)D_800D23B0 + 0x10) > 0) {
        var_t2 = D_800D23B0 + 0xEB0;
        do {
            *var_t2 = -1;
            var_t1 += 1;
            var_t2 += 4;
        } while (var_t1 < *(s32 *)((u8 *)0x10 + D_800D23B0));
        var_t1 = 0;
    }
    var_v1 = D_800D23B0 + 0xFF0;
    var_t2_2 = D_800D23B0 + 0x10F0;
    if (*(s32 *)((u8 *)D_800D23B0 + 0xEA4) > 0) {
        var_v0 = D_800D23B0 + 0xF70;
        var_t3 = D_800D23B0 + 0x1070;
        var_t4 = D_800D23B0 + 0x12F4;
        do {
            *var_v0 = -1;
            *var_v1 = 0;
            *var_t2_2 = -1;
            *var_t3 = 1;
            *var_t4 = 0;
            var_t1 += 1;
            var_v0 += 4;
            var_v1 += 4;
            var_t2_2 += 4;
            var_t3 += 4;
            var_t4 += 4;
        } while (var_t1 < *(s32 *)((u8 *)D_800D23B0 + 0xEA4));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1508DA1C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508DA1C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508DAEC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508DC24.s")
void func_1508E6C8(void) {

}
s32 func_1508E6D0(s32 arg0) {
    switch (arg0) {
    case 0x3F:
        return 0x708;
    case 0x14:
        return 0xC80;
    case 0x22:
        return 0x1F4;
    case 0x23:
        return 0x2710;
    case 0x16:
        return 0x186A0;
    case 0x15:
        return 0x1F4;
    case 0x21:
        return 0x1F4;
    case 0x24:
        return 0x186A0;
    case 0x19:
    case 0x40:
        return 0x1F4;
    case 0x9:
        return 0x1388;
    case 0x38:
        return 0x1388;
    case 0x18:
    case 0x41:
        return 0x186A0;
    case 0x3:
        return 0x2EE;
    case 0x37:
        return 0x5DC;
    default:
        return 0x186A0;
    }
}
s32 func_1508E780(s32 arg0) {
    if (*(s16 *)((u8 *)D_800D23B0 + 0x16BC) != 0xB8) {
        switch (arg0) {                             /* switch 1 */
        case 0x14:                                  /* switch 1 */
            return 0x28;
        case 0x3F:                                  /* switch 1 */
            return 0x2F;
        case 0x22:                                  /* switch 1 */
            return 0x56;
        case 0x23:                                  /* switch 1 */
            return 0x16;
        case 0x16:                                  /* switch 1 */
            return 0x24;
        case 0x15:                                  /* switch 1 */
            return 0x4B;
        case 0x21:                                  /* switch 1 */
            return 0x58;
        case 0x24:                                  /* switch 1 */
            return 0x63;
        case 0x19:                                  /* switch 1 */
            return 0x57;
        case 0x40:                                  /* switch 1 */
            return 0x21;
        case 0x9:                                   /* switch 1 */
            return 0x1D;
        case 0x38:                                  /* switch 1 */
            return 0x7B;
        case 0x39:                                  /* switch 1 */
            return 0x82;
        case 0x37:                                  /* switch 1 */
            return 0x85;
        case 0x18:                                  /* switch 1 */
            return 0x55;
        case 0x41:                                  /* switch 1 */
            return 0x2E;
        case 0x25:                                  /* switch 1 */
            return 0x1060;
        default:                                    /* switch 1 */
            return -1;
        }
    } else {
        switch (arg0) {                             /* switch 2; irregular */
        case 8:                                     /* switch 2 */
            return -1;
        case 1:                                     /* switch 2 */
            return 0x105C;
        case 16:                                    /* switch 2 */
            return 0x1019;
        case 2:                                     /* switch 2 */
            return 0x1059;
        default:                                    /* switch 2 */
            return -1;
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508E89C.s")
typedef struct {
    u8 field_0;
    u8 pad_1[0x32B];
} GameB4080EntityIdRecord;

extern GameB4080EntityIdRecord D_800CC40F[];
void func_1509BFB0(s32, s32, s32, s32);

void func_1508EB90(s32 arg0, s32 arg1, s32 arg2) {
    u8 temp_v0;

    temp_v0 = D_800CC40F[arg0].field_0;
    func_1509BFB0(1, temp_v0 | 0x2000, arg1, arg2);
}
void func_1508EBF8(s32 arg0, s32 arg1) {
    u8 temp_v0;

    temp_v0 = D_800CC40F[arg0].field_0;
    func_1509BFB0(1, temp_v0 | 0x2000, 0x14, arg1);
}
void func_1508EC5C(s32 arg0, s32 arg1) {
    u8 temp_v0;

    temp_v0 = D_800CC40F[arg0].field_0;
    func_1509BFB0(1, temp_v0 | 0x2000, 0x61, arg1);
}
extern u32 D_80087380;
extern s32 D_800D23C0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1508ECC0 CURRENT (3271) */
s32 func_1508ECC0(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_t0;
    u16 temp_a1;
    u16 temp_t1;
    u32 var_a2;
    u32 var_v0;
    u32 var_v0_2;
    void *temp_t2;
    u8 *var_a0;
    u8 *var_t3;

    var_v0 = 0;
    if (D_80087380 != 0) {
        var_t0 = D_800D23C0;
loop_2:
        temp_t1 = *(u16 *)((u8 *)var_t0 + 2);
        var_a2 = 0;
        if (temp_t1 != 0) {
            temp_t2 = (void *)(D_800D23C0 + (var_v0 * 0x18));
            var_t3 = temp_t2;
loop_4:
            if (((((arg0 & 0xFFFF) << 0xC) + (arg1 & 0xFFFF)) & 0xFFFF) == *(u16 *)((u8 *)var_t3 + 8)) {
                var_v0_2 = 0;
                if (temp_t1 != 0) {
                    var_a0 = temp_t2;
loop_7:
                    temp_a1 = *(u16 *)((u8 *)var_a0 + 8);
                    if (((arg2 & 0xFFFF) == ((s32) temp_a1 >> 0xC)) && (var_v0_2 != var_a2)) {
                        return temp_a1 & 0xFFF;
                    }
                    var_v0_2 += 1;
                    var_a0 += 2;
                    if (var_v0_2 >= temp_t1) {
                        goto block_11;
                    }
                    goto loop_7;
                }
block_11:
                goto block_14;
            }
            var_a2 += 1;
            var_t3 += 2;
            if (var_a2 >= temp_t1) {
                goto block_13;
            }
            goto loop_4;
        }
block_13:
        var_v0 += 1;
        var_t0 += 0x18;
        if (var_v0 >= (u32) D_80087380) {
            goto block_14;
        }
        goto loop_2;
    }
block_14:
    return -1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1508ECC0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508ECC0.s")
extern u32 D_80087380;
extern s32 D_800D23C0;

void func_1508EDBC(u32 arg0) {
    s32 temp_v0;

    if (arg0 < (u32) D_80087380) {
        temp_v0 = arg0 * 0x18;
        *(s16 *)((u8 *)D_800D23C0 + temp_v0 + 2) = 0;
        *(s32 *)((u8 *)D_800D23C0 + temp_v0 + 4) = 0;
        *(s16 *)((u8 *)D_800D23C0 + temp_v0) = 0;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508EE0C.s")
