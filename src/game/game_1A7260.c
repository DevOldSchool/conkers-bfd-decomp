#include "types.h"

/*
 * Reviewed source unit: src/game/game_1A7260.c
 * Boundary evidence: docs/evidence/game_raw_direct_call_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15179DB0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    s16 x;
    u8 pad2[0xE];
} Game179DB0Vertex;

typedef struct {
    u8 pad0[0x18];
    f32 velocity[2];
    f32 phase[2];
    f32 magnitude;
    u8 pad2C[0xC];
} Game179DB0State;

typedef struct {
    u8 pad0[4];
    Game179DB0Vertex *first;
    Game179DB0Vertex *second;
    u8 padC[8];
} Game179DB0Entry;

extern Game179DB0State D_8008D0B0[];
extern Game179DB0Entry D_800DDE80[];
extern u8 D_800A7210[];
extern f32 D_800A7218;
f32 func_15047D60(f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15179DB0 CURRENT (1151) */
void func_15179DB0(u8 arg0) {
    Game179DB0State *state;
    f32 scale;
    s32 height;
    Game179DB0Vertex *buffers[2];
    f32 *phases[2];
    f32 *velocities[2];
    Game179DB0Vertex **buffer;
    f32 **phase;
    f32 **velocity;
    s32 i;

    state = &D_8008D0B0[arg0];
    buffers[1] = D_800DDE80[arg0].first;
    buffers[0] = D_800DDE80[arg0].second;
    scale = D_800A7218;
    phases[0] = &state->phase[0];
    phases[1] = &state->phase[1];
    velocities[0] = &state->velocity[0];
    velocities[1] = &state->velocity[1];
    phase = phases;
    buffer = buffers;
    velocity = velocities;
    do {
        height = (s16)(s32)(func_15047D60(**phase * scale) * state->magnitude);
        (*buffer)[2].x = height;
        (*buffer)[3].x = height;
        height = -(height >> 1);
        for (i = 0; i < 7; i++) {
            (*buffer)[D_800A7210[i]].x = height;
        }
        (*buffer)[6].x = height + 0x12;
        (*buffer)[8].x = height - 0x12;
        **phase += **velocity;
        if (**phase >= 360.0f) {
            **phase -= 360.0f;
        }
        phase++;
        velocity++;
        buffer++;
    } while (velocity != phases);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15179DB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A7260/func_15179DB0.s")
