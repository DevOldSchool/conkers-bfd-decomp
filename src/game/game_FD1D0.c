#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_FD1D0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_text_view_descriptor_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D01A0
 * - func_150D0534
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

u8 *func_150CFD20(u8 *arg0) {
    while (*arg0 != 0xBD && *arg0 != 0) {
        arg0++;
    }
    return arg0;
}
u8 *func_150CFD5C(u8 *arg0) {
    if (*arg0 != 0) {
        do {
            arg0 += 1;
        } while (*arg0 != 0);
    }
    return arg0;
}
s32 func_150CFD84(s32 arg0, s32 *arg1) {
    s32 temp_v0;

    temp_v0 = (s32)func_150CFD20((u8 *)arg0);
    *arg1 = temp_v0;
    return temp_v0 - arg0;
}
s32 func_150CFDB8(u8 *arg0) {
    s32 max;
    u8 *end;
    s32 next;

    max = 0;
    end = func_150CFD5C(arg0);
    while (arg0 < end) {
        s32 value = func_150CFD84((s32)arg0, &next);

        if (max < value) {
            max = value;
        }
        arg0 = (u8 *)next + 1;
    }
    return max;
}
void *func_10022EC0(void *, const void *, u32);

struct GameFD1D0State;

void func_150CFE3C(struct GameFD1D0State *arg0) {
    struct Text {
        u8 pad0[0xC];
        void *source;
        u8 pad10[4];
        u8 width;
        u8 page;
        u8 pad16[2];
        u8 *buffers[2];
    } *text = (struct Text *)((u8 *)arg0 + 0x28);

    func_10022EC0(text->buffers[text->page], text->source, text->width);
    text->buffers[text->page][text->width] = 0;
}
typedef struct GameFD1D0TextCursor {
    u8 field_0;
    u8 pad1[7];
    u8 flags;
    u8 pad9[3];
    s32 field_C;
    u8 *cursor;
    u8 width;
    u8 page;
    u8 pad16[2];
    u8 *buffers[2];
    void *state;
    s8 handler;
    u8 mode;
    u8 pad26[2];
} GameFD1D0TextCursor;

typedef struct GameFD1D0State {
    u8 pad0[0xE];
    s16 field_0E;
    u8 pad10[0x18];
    GameFD1D0TextCursor text;
} GameFD1D0State;

void func_150CFE3C(GameFD1D0State *);

void func_150CFE98(GameFD1D0State *arg0) {
    GameFD1D0TextCursor *text;

    text = &arg0->text;
    if (*text->cursor != 0) {
        text->field_C = (s32)(text->cursor + 1);
        text->width = func_150CFD84(text->field_C, (s32 *)&text->cursor);
        text->page ^= 1;
        func_150CFE3C(arg0);
        text->flags |= 1;
    }
}
s32 func_150CFDB8(u8 *);
struct GameFD1D0Object;

typedef struct {
    u8 field_0;
    u8 pad_1[3];
    u8 *field_4;
    u8 field_8;
    u8 pad_9[3];
    u8 *field_C;
    s32 field_10;
    u8 field_14;
    u8 field_15;
    u8 pad_16[2];
    s32 field_18;
    s32 field_1C;
    s32 field_20;
    s8 field_24;
    u8 field_25;
    u8 pad_26[2];
} GameFD1D0Packet;

struct GameFD1D0Object *func_150CFF10(u8 arg0, u8 *arg1, s16 arg2, s32 arg3,
                                      s8 arg4, u8 arg5, u8 arg6, s32 arg7) {
    GameFD1D0Packet packet;
    GameFD1D0State *obj;
    s32 len1;
    GameFD1D0TextCursor *text;

    packet.field_25 = arg5;
    packet.field_24 = arg4;
    packet.field_15 = 0;
    packet.field_8 = 1;
    packet.field_4 = arg1;
    packet.field_C = arg1;
    packet.field_0 = arg0;
    packet.field_14 = func_150CFD84((s32)arg1, &packet.field_10);
    packet.field_18 = 0;
    packet.field_1C = 0;
    packet.field_20 = 0;
    len1 = func_150CFDB8(arg1) + 1;
    obj = func_15149130(arg2, -1, -1, 5, 3, 0x47, arg3 + 0x28 + len1 * 2, arg6, arg7);
    if (obj != NULL) {
        text = &obj->text;
        func_10022EC0(text, &packet, 0x28);
        *(u8 **)(((u8 *)text) + 0x20) = ((u8 *)text) + 0x28;
        *(u8 **)(((u8 *)text) + 0x18) = *(u8 **)(((u8 *)text) + 0x20) + arg3;
        *(u8 **)(((u8 *)text) + 0x1C) = *(u8 **)(((u8 *)text) + 0x18) + len1;
        **(u8 **)(((u8 *)text) + 0x18) = 0;
        **(u8 **)(((u8 *)text) + 0x1C) = 0;
        func_150CFE3C(obj);
    }
    return (struct GameFD1D0Object *)obj;
}
typedef s32 (*GameFD1D0EntryCallback)(GameFD1D0State *);

extern GameFD1D0EntryCallback D_800888A0[];

