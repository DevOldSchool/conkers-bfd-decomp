#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_169510.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_dispatcher_callback_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1513C060
 * - func_1513C350
 * - func_1513C92C
 * - func_1513CAD4
 * - func_1513CBF0
 * - func_1513CFE4
 * - func_1513D2F0
 * - func_1513D6FC
 * - func_1513DB00
 * - func_1513DF9C
 * - func_1513E084
 * - func_1513E13C
 * - func_1513E2AC
 * - func_1513E6E8
 * - func_1513E83C
 * - func_1513EAD8
 * - func_1513EE14
 * - func_1513F114
 * - func_1513F728
 * - func_1513FAB4
 * - func_15140190
 * - func_15140410
 * - func_151406AC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_1513C92C(u8 *arg0);
void func_1513CAD4(void *arg0);

extern s32 (*D_80089C70[])(u8 *);
extern s32 (*D_80089CA8[])(u8 *);
extern u8 D_80090B64[];
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513C060 CURRENT (2813) */
void func_1513C060(u8 *arg0) {
    s8 expired;
    s32 flags, lifetime, product, speed, boundary, value;
    u8 callback;

    if (!(*(s32 *)(arg0 + 0x10) & 1)) return;
    expired = 0;
    if (*(s32 *)(arg0 + 0x18) & 1) {
        *(s16 *)(arg0 + 0x1C) -= D_800BE9E4;
        if (*(s16 *)(arg0 + 0x1C) < 0) expired = 1;
    }
    callback = arg0[0x80];
    if (callback != 0) {
        if (D_80089C70[callback](arg0) == 0) expired = 1;
    }
    flags = *(s32 *)(arg0 + 0x18);
    if ((flags & 0x8000) && expired == 0) {
        lifetime = *(s16 *)(arg0 + 0x1C);
        if (lifetime < *(s16 *)(arg0 + 0x3A)) {
            product = lifetime * *(s16 *)(arg0 + 0x3C);
            if (product < arg0[0x28]) {
                arg0[0x28] = product;
                flags = *(s32 *)(arg0 + 0x18);
            }
        }
    }
    if ((flags & 0x10000) && expired == 0) {
        lifetime = *(s16 *)(arg0 + 0x1C);
        if (lifetime < *(s16 *)(arg0 + 0x3A)) {
            product = lifetime * *(s16 *)(arg0 + 0x3C);
            if (product < arg0[0x28]) arg0[0x2D] = product;
        }
    }
    if (expired == 0) {
        speed = *(s32 *)(arg0 + 0x24);
        if (speed != 0) {
            boundary = (D_80090B64[arg0[0x1E] * 12] << 16) - 1;
            value = (s32)((u32)*(s32 *)(arg0 + 0x20) + (u32)speed * (u32)D_800BE9E4);
            *(s32 *)(arg0 + 0x20) = value;
            if (boundary < value) {
                flags = *(s32 *)(arg0 + 0x18);
                if (flags & 2) expired = 1;
                else if (flags & 0x40) {
                    *(s32 *)(arg0 + 0x24) = 0;
                    *(s32 *)(arg0 + 0x20) = boundary;
                } else if (flags & 4) {
                    *(s32 *)(arg0 + 0x20) = boundary - value % boundary;
                    *(s32 *)(arg0 + 0x24) = (s32)(0U - (u32)speed);
                } else {
                    do {
                        value = (s32)((u32)value - (u32)boundary);
                        *(s32 *)(arg0 + 0x20) = value;
                    } while (boundary < value);
                }
            } else if (value < 0) {
                flags = *(s32 *)(arg0 + 0x18);
                if (flags & 8) expired = 1;
                else if (flags & 0x80) {
                    *(s32 *)(arg0 + 0x24) = 0;
                    *(s32 *)(arg0 + 0x20) = 0;
                } else if (flags & 4) {
                    *(s32 *)(arg0 + 0x20) = (s32)(0U - (u32)value) % boundary;
                    *(s32 *)(arg0 + 0x24) = (s32)(0U - (u32)speed);
                } else {
                    do {
                        value = (s32)((u32)value + (u32)boundary);
                        *(s32 *)(arg0 + 0x20) = value;
                    } while (value < 0);
                }
            }
        }
    }
    if (expired != 0) {
        callback = arg0[0x81];
        if (callback != 0) {
            if (D_80089CA8[callback](arg0) != 0) func_1516972C(arg0);
        } else func_1516972C(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513C060 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513C060.s")

typedef struct Game169510Vec3 {
    s32 x;
    s32 y;
    s32 z;
} Game169510Vec3;

void *func_10022EC0(void *, const void *, u32);
void func_1513FFF4(void *, u8, u8);
void func_151400D0(void *, void *);
void *func_1515D440(void);
s32 func_1515D480(s32);
extern u8 D_800A4AA0;
extern s32 D_80082FA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513C350 CURRENT (1220) */
void *func_1513C350(s32 arg0, s32 arg1, u8 arg2, u8 arg3,
                     s32 arg4, s32 arg5, s32 arg6, void *arg7,
                     s32 arg8, s32 arg9, s32 arg10) {
    u8 *effect;
    u8 *cursor;
    s32 index;
    s32 kind;

    if (arg1 == 0) {
        arg1 = (s32)&D_800A4AA0;
    }
    kind = (*(s32 *)arg0 & 0x40000) ? 0x4A : 0x1B;
    effect = func_15167A68(kind, arg10, arg8 + 0xB0, 1,
                           ((u8 *)&arg9)[3], 1);
    if (effect == 0) {
        return 0;
    }
    func_10022EC0(effect + 0x18, (void *)arg0, 0x28);
    cursor = effect + 0x40;
    func_1513FFF4(cursor, effect[0x1E], (u8)arg4);
    func_151400D0(cursor, (void *)arg1);
    effect[0x80] = arg2;
    *(s32 *)(effect + 0x10) = 1;
    *(s32 *)(effect + 0x14) = 0;
    *(s32 *)(effect + 0x84) = arg5;
    effect[0x81] = arg3;
    *(s32 *)(effect + 0xA0) = arg6;
    index = 0;
    cursor = effect;
    do {
        index++;
        cursor += 4;
        *(s32 *)(cursor + 0x88) = 0;
    } while (index < 4);
    *(s32 *)(effect + 0x9C) = 0;
    if (arg5 != 0) {
        index = 0;
        cursor = effect;
        if (D_80082FA0 >= 0) {
            do {
                *(s32 *)(cursor + 0x8C) = func_1515D480(arg5);
                index++;
                cursor += 4;
            } while (D_80082FA0 >= index);
        }
        *(void **)(effect + 0x9C) = func_1515D440();
    }
    if (arg7 != 0) {
        *(Game169510Vec3 *)(effect + 0xA4) = *(Game169510Vec3 *)arg7;
    }
    return effect;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513C350 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513C350.s")
void *func_1513C350(s32, s32, u8, u8, s32, s32, s32, void *, s32, s32, s32);
void *func_1513E13C(void *, f32, f32, f32, f32, f32, u8);

void *func_1513C4EC(s32 arg0, s32 arg1, register u8 arg2, register u8 arg3, f32 arg4,
    f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 arg10, s32 arg11,
    s32 arg12, s32 arg13, u8 arg14, s32 arg15) {
    void *temp_v0;
    struct {
        f32 first;
        f32 second;
        f32 third;
    } packet;

    packet.first = arg4;
    packet.second = arg5;
    packet.third = arg6;
    temp_v0 = func_1513C350(arg0, arg1, arg2, arg3,
        (s32)arg10, arg11, arg12, &packet, arg13, (s32)arg14, arg15);
    if (temp_v0 == 0) {
        return 0;
    }
    func_1513E13C(temp_v0, arg4, arg5, arg6, arg7, arg8, arg9);
    return temp_v0;
}

void *func_1513C5B0(s32 arg0, s32 arg1, u8 arg2, u8 arg3, f32 arg4,
    f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 arg10,
    s32 arg11, u8 arg12, s32 arg13) {
    void *temp_v0;
    void *sp3C;

    temp_v0 = func_1513C350(arg0, arg1, arg2, arg3, (s32)arg10,
                            0, 0, 0, arg11, (s32)arg12, arg13);
    if (temp_v0 == 0) {
        return 0;
    }
    sp3C = temp_v0;
    func_1513E13C(temp_v0, arg4, arg5, arg6, arg7, arg8, (u8) (s32) arg9);
    return sp3C;
}
s32 func_1513E2AC(void *, s32, s32, f32, f32, f32, f32, f32, s32);

void *func_1513C650(s32 arg0, u8 arg1, u8 arg2, s32 arg3, f32 arg4,
    f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 arg10, s32 arg11,
    s32 arg12, s32 arg13, u8 arg14, s32 arg15) {
    void *object;
    struct {
        f32 x;
        f32 y;
        f32 z;
    } packet;

    packet.x = arg4;
    packet.y = arg5;
    packet.z = arg6;
    object = func_1513C350(arg0, 0, arg1, arg2, (s32)arg10, arg11,
                           arg12, &packet, arg13, (s32)arg14, arg15);
    if (object == 0) {
        return 0;
    }
    if (func_1513E2AC(object, 0, arg3, arg4, arg5, arg6, arg7, arg8,
                      (s32)arg9) == 0) {
        func_1516972C(object);
        return 0;
    }
    return object;
}

void *func_1513C73C(s32 arg0, u8 arg1, u8 arg2, s32 arg3, f32 arg4,
    f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 arg10, s32 arg11,
    u8 arg12, s32 arg13) {
    void *temp_v0;

    temp_v0 = func_1513C350(arg0, 0, arg1, arg2, (s32)arg10,
                            0, 0, 0, arg11, (s32)arg12, arg13);
    if (temp_v0 == 0) {
        return 0;
    }
    if (func_1513E2AC(temp_v0, 0, arg3, arg4, arg5, arg6, arg7, arg8,
                      arg9) == 0) {
        func_1516972C(temp_v0);
        return 0;
    }
    return temp_v0;
}
void *func_1513C804(s32 arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4,
                    f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9,
                    u8 arg10, u8 arg11, s32 arg12, u8 arg13, s32 arg14) {
    void *result;

    result = func_1513C350(arg0, 0, arg2, arg3, arg11, 0, 0, 0, arg12,
                           arg13, arg14);
    if (result == 0) {
        return 0;
    }
    if (func_1513E2AC(result, 0, arg4, arg5, arg6, arg7, arg8, arg9,
                      arg10) == 0) {
        func_1516972C(result);
        return 0;
    }
    return result;
}
void func_1513C8D4(void *arg0) {
    func_1513C92C(arg0);
    func_15169804(arg0);
}
void func_1513C900(void *arg0) {
    func_1513C92C(arg0);
    func_15169824(arg0);
}
void func_100043B4(s32, s32);
extern s32 D_80082FA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513C92C CURRENT (890) */
void func_1513C92C(u8 *arg0) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s0;
    s32 var_s1;

    var_s1 = 0;
    var_s0 = arg0;
    if (D_80082FA0 >= 0) {
        do {
            temp_v0 = *(s32 *)(var_s0 + 0x8C);
            if (temp_v0 != 0) {
                func_100043B4(temp_v0, 4);
            }
            var_s1 += 1;
            var_s0 += 4;
        } while (D_80082FA0 >= var_s1);
    }
    temp_v0_2 = *(s32 *)(arg0 + 0x9C);
    if (temp_v0_2 != 0) {
        func_100043B4(temp_v0_2, 4);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513C92C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513C92C.s")
extern void (*D_80089EE8[])(void);

void func_1513C9B0(void *arg0) {
    u8 var_v0;

    if (*(s32 *)((u8 *)arg0 + 0x18) & 0x1000) {
        var_v0 = *(u8 *)((u8 *)arg0 + 0x1F);
    } else {
        var_v0 = 0;
    }
    D_80089EE8[var_v0]();
}
extern void (*D_80089EF0[])(void);

void func_1513C9FC(void *arg0) {
    u8 var_v0;

    if (*(s32 *)((u8 *)arg0 + 0x18) & 0x1000) {
        var_v0 = *(u8 *)((u8 *)arg0 + 0x1F);
    } else {
        var_v0 = 0;
    }
    D_80089EF0[var_v0]();
}
void func_1513CA48(u8 *arg0) {
    func_151D5E30(arg0 + 0x100, arg0);
}
void func_1513CA6C(void *arg0) {
    func_1513CA48(arg0);
    func_1513CAD4(arg0);
    func_15169804(arg0);
}
void func_1513CAA0(void *arg0) {
    func_1513CA48(arg0);
    func_1513CAD4(arg0);
    func_15169824(arg0);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513CAD4 CURRENT (890) */
void func_1513CAD4(s32 arg0) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s0;
    s32 var_s1;

    var_s1 = 0;
    var_s0 = arg0;
    if (D_80082FA0 >= 0) {
        do {
            temp_v0 = *(s32 *)((u8 *)var_s0 + 0xA4);
            if (temp_v0 != 0) {
                func_100043B4(temp_v0, 4);
            }
            var_s1 += 1;
            var_s0 += 4;
        } while (D_80082FA0 >= var_s1);
    }
    temp_v0_2 = *(s32 *)((u8 *)arg0 + 0xB4);
    if (temp_v0_2 != 0) {
        func_100043B4(temp_v0_2, 4);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513CAD4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513CAD4.s")
extern void (*D_80089EF8[])(void);

void func_1513CB58(void *arg0) {
    u8 var_v0;

    if (*(s32 *)((u8 *)arg0 + 0x58) & 0x400000) {
        var_v0 = *(u8 *)((u8 *)arg0 + 0x19);
    } else {
        var_v0 = 0;
    }
    D_80089EF8[var_v0]();
}
extern void (*D_80089F2C[])(void);

void func_1513CBA4(void *arg0) {
    u8 var_v0;

    if (*(s32 *)((u8 *)arg0 + 0x58) & 0x400000) {
        var_v0 = *(u8 *)((u8 *)arg0 + 0x19);
    } else {
        var_v0 = 0;
    }
    D_80089F2C[var_v0]();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513CBF0.s")
extern void (*D_80089F60)(s32, s32, u8);

void func_1513CF9C(s32 arg0, s32 arg1, u8 arg2) {
    D_80089F60(arg0, arg1, arg2);
}
void func_1513CFD0(s32 arg0, s32 arg1, s32 arg2) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513CFE4.s")
typedef struct Game169510Effect {
    u8 pad0[0x10];
    s32 active;
    s32 state;
    u8 descriptor[0x58];
    u8 type;
    u8 variant;
    u8 flag72;
    u8 flag73;
    u8 flag74;
    u8 pad75[3];
    f32 scale;
    u8 pad7C[0x14];
    s32 field90;
    u8 flag94;
    u8 flag95;
    u8 pad96[2];
    s32 field98;
    s32 resource;
    u8 flagA0;
    u8 padA1[3];
    s32 resources[4];
    void *resourceState;
    s32 fieldB8;
    u8 padBC[4];
    u8 transform[0x40];
    u8 data[0x10];
} Game169510Effect;

void func_100226F0(void *, s32);
extern f32 D_800A5184;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513D2F0 CURRENT (10) */
void *func_1513D2F0(s32 arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4,
    u8 arg5, u8 arg6, s32 arg7, s32 arg8, s32 arg9, u8 arg10, s32 arg11) {
    Game169510Effect *effect;
    u8 *cursor;
    s32 index;
    s32 kind;
    s32 flags;
    s32 count;
    f32 scale;

    flags = *(s32 *)(arg0 + 0x40);
    if (flags & 0x800000) {
        kind = 0x56;
    } else if (flags & 0x02000000) {
        kind = 0x49;
    } else {
        kind = 0x1C;
    }
    if (flags & 0x80000000) {
        count = 2;
    } else {
        count = 1;
    }
    effect = func_15167A68(kind, arg11, arg9 + 0x110, 1, arg10, count);
    if (effect == 0) {
        return 0;
    }
    func_10022EC0(effect->descriptor, (void *)arg0, 0x58);
    effect->type = arg2;
    effect->variant = arg3;
    effect->flag72 = arg4;
    effect->flag73 = arg5;
    effect->flag74 = 0;
    func_100226F0(effect->data, 0x10);
    cursor = effect->transform;
    func_1513FFF4(cursor, effect->descriptor[0], arg6);
    func_151400D0(cursor, (void *)arg1);
    effect->active = 1;
    effect->state = 0;
    scale = D_800A5184;
    effect->field98 = 0;
    effect->flag95 = 0;
    effect->flag94 = 0;
    effect->field90 = 0;
    effect->resource = arg7;
    effect->scale = scale;
    effect->fieldB8 = arg8;
    effect->flagA0 = 0;
    index = 0;
    cursor = (u8 *)effect;
    do {
        index++;
        cursor += 4;
        *(s32 *)(cursor + 0xA0) = 0;
    } while (index < 4);
    effect->resourceState = 0;
    if (arg7 != 0) {
        index = 0;
        cursor = (u8 *)effect;
        if (D_80082FA0 >= 0) {
            do {
                *(s32 *)(cursor + 0xA4) = func_1515D480(arg7);
                index++;
                cursor += 4;
            } while (D_80082FA0 >= index);
        }
        effect->resourceState = func_1515D440();
    }
    return effect;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513D2F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513D2F0.s")
void *func_1513D2F0(s32, s32, u8, u8, u8, u8, u8, s32, s32, s32, u8, s32);

void func_1513D4B8(s32 arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7, u8 arg8, s32 arg9) {
    func_1513D2F0(arg0, arg1, arg2, arg3, arg4, arg5, arg6, 0, 0, arg7, arg8, arg9);
}
extern u8 D_800A4AA0;

void func_1513D524(s32 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, s32 arg6, u8 arg7, s32 arg8) {
    func_1513D2F0(arg0, (s32)&D_800A4AA0, arg1, arg2, arg3, arg4, arg5,
                  0, 0, arg6, arg7, arg8);
}
s32 func_1513D6FC(void *, s16, f32, f32, s32, s32, s32);

void *func_1513D594(s32 arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4,
                    u8 arg5, s16 arg6, f32 arg7, f32 arg8, s32 arg9,
                    s32 arg10, s32 arg11, s32 arg12, u8 arg13, s32 arg14,
                    u8 arg15, s32 arg16) {
    void *sp3C;
    void *temp_v0;

    if (arg1 == 0) {
        arg1 = (s32)&D_800A4AA0;
    }
    temp_v0 = func_1513D2F0(arg0, arg1, arg2, arg3, arg4, 0xC, arg5,
                            arg11, arg12, arg14 + 0x18, arg15, arg16);
    sp3C = temp_v0;
    if ((temp_v0 != 0) &&
        (func_1513D6FC((u8 *)temp_v0 + 0x110, arg6, arg7, arg8,
                       arg9, arg10, arg13) == 0)) {
        func_1516972C((void *)sp3C);
        return 0;
    }
    return (void *)sp3C;
}
void func_1513D668(s32 arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, s16 arg6, f32 arg7, f32 arg8, s32 arg9, s32 arg10, u8 arg11, s32 arg12, u8 arg13, s32 arg14) {
    func_1513D594(arg0, arg1, arg2, arg3, (s32)arg4, (s32)arg5, (s32)arg6,
                  arg7, arg8, arg9, arg10, 0, 0, (s32)arg11, arg12, (s32)arg13, arg14);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513D6FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513DB00.s")
extern void (*D_80089F64[])(void *, s32, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513DF9C CURRENT (20) */
void func_1513DF9C(void *arg0, s32 arg1, u8 arg2) {
    s32 index;
    u8 type;

    if (!(*(s32 *)((u8 *)arg0 + 0x58) & 0x400000)) {
        index = 0;
        goto dispatch;
    }
    type = *(u8 *)((u8 *)arg0 + 0x19);
    switch (type) {
    case 12:
        index = 10;
        break;
    case 11:
        index = 9;
        break;
    case 0:
    case 2:
    case 10:
        index = 0;
        break;
    case 1:
        index = 1;
        break;
    case 5:
        index = 2;
        break;
    case 6:
        index = 3;
        break;
    case 3:
        index = 4;
        break;
    case 7:
        index = 5;
        break;
    case 8:
        index = 6;
        break;
    case 9:
        index = 7;
        break;
    case 4:
        index = 8;
        break;
    default:
        index = 0;
        break;
    }
dispatch:
    D_80089F64[index](arg0, arg1, arg2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513DF9C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513DF9C.s")
void func_1513E070(s32 arg0, s32 arg1, s32 arg2) {
}

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513E084 CURRENT (20) */
void func_1513E084(void *arg0, void *arg1, u8 arg2) {
    u8 *state;
    s32 current;

    state = (u8 *)arg0 + 0x110;
    if (arg2 == 0x1A) {
        if ((*(s32 *)arg1 == *(s32 *)state) ||
            (*(u8 *)((u8 *)arg1 + 4) == *(u8 *)(state + 4))) {
            func_1516972C(arg0);
        }
        return;
    }
    if (arg2 != 0x2D) {
        return;
    }
    current = *(s32 *)state;
    if (*(s32 *)arg1 == current) {
        *(s32 *)state = *(s32 *)((u8 *)arg1 + 4);
        *(u8 *)(state + 4) = *(u8 *)((u8 *)arg1 + 9);
    } else if (*(s32 *)((u8 *)arg1 + 4) == current) {
        *(s32 *)state = *(s32 *)arg1;
        *(u8 *)(state + 4) = *(u8 *)((u8 *)arg1 + 8);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513E084 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513E084.s")
/* Call context: func_151423D8: unique active project prototype */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513E13C CURRENT (2081) */
void *func_1513E13C(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6) {
    f32 sp48;
    volatile f32 sp30;
    volatile f32 sp1C;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft2;
    f32 temp_ft2_2;
    f32 temp_ft3_2;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 temp_ft3;
    s32 angle;

    angle = arg6;
    angle -= 0x40;
    sp48 = func_151423D8(angle);
    temp_fv0 = func_151423D8(arg6);
    temp_fa1 = arg4 * temp_fv0;
    temp_fa0 = arg5 * sp48;
    temp_ft5 = arg1 + temp_fa1;
    *(s16 *)((u8 *)arg0 + 0x40) = (s16) (s32) (temp_ft5 - temp_fa0);
    temp_ft3 = (s32) arg2;
    *(s16 *)((u8 *)arg0 + 0x42) = (s16) temp_ft3;
    temp_ft4 = arg5 * temp_fv0;
    temp_fv1 = arg4 * sp48;
    temp_ft2 = arg3 + temp_ft4;
    sp1C = temp_ft2;
    *(s16 *)((u8 *)arg0 + 0x44) = (s16) (s32) (temp_ft2 + temp_fv1);
    temp_ft2_2 = arg1 - temp_fa1;
    sp30 = temp_ft2_2;
    *(s16 *)((u8 *)arg0 + 0x52) = (s16) temp_ft3;
    *(s16 *)((u8 *)arg0 + 0x50) = (s16) (s32) (temp_ft2_2 - temp_fa0);
    *(s16 *)((u8 *)arg0 + 0x54) = (s16) (s32) (sp1C - temp_fv1);
    *(s16 *)((u8 *)arg0 + 0x62) = (s16) temp_ft3;
    *(s16 *)((u8 *)arg0 + 0x60) = (s16) (s32) (sp30 + temp_fa0);
    temp_ft3_2 = arg3 - temp_ft4;
    sp30 = temp_ft3_2;
    *(s16 *)((u8 *)arg0 + 0x72) = (s16) temp_ft3;
    *(s16 *)((u8 *)arg0 + 0x70) = (s16) (s32) (temp_ft5 + temp_fa0);
    *(s16 *)((u8 *)arg0 + 0x64) = (s16) (s32) (temp_ft3_2 - temp_fv1);
    *(s16 *)((u8 *)arg0 + 0x74) = (s16) (s32) (sp30 + temp_fv1);
    return (void *)temp_ft3;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513E13C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513E13C.s")
void func_1513E2A4(void) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513E2AC.s")
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513E6E8 CURRENT (1290) */
s32 func_1513E6E8(u8 *arg0) {
    u8 *temp_v0;

    if (*(s32 *)((u8 *)arg0 + 0x58) & 0x20) {
        temp_v0 = (void *)(arg0 + 0x110);
        *(f32 *)((u8 *)temp_v0 + 0xC) += *(f32 *)((u8 *)temp_v0 + 0x2C) * D_800BE9A4;
    }
    if (*(s32 *)((u8 *)arg0 + 0x58) & 0x40) {
        temp_v0 = (void *)(arg0 + 0x110);
        *(f32 *)((u8 *)arg0 + 0x34) += *(f32 *)((u8 *)temp_v0 + 8) * D_800BE9A4;
        *(f32 *)((u8 *)arg0 + 0x38) += *(f32 *)((u8 *)temp_v0 + 0xC) * D_800BE9A4;
        *(f32 *)((u8 *)arg0 + 0x3C) += *(f32 *)((u8 *)temp_v0 + 0x10) * D_800BE9A4;
    }
    temp_v0 = (void *)(arg0 + 0x110);
    if (*(s32 *)((u8 *)arg0 + 0x58) & 0x80) {
        *(f32 *)((u8 *)arg0 + 0x40) += *(f32 *)((u8 *)temp_v0 + 0x14) * D_800BE9A4;
        *(f32 *)((u8 *)arg0 + 0x44) += *(f32 *)((u8 *)temp_v0 + 0x18) * D_800BE9A4;
        *(f32 *)((u8 *)arg0 + 0x48) += *(f32 *)((u8 *)temp_v0 + 0x1C) * D_800BE9A4;
    }
    temp_v0 = (void *)(arg0 + 0x110);
    if (*(s32 *)((u8 *)arg0 + 0x58) & 0x100) {
        *(f32 *)((u8 *)arg0 + 0x4C) += *(f32 *)((u8 *)temp_v0 + 0x20) * D_800BE9A4;
        *(f32 *)((u8 *)arg0 + 0x50) += *(f32 *)((u8 *)temp_v0 + 0x24) * D_800BE9A4;
        *(f32 *)((u8 *)arg0 + 0x54) += *(f32 *)((u8 *)temp_v0 + 0x28) * D_800BE9A4;
    }
    *(u8 *)((u8 *)arg0 + 0x5D) = 0xFF;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513E6E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513E6E8.s")
typedef struct Game169510ScaledOwner {
    u8 unknown0[0x2C];
    f32 width, height;
    f32 x, y, z;
    f32 rx, ry, rz;
    f32 sx, sy, sz;
    u8 unknown58[0x68];
    u8 templateData[0x40];
    u8 *buffers[1];
} Game169510ScaledOwner;

typedef struct Game169510ScaledVertex {
    s16 x, y, z, flag;
    u8 other[8];
} Game169510ScaledVertex;

void func_151D5D60(void *, s16, s32, void **, u8 *);
void func_150A8050(void *, f32, f32, f32);
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513E83C CURRENT (2230) */
void *func_1513E83C(Game169510ScaledOwner *owner, s32 arg1) {
    f32 matrix[4][4];
    Game169510ScaledVertex *vertices;
    void *result;
    f32 coords[4][3];
    u8 fresh;
    f32 *point;
    s16 index;
    register s32 bufferIndex = (s16)arg1;
    register f32 (*transform)[4];

    func_151D5D60(owner->buffers, bufferIndex, 0x40, (void **)&vertices, &fresh);
    result = vertices;
    if (vertices != 0) {
        if (fresh != 0) {
            func_10022EC0(owner->buffers[bufferIndex], owner->templateData, 0x40);
            func_10022EC0(owner->buffers[bufferIndex] + 0x40, owner->templateData, 0x40);
        }
    } else {
        return 0;
    }
    transform = matrix;
    coords[0][0] = owner->width;
    coords[0][1] = owner->height;
    coords[1][0] = -owner->width;
    coords[1][1] = owner->height;
    coords[2][0] = -owner->width;
    coords[2][1] = -owner->height;
    coords[3][0] = owner->width;
    coords[3][1] = -owner->height;
    func_150A8050(transform, owner->rx, owner->ry, owner->rz);
    matrix[3][0] = owner->x;
    index = 0;
    matrix[3][1] = owner->y;
    matrix[3][2] = owner->z;
    matrix[0][0] *= owner->sx;
    matrix[0][1] *= owner->sx;
    matrix[0][2] *= owner->sx;
    matrix[1][0] *= owner->sy;
    matrix[1][1] *= owner->sy;
    matrix[1][2] *= owner->sy;
    matrix[2][0] *= owner->sz;
    matrix[2][1] *= owner->sz;
    matrix[2][2] *= owner->sz;
    do {
        point = coords[index];
        func_150A7960(transform, point[0], point[1], 0.0f, &point[0], &point[1], &point[2]);
        vertices->x = (s32)point[0];
        vertices->y = (s32)point[1];
        index++;
        vertices->z = (s32)point[2];
        vertices->flag = 0;
        vertices++;
    } while (index < 4);
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513E83C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513E83C.s")

extern f32 D_800DD1D8[], D_800DD1E8[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513EAD8 CURRENT (3745) */
void func_1513EAD8(void *arg0, s32 arg1, s16 arg2) {
    Game169510ScaledVertex *vertices;
    s16 coords[4][3];
    u8 fresh;
    Game169510ScaledOwner *owner;
    u8 **slot;
    u8 *templateData;
    register f32 width, height, heightScale, directionZ, directionX;

    owner = arg0;
    func_151D5D60((u8 *)arg0 + 0x100, arg2, 0x40, (void **)&vertices, &fresh);
    if (vertices == 0) {
        return;
    }
    if (fresh != 0) {
        slot = (u8 **)((u8 *)arg0 + arg2 * 4 + 0x100);
        templateData = (u8 *)arg0 + 0xC0;
        func_10022EC0(*slot, templateData, 0x40);
        func_10022EC0(*slot + 0x40, templateData, 0x40);
    }
    directionZ = D_800DD1D8[arg2];
    directionX = D_800DD1E8[arg2];
    width = owner->width;
    height = owner->height;
    heightScale = owner->sy;
    vertices[0].flag = 0;
    directionZ *= width;
    vertices[1].flag = 0;
    directionX *= width;
    vertices[2].flag = 0;
    heightScale *= height;
    vertices[3].flag = 0;
    height -= heightScale;
    coords[3][0] = coords[0][0] = (s16)(s32)(owner->x + directionX);
    coords[1][1] = coords[0][1] = (s16)(s32)(owner->y - heightScale);
    coords[3][2] = coords[0][2] = (s16)(s32)(owner->z - directionZ);
    coords[2][0] = coords[1][0] = (s16)(s32)(owner->x - directionX);
    coords[3][1] = coords[2][1] = (s16)(s32)(owner->y + height);
    coords[2][2] = coords[1][2] = (s16)(s32)(owner->z + directionZ);
    if (*(u8 *)((u8 *)&arg1 + 3) != 0) {
        vertices[0].x = coords[1][0];
        vertices[0].y = coords[1][1];
        vertices[0].z = coords[1][2];
        vertices[1].x = coords[2][0];
        vertices[1].y = coords[2][1];
        vertices[1].z = coords[2][2];
        vertices[2].x = coords[3][0];
        vertices[2].y = coords[3][1];
        vertices[2].z = coords[3][2];
        vertices[3].x = coords[0][0];
        vertices[3].y = coords[0][1];
        vertices[3].z = coords[0][2];
    } else {
        vertices[0].x = coords[0][0];
        vertices[0].y = coords[0][1];
        vertices[0].z = coords[0][2];
        vertices[1].x = coords[1][0];
        vertices[1].y = coords[1][1];
        vertices[1].z = coords[1][2];
        vertices[2].x = coords[2][0];
        vertices[2].y = coords[2][1];
        vertices[2].z = coords[2][2];
        vertices[3].x = coords[3][0];
        vertices[3].y = coords[3][1];
        vertices[3].z = coords[3][2];
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513EAD8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513EAD8.s")
void func_1513EAD8(void *arg0, s32 arg1, s16 arg2);

void func_1513EDB4(void *arg0, s16 arg1) {
    func_1513EAD8(arg0, 0, arg1);
}
void func_1513EDE4(void *arg0, s16 arg1) {
    func_1513EAD8(arg0, 1, arg1);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513EE14 CURRENT (2650) */
void *func_1513EE14(void *arg0, s32 arg1) {
    u8 *vertices;
    void *result;
    f32 matrix[4][4];
    f32 corners[4][2];
    f32 points[4][3];
    u8 fresh;
    Game169510ScaledOwner *owner = arg0;

    func_151D5D60((u8 *)arg0 + 0x100, *(s16 *)((u8 *)&arg1 + 2), 0x40, (void **)&vertices, &fresh);
    result = vertices;
    if (vertices != 0) {
        if (fresh != 0) {
            register u8 *base = (u8 *)arg0 + *(s16 *)((u8 *)&arg1 + 2) * 4;
            register u8 *templateData = (u8 *)arg0 + 0xC0;
            func_10022EC0(*(u8 **)(base + 0x100), templateData, 0x40);
            func_10022EC0(*(u8 **)(base + 0x100) + 0x40, templateData, 0x40);
        }
    } else {
        return 0;
    }
    {
        func_150A8050(matrix, owner->rx, owner->ry, owner->rz);
        matrix[3][0] = owner->x;
        matrix[3][1] = owner->y;
        matrix[3][2] = owner->z;
        corners[0][0] = owner->width;
        corners[0][1] = owner->height;
        corners[1][0] = -owner->width;
        corners[1][1] = owner->height;
        corners[2][0] = -owner->width;
        corners[2][1] = -owner->height;
        corners[3][0] = owner->width;
        corners[3][1] = -owner->height;
        func_150A7960(matrix, corners[0][0], corners[0][1], 0.0f, &points[0][0], &points[0][1], &points[0][2]);
        func_150A7960(matrix, corners[1][0], corners[1][1], 0.0f, &points[1][0], &points[1][1], &points[1][2]);
        func_150A7960(matrix, corners[2][0], corners[2][1], 0.0f, &points[2][0], &points[2][1], &points[2][2]);
        func_150A7960(matrix, corners[3][0], corners[3][1], 0.0f, &points[3][0], &points[3][1], &points[3][2]);
        *(s16 *)(vertices + 0) = (s32)points[0][0];
        *(s16 *)(vertices + 2) = (s32)points[0][1];
        *(s16 *)(vertices + 4) = (s32)points[0][2];
        *(s16 *)(vertices + 6) = 0;
        {
            register u8 *second = vertices + 0x10;
            register u8 *third = second + 0x10;
            register u8 *fourth = third + 0x10;
            vertices = second;
            *(s16 *)(second + 0) = (s32)points[1][0];
            *(s16 *)(second + 2) = (s32)points[1][1];
            *(s16 *)(second + 6) = 0;
            *(s16 *)(second + 4) = (s32)points[1][2];
            vertices = third;
            *(s16 *)(third + 0) = (s32)points[2][0];
            *(s16 *)(third + 2) = (s32)points[2][1];
            *(s16 *)(third + 6) = 0;
            *(s16 *)(third + 4) = (s32)points[2][2];
            vertices = fourth;
            *(s16 *)(fourth + 0) = (s32)points[3][0];
            *(s16 *)(fourth + 2) = (s32)points[3][1];
            *(s16 *)(fourth + 6) = 0;
            *(s16 *)(fourth + 4) = (s32)points[3][2];
        }
        return result;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513EE14 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513EE14.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513F114.s")
s32 func_15140410(s32, s32, s32, s16);

void func_1513F4B0(s32 arg0, s16 arg1) {
    func_15140410(arg0, arg0 + 0x110, arg0 + 0x11C, arg1);
}
s16 func_15143044(u8, s32);
extern u8 D_800A4BA8[];
extern s16 D_800DD1BE;

typedef struct {
    u32 w0;
    u32 w1;
} Game169510Gwords;

typedef union {
    Game169510Gwords words;
} Gfx;

#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#define G_SETCOMBINE 0xfc
#define G_RDPPIPESYNC 0xe7
#define gDPNoParam(pkt, cmd) \
{ \
    Gfx *_g = (Gfx *)(pkt); \
 \
    _g->words.w0 = _SHIFTL(cmd, 24, 8); \
    _g->words.w1 = 0; \
}
#define gDPPipeSync(pkt) gDPNoParam(pkt, G_RDPPIPESYNC)
#define gDPSetCombine(pkt, muxs0, muxs1) \
{ \
    Gfx *_g = (Gfx *)(pkt); \
 \
    _g->words.w0 = _SHIFTL(G_SETCOMBINE, 24, 8) | _SHIFTL(muxs0, 0, 24); \
    _g->words.w1 = (u32)(muxs1); \
}
#define GCCc0w0(saRGB0, mRGB0, saA0, mA0) \
    (_SHIFTL((saRGB0), 20, 4) | _SHIFTL((mRGB0), 15, 5) | \
     _SHIFTL((saA0), 12, 3) | _SHIFTL((mA0), 9, 3))
#define GCCc1w0(saRGB1, mRGB1) \
    (_SHIFTL((saRGB1), 5, 4) | _SHIFTL((mRGB1), 0, 5))
#define GCCc0w1(sbRGB0, aRGB0, sbA0, aA0) \
    (_SHIFTL((sbRGB0), 28, 4) | _SHIFTL((aRGB0), 15, 3) | \
     _SHIFTL((sbA0), 12, 3) | _SHIFTL((aA0), 9, 3))
#define GCCc1w1(sbRGB1, saA1, mA1, aRGB1, sbA1, aA1) \
    (_SHIFTL((sbRGB1), 24, 4) | _SHIFTL((saA1), 21, 3) | \
     _SHIFTL((mA1), 18, 3) | _SHIFTL((aRGB1), 6, 3) | \
     _SHIFTL((sbA1), 3, 3) | _SHIFTL((aA1), 0, 3))

Gfx *func_1513F4E4(Gfx *gdl, u8 arg1, u8 *arg2) {
    extern s16 D_800DD1BE;
    extern u8 D_800A4BA8[];
    s32 v0;
    u8 *p;

    v0 = func_15143044(arg1, 0);
    if (v0 != D_800DD1BE) {
        if (*arg2 == 1) {
            gDPPipeSync(gdl++);
            *arg2 = 0;
        }
        p = &D_800A4BA8[arg1 * 16];
        gDPSetCombine(gdl++,
            GCCc0w0(p[0], p[2], p[4], p[6]) | GCCc1w0(p[8], p[10]),
            GCCc0w1(p[1], p[3], p[5], p[7]) | GCCc1w1(p[9], p[12], p[14], p[11], p[13], p[15]));
        D_800DD1BE = v0;
    }
    return gdl;
}
void func_1513F680(void *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4) {
    *(s8 *)((u8 *)arg0 + 0x70) = arg1;
    *(s8 *)((u8 *)arg0 + 0x71) = arg2;
    *(s8 *)((u8 *)arg0 + 0x72) = arg3;
    *(u8 *)((u8 *)arg0 + 0x73) = arg4;
}
void func_1513F6C0(void *arg0, u8 arg1, u8 arg2) {
    *(u8 *)((u8 *)arg0 + 0x80) = arg1;
    *(u8 *)((u8 *)arg0 + 0x81) = arg2;
}
extern f32 D_800BE9A4;

s32 func_1513F6E8(void *arg0) {
    f32 temp_fv0;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x128);
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (*(f32 *)((u8 *)arg0 + 0x2C) + (temp_fv0 * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (*(f32 *)((u8 *)arg0 + 0x30) + (temp_fv0 * D_800BE9A4));
    return 1;
}
extern f32 D_800BE9A8;

typedef struct Game169510Velocity {
    f32 x, y, z;
    f32 gravity;
    f32 damping;
    f32 rx, ry, rz;
} Game169510Velocity;

typedef struct Game169510VelocitySnapshot {
    f32 x, y, z;
} Game169510VelocitySnapshot;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513F728 CURRENT (870) */
s32 func_1513F728(void *arg0) {
    Game169510VelocitySnapshot previous;
    Game169510Velocity *velocity;
    Game169510ScaledOwner *owner = arg0;
    u32 count;
    f32 dx, dy, dz;

    velocity = (Game169510Velocity *)((u8 *)arg0 + 0x110);
    previous = *(Game169510VelocitySnapshot *)velocity;
    for (count = D_800BE9E4; count != 0; count--) {
        velocity->x *= velocity->damping;
        velocity->y *= velocity->damping;
        velocity->z *= velocity->damping;
    }
    velocity->y += velocity->gravity * D_800BE9A4;
    dx = (velocity->x - previous.x) * D_800BE9A8;
    dy = (velocity->y - previous.y) * D_800BE9A8;
    dz = (velocity->z - previous.z) * D_800BE9A8;
    owner->x += (previous.x + 0.5f * dx * D_800BE9A4) * D_800BE9A4;
    owner->y += (previous.y + 0.5f * dy * D_800BE9A4) * D_800BE9A4;
    owner->z += (previous.z + 0.5f * dz * D_800BE9A4) * D_800BE9A4;
    owner->rx += velocity->rx * D_800BE9A4;
    owner->ry += velocity->ry * D_800BE9A4;
    owner->rz += velocity->rz * D_800BE9A4;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513F728 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513F728.s")

extern void func_1513FAB4(void *arg0, s32 arg1, f32 *arg2, s16 arg3);

void func_1513FA2C(void *arg0, s16 arg1) {
    f32 sp18[2];

    sp18[0] = 1.0f;
    sp18[1] = 1.0f;
    func_1513FAB4(arg0, 0, sp18, arg1);
}
void func_1513FA70(void *arg0, s16 arg1) {
    f32 sp18[2];

    sp18[0] = 1.0f;
    sp18[1] = 1.0f;
    func_1513FAB4(arg0, 1, sp18, arg1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513FAB4.s")
typedef struct {
    u8 pad0[6];
    u16 width;
    u16 height;
    u8 padA[2];
} Game169510TextureInfo;

extern Game169510TextureInfo D_80090B60[];

void func_1513FFF4(void *arg0, u8 arg1, u8 arg2) {
    typedef struct {
        s16 ob[3];
        u16 flag;
        s16 tc[2];
        u8 cn[4];
    } LocalVtx_t;
    typedef struct {
        LocalVtx_t v;
    } LocalVtx;
    Game169510TextureInfo *p;
    s32 a;
    u16 w;
    u16 h;

    if (arg1 == 0xFF) {
        return;
    }
    p = &D_80090B60[arg1];
    w = p->width - 1;
    h = p->height - 1;
    a = (arg2 & 1) ? (w << 6) : 0;
    ((LocalVtx *)arg0)[3].v.tc[0] = a;
    ((LocalVtx *)arg0)[0].v.tc[0] = a;
    a = (arg2 & 1) ? 0 : (w << 6);
    ((LocalVtx *)arg0)[2].v.tc[0] = a;
    ((LocalVtx *)arg0)[1].v.tc[0] = a;
    a = (arg2 & 2) ? (h << 6) : 0;
    ((LocalVtx *)arg0)[1].v.tc[1] = a;
    ((LocalVtx *)arg0)[0].v.tc[1] = a;
    a = (arg2 & 2) ? 0 : (h << 6);
    ((LocalVtx *)arg0)[3].v.tc[1] = a;
    ((LocalVtx *)arg0)[2].v.tc[1] = a;
}
void func_151400D0(void *arg0, void *arg1) {
    *(u16 *)((u8 *)arg0 + 6) = *(u16 *)((u8 *)arg1 + 8);
    arg0 = (u8 *)arg0 + 0x30;
    arg1 = (u8 *)arg1 + 0x1E;
    *(s8 *)((u8 *)arg0 + -0x24) = (s8) *(s16 *)((u8 *)arg1 + -0x1E);
    *(s8 *)((u8 *)arg0 + -0x23) = (s8) *(s16 *)((u8 *)arg1 + -0x1C);
    *(s8 *)((u8 *)arg0 + -0x22) = (s8) *(s16 *)((u8 *)arg1 + -0x1A);
    *(s8 *)((u8 *)arg0 + -0x21) = (s8) *(s16 *)((u8 *)arg1 + -0x18);
    *(u16 *)((u8 *)arg0 + -0x2A) = 0U;
    *(u16 *)((u8 *)arg0 + -0x1A) = (u16) *(u16 *)((u8 *)arg1 + -0xC);
    *(s8 *)((u8 *)arg0 + -0x14) = (s8) *(s16 *)((u8 *)arg1 + -0x14);
    *(s8 *)((u8 *)arg0 + -0x13) = (s8) *(s16 *)((u8 *)arg1 + -0x12);
    *(s8 *)((u8 *)arg0 + -0x12) = (s8) *(s16 *)((u8 *)arg1 + -0x10);
    *(s8 *)((u8 *)arg0 + -0x11) = (s8) *(s16 *)((u8 *)arg1 + -0xE);
    *(u16 *)((u8 *)arg0 + -0x1A) = 0U;
    *(u16 *)((u8 *)arg0 + -0xA) = (u16) *(u16 *)((u8 *)arg1 + -2);
    *(s8 *)((u8 *)arg0 + -4) = (s8) *(s16 *)((u8 *)arg1 + -0xA);
    *(s8 *)((u8 *)arg0 + -3) = (s8) *(s16 *)((u8 *)arg1 + -8);
    *(s8 *)((u8 *)arg0 + -2) = (s8) *(s16 *)((u8 *)arg1 + -6);
    *(s8 *)((u8 *)arg0 + -1) = (s8) *(s16 *)((u8 *)arg1 + -4);
    *(u16 *)((u8 *)arg0 + -0xA) = 0U;
    *(u16 *)((u8 *)arg0 + 6) = (u16) *(u16 *)((u8 *)arg1 + 8);
    *(s8 *)((u8 *)arg0 + 0xC) = (s8) *(s16 *)arg1;
    *(s8 *)((u8 *)arg0 + 0xD) = (s8) *(s16 *)((u8 *)arg1 + 2);
    *(s8 *)((u8 *)arg0 + 0xE) = (s8) *(s16 *)((u8 *)arg1 + 4);
    *(s8 *)((u8 *)arg0 + 0xF) = (s8) *(s16 *)((u8 *)arg1 + 6);
    *(u16 *)((u8 *)arg0 + 6) = 0U;
}
typedef struct Game169510RenderOwner {
    u8 pad00[0x2C];
    f32 width, height, x, y, z, rx, ry, rz;
    u8 pad4C[0x74];
    u8 templateData[0x40];
    u8 *buffers[1];
} Game169510RenderOwner;
typedef struct Game169510Vertex {
    s16 x, y, z, flag;
    u8 other[8];
} Game169510Vertex;
void func_151D5D60(void *, s16, s32, void **, u8 *);
void func_150A8050(void *, f32, f32, f32);
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15140190 CURRENT (1466) */
void *func_15140190(Game169510RenderOwner *arg0, s32 arg1) {
    Game169510Vertex *vertices;
    void *result;
    f32 matrix[4][4];
    f32 coords[4][3];
    u8 fresh;
    f32 *point;
    u8 index;
    s16 bufferIndex = (s16)arg1;

    func_151D5D60(arg0->buffers, bufferIndex, 0x40, (void **)&vertices, &fresh);
    result = vertices;
    if (vertices != 0) {
        if (fresh != 0) {
            func_10022EC0(arg0->buffers[bufferIndex], arg0->templateData, 0x40);
            func_10022EC0(arg0->buffers[bufferIndex] + 0x40, arg0->templateData, 0x40);
        }
    } else {
        return 0;
    }
    coords[0][0] = arg0->width;
    coords[0][1] = arg0->height;
    coords[0][2] = 0.0f;
    coords[1][0] = -arg0->width;
    coords[1][1] = arg0->height;
    coords[1][2] = 0.0f;
    coords[2][0] = -arg0->width;
    coords[2][1] = -arg0->height;
    coords[2][2] = 0.0f;
    coords[3][0] = arg0->width;
    coords[3][1] = -arg0->height;
    coords[3][2] = 0.0f;
    func_150A8050(matrix, arg0->rx, arg0->ry, arg0->rz);
    index = 0;
    matrix[3][0] = arg0->x;
    matrix[3][1] = arg0->y;
    matrix[3][2] = arg0->z;
    do {
        point = coords[index];
        func_150A7960(matrix, point[0], point[1], 0.0f, &point[0], &point[1], &point[2]);
        vertices->x = (s32)point[0];
        vertices->y = (s32)point[1];
        vertices->z = (s32)point[2];
        vertices->flag = 0;
        vertices++;
        index++;
    } while (index < 4);
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15140190 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_15140190.s")
void func_15169260(void *arg0, s32 arg1, s32 arg2, u8 arg3);
extern u8 D_800A5168;

void func_151403A8(s32 arg0, u8 arg1) {
    func_15169260(&D_800A5168, 4, arg0, arg1);
}
extern u8 D_800A5178;

void func_151403DC(s32 arg0, u8 arg1) {
    func_15169260(&D_800A5178, 3, arg0, arg1);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15140410 CURRENT (730) */
s32 func_15140410(s32 arg0, s32 arg1, s32 arg2, s16 arg3) {
    Game169510Vertex *vertices;
    register void *result;
    u8 fresh;
    register f32 width, height;
    f32 ax, ay, az, bx, by, bz;
    register Game169510RenderOwner *slot;
    register void *templateData;

    func_151D5D60(((Game169510RenderOwner *)arg0)->buffers, arg3, 0x40, (void **)&vertices, &fresh);
    result = vertices;
    if (vertices != 0) {
        if (fresh != 0) {
            slot = (Game169510RenderOwner *)((u8 *)arg0 + arg3 * 4);
            templateData = ((Game169510RenderOwner *)arg0)->templateData;
            func_10022EC0(slot->buffers[0], templateData, 0x40);
            func_10022EC0(slot->buffers[0] + 0x40, templateData, 0x40);
        }
    } else {
        return 0;
    }
    width = ((Game169510RenderOwner *)arg0)->width;
    ax = ((f32 *)arg1)[0] * width;
    height = ((Game169510RenderOwner *)arg0)->height;
    ay = ((f32 *)arg1)[1] * width;
    az = ((f32 *)arg1)[2] * width;
    bx = ((f32 *)arg2)[0] * height;
    by = ((f32 *)arg2)[1] * height;
    bz = ((f32 *)arg2)[2] * height;
    vertices[0].x = (s32)(((Game169510RenderOwner *)arg0)->x + ax + bx);
    vertices[0].y = (s32)(((Game169510RenderOwner *)arg0)->y + ay + by);
    vertices[0].z = (s32)(((Game169510RenderOwner *)arg0)->z + az + bz);
    vertices[0].flag = 0;
    vertices[1].x = (s32)((((Game169510RenderOwner *)arg0)->x - ax) + bx);
    vertices[1].y = (s32)((((Game169510RenderOwner *)arg0)->y - ay) + by);
    vertices[1].z = (s32)((((Game169510RenderOwner *)arg0)->z - az) + bz);
    vertices[1].flag = 0;
    vertices[2].x = (s32)((((Game169510RenderOwner *)arg0)->x - ax) - bx);
    vertices[2].y = (s32)((((Game169510RenderOwner *)arg0)->y - ay) - by);
    vertices[2].z = (s32)((((Game169510RenderOwner *)arg0)->z - az) - bz);
    vertices[2].flag = 0;
    vertices[3].x = (s32)((((Game169510RenderOwner *)arg0)->x + ax) - bx);
    vertices[3].y = (s32)((((Game169510RenderOwner *)arg0)->y + ay) - by);
    vertices[3].z = (s32)((((Game169510RenderOwner *)arg0)->z + az) - bz);
    vertices[3].flag = 0;
    return (s32)result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15140410 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_15140410.s")
typedef struct Game169510Node {
    u8 pad00[4];
    struct Game169510Node *prev;
    struct Game169510Node *next;
    u8 pad0C[0xC];
    u8 field18;
    u8 pad19[7];
    s32 field20;
} Game169510Node;

extern Game169510Node *D_800DCE50[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151406AC CURRENT (1037) */
s32 func_151406AC(s32 arg0, s32 arg1, s32 arg2, s16 arg3) {
    Game169510Node sp28;
    Game169510Node **temp_v1;
    Game169510Node *temp_a2;
    Game169510Node *temp_t0;
    Game169510Node *temp_t0_2;
    Game169510Node *temp_t7;
    Game169510Node *temp_v0;
    Game169510Node *var_a1;
    register s32 temp_t1;
    register s32 temp_t2;

    if (arg3 != 0) {
        return arg0;
    }
    temp_v1 = (Game169510Node **)((u32)D_800DCE50 +
        ((((((u32)arg2 << 2) - (u32)arg2) << 2) + (u32)arg2) << 5) + ((u32)arg1 << 2));
    temp_v0 = *temp_v1;
    sp28.field18 = 0;
    sp28.field20 = 0;
    sp28.next = temp_v0;
    temp_v0->prev = &sp28;
    if (temp_v0 != 0) {
        var_a1 = temp_v0->next;
        if (var_a1 != 0) {
            do {
                temp_t1 = (var_a1->field18 << 8) +
                          (var_a1->field20 >> 16);
                temp_a2 = var_a1->prev;
                temp_t0 = var_a1->next;
                temp_v0 = temp_a2;
                if (temp_a2 != 0) {
loop_5:
                    temp_t2 = (temp_v0->field18 << 8) +
                              (temp_v0->field20 >> 16);
                    if (temp_t1 >= temp_t2) {
                        if (temp_v0 != temp_a2) {
                            temp_a2->next = temp_t0;
                            temp_t0_2 = var_a1->next;
                            if (temp_t0_2 != 0) {
                                temp_t0_2->prev = var_a1->prev;
                            }
                            temp_t7 = temp_v0->next;
                            var_a1->next = temp_t7;
                            if (temp_t7 != 0) {
                                temp_t7->prev = var_a1;
                            }
                            var_a1->prev = temp_v0;
                            temp_v0->next = var_a1;
                        }
                    } else {
                        temp_v0 = temp_v0->prev;
                        if (temp_v0 != 0) {
                            goto loop_5;
                        }
                    }
                }
                var_a1 = temp_t0;
            } while (temp_t0 != 0);
        }
    }
    *temp_v1 = sp28.next;
    sp28.next->prev = 0;
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151406AC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_151406AC.s")
