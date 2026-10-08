#include "types.h"

/*
 * Reviewed source unit: src/game/game_1238B0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_directly_called_families.md
 */

typedef struct Game1238B0Substate {
    u8 pad0[8];
    s32 field_8;
} Game1238B0Substate;

typedef struct Game1238B0Inner {
    u8 pad0[0x28];
    Game1238B0Substate field_28;
} Game1238B0Inner;

typedef struct Game1238B0Object {
    u8 pad0[0x160];
    Game1238B0Inner *field_160;
} Game1238B0Object;

void func_150F6400(Game1238B0Object *arg0) {
    Game1238B0Inner **inner = &arg0->field_160;

    if (*inner) {
        Game1238B0Substate *state = &(*inner)->field_28;

        state->field_8 = 0;
    }
}
