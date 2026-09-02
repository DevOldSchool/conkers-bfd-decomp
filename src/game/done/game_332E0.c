#include "types.h"

/*
 * Reviewed source unit: src/game/game_332E0.c
 * Boundary evidence: docs/evidence/game_330E0_33460.md
 */

typedef struct Game332E0State {
    u8 pad0[0x1B4];
    s16 unk1B4;
    u8 pad1B6[0x2A];
    s16 unk1E0;
} Game332E0State;

void func_15124B18(void);
extern s32 D_800BE9F0;

void func_15005E30(Game332E0State *arg0) {
    if (D_800BE9F0 == 0x32) {
        arg0->unk1B4 = 2;
        arg0->unk1E0 = 4;
        func_15124B18();
    }
}
