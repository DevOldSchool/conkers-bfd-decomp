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
 * - func_15136918
 * - func_15136A50
 * - func_15136AE4
 * - func_15136C3C
 * - func_15136F50
 * - func_15137610
 * - func_1513783C
 * - func_15137C64
 * - func_15137E60
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
void func_1513A5E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15134070.s")
s32 func_1513416C(void *arg0) {
    short temp_v0;

    temp_v0 = *(short *)((char *)arg0 + 0x1C);
    if (temp_v0 < 0x20) {
        *(char *)((char *)arg0 + 0x28) = (char)(temp_v0 * 8);
    }
    return 1;
}
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
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_151347CC.s")
void func_151348F0(f32 arg0, f32 arg1, s32 arg2, s32 arg3) {

}
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
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15135480.s")
void func_1516972C(void *);

void func_1513555C(void *arg0, void *arg1, u8 arg2) {
    if (((arg2 == 0) || (arg2 == 0x12)) &&
        ((*(void **)arg1 == *(void **)((u8 *)arg0 + 0x1C)) ||
         (*(u8 *)((u8 *)arg1 + 4) == *(u8 *)((u8 *)arg0 + 0x18)))) {
        func_1516972C(arg0);
    }
}
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
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15136918.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15136A50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15136AE4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15136C3C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15136F50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15137610.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513783C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15137C64.s")
f32 func_150ADA68();                                /* extern */
extern f32 D_800A4828;

s32 func_15137E10(void *arg0) {
    *(f32 *)((u8 *)arg0 + 0x74) = (f32) (((func_150ADA68() * 50.0f) + 580.0f) * D_800A4828);
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15137E60.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15138120.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_151382E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15138424.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_151389A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15138BC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15138C80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15138E98.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15139578.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15139768.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_15139D74.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/blood/func_1513A24C.s")
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
