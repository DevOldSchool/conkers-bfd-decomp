#include "types.h"

/*
 * Reviewed source unit: src/game/game_A9820.c
 * Boundary evidence: docs/evidence/game_raw_direct_helper_pairs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1507C3E0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameA9820Nested {
    u8 pad0[0x114];
    s16 field_114;
    s16 field_116;
    s16 field_118;
} GameA9820Nested;

typedef struct GameA9820Actor {
    u8 pad0[0x31C];
    GameA9820Nested *nested;
    u8 pad320[0xC];
} GameA9820Actor;

extern s8 D_8008FD8C;
extern GameA9820Actor D_800CC2D0[];

void func_1507C3E0(GameA9820Actor *, s16 *, s16 *, s16 *);

void func_1507C370(void) {
    GameA9820Actor *actor;
    GameA9820Nested *nested;
    s32 index;

    actor = D_800CC2D0;
    index = 0;
    if (D_8008FD8C > 0) {
        do {
            nested = actor->nested;
            if (nested != 0) {
                func_1507C3E0(actor, &nested->field_114, &nested->field_116,
                              &nested->field_118);
            }
            index++;
            actor++;
        } while (index < D_8008FD8C);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9820/func_1507C3E0.s")
