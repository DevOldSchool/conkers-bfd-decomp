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
 * - func_150D032C
 * - func_150D0534
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CFD20 CURRENT (15) */
u8 *func_150CFD20(u8 *arg0) {
    u8 temp_v0;
    u8 temp_v0_2;

    temp_v0 = *arg0;
    if ((temp_v0 != 0xBD) && (temp_v0 != 0)) {
loop_2:
        temp_v0_2 = arg0[1];
        arg0 += 1;
        if (temp_v0_2 != 0xBD) {
            if (temp_v0_2 != 0) {
                goto loop_2;
            }
        }
    }
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CFD20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150CFD20.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CFD5C CURRENT (15) */
u8 *func_150CFD5C(u8 *arg0) {
    u8 temp_t7;

    if (*arg0 != 0) {
        do {
            temp_t7 = arg0[1];
            arg0 += 1;
        } while (temp_t7 != 0);
    }
    return arg0;
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
s32 func_150CFDB8(u8 *);
GameFD1D0State *func_15149130(s16, s32, s32, s32, s32, s32, s32, s32, s32);
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CFF10 CURRENT (1032) */
struct GameFD1D0Object *func_150CFF10(u8 arg0, u8 *arg1, s16 arg2, s32 arg3,
                                      s8 arg4, u8 arg5, u8 arg6, s32 arg7) {
    GameFD1D0Packet packet;
    GameFD1D0State *temp_v0_2;
    GameFD1D0TextCursor *temp_a3;
    s32 temp_v0;
    s32 temp_v0_3;
    s8 *temp_v1;
    void *temp_a1;

    packet.field_15 = 0;
    packet.field_8 = 1;
    packet.field_4 = arg1;
    packet.field_C = arg1;
    packet.field_25 = arg5;
    packet.field_24 = arg4;
    packet.field_0 = arg0;
    packet.field_14 = func_150CFD84((s32)arg1, &packet.field_10);
    packet.field_18 = 0;
    packet.field_1C = 0;
    packet.field_20 = 0;
    temp_v0 = func_150CFDB8(arg1);
    temp_v0_3 = temp_v0 + 1;
    temp_v0_2 = func_15149130(arg2, -1, -1, 5, 3, 0x47,
                              arg3 + (temp_v0 * 2) + 0x2A,
                              (s32)arg6, arg7);
    if (temp_v0_2 != 0) {
        temp_a3 = &temp_v0_2->text;
        func_10022EC0(temp_a3, &packet, 0x28);
        temp_a1 = (u8 *)temp_a3 + 0x28;
        *(void **)((u8 *)temp_a3 + 0x20) = temp_a1;
        temp_v1 = (s8 *)temp_a1 + arg3;
        *(s8 **)((u8 *)temp_a3 + 0x18) = temp_v1;
        *(s8 **)((u8 *)temp_a3 + 0x1C) = temp_v1 + temp_v0_3;
        *temp_v1 = 0;
        **(s8 **)((u8 *)temp_a3 + 0x1C) = 0;
        func_150CFE3C(temp_v0_2);
    }
    return (struct GameFD1D0Object *)temp_v0_2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CFF10 */
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
void func_1504332C(u8, u8, u8, u8);
void func_15042D94(s32, s32, u8, s32);
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D01A0 CURRENT (4271) */
s32 func_150D01A0(u8 *arg0) {
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
        *temp_v0 = 8;
    }
    temp_v1 = *temp_v0;
    if (temp_v1 > 0) {
        temp_t0 = (temp_v1 * 0x1F) & 0xFF;
        var_s0 = temp_t0;
        var_a3 = (0xFF - temp_t0) & 0xFF;
        *temp_v0 = temp_v1 - D_800BE9E4;
    }
    if (var_a3 != 0) {
        func_1504332C(0xCE, 0xC4, 0x61, var_a3);
        func_15042D94(0x92, 0xBE, 0x81,
                      *(s32 *)(arg0 + 0x28 + (arg0[0x3D] * 4) + 0x18));
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
extern u8 D_800A0880[];
extern f32 D_800A0888;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D032C CURRENT (1898) */
s32 func_150D032C(u8 *arg0) {
    u8 text[0x48];
    u8 initial[8];
    u8 *state;
    u8 *view;
    f32 value;

    *(u32 *)initial = *(u32 *)D_800A0880;
    initial[4] = D_800A0880[4];
    view = arg0 + 0x28;
    state = *(u8 **)(arg0 + 0x48);
    if (arg0[0x30] & 1) {
        *(s16 *)(state + 4) = 0;
        *(f32 *)state = 0.0f;
    }
    value = (f32)view[0x14];
    if (*(f32 *)state < value) {
        *(f32 *)state += D_800A0888 * D_800BE9A4;
        if (*(f32 *)state > 1.0f) {
            do {
                *(s16 *)(state + 4) = *(s16 *)(state + 4) + 1;
                if (view[0x14] < *(s16 *)(state + 4)) {
                    *(s16 *)(state + 4) = view[0x14];
                }
                *(f32 *)state -= 1.0f;
            } while (*(f32 *)state > 1.0f);
        }
    }
    func_10022EC0(text, initial, 4);
    func_10022EC0(text + 4, *(void **)(view + (view[0x15] * 4) + 0x18),
                  *(s16 *)(state + 4));
    text[4 + *(s16 *)(state + 4)] = 0x20;
    text[5 + *(s16 *)(state + 4)] = 0xBB;
    text[6 + *(s16 *)(state + 4)] = 0;
    func_1504332C(0, 0xFF, 0, 0x96);
    func_15042D94(0xF, 0xBE, 0x80, (s32)text);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D032C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FD1D0/func_150D032C.s")
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
