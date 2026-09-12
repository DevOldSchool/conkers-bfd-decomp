#include "types.h"

/*
 * Reviewed source unit: src/game/game_330E0.c
 * Boundary evidence: docs/evidence/game_330E0_33460.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15005C30
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game330E0State {
    u8 pad0[0x84];
    s32 unk84;
    u8 pad88[0x12C];
    s16 unk1B4;
    u8 pad1B6[0x2A];
    s16 unk1E0;
} Game330E0State;

void func_15124B18(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15005C30 CURRENT (55) */
void func_15005C30(Game330E0State *arg0) {
    s32 temp_t6;
    s32 temp_t7;
    s32 temp_t9;

    temp_t6 = arg0->unk84;
    temp_t7 = temp_t6 | 0x100000;
    *(volatile s32 *)&arg0->unk84 = temp_t7;
    temp_t9 = temp_t7 & ~4;
    arg0->unk84 = temp_t9;
    arg0->unk1B4 = 2;
    arg0->unk1E0 = 5;
    func_15124B18();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15005C30 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_330E0/func_15005C30.s")
