#include "types.h"
#include "game_functions.h"
#ifndef F3DEX_GBI_2
#define F3DEX_GBI_2
#endif
#include <PR/mbi.h>

/*
 * Reviewed source unit: src/game/game_193430.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_display_transition_groups.md
 */

f32 func_15047D60(f32);
f32 func_15047C00(f32);
void func_1517E05C(s32, s32, s32);
extern f32 D_800A6C94;

void func_15165F80(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   s32 arg5, s32 arg6, u8 arg7, s32 arg8) {
    u8 *cursor;
    u8 *effect;
    f32 angle;
    s32 i;
    s32 j;

    effect = func_15167A68(4, arg8, 0xA8, 1, arg7, 1);
    if (effect == 0) {
        return;
    }
    if (arg0 == -1) {
        i = 0;
        cursor = effect;
        do {
            i += 0x40;
            cursor += 0x40;
            *(s16 *)(cursor - 0x2E) = arg2;
            *(s16 *)(cursor - 0x1E) = arg2;
            *(s16 *)(cursor - 0xE) = arg2;
            *(s16 *)(cursor + 2) = arg2;
            *(s16 *)(cursor - 0x2A) = 0;
            *(s16 *)(cursor - 0x1A) = 0;
            *(s16 *)(cursor - 0xA) = 0;
            *(s16 *)(cursor + 6) = 0;
        } while (i != 0x80);
        effect[0x95] = 0;
    } else {
        angle = (f32)arg0 * D_800A6C94;
        effect[0x91] = (s32)(func_15047D60(angle) * 127.0f);
        effect[0x90] = (s32)(-func_15047C00(angle) * 127.0f);
        effect[0x95] = 1;
    }
    j = 0;
    {
    u8 *cursor2 = effect;
    do {
        j++;
        cursor2 += 0x40;
        *(s16 *)(cursor2 - 0x28) = 0x2000;
        *(s16 *)(cursor2 - 0x26) = 0x2000;
        *(s16 *)(cursor2 - 0x18) = 0x2800;
        *(s16 *)(cursor2 - 0x16) = 0x2000;
        *(s16 *)(cursor2 - 8) = 0x2800;
        *(s16 *)(cursor2 - 6) = 0x2800;
        *(s16 *)(cursor2 + 8) = 0x2000;
        *(s16 *)(cursor2 + 0xA) = 0x2800;
    } while (j != 2);
    *(s16 *)(effect + 0x9A) = arg2;
    *(s16 *)(effect + 0x9E) = 1;
    effect[0x92] = arg5;
    effect[0x93] = arg5;
    *(s16 *)(effect + 0x98) = arg1;
    *(s16 *)(effect + 0x9C) = arg3;
    *(s16 *)(effect + 0x96) = arg4;
    effect[0x94] = arg6;
    func_1517E05C(arg1, arg2, arg3);
    }
}
void func_1517E05C(s32, s32, s32);

typedef struct Game193430Vertex {
    s16 position[3];
    u16 flag;
    s16 texcoord[2];
    u8 color[4];
} Game193430Vertex;

typedef struct Game193430Quad {
    Game193430Vertex vertices[4];
} Game193430Quad;

