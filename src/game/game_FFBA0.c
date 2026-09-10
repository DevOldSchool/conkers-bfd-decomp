#include "types.h"

/*
 * Reviewed source unit: src/game/game_FFBA0.c
 * Boundary evidence: docs/evidence/game_raw_child_chain_render_lists.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D26F0
 * - func_150D278C
 * - func_150D2924
 * - func_150D2D6C
 * - func_150D317C
 * - func_150D32FC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_FFBA0/func_150D26F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FFBA0/func_150D278C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FFBA0/func_150D2924.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FFBA0/func_150D2D6C.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D317C CURRENT (1600) */
s32 func_150D317C(u8 *arg0) {
    s32 var_v0;
    u8 *temp_s0;

    *(f32 *)((u8 *)arg0 + 0x128) = (f32) (*(f32 *)((u8 *)arg0 + 0x128) + (*(f32 *)((u8 *)arg0 + 0x130) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x12C) = (f32) (*(f32 *)((u8 *)arg0 + 0x12C) + (*(f32 *)((u8 *)arg0 + 0x134) * D_800BE9A4));
    temp_s0 = (void *)(arg0 + 0x110);
    *(f32 *)((u8 *)temp_s0 + 0x18) = func_15144B68(*(f32 *)((u8 *)arg0 + 0x128));
    *(f32 *)((u8 *)temp_s0 + 0x1C) = func_15144B68(*(f32 *)((u8 *)temp_s0 + 0x1C));
    *(f32 *)((u8 *)arg0 + 0x110) = (f32) ((func_15047D60(*(f32 *)((u8 *)temp_s0 + 0x18)) * *(f32 *)((u8 *)temp_s0 + 0x10)) + *(f32 *)((u8 *)temp_s0 + 8));
    var_v0 = 0;
    *(f32 *)((u8 *)temp_s0 + 4) = (f32) ((func_15047D60(*(f32 *)((u8 *)temp_s0 + 0x1C)) * *(f32 *)((u8 *)temp_s0 + 0x14)) + *(f32 *)((u8 *)temp_s0 + 0xC));
    *(f32 *)((u8 *)temp_s0 + 0x28) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x28) - D_800BE9A4);
    *(s8 *)((u8 *)arg0 + 0x5C) = (s8) (u32) (*(f32 *)((u8 *)temp_s0 + 0x2C) * *(f32 *)((u8 *)temp_s0 + 0x28));
    if (*(f32 *)((u8 *)temp_s0 + 0x28) > 0.0f) {
        var_v0 = 1;
    }
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D317C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FFBA0/func_150D317C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FFBA0/func_150D32FC.s")
