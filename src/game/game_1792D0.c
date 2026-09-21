#include "types.h"

/*
 * Reviewed source unit: src/game/game_1792D0.c
 * Boundary evidence: docs/evidence/game_raw_directly_called_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1514BE20
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_15145128(f32 *, f32 *, f32 *, f32 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514BE20 CURRENT (3694) */
void func_1514BE20(u8 *arg0) {
    f32 sp5C;
    f32 sp58;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 x;
    f32 current_x;
    f32 current_y;
    f32 current_z;
    f32 factor;

    x = *(f32 *)(arg0 + 0x34);
    sp58 = *(f32 *)(arg0 + 0x38) + 100.0f;
    sp5C = *(f32 *)(arg0 + 0x3C);
    current_x = *(f32 *)(arg0 + 0x40);
    factor = *(f32 *)(arg0 + 0x15C);
    sp48 = current_x + ((x - current_x) * factor);
    current_y = *(f32 *)(arg0 + 0x44);
    sp4C = current_y + ((sp58 - current_y) * factor);
    current_z = *(f32 *)(arg0 + 0x48);
    sp50 = current_z + ((sp5C - current_z) * factor);
    sp38 = sp48 - x;
    sp3C = sp4C - *(f32 *)(arg0 + 0x38);
    sp40 = sp50 - *(f32 *)(arg0 + 0x3C);

    if (func_15145128(&sp38, &sp38, &sp34, &sp30) != 0) {
        *(f32 *)(arg0 + 0x40) = *(f32 *)(arg0 + 0x34) + (sp38 * 100.0f);
        *(f32 *)(arg0 + 0x44) = *(f32 *)(arg0 + 0x38) + (sp3C * 100.0f);
        *(f32 *)(arg0 + 0x48) = *(f32 *)(arg0 + 0x3C) + (sp40 * 100.0f);
    } else {
        *(s32 *)(arg0 + 0x40) = *(s32 *)(arg0 + 0x34);
        *(s32 *)(arg0 + 0x44) = *(s32 *)(arg0 + 0x38);
        *(s32 *)(arg0 + 0x48) = *(s32 *)(arg0 + 0x3C);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514BE20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1792D0/func_1514BE20.s")
