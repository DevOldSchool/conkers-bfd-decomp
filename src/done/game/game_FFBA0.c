#include "types.h"
#include "game_functions.h"
#include "globals.h"

/*
 * Reviewed source unit: src/game/game_FFBA0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_child_chain_render_lists.md
 */

/* Call context: func_150D278C: unique active declaration in the allowed source */
void func_150D278C(s32, void *, u8, s32);

typedef struct GameFFBA0Timer {
    s32 arg;
    s32 baseDelay;
    s32 delayRange;
    s32 countdown;
    u8 data[4];
} GameFFBA0Timer;

void func_150D26F0(u8 *arg0) {
    GameFFBA0Timer *state = (GameFFBA0Timer *)(arg0 + 0x28);

    if (arg0[0x78] & 1) {
        if ((state->countdown -= D_800BE9E4) < 0) {
            func_150D278C(state->arg, state->data, arg0[0xC], arg0[1]);
            state->countdown = state->baseDelay + (func_150ADA20() % (u32)(state->delayRange + 1));
        }
    }
}
void *func_10022EC0(void *, const void *, u32);
f32 func_150ADA68(void);

void func_150D278C(s32 arg0, void *arg1, u8 arg2, s32 arg3) {
    u8 packet[0x60];
    u8 *object;

    *(s32 *)(packet + 0) = arg0;
    *(f32 *)(packet + 4) = (2.0f * func_150ADA68()) * 3.1415927f;
    *(f32 *)(packet + 8) = (func_150ADA68() * 0.4f) + 0.3f;
    *(f32 *)(packet + 0xC) = 1.0f / *(f32 *)(packet + 8);
    *(f32 *)(packet + 0x10) = (func_150ADA68() * 0.13000001f) + 0.3f;
    if (func_150ADA20() & 1) {
        *(f32 *)(packet + 0x10) = -*(f32 *)(packet + 0x10);
    }
    *(f32 *)(packet + 0x14) = 0.0f;
    *(f32 *)(packet + 0x18) = 0.0f;
    func_10022EC0(packet + 0x1C, arg1, 0x40);
    {
        const u8 choices[9] = { 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00 };

        object = (u8 *)choices + (((func_150ADA20() % 3U) & 0xFF) * 3);
        packet[0x5C] = object[0];
        packet[0x5D] = object[1];
        packet[0x5E] = object[2];
    }
    object = func_15149130((s16)((func_150ADA20() % 101U) + 0x64), -1,
                           0x32, -1, 1, 0, 0x60, arg2, arg3);
    if (object != 0) {
        func_10022EC0(object + 0x28, packet, 0x60);
    }
}
void func_1514373C(f32, f32, f32 *, f32 *);
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
void *func_1513D2F0(void *, void *, u8, u8, u8, u8, u8, s32, s32, s32, u8, s32);
extern u8 D_800A4AA0[0x28];
extern f32 D_800BE9A4;

typedef struct GameFFBA0Emitter {
    s16 *record;
    f32 angle;
    f32 rate;
    f32 fade;
    f32 spin;
    f32 counter;
    f32 age;
    u8 matrix[0x40];
    u8 color[3];
} GameFFBA0Emitter;

typedef struct GameFFBA0Spark {
    f32 field0;
    f32 field4;
    f32 field8;
    f32 fieldC;
    f32 field10;
    f32 field14;
    f32 field18;
    f32 field1C;
    f32 field20;
    f32 field24;
    f32 field28;
    f32 field2C;
} GameFFBA0Spark;

typedef struct GameFFBA0Spawn {
    u8 field0;
    u8 field1;
    s16 field2;
    s16 field4;
    s32 field8;
    s32 fieldC;
    u8 colors10[4];
    f32 field14;
    f32 field18;
    Vec3f position1C;
    Vec3f field28;
    f32 field34;
    f32 field38;
    f32 field3C;
    s32 field40;
    u8 field44;
    u8 field45;
    u8 field46;
    u8 field47;
    s32 field48;
    u8 field4C;
    s32 field50;
    s16 field54;
    s16 field56;
} GameFFBA0Spawn;

