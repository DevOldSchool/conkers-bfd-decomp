#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1D4E00.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_model_owner_mode_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A7950
 * - func_151A7A90
 * - func_151A7D6C
 * - func_151A8340
 * - func_151A8584
 * - func_151A85D4
 * - func_151A8624
 * - func_151A87F8
 * - func_151A8A78
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);
void func_100226F0(void *, s32, void *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A7950 CURRENT (445) */
void *func_151A7950(u8 *arg0, s32 arg1, u8 arg2, s32 arg3) {
    u8 *result;
    u8 *data;

    result = func_15167A68(0x2D, arg3,
                           *(s16 *)(arg0 + 2) * 0x18U + arg1 + 0x80,
                           1, arg2, 1);
    if (result == 0) {
        return 0;
    }
    func_10022EC0(result + 0x10, arg0, 0x50);
    data = result + 0x80;
    *(u8 **)(result + 0x64) = data;
    *(f32 *)(result + 0x68) = 0.0f;
    *(u8 **)(result + 0x60) = *(u8 **)(result + 0x64) +
                              *(s16 *)(arg0 + 2) * 0x18;
    *(f32 *)*(u8 **)(result + 0x64) = 0.0f;
    *(f32 *)(*(u8 **)(result + 0x64) + 4) = 0.0f;
    *(f32 *)(*(u8 **)(result + 0x64) + 8) = 0.0f;
    *(f32 *)(*(u8 **)(result + 0x64) + *(s16 *)(arg0 + 2) * 0x18 - 0x18) = 0.0f;
    *(f32 *)(*(u8 **)(result + 0x64) + *(s16 *)(arg0 + 2) * 0x18 - 0x14) = 0.0f;
    *(f32 *)(*(u8 **)(result + 0x64) + *(s16 *)(arg0 + 2) * 0x18 - 0x10) = 1.0f;
    func_100226F0(result + 0x6C, 0x10, data, 0x18);
    *(s32 *)(result + 0x7C) = (*(s16 *)(result + 0x12) << 6) + 0x140;
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A7950 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A7950.s")
typedef struct {
    u8 pad0[0x64];
    f32 (*points)[6];
} Game1D4E00Curve;
typedef struct { f32 x, y, z; } Game1D4E00Vector;

f32 func_150ADA68(void);
void func_151A8340(Game1D4E00Curve *, s16, s16, f32, s32);
void func_151450B4(void *, void *, void *);
extern s32 (*D_8008F940[])(Game1D4E00Curve *);
extern s32 (*D_8008F948[])(Game1D4E00Curve *);
extern f32 D_800BE9A4;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A7A90 CURRENT (1970) */
void func_1516972C(s32);
void func_151A7A90(Game1D4E00Curve *arg0) {
    Game1D4E00Curve *countOwner;
    struct { u8 expired; } state;
    Game1D4E00Vector cross;
    Game1D4E00Vector axis;
    Game1D4E00Vector delta;
    f32 (*point)[6];
    f32 x, y, z;
    s32 callbackIndex;

    countOwner = arg0;
    state.expired = 0;
    if (arg0->pad0[0x1C] & 1) {
        *(s16 *)((u8 *)arg0 + 0x10) -= D_800BE9E4;
        if (*(s16 *)((u8 *)arg0 + 0x10) < 0) {
            state.expired = 1;
        }
    }
    callbackIndex = *(s8 *)((u8 *)arg0 + 0x2C);
    if (callbackIndex != -1 && state.expired == 0) {
        state.expired = D_8008F940[callbackIndex](arg0) == 0;
    }
    callbackIndex = *(s8 *)((u8 *)arg0 + 0x2D);
    if (callbackIndex != -1 && state.expired == 0) {
        state.expired = D_8008F948[callbackIndex](arg0) == 0;
    }
    if (state.expired == 0) {
        *(f32 *)((u8 *)arg0 + 0x68) -= D_800BE9A4;
        if (*(f32 *)((u8 *)arg0 + 0x68) < 0.0f) {
            func_151A8340(arg0, 0, (s16)(*(s16 *)((u8 *)arg0 + 0x12) - 1),
                          *(f32 *)((u8 *)arg0 + 0x20), 100);
            *(f32 *)((u8 *)arg0 + 0x68) = func_150ADA68() * *(f32 *)((u8 *)arg0 + 0x18) + *(f32 *)((u8 *)arg0 + 0x14);
        }
        if (arg0->pad0[0x1C] & 2) {
            delta.x = *(f32 *)((u8 *)arg0 + 0x3C) - *(f32 *)((u8 *)arg0 + 0x30);
            delta.y = *(f32 *)((u8 *)arg0 + 0x40) - *(f32 *)((u8 *)arg0 + 0x34);
            delta.z = *(f32 *)((u8 *)arg0 + 0x44) - *(f32 *)((u8 *)arg0 + 0x38);
            axis = *(Game1D4E00Vector *)((u8 *)arg0 + 0x48);
            func_151450B4(&delta, &axis, &cross);
            cross.x *= *(f32 *)((u8 *)arg0 + 0x58);
            cross.y *= *(f32 *)((u8 *)arg0 + 0x58);
            cross.z *= *(f32 *)((u8 *)arg0 + 0x58);
            callbackIndex = 0;
            point = arg0->points;
            if (*(s16 *)((u8 *)arg0 + 0x12) > 0) {
                do {
                    x = (*point)[0];
                    y = (*point)[1];
                    z = (*point)[2];
                    callbackIndex++;
                    point++;
                    point[-1][3] = *(f32 *)((u8 *)arg0 + 0x30) + x * cross.x + y * axis.x + z * delta.x;
                    point[-1][4] = *(f32 *)((u8 *)arg0 + 0x34) + x * cross.y + y * axis.y + z * delta.y;
                    point[-1][5] = *(f32 *)((u8 *)arg0 + 0x38) + x * cross.z + y * axis.z + z * delta.z;
                } while (callbackIndex < *(s16 *)((u8 *)countOwner + 0x12));
            }
        }
    }
    if (state.expired != 0) {
        func_1516972C((s32)arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A7A90 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A7A90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A7D6C.s")

f32 func_150ADA68(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A8340 CURRENT (5170) */
void func_151A8340(Game1D4E00Curve *arg0, s16 arg1, s16 arg2, f32 arg3, s32 arg4) {
    f32 random;
    f32 width;
    f32 bias;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 firstIndex;
    s16 lastIndex;
    s16 middle;
    s16 nextDepth;
    s32 span;
    f32 *first;
    f32 *last;

    firstIndex = arg1;
    lastIndex = arg2;
    span = lastIndex - firstIndex;
    if (span >= 2) {
loop:
        if (((s16 *)&arg4)[1] > 0) {
        middle = firstIndex + (span >> 1);
        first = arg0->points[firstIndex];
        last = arg0->points[lastIndex];
        dx = last[0] - first[0];
        dy = last[1] - first[1];
        dz = last[2] - first[2];
        random = func_150ADA68();
        width = arg3 + arg3;
        bias = -arg3;
        arg0->points[middle][0] = (first[0] + dx * 0.5f) + (random * width + bias);
        arg0->points[middle][1] = (first[1] + dy * 0.5f) + (func_150ADA68() * width + bias);
        arg0->points[middle][2] = first[2] + dz * 0.5f;
        nextDepth = ((s16 *)&arg4)[1] - 1;
        func_151A8340(arg0, firstIndex, middle, arg3, nextDepth);
        lastIndex = lastIndex;
        span = lastIndex - middle;
        firstIndex = middle;
        ((s16 *)&arg4)[1] = nextDepth;
        if (span >= 2) {
            goto loop;
        }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A8340 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A8340.s")
void func_151A8560(s32 arg0) {
    func_151D5E30(arg0 + 0x6C, arg0);
}
typedef struct {
    u8 pad_0[0x5C];
    u8 field_5C;
} Game1D4E00State;

void func_151A8560(s32);
extern void (*D_8008F94C[])(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A8584 CURRENT (575) */
void func_151A8584(s32 arg0) {
    void (*temp_v0)(s32);

    temp_v0 = D_8008F94C[((Game1D4E00State *)arg0)->field_5C];
    if (temp_v0 != 0) {
        temp_v0(arg0);
    }
    func_151A8560(arg0);
    func_15169804(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A8584 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A8584.s")
extern void (*D_8008F958[])(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A85D4 CURRENT (575) */
void func_151A85D4(s32 arg0) {
    void (*temp_v0)(s32);

    temp_v0 = D_8008F958[((Game1D4E00State *)arg0)->field_5C];
    if (temp_v0 != 0) {
        temp_v0(arg0);
    }
    func_151A8560(arg0);
    func_15169824(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A85D4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A85D4.s")
typedef struct { u8 bytes[4]; } Game1D4E00Colour;
typedef struct {
    s16 lifetime;
    s16 count;
    f32 field04;
    f32 field08;
    u8 timed;
    u8 pad0D[3];
    f32 field10;
    Game1D4E00Colour colour;
    f32 field18;
    u8 mode;
    s8 type;
    u8 pad1E[2];
    f32 field20[10];
    f32 field48;
    u8 field4C;
    u8 pad4D[3];
} Game1D4E00Descriptor;
typedef struct {
    void *owner;
    u8 generation;
    u8 pad05[3];
    Game1D4E00Vector position;
    u8 style;
    u8 pad15[3];
    Game1D4E00Vector offset;
    u8 flag24;
    u8 flag25;
    u8 pad26[2];
} Game1D4E00OwnerData;

extern f32 D_800A8DE0;
void *func_151A7950(u8 *, s32, u8, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A8624 CURRENT (1828) */
void *func_151A8624(u8 *arg0, Game1D4E00Vector *arg1, s32 arg2, s32 arg3,
                   f32 arg4, f32 arg5, Game1D4E00Colour *arg6, f32 arg7,
                   Game1D4E00Vector *arg8, s32 arg9, s32 arg10, s32 arg11,
                   s32 arg12, s32 arg13, s32 arg14) {
    void *result;
    Game1D4E00Descriptor descriptor;
    Game1D4E00OwnerData owner;
    u8 mode;

    arg2 = (u8)arg2;
    arg3 = (s16)arg3;
    mode = arg9;
    if (arg0 == 0) {
        return 0;
    }
    if (mode >= 2) {
        mode = 0;
    }
    owner.position = *arg1;
    owner.style = arg2;
    owner.flag25 = 0;
    owner.owner = arg0;
    owner.generation = arg0[0x3B];
    owner.flag24 = arg10;
    if (arg8 != 0) {
        owner.offset = *arg8;
    } else {
        owner.offset.x = 0.0f;
        owner.offset.y = 0.0f;
        owner.offset.z = 0.0f;
    }
    if (arg3 == -1) {
        descriptor.lifetime = 300;
    } else {
        descriptor.lifetime = arg3;
    }
    descriptor.count = 9;
    descriptor.field04 = arg4;
    descriptor.field08 = arg5;
    if (arg3 == -1) {
        descriptor.timed = 0;
    } else {
        descriptor.timed = 1;
    }
    descriptor.field10 = D_800A8DE0;
    descriptor.colour = *arg6;
    descriptor.field18 = arg7;
    if (mode != 0 && mode == 1) {
        descriptor.mode = 1;
    } else {
        descriptor.mode = 1;
    }
    descriptor.field20[0] = 0.0f;
    descriptor.field20[1] = 0.0f;
    descriptor.field20[2] = 0.0f;
    descriptor.field20[3] = 0.0f;
    descriptor.field20[4] = 0.0f;
    descriptor.field20[5] = 0.0f;
    descriptor.field20[6] = 0.0f;
    descriptor.field20[7] = 0.0f;
    descriptor.field20[8] = 0.0f;
    descriptor.field20[9] = 0.0f;
    descriptor.field4C = 2;
    descriptor.type = arg11;
    descriptor.field48 = 1.0f;
    result = func_151A7950((u8 *)&descriptor, arg12 + 0x28, arg13, arg14);
    if (result != 0) {
        func_10022EC0(*(void **)((u8 *)result + 0x60), &owner, sizeof(owner));
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A8624 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A8624.s")
typedef struct Game1D4E00Owner {
    s32 active;
    u8 type;
    u8 pad5[0xF];
    Game1D4E00Vector position;
    u8 pad20[0x1B];
    u8 generation;
    u8 pad3C[0x198];
    u8 *transform;
} Game1D4E00Owner;

typedef struct Game1D4E00Beam {
    u8 pad0[0x1C];
    u8 flags;
    u8 pad1D[0x13];
    Game1D4E00Vector position;
    Game1D4E00Vector endpoint;
    Game1D4E00Vector perpendicular;
    f32 length;
    f32 inverse_length;
    u8 pad5C[4];
    Game1D4E00OwnerData *owner_data;
} Game1D4E00Beam;

s32 func_150AC9C0(f32, f32, f32, f32, f32, f32, void *, s16 *, f32 *, f32 *, f32 *, f32 *, s32 *, void *, f32);
void func_15143134(f32 *, f32 *, s32);
s32 func_15145C90(s32);
s32 func_15146078(void *, void *, void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A87F8 CURRENT (2941) */
s32 func_151A87F8(Game1D4E00Beam *arg0) {
    Game1D4E00OwnerData *data;
    Game1D4E00Owner *owner;
    Game1D4E00Vector delta;
    s32 hit;
    f32 x;
    f32 z;
    f32 y;
    Game1D4E00Vector scratch;
    f32 length;
    u8 *transform;
    f32 dx;
    f32 dy;

    data = arg0->owner_data;
    owner = data->owner;
    if (owner->active == 0 || owner->generation != data->generation || owner->type == 0xFF) {
        return 0;
    }
    transform = owner->transform;
    if (transform != 0) {
        func_15143134(&data->position.x, &arg0->position.x, (s32)(transform + (data->style << 6)));
        if (!(data->flag25 & 1)) {
            x = arg0->position.x;
            z = arg0->position.z;
            y = arg0->position.y;
            if (func_150AC9C0(x, y, z,
                              dx = x - (owner->position.x + data->offset.x),
                              dy = y - (owner->position.y + data->offset.y),
                              z - (owner->position.z + data->offset.z),
                              0, 0, &arg0->endpoint.x, &arg0->endpoint.y, &arg0->endpoint.z,
                              0, &hit, 0, 0.0f) != 0) {
                if (func_15145C90(hit) != 0) {
                    data->flag25 |= 1;
                } else {
                    arg0->flags &= ~2;
                    return 1;
                }
            } else {
                arg0->flags &= ~2;
                return 1;
            }
        }
        delta.x = arg0->endpoint.x - arg0->position.x;
        delta.y = arg0->endpoint.y - arg0->position.y;
        delta.z = arg0->endpoint.z - arg0->position.z;
        length = func_15143E64(&delta);
        arg0->length = length;
        if (length != 0.0f) {
            arg0->inverse_length = 1.0f / arg0->length;
            func_15146078(&delta, &scratch, &arg0->perpendicular);
            arg0->flags |= 2;
            goto done;
        } else {
            arg0->flags &= ~2;
            goto done;
        }
    } else {
        arg0->flags &= ~2;
    }
done:
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A87F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A87F8.s")
typedef void (*Game1D4E00Callback)(void *, s32, u8);

extern Game1D4E00Callback D_8008F964[];

void func_151A8A20(void *arg0, s32 arg1, u8 arg2) {
    Game1D4E00Callback temp_v1;
    u8 var_v0;

    var_v0 = *(u8 *)((u8 *)arg0 + 0x5C);
    if (var_v0 >= 3) {
        var_v0 = 0;
    }
    temp_v1 = D_8008F964[var_v0];
    if (temp_v1 != 0) {
        temp_v1(arg0, arg1, arg2);
    }
}

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A8A78 CURRENT (115) */
void func_151A8A78(void *arg0, void *arg1, u8 arg2) {
    s32 temp_a0;
    s32 temp_t6;
    s32 temp_v1;
    void *temp_v0;

    temp_t6 = arg2;
    temp_v0 = *(void **)((u8 *)arg0 + 0x60);
    if (temp_t6 == 0) {
        if ((*(s32 *)arg1 == *(s32 *)temp_v0) || (*(u8 *)((u8 *)arg1 + 4) == *(u8 *)((u8 *)temp_v0 + 4))) {
            func_1516972C(arg0);
        }
    } else if (temp_t6 == 0x2D) {
        temp_a0 = *(s32 *)arg1;
        temp_v1 = *(s32 *)temp_v0;
        if (temp_a0 == temp_v1) {
            *(s32 *)temp_v0 = *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)((u8 *)temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_v1) {
            *(s32 *)temp_v0 = temp_a0;
            *(u8 *)((u8 *)temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 8);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A8A78 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A8A78.s")
