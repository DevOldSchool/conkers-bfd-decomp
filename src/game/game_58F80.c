#include "types.h"

/*
 * Reviewed source unit: src/game/game_58F80.c
 * Boundary evidence: docs/evidence/game_raw_core_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1502BAD0
 * - func_1502BD84
 * - func_1502BEE4
 * - func_1502C1A4
 * - func_1502C380
 * - func_1502C3BC
 * - func_1502C408
 * - func_1502C608
 * - func_1502C6E8
 * - func_1502C974
 * - func_1502CC34
 * - func_1502CCFC
 * - func_1502D54C
 * - func_1502D630
 * - func_1502D824
 * - func_1502DB20
 * - func_1502DB84
 * - func_1502DF38
 * - func_1502E474
 * - func_1502E4C4
 * - func_1502EA0C
 * - func_1502EA98
 * - func_1502EAFC
 * - func_1502EC34
 * - func_1502EE8C
 * - func_1502EEF4
 * - func_1502F01C
 * - func_1502F264
 * - func_1502F3C8
 * - func_1502F490
 * - func_1502F948
 * - func_1502F9FC
 * - func_1502FBE8
 * - func_1502FD70
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502BAD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502BD84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502BEE4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502C1A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502C380.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502C3BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502C408.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502C608.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502C6E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502C974.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502CC34.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502CCFC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502D54C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502D630.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502D824.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502DB20.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502DB84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502DF38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502E474.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502E4C4.s")
void func_1502E9FC(s32 arg0, s32 arg1) {
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502EA0C CURRENT (860) */
void func_1502EA0C(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    *(s8 *)((u8 *)arg0 + 0xA4) = 4;
    *(s8 *)((u8 *)arg0 + 0xA5) = 0;
    *(s8 *)((u8 *)arg0 + 0xA6) = (s8) arg5;
    *(s8 *)((u8 *)arg0 + 0xA7) = 0xFF;
    *(s32 *)((u8 *)arg0 + 0xA0) = (s32) ((arg4 << 0x18) | (arg1 << 0x10) | (arg2 << 8) | arg3);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502EA0C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502EA0C.s")
void func_1502EA50(u8 *arg0) {
    arg0[0xA4] = 5;
}
void func_1502EA60(u8 *arg0, s32 arg1) {
    arg0[0xA4] = 2;
    arg0[0xA5] = 0xFF;
    arg0[0xA6] = arg1;
}
void func_1502EA7C(u8 *arg0, s32 arg1) {
    arg0[0xA4] = 3;
    arg0[0xA5] = 0xFF;
    arg0[0xA6] = arg1;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1502EA98 CURRENT (5) */
void func_1502EA98(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    u8 temp_v0;

    temp_v0 = *(u8 *)((u8 *)arg0 + 0xA4);
    if ((temp_v0 != 6) && (temp_v0 != 7)) {
        if (arg5 != 0) {
            *(s8 *)((u8 *)arg0 + 0xA5) = 0xFF;
        } else {
            *(s8 *)((u8 *)arg0 + 0xA5) = 0;
        }
        *(s32 *)((u8 *)arg0 + 0xA0) = (s32) ((arg4 << 0x18) | (arg1 << 0x10) | (arg2 << 8) | arg3);
        *(s8 *)((u8 *)arg0 + 0xA6) = (s8) arg6;
    }
    *(u8 *)((u8 *)arg0 + 0xA4) = 6U;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1502EA98 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502EA98.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502EAFC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502EC34.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502EE8C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502EEF4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502F01C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502F264.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502F3C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502F490.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502F948.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502F9FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502FBE8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502FD70.s")
