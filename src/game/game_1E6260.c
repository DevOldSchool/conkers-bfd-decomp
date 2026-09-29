#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E6260.c
 * Boundary evidence: docs/evidence/game_raw_isolated_selectors_and_calls.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B8DB0
 * - func_151B9214
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E6260/func_151B8DB0.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800AA564;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B9214 CURRENT (293) */
s32 func_151B9214(u8 *arg0) {
    u8 *volatile saved;
    f32 timer;
    f32 value;
    f32 amplitude;
    u8 *state;

    *(f32 *)(arg0 + 0x178) += *(f32 *)(arg0 + 0x17C) * D_800BE9A4;
    value = func_15144B68(*(f32 *)(arg0 + 0x178));
    state = arg0 + 0x170;
    *(f32 *)(state + 8) = value;
    saved = state;
    value = func_15047D60(value);
    state = saved;
    amplitude = *(f32 *)(state + 4);
    timer = *(f32 *)(state + 0x18);
    *(f32 *)state = value * amplitude;
    if (timer > 0.0f) {
        *(f32 *)(state + 0x18) = timer - D_800BE9A4;
        *(f32 *)(state + 0xC) += *(f32 *)(state + 0x20) * D_800BE9A4;
        *(f32 *)(state + 4) = *(f32 *)(state + 0x1C) * D_800BE9A4 + amplitude;
    } else {
        value = *(f32 *)(state + 0xC);
        timer = D_800AA564;
        *(f32 *)(state + 0xC) = (*(f32 *)(state + 0x14) - value) * timer + value;
        *(f32 *)(state + 4) = (*(f32 *)(state + 0x10) - amplitude) * timer + amplitude;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B9214 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E6260/func_151B9214.s")
