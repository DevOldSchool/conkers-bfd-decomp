#include "types.h"

/*
 * Reviewed source unit: src/game/game_32F60.c
 * Boundary evidence: docs/evidence/game_32F10_33080.md
 */

typedef struct Game32F60State {
    u8 pad0[0x84];
    s32 flags84;
    u8 pad88[0x12C];
    s16 unk1B4;
    u8 pad1B6[0x2A];
    s16 unk1E0;
    u8 pad1E2[0x166];
    f32 unk348;
    f32 unk34C;
    u8 pad350[0x24];
    f32 unk374;
} Game32F60State;

void func_15005AB0(Game32F60State *arg0) {
    arg0->unk1B4 = 1;
    arg0->unk1E0 = 3;
    arg0->unk348 = 230.0f;
    arg0->unk34C = 230.0f;
    arg0->flags84 |= 0x4000;
    arg0->unk374 = 290.0f;
}
void func_15005AF0(s32 arg0) {

}
