#include "types.h"

/*
 * Reviewed source unit: src/game/game_126ED0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_final.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F9A20
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game126ED0State {
    u8 pad0[0x84];
    volatile u32 flags;
    u8 pad88[0x108];
    f32 field190;
} Game126ED0State;

s32 func_1509BE40(s32, ...);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F9A20 CURRENT (75) */
void func_150F9A20(Game126ED0State *arg0) {
    s32 temp_t0;
    s32 temp_t1;
    s32 temp_t6;
    s32 temp_t7;

    if (func_1509BE40(1, 0x4025, 6, 0x2000) != 0) {
        temp_t6 = arg0->flags;
        temp_t7 = temp_t6 | 0x80;
        arg0->flags = temp_t7;
        arg0->flags = temp_t7 & ~8;
        arg0->field190 = 85.0f;
        return;
    }
    temp_t0 = arg0->flags;
    temp_t1 = temp_t0 & ~0x80;
    arg0->flags = temp_t1;
    arg0->flags = temp_t1 | 8;
    arg0->field190 = 0.0f;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F9A20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_126ED0/func_150F9A20.s")
