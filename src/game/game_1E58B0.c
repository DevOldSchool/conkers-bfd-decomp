#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1E58B0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_dense_pointer_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B8908
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);
void *func_1513D2F0(s32, s32, u8, u8, u8, u8, u8, s32, s32, s32, u8, s32);
extern u8 D_800AA490;

typedef struct Game1E58B0SpawnPacket {
    u8 kind;
    u8 zero;
    s16 identifier;
    s16 count;
    u8 pad06[2];
    s32 reserved0;
    s32 reserved1;
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
    f32 scale;
    f32 rate;
} Game1E58B0SpawnPacket;

typedef struct Game1E58B0MotionPacket {
    Vec3i first;
    Vec3i second;
    f32 velocity[3];
    s32 tag;
    u8 color0;
    u8 color1;
    u8 color2;
    u8 color3;
    s32 reserved0;
    u8 kind;
    u8 pad31[3];
    s32 reserved1;
    s16 count;
    s16 mode;
} Game1E58B0MotionPacket;

void *func_151B8400(void *arg0) {
    u8 *actor = arg0;
    void *saved_actor;
    struct {
        Game1E58B0SpawnPacket spawn;
        Game1E58B0MotionPacket motion;
    } packet;
    Vec3i position;
    void *result;

    saved_actor = arg0;

    packet.spawn.kind = 0xFF;
    packet.spawn.zero = 0;
    packet.spawn.identifier = 0x5901;
    packet.spawn.count = 0x32;
    packet.spawn.reserved0 = 0;
    packet.spawn.reserved1 = 0;
    packet.spawn.red = 0xFF;
    packet.spawn.green = 0xE6;
    packet.spawn.blue = 0xB6;
    packet.spawn.alpha = 0xFF;
    packet.spawn.scale = 9.0f;
    packet.spawn.rate = 1.0f;

    position = *(Vec3i *)(actor + 0x38);
    packet.motion.second = position;
    packet.motion.first = position;
    packet.motion.velocity[0] = *(f32 *)(actor + 0x44) * 0.25f;
    packet.motion.velocity[1] = *(f32 *)(actor + 0x48) * 0.25f;
    packet.motion.velocity[2] = *(f32 *)(actor + 0x4C) * 0.25f;
    packet.motion.tag = 0x0CCC0000;
    packet.motion.color0 = 0xC8;
    packet.motion.color1 = 0xFF;
    packet.motion.color2 = 0;
    packet.motion.color3 = 6;
    packet.motion.reserved0 = 0;
    packet.motion.kind = 0xFF;
    packet.motion.reserved1 = 0;
    packet.motion.count = 0x32;
    packet.motion.mode = 5;

    result = func_1513D2F0((s32)&packet, (s32)&D_800AA490, 0x1B, 0, 0, 0x19,
                           0, 0, 0, 4, actor[0xC], actor[1]);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x110, &saved_actor, 4);
    }
    return result;
}
extern f32 D_800BE9A4;

s32 func_151B85AC(void *arg0) {
    typedef struct {
        s32 x;
        s32 y;
        s32 z;
    } Vec3;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x110);
    if (temp_v0 != 0) {
        *(Vec3 *)((u8 *)arg0 + 0x34) = *(Vec3 *)((u8 *)temp_v0 + 0x38);
        *(f32 *)((u8 *)arg0 + 0x40) += *(f32 *)((u8 *)arg0 + 0x4C) * D_800BE9A4;
        *(f32 *)((u8 *)arg0 + 0x44) += *(f32 *)((u8 *)arg0 + 0x50) * D_800BE9A4;
        *(f32 *)((u8 *)arg0 + 0x48) += *(f32 *)((u8 *)arg0 + 0x54) * D_800BE9A4;
    } else {
        *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) | 1);
    }
    return 1;
}

void func_151B863C(void *arg0, s16 arg1) {
    func_1513FA70(arg0, arg1);
}
extern f32 D_800AA4C8;
extern f32 D_800DCA24;

void func_151B8668(s32 arg0, u8 arg1, s32 arg2) {
    struct {
        s32 x;
        s32 y;
        s32 z;
        f32 size;
        f32 scale;
        s16 lifetime;
        s8 flag;
        s8 kind;
        s8 extra;
        u32 pad;
    } packet;

    packet.size = 10.0f;
    packet.x = arg0 + 0x38;
    packet.y = arg0 + 0x3C;
    packet.z = arg0 + 0x40;
    packet.scale = D_800AA4C8 * D_800DCA24;
    packet.lifetime = 0x12C;
    packet.flag = 0;
    packet.kind = 3;
    packet.extra = 0;
    func_15134908(&packet, 0, arg1, arg2);
}
void func_15143794(s16, s16, f32, void *);
void func_151A26EC(f32 *, f32 *, f32 *, f32, f32, f32, s32, s32, s32,
                    s32, s32, s32, s32, s32, s32, s32, s32);
f32 func_150ADA68(void);
extern f32 D_800BE9A8;

