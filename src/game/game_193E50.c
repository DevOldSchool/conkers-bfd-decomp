#include "types.h"

/*
 * Reviewed source unit: src/game/game_193E50.c
 * Boundary evidence: docs/evidence/game_raw_display_transition_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151669A0
 * - func_15166B50
 * - func_15166D68
 * - func_15166F6C
 * - func_15166FD8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_193E50/func_151669A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_193E50/func_15166B50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_193E50/func_15166D68.s")

void func_15094F70(s32, void *, s32, void *, s32, s32, s32, s32, s32);
extern u8 D_8009054C;
extern s32 D_800DD220;
extern s32 D_800DD224;
extern u8 *D_800DD228;
extern u8 D_800DD230;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15166F6C CURRENT (883) */
void func_15166F6C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_800DD228 = &D_8009054C;
    func_15094F70(arg0, &D_8009054C, D_800DD220, &D_800DD230, 0, 0, 0,
                   D_800DD224, 3);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15166F6C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_193E50/func_15166F6C.s")
extern u8 D_80089470;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15166FD8 CURRENT (485) */
void *func_15166FD8(void *arg0, s32 arg1, s32 arg2) {
    u32 *temp_v1;

    temp_v1 = arg0;
    temp_v1[0] = 0xDA380003;
    temp_v1[1] = (u32)&D_80089470;
    return temp_v1 + 2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15166FD8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_193E50/func_15166FD8.s")
