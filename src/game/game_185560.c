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
 * - func_15158AFC
 * - func_15158B3C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15158A20(s32 arg0);
void func_15169804(s32 arg0);
void func_15169824(s32 arg0);
void func_151580B0(void *arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4, u8 arg5, s32 arg6);

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
#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_1515858C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_15158684.s")
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15158AFC CURRENT (10) */
s32 func_15158AFC(void *arg0) {
    s16 temp_v0;
    s32 temp_lo;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x14);
    if (temp_v0 < *(s16 *)((u8 *)arg0 + 0xF8)) {
        temp_lo = temp_v0 * *(s32 *)((u8 *)arg0 + 0xFC);
        if (temp_lo < (s32) *(u8 *)((u8 *)arg0 + 0x3B)) {
            *(u8 *)((u8 *)arg0 + 0x3B) = (u8) temp_lo;
        }
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15158AFC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_15158AFC.s")
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
