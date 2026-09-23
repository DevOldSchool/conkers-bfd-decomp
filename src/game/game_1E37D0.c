#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E37D0.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B6320
 * - func_151B6420
 * - func_151B65D4
 * - func_151B6928
 * - func_151B70B4
 * - func_151B7144
 * - func_151B7328
 * - func_151B7678
 * - func_151B77F4
 * - func_151B7998
 * - func_151B7C38
 * - func_151B82CC
 * - func_151B8318
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    u8 field04;
    u8 pad05[3];
    f32 copiedPosition[3];
    f32 field14;
    f32 field18;
    f32 field1C;
    f32 field20;
    f32 field24;
    u8 pad28[8];
    f32 position[3];
    s16 field3C;
    s16 field3E;
    s32 field40;
    u8 field44;
    s8 field45;
    u8 pad46[2];
} Game1E37D0Spawn;

void *func_10022EC0(void *, const void *, u32);
void *func_15147A80(void *, void *, s32, s32, s32, s32, s32, s32,
                    s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B6320 CURRENT (2244) */
void func_151B6320(void *arg0, u8 arg1, s32 arg2) {
    u8 local[0x48];
    void *result;

    *(s8 *)&local[0x45] = 0xA;
    *(f32 *)&local[0x30] = *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)&local[0x34] = *(f32 *)((u8 *)arg0 + 0x18);
    *(s16 *)&local[0x3C] = 0x12C;
    *(s16 *)&local[0x3E] = 6;
    *(void **)&local[0] = arg0;
    *(f32 *)&local[0x38] = *(f32 *)((u8 *)arg0 + 0x1C);
    local[4] = *(u8 *)((u8 *)arg0 + 0x3B);
    *(s32 *)&local[8] = *(s32 *)&local[0x30];
    *(s32 *)&local[0xC] = *(s32 *)&local[0x34];
    *(s32 *)&local[0x10] = *(s32 *)&local[0x38];
    *(f32 *)&local[0x14] = 0.0f;
    *(f32 *)&local[0x18] = 0.0f;
    *(f32 *)&local[0x20] = -16384.0f;
    *(f32 *)&local[0x1C] = -16384.0f;
    *(f32 *)&local[0x24] = 0.0f;
    *(s32 *)&local[0x40] = 0xD;
    result = func_15147A80(&local[0x30], (void *)0x30, 0x1C, 0xB,
                           0xB, 0xB, 0, 0, 0, arg1, arg2);
    if (result != 0) {
        func_10022EC0(*(void **)((u8 *)result + 0x98), local, 0x2C);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B6320 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B6320.s")
typedef struct Game1B6420Record {
    u8 pad0[0xC];
    f32 countdown;
    u8 intensity;
    u8 pad11[7];
    f32 time;
} Game1B6420Record;

typedef struct Game1B6420Actor {
    u8 pad0[0x1E];
    u16 flags;
    u8 pad20[5];
    u8 capacity;
    u8 pad26[6];
    s8 count;
    s8 head;
    s8 tail;
    u8 pad2F[0x25];
    s32 output[3];
    u8 pad60[0x34];
    Game1B6420Record *records;
} Game1B6420Actor;

extern f32 D_800AA470;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B6420 CURRENT (110) */
s32 func_151B6420(Game1B6420Actor *actor) {
    Game1B6420Record *records;
    Game1B6420Record *record;
    s32 index;
    s32 intensity;
    f32 zero;
    f32 baseTime;
    f32 scale;

    records = actor->records;
    if (actor->count < 2 && (actor->flags & 8)) {
        return 0;
    }
    index = actor->tail;
    zero = 0.0f;
    if (index != actor->head) {
        do {
            index--;
            if (index < 0) {
                index = actor->capacity - 1;
            }
            record = &records[index];
            record->countdown -= D_800BE9A4;
            if (record->countdown < zero && index != actor->head) {
                do {
                    actor->head++;
                    if (actor->capacity == actor->head) {
                        actor->head = 0;
                    }
                    actor->count--;
                } while (index != actor->head);
            }
        } while (index != actor->head);
    }
    if (actor->count > 0) {
        index = actor->head;
        baseTime = records[index].time;
        scale = D_800AA470;
        do {
            record = &records[index];
            intensity = (s32)((record->time - baseTime) * scale);
            if (intensity >= 0x9C) {
                record->intensity = 0x9B;
            } else {
                record->intensity = intensity;
            }
            index++;
            if (index >= actor->capacity) {
                index = 0;
            }
        } while (index != actor->tail);
    }
    if (actor->count > 0) {
        record = &records[actor->head];
        actor->output[0] = *(s32 *)((u8 *)record + 0);
        actor->output[1] = *(s32 *)((u8 *)record + 4);
        actor->output[2] = *(s32 *)((u8 *)record + 8);
    } else {
        *(f32 *)&actor->output[0] = zero;
        *(f32 *)&actor->output[1] = zero;
        *(f32 *)&actor->output[2] = zero;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B6420 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B6420.s")
f32 func_15143E64(f32 *, void *, void *);           /* extern */
extern f32 D_800AA474;
extern f32 D_800AA478;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B65D4 CURRENT (7417) */
s32 func_151B65D4(u8 *arg0) {
    u8 *spB4;
    s32 spB0;
    f32 spA8;
    f32 spA4;
    f32 spA0;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp58;
    f32 sp50;
    f32 sp48;
    f32 temp_fa0;
    f32 temp_fs2;
    f32 temp_ft1;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fs0;
    f32 var_ft4;
    f32 var_ft5;
    s8 temp_v0_3;
    u8 *temp_a2;
    u8 *temp_t2;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_a2 = (void *)(*(void **)((u8 *)arg0 + 0x98));
    temp_v0 = (void *)(*(void **)((u8 *)temp_a2 + 0));
    if ((*(s32 *)((u8 *)temp_v0 + 0) == 0) || (*(u8 *)((u8 *)temp_a2 + 4) != *(u8 *)((u8 *)temp_v0 + 0x3B)) || (*(f32 *)((u8 *)temp_v0 + 0x3C) < 15.0f)) {
        *(s8 *)((u8 *)arg0 + 0x30) = 0;
        *(u16 *)((u8 *)arg0 + 0x1E) = (u16) (*(u16 *)((u8 *)arg0 + 0x1E) | 8);
        return 1;
    }
    *(f32 *)((u8 *)arg0 + 0x10) = (f32) *(f32 *)((u8 *)temp_v0 + 0x14);
    *(f32 *)((u8 *)arg0 + 0x14) = (f32) *(f32 *)((u8 *)temp_v0 + 0x18);
    *(f32 *)((u8 *)arg0 + 0x18) = (f32) *(f32 *)((u8 *)temp_v0 + 0x1C);
    spA0 = *(f32 *)((u8 *)arg0 + 0x10) - *(f32 *)((u8 *)temp_a2 + 8);
    spA4 = *(f32 *)((u8 *)arg0 + 0x14) - *(f32 *)((u8 *)temp_a2 + 0xC);
    spB0 = *(s32 *)((u8 *)arg0 + 0x94);
    spB4 = temp_a2;
    spA8 = *(f32 *)((u8 *)arg0 + 0x18) - *(f32 *)((u8 *)temp_a2 + 0x10);
    temp_fv0 = func_15143E64(&spA0, arg0, temp_a2);
    *(f32 *)((u8 *)spB4 + 0x14) = (f32) (*(f32 *)((u8 *)spB4 + 0x14) + (temp_fv0 * D_800AA474 * D_800BE9A4));
    temp_fv1 = *(f32 *)((u8 *)spB4 + 0x14);
    *(f32 *)((u8 *)spB4 + 0x1C) = (f32) (*(f32 *)((u8 *)spB4 + 0x1C) + (temp_fv0 * D_800AA478));
    sp58 = temp_fv1;
    if (temp_fv1 > 1.0f) {
        temp_t2 = (void *)(spB4 + 8);
        temp_fv1_2 = 1.0f / sp58;
        *(f32 *)((u8 *)&sp84 + 0) = *(f32 *)((u8 *)spB4 + 8);
        *(s32 *)((u8 *)&sp84 + 4) = (s32) *(s32 *)((u8 *)temp_t2 + 4);
        var_ft5 = *(f32 *)((u8 *)spB4 + 0x18) + D_800BE9A4;
        *(s32 *)((u8 *)&sp84 + 8) = (s32) *(s32 *)((u8 *)temp_t2 + 8);
        temp_fa0 = *(f32 *)((u8 *)spB4 + 0x20);
        var_fs0 = *(f32 *)((u8 *)spB4 + 0x24);
        var_ft4 = temp_fa0;
        temp_fs2 = -(var_ft5 * temp_fv1_2);
        sp50 = (*(f32 *)((u8 *)spB4 + 0x1C) - temp_fa0) * temp_fv1_2;
        sp48 = temp_fv0 * temp_fv1_2;
        do {
            temp_v0_2 = (void *)((*(s8 *)((u8 *)arg0 + 0x2E) * 0x1C) + spB0);
            *(f32 *)((u8 *)temp_v0_2 + 0) = (f32) *(f32 *)((u8 *)&sp84 + 0);
            *(s32 *)((u8 *)temp_v0_2 + 4) = (s32) *(s32 *)((u8 *)&sp84 + 4);
            *(s8 *)((u8 *)temp_v0_2 + 0x10) = 0x9B;
            *(f32 *)((u8 *)temp_v0_2 + 0x14) = var_ft4;
            *(s32 *)((u8 *)temp_v0_2 + 8) = (s32) *(s32 *)((u8 *)&sp84 + 8);
            temp_ft1 = 13.0f - var_ft5;
            var_ft5 += temp_fs2;
            *(f32 *)((u8 *)temp_v0_2 + 0xC) = temp_ft1;
            if (var_ft4 > 16384.0f) {
                do {
                    *(f32 *)((u8 *)temp_v0_2 + 0x14) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0x14) - 32768.0f);
                } while (*(f32 *)((u8 *)temp_v0_2 + 0x14) > 16384.0f);
            }
            *(f32 *)((u8 *)temp_v0_2 + 0x18) = var_fs0;
            *(s8 *)((u8 *)arg0 + 0x2E) = (s8) (*(s8 *)((u8 *)arg0 + 0x2E) + 1);
            if (*(u8 *)((u8 *)arg0 + 0x25) == *(s8 *)((u8 *)arg0 + 0x2E)) {
                *(s8 *)((u8 *)arg0 + 0x2E) = 0;
            }
            temp_v0_3 = *(s8 *)((u8 *)arg0 + 0x2D);
            *(s8 *)((u8 *)arg0 + 0x2C) = (s8) (*(s8 *)((u8 *)arg0 + 0x2C) + 1);
            if (temp_v0_3 == *(s8 *)((u8 *)arg0 + 0x2E)) {
                *(s8 *)((u8 *)arg0 + 0x2D) = (s8) (temp_v0_3 + 1);
                if (*(u8 *)((u8 *)arg0 + 0x25) == *(s8 *)((u8 *)arg0 + 0x2D)) {
                    *(s8 *)((u8 *)arg0 + 0x2D) = 0;
                }
                *(s8 *)((u8 *)arg0 + 0x2C) = (s8) (*(s8 *)((u8 *)arg0 + 0x2C) - 1);
            }
            sp84 += spA0 * temp_fv1_2;
            sp88 += spA4 * temp_fv1_2;
            var_ft4 += sp50;
            sp8C += spA8 * temp_fv1_2;
            var_fs0 += sp48;
            *(f32 *)((u8 *)spB4 + 0x14) = (f32) (*(f32 *)((u8 *)spB4 + 0x14) - 1.0f);
        } while (*(f32 *)((u8 *)spB4 + 0x14) > 1.0f);
        *(f32 *)((u8 *)spB4 + 8) = (f32) *(f32 *)((u8 *)&sp84 + 0);
        *(s32 *)((u8 *)temp_t2 + 4) = (s32) *(s32 *)((u8 *)&sp84 + 4);
        *(s32 *)((u8 *)temp_t2 + 8) = (s32) *(s32 *)((u8 *)&sp84 + 8);
        *(f32 *)((u8 *)spB4 + 0x20) = var_ft4;
        *(f32 *)((u8 *)spB4 + 0x24) = var_fs0;
        *(f32 *)((u8 *)spB4 + 0x18) = var_ft5;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B65D4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B65D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B6928.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B70B4 CURRENT (805) */
void func_151B70B4(void *arg0, void *arg1, u8 arg2) {
    s32 temp_a3;
    s32 temp_v1;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    temp_a3 = *(s32 *)((u8 *)temp_v0 + 0);
    if (arg2 == 0) {
        if (temp_a3 == *(s32 *)((u8 *)arg1 + 0)) {
            *(s8 *)((u8 *)arg0 + 0x30) = 0;
            *(u16 *)((u8 *)arg0 + 0x1E) = (u16) (*(u16 *)((u8 *)arg0 + 0x1E) | 8);
        }
    } else if (arg2 == 0x2D) {
        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        if (temp_v1 == temp_a3) {
            *(s32 *)((u8 *)temp_v0 + 0) = (s32) *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_a3) {
            *(s32 *)((u8 *)temp_v0 + 0) = temp_v1;
            *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B70B4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B70B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B7144.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B7328.s")
typedef struct {
    s32 field_0;
    u8 pad_4[0x10];
    f32 field_14;
    f32 field_18;
    f32 field_1C;
    u8 pad_20[0x1B];
    u8 field_3B;
} Game1E37D0Data;

typedef struct {
    Game1E37D0Data *field_0;
    u8 field_4;
} Game1E37D0Entry;

typedef struct {
    u8 pad_0[4];
    Game1E37D0Entry *field_4;
} Game1E37D0Root;

typedef struct {
    u8 pad_0[0x98];
    Game1E37D0Root *field_98;
} Game1E37D0State;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B7678 CURRENT (90) */
s32 func_151B7678(void *arg0, f32 *arg1) {
    void *temp_v1;
    void *temp_a2;

    temp_v1 = *(void **)(*(u8 **)((u8 *)arg0 + 0x98) + 4);
    temp_a2 = *(void **)temp_v1;
    if ((*(s32 *)temp_a2 == 0) || (*(u8 *)((u8 *)temp_v1 + 4) != *(u8 *)((u8 *)temp_a2 + 0x3B))) {
        return 0;
    }
    arg1[0] = *(f32 *)((u8 *)temp_a2 + 0x14);
    arg1[1] = *(f32 *)((u8 *)temp_a2 + 0x18);
    arg1[2] = *(f32 *)((u8 *)temp_a2 + 0x1C);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B7678 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B7678.s")
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
void func_150A8050(f32 *, s32, s32, s32);

typedef struct Game1E37D0TransformLocals {
    u8 pad0[4];
    f32 matrix[12];
    f32 translation[3];
    u8 pad40[4];
} Game1E37D0TransformLocals;

s32 func_151B76CC(void *arg0, f32 *arg1) {
    void *entry;
    void *root;
    void *data;
    Game1E37D0TransformLocals local;

    root = *(void **)((u8 *)arg0 + 0x98);
    entry = *(void **)((u8 *)root + 4);
    data = *(void **)entry;
    func_150A8050(local.matrix, *(s32 *)((u8 *)data + 0x20),
                    *(s32 *)((u8 *)data + 0x24), *(s32 *)((u8 *)data + 0x28));
    local.translation[0] = *(f32 *)((u8 *)data + 0x38);
    local.translation[1] = *(f32 *)((u8 *)data + 0x3C);
    local.translation[2] = *(f32 *)((u8 *)data + 0x40);
    local.matrix[0] *= *(f32 *)((u8 *)data + 0x18);
    local.matrix[1] *= *(f32 *)((u8 *)data + 0x18);
    local.matrix[2] *= *(f32 *)((u8 *)data + 0x18);
    local.matrix[4] *= *(f32 *)((u8 *)data + 0x1C);
    local.matrix[5] *= *(f32 *)((u8 *)data + 0x1C);
    local.matrix[6] *= *(f32 *)((u8 *)data + 0x1C);
    local.matrix[8] *= *(f32 *)((u8 *)data + 0x18);
    local.matrix[9] *= *(f32 *)((u8 *)data + 0x18);
    local.matrix[10] *= *(f32 *)((u8 *)data + 0x18);
    func_150A7960(local.matrix, 0.0f, 0.0f, -250.0f, arg1,
                  (f32 *)((u8 *)arg1 + 4), (f32 *)((u8 *)arg1 + 8));
    return 1;
}
typedef struct Game1E37D0Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Game1E37D0Vec3;

typedef struct Game1E37D0RingEntry {
    Game1E37D0Vec3 position;
    f32 distance;
    u8 state;
    u8 pad11[3];
} Game1E37D0RingEntry;

typedef struct Game1E37D0RingState {
    u8 *linked;
    u8 pad4[4];
    u8 selector;
} Game1E37D0RingState;

typedef struct Game1E37D0RingObject {
    u8 pad0[0x10];
    Game1E37D0Vec3 position;
    u8 pad1C[9];
    u8 capacity;
    u8 pad26[6];
    s8 count;
    s8 tail;
    s8 head;
    u8 pad2F[0x65];
    Game1E37D0RingEntry *entries;
    Game1E37D0RingState *state;
} Game1E37D0RingObject;

extern s32 D_800BE9E4;
extern s32 (*D_8008FB90[])(Game1E37D0RingObject *, Game1E37D0Vec3 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B77F4 CURRENT (821) */
s32 func_151B77F4(Game1E37D0RingObject *arg0) {
    Game1E37D0Vec3 previous;
    Game1E37D0Vec3 delta;
    Game1E37D0RingState *state;
    Game1E37D0RingEntry *entries;
    Game1E37D0RingEntry *entry;
    s8 tail;
    f32 distance;

    entries = arg0->entries;
    state = arg0->state;
    if (D_800BE9E4 > 0) {
        previous = arg0->position;
        if (D_8008FB90[state->selector](arg0, &arg0->position) == 0) {
            return 0;
        }
        if (state->linked != 0) {
            *(Game1E37D0Vec3 *)(state->linked + 0x40) = arg0->position;
        }
        delta.x = arg0->position.x - previous.x;
        delta.y = arg0->position.y - previous.y;
        delta.z = arg0->position.z - previous.z;
        distance = func_15143E64(&delta.x, &arg0->position, arg0);
        entry = &entries[arg0->head];
        entry->position = arg0->position;
        entry->distance = distance;
        entry->state = 0xFF;
        arg0->head++;
        if (arg0->head == arg0->capacity) {
            arg0->head = 0;
        }
        arg0->count++;
        tail = arg0->tail;
        if (tail == arg0->head) {
            arg0->tail = tail + 1;
            if (arg0->tail == arg0->capacity) {
                arg0->tail = 0;
            }
            arg0->count--;
        }
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B77F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B77F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B7998.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B7C38.s")
extern void (*D_8008FB98[])(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B82CC CURRENT (455) */
void func_151B82CC(void *arg0, s32 arg1, s32 arg2) {
    void (*temp_v1)(s32);

    arg2 &= 0xFF;
    temp_v1 = D_8008FB98[*(u8 *)((u8 *)*(void **)((u8 *)arg0 + 0x98) + 8)];
    if (temp_v1 != 0) {
        temp_v1(arg2);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B82CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B82CC.s")
void func_1516972C(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B8318 CURRENT (487) */
void func_151B8318(void *arg0, void *arg1, s32 arg2) {
    s32 temp_t6;
    void *temp_v1;

    temp_t6 = arg2 & 0xFF;
    temp_v1 = *(void **)(*(u8 **)((u8 *)arg0 + 0x98) + 4);
    if ((temp_t6 == 0) && ((*(s32 *)arg1 == *(s32 *)temp_v1) || (*(u8 *)((u8 *)temp_v1 + 4) == *(u8 *)((u8 *)arg1 + 4)))) {
        func_1516972C(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B8318 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B8318.s")