void func_15166118(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   s32 arg5, s32 arg6, s32 arg7, u8 arg8, s32 arg9) {
    s32 i;
    u8 *effect;

    effect = func_15167A68(4, arg9, 0xA8, 1, arg8, 1);
    if (effect != 0) {
        effect[0x95] = 2;
        for (i = 0; i < 2; i++) {
            ((Game193430Quad *)(effect + 0x10))[i].vertices[0].texcoord[0] = 0x2000;
            ((Game193430Quad *)(effect + 0x10))[i].vertices[0].texcoord[1] = 0x2000;
            ((Game193430Quad *)(effect + 0x10))[i].vertices[1].texcoord[0] = 0x2800;
            ((Game193430Quad *)(effect + 0x10))[i].vertices[1].texcoord[1] = 0x2000;
            ((Game193430Quad *)(effect + 0x10))[i].vertices[2].texcoord[0] = 0x2800;
            ((Game193430Quad *)(effect + 0x10))[i].vertices[2].texcoord[1] = 0x2800;
            ((Game193430Quad *)(effect + 0x10))[i].vertices[3].texcoord[0] = 0x2000;
            ((Game193430Quad *)(effect + 0x10))[i].vertices[3].texcoord[1] = 0x2800;
        }
        *(s16 *)(effect + 0x9E) = 1;
        effect[0x92] = arg6;
        effect[0x93] = arg6;
        *(s16 *)(effect + 0x98) = arg2;
        *(s16 *)(effect + 0x9A) = arg3;
        *(s16 *)(effect + 0x9C) = arg4;
        *(s16 *)(effect + 0x96) = arg5;
        effect[0x94] = arg7;
        effect[0xA0] = arg0;
        effect[0xA1] = arg1;
        func_1517E05C(arg2, arg3, arg4);
    }
}
typedef struct {
    u8 pad_0[0x92];
    u8 field_92;
    u8 pad_93[3];
    s16 field_96;
    u8 pad_98[6];
    s16 field_9E;
} Game193430State;

extern s32 D_800BE9E4;