void func_150D2924(u8 *arg0) {
    GameFFBA0Emitter *emitter = (GameFFBA0Emitter *)(arg0 + 0x28);
    GameFFBA0Spawn spawn;
    s16 *record;
    GameFFBA0Spark spark;

    emitter->counter += emitter->rate * D_800BE9A4;
    emitter->age += D_800BE9A4;
    if (emitter->counter > 1.0f) {
        f32 point[3];

        record = emitter->record;
        spark.field2C = 9.0f;
        spark.field18 = 0.0f;
        spark.field1C = 0.0f;
        spawn.field0 = 0x59;
        spawn.field1 = 0;
        spawn.field2 = 0x5A03;
        spawn.field4 = 0x16;
        spawn.field8 = 0;
        spawn.fieldC = 0;
        spawn.colors10[0] = emitter->color[0];
        spawn.colors10[1] = emitter->color[1];
        spawn.colors10[2] = emitter->color[2];
        spawn.colors10[3] = 0xFF;
        spawn.field18 = 1.0f;
        spawn.position1C.x = record[0];
        spawn.position1C.y = record[1];
        spawn.position1C.z = record[2];
        spawn.field34 = 1.0f;
        spawn.field38 = 1.0f;
        spawn.field3C = 1.0f;
        spawn.field40 = 0x26C0000;
        spawn.field45 = 0xFF;
        spawn.field46 = 0;
        spawn.field47 = 6;
        spawn.field48 = 0;
        spawn.field4C = 0xFF;
        do {
            spark.field28 = 22.0f - emitter->age;
            if (spark.field28 > 0.0f) {
                u8 *result;

                func_1514373C(emitter->angle, record[3], &point[0], &point[2]);
                point[1] = record[4];
                func_150A7960(emitter->matrix, point[0], point[1], point[2],
                              &spawn.field28.x, &spawn.field28.y, &spawn.field28.z);
                spawn.field14 = func_150ADA68() * 25.0f + 50.0f;
                spark.field0 = spark.field8 = func_150ADA68() * 1024.0f + -2560.0f + 2048.0f;
                spark.fieldC = func_150ADA68() * 1024.0f + 1536.0f + 2048.0f;
                spark.field4 = spark.fieldC;
                spark.field10 = func_150ADA68() * 768.0f + 768.0f;
                spark.field14 = func_150ADA68() * 768.0f + 768.0f;
                spark.field20 = (func_150ADA68() * 80.0f + 50.0f) * 0.001f;
                spark.field24 = (func_150ADA68() * 80.0f + 50.0f) * 0.001f;
                spawn.field44 = spark.field2C * spark.field28;
                result = func_1513D2F0(&spawn, &D_800A4AA0, 0, 0x26, 0, 0x1F, 0, 0, 0, 0x30,
                                       arg0[0xC], arg0[1]);
                if (result != NULL) {
                    func_10022EC0(result + 0x110, &spark, 0x30);
                }
            }
            emitter->angle += emitter->spin;
            emitter->age -= emitter->fade;
            emitter->counter -= 1.0f;
        } while (emitter->counter > 1.0f);
    }
}
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
typedef struct GameFFBA0BeamVertex {
    s16 x;
    s16 y;
    s16 z;
    s16 flag;
    s16 s;
    s16 t;
    u8 color[4];
} GameFFBA0BeamVertex;

void func_150AD8B0(f32 *, f32 *, f32 *);
s32 func_15144B34(s32);
void func_151D5D60(void *, s16, s32, void **, u8 *);

typedef struct GameFFBA0Beam {
    u8 pad0[0x2C];
    f32 width;
    u8 pad30[4];
    Vec3f start;
    Vec3f end;
    u8 pad4C[0x74];
    u8 vertexTemplate[0x40];
    u8 *buffers[4];
    f32 texture[2];
} GameFFBA0Beam;

