#include "types.h"

/*
 * Reviewed source unit: src/game/game_33620.c
 * Boundary evidence: docs/evidence/game_remaining_units_up_to_64_bytes.md
 */

typedef struct Game33620State {
    u8 pad0[0x84];
    s32 flags84;
    u8 pad88[0x12C];
    s16 unk1B4;
    u8 pad1B6[0x2A];
    s16 unk1E0;
} Game33620State;

void func_15124B18(void);

void func_15006170(Game33620State *arg0) {
    arg0->unk1E0 = 5;
    arg0->unk1B4 = 2;
    func_15124B18();
    arg0->flags84 |= 0x4000;
}
