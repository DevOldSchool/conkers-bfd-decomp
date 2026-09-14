#include "types.h"

/*
 * Reviewed source unit: src/game/game_33130.c
 * Boundary evidence: docs/evidence/game_330E0_33460.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15005C80
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game33130State {
    u8 pad0[0x2C];
    s32 field_2C;
    u8 pad30[0x54];
    u32 field_84;
    u8 pad88[0xAC];
    s32 field_134;
    u8 pad138[0x54];
    f32 field_18C;
    f32 field_190;
    u8 pad194[0x20];
    s16 field_1B4;
    u8 pad1B6[0x2A];
    s16 field_1E0;
    u8 pad1E2[0x5A];
    u8 field_23C;
    u8 pad23D[0x10B];
    f32 field_348;
    f32 field_34C;
    u8 pad350[0x24];
    f32 field_374;
    u8 pad378[0x278];
    u32 field_5F0;
} Game33130State;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15005C80 CURRENT (100) */
void func_15005C80(Game33130State *arg0) {
    arg0->field_2C = 8;
    arg0->field_84 |= 0x01300000;
    arg0->field_1B4 = 1;
    arg0->field_1E0 = 2;
    arg0->field_348 = 117.0f;
    arg0->field_34C = 117.0f;
    arg0->field_190 = 0.0f;
    arg0->field_18C = 0.0f;
    arg0->field_134 = 0;
    arg0->field_5F0 |= 0x10;
    arg0->field_23C = 1;
    arg0->field_374 = 370.0f;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15005C80 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_33130/func_15005C80.s")
void func_15005CF0(s32 arg0) {

}
