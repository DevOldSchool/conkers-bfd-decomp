#include "types.h"

/*
 * Reviewed source unit: src/game/game_1865D0.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15159120
 * - func_15159184
 * - func_15159230
 * - func_151592B8
 * - func_15159370
 * - func_1515942C
 * - func_15159594
 * - func_151596BC
 * - func_15159890
 * - func_15159BB0
 * - func_15159C08
 * - func_1515A11C
 * - func_1515A238
 * - func_1515A60C
 * - func_1515A78C
 * - func_1515A974
 * - func_1515AA84
 * - func_1515AB88
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15159120 CURRENT (715) */
s32 func_15159120(void *arg0, s32 arg1) {
    s32 temp_t6;
    s32 var_v1;

    temp_t6 = arg1 & 0xFF;
    if ((temp_t6 == 2) || (temp_t6 == 3)) {
        var_v1 = 1;
    } else {
        var_v1 = 0;
        if (*(f32 *)((u8 *)arg0 + 0x180) < (*(f32 *)((u8 *)arg0 + 0x118) - 35.0f)) {
            var_v1 = 1;
        }
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15159120 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_15159120.s")
extern u8 D_800C35EA;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15159184 CURRENT (735) */
s32 func_15159184(void *arg0, s32 arg1) {
    s32 temp_t6;
    s32 var_v1;

    temp_t6 = arg1 & 0xFF;
    if ((temp_t6 == 2) || (temp_t6 == 3)) {
        if (D_800C35EA != 1) {
            var_v1 = 0;
        } else if ((*(f32 *)((u8 *)arg0 + 0x118) - 75.0f) < *(f32 *)((u8 *)arg0 + 0x18)) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
    } else {
        var_v1 = 0;
        if ((*(f32 *)((u8 *)arg0 + 0x118) - 75.0f) < *(f32 *)((u8 *)arg0 + 0x18)) {
            var_v1 = 1;
        }
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15159184 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_15159184.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15159230 CURRENT (680) */
s32 func_15159230(void *arg0, void *arg1, u8 arg2) {
    s32 var_v1;

    if ((*(f32 *)((u8 *)arg1 + 0) == *(f32 *)((u8 *)arg0 + 0x14)) &&
        (*(f32 *)((u8 *)arg1 + 4) == *(f32 *)((u8 *)arg0 + 0x18)) &&
        (*(f32 *)((u8 *)arg1 + 8) == *(f32 *)((u8 *)arg0 + 0x1C))) {
        var_v1 = 0;
    } else if ((arg2 == 1) || (arg2 == 2)) {
        var_v1 = 2;
    } else {
        var_v1 = 1;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15159230 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_15159230.s")
extern u16 D_8008B040;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151592B8 CURRENT (1403) */
s32 func_151592B8(void *arg0, s32 arg1) {
    u8 spD;
    u16 spC;
    s32 var_v0;
    s32 var_v1;
    u8 *var_a2;
    u8 temp_t8;

    var_v0 = 0;
    if (!(arg1 & 0xFF)) {
        var_v0 = 0;
        var_a2 = &spD;
        spC = D_8008B040;
loop_2:
        temp_t8 = *var_a2;
        var_a2 -= 1;
        if (*(u16 *)((u8 *)arg0 + 0x84) == temp_t8) {
            var_v0 = 1;
        }
        if (var_v0 == 0) {
            if ((u32) var_a2 < (u32) &spC) {

            } else {
                goto loop_2;
            }
        }
    }
    if (var_v0 != 0) {
        var_v1 = 3;
    } else if (*(u8 *)((u8 *)arg0 + 0xAD) != 0) {
        var_v1 = 2;
    } else {
        var_v1 = 4;
        if (*(f32 *)((u8 *)arg0 + 0x28) != 0.0f) {
            var_v1 = 1;
        }
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151592B8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_151592B8.s")
extern u8 D_800BE616;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15159370 CURRENT (1020) */
s32 func_15159370(void *arg0, s8 *arg1) {
    s32 var_v1;
    u8 temp_v0;
    u8 temp_v0_2;

    var_v1 = 0;
    if (D_800BE616 != 0) {
        *arg1 = 0;
        var_v1 = 1;
    }
    if (*(u8 *)((u8 *)arg0 + 0x3B) == 1) {
        *arg1 = 0;
        var_v1 = 1;
    }
    temp_v0 = *(u8 *)((u8 *)arg0 + 5);
    if ((temp_v0 == 5) || (temp_v0 == 2)) {
        *arg1 = 1;
        var_v1 = 1;
    }
    temp_v0_2 = *(u8 *)((u8 *)arg0 + 4);
    switch (temp_v0_2) {                            /* irregular */
    case 8:
        *arg1 = 2;
block_15:
        var_v1 = 1;
        break;
    case 10:
        *arg1 = 3;
        goto block_15;
    case 41:
    case 42:
        *arg1 = 4;
        goto block_15;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15159370 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_15159370.s")
/* Call context: func_1514ECE0: unique active declaration in the allowed source */
s32 func_1514ECE0(s32, s32, void **, void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515942C CURRENT (3460) */
u8 func_1515942C(void *arg0, s16 arg1, s16 arg2, void *arg3, s16 arg4, s16 arg5) {
    void *sp38;
    u8 sp37;
    s32 temp_v0;
    s32 var_a0;
    s32 var_a2;
    s32 var_a3;
    u8 var_t2;
    s32 var_t0;
    s32 var_t1;
    void *temp_a1;

    sp37 = 0;
    var_t2 = sp37;
    if (func_1514ECE0(*(s32 *)((u8 *)arg0 + 0x2F4), 0x13, &sp38, arg3) == 0) {
        return 0U;
    }
    temp_a1 = *(void **)((u8 *)sp38 + 0x10);
    if (arg4 == -1) {
        var_t1 = 0x1E00;
    } else {
        var_t1 = 1 << (arg4 + 9);
    }
    if ((s16) arg3 == -1) {
        var_t0 = 0x1C0;
    } else {
        var_t0 = 1 << ((s16) arg3 + 6);
    }
    if (arg2 == -1) {
        var_a2 = 0x38;
    } else {
        var_a2 = 1 << (arg2 + 3);
    }
    if (arg1 == -1) {
        var_a3 = 7;
    } else {
        var_a3 = 1 << arg1;
    }
    if (arg5 == -1) {
        var_a0 = 0x3E000;
    } else {
        var_a0 = 1 << (arg5 + 0xD);
    }
    temp_v0 = var_a0 | var_a3 | var_a2 | var_t0 | var_t1;
    if (temp_v0 == (temp_v0 | ((1 << *(u8 *)((u8 *)temp_a1 + 0x2C)) | (1 << (*(u8 *)((u8 *)temp_a1 + 0x2D) + 3)) | (1 << (*(u8 *)((u8 *)temp_a1 + 0x2E) + 6)) | (1 << (*(u8 *)((u8 *)temp_a1 + 0x2F) + 9)) | (1 << (*(u8 *)((u8 *)temp_a1 + 0x30) + 0xD))))) {
        var_t2 = 1;
    }
    return var_t2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515942C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_1515942C.s")
u8 func_151596BC(u8 *, s32);
u8 func_151D8E20(void);
void func_151DBCBC(s32, f32, u8, s32, f32 *, s32, s32);
s32 func_15046C00(f32 *, s32, s32, u8 *);
s32 func_1514672C(f32 *);
extern f32 D_800A63A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15159594 CURRENT (685) */
u8 func_15159594(u8 *arg0, s32 arg1) {
    u8 result;
    struct {
        f32 values[3];
        f32 pad;
    } position;

    result = 1;
    if (func_151596BC(arg0, arg1) != 0) {
        if (*(f32 *)(arg0 + 0x5C) > 0.0f) {
            position.values[0] = *(f32 *)(arg0 + 0x40) + *(f32 *)(arg0 + 0x4C);
            position.values[1] = *(f32 *)((u8 *)arg1 + 4);
            position.values[2] = *(f32 *)(arg0 + 0x48) + *(f32 *)(arg0 + 0x54);
            if (func_1514672C(position.values) == 0) {
                return 0;
            }
            if (func_15046C00(position.values, 0, *(s32 *)(arg0 + 0x44), arg0 + 0x80) != 0) {
                position.values[1] = *(f32 *)(arg0 + 0x80);
                if (*(u8 *)(arg0 + 0x9D) == 3) {
                    func_151DBCBC(func_151D8E20() & 0xFF, *(f32 *)(arg0 + 0xA8) * D_800A63A4,
                                  0xFF, (s32)(arg0 + 0x84), position.values,
                                  *(u8 *)(arg0 + 0xC), *(u8 *)(arg0 + 1));
                }
                result = 0;
            }
        }
    } else {
        result = 0;
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15159594 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_15159594.s")
/* Call context: func_151423D8: unique active project prototype */
f32 func_151423D8(u8);
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151596BC CURRENT (3184) */
u8 func_151596BC(u8 *arg0, s32 arg1) {
    f32 sp30;
    f32 sp24;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    u8 temp_a0;
    u8 temp_a0_2;
    u8 *temp_s0;

    {
        u8 sp2B = 1;
    temp_a0 = *(u8 *)((u8 *)arg0 + 0xAC) + (*(s8 *)((u8 *)arg0 + 0xAE) * D_800BE9E4);
    *(u8 *)((u8 *)arg0 + 0xAC) = temp_a0;
    *(u8 *)((u8 *)arg0 + 0xAD) = (u8) (*(u8 *)((u8 *)arg0 + 0xAD) + (*(s8 *)((u8 *)arg0 + 0xAF) * D_800BE9E4));
    sp30 = func_151423D8((temp_a0 - 0x40) & 0xFF);
    temp_s0 = (void *)(arg0 + 0xA8);
    temp_fv0 = func_151423D8((*(u8 *)((u8 *)temp_s0 + 5) - 0x40) & 0xFF);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x5C);
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)arg0 + 0xA8) + (*(f32 *)((u8 *)temp_s0 + 8) * sp30));
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0xA8) + (*(f32 *)((u8 *)temp_s0 + 0xC) * temp_fv0));
    if (temp_fv1 > 0.0f) {
        temp_fv0_2 = *(f32 *)((u8 *)temp_s0 + 0x10);
        if (temp_fv0_2 < temp_fv1) {
            *(f32 *)((u8 *)arg0 + 0x5C) = temp_fv0_2;
        }
        sp24 = *(f32 *)((u8 *)arg0 + 0x5C) * *(f32 *)((u8 *)temp_s0 + 0x14);
        temp_a0_2 = *(u8 *)((u8 *)temp_s0 + 0x18) + (*(u8 *)((u8 *)temp_s0 + 0x1A) * D_800BE9E4);
        *(u8 *)((u8 *)temp_s0 + 0x18) = temp_a0_2;
        *(u8 *)((u8 *)temp_s0 + 0x19) = (u8) (*(u8 *)((u8 *)temp_s0 + 0x19) + (*(u8 *)((u8 *)temp_s0 + 0x1B) * D_800BE9E4));
        sp30 = func_151423D8((temp_a0_2 - 0x40) & 0xFF);
        temp_fv0_3 = func_151423D8((*(u8 *)((u8 *)temp_s0 + 0x19) - 0x40) & 0xFF);
        *(f32 *)((u8 *)arg0 + 0x4C) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x1C) * sp30 * sp24);
        *(f32 *)((u8 *)arg0 + 0x54) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x20) * temp_fv0_3 * sp24);
    }
    if ((*(s32 *)((u8 *)arg0 + 0x68) & 0x2000) && (*(f32 *)((u8 *)temp_s0 + 0x24) < (*(f32 *)((u8 *)arg0 + 0x50) + *(f32 *)((u8 *)arg0 + 0x44)))) {
        sp2B = 0;
    }
    return sp2B;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151596BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_151596BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_15159890.s")
void func_15159890(f32 *, f32 *, u8, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15159BB0 CURRENT (889) */
void func_15159BB0(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, s32 arg5, void *arg6) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;

    sp24 = arg0;
    sp28 = arg1;
    sp18 = 0.0f;
    sp1C = 0.0f;
    sp20 = 0.0f;
    sp2C = arg2;
    func_15159890(&sp24, &sp18, *(u8 *)((u8 *)arg6 + 0xC), *(u8 *)((u8 *)arg6 + 1));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15159BB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_15159BB0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_15159C08.s")
/* Call context: func_15047D60: unique active project prototype */
/* Call context: func_151423D8: unique active project prototype */
f32 func_15047D60(f32);
f32 func_151423D8(u8);
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800BE9A4;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515A11C CURRENT (1972) */
s32 func_1515A11C(u8 *arg0, s32 arg1) {
    f32 sp20;
    f32 temp_fv0;
    f32 temp_fv0_2;
    u8 temp_a0;
    u8 *temp_s0;

    temp_a0 = *(u8 *)((u8 *)arg0 + 0xAC) + (*(s8 *)((u8 *)arg0 + 0xAE) * D_800BE9E4);
    *(u8 *)((u8 *)arg0 + 0xAC) = temp_a0;
    *(u8 *)((u8 *)arg0 + 0xAD) = (u8) (*(u8 *)((u8 *)arg0 + 0xAD) + (*(s8 *)((u8 *)arg0 + 0xAF) * D_800BE9E4));
    sp20 = func_151423D8((temp_a0 - 0x40) & 0xFF);
    temp_s0 = (void *)(arg0 + 0xA8);
    temp_fv0 = func_151423D8((*(u8 *)((u8 *)temp_s0 + 5) - 0x40) & 0xFF);
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)arg0 + 0xA8) + (*(f32 *)((u8 *)temp_s0 + 8) * sp20));
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0xA8) + (*(f32 *)((u8 *)temp_s0 + 0xC) * temp_fv0));
    *(f32 *)((u8 *)temp_s0 + 0x1C) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x1C) + (*(f32 *)((u8 *)temp_s0 + 0x20) * D_800BE9A4));
    temp_fv0_2 = func_15144B68(*(f32 *)((u8 *)temp_s0 + 0x1C));
    *(f32 *)((u8 *)temp_s0 + 0x1C) = temp_fv0_2;
    {
        f32 temp_fv0_3 = func_15047D60(temp_fv0_2);
    *(f32 *)((u8 *)arg0 + 0x4C) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x10) * temp_fv0_3);
    *(f32 *)((u8 *)arg0 + 0x50) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x14) * temp_fv0_3);
    *(f32 *)((u8 *)arg0 + 0x54) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x18) * temp_fv0_3);
    return 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515A11C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_1515A11C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_1515A238.s")
