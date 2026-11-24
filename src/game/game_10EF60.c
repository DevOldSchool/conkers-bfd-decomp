#include "types.h"
#ifndef F3DEX_GBI_2
#define F3DEX_GBI_2
#endif
#include <PR/mbi.h>
#include "game_view.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_10EF60.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_path_owner_lifecycles.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E1D14
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    s16 pos[3];
    s16 zero;
    s16 u;
    s16 v;
    u8 padC[4];
} Game10EF60Vertex;

typedef struct {
    u8 pad0[0x10];
    Game10EF60Vertex quads[2][4];
    s16 lifetime;
    u8 pad92[2];
    f32 x, y, z;
    f32 pitch, yaw;
    f32 scale, speed;
    f32 target_x, target_y, target_z;
    f32 range, rate;
    f32 dx, dy, dz;
    s8 mode;
    u8 padD1;
    s16 fieldD2, fieldD4, fieldD6;
    s16 material;
    u8 fieldDA, fieldDB;
    s32 owner;
    s16 timeout;
    u8 fieldE2, fieldE3;
    f32 fieldE4, fieldE8, fieldEC, fieldF0, fieldF4, fieldF8;
    u8 fieldFC, fieldFD, fieldFE, padFF;
} Game10EF60Effect;

typedef struct {
    u8 pad0[6];
    u16 width;
    u16 height;
} Game10EF60Texture;

extern Game10EF60Texture *D_8008CA4C[];
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
f32 func_150484A0(f32, f32);

