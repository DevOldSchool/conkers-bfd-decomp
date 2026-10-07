#include "types.h"

/*
 * Reviewed source unit: src/game/game_33260.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_330E0_33460.md
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

void func_15005DB0(Game33260Object *arg0) {
    func_15123934(arg0, 8, 0, arg0->field_134, 3);
    arg0->field_73C = 0;
    *(s32 *)((u8 *)arg0 + 0x84) |= 0x01000000;
    arg0->flags = *(s32 *)((u8 *)arg0 + 0x84) & ~4;
    arg0->field_348 = 500.0f;
    arg0->field_34C = 500.0f;
    arg0->field_374 = 800.0f;
}
