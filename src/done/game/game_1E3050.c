#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E3050.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_direct_call_singletons.md
 */

typedef struct {
    u8 pad_0[4];
    u8 field_4;
} Game1E3050Data;

void *func_151B4FE0(void *, u8, s32);

void func_151B5BA0(Game1E3050Data *arg0, Game1E3050Data *arg1) {
    if ((arg0->field_4 == 0x53) && (arg1->field_4 == 0x16)) {
        func_151B4FE0(arg1, 0xFF, 1);
    }
}
