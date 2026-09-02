#include "types.h"

/*
 * Reviewed source unit: src/game/game_129EB0.c
 * Boundary evidence: docs/evidence/game_remaining_units_up_to_64_bytes.md
 */

typedef struct Game129EB0State {
    u8 pad0[0x348];
    f32 unk348;
    f32 unk34C;
    u8 pad1[0x24];
    f32 unk374;
} Game129EB0State;

void func_150FCA00(Game129EB0State *arg0) {
    arg0->unk348 = 500.0f;
    arg0->unk34C = 500.0f;
    arg0->unk374 = 800.0f;
}
