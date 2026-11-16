#include "types.h"
#include "game_functions.h"
#ifndef F3DEX_GBI_2
#define F3DEX_GBI_2
#endif
#include <PR/mbi.h>

/*
 * Reviewed source unit: src/game/game_1E26F0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_radial_queue_render_groups.md
 */

void *func_10022EC0(void *, const void *, u32);
s32 func_15083E90(u8);
extern f32 D_800AA418;

s32 func_151B5240(s16 arg0, u8 arg1, s32 arg2) {
    s32 temp_v0;
    f32 temp_fv0;
    u8 packet[0x5A8];

    packet[0x584] = 0x17;
    packet[0x58C] = 0x16;
    *(s32 *)(packet + 0x580) = func_15083E90(0x17);
    *(s32 *)(packet + 0x588) = func_15083E90(packet[0x58C]);
    temp_fv0 = 250.0f;
    *(f32 *)(packet + 0x598) = temp_fv0;
    *(f32 *)(packet + 0x590) = 18.0f;
    *(f32 *)(packet + 0x594) = 0.0f;
    *(f32 *)(packet + 0x5A0) = D_800AA418;
    *(f32 *)(packet + 0x59C) = 1.0f / temp_fv0;
    temp_v0 = func_15149130(arg0, -1, -1, 1, 1, 0x15, 0x5A8, arg1, arg2);
    if (temp_v0 != 0) {
        func_10022EC0((void *)(temp_v0 + 0x28), packet, 0x5A8);
    }
    return temp_v0;
}
typedef struct {
    s32 first;
    s32 second;
    u8 firstFlag;
    u8 secondFlag;
} Game1E26F0Pair;

typedef struct {
    s16 x, y, z;
    s16 flag;
    s16 s, t;
    u8 r, g, b, a;
} Game1E26F0Vertex;

typedef struct {
    Game1E26F0Vertex vertices[2][44];
    s32 first;
    u8 firstFlag;
    u8 pad585[3];
    s32 second;
    u8 secondFlag;
    u8 pad58D[3];
    f32 width;
    f32 fadeStart;
    f32 fadeEnd;
    f32 fadeScale;
    f32 fadeMax;
} Game1E26F0State;
f32 func_15047D60(f32);
void func_15143134(f32 *, f32 *, s32);
s32 func_15142E24(s32, s32, s32, s32, s32, s32, s32, u8, s32, u8 *, s32);
Gfx *func_15142B7C(Gfx *, s32, s32);
Gfx *func_15142C10(Gfx *, s32, s32, s32, s32, u8 *);
Gfx *func_15142CF0(Gfx *, s32, s32, s32, s32, s32, s32, u8 *);
Gfx *func_1513F4E4(Gfx *, u8, u8 *);
Gfx *func_15142FBC(Gfx *, s32, s32, u8 *);
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
extern u8 D_8008FB80;
extern u8 D_8008FB84;
extern u8 D_80090F68[];
extern s32 D_800A4AC8[][2];
extern f32 D_800AA400[];
extern f32 D_800AA40C[];
extern u8 D_800BE9C0;
extern s32 D_800D2C9C;
extern u8 *D_800DBFF0;

