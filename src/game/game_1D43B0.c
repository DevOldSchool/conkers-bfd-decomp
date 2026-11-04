#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1D43B0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_recovered_pointer_helper_groups_continued.md
 */

typedef struct Game1D43B0Desc {
    f32 field00, field04, field08, field0C;
    Vec3f angles;
    Vec3f scale;
    Vec3f position;
    Vec3f velocity;
    f32 field40, field44, field48, field4C;
    s32 field50;
    s16 field54, field56;
    u8 field58;
    s32 field5C;
    u8 field60, field61, field62, field63;
    u8 field64, field65, field66, field67;
    u8 field68, pad69, field6A, pad6B;
    s32 field6C;
    u8 field70;
    s16 field72, field74;
    u8 unknown76[6];
} Game1D43B0Desc;

typedef struct Game1D43B0Link {
    f32 *x, *y, *z;
    f32 size;
    f32 scale;
    s16 duration;
    u8 field16, field17;
    u8 pad18[4];
} Game1D43B0Link;

typedef struct Game1D43B0Entry {
    f32 field_0;
    void *field_4;
    u8 spawn;
    u8 alternate;
    s16 first;
    s16 last;
} Game1D43B0Entry;

typedef struct Game1D43B0Emitter {
    s16 count;
    u8 pad2[2];
    Vec3f position;
    s16 field10;
    u8 pad12[2];
    f32 radius;
    s16 pitchBase, pitchRange;
    s16 yawBase, yawRange;
    f32 speedBase, speedRange;
    f32 upBase, upRange;
    Vec3f direction;
    f32 sizeBase, sizeRange;
    f32 spinBase, spinRange;
    f32 rollBase, rollRange;
    u8 spawn, alternate;
    s16 first, last;
} Game1D43B0Emitter;

void *func_10022EC0(void *, const void *, u32);
void *func_15132A4C(void *, s32, s32, s32, u8, s32);
f32 func_150ADA68();
extern f32 D_800A8DC0;
extern f32 D_800A8DC4;

void func_151A6F00(Game1D43B0Emitter *arg0, u8 arg1, u8 arg2, s32 arg3) {
    void *result;
    Game1D43B0Desc desc;
    s16 count;
    Game1D43B0Entry entry;
    f32 size;
    u8 pitch;
    f32 sinPitch, cosPitch;
    u8 yaw;
    f32 sinYaw, cosYaw;
    f32 speed, horizontal;
    Game1D43B0Entry *state;
    void *linked;
    Game1D43B0Link link;

    count = arg0->count;
    desc.scale.x = 1.0f;
    desc.scale.y = 1.0f;
    desc.scale.z = 1.0f;
    desc.field50 = 0x21E9;
    desc.field58 = 0;
    desc.field54 = arg0->field10;
    desc.field04 = D_800A8DC0;
    desc.field56 = 0x1B;
    desc.angles.x = 0.0f;
    desc.angles.y = 0.0f;
    desc.angles.z = 0.0f;
    desc.field44 = 0.0f;
    entry.field_0 = -18.0f;
    entry.spawn = arg0->spawn;
    entry.alternate = arg0->alternate;
    entry.first = arg0->first;
    entry.last = arg0->last;
    desc.field5C = 0;
    desc.field60 = 0xFF;
    desc.field61 = 1;
    desc.field62 = 5;
    desc.field63 = 4;
    desc.field64 = 0;
    desc.field65 = 0;
    desc.field66 = 1;
    desc.field67 = 0;
    desc.field68 = 0;
    desc.field6A = 0;
    desc.field6C = 0;
    desc.field70 = 0;
    desc.field72 = 0x20;
    desc.field74 = 7;
    while (count--) {
        pitch = func_150ADA20() % (u32)(arg0->pitchRange + 1) + arg0->pitchBase;
        yaw = func_150ADA20() % (u32)(arg0->yawRange + 1) + arg0->yawBase;
        sinPitch = func_151423D8(pitch - 64);
        cosPitch = func_151423D8(pitch);
        sinYaw = func_151423D8(yaw - 64);
        cosYaw = func_151423D8(yaw);
        speed = func_150ADA68() * arg0->radius;
        horizontal = speed * cosYaw;
        desc.position.x = arg0->position.x + horizontal * sinPitch;
        desc.position.y = arg0->position.y - speed * sinYaw;
        desc.position.z = arg0->position.z + horizontal * cosPitch;
        switch (arg1) {
        case 0: {
            f32 a;
            a = func_150ADA68() * arg0->speedRange + arg0->speedBase;
            speed = func_150ADA68() * arg0->upRange + arg0->upBase;
            desc.velocity.x = a * sinPitch;
            desc.velocity.y = speed;
            desc.velocity.z = a * cosPitch;
        }
            break;
        case 1: {
            f32 h;
            speed = func_150ADA68() * arg0->speedRange + arg0->speedBase;
            h = speed * cosYaw;
            desc.velocity.x = h * sinPitch;
            desc.velocity.y = -speed * sinYaw;
            desc.velocity.z = h * cosPitch;
        }
            break;
        case 2:
            desc.velocity = arg0->direction;
            break;
        case 3:
            speed = func_150ADA68() * arg0->speedRange + arg0->speedBase;
            desc.velocity.x = arg0->direction.x * speed;
            desc.velocity.y = arg0->direction.y * speed;
            desc.velocity.z = arg0->direction.z * speed;
            break;
        }
        size = desc.field08 = desc.field0C = func_150ADA68() * arg0->sizeRange + arg0->sizeBase;
        desc.field00 = size * 30.0f;
        desc.field4C = func_150ADA68() * arg0->spinRange + arg0->spinBase;
        desc.field40 = func_150ADA68() * arg0->rollRange + arg0->rollBase;
        desc.field48 = func_150ADA68() * arg0->rollRange + arg0->rollBase;
        result = func_15132A4C(&desc, 0, 0, 0x10, arg2, arg3);
        if (result != NULL) {
            state = (Game1D43B0Entry *)((u8 *)result + 0x170);
            func_10022EC0(state, &entry, 0x10);
            link.x = (f32 *)((u8 *)result + 0x38);
            link.y = (f32 *)((u8 *)result + 0x3C);
            link.z = (f32 *)((u8 *)result + 0x40);
            link.size = 15.0f * desc.field0C;
            link.duration = 0x12C;
            link.field16 = 0;
            link.field17 = 1;
            link.scale = D_800A8DC4;
            state->field_4 = NULL;
            linked = func_15134908(&link, 4, arg2, arg3);
            state->field_4 = linked;
            if (linked != NULL) {
                func_10022EC0((u8 *)linked + 0x40, &size, 4);
            }
        }
    }
}
typedef struct {
    f32 field_0;
    void *field_4;
    u8 spawn;
    u8 alternate;
    s16 first;
    s16 last;
} Game1D4140Entry;

