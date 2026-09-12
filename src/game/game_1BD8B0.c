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

typedef struct {
    u8 pad_0[0x18];
    s32 field_18;
    u8 field_1C;
} Game1BD8B0State;

typedef struct {
    s32 field_0;
    u8 field_4;
} Game1BD8B0Data;

void func_1516972C(Game1BD8B0State *, Game1BD8B0Data *, u8, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15190400 CURRENT (272) */
void func_15190400(Game1BD8B0State *arg0, Game1BD8B0Data *arg1, s32 arg2) {
    u8 temp_a2;
    u8 temp_a3;

    if (!(arg2 & 0xFF) && ((temp_a2 = arg0->field_1C, temp_a3 = arg1->field_4,
        (arg0->field_18 == arg1->field_0)) || (temp_a3 == temp_a2))) {
        func_1516972C(arg0, arg1, temp_a2, temp_a3);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15190400 */
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
