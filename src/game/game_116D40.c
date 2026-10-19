#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_116D40.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_loader_transfer_emission_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E9890
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_116D40/func_150E9890.s")
typedef struct Game116D40EmitterState {
    s32 target;
    f32 base;
    f32 range;
    f32 offset;
    f32 spread;
    f32 accumulator;
} Game116D40EmitterState;

f32 func_150ADA68(void);
void func_1514470C(s32, void *);
void func_15143794(s16, s16, f32, void *);
void func_150E9890(void *, void *, f32, u8, s32);
extern f32 D_800BE9A4;

void func_150E9E34(u8 *arg0) {
    Game116D40EmitterState *state;
    Vec3f sp80;
    Vec3f sp74;
    f32 value;
    u32 first;
    u32 second;

    state = (Game116D40EmitterState *)(arg0 + 0x28);
    state->accumulator += (state->base + func_150ADA68() * state->range) * D_800BE9A4;
    if (state->accumulator > 1.0f) {
        do {
            value = func_150ADA68() * state->spread + state->offset;
            func_1514470C(state->target, &sp80);
            first = func_150ADA20();
            second = func_150ADA20();
            func_15143794((s16)(first & 0xFF),
                           (s16)(0x40 - (second % 129U)),
                           func_150ADA68() * 600.0f * 0.01f,
                           &sp74);
            func_150E9890(&sp80, &sp74, value, arg0[0xC], arg0[1]);
            state->accumulator -= 1.0f;
        } while (state->accumulator > 1.0f);
    }
}
