#include "types.h"

/*
 * Reviewed source unit: src/game/game_215960.c
 * Boundary evidence: docs/evidence/game_raw_connected_controller_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151E84B0
 * - func_151E8620
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
 * - func_151EDB58
 * - func_151EDBDC
 * - func_151EDF4C
 * - func_151EE184
 * - func_151EEBE8
 * - func_151EEFF0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151E84B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151E8620.s")
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

typedef struct {
    u8 pad0[0x1D0];
    s32 field_1D0;
} Game215960State;

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
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151ED09C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151ED1E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151ED29C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151ED430.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151ED90C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_215960/func_151EDB58.s")
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
