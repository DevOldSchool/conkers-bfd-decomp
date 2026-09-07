#include "types.h"

/*
 * Reviewed source unit: src/game/game_FD1D0.c
 * Boundary evidence: docs/evidence/game_raw_text_view_descriptor_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150CFD20
 * - func_150CFD5C
 * - func_150CFDB8
 * - func_150CFE3C
 * - func_150CFE98
 * - func_150CFF10
 * - func_150D0034
 * - func_150D00C0
 * - func_150D0134
 * - func_150D01A0
 * - func_150D02B4
 * - func_150D032C
 * - func_150D04C4
 * - func_150D0534
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CFD20 CURRENT (155) */
u8 *func_150CFD20(u8 *arg0) {
    u8 *var_a0;
    u8 temp_v0;
    u8 temp_v0_2;

    var_a0 = arg0;
    temp_v0 = *var_a0;
    if ((temp_v0 != 0xBD) && (temp_v0 != 0)) {
loop_2:
        temp_v0_2 = *(u8 *)((u8 *)var_a0 + 1);
        var_a0 += 1;
        if (temp_v0_2 != 0xBD) {
            if (temp_v0_2 != 0) {
                goto loop_2;
            }
        }
    }
    return var_a0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CFD20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150CFD20.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CFD5C CURRENT (145) */
u8 *func_150CFD5C(u8 *arg0) {
    u8 *var_a0;
    u8 temp_t7;

    var_a0 = arg0;
    if (*var_a0 != 0) {
        do {
            temp_t7 = *(u8 *)((u8 *)var_a0 + 1);
            var_a0 += 1;
        } while (temp_t7 != 0);
    }
    return var_a0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CFD5C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150CFD5C.s")
s32 func_150CFD84(s32 arg0, s32 *arg1) {
    s32 temp_v0;

    temp_v0 = func_150CFD20(arg0);
    *arg1 = temp_v0;
    return temp_v0 - arg0;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CFDB8 CURRENT (1359) */
s32 func_150CFDB8(u8 *arg0) {
    s32 temp_v0_3;
    s32 var_s0;
    u32 temp_v0;
    s32 sp2C;
    u8 *temp_v0_2;
    u8 *var_a0;

    var_s0 = 0;
    temp_v0 = func_150CFD5C(arg0);
    var_a0 = arg0;
    if ((u32) var_a0 < temp_v0) {
        do {
            temp_v0_3 = func_150CFD84((s32) var_a0, &sp2C);
            if (var_s0 < temp_v0_3) {
                var_s0 = temp_v0_3;
            }
            temp_v0_2 = sp2C + 1;
            var_a0 = temp_v0_2;
        } while ((u32) temp_v0_2 < temp_v0);
    }
    return var_s0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CFDB8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150CFDB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150CFE3C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150CFE98.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150CFF10.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150D0034.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150D00C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150D0134.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150D01A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150D02B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150D032C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150D04C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150D0534.s")
