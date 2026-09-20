#include "types.h"

/*
 * Reviewed source unit: src/game/camera/camera_camera.c
 * Boundary evidence: docs/evidence/game_beta_camera_rope_bee.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15122AE0
 * - func_15122C5C
 * - func_15123070
 * - func_1512317C
 * - func_15123568
 * - func_151236D0
 * - func_15123934
 * - func_151239CC
 * - func_15123A54
 * - func_151247C0
 * - func_15124B18
 * - func_15124C38
 * - func_1512523C
 * - func_15125330
 * - func_15125394
 * - func_151253CC
 * - func_15125490
 * - func_151254F4
 * - func_15125628
 * - func_151256BC
 * - func_15125924
 * - func_15125A6C
 * - func_15125C40
 * - func_15125DB4
 * - func_1512623C
 * - func_15126378
 * - func_15127520
 * - func_151277B0
 * - func_151279A0
 * - func_15127EB8
 * - func_15128030
 * - func_151283B8
 * - func_15128540
 * - func_1512868C
 * - func_15128774
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15122AE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15122C5C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15123070.s")
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_1512317C.s")
void func_15123508(void *arg0) {
    if (*(s32 *)((u8 *)arg0 + 0x84) & 2) {
        if ((*(u16 *)((u8 *)arg0 + 0x36A) & 2) && (*(s32 *)((u8 *)arg0 + 0x698) == 0)) {
            *(s32 *)((u8 *)arg0 + 0x6B0) = -1;
        }
        if ((*(u16 *)((u8 *)arg0 + 0x36A) & 1) && (*(s32 *)((u8 *)arg0 + 0x698) == 0)) {
            *(s32 *)((u8 *)arg0 + 0x6B0) = 1;
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15123568.s")
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_151236D0.s")
s32 func_15125394(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15123934 CURRENT (1090) */
s32 func_15123934(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 var_v0;
    u8 *temp_v0;
    u8 *temp_v1;

    var_v0 = 0;
    temp_v1 = (u8 *)arg0 + (arg4 * 2);
    if (*(s16 *)(temp_v1 + 0x20C) == 0) {
        *(u16 *)(temp_v1 + 2) = *(u16 *)arg0;
        temp_v0 = (u8 *)arg0 + (arg4 * 4);
        *(s32 *)(temp_v0 + 0x30) = *(s32 *)((u8 *)arg0 + 0x2C);
        *(s32 *)(temp_v0 + 0x88) = *(s32 *)((u8 *)arg0 + 0x84);
        *(s32 *)(temp_v0 + 0xE0) = *(s32 *)((u8 *)arg0 + 0xDC);
        *(s32 *)(temp_v0 + 0x138) = *(s32 *)((u8 *)arg0 + 0x134);
        *(s16 *)(temp_v1 + 0x1B6) = *(s16 *)((u8 *)arg0 + 0x1B4);
        *(s16 *)(temp_v1 + 0x1E2) = *(s16 *)((u8 *)arg0 + 0x1E0);
        *(s32 *)((u8 *)arg0 + 0x2C) = arg1;
        *(s32 *)((u8 *)arg0 + 0xDC) = arg2;
        *(s32 *)((u8 *)arg0 + 0x134) = arg3;
        *(s16 *)(temp_v1 + 0x20C) = 1;
        func_15125394();
        var_v0 = 1;
    }
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15123934 */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15123934.s")
void func_15124B18();
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151239CC CURRENT (688) */
s32 func_151239CC(void *arg0, s32 arg1) {
    s32 var_v0;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v1 = (u8 *)arg0 + (arg1 * 2);
    var_v0 = 0;
    if (*(s16 *)(temp_v1 + 0x20C) != 0) {
        temp_v0 = (u8 *)arg0 + (arg1 * 4);
        *(u16 *)arg0 = *(u16 *)(temp_v1 + 2);
        *(s32 *)((u8 *)arg0 + 0x2C) = *(s32 *)(temp_v0 + 0x30);
        *(s32 *)((u8 *)arg0 + 0xDC) = *(s32 *)(temp_v0 + 0xE0);
        *(s32 *)((u8 *)arg0 + 0x84) = *(s32 *)(temp_v0 + 0x88);
        *(s32 *)((u8 *)arg0 + 0x134) = *(s32 *)(temp_v0 + 0x138);
        *(s16 *)((u8 *)arg0 + 0x1B4) = *(s16 *)(temp_v1 + 0x1B6);
        *(s16 *)((u8 *)arg0 + 0x1E0) = *(s16 *)(temp_v1 + 0x1E2);
        func_15124B18();
        var_v0 = 1;
        *(s16 *)(temp_v1 + 0x20C) = 0;
    }
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151239CC */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_151239CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15123A54.s")
typedef struct {
    u8 pad_0[0x244];
    s16 field_244;
    u8 pad_246[2];
    void *field_248;
} CameraCameraState;

extern u8 D_800CC2D0[];

void func_15124770(CameraCameraState *arg0, s32 arg1) {
    if (arg1 != 0) {
        arg0->field_244 = arg1;
        arg0->field_248 = D_800CC2D0 + (arg1 * 0x32C);
    } else {
        arg0->field_244 = 0;
        arg0->field_248 = 0;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_151247C0.s")
f32 func_15047C00(f32);                             /* extern */
f32 func_15047D60(f32);                             /* extern */

void func_15124AB4(void *arg0) {
    *(f32 *)((u8 *)arg0 + 0x668) = (f32) -func_15047D60(*(f32 *)((u8 *)arg0 + 0x398));
    *(f32 *)((u8 *)arg0 + 0x66C) = func_15047C00(*(f32 *)((u8 *)arg0 + 0x398));
    *(f32 *)((u8 *)arg0 + 0x664) = (f32) (*(f32 *)((u8 *)arg0 + 0x66C) * func_15047D60(*(f32 *)((u8 *)arg0 + 0x39C)));
    *(f32 *)((u8 *)arg0 + 0x66C) = (f32) (*(f32 *)((u8 *)arg0 + 0x66C) * func_15047C00(*(f32 *)((u8 *)arg0 + 0x39C)));
}
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15124B18.s")
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15124C38.s")
f32 func_150484A0(f32, f32);                        /* extern */
extern f32 D_800A351C;
extern f32 D_800A3520;

f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1512523C CURRENT (685) */
void func_1512523C(void *arg0) {
    f32 temp_fa0;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fa1;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x2BC) - *(f32 *)((u8 *)arg0 + 0x2F8);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x2C4) - *(f32 *)((u8 *)arg0 + 0x300);
    {
        f32 temp_fv0 = sqrtf((temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0));
    if (temp_fv0 < 0.0f) {
        var_fa1 = -temp_fv0;
    } else {
        var_fa1 = temp_fv0;
    }
    temp_fv1_2 = func_150484A0(*(f32 *)((u8 *)arg0 + 0x2FC) - *(f32 *)((u8 *)arg0 + 0x2C0), var_fa1) * D_800A351C;
    *(f32 *)((u8 *)arg0 + 0x388) = temp_fv1_2;
    if (temp_fv1_2 > 180.0f) {
        *(f32 *)((u8 *)arg0 + 0x388) = (f32) (*(f32 *)((u8 *)arg0 + 0x388) - 360.0f);
    }
    *(f32 *)((u8 *)arg0 + 0x388) = (f32) -*(f32 *)((u8 *)arg0 + 0x388);
    *(f32 *)((u8 *)arg0 + 0x388) = (f32) (*(f32 *)((u8 *)arg0 + 0x388) - *(f32 *)((u8 *)arg0 + 0x3A8));
    *(f32 *)((u8 *)arg0 + 0x388) = (f32) (*(f32 *)((u8 *)arg0 + 0x388) + *(f32 *)((u8 *)arg0 + 0x38C));
    *(f32 *)((u8 *)arg0 + 0x398) = (f32) (*(f32 *)((u8 *)arg0 + 0x388) * D_800A3520);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1512523C */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_1512523C.s")
f32 func_15048FC8(f32 *, void *);                   /* extern */
extern f32 D_800A3524;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15125330 CURRENT (689) */
void func_15125330(void *arg0) {
    f32 sp24;
    f32 sp20;
    f32 sp1C;

    sp20 = 0.0f;
    sp1C = *(f32 *)((u8 *)arg0 + 0x2BC) - *(f32 *)((u8 *)arg0 + 0x2F8);
    sp24 = *(f32 *)((u8 *)arg0 + 0x2C4) - *(f32 *)((u8 *)arg0 + 0x300);
    {
        f32 temp_fv0 = func_15048FC8(&sp1C, arg0);
    *(f32 *)((u8 *)arg0 + 0x37C) = temp_fv0;
    *(f32 *)((u8 *)arg0 + 0x39C) = (f32) (temp_fv0 * D_800A3524);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15125330 */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15125330.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15125394 CURRENT (290) */
void func_15125394(void *arg0) {
    s16 var_v0;
    s32 temp_v1;

    temp_v1 = *(s32 *)((u8 *)arg0 + 0x2C);
    var_v0 = 0;
    if (!(temp_v1 & 1)) {
        do {
            var_v0 += 1;
        } while (!(temp_v1 & (1 << var_v0)));
    }
    *(s16 *)((u8 *)arg0 + 0) = var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15125394 */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15125394.s")
void func_15124AB4(void *);
void func_1512523C(void *);
void func_15125330(void *);
void func_15127EB8(void *);
void func_1512C490(void *);
extern f32 D_800A3528;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151253CC CURRENT (95) */
s32 func_151253CC(u8 *arg0) {
    f32 value;
    f32 scale;
    f32 other;
    s32 flags;

    if (*(s32 *)(arg0 + 0x2C) & 0x40000) {
        flags = *(volatile s32 *)(arg0 + 0x84) & ~0x4F;
        *(volatile s32 *)(arg0 + 0x84) = flags;
        *(volatile s32 *)(arg0 + 0x84) = flags | 0x2680;
        *(f32 *)(arg0 + 0x3A8) = 0.0f;
        *(f32 *)(arg0 + 0x5E8) = 0.0f;
        *(f32 *)(arg0 + 0x38C) = 0.0f;
        func_15125330(arg0);
        func_1512523C(arg0);
        scale = D_800A3528;
        value = *(f32 *)(arg0 + 0x37C);
        other = *(f32 *)(arg0 + 0x388);
        *(f32 *)(arg0 + 0x380) = value;
        *(f32 *)(arg0 + 0x3A0) = scale * value;
        *(f32 *)(arg0 + 0x398) = other * scale;
        func_15124AB4(arg0);
        if ((*(u8 **)(arg0 + 0x3D4))[0x197] != 0) {
            func_15127EB8(arg0);
        }
        func_1512C490(arg0);
        return 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151253CC */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_151253CC.s")
typedef struct {
    u8 pad_0[0x14];
    f32 field_14;
    f32 field_18;
    f32 field_1C;
    u8 pad_20[0x8D];
    u8 field_AD;
    u8 pad_AE[0x6A];
    f32 field_118;
} CameraCameraTarget;

typedef struct {
    u8 pad_0[0x84];
    u32 field_84;
    u8 pad_88[0x1B4];
    u8 field_23C;
    u8 pad_23D[0x73];
    f32 field_2B0;
    f32 field_2B4;
    f32 field_2B8;
    u8 pad_2BC[0x114];
    CameraCameraTarget *field_3D0;
    u8 pad_3D4[0x22A];
    s16 field_5FE;
} CameraCameraTargetState;

f32 fabsf(f32);
#pragma intrinsic(fabsf)

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15125490 CURRENT (560) */
void *func_15125490(CameraCameraTargetState *arg0) {
    s32 difference;
    CameraCameraTarget *var_v0;

    var_v0 = arg0->field_3D0;
    if (var_v0->field_AD == 1) {
        difference = (s32)fabsf(var_v0->field_18 - var_v0->field_118);
        if (difference < 100) {
            return 0;
        }
        if (difference >= 301) {
            return (void *)1;
        }
        return var_v0;
    }
    var_v0 = 0;
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15125490 */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15125490.s")
extern f32 D_800A352C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151254F4 CURRENT (828) */
void func_151254F4(void *arg0, s32 arg1) {
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x380) * D_800A352C;
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x388) * D_800A352C;
    *(f32 *)((u8 *)arg0 + 0x3A0) = temp_fv0;
    *(f32 *)((u8 *)arg0 + 0x398) = temp_fv1;
    func_15124AB4(arg0);
    func_151239CC(arg0, 1);
    *((u8 *)*(void **)((u8 *)arg0 + 0x3D4) + 0x198) = 0;
    *(s16 *)((u8 *)arg0 + 0x73C) = 0;
    *(f32 *)((u8 *)arg0 + 0x670) = 0.0f;
    *(void **)((u8 *)arg0 + 0x3D0) = (void *)(D_800CC2D0 + (arg1 * 0x32C));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151254F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_151254F4.s")
extern f32 D_800A3530;

void func_15125594(void *arg0) {
    f32 temp_fv0;
    f32 temp_fv1;

    func_1512523C(arg0);
    func_15125330(arg0);
    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x37C);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x5E8);
    *(f32 *)((u8 *)arg0 + 0x380) = (f32) (temp_fv0 - temp_fv1);
    if (temp_fv0 < temp_fv1) {
        *(f32 *)((u8 *)arg0 + 0x380) = (f32) (*(f32 *)((u8 *)arg0 + 0x380) + 360.0f);
    }
    *(f32 *)((u8 *)arg0 + 0x3A0) = (f32) (*(f32 *)((u8 *)arg0 + 0x380) * D_800A3530);
    func_15124AB4(arg0);
}
void func_15125608(f32 *arg0) {
    arg0[0x93] = 3.0f;
    arg0[0x94] = 2.5f;
}
extern u8 D_800DBFF4[];
extern u8 D_800DBFF5;
extern u8 D_800DBFF6[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15125628 CURRENT (1100) */
void func_15125628(void) {
    u8 value;

    value = D_800DBFF4[0];
    if (value != 0) {
        D_800DBFF4[0] = value - 1;
    }
    value = D_800DBFF5;
    if (value != 0) {
        D_800DBFF5 = value - 1;
    }
    value = D_800DBFF6[0];
    if (value != 0) {
        D_800DBFF6[0] = value - 1;
    }
    value = D_800DBFF6[1];
    if (value != 0) {
        D_800DBFF6[1] = value - 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15125628 */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15125628.s")

void func_15125690(void *arg0, s32 arg1) {
    u8 *temp_v0;

    temp_v0 = &D_800DBFF4[*(u8 *)((u8 *)arg0 + 0x23D)];
    if ((s32) *temp_v0 < arg1) {
        *temp_v0 = (u8) arg1;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_151256BC.s")
s32 func_15123934(void *, s32, s32, s32, s32);
s32 func_151239CC(void *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15125924 CURRENT (450) */
void func_15125924(u8 *arg0) {
    f32 difference;
    s32 flags;
    s32 value;
    s32 type;
    u8 *target;

    target = *(u8 **)(arg0 + 0x3D4);
    value = 0;
    type = 0;
    if (target != 0) {
        type = target[0x4E];
        value = (s32)*(f32 *)(target + 0x1C);
    }
    if (!(*(s32 *)(arg0 + 0x2C) & 0x40) &&
        ((*(s32 *)(arg0 + 0x84) & 0x4000) ||
         (*(u8 **)(arg0 + 0x3D0))[0x102] != 0)) {
        if ((func_15125490(arg0, value) != 0) &&
            (type == 0) && (value == 0)) {
            if ((func_15123934(arg0, 0x80, 1, 1, 0xD) != 0) &&
                (*(s32 *)(arg0 + 0x6C8) == 0)) {
                func_15124B18(arg0);
                *(s32 *)(arg0 + 0x5F0) |= 0x1000;
            }
        } else {
            if (*(s32 *)(arg0 + 0x2C) & 0x80) {
                func_151239CC(arg0, 0xD);
                *(f32 *)(arg0 + 0x190) = 0.0f;
            }
            flags = *(s32 *)(arg0 + 0x5F0);
            if (flags & 0x1000) {
                difference = *(f32 *)(arg0 + 0x2FC) - *(f32 *)(arg0 + 0x354);
                *(s32 *)(arg0 + 0x5F0) = flags & ~0x1000;
                *(f32 *)(arg0 + 0x344) = difference;
                *(f32 *)(arg0 + 0x348) = difference;
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15125924 */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15125924.s")
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15125A6C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15125C40.s")
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15125DB4.s")
void func_151220D0(void *);
void func_151247C0(void);
void func_15124C38(void *, s32);

void func_15126138(u8 *arg0) {
    u8 *target;

    func_151247C0();
    target = *(u8 **)(arg0 + 0x3D0);
    if (((*(f32 *)(arg0 + 0x2B0) != *(f32 *)(target + 0x14)) ||
         (*(f32 *)(arg0 + 0x2B4) != *(f32 *)(target + 0x18)) ||
         (*(f32 *)(arg0 + 0x2B8) != *(f32 *)(target + 0x1C))) &&
        (*(s32 *)(arg0 + 0x2C) & ~0x100)) {
        *(s16 *)(arg0 + 0x298) = 1;
        *(s16 *)(arg0 + 0x7E6) = 0x3C;
        *(s8 *)(arg0 + 0x8ED) = 0;
    } else {
        *(s16 *)(arg0 + 0x298) = 0;
    }
    if (*(s32 *)(arg0 + 0x84) & 0x200000) {
        target = *(u8 **)(arg0 + 0x3D0);
        if ((*(s32 *)target != 0x1E) &&
            (target[0x102] == 0) &&
            (**(u16 **)(arg0 + 0x36C) & 0xF) &&
            !(*(s32 *)(arg0 + 0x2C) & 0x40)) {
            func_151220D0(arg0);
        }
    }
    func_15124C38(arg0, 0);
}
typedef struct Camera2623CVector {
    f32 x;
    f32 y;
    f32 z;
} Camera2623CVector;

void func_15143134(f32 *, f32 *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1512623C CURRENT (132) */
void func_1512623C(u8 *arg0, u8 *arg1, s32 arg2, f32 *arg3, f32 *arg4,
                   f32 *arg5, s32 arg6) {
    s32 saved_result;
    Camera2623CVector input;
    Camera2623CVector output;
    s32 mode;
    s32 result;
    s32 call_index;

    result = 1;
    if (*(s32 *)(arg0 + 0x1D4) != 0) {
        result = 0;
        if (arg6 != 0) {
            mode = 3;
            input.x = 0.0f;
            input.z = 0.0f;
            input.y = 20.0f;
        } else if (arg2 == 0x1B) {
            mode = 4;
            input.y = 116.0f;
            input.x = 0.0f;
            input.z = 130.0f;
        } else {
            result = 1;
        }
        if (result == 0) {
            call_index = *(s32 *)(arg0 + 0x1D4) + (mode << 6);
            saved_result = result;
            func_15143134(&input.x, &output.x, call_index);
            result = saved_result;
            *arg3 = output.x;
            *arg4 = output.y;
            *arg5 = output.z;
        }
    }
    if (result != 0) {
        *arg3 = *(f32 *)(arg0 + 0x14);
        *arg4 = ((f32)*(s16 *)(arg1 + 0x114) * 0.75f) + *(f32 *)(arg0 + 0x18);
        *arg5 = *(f32 *)(arg0 + 0x1C);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1512623C */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_1512623C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15126378.s")
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15127520.s")
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_151277B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_151279A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15127EB8.s")
extern void func_1512A390(void);

void func_15127FEC(void *arg0, void *arg1, void *arg2) {
    *(s16 *)((u8 *) arg0 + 0x7F4) = 1;
    *(f32 *)((u8 *) arg0 + 0x7F8) = *(f32 *)((u8 *) arg0 + 0x2A4);
    *(f32 *)((u8 *) arg0 + 0x7FC) = *(f32 *)((u8 *) arg0 + 0x2A8);
    *(f32 *)((u8 *) arg0 + 0x800) = *(f32 *)((u8 *) arg0 + 0x2AC);
    func_1512A390();
}
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15128030.s")
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_151283B8.s")
void func_15128774(CameraCameraTargetState *, CameraCameraTarget *); /* extern */

void func_151284C4(CameraCameraTargetState *arg0) {
    u8 temp_v1;
    CameraCameraTarget *target;

    func_1512C490(arg0);
    target = arg0->field_3D0;
    temp_v1 = arg0->field_23C;
    arg0->field_2B0 = target->field_14;
    arg0->field_2B4 = target->field_18;
    arg0->field_2B8 = target->field_1C;
    if (temp_v1 != 0) {
        arg0->field_23C = temp_v1 - 1;
    }
    if ((arg0->field_84 & 8) && (arg0->field_5FE <= 0)) {
        arg0->field_5FE = 0x3C;
        func_15128774(arg0, arg0->field_3D0);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15128540.s")
void func_15128680(s32 arg0) {

}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1512868C CURRENT (3570) */
void func_1512868C(u8 *arg0) {
    s32 var_v1;
    u8 temp_v0;
    u8 *temp_t0;
    u8 *temp_v1;
    u8 *var_v0;

    *(s16 *)((u8 *)arg0 + 0x20C) = 0;
    var_v1 = 1;
    var_v0 = (void *)(arg0 + 2);
    do {
        var_v1 += 4;
        *(s16 *)((u8 *)var_v0 + 0x20E) = 0;
        *(s16 *)((u8 *)var_v0 + 0x210) = 0;
        *(s16 *)((u8 *)var_v0 + 0x212) = 0;
        var_v0 += 8;
        *(s16 *)((u8 *)var_v0 + 0x204) = 0;
    } while (var_v1 != 0x15);
    *(s32 *)((u8 *)arg0 + 0x2C) = 1;
    *(s32 *)((u8 *)arg0 + 0xDC) = 0;
    *(s32 *)((u8 *)arg0 + 0x134) = 1;
    *(s32 *)((u8 *)arg0 + 0x84) = 0xE;
    *(s16 *)((u8 *)arg0 + 0x1B4) = 3;
    func_15124B18(arg0, arg0);
    temp_v0 = *(u8 *)((u8 *)arg0 + 0x23D);
    temp_v1 = (void *)((temp_v0 * 0x32C) + D_800CC2D0);
    *(void **)((u8 *)arg0 + 0x3D0) = temp_v1;
    *(s16 *)((u8 *)arg0 + 0x3CC) = (s16) temp_v0;
    *(s16 *)((u8 *)arg0 + 0x368) = (s16) temp_v0;
    temp_t0 = (void *)(*(void **)((u8 *)temp_v1 + 0x31C));
    *(f32 *)((u8 *)arg0 + 0x190) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x198) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x18C) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x194) = 0.0f;
    *(void **)((u8 *)arg0 + 0x3D4) = temp_t0;
    *(f32 *)((u8 *)arg0 + 0x674) = 1.0f;
    *(s8 *)((u8 *)temp_t0 + 0x198) = 0;
    *(s16 *)((u8 *)arg0 + 0x73C) = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1512868C */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_1512868C.s")
typedef struct {
    u8 pad_0[0x40];
    f32 field_40;
} Camera128774Source;

typedef struct {
    u8 pad_0[0x18C];
    f32 field_18C;
} Camera128774TargetState;

typedef struct {
    u8 pad_0[0x23C];
    u8 field_23C;
    u8 pad_23D[0xBB];
    f32 field_2F8;
    f32 field_2FC;
    f32 field_300;
    f32 field_304;
    f32 field_308;
    f32 field_30C;
    u8 pad_310[0x4C];
    f32 field_35C;
    u8 pad_360[0x1C];
    f32 field_37C;
    u8 pad_380[0x50];
    Camera128774Source *field_3D0;
    Camera128774TargetState *field_3D4;
} Camera128774State;

typedef struct {
    u8 pad_0[0x14];
    f32 x;
    f32 y;
    f32 z;
    u8 pad_20[0x160];
    f32 field_180;
} Camera128774Object;

extern f32 D_800A35AC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15128774 CURRENT (300) */
void func_15128774(Camera128774State *arg0, Camera128774Object *arg1) {
    arg0->field_35C = arg1->field_180;
    arg0->field_304 = arg0->field_2F8 = arg1->x;
    arg0->field_308 = arg0->field_2FC = arg1->y;
    arg0->field_30C = arg0->field_300 = arg1->z;
    arg0->field_37C = arg0->field_3D0->field_40 - 180.0f;
    arg0->field_3D4->field_18C = D_800A35AC;
    arg0->field_23C = 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15128774 */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15128774.s")
