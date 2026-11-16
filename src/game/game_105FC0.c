#include "types.h"
#ifndef F3DEX_GBI_2
#define F3DEX_GBI_2
#endif
#include <PR/mbi.h>
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_105FC0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_particle_emitter_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D8E4C
 * - func_150D8FAC
 * - func_150D942C
 * - func_150DA67C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150DA484(void *arg0);
void func_100111C8(s32 arg0, u16 arg1);
void func_15145740(void *arg0, void *arg1, void *arg2, void *arg3, f32 arg4);
extern f32 D_800A0B40;
extern f32 D_800A0B44;
extern u8 D_800BE616;

void func_150D8B10(void *arg0, void *arg1) {
    *(f32 *)((u8 *)arg1 + 0) = (f32) *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)((u8 *)arg1 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + 20.0f);
    *(f32 *)((u8 *)arg1 + 8) = (f32) *(f32 *)((u8 *)arg0 + 0x1C);
}

void func_150D8B3C(void *arg0, void *arg1) {
    Vec3f first;
    Vec3f second;
    func_15145740(arg0, &first, &second, arg1,
                  (D_800BE616 != 0) ? D_800A0B40 : D_800A0B44);
}
typedef struct Game105FC0Spawn {
    Vec3f position;
    s16 life;
    s16 count;
    s32 mode;
    s8 kind;
    s8 rate;
    s32 flags;
} Game105FC0Spawn;
typedef struct Game105FC0Payload {
    void *owner;
    u8 kind;
    Vec3f first;
    Vec3f second;
    Vec3f velocity;
    f32 value2C;
    s16 sound;
    f32 value34;
    f32 value38;
    f32 value3C;
    Vec3f offset;
    u8 flags;
    s8 timer;
} Game105FC0Payload;
void func_1000D96C(s32, s32, s32);
s32 func_10010F88(s32, u16, s32, s32, s32, s32, s32, s32, s32, s32);
void *func_10022EC0(void *, const void *, u32);
void func_150D8B3C(void *, void *);
void *func_15147A80(void *, void *, s32, s32, s32, s32, s32, s32, s32, u8, s32);
s32 func_151EF610(void);
extern f32 D_800A0B48;
extern s32 D_800BE9F0;

void func_150D8B88(void *arg0) {
    Game105FC0Spawn spawn;
    void *object;
    Game105FC0Payload payload;
    Vec3f position;
    void *entity;

    if (*(void **)((u8 *)arg0 + 0x31C) != 0) {
        if (D_800BE9F0 == 0xA) {
            func_1000D96C(0xA, 0x37, 0);
        }
        func_150D8B10(arg0, &spawn.position);
        payload.timer = 0;
        payload.flags = 1;
        payload.owner = arg0;
        payload.kind = *(u8 *)((u8 *)arg0 + 0x3B);
        position = spawn.position;
        payload.first = position;
        payload.second = position;
        func_150D8B3C(arg0, &payload.velocity);
        payload.value3C = D_800A0B48;
        payload.sound = func_10010F88((func_151EF610() % 2) + 0x1B6, 0x7FFFU, 0, 0, 0, 0, 0, 0, 500, 5000);
        payload.value34 = 0.0f;
        payload.value2C = 0.0f;
        payload.offset.x = 0.0f;
        payload.offset.y = 0.0f;
        payload.offset.z = 0.0f;
        payload.value38 = -16384.0f;
        entity = *(void **)((u8 *)arg0 + 0x31C);
        if (entity != 0 && *(u8 *)((u8 *)entity + 0x84) != 0) {
            payload.flags &= 0xFFFE;
        }
        spawn.rate = 0x32;
        spawn.life = 0x12C;
        spawn.count = 0x36;
        spawn.mode = 2;
        spawn.kind = 5;
        spawn.flags = 0;
        object = func_15147A80(&spawn, (void *)0x50, 0x24, 0xE, 1, 0x11, 3, 0xFF, 0, 0xFF, 1);
        if (object != 0) {
            func_10022EC0(*(void **)((u8 *)object + 0x98), &payload, 0x50U);
        }
    }
}
extern f32 D_800A0B4C;
extern f32 D_800A0B50;


