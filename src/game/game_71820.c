#include "types.h"

/*
 * Reviewed source unit: src/game/game_71820.c
 * Boundary evidence: docs/evidence/game_raw_core_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15044380
 * - func_1504452C
 * - func_15044660
 * - func_15044964
 * - func_15044A28
 * - func_15044B78
 * - func_15044D40
 * - func_15044DA0
 * - func_15044DE8
 * - func_15044E40
 * - func_15044E88
 * - func_15044ED0
 * - func_150450CC
 * - func_1504530C
 * - func_15045384
 * - func_1504554C
 * - func_15045714
 * - func_15045780
 * - func_15045800
 * - func_15045880
 * - func_15045AE4
 * - func_15045D48
 * - func_15045F8C
 * - func_150461D0
 * - func_15046460
 * - func_150466F8
 * - func_1504697C
 * - func_15046C00
 * - func_15046C80
 * - func_15046D00
 * - func_15046F84
 * - func_1504715C
 * - func_150472C0
 * - func_15047390
 * - func_15047700
 * - func_15047B80
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800CBD9C;

void func_15044370(void) {
    D_800CBD9C = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15044380.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1504452C CURRENT (6172) */
void func_1504452C(s32 *arg0, void *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7) {
    f32 temp_ft1;
    f32 temp_ft1_2;
    f32 temp_ft3;
    f32 temp_ft3_2;
    f32 var_fa0;
    s16 var_ft4;
    s32 *var_v1;
    u8 *temp_a3;
    u8 *var_a3;
    u8 *var_v0;

    var_v1 = arg0;
    var_a3 = arg1;
    {
        s32 var_a2 = 0xC;
    var_v0 = (void *)(*var_v1 + arg7);
    var_ft4 = *(s16 *)((u8 *)var_v0 + 4);
    var_fa0 = (f32) *(s16 *)((u8 *)var_v0 + 0);
    if (0xC != 0x24) {
        do {
            var_a2 += 0xC;
            var_v1 += 4;
            temp_ft1 = var_fa0 - arg4;
            var_a3 += 0xC;
            temp_ft3 = (f32) var_ft4 - arg6;
            *(f32 *)((u8 *)var_a3 + -8) = (f32) ((f32) *(s16 *)((u8 *)var_v0 + 2) - arg5);
            *(f32 *)((u8 *)var_a3 + -0xC) = (f32) ((temp_ft1 * arg3) + (temp_ft3 * arg2));
            *(f32 *)((u8 *)var_a3 + -4) = (f32) ((temp_ft3 * arg3) - (temp_ft1 * arg2));
            var_v0 = (void *)(*var_v1 + arg7);
            var_ft4 = *(s16 *)((u8 *)var_v0 + 4);
            var_fa0 = (f32) *(s16 *)((u8 *)var_v0 + 0);
        } while (var_a2 != 0x24);
    }
    temp_a3 = (void *)(var_a3 + 0xC);
    temp_ft1_2 = var_fa0 - arg4;
    temp_ft3_2 = (f32) var_ft4 - arg6;
    *(f32 *)((u8 *)temp_a3 + -0xC) = (f32) ((temp_ft1_2 * arg3) + (temp_ft3_2 * arg2));
    *(f32 *)((u8 *)temp_a3 + -4) = (f32) ((temp_ft3_2 * arg3) - (temp_ft1_2 * arg2));
    *(f32 *)((u8 *)temp_a3 + -8) = (f32) ((f32) *(s16 *)((u8 *)var_v0 + 2) - arg5);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1504452C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_1504452C.s")
void func_15044658(void) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15044660.s")
void *func_15044964(s32, s32, s32, void *, s32, s32, s32, s32);

void *func_150448D0(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    void *temp_v0;

    temp_v0 = func_15044964(0x20, 1, arg0, arg1, arg2, 0, 0, 0);
    if (temp_v0 == 0) {
        return 0;
    }
    *(s16 *)((u8 *)temp_v0 + 0x10) = (s16)arg3;
    *(s16 *)((u8 *)temp_v0 + 0x12) = (s16)arg4;
    *(s16 *)((u8 *)temp_v0 + 0x14) = (s16)arg5;
    *(s8 *)((u8 *)temp_v0 + 0x16) = (s8)arg6;
    *(s32 *)((u8 *)temp_v0 + 0x18) = arg7;
    *(s32 *)((u8 *)temp_v0 + 0x1C) = arg8;
    return temp_v0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15044964.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15044A28.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15044B78.s")
void func_15044B78(void);

void func_15044CE4(void *arg0) {
    s32 temp_t0;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x18);
    *(s16 *)((u8 *)arg0 + 6) = *(s16 *)temp_v0;
    *(s16 *)((u8 *)arg0 + 8) = *(s16 *)((u8 *)temp_v0 + 2);
    *(s16 *)((u8 *)arg0 + 0xA) = *(s16 *)((u8 *)temp_v0 + 4);
    temp_t0 = *(s16 *)*(void **)((u8 *)arg0 + 0x1C) / 32;
    *(s16 *)((u8 *)arg0 + 0x10) = temp_t0;
    *(s16 *)((u8 *)arg0 + 0x12) = temp_t0;
    *(s16 *)((u8 *)arg0 + 0x14) = temp_t0;
    func_15044B78();
}
s32 func_1505D1C4(f32, f32, f32, s16, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15044D40 CURRENT (220) */
s32 func_15044D40(void *arg0) {
    s32 sp1C;

    sp1C = 0;
    func_1505D1C4((f32)*(s16 *)((u8 *)arg0 + 6), (f32)*(s16 *)((u8 *)arg0 + 8),
                  (f32)*(s16 *)((u8 *)arg0 + 0xA), *(s16 *)((u8 *)arg0 + 0x10),
                  0xFF, 0, 0, sp1C);
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15044D40 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15044D40.s")
extern void func_1505D024(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 D_800CC2D0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15044DA0 CURRENT (580) */
void func_15044DA0(void) {
    u8 *temp_a0;

    temp_a0 = D_800CC2D0;
    if (temp_a0[0x104] != 0) {
        return;
    }
    if (temp_a0[0x125] != 0) {
        return;
    }
    func_1505D024((s32) temp_a0, 5, *(u16 *)(temp_a0 + 0x7A), -1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15044DA0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15044DA0.s")
/* Call context: func_1505D024: unique active project prototype */
extern u8 D_800C35EA;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15044DE8 CURRENT (535) */
void func_15044DE8(void) {
    if ((*(u8 *)((u8 *)D_800CC2D0 + 0x104) == 0) && (*(u8 *)((u8 *)D_800CC2D0 + 0x125) == 0) && (D_800C35EA != 1)) {
        func_1505D024((s32) D_800CC2D0, 4, (s32) *(u16 *)((u8 *)D_800CC2D0 + 0x7A), -1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15044DE8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15044DE8.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15044E40 CURRENT (640) */
void func_15044E40(void) {
    if ((D_800CC2D0[0x104] == 0) && (D_800CC2D0[0x125] == 0)) {
        func_1505D024((s32) D_800CC2D0, 0x40, *(u16 *)(D_800CC2D0 + 0x7A), -1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15044E40 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15044E40.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15044E88 CURRENT (580) */
void func_15044E88(void) {
    u8 *temp_a0;

    temp_a0 = D_800CC2D0;
    if ((temp_a0[0x104] == 0) && (temp_a0[0x125] == 0)) {
        func_1505D024((s32) temp_a0, 1, *(u16 *)(temp_a0 + 0x7A), -1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15044E88 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15044E88.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15044ED0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_150450CC.s")
s32 func_15044ED0(s32, s32, s32);                   /* extern */
s32 func_150470B0(void *, f32, void *);             /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1504530C CURRENT (819) */
s32 func_1504530C(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;

    temp_v0 = func_150470B0(arg0, arg1, arg2);
    switch (temp_v0) {                              /* irregular */
    case 0:
        return func_15044ED0(arg0, arg1, arg2);
    case 1:
        return 0;
    case 2:
        return 1;
    default:
        return temp_v0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1504530C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_1504530C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15045384.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_1504554C.s")
typedef struct Game71820XZ {
    f32 x;
    u8 pad4[4];
    f32 z;
} Game71820XZ;

s32 func_150A6500(s16, s16, s32, u16);
void func_1510F800(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15045714 CURRENT (100) */
void func_15045714(Game71820XZ *arg0, u16 arg1, s32 *arg2, s32 arg3) {
    func_1510F800(2);
    *arg2 = func_150A6500((s16)(s32)arg0->x, (s16)(s32)arg0->z, arg3, arg1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15045714 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15045714.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15045780.s")
s32 func_15045780(s32, u16, s32, s32);              /* extern */
s32 func_15047004(void *, f32, void *);             /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15045800 CURRENT (819) */
s32 func_15045800(s32 arg0, u16 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;

    temp_v0 = func_15047004(arg0, arg2, arg3);
    switch (temp_v0) {                              /* irregular */
    case 0:
        return func_15045780(arg0, arg1, arg2, arg3);
    case 1:
        return 0;
    case 2:
        return 1;
    default:
        return temp_v0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15045800 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15045800.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15045880.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15045AE4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15045D48.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15045F8C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_150461D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15046460.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_150466F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_1504697C.s")
s32 func_150466F8(s32, u16, s32, s32);              /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15046C00 CURRENT (819) */
s32 func_15046C00(s32 arg0, u16 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;

    temp_v0 = func_150470B0(arg0, arg2, arg3);
    switch (temp_v0) {                              /* irregular */
    case 0:
        return func_150466F8(arg0, arg1, arg2, arg3);
    case 1:
        return 0;
    case 2:
        return 1;
    default:
        return temp_v0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15046C00 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15046C00.s")
s32 func_1504697C(s32, u16, s32, s32);              /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15046C80 CURRENT (819) */
s32 func_15046C80(s32 arg0, u16 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;

    temp_v0 = func_15047004(arg0, arg2, arg3);
    switch (temp_v0) {                              /* irregular */
    case 0:
        return func_1504697C(arg0, arg1, arg2, arg3);
    case 1:
        return 0;
    case 2:
        return 1;
    default:
        return temp_v0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15046C80 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15046C80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15046D00.s")
s32 func_15046D00(s32, u16, s32, s32);              /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15046F84 CURRENT (819) */
s32 func_15046F84(s32 arg0, u16 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;

    temp_v0 = func_15047004(arg0, arg2, arg3);
    switch (temp_v0) {                              /* irregular */
    case 0:
        return func_15046D00(arg0, arg1, arg2, arg3);
    case 1:
        return 0;
    case 2:
        return 1;
    default:
        return temp_v0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15046F84 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15046F84.s")
extern s32 func_150A3FC4(f32, f32, s32, void *, f32 *);

s32 func_15047004(void *arg0, f32 arg1, void *arg2) {
    f32 sp24;

    if ((*(u8 *)((u8 *)arg2 + 0x1C) & 4) &&
        (func_150A3FC4(*(f32 *)arg0, *(f32 *)((u8 *)arg0 + 8), 0, (u8 *)arg2 + 4, &sp24) != 0)) {
        if ((arg1 <= sp24) && (sp24 <= *(f32 *)((u8 *)arg0 + 4))) {
            *(f32 *)arg2 = sp24;
            *(u8 *)((u8 *)arg2 + 0x1C) = (u8)(*(u8 *)((u8 *)arg2 + 0x1C) | 2);
            return 2;
        }
        return 1;
    }
    return 0;
}
s32 func_150470B0(void *arg0, f32 arg1, void *arg2) {
    f32 sp24;

    if ((*(u8 *)((u8 *)arg2 + 0x1C) & 4) &&
        (func_150A3FC4(*(f32 *)arg0, *(f32 *)((u8 *)arg0 + 8), 0, (u8 *)arg2 + 4, &sp24) != 0)) {
        if ((sp24 <= arg1) && (*(f32 *)((u8 *)arg0 + 4) <= sp24)) {
            *(f32 *)arg2 = sp24;
            *(u8 *)((u8 *)arg2 + 0x1C) = (u8)(*(u8 *)((u8 *)arg2 + 0x1C) | 2);
            return 2;
        }
        return 1;
    }
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_1504715C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_150472C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15047390.s")
typedef struct {
    f32 elements[16];
} Game71820Matrix;

void func_15047390(Game71820Matrix *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void func_150A7790(void *, s32);

void func_15047688(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9) {
    Game71820Matrix matrix;

    func_15047390(&matrix, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
    func_150A7790(&matrix, arg0);
}
/* Call context: func_150A7BC0: unique active project prototype */
void func_150A7BC0(s32, s32);
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15047700 CURRENT (16646) */
void func_15047700(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10) {
    f32 sp4C;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fa0_3;
    f32 temp_fa0_4;
    f32 temp_fa0_6;
    f32 temp_fa0_7;
    f32 temp_fa0_8;
    f32 temp_fa1;
    f32 temp_fa1_2;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 temp_fv1_3;
    f32 temp_fv1_4;
    f32 temp_fv1_5;
    f32 var_fs0;
    f32 var_fs1;
    f32 var_fs2;
    f32 var_fs4;
    f32 var_fs5;
    f32 var_ft5;
    f32 var_fv0;
    f32 var_fv0_2;
    f32 var_fv0_3;
    f32 var_fv0_4;
    f32 var_fv0_5;
    f32 var_fv0_6;

    func_150A7BC0(arg0, arg1);
    temp_fv0 = arg6 - arg3;
    temp_fv1 = arg7 - arg4;
    var_fs1 = temp_fv0;
    var_fs0 = arg5 - arg2;
    var_fs2 = temp_fv1;
    if ((arg5 == arg2) && (temp_fv0 == 0.0f) && (temp_fv1 == 0.0f)) {
        var_fs2 = 1.0f;
        var_fs0 = 0.0f;
        var_fs1 = 0.0f;
    }
    temp_fv1_2 = -1.0f / sqrtf((var_fs0 * var_fs0) + (var_fs1 * var_fs1) + (var_fs2 * var_fs2));
    temp_fs0 = var_fs0 * temp_fv1_2;
    temp_fs1 = var_fs1 * temp_fv1_2;
    temp_fs2 = var_fs2 * temp_fv1_2;
    temp_fa0 = (arg9 * temp_fs2) - (arg10 * temp_fs1);
    temp_fa1 = (arg10 * temp_fs0) - (arg8 * temp_fs2);
    temp_ft5 = (arg8 * temp_fs1) - (arg9 * temp_fs0);
    sp4C = temp_ft5;
    temp_fv0_2 = (temp_fa0 * temp_fa0) + (temp_fa1 * temp_fa1) + (temp_ft5 * temp_ft5);
    if (temp_fv0_2 != 0.0f) {
        temp_fv1_3 = 1.0f / sqrtf(temp_fv0_2);
        var_fs4 = temp_fa0 * temp_fv1_3;
        var_fs5 = temp_fa1 * temp_fv1_3;
        sp4C *= temp_fv1_3;
    } else {
        var_fs4 = 1.0f;
        var_fs5 = 0.0f;
        sp4C = 0.0f;
    }
    temp_fv0_3 = (temp_fs1 * sp4C) - (temp_fs2 * var_fs5);
    arg8 = temp_fv0_3;
    temp_fv1_4 = (temp_fs2 * var_fs4) - (temp_fs0 * sp4C);
    arg9 = temp_fv1_4;
    temp_fa0_2 = (temp_fs0 * var_fs5) - (temp_fs1 * var_fs4);
    arg10 = temp_fa0_2;
    temp_fa1_2 = (temp_fv0_3 * temp_fv0_3) + (temp_fv1_4 * temp_fv1_4) + (temp_fa0_2 * temp_fa0_2);
    if (temp_fa1_2 != 0.0f) {
        temp_fv1_5 = 1.0f / sqrtf(temp_fa1_2);
        var_ft5 = arg8 * temp_fv1_5;
        arg9 *= temp_fv1_5;
        arg10 *= temp_fv1_5;
    } else {
        arg8 = 0.0f;
        var_ft5 = arg8;
        arg10 = 0.0f;
        arg9 = 1.0f;
    }
    temp_fa0_3 = var_fs4 * 128.0f;
    if (temp_fa0_3 < 127.0f) {
        var_fv0 = temp_fa0_3;
    } else {
        var_fv0 = 127.0f;
    }
    temp_fa0_4 = var_fs5 * 128.0f;
    *(s8 *)((u8 *)arg1 + 8) = (s8) (s32) var_fv0;
    if (temp_fa0_4 < 127.0f) {
        var_fv0_2 = temp_fa0_4;
    } else {
        var_fv0_2 = 127.0f;
    }
    *(s8 *)((u8 *)arg1 + 9) = (s8) (s32) var_fv0_2;
    {
        f32 temp_fa0_5 = sp4C * 128.0f;
    if (temp_fa0_5 < 127.0f) {
        var_fv0_3 = temp_fa0_5;
    } else {
        var_fv0_3 = 127.0f;
    }
    temp_fa0_6 = var_ft5 * 128.0f;
    *(s8 *)((u8 *)arg1 + 0xA) = (s8) (s32) var_fv0_3;
    if (temp_fa0_6 < 127.0f) {
        var_fv0_4 = temp_fa0_6;
    } else {
        var_fv0_4 = 127.0f;
    }
    *(s8 *)((u8 *)arg1 + 0x18) = (s8) (s32) var_fv0_4;
    temp_fa0_7 = arg9 * 128.0f;
    if (temp_fa0_7 < 127.0f) {
        var_fv0_5 = temp_fa0_7;
    } else {
        var_fv0_5 = 127.0f;
    }
    temp_fa0_8 = arg10 * 128.0f;
    *(s8 *)((u8 *)arg1 + 0x19) = (s8) (s32) var_fv0_5;
    if (temp_fa0_8 < 127.0f) {
        var_fv0_6 = temp_fa0_8;
    } else {
        var_fv0_6 = 127.0f;
    }
    *(s8 *)((u8 *)arg1 + 0) = 0;
    *(s8 *)((u8 *)arg1 + 1) = 0;
    *(s8 *)((u8 *)arg1 + 2) = 0;
    *(s8 *)((u8 *)arg1 + 3) = 0;
    *(s8 *)((u8 *)arg1 + 4) = 0;
    *(s8 *)((u8 *)arg1 + 5) = 0;
    *(s8 *)((u8 *)arg1 + 6) = 0;
    *(s8 *)((u8 *)arg1 + 7) = 0;
    *(s8 *)((u8 *)arg1 + 0x10) = 0;
    *(s8 *)((u8 *)arg1 + 0x11) = 0x80;
    *(s8 *)((u8 *)arg1 + 0x12) = 0;
    *(s8 *)((u8 *)arg1 + 0x13) = 0;
    *(s8 *)((u8 *)arg1 + 0x14) = 0;
    *(s8 *)((u8 *)arg1 + 0x15) = 0x80;
    *(s8 *)((u8 *)arg1 + 0x16) = 0;
    *(s8 *)((u8 *)arg1 + 0x17) = 0;
    *(s8 *)((u8 *)arg1 + 0x1A) = (s8) (s32) var_fv0_6;
    *(f32 *)((u8 *)arg0 + 0) = var_fs4;
    *(f32 *)((u8 *)arg0 + 0x10) = var_fs5;
    *(f32 *)((u8 *)arg0 + 4) = var_ft5;
    *(f32 *)((u8 *)arg0 + 0x20) = sp4C;
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) -((arg2 * var_fs4) + (arg3 * var_fs5) + (arg4 * sp4C));
    *(f32 *)((u8 *)arg0 + 0x24) = arg10;
    *(f32 *)((u8 *)arg0 + 0x14) = arg9;
    *(f32 *)((u8 *)arg0 + 8) = temp_fs0;
    *(f32 *)((u8 *)arg0 + 0x18) = temp_fs1;
    *(f32 *)((u8 *)arg0 + 0x28) = temp_fs2;
    *(f32 *)((u8 *)arg0 + 0x34) = (f32) -((arg2 * var_ft5) + (arg3 * arg9) + (arg4 * arg10));
    *(f32 *)((u8 *)arg0 + 0xC) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x1C) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x2C) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x3C) = 1.0f;
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) -((arg2 * temp_fs0) + (arg3 * temp_fs1) + (arg4 * temp_fs2));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15047700 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15047700.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15047B80.s")
