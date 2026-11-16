#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_147C70.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_direct_helper_pairs.md
 */

typedef struct {
    u8 *bytes;
    f32 *values;
    f32 *rates;
    f32 *scales;
    f32 field_10;
    f32 field_14;
    f32 field_18;
    u8 field_1C;
    u8 field_1D;
    u8 field_1E;
    s32 field_20;
    s32 field_24;
} Game147C70Output;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u16 flags;
    u8 pad8[8];
} Game147C70Vertex;

typedef struct {
    u8 pad0[0x16];
    u16 value_count;
    u8 pad18[8];
    Game147C70Vertex *lists[2];
    Game147C70Vertex *vertices;
    u8 pad2C[0x10];
    s32 packed3C;
    u8 pad40[0x33];
    u8 flags73;
    u8 pad74[0xC];
    Game147C70Output *output;
    s32 packed84;
} Game147C70State;

void func_1511A7C0(Game147C70State *arg0) {
    s32 offset;
    s32 index;
    Game147C70Output *output;

    output = arg0->output;
    output->field_1E = 1;
    output->field_10 = 0.0f;
    output->field_1C = 0;
    output->field_1D = 7;
    output->field_14 = 260.0f;
    output->field_18 = 100.0f;
    index = 0;
    offset = 0;
    if ((s32)arg0->value_count > 0) {
        do {
            index += 1;
            *(f32 *)((u8 *)output->values + offset) = 0.0f;
            offset += sizeof(f32);
        } while (index < (s32)arg0->value_count);
    }
}
void *func_10003C40(s32, s32, s32, s32);
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
void func_1511490C(void *, void *);
void func_1511A494(void *, void *, void *);
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
extern s32 D_800BE9E4;
extern u8 D_800BE9C0;

void func_1511A838(Game147C70State *arg0) {
    s32 i;
    s32 j;
    f32 matrix[16];
    f32 x;
    f32 y;
    f32 z;
    f32 scale;
    f32 inv;
    f32 factor;
    f32 offsetX;
    f32 offsetZ;
    s32 old;
    u8 shift[4];
    u8 *bytes;
    f32 *values;
    f32 *rates;
    f32 *scales;
    Game147C70Vertex *vertices;
    Game147C70Output *output;
    s32 offsetY;
    f32 radius;
    f32 dist;
    u8 angle;
    s32 lane;
    Game147C70Vertex *list;
    f32 dx;
    f32 dz;

    vertices = arg0->vertices;
    scale = arg0->packed3C & 0xFF;
    if (arg0->output == NULL) {
        arg0->output = func_10003C40(0x28, 1, 0, 0);
        output = arg0->output;
        output->bytes = bytes = func_10003C40(arg0->value_count, 1, 0, 0);
        output->values = func_10003C40(arg0->value_count * 4, 1, 0, 0);
        values = output->values;
        output->rates = rates = func_10003C40(arg0->value_count * 4, 1, 0, 0);
        output->scales = scales = func_10003C40(arg0->value_count * 4, 1, 0, 0);
        radius = (arg0->packed3C >> 16) & 0xFFFF;
        if (radius == 0.0f) {
            inv = 1.0f;
        } else {
            inv = 1.0f / radius;
        }
        for (i = 0; i < arg0->value_count; i++) {
            bytes[i] = func_150ADA20() % 255;
            dx = vertices[i].x;
            dz = vertices[i].z;
            dx *= dx;
            dz *= dz;
            dist = sqrtf(dx + dz);
            scales[i] = (radius - dist) * inv;
            rates[i] = (radius - dist * 1.2f) * inv;
            if (rates[i] < 0.0f) {
                rates[i] = 0.0f;
            }
        }
        for (i = 0; i < arg0->value_count; i++) {
            bytes[i] = func_150ADA20();
            for (j = 0; j < arg0->value_count; j++) {
                if (vertices[i].x == vertices[j].x && vertices[i].y == vertices[j].y && vertices[i].z == vertices[j].z) {
                    bytes[j] = bytes[i];
                }
            }
        }
        output->field_10 = 0.0f;
        output->field_1E = 0;
        for (i = 0; i < arg0->value_count; i++) {
            values[i] = 0.0f;
        }
        output->field_20 = 0;
        output->field_24 = 0;
    }
    bytes = arg0->output->bytes;
    values = arg0->output->values;
    rates = arg0->output->rates;
    output = arg0->output;
    scales = arg0->output->scales;
    if ((arg0->flags73 & 3) == 3) {
        func_1511A7C0(arg0);
        arg0->flags73 &= ~3;
    }
    if (output->field_1E != 0) {
        old = output->field_1C;
        output->field_1C += output->field_1D * D_800BE9E4;
        if (output->field_14 < output->field_18) {
            factor = 0.5f;
        } else {
            factor = 0.8f;
        }
        if (output->field_1C < old || (output->field_1C >= 0x81 && old < 0x81)) {
            output->field_14 *= factor;
        }
        output->field_10 = func_15048A40(output->field_1C);
        output->field_10 = output->field_14 * output->field_10;
        if (output->field_14 <= 3.0f) {
            output->field_10 = 0.0f;
            output->field_1E = 0;
        }
        for (i = 0; i < arg0->value_count; i++) {
            f32 delta = output->field_10 - values[i];

            values[i] += delta * rates[i];
        }
    }
    func_1511490C(matrix, arg0);
    list = arg0->lists[D_800BE9C0];
    shift[0] = arg0->packed84 & 0xFF;
    shift[1] = (arg0->packed84 >> 8) & 0xFF;
    shift[2] = (arg0->packed84 >> 16) & 0xFF;
    shift[3] = (arg0->packed84 >> 24) & 0xFF;
    offsetY = 0;
    for (i = 0; i < arg0->value_count; i++, list++, vertices++) {
        if (!(list->flags & 0x4000)) {
            lane = bytes[i] & 3;
            angle = bytes[i] + shift[lane];
            if (bytes[i] & 0x80) {
                angle = -angle;
            }
            offsetX = func_15048A40(angle) * scale;
            offsetZ = func_150489B0(angle) * scale;
            if (output->field_1E != 0) {
                offsetY = values[i] * scales[i];
            }
            func_150A7960(matrix, vertices->x + offsetX, vertices->y + offsetY, vertices->z + offsetZ, &x, &y, &z);
        } else {
            func_150A7960(matrix, vertices->x, vertices->y, vertices->z, &x, &y, &z);
        }
        list->x = x;
        list->y = y;
        list->z = z;
    }
    shift[0] += 1;
    shift[1] += 2;
    shift[2] += 3;
    shift[3] += 4;
    arg0->packed84 = shift[0] | (shift[1] << 8) | (shift[2] << 16) | (shift[3] << 24);
    func_1511A494(arg0, &output->field_20, &output->field_24);
}
