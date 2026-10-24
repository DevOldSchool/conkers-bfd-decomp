#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_EEE70.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C1A40
 * - func_150C1E34
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameEEE70State {
    u8 pad0[0x1D4];
    void *field_1D4;
} GameEEE70State;

s32 func_150C19C0(void *arg0, GameEEE70State *arg1, u8 arg2) {
    s32 index;

    switch (arg2) {
    case 1:
        index = 0x18;
        break;
    case 2:
        index = 0x15;
        break;
    }
    func_15142314(arg1->field_1D4, index, arg0);
    return 1;
}
s32 func_150C1A2C(s32 arg0, s32 arg1) {
    return 7;
}
typedef struct GameEEE70SpawnPacket {
    f32 scaleX, field04, scaleY, scaleZ;
    Vec3f rotation;
    Vec3f stretch;
    Vec3f position;
    Vec3f velocity;
    Vec3f angularVelocity;
    f32 field4C;
    s32 flags;
    s16 lifetime, type;
    u8 field58;
    u8 pad59[3];
    s32 field5C;
    u8 color0, color1, color2, color3, color4;
    u8 color5, color6, color7, color8;
    u8 pad69;
    u8 field6A;
    u8 pad6B;
    GameEEE70State *owner;
    u8 layer;
    u8 pad71;
    s16 field72, field74;
    u8 pad76[2];
} GameEEE70SpawnPacket;

void *func_15132A4C(void *, s32, s32, s32, u8, s32);
void func_1514C2F0(f32, f32, f32, f32, u8, s8, s16, u8, s32, f32, s32, u8);
f32 func_150ADA68(void);
extern f32 D_800A0210, D_800A0214, D_800A0218;
extern f32 D_800A021C, D_800A0220;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C1A40 CURRENT (340) */
void func_150C1A40(GameEEE70State *arg0, s32 arg1, s32 arg2) {
    Vec3f position;
    f32 average;
    f32 radius;
    GameEEE70SpawnPacket packet;
    f32 speed;
    f32 cosine;
    f32 sine;
    f32 size;
    f32 base;
    f32 spread;
    s32 direction;
    void *result;

    if (arg0->field_1D4 != NULL) {
        average = (*(f32 *)((u8 *)arg0 + 0x150) + *(f32 *)((u8 *)arg0 + 0x14C)) * 0.5f;
        func_150C19C0(&position, arg0, arg1);
        arg2 = ((s32)*(u16 *)((u8 *)arg0 + 0x76) >> 8) + 0x40;
        arg2 &= 0xFF;
        radius = average * 70.0f;
        func_1514C2F0(position.x, *(f32 *)((u8 *)arg0 + 0x180), position.z,
                      radius, arg2, arg1 == 1 ? 0x10 : -0x10, 8, 0, 0, radius * D_800A0210, 0, 0xFF);
        func_15165F80(-1, (s32)position.x,
                      (s32)((f32)(s32)*(f32 *)((u8 *)arg0 + 0x180) + 2.0f),
                      (s32)position.z, 8, 0x15, 0, 0xFF, 0);
        packet.type = 5;
        packet.flags = 0x29E9;
        packet.field58 = 0;
        packet.field5C = 0;
        packet.color0 = 0xFF;
        packet.color1 = 1;
        packet.color2 = 0;
        packet.color3 = 0;
        packet.color4 = 0;
        packet.color5 = 0;
        packet.color6 = 0;
        packet.color7 = 0;
        packet.color8 = 0;
        packet.field6A = 1;
        packet.owner = arg0;
        packet.stretch.x = 1.0f;
        packet.stretch.y = 1.0f;
        packet.stretch.z = 1.0f;
        packet.field04 = D_800A0214;
        packet.angularVelocity.z = 0.0f;
        packet.field4C = D_800A0218;
        packet.layer = arg0->pad0[0x3B];
        packet.field72 = 0x10;
        packet.field74 = 0xF;
        arg2 = (func_150ADA20() & 7) + 5;
        direction = arg2 - 1;
        if (arg2 != 0) {
            base = D_800A021C;
            spread = D_800A0220;
            do {
                arg1 = (u8)func_150ADA20();
                speed = (func_150ADA68() * spread + base) * 9.0f * average;
                cosine = func_151423D8(arg1 - 0x40);
                sine = func_151423D8(arg1);
                packet.lifetime = (func_150ADA20() & 0xF) + 0x1E;
                packet.position.x = radius * cosine + position.x;
                packet.position.y = *(f32 *)((u8 *)arg0 + 0x180) + 2.0f;
                packet.position.z = radius * sine + position.z;
                packet.velocity.x = speed * cosine;
                packet.velocity.y = 2.0f * speed;
                packet.velocity.z = speed * sine;
                size = (func_150ADA68() * spread + base) * average * 1.5f;
                packet.scaleY = size;
                packet.scaleZ = size;
                packet.scaleX = size;
                packet.rotation.x = func_150ADA68() * 360.0f;
                packet.rotation.y = func_150ADA68() * 360.0f;
                packet.rotation.z = func_150ADA68() * 360.0f;
                packet.angularVelocity.x = 25.0f - func_150ADA68() * 50.0f;
                packet.angularVelocity.y = 25.0f - func_150ADA68() * 50.0f;
                result = func_15132A4C(&packet, 3, 0xFF, 4, 0xFF, 0);
                if (result != NULL) {
                    *(f32 *)((u8 *)result + 0x170) = *(f32 *)((u8 *)arg0 + 0x180);
                }
            } while (direction--);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C1A40 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EEE70/func_150C1A40.s")

void func_151429E0(u8, u8 *, u8 *, u8 *);
void func_1518CA80();
extern f64 D_800A0228;

typedef struct GameEEE70EffectPacket {
    f32 position[3];
    u8 pad0C[0xA];
    s16 values[9];
    u8 colors[10];
} GameEEE70EffectPacket;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C1E34 CURRENT (3641) */
s32 func_150C1E34(s32 arg0, s32 arg1, f32 arg2, f32 arg3,
                   f32 arg4, f32 arg5, f32 arg6, f32 arg7,
                   f32 arg8, f32 arg9, f32 arg10, f32 arg11, f32 arg12) {
    GameEEE70EffectPacket packet;
    s32 integer;
    s32 scaled;

    packet.position[2] = arg4;
    packet.position[0] = arg2;
    packet.position[1] = arg3;
    packet.values[6] = 0x96;
    packet.values[8] = 0x258;
    integer = (s32)arg12;
    packet.values[4] = (s32)((arg2 - arg5) * 10.0f);
    packet.values[7] = 0x14;
    packet.values[5] = (s32)((arg4 - arg7) * 10.0f);
    packet.values[0] = integer;
    scaled = (s32)((f64)arg12 * D_800A0228);
    packet.values[1] = integer;
    packet.values[3] = scaled;
    packet.values[2] = scaled;
    func_151429E0(0, &packet.colors[0], &packet.colors[1], &packet.colors[2]);
    func_151429E0(0, &packet.colors[3], &packet.colors[4], &packet.colors[5]);
    packet.colors[6] = 0xFF;
    packet.colors[7] = 0xFF;
    packet.colors[8] = (func_150ADA20() & 0xF) + 0xC;
    packet.colors[9] = 1;
    func_1518CA80(&packet, 1);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C1E34 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EEE70/func_150C1E34.s")
