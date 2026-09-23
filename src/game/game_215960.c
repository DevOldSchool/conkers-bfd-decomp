#include "types.h"

/*
 * Reviewed source unit: src/game/game_215960.c
 * Boundary evidence: docs/evidence/game_raw_connected_controller_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151E86E4
 * - func_151E89A0
 * - func_151E966C
 * - func_151E9D18
 * - func_151EA15C
 * - func_151EADFC
 * - func_151EB06C
 * - func_151EB96C
 * - func_151EBB50
 * - func_151EC178
 * - func_151EC1F0
 * - func_151EC3E8
 * - func_151EC648
 * - func_151ED09C
 * - func_151ED1E0
 * - func_151ED29C
 * - func_151ED430
 * - func_151ED90C
 * - func_151EDBDC
 * - func_151EDF4C
 * - func_151EE184
 * - func_151EEBE8
 * - func_151EEFF0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef void *(*Game215960Dispatch)(void *);
typedef struct {
    u8 pad0[0x1D0];
    s32 field_1D0;
} Game215960State;

void *func_151ED1E0(void *);
void func_15042D94(s32, s32, s32, s32);
void func_1504332C(s32, s32, s32, s32);
extern s32 D_8003C8E0;
extern s32 D_80000300;
extern s8 D_8008FD90;
extern Game215960Dispatch D_8008FFF4[];
extern u8 D_800BE616;
extern u8 D_800BE740;
extern s8 D_800E0BD3;
extern Game215960State *D_800E0BD8;
extern u8 D_800E0B94;

void *func_151E84B0(void *arg0) {
    s32 effect = 0;
    Game215960Dispatch callback;

    D_8003C8E0 = 0x09000001;
    arg0 = func_151ED1E0(arg0);
    callback = D_8008FFF4[D_800E0B94];
    if (callback != 0) {
        arg0 = callback(arg0);
    }
    if (D_80000300 != 0) {
        if ((D_800BE616 != 0) && (D_8008FD90 >= 2)) {
            if ((D_800BE740 & 0xF) == 0) {
                if (D_800E0BD3 == 1) {
                    effect = 0x33;
                } else if (D_800E0BD3 == 2) {
                    effect = 0x16;
                }
            }
        } else if ((D_800BE740 & 1) == 0) {
            if (D_800E0BD3 == 1) {
                effect = 0x32;
            } else if (D_800E0BD3 == 2) {
                effect = 0x15;
            }
        }
    }
    if (effect != 0) {
        func_1504332C(0xFF, 0xFF, 0xFF, 0xFF);
        func_15042D94(0x94, 0xC8, 0x81, ((s32 *)D_800E0BD8)[effect]);
    }
    D_8003C8E0 = 0;
    return arg0;
}
typedef s32 (*Game215960Callback)(s32, s32);

extern s32 D_8003C8E0;
extern Game215960Callback D_8008FFC0[];
extern s32 D_80090058;
extern u8 D_800BE9C0;
extern s32 D_800BE9C8[];
extern s32 D_800BEBA4;
extern u8 D_800E0B94;
extern s16 D_800E0C78;

s32 func_151E8620(s32 arg0) {
    Game215960Callback callback;
    s32 original;
    s32 result;
    u8 mode;

    mode = D_800E0B94;
    original = arg0;
    D_8003C8E0 = 0x09000000;
    callback = D_8008FFC0[mode];
    if (callback != 0) {
        arg0 = callback(arg0, (s32) callback);
    }
    if (D_800E0B94 != 0) {
        D_80090058 = 0;
        D_800E0C78 = 0;
    }
    D_8003C8E0 = 0;
    if (D_800BEBA4 < ((arg0 - D_800BE9C8[D_800BE9C0]) >> 3)) {
        result = 1;
    } else {
        result = 0;
    }
    if (result != 0) {
        return original;
    }
    return arg0;
}
extern f32 D_8008FE1C;
extern f32 D_8008FE20;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151E86E4 CURRENT (6320) */
void *func_151E86E4(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    s16 var_t0;
    s16 var_t0_2;
    s16 var_t1;
    s16 var_t1_2;
    s32 temp_t4;
    s32 temp_t5;
    s32 temp_t6;
    s32 temp_t7;
    s32 var_a2;
    s32 var_t1_3;
    s32 var_t2;
    s32 var_v0;
    s32 var_v0_2;
    u8 *temp_a0;

    var_a2 = arg2;
    if (D_8008FE1C != 1.0f) {
        arg1 = (s32) ((f32) arg1 * D_8008FE1C);
        arg3 = (s32) ((f32) arg3 * D_8008FE1C);
        var_a2 = (s32) ((f32) var_a2 * D_8008FE20);
        arg4 = (s32) ((f32) arg4 * D_8008FE20);
        arg8 = (s32) ((f32) arg8 / D_8008FE1C);
        arg9 = (s32) ((f32) arg9 / D_8008FE20);
    }
    {
        u8 * temp_a0_2 = (void *)(arg0 + 8);
    if ((s16) arg3 > 0) {
        var_t0 = (s16) arg3;
    } else {
        var_t0 = 0;
    }
    if ((s16) arg4 > 0) {
        var_t1 = (s16) arg4;
    } else {
        var_t1 = 0;
    }
    *(s32 *)((u8 *)arg0 + 0) = (s32) ((var_t1 & 0xFFF) | 0xE4000000 | ((var_t0 & 0xFFF) << 0xC));
    if ((s16) arg1 > 0) {
        var_t0_2 = (s16) arg1;
    } else {
        var_t0_2 = 0;
    }
    if ((s16) var_a2 > 0) {
        var_t1_2 = (s16) var_a2;
    } else {
        var_t1_2 = 0;
    }
    *(s32 *)((u8 *)arg0 + 4) = (s32) ((var_t1_2 & 0xFFF) | ((arg5 & 7) << 0x18) | ((var_t0_2 & 0xFFF) << 0xC));
    *(s32 *)((u8 *)arg0 + 8) = 0xE1000000;
    temp_a0 = (void *)(temp_a0_2 + 8);
    if ((s16) arg1 < 0) {
        if ((s16) arg8 < 0) {
            temp_t5 = (s32) ((s16) arg1 * (s16) arg8) >> 7;
            if (temp_t5 > 0) {
                var_t2 = temp_t5;
            } else {
                var_t2 = 0;
            }
        } else {
            var_v0 = 0;
            temp_t4 = (s32) ((s16) arg1 * (s16) arg8) >> 7;
            if (temp_t4 < 0) {
                var_v0 = temp_t4;
            }
            var_t2 = var_v0;
        }
    } else {
        var_t2 = 0;
    }
    if (var_a2 < 0) {
        if ((s16) arg9 < 0) {
            temp_t7 = (s32) ((s16) var_a2 * (s16) arg9) >> 7;
            if (temp_t7 > 0) {
                var_t1_3 = temp_t7;
            } else {
                var_t1_3 = 0;
            }
        } else {
            var_v0_2 = 0;
            temp_t6 = (s32) ((s16) var_a2 * (s16) arg9) >> 7;
            if (temp_t6 < 0) {
                var_v0_2 = temp_t6;
            }
            var_t1_3 = var_v0_2;
        }
    } else {
        var_t1_3 = 0;
    }
    *(s32 *)((u8 *)temp_a0_2 + 4) = (s32) (((arg7 - var_t1_3) & 0xFFFF) | ((arg6 - var_t2) << 0x10));
    *(s32 *)((u8 *)temp_a0_2 + 8) = 0xF1000000;
    *(s32 *)((u8 *)temp_a0 + 4) = (s32) ((arg8 << 0x10) | (arg9 & 0xFFFF));
    return temp_a0 + 8;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151E86E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151E86E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151E89A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151E966C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151E9D18.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EA15C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EADFC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EB06C.s")
extern s16 D_8008FDCC;
extern s32 func_151EA15C(s32, s32, s16, s32);

s32 func_151EB930(s32 arg0) {
    if (D_8008FDCC != 0) {
        arg0 = func_151EA15C(arg0, 0x6A, D_8008FDCC, 0);
    }
    return arg0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EB96C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EBB50.s")

void func_15042D94(s32, s32, s32, s32);
void func_1504332C(s32, s32, s32, s32);
extern s32 D_800E0A90;
extern Game215960State *D_800E0BD8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151EC178 CURRENT (230) */
s32 func_151EC178(s32 arg0) {
    s32 scaled;
    s32 alpha;

    if (D_800E0A90 >= 0x5DD) {
        scaled = (D_800E0A90 - 0x5DC) << 3;
        alpha = scaled;
        if (scaled >= 0x100) {
            alpha = 0xFF;
        }
        func_1504332C(0xFF, 0xFF, 0xFF, alpha & 0xFF);
        func_15042D94(0xDC, 0x130, 1, D_800E0BD8->field_1D0);
    }
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151EC178 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EC178.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EC1F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EC3E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EC648.s")
void func_15096934(void *);
void *func_151ED430(void *, void *, s32, s32, s32, s32, f32, s32);
extern u8 D_80090028[];
extern u8 D_8009181C[];
extern u8 D_80091828[];
extern u8 D_800E0B97;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151ED09C CURRENT (2769) */
void func_151ED09C(void *arg0) {
    s32 saved_alpha;
    s32 scaled;
    s32 alpha;
    u8 *command;
    u8 *result;

    *(u32 *)arg0 = 0xDE000000;
    *(void **)((u8 *)arg0 + 4) = D_80090028;
    command = (u8 *)arg0 + 8;
    scaled = D_800E0A90 * 4;
    alpha = scaled;
    if (scaled >= 0x100) {
        alpha = 0xFF;
    }
    *(u32 *)command = 0xFB000000;
    *(u32 *)(command + 4) = (alpha & 0xFF) | ~0xFF;
    saved_alpha = alpha;
    result = func_151ED430(command + 8, D_8009181C, 0x92, 0x6C,
                           8, 3, 1.0f, 0);
    *(u32 *)result = 0xE7000000;
    *(u32 *)(result + 4) = 0;
    *(u32 *)(result + 8) = 0xFCFFD3FF;
    *(u32 *)(result + 0xC) = 0xFFA6FF7F;
    *(u32 *)(result + 0x10) = 0xFB000000;
    *(u32 *)(result + 0x14) = (((D_800E0B97 * (saved_alpha + 1)) >> 8) & 0xFF) | 0xFF802000;
    func_15096934(func_151ED430(result + 0x18, D_80091828, 0x92, 0x6C,
                                  8, 3, 1.0f, 0));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151ED09C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151ED09C.s")
void *func_1501A6CC(void *, s32, s32, s32, s32);
extern s32 D_800BE620;
extern s32 D_800BE624;
extern u8 D_800E0B96;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151ED1E0 CURRENT (3956) */
void *func_151ED1E0(void *arg0) {
    u8 *temp_a0;
    u8 *temp_a0_2;
    u8 *temp_a0_3;

    if (D_800E0B96 == 0) {
        return arg0;
    }
    *(s32 *)arg0 = 0xE7000000;
    *(s32 *)((u8 *)arg0 + 4) = 0;
    temp_a0_2 = (u8 *)arg0 + 8;
    *(s32 *)temp_a0_2 = 0xEF082C3F;
    *(s32 *)(temp_a0_2 + 4) = 0x00504340;
    temp_a0_3 = temp_a0_2 + 8;
    *(s32 *)temp_a0_3 = 0xFCFFFFFF;
    *(s32 *)(temp_a0_3 + 4) = 0xFFFEFB7D;
    temp_a0 = temp_a0_3 + 8;
    *(s32 *)temp_a0 = 0xFB000000;
    *(s32 *)(temp_a0 + 4) = D_800E0B96;
    return func_1501A6CC(temp_a0 + 8, 0, 0, D_800BE620, D_800BE624);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151ED1E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151ED1E0.s")
extern u8 D_8009DEB0[];
extern u8 D_8009DEB4[];
extern u8 D_8009DEB8[];
extern u8 D_8009DEBC[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151ED29C CURRENT (4255) */
void *func_151ED29C(u32 *arg0, u8 *arg1, s32 *arg2) {
    s32 temp_at;
    s32 temp_at_2;
    s32 temp_t2;
    s32 temp_t5;
    s32 temp_t6;
    s32 var_a2;
    s32 var_t1;
    s32 var_v0;
    u16 temp_t0;
    u16 temp_v1;
    u8 temp_a3;
    u8 temp_a3_2;
    u32 *cursor;

    temp_a3 = arg1[0xB];
    var_v0 = 1;
    var_t1 = 2;
    *arg2 = (D_8009DEB0[temp_a3] +
             (*(u16 *)(arg1 + 6) * *(u16 *)(arg1 + 8))) >>
            D_8009DEB4[temp_a3];
    temp_t0 = *(u16 *)(arg1 + 6);
    if (temp_t0 >= 3) {
        do {
            temp_t5 = var_t1 * 2;
            temp_at = temp_t5 < temp_t0;
            var_t1 = temp_t5;
            var_v0 += 1;
        } while (temp_at != 0);
        var_t1 = 2;
    }
    temp_v1 = *(u16 *)(arg1 + 8);
    var_a2 = 1;
    cursor = arg0;
    if (temp_v1 >= 3) {
        do {
            temp_t6 = var_t1 * 2;
            temp_at_2 = temp_t6 < temp_v1;
            var_t1 = temp_t6;
            var_a2 += 1;
        } while (temp_at_2 != 0);
    }
    cursor[0] = 0xE7000000;
    cursor[1] = 0;
    cursor += 2;
    temp_t2 = ((arg1[0xA] & 7) << 21) | 0xF5000000;
    cursor[0] = ((D_8009DEBC[arg1[0xB]] & 3) << 19) | temp_t2;
    cursor[1] = 0x07000000;
    cursor += 2;
    temp_a3_2 = arg1[0xB];
    cursor[0] = (((((D_8009DEB8[temp_a3_2] * *(u16 *)(arg1 + 6)) + 7) >> 3)
                & 0x1FF) << 9) | temp_t2 | ((temp_a3_2 & 3) << 19);
    cursor[1] = ((var_a2 & 0xF) << 14) | 0x80000 | 0x200 | ((var_v0 & 0xF) * 0x10);
    cursor += 2;
    cursor[0] = 0xF2000000;
    cursor[1] = ((((*(u16 *)(arg1 + 6) - 1) * 4) & 0xFFF) << 12) |
              (((*(u16 *)(arg1 + 8) - 1) * 4) & 0xFFF);
    cursor += 2;
    return cursor;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151ED29C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151ED29C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151ED430.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151ED90C.s")
void func_100043B4(void *, s32);
void func_1503F7B8(s32);

void func_151EDB58(void *arg0) {
    s32 var_s0;
    void *var_s1;

    if (arg0 != 0) {
        func_1503F7B8(*(s32 *)((u8 *)arg0 + 0x24));
        func_100043B4(arg0, 4);
        var_s0 = 0;
        var_s1 = arg0;
        if ((s32) *(u8 *)((u8 *)arg0 + 0x14) > 0) {
            do {
                func_100043B4(*(void **)((u8 *)var_s1 + 4), 4);
                var_s0 += 1;
                var_s1 = (void *)((u8 *)var_s1 + 4);
            } while (var_s0 < (s32) *(u8 *)((u8 *)arg0 + 0x14));
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EDBDC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EDF4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EE184.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EEBE8.s")
extern s32 D_800E9D00;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151EEFF0 CURRENT (505) */
void func_151EEFF0(void) {
    volatile s32 zero = 0;

    D_800E9D00 = zero;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151EEFF0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EEFF0.s")
