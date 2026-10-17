#include "types.h"

/*
 * Reviewed source unit: src/game/game_30E90.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150039E0
 * - func_15004574
 * - func_150045C4
 * - func_150049A4
 * - func_15004CE0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_30E90/func_150039E0.s")
extern s32 D_800DBEF4;
extern u8 D_800DBF88;
extern s32 D_800DBF8C;
extern s32 D_800DBF90;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15004574 CURRENT (200) */
void func_15004574(void) {
    void *temp_v1;

    if (D_800DBF88 != 0xFF) {
        temp_v1 = (u8 *)D_800DBEF4 + (D_800DBF88 * 0xA0);
        D_800DBF8C = *(s32 *)((u8 *)temp_v1 + 0x1C);
        D_800DBF90 = *(s32 *)((u8 *)temp_v1 + 0x28);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15004574 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_30E90/func_15004574.s")
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150045C4 CURRENT (2577) */
void func_150045C4(s32 arg0) {
    s32 index;
    s32 count;
    f32 matrix[16];
    s32 offset;
    s32 flags;
    f32 height;
    s32 hit;
    f32 x, y, z;
    s32 vertexIndex;
    s32 vertexOffset;
    u8 *object;

    func_15004A4C();
    func_150A7BC0(D_800DBF08);
    func_150A7BC0(D_800DBF48);
    count = D_800DBEF0;
    index = 0;
    offset = 0;
    if (count > 0) {
        do {
            object = (u8 *)(offset + D_800DBEF4);
            if (*(s32 *)(object + 0x38) == 0 ||
                (s32)func_15116058 == *(s32 *)(object + 0x38) ||
                (s32)func_15116110 == *(s32 *)(object + 0x38)) {
                object[0x4E] = 3;
            }
            if (!(object[0x70] & 1)) {
                func_1511490C(matrix, object);
                vertexOffset = index << 6;
                func_150A7790(matrix, *D_80089250[D_800BE9C0] + vertexOffset);
                vertexIndex = D_800BE9C0;
                count = vertexIndex == 0;
                func_10023A10((void *)(*D_80089250[vertexIndex] + vertexOffset),
                             (void *)(*D_80089250[count] + vertexOffset), 0x40);
            }
            if ((s32)func_151150B0 == *(s32 *)(object + 0x38)) {
                *(s32 *)(object + 0x38) = 0;
            }
            if ((object[0x70] & 1) == 1) {
                vertexIndex = 0;
                func_1511490C(matrix, object);
                vertexOffset = 0;
                if (*(u16 *)(object + 0x16) > 0) {
                    do {
                        func_150A7960(matrix, *(s16 *)(*(u8 **)(object + 0x28) + vertexOffset + 0), *(s16 *)(*(u8 **)(object + 0x28) + vertexOffset + 2), *(s16 *)(*(u8 **)(object + 0x28) + vertexOffset + 4), &x, &y, &z);
                        vertexIndex++;
                        *(s16 *)(*(u8 **)(object + 0x20) + vertexOffset) = (s32)x;
                        *(s16 *)(*(u8 **)(object + 0x20) + vertexOffset + 2) = (s32)y;
                        *(s16 *)(*(u8 **)(object + 0x20) + vertexOffset + 4) = (s32)z;
                        vertexOffset += 0x10;
                    } while (vertexIndex < *(u16 *)(object + 0x16));
                }
                func_10023A10(*(void **)(object + 0x20), *(void **)(object + 0x24),
                             *(u16 *)(object + 0x16) * 0x10);
            }
            func_1510F800(2);
            if ((object[0x6F] & 0x80) == 0x80 && (object[0x4F] & 0x60) != 0x20) {
                D_800D37E0 = index;
                func_150A44F0(1, &D_800D37E0, 1);
            }
            count = D_800DBEF0;
            index++;
            offset += 0xA0;
        } while (index < count);
        index = 0;
    }
    offset = 0;
    if (count > 0) {
        do {
            object = (u8 *)(offset + D_800DBEF4);
            if (object[0x6E] == 1) {
            } else if ((object[0x6F] & 0x20) == 0x20) {
                func_1510E7A4((s32)&hit, 0, (s32)&height, 0, (s32)&flags, 0,
                             *(s16 *)(object + 0x10), (f32)*(s16 *)(object + 0x12), *(s16 *)(object + 0x14),
                             (f32)*(s16 *)(object + 0x12), (u16)(index + 1), 0, D_800959D0, D_800959D4);
                *(s32 *)(object + 0x80) = hit;
                *(f32 *)(object + 0x84) = height;
                count = D_800DBEF0;
            }
            vertexIndex = index + 1;
            index = vertexIndex;
            offset += 0xA0;
        } while (vertexIndex < count);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150045C4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_30E90/func_150045C4.s")

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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15004CE0 CURRENT (1310) */
void func_15004CE0(s8 *arg0, s32 arg1) {
    s32 var_v0;
    s8 *var_v1;
    s8 var_a1;
    u32 temp_a1;

    var_v0 = 0;
    var_v1 = arg0;
    if (*arg0 != -0x21) {
        var_a1 = *arg0;
        do {
            var_v0 += 1;
            if ((var_a1 == -0x24) && (*(u8 *)((u8 *)var_v1 + 3) == 0xE)) {
                temp_a1 = *(u32 *)((u8 *)var_v1 + 4);
                if (temp_a1 < 0x80000000U) {
                    *(u32 *)((u8 *)var_v1 + 4) = (u32) (temp_a1 + arg1);
                }
            }
            var_v1 = (var_v0 * 8) + arg0;
            var_a1 = *var_v1;
        } while (var_a1 != -0x21);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15004CE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_30E90/func_15004CE0.s")
