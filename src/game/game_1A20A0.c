#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1A20A0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_model_debris_family.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15174BF0
 * - func_15175390
 * - func_15175958
 * - func_1517685C
 * - func_15176DF0
 * - func_1517725C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game17725CEntry {
    u8 *model;
    u8 pad[0x10];
} Game17725CEntry;
extern Game17725CEntry D_800DDE88[];
typedef struct Game174BF0Actor {
    u8 pad0[0x90];
    s8 group, phase;
    s16 flags;
    u8 *model;
    f32 x, y, z;
    s16 timer, enabled;
    f32 pitch, yaw, roll, velocity, yawStep, fieldBC, scale;
    u8 padC4[4];
    f32 baseHeight;
    u8 padCC[0x1C];
    u32 surfaceFlags;
    u8 brightness;
    s8 modelIndex;
    u16 sound;
    s8 opacity, fieldF1;
} Game174BF0Actor;
u16 func_10010E78(s32, s32, u16, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_1510F8D8(s32, s32, s32, s32 *);
extern f32 D_800A7174;
extern s32 D_800DBE3C, D_800DBE5C;
extern u8 *D_800DBFF0;
extern u8 D_800A7170[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15174BF0 CURRENT (2285) */
void func_15174BF0(volatile s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, volatile s32 arg8) {
    f32 height;
    f32 jitterScale;
    s32 baseAngle;
    s32 pitch;
    s32 x, z;
    s32 angleValue;
    s32 angle;
    s32 index;
    u32 flags;
    f32 delta[3];
    u8 *position;
    s32 surface;
    Game174BF0Actor *actor;

    position = D_800DBFF0 + arg5 * 0x9A0;
    height = (f32)arg3;
    delta[0] = (f32)arg2 - *(f32 *)(position + 0x2f8);
    delta[1] = height - *(f32 *)(position + 0x2fc);
    delta[2] = (f32)arg4 - *(f32 *)(position + 0x300);
    baseAngle = (s32)func_15048FC8(delta);
    index = 0;
    if (arg0 > 0) {
        jitterScale = D_800A7174;
        do {
            actor = func_15167A68(0xA, 0, 0xF8, 1, 0xFF, 1);
            if (actor == NULL) return;
            arg5 = arg8 & 1;
            x = (s32)(func_150ADA20() & 0x7F) + arg2 - 0x3F;
            z = (s32)(func_150ADA20() & 0x7F) + arg4 - 0x3F;
            actor->flags = 3;
            actor->y = height;
            actor->x = (f32)x;
            actor->group = arg1;
            actor->z = (f32)z;
            actor->timer = func_150ADA20() % 15U + 0xA;
            actor->enabled = 1;
            angleValue = (s32)(func_150ADA20() & 0x1F) + baseAngle - 0xF;
            angle = angleValue;
            if (angleValue < 0) angle = angleValue + 0x168;
            else if (angleValue >= 0x168) angle = angleValue - 0x168;
            pitch = (s32)(func_150ADA20() & 0x1F) - 0xF;
            actor->roll = 0.0f;
            actor->velocity = -1.0f;
            actor->pitch = (f32)pitch;
            actor->yaw = (f32)angle;
            pitch = (s32)(func_150ADA20() & 0xFF) - 0x80;
            actor->fieldBC = 0.0f;
            actor->yawStep = (f32)pitch * jitterScale;
            actor->scale = (f32)(s32)(func_150ADA20() & 0xFFFF) * 0.000030517578125f * arg7 + arg6;
            angleValue = func_150ADA20() & 1;
            actor->modelIndex = angleValue;
            actor->model = D_800DDE88[angleValue].model;
            if (index == 0) actor->sound = func_10010E78(0, 0xA2, 0x7D00, 0, 0, 0, x, arg3, z, 0x3E8, 0xFA0);
            else actor->sound = 0;
            actor->surfaceFlags = 0;
            if (arg5) {
                actor->flags |= 0x80;
                actor->baseHeight = (f32)func_1510F8D8(x, arg3, z, &surface);
                flags = surface != 0 ? *(u32 *)(D_800DBE5C + ((surface - D_800DBE3C) / 12) * 4) : 0;
                actor->surfaceFlags = flags;
                actor->brightness = D_800A7170[(flags >> 5) & 3];
            } else actor->brightness = 0;
            actor->opacity = 0;
            actor->fieldF1 = 0;
            index++;
        } while (index != arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15174BF0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A20A0/func_15174BF0.s")
typedef struct Game174FA4Surface {
    s32 height;
    u8 pad04[0xC];
} Game174FA4Surface;

s32 func_150A3A70(s32, s32);
void func_1510F800(s32);
extern Game174FA4Surface D_800D3300[];
extern s32 D_800DDF14;

void func_15174FA4(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                   s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   f32 arg8, f32 arg9) {
    f32 height;
    s32 initialX;
    s32 initialHeight;
    s32 x;
    s32 z;
    s32 radius;
    s32 minimum;
    s32 count;
    s32 i;
    s32 index;
    Game174BF0Actor *actor;

    initialX = arg2;
    initialHeight = arg3;
    if (arg7 == 0) func_1510F800(0);
    index = 0;
    if (arg0 > 0) {
        do {
            actor = func_15167A68(0x13, 0, 0xF8, 1, 0xFF, 1);
            if (actor == NULL) return;
            radius = arg5 >> 1;
            height = (f32)initialHeight;
            x = (func_150ADA20() % (u32)arg5) + initialX - radius;
            z = (func_150ADA20() % (u32)arg5) + arg4 - radius;
            actor->group = arg1;
            actor->x = (f32)x;
            actor->y = height;
            actor->z = (f32)z;
            actor->timer = func_150ADA20() % 3U + 4;
            actor->enabled = 0;
            actor->pitch = (f32)((s32)(func_150ADA20() & 0x1F) - 0xF);
            actor->yaw = (f32)(func_150ADA20() % 360U);
            actor->roll = (f32)((s32)(func_150ADA20() & 0x1F) - 0xF);
            actor->velocity = 0.0f;
            actor->fieldBC = 0.0f;
            actor->yawStep = 3.0f;
            actor->scale = (f32)(s32)(func_150ADA20() & 0xFFFF) * 0.000030517578125f * arg9 + arg8;
            actor->model = (u8 *)D_800DDF14;
            actor->modelIndex = 7;
            count = func_150A3A70(x, z);
            if (count == 0) {
                func_1516979C(actor);
            } else {
                minimum = D_800D3300[0].height;
                for (i = 1; i < count; i++) {
                    if (D_800D3300[i].height < minimum) {
                        minimum = D_800D3300[i].height;
                    }
                }
                minimum >>= 8;
                actor->baseHeight = (f32)minimum;
                if (arg7 == 0) {
                    actor->phase = 0;
                    actor->y = (f32)(minimum + 10);
                    actor->flags = 1;
                } else {
                    actor->phase = 2;
                    actor->flags = 4;
                    *(f32 *)((u8 *)actor + 0xE4) = (f32)((s32)(func_150ADA20() & 0x7F) + minimum + 300);
                    actor->y = (f32)((s32)(func_150ADA20() & 0x7F) + minimum + 300);
                }
                *(f32 *)((u8 *)actor + 0xCC) = 0;
                *(s16 *)((u8 *)actor + 0xD0) = initialX;
                *(s16 *)((u8 *)actor + 0xD4) = arg4;
                *(s16 *)((u8 *)actor + 0xD6) = radius;
                *(f32 *)((u8 *)actor + 0xE0) = 0;
                *(s16 *)((u8 *)actor + 0xDC) = 0;
                actor->surfaceFlags = 0;
                actor->brightness = 0;
                actor->opacity = 0;
                actor->fieldF1 = 0;
            }
            index++;
        } while (index != arg0);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A20A0/func_15175390.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A20A0/func_15175958.s")
typedef struct {
    u8 pad0[0x90];
    u8 group, phase;
    s16 flags;
    u8 pad94[4];
    f32 x, y, z;
    u8 padA4[4];
    f32 angle, yaw;
    u8 padB0[4];
    f32 velocity, yawStep;
    u8 padBC[0xC];
    f32 baseHeight, angleStep;
    u8 padD0[0x14];
    f32 targetHeight;
    u8 padE8[5];
    u8 model;
} Game17685CActor;
typedef struct {
    u8 pad0[0x14];
    f32 x, y, z;
} Game17685CPosition;
extern Game17685CPosition D_800CC2D0;
extern u8 D_800DDF5C[], D_800DDF68[];
s32 func_150AD960(s32, s32, s32, s32);
void func_15175958(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517685C CURRENT (700) */
void func_1517685C(Game17685CActor *arg0) {
    f32 temp_ft3;
    f32 temp_fv0;
    s32 temp_v1;

    if (D_800DDF5C[arg0->group] != 0) {
        temp_v1 = 1;
        D_800DDF68[arg0->model] = temp_v1;
        switch (arg0->phase) {                          /* irregular */
        case 0:
            if (func_150AD960((s32) D_800CC2D0.x, (s32) D_800CC2D0.z, (s32) arg0->x, (s32) arg0->z) < 0x190) {
                arg0->phase = 1U;
                temp_ft3 = (f32) (-1 - (s32)(func_150ADA20() & 3));
                arg0->velocity = temp_ft3;
                arg0->angle = -8.0f;
                return;
            }
            temp_fv0 = arg0->angleStep;
            if (0.0f != temp_fv0) {
                arg0->angle = (f32) (arg0->angle + temp_fv0);
                if (temp_fv0 < 0.0f) {
                    arg0->yaw = (f32) (arg0->yaw + arg0->yawStep);
                }
                temp_fv0 = arg0->angle;
                if (temp_fv0 > 45.0f) {
                    arg0->angleStep = -5.0f;
                } else if ((arg0->angleStep < 0) && (temp_fv0 > 25.0f) && ((s32)(func_150ADA20() & 0xFF) < 0x33)) {
                    arg0->angleStep = 5.0f;
                }
                if (arg0->angle <= 10.0f) {
                    arg0->angleStep = 0.0f;
                    return;
                }
            } else {
                temp_v1 = func_150ADA20() & 0xFF;
                if (temp_v1 < 0x19) {
                    arg0->angleStep = 5.0f;
                    if (temp_v1 < 0xD) {
                        arg0->yawStep = (f32) ((s32)(func_150ADA20() % 6U) - 3);
                        return;
                    }
                    arg0->yawStep = 0.0f;
                }
            }
            break;
        case 1:
            if ((300.0f + arg0->baseHeight) <= arg0->y) {
                arg0->phase = 2U;
                arg0->flags = (s16) (arg0->flags & 0xFFFE);
                arg0->flags = (s16) (arg0->flags | 4);
                arg0->targetHeight = (f32) ((f32) (s32)(func_150ADA20() & 0x7F) + (300.0f + arg0->baseHeight));
            }
            func_15175958(arg0);
            return;
        default:
        case 2:
        case 3:
            if (arg0->y < arg0->targetHeight) {
                arg0->velocity = -1.5f;
            } else if (arg0->angle < 0) {
                arg0->velocity = 1.5f;
            }
            func_15175958(arg0);
            return;
        }
    } else {
        func_1516972C(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517685C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A20A0/func_1517685C.s")
typedef struct Game176B84Actor {
    u8 pad0[0x90];
    u8 group, phase;
    u8 pad92[2];
    u8 *model;
    f32 x, y, z;
    u8 padA4[0x24];
    f32 floor;
    u8 padCC[6];
    s16 delayBase;
    u8 padD4[6];
    s16 delayRange;
    u8 padDC[8];
    f32 delay;
    u8 padE8[5];
    u8 slot;
    u8 padEE[2];
    u8 alpha;
    u8 fading;
} Game176B84Actor;

extern u8 D_800DDE80[], D_800DDE84[];
extern s32 D_800BE9E4, D_800DDF78[];

void func_15176B84(Game176B84Actor *arg0) {
    s32 alpha;

    if (*(s32 *)(D_800DDE80 + arg0->slot * 0x14) == 0 || D_800DDF78[arg0->slot] == 0) {
        func_1516972C(arg0);
        return;
    }
    alpha = arg0->alpha;
    if (arg0->fading == 0) {
        if (D_800DDF5C[arg0->group] == 0) {
            arg0->fading = 1;
        } else if (alpha != 0xFF) {
            alpha += D_800BE9E4 * 4;
            if (alpha >= 0x100) {
                alpha = 0xFF;
            }
            arg0->alpha = alpha;
        }
    } else {
        if (alpha == 0) {
            func_1516972C(arg0);
            return;
        }
        alpha -= D_800BE9E4 * 4;
        if (alpha < 0) {
            alpha = 0;
        }
        arg0->alpha = alpha;
    }
    D_800DDF68[arg0->slot] = 1;
    switch (arg0->phase) {
    case 0:
        if (func_150AD960(D_800CC2D0.x, D_800CC2D0.z, arg0->x, arg0->z) < 0xC8) {
            arg0->phase = 2;
            arg0->delay = (f32)(func_150ADA20() % arg0->delayRange) + arg0->delayBase;
            arg0->model = D_800DDE88[arg0->slot].model;
        } else {
            arg0->model = *(u8 **)(D_800DDE84 + arg0->slot * 0x14);
        }
        break;
    case 4:
        if (arg0->y < arg0->floor) {
            func_1516972C(arg0);
            return;
        }
    default:
    case 2:
    case 3:
        func_15175958(arg0);
        break;
    }
}
void func_150A7790(void *, s32);
void func_150A8050(void *, f32, f32, f32);
void func_150A7A48(void *, void *, void *);
void *func_15142FBC(void *, s32, s32, u8 *);
extern u8 D_800BE9C0, D_800DDE80[], D_800A7170[];
extern s32 D_800BE9E4, D_800DDF78[];
extern u32 D_800DDE8C[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15176DF0 CURRENT (2296) */
void *func_15176DF0(u32 *gdl, u8 *state, s16 arg2) {
    s32 model;
    f32 second[4][4];
    f32 first[4][4];
    struct { s32 red, green, blue; } color;
    f32 zero;
    s32 brightness;

    model = state[0xED];
    if (*(s32 *)(D_800DDE80 + model * 0x14) == 0 || D_800DDF78[model] == 0) {
        return gdl;
    }
    zero = 0.0f;
    func_150A8050(first, zero, *(f32 *)(state + 0xAC), zero);
    func_150A8050(second, *(f32 *)(state + 0xA8), 0, *(f32 *)(state + 0xB0));
    func_150A7A48(second, first, first);
    first[3][0] = *(f32 *)(state + 0x98);
    first[3][1] = *(f32 *)(state + 0x9C);
    first[3][2] = *(f32 *)(state + 0xA0);
    first[0][0] *= *(f32 *)(state + 0xC0);
    first[0][1] *= *(f32 *)(state + 0xC0);
    first[0][2] *= *(f32 *)(state + 0xC0);
    first[1][0] *= *(f32 *)(state + 0xC0);
    first[1][1] *= *(f32 *)(state + 0xC0);
    first[1][2] *= *(f32 *)(state + 0xC0);
    first[2][0] *= *(f32 *)(state + 0xC0);
    first[2][1] *= *(f32 *)(state + 0xC0);
    first[2][2] *= *(f32 *)(state + 0xC0);
    func_150A7790(first, (s32)((state + 0x10) + (D_800BE9C0 << 6)));
    { u32 *g = gdl; gdl += 2; g[0] = 0xDA380003; g[1] = (u32)((state + 0x10) + (D_800BE9C0 << 6)); }
    { u32 *g = gdl; gdl += 2; g[0] = 0xDB060004; g[1] = *(u32 *)(state + 0x94); }
    { u32 *g = gdl; gdl += 2; g[0] = 0xE7000000; g[1] = 0; }
    {
        u8 loaded;
        s32 target;

        brightness = state[0xEC];
        target = D_800A7170[(*(u32 *)(state + 0xE8) >> 5) & 3];
        if (brightness != target) {
            if (brightness < target) {
                brightness += D_800BE9E4 * 4;
                if (target < brightness) {
                    brightness = target;
                }
            } else {
                brightness -= D_800BE9E4 * 4;
                if (brightness < 0) {
                    brightness = 0;
                }
            }
            state[0xEC] = brightness;
        }
        color.green = brightness;
        color.red = brightness;
        loaded = 0;
        color.blue = brightness;
        gdl = func_15142FBC(gdl, 0x82CA0, 0x504A50, &loaded);
    }
    { u32 *g = gdl; gdl += 2; g[0] = 0xFB000000; g[1] = ((color.red & 0xFF) << 24) | ((color.green & 0xFF) << 16) | ((color.blue & 0xFF) << 8) | state[0xF0]; }
    { u32 *g = gdl; gdl += 2; g[0] = 0xDE000000; g[1] = D_800DDE8C[state[0xED] * 5]; }
    return gdl;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15176DF0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A20A0/func_15176DF0.s")
typedef struct Game1770C8Packet {
    f32 m[4][4];
} Game1770C8Packet;

void func_150A7790(void *, s32);
void func_150A8050(void *, f32, f32, f32);
s32 func_1510AEE0(f32 *, f32, f32, f32, f32, f32, f32, f32, f32 *, f32 *);
void *func_15176DF0(u32 *, u8 *, s16);
extern u8 D_800BE9C0;
extern f32 D_800D35E0, D_800D35E4;
extern f32 D_800D9B20;
extern u8 D_800D9C10[];
extern u8 D_800DDE80[];

void *func_151770C8(u32 *gdl, u8 *arg1, s16 arg2) {
    Game1770C8Packet packet;
    s32 culled;

    culled = func_1510AEE0((f32 *)(D_800D9C10 + (arg2 << 6)),
                      *(f32 *)(arg1 + 0x98), *(f32 *)(arg1 + 0x9C), *(f32 *)(arg1 + 0xA0),
                      D_800D9B20, 4000.0f, D_800D35E0, D_800D35E4, 0, 0);
    if (culled == 0) {
        switch (arg1[0x91]) {
        case 0:
            func_150A8050(&packet, *(f32 *)(arg1 + 0xA8), *(f32 *)(arg1 + 0xAC), *(f32 *)(arg1 + 0xB0));
            packet.m[3][0] = *(f32 *)(arg1 + 0x98);
            packet.m[3][1] = *(f32 *)(arg1 + 0x9C);
            packet.m[3][2] = *(f32 *)(arg1 + 0xA0);
            func_150A7790(&packet, (s32)((arg1 + 0x10) + (D_800BE9C0 << 6)));
            { u32 *g = gdl; gdl += 2; g[0] = 0xDA380003; g[1] = (u32)((arg1 + 0x10) + (D_800BE9C0 << 6)); }
            { u32 *g = gdl; gdl += 2; g[0] = 0xDB060004; g[1] = *(u32 *)(D_800DDE80 + 0xCC); }
            { u32 *g = gdl; gdl += 2; g[0] = 0xDE000000; g[1] = *(u32 *)(D_800DDE80 + 0xD4); }
            break;
        case 1:
        case 2:
        case 3:
        default:
            gdl = func_15176DF0(gdl, arg1, arg2);
            break;
        }
    }
    return gdl;
}
typedef struct Game17725CState {
    u8 pad0[0x18];
    f32 scale;
    f32 increment;
    u8 pad20[4];
    f32 angle;
    f32 magnitude;
    u8 pad2C[4];
    f32 firstRadius;
    f32 secondRadius;
} Game17725CState;


f32 func_150AD780(f32);
f32 func_150AD78C(f32);
extern Game17725CState D_8008D0B0[];
extern f32 D_800A71AC;
extern f32 D_800A71B0;
extern f32 D_800A71B4;
extern f32 D_800A71B8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517725C CURRENT (1884) */
void func_1517725C(u8 arg0) {
    Game17725CState *state;
    u8 *model;
    f32 trig;
    f32 amount;
    s32 x;
    s32 y;
    s32 index;

    index = arg0;
    state = &D_8008D0B0[index];
    model = D_800DDE88[index].model;
    state->scale = func_150AD78C(state->angle * D_800A71AC) * state->magnitude;
    amount = state->scale * D_800A71B0;
    trig = func_150AD78C(amount);
    x = (s32)(state->firstRadius * func_150AD780(amount));
    y = (s32)(state->firstRadius * trig);
    *(s16 *)(model + 0xA0) = -x;
    *(s16 *)(model + 0xB0) = -x;
    *(s16 *)(model + 0x110) = x;
    *(s16 *)(model + 0x120) = x;
    *(s16 *)(model + 0x112) = y;
    *(s16 *)(model + 0x122) = y;
    *(s16 *)(model + 0xA2) = y;
    *(s16 *)(model + 0xB2) = y;
    state->scale = func_150AD78C((state->angle - 30.0f) * D_800A71B4) * state->magnitude;
    amount = state->scale * D_800A71B8;
    trig = func_150AD78C(amount);
    x = (s32)(state->secondRadius * func_150AD780(amount));
    y = (s32)(state->secondRadius * trig);
    *(s16 *)(model + 0xE0) = -x;
    *(s16 *)(model + 0x130) = x;
    *(s16 *)(model + 0xE2) = y;
    *(s16 *)(model + 0x132) = y;
    state->angle += state->increment;
    if (state->angle >= 360.0f) {
        state->angle -= 360.0f;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517725C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A20A0/func_1517725C.s")
