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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510D694 CURRENT (130) */
void func_1510D694(s32 arg0) {
    u8 temp_v1;
    u8 *temp_v0;
    u8 temp_t8;

    temp_v0 = &D_800D9F68[arg0];
    if (D_800BC448[arg0] != 0) {
        temp_v1 = *temp_v0;
        temp_t8 = temp_v1 - 1;
        if (temp_v1 != 0) {
            *temp_v0 = temp_t8;
            if ((temp_t8 & 0xFF) == 0) {
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
#endif /* CONKER_DEFERRED_CANDIDATE func_1510D694 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13AAE0/func_1510D694.s")
