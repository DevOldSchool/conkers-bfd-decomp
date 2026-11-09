#include "types.h"

/*
 * Reviewed source unit: src/game/game_FF900.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_singletons_continued.md
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

void func_150D2450(GameFF900State *arg0) {
    GameFF900Color *color = &arg0->color;

    func_1515D4D4((u8)(u32)(color->base[0] + color->amplitude[0] * func_15047D60(color->phase[0])),
                  (u8)(u32)(color->base[1] + color->amplitude[1] * func_15047D60(color->phase[1])),
                  (u8)(u32)(color->base[2] + color->amplitude[2] * func_15047D60(color->phase[2])), 0);
    color->phase[0] = func_15144B68(color->rate[0] * D_800BE9A4 + color->phase[0]);
    color->phase[1] = func_15144B68(color->rate[1] * D_800BE9A4 + color->phase[1]);
    color->phase[2] = func_15144B68(color->rate[2] * D_800BE9A4 + color->phase[2]);
}
