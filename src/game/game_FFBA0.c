#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_FFBA0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_child_chain_render_lists.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D2924
 * - func_150D2D6C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

/* Call context: func_150D278C: unique active declaration in the allowed source */
void func_150D278C(s32, void *, u8, s32);
extern s32 D_800BE9E4;

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
#pragma GLOBAL_ASM("asm/nonmatchings/game_FFBA0/func_150D2924.s")
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D2D6C */
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
#endif /* CONKER_DEFERRED_CANDIDATE func_150D2D6C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FFBA0/func_150D2D6C.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800BE9A4;

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
