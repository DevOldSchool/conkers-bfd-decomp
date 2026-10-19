#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_117940.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_singletons_final.md
 */

typedef struct Game117940Phase {
    u32 phase_80;
    s32 phase_step_84;
    f32 base_88;
    f32 amplitude_8C;
} Game117940Phase;

typedef struct Game117940State {
    u8 pad0[0x80];
    Game117940Phase phase;
} Game117940State;

extern s32 D_800BE9E4;

f32 func_150EA490(Game117940State *arg0) {
    Game117940Phase *phase = &arg0->phase;
    f32 result;

    result = (func_151423D8((phase->phase_80 >> 16) - 0x40) * phase->amplitude_8C) + phase->base_88;
    phase->phase_80 += (u32)phase->phase_step_84 * (u32)D_800BE9E4;
    return result;
}
