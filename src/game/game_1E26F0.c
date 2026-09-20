#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E26F0.c
 * Boundary evidence: docs/evidence/game_raw_radial_queue_render_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B5240
 * - func_151B5328
 * - func_151B5A9C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);
s32 func_15083E90(u8);
s32 func_15149130(s16, s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 D_800AA418;

typedef struct {
    u8 packet[0x5A8];
    u8 pad_5D8[4];
    s32 sp5DC;
} Game1E26F0Stack;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B5240 CURRENT (582) */
s32 func_151B5240(s16 arg0, u8 arg1, s32 arg2) {
    Game1E26F0Stack stack;
    f32 temp_fv0;
    s32 temp_v0;
    s32 var_v1;

    stack.packet[0x584] = 0x17;
    stack.packet[0x58C] = 0x16;
    *(s32 *)(stack.packet + 0x580) = func_15083E90(0x17);
    *(s32 *)(stack.packet + 0x588) = func_15083E90(stack.packet[0x58C]);
    temp_fv0 = 250.0f;
    *(f32 *)(stack.packet + 0x598) = temp_fv0;
    *(f32 *)(stack.packet + 0x590) = 18.0f;
    *(f32 *)(stack.packet + 0x5A0) = D_800AA418;
    *(f32 *)(stack.packet + 0x594) = 0.0f;
    *(f32 *)(stack.packet + 0x59C) = 1.0f / temp_fv0;
    temp_v0 = func_15149130(arg0, -1, -1, 1, 1, 0x15, 0x5A8, arg1, arg2);
    var_v1 = temp_v0;
    if (temp_v0 != 0) {
        stack.sp5DC = temp_v0;
        func_10022EC0((void *)(temp_v0 + 0x28), stack.packet, 0x5A8);
        var_v1 = stack.sp5DC;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B5240 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E26F0/func_151B5240.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E26F0/func_151B5328.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E26F0/func_151B5A9C.s")
