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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15004574 CURRENT (400) */
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
