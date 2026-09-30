#include "types.h"

/*
 * Reviewed source unit: src/game/game_15A840.c
 * Boundary evidence: docs/evidence/game_raw_direct_call_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1512D390
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_1508EF80(f32 *, f32 *, f32, f32 *);
extern f32 D_800A36E0;
extern f32 D_800BE9A4;

typedef struct Game15A840State {
    u8 pad0[0x14];
    s32 direction;
    u8 pad18[0xC];
    s32 counter;
    f32 rate;
} Game15A840State;

typedef struct Game15A840Owner {
    u8 pad0[0x2C];
    u32 flags2C;
    u8 pad30[0x54];
    u32 flags84;
    u8 pad88[0x21C];
    f32 target[3];
    u8 pad2B0[0x48];
    f32 vector[3];
    u8 pad304[0x68];
    u16 *input;
    u8 pad370[0x328];
    s32 lock;
    Game15A840State state;
} Game15A840Owner;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1512D390 CURRENT (490) */
void func_1512D390(Game15A840Owner *arg0) {
    Game15A840State *state;
    u16 input;
    f32 value;
    f32 clamped;

    input = *arg0->input;
    if ((input & 3) && !(arg0->flags84 & 0x200000)) {
        state = &arg0->state;
        if (arg0->lock == 0) {
            if (input & 1) {
                arg0->state.direction = 1;
            } else {
                arg0->state.direction = -1;
            }
            clamped = -10.0f;
            state->counter++;
            state->rate += (f32)arg0->state.direction * 0.5f * D_800BE9A4;
            value = state->rate;
            if (value < -10.0f) {
                state->rate = -10.0f;
            } else {
                if (value > 10.0f) {
                    clamped = 10.0f;
                } else {
                    clamped = value;
                }
                state->rate = clamped;
            }
            if (arg0->flags2C & 0x400) {
                state->counter = 0x14;
                return;
            }
            func_1508EF80(arg0->vector, arg0->target,
                         (state->rate * D_800BE9A4) / 2.5f, arg0->vector);
        }
    } else {
        Game15A840State *decayState = &arg0->state;
        f32 old = decayState->rate;

        if (0.0f != old) {
            decayState->rate = old - (old * D_800A36E0 * D_800BE9A4);
            func_1508EF80(arg0->vector, arg0->target,
                         (decayState->rate * D_800BE9A4) / 2.5f, arg0->vector);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1512D390 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15A840/func_1512D390.s")
