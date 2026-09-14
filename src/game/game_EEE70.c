#include "types.h"

/*
 * Reviewed source unit: src/game/game_EEE70.c
 * Boundary evidence: docs/evidence/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C1A40
 * - func_150C1E34
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameEEE70State {
    u8 pad0[0x1D4];
    s32 field_1D4;
} GameEEE70State;

void func_15142314(s32, s32, void *);

s32 func_150C19C0(void *arg0, GameEEE70State *arg1, u8 arg2) {
    s32 index;

    switch (arg2) {
    case 1:
        index = 0x18;
        break;
    case 2:
        index = 0x15;
        break;
    }
    func_15142314(arg1->field_1D4, index, arg0);
    return 1;
}
s32 func_150C1A2C(s32 arg0, s32 arg1) {
    return 7;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_EEE70/func_150C1A40.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EEE70/func_150C1E34.s")
