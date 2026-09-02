#include "types.h"

/*
 * Reviewed source unit: src/game/game_32FC0.c
 * Boundary evidence: docs/evidence/game_32F10_33080.md
 */

typedef struct Game32FC0State {
    u8 pad0[0x84];
    s32 flags84;
    u8 pad88[0x12C];
    s16 unk1B4;
    u8 pad1B6[0x2A];
    s16 unk1E0;
} Game32FC0State;

void func_15124B18(void);

void func_15005B10(Game32FC0State *arg0) {
    arg0->unk1E0 = 8;
    arg0->unk1B4 = 3;
    arg0->flags84 &= ~4;
    func_15124B18();
}
