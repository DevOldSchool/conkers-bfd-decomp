#include "types.h"

/*
 * Reviewed source unit: src/game/game_1BD8B0.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15190400
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1BD8B0Inner {
    u8 pad0[0x84];
    s32 field_84;
} Game1BD8B0Inner;

typedef struct Game1BD8B0Object {
    u8 pad0[0x40];
    Game1BD8B0Inner *inner;
} Game1BD8B0Object;

#pragma GLOBAL_ASM("asm/nonmatchings/game_1BD8B0/func_15190400.s")
Game1BD8B0Inner *func_15190454(Game1BD8B0Object *arg0) {
    Game1BD8B0Inner *inner = arg0->inner;

    inner->field_84 = 0;
    return inner;
}
void func_151617C4(Game1BD8B0Object *arg0);

void func_15190464(Game1BD8B0Object *arg0) {
    func_15190454(arg0);
    func_151617C4(arg0);
}
