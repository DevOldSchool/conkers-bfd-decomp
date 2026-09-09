#include "types.h"

/*
 * Reviewed source unit: src/game/game_B4080.c
 * Boundary evidence: docs/evidence/game_raw_reconciled_empty_stub_splits.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15086BD0
 * - func_15086C70
 * - func_15086CBC
 * - func_15086D48
 * - func_15086D94
 * - func_150870D0
 * - func_15087350
 * - func_15087CC0
 * - func_15087DCC
 * - func_15087E54
 * - func_15087EF0
 * - func_15087FC4
 * - func_15087FEC
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
 * - func_1508E6D0
 * - func_1508E780
 * - func_1508E89C
 * - func_1508EB90
 * - func_1508EBF8
 * - func_1508EC5C
 * - func_1508ECC0
 * - func_1508EDBC
 * - func_1508EE0C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800D2350;

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
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15086C70.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15086CBC.s")
extern s16 D_80087290;

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
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15086D94.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_150870D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15087350.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15087CC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15087DCC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15087E54.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15087EF0.s")
extern s32 D_800872A0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15087FC4 CURRENT (10) */
void func_15087FC4(s32 arg0, s32 arg1) {
    if (D_800872A0 != 0) {
        *(s8 *)((u8 *)((arg0 * 0x84) + D_800872A0) + 0x31) = arg1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15087FC4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15087FC4.s")
extern s32 D_800872A0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15087FEC CURRENT (10) */
void func_15087FEC(s32 arg0, s32 arg1) {
    if (D_800872A0 != 0) {
        *(f32 *)((u8 *)((arg0 * 0x84) + D_800872A0) + 4) = (f32) ((f32) arg1 * 0.00390625f);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15087FEC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15087FEC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508802C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_150880F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_150881CC.s")
extern s32 D_800872A0;

s32 func_15088218(s32 arg0) {
    u8 *temp_a0;

    if (D_800872A0 == 0) {
        return 0;
    }
    temp_a0 = (void *)((arg0 * 0x84) + D_800872A0);
    return (*(s16 *)((u8 *)temp_a0 + 0x24) * 0x10) + (s32) (*(f32 *)((u8 *)temp_a0 + 8) * 16.0f);
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508855C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_150885EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508868C.s")
s32 func_1508855C();                                /* extern */
extern s32 D_800D2394;

void func_15088780(void) {
    s32 temp_v0;

    if (D_800872A0 != 0) {
        temp_v0 = func_1508855C();
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_150888A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15088A08.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_15088D58.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508E6D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508E780.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508E89C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508EB90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508EBF8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508EC5C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508ECC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508EDBC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B4080/func_1508EE0C.s")
