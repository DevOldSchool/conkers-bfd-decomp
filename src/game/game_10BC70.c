#include "types.h"

/*
 * Reviewed source unit: src/game/game_10BC70.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150DEB58
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game10BC70Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Game10BC70Vec3;

typedef union Game10BC70Pair {
    s32 value[2];
    f32 f[2];
} Game10BC70Pair;

typedef struct Game10BC70SpawnPacket {
    u8 field0;
    s8 field1;
    s16 field2;
    s16 field4;
    u8 pad6[2];
    s32 field8;
    s32 fieldC;
    u8 colour[4];
    f32 scale[2];
    Game10BC70Vec3 position;
    Game10BC70Vec3 rotation;
    f32 size[3];
    s32 field40;
    u8 field44;
    u8 field45;
    u8 field46;
    u8 field47;
    s32 field48;
    u8 field4C;
    u8 pad4D[3];
    s32 field50;
    s16 field54;
    s16 field56;
} Game10BC70SpawnPacket;

typedef struct Game10BC70Motion {
    Game10BC70Vec3 velocity;
    f32 duration;
    Game10BC70Vec3 side;
    Game10BC70Vec3 forward;
} Game10BC70Motion;

typedef struct Game10BC70Link {
    s16 timer;
    u8 pad2[2];
    s32 source;
    s32 target;
} Game10BC70Link;

typedef struct Game10BC70Emitter {
    u8 pad0;
    u8 flags01;
    u8 pad2[0xA];
    u8 flags0C;
    u8 padD[0x1B];
    Game10BC70Link link;
} Game10BC70Emitter;

void *func_10022EC0(void *, const void *, u32);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
void *func_1513D2F0(s32, s32, u8, u8, u8, u8, u8, s32, s32, s32, u8, s32);
void func_1514470C(s32, void *);
s32 func_15145128(f32 *, f32 *, f32 *, f32 *);
extern Game10BC70Pair D_800A0D00;
extern f32 D_800A0D58;
extern u8 D_800A4AA0;
extern Game10BC70Vec3 D_800A5480;
extern s32 D_800BE9E4;

void func_150DE7C0(Game10BC70Emitter *arg0) {
    Game10BC70Link *link;
    Game10BC70Vec3 target;
    Game10BC70Vec3 delta;
    f32 length;
    f32 unused;
    f32 base;
    Game10BC70Motion motion;
    Game10BC70SpawnPacket packet;
    Game10BC70Pair kinds;
    void *result;
    f32 speed;

    link = &arg0->link;
    link->timer -= D_800BE9E4;
    if (link->timer < 0) {
        kinds = D_800A0D00;
        packet.field0 = *(kinds.value + (func_150ADA20() & 1));
        func_1514470C(link->source, &packet.position);
        func_1514470C(link->target, &target);
        delta.x = target.x - packet.position.x;
        delta.y = target.y - packet.position.y;
        delta.z = target.z - packet.position.z;
        func_15145128(&delta.x, &motion.velocity.x, &length, &unused);
        speed = (func_150ADA68() * 30.0f) + 25.0f;
        base = speed;
        if (packet.field0 == 0xBF) {
            speed = base * D_800A0D58;
        }
        motion.velocity.x *= speed;
        motion.velocity.y *= speed;
        motion.velocity.z *= speed;
        motion.duration = length / speed;
        motion.forward.x = delta.x;
        motion.forward.y = 0.0f;
        motion.forward.z = delta.z;
        func_15145128(&motion.forward.x, &motion.forward.x, 0, 0);
        motion.side.x = -motion.forward.z;
        motion.side.y = 0.0f;
        motion.side.z = motion.forward.x;
        packet.rotation = D_800A5480;
        packet.field1 = 0;
        packet.field2 = 0x3B03;
        packet.field4 = 0x12C;
        packet.field8 = 0;
        packet.fieldC = 0;
        packet.colour[0] = 0xFF;
        packet.colour[1] = 0xFF;
        packet.colour[2] = 0xFF;
        packet.colour[3] = 0xFF;
        func_150ADA68();
        packet.scale[1] = 706.0f;
        packet.scale[0] = 706.0f;
        packet.rotation = D_800A5480;
        packet.field40 = 0x065C0000;
        packet.field44 = 0xFF;
        packet.field45 = 0xFF;
        packet.field46 = 0;
        packet.field47 = 7;
        packet.field48 = 0;
        packet.field4C = 0xFF;
        packet.field50 = 0;
        packet.field54 = 1;
        packet.field56 = 0xFF;
        packet.size[0] = 1.0f;
        packet.size[1] = 1.0f;
        packet.size[2] = 1.0f;
        result = func_1513D2F0((s32)&packet, (s32)&D_800A4AA0, 0x28, 0, 0,
                               0x26, 0, 3, 0xFF, 0x28, arg0->flags0C, arg0->flags01);
        if (result != 0) {
            func_10022EC0((u8 *)result + 0x110, &motion, sizeof(motion));
        }
        link->timer = (func_150ADA20() % 201U) + 0xC8;
    }
}
extern f32 D_800BE9A4;

s32 func_150DEACC(void *arg0) {
    *(f32 *)((u8 *)arg0 + 0x34) = (f32) ((*(f32 *)((u8 *)arg0 + 0x110) * D_800BE9A4) + *(f32 *)((u8 *)arg0 + 0x34));
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) ((*(f32 *)((u8 *)arg0 + 0x114) * D_800BE9A4) + *(f32 *)((u8 *)arg0 + 0x38));
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) ((*(f32 *)((u8 *)arg0 + 0x118) * D_800BE9A4) + *(f32 *)((u8 *)arg0 + 0x3C));
    *(f32 *)((u8 *)arg0 + 0x11C) = (f32) (*(f32 *)((u8 *)arg0 + 0x11C) - D_800BE9A4);
    if (*(f32 *)((u8 *)arg0 + 0x11C) < 0.0f) {
        return 0;
    }
    return 1;
}
s32 func_15140410(s32, s32, s32, s16);
extern s32 D_80082FA0;
extern s32 D_800DBFF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DEB58 CURRENT (120) */
s32 func_150DEB58(s32 arg0, s16 arg1) {
    if (*(f32 *)((u8 *)(D_800DBFF0 + (D_80082FA0 * 0x9A0)) + 0x388) < 5.0f) {
        return 0;
    }
    return func_15140410(arg0, arg0 + 0x120, arg0 + 0x12C, arg1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DEB58 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10BC70/func_150DEB58.s")
