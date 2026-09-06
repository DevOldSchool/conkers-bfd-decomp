#include "types.h"

/*
 * Reviewed source unit: src/game/game_188440.c
 * Boundary evidence: docs/evidence/game_raw_quad_actor_effect_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1515AF90
 * - func_1515B21C
 * - func_1515B5F4
 * - func_1515B62C
 * - func_1515B674
 * - func_1515B994
 * - func_1515BA1C
 * - func_1515BA54
 * - func_1515BA80
 * - func_1515BAAC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_188440/func_1515AF90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_188440/func_1515B21C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_188440/func_1515B5F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_188440/func_1515B62C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_188440/func_1515B674.s")
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515B994 CURRENT (555) */
s32 func_1515B994(void *arg0) {
    f32 temp_fa1;
    f32 temp_fv1;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x78);
    temp_fa1 = *(f32 *)((u8 *)arg0 + 0x74);
    *(f32 *)((u8 *)arg0 + 0x14) = (f32) (*(f32 *)((u8 *)arg0 + 0x14) + ((temp_fv1 * D_800BE9A4) + (0.5f * temp_fa1 * D_800BE9A4)));
    *(f32 *)((u8 *)arg0 + 0x78) = (f32) (temp_fv1 + (temp_fa1 * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x1C) = (f32) (*(f32 *)((u8 *)arg0 + 0x7C) + (*(f32 *)((u8 *)arg0 + 0x80) * (*(f32 *)((u8 *)arg0 + 0x78) + temp_fv1) * 0.5f));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515B994 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_188440/func_1515B994.s")
void func_1515BA10(s32 arg0) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_188440/func_1515BA1C.s")
void func_1515BA48(s32 arg0) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_188440/func_1515BA54.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_188440/func_1515BA80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_188440/func_1515BAAC.s")