typedef struct {
    u8 pad_0[0x10];
    f32 base_height;
    f32 bounce;
    f32 scale;
    u8 pad1C[0x20];
    f32 height;
    u8 pad40[4];
    f32 velocity_x;
    f32 velocity_y;
    f32 velocity_z;
    f32 rotation_x;
    f32 rotation_y;
    f32 rotation_z;
    u8 pad5C[4];
    s32 flags;
    s16 field_64;
    u8 pad_66[0x10A];
    Game1D4140Entry field_170;
} Game1D4140State;

s32 func_151A73EC(Game1D4140State *arg0) {
    Game1D4140Entry *temp_v0;

    temp_v0 = &arg0->field_170;
    if (arg0->field_64 < 0x20) {
        if (temp_v0->field_4 != 0) {
            func_1516972C(temp_v0->field_4);
            temp_v0->field_4 = 0;
        }
    }
    return 1;
}
void func_1514AB5C(f32, f32, f32, f32, s32, f32, f32, f32, f32, s32, s32, s32);

s32 func_151A743C(Game1D4140State *arg0, f32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    Game1D4140Entry *state;
    u8 alternate;

    state = &arg0->field_170;
    arg0->height = arg0->base_height + arg4;
    if (arg0->field_170.field_4 != 0) {
        func_1516972C(state->field_4);
        state->field_4 = 0;
    }
    if (state->field_0 < arg0->velocity_y) {
        arg0->flags &= ~7;
        arg0->flags &= ~8;
        arg0->flags &= ~0x40;
        arg0->flags &= ~0x20;
        arg0->velocity_x = 0.0f;
        arg0->velocity_y = 0.0f;
        arg0->velocity_z = 0.0f;
        if (arg0->field_64 >= 0x21) {
            arg0->field_64 = 0x20;
        }
        if (state->spawn != 0) {
            alternate = 0;
            if (state->alternate != 0) {
                alternate = 1;
            }
            func_1514AB5C(arg1, arg4, arg3, arg0->scale * 35.0f,
                         func_150ADA20() % 3U + 2,
                         arg0->scale, arg0->scale * 0.5f,
                         arg0->scale, arg0->scale * 0.5f,
                         state->first, state->last, alternate);
        }
    } else {
        arg0->velocity_x *= arg0->bounce;
        arg0->velocity_y = -arg0->velocity_y * arg0->bounce;
        arg0->velocity_z *= arg0->bounce;
        arg0->rotation_x *= arg0->bounce;
        arg0->rotation_y *= arg0->bounce;
        arg0->rotation_z *= arg0->bounce;
    }
    return 1;
}
