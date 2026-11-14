#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1483E0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_dense_pointer_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1511B07C
 * - func_1511B51C
 * - func_1511B7D4
 * - func_1511BEBC
 * - func_1511CB44
 * - func_1511D394
 * - func_1511D9E4
 * - func_1511DF6C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

f32 fabsf(f32);
#pragma intrinsic(fabsf)
extern f32 D_800A3188;
extern f32 D_800A318C;
extern f32 D_800A3190;
extern f32 D_800A3194;

void func_1511AF30(void *arg0) {
    f32 scale = (f32) *(s32 *)((u8 *)arg0 + 0x3C);
    u32 roll;
    f32 diff;

    if (75.0f * scale * D_800A3188 != *(f32 *)((u8 *)arg0 + 0x7C)) {
        diff = 75.0f * scale * D_800A3188 - *(f32 *)((u8 *)arg0 + 0x7C);
        if (fabsf(diff) < 1.0f) {
            *(f32 *)((u8 *)arg0 + 0x7C) = 75.0f * scale * D_800A3188;
        } else {
            *(f32 *)((u8 *)arg0 + 0x7C) += (diff < 0.0f) ? -1 : 1;
        }
        *(f32 *)((u8 *)arg0 + 0x80) = 0.0f;
    } else {
        roll = func_150ADA20() % 1000U;
        if ((s32)roll < 0x1F4) {
            *(f32 *)((u8 *)arg0 + 0x84) = (s32)roll * 5.0f * scale * D_800A318C * D_800A3190;
        }
        diff = *(f32 *)((u8 *)arg0 + 0x84) - *(f32 *)((u8 *)arg0 + 0x80);
        *(f32 *)((u8 *)arg0 + 0x80) += diff * D_800A3194;
    }
    *(f32 *)((u8 *)arg0 + 0) = *(f32 *)((u8 *)arg0 + 0x80) + *(f32 *)((u8 *)arg0 + 0x7C);
}
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
    u32 unknown0C;
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

    coords = arg0->coords;
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
    for (i = 0; i < arg0->count; i++) {
        arg0->buffers[D_800BE9C0][i].s =
            (s16)(((f32)coords[i].s + s_offset) * s_scale + 1024.0f);
        arg0->buffers[D_800BE9C0][i].t =
            (s16)(((f32)coords[i].t + t_offset) * t_scale + 1024.0f);
    }
}


Game1483E0Reference *func_15083E90(u8);
void func_1511BB04(Game1483E0State *, f32, f32, f32, f32);

void func_1511BDF4(Game1483E0State *arg0) {
    Game1483E0Reference *reference;

    if (arg0->reference != 0) {
        reference = arg0->reference;
    } else {
        reference = func_15083E90(arg0->reference_id);
    }
    if (reference != 0) {
        func_1511BB04(arg0, reference->x, reference->z, 1.0f, 1.0f);
    }
}
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

void func_1511C548(void *arg0) {
    {
        f32 cosY;
        f32 sinX;

        sinX = func_15047D60(*(f32 *)((u8 *)arg0 + 0x80));
        cosY = func_15047D60(*(f32 *)((u8 *)arg0 + 0x84)) * 16.0f;
        *(f32 *)((u8 *)arg0 + 0) = sinX * 16.0f;
        *(f32 *)((u8 *)arg0 + 8) = cosY;
        *(f32 *)((u8 *)arg0 + 0x80) = *(f32 *)((u8 *)arg0 + 0x80) + D_800A31EC * D_800BE9A4;
        *(f32 *)((u8 *)arg0 + 0x84) = *(f32 *)((u8 *)arg0 + 0x84) + D_800A31F0 * D_800BE9A4;
        *(f32 *)((u8 *)arg0 + 0x80) = func_15144B68(*(f32 *)((u8 *)arg0 + 0x80));
        *(f32 *)((u8 *)arg0 + 0x84) = func_15144B68(*(f32 *)((u8 *)arg0 + 0x84));
    }
    if ((*(f32 *)((u8 *)arg0 + 8) == 0.0f) && (*(f32 *)((u8 *)arg0 + 0x84) == 0.0f)) {
        *(f32 *)((u8 *)arg0 + 0) = 7.5f;
        *(f32 *)((u8 *)arg0 + 8) = 8.0f;
    }
}
typedef struct Game1483E0SoundSet {
    u16 id[3];
} Game1483E0SoundSet;

