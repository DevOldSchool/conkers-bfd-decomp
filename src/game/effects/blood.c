#include "types.h"

/*
 * Reviewed source unit: src/game/effects/blood.c
 * Boundary evidence: docs/evidence/effects_blood.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15134070
 * - func_1513416C
 * - func_1513418C
 * - func_151342BC
 * - func_151346D0
 * - func_151346EC
 * - func_1513470C
 * - func_151347CC
 * - func_15134908
 * - func_151349D0
 * - func_15134CEC
 * - func_15134DAC
 * - func_15134E48
 * - func_151352EC
 * - func_1513530C
 * - func_1513532C
 * - func_151353A8
 * - func_15135480
 * - func_151355B8
 * - func_15135658
 * - func_151356D4
 * - func_15135BF8
 * - func_15135DD0
 * - func_15136404
 * - func_15136698
 * - func_151368A8
 * - func_15136A50
 * - func_15136AE4
 * - func_15136C3C
 * - func_15136F50
 * - func_15137610
 * - func_1513783C
 * - func_15137F30
 * - func_15138120
 * - func_151382E0
 * - func_15138424
 * - func_151389A8
 * - func_15138BC0
 * - func_15138C80
 * - func_15138E98
 * - func_15139578
 * - func_15139768
 * - func_15139D74
 * - func_1513A24C
 * - func_1513A48C
 * - func_1513A594
 * - func_1513A5E0
 * - func_1513A6E0
 * - func_1513ABB8
 * - func_1513B0F8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct BloodState {
    u8 pad0[0x1C];
    s16 unk1C;
    u8 pad1E[0xA];
    u8 unk28;
    u8 pad29[0x14];
    u8 field3D;
    u8 pad3E[0x6];
    u16 field44;
    u8 pad46[0xA];
    u8 field50;
    u8 pad51[0xF];
    s32 flags60;
    u8 pad64[0x10C];
    s32 unk170;
} BloodState;

void func_151BC5A4(BloodState *arg0, s32 arg1, u8 arg2);
void func_1513A5E0(s32 arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15134070 CURRENT (2310) */
s32 func_15134070(void *arg0) {
    u8 temp_v0;

    temp_v0 = *(u8 *)((u8 *)arg0 + 4);
    switch ((s32) temp_v0) {                        /* irregular */
    case 0x87:
    case 0xB0:
        return 0xE;
    case 0xB1:
        return 0xF;
    case 0xB4:
        return 0x10;
    case 0x70:
    case 0xB2:
        return 0x11;
    case 0xAB:
        return 0x12;
    case 0x10:
    case 0x38:
    case 0x91:
        return 0xD;
    case 0x98:
        return 0xC;
    case 0x34:
        return 0xB;
    case 0x47:
        return 0xA;
    case 0x11:
    case 0x14:
    case 0x3B:
        return 1;
    case 0x5A:
    case 0x5F:
    case 0x74:
    case 0x75:
    case 0x7A:
        return 2;
    case 0x58:
    case 0x5B:
    case 0x80:
        return 3;
    case 0x16:
    case 0x88:
    case 0x90:
        return 4;
    case 0x9C:
        return 5;
    case 0x9D:
        return 6;
    case 0x96:
        return 7;
    case 0xA0:
        return 8;
    case 0x9F:
        return 9;
    case 0x9A:
        return 0x13;
    case 0x0:
    case 0x1:
    case 0x2:
    case 0x3:
    case 0x4:
        return 0;
    default:
        return 0x63;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15134070 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15134070.s")
s32 func_1513416C(void *arg0) {
    short temp_v0;

    temp_v0 = *(short *)((char *)arg0 + 0x1C);
    if (temp_v0 < 0x20) {
        *(char *)((char *)arg0 + 0x28) = (char)(temp_v0 * 8);
    }
    return 1;
}
void *func_15167A68(s32, s32, s32, s32, s32, s32);
void func_10022EC0(void *, void *, s32);
void func_15143134(f32 *, f32 *, s32);
void func_1516972C(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513418C CURRENT (40) */
void *func_1513418C(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    void *temp_v0;
    void *sp24;
    s32 temp_v1;
    u8 temp_a0;
    void *temp_v0_2;
    f32 one;
    f32 denominator;
    f32 zero;

    temp_v0 = func_15167A68(0x28, arg3, arg1 + 0x58, 1, (s32)arg2, 1);
    if (temp_v0 == (void *)0) {
        return (void *)0;
    }
    sp24 = temp_v0;
    func_10022EC0((u8 *)sp24 + 0x10, (void *)arg0, 0x30);
    temp_a0 = *(u8 *)((u8 *)sp24 + 0x3A);
    if (temp_a0 & 2) {
        temp_v0_2 = *(void **)((u8 *)sp24 + 0x1C);
        if ((*(s32 *)temp_v0_2 == 0) ||
            (*(u8 *)((u8 *)sp24 + 0x18) != *(u8 *)((u8 *)temp_v0_2 + 0x3B))) {
            func_1516972C(sp24);
            return (void *)0;
        }
        temp_v1 = *(s32 *)((u8 *)temp_v0_2 + 0x1D4);
        if ((temp_v1 != 0) && ((*(u8 *)((u8 *)temp_v0_2 + 0x74) & 0xF) != 0xF)) {
            func_15143134((f32 *)((u8 *)sp24 + 0x24),
                          (f32 *)((u8 *)sp24 + 0x40),
                          temp_v1 + (*(u8 *)((u8 *)sp24 + 0x20) << 6));
        } else {
            *(u8 *)((u8 *)sp24 + 0x3A) = temp_a0 | 8;
        }
    } else {
        *(u8 *)((u8 *)sp24 + 0x3A) = temp_a0 | 0x18;
    }
    one = 1.0f;
    denominator = *(f32 *)((u8 *)sp24 + 0x30) + *(f32 *)((u8 *)sp24 + 0x30);
    zero = 0.0f;
    *(f32 *)((u8 *)sp24 + 0x50) = zero;
    *(f32 *)((u8 *)sp24 + 0x4C) = one / denominator;
    return sp24;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513418C */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513418C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_151342BC.s")
s32 func_151346D0(s32 arg0, void *arg1, s32 arg2) {
    *((unsigned char *)arg1 + 0x3A) =
        (unsigned char)(*((unsigned char *)arg1 + 0x3A) & 0xFFEF);
    return arg0;
}
void func_151346EC(void) {
    func_15169804();
}
void func_1513470C(void) {
    func_15169824();
}
extern void (*D_80089AAC[])(void);

void func_1513472C(BloodState *arg0) {
    s32 temp_v0;

    temp_v0 = arg0->field3D;
    if (temp_v0 < 0) {
        temp_v0 = 0;
    }
    if (temp_v0 >= 0xA) {
        temp_v0 = 0;
    }
    D_80089AAC[temp_v0]();
}
extern void (*D_80089AD4[])(void);

void func_1513477C(BloodState *arg0) {
    s32 temp_v0;

    temp_v0 = arg0->field3D;
    if (temp_v0 < 0) {
        temp_v0 = 0;
    }
    if (temp_v0 >= 0xA) {
        temp_v0 = 0;
    }
    D_80089AD4[temp_v0]();
}
typedef struct {
    u8 pad00[0x18];
    u8 field18;
    u8 pad19[3];
    s32 field1C;
    u8 pad20[0x1D];
    u8 field3D;
} Blood347CCState;

typedef struct {
    s32 field00;
    union {
        s32 word;
        u8 bytes[4];
    } field04;
    u8 field08;
    u8 field09;
} Blood347CCEvent;

void func_1516972C(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151347CC CURRENT (10) */
void func_151347CC(Blood347CCState *arg0, Blood347CCEvent *arg1, u8 arg2) {
    s32 temp_v0;
    s32 temp_v1;

    temp_v0 = arg2;
    if ((arg2 == 0) || (arg2 == 3)) {
        if ((arg1->field00 == arg0->field1C) ||
            (arg0->field18 == arg1->field04.bytes[0])) {
            func_1516972C(arg0);
        }
    } else if (temp_v0 == 0x11) {
        if ((arg0->field3D == 5) &&
            ((arg1->field00 == arg0->field1C) ||
             (arg0->field18 == arg1->field04.bytes[0]))) {
            func_1516972C(arg0);
        }
    } else if (temp_v0 == 0x16) {
        if ((s32)arg1 == arg0->field1C) {
            func_1516972C(arg0);
        }
    } else if (temp_v0 == 0x2D) {
        temp_v0 = arg1->field00;
        temp_v1 = arg0->field1C;
        if (temp_v0 == temp_v1) {
            arg0->field1C = arg1->field04.word;
            arg0->field18 = arg1->field09;
            return;
        }
        if (temp_v1 != arg1->field04.word) {
            return;
        }
        arg0->field1C = temp_v0;
        arg0->field18 = *((u8 *)arg1 + 8);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151347CC */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_151347CC.s")
void func_151348F0(f32 arg0, f32 arg1, s32 arg2, s32 arg3) {

}
/* Call context: func_10022EC0: unique active declaration in the allowed source */
/* Call context: func_15167A68: unique active declaration in the allowed source */
void func_15134908(s32 *, s32, u8, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15134908 CURRENT (1750) */
void func_15134908(s32 *arg0, s32 arg1, u8 arg2, s32 arg3) {
    u8 *temp_v0;

    temp_v0 = (void *)(func_15167A68(0x2A, arg3, arg1 + 0x40, 1, (s32) arg2, 1));
    if (temp_v0 == 0) {
        return;
    }
    *(u8 *)((u8 *)arg0 + 0x16) = (u8) (*(u8 *)((u8 *)arg0 + 0x16) | 2);
    {
        u8 * sp24 = temp_v0;
    func_10022EC0(temp_v0 + 0x10, arg0, 0x1C);
    *(f32 *)((u8 *)sp24 + 0x2C) = (f32) **(f32 **)((u8 *)sp24 + 0x10);
    *(f32 *)((u8 *)sp24 + 0x30) = (f32) **(f32 **)((u8 *)sp24 + 0x14);
    *(f32 *)((u8 *)sp24 + 0x3C) = 0.0f;
    *(f32 *)((u8 *)sp24 + 0x34) = (f32) **(f32 **)((u8 *)sp24 + 0x18);
    *(f32 *)((u8 *)sp24 + 0x38) = (f32) (1.0f / (2.0f * *(f32 *)((u8 *)sp24 + 0x1C)));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15134908 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15134908.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_151349D0.s")
void func_15134C98(BloodState *arg0, s32 arg1, u8 arg2) {
    if (arg0->unk28 == 1) {
        func_151BC5A4(arg0, arg1, arg2);
    }
}
void func_15134CD4(f32 arg0, f32 arg1, s32 arg2, s32 arg3) {

}
extern f32 D_800A45B0;
extern s32 D_800BE9E4;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15134CEC CURRENT (140) */
s32 func_15134CEC(void *arg0) {
    s32 temp_v1;

    *(f32 *)((u8 *)arg0 + 0x70) = (f32) (*(f32 *)((u8 *)arg0 + 0x70) + (0.125f * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x74) = (f32) (*(f32 *)((u8 *)arg0 + 0x74) + (D_800A45B0 * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x14) = (f32) (*(f32 *)((u8 *)arg0 + 0x14) + (*(f32 *)((u8 *)arg0 + 0x70) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x1C) = (f32) (*(f32 *)((u8 *)arg0 + 0x1C) + (*(f32 *)((u8 *)arg0 + 0x74) * D_800BE9A4));
    if (*(f32 *)((u8 *)arg0 + 0x14) > 130.0f) {
        return 0;
    }
    temp_v1 = *(u8 *)((u8 *)arg0 + 0x2E) - (D_800BE9E4 * 2);
    if (temp_v1 < 0) {
        return 0;
    }
    *(u8 *)((u8 *)arg0 + 0x2E) = (u8) temp_v1;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15134CEC */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15134CEC.s")
/* Call context: func_10022EC0: unique active declaration in the allowed source */
/* Call context: func_15167A68: unique active declaration in the allowed source */
void * func_15167A68(s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15134DAC CURRENT (754) */
void *func_15134DAC(u8 *arg0, s32 arg1) {
    u8 *temp_v0;

    temp_v0 = (void *)(func_15167A68(0x29, 0, arg1 + 0x80, 1, 0xFF, 1));
    if (temp_v0 == 0) {
        return 0;
    }
    {
        u8 * sp24 = temp_v0;
    func_10022EC0(temp_v0 + 0x18, arg0, 0x3C);
    *(s32 *)((u8 *)sp24 + 0x10) = 1;
    *(s16 *)((u8 *)sp24 + 0x54) = (s16) -*(s16 *)((u8 *)arg0 + 0x28);
    *(s32 *)((u8 *)sp24 + 0x14) = 0;
    *(f32 *)((u8 *)sp24 + 0x70) = 0.0f;
    *(f32 *)((u8 *)sp24 + 0x74) = 0.0f;
    *(f32 *)((u8 *)sp24 + 0x78) = 0.0f;
    return sp24;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15134DAC */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15134DAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15134E48.s")
void func_151352EC(void) {
    func_15169804();
}
void func_1513530C(void) {
    func_15169824();
}
void func_100111C8(u16, BloodState *); /* extern */
extern void (*D_80089B70[])(BloodState *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513532C CURRENT (468) */
void func_1513532C(BloodState *arg0) {
    s32 index;
    u16 handle;

    index = arg0->field50;
    if (index < 0) {
        index = 0;
    }
    if (index >= 6) {
        index = 0;
    }
    handle = arg0->field44;
    if (handle != 0) {
        func_100111C8(handle, arg0);
        arg0->field44 = 0;
    }
    D_80089B70[index](arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513532C */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513532C.s")
extern void (*D_80089B88[])(BloodState *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151353A8 CURRENT (468) */
void func_151353A8(BloodState *arg0) {
    s32 index;
    u16 handle;

    index = arg0->field50;
    if (index < 0) {
        index = 0;
    }
    if (index >= 6) {
        index = 0;
    }
    handle = arg0->field44;
    if (handle != 0) {
        func_100111C8(handle, arg0);
        arg0->field44 = 0;
    }
    D_80089B88[index](arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151353A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_151353A8.s")
void func_15145EA4(s32 *, s32 *, s32, s32);

void func_15135424(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp20[2];
    s32 sp18[2];

    sp20[0] = arg1;
    sp20[1] = arg2;
    sp18[0] = arg3;
    sp18[1] = arg4;
    func_15145EA4(sp20, sp18, arg0, 2);
}
/* Call context: func_1513555C: unique active declaration in the allowed source */
/* Call context: func_1516972C: unique active declaration in the allowed source */
void func_1513555C(void *, void *, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15135480 CURRENT (1387) */
void func_15135480(void *arg0, void *arg1, s32 arg2) {
    s32 temp_v0;
    s32 temp_v1;
    u8 temp_t6;
    u8 temp_v0_2;

    temp_t6 = arg2 & 0xFF;
    if (temp_t6 == 0x2D) {
        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        temp_v0 = *(s32 *)((u8 *)arg0 + 0x1C);
        if (temp_v1 == temp_v0) {
            *(s32 *)((u8 *)arg0 + 0x1C) = (s32) *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)arg0 + 0x18) = (u8) *(u8 *)((u8 *)arg1 + 9);
        } else if (*(s32 *)((u8 *)arg1 + 4) == temp_v0) {
            *(s32 *)((u8 *)arg0 + 0x1C) = temp_v1;
            *(u8 *)((u8 *)arg0 + 0x18) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    }
    temp_v0_2 = *(u8 *)((u8 *)arg0 + 0x50);
    switch (temp_v0_2) {                            /* irregular */
    case 1:
        func_151355B8(arg0, arg1, (s32) temp_t6);
        return;
    case 2:
        func_1513555C(arg0, arg1, temp_t6);
        return;
    default:
        if ((temp_t6 == 0) && ((*(s32 *)((u8 *)arg1 + 0) == *(s32 *)((u8 *)arg0 + 0x1C)) || ((u8) *(s32 *)((u8 *)arg1 + 4) == *(u8 *)((u8 *)arg0 + 0x18)))) {
            func_1516972C(arg0);
        }
        return;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15135480 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15135480.s")
void func_1516972C(void *);

void func_1513555C(void *arg0, void *arg1, u8 arg2) {
    if (((arg2 == 0) || (arg2 == 0x12)) &&
        ((*(void **)arg1 == *(void **)((u8 *)arg0 + 0x1C)) ||
         (*(u8 *)((u8 *)arg1 + 4) == *(u8 *)((u8 *)arg0 + 0x18)))) {
        func_1516972C(arg0);
    }
}
/* Call context: func_1516972C: unique active declaration in the allowed source */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151355B8 CURRENT (842) */
void func_151355B8(void *arg0, void *arg1, s32 arg2) {
    s32 temp_t6;
    s32 temp_t6_2;

    temp_t6 = arg2 & 0xFF;
    switch (temp_t6) {                              /* irregular */
    case 0:
        if ((*(s32 *)((u8 *)arg1 + 0) == *(s32 *)((u8 *)arg0 + 0x1C)) || (*(u8 *)((u8 *)arg1 + 4) == *(u8 *)((u8 *)arg0 + 0x18))) {
            func_1516972C(arg0);
            return;
        }
        return;
    case 3:
        if ((*(s32 *)((u8 *)arg1 + 0) == *(s32 *)((u8 *)arg0 + 0x1C)) || (*(u8 *)((u8 *)arg1 + 4) == *(u8 *)((u8 *)arg0 + 0x18))) {
            temp_t6_2 = *(s32 *)((u8 *)arg0 + 0x10) & ~1;
            *(s32 *)((u8 *)arg0 + 0x10) = temp_t6_2;
            *(s32 *)((u8 *)arg0 + 0x10) = temp_t6_2;
        }
        break;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151355B8 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_151355B8.s")
s32 func_15135658(f32 *arg0) {
    arg0[0x1D] = 1.0f;
    return 1;
}
s32 func_151422DC(s32, void *, s32, s32, s32, void *, s32);
extern u8 D_800A3FB4;
extern u8 D_800A3FBC;
extern f32 D_800A45B4;

f32 func_15135670(s32 arg0) {
    return (f32)func_151422DC(0, &D_800A3FB4, 0, 0x7D0, 0x3E8,
                             &D_800A3FBC, 0xB7A) * D_800A45B4;
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_151356D4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15135BF8 CURRENT (6876) */
s32 func_15135BF8(u8 *arg0) {
    f32 spC;
    f32 sp8;
    f32 temp_fa0;
    f32 temp_ft1;
    f32 temp_ft2;
    f32 temp_ft3;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 var_ft0;
    s32 var_v1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    var_v1 = 1;
    if (*(s16 *)((u8 *)arg0 + 0x70) > 0) {
        temp_v0 = (void *)(arg0 + 0x70);
        *(s16 *)((u8 *)arg0 + 0x70) = (s16) (*(s16 *)((u8 *)arg0 + 0x70) - D_800BE9E4);
        *(f32 *)((u8 *)arg0 + 0x10) = (f32) (*(f32 *)((u8 *)arg0 + 0x10) + (*(f32 *)((u8 *)temp_v0 + 8) * D_800BE9A4));
        *(f32 *)((u8 *)arg0 + 0x14) = (f32) (*(f32 *)((u8 *)arg0 + 0x14) + (*(f32 *)((u8 *)temp_v0 + 0xC) * D_800BE9A4));
        *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + (*(f32 *)((u8 *)temp_v0 + 4) * D_800BE9A4));
        var_ft0 = *(f32 *)((u8 *)arg0 + 0x1C) + (*(f32 *)((u8 *)temp_v0 + 4) * D_800BE9A4);
    } else {
        temp_v0_2 = (void *)(arg0 + 0x70);
        *(f32 *)((u8 *)&sp8 + 0) = *(f32 *)((u8 *)temp_v0_2 + 8);
        *(f32 *)((u8 *)&sp8 + 4) = (f32) *(f32 *)((u8 *)temp_v0_2 + 0xC);
        *(f32 *)((u8 *)arg0 + 0x14) = (f32) (*(f32 *)((u8 *)arg0 + 0x14) + ((*(f32 *)((u8 *)temp_v0_2 + 0xC) * D_800BE9A4) + (*(f32 *)((u8 *)temp_v0_2 + 0x10) * D_800BE9A4 * D_800BE9A4 * 0.5f)));
        *(f32 *)((u8 *)temp_v0_2 + 0xC) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0xC) + (*(f32 *)((u8 *)temp_v0_2 + 0x10) * D_800BE9A4));
        temp_ft2 = sp8 + *(f32 *)((u8 *)temp_v0_2 + 8);
        sp8 = temp_ft2;
        temp_ft3 = temp_ft2 * 0.5f;
        temp_ft1 = spC + *(f32 *)((u8 *)temp_v0_2 + 0xC);
        spC = temp_ft1;
        sp8 = temp_ft3;
        spC = temp_ft1 * 0.5f;
        temp_fa0 = fabsf(temp_ft3) * *(f32 *)((u8 *)temp_v0_2 + 0x14);
        *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + (temp_fa0 * D_800BE9A4));
        var_ft0 = *(f32 *)((u8 *)arg0 + 0x1C) + (temp_fa0 * D_800BE9A4);
    }
    *(f32 *)((u8 *)arg0 + 0x1C) = var_ft0;
    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x10);
    if ((temp_fv0 > 200.0f) || (temp_fv0 < -200.0f) || (temp_fv0_2 = *(f32 *)((u8 *)arg0 + 0x14), (temp_fv0_2 > 200.0f)) || (temp_fv0_2 < -200.0f)) {
        var_v1 = 0;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15135BF8 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15135BF8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15135DD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15136404.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15136698.s")
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151368A8 CURRENT (1500) */
s32 func_151368A8(void *arg0) {
    s16 temp_v0;
    s32 temp_v1;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    if (temp_v0 < 0x20) {
        temp_v1 = temp_v0 * 8;
        if (temp_v1 < (s32) *(u8 *)((u8 *)arg0 + 0x5C)) {
            *(u8 *)((u8 *)arg0 + 0x5C) = (u8) temp_v1;
        }
    }
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (*(f32 *)((u8 *)arg0 + 0x2C) + (*(f32 *)((u8 *)arg0 + 0x128) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (*(f32 *)((u8 *)arg0 + 0x30) + (*(f32 *)((u8 *)arg0 + 0x128) * D_800BE9A4));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151368A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_151368A8.s")
typedef struct {
    s32 field00;
    s16 field04;
    s8 field06;
    u8 pad07;
    s32 field08;
    s32 field0C;
    u8 bytes10[8];
    s32 field18;
    u8 tailPad[0xC];
} Blood6918Packet;

void *func_1513C73C(s32 *, s32, s32, void *, f32, f32, f32, f32,
                     f32, s32, s32, s32, s32, s32);

void func_15136918(f32 arg0, u8 arg1, u8 arg2, s16 arg3, s16 arg4,
                   void *arg5, f32 *arg6, u8 arg7, s32 arg8) {
    Blood6918Packet packet;
    volatile s32 padding[2];

    packet.field06 = 0x55;
    packet.field00 = 0x300;
    packet.field08 = 0;
    packet.field0C = 0;
    packet.bytes10[0] = arg1;
    packet.bytes10[1] = arg2;
    packet.bytes10[2] = 0;
    packet.bytes10[3] = 0;
    packet.bytes10[4] = 0;
    packet.bytes10[5] = 0;
    packet.field18 = 0x280001;
    packet.bytes10[6] = 1;
    packet.bytes10[7] = 1;
    if (arg3 == -1) {
        packet.field04 = 0x12C;
    } else {
        packet.field00 = 0x301;
        packet.field04 = arg3 + 0x20;
    }
    func_1513C73C(&packet.field00, 0xD, 0, arg5, arg6[0], arg6[1],
                  arg6[2], arg0, arg0, arg4, 0, 0, arg7, arg8);
}
s32 func_15136A1C(BloodState *arg0) {
    s16 temp_v0 = arg0->unk1C;

    if (temp_v0 < 0x20) {
        s32 temp_v1 = temp_v0 * 8;
        if (temp_v1 < arg0->unk28) {
            arg0->unk28 = temp_v1;
        }
    }
    return 1;
}
/* Call context: func_15134908: unique active project prototype */
void func_15134908(s32 *, s32, u8, s32);
extern f32 D_800A461C;
extern f32 D_800A4620;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15136A50 CURRENT (4162) */
void func_15136A50(s32 arg0, s32 arg1, s32 arg2, s16 arg3, u8 arg4, s32 arg5) {
    s8 sp35;
    s8 sp34;
    s8 sp33;
    s8 sp32;
    s16 sp30;
    f32 sp2C;
    f32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;

    sp32 = 5;
    sp33 = 5;
    sp34 = 2;
    sp35 = -1;
    sp28 = D_800A461C;
    sp1C = arg0;
    sp20 = arg1;
    sp24 = arg2;
    sp2C = D_800A4620;
    sp30 = arg3;
    func_15134908(&sp1C, 0, arg4, arg5);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15136A50 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15136A50.s")
f32 func_150ADA68(void);
u32 func_150ADA20(void);
void func_151D9014(f32 *, f32 *, s32, f32, s32, s32, f32, s32, f32,
                   f32, s32, s32, s32, s32, s32, s32);
extern f32 D_800A4624;
extern f32 D_800A4628;
extern f32 D_800A462C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15136AE4 CURRENT (48) */
void func_15136AE4(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4,
                   f32 arg5, void *arg6) {
    f32 sp6C[3];
    f32 sp60[3];
    u32 sp54;
    u32 sp50;
    f32 sp4C;
    f32 temp_fv1;

    sp6C[0] = arg0;
    sp6C[1] = arg1;
    sp6C[2] = arg2;
    temp_fv1 = ((func_150ADA68() * 112.0f) + 247.0f) * D_800A4624;
    sp60[0] = -arg3 * temp_fv1;
    sp60[1] = -arg4 * temp_fv1;
    sp60[2] = -arg5 * temp_fv1;
    sp4C = func_150ADA68();
    sp50 = func_150ADA20();
    sp54 = func_150ADA20();
    func_151D9014(sp6C, sp60, 0, (sp4C * D_800A4628) + D_800A462C,
                   (sp50 & 0xF) + 0x19, (sp54 % 101U) + 0x9B,
                   (func_150ADA68() * 119.0f) + 129.0f, 0, 1.0f, 1.0f,
                   1, 0, 1, 0, *(u8 *)((u8 *)arg6 + 0xC),
                   *(u8 *)((u8 *)arg6 + 1));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15136AE4 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15136AE4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15136C3C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15136F50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15137610.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513783C.s")
typedef struct BloodVec3 {
    f32 x;
    f32 y;
    f32 z;
} BloodVec3;

s32 func_15145128(BloodVec3 *, BloodVec3 *, f32 *, f32 *);
s32 func_15146078(BloodVec3 *, s32, s32);

s32 func_15137C64(BloodVec3 *arg0, BloodVec3 *arg1, BloodVec3 *arg2,
                    s32 arg3, s32 arg4, BloodVec3 *arg5,
                    BloodVec3 *arg6, BloodVec3 *arg7) {
    f32 sp2C;
    f32 sp28;

    if (arg5 != 0 && arg6 != 0) {
        *arg0 = *arg5;
        *arg1 = *arg6;
        goto have_positions;
    }
    if (arg5 != 0) {
        *arg0 = *arg5;
        *arg1 = *arg5;
        goto have_positions;
    }
    if (arg6 != 0) {
        *arg0 = *arg6;
        *arg1 = *arg6;
        goto have_positions;
    }
    return 0;

have_positions:
    if (arg7 == 0) {
        arg2->x = arg1->x - arg0->x;
        arg2->y = arg1->y - arg0->y;
        arg2->z = arg1->z - arg0->z;
        if (func_15145128(arg2, arg2, &sp2C, &sp28) == 0) {
            return 0;
        }
    } else {
        *arg2 = *arg7;
    }
    if (func_15146078(arg2, arg3, arg4) == 0) {
        return 2;
    }
    return 1;
}
f32 func_150ADA68();                                /* extern */
extern f32 D_800A4828;

s32 func_15137E10(void *arg0) {
    *(f32 *)((u8 *)arg0 + 0x74) = (f32) (((func_150ADA68() * 50.0f) + 580.0f) * D_800A4828);
    return 1;
}
void func_15137F30(void *, void *, void *, void *, f32, void *, void *, void *,
                   void *, f32 *, s16 *, s8 *, f32 *);
void func_151D9014(f32 *, f32 *, s32, f32, s32, s32, f32, s32, f32,
                   f32, s32, s32, s32, s32, s32, s32);

void func_15137E60(void *arg0, void *arg1, void *arg2, void *arg3, f32 arg4,
                   u8 *arg5) {
    f32 position[3];
    f32 direction[3];
    f32 vector[3];
    f32 value;
    s16 count;
    s8 alpha;
    f32 scale;

    func_15137F30(arg0, arg1, arg2, arg3, arg4, arg5, position, direction,
                   vector, &value, &count, &alpha, &scale);
    func_151D9014(position, vector, 0, value, count, (u8)alpha, scale, 0,
                   1.0f, 1.0f, 1, 0, 1, 0, arg5[0xC], arg5[1]);
}
u32 func_150ADA20();                                /* extern */
extern f32 D_800A482C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15137F30 CURRENT (405) */
void func_15137F30(void *arg0, void *arg1, void *arg2, void *arg3, f32 arg4, void *arg5, void *arg6, void *arg7, void *arg8, f32 *arg9, s16 *arg10, s8 *arg11, f32 *arg12) {
    *(f32 *)((u8 *)arg6 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) + (*(f32 *)((u8 *)arg2 + 0) * arg4));
    *(f32 *)((u8 *)arg6 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) + (*(f32 *)((u8 *)arg2 + 4) * arg4));
    *(f32 *)((u8 *)arg6 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) + (*(f32 *)((u8 *)arg2 + 8) * arg4));
    *(f32 *)((u8 *)arg7 + 0) = (f32) (*(f32 *)((u8 *)arg1 + 0) + (*(f32 *)((u8 *)arg3 + 0) * arg4));
    *(f32 *)((u8 *)arg7 + 4) = (f32) (*(f32 *)((u8 *)arg1 + 4) + (*(f32 *)((u8 *)arg3 + 4) * arg4));
    *(f32 *)((u8 *)arg7 + 8) = (f32) (*(f32 *)((u8 *)arg1 + 8) + (*(f32 *)((u8 *)arg3 + 8) * arg4));
    *(f32 *)((u8 *)arg8 + 0) = (f32) ((*(f32 *)((u8 *)arg7 + 0) - *(f32 *)((u8 *)arg6 + 0)) * *(f32 *)((u8 *)arg5 + 0x74));
    *(f32 *)((u8 *)arg8 + 4) = (f32) ((*(f32 *)((u8 *)arg7 + 4) - *(f32 *)((u8 *)arg6 + 4)) * *(f32 *)((u8 *)arg5 + 0x74));
    *(f32 *)((u8 *)arg8 + 8) = (f32) ((*(f32 *)((u8 *)arg7 + 8) - *(f32 *)((u8 *)arg6 + 8)) * *(f32 *)((u8 *)arg5 + 0x74));
    *arg9 = ((func_150ADA68(arg4) * 217.0f) + -456.0f) * D_800A482C;
    *arg10 = (func_150ADA20() % 31U) + 0x1E;
    *arg11 = (func_150ADA20() % 156U) + 0x64;
    *arg12 = (func_150ADA68() * 35.0f) + 40.0f;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15137F30 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15137F30.s")
typedef struct {
    u8 pad_0[0x74];
    u8 field_74;
    u8 pad_75[0x15F];
    u8 *field_1D4;
} Blood1380B4State;

typedef struct {
    f32 values[4];
} Blood1380B4Vector;

void func_15143134(f32 *, f32 *, s32);
extern Blood1380B4Vector D_800A3FD8[];

s32 func_151380B4(Blood1380B4State *arg0, s32 arg1, f32 *arg2) {
    u8 *temp_v0;

    temp_v0 = arg0->field_1D4;
    if (temp_v0 == 0) {
        return 0;
    }
    if ((arg0->field_74 & 0xF) == 0xF) {
        return 0;
    }
    func_15143134(D_800A3FD8[arg1].values, arg2, (s32)(temp_v0 + 0x300));
    return 1;
}
extern u8 D_800A4058;
extern u8 D_800A4068;
extern u8 D_1000EBC4;
s32 func_1000FA64(s32, s16, s16, s16, s32, s32, s32, void *, s32, s32, s32, s32);
void func_15134DAC(u8 *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15138120 CURRENT (969) */
void func_15138120(Blood1380B4State *arg0, s32 arg1, s32 arg2) {
    struct {
        u8 color;
        u8 pad01[3];
        Blood1380B4State *owner;
        s8 type;
        u8 pad09[3];
        f32 values[6];
        s8 mode;
        u8 pad25;
        s16 width;
        s16 height;
        s16 alpha;
        s16 sound;
        s8 count;
        s8 amount;
        s8 loop;
        u8 pad31[3];
        f32 scale;
        s8 byte38;
        s8 byte39;
    } packet;
    Blood1380B4Vector *vector;
    u8 kind;

    vector = &D_800A3FD8[arg1];
    kind = ((u8 *)vector)[0xE];
    if (kind == 2) {
        return;
    }
    packet.owner = arg0;
    packet.color = arg0->pad_0[0x3B];
    if (arg2 & 0xFF) {
        packet.type = 0xC;
    } else {
        packet.type = 1;
    }
    packet.mode = 2;
    packet.width = 0x28;
    packet.height = 0x10;
    packet.values[0] = 0.0f;
    packet.values[1] = 0.0f;
    packet.values[2] = 0.0f;
    packet.values[3] = 0.0f;
    packet.values[5] = 0.0f;
    packet.values[4] = 20.0f;
    if ((u8 *)vector == &D_800A4058 || (u8 *)vector == &D_800A4068) {
        if (*(s32 *)((u8 *)arg0 + 0x94) & 0xE) {
            packet.alpha = 0x78;
        } else {
            packet.alpha = 0xF0;
        }
    } else {
        packet.alpha = 0x258;
    }
    packet.count = 5;
    if (kind == 0) {
        packet.amount = 5;
    } else {
        packet.amount = 6;
    }
    packet.loop = -1;
    packet.byte38 = 0;
    packet.byte39 = -1;
    packet.scale = 1.0f;
    packet.sound = (s16)func_1000FA64(0x4FE,
        (s16)(s32)*(f32 *)((u8 *)arg0 + 0x14),
        (s16)(s32)*(f32 *)((u8 *)arg0 + 0x18),
        (s16)(s32)*(f32 *)((u8 *)arg0 + 0x1C),
        0x5DC0, 0x258, 0x12C, &D_1000EBC4, 0x78, 0, 0, 0);
    func_15134DAC(&packet.color, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15138120 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15138120.s")
typedef struct Blood382E0Position {
    s32 x;
    s32 y;
    s32 z;
} Blood382E0Position;

typedef struct Blood382E0Packet {
    s16 field_00;
    s16 field_02;
    s16 field_04;
    s16 field_06;
    Blood382E0Position position;
    f32 field_14;
    f32 field_18;
    f32 field_1C;
    f32 field_20;
    f32 field_24;
    f32 field_28;
    s16 field_2C;
    s16 field_2E;
    s16 field_30;
    s16 field_32;
    s16 field_34;
    s16 field_36;
    s16 field_38;
    s16 field_3A;
    u8 field_3C;
    u8 pad_3D[3];
    f32 field_40;
    s16 field_44;
    s16 field_46;
    s32 field_48;
} Blood382E0Packet;

void func_15153F18(s16 *, void *, s32, s32, s32);
extern u8 D_800A3FE6[];
extern f32 D_800A4830;
extern f32 D_800A4834;
extern f32 D_800A4838;
extern f32 D_800A483C;
extern f32 D_800A4840;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151382E0 CURRENT (1000) */
void func_151382E0(f32 *arg0, s32 arg1, void *arg2, u8 arg3, s32 arg4) {
    Blood382E0Packet packet;
    u8 kind;

    kind = D_800A3FE6[arg1 * 0x10];
    if (kind != 2) {
        packet.position = *(Blood382E0Position *)arg0;
        packet.field_14 = D_800A4830;
        packet.field_2C = 0x12;
        packet.field_2E = 7;
        packet.field_02 = 0xFF;
        packet.field_00 = 0;
        packet.field_04 = -0x3F;
        packet.field_06 = 0x4E;
        packet.field_30 = 3;
        packet.field_32 = 3;
        packet.field_34 = 0x14;
        packet.field_36 = 0x1E;
        packet.field_38 = 0x9B;
        packet.field_3A = 0x64;
        packet.field_44 = 0x10;
        packet.field_46 = 0xF;
        packet.field_48 = 0;
        packet.field_18 = D_800A4834;
        packet.field_1C = D_800A4838;
        packet.field_20 = D_800A483C;
        packet.field_24 = 4.0f;
        packet.field_28 = 9.0f;
        packet.field_40 = D_800A4840;
        if (kind == 1) {
            packet.field_3C = 1;
        } else {
            packet.field_3C = 0;
        }
        func_15153F18(&packet.field_00, &packet.position, (s32)arg2,
                       arg3, arg4);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151382E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_151382E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15138424.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_151389A8.s")
s32 func_15134070(Blood1380B4State *);
void func_15138120(Blood1380B4State *, s32, s32);
void func_151382E0(f32 *, s32, void *, u8, s32);
void func_15138424(Blood1380B4State *, f32 *, s32, void *, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15138BC0 CURRENT (96) */
void func_15138BC0(Blood1380B4State *arg0, u8 arg1, s32 arg2) {
    struct {
        u8 pad[0x27];
        u8 sp4F;
        f32 sp50;
    } locals;
    s32 temp_v0;

    temp_v0 = func_15134070(arg0);
    if (temp_v0 != 0x63) {
        locals.sp4F = func_151380B4(arg0, temp_v0, &locals.sp50);
        func_15138120(arg0, temp_v0, 1);
        if (locals.sp4F != 0) {
            func_1504715C(locals.pad, arg0);
            func_151382E0(&locals.sp50, temp_v0, locals.pad, arg1, arg2);
            func_15138424(arg0, &locals.sp50, temp_v0, locals.pad, arg1, arg2);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15138BC0 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15138BC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15138C80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15138E98.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15139578.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15139768.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15139D74.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513A24C.s")
typedef struct {
    s32 x;
    s32 y;
    s32 z;
} BloodA48CPosition;

typedef struct {
    s32 field_0;
    s32 field_4;
    BloodA48CPosition position;
    s16 field_14;
    s16 field_16;
    s16 field_18;
    s16 field_1A;
    f32 field_1C;
    f32 field_20;
    f32 field_24;
    f32 field_28;
    s16 field_2C;
    s16 field_2E;
    f32 field_30;
    f32 field_34;
    f32 field_38;
} BloodA48CConfig;

void func_15152190(void *, void *, void *, s32, f32, s32, s32, s32);
extern u8 D_800A4260[];
extern u8 D_800A4264[];
extern f32 D_800A4950;
extern f32 D_800A4954;
extern f32 D_800A4958;
extern f32 D_800A495C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513A48C CURRENT (692) */
void func_1513A48C(BloodA48CPosition *arg0, u8 arg1, s32 arg2) {
    BloodA48CConfig config;
    register f32 repeated;
    register f32 zero_value;

    repeated = D_800A4950;
    zero_value = 0.0f;
    config.field_0 = 8;
    config.field_4 = 4;
    config.position = *arg0;
    config.field_14 = 0;
    config.field_16 = 0xFF;
    config.field_18 = -0x37;
    config.field_1A = 0x20;
    config.field_2C = 0x28;
    config.field_2E = 0x14;
    config.field_30 = repeated;
    config.field_34 = repeated;
    config.field_1C = 10.0f;
    config.field_20 = 9.0f;
    config.field_24 = D_800A4954;
    config.field_28 = D_800A4958;
    config.field_38 = D_800A495C;
    func_15152190(&config, D_800A4260, D_800A4264, 1, zero_value, 1,
                  (s32)arg1, arg2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513A48C */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513A48C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513A594 CURRENT (924) */
void func_1513A594(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_t6;

    temp_t6 = arg3 & 0xFF;
    func_1513A5E0(arg1, temp_t6 & 0xFF, arg4, temp_t6);
    if (*(s32 *)((u8 *)arg0 + 0x1D4) == 0) {
        return;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513A594 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513A594.s")
typedef struct {
    s32 x;
    s32 y;
    s32 z;
} BloodA5E0Position;

typedef struct {
    s32 field_0;
    s32 field_4;
    BloodA5E0Position position;
    s16 field_14;
    s16 field_16;
    s16 field_18;
    s16 field_1A;
    f32 field_1C;
    f32 field_20;
    f32 field_24;
    f32 field_28;
    s16 field_2C;
    s16 field_2E;
    f32 field_30;
    f32 field_34;
    f32 field_38;
} BloodA5E0Config;

void func_15152190(void *, void *, void *, s32, f32, s32, s32, s32);
extern u8 D_800A4268[];
extern u8 D_800A4270[];
extern f32 D_800A4960;
extern f32 D_800A4964;
extern f32 D_800A4968;
extern f32 D_800A496C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513A5E0 CURRENT (847) */
void func_1513A5E0(s32 arg0, s32 arg1, s32 arg2) {
    BloodA5E0Config config;
    register f32 scale;
    register f32 repeated;

    scale = 4.0f;
    repeated = D_800A4960;
    config.field_0 = 7;
    config.field_4 = 7;
    config.position = *(BloodA5E0Position *)arg0;
    config.field_14 = 0;
    config.field_16 = 0xFF;
    config.field_18 = -0x32;
    config.field_1A = 0x1B;
    config.field_1C = scale;
    config.field_20 = scale;
    config.field_2C = 0x19;
    config.field_2E = 0x28;
    config.field_30 = repeated;
    config.field_34 = repeated;
    config.field_24 = D_800A4964;
    config.field_28 = D_800A4968;
    config.field_38 = D_800A496C;
    func_15152190(&config, D_800A4268, D_800A4270, 2, 0.0f, 1,
                  (u8)arg1, arg2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513A5E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513A5E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513A6E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513ABB8.s")

void func_1513B0B8(BloodState *arg0, s32 arg1, u8 arg2) {
    s32 *counter = &arg0->unk170;

    if (arg2 == 0x45) {
        if (--*counter < 0) {
            arg0->flags60 |= 0x80;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513B0F8.s")
