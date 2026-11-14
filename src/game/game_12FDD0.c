#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_12FDD0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_directly_called_families.md
 */

typedef struct Game12FDD0Particle {
    s32 flags;
    s16 lifetime;
    u8 kind;
    u8 mode;
    s32 field8;
    s32 fieldC;
    u8 field10;
    u8 field11;
    u8 field12;
    u8 field13;
    u8 field14;
    u8 field15;
    u8 field16;
    u8 field17;
    s32 field18;
    u8 pad1C[6];
    s16 field22;
    s16 field24;
    u8 pad26[2];
} Game12FDD0Particle;

s32 func_1510F8CC(s32);
void *func_1513C650(s32, u8, u8, s32, f32, f32, f32, f32, f32,
    u8, u8, s32, s32, s32, u8, s32);
extern f32 D_800A2340;
extern s32 D_800BE9F0;

void *func_15102920(f32 arg0, u8 arg1, s32 arg2, f32 *arg3, s16 arg4, u8 arg5, u8 arg6, s32 arg7, u8 arg8, s32 arg9) {
    void *result;
    Game12FDD0Particle particle;
    s32 sp60;
    s32 sp5C;
    s32 temp_v0;

    particle.field22 = 0xA;
    particle.field24 = 0x19;
    temp_v0 = func_1510F8CC(arg7);
    particle.kind = 0x5C;
    switch (D_800BE9F0) {
    case 0x36:
        if (temp_v0 == 9) {
            return 0;
        }
        particle.kind = 0x85;
        arg0 *= D_800A2340;
        break;
    case 0x26:
        if (temp_v0 == 2) {
            return 0;
        }
        break;
    }
    particle.mode = 0;
    particle.flags = ((arg4 == -1) ? 0 : 1) | 0x100 | 0x200 | 0x400 | 0x1000 | 0x8000 | 0x20000;
    if (arg4 == -1) {
        particle.lifetime = 0x12C;
    } else {
        particle.lifetime = arg4;
    }
    particle.field8 = 0;
    particle.fieldC = 0;
    if (D_800BE9F0 == 0x36) {
        particle.field10 = (s32)arg1 >> 1;
    } else {
        particle.field10 = arg1;
    }
    particle.field11 = 0xFF;
    particle.field14 = 0;
    particle.field13 = 0;
    particle.field12 = 0;
    particle.field15 = 0xFF;
    particle.field18 = (arg6 ? 2 : 1) + 0x3B0000;
    particle.field16 = 0;
    particle.field17 = 7;
    if (arg5 != 0) {
        sp60 = 3;
        sp5C = 0xFF;
    } else {
        sp60 = 0;
        sp5C = 0;
    }
    result = func_1513C650((s32)&particle, 0, 0, arg2, arg3[0], arg3[1],
        arg3[2], arg0, arg0, func_150ADA20() & 0xFF,
        (func_150ADA20() & 1) + ((func_150ADA20() & 1) * 2), sp60, sp5C, 0,
        arg8, arg9);
    return result;
}

typedef struct Game12FDD0Object {
    u8 pad0[0x3B];
    u8 kind;
} Game12FDD0Object;

typedef struct Game12FDD0Copy3 {
    s32 words[3];
} Game12FDD0Copy3;

typedef struct Game12FDD0Copy2 {
    s32 words[2];
} Game12FDD0Copy2;

typedef struct Game12FDD0Extra {
    void *object;
    u8 object_kind;
    u8 pad5[3];
    s32 scaled_count;
    s16 fieldC;
    u8 padE[2];
    s32 count;
    u8 field14;
    u8 pad15[3];
    Game12FDD0Copy3 field18;
    Game12FDD0Copy3 field24;
} Game12FDD0Extra;

typedef struct Game12FDD0Effect {
    u8 kind;
    u8 mode;
    s16 flags;
    s16 lifetime;
    u8 pad6[2];
    s32 field8;
    s32 fieldC;
    u8 color[4];
    Game12FDD0Copy2 size;
    Game12FDD0Copy3 field1C;
    Game12FDD0Copy3 field28;
    f32 field34;
    f32 field38;
    f32 field3C;
    s32 field40;
    u8 field44;
    u8 field45;
    u8 field46;
    u8 field47;
    u8 pad48[4];
    u8 field4C;
    u8 pad4D[3];
    s32 field50;
    s16 field54;
    s16 field56;
} Game12FDD0Effect;

void *func_10022EC0(void *, const void *, u32);
void *func_1513D2F0(s32, s32, u8, u8, u8, u8, u8, s32, s32, s32, u8, s32);
void func_15103254(s32, s32, f32, s32, s32, s32, s32);
extern u8 D_800A4AA0;
extern s32 D_800A5480[3];

void *func_15102B38(Game12FDD0Object *arg0, u8 arg1, Game12FDD0Copy3 *arg2,
    Game12FDD0Copy3 *arg3, Game12FDD0Copy2 *arg4, s16 arg5, u8 arg6,
    f32 arg7, s32 arg8, u8 arg9, s32 arg10, s16 arg11, u8 arg12,
    s32 arg13) {
    void *result;
    Game12FDD0Effect effect;
    Game12FDD0Extra extra;

    if (arg0 == 0) {
        return 0;
    }
    extra.field14 = 0;
    extra.field18 = *(Game12FDD0Copy3 *)D_800A5480;
    extra.field24 = *(Game12FDD0Copy3 *)D_800A5480;
    extra.count = arg1;
    extra.object = arg0;
    extra.fieldC = arg11;
    extra.object_kind = arg0->kind;
    extra.scaled_count = arg1 << 6;
    effect.kind = 0x5F;
    effect.mode = 5;
    effect.flags = 0x2203;
    effect.lifetime = arg5;
    effect.field8 = 0;
    effect.fieldC = 0;
    effect.color[0] = 0xFF;
    effect.color[1] = 0xFF;
    effect.color[2] = 0xFF;
    effect.color[3] = 0xFF;
    effect.size = *arg4;
    effect.field1C = *arg2;
    effect.field28 = *arg3;
    effect.field40 = 0x40CC0009;
    effect.field34 = 0.0f;
    effect.field38 = 0.0f;
    effect.field3C = 0.0f;
    effect.field44 = arg6;
    effect.field45 = 0xFF;
    effect.field46 = 0;
    effect.field47 = 7;
    effect.field4C = arg9;
    result = func_1513D2F0((s32)&effect, (s32)&D_800A4AA0, 0x29, 0, 0,
        0x16, ((func_150ADA20() & 1) ? 2 : 0) + 1, 0, 0,
        arg10 + 0x30, arg12, arg13);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x110, &extra, 0x30);
    }
    func_15103254(arg5, arg6, arg7, arg8, arg9, arg12, arg13);
    return result;
}
