#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1355D0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_direct_call_singletons.md
 */

struct Blood36C3CActor;
void func_15136C3C(struct Blood36C3CActor *, u8, u8, u8, u8, u8, u8, s32);
void func_15152190(void *, void *, void *, s32, f32, s32, s32, s32);
void func_150E83AC(void *, s16, u8, s32);
extern u8 D_800A2430;
extern u8 D_800A2434;

typedef struct Game1355D0Packet {
    s32 field00;
    s32 field04;
    Vec3f position;
    s16 field14;
    s16 field16;
    s16 field18;
    s16 field1A;
    f32 field1C;
    f32 field20;
    f32 field24;
    f32 field28;
    s16 field2C;
    s16 field2E;
    f32 field30;
    f32 field34;
    f32 field38;
} Game1355D0Packet;

void func_15108120(void *arg0, u8 arg1, s32 arg2) {
    Vec3f target;
    Vec3f source;
    Game1355D0Packet packet;

    {
        s16 r;

        target.x = *(f32 *)((u8 *)arg0 + 0x14);
        target.y = *(f32 *)((u8 *)arg0 + 0x18);
        target.z = *(f32 *)((u8 *)arg0 + 0x1C);
        source.x = *(f32 *)((u8 *)arg0 + 0x14);
        source.y = *(f32 *)((u8 *)arg0 + 0x18) + 30.0f;
        source.z = *(f32 *)((u8 *)arg0 + 0x1C);
        r = (func_150ADA20() % 201U) + 0x1F4;
        func_150E83AC(&target, r, arg1, arg2);
    }
    packet.field00 = 0xF;
    packet.field04 = 8;
    packet.position = source;
    packet.field14 = 0;
    packet.field16 = 0xFF;
    packet.field18 = -0x40;
    packet.field1A = 0x29;
    packet.field2C = 0x27;
    packet.field2E = 0x14;
    packet.field30 = 0.305f;
    packet.field34 = 0.305f;
    packet.field1C = 8.0f;
    packet.field20 = 10.0f;
    packet.field24 = -0.8f;
    packet.field28 = 0.344f;
    packet.field38 = 26.411001f;
    func_15152190(&packet, &D_800A2430, &D_800A2434, 1, 40.0f, 0, arg1, arg2);
    func_15136C3C(arg0, 1, 1, 1, 0, 0, arg1, arg2);
}