void func_10010F30(s32, s32, s32, s32, s32);
void func_150B2740(s32, s32);
void func_15170F4C(u8 *, s32, s32);
void D_1000EC24(void);
extern Game1483E0SoundSet D_800A2F84;
extern s32 D_800BE9E4;
extern s32 D_800BE9F0;

void func_1511C638(void *arg0) {
    s32 state;
    u8 *child;
    u8 *other;
    u16 first;
    u16 second;
    Game1483E0SoundSet sounds;

    state = *((u8 *)arg0 + 0x73) & 3;
    child = (u8 *)arg0 + 0xA0;
    if (D_800BE9F0 == 4) {
        other = (u8 *)arg0 + 0x140;
    } else {
        other = NULL;
    }
    if (state == 1) {
        state = 0;
        *((u8 *)arg0 + 0x8A) = 0;
        child[0x6E] = 0;
        if (other != NULL) {
            other[0x6E] = 0;
        }
        if (*(s32 *)((u8 *)arg0 + 0x3C) != 0xFF) {
            func_15173C60(0, *(s32 *)((u8 *)arg0 + 0x3C));
        }
    }
    if (D_800BE9B4 != 0) {
        if (state == 3) {
            *((u8 *)arg0 + 0x8A) = 0xFF;
            child[0x6E] = 1;
            if (other != NULL) {
                other[0x6E] = 1;
            }
        } else {
            *((u8 *)arg0 + 0x8A) = 0;
            child[0x6E] = 0;
            if (other != NULL) {
                other[0x6E] = 0;
            }
        }
    }
    if (state == 2) {
        if (*(s32 *)((u8 *)arg0 + 0x7C) < 0) {
            *(s32 *)((u8 *)arg0 + 0x7C) += D_800BE9E4;
        } else {
            if (*(s32 *)((u8 *)arg0 + 0x80) == 0) {
                switch (*(s32 *)(child + 0x3C) & 0xFF) {
                case 1:
                    func_15170F4C(child, 0xFF, 0);
                    func_10010F30(0x2BE, 0x7FFF, 0x40, 0, 0);
                    break;
                case 0:
                    first = func_150ADA20() % 3;
                    sounds = D_800A2F84;
                    second = ((func_150ADA20() & 1) + first + 1) % 3;
                    first = sounds.id[first];
                    second = sounds.id[second];
                    func_10010F30(0x2B7, 0x7FFF, 0x40, 0, 0);
                    func_10010F30(first, 0x7FFF, 0xA, 0, 0);
                    func_10010F30(second, 0x7FFF, 0x36, 0, 0);
                    first = func_150ADA20() % 5;
                    second = ((func_150ADA20() & 3) + first + 1) % 5;
                    func_1000FA64((u16)(first + 0x2B1), *(s16 *)((u8 *)arg0 + 0x10), *(s16 *)((u8 *)arg0 + 0x12),
                                  *(s16 *)((u8 *)arg0 + 0x14), 0x4000, 0x2711, 0x2710, (void *)D_1000EC24, 0x1001E, 0, 0x200, 0);
                    func_1000FA64((u16)(second + 0x2B1), *(s16 *)((u8 *)arg0 + 0x10), *(s16 *)((u8 *)arg0 + 0x12),
                                  *(s16 *)((u8 *)arg0 + 0x14), 0x4000, 0x2711, 0x2710, (void *)D_1000EC24, 0x1001E, 0, 0, 0);
                    first = func_150ADA20() % 5;
                    second = ((func_150ADA20() & 3) + first + 1) % 5;
                    func_1000FA64((u16)(first + 0x2B1), *(s16 *)((u8 *)arg0 + 0x10), *(s16 *)((u8 *)arg0 + 0x12),
                                  *(s16 *)((u8 *)arg0 + 0x14), 0x4000, 0x2711, 0x2710, (void *)D_1000EC24, 0x3C, 0, 0x300, 0);
                    func_1000FA64((u16)(second + 0x2B1), *(s16 *)((u8 *)arg0 + 0x10), *(s16 *)((u8 *)arg0 + 0x12),
                                  *(s16 *)((u8 *)arg0 + 0x14), 0x4000, 0x2711, 0x2710, (void *)D_1000EC24, 0x3C, 0, 0x100, 0);
                    break;
                case 3:
                    func_150B2740((*(s32 *)(child + 0x3C) >> 8) & 0xFF, 0xFF);
                    break;
                case 2:
                    break;
                }
            }
            *((u8 *)arg0 + 0x8A) = 0xFF;
            child[0x6E] = 1;
            if (other != NULL) {
                other[0x6E] = 1;
            }
            *(s32 *)((u8 *)arg0 + 0x80) += D_800BE9E4 * 30;
            if (*(s32 *)((u8 *)arg0 + 0x80) >= 0xFF) {
                *(s32 *)((u8 *)arg0 + 0x80) = 0xFF;
                state = 3;
            }
            if (*(s32 *)((u8 *)arg0 + 0x3C) != 0xFF) {
                func_15173C60(*(s32 *)((u8 *)arg0 + 0x80), *(s32 *)((u8 *)arg0 + 0x3C));
            }
            if (state == 3) {
                *(s32 *)((u8 *)arg0 + 0x7C) = 0;
                *(s32 *)((u8 *)arg0 + 0x80) = 0;
            }
        }
    }
    *((u8 *)arg0 + 0x73) &= 0xFFFC;
    *((u8 *)arg0 + 0x73) |= state;
}
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

