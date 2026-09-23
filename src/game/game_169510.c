#include "types.h"

/*
 * Reviewed source unit: src/game/game_169510.c
 * Boundary evidence: docs/evidence/game_dispatcher_callback_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1513C060
 * - func_1513C350
 * - func_1513C4EC
 * - func_1513C5B0
 * - func_1513C73C
 * - func_1513C92C
 * - func_1513CAD4
 * - func_1513CBF0
 * - func_1513CF9C
 * - func_1513CFE4
 * - func_1513D2F0
 * - func_1513D668
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
 * - func_1513F4E4
 * - func_1513F680
 * - func_1513F728
 * - func_1513FAB4
 * - func_1513FFF4
 * - func_151400D0
 * - func_15140190
 * - func_15140410
 * - func_151406AC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_1513C92C(s32 arg0);
void func_15169804(s32 arg0);
void func_15169824(s32 arg0);
void func_1513CAD4(s32 arg0);

#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513C060.s")
typedef struct Game169510Vec3 {
    s32 x;
    s32 y;
    s32 z;
} Game169510Vec3;

void *func_10022EC0(void *, const void *, u32);
void *func_15167A68(s32, s32, s32, s32, u8, u8);
void func_1513FFF4(void *, s32, s32);
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513C4EC CURRENT (920) */
void *func_1513C4EC(s32 arg0, s32 arg1, u8 arg2, u8 arg3, f32 arg4,
    f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 arg10, s32 arg11,
    s32 arg12, s32 arg13, u8 arg14, s32 arg15) {
    struct {
        f32 first;
        f32 second;
        f32 third;
    } packet;
    void *temp_v0;

    packet.first = arg4;
    packet.second = arg5;
    packet.third = arg6;
    temp_v0 = func_1513C350(arg0, arg1, arg2 & 0xFF, arg3 & 0xFF,
        (s32)arg10, arg11, arg12, &packet, arg13, (s32)arg14, arg15);
    if (temp_v0 == 0) {
        return 0;
    }
    func_1513E13C(temp_v0, arg4, arg5, arg6, arg7, arg8, arg9);
    return temp_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513C4EC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513C4EC.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513C5B0 CURRENT (4397) */
void *func_1513C5B0(s32 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 arg10, s32 arg11, u8 arg12, s32 arg13) {
    void *sp3C;
    void *temp_v0;

    temp_v0 = func_1513C350(arg2 & 0xFF, arg3 & 0xFF, (s32) arg10, 0, 0, 0, arg11, (s32) arg12, arg13);
    if (temp_v0 == 0) {
        return 0;
    }
    sp3C = temp_v0;
    func_1513E13C(temp_v0, arg4, arg5, arg6, arg7, arg8, (u8) (s32) arg9);
    return sp3C;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513C5B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513C5B0.s")
s32 func_1513E2AC(void *, s32, s32, s32, f32, f32, f32, f32, s32);
void func_1516972C();

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
    if (func_1513E2AC(object, 0, arg3, *(s32 *)&arg4, arg5, arg6, arg7, arg8,
                      (s32)arg9) == 0) {
        func_1516972C(object);
        return 0;
    }
    return object;
}

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513C73C CURRENT (183) */
void *func_1513C73C(s32 arg0, u8 arg1, u8 arg2, s32 arg3, s32 arg4,
    f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 arg10, s32 arg11,
    u8 arg12, s32 arg13) {
    void *temp_v0;

    temp_v0 = func_1513C350(arg0, 0, (s32)arg1, (s32)arg2, (s32)arg10,
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
#endif /* CONKER_DEFERRED_CANDIDATE func_1513C73C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513C73C.s")
void *func_1513C804(s32 arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4,
                    s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9,
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
void func_1513C8D4(s32 arg0) {
    func_1513C92C(arg0);
    func_15169804(arg0);
}
void func_1513C900(s32 arg0) {
    func_1513C92C(arg0);
    func_15169824(arg0);
}
void func_100043B4(s32, s32);
extern s32 D_80082FA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513C92C CURRENT (890) */
void func_1513C92C(s32 arg0) {
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
void func_1513CA48(s32 arg0) {
    func_151D5E30(arg0 + 0x100, arg0);
}
void func_1513CA6C(s32 arg0) {
    func_1513CA48(arg0);
    func_1513CAD4(arg0);
    func_15169804(arg0);
}
void func_1513CAA0(s32 arg0) {
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
extern void (*D_80089F60)(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513CF9C CURRENT (430) */
void func_1513CF9C(s32 arg0, s32 arg1, s32 arg2) {
    D_80089F60(arg2 & 0xFF);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513CF9C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513CF9C.s")
void func_1513CFD0(s32 arg0, s32 arg1, s32 arg2) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513CFE4.s")
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
    volatile void *sp3C;
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513D668 CURRENT (1582) */
void func_1513D668(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5, s16 arg6, f32 arg7, f32 arg8, s32 arg9, s32 arg10, u8 arg11, s32 arg12, u8 arg13, s32 arg14) {
    s32 temp_a2 = arg2;
    s32 temp_a3 = arg3;

    func_1513D594(arg0, arg1, temp_a2 & 0xFF, temp_a3 & 0xFF, (s32)arg4, (s32)arg5, (s32)arg6,
                  arg7, arg8, arg9, arg10, 0, 0, (s32)arg11, arg12, (s32)arg13, arg14);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513D668 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513D668.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513D6FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513DB00.s")
extern void (*D_80089F64[])(void *, s32, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513DF9C CURRENT (1075) */
void func_1513DF9C(void *arg0, s32 arg1, u8 arg2) {
    s32 index;
    u8 type;

    if (*(s32 *)((u8 *)arg0 + 0x58) & 0x400000) {
        type = *(u8 *)((u8 *)arg0 + 0x19);
    } else {
        type = 0;
    }
    switch (type) {
    case 12:
        index = 10;
        break;
    case 11:
        index = 9;
        break;
    default:
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
    }
    D_80089F64[index](arg0, arg1, arg2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513DF9C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513DF9C.s")
void func_1513E070(s32 arg0, s32 arg1, s32 arg2) {
}
void func_1516972C(void *, s32, void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513E084 CURRENT (1552) */
void func_1513E084(void *arg0, void *arg1, s32 arg2) {
    u8 *state;
    s32 event;
    s32 current;
    s32 incoming;

    state = (u8 *)arg0 + 0x110;
    event = arg2 & 0xFF;
    if (event == 0x1A) {
        if ((*(s32 *)arg1 == *(s32 *)state) ||
            (*(u8 *)((u8 *)arg1 + 4) == *(u8 *)(state + 4))) {
            func_1516972C(arg0, event, arg0);
        }
        return;
    }
    if (event != 0x2D) {
        return;
    }
    current = *(s32 *)state;
    incoming = *(s32 *)arg1;
    if (incoming == current) {
        *(s32 *)state = *(s32 *)((u8 *)arg1 + 4);
        *(u8 *)(state + 4) = *(u8 *)((u8 *)arg1 + 9);
    } else if (*(s32 *)((u8 *)arg1 + 4) == current) {
        *(s32 *)state = incoming;
        *(u8 *)(state + 4) = *(u8 *)((u8 *)arg1 + 8);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513E084 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513E084.s")
/* Call context: func_151423D8: unique active project prototype */
f32 func_151423D8(u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513E13C CURRENT (3972) */
void func_1513E13C(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6) {
    f32 sp48;
    f32 sp30;
    f32 sp1C;
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

    sp48 = func_151423D8((arg6 - 0x40) & 0xFF);
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
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513E13C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513E13C.s")
void func_1513E2A4(void) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513E2AC.s")
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513E6E8 CURRENT (1465) */
s32 func_1513E6E8(u8 *arg0) {
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *temp_v0_4;

    if (*(s32 *)((u8 *)arg0 + 0x58) & 0x20) {
        temp_v0 = (void *)(arg0 + 0x110);
        *(f32 *)((u8 *)temp_v0 + 0xC) = (f32) (*(f32 *)((u8 *)temp_v0 + 0xC) + (*(f32 *)((u8 *)temp_v0 + 0x2C) * D_800BE9A4));
    }
    if (*(s32 *)((u8 *)arg0 + 0x58) & 0x40) {
        temp_v0_2 = (void *)(arg0 + 0x110);
        *(f32 *)((u8 *)arg0 + 0x34) = (f32) (*(f32 *)((u8 *)arg0 + 0x34) + (*(f32 *)((u8 *)temp_v0_2 + 8) * D_800BE9A4));
        *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)arg0 + 0x38) + (*(f32 *)((u8 *)temp_v0_2 + 0xC) * D_800BE9A4));
        *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C) + (*(f32 *)((u8 *)temp_v0_2 + 0x10) * D_800BE9A4));
    }
    temp_v0_3 = (void *)(arg0 + 0x110);
    if (*(s32 *)((u8 *)arg0 + 0x58) & 0x80) {
        *(f32 *)((u8 *)arg0 + 0x40) = (f32) (*(f32 *)((u8 *)arg0 + 0x40) + (*(f32 *)((u8 *)temp_v0_3 + 0x14) * D_800BE9A4));
        *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)arg0 + 0x44) + (*(f32 *)((u8 *)temp_v0_3 + 0x18) * D_800BE9A4));
        *(f32 *)((u8 *)arg0 + 0x48) = (f32) (*(f32 *)((u8 *)arg0 + 0x48) + (*(f32 *)((u8 *)temp_v0_3 + 0x1C) * D_800BE9A4));
    }
    temp_v0_4 = (void *)(arg0 + 0x110);
    if (*(s32 *)((u8 *)arg0 + 0x58) & 0x100) {
        *(f32 *)((u8 *)arg0 + 0x4C) = (f32) (*(f32 *)((u8 *)arg0 + 0x4C) + (*(f32 *)((u8 *)temp_v0_4 + 0x20) * D_800BE9A4));
        *(f32 *)((u8 *)arg0 + 0x50) = (f32) (*(f32 *)((u8 *)arg0 + 0x50) + (*(f32 *)((u8 *)temp_v0_4 + 0x24) * D_800BE9A4));
        *(f32 *)((u8 *)arg0 + 0x54) = (f32) (*(f32 *)((u8 *)arg0 + 0x54) + (*(f32 *)((u8 *)temp_v0_4 + 0x28) * D_800BE9A4));
    }
    *(s8 *)((u8 *)arg0 + 0x5D) = 0xFF;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513E6E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513E6E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513E83C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513EAD8.s")
void func_1513EAD8(void *arg0, s32 arg1, s16 arg2);

void func_1513EDB4(void *arg0, s16 arg1) {
    func_1513EAD8(arg0, 0, arg1);
}
void func_1513EDE4(void *arg0, s16 arg1) {
    func_1513EAD8(arg0, 1, arg1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513EE14.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513F114.s")
s32 func_15140410(s32, s32, s32, s16);

void func_1513F4B0(s32 arg0, s16 arg1) {
    func_15140410(arg0, arg0 + 0x110, arg0 + 0x11C, arg1);
}
s16 func_15143044(u8, s32, s32 *);
extern u8 D_800A4BA8[];
extern s16 D_800DD1BE;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513F4E4 CURRENT (2899) */
s32 *func_1513F4E4(s32 *arg0, u8 arg1, u8 *arg2) {
    s16 selected;
    s32 *output;
    u8 *entry;

    selected = func_15143044(arg1, 0, arg0);
    output = arg0;
    if (selected != D_800DD1BE) {
        if (*arg2 == 1) {
            output[0] = 0xE7000000;
            output += 2;
            output[-1] = 0;
            *arg2 = 0;
        }
        entry = D_800A4BA8 + ((u8)arg1 * 16);
        output[0] = 0xFC000000 | (((entry[10] & 0x1F) |
                      ((entry[8] & 0xF) << 5) |
                      ((entry[0] & 0xF) << 20) |
                      ((entry[2] & 0x1F) << 15) |
                      ((entry[4] & 7) << 12) |
                      ((entry[6] & 7) << 9)) & 0xFFFFFF);
        output[1] = (entry[15] & 7) |
                    ((entry[9] & 0xF) << 24) |
                    ((entry[12] & 7) << 21) |
                    ((entry[14] & 7) << 18) |
                    ((entry[11] & 7) << 6) |
                    ((entry[13] & 7) << 3) |
                    (entry[1] << 28) |
                    ((entry[3] & 7) << 15) |
                    ((entry[5] & 7) << 12) |
                    ((entry[7] & 7) << 9);
        output += 2;
        D_800DD1BE = selected;
    }
    return output;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513F4E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513F4E4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513F680 CURRENT (900) */
void func_1513F680(void *arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4) {
    *(s8 *)((u8 *)arg0 + 0x70) = (s8) (arg1 & 0xFF);
    *(s8 *)((u8 *)arg0 + 0x71) = (s8) (arg2 & 0xFF);
    *(s8 *)((u8 *)arg0 + 0x72) = (s8) (arg3 & 0xFF);
    *(u8 *)((u8 *)arg0 + 0x73) = arg4;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513F680 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513F680.s")
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1513FFF4 CURRENT (2920) */
void func_1513FFF4(void *arg0, s32 arg1, s32 arg2) {
    s16 first_width;
    s16 second_width;
    s16 first_height;
    s16 second_height;
    s32 texture_index;
    s32 flags;
    u8 *output;

    texture_index = arg1 & 0xFF;
    flags = arg2 & 0xFF;
    output = arg0;
    if (texture_index != 0xFF) {
        Game169510TextureInfo *texture;
        s32 width;
        s32 height;

        texture = &D_80090B60[texture_index];
        width = (texture->width - 1) & 0xFFFF;
        height = (texture->height - 1) & 0xFFFF;
        if (flags & 1) {
            first_width = width << 6;
        } else {
            first_width = 0;
        }
        *(s16 *)(output + 0x38) = first_width;
        *(s16 *)(output + 8) = first_width;
        if (flags & 1) {
            second_width = 0;
        } else {
            second_width = width << 6;
        }
        *(s16 *)(output + 0x28) = second_width;
        *(s16 *)(output + 0x18) = second_width;
        if (flags & 2) {
            first_height = height << 6;
        } else {
            first_height = 0;
        }
        *(s16 *)(output + 0x1A) = first_height;
        *(s16 *)(output + 0xA) = first_height;
        if (flags & 2) {
            second_height = 0;
        } else {
            second_height = height << 6;
        }
        *(s16 *)(output + 0x3A) = second_height;
        *(s16 *)(output + 0x2A) = second_height;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1513FFF4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513FFF4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151400D0 CURRENT (1055) */
void func_151400D0(u8 *arg0, u8 *arg1) {
    u8 *temp_a0;
    u8 *temp_a1;

    temp_a0 = (void *)(arg0 + 0x30);
    temp_a1 = (void *)(arg1 + 0x1E);
    *(u16 *)((u8 *)temp_a0 + -0x2A) = (u16) *(u16 *)((u8 *)arg1 + 8);
    *(s8 *)((u8 *)temp_a0 + -0x24) = (s8) *(s16 *)((u8 *)temp_a1 + -0x1E);
    *(s8 *)((u8 *)temp_a0 + -0x23) = (s8) *(s16 *)((u8 *)temp_a1 + -0x1C);
    *(s8 *)((u8 *)temp_a0 + -0x22) = (s8) *(s16 *)((u8 *)temp_a1 + -0x1A);
    *(u16 *)((u8 *)temp_a0 + -0x2A) = 0U;
    *(s8 *)((u8 *)temp_a0 + -0x21) = (s8) *(s16 *)((u8 *)temp_a1 + -0x18);
    *(u16 *)((u8 *)temp_a0 + -0x1A) = (u16) *(u16 *)((u8 *)temp_a1 + -0xC);
    *(s8 *)((u8 *)temp_a0 + -0x14) = (s8) *(s16 *)((u8 *)temp_a1 + -0x14);
    *(s8 *)((u8 *)temp_a0 + -0x13) = (s8) *(s16 *)((u8 *)temp_a1 + -0x12);
    *(s8 *)((u8 *)temp_a0 + -0x12) = (s8) *(s16 *)((u8 *)temp_a1 + -0x10);
    *(u16 *)((u8 *)temp_a0 + -0x1A) = 0U;
    *(s8 *)((u8 *)temp_a0 + -0x11) = (s8) *(s16 *)((u8 *)temp_a1 + -0xE);
    *(u16 *)((u8 *)temp_a0 + -0xA) = (u16) *(u16 *)((u8 *)temp_a1 + -2);
    *(s8 *)((u8 *)temp_a0 + -4) = (s8) *(s16 *)((u8 *)temp_a1 + -0xA);
    *(s8 *)((u8 *)temp_a0 + -3) = (s8) *(s16 *)((u8 *)temp_a1 + -8);
    *(s8 *)((u8 *)temp_a0 + -2) = (s8) *(s16 *)((u8 *)temp_a1 + -6);
    *(u16 *)((u8 *)temp_a0 + -0xA) = 0U;
    *(s8 *)((u8 *)temp_a0 + -1) = (s8) *(s16 *)((u8 *)temp_a1 + -4);
    *(u16 *)((u8 *)temp_a0 + 6) = (u16) *(u16 *)((u8 *)temp_a1 + 8);
    *(s8 *)((u8 *)temp_a0 + 0xC) = (s8) *(s16 *)((u8 *)arg1 + 0x1E);
    *(s8 *)((u8 *)temp_a0 + 0xD) = (s8) *(s16 *)((u8 *)temp_a1 + 2);
    *(s8 *)((u8 *)temp_a0 + 0xE) = (s8) *(s16 *)((u8 *)temp_a1 + 4);
    *(u16 *)((u8 *)temp_a0 + 6) = 0U;
    *(s8 *)((u8 *)temp_a0 + 0xF) = (s8) *(s16 *)((u8 *)temp_a1 + 6);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151400D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_151400D0.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_15140410.s")
typedef struct Game169510Node {
    u8 pad00[4];
    struct Game169510Node *prev;
    struct Game169510Node *next;
    u8 pad0C[0xC];
    u8 field18;
    u8 pad19[7];
    s32 field20;
    u8 pad24[0xEC];
} Game169510Node;

extern Game169510Node *D_800DCE50[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151406AC CURRENT (821) */
s32 func_151406AC(s32 arg0, s32 arg1, s32 arg2, s16 arg3) {
    Game169510Node sp28;
    Game169510Node **temp_v1;
    Game169510Node *temp_a2;
    Game169510Node *temp_t0;
    Game169510Node *temp_t0_2;
    Game169510Node *temp_t7;
    Game169510Node *temp_v0;
    Game169510Node *var_a1;
    Game169510Node *var_v0;
    register s32 temp_t1;
    register s32 temp_t2;

    if (arg3 != 0) {
        return arg0;
    }
    temp_v1 = (Game169510Node **)((u8 *)D_800DCE50 +
        (((((arg2 << 2) - arg2) << 2) + arg2) << 5) + (arg1 << 2));
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
                var_v0 = temp_a2;
                if (temp_a2 != 0) {
loop_5:
                    temp_t2 = (var_v0->field18 << 8) +
                              (var_v0->field20 >> 16);
                    if (temp_t1 >= temp_t2) {
                        if (var_v0 != temp_a2) {
                            temp_a2->next = temp_t0;
                            temp_t0_2 = var_a1->next;
                            if (temp_t0_2 != 0) {
                                temp_t0_2->prev = var_a1->prev;
                            }
                            temp_t7 = var_v0->next;
                            var_a1->next = temp_t7;
                            if (temp_t7 != 0) {
                                temp_t7->prev = var_a1;
                            }
                            var_a1->prev = var_v0;
                            var_v0->next = var_a1;
                        }
                    } else {
                        var_v0 = var_v0->prev;
                        if (var_v0 != 0) {
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
