#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D9F10.c
 * Boundary evidence: docs/evidence/game_raw_owner_point_lifecycle.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151ACA60
 * - func_151ACB38
 * - func_151ACB60
 * - func_151ACBD4
 * - func_151AD174
 * - func_151AD92C
 * - func_151AE06C
 * - func_151AE0E4
 * - func_151AE264
 * - func_151AE2BC
 * - func_151AE3A8
 * - func_151AE590
 * - func_151AE640
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151ACA60.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151ACB38 CURRENT (805) */
s32 func_151ACB38(void *arg0, s8 *arg1) {
    s32 var_v1;

    var_v1 = 0;
    if (*(u8 *)((u8 *)arg0 + 0x3B) == 1) {
        *arg1 = 1;
        var_v1 = 1;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151ACB38 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151ACB38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151ACB60.s")
void func_151ACB94(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x1C, arg0 + 0x20, arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151ACBD4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151AD174.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151AD92C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151AE06C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151AE0E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151AE264.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151AE2BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151AE3A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151AE590.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AE640 CURRENT (590) */
void func_151AE640(void *arg0, void *arg1, s32 arg2) {
    s32 temp_t6;
    s32 temp_v0;
    s32 temp_v1;

    temp_t6 = arg2 & 0xFF;
    if (temp_t6 == 0) {
        if (*(s32 *)((u8 *)arg1 + 0) == *(s32 *)((u8 *)arg0 + 0x44)) {
            *(s32 *)((u8 *)arg0 + 0x44) = 0;
        }
    } else if (temp_t6 == 0x2D) {
        temp_v0 = *(s32 *)((u8 *)arg1 + 0);
        temp_v1 = *(s32 *)((u8 *)arg0 + 0x44);
        if (temp_v0 == temp_v1) {
            *(s32 *)((u8 *)arg0 + 0x44) = (s32) *(s32 *)((u8 *)arg1 + 4);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_v1) {
            *(s32 *)((u8 *)arg0 + 0x44) = temp_v0;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AE640 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D9F10/func_151AE640.s")