void func_150E1AB0(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, s16 arg11, u16 arg12, s8 arg13, s16 arg14, s16 arg15, s32 arg16, u8 arg17, u8 arg18, s32 arg19, u8 arg20, u8 arg21, f32 arg22, f32 arg23, f32 arg24, f32 arg25, f32 arg26, f32 arg27) {
    Game10EF60Effect *effect;
    s32 width;
    s32 height;
    s32 i;

    effect = func_15167A68(0xB, 0, 0x100, 1, 0xFF, 1);
    if (effect != NULL) {
        effect->lifetime = arg11;
        effect->x = arg1;
        effect->y = arg2;
        effect->z = arg3;
        effect->yaw = func_150484A0(-(arg4 - arg1), -(arg6 - arg3));
        effect->pitch = func_150484A0(arg5 - arg2, sqrtf((arg4 - arg1) * (arg4 - arg1) + (arg6 - arg3) * (arg6 - arg3)));
        effect->dx = 0.0f;
        effect->dy = 0.0f;
        effect->dz = 0.0f;
        effect->target_x = arg4;
        effect->target_y = arg5;
        effect->target_z = arg6;
        effect->speed = arg8;
        effect->scale = arg7;
        effect->range = arg9;
        effect->rate = arg10;
        effect->fieldE3 = 0;
        effect->fieldFC = arg20;
        effect->fieldFD = 0;
        effect->fieldFE = arg21;
        effect->owner = arg16;
        effect->material = arg12;
        effect->mode = arg13;
        if (effect->mode != 0) {
            if (arg16 == 0) {
                func_1516979C(effect);
                return;
            }
            effect->fieldD2 = arg14;
            effect->fieldD6 = -arg15;
            effect->fieldD4 = arg15;
            effect->fieldDA = arg17;
            effect->fieldE2 = arg18;
            effect->timeout = arg19;
            effect->fieldE4 = arg22;
            effect->fieldE8 = arg23;
            effect->fieldEC = arg24;
            effect->fieldF0 = arg25;
            effect->fieldF4 = arg26;
            effect->fieldF8 = arg27;
        } else {
            effect->fieldD6 = 1;
            effect->timeout = -1;
        }
        for (i = 0; i < 2; i++) {
            width = (D_8008CA4C[effect->material]->width - 1) << 5;
            height = (D_8008CA4C[effect->material]->height - 1) << 5;
            effect->quads[i][2].u = 0x2000;
            effect->quads[i][2].v = 0x2000;
            effect->quads[i][2].zero = 0;
            effect->quads[i][0].u = width + 0x2000;
            effect->quads[i][0].v = 0x2000;
            effect->quads[i][0].zero = 0;
            effect->quads[i][3].u = 0x2000;
            effect->quads[i][3].v = height + 0x2000;
            effect->quads[i][3].zero = 0;
            effect->quads[i][1].u = width + 0x2000;
            effect->quads[i][1].v = height + 0x2000;
            effect->quads[i][1].zero = 0;
        }
        effect->fieldDB = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_10EF60/func_150E1D14.s")
typedef struct Game10EF60Owner {
    u8 pad0[0x10];
    void *output;
} Game10EF60Owner;

s32 func_15094F70(s32, void *, s32, void *, s32, s32, s32, s32, s32);
Gfx *func_15142FBC(Gfx *, s32, s32, u8 *);
extern u8 D_800BE9C0;
extern s32 D_800D2C9C;

Gfx *func_150E28DC(Gfx *arg0, Game10EF60Effect *arg1, s16 arg2) {
    Vec3f points[2];
    f32 camera[3];
    f32 normal[3];
    f32 delta[3];
    s32 i;
    s32 j;
    f32 corners[4][3];
    f32 length;
    f32 scale;
    f32 temp;
    f32 distances[2];
    f32 range;
    Game10EF60Owner owner;
    u8 flag;

    if (arg1->fieldD6 > 0) {
        points[0].x = arg1->x;
        points[0].y = arg1->y;
        points[0].z = arg1->z;
        points[1].x = arg1->x + arg1->rate * arg1->dx;
        points[1].y = arg1->y + arg1->rate * arg1->dy;
        points[1].z = arg1->z + arg1->rate * arg1->dz;
        camera[0] = D_800DBFF0[arg2].unk2F8;
        camera[1] = D_800DBFF0[arg2].unk2FC;
        camera[2] = D_800DBFF0[arg2].unk300;
        range = arg1->range;
        for (i = 0; i < 2; i++) {
            distances[i] = (points[i].x - camera[0]) * (points[i].x - camera[0]) + (points[i].y - camera[1]) * (points[i].y - camera[1]) + (points[i].z - camera[2]) * (points[i].z - camera[2]);
        }
        temp = points[1].x;
        points[1].x = points[0].x;
        points[0].x = temp;
        temp = points[1].y;
        points[1].y = points[0].y;
        points[0].y = temp;
        temp = points[1].z;
        points[1].z = points[0].z;
        points[0].z = temp;
        delta[0] = camera[0] - arg1->x;
        delta[1] = camera[1] - arg1->y;
        delta[2] = camera[2] - arg1->z;
        normal[0] = delta[1] * arg1->dz - delta[2] * arg1->dy;
        normal[1] = delta[2] * arg1->dx - delta[0] * arg1->dz;
        normal[2] = delta[0] * arg1->dy - delta[1] * arg1->dx;
        for (i = 0; i < 2; i++) {
            delta[0] = points[i].x - camera[0];
            delta[1] = points[i].y - camera[1];
            delta[2] = points[i].z - camera[2];
            normal[0] = delta[1] * arg1->dz - delta[2] * arg1->dy;
            normal[1] = delta[2] * arg1->dx - delta[0] * arg1->dz;
            normal[2] = delta[0] * arg1->dy - delta[1] * arg1->dx;
            length = sqrtf(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
            if (length == 0.0f) {
                return arg0;
            }
            scale = range / length;
            normal[0] *= scale;
            normal[1] *= scale;
            normal[2] *= scale;
            corners[i * 2][0] = points[i].x + normal[0];
            corners[i * 2][1] = points[i].y + normal[1];
            corners[i * 2][2] = points[i].z + normal[2];
            corners[i * 2 + 1][0] = points[i].x - normal[0];
            corners[i * 2 + 1][1] = points[i].y - normal[1];
            corners[i * 2 + 1][2] = points[i].z - normal[2];
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 3; j++) {
                arg1->quads[D_800BE9C0][i].pos[j] = corners[i][j];
            }
        }
        arg0 = (Gfx *)func_15094F70((s32)arg0, D_8008CA4C[arg1->material], 0, &owner, 0, 0, 0, 2, 3);
        flag = 0;
        arg0 = func_15142FBC(arg0, D_800D2C9C | 0x80000 | 0x2000 | 0xC00 | 0x80 | 0x20, 0x504A50, &flag);
        gSPVertex(arg0++, arg1->quads[D_800BE9C0], 4, 0);
        gSP1Triangle(arg0++, 0, 1, 3, 0);
        gSP1Triangle(arg0++, 0, 3, 2, 0);
    }
    arg1->fieldDB = 1;
    return arg0;
}
s32 func_150E2DA4(s32 arg0, s32 arg1) {
    return arg0;
}
void func_150E1AB0(s32, f32, f32, f32, f32, f32, f32, f32, f32, f32,
                   f32, s16, u16, s8, s16, s16, s32, u8, u8, s32,
                   u8, u8, f32, f32, f32, f32, f32, f32);

void func_150E2DB4(s32 arg0, u8 arg1, s16 arg2, s32 arg3,
                   f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8,
                   f32 arg9, s16 arg10, s16 arg11, u16 arg12, u8 arg13) {
    func_150E1AB0(0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                  40.0f, 400.0f, (s32)arg12, 0x27, 1, (s32)arg10,
                  (s32)arg11, arg0, (s32)arg1, (s32)arg2, arg3, 0,
                  (s32)arg13, arg4, arg5, arg6, arg7, arg8, arg9);
}

void func_150E2EA4(s32 arg0, u8 arg1, s16 arg2, s32 arg3,
                   f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8,
                   f32 arg9, s16 arg10, s16 arg11, u16 arg12,
                   f32 arg13, f32 arg14, u8 arg15, f32 arg16) {
    func_150E1AB0(0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, arg16, 0.0f,
                  arg13, arg14, (s32)arg12, 0x27, 1, (s32)arg10,
                  (s32)arg11, arg0, (s32)arg1, (s32)arg2, arg3, 0,
                  (s32)arg15, arg4, arg5, arg6, arg7, arg8, arg9);
}
void func_150E2F90(s32 arg0, s32 arg1, s16 arg2) {
    func_150E2DA4(arg0, (s32) arg2);
}
void func_150E2FC0(void *arg0, void *arg1, u8 arg2) {
    s32 temp_v0;

    if (arg2 == 0x2D) {
        temp_v0 = *(s32 *)((u8 *)arg1 + 0);
        if (temp_v0 == *(s32 *)((u8 *)arg0 + 0xDC)) {
            *(s32 *)((u8 *)arg0 + 0xDC) = (s32) *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)arg0 + 0xDA) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == *(s32 *)((u8 *)arg0 + 0xDC)) {
            *(s32 *)((u8 *)arg0 + 0xDC) = temp_v0;
            *(u8 *)((u8 *)arg0 + 0xDA) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
