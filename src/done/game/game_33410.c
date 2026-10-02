#include "types.h"

/*
 * Reviewed source unit: src/game/game_33410.c
 * Boundary evidence: docs/evidence/game_330E0_33460.md
 */

typedef struct Game33410State {
    u8 pad0[0x84];
    s32 flags84;
    u8 pad88[0x12C];
    s16 unk1B4;
} Game33410State;

void func_15124B18(void);

void func_15005F60(Game33410State *arg0) {
    arg0->unk1B4 = 2;
    func_15124B18();
    arg0->flags84 |= 0x4000;
}
