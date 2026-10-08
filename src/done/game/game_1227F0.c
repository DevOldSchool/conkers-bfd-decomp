#include "types.h"

/*
 * Reviewed source unit: src/game/game_1227F0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_direct_call_singletons.md
 */

typedef struct Game1227F0Indices {
    s32 values[17];
} Game1227F0Indices;

void func_1515F170(s32, s32);
void func_151C970C(s32, void *);
extern Game1227F0Indices D_800A1AB0;
extern s32 D_800D3098;

void func_150F5340(void) {
    u8 var_s0;
    Game1227F0Indices indices;

    var_s0 = 0;
    indices = D_800A1AB0;
    for (var_s0 = 0; var_s0 < 0x11; var_s0++) {
        func_151C970C(1, (void *)((indices.values[var_s0] * 0x34) + D_800D3098));
    }
    func_1515F170(9, 1);
}
