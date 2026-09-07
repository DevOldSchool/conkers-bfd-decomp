#include "types.h"

/*
 * Reviewed source unit: src/game/game_61D10.c
 * Boundary evidence: docs/evidence/game_raw_compact_display_resource_pairs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15034860
 * - func_15034EB4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_61D10/func_15034860.s")
extern f32 D_80097D60;
extern s16 D_800C3EF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15034EB4 CURRENT (10) */
void func_15034EB4(void *arg0, s32 arg1, s32 arg2) {
    f32 temp_fv0;
    s32 temp_v1;
    void *temp_a2;
    void *temp_v0;

    if (D_800C3EF0 != 0) {
        temp_v1 = *(s32 *)((u8 *)arg0 + 0x1D4);
        temp_a2 = (void *)((arg1 << 6) + temp_v1);
        temp_v0 = (void *)((arg2 << 6) + temp_v1);
        temp_fv0 = (f32) D_800C3EF0 * D_80097D60 * *(f32 *)((u8 *)arg0 + 0x14C);
        *(f32 *)((u8 *)temp_a2 + 0x34) = (f32) (*(f32 *)((u8 *)temp_a2 + 0x34) - temp_fv0);
        if (arg2 != -1) {
            *(f32 *)((u8 *)temp_v0 + 0x34) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x34) - temp_fv0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15034EB4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_61D10/func_15034EB4.s")
