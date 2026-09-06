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
#pragma GLOBAL_ASM("asm/nonmatchings/game_1865D0/func_151592B8.s")
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
