#include "types.h"

/*
 * Reviewed source unit: src/game/game_122B60.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F56B0
 * - func_150F5A54
 * - func_150F5C98
 * - func_150F6178
 * - func_150F631C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150F631C(s32 arg0);
void func_1516972C(void *arg0);
void func_1514933C(s32 arg0);
void func_15149368(s32 arg0);
void func_10022EC0(s32, void **, s32);
s32 func_15149130(s16, s32, s32, s32, s32, s32, s32, s32, s32);

#pragma GLOBAL_ASM("asm/nonmatchings/game_122B60/func_150F56B0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F5A54 CURRENT (3690) */
s32 func_150F5A54(u8 *arg0, u8 *arg1) {
    u8 *actor;
    s32 entries;
    s32 mode;
    s32 index;
    s32 remaining;
    s32 flag;
    s32 value;
    f32 weight;
    f32 savedWeight;
    f32 distance;

    actor = *(u8 **)(arg1 + 0x2D0);
    remaining = 1;
    if (actor == 0) {
        return 0;
    }
    mode = *(s32 *)(arg0 + 0x38);
    flag = 0;
    entries = *(s32 *)(*(u8 **)(arg0 + 0x24));
    if (mode != 0) {
        if (mode != 1) {
            weight = savedWeight;
            if (mode == 2) {
                weight = 0.0f;
            }
        } else {
            weight = 1.0f;
        }
    } else {
        if (*(u16 *)(arg1 + 0x84) == 5) {
            *(s32 *)(arg0 + 0x38) = 1;
            savedWeight = 1.0f;
        } else {
            flag = 1;
        }
        weight = savedWeight;
    }
    if (*(u16 *)(arg1 + 0x84) == 5) {
        distance = *(f32 *)(actor + 8);
        if (distance < 69.0f) {
            weight = 1.0f;
        } else if (distance > 84.0f) {
            weight = 0.0f;
            *(s32 *)(arg0 + 0x38) = 2;
        } else {
            weight = 1.0f - ((distance - 69.0f) / 15.0f);
        }
    }
    index = 0;
    do {
        remaining -= 1;
        if (*(s8 *)(entries + index * 8) != -14) {
            do {
                index += 1;
            } while (*(s8 *)(entries + index * 8) != -14);
        }
        if (remaining != 0) {
            index += 1;
        }
    } while (remaining != 0);
    if (flag != 0) {
        value = 2;
    } else {
        value = (s32)((58.0f * weight) + 44.0f);
    }
    *(s32 *)(entries + index * 8) = (value & 0xFFF) | 0xF2002000;
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F5A54 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_122B60/func_150F5A54.s")
void func_150F5C08(void *arg0, s16 arg1, u8 arg2, s32 arg3) {
    struct {
        void *field_0;
        u8 field_4;
        u8 pad5[3];
        f32 field_8;
    } packet;
    s32 temp_v0;

    packet.field_0 = arg0;
    packet.field_4 = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.field_8 = 0.0f;
    temp_v0 = func_15149130(arg1, -1, 0x51, -1, 1, 0x3E, 0xC, (s32) arg2, arg3);
    if (temp_v0 != 0) {
        func_10022EC0(temp_v0 + 0x28, (void **)&packet, 0xC);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_122B60/func_150F5C98.s")
extern void func_15149514(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_150F6138(s32 arg0, s32 arg1, u8 arg2) {
    func_15149514(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}
void func_15145EA4(s32 *, s32 *, s32, s32);
extern u8 D_800A1B18[];
extern u8 D_800A1B24[];

typedef struct Game122B60Vec3Bits {
    u32 words[3];
} Game122B60Vec3Bits;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F6178 CURRENT (1318) */
void func_150F6178(u8 *arg0) {
    struct {
        u8 pad0[8];
        f32 *target[2];
        u8 *source[2];
        f32 vector1[3];
        f32 vector0[3];
        u8 padEnd[8];
    } local;
    u8 *actor;
    u8 *entry;
    u8 *child;
    u8 *other;
    u8 *object;

    entry = arg0 + 0x28;
    actor = *(u8 **)entry;
    if (*(s32 *)actor == 0 || entry[4] != actor[0x3B]) {
        *(s16 *)(arg0 + 0xE) = -1;
        return;
    }
    if (*(s32 *)(actor + 0x1D4) != 0 && !(*(s32 *)(actor + 0x94) & 2)) {
        local.source[0] = D_800A1B18;
        local.source[1] = D_800A1B24;
        local.target[0] = local.vector0;
        local.target[1] = local.vector1;
        func_15145EA4((s32 *)local.source, (s32 *)local.target,
                       *(s32 *)(actor + 0x1D4), 2);
        child = *(u8 **)(entry + 8);
        if (child != 0) {
            child[0x168] |= 1;
            *(Game122B60Vec3Bits *)(child + 0x34) =
                *(Game122B60Vec3Bits *)local.vector0;
            *(Game122B60Vec3Bits *)(child + 0x40) =
                *(Game122B60Vec3Bits *)local.vector1;
        }
        other = *(u8 **)(entry + 0xC);
        if (other != 0) {
            object = *(u8 **)(other + 0x14);
            object[9] = 0;
            *(s16 *)(object + 0xE) = (s32)local.vector0[0];
            *(s16 *)(object + 0x10) = (s32)local.vector0[1];
            *(s16 *)(object + 0x12) = (s32)local.vector0[2];
        }
    } else {
        child = *(u8 **)(entry + 8);
        if (child != 0) {
            object = child + 0x110;
            object[0x58] &= ~1;
        }
        other = *(u8 **)(entry + 0xC);
        if (other != 0) {
            object = *(u8 **)(other + 0x14);
            object[9] = 1;
        }
    }
    child = *(u8 **)(entry + 8);
    if (child != 0) {
        object = child + 0x110;
        *(f32 *)(object + 0x48) = 4.0f;
        *(f32 *)(object + 0x4C) = 8.0f;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F6178 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_122B60/func_150F6178.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F631C CURRENT (505) */
void func_150F631C(s32 arg0) {
    s32 temp_a1;
    void *temp_a0;

    temp_a1 = arg0;
    if (*(void **)((u8 *)temp_a1 + 0x30) != 0) {
        func_1516972C(*(void **)((u8 *)temp_a1 + 0x30));
    }
    temp_a0 = *(void **)((u8 *)temp_a1 + 0x34);
    if (temp_a0 != 0) {
        func_1516972C(temp_a0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F631C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_122B60/func_150F631C.s")
void func_150F6368(s32 arg0) {
    func_150F631C(arg0);
    func_1514933C(arg0);
}
void func_150F6394(s32 arg0) {
    func_150F631C(arg0);
    func_15149368(arg0);
}
