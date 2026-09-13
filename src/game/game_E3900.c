#include "types.h"

/*
 * Reviewed source unit: src/game/game_E3900.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B6450
 * - func_150B648C
 * - func_150B66DC
 * - func_150B6754
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_1516972C(s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B6450 CURRENT (577) */
void func_150B6450(s32 arg0, s32 arg1, s32 arg2) {
    arg2 = arg2 & 0xFF;
    if (arg2 == 0x4A) {
        func_1516972C(arg0, arg1, arg2);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B6450 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E3900/func_150B6450.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E3900/func_150B648C.s")
typedef struct {
    u8 pad0[0x68];
    u8 mode;
} GameE3900Input;

typedef struct {
    u8 pad0[9];
    u8 enabled;
    u8 padA[0x25];
    u8 duration;
} GameE3900Output;

typedef struct {
    u8 pad0[0x14];
    GameE3900Output *output;
    GameE3900Input *input;
} GameE3900State;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B66DC CURRENT (205) */
s32 func_150B66DC(GameE3900State *arg0) {
    s32 mode;

    mode = arg0->input->mode - 0xF;
    switch (mode) {
    case 0:
        arg0->output->enabled = 1;
        break;
    case 1:
        arg0->output->enabled = 0;
        arg0->output->duration = 0x14;
        break;
    default:
    case 2:
        arg0->output->enabled = 0;
        arg0->output->duration = 0x28;
        break;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B66DC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E3900/func_150B66DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E3900/func_150B6754.s")
