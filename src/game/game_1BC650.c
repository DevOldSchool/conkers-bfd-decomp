#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1BC650.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_dense_pointer_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1518F1A0
 * - func_1518F5D0
 * - func_1518F8E0
 * - func_1518FC84
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

f32 func_150ADA68();                                /* extern */
extern f32 D_800BE9A4;
extern f32 D_800A7B68;
extern f32 D_800A7B6C;
extern f32 D_800A7B70;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518F1A0 CURRENT (595) */
s32 func_1518F1A0(u8 *arg0) {
    f32 randomResult;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 temp_fv1_3;
    f32 temp_fv1_4;
    s32 temp_v1;
    u8 *temp_s0;
    u8 *temp_s0_2;

    *(s16 *)((u8 *)arg0 + 0x12E) = (s16) (*(s16 *)((u8 *)arg0 + 0x12E) - D_800BE9E4);
    if (*(s16 *)((u8 *)arg0 + 0x12E) < 0) {
        temp_s0 = (void *)(arg0 + 0x110);
        *(s16 *)((u8 *)temp_s0 + 0x1E) = (s16) (func_150ADA20() % 6U);
        if (func_150ADA20() & 3) {
            randomResult = func_150ADA68();
            temp_fv1 = *(f32 *)((u8 *)temp_s0 + 0x10);
            *(f32 *)((u8 *)temp_s0 + 0x18) = (f32) ((randomResult * (*(f32 *)((u8 *)temp_s0 + 0xC) - temp_fv1)) + temp_fv1);
        } else {
            randomResult = func_150ADA68();
            temp_fv1_2 = *(f32 *)((u8 *)temp_s0 + 0xC);
            *(f32 *)((u8 *)temp_s0 + 0x18) = (f32) ((randomResult * (*(f32 *)((u8 *)temp_s0 + 0x14) - temp_fv1_2)) + temp_fv1_2);
        }
    }
    temp_s0_2 = (void *)(arg0 + 0x110);
    {
        f32 temp_fv0 = *(f32 *)((u8 *)arg0 + 0x30);
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (temp_fv0 + ((*(f32 *)((u8 *)temp_s0_2 + 0x18) - temp_fv0) * D_800A7B68));
    *(s16 *)((u8 *)temp_s0_2 + 0x1C) = (s16) (*(s16 *)((u8 *)temp_s0_2 + 0x1C) - D_800BE9E4);
    if (*(s16 *)((u8 *)temp_s0_2 + 0x1C) < 0) {
        *(s16 *)((u8 *)temp_s0_2 + 0x1C) = (s16) (func_150ADA20() % 17U);
        randomResult = func_150ADA68();
        temp_fv1_3 = *(f32 *)((u8 *)temp_s0_2 + 4);
        *(f32 *)((u8 *)temp_s0_2 + 8) = (f32) ((randomResult * (*(f32 *)((u8 *)arg0 + 0x110) - temp_fv1_3)) + temp_fv1_3);
    }
    temp_fv0_2 = *(f32 *)((u8 *)arg0 + 0x2C);
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (temp_fv0_2 + ((*(f32 *)((u8 *)temp_s0_2 + 8) - temp_fv0_2) * D_800A7B6C));
    *(s16 *)((u8 *)temp_s0_2 + 0x2C) = (s16) (*(s16 *)((u8 *)temp_s0_2 + 0x2C) - D_800BE9E4);
    if (*(s16 *)((u8 *)temp_s0_2 + 0x2C) < 0) {
        *(s16 *)((u8 *)temp_s0_2 + 0x2C) = (s16) (func_150ADA20() % 15U);
        randomResult = func_150ADA68();
        temp_fv1_4 = *(f32 *)((u8 *)temp_s0_2 + 0x24);
        *(f32 *)((u8 *)temp_s0_2 + 0x28) = (f32) ((randomResult * (*(f32 *)((u8 *)temp_s0_2 + 0x20) - temp_fv1_4)) + temp_fv1_4);
    }
    temp_v1 = *(s32 *)((u8 *)arg0 + 0x24);
    *(s32 *)((u8 *)arg0 + 0x24) = (s32) (temp_v1 + (s32) ((*(f32 *)((u8 *)temp_s0_2 + 0x28) - (f32) temp_v1) * D_800A7B70));
    return 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518F1A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518F1A0.s")
extern f32 D_800A7B74;
extern f32 D_800A7B78;

s32 func_1518F384(u8 *arg0) {
    struct RangeState {
        f32 firstHigh;
        f32 firstLow;
        f32 firstValue;
        f32 secondHigh;
        f32 secondLow;
        f32 unused14;
        f32 secondValue;
        s16 firstReady;
        s16 secondReady;
    } *state = (struct RangeState *)(arg0 + 0x110);

    if (*(s16 *)(arg0 + 0x12C) == 0) {
        state->firstValue = func_150ADA68() * (state->firstHigh - state->firstLow) + state->firstLow;
        state->firstReady = 1;
    }
    if (state->secondReady == 0) {
        state->secondValue = func_150ADA68() * (state->secondHigh - state->secondLow) + state->secondLow;
        state->secondReady = 1;
    }
    *(f32 *)(arg0 + 0x30) += (state->secondValue - *(f32 *)(arg0 + 0x30)) * D_800A7B74;
    *(f32 *)(arg0 + 0x2C) += (state->firstValue - *(f32 *)(arg0 + 0x2C)) * D_800A7B78;
    return 1;
}
extern void func_15169260(s32 *arg0, s32 arg1, s32 arg2, u8 arg3);
typedef struct {
    s32 value;
} Game1BC650DispatchDescriptor;
extern Game1BC650DispatchDescriptor D_800A74D4;

void func_1518F45C(s32 arg0, u8 arg1) {
    Game1BC650DispatchDescriptor sp1C = D_800A74D4;

    func_15169260(&sp1C.value, 1, arg0, arg1);
}
void func_15169850(s32, u8, void *, void *, void *);

void func_1518F49C(u8 *arg0, s32 arg1, u8 arg2) {
    s32 first;
    s32 second;
    u8 first_kind;
    u8 second_kind;

    func_15169850(arg1, arg2, arg0 + 0x18, arg0 + 0x1C, arg0);
    if (arg2 == 0x49) {
        first = *(s32 *)((u8 *)arg0 + 0x18);
        second = *(s32 *)arg1;
        first_kind = *(u8 *)((u8 *)arg0 + 0x1C);
        second_kind = *(u8 *)((u8 *)arg1 + 4);
        if ((first == second) || (first_kind == second_kind)) {
            func_1516972C(arg0);
        }
    }
}
extern s32 D_8008D630;
s32 func_1518FDC4(void *, s8 *, u8);
s32 func_1518F5D0(void *, s32, s16, s8, s32, s32, s32, s32, s32, s32);

 s32 func_1518F51C(void *arg0, u8 arg1, s16 arg2, s8 arg3,
                  s8 arg4, s8 arg5, u8 arg6, s32 arg7, u8 arg8, s32 arg9) {
    s32 record;
    s8 index;

    if (arg0 == 0) {
        return 0;
    }
    if (func_1518FDC4(arg0, &index, arg1) == 0) {
        return 0;
    }
    record = *(s32 *)((u8 *)&D_8008D630 + ((u8)index * 4)) + (arg1 * 0x50);
    return func_1518F5D0(
        arg0, record,
        arg2, arg3, (s32)arg4, (s32)arg5, (s32)arg6, arg7, (s32)arg8, arg9);
}
typedef struct Game1BC650Record {
    s32 words[20];
} Game1BC650Record;

typedef struct Game1BC650CreatePacket {
    f32 zero;
    Game1BC650Record record;
    s32 child;
    s8 field58;
    s8 field59;
    u8 field5A;
    u8 pad5B;
} Game1BC650CreatePacket;

typedef struct Game1BC650Spawn {
    void *owner;
    u8 field4;
    u8 pad5;
    s16 duration;
    s8 enabled;
    s8 field9;
    s8 fieldA;
    s8 fieldB;
    s8 fieldC;
    s8 fieldD;
} Game1BC650Spawn;

void *func_10022EC0(void *, const void *, u32);
s32 func_1519021C(s32, u8 *, u8, s16, u8, s32);
void func_151D2AB0(s32);
void *func_151D2F00(void *, s32, u8, s32);
s32 func_1000FA64(s32, s32, s32, s32, s32, s32, s32, void *, void *, void *, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518F5D0 CURRENT (2197) */
s32 func_1518F5D0(void *arg0, s32 arg1, s16 arg2, s8 arg3,
                   s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    Game1BC650Spawn spawn;
    Game1BC650CreatePacket packet;
    s8 enabled;
    u8 *data;
    void *result;

    packet.zero = 0.0f;
    packet.record = *(Game1BC650Record *)arg1;
    enabled = 1;
    packet.field58 = arg3;
    spawn.owner = arg0;
    packet.field59 = (s8)arg4;
    packet.field5A = (u8)arg6;
    spawn.field4 = *((u8 *)arg0 + 0x3B);
    if (arg2 == -1) {
        spawn.duration = 0x12C;
    } else {
        spawn.duration = arg2;
    }
    if (arg2 == -1) {
        enabled = 0;
    }
    spawn.enabled = enabled;
    spawn.field9 = 0;
    spawn.fieldA = 0;
    spawn.fieldB = 0;
    spawn.fieldC = 0;
    spawn.fieldD = 1;
    result = func_151D2F00(&spawn, arg7 + 0x60, (u8)arg8, arg9);
    if (result != 0) {
        data = (u8 *)result + 0x30;
        func_10022EC0(data, &packet, 0x5CU);
        if ((s8)arg5 != -1) {
            *(s32 *)(data + 0x54) = func_1519021C((s32)result, arg0,
                (s8)arg5 & 0xFF, arg2, (u8)arg8, arg9);
        } else {
            *(s32 *)(data + 0x54) = 0;
        }
        func_151D2AB0(*(s32 *)(data + 0x48));
        func_1000FA64(0x4D, (s16)(s32)*(f32 *)((u8 *)arg0 + 0x14),
            (s16)(s32)*(f32 *)((u8 *)arg0 + 0x18),
            (s16)(s32)*(f32 *)((u8 *)arg0 + 0x1C), 0x3A98, 0x7D0, 0x320,
            func_1518E298, result, arg0, 0, 0);
    }
    return (s32)result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518F5D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518F5D0.s")
extern s32 (*D_8008D67C[])(void *);
extern void func_1518F8E0(void *arg0);

s32 func_1518F7C4(void *arg0) {
    f32 *p = (f32 *)((u8 *)arg0 + 0x30);

    p[0] += (p[1] + (func_150ADA68() * p[2])) * D_800BE9A4;
    func_1518F8E0(arg0);
    if (((s8 *)p)[0x58] != -1) {
        return D_8008D67C[((s8 *)p)[0x58]](arg0);
    }
    return 1;
}
extern void (*D_8008D680[])(void);

void func_1518F858(void *arg0) {
    s8 *field;

    field = (s8 *)((u8 *)arg0 + 0x89);
    if (*field != -1) {
        D_8008D680[*field]();
    }
}
void func_1518F89C(void *arg0) {
    f32 *temp_v0;

    temp_v0 = (f32 *)((u8 *)arg0 + 0x30);
    *temp_v0 = temp_v0[3] + (temp_v0[4] * func_150ADA68());
    func_1518F8E0(arg0);
}
void func_15143134(f32 *, f32 *, s32);
s32 func_1514B8E4(s32, f32 *, s16, s32, s32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void *func_151D2BA4(s32, void *, s32, u8, s32);
extern u8 D_800A5480[];
extern s16 D_800E0968[];
extern s32 D_800E0990[];

typedef struct {
    void *source;
    u8 owner;
    u8 pad5[3];
    Vec3f position;
    u8 frame;
    u8 pad15;
    s16 duration;
    u8 enabled, callback, endCallback, pad1B;
    s32 effect;
    void *parent;
} Game1BC650Motion;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518F8E0 CURRENT (4621) */
void func_1518F8E0(void *arg0) {
    Vec3f *localPosition;
    s32 model;
    f32 sizes[2];
    Vec3f position;
    s32 kind;
    u32 random;
    u8 *state;
    Game1BC650Motion motion;
    u8 *entry;
    u8 *source;

    source = *(u8 **)((u8 *)arg0 + 0x10);
    if (*(f32 *)((u8 *)arg0 + 0x30) > 1.0f) {
        if ((*(s32 *)(source + 0x1D4) != 0) && ((source[0x74] & 15) != 15)) {
            state = (u8 *)arg0 + 0x30;
            do {
                if (*(s16 *)((u8 *)arg0 + 0x20) < *(s32 *)(state + 0x2C)) {
                    model = *(s32 *)(state + 0x48);
                    entry = (u8 *)D_800E0990[model] + (func_150ADA20() % (u16)D_800E0968[model]) * 16;
                    sizes[0] = func_150ADA68() * *(f32 *)(state + 0x1C) + *(f32 *)(state + 0x14);
                    localPosition = (Vec3f *)(entry + 4);
                    sizes[1] = func_150ADA68() * *(f32 *)(state + 0x20) + *(f32 *)(state + 0x18);
                    func_15143134((f32 *)localPosition, (f32 *)&position, *(s32 *)(source + 0x1D4) + (entry[0] << 6));
                    random = func_150ADA20();
                    if (func_150ADA20() & 1) kind = 0x13;
                    else kind = 0x14;
                    random = func_1514B8E4((s32)&position, sizes, -1,
                        (random % (u32)(state[0x25] + 1) + state[0x24]) & 255,
                        (s32)D_800A5480, 0.0f, 1.0f, *(f32 *)(state + 0x50),
                        0, 0x23, 0, kind, 1, 1, 255, 0,
                        *((u8 *)arg0 + 0xC), *((u8 *)arg0 + 1));
                    if (random != 0) {
                        motion.source = source;
                        motion.owner = source[0x3B];
                        motion.position = *localPosition;
                        motion.frame = entry[0];
                        motion.duration = func_150ADA20() % (u32)(*(s16 *)(state + 0x28) + 1) + *(s16 *)(state + 0x26);
                        motion.enabled = 1;
                        if (state[0x4C] & 1) motion.callback = 1;
                        else motion.callback = 0;
                        motion.endCallback = 0;
                        motion.parent = arg0;
                        motion.effect = random;
                        func_151D2BA4((s32)&motion, &position, 0, *((u8 *)arg0 + 0xC), *((u8 *)arg0 + 1));
                    }
                }
                *(f32 *)((u8 *)arg0 + 0x30) -= 1.0f;
            } while (*(f32 *)((u8 *)arg0 + 0x30) > 1.0f);
            return;
        }
        do {
            *(f32 *)((u8 *)arg0 + 0x30) -= 1.0f;
        } while (*(f32 *)((u8 *)arg0 + 0x30) > 1.0f);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518F8E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518F8E0.s")
extern void func_1514BE20(s32 arg0);

s32 func_1518FC04(void *arg0, void *arg1) {
    typedef struct { s32 words[3]; } Copy3;
    struct {
        u8 pad0[0x2C];
        s32 *field2C;
    } *temp_a2;
    void *temp_a0;

    temp_a2 = arg0;
    temp_a0 = temp_a2->field2C;
    *(Copy3 *)((u8 *)temp_a0 + 0x34) = *(Copy3 *)arg1;
    func_1514BE20((s32) temp_a0);
    return 1;
}

s32 func_1518FC44(void *arg0, void *arg1) {
    typedef struct { s32 words[3]; } Copy3;
    struct {
        u8 pad0[0x2C];
        s32 *field2C;
    } *temp_a2;
    void *temp_a0;

    temp_a2 = arg0;
    temp_a0 = temp_a2->field2C;
    *(Copy3 *)((u8 *)temp_a0 + 0x34) = *(Copy3 *)arg1;
    func_1514BF50(temp_a0);
    return 1;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518FC84 CURRENT (153) */
void func_1518FC84(u8 *arg0, f32 *arg1) {
    u8 *object;
    u8 *fields;
    u8 *transform;
    u8 *settings;

    settings = *(u8 **)(arg0 + 0x30);
    object = *(u8 **)(arg0 + 0x2C);
    if (settings == 0) {
        func_1516972C((s32)object);
        return;
    }
    *(f32 *)(object + 0x148) = *(f32 *)(settings + 0x60) *
                              (arg1[0] - *(f32 *)(arg0 + 0x34));
    *(f32 *)(object + 0x14C) = *(f32 *)(settings + 0x60) *
                              (arg1[1] - *(f32 *)(arg0 + 0x38));
    *(f32 *)(object + 0x150) = *(f32 *)(settings + 0x60) *
                              (arg1[2] - *(f32 *)(arg0 + 0x3C));
    transform = object + 0x110;
    fields = settings + 0x30;
    *(f32 *)(transform + 0x44) = *(f32 *)(fields + 0x34) +
                                  *(f32 *)(fields + 0x38) * func_150ADA68();
    *(f32 *)(transform + 0x48) = *(f32 *)(fields + 0x3C);
    *(s16 *)(object + 0x6C) = *(s16 *)(fields + 0x40);
    *(s16 *)(object + 0x6E) = *(s16 *)(fields + 0x42);
    *(s16 *)(object + 0x1C) = *(s16 *)(fields + 0x44) +
                              func_150ADA20() % (u32)(*(s16 *)(fields + 0x46) + 1);
    if (fields[0x4C] & 1) {
        object[0x70] = 0x21;
    } else {
        object[0x70] = 0x20;
    }
    object[0x71] = 0x24;
    *(s32 *)(object + 0x58) |= 0x8000001;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518FC84 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BC650/func_1518FC84.s")
s32 func_1518FDC4(void *arg0, s8 *arg1, u8 arg2) {

    switch ((s32)*((u8 *)arg0 + 4)) {
    case 0x87:
    case 0xB0:
        *arg1 = 0xD;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0xB1:
        *arg1 = 0xE;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0xB4:
        *arg1 = 0xF;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x70:
    case 0xB2:
        *arg1 = 0x10;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x53:
        *arg1 = 0x11;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x96:
        *arg1 = 0x12;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x0:
    case 0x1:
    case 0x2:
    case 0x3:
    case 0x4:
        *arg1 = 0;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x49:
        *arg1 = 1;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x58:
        *arg1 = 2;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x50:
        *arg1 = 3;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x5A:
    case 0x5F:
    case 0x74:
    case 0x75:
    case 0x7A:
        *arg1 = 4;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x80:
        *arg1 = 5;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x11:
    case 0x14:
    case 0x3B:
    case 0x98:
    case 0x99:
        *arg1 = 6;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x16:
        *arg1 = 7;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x88:
    case 0x90:
        *arg1 = 8;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x9C:
        *arg1 = 9;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x9D:
        *arg1 = 0xA;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0x9F:
        *arg1 = 0xB;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    case 0xA0:
        *arg1 = 0xC;
        if (arg2 > 0) {
            return 0;
        }
        return 1;
    default:
        return 0;
    }
}
extern u8 D_800A7AC8;
extern u8 D_800A7ACC;
extern u8 D_800A7AD0;
extern u8 D_800A7AD4;
extern u8 D_800A7AD8;
extern u8 D_800A7ADC;
extern u8 D_800A7AE0;
extern u8 D_800A7AE4;
extern u8 D_800A7AE8;
extern u8 D_800A7AEC;
extern u8 D_800A7AF0;
extern u8 D_800A7AF4;
extern u8 D_800A7AF8;
extern u8 D_800A7AFC;
extern u8 D_800A7B00;
extern u8 D_800A7B04;
extern u8 D_800A7B08;
extern u8 D_800A7B0C;
extern u8 D_800A7B10;

u8 *func_1519003C(u8 *arg0, s32 *arg1) {
    u8 *var_v1;

    switch (arg0[4]) {
    case 0x87:
    case 0xB0:
        var_v1 = &D_800A7AFC;
        *arg1 = 1;
        break;
    case 0xB1:
        var_v1 = &D_800A7B00;
        *arg1 = 1;
        break;
    case 0xB4:
        var_v1 = &D_800A7B04;
        *arg1 = 1;
        break;
    case 0x70:
    case 0xB2:
        var_v1 = &D_800A7B08;
        *arg1 = 1;
        break;
    case 0x53:
        var_v1 = &D_800A7B0C;
        *arg1 = 1;
        break;
    case 0x96:
        var_v1 = &D_800A7B10;
        *arg1 = 1;
        break;
    case 0x0:
    case 0x1:
    case 0x2:
    case 0x3:
    case 0x4:
        var_v1 = &D_800A7AC8;
        *arg1 = 1;
        break;
    case 0x49:
        var_v1 = &D_800A7ACC;
        *arg1 = 1;
        break;
    case 0x58:
        var_v1 = &D_800A7AD0;
        *arg1 = 1;
        break;
    case 0x50:
        var_v1 = &D_800A7AD4;
        *arg1 = 1;
        break;
    case 0x75:
        var_v1 = &D_800A7AD8;
        *arg1 = 1;
        break;
    case 0x80:
        var_v1 = &D_800A7ADC;
        *arg1 = 1;
        break;
    case 0x11:
    case 0x14:
    case 0x3B:
    case 0x98:
    case 0x99:
        var_v1 = &D_800A7AE0;
        *arg1 = 1;
        break;
    case 0x16:
        var_v1 = &D_800A7AE4;
        *arg1 = 1;
        break;
    case 0x88:
    case 0x90:
        var_v1 = &D_800A7AE8;
        *arg1 = 1;
        break;
    case 0x9C:
        var_v1 = &D_800A7AEC;
        *arg1 = 1;
        break;
    case 0x9D:
        var_v1 = &D_800A7AF0;
        *arg1 = 1;
        break;
    case 0x9F:
        var_v1 = &D_800A7AF4;
        *arg1 = 1;
        break;
    case 0xA0:
        var_v1 = &D_800A7AF8;
        *arg1 = 1;
        break;
    default:
        var_v1 = 0;
        *arg1 = 0;
        break;
    }
    return var_v1;
}
typedef struct Game19021CDescriptor {
    u8 flags;
    u8 kind;
    s16 duration;
    u8 type;
    u8 pad5[3];
} Game19021CDescriptor;

typedef struct Game19021CLocals {
    s32 position[3];
    s32 source;
    f32 values[8];
    void *node;
    u8 color;
    u8 pad35[3];
    Game19021CDescriptor descriptor;
    u8 pad40[4];
} Game19021CLocals;

void *func_10022EC0(void *, const void *, u32);
s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 D_800A6760[];
extern f32 D_800A67C0[];
extern f32 D_800A6820[];
extern f32 D_800A8004;

s32 func_1519021C(s32 arg0, u8 *arg1, u8 arg2, s16 arg3, u8 arg4,
                   s32 arg5) {
    Game19021CLocals locals;
    s32 result;

    if (arg2 >= 0x18) {
        return 0;
    }
    locals.source = arg0;
    locals.values[0] = D_800A67C0[arg2];
    locals.values[1] = D_800A6760[arg2];
    locals.values[2] = D_800A6820[arg2];
    locals.values[3] = 1.0f;
    locals.values[5] = 5.0f;
    locals.values[4] = 0.0f;
    locals.values[7] = 0.0f;
    locals.values[6] = D_800A8004;
    locals.descriptor.flags = (arg3 == -1 ? 0 : 1) | 2;
    locals.descriptor.kind = 0x12;
    locals.descriptor.duration = arg3 == -1 ? 0x12C : arg3;
    locals.descriptor.type = 0x25;
    locals.node = arg1;
    locals.color = arg1[0x3B];
    locals.position[0] = (s32)*(f32 *)(arg1 + 0x14);
    locals.position[1] = (s32)*(f32 *)(arg1 + 0x18);
    locals.position[2] = (s32)*(f32 *)(arg1 + 0x1C);
    result = func_151602C0((u8 *)&locals.descriptor, locals.position,
                           0, 0xFF, 0xD1, 0, 0xFF, 0, 0x30, arg4, arg5);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x18, &locals.node, 8);
        func_10022EC0((u8 *)result + 0x20, locals.values, 0x20);
        func_10022EC0((u8 *)result + 0x40, &locals.source, 4);
    }
    return result;
}
