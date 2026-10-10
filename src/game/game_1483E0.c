#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1483E0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_dense_pointer_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1511AF30
 * - func_1511B07C
 * - func_1511B51C
 * - func_1511B7D4
 * - func_1511BB04
 * - func_1511BDF4
 * - func_1511BEBC
 * - func_1511C548
 * - func_1511C638
 * - func_1511CB44
 * - func_1511D394
 * - func_1511D7BC
 * - func_1511D9E4
 * - func_1511DBC4
 * - func_1511DF6C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

u32 func_150ADA20(void);                        /* extern */
f32 fabsf(f32);
#pragma intrinsic(fabsf)
extern f32 D_800A3188;
extern f32 D_800A318C;
extern f32 D_800A3190;
extern f32 D_800A3194;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1511AF30 CURRENT (791) */
void func_1511AF30(void *arg0) {
    f32 sp1C;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0_2;
    f32 temp_fv1;
    s32 var_v0;
    u32 temp_hi;
    f32 temp_fv0;

    temp_fv0 = (f32) *(s32 *)((u8 *)arg0 + 0x3C);
    temp_fa1 = *(f32 *)((u8 *)arg0 + 0x7C);
    temp_fa0 = 75.0f * temp_fv0 * D_800A3188;
    if (temp_fa0 != temp_fa1) {
        temp_fv1 = temp_fa0 - temp_fa1;
        if (fabsf(temp_fv1) < 1.0f) {
            *(f32 *)((u8 *)arg0 + 0x7C) = temp_fa0;
        } else {
            var_v0 = 1;
            if (temp_fv1 < 0.0f) {
                var_v0 = -1;
            }
            *(f32 *)((u8 *)arg0 + 0x7C) = (f32) (temp_fa1 + (f32) var_v0);
        }
        *(f32 *)((u8 *)arg0 + 0x80) = 0.0f;
    } else {
        sp1C = temp_fv0;
        temp_hi = func_150ADA20() % 1000U;
        if ((s32) temp_hi < 0x1F4) {
            *(f32 *)((u8 *)arg0 + 0x84) = (f32) ((f32) (s32) temp_hi * 5.0f * temp_fv0 * D_800A318C * D_800A3190);
        }
        temp_fv0_2 = *(f32 *)((u8 *)arg0 + 0x80);
        *(f32 *)((u8 *)arg0 + 0x80) = (f32) (temp_fv0_2 + ((*(f32 *)((u8 *)arg0 + 0x84) - temp_fv0_2) * D_800A3194));
    }
    *(f32 *)((u8 *)arg0 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0x7C) + *(f32 *)((u8 *)arg0 + 0x80));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1511AF30 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511AF30.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511B07C.s")
typedef struct Game1483E0Rotation {
    u8 pad0[8];
    f32 angle;
    u8 padC[0x30];
    s32 flags;
    u8 pad40[0x33];
    u8 mode;
    u8 pad74[8];
    f32 restitution, acceleration, velocity;
} Game1483E0Rotation;

