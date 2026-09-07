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
 * - func_1515A920
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15159230 CURRENT (1245) */
s32 func_15159230(void *arg0, void *arg1, s32 arg2) {
    s32 temp_t6;
    s32 var_v1;

    temp_t6 = arg2 & 0xFF;
    if ((*(f32 *)((u8 *)arg1 + 0) != *(f32 *)((u8 *)arg0 + 0x14)) || (*(f32 *)((u8 *)arg1 + 4) != *(f32 *)((u8 *)arg0 + 0x18)) || (var_v1 = 0, (*(f32 *)((u8 *)arg1 + 8) != *(f32 *)((u8 *)arg0 + 0x1C)))) {
        if ((temp_t6 == 1) || (temp_t6 == 2)) {
            var_v1 = 2;
        } else {
            var_v1 = 1;
        }
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_1515942C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_15159594.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_151596BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_15159890.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_15159BB0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_15159C08.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_1515A11C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_1515A238.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_1515A60C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_1515A78C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_1515A920.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_1515A974.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_1515AA84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_1515AB88.s")