/* Call context: func_151423D8: unique active project prototype */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515A60C CURRENT (1615) */
s32 func_1515A60C(u8 *arg0, s32 arg1) {
    s32 var_v0;
    u8 *temp_s1;

    temp_s1 = (void *)(arg0 + 0xA8);
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) ((func_151423D8((*(u8 *)((u8 *)arg0 + 0xAC) - 0x40) & 0xFF) * *(f32 *)((u8 *)temp_s1 + 8)) + *(f32 *)((u8 *)arg0 + 0xA8));
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) ((func_151423D8((*(u8 *)((u8 *)temp_s1 + 5) - 0x40) & 0xFF) * *(f32 *)((u8 *)temp_s1 + 0xC)) + *(f32 *)((u8 *)arg0 + 0xA8));
    *(f32 *)((u8 *)arg0 + 0x4C) = (f32) (func_151423D8((*(u8 *)((u8 *)temp_s1 + 0x10) - 0x40) & 0xFF) * *(f32 *)((u8 *)temp_s1 + 0x14));
    *(f32 *)((u8 *)arg0 + 0x54) = (f32) (func_151423D8((*(u8 *)((u8 *)temp_s1 + 0x11) - 0x40) & 0xFF) * *(f32 *)((u8 *)temp_s1 + 0x18));
    *(u8 *)((u8 *)temp_s1 + 4) = (u8) (*(u8 *)((u8 *)temp_s1 + 4) + (*(s8 *)((u8 *)temp_s1 + 6) * D_800BE9E4));
    *(u8 *)((u8 *)temp_s1 + 5) = (u8) (*(u8 *)((u8 *)temp_s1 + 5) + (*(s8 *)((u8 *)temp_s1 + 7) * D_800BE9E4));
    *(u8 *)((u8 *)temp_s1 + 0x10) = (u8) (*(u8 *)((u8 *)temp_s1 + 0x10) + (*(u8 *)((u8 *)temp_s1 + 0x12) * D_800BE9E4));
    *(u8 *)((u8 *)temp_s1 + 0x11) = (u8) (*(u8 *)((u8 *)temp_s1 + 0x11) + (*(u8 *)((u8 *)temp_s1 + 0x13) * D_800BE9E4));
    var_v0 = D_800BE9E4;
    if (var_v0 > 0) {
        do {
            var_v0 -= 1;
            *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * *(f32 *)((u8 *)temp_s1 + 0x1C));
            *(f32 *)((u8 *)arg0 + 0x5C) = (f32) (*(f32 *)((u8 *)arg0 + 0x5C) * *(f32 *)((u8 *)temp_s1 + 0x1C));
            *(f32 *)((u8 *)arg0 + 0x60) = (f32) (*(f32 *)((u8 *)arg0 + 0x60) * *(f32 *)((u8 *)temp_s1 + 0x1C));
        } while (var_v0 > 0);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515A60C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_1515A60C.s")