void func_150D8D84(Vec3f *arg0, Vec3f *arg1, f32 arg2) {
    Vec3f sp4;

    sp4 = *arg1;
    arg1->y += D_800A0B4C * arg2;
    arg0->x += sp4.x * arg2;
    arg0->y += (sp4.y * arg2) + (D_800A0B50 * arg2 * arg2);
    arg0->z += sp4.z * arg2;
}
void func_150D8E1C(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x30) = 0;
    *(u16 *)((u8 *)arg0 + 0x1E) &= 0xFFFD;
    *(u16 *)((u8 *)arg0 + 0x1E) |= 8;
    *(u16 *)((u8 *)arg0 + 0x1E) |= 1;
    *(s16 *)((u8 *)arg0 + 0x1C) = 0x28;
}
typedef struct Game105FC0Sub {
    u8 pad0[0x1AA];
    s16 count;
} Game105FC0Sub;

typedef struct Game105FC0Owner {
    u8 pad0[0x31C];
    Game105FC0Sub *sub;
} Game105FC0Owner;

typedef struct Game105FC0Timer {
    Game105FC0Owner *owner;
    u8 pad4[0x49];
    s8 count;
} Game105FC0Timer;

typedef struct Game105FC0State {
    u8 pad0[0x1E];
    u16 flags;
    u8 pad20[5];
    u8 capacity;
    u8 pad26[6];
    s8 mode;
    s8 stop;
    s8 current;
    u8 pad2F[0x25];
    Vec3f position;
    u8 pad60[0x34];
    u8 *samples;
    Game105FC0Timer *timer;
} Game105FC0State;

