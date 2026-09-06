#include "types.h"

/*
 * Reviewed source unit: src/game/game_1BDC20.c
 * Boundary evidence: docs/evidence/game_raw_owner_particle_lifecycle.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15190770
 * - func_1519086C
 * - func_15190898
 * - func_15190F9C
 * - func_1519108C
 * - func_15191400
 * - func_15191520
 * - func_1519187C
 * - func_151918BC
 * - func_15191980
 * - func_15191A84
 * - func_15191B8C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDC20/func_15190770.s")
void func_15190840(s32 arg0) {
    func_15191400(arg0);
    func_15169804(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDC20/func_1519086C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDC20/func_15190898.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDC20/func_15190F9C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDC20/func_1519108C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDC20/func_15191400.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDC20/func_15191520.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519187C CURRENT (10) */
s32 func_1519187C(void *arg0) {
    s16 temp_v0;
    s32 temp_lo;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    if (temp_v0 < *(s16 *)((u8 *)arg0 + 0x124)) {
        temp_lo = temp_v0 * *(s16 *)((u8 *)arg0 + 0x126);
        if (temp_lo < (s32) *(u8 *)((u8 *)arg0 + 0x5C)) {
            *(u8 *)((u8 *)arg0 + 0x5C) = (u8) temp_lo;
        }
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519187C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDC20/func_1519187C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDC20/func_151918BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDC20/func_15191980.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDC20/func_15191A84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDC20/func_15191B8C.s")
