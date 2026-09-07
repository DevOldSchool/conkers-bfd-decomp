#include "types.h"

/*
 * Reviewed source unit: src/game/effects/effects_sight.c
 * Boundary evidence: docs/evidence/game_beta_sight.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151C71A0
 * - func_151C756C
 * - func_151C7E98
 * - func_151C82D0
 * - func_151C8674
 * - func_151C86AC
 * - func_151C87AC
 * - func_151C87E0
 * - func_151C899C
 * - func_151C8FCC
 * - func_151C9198
 * - func_151C94D4
 * - func_151C95D8
 * - func_151C96DC
 * - func_151C970C
 * - func_151C9740
 * - func_151C9AC0
 * - func_151C9B30
 * - func_151C9B64
 * - func_151C9BA0
 * - func_151C9DE8
 * - func_151C9ED4
 * - func_151C9F38
 * - func_151CA6A0
 * - func_151CAACC
 * - func_151CAB78
 * - func_151CAD28
 * - func_151CB110
 * - func_151CB49C
 * - func_151CB510
 * - func_151CB5FC
 * - func_151CB918
 * - func_151CB970
 * - func_151CBB6C
 * - func_151CBBE0
 * - func_151CBC60
 * - func_151CC1D4
 * - func_151CC2BC
 * - func_151CC524
 * - func_151CC77C
 * - func_151CC840
 * - func_151CCD1C
 * - func_151CCE94
 * - func_151CCF08
 * - func_151CD224
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C71A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C756C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C7E98.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C82D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C8674.s")
s32 func_151C87E0(s32, void *, s32, void *);
void func_151C899C();

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C86AC CURRENT (1931) */
void func_151C86AC(void *arg0, void *arg1, s32 arg2) {
    s32 temp_t6;
    u8 temp_v1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_t6 = arg2 & 0xFF;
    switch (temp_t6) {
    case 0x20:
        temp_v0 = (u8 *)arg0 + 0x110;
        if ((temp_v0[0x86] & 0x10) &&
            (*(s32 *)(temp_v0 + 0x28) == *(s32 *)((u8 *)arg1 + 4)) &&
            (func_151C87E0(*(s32 *)arg1, arg0, temp_t6, arg1) != 0)) {
            func_151C899C(*(s32 *)arg1, arg0);
        }
        return;
    case 0x3A:
        temp_v0_2 = (u8 *)arg0 + 0x110;
        if (*(s32 *)((u8 *)arg0 + 0x138) == *(s32 *)arg1) {
            temp_v1 = *((u8 *)arg1 + 4);
            switch (temp_v1) {
            case 0:
                temp_v0_2[0x86] |= 2;
                return;
            case 1:
                temp_v0_2[0x86] &= 0xFFFD;
                return;
            case 2:
                func_151C899C(0, arg0);
                break;
            }
        }
        break;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C86AC */
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C86AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C87AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C87E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C899C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C8FCC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C9198.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C94D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C95D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C96DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C970C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C9740.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C9AC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C9B30.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C9B64.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C9BA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C9DE8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C9ED4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151C9F38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CA6A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CAACC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CAB78.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CAD28.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CB110.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CB49C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CB510.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CB5FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CB918.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CB970.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CBB6C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CBBE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CBC60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CC1D4.s")
void func_151CC290(s32 arg0) {
    s32 sp1C;

    sp1C = arg0;
    func_1515572C(&sp1C, 0x46, arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CC2BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CC524.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CC77C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CC840.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CCD1C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CCE94.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CCF08.s")
#pragma GLOBAL_ASM("asm/nonmatchings/effects/effects_sight/func_151CD224.s")