extern f32 D_800BE9A4;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D8E4C CURRENT (565) */
s32 func_150D8E4C(Game105FC0State *arg0) {
    s32 temp_s4;
    s32 var_s0;
    Game105FC0Timer *temp_s5;
    Vec3f *temp_a0;
    Vec3f *temp_t0;
    Game105FC0Owner *temp_v1;
    Game105FC0Sub *temp_v0;
    s32 stride;

    temp_s5 = arg0->timer;
    temp_s4 = (s32)arg0->samples;
    if (arg0->mode < 2 && (arg0->flags & 8)) {
        return 0;
    }
    var_s0 = arg0->current;
    if (var_s0 != arg0->stop) {
        do {
            var_s0 -= 1;
            if (var_s0 < 0) {
                var_s0 = arg0->capacity - 1;
            }
            temp_a0 = (Vec3f *)(temp_s4 + var_s0 * 0x24);
            func_150D8D84(temp_a0, temp_a0 + 1, D_800BE9A4);
        } while (var_s0 != arg0->stop);
    }
    stride = 0x24;
    if (arg0->mode > 0) {
        temp_t0 = (Vec3f *)(temp_s4 + arg0->stop * stride);
        arg0->position = *temp_t0;
    } else {
        arg0->position.x = 0.0f;
        arg0->position.y = 0.0f;
        arg0->position.z = 0.0f;
    }
    temp_s5->count += D_800BE9E4;
    if (temp_s5->count >= 0x3D) {
        temp_v1 = temp_s5->owner;
        if (temp_v1 != 0) {
            temp_v0 = temp_v1->sub;
            if (temp_v0 != 0) {
                temp_v0->count += 1;
            }
        }
        temp_s5->count = 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D8E4C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150D8E4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150D8FAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150D942C.s")
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
typedef struct Game105FC0TrailRecord {
    Vec3f position;
    u8 pad0C[0x10];
    u8 alpha;
    u8 pad1D[3];
    f32 texture;
} Game105FC0TrailRecord;

void func_151D5D60(void *, s16, s32, void **, u8 *);
s32 func_15144B34(s32);
s32 func_15142E24(s32, s32, s32, s32, s32, s32, s32, u8, s32, u8 *, s32);
Gfx *func_1513F4E4(Gfx *, u8, u8 *);
Gfx *func_15142B7C(Gfx *, s32, s32);
Gfx *func_15142FBC(Gfx *, s32, s32, u8 *);
extern u8 D_80091238[];
extern s32 D_800A4AC8[][2];
extern s32 D_800D2C9C;

Gfx *func_150D9C7C(u8 *arg0, Gfx *arg1, s16 arg2) {
    Game105FC0TrailRecord *records;
    Vec3f next;
    Vec3f cur;
    Vec3f toCamera;
    Vec3f delta;
    Vec3f normal;
    u8 *state;
    Vec3f *camera;
    s32 index;
    s32 previous;
    f32 lengthSquared;
    u8 flag;
    u8 alpha;
    f32 nextTexture;
    f32 curTexture;
    Vtx_t *vtx;

    if (*(s8 *)(arg0 + 0x2C) < 2) {
        return arg1;
    }
    state = *(u8 **)(arg0 + 0x98);
    records = *(Game105FC0TrailRecord **)(arg0 + 0x94);
    func_151D5D60(arg0 + 0x84, arg2, (arg0[0x25] * 2 + 10) * sizeof(Vtx_t), (void **)&vtx, NULL);
    if (vtx == NULL) {
        return arg1;
    }
    camera = (Vec3f *)func_15144B34(arg2);
    flag = 1;
    arg1 = (Gfx *)func_15142E24((s32)arg1, (s32)D_80091238, 0, 0, 0, 0, 0x92, 0, 0, &flag, 3);
    arg1 = func_15142B7C(arg1, 0x220005, 0x1D0600);
    arg1 = func_1513F4E4(arg1, 0x4E, &flag);
    arg1 = func_15142FBC(arg1, D_800D2C9C | 0x80000 | 0x2000 | 0xC00 | 0x80 | 0x20, D_800A4AC8[3][0] | D_800A4AC8[3][1], &flag);
    if (*(u16 *)(arg0 + 0x1E) & 2) {
        index = *(s8 *)(arg0 + 0x2E) - 1;
        if (index < 0) {
            index = arg0[0x25] - 1;
        }
        cur = *(Vec3f *)(arg0 + 0x10);
        curTexture = *(f32 *)(state + 0x38);
    } else {
        previous = *(s8 *)(arg0 + 0x2E) - 1;
        if (previous < 0) {
            previous = arg0[0x25] - 1;
        }
        index = previous - 1;
        if (index < 0) {
            index = arg0[0x25] - 1;
        }
        cur = records[previous].position;
        curTexture = records[previous].texture;
    }
    next = records[index].position;
    alpha = records[index].alpha;
    nextTexture = records[index].texture;
    delta.x = cur.x - next.x;
    delta.y = cur.y - next.y;
    delta.z = cur.z - next.z;
    toCamera.x = cur.x - camera->x;
    toCamera.y = cur.y - camera->y;
    toCamera.z = cur.z - camera->z;
    normal.x = delta.y * toCamera.z - toCamera.y * delta.z;
    normal.y = delta.z * toCamera.x - toCamera.z * delta.x;
    normal.z = delta.x * toCamera.y - toCamera.x * delta.y;
    lengthSquared = normal.x * normal.x + normal.y * normal.y + normal.z * normal.z;
    if (lengthSquared != 0.0f) {
        f32 scale = 4.0f / sqrtf(lengthSquared);

        normal.x *= scale;
        normal.y *= scale;
        normal.z *= scale;
    } else {
        normal.x = 0.0f;
        normal.y = 0.0f;
        normal.z = 0.0f;
    }
    vtx->ob[0] = cur.x + normal.x;
    vtx->ob[1] = cur.y + normal.y;
    vtx->ob[2] = cur.z + normal.z;
    vtx->tc[0] = curTexture;
    vtx->tc[1] = 0x400;
    vtx->cn[0] = 0xFF;
    vtx->cn[1] = 0xFF;
    vtx->cn[2] = 0xFF;
    vtx->cn[3] = alpha;
    vtx->flag = 0;
    vtx++;
    vtx->ob[0] = cur.x - normal.x;
    vtx->ob[1] = cur.y - normal.y;
    vtx->ob[2] = cur.z - normal.z;
    vtx->tc[0] = curTexture;
    vtx->tc[1] = 0;
    vtx->cn[0] = 0xFF;
    vtx->cn[1] = 0xFF;
    vtx->cn[2] = 0xFF;
    vtx->cn[3] = alpha;
    vtx->flag = 0;
    vtx++;
    do {
        delta.x = cur.x - next.x;
        delta.y = cur.y - next.y;
        delta.z = cur.z - next.z;
        toCamera.x = next.x - camera->x;
        toCamera.y = next.y - camera->y;
        toCamera.z = next.z - camera->z;
        normal.x = delta.y * toCamera.z - toCamera.y * delta.z;
        normal.y = delta.z * toCamera.x - toCamera.z * delta.x;
        normal.z = delta.x * toCamera.y - toCamera.x * delta.y;
        lengthSquared = normal.x * normal.x + normal.y * normal.y + normal.z * normal.z;
        if (lengthSquared != 0.0f) {
            f32 scale = 4.0f / sqrtf(lengthSquared);

            normal.x *= scale;
            normal.y *= scale;
            normal.z *= scale;
        } else {
            normal.x = 0.0f;
            normal.y = 0.0f;
            normal.z = 0.0f;
        }
        vtx->ob[0] = next.x + normal.x;
        vtx->ob[1] = next.y + normal.y;
        vtx->ob[2] = next.z + normal.z;
        vtx->tc[0] = nextTexture;
        vtx->tc[1] = 0x400;
        vtx->cn[0] = 0xFF;
        vtx->cn[1] = 0xFF;
        vtx->cn[2] = 0xFF;
        vtx->cn[3] = alpha;
        vtx->flag = 0;
        vtx++;
        vtx->ob[0] = next.x - normal.x;
        vtx->ob[1] = next.y - normal.y;
        vtx->ob[2] = next.z - normal.z;
        vtx->tc[0] = nextTexture;
        vtx->tc[1] = 0;
        vtx->cn[0] = 0xFF;
        vtx->cn[1] = 0xFF;
        vtx->cn[2] = 0xFF;
        vtx->cn[3] = alpha;
        vtx->flag = 0;
        vtx++;
        gSPVertex(arg1++, vtx - 4, 4, 0);
        gSP1Triangle(arg1++, 0, 1, 2, 0);
        gSP1Triangle(arg1++, 1, 3, 2, 0);
        if (nextTexture < curTexture) {
            func_10022EC0(vtx, vtx - 2, 0x20);
            vtx[-2].tc[0] -= 0x8000;
            vtx++;
            vtx[-2].tc[0] -= 0x8000;
            vtx++;
        }
        previous = index;
        index--;
        if (index < 0) {
            index = arg0[0x25] - 1;
        }
        cur = records[previous].position;
        next = records[index].position;
        alpha = records[index].alpha;
        curTexture = records[previous].texture;
        nextTexture = records[index].texture;
    } while (previous != *(s8 *)(arg0 + 0x2D));
    return arg1;
}
void func_150DA484(void *arg0) {
    u8 *temp_v0;
    u16 temp_a1;

    temp_v0 = *(u8 **)((u8 *)arg0 + 0x98);
    temp_a1 = *(u16 *)(temp_v0 + 0x30);
    if (temp_a1 != 0) {
        func_100111C8(temp_a1 & 0xFFFF, temp_a1);
    }
}
void func_150DA4B4(void *arg0) {
    func_150DA484(arg0);
    func_151478F4(arg0);
}
void func_150DA4E0(void *arg0) {
    func_150DA484(arg0);
    func_15147928(arg0);
}

void func_150DA50C(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 temp_v1;
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x98);
    temp_v1 = arg2;
    if (temp_v1 == 0x44) {
        if ((*(s32 *)temp_v0 == *(s32 *)arg1) || (temp_v0[4] == arg1[4])) {
            u8 *dst = temp_v0;

            *(f32 *)(dst + 0x3C) = *(f32 *)(arg1 + 8);
        }
    } else if (temp_v1 == 0) {
        temp_v1 = *(s32 *)arg1;
        if ((temp_v1 == *(s32 *)temp_v0) || (arg1[4] == temp_v0[4])) {
            func_1516972C(arg0);
        }
    } else if (temp_v1 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)temp_v0) {
            *(s32 *)temp_v0 = *(s32 *)(arg1 + 4);
            temp_v0[4] = arg1[9];
        } else if (*(s32 *)(arg1 + 4) == *(s32 *)temp_v0) {
            u8 *dst = temp_v0;

            *(s32 *)dst = *(s32 *)arg1;
            dst[4] = arg1[8];
        }
    }
}
void func_15147D64(void *, u8);

void func_150DA5EC(void *arg0, f32 arg1) {
    struct {
        void *object;
        u8 type;
        f32 value;
    } packet;

    packet.object = arg0;
    packet.type = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.value = arg1;
    func_15147D64(&packet, 0x44);
}
void func_15131828(s32, s32, s32, s32);
void func_15131958(void *, f32, s32);

s32 func_150DA628(s32 arg0, s32 arg1) {
    struct {
        s32 state;
        s32 pad;
    } locals;

    locals.state = arg0 + 0xA8;
    func_15131828(arg0, arg0 + 0xAC, locals.state, arg0 + 0xAA);
    func_15131958((void *)(arg0 + 0x58), *(f32 *)(locals.state + 0xC), locals.state);
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150DA67C.s")
