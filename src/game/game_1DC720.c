#include "types.h"

/*
 * Reviewed source unit: src/game/game_1DC720.c
 * Boundary evidence: docs/evidence/game_raw_buffer_stream_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151AF270
 * - func_151AF338
 * - func_151AF388
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1DC720/func_151AF270.s")
typedef struct {
    u8 pad_0[0xC];
    u8 field_C;
} Game1DC720State;

void func_151AF388(f32 *, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AF338 CURRENT (460) */
void func_151AF338(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, s32 arg5,
                   Game1DC720State *arg6) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;

    sp24 = arg0;
    sp28 = arg1;
    sp2C = arg2;
    func_151AF388(&sp24, arg3, arg4, arg5, arg6->field_C);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AF338 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DC720/func_151AF338.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DC720/func_151AF388.s")
