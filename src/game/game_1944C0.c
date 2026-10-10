#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1944C0.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_state_callback_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151670C0
 * - func_151671E8
 * - func_15167310
 * - func_151674F8
 * - func_15167C58
 * - func_15167E0C
 * - func_15168118
 * - func_1516865C
 * - func_15168870
 * - func_15168C4C
 * - func_15168E54
 * - func_15168F08
 * - func_15169070
 * - func_15169260
 * - func_1516944C
 * - func_15169850
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15168B10(s32 arg0, s32 arg1);

extern u8 D_8008B4A8;

typedef struct Game1944C0Struct115 { void (*unk0)(void *); u8 pad4[0x14]; void (*unk18)(void); u8 pad1C[0x18]; } struct115;

void func_15167010(void) {
    struct115 *var_s0;
    struct115 *end;
    void (*func)(void);
    s32 pad;

    var_s0 = (struct115 *)&D_8008B4A8;
    end = (struct115 *)((u32)var_s0 + 0x1484);
    pad = 0;
loop:
    func = (void (*)(void))var_s0->unk18;
    if (func != 0) {
        func();
    }
    var_s0++;
    pad ^= 0;
    if ((u32)var_s0 < (u32)end) {
        goto loop;
    }
}
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151670C0 CURRENT (2253) */
void func_151670C0(void) {
    Game1944C0CallbackEntry *entry;
    struct Game1944C0Node **slot;
    struct Game1944C0Node *node;
    s32 column;
    s32 row;

    row = 0;
    do {
        entry = (Game1944C0CallbackEntry *)(u32)&D_8008B4A8;
        column = 0;
        do {
            if (entry->callback != 0) {
                node = D_800DCE50[row][column];
                D_800DD190++;
                if (node != 0) {
                    slot = (struct Game1944C0Node **)((u32)D_800DD198 + ((u32)(s32)D_800DD190 << 2));
                    do {
                        *slot = ((Game1944C0ProcessNode *)node)->next;
                        entry->callback(node);
                        slot = (struct Game1944C0Node **)((u32)D_800DD198 + ((u32)(s32)D_800DD190 << 2));
                        node = *slot;
                    } while (node != 0);
                }
                D_800DD190--;
            }
            column++;
            entry = (Game1944C0CallbackEntry *)((u32)entry + sizeof(*entry));
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
typedef struct Game1944C0UpdateEntry {
    u8 pad0[0xC];
    void (*update)(struct Game1944C0Node *);
    u8 pad10[0x24];
} Game1944C0UpdateEntry;

f32 func_15047D60(f32);
f32 func_15047C00(f32);
extern s32 D_80082FA0;
extern void *D_800DBFF0;
extern f32 D_800DD1D0[2];
extern f32 D_800DD1D8[];
extern f32 D_800DD1E8[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15167310 CURRENT (1435) */
void func_15167310(void) {
    s32 columnOffset;
    struct Game1944C0Node *(*row)[104];
    struct Game1944C0Node **next;
    struct Game1944C0Node **head;
    struct Game1944C0Node *initial;
    struct Game1944C0Node *node;
    f32 *cosines;
    f32 *sines;
    f32 angle;
    f32 mainAngle;
    f32 cosineValue;
    s32 index;
    s32 offset;
    s32 column;
    Game1944C0UpdateEntry *entry;

    index = 0;
    offset = 0;
    if (D_80082FA0 + 1 > 0) {
        sines = D_800DD1D8;
        cosines = D_800DD1E8;
        do {
            angle = *(f32 *)((u8 *)D_800DBFF0 + offset + 0x3A0);
            *sines = func_15047D60(angle);
            cosineValue = func_15047C00(angle);
            index++;
            offset += 0x9A0;
            sines++;
            cosines++;
            cosines[-1] = cosineValue;
        } while (D_80082FA0 >= index);
    }
    mainAngle = *(f32 *)((u8 *)D_800DBFF0 + 0x3A0);
    D_800DD1D0[0] = func_15047D60(mainAngle);
    D_800DD1D0[1] = func_15047C00(mainAngle);
    column = 0;
    columnOffset = 0;
    do {
        row = D_800DCE50;
        head = (struct Game1944C0Node **)((u8 *)D_800DCE50 + columnOffset);
        do {
            initial = *head;
            if (initial != 0) {
                entry = (Game1944C0UpdateEntry *)&D_8008B4A8 + column;
                if (entry->update != 0) {
                    node = initial;
                    D_800DD190++;
                    if (initial != 0) {
                        next = &D_800DD198[D_800DD190];
                        do {
                            entry->update((*next = ((Game1944C0ProcessNode *)node)->next, node));
                            next = &D_800DD198[D_800DD190];
                            node = *next;
                        } while (node != 0);
                    }
                    D_800DD190--;
                }
            }
            row++;
            head = (struct Game1944C0Node **)((u8 *)head + 0x1A0);
        } while ((u8 *)row != (u8 *)&D_800DD190);
        column++;
        columnOffset += 4;
    } while (column != 104);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15167310 */
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
void func_15167B44(void *arg0)
{
  typedef struct
  {
    u8 pad[4];
    u8 unk4;
  } Inner;
  typedef struct
  {
    u8 pad0[0x10];
    Inner *unk10;
    s16 unk14;
    s16 unk16;
    u8 pad18[0xA];
    s8 unk22;
    u8 unk23;
    u8 unk24;
  } Local;
  Local *a = arg0;
  s8 v1;
  u32 v0;
  s16 a2;
  if (a->unk24 != 0)
  {
    ((void (*)(void *))D_8008CA20[a->unk24])(a);
  }
  v1 = a->unk22;
  if (v1 > 0)
  {
    v0 = a->unk23;
    if (v1 < ((s32) v0))
    {
      a->unk23 = v0 - v1;
    }
    else
    {
      a->unk14 = a->unk10->unk4 << 8;
    }
  }
  else
    if (v1 < 0)
  {
    a2 = a->unk14;
    if ((a2 / 256) >= (a->unk10->unk4 - 1))
    {
      if ((v1 && v1) && v1)
      {
      }
      v0 = a->unk23;
      if ((-v1) < ((s32) v0))
      {
        a->unk23 = v0 - (-v1);
        a->unk14 = a2 - a->unk16;
      }
    }
  }
  a->unk14 = a->unk14 + a->unk16;
  if ((a->unk14 / 256) >= ((s32) a->unk10->unk4))
  {
    func_1516972C((struct102 *) a);
  }
}
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

void *func_15167D84(void *arg0, s32 arg1, s32 arg2, s8 arg3, u8 arg4, s32 arg5) {
    void *v0 = func_15167A68(arg1 == 0 ? 5 : 0x42, arg5, arg2 + 0x50, 0, arg4, 1);

    if (v0 == 0) {
        return v0;
    }
    func_10023A10(arg0, (u8 *)v0 + 0x10, 0x38);
    ((s8 *)v0)[0x48] = arg3;
    return v0;
}
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15168870 CURRENT (245) */
void func_15168870(Game168870State *arg0) {
    s32 speed;
    s32 maximum;
    s32 flags;
    Game168870Callback callback;

    speed = arg0->speed;
    if (speed != 0) {
        flags = D_8008CA4C[arg0->descriptor][4];
        maximum = (flags << 8) - 1;
        arg0->progress = arg0->progress + speed * D_800BE9E4;
        if (maximum < arg0->progress) {
            flags = arg0->flags;
            if (flags & 0x40) {
                arg0->progress = maximum - (arg0->progress % maximum);
                arg0->speed = -speed;
            } else if (flags & 4) {
                arg0->progress = -1;
            } else {
                do {
                    arg0->progress = arg0->progress - maximum;
                } while (maximum < arg0->progress);
            }
        } else if (arg0->progress < 0) {
            flags = arg0->flags;
            if (flags & 0x40) {
                arg0->progress = -arg0->progress % maximum;
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

void func_15168A4C(s32 arg0, s32 arg1) {
    Game1944C0Node **temp_v1;
    Game1944C0Node *node;
    s32 group;

    node = (Game1944C0Node *)arg0;
    group = node->field_1;
    temp_v1 = &D_800DCE50[group][arg1];
    node->field_8 = *temp_v1;
    if (node->field_8 != 0) {
        node->field_8->field_4 = node;
    }
    node->field_0 = arg1;
    node->field_4 = 0;
    *temp_v1 = node;
}
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
typedef struct Local15168B44 { u8 pad0[0x14]; s32 unk14; u8 pad18[0x20]; s16 unk38; u8 pad3A[5]; u8 unk3F; } Local15168B44;

void func_15168B44(void *arg0)
{
  Local15168B44 *a;
  s32 v1;
  s32 new_var2;
  u16 t6;
  u16 hi;
  u8 a2;
  s32 new_var;
  s32 c0;
  s32 z0;
  s32 z1;
  s32 z2;
  s32 t9;
  s32 z3;
  s32 z4;
  s32 z5;
  s32 keep;
  a = arg0;
  hi = 0x1E;
  v1 = a->unk14;
  new_var2 = v1;
  t6 = ((u16) new_var2) ^ 0;
  new_var = t6 - (1 & 0xFFFFFFFFu);
  if (t6 != 0)
  {
    c0 = v1;
    z0 = 0;
    z1 = 0;
    z2 = 0;
    z3 = 0;
    z4 = 0;
    z5 = 0;
    keep = new_var & 0xFFFF;
    new_var = keep * 0;
    if (a)
    {
    }
    hi++;
    hi--;
    t9 = (v1 & 0xFFFF0000) | new_var;
    v1 = 0;
    a->unk14 = t9;
    a->unk38 = hi;
    if (keep)
    {
      ;
    }
    *((s32 *) (((s8 *) arg0) + 0x14)) = ((t9 | keep) | (((((((c0 * 0) | (z0 * 0)) | (z1 * 0)) | (z2 * 0)) | (z3 * 0)) | (z4 * 0)) | (z4 = z5 * 0))) & 0xFFFFFFFFu;
    return;
  }
  hi = (u16) (v1 >> 16);
  v1 = a->unk3F;
  if (0)
  {
  }
  a2 = v1;
  if (hi < a2)
  {
    a->unk3F = a2 - hi;
    if (1)
    {
    }
    a->unk38 = 0x1E;
  }
  else
  {
    a2 = 0;
    a->unk38 = (a2, 0);
  }
}
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
typedef struct Game1944C0Command {
    u32 w0, w1;
} Game1944C0Command;
typedef struct Game1944C0RenderState {
    u8 pad00[0x10];
    u8 matrices[2][0x40];
    f32 values90[3];
    f32 field9C, fieldA0, fieldA4;
    u8 padA8[0x18];
    f32 valuesC0[3];
    u8 padCC[4];
    s32 displayList;
    u8 padD4[0x11];
    u8 alpha, tile;
    u8 padE7[5];
    u8 kind, mode;
} Game1944C0RenderState;
void func_15043D90(s32, f32, f32, f32, f32, f32, f32, f32, f32, f32);
extern s16 D_800DD1C0, D_800DD1C2, D_800DD1C4, D_800DD1C6;
extern u8 D_800BE9C0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15168C4C CURRENT (383) */
void *func_15168C4C(Game1944C0Command *arg0, Game1944C0RenderState *arg1, s32 arg2) {
    s32 texture;
    u8 loaded;
    Game1944C0Command *result;

    func_15043D90((s32)arg1->matrices[D_800BE9C0], arg1->field9C, arg1->fieldA0, arg1->fieldA4,
                   arg1->valuesC0[0], arg1->valuesC0[1], arg1->valuesC0[2],
                   arg1->values90[0], arg1->values90[1], arg1->values90[2]);
    {
        Game1944C0Command *command = arg0++;
        command->w0 = 0xE7000000;
        command->w1 = 0;
    }
    {
        Game1944C0Command *command = arg0++;
        command->w0 = 0xFA000000;
        command->w1 = arg1->alpha;
    }
    D_800DD1C6 = arg1->alpha;
    D_800DD1C4 = 0;
    D_800DD1C2 = D_800DD1C4;
    D_800DD1C0 = D_800DD1C2;
    {
        Game1944C0Command *command = arg0++;
        command->w0 = 0xFB000000;
        command->w1 = 0;
    }
    {
        Game1944C0Command *command = arg0++;
        command->w0 = arg1->tile | 0xF2002000;
        command->w1 = 0x7E0FE;
    }
    switch (arg1->kind) {
    case 1: texture = 0x552230; break;
    case 2: texture = 0x504A50; break;
    }
    loaded = 0;
    result = func_15142FBC(arg0, 0x8ACA0, texture, &loaded);
    arg0 = result;
    if (arg1->mode == 1) {
        result->w0 = 0xFC123824;
        result->w1 = 0xFF73FFFF;
        arg0 = result + 1;
    }
    {
        Game1944C0Command *command = arg0++;
        command->w0 = 0xDA380003;
        command->w1 = (u32)arg1->matrices[D_800BE9C0];
    }
    {
        Game1944C0Command *command = arg0++;
        command->w0 = 0xDE000000;
        command->w1 = arg1->displayList;
    }
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15168C4C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15168C4C.s")
void func_15168E34(s32 *arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = *arg0;
    if (!(temp_v0 & 0x0F000000)) {
        *arg0 = temp_v0 + arg1;
    }
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15168E54 CURRENT (65) */
void func_15168E54(s8 *arg0, s32 arg1) {
    s32 var_s0;
    s8 *var_v1;
    s32 var_v0;

    var_s0 = 0;
    var_v1 = arg0;
    if (*(volatile s8 *)arg0 != -0x21) {
        var_v0 = *arg0;
        do {
            if ((var_v0 == 1) || ((var_v0 == -0x24) && (*(u8 *)((u8 *)var_v1 + 3) == 0xE))) {
                func_15168E34((s32 *)(var_v1 + 4), arg1);
            }
            var_s0 += 1;
            var_v1 = (s8 *)((var_s0 << 3) + (s32)arg0);
            var_v0 = *var_v1;
        } while (var_v0 != -0x21);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15168E54 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15168E54.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15168F08 CURRENT (1295) */
void func_15168F08(s8 *arg0, s32 arg1) {
    s32 temp_t9;
    s32 var_v0;
    s8 *var_v1;
    s32 var_a1;

    var_v0 = 0;
    var_v1 = arg0;
    if (*(volatile s8 *)arg0 != -0x21) {
        var_a1 = *arg0;
        do {
            var_v0 += 1;
            if ((var_a1 == 1) || ((var_a1 == -0x24) && (*(u8 *)((u8 *)var_v1 + 3) == 0xE))) {
                temp_t9 = *(s32 *)((u8 *)var_v1 + 4) & 0xFFFFFF;
                *(volatile s32 *)((u8 *)var_v1 + 4) = temp_t9;
                *(s32 *)((u8 *)var_v1 + 4) = (s32) (temp_t9 + arg1);
            }
            var_v1 = (s8 *)((var_v0 * 8) + (s32)arg0);
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
typedef struct Game1944C0TraversalEntry {
    u8 pad0[0x1C];
    void (*callback)(Game1944C0Node *, s8 *, u8);
    u8 pad20[0x14];
} Game1944C0TraversalEntry;

void func_1516968C(void *, u8 *, u8);
void func_15143D18(s32 *, s32 *, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15169070 CURRENT (2476) */
void func_15169070(s32 arg0, s32 arg1, s32 arg2, u8 arg3) {
    s32 offset;
    Game1944C0Node *(*row)[104];
    Game1944C0Node **slot;
    Game1944C0Node **head;
    Game1944C0Node *node;
    Game1944C0TraversalEntry *entry;

    func_15143D18(&arg0, &arg1, 2, 104);
    if (arg0 < arg1) {
        offset = arg0 * 4;
        entry = (Game1944C0TraversalEntry *)&D_8008B4A8 + arg0;
        do {
            row = D_800DCE50;
            head = (Game1944C0Node **)((u8 *)D_800DCE50 + offset);
            do {
                if (entry->callback != 0) {
                    node = *head;
                    D_800DD190++;
                    if (node != 0) {
                        slot = &D_800DD198[D_800DD190];
                        do {
                            *slot = node->field_8;
                            func_1516968C(node, (u8 *)arg2, arg3);
                            entry->callback(node, (s8 *)arg2, arg3);
                            slot = &D_800DD198[D_800DD190];
                            node = *slot;
                        } while (node != 0);
                    }
                    D_800DD190--;
                } else {
                    node = *head;
                    D_800DD190++;
                    if (node != 0) {
                        slot = &D_800DD198[D_800DD190];
                        do {
                            *slot = node->field_8;
                            func_1516968C(node, (u8 *)arg2, arg3);
                            slot = &D_800DD198[D_800DD190];
                            node = *slot;
                        } while (node != 0);
                    }
                    D_800DD190--;
                }
                row++;
                head += 104;
            } while (row != (Game1944C0Node *(*)[104])&D_800DD190);
            offset += 4;
            entry++;
        } while (offset < arg1 * 4);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15169070 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15169070.s")

void func_1516968C(void *, u8 *, u8);


#if 0 /* CONKER_DEFERRED_CANDIDATE func_15169260 CURRENT (781) */
void func_15169260(s32 *arg0, s32 arg1, u8 *arg2, u8 arg3) {
    s32 count;
    Game1944C0Node *(*row)[104];
    Game1944C0Node **slot;
    Game1944C0Node *node;
    s32 *ids;

    count = 0;
    ids = arg0;
    if (arg1 > 0) {
        do {
            row = D_800DCE50;
            do {
                if (((Game1944C0TraversalEntry *)&D_8008B4A8)[*ids].callback != 0) {
                    node = (*row)[*ids];
                    D_800DD190++;
                    if (node != 0) {
                        slot = &D_800DD198[D_800DD190];
                        do {
                            *slot = node->field_8;
                            func_1516968C(node, arg2, arg3);
                            ((Game1944C0TraversalEntry *)&D_8008B4A8)[*ids].callback(node, (s8 *)arg2, arg3);
                            slot = &D_800DD198[D_800DD190];
                            node = *slot;
                        } while (node != 0);
                    }
                    D_800DD190--;
                } else {
                    node = (*row)[*ids];
                    D_800DD190++;
                    if (node != 0) {
                        slot = &D_800DD198[D_800DD190];
                        do {
                            *slot = node->field_8;
                            func_1516968C(node, arg2, arg3);
                            slot = &D_800DD198[D_800DD190];
                            node = *slot;
                        } while (node != 0);
                    }
                    D_800DD190--;
                }
                row++;
            } while (row != (Game1944C0Node *(*)[104])&D_800DD190);
            ids++;
            count++;
        } while (count != arg1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15169260 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15169260.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516944C CURRENT (560) */
void func_1516944C(s32 arg0, s8 *arg1, u8 arg2) {
    Game1944C0Node **row;
    Game1944C0Node **head;
    Game1944C0Node **slot;
    Game1944C0Node *node;
    Game1944C0TraversalEntry *entry;

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
                    func_1516968C(node, (u8 *)arg1, arg2);
                    entry->callback(node, arg1, arg2);
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
                    func_1516968C(node, (u8 *)arg1, arg2);
                    slot = &D_800DD198[D_800DD190];
                    node = *slot;
                } while (node != 0);
            }
            D_800DD190--;
        }
        row += 104;
        head += 104;
    } while (row != (Game1944C0Node **)(D_800DCE50 + 2));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516944C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_1516944C.s")
void func_151695F0(void *arg0, u8 arg1) {
    struct { void *object; u8 kind; } descriptor;

    descriptor.object = arg0;
    descriptor.kind = *(u8 *)((u8 *)arg0 + 0x3B);
    func_15169040((s32) &descriptor, arg1);
}
/* Call context: func_1516944C: unique active project prototype */
void func_1516944C(s32, s8 *, u8);

void func_1516962C(s32 arg0, void *arg1, u8 arg2) {
    struct { void *object; u8 kind; } descriptor;

    descriptor.object = arg1;
    descriptor.kind = *(u8 *)((u8 *)arg1 + 0x3B);
    func_1516944C(arg0, (s8 *) &descriptor, arg2);
}
extern s8 D_800D2DAB;

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
void func_151696DC(struct102 *arg0) {
    s32 i;

    for (i = 0; i < D_800DD190; i = (s8)(i + 1)) {
        if (arg0 == ((void **)D_800DD198)[i]) {
            ((void **)D_800DD198)[i] = (void *)arg0->unk8;
        }
    }
}
typedef void (*Game1944C0DestroyCallback)(u8 *);

typedef struct Game1944C0DestroyRecord {
    Game1944C0DestroyCallback callback;
    u8 pad4[0x30];
} Game1944C0DestroyRecord;

extern Game1944C0DestroyRecord D_8008B4D0[];
extern Game1944C0DestroyRecord D_8008B4D4[];
void func_151696DC(struct102 *);
void func_15169804(s32);
void func_15169824(s32);

void func_1516972C(void *arg0) {
    Game1944C0DestroyCallback callback;
    u8 type;

    func_151696DC(arg0);
    type = *(u8 *)arg0;
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15169850 CURRENT (235) */
void func_15169850(void *arg0, u8 arg1, s32 *arg2, u8 *arg3, u8 *arg4) {
    s32 temp_v0;
    s32 temp_v1;

    if (arg1 == 0) {
        if ((*(s32 *)((u8 *)arg0 + 0) == *arg2) || (*(u8 *)((u8 *)arg0 + 4) == *arg3)) {
            func_1516972C(arg4);
        }
    } else if (arg1 == 0x2D) {
        temp_v1 = *(s32 *)((u8 *)arg0 + 0);
        temp_v0 = *arg2;
        if (temp_v1 == temp_v0) {
            *arg2 = *(s32 *)((u8 *)arg0 + 4);
            *arg3 = *(u8 *)((u8 *)arg0 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg0 + 4) == temp_v0) {
            *arg2 = temp_v1;
            *arg3 = *(u8 *)((u8 *)arg0 + 8);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15169850 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15169850.s")