void func_151B86F4(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4,
                   f32 arg5, void *arg6) {
    f32 position[3];
    f32 velocity[3];
    f32 zero[3];
    f32 velocityScale;
    f32 randomScale1;
    u32 random1;
    u32 random0;
    f32 randomScale0;

    position[0] = arg0;
    position[1] = arg1;
    position[2] = arg2;
    random0 = func_150ADA20();
    random1 = func_150ADA20();
    randomScale0 = func_150ADA68();
    func_15143794((s16)(random0 & 0xFF), (s16)((random1 % 65U) - 0x20),
                   randomScale0 * 945.0f * 0.01f, velocity);
    velocityScale = ((func_150ADA68() * 157.0f) + 604.0f) * 0.001f;
    zero[0] = 0.0f;
    zero[1] = 0.0f;
    zero[2] = 0.0f;
    velocity[0] += -arg3 * D_800BE9A8 * velocityScale;
    velocity[1] += -arg4 * D_800BE9A8 * velocityScale;
    velocity[2] += -arg5 * D_800BE9A8 * velocityScale;
    randomScale0 = func_150ADA68();
    randomScale1 = func_150ADA68();
    random0 = func_150ADA20();
    random1 = func_150ADA20();
    func_151A26EC(position, zero, velocity, 1.0f,
                   ((randomScale0 * 157.0f) + -151.0f) * 0.001f,
                   (randomScale1 * 55.0f) + 75.0f,
                   (random0 % 26U) + 0x19, (random1 % 101U) + 0x64,
                   0xA, 0x19, 0, -1, 0, 0, 0,
                   *(u8 *)((u8 *)arg6 + 0xC), *(u8 *)((u8 *)arg6 + 1));
}
typedef struct Game1E58B0ActorDescriptor {
    s32 field00;
    s32 field04;
    s16 field08;
    s16 field0A;
    s32 field0C;
    s32 field10;
    u8 fields14[9];
    u8 field1D;
    s16 field1E;
    s16 field20;
    s16 field22;
    f32 field24;
    f32 field28;
    f32 field2C;
    Vec3i field30;
    Vec3i field3C;
    Vec3i field48;
    f32 field54;
    s32 field58;
    s32 field5C;
    s8 fields60[6];
    u8 field66;
    u8 unknown67[9];
} Game1E58B0ActorDescriptor;

typedef struct Game1E58B0ChoiceTable {
    s32 values[4];
} Game1E58B0ChoiceTable;

struct Game15D730CopyBlock;
extern Game1E58B0ChoiceTable D_800AA4B8;
extern Vec3i D_800A5480;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B8908 CURRENT (1068) */
void *func_151B8908(void *arg0) {
    Game1E58B0ActorDescriptor descriptor;
    Game1E58B0ChoiceTable choices;
    f32 size;
    s32 selected;
    s32 secondFlags;
    s32 firstFlags;

    choices = D_800AA4B8;
    selected = choices.values[func_150ADA20() & 3];
    descriptor.field08 = 0x1303;
    descriptor.field00 = 0x200005;
    descriptor.field1D = (u8)selected;
    descriptor.field04 = 0;
    descriptor.field0A = 0x12C;
    descriptor.field0C = 0;
    descriptor.field10 = 0;
    descriptor.fields14[0] = 0xFF;
    descriptor.fields14[1] = 0xFF;
    descriptor.fields14[2] = 0xFF;
    descriptor.fields14[3] = 0xFF;
    descriptor.fields14[4] = 0xFF;
    descriptor.fields14[5] = 0xFF;
    descriptor.fields14[6] = 0xFF;
    descriptor.fields14[7] = 0xFF;
    descriptor.fields14[8] = 0xFF;
    size = (func_150ADA68() * 500.0f) + 900.0f;
    descriptor.field2C = size;
    descriptor.field28 = size;
    descriptor.field30 = *(Vec3i *)((u8 *)arg0 + 0x38);
    descriptor.field3C = D_800A5480;
    descriptor.field48 = D_800A5480;
    descriptor.field1E = 1;
    descriptor.field20 = 0xFF;
    descriptor.field22 = 1;
    descriptor.field54 = 0.0f;
    descriptor.field24 = 1.0f;
    firstFlags = (func_150ADA20() & 1) ? 0x40 : 0;
    if (func_150ADA20() & 1) {
        secondFlags = 0x80;
    } else {
        secondFlags = 0;
    }
    descriptor.field58 = secondFlags | firstFlags | 0xC000 | 0x40000 | 0x800000;
    descriptor.fields60[0] = 6;
    descriptor.fields60[1] = 5;
    descriptor.fields60[2] = -1;
    descriptor.fields60[3] = -1;
    descriptor.fields60[4] = -1;
    descriptor.fields60[5] = 0;
    descriptor.field5C = 0;
    descriptor.field66 = 0xFF;
    return func_15130280(&descriptor, 1, 0, 0,
                          *(u8 *)((u8 *)arg0 + 0xC), *(u8 *)((u8 *)arg0 + 1));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B8908 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E58B0/func_151B8908.s")
