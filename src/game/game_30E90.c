#include "types.h"

/*
 * Reviewed source unit: src/game/game_30E90.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150039E0
 * - func_150049A4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_30E90/func_150039E0.s")
extern s32 D_800DBEF4;
extern u8 D_800DBF88;
extern s32 D_800DBF8C;
extern s32 D_800DBF90;

void func_15004574(void) {
    void *temp_v1;

    if (D_800DBF88 != 0xFF) {
        temp_v1 = (u8 *)D_800DBEF4 + (D_800DBF88 * 0xA0);
        D_800DBF8C = *(s32 *)((u8 *)temp_v1 + 0x1C);
        D_800DBF90 = *(s32 *)((u8 *)temp_v1 + 0x28);
    }
}

void func_150045BC(void) {
}
void func_10023A10(void *, void *, s32);
void func_15004A4C(void);
void func_150A44F0(s32, void *, s32);
void func_150A7790(void *, s32);
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
void func_150A7BC0(void *);
void func_1511490C(void *, void *);
void func_1510E7A4(s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, u16, s32, f32, f32);
void func_1510F800(s32);
void func_151150B0(s32);
void func_15116058(void *);
void func_15116110(void *);
extern s32 *D_80089250[];
extern f32 D_800959D0, D_800959D4;
extern u8 D_800BE9C0;
extern s16 D_800D37E0;
extern u8 D_800DBF08[], D_800DBF48[];
extern s32 D_800DBEF0;

typedef struct Game30E90Vertex {
    s16 x;
    s16 y;
    s16 z;
    u8 unk_06[0xA];
} Game30E90Vertex;

typedef struct Game30E90Object {
    u8 unk_00[0x10];
    s16 x;
    s16 y;
    s16 z;
    u16 vertexCount;
    u8 unk_18[0x8];
    Game30E90Vertex *vertices;
    Game30E90Vertex *verticesCopy;
    Game30E90Vertex *sourceVertices;
    u8 unk_2C[0xC];
    void *callback;
    u8 unk_3C[0x12];
    u8 unk_4E;
    u8 unk_4F;
    u8 unk_50[0x1E];
    u8 unk_6E;
    u8 unk_6F;
    u8 unk_70;
    u8 unk_71[0xF];
    s32 hit;
    f32 height;
    u8 unk_88[0x18];
} Game30E90Object;

void func_150045C4(s32 arg0) {
    s32 index;
    Game30E90Object *object;
    f32 matrix[16];
    s32 vertexIndex;
    s32 flags;
    f32 height;
    s32 hit;
    f32 x, y, z;
    s32 other;

    func_15004A4C();
    func_150A7BC0(D_800DBF08);
    func_150A7BC0(D_800DBF48);
    for (index = 0; index < D_800DBEF0; index++) {
        object = (Game30E90Object *)(index * 0xA0 + D_800DBEF4);
        if (object->callback == NULL ||
            object->callback == (void *)func_15116058 ||
            object->callback == (void *)func_15116110) {
            object->unk_4E = 3;
        }
        if (!(object->unk_70 & 1)) {
            func_1511490C(matrix, object);
            func_150A7790(matrix, *D_80089250[D_800BE9C0] + (index << 6));
            other = D_800BE9C0 == 0;
            func_10023A10((void *)(*D_80089250[D_800BE9C0] + (index << 6)),
                         (void *)(*D_80089250[other] + (index << 6)), 0x40);
        }
        if (object->callback == (void *)func_151150B0) {
            object->callback = NULL;
        }
        if ((object->unk_70 & 1) == 1) {
            func_1511490C(matrix, object);
            for (vertexIndex = 0; vertexIndex < object->vertexCount; vertexIndex++) {
                func_150A7960(matrix, object->sourceVertices[vertexIndex].x,
                              object->sourceVertices[vertexIndex].y,
                              object->sourceVertices[vertexIndex].z, &x, &y, &z);
                object->vertices[vertexIndex].x = x;
                object->vertices[vertexIndex].y = y;
                object->vertices[vertexIndex].z = z;
            }
            func_10023A10(object->vertices, object->verticesCopy,
                          object->vertexCount * sizeof(Game30E90Vertex));
        }
        func_1510F800(2);
        if ((object->unk_6F & 0x80) == 0x80 && (object->unk_4F & 0x60) != 0x20) {
            D_800D37E0 = index;
            func_150A44F0(1, &D_800D37E0, 1);
        }
    }
    for (index = 0; index < D_800DBEF0; index++) {
        object = (Game30E90Object *)(index * 0xA0 + D_800DBEF4);
        if (object->unk_6E == 1) {
            continue;
        }
        if ((object->unk_6F & 0x20) == 0x20) {
            func_1510E7A4((s32)&hit, 0, (s32)&height, 0, (s32)&flags, 0,
                          object->x, object->y, object->z, object->y,
                          index + 1, 0, -10000.0f, 20000.0f);
            object->hit = hit;
            object->height = height;
        }
    }
}


#if 0 /* CONKER_DEFERRED_CANDIDATE func_150049A4 CURRENT (1375) */
void func_150049A4(s8 *arg0, s32 arg1, s32 arg2) {
    s32 offset1;
    s32 offset2;
    s32 index;

    index = 0;
    offset1 = arg1;
    offset2 = arg2;
    arg1 = (s32)arg0;
    if (*(volatile s8 *)arg0 != -0x21) {
        arg2 = *arg0;
        do {
            index++;
            switch (arg2) {
            case 0xDE:
                *(s32 *)(arg1 + 4) += offset1;
                break;
            case 1:
                *(s32 *)(arg1 + 4) += offset1;
                break;
            case -0x24:
                if (*(u8 *)(arg1 + 3) == 0xE) {
                    *(s32 *)(arg1 + 4) += offset2;
                }
                break;
            }
            arg1 = (s32)arg0 + (index << 3);
            arg2 = *(s8 *)arg1;
        } while (arg2 != -0x21);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150049A4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_30E90/func_150049A4.s")
extern s32 D_800DBEF0;
extern s32 D_800DBEF8;
extern s32 D_800DBEFC;

/* Semantic role: placed_object_reset_vertex_cache_slots.
 * Clear per-object cache-pointer/countdown slots without freeing payloads.
 * See docs/evidence/assets/naming/placed_object_helper_semantics.md.
 */
void func_15004A4C(void) {
    s32 objectIndex;
    s32 cacheSlotOffset;

    objectIndex = 0;
    cacheSlotOffset = 0;
    if (D_800DBEF0 > 0) {
        do {
            *(s32 *)(D_800DBEF8 + cacheSlotOffset) = 0;
            cacheSlotOffset += 4;
            *(u8 *)(D_800DBEFC + objectIndex) = 0;
            objectIndex += 1;
        } while (objectIndex < D_800DBEF0);
    }
}
extern u16 D_800BE2A0;
extern u16 D_800BE2A2;
extern u16 D_800BE2A4;

f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
void func_15004AAC(void *arg0, s32 arg1) {
    f32 sz;
    f32 sx;
    f32 sy;
    f32 x;
    f32 y;
    f32 z;
    f32 root;
    f32 new_var;
    s32 maxv = 0;
    s32 off;
    s32 len;
    s32 val;
    s16 *p;
    u16 new_var2;
    u16 cur;
    u16 count;

    count = *((u16 *)(((s8 *)arg0) + 0x16));
    new_var2 = count;
    if (0 < ((s32)new_var2)) {
        if ((arg0 && arg0) && arg0) {
        }
        off = 0;
        p = *((s16 **)(((s8 *)arg0) + 0x28));
        sz = *((f32 *)(((s8 *)arg0) + 0x34));
        z = ((f32)p[2]) * sz;
        sx = *((f32 *)(((s8 *)arg0) + 0x2C));
        x = ((f32)p[0]) * sx;
        sy = *((f32 *)(((s8 *)arg0) + 0x30));
        if (!arg0) {
        }
        len = ((s32)new_var2) * 0x10;
        do {
            off += 0x10;
            z = ((f32)p[2]) * sz;
            x = ((f32)p[0]) * sx;
            new_var = sy;
            y = ((f32)p[1]) * new_var;
            val = (s32)((z * z) + ((x * x) + (y * y)));
            if (maxv < val) {
                maxv = val;
            }
            p = p + 8;
        } while (off < len);
    }
    if (maxv != 0) {
        cur = *((u16 *)(((s8 *)arg0) + 0x50));
        root = sqrtf((f32)maxv);
        if ((*((u16 *)(((s8 *)arg0) + 0x50))) == 0) {
            val = (s32)root;
            *((u16 *)(((s8 *)arg0) + 0x50)) = (u16)val;
            *((u16 *)(((s8 *)arg0) + 0x52)) = (u16)val;
            D_800BE2A2 += 1;
            return;
        }
        val = (s32)root;
        if ((((s32)cur) < val) || (((s32)(*((u16 *)(((s8 *)arg0) + 0x52)))) < val)) {
            D_800BE2A0 += 1;
            return;
        }
        D_800BE2A4 += 1;
    }
}
extern s32 D_800DBEF0;
extern u8 D_800DBF00;

/* Semantic role: placed_object_choose_id.
 * Exhaustion returns 255 in ascending mode or the starting ID in descending
 * mode; uniqueness is not guaranteed. arg0 is reused as start/fallback.
 * See docs/evidence/assets/naming/placed_object_helper_semantics.md.
 */
s32 func_15004BF0(s32 arg0) {
    typedef struct { u8 before[0x72]; u8 objectId; u8 after[0x2D]; } Entry;
    s32 objectIndex;
    s32 candidateObjectId;

    if (arg0 == 0) {
        candidateObjectId = 1;
        for (objectIndex = (arg0 = D_800DBF00); objectIndex < D_800DBEF0; objectIndex++) {
            if (candidateObjectId == ((Entry *)D_800DBEF4)[objectIndex].objectId) {
                candidateObjectId++;
                objectIndex = arg0 - 1;
            }
            if (candidateObjectId >= 0x100) {
                candidateObjectId = 0xFF;
                break;
            }
        }
    } else {
        arg0 = 0xFF - D_800DBF00;
        candidateObjectId = arg0;
        for (objectIndex = 0; objectIndex < D_800DBEF0; objectIndex++) {
            if (candidateObjectId == ((Entry *)D_800DBEF4)[objectIndex].objectId) {
                candidateObjectId--;
                objectIndex = -1;
            }
            if (candidateObjectId <= 0) {
                candidateObjectId = arg0;
                break;
            }
        }
    }
    return candidateObjectId;
}
void func_15004CE0(s8 *arg0, s32 arg1) {
    s32 i;
    s8 *entry;

    for (i = 0; arg0[i << 3] != -0x21; i++) {
        entry = &arg0[i << 3];
        if (entry[0] == -0x24 && (u8)entry[3] == 0xE) {
            if (*(u32 *)&entry[4] < 0x80000000U) {
                *(u32 *)&entry[4] += arg1;
            }
        }
    }
}
