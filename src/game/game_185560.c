#include "types.h"

/*
 * Reviewed source unit: src/game/game_185560.c
 * Boundary evidence: docs/evidence/game_raw_descriptor_attachment_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151580B0
 * - func_151581D8
 * - func_15158224
 * - func_151582C8
 * - func_1515858C
 * - func_15158684
 * - func_15158920
 * - func_15158A20
 * - func_15158AD0
 * - func_15158AFC
 * - func_15158B3C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_151580B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_151581D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_15158224.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_151582C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_1515858C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_15158684.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_15158920.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_15158A20.s")
void func_15158AA4(s32 arg0) {
    func_15158A20(arg0);
    func_15169804(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_15158AD0.s")
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
