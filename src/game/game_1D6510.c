#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D6510.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_final.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A9060
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1D6510State {
    u8 pad0[0x16];
    u8 flags;
    u8 pad17;
    s32 callbackIndex;
} Game1D6510State;

extern s32 (*D_8008F984[])(Game1D6510State *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A9060 CURRENT (460) */
s32 func_151A9060(Game1D6510State *arg0) {
    s32 index;
    s32 (*callback)(Game1D6510State *);

    index = arg0->callbackIndex;
    arg0->flags |= 4;
    if ((index >= 0) && (index < 8)) {
        callback = D_8008F984[index];
        if (callback != 0) {
            callback(arg0);
        }
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A9060 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6510/func_151A9060.s")
