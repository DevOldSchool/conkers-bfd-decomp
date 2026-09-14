#include "types.h"

/*
 * Reviewed source unit: src/game/game_121A20.c
 * Boundary evidence: docs/evidence/game_raw_secondary_stream_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F4570
 * - func_150F48D0
 * - func_150F4A38
 * - func_150F4CFC
 * - func_150F4D5C
 * - func_150F4DEC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game121A20NestedState {
    u8 pad0[0x24];
    u8 flags;
} Game121A20NestedState;

typedef struct Game121A20State {
    u8 pad0[0x71];
    u8 field71;
    u8 pad72[0xFE];
    Game121A20NestedState nested170;
} Game121A20State;

void func_1516972C(s32);

#pragma GLOBAL_ASM("asm/nonmatchings/game_121A20/func_150F4570.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_121A20/func_150F48D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_121A20/func_150F4A38.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F4CFC CURRENT (520) */
void func_150F4CFC(Game121A20State *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x4E) {
        arg0->field71 = 0;
        arg0->nested170.flags |= 5;
        return;
    }
    if (arg2 == 0x4F) {
        func_1516972C(arg2);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F4CFC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_121A20/func_150F4CFC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_121A20/func_150F4D5C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_121A20/func_150F4DEC.s")
