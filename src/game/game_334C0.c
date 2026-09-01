#include "types.h"

/*
 * Reviewed source unit: src/game/game_334C0.c
 * Boundary evidence: docs/evidence/game_compact_multi_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15006010
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game334C0State {
    u8 pad0[0x1B4];
    s16 unk1B4;
    u8 pad1[0x2A];
    s16 unk1E0;
} Game334C0State;

void func_15124B18(void);

#pragma GLOBAL_ASM("asm/nonmatchings/game_334C0/func_15006010.s")
void func_15006140(Game334C0State *arg0) {
    arg0->unk1E0 = 5;
    arg0->unk1B4 = 2;
    func_15124B18();
}
