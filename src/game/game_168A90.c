#include "types.h"

/*
 * Reviewed source unit: src/game/game_168A90.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_state_callback_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1513B5E0
 * - func_1513B798
 * - func_1513B83C
 * - func_1513BAE8
 * - func_1513BBFC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game168A90Allocated {
    u8 pad00[0x4C];
    s32 *source;
    s32 size;
    s32 value;
    void *first;
    u8 pad5C[0xC];
    void *second;
} Game168A90Allocated;

extern s32 D_80082FA0;
s32 *func_1502B6BC(s32 *, s32, s32 *, s32, s32, s32);
void *func_15167A68(s32, s32, s32, s32, u8, u8);
void func_1510CE60(s32, s32, s32, s32, void *);
void *func_10022EC0(void *, const void *, u32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513B5E0 CURRENT (2607) */
void *func_1513B5E0(s8 *arg0, u8 arg1, s32 arg2, u8 arg3, s32 arg4) {
    s32 *volatile sp70;
    s32 sp6C;
    s32 sp60;
    s32 sp5C;
    s32 sp50;
    s32 itemSize;
    s32 stride;
    s32 total;
    s32 kind;
    s32 index;
    u8 *first;
    u8 *entry;
    u8 *copySource;
    Game168A90Allocated *result;
    Game168A90Allocated *cursor;

    sp70 = func_1502B6BC(&sp60, 0, &sp5C, 2,
                          *(s32 *)(arg0 + 0x30), *(s32 *)(arg0 + 0x34));
    itemSize = *sp70 - (s32)sp70 - 0x28;
    stride = itemSize * 2;
    total = stride * (D_80082FA0 + 1);
    kind = 0x38;
    if (arg1 & 0xFF) {
        kind = 0x54;
    }
    sp50 = stride;
    sp6C = total;
    result = func_15167A68(kind, arg4, arg2 + total + 0xF8,
                           2, (u8)arg3, 1);
    if (result == 0) {
        return 0;
    }
    sp50 = stride;
    func_10022EC0((u8 *)result + 0x10, arg0, 0x3C);
    cursor = result;
    result->source = sp70;
    index = 0;
    first = (u8 *)result + 0xF8;
    copySource = (u8 *)sp70 + 0x28;
    if (D_80082FA0 + 1 > 0) {
        do {
            entry = first + itemSize;
            cursor->first = first;
            cursor->second = entry;
            func_10022EC0(first, copySource, itemSize);
            func_10022EC0(cursor->second, copySource, itemSize);
            index++;
            cursor = (Game168A90Allocated *)((u8 *)cursor + 4);
            first += sp50;
        } while (D_80082FA0 >= index);
    }
    result->value = *sp70;
    result->size = sp6C;
    func_1510CE60(*sp70, 0, 1, 0x3E, 0);
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513B5E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513B5E0.s")
typedef s32 (*Game168A90Callback)(void *);

extern Game168A90Callback D_80089C18[];
extern s32 D_800BE9E4;
void func_1516972C(void *arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513B798 CURRENT (120) */
void func_1513B798(void *arg0) {
    s32 result;
    u8 sp1B;
    s8 callback_index;
    u8 callback_pending;

    callback_pending = 0;
    if (*(u8 *)((u8 *)arg0 + 0x10) & 1) {
        *(s16 *)((u8 *)arg0 + 0x14) = (s16) (*(s16 *)((u8 *)arg0 + 0x14) - D_800BE9E4);
        if (*(s16 *)((u8 *)arg0 + 0x14) < 0) {
            callback_pending = 1;
        }
    }
    if (callback_pending == 0) {
        callback_index = *(s8 *)((u8 *)arg0 + 0x11);
        if (callback_index != -1) {
            sp1B = callback_pending;
            result = D_80089C18[(s32) callback_index](arg0);
            callback_pending = sp1B;
            if (result == 0) {
                callback_pending = 1;
            }
        }
    }
    if (callback_pending != 0) {
        func_1516972C(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513B798 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513B798.s")
typedef struct {
    u8 pad0[0x10];
    u8 flags;
    u8 pad11;
    s8 callback;
    u8 pad13[0x41];
    s32 displayList;
} Game168A90RenderState;

typedef s32 (*Game168A90RenderCallback)(void *, s16, s32, void *);

typedef struct {
    u32 word0;
    u32 word1;
} Game168A90Command;

extern Game168A90RenderCallback D_80089C28[];
extern u8 D_800BE9C0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513B83C CURRENT (4000) */
void *func_1513B83C(void *arg0, Game168A90RenderState *arg1, s32 arg2) {
    s32 result;
    Game168A90Command *cursor;
    Game168A90Command *command;

    arg2 = (s16) arg2;
    if ((arg1->flags & 2) && !(*((u8 *) arg1 + 0x49) & (1 << arg2))) {
        return arg0;
    }
    if (arg1->callback != -1) {
        result = D_80089C28[arg1->callback](arg1, arg2, arg2, arg0);
        if (result == 0) {
            return arg0;
        }
    }

    cursor = arg0;
    command = cursor++;
    command->word0 = 0xDA380003;
    command->word1 = (s32) ((u8 *) arg1 + (D_800BE9C0 << 6) + 0x78);
    command = cursor++;
    command->word0 = 0xDB060004;
    command->word1 =
        *(s32 *) ((u8 *) arg1 + (D_800BE9C0 << 4) + (arg2 * 4) + 0x58);
    command = cursor++;
    command->word0 = 0xDE000000;
    command->word1 = arg1->displayList;
    return cursor;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513B83C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513B83C.s")
void func_150A7B80(void *);
extern u8 D_800BE9C0;

s32 func_1513B968(s32 arg0, s32 arg1) {
    func_150A7B80(((u8 (*)[0x40])arg0)[D_800BE9C0] + 0x78);
    return 1;
}
void func_100043B4(void *arg0, s32 arg1);
void func_15169804(s32 arg0);
void func_15169824(s32 arg0);

void func_1513B9A8(void *arg0) {
    func_100043B4(((Game168A90Allocated *)arg0)->source, 4);
    func_15169804((s32)arg0);
}
void func_1513B9DC(void *arg0) {
    func_100043B4(((Game168A90Allocated *)arg0)->source, 4);
    func_15169824((s32)arg0);
}
typedef void (*Func_1513BA10)(void *);
extern Func_1513BA10 D_80089C44[];

void func_1513BA10(void *arg0) {
    D_80089C44[*(u8 *)((u8 *)arg0 + 0x48)](arg0);
}
extern Func_1513BA10 D_80089C54[];

void func_1513BA44(void *arg0) {
    D_80089C54[*(u8 *)((u8 *)arg0 + 0x48)](arg0);
}
void func_15109064(void *, void *, u8);
void func_151BA468(void *, void *, u8);

void func_1513BA78(void *arg0, void *arg1, u8 arg2) {
    switch (*(u8 *)((u8 *)arg0 + 0x48)) {
    case 1:
        func_15109064(arg0, arg1, arg2);
        return;
    case 2:
        func_151BA468(arg0, arg1, arg2);
        return;
    }
}
s32 func_1513BAD4(s32 arg0, s32 arg1) {
    return 0;
}
void *func_10022EC0(void *, const void *, u32);
void *func_1513B5E0(s8 *, u8, s32, u8, s32);

typedef struct Game168A90SpawnParams {
    s8 field_00;
    s8 field_01;
    s8 field_02;
    u8 pad03;
    s16 field_04;
    u8 pad06[2];
    s32 field_08;
    s32 field_0C;
    s32 field_10;
    s32 field_14;
    s32 field_18;
    s32 field_1C;
    s32 field_20;
    s8 field_24;
    s8 field_25;
    u8 pad26[10];
    s32 field_30;
    s32 field_34;
    s8 field_38;
    u8 pad39[3];
} Game168A90SpawnParams;

typedef struct Game168A90Vector5 {
    f32 field_00;
    f32 field_04;
    f32 field_08;
    f32 field_0C;
    f32 field_10;
} Game168A90Vector5;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513BAE8 CURRENT (1102) */
void *func_1513BAE8(void) {
    void *sp74;
    Game168A90SpawnParams sp38;
    Game168A90Vector5 sp24;
    register void *temp_v0;
    register void *var_a3;

    sp38.field_01 = 2;
    sp38.field_02 = 5;
    sp38.field_04 = 0x12C;
    sp38.field_30 = 9;
    sp24.field_00 = 0.0f;
    sp24.field_04 = 0.0f;
    sp24.field_0C = 0.0f;
    sp24.field_10 = 0.0f;
    sp24.field_08 = 0.0f;
    sp38.field_00 = 0;
    sp38.field_34 = 0x1AE;
    sp38.field_08 = 1;
    sp38.field_0C = 0x220205;
    sp38.field_10 = 0x40600;
    sp38.field_24 = 0;
    sp38.field_25 = 0;
    sp38.field_14 = 1;
    sp38.field_18 = 0x36;
    sp38.field_1C = 0x80;
    sp38.field_20 = 0x20;
    sp38.field_38 = 3;
    temp_v0 = func_1513B5E0((s8 *)&sp38, 1, 0x14, 0xFF, 1);
    var_a3 = temp_v0;
    if (temp_v0 != 0) {
        if (*(s32 *)((u8 *)temp_v0 + 0x50) != 0x1180) {
            sp74 = temp_v0;
            func_1516972C(temp_v0);
        } else {
            sp74 = var_a3;
            func_10022EC0((u8 *)var_a3 + *(s32 *)((u8 *)var_a3 + 0x50) + 0xF8,
                          &sp24, 0x14U);
        }
        var_a3 = sp74;
    }
    return var_a3;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513BAE8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513BAE8.s")
typedef struct { f32 x, y, z; } Game168A90Point;
typedef struct { s32 first, count; } Game168A90Range;
typedef struct { s16 x, y, z, flag, u, v; u8 color[4]; } Game168A90Vertex;
extern Game168A90Point D_800A49C0[9];
extern Game168A90Range D_800A4A2C[9];
extern f32 D_800A4A74, D_800A4A78, D_800A4A7C, D_800A4A80;
f32 func_15047D60(f32);
s32 func_15144B34(s32);
f32 sqrtf(f32);
__pragma(1, sqrtf);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513BBFC CURRENT (10188) */
s32 func_1513BBFC(Game168A90Allocated *owner, s16 arg1) {
    register Game168A90Vector5 *state;
    register Game168A90Point *position, *point;
    register Game168A90Range *range;
    register Game168A90Vertex *vertex;
    register s32 current;
    register f32 width, height, wrapX, wrapY, x, y;
    register f32 dx, dz, inverse, basisX, basisZ;
    register f32 vx, vy, vz, deltaX, deltaY, deltaZ, outU, outV;

    func_1513B968((s32)owner, (s16)arg1);
    state = (Game168A90Vector5 *)((u8 *)owner + owner->size + 0xF8);
    width = func_15047D60(state->field_0C) * D_800A4A74 + D_800A4A78;
    height = func_15047D60(state->field_10) * D_800A4A7C + D_800A4A80;
    position = (Game168A90Point *)func_15144B34(arg1);
    x = state->field_00;
    y = state->field_04;
    wrapX = x - (f32)(s32)(x * 0.0009765625f) * 1024.0f;
    wrapY = y - (f32)(s32)(y * 0.0009765625f) * 1024.0f;
    point = D_800A49C0;
    range = D_800A4A2C;
    do {
        dx = point->x - position->x;
        dz = point->z - position->z;
        if (dx != 0.0f || dz != 0.0f) {
            inverse = 1.0f / sqrtf(dx * dx + dz * dz);
            basisX = dz * inverse;
            basisZ = -dx * inverse;
        } else {
            basisX = 1.0f;
            basisZ = 0.0f;
        }
        current = range->first;
        if (current < range->first + range->count) {
            do {
                vertex = *(Game168A90Vertex **)((u8 *)owner + D_800BE9C0 * 16 + arg1 * 4 + 0x58) + current;
                vx = (f32)vertex->x;
                vz = (f32)vertex->z;
                vy = (f32)vertex->y;
                deltaX = vx - point->x;
                deltaZ = vz - point->z;
                deltaY = vy - point->y;
                outU = (deltaX * basisX + deltaZ * basisZ) * width - wrapX;
                outV = deltaY * height - wrapY;
                vertex->u = (s32)outU;
                vertex->v = (s32)outV;
                current++;
            } while (current < range->first + range->count);
        }
        range++;
        point++;
    } while (range != (Game168A90Range *)&D_800A4A74);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513BBFC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513BBFC.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800A4A84;
extern f32 D_800A4A88;
extern f32 D_800A4A8C;
extern f32 D_800A4A90;
extern f32 D_800A4A94;
extern f32 D_800BE9A4;

s32 func_1513BEB0(u8 *arg0) {
    f32 temp_fv0;
    u8 *temp_s0;

    temp_s0 = arg0;
    temp_s0 += *(s32 *)((u8 *)arg0 + 0x50);
    temp_s0 += 0xF8;
    *(f32 *)((u8 *)temp_s0 + 8) = (f32) (*(f32 *)(temp_s0 + 8) + (D_800A4A84 * D_800BE9A4));
    temp_fv0 = func_15144B68(*(f32 *)((u8 *)temp_s0 + 8));
    *(f32 *)((u8 *)temp_s0 + 8) = temp_fv0;
    *(f32 *)((u8 *)temp_s0 + 0) = (f32) (*(f32 *)((u8 *)temp_s0 + 0) + (D_800A4A88 * D_800BE9A4));
    *(f32 *)((u8 *)temp_s0 + 4) = (f32) (func_15047D60(temp_fv0) * D_800A4A8C);
    *(f32 *)((u8 *)temp_s0 + 0xC) = (f32) (*(f32 *)((u8 *)temp_s0 + 0xC) + (D_800A4A90 * D_800BE9A4));
    *(f32 *)((u8 *)temp_s0 + 0x10) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x10) + (D_800A4A94 * D_800BE9A4));
    *(f32 *)((u8 *)temp_s0 + 0xC) = func_15144B68(*(f32 *)((u8 *)temp_s0 + 0xC));
    *(f32 *)((u8 *)temp_s0 + 0x10) = func_15144B68(*(f32 *)((u8 *)temp_s0 + 0x10));
    if (*(f32 *)((u8 *)temp_s0 + 0) > 4096.0f) {
        do {
            *(f32 *)((u8 *)temp_s0 + 0) = (f32) (*(f32 *)((u8 *)temp_s0 + 0) - 4096.0f);
        } while (*(f32 *)((u8 *)temp_s0 + 0) > 4096.0f);
    }
    if (*(f32 *)((u8 *)temp_s0 + 0) < 0.0f) {
        do {
            *(f32 *)((u8 *)temp_s0 + 0) = (f32) (*(f32 *)((u8 *)temp_s0 + 0) + 4096.0f);
        } while (*(f32 *)((u8 *)temp_s0 + 0) < 0.0f);
    }
    if (*(f32 *)((u8 *)temp_s0 + 4) > 4096.0f) {
        do {
            *(f32 *)((u8 *)temp_s0 + 4) = (f32) (*(f32 *)((u8 *)temp_s0 + 4) - 4096.0f);
        } while (*(f32 *)((u8 *)temp_s0 + 4) > 4096.0f);
    }
    if (*(f32 *)((u8 *)temp_s0 + 4) < 0.0f) {
        do {
            *(f32 *)((u8 *)temp_s0 + 4) = (f32) (*(f32 *)((u8 *)temp_s0 + 4) + 4096.0f);
        } while (*(f32 *)((u8 *)temp_s0 + 4) < 0.0f);
    }
    return 1;
}
