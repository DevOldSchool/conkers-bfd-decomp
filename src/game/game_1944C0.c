#include "types.h"

/*
 * Reviewed source unit: src/game/game_1944C0.c
 * Boundary evidence: docs/evidence/game_state_callback_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15167010
 * - func_151670C0
 * - func_151671E8
 * - func_15167310
 * - func_151674F8
 * - func_15167B44
 * - func_15167C58
 * - func_15167D84
 * - func_15167E0C
 * - func_15168118
 * - func_1516865C
 * - func_15168870
 * - func_15168A4C
 * - func_15168B44
 * - func_15168C4C
 * - func_15168E54
 * - func_15168F08
 * - func_15169070
 * - func_15169260
 * - func_1516944C
 * - func_151695F0
 * - func_1516962C
 * - func_151696DC
 * - func_15169850
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15168B10(s32 arg0, s32 arg1);

extern u8 D_8008B4A8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15167010 CURRENT (424) */
void func_15167010(void) {
    void (*temp_v0)(void);
    u8 *var_s0;

    var_s0 = &D_8008B4A8;
    do {
        temp_v0 = *(void (**)(void))(var_s0 + 0x18);
        if (temp_v0 != 0) {
            temp_v0();
        }
        var_s0 += 0x34;
    } while ((u32)var_s0 < (u32)(&D_8008B4A8 + 0x1484));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15167010 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15167010.s")
extern void (*D_8008CB64)(void);
extern void (*D_8008CB70)(void);

void func_1516706C(void) {
    void (**var_s0)(void);
    void (**var_s1)(void);
    void (*temp_v0)(void);

    var_s1 = (var_s0 = &D_8008CB64, &D_8008CB70);
    do {
        temp_v0 = *var_s0;
        if (temp_v0 != 0) {
            temp_v0();
        }
        var_s0++;
    } while (var_s0 != var_s1);
}
struct Game1944C0Node;

typedef struct Game1944C0ProcessNode {
    u8 pad0[8];
    struct Game1944C0Node *next;
} Game1944C0ProcessNode;

typedef struct Game1944C0CallbackEntry {
    void (*callback)(struct Game1944C0Node *);
    u8 pad4[0x30];
} Game1944C0CallbackEntry;

extern struct Game1944C0Node *D_800DCE50[][104];
extern s8 D_800DD190;
extern struct Game1944C0Node *D_800DD198[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151670C0 CURRENT (430) */
void func_151670C0(void) {
    Game1944C0CallbackEntry *entry;
    struct Game1944C0Node **slot;
    struct Game1944C0Node *node;
    s32 column;
    s32 row;

    row = 0;
    do {
        entry = (Game1944C0CallbackEntry *)&D_8008B4A8;
        column = 0;
        do {
            if (entry->callback != 0) {
                node = D_800DCE50[row][column];
                D_800DD190++;
                if (node != 0) {
                    slot = &D_800DD198[D_800DD190];
                    do {
                        *slot = ((Game1944C0ProcessNode *)node)->next;
                        entry->callback(node);
                        slot = &D_800DD198[D_800DD190];
                        node = *slot;
                    } while (node != 0);
                }
                D_800DD190--;
            }
            column++;
            entry++;
        } while (column != 0x65);
        row++;
    } while (row != 2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151670C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_151670C0.s")
typedef struct Game1944C0CallbackEntry2 {
    void (*callback0)(struct Game1944C0Node *);
    void (*callback1)(struct Game1944C0Node *);
    u8 pad8[0x2C];
} Game1944C0CallbackEntry2;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151671E8 CURRENT (430) */
void func_151671E8(void) {
    Game1944C0CallbackEntry2 *entry;
    struct Game1944C0Node **slot;
    struct Game1944C0Node *node;
    s32 column;
    s32 row;

    row = 0;
    do {
        entry = (Game1944C0CallbackEntry2 *)&D_8008B4A8;
        column = 0;
        do {
            if (entry->callback1 != 0) {
                node = D_800DCE50[row][column];
                D_800DD190++;
                if (node != 0) {
                    slot = &D_800DD198[D_800DD190];
                    do {
                        *slot = ((Game1944C0ProcessNode *)node)->next;
                        (*(void (**)(struct Game1944C0Node *))((u8 *)entry + 4))(node);
                        slot = &D_800DD198[D_800DD190];
                        node = *slot;
                    } while (node != 0);
                }
                D_800DD190--;
            }
            column++;
            entry++;
        } while (column != 0x65);
        row++;
    } while (row != 2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151671E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_151671E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15167310.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_151674F8.s")
typedef struct Game1944C0AllocatedEffect {
    s8 field_0;
    s8 field_1;
    u8 pad2[0xA];
    u8 field_C;
} Game1944C0AllocatedEffect;

Game1944C0AllocatedEffect *func_10003C6C(s32, s32, s32, s32, u8);
void func_15168A4C(s32, s32);

void *func_15167A68(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5) {
    Game1944C0AllocatedEffect *effect;
    Game1944C0AllocatedEffect *sp24;
    Game1944C0AllocatedEffect *result;

    effect = func_10003C6C(arg2, 1, arg3, 0, arg5);
    result = effect;
    if (effect != 0) {
        effect->field_1 = arg1;
        sp24 = effect;
        func_15168A4C((s32)result, arg0);
        result = sp24;
        result->field_C = arg4;
    }
    return result;
}

typedef struct Game1944C0Effect28 {
    u8 pad0[0x10];
    u8 payload[0x18];
} Game1944C0Effect28;

void *func_15167A68(s32, s32, s32, s32, u8, u8);
void func_10023A10(void *, void *, s32);

void func_15167AD8(void *arg0, u8 arg1, s32 arg2) {
    Game1944C0Effect28 *effect;

    effect = func_15167A68(3, arg2, sizeof(*effect), 0, arg1, 1);
    if (effect != 0) {
        func_10023A10(arg0, effect->payload, sizeof(effect->payload));
        effect->payload[0x13] = 0xFF;
    }
}
typedef void (*Game1944C0EffectCallback)(void);
extern Game1944C0EffectCallback D_8008CA20[];
void func_1516972C(u8 *);

typedef struct Game1944C0AnimatedEffect {
    u8 pad0[0x10];
    u8 *data;
    s16 frame;
    s16 step;
    u8 pad18[0xA];
    s8 fade;
    u8 alpha;
    u8 callback;
} Game1944C0AnimatedEffect;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15167B44 CURRENT (45) */
void func_15167B44(Game1944C0AnimatedEffect *arg0) {
    s16 temp_a2;
    s32 temp_a1;
    s8 temp_v1;
    u8 temp_v0;

    temp_v0 = arg0->callback;
    if (temp_v0 != 0) {
        D_8008CA20[temp_v0]();
    }
    temp_v1 = arg0->fade;
    if (temp_v1 > 0) {
        temp_v0 = arg0->alpha;
        if (temp_v1 < (s32)temp_v0) {
            arg0->alpha = temp_v0 - temp_v1;
        } else {
            arg0->frame = arg0->data[4] << 8;
        }
    } else if (temp_v1 < 0) {
        temp_a2 = arg0->frame;
        if ((temp_a2 / 256) >= (arg0->data[4] - 1)) {
            temp_v0 = arg0->alpha;
            temp_a1 = -temp_v1;
            if (temp_a1 < (s32)temp_v0) {
                arg0->alpha = temp_v0 - temp_a1;
                arg0->frame = temp_a2 - arg0->step;
            }
        }
    }
    arg0->frame += arg0->step;
    if ((arg0->frame / 256) >= (s32)arg0->data[4]) {
        func_1516972C((u8 *)arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15167B44 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15167B44.s")
typedef struct {
    u8 pad0[0x10];
    s32 **table;
    s16 frame;
    u8 pad16[2];
    s16 values[5];
    s8 field22;
    u8 field23;
} Game1944C0RenderInput;

typedef struct {
    s32 word0;
    s32 word1;
} Game1944C0Flags;

typedef struct {
    s32 mode;
    u8 pad04[4];
    s32 value;
    u8 pad0C[8];
    s16 values[5];
    u8 field1E;
    u8 pad1F[2];
    s8 field21;
} Game1944C0RenderLocals;

s32 func_15142E24(s32, s32, s32, s32, s32, s32, s32, u8, s32, u8 *, s32);
void *func_15142FBC(void *, s32, s32, u8 *);
void func_15095760(void *, s16 *);
extern Game1944C0Flags D_800A4AC8[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15167C58 CURRENT (736) */
void func_15167C58(s32 arg0, Game1944C0RenderInput *arg1, s32 arg2) {
    Game1944C0RenderLocals locals;
    s16 frame;
    s32 **table;
    s32 object;
    s8 field22;
    Game1944C0Flags *flags;

    locals.value = 1;
    frame = arg1->frame;
    table = arg1->table;
    object = func_15142E24(arg0, (s32) table, frame << 8, 2, 0x100, 0x100,
                          (*table)[frame >> 8], 5, (s32) locals.values,
                          (u8 *) &locals.value, 3);
    locals.values[0] = arg1->values[0];
    locals.values[1] = arg1->values[1];
    locals.values[2] = arg1->values[2];
    locals.values[3] = arg1->values[3];
    locals.values[4] = arg1->values[4];
    locals.field21 = 0;
    locals.field1E = arg1->field23;
    field22 = arg1->field22;
    if (field22 != 0xFF) {
        locals.mode = 3;
    } else if (field22 == 0xFF) {
        locals.mode = 9;
    }
    flags = &D_800A4AC8[locals.mode];
    func_15095760(func_15142FBC((void *) object, 0x2C00,
                                flags->word1 | flags->word0 | 4,
                                (u8 *) &locals.value), locals.values);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15167C58 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15167C58.s")
/* Call context: func_10023A10: unique active project prototype */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15167D84 CURRENT (1037) */
void func_15167D84(void *arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    u8 *temp_v0;
    u8 *sp24;
    s32 var_a0;

    if (arg1 == 0) {
        var_a0 = 5;
    } else {
        var_a0 = 0x42;
    }
    temp_v0 = (void *)(func_15167A68(var_a0, arg5, arg2 + 0x50, 0, (u8) (s32) arg4, 1U));
    if (temp_v0 == 0) {
        return;
    }
    sp24 = temp_v0;
    func_10023A10(arg0, temp_v0 + 0x10, 0x38);
    *(s8 *)((u8 *)sp24 + 0x48) = arg3;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15167D84 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15167D84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15167E0C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15168118.s")
extern u8 *D_8008CA4C[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516865C CURRENT (3865) */
void func_1516865C(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *record;
    u8 *cursor;
    u8 **table;
    s32 index;
    s16 value0;
    s16 value1;
    s16 value2;
    s16 value3;
    u16 flags;
    u8 a;

    arg1 &= 0xFF;
    arg2 &= 0xFF;
    arg3 &= 0xFF;
    a = *(u8 *)((u8 *)&arg4 + 3);
    value0 = 0x2000;
    value1 = 0x2000;
    table = D_8008CA4C;
    record = table[arg0[0xA0]];
    value2 = (s16)((*(u16 *)(record + 8) + 0x100) << 5);
    value3 = (s16)((*(u16 *)(record + 6) + 0x100) << 5);
    cursor = arg0;
    index = 0;
    do {
        index++;
        cursor += 0x40;
        *(s16 *)(cursor - 0x2A) = 0;
        cursor[-0x24] = arg1;
        cursor[-0x23] = arg2;
        cursor[-0x22] = arg3;
        cursor[-0x21] = a;
        *(s16 *)(cursor - 0x1A) = 0;
        cursor[-0x14] = arg1;
        cursor[-0x13] = arg2;
        cursor[-0x12] = arg3;
        cursor[-0x11] = a;
        *(s16 *)(cursor - 0xA) = 0;
        cursor[-4] = arg1;
        cursor[-3] = arg2;
        cursor[-2] = arg3;
        cursor[-1] = a;
        *(s16 *)(cursor - 0x3A) = 0;
        cursor[-0x34] = arg1;
        cursor[-0x33] = arg2;
        cursor[-0x32] = arg3;
        cursor[-0x31] = a;
    } while (index != 2);
    flags = *(u16 *)(arg0 + 0x98);
    if (flags & 0x80) {
        value2 = 0x2000;
        record = table[arg0[0xA0]];
        value0 = (s16)((*(u16 *)(record + 8) + 0x100) << 5);
    }
    if (flags & 0x100) {
        value3 = 0x2000;
        record = table[arg0[0xA0]];
        value1 = (s16)((*(u16 *)(record + 6) + 0x100) << 5);
    }
    *(s16 *)(arg0 + 0x68) = value1;
    *(s16 *)(arg0 + 0x7A) = value0;
    *(s16 *)(arg0 + 0x78) = value3;
    *(s16 *)(arg0 + 0x28) = *(s16 *)(arg0 + 0x68);
    *(s16 *)(arg0 + 0x58) = *(s16 *)(arg0 + 0x68);
    *(s16 *)(arg0 + 0x18) = *(s16 *)(arg0 + 0x68);
    *(s16 *)(arg0 + 0x5A) = value2;
    *(s16 *)(arg0 + 0x88) = 0;
    *(s16 *)(arg0 + 0x3A) = *(s16 *)(arg0 + 0x7A);
    *(s16 *)(arg0 + 0x6A) = *(s16 *)(arg0 + 0x7A);
    *(s16 *)(arg0 + 0x2A) = *(s16 *)(arg0 + 0x7A);
    *(s16 *)(arg0 + 0x9C) = 0;
    *(s16 *)(arg0 + 0x9E) = 0;
    *(s16 *)(arg0 + 0x38) = *(s16 *)(arg0 + 0x78);
    *(s16 *)(arg0 + 0x48) = *(s16 *)(arg0 + 0x78);
    *(s16 *)(arg0 + 8) = *(s16 *)(arg0 + 0x78);
    *(s16 *)(arg0 + 0x1A) = *(s16 *)(arg0 + 0x5A);
    *(s16 *)(arg0 + 0x4A) = *(s16 *)(arg0 + 0x5A);
    *(s16 *)(arg0 + 0xA) = *(s16 *)(arg0 + 0x5A);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516865C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_1516865C.s")
typedef struct Game1944C0EffectB8 {
    u8 pad0[0x10];
    u8 payload[0xA8];
} Game1944C0EffectB8;

Game1944C0EffectB8 *func_15168800(void *arg0, u8 arg1, s32 arg2) {
    Game1944C0EffectB8 *effect;
    Game1944C0EffectB8 *sp24;

    effect = func_15167A68(0xE, arg2, sizeof(*effect), 1, arg1, 1);
    if (effect == 0) {
        return 0;
    }
    sp24 = effect;
    func_10023A10(arg0, effect->payload, sizeof(effect->payload));
    return sp24;
}
typedef struct Game168870State {
    u8 pad00[0x98];
    s16 progress;
    s16 speed;
    u8 pad9C[0xC];
    u16 flags;
    u8 padAA[6];
    u8 descriptor;
    u8 padB1;
    s8 callback;
} Game168870State;

typedef void (*Game168870Callback)(void);
extern Game168870Callback D_8008C9C8[];
extern u8 *D_8008CA4C[];
extern s32 D_800BE9E4;
void func_1516972C(u8 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15168870 CURRENT (1275) */
void func_15168870(Game168870State *arg0) {
    s32 speed;
    s32 progress;
    s32 maximum;
    u16 flags;
    u8 width;
    Game168870Callback callback;

    speed = arg0->speed;
    if (speed != 0) {
        width = D_8008CA4C[arg0->descriptor][4];
        arg0->progress = arg0->progress + speed * D_800BE9E4;
        progress = arg0->progress;
        maximum = (width << 8) - 1;
        if (maximum < progress) {
            flags = arg0->flags;
            if (flags & 0x40) {
                arg0->progress = maximum - (progress % maximum);
                arg0->speed = -speed;
            } else if (flags & 4) {
                arg0->progress = -1;
            } else {
                do {
                    arg0->progress = arg0->progress - maximum;
                } while (maximum < arg0->progress);
            }
        } else if (progress < 0) {
            flags = arg0->flags;
            if (flags & 0x40) {
                arg0->progress = -progress % maximum;
                arg0->speed = -speed;
            } else if (flags & 4) {
                arg0->progress = -1;
            } else {
                do {
                    arg0->progress = arg0->progress + maximum;
                } while (arg0->progress < 0);
            }
        }
    }
    if (arg0->callback != -1) {
        callback = D_8008C9C8[arg0->callback];
        if (callback != 0) {
            callback();
        }
    }
    if (arg0->progress == -1) {
        func_1516972C((u8 *)arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15168870 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15168870.s")
void func_15168A2C(s32 arg0) {
    func_15168B10(arg0, 0);
}
void func_15168A9C(s32 arg0);

typedef struct Game1944C0Node {
    u8 field_0;
    u8 field_1;
    u8 pad_2[2];
    struct Game1944C0Node *field_4;
    struct Game1944C0Node *field_8;
} Game1944C0Node;

extern Game1944C0Node *D_800DCE50[][104];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15168A4C CURRENT (145) */
void func_15168A4C(s32 arg0, s32 arg1) {
    Game1944C0Node **temp_v1;
    Game1944C0Node *temp_t0;
    Game1944C0Node *node;

    node = (Game1944C0Node *)arg0;
    temp_v1 = &D_800DCE50[node->field_1][arg1];
    temp_t0 = *temp_v1;
    node->field_8 = temp_t0;
    if (temp_t0 != 0) {
        temp_t0->field_4 = node;
    }
    node->field_0 = arg1;
    node->field_4 = 0;
    *temp_v1 = node;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15168A4C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15168A4C.s")
void func_15168A9C(s32 arg0) {
    u8 row;
    u8 column;
    Game1944C0Node **head;
    Game1944C0Node *next;
    Game1944C0Node *node;

    node = (Game1944C0Node *)arg0;
    row = node->field_1;
    column = node->field_0;
    head = &D_800DCE50[row][column];
    if (node == *head) {
        *head = node->field_8;
    }
    next = node->field_8;
    if (next != 0) {
        next->field_4 = node->field_4;
    }
    next = node->field_4;
    if (next != 0) {
        next->field_8 = node->field_8;
    }
}
void func_15168B10(s32 arg0, s32 arg1) {
    func_15168A9C(arg0);
    func_15168A4C(arg0, arg1);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15168B44 CURRENT (375) */
void func_15168B44(void *arg0) {
    s32 temp_t2;
    s32 temp_t6;
    s32 temp_t9;
    s32 temp_v1;
    u8 temp_a2;

    temp_v1 = *(s32 *)((u8 *)arg0 + 0x14);
    temp_t6 = temp_v1 & 0xFFFF;
    if (temp_t6 != 0) {
        temp_t9 = temp_v1 & 0xFFFF0000;
        *(s32 *)((u8 *)arg0 + 0x14) = temp_t9;
        *(s16 *)((u8 *)arg0 + 0x38) = 0x1E;
        *(s32 *)((u8 *)arg0 + 0x14) = (s32) (temp_t9 | ((temp_t6 - 1) & 0xFFFF));
        return;
    }
    temp_a2 = *(u8 *)((u8 *)arg0 + 0x3F);
    temp_t2 = (temp_v1 >> 0x10) & 0xFFFF;
    if (temp_t2 < (s32) temp_a2) {
        *(u8 *)((u8 *)arg0 + 0x3F) = (u8) (temp_a2 - temp_t2);
        *(s16 *)((u8 *)arg0 + 0x38) = 0x1E;
        return;
    }
    *(s16 *)((u8 *)arg0 + 0x38) = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15168B44 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15168B44.s")
typedef void (*Game1944C0Callback)(void);
extern Game1944C0Callback D_8008CA20[];

void func_15168BAC(void *arg0) {
    u8 temp_v0;

    temp_v0 = *(u8 *)((u8 *)arg0 + 0xE4);
    if (temp_v0 != 0) {
        D_8008CA20[temp_v0]();
    }
}
typedef struct Game1944C0State {
    u8 pad0[0x40];
    void *active_effect;
} Game1944C0State;

typedef struct Game1944C0Effect {
    u8 pad0[0x90];
    u8 payload[0x60];
} Game1944C0Effect;

void *func_15167A68(s32, s32, s32, s32, u8, u8);
void func_10023A10(void *, void *, s32);

void func_15168BE4(Game1944C0State *arg0, u8 arg1, s32 arg2) {
    Game1944C0Effect *effect;

    if (arg0->active_effect != 0) {
        effect = func_15167A68(0x10, arg2, 0xF0, 1, arg1, 1);
        if (effect != 0) {
            func_10023A10(arg0, effect->payload, sizeof(effect->payload));
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15168C4C.s")
void func_15168E34(s32 *arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = *arg0;
    if (!(temp_v0 & 0x0F000000)) {
        *arg0 = temp_v0 + arg1;
    }
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15168E54 CURRENT (2110) */
void func_15168E54(s8 *arg0, s32 arg1) {
    s32 var_s0;
    s8 *var_v1;
    s8 var_v0;

    var_s0 = 0;
    var_v1 = arg0;
    if (*arg0 != -0x21) {
        var_v0 = *arg0;
        do {
            if ((var_v0 == 1) || ((var_v0 == -0x24) && (*(u8 *)((u8 *)var_v1 + 3) == 0xE))) {
                func_15168E34(var_v1 + 4, arg1);
            }
            var_s0 += 1;
            var_v1 = (var_s0 * 8) + arg0;
            var_v0 = *var_v1;
        } while (var_v0 != -0x21);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15168E54 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15168E54.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15168F08 CURRENT (1645) */
void func_15168F08(s8 *arg0, s32 arg1) {
    s32 temp_t9;
    s32 var_v0;
    s8 *var_v1;
    s8 var_a1;

    var_v0 = 0;
    var_v1 = arg0;
    if (*arg0 != -0x21) {
        var_a1 = *arg0;
        do {
            var_v0 += 1;
            if ((var_a1 == 1) || ((var_a1 == -0x24) && (*(u8 *)((u8 *)var_v1 + 3) == 0xE))) {
                temp_t9 = *(s32 *)((u8 *)var_v1 + 4) & 0xFFFFFF;
                *(s32 *)((u8 *)var_v1 + 4) = temp_t9;
                *(s32 *)((u8 *)var_v1 + 4) = (s32) (temp_t9 + arg1);
            }
            var_v1 = (var_v0 * 8) + arg0;
            var_a1 = *var_v1;
        } while (var_a1 != -0x21);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15168F08 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15168F08.s")
void func_15168F84(s32 arg0, s32 *arg1, s32 *arg2) {
    if (arg0 == 0) {
        *arg1 = 1;
        *arg2 = 0x41;
        return;
    }
    if (arg0 == 1) {
        *arg1 = 0x42;
        *arg2 = 0x4F;
        return;
    }
    if (arg0 == 2) {
        *arg1 = 0x50;
        *arg2 = 0x58;
        return;
    }
    if (arg0 == 3) {
        *arg1 = 0x59;
        *arg2 = 0x5C;
        return;
    }
    if (arg0 == 5) {
        *arg1 = 0x61;
        *arg2 = 0x63;
        return;
    }
    if (arg0 == 6) {
        *arg1 = 0x64;
        *arg2 = 0x65;
        return;
    }
    *arg1 = 0x5D;
    *arg2 = 0x60;
}
void func_15169070(s32 arg0, s32 arg1, s32 arg2, u8 arg3);

void func_15169040(s32 arg0, u8 arg1) {
    func_15169070(0, 0x68, arg0, arg1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15169070.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15169260.s")
void func_1516968C(void *, u8 *, u8);

typedef struct Game1944C0TraversalEntry {
    u8 pad0[0x1C];
    void (*callback)(Game1944C0Node *, s8 *, s32);
    u8 pad20[0x14];
} Game1944C0TraversalEntry;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516944C CURRENT (2645) */
void func_1516944C(s32 arg0, s8 *arg1, u8 arg2, u8 arg3) {
    Game1944C0Node **row;
    Game1944C0Node **head;
    Game1944C0Node **slot;
    Game1944C0Node *node;
    Game1944C0TraversalEntry *entry;
    s32 mode;

    mode = arg2 & 0xFF;
    if (arg0 >= 0x68) {
        arg0 = 0x67;
    }
    row = &D_800DCE50[0][0];
    head = row + arg0;
    entry = (Game1944C0TraversalEntry *)&D_8008B4A8 + arg0;
    do {
        if (entry->callback != 0) {
            node = *head;
            D_800DD190++;
            if (node != 0) {
                do {
                    slot = &D_800DD198[D_800DD190];
                    *slot = node->field_8;
                    func_1516968C(node, (u8 *)arg1, mode);
                    entry->callback(node, arg1, mode);
                    slot = &D_800DD198[D_800DD190];
                    node = *slot;
                } while (node != 0);
            }
            D_800DD190--;
        } else {
            node = *head;
            D_800DD190++;
            if (node != 0) {
                do {
                    slot = &D_800DD198[D_800DD190];
                    *slot = node->field_8;
                    func_1516968C(node, (u8 *)arg1, mode);
                    slot = &D_800DD198[D_800DD190];
                    node = *slot;
                } while (node != 0);
            }
            D_800DD190--;
        }
        row += 104;
        head += 104;
    } while ((void *)row != (void *)&D_800DD190);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516944C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_1516944C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151695F0 CURRENT (541) */
void func_151695F0(void *arg0, s32 arg1) {
    u8 sp1C;
    void *sp18;

    arg1 = arg1 & 0xFF;
    sp18 = arg0;
    sp1C = *(u8 *)((u8 *)arg0 + 0x3B);
    func_15169040((s32) &sp18, arg1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151695F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_151695F0.s")
/* Call context: func_1516944C: unique active project prototype */
void func_1516944C(s32, s8 *, u8, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516962C CURRENT (1300) */
void func_1516962C(s32 arg0, void *arg1, s32 arg2) {
    u8 sp1C;
    void *sp18;

    sp18 = arg1;
    sp1C = *(u8 *)((u8 *)arg1 + 0x3B);
    func_1516944C(arg0, (s8 *) &sp18, arg2 & 0xFF, (u8) arg1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516962C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_1516962C.s")
extern s8 D_800D2DAB;
void func_1516972C(u8 *arg0);

s32 func_15169668(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_800D2DAB = 1;
    return arg0;
}
void func_1516968C(void *arg0, u8 *arg1, u8 arg2) {
    if (((arg2 == 0xF) || (arg2 == 0x10)) &&
        (*arg1 == *(u8 *)((u8 *)arg0 + 0xC))) {
        func_1516972C(arg0);
    }
}
extern s8 D_800DD190;
extern Game1944C0Node *D_800DD198[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151696DC CURRENT (475) */
void func_151696DC(void *arg0) {
    Game1944C0Node **temp_a1;
    s8 temp_v0;

    temp_v0 = 0;
    if (D_800DD190 > 0) {
        do {
            temp_a1 = &D_800DD198[temp_v0];
            temp_v0++;
            if (arg0 == *temp_a1) {
                *temp_a1 = ((Game1944C0Node *)arg0)->field_8;
            }
        } while (temp_v0 < D_800DD190);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151696DC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_151696DC.s")
typedef void (*Game1944C0DestroyCallback)(u8 *);

typedef struct Game1944C0DestroyRecord {
    Game1944C0DestroyCallback callback;
    u8 pad4[0x30];
} Game1944C0DestroyRecord;

extern Game1944C0DestroyRecord D_8008B4D0[];
extern Game1944C0DestroyRecord D_8008B4D4[];
void func_151696DC(void *);
void func_15169804(s32);
void func_15169824(s32);

void func_1516972C(u8 *arg0) {
    Game1944C0DestroyCallback callback;
    u8 type;

    func_151696DC(arg0);
    type = *arg0;
    if (type >= 2) {
        callback = D_8008B4D0[type].callback;
        if (callback != 0) {
            callback(arg0);
            return;
        }
        func_15169804((s32)arg0);
    }
}

void func_1516979C(u8 *arg0) {
    Game1944C0DestroyCallback callback;

    func_151696DC(arg0);
    callback = D_8008B4D4[*arg0].callback;
    if (callback != 0) {
        callback(arg0);
        return;
    }
    func_15169824((s32)arg0);
}
void func_15169804(s32 arg0) {
    func_15168B10(arg0, 1);
}
void func_15168A9C(s32 arg0);
void func_10004074(s32 arg0);

void func_15169824(s32 arg0) {
    func_15168A9C(arg0);
    func_10004074(arg0);
}
/* Call context: func_1516972C: unique active declaration in the allowed source */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15169850 CURRENT (1088) */
void func_15169850(void *arg0, s32 arg1, s32 *arg2, u8 *arg3, u8 *arg4) {
    s32 temp_t6;
    s32 temp_v0;
    s32 temp_v1;

    temp_t6 = arg1 & 0xFF;
    if (temp_t6 == 0) {
        if ((*(s32 *)((u8 *)arg0 + 0) == *arg2) || (*(u8 *)((u8 *)arg0 + 4) == *arg3)) {
            func_1516972C(arg4);
        }
    } else if (temp_t6 == 0x2D) {
        temp_v1 = *(s32 *)((u8 *)arg0 + 0);
        temp_v0 = *arg2;
        if (temp_v1 == temp_v0) {
            *arg2 = (s32) *(u8 *)((u8 *)arg0 + 4);
            *arg3 = *(u8 *)((u8 *)arg0 + 9);
            return;
        }
        if ((s32) *(u8 *)((u8 *)arg0 + 4) == temp_v0) {
            *arg2 = temp_v1;
            *arg3 = *(u8 *)((u8 *)arg0 + 8);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15169850 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15169850.s")
