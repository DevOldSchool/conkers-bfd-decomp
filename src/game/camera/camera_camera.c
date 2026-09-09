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
 * - func_15124770
 * - func_151247C0
 * - func_15124AB4
 * - func_15124B18
 * - func_15124C38
 * - func_1512523C
 * - func_15125330
 * - func_15125394
 * - func_151253CC
 * - func_15125490
 * - func_151254F4
 * - func_15125628
 * - func_15125690
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
 * - func_15127FEC
 * - func_15128030
 * - func_151283B8
 * - func_151284C4
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
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15123934.s")
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_151239CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15123A54.s")
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15124770.s")
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_151247C0.s")
f32 func_15047C00(f32);                             /* extern */
f32 func_15047D60(f32);                             /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15124AB4 CURRENT (20) */
void func_15124AB4(void *arg0) {
    *(f32 *)((u8 *)arg0 + 0x668) = (f32) -func_15047D60(*(f32 *)((u8 *)arg0 + 0x398));
    *(f32 *)((u8 *)arg0 + 0x66C) = func_15047C00(*(f32 *)((u8 *)arg0 + 0x398));
    *(f32 *)((u8 *)arg0 + 0x664) = (f32) (func_15047D60(*(f32 *)((u8 *)arg0 + 0x39C)) * *(f32 *)((u8 *)arg0 + 0x66C));
    *(f32 *)((u8 *)arg0 + 0x66C) = (f32) (func_15047C00(*(f32 *)((u8 *)arg0 + 0x39C)) * *(f32 *)((u8 *)arg0 + 0x66C));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15124AB4 */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15124AB4.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15125490.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15125628.s")
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15125690.s")
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_151256BC.s")
s32 func_15123934(void *, s32, s32, s32, s32);
void func_151239CC(void *, s32);
void func_15124B18(void *);
s32 func_15125490(void *, s32);

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
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15127FEC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15128030.s")
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_151283B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_151284C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15128540.s")
void func_15128680(s32 arg0) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_1512868C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15128774.s")
