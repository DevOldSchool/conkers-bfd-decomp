#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1BF090.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_composite_emitter_timed_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15191BE0
 * - func_15191D54
 * - func_1519203C
 * - func_15192358
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1BF090Vector {
    s32 x;
    s32 y;
    s32 z;
} Game1BF090Vector;

typedef struct Game1BF090Payload {
    void *owner;
    u8 mode;
    u8 pad5[3];
    Game1BF090Vector origin;
    s32 radius;
    f32 zero;
    f32 start;
    f32 end;
    u8 scratch[0x24];
    f32 scaleX;
    f32 scaleY;
    s16 field50;
    s16 field52;
    u8 field54;
    u8 field55;
    u8 pad56[2];
    f32 scaleZ;
    f32 field5C;
    f32 field60;
    u8 field64;
    u8 pad65[3];
} Game1BF090Payload;

void func_1504715C(void *, void *, s32, void *);
void *func_10022EC0(void *, const void *, u32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15191BE0 CURRENT (3280) */
s32 func_15191BE0(u8 *arg0, Game1BF090Vector *arg1, s32 arg2,
                  f32 arg3, f32 arg4, s16 arg5, f32 arg6, f32 arg7,
                  s16 arg8, s16 arg9, u8 arg10, u8 arg11, f32 arg12,
                  f32 arg13, f32 arg14, u8 arg15, u8 arg16, s32 arg17) {
    Game1BF090Payload payload;
    void *effect;
    s16 kind;
    s32 enabled;

    if (arg0 == 0) {
        return 0;
    }
    payload.owner = arg0;
    payload.mode = arg0[0x3B];
    payload.origin = *arg1;
    payload.radius = (arg2 & 0xFF) << 6;
    payload.zero = 0.0f;
    payload.start = arg3;
    payload.end = arg4;
    func_1504715C(payload.scratch, arg0, arg2 & 0xFF, arg0);
    payload.scaleX = arg6;
    payload.scaleY = arg7;
    payload.field50 = arg8;
    payload.field52 = arg9;
    payload.field54 = arg10;
    payload.field55 = arg11;
    payload.scaleZ = arg12;
    payload.field5C = arg13;
    payload.field60 = arg14;
    payload.field64 = arg15;
    if (arg5 == -1) {
        kind = 0x12C;
        enabled = 0;
    } else {
        kind = arg5;
        enabled = 1;
    }
    effect = func_15149130(kind, -1, 0x1D, -1, enabled, 0x1D, 0x68, arg16, arg17);
    if (effect != 0) {
        func_10022EC0((u8 *)effect + 0x28, &payload, 0x68);
    }
    return (s32)effect;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15191BE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BF090/func_15191BE0.s")
struct Game1BF090Packed;
u32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_15143134(f32 *, f32 *, s32);
s32 func_1514672C(f32 *);
s32 func_15046F84(f32 *, u16, f32, void *);
void *func_1519203C(Game1BF090Vector *, Game1BF090Vector *, f32, s32, s32,
                    s32, f32, s32, f32, struct Game1BF090Packed *, s32, s32, s32);
extern f32 D_800A80E8, D_800A80EC, D_800A80F0, D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15191D54 CURRENT (994) */
void func_15191D54(u8 *arg0) {
    Game1BF090Vector position;
    Game1BF090Vector direction;
    f32 limit;
    f32 height;
    u32 lifeRandom, modeRandom;
    s32 enabled;
    s32 transform;
    u8 *owner;
    Game1BF090Payload *payload;

    owner = *(u8 **)(arg0 + 0x28);
    payload = (Game1BF090Payload *)(arg0 + 0x28);
    if (*(s32 *)owner == 0 || ((u8 *)payload)[4] != owner[0x3B]) {
        *(s16 *)(arg0 + 0xE) = -1;
        return;
    }
    payload->zero += (payload->start + func_150ADA68() * payload->end) * D_800BE9A4;
    if (payload->zero > 1.0f) {
        transform = *(s32 *)(owner + 0x1D4);
        if (transform != 0) {
            func_15143134((f32 *)&payload->origin, (f32 *)&position, transform + payload->radius);
            if (payload->field60 > 0.0f) {
                if (func_1514672C((f32 *)&position) == 0) {
                    height = D_800A80E8;
                } else {
                    limit = D_800A80EC;
                    if (func_15046F84((f32 *)&position, 0, limit, payload->scratch) != 0) {
                        height = *(f32 *)payload->scratch;
                    } else {
                        height = limit;
                    }
                }
            } else {
                height = D_800A80F0;
            }
            do {
                limit = func_150ADA68();
                enabled = 0;
                if (limit < payload->field60) {
                    enabled = 1;
                }
                ((f32 *)&direction)[0] = 0.0f;
                ((f32 *)&direction)[1] = 0.0f;
                ((f32 *)&direction)[2] = 0.0f;
                limit = func_150ADA68();
                lifeRandom = func_150ADA20();
                modeRandom = func_150ADA20();
                func_1519203C(&position, &direction,
                    limit * payload->scaleY + payload->scaleX,
                    (s16)(lifeRandom % (u32)(payload->field52 + 1) + payload->field50),
                    modeRandom % (u32)(payload->field55 + 1) + payload->field54,
                    0xFF, func_150ADA68() * payload->field5C + payload->scaleZ,
                    enabled, height, (struct Game1BF090Packed *)(payload->scratch + 4),
                    payload->field64, arg0[0xC], arg0[1]);
                payload->zero -= 1.0f;
            } while (payload->zero > 1.0f);
            return;
        }
        if (payload->zero > 1.0f) {
            do {
                payload->zero -= 1.0f;
            } while (payload->zero > 1.0f);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15191D54 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BF090/func_15191D54.s")

typedef struct Game1BF090Spawn {
    s32 header;
    s32 owner;
    s16 type, lifetime;
    s32 fieldC, field10;
    u8 color[4];
    u8 field18, field19, field1A, mode, group, kind;
    s16 field1E, field20, count;
    f32 scale, scaleX, scaleY;
    Game1BF090Vector position;
    f32 rotation[3];
    Game1BF090Vector direction;
    f32 speed;
    s32 flags;
    u8 pad5C[4];
    u8 channel0, channel1, channel2;
    s8 channel3, channel4;
    u8 channel5;
    u8 pad66[0xA];
} Game1BF090Spawn;

typedef struct Game1BF090Packed {
    u8 bytes[16];
    u16 last;
} Game1BF090Packed;

typedef struct Game1BF090Fragment {
    f32 scale;
    u8 random[4];
    f32 scaleX, scaleY, height;
    Game1BF090Packed body;
    u8 kind;
} Game1BF090Fragment;

u32 func_150ADA20(void);
f32 func_150ADA68(void);
void *func_15130374(s32, u8, s32, u8, s32);
extern s32 (*D_8008FCD0[])(void);
extern f32 D_800A80F4, D_800A80F8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519203C CURRENT (210) */
void *func_1519203C(Game1BF090Vector *position, Game1BF090Vector *direction,
                    f32 speed, s32 lifetime, s32 mode, s32 group,
                    f32 scale, s32 unused, f32 height, Game1BF090Packed *body,
                    s32 kind, s32 priority, s32 owner) {
    void *effect;
    Game1BF090Spawn spawn;
    Game1BF090Fragment fragment;
    s32 second;
    s32 first;

    spawn.type = 0x4401;
    spawn.header = 0x200005;
    spawn.owner = 0;
    spawn.fieldC = 0;
    spawn.field10 = 0;
    spawn.color[0] = 0;
    spawn.color[1] = 0;
    spawn.color[2] = 0;
    spawn.color[3] = 0xFF;
    spawn.field18 = 0;
    spawn.field19 = 0;
    spawn.field1A = 0;
    spawn.mode = ((u8 *)&mode)[3];
    spawn.group = ((u8 *)&group)[3];
    spawn.position = *position;
    spawn.rotation[0] = 0.0f;
    spawn.rotation[1] = 0.0f;
    spawn.rotation[2] = 0.0f;
    spawn.direction = *direction;
    spawn.speed = speed;
    spawn.count = 1;
    spawn.scale = 1.0f;
    if (func_150ADA20() & 1) {
        first = 0x40;
    } else {
        first = 0;
    }
    if (func_150ADA20() & 1) {
        second = 0x80;
    } else {
        second = 0;
    }
    spawn.flags = second | 0xC207 | first | 0x10000;
    spawn.lifetime = ((s16 *)&lifetime)[1] + 0x12;
    spawn.field1E = 0x12;
    spawn.field20 = 0xE;
    spawn.channel0 = 6;
    spawn.channel1 = 8;
    spawn.channel2 = 0xF;
    spawn.channel3 = -1;
    spawn.channel4 = -1;
    spawn.channel5 = 3;
    fragment.random[0] = func_150ADA20();
    fragment.random[1] = func_150ADA20();
    spawn.kind = D_8008FCD0[((u8 *)&kind)[3]]();
    spawn.scaleY = scale;
    spawn.scaleX = scale;
    fragment.scale = scale;
    fragment.random[2] = func_150ADA20() % 6U + 5;
    fragment.random[3] = func_150ADA20() % 6U + 5;
    fragment.scaleX = (func_150ADA68() * 0.25f + D_800A80F4) * fragment.scale;
    fragment.scaleY = (func_150ADA68() * 0.25f + D_800A80F8) * fragment.scale;
    fragment.height = height;
    fragment.body = *body;
    fragment.kind = ((u8 *)&kind)[3];
    effect = func_15130374((s32)&spawn, 1, 0x28, ((u8 *)&priority)[3], owner);
    if (effect != 0) {
        func_10022EC0((u8 *)effect + 0xA8, &fragment, 0x28U);
    }
    return effect;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519203C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BF090/func_1519203C.s")
typedef struct {
    u8 pad_0[0x38];
    s32 field_38;
    s32 field_3C;
    u8 pad_40[0x68];
    s32 field_A8;
    s16 field_AC;
    s16 field_AE;
    s32 field_B0;
} Game1BF090State;

void func_15131C84(s16 *, s16 *, s32, s32 *, s32 *, s32 *);

s32 func_15192308(s32 arg0, s32 arg1) {
    Game1BF090State *state;

    state = (Game1BF090State *)arg0;
    func_15131C84(&state->field_AC, &state->field_AE, state->field_A8, &state->field_B0,
                  &state->field_38, &state->field_3C);
    return 1;
}
typedef struct Game1BF090FloatVector {
    f32 values[3];
} Game1BF090FloatVector;

typedef struct Game1BF090Emitter {
    f32 scale;
    u8 pad4[0xC];
    f32 height;
    u8 data[0x12];
    u8 kind;
} Game1BF090Emitter;

typedef struct Game1BF090Effect {
    u8 pad0;
    u8 group;
    u8 pad2[0xA];
    u8 mode;
    u8 padD[0x1E];
    u8 index;
    u8 pad2C[0x14];
    f32 position[3];
    u8 pad4C[0x5C];
    Game1BF090Emitter emitter;
} Game1BF090Effect;

void func_151D9B8C(u8, f32, s32, s32, f32 *, s32, s32, s32, s32, s32, s32);
void func_151DA6F8(f32 *, f32 *, f32, s16, s32, f32, s32, s32, f32, f32,
                  s32, s32, s32, s32, s32, s32, s32, s32);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_151436B4(f32, f32, f32, void *);
extern f32 D_800A80FC;
extern f32 D_800A8100;
extern f32 D_800A8104;
extern f32 D_800A8108;
extern f32 D_800A810C;
extern f32 D_800A8110;
extern f32 D_800A8114;
extern f32 D_800A8118;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15192358 CURRENT (130) */
s32 func_15192358(s32 arg0, s32 arg1) {
    u8 result;
    f32 factor;
    Game1BF090FloatVector position;
    Game1BF090FloatVector direction;
    f32 size_random;
    f32 speed_random;
    f32 angle_random;
    register u32 count_random;
    u32 duration_random;
    Game1BF090Emitter *emitter;

    result = 1;
    emitter = &((Game1BF090Effect *)arg0)->emitter;
    if (((Game1BF090Effect *)arg0)->position[1] < ((Game1BF090Effect *)arg0)->emitter.height) {
        result = 0;
        position.values[0] = ((Game1BF090Effect *)arg0)->position[0];
        position.values[1] = emitter->height + 2.0f;
        position.values[2] = ((Game1BF090Effect *)arg0)->position[2];
        func_151D9B8C(emitter->kind, emitter->scale * D_800A80FC,
                      ((Game1BF090Effect *)arg0)->index, (s32)emitter->data, (f32 *)&position,
                      100, 0, 1, 0, ((Game1BF090Effect *)arg0)->mode,
                      ((Game1BF090Effect *)arg0)->group);
        angle_random = func_150ADA68();
        speed_random = func_150ADA68();
        size_random = func_150ADA68();
        factor = D_800A8100;
        func_151436B4(angle_random * D_800A8104,
                      (speed_random * 1000.0f + D_800A8108) * factor,
                      (size_random * D_800A810C + D_800A8110) * factor,
                      &direction);
        size_random = func_150ADA68();
        duration_random = func_150ADA20();
        count_random = func_150ADA20();
        factor = 1.0f;
        func_151DA6F8((f32 *)&position, (f32 *)&direction, size_random * D_800A8114 + D_800A8114,
                      (s16)(duration_random % 21U + 35), ((Game1BF090Effect *)arg0)->index,
                      emitter->scale * D_800A8118, count_random % 7U + 5, 0,
                      factor, factor, 1, emitter->kind, 0, 0x10, 0xF, 0,
                      ((Game1BF090Effect *)arg0)->mode, ((Game1BF090Effect *)arg0)->group);
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15192358 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BF090/func_15192358.s")
s32 func_15192308(s32, s32);                        /* extern */
s32 func_15192358(s32, s32);                        /* extern */

s32 func_1519257C(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 var_v1;

    temp_v0 = func_15192308(arg0, arg1);
    var_v1 = temp_v0 & 0xFF;
    if (temp_v0 != 0) {
        var_v1 = func_15192358(arg0, arg1) & 0xFF;
    }
    return var_v1;
}
extern Game1BF090Vector D_800A8030[];
extern u8 D_800A8060[];
extern f32 D_800A8064[];
extern f32 D_800A8074[];
extern f32 D_800A8084[];
extern f32 D_800A8094[];
extern s16 D_800A80A4[];
extern s16 D_800A80AC[];
extern f32 D_800A80B4[];
extern f32 D_800A80C4[];
extern f32 D_800A80D4[];
extern u8 D_800A80E4[];

s32 func_15191BE0(u8 *, Game1BF090Vector *, s32, f32, f32, s16,
                  f32, f32, s16, s16, u8, u8, f32, f32, f32,
                  u8, u8, s32);

s32 func_151925C4(u8 *arg0, s16 arg1, u8 arg2, s32 arg3) {
    s32 kind;
    s32 result;
    u8 mode;

    if (arg0 == 0) {
        return 0;
    }
    kind = -1;
    result = 0;
    switch (arg0[4]) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        kind = 0;
        break;
    case 0x10:
        kind = 1;
        break;
    case 0x58:
        kind = 2;
        break;
    case 0x79:
        kind = 3;
        break;
    }
    if (kind != -1) {
        result = func_15191BE0(arg0, &D_800A8030[kind],
                               D_800A8060[kind], D_800A8064[kind],
                               D_800A8074[kind], arg1,
                               D_800A8084[kind], D_800A8094[kind],
                               D_800A80A4[kind], D_800A80AC[kind],
                               0x64, 0x9B, D_800A80B4[kind],
                               D_800A80C4[kind], D_800A80D4[kind],
                               D_800A80E4[kind], arg2, arg3);
    }
    return result;
}
void func_1519277C(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}
