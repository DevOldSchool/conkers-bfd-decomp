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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EA490 CURRENT (865) */
f32 func_150EA490(Game117940State *arg0) {
    u8 index;
    f32 result;

    index = ((arg0->phase.phase_80 >> 16) - 0x40) & 0xFF;
    result = (func_151423D8(index) * arg0->phase.amplitude_8C) + arg0->phase.base_88;
    arg0->phase.phase_80 += arg0->phase.phase_step_84 * D_800BE9E4;
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EA490 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_117940/func_150EA490.s")
