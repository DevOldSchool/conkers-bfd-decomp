#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_2062D0.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151D8F30
 * - func_151D9014
 * - func_151D9534
 * - func_151D98D0
 * - func_151D9918
 * - func_151D9A20
 * - func_151D9B8C
 * - func_151D9FC0
 * - func_151DA08C
 * - func_151DA368
 * - func_151DA6F8
 * - func_151DA938
 * - func_151DAE28
 * - func_151DB5D0
 * - func_151DB97C
 * - func_151DBAA8
 * - func_151DBCBC
 * - func_151DBE80
 * - func_151DC034
 * - func_151DC260
 * - func_151DC484
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_150A29C8(s32 arg0, s32 arg1);
extern s32 D_800BE9F0;
extern u8 D_800E0A10;
extern u8 D_800AB344[];
extern s32 func_150ADA20();

u8 func_151D8E20(void) {
    if ((D_800BE9F0 == 0) && (func_150A29C8(0, 0x1C) == 0)) {
        return 0xA;
    }
    return D_800E0A10;
}
typedef struct {
    u8 field0;
    u8 field1;
    u8 field2;
} Func151D8E6CBytes;
extern Func151D8E6CBytes D_800AB340;
extern s32 func_150ADA20();

u8 func_151D8E6C(void) {
    Func151D8E6CBytes sp1C;

    sp1C = D_800AB340;
    return ((u8 *)&sp1C)[func_150ADA20() % 3U];
}
s32 func_151D8EB0(void) {
    return 0x75;
}
s32 func_151D8EBC(void) {
    return 0x1D;
}
s32 func_150ADA20();                                /* extern */

