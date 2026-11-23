#include "types.h"
#include <PR/gbi.h>
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1A48C0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_compact_display_resource_pairs.md
 */

typedef struct {
    f32 rotation[3];
    u8 unk_0C[4];
    s16 x;
    s16 y;
    s16 z;
    u16 vertexCount;
    u8 unk_18[8];
    Vtx *vertices[2];
    Vtx *baseVertices;
    f32 scale[3];
    u8 unk_38[0x37];
    u8 unk_6F;
} Game1A48C0Object;

typedef struct {
    u8 objectId;
    u8 flags;
    u8 shared;
    u8 unk_03;
    f32 unk_04;
    f32 unk_08;
    u16 unk_0C;
    s16 x;
    s16 y;
    s16 z;
    s16 unk_14;
    s8 unk_16;
    s8 unk_17;
    u8 unk_18[6];
    u8 unk_1E[2];
    f32 *unk_20;
    u8 *unk_24;
    u8 *unk_28;
} Game1A48C0Effect;

void func_150A6FA0(Vtx *, s32, f32 *, u8 *, f32 *, Vtx *);
void func_150A70C0(Vtx *, s32, f32 *, u8 *, Vtx *);
void func_150A71C8(Vtx *, s32, f32 *, u8 *, u8 *, Vtx *);
void func_150A7360(Vtx *, s32, f32 *, u8 *, u8 *, f32 *, Vtx *);
void func_150A751C(Vtx *, s32, f32 *, u8 *, u8 *, f32 *, Vtx *);
void func_150A7960(f32 (*)[4], f32, f32, f32, f32 *, f32 *, f32 *);
void func_1511490C(f32 (*)[4], Game1A48C0Object *);
void *func_10003C40(s32, s32, s32, s32);
f32 func_15047C00(f32);
f32 func_15047D60(f32);
f32 func_150484A0(f32, f32);
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
extern u8 D_800BE9C0;
extern Game1A48C0Effect *D_800DD410[];
extern u8 D_800DD418;

/* Register a vertex effect on an object and precompute its per-vertex weights. */
void func_15177410(u8 flags, u8 objectId, s16 x, s16 y, s16 z, f32 angle, u16 radius, f32 strength, s8 unk_16,
                   s8 unk_17, u8 arg10, u8 arg11, u8 arg12, u8 arg13, u8 arg14, u8 arg15) {
    Game1A48C0Effect *effect;
    Game1A48C0Object *object;
    s32 i;
    s32 shared;
    f32 scale;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 delta[3];
    Game1A48C0Effect *other;
    s32 distance;
    s32 weight;
    f32 length;
    f32 sine;
    f32 cosine;
    f32 rad;
    u8 value;

    effect = func_10003C40(sizeof(Game1A48C0Effect), 1, 0, 0);
    if (effect != NULL) {
        D_800DD410[D_800DD418++] = effect;
        object = func_151149AC(objectId);
        effect->objectId = objectId;
        effect->flags = flags;
        shared = 0;
        for (i = 0; i < D_800DD418 - 1; i++) {
            other = D_800DD410[i];
            if (other->objectId == objectId) {
                shared = 1;
                break;
            }
        }
        effect->shared = shared;
        delta[0] = x - object->x;
        delta[1] = y - object->y;
        delta[2] = z - object->z;
        effect->x = delta[0];
        effect->y = delta[1];
        effect->z = delta[2];
        effect->unk_0C = radius;
        effect->unk_08 = strength;
        effect->unk_14 = 0;
        effect->unk_16 = unk_16;
        effect->unk_17 = unk_17;
        if (radius != 0) {
            scale = 0.01f;
            length = radius * scale;
            effect->unk_04 = 1.0f / (length * length);
        } else {
            effect->unk_04 = 0.0f;
            scale = 0.01f;
        }
        if ((flags & 3) == 1) {
            effect->unk_18[0] = arg10;
            effect->unk_18[1] = arg11;
            effect->unk_18[2] = arg12;
            effect->unk_18[3] = arg13;
            effect->unk_18[4] = arg14;
            effect->unk_18[5] = arg15;
        }
        effect->unk_24 = func_10003C40(object->vertexCount, 1, 0, 0);
        if ((flags & 3) == 2) {
            effect->unk_28 = func_10003C40(object->vertexCount, 1, 0, 0);
        }
        if ((flags & 4) == 4) {
            effect->unk_20 = func_10003C40(object->vertexCount * 4, 1, 0, 0);
        }
        if ((flags & 0x10) == 0x10) {
            rad = -angle * 0.017453292f;
            cosine = func_15047D60(rad);
            sine = func_15047C00(rad);
            value = angle * 0.7111111f;
        }
        for (i = 0; i < object->vertexCount; i++) {
            if ((flags & 0x10) == 0) {
                dx = object->baseVertices[i].v.ob[0] - delta[0];
                dy = object->baseVertices[i].v.ob[1] - delta[1];
                dz = object->baseVertices[i].v.ob[2] - delta[2];
                dx *= dx;
                dy *= dy;
                dz *= dz;
                length = dx + dy + dz;
                if (length != 0.0f) {
                    length = sqrtf(length);
                }
                distance = length * scale;
                weight = distance;
            } else if ((flags & 0x10) == 0x10) {
                dx = object->baseVertices[i].v.ob[0] - delta[0];
                dz = object->baseVertices[i].v.ob[2] - delta[2];
                dz = -dx * cosine + dz * sine;
                distance = dz * scale;
                weight = distance;
                if (distance < 0) {
                    distance = -distance;
                }
            }
            effect->unk_24[i] = unk_17 * weight;
            if ((flags & 4) == 4) {
                distance = distance - radius * scale;
                if (distance >= 0) {
                    effect->unk_20[i] = 0;
                } else {
                    effect->unk_20[i] = effect->unk_04 * strength * (distance * distance);
                }
            }
            if ((flags & 3) == 2) {
                if ((flags & 0x10) == 0x10) {
                    effect->unk_28[i] = value;
                    continue;
                }
                length = func_150484A0(dx, dz);
                effect->unk_28[i] = length * 40.743664f;
            }
        }
    }
}

