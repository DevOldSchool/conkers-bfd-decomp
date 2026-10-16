#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_13AAE0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_internal_call_callback_clusters.md
 */

typedef struct Game13AAE0ValueList {
    s16 count;
    s16 values[1];
} Game13AAE0ValueList;

void func_10004074(s32);
void func_1510D694(s32);

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
void func_1510D608(s32, s32);
extern s8 D_800BC448[];
extern s32 D_800D9F58;
extern s32 D_800D9F5C;
extern u8 D_800D9F68[];

void func_1510D694(s32 arg0) {
    u8 *temp_v0;

    temp_v0 = &D_800D9F68[arg0];
    if (D_800BC448[arg0] != 0) {
        if (*temp_v0 != 0) {
            *temp_v0 -= 1;
            if (*temp_v0 == 0) {
                if (arg0 < D_800D9F58) {
                    D_800D9F58 = (s32) arg0;
                }
                if (D_800D9F5C < arg0) {
                    D_800D9F5C = (s32) arg0;
                }
                func_1510D608((s32) arg0, 3);
            }
        }
    }
}
