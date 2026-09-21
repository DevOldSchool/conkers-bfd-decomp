#include "types.h"

/*
 * Reviewed source unit: src/game/game_6CEA0.c
 * Boundary evidence: docs/evidence/game_raw_parser_actor_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1503F9F0
 * - func_1503FB40
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s16 D_80084484;
extern s8 **D_800BE728;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1503F9F0 CURRENT (2050) */
void func_1503F9F0(s16 arg0, s16 *arg1, s16 *arg2) {
    s16 counter;
    s16 value;
    s8 first;
    s8 second;
    s8 *entry;

    counter = D_80084484 - 1;
    entry = D_800BE728[arg0];
    if (counter != 0) {
        D_80084484 = counter;
        *arg1 = 0;
        *arg2 = 0;
        return;
    }
    first = entry[2];
    D_80084484 = 5;
    if ((first < -0x14) || (first >= 0x15)) {
        *arg1 = first;
    } else {
        *arg1 = 0;
    }
    second = entry[3];
    if ((second < -0x14) || (second >= 0x15)) {
        *arg2 = second;
    } else {
        *arg2 = 0;
    }
    entry[2] = 0;
    entry[3] = 0;

    value = *arg1;
    if (value < -1) {
        *arg1 = -1;
    } else {
        if (value >= 2) {
            value = 1;
        }
        *arg1 = value;
    }
    value = *arg2;
    if (value < -1) {
        *arg2 = -1;
        return;
    }
    if (value >= 2) {
        value = 1;
    }
    *arg2 = value;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1503F9F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6CEA0/func_1503F9F0.s")
extern s32 D_80084488;
extern s32 D_8008448C;
extern s8 D_80084490;
extern s8 D_80084494;
extern f32 D_800C6850;

void func_1503FB08(void) {
    D_80084488 = 0;
    D_800C6850 = 0.0f;
    D_8008448C = 0;
    D_80084490 = 0x1E;
    D_80084494 = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_6CEA0/func_1503FB40.s")
