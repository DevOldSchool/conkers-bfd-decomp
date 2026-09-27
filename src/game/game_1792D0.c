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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514BE20 CURRENT (2151) */
void func_1514BE20(u8 *arg0) {
    typedef struct { f32 x, y, z; } Vector;
    struct { Vector delta; volatile Vector interpolated; f32 targetY, targetZ; } vectors;
    f32 sp34;
    f32 sp30;
    f32 x;
    f32 current_x;
    f32 current_y;
    f32 current_z;
    f32 factor;

    x = *(f32 *)(arg0 + 0x34);
    vectors.targetY = *(f32 *)(arg0 + 0x38) + 100.0f;
    vectors.targetZ = *(f32 *)(arg0 + 0x3C);
    current_x = *(f32 *)(arg0 + 0x40);
    factor = *(f32 *)(arg0 + 0x15C);
    vectors.interpolated.x = current_x + ((x - current_x) * factor);
    current_y = *(f32 *)(arg0 + 0x44);
    vectors.interpolated.y = current_y + ((vectors.targetY - current_y) * factor);
    current_z = *(f32 *)(arg0 + 0x48);
    vectors.interpolated.z = current_z + ((vectors.targetZ - current_z) * factor);
    vectors.delta.x = vectors.interpolated.x - x;
    vectors.delta.y = vectors.interpolated.y - *(f32 *)(arg0 + 0x38);
    vectors.delta.z = vectors.interpolated.z - *(f32 *)(arg0 + 0x3C);

    if (func_15145128(&vectors.delta.x, &vectors.delta.x, &sp34, &sp30) != 0) {
        *(f32 *)(arg0 + 0x40) = *(f32 *)(arg0 + 0x34) + (vectors.delta.x * 100.0f);
        *(f32 *)(arg0 + 0x44) = *(f32 *)(arg0 + 0x38) + (vectors.delta.y * 100.0f);
        *(f32 *)(arg0 + 0x48) = *(f32 *)(arg0 + 0x3C) + (vectors.delta.z * 100.0f);
    } else {
        *(Vector *)(arg0 + 0x40) = *(Vector *)(arg0 + 0x34);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514BE20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1792D0/func_1514BE20.s")
