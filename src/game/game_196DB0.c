#include "types.h"

/*
 * Reviewed source unit: src/game/game_196DB0.c
 * Boundary evidence: docs/evidence/game_raw_radial_queue_render_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15169988
 * - func_15169A48
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game196DB0Effect {
    u8 pad0[0x10];
    u8 payload[0x3C];
} Game196DB0Effect;

Game196DB0Effect *func_15167A68(s32, s32, s32, s32, s32, s32);
void func_10023A10(void *, void *, s32);

Game196DB0Effect *func_15169900(void *arg0, s32 arg1) {
    Game196DB0Effect *effect;

    effect = func_15167A68(0x5E, 0, 0x4C, 0, arg1, 1);
    if (effect != 0) {
        func_10023A10(arg0, effect->payload, sizeof(effect->payload));
    }
    return effect;
}

void func_15169968(void *arg0) {
    func_15169900(arg0, 0xFF);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_196DB0/func_15169988.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_196DB0/func_15169A48.s")
