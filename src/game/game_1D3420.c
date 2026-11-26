#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1D3420.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_direct_helper_pairs.md
 */

typedef struct Game1D3420Object {
    s16 position[3];
    s16 radius;
    s16 height;
    u8 unk_A[0xA];
    u8 active;
} Game1D3420Object;

void func_151A6068(Game1D3420Object *, s32, u8, u8, u8, s32);

typedef struct Game1D3420Message {
    s32 count;
    u8 *ids;
    s32 value;
} Game1D3420Message;

typedef struct Game1D3420Target {
    Game1D3420Object *object;
    u8 id;
    u8 pad05[3];
    s32 argument;
    u8 flags;
    u8 pad0D[3];
    s32 value;
} Game1D3420Target;

void func_151A5F70(u8 *arg0, void *arg1, u8 arg2) {
    Game1D3420Message *msg = arg1;
    s32 i;
    s32 found;
    Game1D3420Target *target;

    if (arg2 == 0x35) {
        target = (Game1D3420Target *)(arg0 + 0x28);
        i = 0;
        found = 0;
        while (i < msg->count && found == 0) {
            if (target->id == msg->ids[i]) {
                found = 1;
            } else {
                i++;
            }
        }
        if (found != 0) {
            if (target->object->active == 1) {
                func_151A6068(target->object, target->argument, target->flags & 1, target->flags & 2, arg0[0xC], arg0[1]);
                target->object->active = 0;
                target->value = msg->value;
            }
        }
    }
}
typedef struct Game1D3420Spawn {
    u8 kind, subtype;
    s16 flags, life;
    u8 reserved6[2];
    s32 frame, rate;
    u8 colors[4];
    f32 radius, height;
    f32 position[3], angles[3], scale[3];
    s32 options;
    u8 alpha, color, mode46, mode47;
    s32 control;
    u8 unused50, inactive51[3];
    s32 unk_50;
    s16 unk_54, unk_56;
} Game1D3420Spawn;

typedef struct Game1D3420Extension {
    void *owner;
    f32 angle, velocity, scale;
    s32 light;
    u8 phase, step, brightness, enabled;
    f32 elapsed;
} Game1D3420Extension;

typedef struct Game1D3420Light {
    u8 flags, callback;
    s16 life;
    u8 kind, reserved5;
} Game1D3420Light;

typedef struct Game1D3420Effect {
    u8 unk_0[0x110];
    Game1D3420Extension extension;
} Game1D3420Effect;

void *func_1513D2F0(s32, s32, u8, u8, u8, u8, u8, s32, s32, s32, u8, s32);
void *func_10022EC0(void *, const void *, u32);
s32 func_1516284C(u8 *, s32 *, s32, s32, s32, u8, u8, s32, u8, u8, s32);
f32 func_150ADA68(void);
extern u8 D_800A4AA0[], D_1000EF40[];
extern f32 D_800A8D98, D_800A8D9C;

#define RANDOM_U8() ((u8)func_150ADA20())
#define RAND_RANGE(min, range) (func_150ADA68() * (range) + (min))

void func_151A6068(Game1D3420Object *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5) {
    Game1D3420Spawn spawn;
    Game1D3420Extension extension;
    Game1D3420Extension *payload;
    Game1D3420Effect *result;
    Game1D3420Light light;
    s32 position[3];

    extension.owner = arg0;
    extension.angle = 0.0f;
    extension.velocity = RAND_RANGE(-380.0f, 80.0f);
    extension.scale = RAND_RANGE(D_800A8D9C, D_800A8D98);
    extension.light = 0;
    extension.phase = RANDOM_U8();
    extension.step = (RANDOM_U8() & 3) + 4;
    extension.brightness = 255;
    extension.elapsed = 0.0f;
    extension.enabled = arg3;
    spawn.kind = 0x6B;
    spawn.subtype = 10;
    spawn.flags = 0x4C03;
    spawn.life = 240;
    spawn.frame = 0;
    spawn.rate = 0;
    spawn.colors[0] = 255;
    spawn.colors[1] = 255;
    spawn.colors[2] = 255;
    spawn.colors[3] = 255;
    spawn.radius = arg0->radius;
    spawn.height = arg0->height;
    spawn.position[0] = arg0->position[0];
    spawn.position[1] = arg0->position[1];
    spawn.position[2] = arg0->position[2];
    spawn.options = 0x01EC0009;
    spawn.alpha = 255;
    spawn.color = 255;
    spawn.mode46 = 0;
    spawn.mode47 = 0;
    spawn.control = arg1;
    spawn.unused50 = 255;
    spawn.angles[0] = 0.0f;
    spawn.angles[1] = 0.0f;
    spawn.angles[2] = 0.0f;
    spawn.scale[0] = 1.0f;
    spawn.scale[1] = 1.0f;
    spawn.scale[2] = 1.0f;
    result = func_1513D2F0((s32)&spawn, (s32)D_800A4AA0,
        0, 0x28, 0, 0x20, 0, 0, 0, 0x1C, arg4, arg5);
    if (result != NULL) {
        payload = &result->extension;
        func_10022EC0(payload, &extension, 0x1C);
        if (arg2 != 0) {
            position[0] = arg0->position[0];
            position[1] = (arg0->height >> 1) + arg0->position[1];
            position[2] = arg0->position[2];
            light.flags = 2;
            light.callback = 2;
            light.life = 300;
            light.kind = 6;
            payload->light = func_1516284C(&light.flags, position,
                255, 0x79, 0, 255, 0, 0, 14, arg4, arg5);
        }
    }
    if (arg2 != 0) {
        func_1000FA64(0x1AA, arg0->position[0], arg0->position[1],
            arg0->position[2], 0x4000, 1000, 750, D_1000EF40,
            (s32)arg0, 0, 8, func_150ADA20() & 0x300);
    }
}