/* Apply each active vertex effect, then refresh unshared object vertices from their transforms. */
void func_15177A94(void) {
    s32 i;
    s32 j;
    Game1A48C0Effect *effect;
    Game1A48C0Object *object;
    f32 transform[4][4];
    f32 x;
    f32 y;
    f32 z;
    Vtx *source;

    for (i = 0; i < D_800DD418; i++) {
        effect = D_800DD410[i];
        object = func_151149AC(effect->objectId);
        if (!(object->unk_6F & 0xF)) {
            continue;
        }
        if (effect->shared == 0) {
            source = object->baseVertices;
        } else {
            source = object->vertices[D_800BE9C0];
        }
        if ((effect->flags & 3) == 1) {
            if ((effect->flags & 4) == 4) {
                func_150A7360(object->vertices[D_800BE9C0], object->vertexCount, &effect->unk_04,
                              effect->unk_18, effect->unk_24, effect->unk_20, source);
            } else {
                func_150A71C8(object->vertices[D_800BE9C0], object->vertexCount, &effect->unk_04,
                              effect->unk_18, effect->unk_24, source);
            }
        } else if ((effect->flags & 3) == 0) {
            if ((effect->flags & 4) == 4) {
                func_150A6FA0(object->vertices[D_800BE9C0], object->vertexCount, &effect->unk_04,
                              effect->unk_24, effect->unk_20, source);
            } else {
                func_150A70C0(object->vertices[D_800BE9C0], object->vertexCount, &effect->unk_04,
                              effect->unk_24, source);
            }
        } else if ((effect->flags & 3) == 2) {
            if ((effect->flags & 4) == 4) {
                func_150A751C(object->vertices[D_800BE9C0], object->vertexCount, &effect->unk_04,
                              effect->unk_28, effect->unk_24, effect->unk_20, source);
            }
        }
    }
    for (i = 0; i < D_800DD418; i++) {
        effect = D_800DD410[i];
        object = func_151149AC(effect->objectId);
        if (object->unk_6F & 0xF) {

            if (effect->shared == 0) {
                object = func_151149AC(effect->objectId);
                if (object->rotation[0] == 0.0f && object->rotation[1] == 0.0f && object->rotation[2] == 0.0f &&
                    object->scale[0] == 1.0f && object->scale[1] == 1.0f && object->scale[2] == 1.0f) {
                    for (j = 0; j < object->vertexCount; j++) {
                        object->vertices[D_800BE9C0][j].v.ob[0] = object->baseVertices[j].v.ob[0] + object->x;
                        object->vertices[D_800BE9C0][j].v.ob[1] = object->vertices[D_800BE9C0][j].v.ob[1] + object->y;
                        object->vertices[D_800BE9C0][j].v.ob[2] = object->baseVertices[j].v.ob[2] + object->z;
                    }
                } else {
                    func_1511490C(transform, object);
                    for (j = 0; j < object->vertexCount; j++) {
                        func_150A7960(transform, object->baseVertices[j].v.ob[0],
                                      object->vertices[D_800BE9C0][j].v.ob[1], object->baseVertices[j].v.ob[2],
                                      &x, &y, &z);
                        object->vertices[D_800BE9C0][j].v.ob[0] = x;
                        object->vertices[D_800BE9C0][j].v.ob[1] = y;
                        object->vertices[D_800BE9C0][j].v.ob[2] = z;
                    }
                }
            }
        }
    }
}
