#include "types.h"

/*
 * Reviewed source unit: src/game/game_333D0.c
 * Boundary evidence: docs/evidence/game_330E0_33460.md
 */

typedef struct Game333D0State {
    u8 pad0[0x134];
    s32 unk134;
    u8 pad138[0x7C];
    s16 unk1B4;
    u8 pad1B6[0x2A];
    s16 unk1E0;
} Game333D0State;

void func_15124B18(void);

void func_15005F20(Game333D0State *arg0) {
    arg0->unk1B4 = 3;
    arg0->unk1E0 = 0xF;
    func_15124B18();
    arg0->unk134 = 1;
}
