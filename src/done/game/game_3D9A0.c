#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_3D9A0.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_compact_multi_function_units.md
 */

extern u8 D_800D9950[];
extern s8 D_80088980;

void func_150104F0(void) {
    typedef struct {
        u8 unk[3];
    } Col;
    Col *c = (Col *)&D_800D9950;

    c->unk[0] = c->unk[1] = c->unk[2] = 0;
    *(f32 *)((u8 *)func_151149AC(0xF6) + 0x7C) = 2.0f;
    D_80088980 = 0;
}

void *func_10022EC0(void *, const void *, u32);

typedef struct Game3D9A0Packet {
    void *owner;
    u8 type;
    u8 pad5;
    s16 x;
    s16 y;
    s16 z;
} Game3D9A0Packet;

void func_15010538(void *arg0) {
    func_15161E24(arg0, 2, 2, 0x12C, 0x1E, 0x64, 0xC8, 0xFF, 0xFF, 1);
    {
        Game3D9A0Packet packet;
        u8 *object;

        packet.owner = arg0;
        packet.type = ((u8 *)packet.owner)[0x3B];
        packet.x = 0;
        packet.y = 0;
        packet.z = 0;
        object = func_15149130(0x12C, -1, 0x50, -1, 0, 0x3D, 0xC, 0xFF, 1);
        if (object != 0) {
            func_10022EC0(object + 0x28, &packet, sizeof(packet));
        }
    }
}

extern s8 D_800D9920;
extern s8 D_800D9921;
extern u8 D_800D9928[];
extern u8 D_800D9938[];

void func_15010600(void) {
    s32 i;

    D_800D9921 = 0;
    D_800D9920 = 0;
    for (i = 0; i < 14; i++) {
        D_800D9928[i] = 0;
        D_800D9938[i] = 0;
    }
}