s32 func_150D0034(s32 arg0, GameFD1D0State *arg1, s32 arg2) {
    GameFD1D0TextCursor *text = &arg1->text;

    if ((text->handler != -1) && (D_800888A0[text->handler](arg1) == 0)) {
        arg1->field_0E = -1;
        return arg0;
    }
    text->flags &= ~1;
    return arg0;
}

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
        callback = D_800888B0[arg0->text.mode];
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
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D01A0 CURRENT (2569) */
s32 func_150D01A0(u8 *volatile arg0) {
    u8 *sp20;
    s32 temp_t0;
    register s32 var_s0;
    s8 *temp_v0;
    s8 temp_v1;
    u8 var_a3;
    u8 *temp_v0_2;

    var_a3 = 0xFF;
    var_s0 = 0;
    temp_v0_2 = arg0;
    temp_v0 = *(s8 **)(temp_v0_2 + 0x48);
    if (temp_v0_2[0x30] & 1) {
        *temp_v0 = 8;
    }
    temp_v1 = *temp_v0;
    if (temp_v1 > 0) {
        temp_t0 = (temp_v1 * 0x1F) & 0xFF;
        var_s0 = temp_t0;
        var_a3 = (0xFF - temp_t0) & 0xFF;
        *temp_v0 = (s8)((u32)(s32)temp_v1 - (u32)D_800BE9E4);
    }
    if (var_a3 != 0) {
        func_1504332C(0xCE, 0xC4, 0x61, var_a3);
        temp_v0_2 = arg0;
        temp_t0 = temp_v0_2[0x3D];
        temp_v0_2 += 0x28;
        func_15042D94(0x92, 0xBE, 0x81,
                      *(s32 *)(temp_v0_2 + (temp_t0 * 4) + 0x18));
    }
    if (var_s0 != 0) {
        temp_v0_2 = arg0 + 0x28;
        sp20 = temp_v0_2;
        func_1504332C(0xCE, 0xC4, 0x61, var_s0 & 0xFF);
        temp_v0_2 = sp20;
        func_15042D94(0x92, 0xBE, 0x81,
                      *(s32 *)(temp_v0_2 +
                               ((temp_v0_2[0x15] ^ 1) * 4) + 0x18));
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D01A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150D01A0.s")
typedef struct {
    f32 value;
    s16 field_4;
    u8 pad6[2];
} GameFD1D0ValuePacket;

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
extern f32 D_800BE9A4;

s32 func_150D032C(GameFD1D0State *arg0) {
    GameFD1D0TextCursor *view;
    GameFD1D0ValuePacket *state;
    u8 text[0x50];
    u8 prompt[] = "C:> ";

    view = &arg0->text;
    state = view->state;
    if (view->flags & 1) {
        state->field_4 = 0;
        state->value = 0.0f;
    }
    if (state->value < view->width) {
        state->value += 0.437f * D_800BE9A4;
        while (state->value > 1.0f) {
            state->field_4++;
            if (view->width < state->field_4) {
                state->field_4 = view->width;
            }
            state->value -= 1.0f;
        }
    }
    func_10022EC0(text, prompt, 4);
    func_10022EC0(text + 4, view->buffers[view->page], state->field_4);
    text[4 + state->field_4] = 0x20;
    text[5 + state->field_4] = 0xBB;
    text[6 + state->field_4] = 0;
    func_1504332C(0, 0xFF, 0, 0x96);
    func_15042D94(0xF, 0xBE, 0x80, (s32)text);
    return 1;
}
void func_150D04C4(u8 arg0, u8 *arg1, s16 arg2, u8 arg3, s32 arg4) {
    GameFD1D0SmallByteSlot slot;
    GameFD1D0Object *object;

    slot.value = 0;
    object = func_150CFF10(arg0, arg1, arg2, 8, 2, 0, arg3, arg4);
    if (object != 0) {
        func_10022EC0(object->field_48, &slot.value, 1);
    }
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D0534 CURRENT (3529) */
s32 func_150D0534(u8 * volatile arg0) {
    u8 *sp20;
    s32 temp_t0;
    register s32 var_s0;
    s8 *temp_v0;
    s8 temp_v1;
    u8 var_a3;
    u8 *temp_v0_2;

    var_a3 = 0xFF;
    var_s0 = 0;
    temp_v0 = *(s8 **)(arg0 + 0x48);
    if (arg0[0x30] & 1) {
        *temp_v0 = 0x14;
    }
    temp_v1 = *temp_v0;
    if (temp_v1 > 0) {
        temp_t0 = (temp_v1 * 0xC) & 0xFF;
        var_s0 = temp_t0;
        var_a3 = (0xFF - temp_t0) & 0xFF;
        *temp_v0 = temp_v1 - D_800BE9E4;
    }
    if (var_a3 != 0) {
        func_1504332C(0xFF, 0xFF, 0xFF, var_a3);
        func_15042D94(0x14, 0x14, 0x80,
                      *(s32 *)(arg0 + 0x28 + (arg0[0x3D] * 4) + 0x18));
    }
    if (var_s0 != 0) {
        temp_v0_2 = arg0 + 0x28;
        sp20 = temp_v0_2;
        func_1504332C(0xFF, 0xFF, 0xFF, var_s0 & 0xFF);
        temp_v0_2 = sp20;
        func_15042D94(0x14, 0x14, 0x80,
                      *(s32 *)(temp_v0_2 +
                               ((temp_v0_2[0x15] ^ 1) * 4) + 0x18));
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D0534 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150D0534.s")
