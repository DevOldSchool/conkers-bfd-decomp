#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E04F0.c
 * Boundary evidence: docs/evidence/game_raw_preserved_singleton_1b3040.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B3040
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1E04F0State {
    u8 pad0[0x150];
    s32 field_150;
    s32 field_154;
    u8 pad158[0xC];
    s32 field_164;
    s32 field_168;
} Game1E04F0State;

void func_15169850(s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B3040 CURRENT (406) */
void func_151B3040(s32 arg0, s32 arg1, u8 arg2) {
    s32 first = arg0 + 0x150;

    func_15169850(arg1, (s32)arg2, first, arg0 + 0x154, arg0);
    func_15169850(arg1, (s32)arg2, first + 0x14, first + 0x18, arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B3040 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E04F0/func_151B3040.s")
