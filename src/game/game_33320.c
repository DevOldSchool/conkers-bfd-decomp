#include "types.h"

/*
 * Reviewed source unit: src/game/game_33320.c
 * Boundary evidence: docs/evidence/game_330E0_33460.md
 */

typedef struct Game33320State {
    u8 pad0[0x134];
    s32 unk134;
    u8 pad138[0x7C];
    s16 unk1B4;
    u8 pad1B6[0x2A];
    s16 unk1E0;
    u8 pad1E2[0x5A];
    s8 unk23C;
} Game33320State;

void func_15124B18(Game33320State *arg0);

void func_15005E70(Game33320State *arg0) {
    arg0->unk1B4 = 2;
    func_15124B18(arg0);
    arg0->unk23C = 1;
}
void func_15005EA0(Game33320State *arg0) {
    arg0->unk1B4 = 1;
    arg0->unk1E0 = 0xF;
    func_15124B18(arg0);
    arg0->unk134 = 1;
}
