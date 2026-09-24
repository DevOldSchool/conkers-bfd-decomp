#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D92F0.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151ABE40
 * - func_151AC078
 * - func_151AC3CC
 * - func_151AC408
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D92F0/func_151ABE40.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D92F0/func_151AC078.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AC3CC CURRENT (230) */
s32 func_151AC3CC(void *arg0) {
    s32 temp_t6;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    temp_t6 = *(s16 *)((u8 *)arg0 + 0x1C) * 8;
    {
        s32 var_v1 = temp_t6;
    if (temp_t6 >= 0x100) {
        var_v1 = 0xFF;
    }
    if (var_v1 < (s32) *(u8 *)((u8 *)temp_v0 + 0x1B)) {
        *(u8 *)((u8 *)temp_v0 + 0x1B) = (u8) var_v1;
    }
    return 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AC3CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D92F0/func_151AC3CC.s")
u8 func_151D8E20(void);
void func_151D9B8C(u8, f32, s32, s32, f32 *, s32, s32, s32, s32, s32, s32);
u32 func_150ADA20(void);
void func_151DAB58(u8, f32, u8, f32 *, s32, s32, s32);

typedef struct Game1D92F0Entry {
    f32 field_0;
    u8 pad_4[4];
    f32 field_8;
    u8 pad_C[8];
} Game1D92F0Entry;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AC408 CURRENT (128) */
s32 func_151AC408(void *arg0, s32 arg1, s32 arg2, s32 arg3,
                  f32 arg4, s32 arg5) {
    f32 position[3];
    u8 effect;
    Game1D92F0Entry *source;
    u8 *state;

    source = *(Game1D92F0Entry **)((u8 *)arg0 + 0x94);
    position[0] = source[*(s8 *)((u8 *)arg0 + 0x2D)].field_0;
    state = *(u8 **)((u8 *)arg0 + 0x98);
    position[1] = arg4;
    position[2] = source[*(s8 *)((u8 *)arg0 + 0x2D)].field_8;
    effect = func_151D8E20();
    if (func_150ADA20() & 1) {
        func_151D9B8C(effect, *(f32 *)state * 6.0f, state[0x1B], arg5,
                       position, (func_150ADA20() % 41U) + 0x50, 1, 1, 0,
                       *(u8 *)((u8 *)arg0 + 0xC), *(u8 *)((u8 *)arg0 + 1));
    } else {
        func_151DAB58(effect, *(f32 *)state * 1.5f, state[0x1B],
                       position, 1, *(u8 *)((u8 *)arg0 + 0xC),
                       *(u8 *)((u8 *)arg0 + 1));
    }
    state[0x20] = 4;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AC408 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D92F0/func_151AC408.s")
