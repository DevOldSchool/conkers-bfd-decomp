#include "types.h"

/*
 * Reviewed source unit: src/game/game_33210.c
 * Boundary evidence: docs/evidence/game_330E0_33460.md
 */

typedef struct Game33210State {
    u8 pad0[0x84];
    s32 flags84;
    u8 pad88[0xAC];
    s32 unk134;
    u8 pad138[0x7C];
    s16 unk1B4;
    u8 pad1B6[0x2A];
    s16 unk1E0;
} Game33210State;

void func_15124B18(void);

void func_15005D60(Game33210State *arg0) {
    arg0->unk1B4 = 2;
    arg0->unk1E0 = 5;
    func_15124B18();
    arg0->unk134 = 0;
    arg0->flags84 |= 0x4000;
}
void func_15005DA0(s32 arg0) {

}
