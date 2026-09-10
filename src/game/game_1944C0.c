#include "types.h"

/*
 * Reviewed source unit: src/game/game_1944C0.c
 * Boundary evidence: docs/evidence/game_state_callback_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15167010
 * - func_1516706C
 * - func_151670C0
 * - func_151671E8
 * - func_15167310
 * - func_151674F8
 * - func_15167A68
 * - func_15167AD8
 * - func_15167B44
 * - func_15167C58
 * - func_15167D84
 * - func_15167E0C
 * - func_15168118
 * - func_1516865C
 * - func_15168800
 * - func_15168870
 * - func_15168A4C
 * - func_15168A9C
 * - func_15168B10
 * - func_15168B44
 * - func_15168BAC
 * - func_15168BE4
 * - func_15168C4C
 * - func_15168E54
 * - func_15168F08
 * - func_15169040
 * - func_15169070
 * - func_15169260
 * - func_1516944C
 * - func_151695F0
 * - func_1516962C
 * - func_1516968C
 * - func_151696DC
 * - func_1516972C
 * - func_1516979C
 * - func_15169824
 * - func_15169850
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15168B10(s32 arg0, s32 arg1);

#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15167010.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_1516706C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_151670C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_151671E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15167310.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_151674F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15167A68.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15167AD8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15167B44.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15167C58.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15167D84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15167E0C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15168118.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_1516865C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15168800.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15168870.s")
void func_15168A2C(s32 arg0) {
    func_15168B10(arg0, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15168A4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15168A9C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15168B10.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15168B44 CURRENT (375) */
void func_15168B44(void *arg0) {
    s32 temp_t2;
    s32 temp_t6;
    s32 temp_t9;
    s32 temp_v1;
    u8 temp_a2;

    temp_v1 = *(s32 *)((u8 *)arg0 + 0x14);
    temp_t6 = temp_v1 & 0xFFFF;
    if (temp_t6 != 0) {
        temp_t9 = temp_v1 & 0xFFFF0000;
        *(s32 *)((u8 *)arg0 + 0x14) = temp_t9;
        *(s16 *)((u8 *)arg0 + 0x38) = 0x1E;
        *(s32 *)((u8 *)arg0 + 0x14) = (s32) (temp_t9 | ((temp_t6 - 1) & 0xFFFF));
        return;
    }
    temp_a2 = *(u8 *)((u8 *)arg0 + 0x3F);
    temp_t2 = (temp_v1 >> 0x10) & 0xFFFF;
    if (temp_t2 < (s32) temp_a2) {
        *(u8 *)((u8 *)arg0 + 0x3F) = (u8) (temp_a2 - temp_t2);
        *(s16 *)((u8 *)arg0 + 0x38) = 0x1E;
        return;
    }
    *(s16 *)((u8 *)arg0 + 0x38) = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15168B44 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15168B44.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15168BAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15168BE4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15168C4C.s")
void func_15168E34(s32 *arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = *arg0;
    if (!(temp_v0 & 0x0F000000)) {
        *arg0 = temp_v0 + arg1;
    }
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15168E54 CURRENT (2110) */
void func_15168E54(s8 *arg0, s32 arg1) {
    s32 var_s0;
    s8 *var_v1;
    s8 var_v0;

    var_s0 = 0;
    var_v1 = arg0;
    if (*arg0 != -0x21) {
        var_v0 = *arg0;
        do {
            if ((var_v0 == 1) || ((var_v0 == -0x24) && (*(u8 *)((u8 *)var_v1 + 3) == 0xE))) {
                func_15168E34(var_v1 + 4, arg1);
            }
            var_s0 += 1;
            var_v1 = (var_s0 * 8) + arg0;
            var_v0 = *var_v1;
        } while (var_v0 != -0x21);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15168E54 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15168E54.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15168F08 CURRENT (1645) */
void func_15168F08(s8 *arg0, s32 arg1) {
    s32 temp_t9;
    s32 var_v0;
    s8 *var_v1;
    s8 var_a1;

    var_v0 = 0;
    var_v1 = arg0;
    if (*arg0 != -0x21) {
        var_a1 = *arg0;
        do {
            var_v0 += 1;
            if ((var_a1 == 1) || ((var_a1 == -0x24) && (*(u8 *)((u8 *)var_v1 + 3) == 0xE))) {
                temp_t9 = *(s32 *)((u8 *)var_v1 + 4) & 0xFFFFFF;
                *(s32 *)((u8 *)var_v1 + 4) = temp_t9;
                *(s32 *)((u8 *)var_v1 + 4) = (s32) (temp_t9 + arg1);
            }
            var_v1 = (var_v0 * 8) + arg0;
            var_a1 = *var_v1;
        } while (var_a1 != -0x21);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15168F08 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15168F08.s")
void func_15168F84(s32 arg0, s32 *arg1, s32 *arg2) {
    if (arg0 == 0) {
        *arg1 = 1;
        *arg2 = 0x41;
        return;
    }
    if (arg0 == 1) {
        *arg1 = 0x42;
        *arg2 = 0x4F;
        return;
    }
    if (arg0 == 2) {
        *arg1 = 0x50;
        *arg2 = 0x58;
        return;
    }
    if (arg0 == 3) {
        *arg1 = 0x59;
        *arg2 = 0x5C;
        return;
    }
    if (arg0 == 5) {
        *arg1 = 0x61;
        *arg2 = 0x63;
        return;
    }
    if (arg0 == 6) {
        *arg1 = 0x64;
        *arg2 = 0x65;
        return;
    }
    *arg1 = 0x5D;
    *arg2 = 0x60;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15169040.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15169070.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15169260.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_1516944C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_151695F0.s")
/* Call context: func_1516944C: unique active project prototype */
void func_1516944C(s32, s8 *, u8, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516962C CURRENT (1300) */
void func_1516962C(s32 arg0, void *arg1, s32 arg2) {
    u8 sp1C;
    void *sp18;

    sp18 = arg1;
    sp1C = *(u8 *)((u8 *)arg1 + 0x3B);
    func_1516944C(arg0, (s8 *) &sp18, arg2 & 0xFF, (u8) arg1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516962C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_1516962C.s")
extern s8 D_800D2DAB;

s32 func_15169668(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_800D2DAB = 1;
    return arg0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_1516968C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_151696DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_1516972C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_1516979C.s")
void func_15169804(s32 arg0) {
    func_15168B10(arg0, 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15169824.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15169850.s")
