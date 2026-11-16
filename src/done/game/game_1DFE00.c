#include "types.h"
#ifndef F3DEX_GBI_2
#define F3DEX_GBI_2
#endif
#include <PR/mbi.h>
#include "game_view.h"
#include "game_vec.h"

/*
 * Reviewed source unit: src/game/game_1DFE00.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_subranges.md
 */

void func_151B2950(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x178);
    if (temp_v0 != 0) {
        *(s32 *)(temp_v0 + (*(u8 *)(arg0 + 0x17C) * 4) + 0x38) = 0;
    }
}
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

typedef struct Game1DFE00Target {
    s32 active;
    u8 pad4[0x37];
    u8 id;
    u8 pad3C[0x198];
    s32 matrices;
} Game1DFE00Target;

typedef struct Game1DFE00Link {
    Game1DFE00Target *target;
    u8 id;
    u8 bone;
    u8 pad6[2];
    Vec3f start;
    Vec3f end;
    f32 width;
} Game1DFE00Link;

typedef struct Game1DFE00Beam {
    u8 pad0[0xE];
    s16 state;
    u8 pad10[4];
    u8 buffers[0x14];
    Game1DFE00Link link;
} Game1DFE00Beam;

void func_151D5D60(void *, s16, s32, void **, u8 *);
void func_15143134(f32 *, f32 *, s32);
s32 func_15142E24(s32, s32, s32, s32, s32, s32, s32, u8, s32, u8 *, s32);
Gfx *func_15142C10(Gfx *, s32, s32, s32, s32, u8 *);
Gfx *func_15142CF0(Gfx *, s32, s32, s32, s32, s32, s32, u8 *);
Gfx *func_1513F4E4(Gfx *, u8, u8 *);
Gfx *func_15142B7C(Gfx *, s32, s32);
Gfx *func_15142FBC(Gfx *, s32, s32, u8 *);
extern u8 D_80090DE8[];
extern s32 D_800A4AC8[][2];
extern s32 D_800D2C9C;

Gfx *func_151B2974(Gfx *arg0, Game1DFE00Beam *arg1, s16 arg2) {
    Game1DFE00Link *link;
    u8 done;
    u8 flag;
    Vtx_t *vtx;
    Vec3f *camera;
    Vec3f delta;
    Vec3f toCamera;
    f32 lengthSquared;
    Vec3f start;
    Vec3f end;
    Vec3f normal;
    s32 matrix;
    f32 scale;

    done = 0;
    link = &arg1->link;
    if (link->target->active == 0 || link->target->id != link->id) {
        done = 1;
    }
    if (!done && link->target->matrices != 0) {
        func_151D5D60(arg1->buffers, arg2, 4 * sizeof(Vtx_t), (void **)&vtx, NULL);
        if (vtx == NULL) {
            return arg0;
        }
        matrix = link->target->matrices + (link->bone << 6);
        func_15143134((f32 *)&link->start, (f32 *)&start, matrix);
        func_15143134((f32 *)&link->end, (f32 *)&end, matrix);
        flag = 1;
        camera = (Vec3f *)&D_800DBFF0[arg2].unk2F8;
        arg0 = func_15142B7C(arg0, 0x200005, 0x60600);
        arg0 = (Gfx *)func_15142E24((s32)arg0, (s32)D_80090DE8, 0, 0, 0, 0, 0x36, 0, 0, &flag, 3);
        arg0 = func_15142C10(arg0, 0xFF, 0xFF, 0xFF, 0xFF, &flag);
        arg0 = func_15142CF0(arg0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF, &flag);
        arg0 = func_1513F4E4(arg0, 0x2B, &flag);
        arg0 = func_15142FBC(arg0, D_800D2C9C | 0x80000 | 0x2000 | 0xC00 | 0x80 | 0x20, D_800A4AC8[5][0] | D_800A4AC8[5][1], &flag);
        delta.x = end.x - start.x;
        toCamera.x = delta.x * 0.5f + start.x - camera->x;
        delta.y = end.y - start.y;
        toCamera.y = delta.y * 0.5f + start.y - camera->y;
        delta.z = end.z - start.z;
        toCamera.z = delta.z * 0.5f + start.z - camera->z;
        normal.x = delta.y * toCamera.z - toCamera.y * delta.z;
        normal.y = delta.z * toCamera.x - toCamera.z * delta.x;
        normal.z = delta.x * toCamera.y - toCamera.x * delta.y;
        lengthSquared = normal.x * normal.x + normal.y * normal.y + normal.z * normal.z;
        if (lengthSquared == 0.0f) {
            normal.x = 0.0f;
            normal.y = 0.0f;
            normal.z = 0.0f;
        } else {
            scale = link->width / sqrtf(lengthSquared);
            normal.x *= scale;
            normal.y *= scale;
            normal.z *= scale;
        }
        vtx->ob[0] = end.x + normal.x;
        vtx->ob[1] = end.y + normal.y;
        vtx->ob[2] = end.z + normal.z;
        vtx->tc[0] = 0;
        vtx->tc[1] = 0;
        vtx++;
        vtx->ob[0] = end.x - normal.x;
        vtx->ob[1] = end.y - normal.y;
        vtx->ob[2] = end.z - normal.z;
        vtx->tc[0] = 0x3C0;
        vtx->tc[1] = 0;
        vtx++;
        vtx->ob[0] = start.x - normal.x;
        vtx->ob[1] = start.y - normal.y;
        vtx->ob[2] = start.z - normal.z;
        vtx->tc[0] = 0x3C0;
        vtx->tc[1] = 0x3C0;
        vtx++;
        vtx->ob[0] = start.x + normal.x;
        vtx->ob[1] = start.y + normal.y;
        vtx->ob[2] = start.z + normal.z;
        vtx->tc[0] = 0;
        vtx->tc[1] = 0x3C0;
        vtx++;
        gSPVertex(arg0++, vtx - 4, 4, 0);
        gSP1Triangle(arg0++, 0, 1, 2, 0);
        gSP1Triangle(arg0++, 0, 2, 3, 0);
    }
    if (done) {
        arg1->state = -1;
    }
    return arg0;
}
void func_151B2EC4(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}
void func_151B2F04(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 temp_a2;
    s32 temp_v1;
    s32 replacement;
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + 0x28);
    if (arg2 == 0x2D) {
        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        temp_a2 = *(s32 *)temp_v0;
        if (temp_v1 == temp_a2) {
            *(s32 *)temp_v0 = (s32) *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 9);
        } else if ((replacement = *(s32 *)((u8 *)arg1 + 4)) == temp_a2) {
            *(s32 *)temp_v0 = temp_v1;
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
        replacement = *(s32 *)(arg1 + 4);
        temp_v1 = *(s32 *)arg1;
        temp_a2 = *(s32 *)((u8 *)temp_v0 + 8);
        if (temp_v1 == temp_a2) {
            *(s32 *)((u8 *)temp_v0 + 8) = replacement;
            *(u8 *)((u8 *)temp_v0 + 0xC) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (replacement == temp_a2) {
            *(s32 *)((u8 *)temp_v0 + 8) = temp_v1;
            *(u8 *)((u8 *)temp_v0 + 0xC) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
s32 func_151B47D8(s32 arg0, s32 arg1, s32 arg2, u8 arg3);

void func_151B2FA0(s32 arg0, s32 arg1, u8 arg2) {
    func_151B47D8(arg0, arg0 + 0x150, arg1, arg2);
}
