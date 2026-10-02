#include "types.h"

/*
 * Reviewed source unit: src/game/game_E2DA0.c
 * Boundary evidence: docs/evidence/game_raw_direct_call_singletons.md
 */

typedef struct GameE2DA0Output {
    s16 type;
    u16 value;
} GameE2DA0Output;

typedef struct GameE2DA0ValueRecord {
    u16 value;
    u8 pad2[0x32A];
} GameE2DA0ValueRecord;

extern u8 D_800C35EA;
extern GameE2DA0ValueRecord D_800CC34A[];

GameE2DA0Output *func_150B58F0(GameE2DA0Output *arg0, s32 arg1) {
    if (D_800C35EA == 1) {
        return arg0;
    }
    arg0->type = 0x1A;
    arg0->value = D_800CC34A[arg1].value;
    return arg0 + 1;
}