s32 func_1515A60C(u8 *, s32);
f32 func_150ADA68(void);
extern f32 D_800A6408;
extern f32 D_800A640C;
extern f32 D_800A6410;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515A78C CURRENT (2930) */
u8 func_1515A78C(u8 *arg0, s32 volatile arg1) {
    u8 sp4B;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    u8 *sp34;
    f32 temp_fv0;
    u8 *temp_t8;

    sp4B = 1;
    func_1515A60C(arg0, arg1);
    if (*(f32 *)(arg0 + 0x5C) < 0.0f) {
        return 1;
    }
    temp_t8 = arg0 + 0xA8;
    sp3C = *(f32 *)(arg0 + 0x4C) + *(f32 *)(arg0 + 0x40);
    sp40 = *(f32 *)((u8 *)arg1 + 4);
    sp34 = temp_t8;
    sp44 = *(f32 *)(arg0 + 0x48) + *(f32 *)(arg0 + 0x54);
    temp_fv0 = *(f32 *)(temp_t8 + 0x20);
    if (D_800A6408 == temp_fv0) {
        if (func_1514672C(&sp3C) == 0) {
            return 0;
        }
        if (func_15046C00(&sp3C, 0, *(s32 *)(arg0 + 0x44), arg0 + 0x80) != 0) {
            sp4B = 0;
            sp40 = *(f32 *)(arg0 + 0x80);
        }
        goto block_9;
    }
    if (temp_fv0 <= *(f32 *)(arg0 + 0x44)) {
        sp40 = temp_fv0;
        sp4B = 0;
    }
block_9:
    if ((sp4B == 0) && (func_150ADA68() < D_800A640C) &&
        (arg0[0x9D] == 3)) {
        func_151DBCBC(func_151D8E20() & 0xFF, *(f32 *)sp34 * D_800A6410,
                       arg0[0x2B], (s32)(arg0 + 0x84), &sp3C,
                       arg0[0xC], arg0[1]);
    }
    return sp4B;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515A78C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_1515A78C.s")
typedef struct {
    u8 pad_0[0x2F4];
    s32 field_2F4;
} Game1865D0State;

s32 func_1514ECE0(s32, s32, void **, void *);

s32 func_1515A920(Game1865D0State *arg0, s32 *arg1) {
    void *sp1C;
    s32 temp_v1;

    if (func_1514ECE0(arg0->field_2F4, 0x13, &sp1C, arg0) == 0) {
        return 0;
    }
    temp_v1 = *(s32 *)((u8 *)sp1C + 0x10);
    *arg1 = temp_v1 + 0x34;
    return 1;
}
typedef struct Game1865D0A974Payload {
    u8 bytes[0x2C];
} Game1865D0A974Payload;

typedef struct Game1865D0A974Entry {
    u8 bytes[0x34];
} Game1865D0A974Entry;

typedef struct Game1865D0A974Descriptor {
    s8 field00;
    u8 pad01[3];
    void *owner;
    f32 field08;
    f32 field0C;
    f32 zero10;
    f32 zero14;
    f32 zero18;
    f32 zero1C;
    f32 zero20;
    u8 field24;
    s8 field25;
    u8 field26;
    u8 pad27;
} Game1865D0A974Descriptor;

typedef struct Game1865D0A974Locals {
    Game1865D0A974Payload payload;
    u8 pad2C[8];
    Game1865D0A974Descriptor descriptor;
} Game1865D0A974Locals;

extern Game1865D0A974Entry D_800A636C[];
void *func_151A8B20(void *, s32, s32, s32, s32);
void *func_10022EC0(void *, const void *, u32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515A974 CURRENT (5322) */
void func_1515A974(void *arg0, s32 arg1) {
    Game1865D0A974Payload payload;
    Game1865D0A974Descriptor descriptor;
    Game1865D0A974Entry *temp_v0;
    void *result;
    u8 temp_v1;

    temp_v1 = *(u8 *)((u8 *)arg0 + 0x1F);
    if ((s32)temp_v1 <= 0) {
        temp_v0 = &D_800A636C[temp_v1];
        descriptor.field00 = 0xF;
        descriptor.field24 = 0;
        descriptor.field25 = -1;
        descriptor.field26 = 2;
        descriptor.zero10 = 0.0f;
        descriptor.zero14 = 0.0f;
        descriptor.zero18 = 0.0f;
        descriptor.zero1C = 0.0f;
        descriptor.zero20 = 0.0f;
        descriptor.owner = arg0;
        descriptor.field08 = *(f32 *)&temp_v0->bytes[0];
        descriptor.field0C = *(f32 *)&temp_v0->bytes[4];
        payload = *(Game1865D0A974Payload *)&temp_v0->bytes[8];
        result = func_151A8B20(&descriptor, -1, 0x2C, 0xFF, 0);
        if (result != 0) {
            func_10022EC0((u8 *)result + 0x80, &payload, 0x2C);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515A974 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_1515A974.s")
typedef struct {
    s32 words[10];
} Game1865D0Copy40;

typedef struct {
    s32 words[3];
} Game1865D0Copy12;

typedef struct {
    u8 pad0;
    u8 value1;
    u8 pad2[0xA];
    u8 valueC;
    u8 padD[0x73];
    s16 base;
    s16 range;
    Game1865D0Copy40 copied;
} Game1865D0Arg;

typedef struct {
    f32 zero;
    Game1865D0Copy12 input;
    f32 scale;
    Game1865D0Copy40 copied;
} Game1865D0Spawn;

u32 func_150ADA20(void);
void *func_15149130(s16, s32, s32, s32, s32, s32, s32, s32, s32);
void *func_10022EC0(void *, const void *, u32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515AA84 CURRENT (1781) */
void func_1515AA84(Game1865D0Arg *volatile arg0, Game1865D0Copy12 *arg1, f32 arg2, s32 arg3) {
    Game1865D0Spawn spawn;
    void *result;
    u32 random;
    s16 type;

    spawn.zero = 0.0f;
    spawn.input = *arg1;
    spawn.scale = arg2;
    spawn.copied = arg0->copied;

    random = func_150ADA20();
    type = (s16) ((random % (u32) (arg0->range + 1)) + arg0->base);
    result = func_15149130(type, -1, 0x3F, -1, 1, 0, 0x3C,
                          arg0->valueC, arg0->value1);
    if (result != 0) {
        func_10022EC0((u8 *) result + 0x28, &spawn, 0x3C);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515AA84 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_1515AA84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_1515AB88.s")
