#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_EC420.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150BF21C
 * - func_150BFA7C
 * - func_150C01DC
 * - func_150C0648
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150BEF70(s32 arg0) {

}
/* Call context: func_1516D99C: matched US definition in src/game/game_19A8B0.c */
void func_1516D99C(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, u8, s32);

void func_150BEF7C(s32 arg0) {
    s32 var_s0;
    s32 var_s1;

    var_s0 = 0x17C;
    var_s1 = 0;
    do {
        func_1516D99C(
            0x1FDB, 0x25, (s16)var_s0, 0xD,
            0, 0x50, 0x8F, 0,
            0, 0, 0, 0,
            8, 0xC8, 0xA, 0,
            0, 0, 0, 0,
            0x28, 0x28, 4, 0,
            0, 0, 0, 0x555,
            0x555, 0x555, 0x555, arg0 & 0xFFFF,
            0x32, 0, 0xFF, 0x14,
            0xFA0, 0x7D0, 1, 6,
            0, 1, 0, 0,
            0, 0, 3, 0xFFU,
            0);
        var_s1 += 1;
        var_s0 = -var_s0;
    } while (var_s1 != 2);
}
extern s32 D_800BE9E4;

s32 func_150BF0F4(void *arg0) {
    s32 var_v1;
    s32 var_v0;

    var_v0 = *(u8 *)((u8 *)arg0 + 0x1F);
    var_v1 = *(u8 *)((u8 *)arg0 + 0x26);
    if (*(u8 *)((u8 *)arg0 + 0x24) != 0) {
        if (var_v0 != var_v1) {
            var_v0 += D_800BE9E4 * *(u8 *)((u8 *)arg0 + 0x27);
            if ((s32) var_v1 < (s32) var_v0) {
                var_v0 = var_v1;
            }
            *(u8 *)((u8 *)arg0 + 0x1F) = var_v0;
        }
    } else if (var_v0 != 0) {
        var_v0 -= D_800BE9E4 * *(u8 *)((u8 *)arg0 + 0x2F);
        if ((s32) var_v0 < 0) {
            var_v0 = 0;
        }
        *(u8 *)((u8 *)arg0 + 0x1F) = var_v0;
    }
    if ((*(u8 *)((u8 *)arg0 + 0x24) == 0) && (var_v0 == 0)) {
        return 1;
    }
    var_v0 = *(s8 *)((u8 *)arg0 + 0x2D);
    var_v0 *= D_800BE9E4;
    *(s16 *)((u8 *)arg0 + 0x14) += var_v0;
    var_v1 = *(s16 *)((u8 *)arg0 + 0x14);
    var_v0 = *(s8 *)((u8 *)arg0 + 0x2E);
    var_v0 *= D_800BE9E4;
    *(s16 *)((u8 *)arg0 + 0x16) += var_v0;
    if ((var_v1 <= 0) || (var_v1 <= 0)) {
        *(s16 *)((u8 *)arg0 + 0x16) = 0;
        *(s16 *)((u8 *)arg0 + 0x14) = (s16) *(s16 *)((u8 *)arg0 + 0x16);
        return 1;
    }
    var_v1 = *(u8 *)((u8 *)arg0 + 0x2C);
    var_v1 += D_800BE9E4;
    if (var_v1 >= 0x80) {
        var_v1 = 0x7F;
    }
    *(u8 *)((u8 *)arg0 + 0x2C) = (u8) var_v1;
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_EC420/func_150BF21C.s")
f32 func_15047D60(f32);
void func_15060F28(u8 *, s32);
void func_150825C0(s32, s32);
s32 func_15083E0C(s32);
void *func_15083E90(u8);
void func_1511B51C(void *);
extern s32 D_800902B8;
extern f32 D_800A0124, D_800A0128, D_800A012C, D_800A0130;
extern u8 D_800C35E8, D_800C35EA;
extern u8 *D_800D20FC;

void func_150BF760(u8 *arg0) {
    u8 *actor;
    f32 *motion;
    s32 mode;
    s32 index;
    f32 ratio = 0.0f;

    if (D_800C35EA != 1 || D_800C35E8 == 1) {
        func_1511B51C(arg0);
        if (*(void **)(arg0 + 0x124) == 0) {
            *(void **)(arg0 + 0x124) = func_15195FB0((struct CharacterFlamethrowerDispatch *)arg0, D_800902B8, 1, -1, 0, 0, -8);
        }
        actor = func_15083E90(0x14);
        mode = arg0[0x73] & 3;
        if (actor != 0) {
            motion = *(f32 **)(actor + 0x2D0);
            ratio = motion[2] / (motion[6] - 2.0f);
        }
        *(f32 *)(arg0 + 0xA8) = 0.0f;
        if (mode == 2) {
            if (ratio <= 0.75f) {
                *(f32 *)(arg0 + 0xA8) = -func_15047D60(ratio * D_800A0124 * D_800A0128) * 10.0f;
            }
            if (actor == 0) {
                index = func_15083E0C(0x14);
                D_800D20FC[index * 0x30 + 2] = 0;
                func_150825C0(index, 0);
                actor = func_15083E90(0x14);
            }
            if (actor[0x232] != 2) {
                actor[0x232] = 2;
                *(s32 *)(actor + 0x218) = 0;
            }
        } else if (mode == 3) {
            if (actor != 0 && ratio >= 1.0f) {
                func_15060F28(actor, 0);
            }
        } else if (mode == 0) {
            if (ratio >= 0.25f) {
                *(f32 *)(arg0 + 0xA8) = func_15047D60(ratio * D_800A012C - D_800A012C) * 10.0f;
            }
            if (actor != 0 && ratio >= 1.0f) {
                func_15060F28(actor, 0);
            }
        } else if (mode == 1) {
            if (ratio >= 0.25f) {
                *(f32 *)(arg0 + 0xA8) = func_15047D60(ratio * D_800A0130 - D_800A0130) * 10.0f;
            }
            if (actor == 0) {
                index = func_15083E0C(0x14);
                D_800D20FC[index * 0x30 + 2] = 0;
                func_150825C0(index, 0);
                actor = func_15083E90(0x14);
            }
            /* Preserve the null test in the original US routine. */
            if (actor == 0 && actor[0x232] != 3) {
                actor[0x232] = 3;
                *(s32 *)(actor + 0x218) = 0;
            }
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_EC420/func_150BFA7C.s")
typedef struct GameEC420Spawn {
    s16 field00;
    s16 field02;
    u8 field04;
    s16 field06;
    s32 field08;
    s32 field0C;
    s16 field10;
    s16 field12;
    s32 field14;
    s32 field18;
    u8 field1C;
    u8 field1D;
    u8 field1E;
    u8 field1F;
    u8 field20;
    u8 field21;
    u8 field22;
    u8 field23;
    u8 field24;
    u8 field25;
    s16 field26;
    s16 field28;
    s16 field2A;
    f32 field2C;
    f32 field30;
    f32 field34;
    f32 field38;
    f32 field3C;
    f32 field40;
    s16 field44;
    s16 field46;
    s16 field48;
    s16 field4A;
    f32 field4C;
    f32 field50;
    f32 field54;
    f32 field58;
    s32 field5C;
    s8 field60;
    s8 field61;
    s8 field62;
    s8 field63;
    s8 field64;
    f32 field68;
} GameEC420Spawn;

struct Blood36C3CActor;
void func_15136C3C(struct Blood36C3CActor *, u8, u8, u8, u8, u8, u8, s32);
void func_15153634(GameEC420Spawn *, s32, s32, s32);
extern f32 D_800A0134;
extern f32 D_800A0138;
extern f32 D_800A013C;
extern f32 D_800A0140;
extern f32 D_800A0144;
extern f32 D_800A0148;

void func_150BFFE0(void *arg0) {
    f32 position[3];
    GameEC420Spawn spawn;

    position[0] = *(f32 *)((u8 *)arg0 + 0x14);
    position[1] = *(f32 *)((u8 *)arg0 + 0x180) + 70.0f;
    position[2] = *(f32 *)((u8 *)arg0 + 0x1C);
    func_15136C3C(arg0, 0, 0, 1, 0, 0, 0xFF, 1);
    spawn.field00 = 0x11;
    spawn.field02 = 7;
    spawn.field04 = 0x6C;
    spawn.field06 = 0x5103;
    spawn.field08 = 0x200005;
    spawn.field0C = 0;
    spawn.field10 = 0x28;
    spawn.field12 = 0x14;
    spawn.field14 = 0;
    spawn.field18 = 0;
    spawn.field1F = 0xFF;
    spawn.field1C = 0x4E;
    spawn.field1D = 0x54;
    spawn.field1E = 0x7B;
    spawn.field20 = 0xA4;
    spawn.field21 = 0xA1;
    spawn.field22 = 0xC8;
    spawn.field23 = 0x9B;
    spawn.field24 = 0x64;
    spawn.field25 = 0xFF;
    spawn.field26 = 0x1E;
    spawn.field28 = 8;
    spawn.field2A = 0x1E;
    spawn.field2C = D_800A0134;
    spawn.field30 = D_800A0138;
    spawn.field34 = D_800A013C;
    spawn.field38 = position[0];
    spawn.field3C = position[1] + 35.0f;
    spawn.field40 = position[2];
    spawn.field44 = 0;
    spawn.field46 = -0x14;
    spawn.field48 = 0xFF;
    spawn.field4A = 0x1E;
    spawn.field4C = 15.0f;
    spawn.field50 = 39.0f;
    spawn.field54 = D_800A0140;
    spawn.field58 = D_800A0144;
    spawn.field5C = 0x40040E07;
    spawn.field60 = 0x10;
    spawn.field61 = -1;
    spawn.field62 = 8;
    spawn.field63 = 6;
    spawn.field64 = 1;
    spawn.field68 = D_800A0148;
    func_15153634(&spawn, 0xFF, 0xFF, 1);
}
typedef struct GameEC420Position { f32 x; f32 y; f32 z; } GameEC420Position;
typedef struct GameEC420Word { s32 value; } GameEC420Word;
typedef struct GameEC420Burst {
    s32 field00;
    s32 field04;
    GameEC420Position position;
    s16 field14;
    s16 field16;
    s16 field18;
    s16 field1A;
    f32 field1C;
    f32 field20;
    f32 field24;
    f32 field28;
    s16 field2C;
    s16 field2E;
    f32 field30;
    f32 field34;
    f32 field38;
} GameEC420Burst;
void func_15152190(void *, void *, void *, s32, f32, s32, s32, s32);
extern GameEC420Word D_800A0100;
extern GameEC420Word D_800A0104;
extern f32 D_800A014C;
extern f32 D_800A0150;
extern f32 D_800A0154;
extern f32 D_800A0158;
extern f32 D_800A015C;
extern f32 D_800A0160;
extern f32 D_800A0164;
extern f32 D_800A0168;
extern f32 D_800A016C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C01DC CURRENT (910) */
s32 func_150C01DC(void *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    GameEC420Position position;
    GameEC420Burst burst;
    GameEC420Word word1;
    GameEC420Word word2;
    GameEC420Spawn spawn;

    position.x = *(f32 *)((u8 *)arg0 + 0x38);
    position.y = arg4 + 20.0f;
    position.z = *(f32 *)((u8 *)arg0 + 0x40);
    word1 = D_800A0100;
    word2 = D_800A0104;
    burst.field00 = 5;
    burst.field04 = 4;
    burst.position = position;
    burst.field1C = 12.0f;
    burst.field20 = 8.0f;
    burst.field14 = 0;
    burst.field16 = 0xFF;
    burst.field18 = -0x40;
    burst.field1A = 0x22;
    burst.field2C = 0x1E;
    burst.field2E = 0xF;
    burst.field24 = D_800A014C;
    burst.field28 = D_800A0150;
    burst.field30 = D_800A0154;
    burst.field34 = D_800A0158;
    burst.field38 = D_800A015C;
    func_15152190(&burst, &word1, &word2, 1, 0.0f, 1, (s32) *(u8 *)((u8 *)arg0 + 0xC), (s32) *((u8 *)arg0 + 1));
    spawn.field00 = 5;
    spawn.field02 = 8;
    spawn.field04 = 0x6C;
    spawn.field06 = 0x5103;
    spawn.field08 = 0x200005;
    spawn.field0C = 0;
    spawn.field10 = 0x1E;
    spawn.field12 = 0xF;
    spawn.field14 = 0;
    spawn.field18 = 0;
    spawn.field1F = 0xFF;
    spawn.field1C = 0x4E;
    spawn.field1D = 0x54;
    spawn.field1E = 0x7B;
    spawn.field20 = 0xA4;
    spawn.field21 = 0xA1;
    spawn.field22 = 0xC8;
    spawn.field23 = 0x64;
    spawn.field24 = 0x9B;
    spawn.field25 = 0xFF;
    spawn.field26 = 0xE;
    spawn.field28 = 0x12;
    spawn.field2A = 0xE;
    spawn.field2C = D_800A0164;
    spawn.field30 = 218.0f;
    spawn.field34 = D_800A0168;
    *(GameEC420Position *)&spawn.field38 = position;
    spawn.field44 = 0;
    spawn.field46 = -0x28;
    spawn.field48 = 0xFF;
    spawn.field4A = 0x28;
    spawn.field4C = 19.0f;
    spawn.field50 = 8.0f;
    spawn.field54 = 0.26200002431869507f;
    spawn.field58 = 0.26200002431869507f;
    spawn.field5C = 0x840E07;
    spawn.field60 = 0x10;
    spawn.field61 = -1;
    spawn.field62 = 8;
    spawn.field63 = 6;
    spawn.field64 = 1;
    spawn.field68 = D_800A016C;
    func_15153634(&spawn, 0xFF, (s32) *(u8 *)((u8 *)arg0 + 0xC), (s32) *((u8 *)arg0 + 1));
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C01DC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EC420/func_150C01DC.s")
typedef struct GameEC420Vec3 {
    s32 x;
    s32 y;
    s32 z;
} GameEC420Vec3;

typedef struct GameEC420Head {
    s32 value;
} GameEC420Head;

typedef struct GameEC420Packet {
    f32 base;
    GameEC420Head head;
    s32 arg2;
    s16 config[4];
    s32 count;
    s32 mode;
    GameEC420Vec3 position;
    f32 value4;
    f32 value7;
    f32 value2C;
    f32 value30;
    s16 value50;
    s16 value3C;
    f32 value38;
    f32 value3CFloat;
    f32 value40;
    s32 arg1;
    f32 value48;
    f32 value4C;
    f32 value50Float;
    f32 value10;
    s32 *arg2Pointer;
    s32 *headPointer;
    s32 one;
    f32 value78;
    s8 enabled;
    s8 value14;
    u8 pad6A[2];
    s32 four;
    f32 *basePointer;
} GameEC420Packet;

void func_15150400(s32 *, s16 *, u8, s32);
extern GameEC420Head D_800A0108;
extern f32 D_800A0170;
extern f32 D_800A0174;
extern f32 D_800A0178;
extern f32 D_800A017C;
extern f32 D_800A0180;
extern f32 D_800A0184;
extern f32 D_800A0188;
extern f32 D_800A018C;
extern f32 D_800A0190;

void func_150C04C0(void *arg0, s32 arg1, s32 arg2, u8 arg3, u8 arg4, s32 arg5) {
    GameEC420Packet packet;
    s8 enabled;

    packet.head = D_800A0108;
    packet.arg2 = arg2;
    packet.count = 9;
    packet.mode = 4;
    packet.base = D_800A0170;
    packet.position = *(GameEC420Vec3 *)arg0;
    packet.value4 = 4.0f;
    packet.value7 = 7.0f;
    packet.value2C = D_800A0174;
    packet.value30 = D_800A0178;
    packet.value38 = D_800A017C;
    packet.value3CFloat = D_800A0180;
    packet.value50 = 0x50;
    packet.value3C = 0x3C;
    packet.arg1 = arg1;
    packet.arg2Pointer = &packet.arg2;
    packet.headPointer = &packet.head.value;
    packet.one = 1;
    packet.value40 = D_800A0184;
    packet.value48 = D_800A0188;
    packet.value4C = D_800A018C;
    packet.value50Float = D_800A0190;
    packet.value10 = 10.0f;
    packet.value78 = 78.0f;
    if (arg3 != 0) {
        enabled = 1;
    } else {
        enabled = 0;
    }
    packet.enabled = enabled;
    packet.value14 = 0xE;
    packet.four = 4;
    packet.basePointer = &packet.base;
    packet.config[0] = 0;
    packet.config[1] = 0xFF;
    packet.config[2] = -0x32;
    packet.config[3] = 0x23;
    func_15150400(&packet.count, packet.config, arg4, arg5);
}
typedef struct GameEC420CollisionPacket {
    GameEC420Head head;
    s32 arg2;
    s16 config[4];
    s32 count;
    s32 mode;
    GameEC420Position position;
    f32 value4;
    f32 value7;
    f32 value2C;
    f32 value30;
    s16 value50;
    s16 value3C;
    f32 value38;
    f32 value3CFloat;
    f32 value40;
    s32 arg1;
    f32 value48;
    f32 value4C;
    f32 value50Float;
    f32 value10;
    s32 *arg2Pointer;
    s32 *headPointer;
    s32 one;
    f32 value78;
    s8 enabled;
    s8 value14;
    u8 pad6A[2];
    s32 four;
    f32 *basePointer;
} GameEC420CollisionPacket;

f32 func_150ADA68(void);
s32 func_15133B98(void *, f32, f32, f32, f32, s32);
extern GameEC420Head D_800A010C;
extern f32 D_800A0194;
extern f32 D_800A0198;
extern f32 D_800A019C;
extern f32 D_800A01A0;
extern f32 D_800A01A4;
extern f32 D_800A01A8;
extern f32 D_800A01AC;
extern f32 D_800A01B0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C0648 CURRENT (2699) */
s32 func_150C0648(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    f32 height;
    GameEC420CollisionPacket packet;
    GameEC420Spawn spawn;
    f32 zero;

    if (func_150ADA68() < *(f32 *)((u8 *)arg0 + 0x170)) {
        zero = 0.0f;
        packet.head = D_800A010C;
        packet.arg2 = *(u16 *)((u8 *)arg0 + 0x66);
        packet.count = 2;
        packet.mode = 0;
        height = arg4 + 20.0f;
        packet.position.x = *(f32 *)((u8 *)arg0 + 0x38);
        packet.position.y = height;
        packet.position.z = *(f32 *)((u8 *)arg0 + 0x40);
        packet.value50 = 0x28;
        packet.value3C = 0x1E;
        packet.value4 = 5.0f;
        packet.value7 = 4.0f;
        packet.value2C = D_800A0194;
        packet.value30 = D_800A0198;
        packet.value38 = *(f32 *)((u8 *)arg0 + 0x18) * D_800A019C;
        packet.value3CFloat = *(f32 *)((u8 *)arg0 + 0x18) * D_800A01A0;
        packet.arg1 = (s32)((u8 *)arg0 + 0x110);
        packet.value4C = zero;
        packet.value50Float = zero;
        packet.arg2Pointer = &packet.arg2;
        packet.headPointer = &packet.head.value;
        packet.one = 1;
        packet.value78 = zero;
        packet.value40 = D_800A01A4;
        packet.value48 = 1.0f;
        packet.value10 = 10.0f;
        if (*(s32 *)((u8 *)arg0 + 0x60) & 0x800) {
            arg5 = 1;
        } else {
            arg5 = 0;
        }
        packet.enabled = (s8)arg5;
        packet.value14 = 10;
        packet.four = 0;
        packet.basePointer = 0;
        packet.config[0] = 0;
        packet.config[1] = 0xFF;
        packet.config[2] = -0x2A;
        packet.config[3] = 0x19;
        func_15150400(&packet.count, packet.config, *((u8 *)arg0 + 0xC), *((u8 *)arg0 + 1));
        spawn.field00 = 1;
        spawn.field02 = 2;
        spawn.field04 = 0x6C;
        spawn.field06 = 0x5103;
        spawn.field08 = 0x200005;
        spawn.field10 = 0x1E;
        spawn.field12 = 0x10;
        spawn.field1F = 0xFF;
        spawn.field1C = 0x4E;
        spawn.field1D = 0x54;
        spawn.field0C = 0;
        spawn.field14 = 0;
        spawn.field18 = 0;
        spawn.field1E = 0x7B;
        spawn.field20 = 0xA4;
        spawn.field21 = 0xA1;
        spawn.field22 = 0xC8;
        spawn.field23 = 0xC8;
        spawn.field24 = 0x37;
        spawn.field25 = 0xFF;
        spawn.field26 = 0x14;
        spawn.field28 = 0xC;
        spawn.field2A = 0x14;
        spawn.field2C = D_800A01A8;
        spawn.field30 = 178.0f;
        spawn.field34 = 91.0f;
        spawn.field38 = *(f32 *)((u8 *)arg0 + 0x38);
        spawn.field3C = height;
        spawn.field40 = *(f32 *)((u8 *)arg0 + 0x40);
        spawn.field44 = 0;
        spawn.field46 = -0x12;
        spawn.field48 = 0xFF;
        spawn.field4A = 0xB;
        spawn.field5C = 0x40040E07;
        spawn.field60 = 0x10;
        spawn.field61 = -1;
        spawn.field62 = 8;
        spawn.field63 = 6;
        spawn.field64 = 1;
        spawn.field4C = 4.0f;
        spawn.field50 = 6.0f;
        spawn.field54 = D_800A01AC;
        spawn.field58 = 0.0f;
        spawn.field68 = D_800A01B0;
        func_15153634(&spawn, 0xFF, *((u8 *)arg0 + 0xC), *((u8 *)arg0 + 1));
        return 0;
    }
    return func_15133B98(arg0, arg1, arg2, arg3, arg4, arg5);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C0648 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EC420/func_150C0648.s")
