#include "types.h"

/*
 * Reviewed source unit: src/game/game_15D6E0.c
 * Boundary evidence: docs/evidence/game_raw_direct_call_singletons.md
 */

typedef struct {
    u8 pad_0[0xF];
    u8 field_F;
} Game15D6E0State;

extern Game15D6E0State *D_800B0DF0;
extern void (*D_80089670[])(void *);

void func_15130230(void *arg0, void *arg1) {
    u8 temp_v0;

    temp_v0 = D_800B0DF0->field_F;
    if (temp_v0 != 0) {
        D_80089670[temp_v0](arg0);
    }
}
