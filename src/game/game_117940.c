#include "types.h"

/*
 * Reviewed source unit: src/game/game_117940.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_final.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150EA490
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
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

f32 func_151423D8(u8);
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EA490 CURRENT (20) */
f32 func_150EA490(Game117940State *volatile arg0) {
    s32 angle;
    f32 result;
    f32 sine;
    Game117940Phase *phase;

    angle = (s32)(arg0->phase.phase_80 >> 16) - 0x40;
    sine = func_151423D8(angle & 0xFF);
    phase = (Game117940Phase *)((u8 (*)[1])arg0)[0x80];
    result = (sine * phase->amplitude_8C) + phase->base_88;
    phase->phase_80 += phase->phase_step_84 * D_800BE9E4;
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EA490 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_117940/func_150EA490.s")
