#include "types.h"

/*
 * Reviewed source unit: src/game/game_FF900.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_singletons_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D2450
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameFF900Color {
    f32 base[3];
    f32 amplitude[3];
    f32 phase[3];
    f32 rate[3];
} GameFF900Color;

typedef struct GameFF900State {
    u8 pad0[0x28];
    GameFF900Color color;
} GameFF900State;

f32 func_15047D60(f32);
f32 func_15144B68(f32);
void func_1515D4D4(s32, s32, s32, s32);
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D2450 CURRENT (951) */
void func_150D2450(GameFF900State *arg0) {
    f32 first;
    f32 second;
    GameFF900Color *color;

    first = func_15047D60(arg0->color.phase[0]);
    color = &arg0->color;
    second = func_15047D60(arg0->color.phase[1]);
    func_1515D4D4((u32)(first * color->amplitude[0] + color->base[0]) & 0xFF,
                  (u32)(second * color->amplitude[1] + color->base[1]) & 0xFF,
                  (u32)(func_15047D60(color->phase[2]) * color->amplitude[2] + color->base[2]) & 0xFF, 0);
    color->phase[0] = func_15144B68(color->phase[0] + color->rate[0] * D_800BE9A4);
    color->phase[1] = func_15144B68(color->phase[1] + color->rate[1] * D_800BE9A4);
    color->phase[2] = func_15144B68(color->phase[2] + color->rate[2] * D_800BE9A4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D2450 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FF900/func_150D2450.s")
