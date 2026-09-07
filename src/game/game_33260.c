#include "types.h"

/*
 * Reviewed source unit: src/game/game_33260.c
 * Boundary evidence: docs/evidence/game_330E0_33460.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15005DB0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game33260Object {
    u8 pad0[0x84];
    volatile s32 flags;
    u8 pad88[0xAC];
    s32 field_134;
    u8 pad138[0x210];
    f32 field_348;
    f32 field_34C;
    u8 pad350[0x24];
    f32 field_374;
    u8 pad378[0x3C4];
    s16 field_73C;
} Game33260Object;

void func_15123934(Game33260Object *, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15005DB0 CURRENT (35) */
void func_15005DB0(Game33260Object *arg0) {
    s32 temp_t7;
    s32 temp_t8;
    s32 temp_t0;

    func_15123934(arg0, 8, 0, arg0->field_134, 3);
    arg0->field_73C = 0;
    temp_t7 = arg0->flags;
    temp_t8 = temp_t7 | 0x01000000;
    temp_t0 = temp_t8 & ~4;
    arg0->flags = temp_t8;
    arg0->flags = temp_t0;
    arg0->field_348 = 500.0f;
    arg0->field_34C = 500.0f;
    arg0->field_374 = 800.0f;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15005DB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_33260/func_15005DB0.s")
