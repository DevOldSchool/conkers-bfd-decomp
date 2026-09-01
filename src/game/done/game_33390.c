#include "types.h"

/*
 * Reviewed source unit: src/game/game_33390.c
 * Boundary evidence: docs/evidence/game_330E0_33460.md
 */

typedef struct Game33390State {
    u8 pad0[0x134];
    s32 unk134;
    u8 pad138[0x7C];
    s16 unk1B4;
    u8 pad1B6[0x2A];
    s16 unk1E0;
} Game33390State;

void func_15124B18(void);

void func_15005EE0(Game33390State *arg0) {
    arg0->unk1B4 = 2;
    arg0->unk1E0 = 0xF;
    func_15124B18();
    arg0->unk134 = 1;
}