void func_1511D7BC(Game1483E0WaveMesh *arg0) {
    f32 sine;
    s32 index;
    Game1483E0UvPair *coords;
    struct {
        s32 speed;
        s32 amplitude_t;
        s32 amplitude_s;
    } parameters;
    s16 s_delta;
    s16 t_delta;
    f32 cosine;
    u8 angle;
    Game1483E0WaveState *state;

    state = arg0->wave;
    if (state == NULL) {
        state = func_10003C40(0xC, 1, 0, 0);
        arg0->wave = state;
        state->field4 = 0;
        state->field8 = 0;
        coords = func_10003C40(arg0->count * 4, 1, 0, 0);
        state->coords = coords;
        for (index = 0; index < arg0->count; index++) {
            coords[index].s = arg0->source[index].s;
            coords[index].t = arg0->source[index].t;
        }
    } else {
        coords = arg0->wave->coords;
    }
    parameters.amplitude_s = arg0->flags & 0xFFF;
    parameters.amplitude_t = (arg0->flags >> 12) & 0xFFF;
    parameters.speed = (arg0->flags >> 24) & 0xFF;
    angle = arg0->phase >> 4;
    cosine = func_15048A40(angle);
    sine = func_150489B0(angle);
    arg0->phase += parameters.speed * D_800BE9E4;
    s_delta = (f32)parameters.amplitude_s * sine;
    t_delta = (f32)parameters.amplitude_t * cosine;
    for (index = 0; index < arg0->count; index++) {
        arg0->buffers[D_800BE9C0][index].s = coords[index].s + s_delta;
        arg0->buffers[D_800BE9C0][index].t = coords[index].t + t_delta;
    }
    func_1511A494(arg0, &state->field4, &state->field8);
}
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

void func_1511DBC4(void *arg0) {
    s32 mode;
    f32 *state;

    if (*(f32 **)((u8 *)arg0 + 0x7C) == NULL) {
        state = func_10003C40(0x10, 1, 0, 0);
        *(f32 **)((u8 *)arg0 + 0x7C) = state;
        state[0] = 0.0f;
        state[1] = 0.0f;
        state[2] = 0.0f;
        state[3] = D_800A3210;
    } else {
        state = *(f32 **)((u8 *)arg0 + 0x7C);
    }
    mode = *(u8 *)((u8 *)arg0 + 0x73) & 3;
    if (mode == 0) {
        *(f32 *)((u8 *)arg0 + 8) = 0.0f;
    } else if (mode == 3) {
        *(f32 *)((u8 *)arg0 + 8) = 90.0f;
        *(f32 *)((u8 *)arg0 + 8) += func_15047C00(state[0] * D_800A3214) * 0.5f;
        state[0] += 3.0f * D_800BE9E4;
    } else if (mode == 2) {
        if (*(f32 *)((u8 *)arg0 + 8) == 0.0f) {
            state[1] = 0.0f;
            state[2] = 0.0f;
        }
        state[2] += state[3];
        state[1] += state[2];
        *(f32 *)((u8 *)arg0 + 8) += state[1];
        if (*(f32 *)((u8 *)arg0 + 8) >= 90.0f) {
            mode = 3;
            *(f32 *)((u8 *)arg0 + 8) = 90.0f;
        }
    } else if (D_800BE9E4 < *(f32 *)((u8 *)arg0 + 8)) {
        *(f32 *)((u8 *)arg0 + 8) -= D_800BE9E4;
    } else {
        *(f32 *)((u8 *)arg0 + 8) = 0.0f;
        mode = 0;
    }
    *(u8 *)((u8 *)arg0 + 0x73) &= ~3;
    *(u8 *)((u8 *)arg0 + 0x73) |= mode;
}
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