f32 func_15048A70(f32, f32);
void func_15173C60(s32, s32);
void func_1518804C(s32, f32);
f32 fabsf(f32);
__pragma(1, fabsf);
extern f32 D_800A31BC, D_800A31C0, D_800A31C4, D_800A31C8;
extern u8 D_800BE9B4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1511B51C CURRENT (1528) */
void func_1511B51C(Game1483E0Rotation *arg0) {
    s32 target;
    s32 mode;
    f32 original;
    f32 desired, angle, velocity, restitution, acceleration;
    f32 difference, fraction;
    s32 sound, index;
    u32 flags;

    target = ((s16 *)&arg0->flags)[1];
    mode = arg0->mode & 3;
    original = (f32)target;
    desired = original;
    angle = arg0->angle;
    velocity = arg0->velocity;
    if ((mode == 0) || (mode == 1)) {
        desired = 0.0f;
    }
    if ((mode == 0) || (mode == 3)) {
        angle = desired;
        velocity = 0.0f;
    }
    if ((angle != desired) || (velocity != 0.0f)) {
        restitution = arg0->restitution;
        if (restitution == 0.0f) {
            restitution = D_800A31BC;
        }
        acceleration = arg0->acceleration;
        if (acceleration == 0.0f) {
            acceleration = 0.5f;
        }
        angle += velocity;
        difference = func_15048A70(angle, desired);
        if (fabsf(difference) < fabsf(velocity)) {
            velocity = -velocity * restitution;
            if (fabsf(velocity) < acceleration * D_800A31C0) {
                velocity = 0.0f;
                angle = desired;
                if (desired == 0.0f) {
                    mode = 0;
                } else {
                    mode = 3;
                }
            }
        } else if (difference > 0.0f) {
            velocity += (acceleration - velocity) * D_800A31C4;
        } else {
            velocity -= (acceleration + velocity) * D_800A31C8;
        }
        if (angle < 0.0f) {
            angle += 360.0f;
        } else if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        flags = arg0->mode & 0xFFFC;
        arg0->mode = flags;
        arg0->mode = flags | mode;
    }
    arg0->velocity = velocity;
    if ((D_800BE9B4 != 0) || (angle != arg0->angle)) {
        arg0->angle = angle;
        sound = (arg0->flags >> 24) & 0xFF;
        if ((sound != 0) && (target != 0)) {
            index = sound - 1;
            fraction = fabsf((angle - original) / original);
            func_1518804C(index, fraction);
            func_15173C60((s32)((1.0f - fraction) * 255.0f), index);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1511B51C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511B51C.s")

f32 func_15047C00(f32);
f32 func_15047D60(f32);
extern u8 D_800A2F70;
extern u8 D_800A2F71[];
extern f32 D_800A31CC;
extern u8 D_800BE9C0;

typedef struct Game1483E0RotateVertex {
    s16 x, y, z;
    u8 pad06[0xA];
} Game1483E0RotateVertex;

typedef struct Game1483E0RotateMesh {
    u8 pad00[8];
    f32 angle;
    u8 pad0C[4];
    s16 x, y, z;
    u8 pad16[0xA];
    Game1483E0RotateVertex *buffers[2];
    Game1483E0RotateVertex *source;
    u8 pad2C[0x10];
    s32 flags;
    u8 pad40[0x3C];
    s32 updates;
    f32 previous[2];
} Game1483E0RotateMesh;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1511B7D4 CURRENT (3548) */
void func_1511B7D4(Game1483E0RotateMesh *mesh) {
    u8 *saved_pairs;
    Game1483E0RotateMesh *neighbors[2];
    u8 *pairs;
    s32 count;
    s32 dx, dy;
    f32 angle, sine, cosine, scale;
    f32 x, y;
    Game1483E0RotateMesh *neighbor;
    Game1483E0RotateVertex *source;
    Game1483E0RotateVertex *output;
    s32 offset;
    s16 z;
    s32 rotated_x, rotated_y;

    count = 0;
    if (mesh->flags == 0) {
        count = D_800A2F70;
        neighbors[0] = (Game1483E0RotateMesh *)((u8 *)mesh - 0xA0);
        neighbors[1] = (Game1483E0RotateMesh *)((u8 *)mesh - 0x140);
        saved_pairs = D_800A2F71;
    }
    pairs = saved_pairs;
    if (mesh->previous[0] != neighbors[0]->angle ||
        mesh->previous[1] != neighbors[1]->angle) {
        mesh->previous[0] = neighbors[0]->angle;
        mesh->updates = 2;
        mesh->previous[1] = neighbors[1]->angle;
    }
    if (mesh->updates != 0) {
        mesh->updates--;
        if (count != 0) {
            count--;
            scale = D_800A31CC;
            do {
                neighbor = neighbors[pairs[1]];
                dx = neighbor->x - mesh->x;
                angle = -neighbor->angle * scale;
                dy = neighbor->y - mesh->y;
                sine = func_15047D60(angle);
                cosine = func_15047C00(angle);
                offset = pairs[0] * 0x10;
                source = (Game1483E0RotateVertex *)((u8 *)mesh->source + offset);
                y = (f32)(source->y - dy);
                x = (f32)(source->x - dx);
                output = (Game1483E0RotateVertex *)((u8 *)mesh->buffers[D_800BE9C0] + offset);
                z = source->z + mesh->z;
                rotated_y = (s32)(y * cosine - x * sine) + dy + mesh->y;
                rotated_x = (s32)(y * sine + x * cosine) + dx + mesh->x;
                pairs += 2;
                output->x = rotated_x;
                mesh->buffers[D_800BE9C0][pairs[-2]].y = rotated_y;
                mesh->buffers[D_800BE9C0][pairs[-2]].z = z;
            } while (count-- != 0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1511B7D4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511B7D4.s")

/* Call context: func_15188010: unique active project prototype */
void func_15188010(s32, f32 *);

void func_1511BA24(void *arg0) {
    f32 sp1C;

    sp1C = 0.0f;
    func_15188010(*(s32 *)((u8 *)arg0 + 0x3C), &sp1C);
    *(u8 *)((u8 *)arg0 + 0x8A) = (u32) (sp1C * 255.0f);
    if (*(u8 *)((u8 *)arg0 + 0x8A) == 0) {
        *(s8 *)((u8 *)arg0 + 0x8A) = 1;
    }
}
typedef struct Game1483E0Reference {
    u8 pad0[0x14];
    f32 x;
    u8 pad18[4];
    f32 z;
} Game1483E0Reference;

typedef struct Game1483E0UvVertex {
    s16 x, y, z;
    u8 unknown06[2];
    s16 s, t;
    u8 unknown0C[4];
} Game1483E0UvVertex;

typedef struct Game1483E0UvPair {
    s16 s, t;
} Game1483E0UvPair;

typedef struct Game1483E0State {
    u8 unknown00[0x10];
    s16 x, y, z;
    u16 count;
    u8 unknown18[8];
    Game1483E0UvVertex *buffers[2];
    Game1483E0UvVertex *source;
    u8 unknown2C[0x13];
    u8 reference_id;
    u8 unknown40[0x3C];
    Game1483E0UvPair *coords;
    Game1483E0Reference *reference;
} Game1483E0State;

void *func_10003C40(s32, s32, s32, s32);
extern u8 D_800BE9C0;
extern f32 D_800A31D0;
extern f32 D_800A31D4;
extern f32 D_800A31D8;
extern f32 D_800A31DC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1511BB04 CURRENT (6550) */
void func_1511BB04(Game1483E0State *arg0, f32 arg1, f32 arg2,
                   f32 arg3, f32 arg4) {
    Game1483E0UvPair *coords;
    s32 i;
    f32 s_offset;
    f32 t_offset;
    f32 s_scale;
    f32 t_scale;

    if (arg0->coords == 0) {
        coords = func_10003C40(arg0->count * 4, 1, 0, 0);
        arg0->coords = coords;
        for (i = 0; i < arg0->count; i++) {
            coords[i].s = arg0->source[i].s;
            coords[i].t = arg0->source[i].t;
            arg0->buffers[0][i] = arg0->source[i];
            arg0->buffers[1][i] = arg0->source[i];
            arg0->buffers[0][i].x += arg0->x;
            arg0->buffers[0][i].y += arg0->y;
            arg0->buffers[0][i].z += arg0->z;
            arg0->buffers[1][i].x += arg0->x;
            arg0->buffers[1][i].y += arg0->y;
            arg0->buffers[1][i].z += arg0->z;
        }
    }

    s_offset = arg1 - ((f32)arg0->x + D_800A31D0);
    t_offset = arg2 - ((f32)arg0->z + D_800A31D4);
    s_offset = -s_offset;
    s_offset *= D_800A31D8;
    t_offset *= D_800A31DC;
    s_offset -= 1024.0f;
    t_offset -= 1024.0f;
    s_scale = 1.0f;
    t_scale = 1.0f;
    if (arg3 != 1.0f) {
        s_scale = 1.0f / arg3;
    }
    if (arg4 != 1.0f) {
        t_scale = 1.0f / arg4;
    }
    coords = arg0->coords;
    for (i = 0; i < arg0->count; i++) {
        arg0->buffers[D_800BE9C0][i].s =
            (s16)(s32)(((f32)coords[i].s + s_offset) * s_scale + 1024.0f);
        arg0->buffers[D_800BE9C0][i].t =
            (s16)(s32)(((f32)coords[i].t + t_offset) * t_scale + 1024.0f);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1511BB04 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511BB04.s")

Game1483E0Reference *func_15083E90(u8);
void func_1511BB04(Game1483E0State *, f32, f32, f32, f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1511BDF4 CURRENT (605) */
void func_1511BDF4(Game1483E0State *arg0) {
    Game1483E0Reference *reference;

    reference = arg0->reference;
    reference = (reference != 0) ? reference : func_15083E90(arg0->reference_id);
    if (reference != 0) {
        func_1511BB04(arg0, reference->x, reference->z, 1.0f, 1.0f);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1511BDF4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511BDF4.s")
f32 func_150484A0(f32, f32);                        /* extern */
extern f32 D_800A31E0;
extern void *D_800DBFF0;

void func_1511BE5C(void *arg0) {
    *(f32 *)((u8 *)arg0 + 4) = (f32) (func_150484A0((f32) *(s16 *)((u8 *)arg0 + 0x10) - *(f32 *)((u8 *)D_800DBFF0 + 0x2F8), (f32) *(s16 *)((u8 *)arg0 + 0x14) - *(f32 *)((u8 *)D_800DBFF0 + 0x300)) * D_800A31E0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511BEBC.s")
void func_1511C540(void) {

}
f32 func_15047D60(f32);                             /* extern */
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800A31EC;
extern f32 D_800A31F0;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1511C548 CURRENT (60) */
void func_1511C548(void *arg0) {
    f32 temp_ft2;
    f32 sp20;

    sp20 = func_15047D60(*(f32 *)((u8 *)arg0 + 0x80));
    temp_ft2 = func_15047D60(*(f32 *)((u8 *)arg0 + 0x84)) * 16.0f;
    *(f32 *)((u8 *)arg0 + 0) = (f32) (sp20 * 16.0f);
    *(f32 *)((u8 *)arg0 + 8) = temp_ft2;
    *(f32 *)((u8 *)arg0 + 0x80) = (f32) (*(f32 *)((u8 *)arg0 + 0x80) + (D_800A31EC * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x84) = (f32) (*(f32 *)((u8 *)arg0 + 0x84) + (D_800A31F0 * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x80) = func_15144B68(*(f32 *)((u8 *)arg0 + 0x80));
    *(f32 *)((u8 *)arg0 + 0x84) = func_15144B68(*(f32 *)((u8 *)arg0 + 0x84));
    if ((*(f32 *)((u8 *)arg0 + 8) == 0.0f) && (*(f32 *)((u8 *)arg0 + 0x84) == 0.0f)) {
        *(f32 *)((u8 *)arg0 + 0) = 7.5f;
        *(f32 *)((u8 *)arg0 + 8) = 8.0f;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1511C548 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511C548.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511C638.s")
extern f32 D_800A31F4;

void func_1511CB2C(s32 arg0, f32 *arg1) {
    *arg1 = D_800A31F4;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511CB44.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511D394.s")
typedef struct Game1483E0WaveState {
    Game1483E0UvPair *coords;
    s32 field4;
    s32 field8;
} Game1483E0WaveState;

typedef struct Game1483E0WaveMesh {
    u8 pad0[0x16];
    u16 count;
    u8 pad18[8];
    Game1483E0UvVertex *buffers[2];
    Game1483E0UvVertex *source;
    u8 pad2C[0x10];
    s32 flags;
    u8 pad40[0x3C];
    Game1483E0WaveState *wave;
    s32 phase;
} Game1483E0WaveMesh;

void func_1511A494(void *, void *, void *);
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1511D7BC CURRENT (2638) */
void func_1511D7BC(Game1483E0WaveMesh *arg0) {
    f32 sine;
    s32 index;
    Game1483E0UvPair *coords;
    struct {
        s32 speed;
        s32 amplitude_t;
        s32 amplitude_s;
    } parameters;
    s32 flags;
    f32 cosine;
    u8 angle;
    Game1483E0WaveState *state;
    Game1483E0UvPair *cursor;
    Game1483E0UvPair *output;
    Game1483E0WaveState *existing;
    s32 offset;

    existing = arg0->wave;
    state = existing;
    if (existing == 0) {
        state = func_10003C40(0xC, 1, 0, 0);
        arg0->wave = state;
        state->field4 = 0;
        state->field8 = 0;
        coords = func_10003C40(arg0->count * 4, 1, 0, 0);
        state->coords = coords;
        index = 0;
        offset = 0;
        cursor = coords;
        if (arg0->count > 0) {
            do {
                index++;
                cursor++;
                cursor[-1].s = ((Game1483E0UvVertex *)((u8 *)arg0->source + offset))->s;
                cursor[-1].t = ((Game1483E0UvVertex *)((u8 *)arg0->source + offset))->t;
                offset += 0x10;
            } while (index < arg0->count);
        }
    } else {
        coords = existing->coords;
    }
    flags = arg0->flags;
    parameters.amplitude_s = flags & 0xFFF;
    parameters.amplitude_t = (flags >> 12) & 0xFFF;
    parameters.speed = (flags >> 24) & 0xFF;
    angle = (arg0->phase >> 4) & 0xFF;
    index = 0;
    cosine = func_15048A40(angle);
    sine = func_150489B0(angle);
    arg0->phase += parameters.speed * D_800BE9E4;
    if (arg0->count > 0) {
        output = coords;
        offset = 0;
        do {
            index++;
            ((Game1483E0UvVertex *)((u8 *)arg0->buffers[D_800BE9C0] + offset))->s =
                output->s + (s16)(s32)((f32)parameters.amplitude_s * sine);
            output++;
            ((Game1483E0UvVertex *)((u8 *)arg0->buffers[D_800BE9C0] + offset))->t =
                output[-1].t + (s16)(s32)((f32)parameters.amplitude_t * cosine);
            offset += 0x10;
        } while (index < arg0->count);
    }
    func_1511A494(arg0, &state->field4, &state->field8);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1511D7BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511D7BC.s")
typedef struct Game1483E0Vertex {
    s16 x, y, z, flag, s, t;
    u8 color[4];
} Game1483E0Vertex;
typedef struct Game1483E0Texcoord {
    s16 s, t;
} Game1483E0Texcoord;
typedef struct Game1483E0Mesh {
    u8 pad00[0x10];
    s16 x, y, z;
    u16 count;
    u8 pad18[8];
    Game1483E0Vertex *buffers[2];
    Game1483E0Vertex *source;
    u8 pad2C[0x10];
    s32 flags;
    u8 pad40[0x3C];
    Game1483E0Texcoord *coords;
    f32 phase;
} Game1483E0Mesh;
void *func_10003C40(s32, s32, s32, s32);
void func_15094AB8(s32, s32, s32, f32, s32, s32);
extern f64 D_800A3208;
extern u8 D_800BE9C0;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1511D9E4 CURRENT (1400) */
void func_1511D9E4(Game1483E0Mesh *arg0) {
    Game1483E0Texcoord *coords;
    Game1483E0Texcoord *cursor;
    s32 index;
    s32 flags;
    s32 offset;
    f32 delta;
    Game1483E0Texcoord *existing;
    Game1483E0Texcoord *allocated;
    s16 x, y, z;

    existing = arg0->coords;
    if (existing == 0) {
        allocated = func_10003C40(arg0->count * 4, 1, 0, 0);
        arg0->coords = allocated;
        coords = allocated;
        index = 0;
        offset = 0;
        cursor = allocated;
        while (index < arg0->count) {
            cursor->s = (*(Game1483E0Vertex *)((u8 *)arg0->source + offset)).s - 0x2000;
            cursor->t = (*(Game1483E0Vertex *)((u8 *)arg0->source + offset)).t - 0x2000;
            cursor++;
            index++;
            offset += 0x10;
        }
        index = 0;
        offset = 0;
        while (index < arg0->count) {
            x = (*(Game1483E0Vertex *)((u8 *)arg0->source + offset)).x + arg0->x;
            (*(Game1483E0Vertex *)((u8 *)arg0->buffers[1] + offset)).x = x;
            (*(Game1483E0Vertex *)((u8 *)arg0->buffers[0] + offset)).x = x;
            y = (*(Game1483E0Vertex *)((u8 *)arg0->source + offset)).y + arg0->y;
            (*(Game1483E0Vertex *)((u8 *)arg0->buffers[1] + offset)).y = y;
            (*(Game1483E0Vertex *)((u8 *)arg0->buffers[0] + offset)).y = y;
            z = (*(Game1483E0Vertex *)((u8 *)arg0->source + offset)).z + arg0->z;
            (*(Game1483E0Vertex *)((u8 *)arg0->buffers[1] + offset)).z = z;
            (*(Game1483E0Vertex *)((u8 *)arg0->buffers[0] + offset)).z = z;
            index++;
            offset += 0x10;
        }
    }
    else {
        coords = existing;
    }
    flags = arg0->flags;
    delta = (f32)((f64)(f32)(s16)flags * D_800A3208);
    arg0->phase += delta * (f32)D_800BE9E4;
    func_15094AB8((s32)arg0->buffers[D_800BE9C0], (s32)coords, arg0->count, arg0->phase, flags >> 24, (flags >> 16) & 0xFF);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1511D9E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511D9E4.s")
/* Call context: func_10003C40: unique active project prototype */
void * func_10003C40(s32, s32, s32, s32);
f32 func_15047C00(f32);                             /* extern */
extern f32 D_800A3210;
extern f32 D_800A3214;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1511DBC4 CURRENT (213) */
void func_1511DBC4(void *arg0) {
    f32 temp_fa0;
    f32 temp_fv1;
    s32 temp_t6;
    s32 temp_t1;
    s32 var_v0;
    void *var_v1;
    void *temp_v0;
    void *temp_v0_2;

    temp_v0 = *(void **)((u8 *)arg0 + 0x7C);
    if (temp_v0 == 0) {
        temp_v0_2 = func_10003C40(0x10, 1, 0, 0);
        *(void **)((u8 *)arg0 + 0x7C) = temp_v0_2;
        *(f32 *)((u8 *)temp_v0_2 + 0) = 0.0f;
        *(f32 *)((u8 *)temp_v0_2 + 4) = 0.0f;
        *(f32 *)((u8 *)temp_v0_2 + 8) = 0.0f;
        var_v1 = temp_v0_2;
        *(f32 *)((u8 *)temp_v0_2 + 0xC) = (f32) D_800A3210;
    } else {
        var_v1 = temp_v0;
    }
    temp_t6 = *(u8 *)((u8 *)arg0 + 0x73) & 3;
    var_v0 = temp_t6;
    if (temp_t6 == 0) {
        *(f32 *)((u8 *)arg0 + 8) = 0.0f;
    } else if (var_v0 == 3) {
        *(f32 *)((u8 *)arg0 + 8) = 90.0f;
        *(f32 *)((u8 *)arg0 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) + (func_15047C00(*(f32 *)((u8 *)var_v1 + 0) * D_800A3214) * 0.5f));
        *(f32 *)((u8 *)var_v1 + 0) = (f32) (*(f32 *)((u8 *)var_v1 + 0) + (3.0f * (f32) D_800BE9E4));
    } else if (var_v0 == 2) {
        if (*(f32 *)((u8 *)arg0 + 8) == 0.0f) {
            *(f32 *)((u8 *)var_v1 + 4) = 0.0f;
            *(f32 *)((u8 *)var_v1 + 8) = 0.0f;
        }
        *(f32 *)((u8 *)var_v1 + 8) = (f32) (*(f32 *)((u8 *)var_v1 + 8) + *(f32 *)((u8 *)var_v1 + 0xC));
        *(f32 *)((u8 *)var_v1 + 4) = (f32) (*(f32 *)((u8 *)var_v1 + 4) + *(f32 *)((u8 *)var_v1 + 8));
        *(f32 *)((u8 *)arg0 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) + *(f32 *)((u8 *)var_v1 + 4));
        if (*(f32 *)((u8 *)arg0 + 8) >= 90.0f) {
            var_v0 = 3;
            *(f32 *)((u8 *)arg0 + 8) = 90.0f;
        }
    } else {
        temp_fv1 = *(f32 *)((u8 *)arg0 + 8);
        temp_fa0 = (f32) D_800BE9E4;
        if (temp_fa0 < temp_fv1) {
            *(f32 *)((u8 *)arg0 + 8) = (f32) (temp_fv1 - temp_fa0);
        } else {
            *(f32 *)((u8 *)arg0 + 8) = 0.0f;
            var_v0 = 0;
        }
    }
    temp_t1 = *(u8 *)((u8 *)arg0 + 0x73) & 0xFFFC;
    *(volatile u8 *)((u8 *)arg0 + 0x73) = temp_t1;
    *(volatile u8 *)((u8 *)arg0 + 0x73) = (u8) (temp_t1 | var_v0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1511DBC4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511DBC4.s")
void func_10010630(u16, void *, s32, s32, s32);
void func_10010558(u16, void *, s32, s32, s32, s32);

void func_1511DD98(u8 *arg0, u8 *arg1) {
    s32 sound;
    s32 volume;
    s32 type_3B;
    s32 type_80;

    volume = 0x6590;
    type_3B = arg1[4] == 0x3B;
    type_80 = arg1[4] == 0x80;
    sound = 0;
    switch (*(u16 *)(arg0 + 0x54)) {
    case 0x39:
    case 0x5C:
    case 0x5D:
    case 0x5E:
        if (type_3B) {
            func_10010630(0x542, arg1, 0x6590, 100, 1000);
        } else if (type_80) {
            func_10010630(0x567, arg1, 0x6590, 100, 1000);
        }
        sound = 0x2B0;
        break;
    case 0x3A:
        if (type_3B) {
            sound = (func_150ADA20() & 1) + 0x53E;
        } else if (type_80) {
            sound = 0x567;
        } else {
            sound = 0x60A;
        }
        break;
    case 0x3B:
    case 0x51:
        sound = 0x181;
        break;
    case 0x3C:
    case 0x6A:
        sound = 0xB1;
        break;
    case 0x3D:
    case 0x6B:
        sound = 0x442;
        break;
    case 0x3E:
        sound = 0x444;
        break;
    case 0x46:
        sound = 0x2F0;
        break;
    case 0x47:
        sound = 0x4A3;
        break;
    case 0x50:
    case 0x55:
        sound = (func_150ADA20() & 1) + 0xB;
        break;
    case 0x52:
    case 0x58:
        sound = 0x510;
        break;
    case 0x53:
        sound = 0x2AF;
        if (type_80) {
            func_10010558(0x567, arg1, 0x7D00, 100, 1000, 30);
        }
        break;
    case 0x56:
        if (type_80) {
            func_10010630(0x567, arg1, 0x6590, 100, 1000);
        }
        sound = 0x5AE;
        break;
    case 0x57:
    case 0x6D:
    case 0x6E:
        sound = 0x51;
        volume = 0x2328;
        break;
    case 0x64:
    case 0x65:
        sound = 0x629;
        volume = 0x7FFF;
        break;
    }
    if (sound != 0) {
        func_10010630(sound, arg1, volume, 100, 1000);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1483E0/func_1511DF6C.s")