void func_15166204(Game193430State *arg0) {
    s32 temp_v0;

    arg0->field_9E = arg0->field_9E + (arg0->field_96 * D_800BE9E4);
    temp_v0 = arg0->field_92;
    temp_v0 -= D_800BE9E4;
    if (temp_v0 <= 0) {
        func_1516972C(arg0);
        return;
    }
    arg0->field_92 = temp_v0;
}
extern u8 D_800BE9C0;
Gfx *func_15166268(Gfx *gdl, u8 *effect, s32 arg2) {
    s32 i;
    s32 x;
    s32 y;
    s32 z;
    s32 size;
    s32 alpha;
    s32 limit;
    s32 half;
    s32 dx;
    s32 dz;
    s32 mode;

    if (effect[0x92] != 0) {
        x = *(s16 *)(effect + 0x98);
        y = *(s16 *)(effect + 0x9A);
        z = *(s16 *)(effect + 0x9C);
        size = *(s16 *)(effect + 0x9E);
        half = effect[0x93] >> 1;
        limit = effect[0x93] * 3 / 4;
        if (effect[0x92] < half) {
            *(s16 *)(effect + 0x96) = *(s16 *)(effect + 0x96) * 14 / 15;
            if (*(s16 *)(effect + 0x96) <= 0) {
                *(s16 *)(effect + 0x96) = 1;
            }
        }
        if (effect[0x92] < limit) {
            alpha = effect[0x92] * 255 / limit;
        } else {
            alpha = 255;
        }
        mode = effect[0x95];
        if (mode == 0) {
            ((Game193430Quad *)(effect + 0x10))[D_800BE9C0].vertices[0].position[0] = x - size;
            ((Game193430Quad *)(effect + 0x10))[D_800BE9C0].vertices[0].position[2] = z - size;
            ((Game193430Quad *)(effect + 0x10))[D_800BE9C0].vertices[1].position[0] = x + size;
            ((Game193430Quad *)(effect + 0x10))[D_800BE9C0].vertices[1].position[2] = z - size;
            ((Game193430Quad *)(effect + 0x10))[D_800BE9C0].vertices[2].position[0] = x + size;
            ((Game193430Quad *)(effect + 0x10))[D_800BE9C0].vertices[2].position[2] = z + size;
            ((Game193430Quad *)(effect + 0x10))[D_800BE9C0].vertices[3].position[0] = x - size;
            ((Game193430Quad *)(effect + 0x10))[D_800BE9C0].vertices[3].position[2] = z + size;
        } else if (mode == 1) {
            dx = (s8)effect[0x90] * size / 127;
            dz = (s8)effect[0x91] * size / 127;
            ((Game193430Quad *)(effect + 0x10))[D_800BE9C0].vertices[0].position[0] = x - dx;
            ((Game193430Quad *)(effect + 0x10))[D_800BE9C0].vertices[0].position[1] = y + size;
            ((Game193430Quad *)(effect + 0x10))[D_800BE9C0].vertices[0].position[2] = z - dz;
            ((Game193430Quad *)(effect + 0x10))[D_800BE9C0].vertices[1].position[0] = x + dx;
            ((Game193430Quad *)(effect + 0x10))[D_800BE9C0].vertices[1].position[1] = y + size;
            ((Game193430Quad *)(effect + 0x10))[D_800BE9C0].vertices[1].position[2] = z + dz;
            ((Game193430Quad *)(effect + 0x10))[D_800BE9C0].vertices[2].position[0] = x + dx;
            ((Game193430Quad *)(effect + 0x10))[D_800BE9C0].vertices[2].position[1] = y - size;
            ((Game193430Quad *)(effect + 0x10))[D_800BE9C0].vertices[2].position[2] = z + dz;
            ((Game193430Quad *)(effect + 0x10))[D_800BE9C0].vertices[3].position[0] = x - dx;
            ((Game193430Quad *)(effect + 0x10))[D_800BE9C0].vertices[3].position[1] = y - size;
            ((Game193430Quad *)(effect + 0x10))[D_800BE9C0].vertices[3].position[2] = z - dz;
        } else {
            f32 points[4][3];
            f32 sinA;
            f32 cosA;
            f32 sinB;
            f32 cosB;
            f32 py;
            f32 pz;
            f32 px;

            points[0][0] = -size;
            points[0][1] = size;
            points[0][2] = 0.0f;
            points[1][0] = size;
            points[1][1] = size;
            points[1][2] = 0.0f;
            points[2][0] = size;
            points[2][1] = -size;
            points[2][2] = 0.0f;
            points[3][0] = -size;
            points[3][1] = -size;
            points[3][2] = 0.0f;
            sinA = func_15048A40(effect[0xA0]);
            sinB = func_15048A40(effect[0xA1]);
            cosA = func_150489B0(effect[0xA0]);
            cosB = func_150489B0(effect[0xA1]);
            for (i = 0; i < 4; i++) {
                py = points[i][1];
                pz = points[i][2];
                points[i][1] = cosA * py - sinA * pz;
                pz = cosA * pz + sinA * py;
                px = points[i][0];
                points[i][0] = cosB * px - sinB * pz;
                points[i][2] = cosB * pz + sinB * px;
                ((Game193430Quad *)(effect + 0x10))[D_800BE9C0].vertices[i].position[0] = points[i][0] + x;
                ((Game193430Quad *)(effect + 0x10))[D_800BE9C0].vertices[i].position[1] = points[i][1] + y;
                ((Game193430Quad *)(effect + 0x10))[D_800BE9C0].vertices[i].position[2] = points[i][2] + z;
            }
        }
        gDPPipeSync(gdl++);
        gDPSetPrimColor(gdl++, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
        gSPVertex(gdl++, &((Game193430Quad *)(effect + 0x10))[D_800BE9C0], 4, 0);
        gSP1Triangle(gdl++, 0, 1, 2, 0);
        gSP1Triangle(gdl++, 0, 2, 3, 0);
    }
    return gdl;
}
void *func_15142FBC(void *, s32, s32, u8 *);
s32 func_15094F70();
extern s32 D_800903F4;
extern s32 D_800A4AC8[][2];
extern s32 D_800D2C9C;
extern s16 D_800DCE40;
extern s32 D_800DD220;
extern s32 D_800DD224;
extern void *D_800DD228;
extern s32 D_800DD230;

void func_151668B8(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 changed;
    s16 offset;

    offset = D_800DCE40;
    D_800DD228 = &D_800903F4;
    D_800DCE40 = offset + 0x80;
    changed = 1;
    D_800DD220 = offset;
    if (D_800DCE40 >= 0x500) {
        D_800DCE40 = 0;
    }
    D_800DD224 = 1;
    func_15142FBC((void *)func_15094F70(arg0, D_800DD228, D_800DD220, &D_800DD230, 0, 0, 0, D_800DD224, 3),
                  D_800D2C9C | 0x80000 | 0x2000 | 0xC00 | 0x80 | 0x20,
                  D_800A4AC8[3][0] | D_800A4AC8[3][1], &changed);
}
