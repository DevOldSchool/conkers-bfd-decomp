#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E6260.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_isolated_selectors_and_calls.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B8DB0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E6260/func_151B8DB0.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800BE9A4;

typedef struct {
    f32 out;
    f32 amp;
    f32 phase;
    f32 speed;
    f32 targetAmp;
    f32 targetSpeed;
    f32 timer;
    f32 ampRate;
    f32 speedRate;
} Osc151B9214;

s32 func_151B9214(u8 *arg0) {
    Osc151B9214 *s;

    s = (Osc151B9214 *)(arg0 + 0x170);
    s->phase += s->speed * D_800BE9A4;
    s->phase = func_15144B68(s->phase);
    s->out = func_15047D60(s->phase) * s->amp;
    if (s->timer > 0.0f) {
        s->timer -= D_800BE9A4;
        s->speed += s->speedRate * D_800BE9A4;
        s->amp = s->amp + s->ampRate * D_800BE9A4;
    } else {
        s->speed += (s->targetSpeed - s->speed) * 0.0234f;
        s->amp += (s->targetAmp - s->amp) * 0.0234f;
    }
    return 1;
}
