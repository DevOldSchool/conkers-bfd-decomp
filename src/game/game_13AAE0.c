#include "types.h"

/*
 * Reviewed source unit: src/game/game_13AAE0.c
 * Boundary evidence: docs/evidence/game_raw_internal_call_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1510D694
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    s16 count;
    s16 values[1];
} Game13AAE0ValueList;

void func_10004074(s32);
void func_1510D694(s16);

void func_1510D630(Game13AAE0ValueList *arg0) {
    s16 *current;
    s16 *end;
    s16 count;

    count = arg0->count;
    current = arg0->values;
    if (count > 0) {
        end = (s16 *)((count * 2) + (u8 *)arg0 + 2);
        do {
            func_1510D694(*current);
            current++;
        } while (end != current);
    }
    func_10004074((s32)arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_13AAE0/func_1510D694.s")
