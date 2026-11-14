#include "types.h"
#include "game_functions.h"
#ifndef F3DEX_GBI_2
#define F3DEX_GBI_2
#endif
#include <PR/mbi.h>

/*
 * Reviewed source unit: src/game/game_1D4E00.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_model_owner_mode_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A7950
 * - func_151A7A90
 * - func_151A8624
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);
void func_100226F0(void *, s32, void *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A7950 CURRENT (445) */
void *func_151A7950(u8 *arg0, s32 arg1, u8 arg2, s32 arg3) {
    u8 *result;
    u8 *data;

    result = func_15167A68(0x2D, arg3,
                           *(s16 *)(arg0 + 2) * 0x18U + arg1 + 0x80,
                           1, arg2, 1);
    if (result == 0) {
        return 0;
    }
    func_10022EC0(result + 0x10, arg0, 0x50);
    data = result + 0x80;
    *(u8 **)(result + 0x64) = data;
    *(f32 *)(result + 0x68) = 0.0f;
    *(u8 **)(result + 0x60) = *(u8 **)(result + 0x64) +
                              *(s16 *)(arg0 + 2) * 0x18;
    *(f32 *)*(u8 **)(result + 0x64) = 0.0f;
    *(f32 *)(*(u8 **)(result + 0x64) + 4) = 0.0f;
    *(f32 *)(*(u8 **)(result + 0x64) + 8) = 0.0f;
    *(f32 *)(*(u8 **)(result + 0x64) + *(s16 *)(arg0 + 2) * 0x18 - 0x18) = 0.0f;
    *(f32 *)(*(u8 **)(result + 0x64) + *(s16 *)(arg0 + 2) * 0x18 - 0x14) = 0.0f;
    *(f32 *)(*(u8 **)(result + 0x64) + *(s16 *)(arg0 + 2) * 0x18 - 0x10) = 1.0f;
    func_100226F0(result + 0x6C, 0x10, data, 0x18);
    *(s32 *)(result + 0x7C) = (*(s16 *)(result + 0x12) << 6) + 0x140;
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A7950 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A7950.s")
typedef struct {
    u8 pad0[0x64];
    f32 (*points)[6];
} Game1D4E00Curve;

f32 func_150ADA68(void);
void func_151A8340(Game1D4E00Curve *, s16, s16, f32, s16);
void func_151450B4(void *, void *, void *);
extern s32 (*D_8008F940[])(Game1D4E00Curve *);
extern s32 (*D_8008F948[])(Game1D4E00Curve *);
extern f32 D_800BE9A4;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A7A90 CURRENT (1970) */
void func_1516972C(s32);
void func_151A7A90(Game1D4E00Curve *arg0) {
    Game1D4E00Curve *countOwner;
    struct { u8 expired; } state;
    Vec3f cross;
    Vec3f axis;
    Vec3f delta;
    f32 (*point)[6];
    f32 x, y, z;
    s32 callbackIndex;

    countOwner = arg0;
    state.expired = 0;
    if (arg0->pad0[0x1C] & 1) {
        *(s16 *)((u8 *)arg0 + 0x10) -= D_800BE9E4;
        if (*(s16 *)((u8 *)arg0 + 0x10) < 0) {
            state.expired = 1;
        }
    }
    callbackIndex = *(s8 *)((u8 *)arg0 + 0x2C);
    if (callbackIndex != -1 && state.expired == 0) {
        state.expired = D_8008F940[callbackIndex](arg0) == 0;
    }
    callbackIndex = *(s8 *)((u8 *)arg0 + 0x2D);
    if (callbackIndex != -1 && state.expired == 0) {
        state.expired = D_8008F948[callbackIndex](arg0) == 0;
    }
    if (state.expired == 0) {
        *(f32 *)((u8 *)arg0 + 0x68) -= D_800BE9A4;
        if (*(f32 *)((u8 *)arg0 + 0x68) < 0.0f) {
            func_151A8340(arg0, 0, (s16)(*(s16 *)((u8 *)arg0 + 0x12) - 1),
                          *(f32 *)((u8 *)arg0 + 0x20), 100);
            *(f32 *)((u8 *)arg0 + 0x68) = func_150ADA68() * *(f32 *)((u8 *)arg0 + 0x18) + *(f32 *)((u8 *)arg0 + 0x14);
        }
        if (arg0->pad0[0x1C] & 2) {
            delta.x = *(f32 *)((u8 *)arg0 + 0x3C) - *(f32 *)((u8 *)arg0 + 0x30);
            delta.y = *(f32 *)((u8 *)arg0 + 0x40) - *(f32 *)((u8 *)arg0 + 0x34);
            delta.z = *(f32 *)((u8 *)arg0 + 0x44) - *(f32 *)((u8 *)arg0 + 0x38);
            axis = *(Vec3f *)((u8 *)arg0 + 0x48);
            func_151450B4(&delta, &axis, &cross);
            cross.x *= *(f32 *)((u8 *)arg0 + 0x58);
            cross.y *= *(f32 *)((u8 *)arg0 + 0x58);
            cross.z *= *(f32 *)((u8 *)arg0 + 0x58);
            callbackIndex = 0;
            point = arg0->points;
            if (*(s16 *)((u8 *)arg0 + 0x12) > 0) {
                do {
                    x = (*point)[0];
                    y = (*point)[1];
                    z = (*point)[2];
                    callbackIndex++;
                    point++;
                    point[-1][3] = *(f32 *)((u8 *)arg0 + 0x30) + x * cross.x + y * axis.x + z * delta.x;
                    point[-1][4] = *(f32 *)((u8 *)arg0 + 0x34) + x * cross.y + y * axis.y + z * delta.y;
                    point[-1][5] = *(f32 *)((u8 *)arg0 + 0x38) + x * cross.z + y * axis.z + z * delta.z;
                } while (callbackIndex < *(s16 *)((u8 *)countOwner + 0x12));
            }
        }
    }
    if (state.expired != 0) {
        func_1516972C((s32)arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A7A90 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A7A90.s")
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
s32 func_15142E24(s32, s32, s32, s32, s32, s32, s32, u8, s32, u8 *, s32);
s32 func_15144B34(s32);
void func_15145548(void *, void *, void *, void *, f32 *);
void func_151D5D60(void *, s16, s32, void **, u8 *);
Gfx *func_1513F4E4(Gfx *, u8, u8 *);
Gfx *func_15142B7C(Gfx *, s32, s32);
Gfx *func_15142C10(Gfx *, s32, s32, s32, s32, u8 *);
Gfx *func_15142FBC(Gfx *, s32, s32, u8 *);
extern u8 D_80090D70[];
extern s32 D_800A4AC8[][2];
extern s32 D_800D2C9C;

typedef struct {
    u8 pad0[0xC];
    Vec3f pos;
} Game1D4E00Point;

typedef struct {
    u8 pad0[0x12];
    s16 count;
    u8 pad14[8];
    u8 flags;
    u8 pad1D[7];
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    f32 width;
    u8 pad2C[0x38];
    Game1D4E00Point *points;
    u8 pad68[4];
    u8 buffers[0x10];
    s32 size;
} Game1D4E00Bolt;



Gfx *func_151A7D6C(Gfx *gdl, Game1D4E00Bolt *arg1, s16 arg2) {
    Game1D4E00Bolt *self = arg1;
    Vtx_t *vtx;
    Vec3f dir;
    Vec3f closest;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 nx;
    f32 ny;
    f32 nz;
    f32 *camera;
    f32 lenSq;
    u8 changed;
    s16 last;
    f32 scale;
    s16 i;
    f32 parameter;
    s16 j;
    Vec3f *a;
    Vec3f *b;

    if (arg1->flags & 2) {
        func_151D5D60(arg1->buffers, arg2, arg1->size, (void **)&vtx, NULL);
        if (vtx != NULL) {
            camera = (f32 *)func_15144B34(arg2);
            changed = 1;
            last = arg1->count - 1;
            j = 0;
            i = 1;
            gdl = (Gfx *)func_15142E24((s32)gdl, (s32)D_80090D70, 0, 0, 0, 0, 0x2C, 0, 0, &changed, 3);
            gdl = func_15142B7C(gdl, 0x200005, 0x1F0600);
            gdl = func_15142C10(gdl, arg1->r, arg1->g, arg1->b, arg1->a, &changed);
            gdl = func_1513F4E4(gdl, 0x19, &changed);
            gdl = func_15142FBC(gdl, D_800D2C9C | 0x80000 | 0x2000 | 0xC00 | 0x80 | 0x20, D_800A4AC8[3][0] | D_800A4AC8[3][1], &changed);
            dir.x = arg1->points[0].pos.x - arg1->points[last].pos.x;
            dir.y = arg1->points[0].pos.y - arg1->points[last].pos.y;
            dir.z = arg1->points[0].pos.z - arg1->points[last].pos.z;
            func_15145548(&arg1->points[last].pos, &dir, camera, &closest, &parameter);
            dx = camera[0] - closest.x;
            dy = camera[1] - closest.y;
            dz = camera[2] - closest.z;
            nx = dir.y * dz - dy * dir.z;
            ny = dir.z * dx - dz * dir.x;
            nz = dir.x * dy - dx * dir.y;
            lenSq = nx * nx + ny * ny + nz * nz;
            if (lenSq == 0.0f) {
                nx = 0.0f;
                ny = 0.0f;
                nz = 0.0f;
            } else {
                scale = arg1->width / sqrtf(lenSq);
                nx *= scale;
                ny *= scale;
                nz *= scale;
            }
            for (; i < self->count; i++, j++) {
                b = &arg1->points[i].pos;
                a = &arg1->points[j].pos;
                vtx->ob[0] = a->x + nx;
                vtx->ob[1] = a->y + ny;
                vtx->ob[2] = a->z + nz;
                vtx->tc[0] = 0;
                vtx->tc[1] = 0;
                vtx->cn[0] = 0xFF;
                vtx->cn[1] = 0xFF;
                vtx->cn[2] = 0xFF;
                vtx->cn[3] = 0xFF;
                vtx->flag = 0;
                vtx++;
                vtx->ob[0] = a->x - nx;
                vtx->ob[1] = a->y - ny;
                vtx->ob[2] = a->z - nz;
                vtx->tc[0] = 0x3C0;
                vtx->tc[1] = 0;
                vtx->cn[0] = 0xFF;
                vtx->cn[1] = 0xFF;
                vtx->cn[2] = 0xFF;
                vtx->cn[3] = 0xFF;
                vtx->flag = 0;
                vtx++;
                vtx->ob[0] = b->x - nx;
                vtx->ob[1] = b->y - ny;
                vtx->ob[2] = b->z - nz;
                vtx->tc[0] = 0x3C0;
                vtx->tc[1] = 0x3C0;
                vtx->cn[0] = 0xFF;
                vtx->cn[1] = 0xFF;
                vtx->cn[2] = 0xFF;
                vtx->cn[3] = 0xFF;
                vtx->flag = 0;
                vtx++;
                vtx->ob[0] = b->x + nx;
                vtx->ob[1] = b->y + ny;
                vtx->ob[2] = b->z + nz;
                vtx->tc[0] = 0;
                vtx->tc[1] = 0x3C0;
                vtx->cn[0] = 0xFF;
                vtx->cn[1] = 0xFF;
                vtx->cn[2] = 0xFF;
                vtx->cn[3] = 0xFF;
                vtx->flag = 0;
                vtx++;
                gSPVertex(gdl++, vtx - 4, 4, 0);
                gSP1Triangle(gdl++, 0, 1, 2, 0);
                gSP1Triangle(gdl++, 0, 2, 3, 0);
            }
        }
    }
    return gdl;
}


f32 func_150ADA68(void);

void func_151A8340(Game1D4E00Curve *arg0, s16 first, s16 last, f32 amp, s16 depth) {
    s16 middle;

    if (last - first < 2) {
        return;
    }
    if (depth <= 0) {
        return;
    }
    {
        f32 dx;
        f32 dy;
        f32 dz;
        f32 *a;

        {
            f32 *b;

            a = &arg0->points[first][0];
            middle = first + ((last - first) >> 1);
            b = arg0->points[last];
            dx = b[0] - arg0->points[first][0];
            dy = b[1] - arg0->points[first][1];
            dz = b[2] - arg0->points[first][2];
        }
        arg0->points[middle][0] = (a[0] + dx * 0.5f) + (func_150ADA68() * (amp + amp) + -amp);
        arg0->points[middle][1] = (a[1] + dy * 0.5f) + (func_150ADA68() * (amp + amp) + -amp);
        arg0->points[middle][2] = a[2] + dz * 0.5f;
    }
    func_151A8340(arg0, first, middle, amp, depth - 1);
    func_151A8340(arg0, middle, last, amp, depth - 1);
}

void func_151A8560(s32 arg0) {
    func_151D5E30(arg0 + 0x6C, arg0);
}
typedef struct {
    u8 pad_0[0x5C];
    u8 field_5C;
} Game1D4E00State;

void func_151A8560(s32);
extern void (*D_8008F94C[])(s32);

void func_151A8584(s32 arg0) {
    Game1D4E00State *state = (Game1D4E00State *)arg0;

    if (D_8008F94C[state->field_5C] != NULL) {
        D_8008F94C[state->field_5C](arg0);
    }
    func_151A8560(arg0);
    func_15169804((void *)arg0);
}
extern void (*D_8008F958[])(s32);

void func_151A85D4(s32 arg0) {
    Game1D4E00State *state = (Game1D4E00State *)arg0;

    if (D_8008F958[state->field_5C] != NULL) {
        D_8008F958[state->field_5C](arg0);
    }
    func_151A8560(arg0);
    func_15169824((void *)arg0);
}
typedef struct { u8 bytes[4]; } Game1D4E00Colour;
typedef struct {
    s16 lifetime;
    s16 count;
    f32 field04;
    f32 field08;
    u8 timed;
    u8 pad0D[3];
    f32 field10;
    Game1D4E00Colour colour;
    f32 field18;
    u8 mode;
    s8 type;
    u8 pad1E[2];
    f32 field20[10];
    f32 field48;
    u8 field4C;
    u8 pad4D[3];
} Game1D4E00Descriptor;
typedef struct {
    void *owner;
    u8 generation;
    u8 pad05[3];
    Vec3f position;
    u8 style;
    u8 pad15[3];
    Vec3f offset;
    u8 flag24;
    u8 flag25;
    u8 pad26[2];
} Game1D4E00OwnerData;

extern f32 D_800A8DE0;
void *func_151A7950(u8 *, s32, u8, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A8624 CURRENT (1828) */
void *func_151A8624(u8 *arg0, Vec3f *arg1, s32 arg2, s32 arg3,
                   f32 arg4, f32 arg5, Game1D4E00Colour *arg6, f32 arg7,
                   Vec3f *arg8, s32 arg9, s32 arg10, s32 arg11,
                   s32 arg12, s32 arg13, s32 arg14) {
    void *result;
    Game1D4E00Descriptor descriptor;
    Game1D4E00OwnerData owner;
    u8 mode;

    arg2 = (u8)arg2;
    arg3 = (s16)arg3;
    mode = arg9;
    if (arg0 == 0) {
        return 0;
    }
    if (mode >= 2) {
        mode = 0;
    }
    owner.position = *arg1;
    owner.style = arg2;
    owner.flag25 = 0;
    owner.owner = arg0;
    owner.generation = arg0[0x3B];
    owner.flag24 = arg10;
    if (arg8 != 0) {
        owner.offset = *arg8;
    } else {
        owner.offset.x = 0.0f;
        owner.offset.y = 0.0f;
        owner.offset.z = 0.0f;
    }
    if (arg3 == -1) {
        descriptor.lifetime = 300;
    } else {
        descriptor.lifetime = arg3;
    }
    descriptor.count = 9;
    descriptor.field04 = arg4;
    descriptor.field08 = arg5;
    if (arg3 == -1) {
        descriptor.timed = 0;
    } else {
        descriptor.timed = 1;
    }
    descriptor.field10 = D_800A8DE0;
    descriptor.colour = *arg6;
    descriptor.field18 = arg7;
    if (mode != 0 && mode == 1) {
        descriptor.mode = 1;
    } else {
        descriptor.mode = 1;
    }
    descriptor.field20[0] = 0.0f;
    descriptor.field20[1] = 0.0f;
    descriptor.field20[2] = 0.0f;
    descriptor.field20[3] = 0.0f;
    descriptor.field20[4] = 0.0f;
    descriptor.field20[5] = 0.0f;
    descriptor.field20[6] = 0.0f;
    descriptor.field20[7] = 0.0f;
    descriptor.field20[8] = 0.0f;
    descriptor.field20[9] = 0.0f;
    descriptor.field4C = 2;
    descriptor.type = arg11;
    descriptor.field48 = 1.0f;
    result = func_151A7950((u8 *)&descriptor, arg12 + 0x28, arg13, arg14);
    if (result != 0) {
        func_10022EC0(*(void **)((u8 *)result + 0x60), &owner, sizeof(owner));
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A8624 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A8624.s")
typedef struct Game1D4E00Owner {
    s32 active;
    u8 type;
    u8 pad5[0xF];
    Vec3f position;
    u8 pad20[0x1B];
    u8 generation;
    u8 pad3C[0x198];
    u8 *transform;
} Game1D4E00Owner;

typedef struct Game1D4E00Beam {
    u8 pad0[0x1C];
    u8 flags;
    u8 pad1D[0x13];
    Vec3f position;
    Vec3f endpoint;
    Vec3f perpendicular;
    f32 length;
    f32 inverse_length;
    u8 pad5C[4];
    Game1D4E00OwnerData *owner_data;
} Game1D4E00Beam;

s32 func_150AC9C0(f32, f32, f32, f32, f32, f32, void *, s16 *, f32 *, f32 *, f32 *, f32 *, s32 *, void *, f32);
void func_15143134(f32 *, f32 *, s32);
s32 func_15145C90(s32);
s32 func_15146078(void *, void *, void *);

s32 func_151A87F8(Game1D4E00Beam *arg0) {
    Game1D4E00OwnerData *data;
    Game1D4E00Owner *owner;

    data = arg0->owner_data;
    owner = data->owner;
    if (owner->active == 0 || owner->generation != data->generation || owner->type == 0xFF) {
        return 0;
    }
    if (owner->transform != 0) {
        Vec3f delta;

        func_15143134(&data->position.x, &arg0->position.x, (s32)owner->transform + (data->style << 6));
        if (!(data->flag25 & 1)) {
            s32 hit;
            f32 dx;
            f32 dy;
            f32 dz;

            dx = arg0->position.x - (owner->position.x + data->offset.x);
            dy = arg0->position.y - (owner->position.y + data->offset.y);
            dz = arg0->position.z - (owner->position.z + data->offset.z);
            if (func_150AC9C0(arg0->position.x, arg0->position.y, arg0->position.z, dx, dy, dz, 0, 0, &arg0->endpoint.x, &arg0->endpoint.y, &arg0->endpoint.z, 0, &hit, 0, 0.0f) != 0) {
                if (func_15145C90(hit) != 0) {
                    data->flag25 |= 1;
                } else {
                    arg0->flags &= ~2;
                    return 1;
                }
            } else {
                arg0->flags &= ~2;
                return 1;
            }
        }
        delta.x = arg0->endpoint.x - arg0->position.x;
        delta.y = arg0->endpoint.y - arg0->position.y;
        delta.z = arg0->endpoint.z - arg0->position.z;
        arg0->length = func_15143E64(&delta);
        if (arg0->length != 0.0f) {
            Vec3f scratch;

            arg0->inverse_length = 1.0f / arg0->length;
            func_15146078(&delta, &scratch, &arg0->perpendicular);
            arg0->flags |= 2;
        } else {
            arg0->flags &= ~2;
        }
    } else {
        arg0->flags &= ~2;
    }
    return 1;
}
typedef void (*Game1D4E00Callback)(void *, s32, u8);

extern Game1D4E00Callback D_8008F964[];

void func_151A8A20(void *arg0, s32 arg1, u8 arg2) {
    Game1D4E00Callback temp_v1;
    u8 var_v0;

    var_v0 = *(u8 *)((u8 *)arg0 + 0x5C);
    if (var_v0 >= 3) {
        var_v0 = 0;
    }
    temp_v1 = D_8008F964[var_v0];
    if (temp_v1 != 0) {
        temp_v1(arg0, arg1, arg2);
    }
}

void func_151A8A78(void *arg0, void *arg1, u8 arg2) {
    s32 temp_a0;
    s32 temp_t6;
    s32 current_id;
    void *temp_v0;

    temp_t6 = arg2;
    temp_v0 = *(void **)((u8 *)arg0 + 0x60);
    if (temp_t6 == 0) {
        current_id = *(s32 *)arg1;
        if ((current_id == *(s32 *)temp_v0) || (*(u8 *)((u8 *)arg1 + 4) == *(u8 *)((u8 *)temp_v0 + 4))) {
            func_1516972C(arg0);
        }
    } else if (temp_t6 == 0x2D) {
        temp_a0 = *(s32 *)arg1;
        if (temp_a0 == *(s32 *)temp_v0) {
            *(s32 *)temp_v0 = *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == *(s32 *)temp_v0) {
            *(s32 *)temp_v0 = temp_a0;
            *(u8 *)((u8 *)temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