s32 func_151D8EC8(void) {
    s32 var_v1;

    if (func_150ADA20() & 1) {
        var_v1 = 0x11;
    } else {
        var_v1 = 0x93;
    }
    return var_v1 & 0xFF;
}
s32 func_151D8EFC(void) {
    s32 var_v1;

    if (func_150ADA20() & 1) {
        var_v1 = 0x5A;
    } else {
        var_v1 = 0x5B;
    }
    return var_v1 & 0xFF;
}
extern f32 D_800AB4B0;
extern s32  D_800BE9E4;
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D8F30 CURRENT (425) */
u8 func_151D8F30(void) {
    u8 sp20[8];
    u8 *temp_t7;

    temp_t7 = D_800AB344;
    *(s32 *)(sp20 + 0) = *(s32 *)(temp_t7 + 0);
    *(u8 *)(sp20 + 4) = *(u8 *)(temp_t7 + 4);
    return sp20[func_150ADA20() % 5U];
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D8F30 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D8F30.s")
s32 func_151D8F7C(void) {
    s32 var_v1;

    if (func_150ADA20() & 1) {
        var_v1 = 0x66;
    } else {
        var_v1 = 0x67;
    }
    return var_v1 & 0xFF;
}
s32 func_151D8FB0(void) {
    return 0x95;
}
s32 func_151D8FBC(void) {
    return 0x9F;
}
s32 func_151D8FC8(void) {
    return 0xB3;
}
s32 func_151D8FD4(void) {
    return 0x75;
}
extern s32 D_800AB34C;
s32 func_151D8FE0(void) {
    s32 sp1C;

    sp1C = D_800AB34C;
    return ((u8 *)&sp1C)[func_150ADA20() & 3];
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9014.s")
s32 func_151D9450(void *, void *);
s32 func_151D9534(s32, s32);                        /* extern */

s32 func_151D93F4(s32 arg0, s32 arg1) {
    s32 var_v1;

    if (func_151D9450((void *)arg0, (void *)arg1) != 0) {
        if (func_151D9534(arg0, arg1) != 0) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
    } else {
        var_v1 = 0;
    }
    return var_v1;
}
s32 func_151D9450(void *arg0, void *arg1) {
    typedef struct {
        f32 unk0;
        u8 unk4;
        u8 unk5;
        s8 unk6;
        s8 unk7;
        f32 unk8;
        f32 unkC;
    } Mid;
    typedef struct {
        u8 pad[0x38];
        f32 unk38;
        f32 unk3C;
        u8 pad40[0x68];
        Mid unkA8;
        u8 padB8[9];
        u8 unkC1;
    } Local;
    Mid *m;

    arg1 = arg0;
    m = &((Local *) arg1)->unkA8;
    if (((Local *) arg1)->unkC1 & 1) {
        return 1;
    }
    m->unk4 += m->unk6 * D_800BE9E4;
    m->unk5 += m->unk7 * D_800BE9E4;
    ((Local *) arg1)->unk38 = func_151423D8((u8) (m->unk4 - 0x40)) * m->unk8 + m->unk0;
    ((Local *) arg1)->unk3C = func_151423D8((u8) (m->unk5 - 0x40)) * m->unkC + m->unk0;
    return 1;
}
s32 func_1514672C(f32 *);
s32 func_15046C80(f32 *, u16, f32, void *);
void func_151D9B8C(u8, f32, s32, s32, f32 *, s32, s32, s32, s32, s32, s32);
void func_151D9FC0(u8, f32, u8, s32, f32 *, u8, s32);
f32 fabsf(f32);
#pragma intrinsic(fabsf)
extern f32 D_800AB44C, D_800AB450, D_800AB454, D_800AB458, D_800AB45C, D_800AB460;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D9534 CURRENT (2086) */
s32 func_151D9534(s32 arg0, s32 arg1) {
    volatile u8 active;
    f32 point[3];
    f32 average;
    f32 damping;
    u8 *actor;

    actor = (u8 *)arg0;
    active = 1;
    if (*(f32 *)(actor + 0x44) < *(f32 *)(arg1 + 4)) {
        point[0] = *(f32 *)(actor + 0x40);
        point[1] = *(f32 *)(arg1 + 4);
        point[2] = *(f32 *)(actor + 0x48);
        if (func_1514672C(point) == 0) return 0;
        if (func_15046C80(point, 0, *(f32 *)(actor + 0x44), actor + 0x80) != 0) {
            point[1] = *(f32 *)(actor + 0x80) + 2.0f;
            if (actor[0xC1] & 2) {
                damping = D_800AB44C;
                average = *(f32 *)(actor + 0x3C) * D_800AB450 + point[1];
                *(f32 *)(actor + 0x58) *= damping;
                *(f32 *)(actor + 0x44) = average;
                *(f32 *)(actor + 0x5C) *= D_800AB454;
                *(f32 *)(actor + 0x60) *= damping;
                if (fabsf(*(f32 *)(actor + 0x5C)) < D_800AB458) {
                    *(f32 *)(actor + 0x58) = 0.0f;
                    *(s32 *)(actor + 0x68) &= ~6;
                    *(f32 *)(actor + 0x5C) = 0.0f;
                    *(f32 *)(actor + 0x60) = 0.0f;
                    *(f32 *)(actor + 0x64) = 0.0f;
                }
            } else {
                active = 0;
                average = (*(f32 *)(actor + 0x38) + *(f32 *)(actor + 0x3C)) * 0.5f;
                arg1 = (s32)(actor + 0xA8);
                if (actor[0x9D] == 3) {
                    func_151D9FC0(*(u8 *)(arg1 + 0x18), *(f32 *)(arg1 + 0x14) * average,
                        actor[0x2B], (s32)(actor + 0x84), point, actor[0xC], actor[1]);
                } else if (func_150ADA20() & 1) {
                    arg1 = (s32)(actor + 0xA8);
                    func_151D9B8C(*(u8 *)(arg1 + 0x18), average * D_800AB45C * *(f32 *)(arg1 + 0x10),
                        actor[0x2B], (s32)(actor + 0x84), point, 0x64, 0, 1, 0, actor[0xC], actor[1]);
                } else {
                    arg1 = (s32)(actor + 0xA8);
                    func_151DAB58(*(u8 *)(arg1 + 0x18), average * D_800AB460 * *(f32 *)(arg1 + 0x10),
                        actor[0x2B], point, 1, actor[0xC], actor[1]);
                }
            }
        }
    }
    return active;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D9534 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9534.s")
typedef struct {
    u32 field_0;
    u32 field_4;
    u32 field_8;
    u32 field_C;
    u32 field_10;
    u32 field_14;
    u32 field_18;
} Game2062D0Septuple;

extern Game2062D0Septuple D_800AB350;

u8 func_151D97A8(void) {
    Game2062D0Septuple sp1C;

    sp1C = D_800AB350;
    return *((u8 *)&sp1C + ((func_150ADA20() % 7U) * 4) + 3);
}

typedef struct {
    u32 field_0;
    u32 field_4;
    u32 field_8;
} Game2062D0Triple;

typedef union {
    struct {
        u32 field_0;
        u32 field_4;
        u32 field_8;
        u32 field_C;
    } fields;
    u64 alignment;
} Game2062D0Quad;

extern Game2062D0Triple D_800AB36C;
extern Game2062D0Triple D_800AB378;
extern Game2062D0Triple D_800AB3A8;
extern Game2062D0Triple D_800AB3BC;
extern Game2062D0Triple D_800AB3CC;
extern Game2062D0Quad D_800AB3D8;

u8 func_151D9820(void) {
    Game2062D0Triple sp1C;

    sp1C = D_800AB36C;
    return *((u8 *)&sp1C + ((func_150ADA20() % 3U) * 4) + 3);
}
u8 func_151D9878(void) {
    Game2062D0Triple sp1C;

    sp1C = D_800AB378;
    return *((u8 *)&sp1C + ((func_150ADA20() % 3U) * 4) + 3);
}
extern s32 func_150ADA20();
typedef struct Game2062D0Pair {
    s32 values[2];
} Game2062D0Pair;

extern Game2062D0Pair D_800AB384;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D98D0 CURRENT (20) */
u8 func_151D98D0(void) {
    Game2062D0Pair sp20;

    sp20 = D_800AB384;
    return ((u8 *)sp20.values)[(func_150ADA20() & 1) * 4 + 3];
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D98D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D98D0.s")
extern s32 func_150ADA20();
extern Game2062D0Pair D_800AB38C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D9918 CURRENT (20) */
u8 func_151D9918(void) {
    Game2062D0Pair sp20;

    sp20 = D_800AB38C;
    return ((u8 *)sp20.values)[(func_150ADA20() & 1) * 4 + 3];
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D9918 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9918.s")
typedef struct Game2062D0Quint {
    u32 field_0;
    u32 field_4;
    u32 field_8;
    u32 field_C;
    u32 field_10;
} Game2062D0Quint;

extern Game2062D0Quint D_800AB394;

u8 func_151D9960(void) {
    Game2062D0Quint sp1C;

    sp1C = D_800AB394;
    return *((u8 *)&sp1C + ((func_150ADA20() % 5U) * 4) + 3);
}
u8 func_151D99C8(void) {
    Game2062D0Triple sp1C;

    sp1C = D_800AB3A8;
    return *((u8 *)&sp1C + ((func_150ADA20() % 3U) * 4) + 3);
}
extern s32 func_150ADA20();
extern s32 D_800AB3B4[2];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D9A20 CURRENT (245) */
u8 func_151D9A20(void) {
    struct {
        u8 pad[8];
        s32 values[2];
    } sp20;

    sp20.values[0] = D_800AB3B4[0];
    sp20.values[1] = D_800AB3B4[1];
    return ((u8 *)sp20.values)[(func_150ADA20() & 1) * 4 + 3];
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D9A20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9A20.s")
u8 func_151D9A68(void) {
    Game2062D0Triple sp1C;

    sp1C = D_800AB3BC;
    return *((u8 *)&sp1C + ((func_150ADA20() % 3U) * 4) + 3);
}
typedef union Game2062D0Word {
    s32 value;
    u8 bytes[4];
} Game2062D0Word;

extern s32 D_800AB3C8;

u8 func_151D9AC0(void) {
    Game2062D0Word word;

    word.value = D_800AB3C8;
    return word.bytes[3];
}
u8 func_151D9ADC(void) {
    Game2062D0Triple sp1C;

    sp1C = D_800AB3CC;
    return *((u8 *)&sp1C + ((func_150ADA20() % 3U) * 4) + 3);
}
u8 func_151D9B34(void) {
    Game2062D0Quad sp20;
    s32 pad;

    sp20 = D_800AB3D8;
    return *((u8 *)&sp20 + ((func_150ADA20() & 3) * 4) + 3);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9B8C.s")
f32 func_150ADA68(void);
void func_151D9014(f32 *, f32 *, s32, f32, s32, s32, f32, s32, f32,
                   f32, s32, s32, s32, s32, s32, s32);
extern f32 D_800A5480;
extern f32 D_800AB464;
extern f32 D_800AB468;

void func_151D9EB0(u8 *arg0) {
    u8 *temp_v1;

    *(s16 *)(arg0 + 0x28) =
        (s16)(*(s16 *)(arg0 + 0x28) - D_800BE9E4);
    if (*(s16 *)(arg0 + 0x28) < 0) {
        temp_v1 = arg0 + 0x28;
        func_151D9014((f32 *)(temp_v1 + 8), &D_800A5480,
                       (s32)temp_v1[0x16],
                       (func_150ADA68() * D_800AB464) + D_800AB468,
                       (func_150ADA20() % 41U) + 0x23,
                       (s32)temp_v1[0x14], *(f32 *)(temp_v1 + 4), 0,
                       1.0f, 1.0f, (s32)temp_v1[0x15], 0, 1, 0,
                       (s32)arg0[0xC], (s32)arg0[1]);
        *(s16 *)temp_v1 =
            (s16)((func_150ADA20() % 111U) + 0x1E);
    }
}
void func_151DBCBC(s32, f32, s32, s32, f32 *, s32, s32);
void func_151DA08C(u8, f32, s32, u8, s32, s32, f32 *, s32, s32);
extern f32 D_800AB46C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D9FC0 CURRENT (1544) */
void func_151D9FC0(u8 arg0, f32 arg1, u8 arg2, s32 arg3, f32 *arg4,
                   u8 arg5, s32 arg6) {
    register u8 kind;

    kind = arg0 & 0xFF;
    arg0 = kind;
    func_151DBCBC(kind, arg1 * 0.5f, arg2, arg3, arg4, (s32)arg5,
                  arg6);
    if ((arg0 != 5) && (arg0 != 2)) {
        func_151DA08C(arg0, arg1 * D_800AB46C, 0x3F8147AE, arg2, 0x64,
                      arg3, arg4, (s32)arg5, arg6);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D9FC0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151D9FC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DA08C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DA368.s")

s32 func_151DA6A8(u8 *arg0) {
    s32 var_v1;
    u8 *temp_v0;

    if (*(s32 *)((u8 *)arg0 + 0x58) & 1) {
        temp_v0 = (void *)(arg0 + 0x128);
        var_v1 = D_800BE9E4;
        while (var_v1--) {
            *(f32 *)((u8 *)temp_v0 + 0x10) *= *(f32 *)((u8 *)temp_v0 + 0x14);
        }
    }
    return 1;
}
typedef struct {
    s32 words[3];
} Game2062D0Vector3;

typedef struct {
    Game2062D0Vector3 position;
    s16 lifetime, kind;
    s32 enabled;
    s8 mode, variant;
    u8 pad16[2];
    s32 field18;
} Game1DA6F8Descriptor;

typedef struct {
    f32 magnitude;
    Game2062D0Vector3 vector;
    f32 scale, decay;
    u8 flags, mode, alpha, variant;
    s16 field1C, field1E;
} Game1DA6F8Config;

typedef struct {
    f32 scaleX, scaleY;
    u8 kind;
    u8 pad9[3];
} Game1DA6F8Extension;

typedef struct {
    s32 words[7];
    u8 field1C, field1D;
    u8 pad1E[2];
} Game1DA6F8Preset;

typedef struct {
    u8 pad0[0x98];
    u8 *data;
} Game1DA6F8Object;

void *func_10022EC0(void *, const void *, u32);
extern u8 D_800AB3F4[], D_800AB404[], D_800AB330[];
extern f32 D_800AB498;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DA6F8 CURRENT (3065) */
void *func_151DA6F8(Game2062D0Vector3 *arg0, Game2062D0Vector3 *arg1,
                    f32 arg2, s16 arg3, u8 arg4, f32 arg5, s32 arg6,
                    u8 arg7, f32 arg8, f32 arg9, u8 arg10, u8 arg11,
                    void *arg12, s16 arg13, s16 arg14, s32 arg15,
                    u8 arg16, s32 arg17) {
    Game1DA6F8Object *saved;
    Game1DA6F8Descriptor descriptor;
    Game1DA6F8Config config;
    Game1DA6F8Extension extension;
    s32 mode0;
    s32 mode1;
    s32 flagA;
    s32 flagB;
    Game1DA6F8Preset preset;
    register s32 flags;
    Game1DA6F8Object *result;

    descriptor.variant = arg6;
    descriptor.position = *arg0;
    descriptor.lifetime = arg3 + 0x10;
    descriptor.kind = 0x35;
    descriptor.enabled = 1;
    descriptor.mode = -1;
    descriptor.field18 = arg15;
    config.magnitude = arg5;
    config.vector = *arg1;
    config.scale = arg2;
    config.decay = D_800AB498;
    flagA = D_800AB404[arg11] != 0 ? 0x20 : 0;
    flagB = D_800AB330[arg11] != 0 ? 0x80 : 0;
    flags = (flagB | 8 | flagA | 0x40) & 0xFF;
    config.alpha = 0xFF;
    config.mode = D_800AB3F4[arg11];
    config.variant = arg4;
    config.field1C = arg13;
    config.field1E = arg14;
    if (arg7 != 0) {
        mode0 = 7;
        config.flags = flags | 3;
        mode1 = 4;
    } else {
        config.flags = flags;
        mode0 = 0;
        mode1 = 0;
    }
    extension.kind = arg11;
    extension.scaleX = arg8;
    extension.scaleY = arg9;
    preset.words[0] = 0;
    preset.words[1] = 0x220005;
    preset.words[2] = 0x50600;
    preset.words[3] = 3;
    preset.words[4] = 0x46;
    preset.words[5] = 0x80;
    preset.words[6] = 0x20;
    preset.field1C = 0;
    preset.field1D = 0xC;
    if (arg10 != 0) {
        flagB = 2;
        flagA = 0xFF;
    } else {
        flagB = 0;
        flagA = 0;
    }
    result = func_15147DA0(&descriptor, &config, 0x10, 1, 0, 0,
                           mode0, mode1, 0, flagB, flagA, &preset,
                           arg12, arg16, arg17);
    if (result != 0) {
        saved = result;
        func_10022EC0(result->data + 0x48, &extension, 0xC);
        result = saved;
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151DA6F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DA6F8.s")

void func_151D9B8C(u8, f32, s32, s32, f32 *, s32, s32, s32, s32, s32, s32);
extern f32 D_800AB49C;
typedef struct {
    f32 x;
    u8 pad4[4];
    f32 z;
    u8 padC[8];
} Game2062D0Position;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DA938 CURRENT (1578) */
s32 func_151DA938(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4,
                   s32 arg5) {
    f32 position[3];
    Game2062D0Position *base;
    u8 *effect;

    base = *(Game2062D0Position **)(arg0 + 0x94);
    effect = *(u8 **)(arg0 + 0x98);
    position[0] = base[*(s8 *)(arg0 + 0x2D)].x;
    position[1] = arg4 + 2.0f;
    position[2] = base[*(s8 *)(arg0 + 0x2D)].z;
    if (func_150ADA20() & 1) {
        func_151D9B8C(effect[0x50], *(f32 *)(effect + 0x48) * (*(f32 *)effect * 3.0f),
                       effect[0x1B], arg5, position, 0x64, 0, 1, 0,
                       arg0[0xC], arg0[1]);
    } else {
        func_151DAB58(effect[0x50], *(f32 *)(effect + 0x48) * (*(f32 *)effect * D_800AB49C),
                       effect[0x1B], position, 1, arg0[0xC], arg0[1]);
    }
    *(s8 *)(effect + 0x20) = 4;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151DA938 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DA938.s")
void func_151D9FC0(u8, f32, u8, s32, f32 *, u8, s32);

s32 func_151DAA88(void *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4,
                  s32 arg5) {
    typedef struct {
        f32 field_0;
        u8 pad_4[4];
        f32 field_8;
        u8 pad_C[8];
    } Entry;
    u8 *state;
    Entry *table;
    f32 position[3];

    table = *(Entry **)((u8 *)arg0 + 0x94);
    state = *(u8 **)((u8 *)arg0 + 0x98);
    position[0] = table[*(s8 *)((u8 *)arg0 + 0x2D)].field_0;
    position[1] = arg4;
    position[2] = table[*(s8 *)((u8 *)arg0 + 0x2D)].field_8;
    func_151D9FC0(state[0x50], *(f32 *)(state + 0x4C) *
                    (*(f32 *)state * 11.0f), state[0x1B], arg5, position,
                    *(u8 *)((u8 *)arg0 + 0xC), *(u8 *)((u8 *)arg0 + 1));
    state[0x20] = 4;
    return 1;
}
typedef struct Game1DAB58Packet {
    u8 kind, mode;
    s16 flags;
    s16 lifetime;
    u8 pad6[2];
    s32 field8, fieldC;
    u8 color[4];
    f32 scaleX, scaleY;
    Game2062D0Vector3 position;
    f32 direction[3];
    f32 scale[3];
    s32 field40;
    u8 variant, alpha, field46, field47;
    s32 field48;
    u8 field4C;
    u8 pad4D[3];
    s32 field50;
    s16 field54, field56;
} Game1DAB58Packet;

typedef struct Game1DAB58Extension {
    u8 phase, step;
    u8 pad2[2];
    f32 scaleX, scaleY;
} Game1DAB58Extension;

extern s32 (*D_8008FCD0[])(void);
extern u8 D_800A4AA0[0x28];
extern f32 D_800AB4A0, D_800AB4A4, D_800AB4A8, D_800AB4AC;
void *func_1513D2F0(void *, void *, u8, u8, u8, u8, u8, s32, s32, s32, u8, s32);

void func_151DAB58(u8 arg0, f32 arg1, u8 arg2, f32 *arg3, s32 arg4, u8 arg5, s32 arg6) {
    s32 resource;
    Game1DAB58Packet packet;
    Game1DAB58Extension extension;
    s32 mode;
    s32 flags;
    register u8 *effect;

    packet.kind = D_8008FCD0[arg0]();
    if (((u8 *)&arg4)[3] != 0) {
        mode = 0x3B;
    } else {
        mode = 0x22;
    }
    packet.flags = (mode << 8) + 3;
    packet.lifetime = 0x64;
    packet.color[2] = 0;
    packet.color[1] = 0;
    packet.color[0] = 0;
    packet.color[3] = 0xFF;
    packet.variant = arg2;
    packet.alpha = 0xFF;
    packet.position = *(Game2062D0Vector3 *)arg3;
    if (D_800AB330[arg0] != 0) {
        mode = 0x40000000;
    } else {
        mode = 0;
    }
    packet.field40 = mode | 0x0CDC0009;
    packet.direction[0] = 0.0f;
    packet.direction[1] = 0.0f;
    packet.direction[2] = 0.0f;
    packet.scale[0] = 1.0f;
    packet.scale[1] = 1.0f;
    packet.scale[2] = 1.0f;
    packet.field8 = 0;
    packet.fieldC = 0;
    packet.scaleY = arg1;
    packet.scaleX = arg1;
    packet.field46 = 0;
    packet.field47 = 7;
    extension.phase = 0;
    extension.step = (func_150ADA20() % 3U) + 6;
    extension.scaleX = func_150ADA68() * D_800AB4A0 + D_800AB4A4;
    extension.scaleY = func_150ADA68() * D_800AB4A8 + D_800AB4AC;
    packet.mode = 0;
    packet.field48 = 0;
    packet.field4C = 0xFF;
    packet.field50 = 0;
    packet.field54 = 0x20;
    packet.field56 = 7;
    if (func_150ADA20() & 1) {
        flags = 1;
    } else {
        flags = 0;
    }
    mode = (u8)arg4;
    if (mode != 0) {
        resource = 3;
    } else {
        resource = 0;
    }
    if (mode != 0) {
        mode = 0xFF;
    } else {
        mode = 0;
    }
    effect = func_1513D2F0(&packet, D_800A4AA0, 0, 0x14, 0, 0xE,
                           flags | 2, resource, mode, 0xC, (u8)arg5, arg6);
    if (effect != 0) {
        func_10022EC0(effect + 0x110, &extension, 0xC);
    }
}
/* Call context: func_151423D8: unique active project prototype */

s32 func_151DADA0(void *arg0) {
    typedef struct {
        u8 unk0;
        s8 unk1;
        u8 pad2[0x2];
        f32 unk4;
        f32 unk8;
    } Mid;
    typedef struct {
        u8 pad[0x4C];
        f32 unk4C;
        f32 unk50;
        u8 pad54[0xBC];
        Mid unk110;
    } Local;
    Local *a = arg0;
    Mid *m = &a->unk110;
    f32 s;

    s = func_151423D8((u8)((m->unk0 += m->unk1 * D_800BE9E4) - 0x40));
    a->unk4C = m->unk4 * s + 1.0f;
    a->unk50 = D_800AB4B0 - m->unk8 * s;
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DAE28.s")
void func_151DB004(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x14) = (s8) ((func_150ADA20() % 56U) + 0x50);
    *(s8 *)((u8 *)arg0 + 0x15) = 0;
    *(s8 *)((u8 *)arg0 + 0x16) = 0;
    *(s8 *)((u8 *)arg0 + 0x18) = (s8) ((func_150ADA20(arg0) % 46U) + 0xB4);
    *(s8 *)((u8 *)arg0 + 0x19) = 0;
    *(s8 *)((u8 *)arg0 + 0x1A) = 0;
}
void func_151DB068(void *arg0) {
    s8 temp_v1;
    s8 temp_v1_2;

    temp_v1 = (func_150ADA20() % 56U) + 0x64;
    *(s8 *)((u8 *)arg0 + 0x15) = temp_v1;
    *(s8 *)((u8 *)arg0 + 0x14) = temp_v1;
    *(s8 *)((u8 *)arg0 + 0x16) = 0;
    temp_v1_2 = (func_150ADA20(arg0) % 46U) + 0xB4;
    *(s8 *)((u8 *)arg0 + 0x19) = temp_v1_2;
    *(s8 *)((u8 *)arg0 + 0x18) = temp_v1_2;
    *(s8 *)((u8 *)arg0 + 0x1A) = 0;
}
void func_151DB0CC(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x14) = (s8) ((func_150ADA20() % 56U) + 0x50);
    *(s8 *)((u8 *)arg0 + 0x15) = (s8) ((func_150ADA20() % 56U) + 0x50);
    *(s8 *)((u8 *)arg0 + 0x16) = 0;
    *(s8 *)((u8 *)arg0 + 0x18) = (s8) ((func_150ADA20() % 46U) + 0xB4);
    *(s8 *)((u8 *)arg0 + 0x19) = (s8) ((func_150ADA20() % 46U) + 0xB4);
    *(s8 *)((u8 *)arg0 + 0x1A) = 0;
}
void func_151DB15C(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x14) = (s8) ((func_150ADA20() % 56U) + 0x50);
    *(s8 *)((u8 *)arg0 + 0x15) = (s8) ((func_150ADA20() % 56U) + 0x50);
    *(s8 *)((u8 *)arg0 + 0x16) = 0;
    *(s8 *)((u8 *)arg0 + 0x18) = (s8) ((func_150ADA20() % 46U) + 0xB4);
    *(s8 *)((u8 *)arg0 + 0x19) = (s8) ((func_150ADA20() % 46U) + 0xB4);
    *(s8 *)((u8 *)arg0 + 0x1A) = 0;
}
void func_151DB1EC(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x14) = (s8) ((func_150ADA20() % 56U) + 0x50);
    *(s8 *)((u8 *)arg0 + 0x15) = (s8) ((func_150ADA20() % 56U) + 0x50);
    *(s8 *)((u8 *)arg0 + 0x16) = 0;
    *(s8 *)((u8 *)arg0 + 0x18) = (s8) ((func_150ADA20() % 46U) + 0xB4);
    *(s8 *)((u8 *)arg0 + 0x19) = (s8) ((func_150ADA20() % 46U) + 0xB4);
    *(s8 *)((u8 *)arg0 + 0x1A) = 0;
}
void func_151DB27C(void *arg0) {
    *(u8 *)((u8 *)arg0 + 0x14) = 0xFF;
    *(u8 *)((u8 *)arg0 + 0x15) = 0xFF;
    *(u8 *)((u8 *)arg0 + 0x16) = 0xFF;
    *(u8 *)((u8 *)arg0 + 0x18) = 0xB4;
    *(u8 *)((u8 *)arg0 + 0x19) = 0xC8;
    *(u8 *)((u8 *)arg0 + 0x1A) = 0xC8;
}
void func_151DB2A8(void *arg0) {
    *(u8 *)((u8 *)arg0 + 0x14) = 0;
    *(u8 *)((u8 *)arg0 + 0x15) = 0xC8;
    *(u8 *)((u8 *)arg0 + 0x16) = 0;
    *(u8 *)((u8 *)arg0 + 0x18) = 0;
    *(u8 *)((u8 *)arg0 + 0x19) = 0xC8;
    *(u8 *)((u8 *)arg0 + 0x1A) = 0;
}
void func_151DB2CC(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x14) = 0;
    *(s8 *)((u8 *)arg0 + 0x15) = (s8) ((func_150ADA20() % 56U) + 0x50);
    *(s8 *)((u8 *)arg0 + 0x16) = 0;
    *(s8 *)((u8 *)arg0 + 0x18) = 0;
    *(s8 *)((u8 *)arg0 + 0x19) = (s8) ((func_150ADA20(arg0) % 46U) + 0xB4);
    *(s8 *)((u8 *)arg0 + 0x1A) = 0;
}
void func_151DB330(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x14) = (s8) ((func_150ADA20() % 21U) + 0x5F);
    *(s8 *)((u8 *)arg0 + 0x15) = (s8) ((func_150ADA20() % 21U) + 0x5F);
    *(s8 *)((u8 *)arg0 + 0x16) = (s8) ((func_150ADA20() % 11U) + 0x2D);
    *(s8 *)((u8 *)arg0 + 0x18) = (s8) ((func_150ADA20() & 0xF) + 0x3A);
    *(s8 *)((u8 *)arg0 + 0x19) = (s8) ((func_150ADA20() & 0xF) + 0x3C);
    *(s8 *)((u8 *)arg0 + 0x1A) = (s8) ((func_150ADA20() % 11U) + 0x19);
}
void func_151DB3D8(void *arg0) {
    s8 temp_v1;
    s8 temp_v1_2;

    *(s8 *)((u8 *)arg0 + 0x14) = 0;
    temp_v1 = (func_150ADA20() % 56U) + 0x50;
    *(s8 *)((u8 *)arg0 + 0x16) = temp_v1;
    *(s8 *)((u8 *)arg0 + 0x15) = temp_v1;
    *(s8 *)((u8 *)arg0 + 0x18) = 0;
    temp_v1_2 = (func_150ADA20(arg0) % 46U) + 0xB4;
    *(s8 *)((u8 *)arg0 + 0x1A) = temp_v1_2;
    *(s8 *)((u8 *)arg0 + 0x19) = temp_v1_2;
}
void func_151DB43C(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x14) = (s8) ((func_150ADA20() % 56U) + 0x50);
    *(s8 *)((u8 *)arg0 + 0x15) = 0;
    *(s8 *)((u8 *)arg0 + 0x16) = (s8) ((func_150ADA20() % 56U) + 0x50);
    *(s8 *)((u8 *)arg0 + 0x18) = (s8) ((func_150ADA20() % 46U) + 0xB4);
    *(s8 *)((u8 *)arg0 + 0x19) = 0;
    *(s8 *)((u8 *)arg0 + 0x1A) = (s8) ((func_150ADA20() % 46U) + 0xB4);
}
void func_151DB4CC(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x14) = (s8) ((func_150ADA20() % 56U) + 0xC8);
    *(s8 *)((u8 *)arg0 + 0x15) = (s8) ((func_150ADA20() % 56U) + 0xC8);
    *(s8 *)((u8 *)arg0 + 0x16) = (s8) ((func_150ADA20() % 56U) + 0xC8);
    *(s8 *)((u8 *)arg0 + 0x18) = (s8) ((func_150ADA20() % 56U) + 0xC8);
    *(s8 *)((u8 *)arg0 + 0x19) = (s8) ((func_150ADA20() % 56U) + 0xC8);
    *(s8 *)((u8 *)arg0 + 0x1A) = (s8) ((func_150ADA20() % 56U) + 0xC8);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DB5D0.s")
/* Call context: func_15131918: unique active project prototype */
/* Call context: func_151423D8: unique active project prototype */
void func_15131918(void *, f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DB97C CURRENT (680) */
s32 func_151DB97C(u8 *arg0, s32 arg1) {
    f32 temp_fv0;
    u8 *temp_s0;
    f32 sp24;
    f32 sp20;

    if (*(u8 *)((u8 *)arg0 + 0xA8) & 2) {
        func_15131918(arg0 + 0x58, *(f32 *)((u8 *)arg0 + 0xAC));
    }
    temp_s0 = (void *)(arg0 + 0xA8);
    if (*(volatile u8 *)temp_s0 & 1) {
        temp_s0[8] += temp_s0[0xB] * D_800BE9E4;
        temp_s0[9] += temp_s0[0xC] * D_800BE9E4;
        temp_s0[0xA] += temp_s0[0xD] * D_800BE9E4;
        sp20 = func_151423D8((*(u8 *)((u8 *)temp_s0 + 8) - 0x40));
        sp24 = func_151423D8((*(u8 *)((u8 *)temp_s0 + 9) - 0x40));
        temp_fv0 = func_151423D8((*(u8 *)((u8 *)temp_s0 + 0xA) - 0x40));
        *(f32 *)((u8 *)arg0 + 0x4C) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x10) * sp20);
        *(f32 *)((u8 *)arg0 + 0x50) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x14) * sp24);
        *(f32 *)((u8 *)arg0 + 0x54) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x18) * temp_fv0);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151DB97C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DB97C.s")

typedef struct {
    s16 field24;
    s16 field26;
    s16 field28;
    s16 field2A;
    Game2062D0Vector3 vector;
    f32 field38;
    f32 field3C;
    f32 field40;
    f32 field44;
    f32 field48;
    f32 field4C;
    s16 field50;
    s16 field52;
    s16 field54;
    s16 field56;
    s16 field58;
    s16 field5A;
    s16 field5C;
    s16 field5E;
    u8 field60;
    u8 pad61[3];
    f32 field64;
    s16 field68;
    s16 field6A;
    s32 field6C;
} Game2062D0Params;

void func_15153F18(s16 *, void *, s32, s32, s32);
extern f32 D_800AB4C0;
extern f32 D_800AB4C4;
extern f32 D_800AB4C8;
extern f32 D_800AB4CC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DBAA8 CURRENT (630) */
void func_151DBAA8(Game2062D0Vector3 *arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4) {
    Game2062D0Params params;

    params.vector = *arg0;
    params.field50 = (s16) arg1;
    params.field26 = 0xFF;
    params.field28 = -0x40;
    params.field2A = 0x2E;
    params.field38 = 5.5f;
    params.field52 = 0;
    params.field24 = 0;
    params.field54 = 3;
    params.field56 = 2;
    params.field58 = 0x1E;
    params.field5A = 0x1E;
    params.field5C = 0x9B;
    params.field5E = 0x64;
    params.field68 = 0x10;
    params.field6A = 0xF;
    params.field6C = 0;
    params.field3C = D_800AB4C0;
    params.field40 = D_800AB4C4;
    params.field44 = D_800AB4C8;
    params.field48 = 10.0f;
    params.field4C = D_800AB4CC;
    params.field64 = 0.5f;
    params.field60 = arg2;
    func_15153F18(&params.field24, &params.vector, 0, arg3, arg4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151DBAA8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DBAA8.s")
f32 func_150ADA68(void);
void func_151D9B8C(u8, f32, s32, s32, f32 *, s32, s32, s32, s32, s32, s32);

typedef struct {
    f32 random_f;
    s32 random_i;
    u8 pad_8[7];
    u8 type;
    f32 position[3];
} Game2062D0Spawn;

void func_151DBBD4(f32 *arg0, s32 arg1, u8 *arg2, u8 arg3, s32 arg4) {
    Game2062D0Spawn spawn;

    spawn.position[0] = arg0[0];
    spawn.position[1] = arg0[1] + 5.0f;
    spawn.position[2] = arg0[2];
    spawn.type = *arg2;
    spawn.random_f = func_150ADA68();
    spawn.random_i = func_150ADA20();
    func_151D9B8C(
        spawn.type,
        (spawn.random_f * 25.0f) + 10.0f,
        ((spawn.random_i % 56U) + 0xC8) & 0xFF,
        arg1 + 4,
        spawn.position,
        (func_150ADA20() % 151U) + 0x96,
        0,
        1,
        0,
        arg3,
        arg4);
}
typedef struct Game1DBE80Color {
    u8 r;
    u8 g;
    u8 b;
} Game1DBE80Color;
extern Game1DBE80Color D_800AB414[];

typedef struct Game1DBCBCPacket {
    s32 flags;
    s16 duration;
    u8 type, mode;
    s32 field8, fieldC;
    u8 selector, alpha, red, green, blue, flag15, flag16, flag17;
    s32 field18, field1C;
    u8 field20;
    s16 field22, field24;
} Game1DBCBCPacket;

void *func_1513C5B0(s32, s32, u8, u8, f32, f32, f32, f32, f32, u8, u8, s32, u8, s32);
void *func_1513C73C(s32, u8, u8, s32, f32, f32, f32, f32, f32, u8, u8, s32, u8, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DBCBC CURRENT (3624) */
void func_151DBCBC(s32 arg0, f32 arg1, s32 arg2, s32 arg3, f32 *arg4, s32 arg5, s32 arg6) {
    Game1DBCBCPacket packet;
    s32 random1;
    s32 random2;
    Game1DBE80Color *color;

    arg0 &= 0xFF;
    arg2 = (s16)arg2;
    color = &D_800AB414[arg0];
    packet.fieldC = 0x8000;
    packet.type = 0x38;
    packet.flags = 0x67B02;
    packet.duration = 0x12C;
    packet.field8 = 0;
    packet.selector = arg2;
    packet.alpha = 0xFF;
    packet.flag15 = 0xFF;
    packet.field18 = 0x440001;
    packet.mode = 0;
    packet.flag16 = 0;
    packet.flag17 = 6;
    packet.field22 = 1;
    packet.field24 = 0xFF;
    packet.field20 = 0xFF;
    packet.field1C = 0;
    packet.red = color->r;
    packet.green = color->g;
    packet.blue = color->b;
    if (arg3 != 0) {
        random1 = func_150ADA20();
        random2 = func_150ADA20();
        func_1513C73C((s32)&packet, 0, 0, arg3,
                       arg4[0], arg4[1], arg4[2], arg1, arg1,
                       random1 & 0xFF, ((func_150ADA20() & 1) * 2) + (random2 & 1),
                       0, (u8)arg5, arg6);
        return;
    }
    func_1513C5B0((s32)&packet, 0, 0, 0, arg4[0], arg4[1], arg4[2],
                   arg1, arg1, 0, 0, 0, (u8)arg5, arg6);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151DBCBC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DBCBC.s")


typedef struct Game1DBE80Packet {
    s8 type;
    s8 mode;
    s16 flags;
    s16 duration;
    u8 pad6[2];
    s32 field8;
    s32 fieldC;
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
    f32 scaleX;
    f32 scaleY;
    s32 position[3];
    f32 field28;
    f32 field2C;
    f32 field30;
    f32 magnitude;
    f32 field38;
    f32 field3C;
    s32 field40;
    u8 selector;
    u8 flag45;
    u8 flag46;
    u8 flag47;
    s32 field48;
    u8 field4C;
    u8 pad4D[3];
    s32 field50;
    s16 field54;
    s16 field56;
} Game1DBE80Packet;

void func_1513D668(s32, s32, s32, s32, u8, u8, s16, f32, f32,
                   s32, s32, u8, s32, u8, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DBE80 CURRENT (898) */
void func_151DBE80(s32 arg0, f32 arg1, f32 arg2, s16 arg3, s32 *arg4,
                    s32 arg5, u8 arg6, u8 arg7, u8 arg8, s32 arg9) {
    typedef struct { s32 words[3]; } Copy3;
    Game1DBE80Packet packet;
    s32 random1;
    s32 random2;

    arg0 &= 0xFF;
    packet.type = 0x38;
    packet.flags = (arg7 != 0 ? 2 : 1) + 0x440000;
    packet.duration = arg3;
    packet.field8 = 0;
    packet.fieldC = 0x4000;
    packet.alpha = 0xFF;
    packet.red = D_800AB414[arg0].r;
    packet.green = D_800AB414[arg0].g;
    packet.blue = D_800AB414[arg0].b;
    packet.scaleX = 1.0f;
    packet.scaleY = 1.0f;
    *(Copy3 *)packet.position = *(Copy3 *)arg4;
    packet.magnitude = arg2;
    packet.field40 = 0x466C0001;
    packet.flag45 = 0xFF;
    packet.mode = 0;
    packet.flag46 = 0;
    packet.flag47 = 6;
    packet.field48 = 0;
    packet.field4C = 0xFF;
    packet.field50 = 0;
    packet.field54 = 1;
    packet.field56 = 0xFF;
    packet.field38 = 1.0f;
    packet.field3C = 1.0f;
    packet.field28 = 0.0f;
    packet.field2C = 0.0f;
    packet.field30 = 0.0f;
    packet.selector = arg6;
    random1 = func_150ADA20();
    random2 = func_150ADA20();
    func_1513D668((s32)&packet, 0, 0xB, 0x11, 0,
                   (random2 & 1) + (random1 & 1),
                   func_150ADA20() & 0xFF, arg1, arg1, 0, arg5,
                   0, 0, arg8, arg9);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151DBE80 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DBE80.s")
typedef struct {
    s32 field00;
    s32 field04;
    s16 field08;
    s16 field0A;
    s32 field0C;
    s32 field10;
    u8 field14, field15, field16, field17;
    u8 field18, field19, field1A, field1B, field1C, field1D;
    s16 field1E, field20, field22;
    f32 field24, scaleY, scaleX;
    Game2062D0Vector3 position;
    Game2062D0Vector3 vector3C;
    Game2062D0Vector3 vector48;
    f32 field54;
    s32 flags;
    s32 field5C;
    s8 field60, field61, field62, field63, field64, field65;
    u8 field66;
    u8 pad67;
    s16 field68;
    u8 pad6A[2];
    f32 field6C;
} Game1DC034Packet;

extern u8 D_800AB320[];
extern u8 D_800AB330[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DC034 CURRENT (125) */
void func_151DC034(Game2062D0Vector3 *arg0, f32 arg1, u8 arg2,
                   s16 arg3, u8 arg4, u8 arg5, s32 arg6) {
    Game1DC034Packet packet;
    s32 random2;
    s32 flags;
    register s32 random1;

    packet.field1D = D_800AB320[arg4];
    packet.field08 = 0x4403;
    packet.field00 = 0x200005;
    packet.field04 = 0x9F0600;
    packet.field0A = arg3;
    packet.field0C = 0;
    packet.field10 = 0;
    packet.field14 = 0xFF;
    packet.field15 = 0xFF;
    packet.field16 = 0xFF;
    packet.field17 = 0xFF;
    packet.field18 = 0xFF;
    packet.field19 = 0xFF;
    packet.field1A = 0xFF;
    packet.field1B = arg2;
    packet.field1C = 0xFF;
    packet.scaleX = arg1;
    packet.scaleY = arg1;
    packet.position = *arg0;
    packet.vector3C = *(Game2062D0Vector3 *)&D_800A5480;
    packet.vector48 = *(Game2062D0Vector3 *)&D_800A5480;
    packet.field1E = 4;
    packet.field20 = 0x3F;
    packet.field22 = 1;
    packet.field54 = 0.0f;
    packet.field24 = 1.0f;
    random1 = (func_150ADA20() & 1) ? 0x80 : 0;
    if (func_150ADA20() & 1) {
        random2 = 0x40;
    } else {
        random2 = 0;
    }
    if (D_800AB330[arg4] != 0) {
        flags = 0x800000;
    } else {
        flags = 0;
    }
    packet.flags = flags | 1 | random2 | random1 | 0xC200 | 0x10000;
    packet.field60 = 6;
    packet.field61 = 8;
    packet.field62 = -1;
    packet.field63 = -1;
    packet.field64 = -1;
    packet.field65 = 0;
    packet.field5C = 0;
    packet.field66 = 0xFF;
    packet.field68 = 0x3E8;
    packet.field6C = 1000.0f;
    func_15130280(&packet, 1, 0, 0, arg5, arg6);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151DC034 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DC034.s")

/* The second descriptor has the same 0x48-byte layout used by
 * GameEF410Spawn; position-relative fields are consumed by func_15150178. */
typedef struct {
    s16 field00;
    s16 field02;
    s16 field04;
    s16 field06;
    Game2062D0Vector3 vector;
    s16 field14;
    s16 field16;
    f32 field18;
    f32 field1C;
    s16 field20;
    s16 field22;
    f32 field24;
    f32 field28;
    u8 field2C;
    u8 field2D;
    u8 pad2E[2];
    f32 field30;
    f32 field34;
    s8 field38;
    u8 field39;
    u8 pad3A[2];
    f32 field3C;
    s8 field40;
    u8 pad41[3];
    f32 field44;
} Game2062D0SecondaryParams;

void func_15150178(s16 *, f32 *, s32, u8, s32);
extern f32 D_800AB4E4;
extern f32 D_800AB4E8;
extern f32 D_800AB4EC;
extern f32 D_800AB4F0;
extern f32 D_800AB4F4;

extern f32 D_800AB4D0;
extern f32 D_800AB4D4;
extern f32 D_800AB4D8;
extern f32 D_800AB4DC;
extern f32 D_800AB4E0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DC260 CURRENT (1543) */
void func_151DC260(Game2062D0Vector3 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Game2062D0Params params;
    Game2062D0SecondaryParams secondary;

    params.vector = *arg0;
    params.field50 = 0xA;
    params.field52 = 0xA;
    params.field26 = 0xFF;
    params.field28 = -0x40;
    params.field2A = 0x28;
    params.field38 = 3.0f;
    params.field24 = 0;
    params.field54 = 3;
    params.field56 = 1;
    params.field58 = 0x3C;
    params.field5A = 0x28;
    params.field5C = 0x64;
    params.field5E = 0x64;
    params.field68 = 0x10;
    params.field6A = 0xF;
    params.field6C = 0;
    params.field3C = 4.0f;
    params.field40 = D_800AB4D0;
    params.field44 = D_800AB4D4;
    params.field48 = 12.0f;
    params.field4C = 11.0f;
    params.field64 = 1.0f;
    params.field60 = (u8)arg2;
    func_15153F18(&params.field24, &params.vector, arg1, (u8)arg3, arg4);
    secondary.vector = *arg0;
    secondary.field14 = 0xC;
    secondary.field16 = 6;
    secondary.field02 = 0xFF;
    secondary.field18 = 6.0f;
    secondary.field1C = 8.0f;
    secondary.field00 = 0;
    secondary.field04 = -0x40;
    secondary.field06 = 0x24;
    secondary.field20 = 0x23;
    secondary.field22 = 0xF;
    secondary.field2C = 0x9B;
    secondary.field2D = 0x64;
    secondary.field38 = 1;
    secondary.field40 = 1;
    secondary.field24 = D_800AB4D8;
    secondary.field28 = D_800AB4DC;
    secondary.field30 = 123.0f;
    secondary.field34 = 134.0f;
    secondary.field39 = (u8)arg2;
    secondary.field3C = D_800AB4E0;
    secondary.field44 = 0.0f;
    func_15150178(&secondary.field00, (f32 *)&secondary.vector, arg1, arg3, arg4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151DC260 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DC260.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DC484 CURRENT (2910) */
void func_151DC484(Game2062D0Vector3 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Game2062D0Params params;
    Game2062D0SecondaryParams secondary;

    params.vector = *arg0;
    params.field50 = 8;
    params.field52 = 6;
    params.field26 = 0xFF;
    params.field28 = -0x40;
    params.field38 = 3.0f;
    params.field24 = 0;
    params.field2A = 0x28;
    params.field54 = 3;
    params.field56 = 0;
    params.field58 = 0x3C;
    params.field5A = 0x28;
    params.field5C = 0x64;
    params.field5E = 0x64;
    params.field68 = 0x10;
    params.field6A = 0xF;
    params.field6C = 0;
    params.field3C = 2.0f;
    params.field40 = D_800AB4E4;
    params.field44 = D_800AB4E8;
    params.field48 = 8.0f;
    params.field4C = 5.0f;
    params.field64 = 1.0f;
    params.field60 = (u8)arg2;
    func_15153F18(&params.field24, &params.vector, arg1, (u8)arg3, arg4);
    secondary.vector = *arg0;
    secondary.field14 = 0xC;
    secondary.field16 = 6;
    secondary.field02 = 0xFF;
    secondary.field00 = 0;
    secondary.field04 = -0x40;
    secondary.field06 = 0x1A;
    secondary.field20 = 0x23;
    secondary.field22 = 0xF;
    secondary.field2C = 0x9B;
    secondary.field2D = 0x64;
    secondary.field30 = 59.0f;
    secondary.field34 = 59.0f;
    secondary.field38 = 1;
    secondary.field40 = 1;
    secondary.field44 = 0.0f;
    secondary.field18 = 7.0f;
    secondary.field1C = 3.0f;
    secondary.field24 = D_800AB4EC;
    secondary.field28 = D_800AB4F0;
    secondary.field39 = (u8)arg2;
    secondary.field3C = D_800AB4F4;
    func_15150178(&secondary.field00, (f32 *)&secondary.vector, arg1, arg3, arg4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151DC484 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/func_151DC484.s")
