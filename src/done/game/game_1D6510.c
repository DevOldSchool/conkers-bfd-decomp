#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D6510.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_singletons_final.md
 */

typedef struct Game1D6510State {
    u8 pad0[0x16];
    u8 flags;
    u8 pad17;
    s32 callbackIndex;
} Game1D6510State;

extern s32 (*D_8008F984[])(Game1D6510State *);

s32 func_151A9060(Game1D6510State *arg0) {
    s32 index;
    s32 (*callback)(Game1D6510State *);

    index = arg0->callbackIndex;
    arg0->flags |= 4;
    if ((index < 0) || (index >= 8)) {
        return 1;
    }
    /*
     * The empty blocks and the table re-read in the test below are required
     * for IDO codegen (permuter); callback holds the same table entry.
     */
    if (1) {
    }
    if (1) {
    }
    if (1) {
    }
    if (1) {
    }
    if (1) {
    }
    if (1) {
    }
    callback = D_8008F984[index];
    if (D_8008F984[index] != 0) {
        callback(arg0);
    }
    return 1;
}
