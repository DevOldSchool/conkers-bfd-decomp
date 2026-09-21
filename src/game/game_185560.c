#include "types.h"

/*
 * Reviewed source unit: src/game/game_185560.c
 * Boundary evidence: docs/evidence/game_raw_descriptor_attachment_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151580B0
 * - func_15158224
 * - func_151582C8
 * - func_1515858C
 * - func_15158684
 * - func_15158920
 * - func_15158A20
 * - func_15158B3C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15158A20(s32 arg0);
void func_15169804(s32 arg0);
void func_15169824(s32 arg0);
void *func_151580B0(void *arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4, u8 arg5, s32 arg6);

void *func_10022EC0(void *, const void *, u32);
void *func_1515D440(void);
s32 func_1515D480(s32);
void *func_15167A68(s32, s32, s32, s32, u8, u8);
extern s32 D_80082FA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151580B0 CURRENT (1168) */
void *func_151580B0(void *arg0, s32 arg1, s32 arg2, u8 arg3,
                    s32 arg4, u8 arg5, s32 arg6) {
    s32 var_a0;
    s32 var_s1;
    s32 var_s1_2;
    void *temp_v0;
    volatile s32 *var_s0;
    void *var_s0_2;

    if (arg3) {
        var_a0 = 0x55;
    } else {
        var_a0 = 0x37;
    }
    temp_v0 = func_15167A68(var_a0, arg6, arg4 + 0xF8, 1, arg5, 1);
    if (temp_v0 == 0) {
        return 0;
    }
    func_10022EC0((u8 *)temp_v0 + 0x10, arg0, 0x44);
    *(s32 *)((u8 *)temp_v0 + 0xD8) = arg1;
    *(s32 *)((u8 *)temp_v0 + 0xF4) = arg2;
    *(s8 *)((u8 *)temp_v0 + 0xDC) = 0;
    var_s1 = 0;
    var_s0 = (volatile s32 *)((u8 *)temp_v0 + 0xDC);
    do {
        var_s1++;
        var_s0++;
        *var_s0 = 0;
    } while (var_s1 < 4);
    *(void **)((u8 *)temp_v0 + 0xF0) = 0;
    if (arg1 != 0) {
        var_s1_2 = 0;
        var_s0_2 = temp_v0;
        if (D_80082FA0 >= 0) {
            do {
                *(s32 *)((u8 *)var_s0_2 + 0xE0) = func_1515D480(arg1);
                var_s1_2++;
                var_s0_2 = (u8 *)var_s0_2 + 4;
            } while (D_80082FA0 >= var_s1_2);
        }
        *(void **)((u8 *)temp_v0 + 0xF0) = func_1515D440();
    }
    return temp_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151580B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_151580B0.s")
void func_151581D8(void *arg0, u8 arg1, s32 arg2, u8 arg3, s32 arg4) {
    func_151580B0(arg0, 0, 0, arg1, arg2, arg3, arg4);
}
typedef s32 (*Game185560Callback)(void *);

extern Game185560Callback D_8008AE00[];
extern s32 D_800BE9E4;
void func_1516972C(void *arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15158224 CURRENT (878) */
void func_15158224(void *arg0) {
    struct {
        s8 value;
        u8 pad[4];
    } local;
    s8 callback_index;
    u8 callback_pending;

    callback_pending = 0;
    if (*(u8 *)((u8 *)arg0 + 0x10) & 1) {
        *(s16 *)((u8 *)arg0 + 0x14) = (s16) (*(s16 *)((u8 *)arg0 + 0x14) - D_800BE9E4);
        if (*(s16 *)((u8 *)arg0 + 0x14) < 0) {
            callback_pending = 1;
        }
    }
    if (callback_pending == 0) {
        callback_index = *(s8 *)((u8 *)arg0 + 0x12);
        if (callback_index != -1) {
            local.value = callback_pending;
            if (D_8008AE00[(s32) callback_index](arg0) != 0) {
                callback_pending = local.value;
            } else {
                callback_pending = 1;
            }
        }
    }
    if (callback_pending != 0) {
        func_1516972C(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15158224 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_15158224.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_151582C8.s")
typedef struct Game185560TransformArgs {
    u8 pad0[0x48];
    f32 field48;
    f32 field4C;
    f32 field50;
    u8 pad54[0xA4];
    f32 fieldF8;
    s32 fieldFC;
    f32 field100;
    f32 field104;
} Game185560TransformArgs;

void func_150A7790(void *, s32);
void func_150A8050(void *, f32, s32, f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515858C CURRENT (583) */
s32 func_1515858C(s32 arg0, Game185560TransformArgs *arg1) {
    f32 matrix[15];
    void *temp_v0;

    func_150A8050(matrix, arg1->fieldF8, arg1->fieldFC, arg1->field100);
    temp_v0 = (u8 *)arg1 + 0xF8;
    matrix[12] = arg1->field48;
    matrix[13] = arg1->field4C;
    matrix[14] = arg1->field50;
    matrix[0] *= *(f32 *)((u8 *)temp_v0 + 0xC);
    matrix[1] *= *(f32 *)((u8 *)temp_v0 + 0xC);
    matrix[2] *= *(f32 *)((u8 *)temp_v0 + 0xC);
    matrix[4] *= *(f32 *)((u8 *)temp_v0 + 0xC);
    matrix[5] *= *(f32 *)((u8 *)temp_v0 + 0xC);
    matrix[6] *= *(f32 *)((u8 *)temp_v0 + 0xC);
    matrix[8] *= *(f32 *)((u8 *)temp_v0 + 0xC);
    matrix[9] *= *(f32 *)((u8 *)temp_v0 + 0xC);
    matrix[10] *= *(f32 *)((u8 *)temp_v0 + 0xC);
    func_150A7790(matrix, arg0);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515858C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_1515858C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_15158684.s")
typedef struct {
    f32 values[16];
} Game185560Matrix;

extern Game185560Matrix D_8008AE18;
extern f32 D_800A6070;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15158920 CURRENT (89) */
s32 func_15158920(s32 arg0, Game185560TransformArgs *arg1) {
    register f32 scale;
    Game185560Matrix matrix;

    matrix = D_8008AE18;
    scale = arg1->fieldF8 * D_800A6070;
    matrix.values[12] = arg1->field48;
    matrix.values[13] = arg1->field4C;
    matrix.values[14] = arg1->field50;
    matrix.values[0] *= scale;
    matrix.values[1] *= scale;
    matrix.values[2] *= scale;
    matrix.values[4] *= scale;
    matrix.values[5] *= scale;
    matrix.values[6] *= scale;
    matrix.values[8] *= scale;
    matrix.values[9] *= scale;
    matrix.values[10] *= scale;
    func_150A7790(&matrix, arg0);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15158920 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_15158920.s")
void func_100043B4(s32, s32);
extern s32 D_80082FA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15158A20 CURRENT (890) */
void func_15158A20(s32 arg0) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s0;
    s32 var_s1;

    var_s1 = 0;
    var_s0 = arg0;
    if (D_80082FA0 >= 0) {
        do {
            temp_v0 = *(s32 *)((u8 *)var_s0 + 0xE0);
            if (temp_v0 != 0) {
                func_100043B4(temp_v0, 4);
            }
            var_s1 += 1;
            var_s0 += 4;
        } while (D_80082FA0 >= var_s1);
    }
    temp_v0_2 = *(s32 *)((u8 *)arg0 + 0xF0);
    if (temp_v0_2 != 0) {
        func_100043B4(temp_v0_2, 4);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15158A20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_15158A20.s")
void func_15158AA4(s32 arg0) {
    func_15158A20(arg0);
    func_15169804(arg0);
}
void func_15158AD0(s32 arg0) {
    func_15158A20(arg0);
    func_15169824(arg0);
}
s32 func_15158AFC(void *arg0) {
    s16 temp_v0;
    s32 temp_lo;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x14);
    if (temp_v0 < *(s16 *)((u8 *)arg0 + 0xF8)) {
        temp_lo = temp_v0;
        temp_lo *= *(s32 *)((u8 *)arg0 + 0xFC);
        if (temp_lo < (s32) *(u8 *)((u8 *)arg0 + 0x3B)) {
            *(u8 *)((u8 *)arg0 + 0x3B) = (u8) temp_lo;
        }
    }
    return 1;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15158B3C CURRENT (440) */
void func_15158B3C(void *arg0, void *arg1, s32 arg2) {
    s32 temp_t6;
    s32 temp_v0;
    s32 temp_v1;

    temp_t6 = arg2 & 0xFF;
    if (temp_t6 == 0x2D) {
        temp_v0 = *(s32 *)((u8 *)arg1 + 0);
        temp_v1 = *(s32 *)((u8 *)arg0 + 0x40);
        if (temp_v0 == temp_v1) {
            *(s32 *)((u8 *)arg0 + 0x40) = (s32) *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)arg0 + 0x44) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_v1) {
            *(s32 *)((u8 *)arg0 + 0x40) = temp_v0;
            *(u8 *)((u8 *)arg0 + 0x44) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    } else if ((temp_t6 == 0) && ((*(s32 *)((u8 *)arg1 + 0) == *(s32 *)((u8 *)arg0 + 0x40)) || (*(u8 *)((u8 *)arg0 + 0x44) == (u8) *(s32 *)((u8 *)arg1 + 4)))) {
        *(s32 *)((u8 *)arg0 + 0x40) = 0;
        *(u8 *)((u8 *)arg0 + 0x44) = 0U;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15158B3C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_15158B3C.s")
