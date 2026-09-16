#include "types.h"

/*
 * Reviewed source unit: src/game/game_FD1D0.c
 * Boundary evidence: docs/evidence/game_raw_text_view_descriptor_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150CFD20
 * - func_150CFD5C
 * - func_150CFDB8
 * - func_150CFE3C
 * - func_150CFE98
 * - func_150CFF10
 * - func_150D0034
 * - func_150D01A0
 * - func_150D02B4
 * - func_150D032C
 * - func_150D04C4
 * - func_150D0534
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CFD20 CURRENT (155) */
u8 *func_150CFD20(u8 *arg0) {
    u8 *var_a0;
    u8 temp_v0;
    u8 temp_v0_2;

    var_a0 = arg0;
    temp_v0 = *var_a0;
    if ((temp_v0 != 0xBD) && (temp_v0 != 0)) {
loop_2:
        temp_v0_2 = *(u8 *)((u8 *)var_a0 + 1);
        var_a0 += 1;
        if (temp_v0_2 != 0xBD) {
            if (temp_v0_2 != 0) {
                goto loop_2;
            }
        }
    }
    return var_a0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CFD20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150CFD20.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CFD5C CURRENT (145) */
u8 *func_150CFD5C(u8 *arg0) {
    u8 *var_a0;
    u8 temp_t7;

    var_a0 = arg0;
    if (*var_a0 != 0) {
        do {
            temp_t7 = *(u8 *)((u8 *)var_a0 + 1);
            var_a0 += 1;
        } while (temp_t7 != 0);
    }
    return var_a0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CFD5C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150CFD5C.s")
s32 func_150CFD84(s32 arg0, s32 *arg1) {
    s32 temp_v0;

    temp_v0 = func_150CFD20(arg0);
    *arg1 = temp_v0;
    return temp_v0 - arg0;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CFDB8 CURRENT (1359) */
s32 func_150CFDB8(u8 *arg0) {
    s32 temp_v0_3;
    s32 var_s0;
    u32 temp_v0;
    s32 sp2C;
    u8 *temp_v0_2;
    u8 *var_a0;

    var_s0 = 0;
    temp_v0 = func_150CFD5C(arg0);
    var_a0 = arg0;
    if ((u32) var_a0 < temp_v0) {
        do {
            temp_v0_3 = func_150CFD84((s32) var_a0, &sp2C);
            if (var_s0 < temp_v0_3) {
                var_s0 = temp_v0_3;
            }
            temp_v0_2 = sp2C + 1;
            var_a0 = temp_v0_2;
        } while ((u32) temp_v0_2 < temp_v0);
    }
    return var_s0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CFDB8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150CFDB8.s")
void func_10022EC0(void *, void *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CFE3C CURRENT (140) */
void func_150CFE3C(void *arg0) {
    s32 temp_v0;

    func_10022EC0(*(void **)((u8 *)arg0 + (*(u8 *)((u8 *)arg0 + 0x3D) * 4) + 0x40),
                   *(void **)((u8 *)arg0 + 0x34), *(u8 *)((u8 *)arg0 + 0x3C), arg0);
    temp_v0 = (s32)arg0 + 0x28;
    *(*(u8 **)(temp_v0 + (*(u8 *)(temp_v0 + 0x15) * 4) + 0x18) + *(u8 *)(temp_v0 + 0x14)) = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CFE3C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150CFE3C.s")
typedef struct GameFD1D0TextCursor {
    u8 field_0;
    u8 pad1[7];
    u8 flags;
    u8 pad9[3];
    u8 *field_C;
    u8 *cursor;
    u8 width;
    u8 page;
} GameFD1D0TextCursor;

typedef struct GameFD1D0State {
    u8 pad0[0xE];
    s16 field_0E;
    u8 pad10[0x18];
    GameFD1D0TextCursor text;
    u8 pad40[0xC];
    s8 field_4C;
    u8 field_4D;
} GameFD1D0State;

void func_150CFE3C(GameFD1D0State *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CFE98 CURRENT (10) */
void func_150CFE98(GameFD1D0State *arg0) {
    GameFD1D0TextCursor *text;

    text = &arg0->text;
    if (*text->cursor != 0) {
        text->field_C = text->cursor + 1;
        text->width = func_150CFD84((s32)text->field_C, (s32 *)&text->cursor);
        text->page ^= 1;
        func_150CFE3C(arg0);
        text->flags |= 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CFE98 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150CFE98.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150CFF10.s")
typedef s32 (*GameFD1D0EntryCallback)(GameFD1D0State *);

extern GameFD1D0EntryCallback D_800888A0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D0034 CURRENT (1255) */
s32 func_150D0034(s32 arg0, GameFD1D0State *arg1, s32 arg2) {
    GameFD1D0TextCursor *text;

    if ((arg1->field_4C != -1) && (D_800888A0[arg1->field_4C](arg1) == 0)) {
        arg1->field_0E = -1;
        return arg0;
    }
    text = &arg1->text;
    text->flags = (u8) ((u16) text->flags & 0xFFFE);
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D0034 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150D0034.s")

typedef void (*GameFD1D0Callback)(GameFD1D0State *);

void func_150CFE98(GameFD1D0State *);
extern GameFD1D0Callback D_800888B0[];

void func_150D00C0(GameFD1D0State *arg0, u8 *arg1, u8 arg2) {
    GameFD1D0Callback callback;

    if (arg2 == 0x51) {
        if (*arg1 == arg0->text.field_0) {
            func_150CFE98(arg0);
        }
    } else {
        callback = D_800888B0[arg0->field_4D];
        if (callback != 0) {
            callback(arg0);
        }
    }
}

typedef struct GameFD1D0Object {
    u8 pad0[0x48];
    void *field_48;
} GameFD1D0Object;

typedef struct GameFD1D0ByteSlot {
    u8 pad0[8];
    u8 value;
} GameFD1D0ByteSlot;

typedef struct GameFD1D0SmallByteSlot {
    u8 pad0[4];
    u8 value;
    u8 pad5[4];
} GameFD1D0SmallByteSlot;

GameFD1D0Object *func_150CFF10(u8, u8 *, s16, s32, s8, u8, u8, s32);

void func_150D0134(u8 arg0, u8 *arg1, s16 arg2, u8 arg3, s32 arg4) {
    GameFD1D0Object *object;
    GameFD1D0ByteSlot slot;

    slot.value = 0;
    object = func_150CFF10(arg0, arg1, arg2, 8, 0, 0, arg3, arg4);
    if (object != 0) {
        func_10022EC0(object->field_48, &slot.value, 1);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150D01A0.s")
typedef struct {
    f32 value;
    s16 field_4;
    u8 pad6[2];
} GameFD1D0ValuePacket;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D02B4 CURRENT (100) */
void func_150D02B4(u8 arg0, u8 *arg1, s16 arg2, u8 arg3, s32 arg4) {
    GameFD1D0Object *object;
    GameFD1D0ValuePacket packet;

    packet.field_4 = 0;
    packet.value = 0.0f;
    object = func_150CFF10(arg0, arg1, arg2, 8, 1, 0, arg3, arg4);
    if (object != 0) {
        func_10022EC0(object->field_48, &packet, sizeof(packet));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D02B4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150D02B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150D032C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D04C4 CURRENT (100) */
void func_150D04C4(u8 arg0, u8 *arg1, s16 arg2, u8 arg3, s32 arg4) {
    GameFD1D0SmallByteSlot slot;
    GameFD1D0Object *object;

    slot.value = 0;
    object = func_150CFF10(arg0, arg1, arg2, 8, 2, 0, arg3, arg4);
    if (object != 0) {
        func_10022EC0(object->field_48, &slot.value, 1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D04C4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150D04C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150D0534.s")
