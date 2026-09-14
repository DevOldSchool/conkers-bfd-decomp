#include "types.h"

/*
 * Reviewed source unit: src/game/game_1A6300.c
 * Boundary evidence: docs/evidence/game_remaining_single_function_units_up_to_256_bytes.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15178E50
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1A6300InputState {
    u8 pad0[0x14];
    u8 mode;
    u8 pad15;
    s16 threshold;
} Game1A6300InputState;

typedef struct Game1A6300WorldState {
    u8 pad0[0x2FC];
    f32 value2FC;
} Game1A6300WorldState;

extern Game1A6300InputState *D_800B0DF0;
extern Game1A6300WorldState *D_800DBFF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15178E50 CURRENT (40) */
s32 func_15178E50(s32 arg0) {
    if ((D_800B0DF0->mode == 1) &&
        (D_800B0DF0->threshold < (s32) D_800DBFF0->value2FC)) {
        return 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15178E50 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A6300/func_15178E50.s")