Gfx *func_151B5328(Gfx *gdl, u8 *arg1, s16 arg2) {
    Game1E26F0State *state;
    u8 failed;
    u8 changed;
    s32 i;
    Game1E26F0Vertex *vtx;
    Vec3f *pos;
    f32 lenSq;
    f32 inv;
    Vec3f perp;
    f32 w;
    Vec3f start;
    Vec3f end;
    Vec3f dir;
    f32 dx, dy, dz;
    Vec3f cur;
    f32 t;
    f32 count;
    f32 length;
    f32 fade;
    f32 stepX, stepY, stepZ;
    f32 angle;
    f32 mag;
    f32 wave;

    failed = 0;
    state = (Game1E26F0State *)(arg1 + 0x28);
    if (*(s32 *)state->first == 0 || state->firstFlag != *(u8 *)(state->first + 0x3B)) {
        failed = 1;
    }
    if (*(s32 *)state->second == 0 || state->secondFlag != *(u8 *)(state->second + 0x3B)) {
        failed = 1;
    }
    if (!failed && *(s32 *)(state->first + 0x1D4) != 0 && *(s32 *)(state->second + 0x1D4) != 0) {
        func_15143134(D_800AA400, &start.x, *(s32 *)(state->first + 0x1D4) + (D_8008FB80 << 6));
        func_15143134(D_800AA40C, &end.x, *(s32 *)(state->second + 0x1D4) + (D_8008FB84 << 6));
        changed = 1;
        vtx = state->vertices[D_800BE9C0];
        pos = (Vec3f *)(D_800DBFF0 + arg2 * 0x9A0 + 0x2F8);
        gdl = func_15142B7C(gdl, 0x200005, 0x60600);
        gdl = (Gfx *)func_15142E24((s32)gdl, (s32)D_80090F68, 0, 0, 0, 0, 0x56, 0, 0, &changed, 3);
        gdl = func_15142C10(gdl, 0xFF, 0xFF, 0xFF, 0xFF, &changed);
        gdl = func_15142CF0(gdl, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF, &changed);
        gdl = func_1513F4E4(gdl, 0x2E, &changed);
        gdl = func_15142FBC(gdl, D_800D2C9C | 0x80000 | 0x2000 | 0xC00 | 0x80 | 0x20, D_800A4AC8[5][0] | D_800A4AC8[5][1], &changed);
        dir.x = end.x - start.x;
        dir.y = end.y - start.y;
        dir.z = end.z - start.z;
        length = func_15143E64(&dir);
        dx = dir.x * 0.5f + start.x - pos->x;
        dy = dir.y * 0.5f + start.y - pos->y;
        dz = dir.z * 0.5f + start.z - pos->z;
        perp.x = dir.y * dz - dy * dir.z;
        perp.y = dir.z * dx - dz * dir.x;
        perp.z = dir.x * dy - dx * dir.y;
        lenSq = perp.x * perp.x + perp.y * perp.y + perp.z * perp.z;
        if (lenSq == 0.0f) {
            perp.x = 0.0f;
            perp.y = 0.0f;
            perp.z = 0.0f;
        } else {
            mag = sqrtf(lenSq);
            inv = state->width / mag;
            perp.x *= inv;
            perp.y *= inv;
            perp.z *= inv;
        }
        stepX = dir.x * 0.1f;
        stepY = dir.y * 0.1f;
        stepZ = dir.z * 0.1f;
        if (length < state->fadeStart) {
            fade = 0.0f;
        } else if (length < state->fadeEnd) {
            fade = (length - state->fadeStart) * state->fadeScale * state->fadeMax;
        } else {
            fade = state->fadeMax;
        }
        i = 0;
        cur = start;
        angle = 0.0f;
        t = 0.0f;
        count = 0.0f;
        do {
            wave = func_15047D60(angle);
            w = 1.0f - wave * fade;
            vtx[0].x = perp.x * w + cur.x;
            vtx[0].y = perp.y * w + cur.y;
            vtx[0].z = perp.z * w + cur.z;
            vtx[0].r = 0xFF;
            vtx[0].g = 0;
            vtx[0].b = 0;
            vtx[0].a = 0xFF;
            vtx[0].s = 0;
            vtx[0].t = t;
            vtx[1].x = cur.x - perp.x * w;
            vtx[1].y = cur.y - perp.y * w;
            vtx[1].z = cur.z - perp.z * w;
            vtx[1].r = 0xFF;
            vtx[1].g = 0;
            vtx[1].b = 0;
            vtx[1].a = 0xFF;
            vtx[1].s = 0x7C0;
            vtx[1].t = t;
            vtx += 2;
            wave = func_15047D60(angle + 0.31415927f);
            w = 1.0f - wave * fade;
            vtx[0].x = cur.x + stepX - perp.x * w;
            vtx[0].y = cur.y + stepY - perp.y * w;
            vtx[0].z = cur.z + stepZ - perp.z * w;
            vtx[0].r = 0xFF;
            vtx[0].g = 0;
            vtx[0].b = 0;
            vtx[0].a = 0xFF;
            vtx[0].s = 0x7C0;
            vtx[0].t = t + 204.8f;
            vtx[1].x = cur.x + stepX + perp.x * w;
            vtx[1].y = cur.y + stepY + perp.y * w;
            vtx[1].z = cur.z + stepZ + perp.z * w;
            vtx[1].r = 0xFF;
            vtx[1].g = 0;
            vtx[1].b = 0;
            vtx[1].a = 0xFF;
            vtx[1].s = 0;
            vtx[1].t = t + 204.8f;
            vtx += 2;
            gSPVertex(gdl++, vtx - 4, 4, 0);
            gSP1Triangle(gdl++, 0, 1, 2, 0);
            gSP1Triangle(gdl++, 0, 2, 3, 0);
            cur.x += stepX;
            cur.y += stepY;
            cur.z += stepZ;
            angle += 0.31415927f;
            t += 204.8f;
            count += 0.1f;
            i++;
        } while (i != 10);
    }
    if (failed) {
        *(s16 *)(arg1 + 0xE) = -1;
    }
    return gdl;
}

void func_151B5A9C(u8 *arg0, void *arg1, u8 arg2) {
    Game1E26F0State *state = (Game1E26F0State *)(arg0 + 0x28);

    if (arg2 == 0x2D) {
        Game1E26F0Pair *pair = arg1;

        if (state->first == pair->first) {
            state->first = pair->second;
            state->firstFlag = pair->secondFlag;
        } else if (state->first == pair->second) {
            state->first = pair->first;
            state->firstFlag = pair->firstFlag;
        }
        if (state->second == pair->first) {
            state->second = pair->second;
            state->secondFlag = pair->secondFlag;
        } else if (state->second == pair->second) {
            state->second = pair->first;
            state->secondFlag = pair->firstFlag;
        }
    } else if (arg2 == 0) {
        s32 current = *(s32 *)arg1;

        if (current == state->first || current == state->second ||
            state->firstFlag == ((u8 *)arg1)[4] || state->secondFlag == ((u8 *)arg1)[4]) {
            func_1516972C(arg0);
        }
    }
}
