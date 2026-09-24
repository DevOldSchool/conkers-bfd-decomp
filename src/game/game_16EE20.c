#include "types.h"

/*
 * Reviewed source unit: src/game/game_16EE20.c
 * Boundary evidence: docs/evidence/game_state_callback_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151419D0
 * - func_15141A7C
 * - func_15141C0C
 * - func_15141DA4
 * - func_15141E38
 * - func_15141F78
 * - func_151420F8
 * - func_15142180
 * - func_15142314
 * - func_151424F4
 * - func_15142600
 * - func_15142838
 * - func_15142B7C
 * - func_15142C10
 * - func_15142CF0
 * - func_15142FBC
 * - func_1514306C
 * - func_15143134
 * - func_151432BC
 * - func_151436B4
 * - func_15143874
 * - func_151438D8
 * - func_15143D18
 * - func_15143E94
 * - func_1514401C
 * - func_151441A4
 * - func_1514462C
 * - func_1514470C
 * - func_15144A74
 * - func_15144B68
 * - func_15144CEC
 * - func_15144E80
 * - func_151452C4
 * - func_15145548
 * - func_1514563C
 * - func_15145740
 * - func_15145AD8
 * - func_15145C90
 * - func_15145CD0
 * - func_15145DB4
 * - func_15145EA4
 * - func_15146078
 * - func_151462C8
 * - func_151464B8
 * - func_1514654C
 * - func_1514672C
 * - func_151467A4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_1514EDF0(s32 arg0, s32 arg1);

void func_15141970(s32 *arg0) {
    func_1514EDF0((s32)arg0, arg0[0xB]);
}
void func_15141990(s32 *arg0) {
    func_15141970(arg0);
}
void func_151419B0(s32 *arg0) {
    func_15141970(arg0);
}
void func_1516972C(void *, s32, void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151419D0 CURRENT (1187) */
void func_151419D0(void *arg0, void *arg1, s32 arg2) {
    void *temp_a3;
    s32 temp_a0;
    s32 temp_v1;
    void *temp_v0;
    void *temp_v0_2;

    arg2 = arg2 & 0xFF;
    temp_a3 = arg0;
    if (arg2 == 0) {
        temp_v0 = (u8 *)temp_a3 + 0x28;
        if ((*(s32 *)arg1 == *(s32 *)((u8 *)temp_v0 + 4)) ||
            (*(u8 *)((u8 *)temp_v0 + 8) == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C(temp_a3, arg2, temp_a3);
        }
    } else {
        temp_v0_2 = (u8 *)temp_a3 + 0x28;
        if (arg2 == 0x2D) {
            temp_a0 = *(s32 *)((u8 *)temp_v0_2 + 4);
            temp_v1 = *(s32 *)arg1;
            if (temp_v1 == temp_a0) {
                *(s32 *)((u8 *)temp_v0_2 + 4) = *(s32 *)((u8 *)arg1 + 4);
                *(u8 *)((u8 *)temp_v0_2 + 8) = *(u8 *)((u8 *)arg1 + 9);
                return;
            }
            if (*(s32 *)((u8 *)arg1 + 4) == temp_a0) {
                *(s32 *)((u8 *)temp_v0_2 + 4) = temp_v1;
                *(u8 *)((u8 *)temp_v0_2 + 8) = *(u8 *)((u8 *)arg1 + 8);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151419D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151419D0.s")
s32 func_1510F8CC(s32);
s32 func_15141C0C(void *);
s32 func_15141CC0(u32);
void func_15141E38(void *, s32);
s32 func_1514ECE0(void *, s32, void **);
extern u8 D_800BE616;
extern s32 D_8008A084[];
extern s32 D_8008A0B4[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15141A7C CURRENT (3828) */
void func_15141A7C(void *arg0, s32 arg1) {
    void *current;
    u8 *actor = arg0;
    s32 index;
    s32 result;
    s32 *entry;
    u8 *object;
    void *next;

    if (D_800BE616 != 0) {
        return;
    }
    index = func_15141C0C(arg0);
    if (D_8008A084[index] != 0) {
        result = ((s32 (*)(s32, void *))D_8008A084[index])(
            func_15141CC0(func_1510F8CC(*(s32 *)(actor + 0x184))), arg0);
        if (result != -1) {
            entry = &D_8008A0B4[result * 2];
            if (entry[0] != 0) {
                if (entry[1] > 0) {
                    func_15141E38(arg0, result);
                } else {
                    ((void (*)(void *, s32, s32, s32))entry[0])(
                        arg0, arg1, 0, result);
                }
            }
        }
    }
    current = *(void **)(actor + 0x2F4);
    if (func_1514ECE0(current, 0x1A, &current) != 0) {
        do {
            object = *(u8 **)((u8 *)current + 0x10);
            entry = &D_8008A0B4[*(s32 *)(object + 0x28) * 2];
            if (entry[0] != 0) {
                ((void (*)(void *, s32, s16))entry[0])(
                    arg0, arg1, *(s16 *)(object + 0xE));
            }
            next = *(void **)((u8 *)current + 0x14);
            current = next;
        } while (func_1514ECE0(next, 0x1A, &current) != 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15141A7C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15141A7C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15141C0C CURRENT (1410) */
s32 func_15141C0C(void *arg0) {
    u8 temp_v0;

    temp_v0 = *(u8 *)((u8 *)arg0 + 4);
    switch ((s32) temp_v0) {                        /* irregular */
    case 0x79:
        return 0xA;
    case 0x21:
        return 9;
    case 0x7B:
        return 8;
    case 0x0:
    case 0x1:
    case 0x2:
    case 0x3:
    case 0x4:
    case 0x96:
        return 0;
    case 0x10:
    case 0x91:
        return 1;
    case 0x2B:
        return 2;
    case 0x54:
        return 5;
    case 0x36:
    case 0x53:
    case 0xA5:
        return 6;
    case 0x58:
        return 7;
    case 0x45:
        return 3;
    case 0x4B:
        return 4;
    default:
        return 0xB;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15141C0C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15141C0C.s")
extern s32 D_800BE9F0;

s32 func_15141CC0(u32 arg0) {
    if (D_800BE9F0 == 0x2F) {
        return 6;
    }
    if (D_800BE9F0 == 0x42) {
        return 7;
    }
    if (D_800BE9F0 == 0x27) {
        return 8;
    }
    if (D_800BE9F0 == 0x19) {
        return 5;
    }
    switch (arg0) {
    case 10:
        return 0;
    case 7:
        return 2;
    case 11:
        return 1;
    case 15:
        return 3;
    case 2:
    case 8:
    case 12:
        if (D_800BE9F0 == 2) {
            return 7;
        }
        return 4;
    case 5:
        if (D_800BE9F0 == 0x14) {
            return 5;
        }
        return 9;
    case 0:
        return 9;
    default:
        return 9;
    }
}
void func_15141E38(void *, s32);
extern s32 D_8008A084[];
extern s32 D_8008A0B4[];
extern u8 D_800BE616;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15141DA4 CURRENT (539) */
void func_15141DA4(s32 arg0, s32 arg1, s32 arg2) {
    s32 *temp_v0;

    if ((arg1 < 0xC) && (arg1 >= 0) && (arg2 < 0x14) && (arg2 >= 0) &&
        (D_800BE616 == 0) && (D_8008A084[arg1] != 0) && (arg2 != -1)) {
        temp_v0 = &D_8008A0B4[arg2 * 2];
        if ((temp_v0[0] != 0) && (temp_v0[1] > 0)) {
            func_15141E38(arg2);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15141DA4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15141DA4.s")
s32 func_1514ECE0(void *, s32, void **);
void func_1514EC1C(void *, void *, s32);
u8 *func_15149130(s16, s32, s32, s32, s32, s32, s32, s32, s32);
void *func_10022EC0(void *, const void *, u32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15141E38 CURRENT (1418) */
void func_15141E38(void *arg0, s32 arg1) {
    struct {
        s32 id;
        void *owner;
        u8 flag;
    } packet;
    void *current;
    void *next;
    void *found;
    u8 *created;
    s32 *entry;

    current = *(void **)((u8 *)arg0 + 0x2F4);
    found = 0;
    if (func_1514ECE0(current, 0x1A, &current) != 0) {
        do {
            entry = &D_8008A0B4[arg1 * 2];
            if (arg1 == *(s32 *)(*(u8 **)((u8 *)current + 0x10) + 0x28)) {
                found = current;
                *(s16 *)(*(u8 **)((u8 *)current + 0x10) + 0xE) = (s16)entry[1];
            }
            next = *(void **)((u8 *)current + 0x14);
            current = next;
        } while (func_1514ECE0(next, 0x1A, &current) != 0);
    }
    if (found == 0) {
        packet.id = arg1;
        packet.owner = arg0;
        packet.flag = *(u8 *)((u8 *)arg0 + 0x3B);
        created = func_15149130((s16)D_8008A0B4[arg1 * 2 + 1], -1, -1, -1,
                               1, 0x32, 0xC, 0xFF, 1);
        if (created != 0) {
            func_10022EC0(created + 0x28, &packet, 0xC);
            func_1514EC1C(created, arg0, 0x1A);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15141E38 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15141E38.s")
typedef struct Game141F78Packet {
    s32 code;
    s16 value;
    u8 kind;
    u8 zero7;
    s32 zero8;
    s32 zeroC;
    u8 color[6];
    u8 zero16;
    u8 seven;
    s32 type;
    s32 owner;
    u8 ff;
    u8 pad21;
    s16 size;
    s16 count;
} Game141F78Packet;

void *func_1513C650(s32, u8, u8, s32, f32, f32, f32, f32, f32,
                     u8, u8, s32, s32, s32, u8, s32);
s32 func_150ADA20();
f32 func_150ADA68();

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15141F78 CURRENT (1678) */
void func_15141F78(s32 arg0, void *arg1, f32 arg2, u8 arg3,
                   void *arg4, u8 arg5) {
    Game141F78Packet packet;
    f32 scale;

    arg0 = (u8)arg0;
    packet.kind = arg0;
    packet.zero7 = 0;
    packet.code = 0x6F701;
    packet.value = (func_150ADA20(arg0) % 61U) + 0x64;
    packet.zero8 = 0;
    packet.zeroC = 0;
    packet.color[0] = (func_150ADA20() & 0x7F) + 0x80;
    packet.color[1] = 0xFF;
    packet.color[2] = 0xFF;
    packet.color[3] = 0xFF;
    packet.color[4] = 0xFF;
    packet.color[5] = 0xFF;
    packet.type = 0x3B0002;
    packet.zero16 = 0;
    packet.seven = 7;
    packet.ff = 0xFF;
    packet.size = 0x28;
    packet.count = 6;
    packet.owner = *(s32 *)((u8 *)arg1 + 0x18);
    scale = ((func_150ADA68() * 5.0f) + 10.0f) * arg2;
    func_1513C650((s32)&packet, 0, 0, (s32)((u8 *)arg1 + 4),
                   *(f32 *)arg4, *(f32 *)arg1, *(f32 *)((u8 *)arg4 + 8),
                   scale, scale, arg3, arg5 == 2 ? 1 : 0, 3, 1, 0, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15141F78 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15141F78.s")
extern s32 D_800A5200[];
extern u8 D_800CC2D0[];
s32 func_150A2AEC(s32, s32, s32 *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151420F8 CURRENT (2410) */
s32 func_151420F8(s32 arg0) {
    s32 sp18[6];

    sp18[0] = D_800A5200[0];
    sp18[1] = D_800A5200[1];
    sp18[2] = D_800A5200[2];
    sp18[3] = D_800A5200[3];
    sp18[4] = D_800A5200[4];
    sp18[5] = D_800A5200[5];
    if (func_150A2AEC((arg0 - (s32)D_800CC2D0) / 0x32C, 6, sp18, arg0) == -1) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151420F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151420F8.s")
void func_15153F18(s16 *, void *, s32, s32, s32);
extern f32 D_800A5470;
extern f32 D_800A5474;

typedef struct Game16EE20Position {
    s32 x;
    s32 y;
    s32 z;
} Game16EE20Position;

typedef struct Game16EE20EffectPacket {
    s16 field00;
    s16 field02;
    s16 field04;
    s16 field06;
    Game16EE20Position position;
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
    s16 field34;
    s16 field36;
    s16 field38;
    s16 field3A;
    u8 field3C;
    u8 pad3D[3];
    f32 field40;
    s16 field44;
    s16 field46;
    s32 field48;
} Game16EE20EffectPacket;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15142180 CURRENT (2569) */
void func_15142180(u8 arg0, s32 *arg1, s32 arg2, f32 arg3, f32 arg4) {
    Game16EE20EffectPacket packet;

    packet.position = *(Game16EE20Position *)arg1;
    packet.field14 = 2.5f * arg3;
    packet.field18 = arg3 * 2.0f;
    packet.field04 = -0x19;
    packet.field06 = 0xA;
    packet.field1C = D_800A5470;
    packet.field2C = 3;
    packet.field2E = 3;
    packet.field02 = 0xFF;
    packet.field30 = 3;
    packet.field24 = 3.0f * arg4;
    packet.field28 = 3.5f * arg4;
    packet.field00 = 0;
    packet.field32 = 1;
    packet.field34 = 9;
    packet.field36 = 0xF;
    packet.field38 = 0xB4;
    packet.field3A = 0x4B;
    packet.field44 = 0xC;
    packet.field46 = 0x15;
    packet.field20 = D_800A5474;
    packet.field40 = 0.0f;
    packet.field48 = arg2;
    packet.field3C = arg0;
    func_15153F18(&packet.field00, &packet.position, 0, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15142180 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142180.s")
s32 func_151422C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return (arg3 + arg2) >> 1;
}
s32 func_151422DC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    return arg4;
}
s32 func_151422F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    return arg4;
}
extern u8 D_800C3E90;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15142314 CURRENT (970) */
void func_15142314(s32 arg0, s32 arg1, void *arg2) {
    void *temp_v0;
    void *temp_v0_2;

    temp_v0 = arg0 + (arg1 << 6);
    if (D_800C3E90 != 0) {
        temp_v0_2 = arg0 + (arg1 << 6);
        *(f32 *)((u8 *)arg2 + 0) = (f32) (((f32) *(s16 *)((u8 *)temp_v0_2 + 0x38) + (f32) (*(s16 *)((u8 *)temp_v0_2 + 0x18) << 0x10)) * 0.000015258789f);
        *(f32 *)((u8 *)arg2 + 4) = (f32) (((f32) *(s16 *)((u8 *)temp_v0_2 + 0x3A) + (f32) (*(s16 *)((u8 *)temp_v0_2 + 0x1A) << 0x10)) * 0.000015258789f);
        *(f32 *)((u8 *)arg2 + 8) = (f32) (((f32) *(s16 *)((u8 *)temp_v0_2 + 0x3C) + (f32) (*(s16 *)((u8 *)temp_v0_2 + 0x1C) << 0x10)) * 0.000015258789f);
        return;
    }
    *(f32 *)((u8 *)arg2 + 0) = (f32) *(f32 *)((u8 *)temp_v0 + 0x30);
    *(f32 *)((u8 *)arg2 + 4) = (f32) *(f32 *)((u8 *)temp_v0 + 0x34);
    *(f32 *)((u8 *)arg2 + 8) = (f32) *(f32 *)((u8 *)temp_v0 + 0x38);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15142314 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142314.s")
extern f32 D_8009A220[];

f32 func_151423D8(u8 arg0) {
    u8 temp_t0;
    s32 temp_v0;
    s32 var_v1;

    temp_v0 = arg0;
    if (temp_v0 & 0x40) {
        var_v1 = 0x40 - (temp_v0 & 0x3F);
    } else {
        var_v1 = temp_v0 & 0x3F;
    }
    temp_t0 = temp_v0 & 0xC0;
    if ((temp_t0 == 0) || (temp_t0 == 0xC0)) {
        return D_8009A220[var_v1];
    }
    return -D_8009A220[var_v1];
}
/* Call context: func_15083E90: unique active project prototype */
void * func_15083E90(u8);

void *func_15142444(u8 arg0, void *arg1) {
    void *temp_v0;

    if (arg0 == 0xFF) {
        if (*(s32 *)((u8 *)arg1 + 0x1D4) != 0) {
            return arg1;
        }
        return 0;
    }
    if ((arg1 != 0) && (*(s32 *)((u8 *)arg1 + 0) != 0) && (arg0 == *(u8 *)((u8 *)arg1 + 0x3B))) {
        if (*(s32 *)((u8 *)arg1 + 0x1D4) != 0) {
            return arg1;
        }
        return 0;
    }
    temp_v0 = func_15083E90(arg0);
    if ((temp_v0 != 0) && (*(s32 *)((u8 *)temp_v0 + 0x1D4) != 0)) {
        return temp_v0;
    }
    return 0;
}
/* Call context: func_150A7790: unique active project prototype */
void func_150A7790(void *, s32);
void func_150A8050(void *, f32, s32, f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151424F4 CURRENT (6410) */
void func_151424F4(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11) {
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;

    func_150A8050(&sp28, arg3, arg4, arg5);
    temp_fv0 = arg6 * arg1;
    sp58 = arg9;
    sp5C = arg10;
    sp60 = arg11;
    temp_fv1 = arg7 * arg1;
    sp28 *= temp_fv0;
    temp_fa0 = arg8 * arg1;
    sp2C *= temp_fv1;
    sp30 *= temp_fa0;
    sp38 *= arg6 * arg2;
    sp3C *= arg7 * arg2;
    sp40 *= arg8 * arg2;
    sp48 *= temp_fv0;
    sp4C *= temp_fv1;
    sp50 *= temp_fa0;
    func_150A7790(&sp28, arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151424F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151424F4.s")
/* Call context: func_150A7790: unique active declaration in the allowed source */
f32 sqrtf(f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15142600 CURRENT (13609) */
void func_15142600(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11) {
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp3C;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fa0_3;
    f32 temp_fa1;
    f32 temp_fs0;
    f32 temp_ft0;
    f32 temp_ft0_2;
    f32 temp_ft3;
    f32 temp_ft3_2;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv1;

    temp_ft4 = arg9 - arg6;
    sp28 = arg6;
    temp_ft5 = arg10 - arg7;
    sp2C = arg7;
    temp_ft3 = arg11 - arg8;
    sp30 = arg8;
    sp3C = temp_ft3;
    temp_fa0 = 1.0f / sqrtf((temp_ft4 * temp_ft4) + (temp_ft5 * temp_ft5) + (temp_ft3 * temp_ft3));
    temp_fa1 = temp_ft3 * temp_fa0;
    sp44 = temp_ft4 * temp_fa0;
    sp6C = temp_ft5 * temp_fa0;
    sp70 = sp44;
    temp_ft0 = -sp44;
    sp44 = temp_ft0;
    sp68 = temp_fa1;
    temp_fa0_2 = 1.0f / sqrtf((temp_fa1 * temp_fa1) + (temp_ft0 * temp_ft0));
    temp_fv1 = temp_fa1 * temp_fa0_2;
    temp_fs0 = temp_ft0 * temp_fa0_2;
    sp7C = 0.0f;
    sp84 = 0.0f;
    sp94 = 0.0f;
    spA4 = 0.0f;
    temp_ft3_2 = sp6C * temp_fs0;
    sp50 = temp_ft3_2;
    temp_ft0_2 = (sp68 * temp_fv1) - (sp70 * temp_fs0);
    sp4C = temp_ft0_2;
    sp48 = -sp6C * temp_fv1;
    temp_fa0_3 = 1.0f / sqrtf((temp_ft3_2 * temp_ft3_2) + (sp4C * temp_ft0_2) + (sp48 * sp48));
    sp78 = temp_fv1 * arg3 * arg1;
    sp88 = temp_ft3_2 * temp_fa0_3 * arg3 * arg2;
    spA8 = sp28;
    sp98 = sp70 * arg3 * arg1;
    sp8C = sp4C * temp_fa0_3 * arg4 * arg2;
    spAC = arg7;
    sp9C = sp6C * arg4 * arg1;
    sp80 = temp_fs0 * arg5 * arg1;
    sp90 = sp48 * temp_fa0_3 * arg5 * arg2;
    {
        f32 spB4 = 1.0f;
    spB0 = arg8;
    spA0 = sp68 * arg5 * arg1;
    func_150A7790(&sp78, arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15142600 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142600.s")
/* Call context: func_150A7790: unique active project prototype */
void func_150A7790(void *, s32);
void func_150A8050(void *, f32, s32, f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15142838 CURRENT (6069) */
void func_15142838(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp20;
    f32 sp1C;
    f32 sp18;

    func_150A8050(&sp18, arg3, arg4, arg5);
    sp18 *= arg1;
    sp1C *= arg1;
    sp48 = arg6;
    sp4C = arg7;
    sp50 = arg8;
    sp20 *= arg1;
    sp28 *= arg2;
    sp2C *= arg2;
    sp30 *= arg2;
    sp38 *= arg1;
    sp3C *= arg1;
    sp40 *= arg1;
    func_150A7790(&sp18, arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15142838 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142838.s")
/* Call context: func_150A8050: unique active project prototype */
void func_150A8050(void *, f32, s32, f32);

void func_15142914(void *arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    func_150A8050(arg0, arg3, arg4, arg5);
    *(f32 *)((u8 *)arg0 + 0x30) = arg6;
    *(f32 *)((u8 *)arg0 + 0x34) = arg7;
    *(f32 *)((u8 *)arg0 + 0x38) = arg8;
    *(f32 *)((u8 *)arg0 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) * arg1);
    *(f32 *)((u8 *)arg0 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) * arg1);
    *(f32 *)((u8 *)arg0 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) * arg1);
    *(f32 *)((u8 *)arg0 + 0x10) = (f32) (*(f32 *)((u8 *)arg0 + 0x10) * arg2);
    *(f32 *)((u8 *)arg0 + 0x14) = (f32) (*(f32 *)((u8 *)arg0 + 0x14) * arg2);
    *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) * arg2);
    *(f32 *)((u8 *)arg0 + 0x20) = (f32) (*(f32 *)((u8 *)arg0 + 0x20) * arg1);
    *(f32 *)((u8 *)arg0 + 0x24) = (f32) (*(f32 *)((u8 *)arg0 + 0x24) * arg1);
    *(f32 *)((u8 *)arg0 + 0x28) = (f32) (*(f32 *)((u8 *)arg0 + 0x28) * arg1);
}
s32 func_150ADA20(); /* extern */
extern u8 D_8008A160[];

void func_151429E0(u8 arg0, u8 *arg1, u8 *arg2, u8 *arg3) {
    u8 *entry;

    entry = ((func_150ADA20() & 3) * 3) + (arg0 * 0xC) + D_8008A160;
    *arg1 = entry[0];
    *arg2 = entry[1];
    *arg3 = entry[2];
}
s32 func_15142A5C(void *arg0) {
    s16 *state = *(s16 **)((u8 *)arg0 + 0x2D0);

    if (state[0x1E] > 0) {
        return 1;
    }
    return 0;
}
extern f32 D_800A5624;

f32 func_15142A80(f32 arg0) {
    return (1.0f - arg0) * (arg0 - 2.0f) * arg0 * D_800A5624;
}
f32 func_15142AC0(f32 arg0) {
    return (arg0 + 1.0f) * (arg0 - 1.0f) * (arg0 - 2.0f) * 0.5f;
}
f32 func_15142B04(f32 arg0) {
    return (2.0f - arg0) * (arg0 + 1.0f) * arg0 * 0.5f;
}
extern f32 D_800A5628;

f32 func_15142B44(f32 arg0) {
    return (arg0 + 1.0f) * (arg0 - 1.0f) * arg0 * D_800A5628;
}
extern s32 D_800DD1FC;
extern s32 D_800DD200;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15142B7C CURRENT (240) */
s32 *func_15142B7C(s32 *arg0, s32 arg1, s32 arg2) {
    s32 *temp_v0;
    s32 *temp_v0_2;

    temp_v0 = arg0;
    if (~D_800DD200 & arg2) {
        *(s32 *)((u8 *)temp_v0 + 0) = (~arg2 & 0xFFFFFF) | 0xD9000000;
        arg0 = (s32 *)((u8 *)arg0 + 8);
        *(s32 *)((u8 *)temp_v0 + 4) = 0;
        D_800DD200 |= arg2;
    }
    temp_v0_2 = arg0;
    if (~D_800DD1FC & arg1) {
        arg0 = (s32 *)((u8 *)arg0 + 8);
        *(s32 *)((u8 *)temp_v0_2 + 0) = 0xD9FFFFFF;
        *(s32 *)((u8 *)temp_v0_2 + 4) = arg1;
        D_800DD1FC |= arg1;
    }
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15142B7C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142B7C.s")
extern s16 D_800DD1C8;
extern s16 D_800DD1CA;
extern s16 D_800DD1CC;
extern s16 D_800DD1CE;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15142C10 CURRENT (2870) */
void *func_15142C10(void *arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4, u8 *arg5) {
    u8 *var_s0;

    var_s0 = arg0;
    if ((arg1 != D_800DD1C8) || (arg2 != D_800DD1CA) || (arg3 != D_800DD1CC) || (arg4 != D_800DD1CE)) {
        if (*arg5 == 1) {
            *(s32 *)((u8 *)var_s0 + 0) = 0xE7000000;
            *(s32 *)((u8 *)var_s0 + 4) = 0;
            var_s0 += 8;
            *arg5 = 0;
        }
        *(s32 *)((u8 *)var_s0 + 0) = 0xFB000000;
        *(s32 *)((u8 *)var_s0 + 4) = (s32) ((arg1 << 0x18) | ((arg2 & 0xFF) << 0x10) | ((arg3 & 0xFF) << 8) | (arg4 & 0xFF));
        var_s0 += 8;
        D_800DD1C8 = arg1;
        D_800DD1CA = arg2;
        D_800DD1CC = arg3;
        D_800DD1CE = (s16) arg4;
    }
    return var_s0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15142C10 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142C10.s")
extern s16 D_800DD1C0;
extern s16 D_800DD1C2;
extern s16 D_800DD1C4;
extern s16 D_800DD1C6;
extern s16 D_800DD204;
extern s16 D_800DD206;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15142CF0 CURRENT (3067) */
void *func_15142CF0(void *arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6, u8 *arg7) {
    u8 *var_s0;

    var_s0 = arg0;
    if ((arg1 != D_800DD204) || (arg2 != D_800DD206) || (arg3 != D_800DD1C0) || (arg4 != D_800DD1C2) || (arg5 != D_800DD1C4) || (arg6 != D_800DD1C6)) {
        if (*arg7 == 1) {
            *(s32 *)((u8 *)var_s0 + 0) = 0xE7000000;
            *(s32 *)((u8 *)var_s0 + 4) = 0;
            var_s0 += 8;
            *arg7 = 0;
        }
        *(s32 *)((u8 *)var_s0 + 0) = (s32) (((arg1 & 0xFF) << 8) | 0xFA000000 | (arg2 & 0xFF));
        *(s32 *)((u8 *)var_s0 + 4) = (s32) ((arg3 << 0x18) | ((arg4 & 0xFF) << 0x10) | ((arg5 & 0xFF) << 8) | (arg6 & 0xFF));
        var_s0 += 8;
        D_800DD204 = arg1;
        D_800DD206 = arg2;
        D_800DD1C0 = arg3;
        D_800DD1C2 = (s16) arg4;
        D_800DD1C4 = (s16) arg5;
        D_800DD1C6 = (s16) arg6;
    }
    return var_s0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15142CF0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142CF0.s")
s32 func_15094FE8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
s32 func_1514306C(s32, s32, s32, u8);               /* extern */
extern s32 D_800BE9F0;
extern s32 D_800DD1B0;
extern s32 D_800DD208;
extern s32 D_800DD20C;
extern s32 D_800DD210;
extern s32 D_800DD214;

s32 func_15142E24(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, s32 arg8, u8 *arg9, s32 arg10) {
    s32 temp_v0;
    s32 sp3C;
    s32 temp_v0_2;

    temp_v0 = func_1514306C(arg1, arg6, arg2 >> 0x10, arg7);
    if ((temp_v0 != D_800DD1B0) || (arg3 != D_800DD208) || (arg4 != D_800DD20C) || (arg5 != D_800DD210) || (arg8 != D_800DD214)) {
        if (*arg9 == 1) {
            *arg9 = 0;
        }
        if ((D_800BE9F0 == 0x18) || (D_800BE9F0 == 0x13) || (D_800BE9F0 == 6) || (D_800BE9F0 == 0x3B) || (D_800BE9F0 == 2) || (D_800BE616 != 0)) {
            arg10 = 3;
        }
        sp3C = temp_v0;
        temp_v0_2 = func_15094FE8(arg0, arg1, arg2 >> 8, arg8, 0, 0, 0, arg3, arg4, arg5, arg10);
        D_800DD1B0 = temp_v0;
        D_800DD208 = arg3;
        D_800DD20C = arg4;
        D_800DD210 = arg5;
        arg0 = temp_v0_2;
        D_800DD214 = D_800DD214;
    }
    return arg0;
}
extern s32 D_800DD218;
extern s32 D_800DD21C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15142FBC CURRENT (540) */
void *func_15142FBC(void *arg0, s32 arg1, s32 arg2, u8 *arg3) {
    u8 *temp_v0;

    if ((arg1 != D_800DD218) || (arg2 != D_800DD21C)) {
        temp_v0 = arg0;
        if (*arg3 == 1) {
            arg0 = (u8 *)arg0 + 8;
            *(s32 *)((u8 *)temp_v0 + 0) = 0xE7000000;
            *(s32 *)((u8 *)temp_v0 + 4) = 0;
            *arg3 = 0;
        }
        temp_v0 = arg0;
        *(s32 *)((u8 *)temp_v0 + 0) = (s32) (((arg1 | 0xF) & 0xFFFFFF) | 0xEF000000);
        *(s32 *)((u8 *)temp_v0 + 4) = arg2;
        arg0 = (u8 *)arg0 + 8;
        D_800DD218 = arg1;
        D_800DD21C = arg2;
    }
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15142FBC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142FBC.s")
s16 func_15143044(u8 arg0, s32 arg1) {
    return (s16) (0x7FFF - arg0);
}
extern s32 D_800915B0;
extern s32 D_80091514;
extern s32 D_80091564[];
typedef struct {
    s32 *field0;
    s32 *field4;
    s32 *field8;
} Game16EE20PointerGroup;
extern Game16EE20PointerGroup D_80090B60[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514306C CURRENT (205) */
s32 func_1514306C(s32 arg0, s32 arg1, s32 arg2, u8 arg3) {
    s32 value;
    u32 address;

    switch (arg3) {
    case 1:
        value = D_800915B0;
        break;
    case 2:
        value = D_80091514;
        break;
    case 3:
        value = 0;
        break;
    case 4:
        value = D_80091564[arg1];
        break;
    case 5:
        value = arg1;
        break;
    case 6:
        address = *(u32 *)arg0;
        if (address >= 0x10000000U) {
            value = ((s32 *)address)[arg2];
        } else {
            value = address;
        }
        break;
    default:
        value = D_80090B60[arg1].field0[arg2];
        break;
    }
    return value;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514306C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514306C.s")
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
void func_15142314(s32, s32, void *);
void func_151EFEB8(void *, s32);
extern s32 D_800DCA00;
extern s32 D_800DCA04;
extern f32 D_800DCA08;
extern f32 D_800DCA0C;
extern f32 D_800DCA10;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15143134 CURRENT (215) */
void func_15143134(f32 *arg0, f32 *arg1, s32 arg2) {
    u8 transform[0x40];

    D_800DCA00 = 1;
    if (arg0 != 0 && (arg0[0] != 0.0f || arg0[1] != 0.0f || arg0[2] != 0.0f)) {
        D_800DCA00 = 2;
        D_800DCA08 = arg0[0];
        D_800DCA0C = arg0[1];
        D_800DCA10 = arg0[2];
        if (D_800C3E90 != 0) {
            D_800DCA00 = 3;
            D_800DCA04 = arg2;
            func_151EFEB8(transform, arg2);
            func_150A7960(transform, arg0[0], arg0[1], arg0[2],
                          &arg1[0], &arg1[1], &arg1[2]);
            D_800DCA00 = 4;
        } else {
            D_800DCA00 = 5;
            D_800DCA04 = arg2;
            func_150A7960((void *)arg2, arg0[0], arg0[1], arg0[2],
                          &arg1[0], &arg1[1], &arg1[2]);
            D_800DCA00 = 6;
        }
    } else {
        D_800DCA00 = 7;
        func_15142314(arg2, 0, arg1);
        D_800DCA00 = 8;
    }
    D_800DCA00 = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15143134 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143134.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151432BC.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15047C00(f32);                             /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151436B4 CURRENT (260) */
void func_151436B4(f32 arg0, f32 arg1, f32 arg2, void *arg3) {
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 temp_fv1;
    f32 last;

    sp24 = func_15047C00(arg0);
    sp20 = func_15047D60(arg0);
    sp1C = func_15047C00(arg1);
    last = func_15047D60(arg1);
    temp_fv1 = arg2 * sp1C;
    {
        f32 temp_ft4 = -arg2 * last;
    *(f32 *)((u8 *)arg3 + 0) = (f32) (temp_fv1 * sp20);
    *(f32 *)((u8 *)arg3 + 4) = temp_ft4;
    *(f32 *)((u8 *)arg3 + 8) = (f32) (temp_fv1 * sp24);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151436B4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151436B4.s")
f32 func_15047C00(f32);                             /* extern */
f32 func_15047D60(f32);                             /* extern */

void func_1514373C(f32 arg0, f32 arg1, f32 *arg2, f32 *arg3) {
    f32 sp1C;
    f32 temp_fv0;

    sp1C = func_15047C00(arg0);
    temp_fv0 = func_15047D60(arg0);
    *arg2 = arg1 * temp_fv0;
    *arg3 = arg1 * sp1C;
}
/* Call context: func_151423D8: unique active project prototype */
f32 func_151423D8(u8);

void func_15143794(s16 arg0, s16 arg1, f32 arg2, void *arg3) {
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 temp_fv1;
    f32 temp_ft4;
    f32 fourth;
    s32 angle0;
    s32 angle1;

    sp24 = func_151423D8(arg0);
    angle0 = arg0;
    angle0 -= 0x40;
    sp20 = func_151423D8(angle0);
    sp1C = func_151423D8(arg1);
    angle1 = arg1;
    angle1 -= 0x40;
    fourth = func_151423D8(angle1);
    temp_ft4 = -arg2 * fourth;
    temp_fv1 = arg2 * sp1C;
    *(f32 *)((u8 *)arg3 + 0) = (f32) (temp_fv1 * sp20);
    *(f32 *)((u8 *)arg3 + 4) = temp_ft4;
    *(f32 *)((u8 *)arg3 + 8) = (f32) (temp_fv1 * sp24);
}
extern void func_15143794(s16 arg0, s16 arg1, f32 arg2, void *arg3);

void func_15143834(s16 arg0, s16 arg1, f32 arg2, void *arg3) {
    func_15143794(arg0, arg1, arg2, arg3);
}
f32 func_151423D8(u8);                              /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15143874 CURRENT (435) */
void func_15143874(s16 arg0, f32 arg1, f32 *arg2, f32 *arg3) {
    f32 sp1C;

    sp1C = func_151423D8(arg0);
    *arg2 = arg1 * func_151423D8(((s16) arg0 - 0x40) & 0xFF);
    *arg3 = arg1 * sp1C;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15143874 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143874.s")
extern s32 D_800D3094;
extern s32 D_800D3098;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151438D8 CURRENT (9269) */
s32 func_151438D8(s32 arg0, s32 arg1, u16 arg2, u8 *arg3) {
    s32 sp58;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 var_a0;
    s32 var_a1;
    s32 var_t0;
    s32 var_v0;
    u8 *temp_v1;
    u8 *temp_v1_2;

    if (arg3 == 0) {
        return 0;
    }
    sp58 = 0;
    func_15143D18(&arg0, &arg1, 0, D_800D3094);
    var_a1 = arg0;
    var_t0 = 0;
    if (var_a1 < arg1) {
        sp30 = arg2 & 0x80;
        sp34 = arg2 & 0x40;
        sp28 = arg2 & 0x200;
        sp2C = arg2 & 0x100;
        sp20 = arg2 & 0x1000;
        sp24 = arg2 & 0x400;
        do {
            var_v0 = 0;
            var_a0 = 0;
            if (arg2 & 1) {
                temp_v1 = (void *)(D_800D3098 + (var_a1 * 0x34));
                if ((*(s16 *)((u8 *)arg3 + 0) == *(s16 *)((u8 *)temp_v1 + 0)) && (*(s16 *)((u8 *)arg3 + 2) == *(s16 *)((u8 *)temp_v1 + 2)) && (*(s16 *)((u8 *)arg3 + 4) == *(s16 *)((u8 *)temp_v1 + 4))) {
                    var_v0 = 1;
                    var_a0 = 1;
                }
            } else {
                var_v0 = 1;
            }
            if (arg2 & 2) {
                temp_v1_2 = (void *)(D_800D3098 + (var_a1 * 0x34));
                if ((*(s16 *)((u8 *)arg3 + 6) == *(s16 *)((u8 *)temp_v1_2 + 6)) && (*(s16 *)((u8 *)arg3 + 8) == *(s16 *)((u8 *)temp_v1_2 + 8)) && (*(s16 *)((u8 *)arg3 + 0xA) == *(s16 *)((u8 *)temp_v1_2 + 0xA))) {
                    var_v0 = (var_v0 | 2) & 0xFFFF;
                    var_a0 = (var_a0 | 2) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 2) & 0xFFFF;
            }
            if (arg2 & 4) {
                if (*(f32 *)((u8 *)arg3 + 0xC) == *(f32 *)((u8 *)(D_800D3098 + (var_a1 * 0x34)) + 0xC)) {
                    var_v0 = (var_v0 | 4) & 0xFFFF;
                    var_a0 = (var_a0 | 4) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 4) & 0xFFFF;
            }
            if (arg2 & 8) {
                if (*(f32 *)((u8 *)arg3 + 0x10) == *(f32 *)((u8 *)(D_800D3098 + (var_a1 * 0x34)) + 0x10)) {
                    var_v0 = (var_v0 | 8) & 0xFFFF;
                    var_a0 = (var_a0 | 8) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 8) & 0xFFFF;
            }
            if (arg2 & 0x10) {
                if (*(u8 *)((u8 *)arg3 + 0x14) == *(u8 *)((u8 *)(D_800D3098 + (var_a1 * 0x34)) + 0x14)) {
                    var_v0 = (var_v0 | 0x10) & 0xFFFF;
                    var_a0 = (var_a0 | 0x10) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 0x10) & 0xFFFF;
            }
            if (arg2 & 0x20) {
                if (*(u8 *)((u8 *)arg3 + 0x15) == ((s32) *(u8 *)((u8 *)(D_800D3098 + (var_a1 * 0x34)) + 0x15) >> 2)) {
                    var_v0 = (var_v0 | 0x20) & 0xFFFF;
                    var_a0 = (var_a0 | 0x20) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 0x20) & 0xFFFF;
            }
            if (sp34 != 0) {
                if (*(u8 *)((u8 *)arg3 + 0x16) == *(u8 *)((u8 *)(D_800D3098 + (var_a1 * 0x34)) + 0x16)) {
                    var_v0 = (var_v0 | 0x40) & 0xFFFF;
                    var_a0 = (var_a0 | 0x40) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 0x40) & 0xFFFF;
            }
            if (sp30 != 0) {
                if (*(u8 *)((u8 *)arg3 + 0x17) == *(u8 *)((u8 *)(D_800D3098 + (var_a1 * 0x34)) + 0x17)) {
                    var_v0 = (var_v0 | 0x80) & 0xFFFF;
                    var_a0 = (var_a0 | 0x80) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 0x80) & 0xFFFF;
            }
            if (sp2C != 0) {
                if (*(s32 *)((u8 *)arg3 + 0x18) == *(s32 *)((u8 *)(D_800D3098 + (var_a1 * 0x34)) + 0x18)) {
                    var_v0 = (var_v0 | 0x100) & 0xFFFF;
                    var_a0 = (var_a0 | 0x100) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 0x100) & 0xFFFF;
            }
            if (sp28 != 0) {
                if (*(s32 *)((u8 *)arg3 + 0x1C) == *(s32 *)((u8 *)(D_800D3098 + (var_a1 * 0x34)) + 0x1C)) {
                    var_v0 = (var_v0 | 0x200) & 0xFFFF;
                    var_a0 = (var_a0 | 0x200) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 0x200) & 0xFFFF;
            }
            if (sp24 != 0) {
                if (*(s32 *)((u8 *)arg3 + 0x20) == *(s32 *)((u8 *)(D_800D3098 + (var_a1 * 0x34)) + 0x20)) {
                    var_v0 = (var_v0 | 0x400) & 0xFFFF;
                    var_a0 = (var_a0 | 0x400) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 0x400) & 0xFFFF;
            }
            if (sp20 != 0) {
                if (var_v0 == 0x7FF) {
                    var_t0 = (var_a1 * 0x34) + D_800D3098;
                }
            } else if (var_a0 != 0) {
                var_t0 = (var_a1 * 0x34) + D_800D3098;
            }
            var_a1 += 1;
        } while (var_a1 != arg1);
    }
    return var_t0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151438D8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151438D8.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15143D18 CURRENT (300) */
void func_15143D18(s32 *arg0, s32 *arg1, s32 arg2, s32 arg3) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_a1;
    s32 var_a2;

    var_a2 = arg2;
    temp_v1 = var_a2 ^ arg3;
    if (arg3 < var_a2) {
        temp_a1 = arg3 ^ temp_v1;
        arg3 = temp_a1;
        var_a2 = temp_a1 ^ temp_v1;
    }
    temp_v1_2 = *arg1;
    var_a1 = *arg0;
    temp_v0 = var_a1 ^ temp_v1_2;
    if (temp_v1_2 < var_a1) {
        *arg0 = temp_v0;
        temp_a0 = *arg1 ^ temp_v0;
        *arg1 = temp_a0;
        var_a1 = *arg0 ^ temp_a0;
        *arg0 = var_a1;
    }
    if (var_a1 < var_a2) {
        *arg0 = var_a2;
    }
    if (arg3 < *arg1) {
        *arg1 = arg3;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15143D18 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143D18.s")
s32 func_15143DA8(s32 *arg0, s32 arg1, s32 arg2) {
    s32 temp_a3;
    s32 temp_v0;

    if (arg2 < arg1) {
        s32 temp_v1 = arg1 ^ arg2;
        temp_a3 = arg2 ^ temp_v1;
        arg2 = temp_a3;
        arg1 = temp_v1 ^ temp_a3;
    }
    temp_v0 = *arg0;
    if (temp_v0 < arg1) {
        *arg0 = arg1;
        return 1;
    }
    if (arg2 < temp_v0) {
        *arg0 = arg2;
        return 2;
    }
    return 0;
}
s32 func_15143E08(u16 *arg0) {
    return (((s32)arg0[0x3D] >> 8) + 0x40) & 0xFF;
}
s16 func_15143E24(void *arg0) {
    void *temp_v1;

    temp_v1 = *(void **)((u8 *)arg0 + 0x31C);
    if (temp_v1 != 0) {
        return (s16) ((s32) (*(u16 *)((u8 *)arg0 + 0x7A) - *(s16 *)((u8 *)temp_v1 + 0x12)) >> 8);
    }
    return (s16) ((s32) *(u16 *)((u8 *)arg0 + 0x7A) >> 8);
}
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
f32 func_15143E64(void *arg0) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv1;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 0);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 4);
    temp_fa1 = *(f32 *)((u8 *)arg0 + 8);
    return sqrtf((temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0) + (temp_fa1 * temp_fa1));
}
typedef struct Game143E94Packet {
    s8 type;
    u8 pad1;
    s16 lifetime;
    s8 size;
    s8 one;
    s8 negative;
} Game143E94Packet;

typedef struct Game143E94Locals {
    Game143E94Packet packet;
    u8 pad7[7];
    volatile u8 success;
} Game143E94Locals;

s32 func_150A29C8(s32, s32);
void func_1512D748(void *, s32, s32);
void func_151D8868(Game143E94Packet *, s32, s32, s32);
extern s32 D_80082FA0;
extern s32 D_800BE9E8;
extern s32 D_800DBFF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15143E94 CURRENT (933) */
u8 func_15143E94(s32 arg0, s32 arg1) {
    Game143E94Locals locals;
    s8 limit = D_80082FA0 + 1;
    s8 index = 0;
    s32 found = 0;
    s32 effect_found;

    locals.success = 0;
    if (limit > 0) {
        do {
            if (D_800CC2D0[index * 0x32C + 0x1CA] != 0) {
                found = 1;
            } else {
                index++;
            }
            if (found != 0) {
                break;
            }
        } while (index < limit);
    }
    if (found != 0) {
        index = 0;
        effect_found = 0;
        if (limit > 0) {
            do {
                if (func_150A29C8(index, arg1) == 0) {
                    effect_found = 1;
                } else {
                    index++;
                }
                if (effect_found != 0) {
                    break;
                }
            } while (index < limit);
        }
        if (effect_found != 0) {
            func_1512D748((u8 *)D_800DBFF0 + D_800BE9E8 * 0x9A0, arg0, 1);
            locals.packet.type = 1;
            locals.packet.lifetime = (func_150ADA20() & 0xF) + 0x14;
            locals.packet.size = (func_150ADA20() & 3) + 4;
            locals.packet.negative = -1;
            locals.packet.one = 1;
            func_151D8868(&locals.packet, 0, 0xFF, 0);
            locals.success = 1;
        }
    }
    return locals.success;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15143E94 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143E94.s")
extern u8 D_80090B64[];
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514401C CURRENT (320) */
s32 func_1514401C(u8 arg0, s32 *arg1, s32 *arg2, u8 arg3) {
    s32 boundary;
    s32 value;
    s32 overflow_value;
    s32 underflow_value;
    s32 current;
    s32 result = 0;

    boundary = (D_80090B64[arg0 * 0xC] << 16) - 1;
    value = *arg2 + (D_800BE9E4 * *arg1);
    *arg2 = value;
    current = value;
    if (boundary < value) {
        if (arg3 & 1) {
            result = 1;
        } else if (arg3 & 2) {
            *arg1 = 0;
            *arg2 = boundary;
        } else if (arg3 & 4) {
            *arg2 = boundary - (current % boundary);
            *arg1 = -*arg1;
        } else {
            do {
                overflow_value = current - boundary;
                *arg2 = overflow_value;
                current = overflow_value;
            } while (boundary < overflow_value);
        }
    } else if (current < 0 && !(arg3 & 8)) {
        if (arg3 & 0x10) {
            *arg1 = 0;
            *arg2 = 0;
        } else if (arg3 & 4) {
            *arg2 = -current % boundary;
            *arg1 = -*arg1;
        } else {
            do {
                underflow_value = current + boundary;
                *arg2 = underflow_value;
                current = underflow_value;
            } while (underflow_value < 0);
        }
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514401C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514401C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151441A4 CURRENT (536) */
void func_151441A4(s16 *arg0, s16 *arg1, s16 *arg2, s16 *arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg8, u8 arg9, u8 arg10, u8 arg11, u8 arg12, u8 arg13) {
    s16 temp_v0;
    s16 temp_v0_2;

    switch (arg13) {
    case 2:
        *arg0 = (s16) arg8;
        *arg1 = (s16) arg9;
        *arg2 = (s16) arg10;
        *arg3 = (s16) arg11;
        return;
    case 0:
        *arg3 = 0;
        temp_v0 = *arg3;
        *arg2 = temp_v0;
        *arg1 = temp_v0;
        *arg0 = temp_v0;
        return;
    case 1:
        *arg2 = 0;
        temp_v0_2 = *arg2;
        *arg1 = temp_v0_2;
        *arg0 = temp_v0_2;
        *arg3 = (s16) arg11;
        return;
    case 3:
        *arg0 = (s16) ((s32) (arg4 * arg12) >> 8);
        *arg1 = (s16) ((s32) (arg5 * arg12) >> 8);
        *arg2 = (s16) ((s32) (arg6 * arg12) >> 8);
        *arg3 = 0;
        return;
    case 4:
        *arg0 = (s16) ((s32) (arg4 * arg12) >> 8);
        *arg1 = (s16) ((s32) (arg5 * arg12) >> 8);
        *arg2 = (s16) ((s32) (arg6 * arg12) >> 8);
        *arg3 = 0;
        return;
    default:
        *arg0 = (s16) ((s32) (arg4 * arg12) >> 8);
        *arg1 = (s16) ((s32) (arg5 * arg12) >> 8);
        *arg2 = (s16) ((s32) (arg6 * arg12) >> 8);
        *arg3 = 0;
        return;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151441A4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151441A4.s")
void func_151442FC(s16 *arg0, s16 *arg1, s16 *arg2, s16 *arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 arg10, u8 arg11, u8 arg12, u8 arg13) {
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;

    switch (arg13) {
    case 2:
    case 3:
        *arg0 = (s16) arg4;
        *arg1 = (s16) arg5;
        *arg2 = (s16) arg6;
        *arg3 = (s16) arg7;
        return;
    case 13:
        *arg0 = (s16) arg4;
        *arg1 = (s16) arg5;
        *arg2 = (s16) arg6;
        *arg3 = 0;
        return;
    case 0:
        *arg3 = 0;
        temp_v0 = *arg3;
        *arg2 = temp_v0;
        *arg1 = temp_v0;
        *arg0 = temp_v0;
        return;
    case 1:
        *arg2 = (s16) arg12;
        *arg1 = (s16) arg12;
        *arg0 = (s16) arg12;
        *arg3 = 0;
        return;
    case 7:
    case 12:
        *arg2 = 0;
        temp_v0_2 = *arg2;
        *arg1 = temp_v0_2;
        *arg0 = temp_v0_2;
        *arg3 = (s16) arg11;
        return;
    case 8:
        *arg2 = 0;
        temp_v0_3 = *arg2;
        *arg1 = temp_v0_3;
        *arg0 = temp_v0_3;
        *arg3 = (s16) arg7;
        return;
    case 4:
        *arg2 = (s16) arg12;
        *arg1 = (s16) arg12;
        *arg0 = (s16) arg12;
        *arg3 = (s16) ((s32) (arg7 * arg11) >> 8);
        return;
    case 5:
        *arg2 = (s16) arg12;
        *arg1 = (s16) arg12;
        *arg0 = (s16) arg12;
        *arg3 = (s16) ((s32) (arg7 * arg11) >> 8);
        return;
    case 6:
        *arg0 = (s16) arg4;
        *arg1 = (s16) arg5;
        *arg2 = (s16) arg6;
        *arg3 = (s16) arg11;
        return;
    case 10:
        *arg0 = (s16) arg8;
        *arg1 = (s16) arg9;
        *arg2 = (s16) arg10;
        *arg3 = (s16) arg11;
        return;
    case 11:
        *arg0 = (s16) arg8;
        *arg1 = (s16) arg9;
        *arg2 = (s16) arg10;
        *arg3 = (s16) arg7;
        return;
    case 9:
        *arg2 = (s16) arg12;
        *arg1 = (s16) arg12;
        *arg0 = (s16) arg12;
        *arg3 = (s16) arg11;
        return;
    default:
        *arg2 = (s16) arg12;
        *arg1 = (s16) arg12;
        *arg0 = (s16) arg12;
        *arg3 = (s16) ((s32) (arg7 * arg11) >> 8);
        return;
    }
}
s32 func_151444DC(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 < arg0) {
        s32 delta = (arg1 - arg2) + 1;
        do {
            arg0 -= delta;
        } while (arg1 < arg0);
    }
    if (arg0 < arg2) {
        s32 delta = (arg1 - arg2) + 1;
        do {
            arg0 += delta;
        } while (arg0 < arg2);
    }
    return arg0;
}
f32 func_15144528(f32 arg0, f32 arg1, f32 arg2) {
    if (arg1 < arg0) {
        do {
            arg0 -= arg1 - arg2;
        } while (arg1 < arg0);
    }
    if (arg0 < arg2) {
        do {
            arg0 += arg1 - arg2;
        } while (arg0 < arg2);
    }
    return arg0;
}
extern f32 D_800A5694;

f32 func_15144598(void *arg0) {
    f32 var_fv1;
    s16 temp_v0;
    s32 temp_t6;

    temp_t6 = *(u8 *)((u8 *)arg0 + 0x15) & 3;
    switch (temp_t6) {                              /* irregular */
    default:
        var_fv1 = 1.0f;
        break;
    case 2:
        var_fv1 = (f32) (*(s16 *)((u8 *)arg0 + 0xA) * *(s16 *)((u8 *)arg0 + 6)) * 4.0f;
        break;
    case 0:
    case 1:
        temp_v0 = *(s16 *)((u8 *)arg0 + 6);
        var_fv1 = (f32) (temp_v0 * temp_v0) * D_800A5694;
        break;
    }
    return var_fv1;
}
extern f32 D_800A5698;
extern f32 D_800A569C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514462C CURRENT (10) */
f32 func_1514462C(void *arg0) {
    f32 temp_fv0;
    f32 var_fv1;
    s16 temp_v0;
    s32 temp_t6;

    temp_t6 = *(u8 *)((u8 *)arg0 + 0x15) & 3;
    switch (temp_t6) {                              /* irregular */
    default:
        var_fv1 = 1.0f;
        break;
    case 2:
        var_fv1 = (f32) ((*(s16 *)((u8 *)arg0 + 8) * *(s16 *)((u8 *)arg0 + 0xA)) * *(s16 *)((u8 *)arg0 + 6));
        break;
    case 0:
        temp_v0 = *(s16 *)((u8 *)arg0 + 6);
        var_fv1 = (f32) *(s16 *)((u8 *)arg0 + 8) * ((f32) (temp_v0 * temp_v0) * D_800A5698);
        break;
    case 1:
        temp_fv0 = (f32) *(s16 *)((u8 *)arg0 + 6);
        var_fv1 = temp_fv0 * D_800A569C * temp_fv0 * temp_fv0;
        break;
    }
    return var_fv1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514462C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514462C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514470C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15144A74 CURRENT (10) */
f32 func_15144A74(void *arg0, void *arg1) {
    return (*(f32 *)((u8 *)arg0 + 0) * *(f32 *)((u8 *)arg1 + 0)) + (*(f32 *)((u8 *)arg0 + 4) * *(f32 *)((u8 *)arg1 + 4)) + (*(f32 *)((u8 *)arg1 + 8) * *(f32 *)((u8 *)arg0 + 8));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15144A74 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15144A74.s")
extern s32 D_800DBFF0;

f32 func_15144AA8(s32 arg0) {
    f32 var_fv1;

    var_fv1 = *(f32 *)((u8 *)D_800DBFF0 + (arg0 * 0x9A0) + 0x380);
    if (var_fv1 > 360.0f) {
        do {
            var_fv1 -= 360.0f;
        } while (var_fv1 > 360.0f);
    }
    if (var_fv1 < 0.0f) {
        do {
            var_fv1 += 360.0f;
        } while (var_fv1 < 0.0f);
    }
    return var_fv1;
}

s32 func_15144B34(s32 arg0) {
    return (arg0 * 0x9A0) + D_800DBFF0 + 0x2F8;
}
extern f32 D_800A56A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15144B68 CURRENT (160) */
f32 func_15144B68(f32 arg0) {
    f32 var_fv1;

    var_fv1 = arg0;
    if (D_800A56A4 < arg0) {
        do {
            var_fv1 -= D_800A56A4;
        } while (D_800A56A4 < var_fv1);
    }
    if (var_fv1 < 0.0f) {
        do {
            var_fv1 += D_800A56A4;
        } while (var_fv1 < 0.0f);
    }
    return var_fv1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15144B68 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15144B68.s")
f32 func_15144BC8(f32 arg0) {
    f32 var_fv1;

    var_fv1 = arg0;
    if (arg0 > 360.0f) {
        do {
            var_fv1 -= 360.0f;
        } while (var_fv1 > 360.0f);
    }
    if (var_fv1 < 0.0f) {
        do {
            var_fv1 += 360.0f;
        } while (var_fv1 < 0.0f);
    }
    return var_fv1;
}
s16 func_15144C2C(s16 arg0) {
    s16 var_v1;

    var_v1 = arg0;
    if (arg0 >= 0x100) {
        do {
            var_v1 -= 0xFF;
        } while (var_v1 >= 0x100);
    }
    if (var_v1 < 0) {
        do {
            var_v1 += 0xFF;
        } while (var_v1 < 0);
    }
    return var_v1;
}
extern f32 D_800A56A8;
extern f32 D_800A56AC;
f32 func_15144B68(f32);
f32 fabsf(f32);
#pragma intrinsic(fabsf)

f32 func_15144C8C(f32 arg0, f32 arg1) {
    f32 var_fv1;

    arg0 = func_15144B68(arg0);
    {
        f32 temp_fv0 = fabsf(arg0 - func_15144B68(arg1));
    var_fv1 = temp_fv0;
    if (D_800A56A8 < temp_fv0) {
        var_fv1 = D_800A56AC - temp_fv0;
    }
    return var_fv1;
    }
}
void func_150A7A00(void *, f32, f32, f32, f32 *, f32 *, f32 *, f32 *);
extern f32 D_800A56B0;
extern f32 D_800D9B20;
extern u8 *D_800BE628;
extern u8 D_800D9D10[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15144CEC CURRENT (4258) */
s32 func_15144CEC(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3,
                  f32 *arg4, u8 arg5) {
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 *var_t0;
    f32 temp_fv0;
    s32 temp_t9;
    u8 *temp_v1;

    if (arg2 == 0) {
        arg2 = &sp44;
    }
    if (arg3 == 0) {
        arg3 = &sp40;
    }
    var_t0 = arg4;
    if (var_t0 == 0) {
        var_t0 = &sp3C;
    }
    func_150A7A00(&D_800D9D10[arg5 << 6], arg0[0], arg0[1], arg0[2],
                   arg1, arg1 + 1, arg2, arg3);
    temp_fv0 = *arg3;
    if ((D_800A56B0 <= temp_fv0) || (temp_fv0 <= D_800D9B20)) {
        return 0;
    }
    if (temp_fv0 != 0.0f) {
        *var_t0 = 1.0f / temp_fv0;
        temp_t9 = arg5 * 0x180;
        temp_v1 = D_800BE628 + temp_t9;
        arg1[0] = (*var_t0 * (arg1[0] * (*(f32 *)(temp_v1 + 0xC) + 5.0f))) +
                  *(f32 *)(temp_v1 + 0x34);
        arg1[1] = *(f32 *)(D_800BE628 + temp_t9 + 0x38) -
                  (*var_t0 * (arg1[1] * (*(f32 *)(temp_v1 + 0x10) + 5.0f)));
        return 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15144CEC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15144CEC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15144E80.s")
void func_151450B4(void *arg0, void *arg1, void *arg2) {
    *(f32 *)((u8 *)arg2 + 0) = (f32) ((*(f32 *)((u8 *)arg0 + 4) * *(f32 *)((u8 *)arg1 + 8)) - (*(f32 *)((u8 *)arg1 + 4) * *(f32 *)((u8 *)arg0 + 8)));
    *(f32 *)((u8 *)arg2 + 4) = (f32) ((*(f32 *)((u8 *)arg0 + 8) * *(f32 *)((u8 *)arg1 + 0)) - (*(f32 *)((u8 *)arg1 + 8) * *(f32 *)((u8 *)arg0 + 0)));
    *(f32 *)((u8 *)arg2 + 8) = (f32) ((*(f32 *)((u8 *)arg0 + 0) * *(f32 *)((u8 *)arg1 + 4)) - (*(f32 *)((u8 *)arg1 + 0) * *(f32 *)((u8 *)arg0 + 4)));
}
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Game16EE20Vector3;

s32 func_15145128(Game16EE20Vector3 *arg0, Game16EE20Vector3 *arg1,
    f32 *arg2, f32 *arg3) {
    f32 magnitude_squared;
    f32 inverse;

    if (arg3 == 0) {
        arg3 = &inverse;
    }
    magnitude_squared = (arg0->x * arg0->x) + (arg0->y * arg0->y) +
                        (arg0->z * arg0->z);
    if (magnitude_squared == 0.0f) {
        return 0;
    }
    if (arg2 != 0) {
        *arg2 = sqrtf(magnitude_squared);
        *arg3 = 1.0f / *arg2;
    } else {
        *arg3 = 1.0f / sqrtf(magnitude_squared);
    }
    arg1->x = *arg3 * arg0->x;
    arg1->y = *arg3 * arg0->y;
    arg1->z = *arg3 * arg0->z;
    return 1;
}
s32 func_151452C4(void *, void *, s32, f32, s32, s32, f32 *, f32 *);

s32 func_151451F0(void *arg0, void *arg1, s32 arg2, f32 arg3, f32 arg4,
                  s32 arg5, s32 arg6, f32 *arg7, f32 *arg8) {
    f32 value;

    if (func_151452C4(arg0, arg1, arg2, arg3, arg5, arg6, arg7, arg8) != 0) {
        value = *arg7;
        if ((value < 0.0f) && (*arg8 < 0.0f)) {
            return 0;
        }
        if ((value >= 0.0f) && (*arg8 < 0.0f)) {
            return 1;
        }
        if (value < arg4) {
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151452C4.s")
s32 func_151454BC(u8 arg0, f32 arg1, void *arg2) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    void *temp_v0;

    temp_v0 = func_15144B34((s32) arg0);
    temp_fv0 = *(f32 *)((u8 *)arg2 + 0) - *(f32 *)((u8 *)temp_v0 + 0);
    temp_fv1 = *(f32 *)((u8 *)arg2 + 4) - *(f32 *)((u8 *)temp_v0 + 4);
    temp_fa0 = *(f32 *)((u8 *)arg2 + 8) - *(f32 *)((u8 *)temp_v0 + 8);
    if ((arg1 * arg1) < ((temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0))) {
        return 0;
    }
    return 1;
}
s32 func_1514563C(f32 *, f32 *, f32 *, f32 *, f32 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15145548 CURRENT (3785) */
void func_15145548(void *arg0, void *arg1, void *arg3, f32 *arg4) {
    f32 sp24;
    f32 temp_fv0;

    if (arg4 == 0) {
        arg4 = &sp24;
    }
    if (func_1514563C(arg4) != 0) {
        temp_fv0 = *arg4;
        if (temp_fv0 < 0.0f) {
            *(f32 *)((u8 *)arg3 + 0) = (f32) *(f32 *)((u8 *)arg0 + 0);
            *(f32 *)((u8 *)arg3 + 4) = (f32) *(f32 *)((u8 *)arg0 + 4);
            goto block_8;
        }
        if (temp_fv0 > 1.0f) {
            *(f32 *)((u8 *)arg3 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) + *(f32 *)((u8 *)arg1 + 0));
            *(f32 *)((u8 *)arg3 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) + *(f32 *)((u8 *)arg1 + 4));
            *(f32 *)((u8 *)arg3 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) + *(f32 *)((u8 *)arg1 + 8));
        }
    } else {
        *(f32 *)((u8 *)arg3 + 0) = (f32) *(f32 *)((u8 *)arg0 + 0);
        *(f32 *)((u8 *)arg3 + 4) = (f32) *(f32 *)((u8 *)arg0 + 4);
block_8:
        *(f32 *)((u8 *)arg3 + 8) = *(f32 *)((u8 *)arg0 + 8);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15145548 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145548.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514563C CURRENT (1600) */
s32 func_1514563C(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3,
                  f32 *arg4) {
    f32 sp10;
    f32 sp0;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft1;
    f32 temp_fv0;
    f32 temp_fv1;

    if (arg4 == 0) {
        arg4 = &sp10;
    }
    temp_fv1 = arg1[0];
    temp_fa0 = arg1[1];
    temp_fa1 = arg1[2];
    temp_fv0 = (temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0) +
               (temp_fa1 * temp_fa1);
    if (temp_fv0 == 0.0f) {
        return 0;
    }
    temp_ft1 = (((temp_fv1 * arg2[0]) + (temp_fa0 * arg2[1]) +
                 (temp_fa1 * arg2[2])) -
                ((temp_fv1 * arg0[0]) + (temp_fa0 * arg0[1]) +
                 (temp_fa1 * arg0[2]))) / temp_fv0;
    sp0 = temp_ft1;
    *arg4 = temp_ft1;
    arg3[0] = (temp_ft1 * arg1[0]) + arg0[0];
    arg3[1] = (*arg4 * arg1[1]) + arg0[1];
    arg3[2] = (*arg4 * arg1[2]) + arg0[2];
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514563C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514563C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145740.s")
/* Call context: func_150484A0: unique active project prototype */
f32 func_150484A0(f32, f32);
extern f32 D_800A56BC;
extern f32 D_800A56C0;

void func_15145974(void *arg0, f32 *arg1, f32 *arg2) {
    f32 temp_ft4;
    f32 temp_fv1;

    *arg1 = func_150484A0(*(f32 *)((u8 *)arg0 + 0), *(f32 *)((u8 *)arg0 + 8)) * D_800A56BC;
    if (arg2 != 0) {
        temp_fv1 = *(f32 *)((u8 *)arg0 + 0);
        temp_ft4 = *(f32 *)((u8 *)arg0 + 8);
        *arg2 = (func_150484A0(sqrtf((temp_fv1 * temp_fv1) + (temp_ft4 * temp_ft4)), *(f32 *)((u8 *)arg0 + 4)) * D_800A56C0) - 90.0f;
    }
}
extern f32 D_800A548C[];

f32 func_15145A0C(f32 arg0, f32 arg1, f32 arg2) {
    return D_800A548C[(s32) (arg0 * arg2 * 100.0f)] * arg1;
}
/* Call context: func_15053694: unique active project prototype */
void func_15053694(u8 *);

void func_15145A50(u8 *arg0) {
    s32 temp_v0;
    void *temp_v0_2;

    *(s8 *)((u8 *)arg0 + 5) = 3;
    if (D_800BE9F0 != 0x33) {
        if ((D_800BE616 != 0) || (temp_v0 = *(s32 *)((u8 *)arg0 + 0), (temp_v0 == 5)) || (temp_v0 == 1) || (temp_v0 == 0x15)) {
            temp_v0_2 = *(void **)((u8 *)arg0 + 0x31C);
            *(s32 *)((u8 *)arg0 + 0) = 5;
            if (temp_v0_2 != 0) {
                *(s8 *)((u8 *)temp_v0_2 + 0x78) = 0;
            }
        } else {
            func_15053694(arg0);
        }
    }
}
typedef struct Game145AD8Locals {
    f32 sp38;
    f32 sp3C;
    f32 sp40;
    f32 sp44;
    f32 sp48;
    f32 sp4C;
    Game16EE20Vector3 third;
    Game16EE20Vector3 second;
    Game16EE20Vector3 first;
    f32 sp74;
    f32 sp78;
} Game145AD8Locals;

void func_1515C1A0(void *, void *, f32 *, f32 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15145AD8 CURRENT (2526) */
s32 func_15145AD8(Game16EE20Vector3 *arg0, Game16EE20Vector3 *arg1,
                   u8 *arg2, f32 *arg3, f32 *arg4, f32 *arg5,
                   f32 *arg6, Game16EE20Vector3 *arg7) {
    Game145AD8Locals local;
    Game16EE20Vector3 sp7C;
    Game16EE20Vector3 *third;
    f32 scale;

    if (arg5 != 0) {
        arg5 = &local.sp78;
    }
    if (arg6 != 0) {
        arg6 = &local.sp74;
    }
    third = arg7;
    if (third != 0) {
        third = &sp7C;
    }
    func_1515C1A0(arg2, third, arg5, arg6);
    if (*arg6 == 0.0f) {
        return 0;
    }
    if (*arg5 == 0.0f) {
        return 0;
    }
    scale = *(f32 *)(arg2 + 0xDC);
    local.sp3C = *(f32 *)(arg2 + 0xE0);
    local.first.x = arg0->x;
    local.first.y = arg0->y * scale;
    local.first.z = arg0->z;
    local.second.x = arg1->x;
    local.second.y = arg1->y * scale;
    local.second.z = arg1->z;
    local.sp40 = scale;
    if (func_15145128(&local.second, &local.second,
                      &local.sp4C, &local.sp38) == 0) {
        return 0;
    }
    local.third.x = third->x;
    local.third.y = third->y * local.sp40;
    local.third.z = third->z;
    if (func_151451F0(&local.first, &local.second, (s32)&local.third,
                      *arg5, local.sp4C, (s32)arg3, (s32)arg4,
                      &local.sp48, &local.sp44) == 0) {
        return 0;
    }
    arg3[1] *= local.sp3C;
    arg4[1] *= local.sp3C;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15145AD8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145AD8.s")
extern s32 D_800DBEF4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15145C90 CURRENT (85) */
s32 func_15145C90(s32 arg0) {
    u8 *base;

    if (arg0 < 0) {
        return 1;
    }
    base = (u8 *)D_800DBEF4;
    return ((base[(arg0 * 0xA0) + 0x6F] & 0x80) == 0x80) & 0xFF;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15145C90 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145C90.s")
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);

typedef struct Game16EE20Transform {
    f32 values[12];
} Game16EE20Transform;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15145CD0 CURRENT (1645) */
void func_15145CD0(u8 *arg0, f32 **arg1, f32 **arg2, s32 arg3) {
    volatile f32 sp80;
    volatile f32 sp7C;
    volatile f32 sp78;
    Game16EE20Transform sp48;
    f32 **var_s2;
    f32 *temp_v1;
    s32 var_s0;
    f32 **var_s1;
    f32 *temp_v0;

    var_s0 = arg3;
    func_150A8050(&sp48, *(f32 *)(arg0 + 0), *(s32 *)(arg0 + 4),
                   *(f32 *)(arg0 + 8));
    var_s2 = arg2;
    sp78 = (f32)*(s16 *)(arg0 + 0x10);
    sp7C = (f32)*(s16 *)(arg0 + 0x12);
    var_s1 = arg1;
    sp80 = (f32)*(s16 *)(arg0 + 0x14);
    if (var_s0 > 0) {
        do {
            temp_v0 = *var_s1;
            temp_v1 = *var_s2;
            func_150A7960(&sp48, temp_v0[0], temp_v0[1], temp_v0[2],
                           temp_v1, temp_v1 + 1, temp_v1 + 2);
            var_s0 -= 1;
            var_s1 += 1;
            var_s2 += 1;
        } while (var_s0 > 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15145CD0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145CD0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15145DB4 CURRENT (1259) */
void func_15145DB4(u8 *arg0, u8 *arg1, f32 *arg2, register s32 arg3) {
    struct {
        u32 pad;
        Game16EE20Transform transform;
        volatile f32 x;
        volatile f32 y;
        volatile f32 z;
    } locals;
    f32 *out_x;
    f32 *out_y;
    f32 *out_z;
    s32 count;
    u8 *input;

    count = arg3;
    func_150A8050(&locals.transform, *(f32 *)(arg0 + 0), *(s32 *)(arg0 + 4),
                   *(f32 *)(arg0 + 8));
    out_x = arg2;
    out_y = out_x + 1;
    out_z = out_x + 2;
    locals.x = (f32)*(s16 *)(arg0 + 0x10);
    locals.y = (f32)*(s16 *)(arg0 + 0x12);
    locals.z = (f32)*(s16 *)(arg0 + 0x14);
    if (count > 0) {
        input = arg1;
        do {
            func_150A7960(&locals.transform, *(f32 *)(input + 0),
                           *(f32 *)(input + 4), *(f32 *)(input + 8),
                           out_x, out_y, out_z);
            count--;
            input += 0xC;
            out_x += 3;
            out_y += 3;
            out_z += 3;
        } while (count > 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15145DB4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145DB4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145EA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15146078.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151462C8.s")
extern s32 D_80082FA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151464B8 CURRENT (245) */
s32 func_151464B8(void *arg0) {
    s16 var_v1;
    s32 temp_t7;
    s32 var_v0;

    var_v0 = 0;
    var_v1 = 0;
    if (D_80082FA0 >= 0) {
        do {
            temp_t7 = 1 << var_v0;
            var_v0 += 1;
            var_v1 |= temp_t7;
        } while (D_80082FA0 >= var_v0);
    }
    return ((*(s16 *)((u8 *)arg0 + 2) & var_v1) == 0) & 0xFF;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151464B8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151464B8.s")
extern void func_15169040(s32 arg0, u8 arg1);

void func_15146508(void *arg0, void *arg1) {
    struct {
        void *field0;
        void *field4;
        u8 field8;
        u8 field9;
    } sp1C;

    sp1C.field0 = arg0;
    sp1C.field4 = arg1;
    sp1C.field8 = *(u8 *)((u8 *) arg0 + 0x3B);
    sp1C.field9 = *(u8 *)((u8 *) arg1 + 0x3B);
    func_15169040((s32) &sp1C, 0x2D);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514654C.s")
extern f32 D_800A56C4;
extern f32 D_800A56C8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514672C CURRENT (215) */
s32 func_1514672C(void *arg0) {
    f32 temp_fv0;

    if ((D_800A56C4 < fabsf(*(f32 *)((u8 *)arg0 + 0))) || (D_800A56C4 < fabsf(*(f32 *)((u8 *)arg0 + 8))) || (temp_fv0 = *(f32 *)((u8 *)arg0 + 4), (D_800A56C4 < temp_fv0)) || (temp_fv0 < D_800A56C8)) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514672C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514672C.s")
s32 func_150ADA20(f32 *);                           /* extern */
f32 func_150ADA68();                                /* extern */
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151467A4 CURRENT (110) */
void func_151467A4(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 *arg7) {
    f32 temp_fv0;

    *arg0 -= D_800BE9A4;
    if (*arg0 < 0.0f) {
        *arg0 = func_150ADA68() * arg1;
        if (func_150ADA20(arg0) & 3) {
            *arg2 = (func_150ADA68() * (arg4 - arg3)) + arg3;
        } else {
            *arg2 = (func_150ADA68() * (arg5 - arg4)) + arg4;
        }
    }
    temp_fv0 = *arg7;
    *arg7 = temp_fv0 + ((*arg2 - temp_fv0) * arg6);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151467A4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151467A4.s")
