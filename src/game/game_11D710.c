#include "types.h"

/*
 * Reviewed source unit: src/game/game_11D710.c
 * Boundary evidence: docs/evidence/game_raw_internal_call_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F02A0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game11D710State {
    u8 pad0[8];
    u8 *field_8;
    u8 field_C;
} Game11D710State;

typedef struct Game11D710Object {
    u8 pad0[0x60];
    Game11D710State *field_60;
} Game11D710Object;

void func_150F02A0(Game11D710Object *arg0);

void func_150F0260(Game11D710Object *arg0) {
    func_150F02A0(arg0);
}
void func_150F0280(Game11D710Object *arg0) {
    func_150F02A0(arg0);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F02A0 CURRENT (40) */
void func_150F02A0(Game11D710Object *arg0) {
    Game11D710State *state = arg0->field_60;

    *(s32 *)(state->field_8 + (state->field_C * 4) + 0x12C) = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F02A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D710/func_150F02A0.s")
