#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_E8090.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150BAFEC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameBABE0Packet {
    s32 field_0;
    s16 field_4;
    u8 field_6;
    u8 field_7;
    s32 field_8;
    s32 field_C;
    u8 field_10;
    u8 field_11;
    u8 field_12;
    u8 field_13;
    u8 field_14;
    u8 field_15;
    u8 field_16;
    u8 field_17;
    s32 field_18;
    s32 field_1C;
    u8 field_20;
    u8 pad21[7];
} GameBABE0Packet;
u8 func_15143E94(s32, s32);
void func_1514C678(f32, f32, f32, f32, s32, s32, s32, s32, s32, f32, s32, u8);
f32 func_150ADA68(void);
s32 func_15046C80(f32 *, u16, f32, void *);
void func_1504715C(void *, void *);
s32 func_1518ABD0(void *, void *, u8);
extern void *D_80088750;
extern s32 D_80082FA4;
extern f32 D_8009FE70;
extern struct108 *D_800DBFF0;

void func_150BABE0(u8 *arg0, u8 arg1, u8 arg2) {
    f32 position[3];
    s32 type;
    s32 angle;
    Game71820Hit hit;
    f32 probe[3];
    GameBABE0Packet packet;
    void *created;
    f32 scale;

    angle = (s32)(D_800DBFF0[D_80082FA4].unk380 * D_8009FE70);
    if (arg0 == NULL) {
        return;
    }
    if (*(s32 *)arg0 == 0 || *(s32 *)arg0 == 8) {
        return;
    }
    if (*(s32 *)(arg0 + 0x1D4) == 0) {
        return;
    }
    switch (arg1) {
    case 0:
        type = 0x11;
        break;
    case 1:
        type = 0x1A;
        break;
    }
    func_15142314((void *)*(s32 *)(arg0 + 0x1D4), type, position);
    position[1] = *(f32 *)(arg0 + 0x180);
    func_15143E94(5, 0x4022);
    func_15165F80(-1, (s32)position[0], (s32)(position[1] + 6.0f),
                 (s32)position[2], 0x19, 0x12, 0, arg2, 1);
    func_1514C678(position[0], position[1], position[2], func_150ADA68() * 50.0f + 40.0f,
                 (s16)(angle + 0x3C), (s16)(angle - 0x3C), (func_150ADA20() % 11U) + 0x1E, 5, 0, 0.0f, 0, arg2);
    func_1504715C(&hit, arg0);
    probe[0] = position[0];
    probe[1] = position[1] + 100.0f;
    probe[2] = position[2];
    if (func_15046C80(probe, 0, position[1] - 100.0f, &hit) != 0) {
        scale = func_150ADA68() * 200.0f + 200.0f;
        packet.field_6 = 0x2A;
        packet.field_7 = 0;
        packet.field_0 = 0x7340;
        packet.field_4 = 0x12C;
        packet.field_8 = 0;
        packet.field_C = (func_150ADA20() % 2001U) + 0x7D0;
        packet.field_10 = 0xFF;
        packet.field_11 = 0xFF;
        packet.field_12 = 0;
        packet.field_13 = 0;
        packet.field_14 = 0;
        packet.field_15 = 0xFF;
        packet.field_16 = 0;
        packet.field_17 = 0xD;
        packet.field_20 = 0xFF;
        packet.field_1C = 0;
        packet.field_18 = 0x170002;
        created = func_1513C73C((s32)&packet, 0, 0, (s32)&hit.points[0],
                                position[0], hit.height, position[2], scale, scale,
                                func_150ADA20() & 0xFF, (func_150ADA20() & 1) * 2 + (func_150ADA20() & 1),
                                4, arg2, 0);
        if (created != NULL) {
            if (func_1518ABD0(D_80088750, created, 1) == 0) {
                func_1516972C(created);
            }
        }
    }
    func_1514C678(position[0], position[1], position[2], func_150ADA68() * 40.0f + 60.0f,
                 (s16)(angle + 0x3C), (s16)(angle - 0x3C), (func_150ADA20() % 7U) + 6, 6, 0, 0.0f, 0, arg2);
}
typedef struct GameBAFECPacket {
    u32 flags;
    u32 owner;
    s16 kind;
    s16 lifetime;
    u32 wordC;
    u32 word10;
    u8 color0[4];
    u8 color1[4];
    u8 mode;
    u8 effect;
    s16 width;
    s16 height;
    s16 count;
    f32 factor;
    f32 scale[2];
    f32 position[3];
    u8 pad3C[0xC];
    f32 velocity[3];
    f32 zero;
    u32 motion;
    u8 pad5C[4];
    s8 dimensions[4];
} GameBAFECPacket;
typedef union GameBAFECAngle { s16 value; u8 byte[2]; } GameBAFECAngle;
void *func_10022EC0(void *, const void *, u32);
void *func_15130374(s32, u8, s32, u8, s32);
f32 func_150ADA68(void);
extern f32 D_8009FE74;
extern f32 D_8009FE78;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150BAFEC CURRENT (2488) */
s32 func_150BAFEC(s32 volatile arg0, s32 volatile arg1, f32 volatile arg2,
    f32 volatile arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7,
    s32 arg8, s32 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14) {
    GameBAFECPacket packet;
    f32 extra;
    GameBAFECAngle angle;
    s32 angle_value;
    f32 cosine;
    f32 sine;
    f32 angle_cosine;
    f32 angle_sine;
    f32 speed;
    f32 horizontal;
    void *created;

    cosine = func_151423D8((arg8 - 0x40) & 0xFF);
    sine = func_151423D8((u8)arg8);
    packet.effect = 0x29;
    packet.kind = 0xE03;
    packet.flags = 0x200005;
    packet.owner = 0;
    packet.lifetime = (func_150ADA20() % 36U) + 0x46;
    packet.wordC = 0;
    packet.word10 = 0;
    packet.color1[0] = 0xB0;
    packet.color1[1] = 0xA0;
    packet.color1[2] = 0x2A;
    packet.color0[0] = 0x40;
    packet.color0[1] = 0xB;
    packet.color0[2] = 0x6A;
    packet.color0[3] = 0xFF;
    packet.color1[3] = (func_150ADA20() % 52U) + 0x5A;
    packet.mode = 0xFF;
    packet.dimensions[0] = 3;
    packet.dimensions[1] = 3;
    speed = func_150ADA68() * 165.0f;
    packet.position[0] = arg2;
    packet.position[1] = arg3;
    packet.position[2] = arg4;
    speed += 800.0f;
    packet.scale[0] = speed;
    packet.scale[1] = speed;
    angle_value = (func_150ADA20() % 11U) - 0xC;
    angle.value = angle_value;
    angle_cosine = func_151423D8((angle_value - 0x40) & 0xFF);
    angle_sine = func_151423D8(*(volatile u8 *)&angle.byte[1]);
    speed = func_150ADA68() * 11.0f;
    packet.motion = 0xE05;
    speed += 15.0f;
    horizontal = speed * angle_sine;
    packet.velocity[0] = horizontal * cosine;
    packet.velocity[1] = -speed * angle_cosine;
    packet.zero = 0.0f;
    packet.velocity[2] = horizontal * sine;
    if (func_150ADA20() & 1) packet.motion |= 0x40;
    if (func_150ADA20() & 1) packet.motion |= 0x80;
    packet.dimensions[2] = 2;
    packet.dimensions[3] = -1;
    packet.width = 0x16;
    packet.height = 0xB;
    packet.count = 1;
    packet.factor = D_8009FE74;
    extra = D_8009FE78;
    created = func_15130374((s32)&packet, 0, 4, arg14, 1);
    if (created != 0) func_10022EC0((u8 *)created + 0xA8, &extra, 4);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150BAFEC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E8090/func_150BAFEC.s")
