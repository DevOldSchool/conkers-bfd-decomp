#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_113480.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_direct_call_singletons.md
 */

typedef struct Game113480Packet {
    s8 kind;
    u8 pad1;
    s16 flags, life;
    u8 pad6[2];
    s32 field8, fieldC;
    u8 color[4];
    f32 field14, field18;
    Vec3f position;
    Vec3f direction;
    Vec3f scale;
    s32 mode;
    u8 field44, field45;
    u8 pad46[0x12];
} Game113480Packet;

typedef struct Game113480Impact {
    u8 flags;
    u8 pad1[3];
    Vec3f point;
    u8 surface[4];
    s16 surfaceIndex;
    u8 pad16[0x12];
    f32 side;
    s8 variant;
    u8 pad2D[3];
} Game113480Impact;

void *func_10022EC0(void *, const void *, u32);
s32 func_150AC9C0(f32, f32, f32, f32, f32, f32, void *, s16 *, f32 *, f32 *, f32 *, f32 *, s32 *, void *, f32);
void *func_1513D524(s32, u8, u8, u8, u8, u8, s32, u8, s32);
f32 func_15144A74(void *, void *);
s32 func_15145C90(s32);

void *func_150E5FD0(Vec3f *arg0, Vec3f *arg1, f32 arg2, f32 arg3, f32 arg4, u8 arg5, s32 arg6, u8 arg7, u8 arg8,
                    s16 arg9, s8 arg10) {
    void *result;
    Game113480Packet packet;
    Game113480Impact impact;
    s32 hitObject;
    Vec3f offset;
    s32 flipX;
    s32 flipY;

    packet.kind = 0x41;
    packet.flags = 0x2301;
    packet.life = arg9;
    packet.field8 = 0;
    packet.fieldC = 0;
    packet.color[0] = 0;
    packet.color[1] = 0;
    packet.color[2] = 0;
    packet.color[3] = 0xFF;
    packet.field44 = arg8;
    packet.field45 = 0xFF;
    packet.field14 = arg3;
    packet.field18 = arg4;
    packet.position = *arg0;
    packet.direction = *arg1;
    packet.scale.x = 0.0f;
    packet.scale.y = arg2;
    packet.scale.z = 0.0f;
    packet.mode = 1;
    impact.flags = 0;
    impact.variant = arg10;
    if ((arg7 != 0) &&
        (func_150AC9C0(arg0->x, arg0->y, arg0->z, arg1->x, arg1->y, arg1->z, impact.surface, &impact.surfaceIndex,
                       &impact.point.x, &impact.point.y, &impact.point.z, NULL, &hitObject, NULL, 0.0f) != 0) &&
        (func_15145C90(hitObject) != 0)) {
        impact.flags |= 1;
        offset.x = impact.point.x - packet.position.x;
        offset.y = impact.point.y - packet.position.y;
        offset.z = impact.point.z - packet.position.z;
        if (func_15144A74(&offset, &impact.point) < 0.0f) {
            impact.side = -1.0f;
        } else {
            impact.side = 1.0f;
        }
    }
    if (func_150ADA20() & 1) {
        flipY = 2;
    } else {
        flipY = 0;
    }
    if (func_150ADA20() & 1) {
        flipX = 1;
    } else {
        flipX = 0;
    }
    result = func_1513D524((s32)&packet, 0xF, 0x15, 0, 0xF, flipX | flipY, 0x30, arg5, arg6);
    if (result != NULL) {
        func_10022EC0((u8 *)result + 0x110, &impact, 0x30);
    }
    return result;
}
