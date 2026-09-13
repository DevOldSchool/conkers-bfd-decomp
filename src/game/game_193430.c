#include "types.h"

/*
 * Reviewed source unit: src/game/game_193430.c
 * Boundary evidence: docs/evidence/game_raw_display_transition_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15165F80
 * - func_15166118
 * - func_15166268
 * - func_151668B8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_193430/func_15165F80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_193430/func_15166118.s")
typedef struct {
    u8 pad_0[0x92];
    u8 field_92;
    u8 pad_93[3];
    s16 field_96;
    u8 pad_98[6];
    s16 field_9E;
} Game193430State;

extern s32 D_800BE9E4;
void func_1516972C(void *);

void func_15166204(Game193430State *arg0) {
    s32 temp_v0;

    arg0->field_9E = arg0->field_9E + (arg0->field_96 * D_800BE9E4);
    temp_v0 = arg0->field_92;
    temp_v0 -= D_800BE9E4;
    if (temp_v0 <= 0) {
        func_1516972C(arg0);
        return;
    }
    arg0->field_92 = temp_v0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_193430/func_15166268.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_193430/func_151668B8.s")
