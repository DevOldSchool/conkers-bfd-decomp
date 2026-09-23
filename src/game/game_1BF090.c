#include "types.h"

/*
 * Reviewed source unit: src/game/game_1BF090.c
 * Boundary evidence: docs/evidence/game_raw_composite_emitter_timed_groups.md
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
void *func_15149130(s16, s8, s8, s8, u8, u8, s32, u8, s32);

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
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BF090/func_15191D54.s")
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
