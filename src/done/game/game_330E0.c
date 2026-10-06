#include "types.h"

/*
 * Reviewed source unit: src/game/game_330E0.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_330E0_33460.md
 */

typedef struct Game330E0State {
    u8 pad0[0x84];
    s32 unk84;
    u8 pad88[0x12C];
    s16 unk1B4;
    u8 pad1B6[0x2A];
    s16 unk1E0;
} Game330E0State;

void func_15124B18(void *arg0);

void func_15005C30(Game330E0State *arg0) {
    arg0->unk84 |= 0x100000;
    *(volatile s32 *)&arg0->unk84 = arg0->unk84 & ~4;
    arg0->unk1B4 = 2;
    arg0->unk1E0 = 5;
    func_15124B18(arg0);
}
