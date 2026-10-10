#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1765E0.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_remaining_upstream_c_groups.md
 */

typedef struct Game1765E0EffectHeader {
    u8 pad_0[0xD];
    u8 flags;
    s16 timer;
    s8 callback_expired;
    s8 callback_tick;
    s8 drawCallbackIndex;
    u8 callbackSetIndex;
    u8 data[0x10];
} Game1765E0EffectHeader;

Game1765E0EffectHeader *func_15167A68();
void func_100226F0(void *, s32);

/*
 * Descriptive role: timer_callback_object_create.
 * Allocates 0x28 base bytes plus extraBytes, selects kind 0x23/0x5F from
 * flag bit 1, initializes the signed timer and callback selectors, and
 * clears only bytes +0x14..+0x23. Both kinds share the timer/draw dispatch.
 * arg7 and arg8 retain their unresolved forwarding roles.
 */
void *func_15149130(s16 initialTimer, s8 expiryCallbackIndex, s8 tickCallbackIndex, s8 drawCallbackIndex,
                     u8 flags, u8 callbackSetIndex, s32 extraBytes, u8 arg7, s32 arg8) {
    Game1765E0EffectHeader *object;
    u8 objectKind;
    s32 size;

    size = extraBytes + 0x28;
    objectKind = (flags & 2) ? 0x5F : 0x23;
    object = func_15167A68(objectKind, arg8, size, 1, arg7, 1);
    if (object == 0) {
        return 0;
    }
    object->timer = initialTimer;
    object->callback_expired = expiryCallbackIndex;
    object->callback_tick = tickCallbackIndex;
    object->drawCallbackIndex = drawCallbackIndex;
    object->flags = flags;
    object->callbackSetIndex = callbackSetIndex;
    func_100226F0(object->data, 0x10);
    return object;
}

/*
 * Descriptive role: timer_callback_object_create_without_draw_callback.
 * Uses draw-callback selector -1 and returns the constructed object, which
 * callers keep. arg6 and arg7 remain unresolved forwarding arguments.
 */
void *func_151491F4(s16 initialTimer, s8 expiryCallbackIndex, s8 tickCallbackIndex, u8 flags, u8 callbackSetIndex,
                    s32 extraBytes, u8 arg6, s32 arg7) {
    return func_15149130(initialTimer, expiryCallbackIndex, tickCallbackIndex, -1, flags, callbackSetIndex, extraBytes, arg6, arg7);
}
typedef struct Game1765E0Effect {
    u8 pad_0[0xD];
    u8 flags;
    s16 timer;
    s8 callback_expired;
    s8 callback_tick;
} Game1765E0Effect;

extern s32 D_800BE9E4;
extern void (*D_8008A4C0[])(Game1765E0Effect *);
extern void (*D_8008A4E8[])(Game1765E0Effect *);

/*
 * Descriptive role: timer_callback_object_update.
 * Optionally decrements the signed timer by D_800BE9E4, then invokes the
 * selected tick callback. If negative, the timer permits the expiry callback.
 * Removal requires a negative timer even after any expiry callback and reload.
 */
void func_15149264(Game1765E0Effect *object) {
    s16 timerValue;
    s8 tickCallbackIndex;
    s8 expiryCallbackIndex;

    if (object->flags & 1) {
        object->timer = object->timer - D_800BE9E4;
    }
    tickCallbackIndex = object->callback_tick;
    if (tickCallbackIndex != -1) {
        D_8008A4E8[tickCallbackIndex](object);
    }
    timerValue = object->timer;
    if (timerValue < 0) {
        expiryCallbackIndex = object->callback_expired;
        if (expiryCallbackIndex != -1) {
            D_8008A4C0[expiryCallbackIndex](object);
            timerValue = object->timer;
        }
    }
    if (timerValue < 0) {
        func_1516972C(object);
    }
}
void func_15149318(s32 arg0) {
    func_151D5E30(arg0 + 0x14, arg0);
}
void func_15169804(s32);

void func_1514933C(s32 arg0) {
    func_15149318(arg0);
    func_15169804(arg0);
}
void func_15149318(s32 arg0);
void func_15169824(s32 arg0);

void func_15149368(s32 arg0) {
    func_15149318(arg0);
    func_15169824(arg0);
}
typedef struct {
    u8 pad_0[0x13];
    u8 callbackSetIndex;
} Game1765E0State;

extern void (*D_8008A688[])(void);

void func_15149394(Game1765E0State *arg0) {
    s32 temp_v0;

    temp_v0 = arg0->callbackSetIndex;
    if (temp_v0 < 0) {
        temp_v0 = 0;
    } else if (temp_v0 >= 0x4A) {
        temp_v0 = 0;
    }
    D_8008A688[temp_v0]();
}
extern void (*D_8008A7B0[])(void);

void func_151493E4(Game1765E0State *arg0) {
    s32 temp_v0;

    temp_v0 = arg0->callbackSetIndex;
    if (temp_v0 < 0) {
        temp_v0 = 0;
    } else if (temp_v0 >= 0x4A) {
        temp_v0 = 0;
    }
    D_8008A7B0[temp_v0]();
}
extern void (*D_8008A8D8[])(void *, void *, u8);

void func_15149434(void *arg0, void *arg1, u8 arg2) {
    s32 var_v0;

    var_v0 = *(u8 *)((u8 *)arg0 + 0x13);
    if ((var_v0 < 0) || (var_v0 >= 0x4A)) {
        var_v0 = 0;
    }
    if (D_8008A8D8[var_v0] != 0) {
        D_8008A8D8[var_v0](arg0, arg1, arg2);
    }
}
typedef struct {
    u8 pad_0[0x12];
    s8 drawCallbackIndex;
} Game1765E0DispatchState;

extern s32 (*D_8008A670[])(s32, Game1765E0DispatchState *, s16);

s32 func_15149490(s32 arg0, Game1765E0DispatchState *arg1, s16 arg2) {
    s8 temp_v0;

    temp_v0 = arg1->drawCallbackIndex;
    if (temp_v0 != -1) {
        arg0 = D_8008A670[temp_v0](arg0, arg1, arg2);
    }
    return arg0;
}
void func_15169260(void *, s32, void *, u8);
extern u8 D_800A5770;

void func_151494E0(void *arg0, u8 arg1) {
    func_15169260(&D_800A5770, 2, arg0, arg1);
}
void func_15169850(s32, u8, s32, s32, s32);

void func_15149514(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_15169850(arg0, arg1, arg2, arg3, arg4);
}
