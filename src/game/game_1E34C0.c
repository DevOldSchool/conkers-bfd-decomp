#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E34C0.c
 * Boundary evidence: docs/evidence/game_raw_compact_display_resource_pairs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B6010
 * - func_151B6254
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E34C0/func_151B6010.s")
f32 func_15047D60(f32);
void func_15133894(void *);
extern f32 D_800AA454;
extern f32 D_800AA458;
extern f32 D_800AA45C;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B6254 CURRENT (469) */
void func_151B6254(u8 *arg0) {
    f32 *angle;
    f32 value;
    f32 wave;
    f32 wrap;

    wrap = D_800AA454;
    angle = (f32 *)(arg0 + 0x170);
    *angle += D_800AA458 * D_800BE9A4;
    while (wrap < *angle) {
        *angle -= wrap;
    }
    wave = func_15047D60(*angle);
    value = angle[1];
    value += wave * (D_800AA45C * value);
    *(f32 *)(arg0 + 0x18) = *(f32 *)(arg0 + 0x1C) = value;
    func_15133894(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B6254 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E34C0/func_151B6254.s")