void *func_150D2D6C(GameFFBA0Beam *arg0, s16 arg1) {
    GameFFBA0BeamVertex *vertices;
    void *result;
    Vec3f *camera;
    Vec3f delta;
    Vec3f end;
    Vec3f middle;
    Vec3f view;
    Vec3f side;
    f32 lengthSquared;
    f32 *texture;
    u8 fresh;

    func_151D5D60(arg0->buffers, arg1, 0x40, (void **)&vertices, &fresh);
    result = vertices;
    if (vertices != NULL) {
        if (fresh != 0) {
            func_10022EC0(arg0->buffers[arg1], arg0->vertexTemplate, 0x40);
            func_10022EC0(arg0->buffers[arg1] + 0x40, arg0->vertexTemplate, 0x40);
        }
    } else {
        return NULL;
    }
    texture = arg0->texture;
    camera = (Vec3f *)func_15144B34(arg1);
    delta.x = arg0->end.x - arg0->start.x;
    delta.y = arg0->end.y - arg0->start.y;
    delta.z = arg0->end.z - arg0->start.z;
    end.x = arg0->start.x + delta.x;
    end.y = arg0->start.y + delta.y;
    end.z = arg0->start.z + delta.z;
    middle.x = arg0->start.x + delta.x * 0.5f;
    middle.y = arg0->start.y + delta.y * 0.5f;
    middle.z = arg0->start.z + delta.z * 0.5f;
    view.x = middle.x - camera->x;
    view.y = middle.y - camera->y;
    view.z = middle.z - camera->z;
    func_150AD8B0(&delta.x, &view.x, &side.x);
    lengthSquared = side.x * side.x + side.y * side.y + side.z * side.z;
    if (lengthSquared != 0.0f) {
        f32 scale = arg0->width / sqrtf(lengthSquared);

        side.x = side.x * scale;
        side.y = side.y * scale;
        side.z = side.z * scale;
    } else {
        side.x = 0;
        side.y = 0;
        side.z = 0;
    }
    vertices->x = arg0->start.x - side.x;
    vertices->y = arg0->start.y - side.y;
    vertices->z = arg0->start.z - side.z;
    vertices->s = texture[1];
    vertices->flag = 0;
    vertices++;
    vertices->x = end.x - side.x;
    vertices->y = end.y - side.y;
    vertices->z = end.z - side.z;
    vertices->s = texture[0];
    vertices->flag = 0;
    vertices++;
    vertices->x = end.x + side.x;
    vertices->y = end.y + side.y;
    vertices->z = end.z + side.z;
    vertices->s = texture[0];
    vertices->flag = 0;
    vertices++;
    vertices->x = arg0->start.x + side.x;
    vertices->y = arg0->start.y + side.y;
    vertices->z = arg0->start.z + side.z;
    vertices->s = texture[1];
    vertices->flag = 0;
    return result;
}
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32);                             /* extern */

s32 func_150D317C(u8 *arg0) {
    u8 *temp_s0;

    *(f32 *)(arg0 + 0x128) += *(f32 *)(arg0 + 0x130) * D_800BE9A4;
    *(f32 *)(arg0 + 0x12C) += *(f32 *)(arg0 + 0x134) * D_800BE9A4;
    temp_s0 = (void *)(arg0 + 0x110);
    *(f32 *)((u8 *)temp_s0 + 0x18) = func_15144B68(*(f32 *)((u8 *)arg0 + 0x128));
    *(f32 *)((u8 *)temp_s0 + 0x1C) = func_15144B68(*(f32 *)((u8 *)temp_s0 + 0x1C));
    *(f32 *)temp_s0 = *(f32 *)(temp_s0 + 8) + *(f32 *)(temp_s0 + 0x10) * func_15047D60(*(f32 *)(temp_s0 + 0x18));
    *(f32 *)((u8 *)temp_s0 + 4) = *(f32 *)(temp_s0 + 0xC) + *(f32 *)(temp_s0 + 0x14) * func_15047D60(*(f32 *)(temp_s0 + 0x1C));
    *(f32 *)((u8 *)temp_s0 + 0x28) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x28) - D_800BE9A4);
    *(s8 *)((u8 *)arg0 + 0x5C) = (s8) (u32) (*(f32 *)((u8 *)temp_s0 + 0x28) * *(f32 *)((u8 *)temp_s0 + 0x2C));
    if (*(f32 *)((u8 *)temp_s0 + 0x28) > 0.0f) {
        return 1;
    }
    return 0;
}
typedef struct {
    s32 field_0;
    u8 pad_4[0xC];
    u8 field_10[0x41];
    u8 field_51;
} GameFFBA0Child;

typedef struct {
    u8 pad_0;
    u8 field_1;
    u8 pad_2[0xA];
    u8 field_C;
    u8 pad_D[0x1B];
    GameFFBA0Child child;
} GameFFBA0State;

void func_150D278C(s32, void *, u8, s32);

void func_150D32FC(GameFFBA0State *arg0, u8 *arg1, u8 arg2) {
    GameFFBA0Child *child = &arg0->child;
    if (arg2 == 0x34 && *arg1 == ((u8 *)child)[0x51]) {
        func_150D278C(child->field_0, child->field_10, arg0->field_C, arg0->field_1);
    }
}
