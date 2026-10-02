#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E9820.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151BC370
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15143794(s16, s16, f32, void *);
void func_151A26EC(f32 *, f32 *, f32 *, f32, f32, f32, s32, s32, s32,
                    s32, s32, s32, s32, s32, s32, s32, s32);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
extern f32 D_800AA834;
extern f32 D_800AA838;
extern f32 D_800AA83C;
extern f32 D_800AA840;
extern f32 D_800AA844;
extern f32 D_800BE9A8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BC370 CURRENT (1110) */
void func_151BC370(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4,
                   f32 arg5, void *arg6) {
    f32 position[3];
    f32 velocity[3];
    f32 zero[3];
    f32 velocityScale;
    f32 randomScale1;
    u32 random1;
    u32 random0;
    f32 randomScale0;

    position[0] = arg0;
    position[1] = arg1;
    position[2] = arg2;
    random0 = func_150ADA20();
    random1 = func_150ADA20();
    func_15143794((s16)(random0 & 0xFF), (s16)((random1 % 65U) - 0x20),
                   func_150ADA68() * 1680.0f * D_800AA834, velocity);
    velocityScale = ((func_150ADA68() * 202.0f) + 208.0f) * D_800AA838;
    zero[0] = 0.0f;
    zero[1] = 0.0f;
    zero[2] = 0.0f;
    velocity[0] += -arg3 * D_800BE9A8 * velocityScale;
    velocity[1] += -arg4 * D_800BE9A8 * velocityScale;
    velocity[2] += -arg5 * D_800BE9A8 * velocityScale;
    randomScale0 = func_150ADA68();
    randomScale1 = func_150ADA68();
    random0 = func_150ADA20();
    func_151A26EC(position, zero, velocity, 1.0f,
                   ((randomScale0 * D_800AA83C) + D_800AA840) * D_800AA844,
                   (randomScale1 * 124.0f) + 202.0f,
                   (random0 & 0xF) + 0x14, (func_150ADA20() % 201U) + 0x37,
                   0xF, 0xF, 0, -1, 0xCB, 0, 0,
                   *(u8 *)((u8 *)arg6 + 0xC), *(u8 *)((u8 *)arg6 + 1));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BC370 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9820/func_151BC370.s")
