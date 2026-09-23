#include "types.h"

/*
 * Reviewed source unit: src/game/game_1897A0.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1515C388
 * - func_1515C534
 * - func_1515C6F4
 * - func_1515CF9C
 * - func_1515D088
 * - func_1515D130
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_10022EC0(void *, void *, s32);
void *func_15147A80(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void *func_1515C2F0(void *arg0, void *arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    void *temp_v0;
    void *sp3C;

    *(s32 *)((u8 *)arg0 + 0x10) = 0xA;
    temp_v0 = func_15147A80(arg0, (u8 *)arg1 + 0x40, 0x10, 8, 8, 8, 0, 0,
                            arg3, arg4, arg5);
    if (temp_v0 == 0) {
        return 0;
    }
    sp3C = temp_v0;
    func_10022EC0(*(void **)((u8 *)temp_v0 + 0x98), (void *)arg2, 0x3C);
    return sp3C;
}
extern f32 D_800BE9A4;
typedef s32 (*Game1897A0UpdateCallback)(void *);
extern Game1897A0UpdateCallback D_8008B080[];

typedef struct Game1897A0Position {
    s32 values[3];
} Game1897A0Position;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515C388 CURRENT (2434) */
s32 func_1515C388(void *arg0) {
    u8 *actor = arg0;
    u8 *settings = *(u8 **)(actor + 0x98);
    u8 *points = *(u8 **)(actor + 0x94);
    Game1897A0Position initial;
    Game1897A0Position *position;
    f32 *point;
    f32 old_velocity;
    s32 callback_failed = 0;
    s32 index;
    s32 callback_index;
    s32 result = 1;

    if (*(s8 *)(actor + 0x2C) != 0) {
        position = (Game1897A0Position *)(points + (*(s8 *)(actor + 0x2D) * 0x10));
        initial.values[0] = position->values[0];
        initial.values[1] = position->values[1];
        initial.values[2] = position->values[2];
        index = *(s8 *)(actor + 0x2D);
        if (index != *(s8 *)(actor + 0x2E)) {
            do {
                point = (f32 *)(points + (index * 0x10));
                old_velocity = point[3];
                index += 1;
                point[0] += *(f32 *)(settings + 4) * D_800BE9A4;
                point[1] += old_velocity * D_800BE9A4 +
                            (*(f32 *)(settings + 0x10) * D_800BE9A4 * D_800BE9A4 * 0.5f);
                point[2] += *(f32 *)(settings + 0xC) * D_800BE9A4;
                point[3] = *(f32 *)(settings + 0x10) * D_800BE9A4 + old_velocity;
                if (index == *(u8 *)(actor + 0x25)) {
                    index = 0;
                }
            } while (index != *(s8 *)(actor + 0x2E));
        }
    }

    callback_index = *(s8 *)(settings + 0x38);
    if (callback_index != -1) {
        callback_failed = (D_8008B080[callback_index](actor) == 0);
    }
    if (*(s8 *)(actor + 0x2C) > 0) {
        position = (Game1897A0Position *)(points + (*(s8 *)(actor + 0x2D) * 0x10));
        *(Game1897A0Position *)(actor + 0x54) = *position;
    } else {
        *(f32 *)(actor + 0x54) = 0.0f;
        *(f32 *)(actor + 0x58) = 0.0f;
        *(f32 *)(actor + 0x5C) = 0.0f;
    }
    if (callback_failed != 0) {
        result = 0;
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515C388 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/func_1515C388.s")
extern s32 D_800BE9E4;
typedef s32 (*Game1897A0ActionCallback)(void *, void *, void *, s32);
extern Game1897A0ActionCallback D_8008B084[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515C534 CURRENT (179) */
s32 func_1515C534(void *arg0) {
    struct Actor {
        u8 pad00[0x1C];
        s16 time;
        u8 pad1E[0x7A];
        void *settings;
    } *actor = arg0;
    struct Settings {
        f32 value;
        u8 pad04[0x10];
        u8 flags;
        u8 pad15[5];
        u8 intensity;
        u8 pad1B[0x11];
        s16 start;
        s16 slope;
        s16 end;
        u8 paused;
        u8 pad33;
        f32 attenuation;
        u8 pad38;
        s8 callbackIndex;
    } *settings;
    s32 callbackFailed;
    s32 newValue;
    s32 count;

    settings = actor->settings;
    callbackFailed = 0;
    if (settings->callbackIndex != -1) {
        callbackFailed = (D_8008B084[settings->callbackIndex](arg0, settings, arg0, 0) == 0) & 0xFF;
    }
    if (callbackFailed == 0) {
        if (settings->flags & 4) {
            if (actor->time < settings->start) {
                newValue = actor->time * settings->slope;
                if (newValue < settings->intensity) {
                    settings->intensity = newValue;
                }
            }
        }
        if ((settings->flags & 8) && actor->time < settings->end && settings->paused == 0) {
            count = D_800BE9E4;
            if (count != 0) {
                do {
                    settings->value *= settings->attenuation;
                    count--;
                } while (count != 0);
            }
        }
    }
    if (callbackFailed != 0) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515C534 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/func_1515C534.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/func_1515C6F4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515CF9C CURRENT (370) */
s32 func_1515CF9C(void *arg0, void *arg1) {
    s8 temp_v0;
    s32 *temp_v1;
    s32 *temp_t1;

    temp_v0 = *(s8 *)((u8 *)arg0 + 0x2C);
    if (temp_v0 < (*(u8 *)((u8 *)arg0 + 0x25) - 1)) {
        temp_v1 = *(s32 **)((u8 *)arg0 + 0x94);
        temp_t1 = (s32 *)((u8 *)temp_v1 + (*(s8 *)((u8 *)arg0 + 0x2E) * 0x10));
        *(s8 *)((u8 *)arg0 + 0x2C) = (s8)(temp_v0 + 1);
        temp_t1[0] = *(s32 *)((u8 *)arg0 + 0x10);
        temp_t1[1] = *(s32 *)((u8 *)arg0 + 0x14);
        temp_t1[2] = *(s32 *)((u8 *)arg0 + 0x18);
        *(f32 *)((u8 *)temp_v1 + (*(s8 *)((u8 *)arg0 + 0x2E) * 0x10) + 0xC) = *(f32 *)((u8 *)arg1 + 8);
        *(s8 *)((u8 *)arg0 + 0x2E) = (s8)(*(s8 *)((u8 *)arg0 + 0x2E) + 1);
        if (*(u8 *)((u8 *)arg0 + 0x25) == *(s8 *)((u8 *)arg0 + 0x2E)) {
            *(s8 *)((u8 *)arg0 + 0x2E) = 0;
        }
    } else {
        *(s8 *)((u8 *)arg1 + 0x39) = -1;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515CF9C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/func_1515CF9C.s")
s32 func_1515D030(void *arg0, s32 arg1) {
    s32 var_v1;
    s8 temp_v0;

    temp_v0 = *(s8 *)((u8 *)arg0 + 0x2C);
    var_v1 = 1;
    if (temp_v0 >= 3) {
        *(s8 *)((u8 *)arg0 + 0x2C) = (s8) (temp_v0 - 1);
        *(s8 *)((u8 *)arg0 + 0x2E) = (s8) (*(s8 *)((u8 *)arg0 + 0x2E) - 1);
        if (*(s8 *)((u8 *)arg0 + 0x2E) < 0) {
            *(s8 *)((u8 *)arg0 + 0x2E) = (s8) (*(u8 *)((u8 *)arg0 + 0x25) - 1);
        }
    } else {
        var_v1 = 0;
    }
    return var_v1;
}
extern s32 func_151491F4(s32, s32, s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515D088 CURRENT (650) */
s32 func_1515D088(void *arg0) {
    s32 sp3C;
    s8 sp38;
    f32 sp34;
    void *sp30;
    s32 temp_t7;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_v1;

    temp_t7 = *(s32 *)((u8 *)arg0 + 0x18);
    temp_v0 = temp_t7 & 0xFF;
    sp38 = (s8)temp_t7;
    if ((temp_v0 < 0) || (temp_v0 >= 2)) {
        return 0;
    }
    sp30 = arg0;
    sp34 = 0.0f;
    temp_v0_2 = func_151491F4(0x12C, -1, 0x11, 0, 0xD, 0xC, 0xFF, 1);
    var_v1 = temp_v0_2;
    if (temp_v0_2 != 0) {
        sp3C = temp_v0_2;
        func_10022EC0((u8 *)temp_v0_2 + 0x28, &sp30, 0xC);
        var_v1 = sp3C;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515D088 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/func_1515D088.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/func_1515D130.s")
