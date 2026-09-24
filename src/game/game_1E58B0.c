#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E58B0.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B8400
 * - func_151B86F4
 * - func_151B8908
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);
void *func_1513D2F0(s32, s32, u8, u8, u8, u8, u8, s32, s32, s32, u8, s32);
extern u8 D_800AA490;

typedef struct Game1E58B0Vec3 {
    s32 x;
    s32 y;
    s32 z;
} Game1E58B0Vec3;

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
    Game1E58B0Vec3 first;
    Game1E58B0Vec3 second;
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

typedef struct Game1E58B0SavedActor {
    void *actor;
    u32 pad;
} Game1E58B0SavedActor;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B8400 CURRENT (273) */
void *func_151B8400(void *arg0) {
    Game1E58B0SavedActor saved_actor;
    Game1E58B0MotionPacket motion;
    Game1E58B0SpawnPacket spawn;
    Game1E58B0Vec3 position;
    void *result;
    u8 *actor = arg0;
    f32 z_velocity;

    saved_actor.actor = arg0;

    spawn.kind = 0xFF;
    spawn.zero = 0;
    spawn.identifier = 0x5901;
    spawn.count = 0x32;
    spawn.reserved0 = 0;
    spawn.reserved1 = 0;
    spawn.red = 0xFF;
    spawn.green = 0xE6;
    spawn.blue = 0xB6;
    spawn.alpha = 0xFF;
    spawn.scale = 9.0f;
    spawn.rate = 1.0f;

    position = *(Game1E58B0Vec3 *)(actor + 0x38);
    motion.first = position;
    motion.second = position;
    motion.velocity[0] = *(f32 *)(actor + 0x44) * 0.25f;
    motion.velocity[1] = *(f32 *)(actor + 0x48) * 0.25f;
    z_velocity = *(f32 *)(actor + 0x4C) * 0.25f;
    motion.tag = 0x0CCC0000;
    motion.color0 = 0xC8;
    motion.color1 = 0xFF;
    motion.color2 = 0;
    motion.color3 = 6;
    motion.reserved0 = 0;
    motion.kind = 0xFF;
    motion.reserved1 = 0;
    motion.velocity[2] = z_velocity;
    motion.count = 0x32;
    motion.mode = 5;

    result = func_1513D2F0((s32)&spawn, (s32)&D_800AA490, 0x1B, 0, 0, 0x19,
                           0, 0, 0, 4, actor[0xC], actor[1]);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x110, &saved_actor.actor, 4);
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B8400 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E58B0/func_151B8400.s")
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
void func_1513FA70(s32 arg0, s16 arg1);

void func_151B863C(s32 arg0, s16 arg1) {
    func_1513FA70(arg0, arg1);
}
/* Call context: func_15134908: unique active project prototype */
void func_15134908(s32 *, s32, u8, s32);
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
    func_15134908((s32 *)&packet, 0, arg1, arg2);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E58B0/func_151B86F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E58B0/func_151B8908.s")
