#include "types.h"

/*
 * Reviewed source unit: src/game/game_FC9E0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150CF530
 * - func_150CF578
 * - func_150CF5E8
 * - func_150CF680
 * - func_150CF800
 * - func_150CFBEC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_FC9E0/func_150CF530.s")
extern s32 D_80088890;
extern s32 D_80088894;
extern s32 D_80088898;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CF578 CURRENT (265) */
void func_150CF578(s32 arg0) {
    s32 temp_v1;

    temp_v1 = D_800BE9E4 * 0x1C;
    D_80088890 += D_800BE9E4 * 0x1A;
    D_80088894 -= temp_v1;
    D_80088898 -= temp_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CF578 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FC9E0/func_150CF578.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FC9E0/func_150CF5E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FC9E0/func_150CF680.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FC9E0/func_150CF800.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FC9E0/func_150CFBEC.s")
void func_150CFC38(f32 arg0) {
    f32 sp1C;

    sp1C = arg0;
    func_1515572C(&sp1C, 0x52);
}
