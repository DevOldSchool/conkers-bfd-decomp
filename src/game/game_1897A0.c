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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515CF9C CURRENT (265) */
s32 func_1515CF9C(void *arg0, void *arg1) {
    typedef struct { s32 words[3]; } Copy3;
    s8 temp_v0;
    s32 *temp_v1;

    temp_v0 = *(s8 *)((u8 *)arg0 + 0x2C);
    if (temp_v0 < (*(u8 *)((u8 *)arg0 + 0x25) - 1)) {
        temp_v1 = *(s32 **)((u8 *)arg0 + 0x94);
        *(s8 *)((u8 *)arg0 + 0x2C) = (s8)(temp_v0 + 1);
        *(Copy3 *)((u8 *)temp_v1 + (*(s8 *)((u8 *)arg0 + 0x2E) * 0x10)) = *(Copy3 *)((u8 *)arg0 + 0x10);
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515D088 CURRENT (121) */
s32 func_1515D088(void *arg0) {
    struct { void *owner; f32 value; s8 selector; } packet;
    s32 temp_v0;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x18) & 0xFF;
    packet.selector = (s8)*(s32 *)((u8 *)arg0 + 0x18);
    if ((temp_v0 < 0) || (temp_v0 >= 2)) {
        return 0;
    }
    packet.owner = arg0;
    packet.value = 0.0f;
    temp_v0 = func_151491F4(0x12C, -1, 0x11, 0, 0xD, 0xC, 0xFF, 1);
    if (temp_v0 != 0) {
        func_10022EC0((u8 *)temp_v0 + 0x28, &packet, 0xC);
    }
    return temp_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515D088 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/func_1515D088.s")
typedef struct Game1897A0EmitterVector {
    f32 x;
    f32 y;
    f32 z;
} Game1897A0EmitterVector;

typedef struct Game1897A0EmitterParticle {
    s32 field0;
    s32 field4;
    Game1897A0EmitterVector position8;
    f32 field14;
    f32 field18;
    f32 field1C;
    f32 field20;
    f32 field24;
    f32 field28;
    s16 field2C;
    s16 field2E;
    s16 field30;
    s16 field32;
    s32 field34;
    s32 field38;
    s16 field3C;
    s16 field3E;
    s16 field40;
    u8 fields42[23];
    s32 field5C;
    s32 field60;
    s16 field64;
    s16 field66;
    s16 field68;
    u8 field6A;
    f32 field6C;
    s8 fields70[4];
} Game1897A0EmitterParticle;

typedef struct Game1897A0EmitterSettings {
    f32 field0;
    f32 field4;
    s32 field8;
    s32 fieldC;
    f32 field10;
    f32 field14;
    f32 field18;
    f32 field1C;
    f32 field20;
    f32 field24;
    s32 field28;
    s32 field2C;
    s16 field30;
    s16 field32;
    s16 field34;
    s16 field36;
    s16 field38;
    f32 field3C;
} Game1897A0EmitterSettings;

typedef struct Game1897A0EmitterState {
    s16 *origin;
    f32 accumulator;
    u8 selector;
} Game1897A0EmitterState;

typedef struct Game1897A0EmitterOwner {
    u8 pad0;
    u8 field1;
    u8 pad2[0xA];
    u8 fieldC;
    u8 padD[0x1B];
    Game1897A0EmitterState state28;
} Game1897A0EmitterOwner;

void func_15143794(s16, s16, f32, void *);
void func_15152B38(void *, s32, s32);
s32 func_150ADA20();
f32 func_150ADA68();
extern Game1897A0EmitterSettings D_800A64A0[];

void func_1515D130(Game1897A0EmitterOwner *arg0) {
    Game1897A0EmitterSettings *settings;
    Game1897A0EmitterState *state;
    Game1897A0EmitterParticle descriptor;
    s32 random;

    settings = &D_800A64A0[arg0->state28.selector];
    state = &arg0->state28;
    state->accumulator += settings->field0 + func_150ADA68() * settings->field4;
    if (state->accumulator > 1.0f) {
        do {
            descriptor.field0 = settings->field8;
            descriptor.field4 = settings->fieldC;
            descriptor.field14 = settings->field10;
            descriptor.field18 = settings->field14;
            descriptor.field1C = settings->field18;
            descriptor.field20 = settings->field1C;
            descriptor.field24 = settings->field20;
            descriptor.field28 = settings->field24;
            descriptor.field2C = 0;
            descriptor.field2E = 0xFF;
            descriptor.field30 = -0x3F;
            descriptor.field32 = 0x50;
            descriptor.field34 = settings->field28;
            descriptor.field38 = settings->field2C;
            descriptor.field3C = settings->field30;
            descriptor.field3E = settings->field32;
            descriptor.field40 = 1;
            descriptor.fields42[0] = 0xC;
            descriptor.fields42[1] = 2;
            descriptor.fields42[2] = 3;
            descriptor.fields42[3] = 0xB4;
            descriptor.fields42[4] = 0;
            descriptor.fields42[5] = 0;
            descriptor.fields42[6] = 0x9B;
            descriptor.fields42[7] = 0x32;
            descriptor.fields42[8] = 0x64;
            descriptor.fields42[9] = 0;
            descriptor.fields42[10] = 0x64;
            descriptor.fields42[11] = 0xFF;
            descriptor.fields42[12] = 0xFF;
            descriptor.fields42[13] = 0xFF;
            descriptor.fields42[14] = 0xFF;
            descriptor.fields42[15] = 0;
            descriptor.fields42[16] = 0;
            descriptor.fields42[17] = 0;
            descriptor.fields42[18] = 0;
            descriptor.fields42[19] = 0xFF;
            descriptor.fields42[20] = 0;
            descriptor.fields42[21] = 1;
            descriptor.fields42[22] = 0x24;
            descriptor.field5C = 0x200005;
            descriptor.field60 = 0x60600;
            descriptor.field64 = settings->field34;
            descriptor.field66 = settings->field36;
            descriptor.field68 = settings->field38;
            descriptor.field6A = 0;
            descriptor.field6C = settings->field3C;
            descriptor.fields70[0] = -1;
            descriptor.fields70[1] = 0;
            random = func_150ADA20();
            func_15143794((s16)(random & 0xFF),
                         (s16)(0x40 - (func_150ADA20() & 0x7F)),
                         (f32)state->origin[3], &descriptor.position8);
            descriptor.position8.x += (f32)state->origin[0];
            descriptor.position8.y += (f32)state->origin[1];
            descriptor.position8.z += (f32)state->origin[2];
            func_15152B38(&descriptor, arg0->fieldC, arg0->field1);
            state->accumulator -= 1.0f;
        } while (state->accumulator > 1.0f);
    }
}
