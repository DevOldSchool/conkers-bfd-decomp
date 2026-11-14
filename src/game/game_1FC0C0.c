#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1FC0C0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_direct_helper_pairs.md
 */

s32 func_151CEC10(void *arg0, void *arg1, void *arg2) {
    typedef struct { s32 words[3]; } Copy3;
    s32 var_v0;

    var_v0 = 1;
    if (arg2 != 0) {
        *(Copy3 *)arg0 = *(Copy3 *)((u8 *)arg2 + 0x40);
    } else {
        *(f32 *)((u8 *)arg0 + 0) = *(f32 *)((u8 *)arg1 + 0x14);
        *(f32 *)((u8 *)arg0 + 4) = *(f32 *)((u8 *)arg1 + 0x18);
        *(f32 *)((u8 *)arg0 + 8) = *(f32 *)((u8 *)arg1 + 0x1C);
    }
    return var_v0;
}
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
extern f32 D_800AB00C;
extern f32 D_800AB010;
extern s32 D_800BE9E4;

typedef struct { f32 x, y, z; } TrailVec3;
typedef struct { f32 x, z; } TrailVec2;
typedef struct { f32 w[4]; } TrailQuad;

typedef struct {
    s32 unk0;
    u8 pad4[0x37];
    u8 unk3B;
} TrailSub;

typedef struct {
    TrailSub *sub;
    u8 unk4;
    u8 pad5[3];
    void *unk8;
    TrailVec2 scaled;
    TrailVec2 normal;
    u8 flags;
} TrailInfo;

typedef struct {
    TrailVec3 pos;
    f32 dist;
    f32 invLen;
    f32 unk14;
    TrailVec2 scaled;
    TrailVec2 normal;
} TrailEntry;

typedef struct {
    u8 pad0[0x10];
    TrailVec3 pos;
    u8 pad1C[2];
    u16 flags;
    u8 pad20[5];
    u8 count;
    u8 pad26[6];
    s8 num;
    s8 tail;
    s8 head;
    u8 pad2F[0x65];
    TrailEntry *entries;
    TrailInfo *info;
} TrailObj;

s32 func_151CEC54(TrailObj *arg0) {
    TrailInfo *info;
    TrailEntry *entries;
    TrailSub *sub;
    void *unk8;
    TrailVec3 prev;
    TrailVec3 delta;
    f32 dist;
    f32 len;
    f32 inv;
    f32 dx;
    f32 dz;
    f32 nx;
    f32 nz;

    info = arg0->info;
    entries = arg0->entries;
    sub = info->sub;
    unk8 = info->unk8;
    if (sub != NULL) {
        if (sub->unk0 == 0 || sub->unk3B != info->unk4) {
            return 0;
        }
    }
    if (D_800BE9E4 > 0) {
        prev = arg0->pos;
        if (func_151CEC10(&arg0->pos, sub, unk8) != 0) {
            if (!(arg0->flags & 4)) {
                prev = arg0->pos;
            } else if (!(info->flags & 1)) {
                dx = arg0->pos.x - prev.x;
                dz = arg0->pos.z - prev.z;
                len = sqrtf(dx * dx + dz * dz);
                if (len != 0.0f) {
                    inv = 1.0f / len;
                    info->flags |= 1;
                    nz = dx * inv;
                    nx = -(dz * inv);
                    info->normal.x = nx;
                    info->scaled.x = nx * 51.0f;
                    info->normal.z = nz;
                    info->scaled.z = nz * 51.0f;
                }
            }
            arg0->flags |= 4;
        } else {
            arg0->flags &= ~4;
            return 1;
        }
        delta.x = arg0->pos.x - prev.x;
        delta.y = arg0->pos.y - prev.y;
        delta.z = arg0->pos.z - prev.z;
        dist = func_15143E64(&delta);
        if (dist > D_800AB00C) {
            TrailEntry *e;

            e = &entries[arg0->head];
            e->pos = arg0->pos;
            e->dist = dist;
            len = sqrtf(delta.x * delta.x + delta.z * delta.z);
            if (len == 0.0f) {
                e->invLen = 1.0f;
            } else {
                e->invLen = 1.0f / len;
            }
            e->unk14 = 0.0f;
            e->scaled = info->scaled;
            e->normal = info->normal;
            arg0->head++;
            if (arg0->head == arg0->count) {
                arg0->head = 0;
            }
            arg0->num++;
            if (arg0->head == arg0->tail) {
                arg0->tail++;
                if (arg0->tail == arg0->count) {
                    arg0->tail = 0;
                }
                arg0->num--;
            }
            if ((info->flags & 2) && arg0->num >= 3) {
                TrailEntry *e1;
                TrailEntry *e2;
                f32 headInv;
                s16 j;
                s16 k;
                f32 d1z;
                f32 d1x;
                f32 d2z;
                f32 d2x;
                f32 midInv;
                f32 scale;
                TrailVec2 n;
                f32 lenSq;

                j = arg0->head - 1;
                if (j < 0) {
                    j = arg0->count - 1;
                }
                j = j - 1;
                if (j < 0) {
                    j = arg0->count - 1;
                }
                k = j - 1;
                if (k < 0) {
                    k = arg0->count - 1;
                }
                e1 = &entries[j];
                e2 = &entries[k];
                headInv = e->invLen;
                midInv = e1->invLen;
                d1x = (e->pos.x - e1->pos.x) * headInv;
                d1z = (e->pos.z - e1->pos.z) * headInv;
                d2x = (e2->pos.x - e1->pos.x) * midInv;
                d2z = (e2->pos.z - e1->pos.z) * midInv;
                n.x = -(d1z - d2z);
                n.z = d1x - d2x;
                lenSq = n.x * n.x + n.z * n.z;
                if (lenSq > D_800AB010) {
                    f32 normInv;

                    scale = 51.0f;
                    normInv = 1.0f / sqrtf(lenSq);
                    n.x *= normInv;
                    n.z *= normInv;
                    e1->normal = n;
                    e1->scaled.x = n.x * scale;
                    e1->scaled.z = n.z * scale;
                } else {
                    e1->scaled.x = 0.0f;
                    e1->scaled.z = 0.0f;
                    e1->normal.x = 0.0f;
                    e1->normal.z = 0.0f;
                }
            }
        }
    }
    return 1;
}
