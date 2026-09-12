#include "types.h"

/*
 * Reviewed source unit: src/game/game_CC4A0.c
 * Boundary evidence: docs/evidence/game_raw_dispatch_position_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1509EFF0
 * - func_1509F284
 * - func_1509F354
 * - func_1509F47C
 * - func_1509F4E8
 * - func_1509F5A8
 * - func_1509F5F4
 * - func_1509F660
 * - func_1509F6B0
 * - func_1509F6E8
 * - func_1509F77C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_CC4A0/func_1509EFF0.s")
s32 func_1509F248(s32 arg0, s32 *arg1) {
    if (arg0 != 0) {
        func_100111C8(((u32) (*arg1 & 0xFFFF0000) >> 0x10) & 0xFFFF);
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_CC4A0/func_1509F284.s")
s32 func_1509F33C(s32 arg0, s32 arg1, s32 arg2) {
    return 0;
}
s32 func_10010344(s32, s32, u32, s16, s32);         /* extern */
s32 func_10010894(s32);                             /* extern */
s32 func_1505EEF4(s32);                             /* extern */
u32 func_150ADA20();                                /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509F354 CURRENT (1773) */
u32 func_1509F354(s32 arg0, s32 arg1, u32 arg2, u32 arg3, s32 arg4, s16 arg5, s32 arg6) {
    s32 sp2C;
    s32 temp_t0;
    s32 temp_a0;
    s32 temp_v0;
    u32 temp_hi;
    u32 var_s1;

    var_s1 = arg2;
    temp_v0 = func_1505EEF4(arg4);
    temp_a0 = temp_v0;
    if (arg3 >= 0x8000U) {
        arg3 = 0x7FFFU;
    }
    if (temp_v0 == 0) {

    } else {
        sp2C = temp_a0;
        if (func_10010894(temp_a0) == 0) {
            if (var_s1 == 0) {
                var_s1 = -1U >> -(((arg1 - arg0) + 1) & 0xFF);
            }
            do {
                temp_hi = func_150ADA20() % (u32) (((arg1 - arg0) + 1) & 0xFF);
                temp_t0 = temp_hi & 0xFF;
            } while (!((1 << (temp_hi & 0xFF)) & var_s1));
            if (func_10010344((temp_t0 + arg0) & 0xFFFF, sp2C, arg3, arg5, arg6) != 0) {
                var_s1 ^= 1 << temp_t0;
            }
        }
    }
    return var_s1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509F354 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CC4A0/func_1509F354.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CC4A0/func_1509F47C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CC4A0/func_1509F4E8.s")
/* Call context: func_10010F30: unique active project prototype */
void func_10010F30(s32, s32, s32, s32, s32);
s32 func_1000F568(s32, s32);                        /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509F5A8 CURRENT (40) */
void func_1509F5A8(s32 arg0, s32 arg1, u16 arg2) {
    func_10010F30(func_1000F568(((arg1 - arg0) + 1) & 0xFF, arg1), (s32) arg2, 0x40, 0, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509F5A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CC4A0/func_1509F5A8.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509F5F4 CURRENT (60) */
void func_1509F5F4(u16 arg0, u32 arg1, s32 arg2, s16 arg3, s32 arg4, s32 arg5) {
    s32 var_a1;
    s32 sp24;
    s32 temp_v0;

    temp_v0 = func_1505EEF4(arg2);
    var_a1 = temp_v0;
    if ((temp_v0 != 0) && ((arg5 != 0) || (sp24 = temp_v0, var_a1 = sp24, (func_10010894(temp_v0) == 0)))) {
        func_10010344((s32) arg0, var_a1, arg1, arg3, arg4);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509F5F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CC4A0/func_1509F5F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CC4A0/func_1509F660.s")
/* Call context: func_10010F30: unique active project prototype */
void func_10010F30(s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509F6B0 CURRENT (120) */
void func_1509F6B0(s32 arg0, u16 arg1, s16 arg2, u8 arg3) {
    func_10010F30(arg0, (s32) arg1, (s32) arg3, (s32) arg2, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509F6B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CC4A0/func_1509F6B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CC4A0/func_1509F6E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CC4A0/func_1509F77C.s")
