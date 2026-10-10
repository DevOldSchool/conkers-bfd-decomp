#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_40490.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_early_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15013000
 * - func_150130B4
 * - func_15013778
 * - func_150139AC
 * - func_15013DE8
 * - func_15014094
 * - func_150144B8
 * - func_1501474C
 * - func_15014B60
 * - func_15015354
 * - func_150156F4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800BE570;
extern s8 D_800BE574;
extern s8 D_800BE575;

typedef s32 (*Game40490SimpleCallback)(u8 *);

extern Game40490SimpleCallback D_80082EA0[];
extern Game40490SimpleCallback D_80082ECC[];
extern Game40490SimpleCallback D_80082F40[];

void func_15012FE0(void) {
    D_800BE570 = 0;
    D_800BE574 = 0;
    D_800BE575 = 0;
}
typedef void (*Game40490DispatchCallback)(u8 *, void *);
extern Game40490DispatchCallback D_80082E30[];
extern u32 D_800D3094;
extern u8 *D_800D3098;
extern f32 D_800DCD90;
extern void *D_800DCDC4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15013000 CURRENT (275) */
void func_15013000(void) {
    Game40490DispatchCallback callback;
    u32 var_s1;
    s32 var_s0;
    u8 *base;
    s32 index;

    D_800DCDC4 = 0;
    D_800DCD90 = 0.0f;
    var_s1 = 0;
    var_s0 = 0;
    if (D_800D3094 != 0) {
        do {
            base = D_800D3098;
            index = *(u8 *)((s32)base + var_s0 + 0x15);
            callback = D_80082E30[(index >> 2) & 0xFF];
            if (callback != 0) {
                callback(base + var_s0, callback);
            }
            var_s1 += 1;
            var_s0 += 0x34;
        } while (var_s1 < D_800D3094);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15013000 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15013000.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_150130B4.s")
s32 func_1501370C(u8 *arg0) {
    Game40490SimpleCallback callback;
    s32 index;

    index = arg0[0x17];
    callback = D_80082EA0[index];
    if (callback != 0) {
        callback(arg0);
    }
    return 1;
}
s32 func_1501374C(u8 *arg0) {
    arg0[0x16] |= 4;
    func_1515D088(arg0);
    return 1;
}
void *func_10022EC0(void *, const void *, u32);
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
void func_150A8050(f32 *, f32, f32, f32);
void func_1000FA64(s32, s32, s32, s32, s32, s32, s32, void *, s32, s32, s32, s32);
extern u8 D_1000EF40[];
extern f32 D_80096640;
extern f32 D_80096644;

typedef struct Game40490BeamPacket {
    f32 position[3];
    f32 direction[3];
    f32 height;
    f32 width;
    f32 rotation[2];
    f32 zero;
    f32 field2C;
    f32 field30;
} Game40490BeamPacket;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15013778 CURRENT (1233) */
s32 func_15013778(u8 *arg0) {
    s32 result;
    Game40490BeamPacket packet;
    f32 matrix[4][4];
    f32 inverse;
    s16 height;

    height = *(s16 *)(arg0 + 8);
    if (height != 0) {
        packet.height = 2.0f * (f32)height;
        inverse = 1.0f / packet.height;
        packet.width = (f32)*(s16 *)(arg0 + 6);
        packet.rotation[0] = *(f32 *)(arg0 + 0xC);
        packet.zero = 0.0f;
        packet.field2C = D_80096640;
        packet.field30 = D_80096644;
        packet.rotation[1] = *(f32 *)(arg0 + 0x10);
        packet.position[0] = (f32)*(s16 *)(arg0 + 0);
        packet.position[1] = (f32)*(s16 *)(arg0 + 2);
        packet.position[2] = (f32)*(s16 *)(arg0 + 4);
        func_150A8050(&matrix[0][0], *(s32 *)(arg0 + 0xC), *(s32 *)(arg0 + 0x10), 0);
        func_150A7960(matrix, 0.0f, packet.height, 0.0f,
                      &packet.direction[0], &packet.direction[1], &packet.direction[2]);
        packet.direction[0] *= inverse;
        packet.direction[1] *= inverse;
        packet.direction[2] *= inverse;
        result = func_15149130(0x12C, -1, 0x19, -1, 0, 0x17, 0x34, 0xFF, 0);
        if (result != 0) {
            func_10022EC0((void *)(result + 0x28), &packet, 0x34);
        }
        height = *(s16 *)(arg0 + 8);
        func_1000FA64(0x67C, *(s16 *)(arg0 + 0),
                      (s16)(*(s16 *)(arg0 + 2) + height), *(s16 *)(arg0 + 4),
                      0x2EE0, height * 2, height / 2, D_1000EF40, 0, 0, 8, 0);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15013778 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15013778.s")
s32 func_1501396C(u8 *arg0) {
    Game40490SimpleCallback callback;
    s32 index;

    index = arg0[0x17];
    callback = D_80082ECC[index];
    if (callback != 0) {
        callback(arg0);
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_150139AC.s")
typedef struct Game40490CallbackState {
    u8 pad0[0x16];
    u8 flags;
    u8 pad17;
    s32 callback_index;
    u32 callback_value;
} Game40490CallbackState;

typedef void (*Game40490Callback)(Game40490CallbackState *, f32);

extern Game40490Callback D_80082F28[];
extern f32 D_80096650;
extern s32 D_800BE9F0;
extern u8 D_800C35E8;
extern u8 D_800C35EA;
extern u8 *D_800D2E4C;

s32 func_15013C38(Game40490CallbackState *state) {
    Game40490Callback callback;
    f32 callback_value;
    s32 index;

    index = state->callback_index;
    state->flags |= 4;
    if ((D_800D2E4C[0x11] & 4) && (D_800BE9F0 == 0x13)) {
        return 1;
    }
    if ((D_800C35EA == 1) &&
        ((D_800C35E8 == 0xF) || (D_800C35E8 == 0x10) || (D_800C35E8 == 0x11))) {
        return 1;
    }
    if (index >= 6) {
        return 1;
    }
    callback = D_80082F28[index];
    if (callback != 0) {
        callback_value = D_80096650 * (f32)state->callback_value;
        callback(state, callback_value);
    }
    return 1;
}
typedef struct Game40490DispatchState {
    s16 value_x;
    s16 value_y;
    s16 value_z;
    u8 pad6[0xA];
    s32 callback_arg;
    u8 pad14[2];
    u8 flags;
    u8 pad17;
    s32 callback_result;
    u8 pad1C[3];
    u8 callback_index;
} Game40490DispatchState;

extern void func_151BE850(f32 *arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4, s32 arg5, s32 arg6);

s32 func_15013D38(Game40490DispatchState *arg0) {
    f32 position[3];
    s32 temp_v0;

    arg0->flags |= 4;
    position[0] = (f32)arg0->value_x;
    position[1] = (f32)arg0->value_y;
    position[2] = (f32)arg0->value_z;
    temp_v0 = arg0->callback_result;
    func_151BE850(&position[0], arg0->callback_arg, (temp_v0 != 0 ? temp_v0 : 1) & 0xFF, arg0->callback_index, 1, 0xFF, 1);
    return 1;
}
void func_15149550(f32 *, s32, s32, s32, s32, s32);
u32 func_150ADA20(void);
extern f32 D_80096654;
extern f32 D_80096658;
extern f32 D_8009665C;
extern f32 D_80096660;
extern f32 D_80096664;
extern f32 D_80096668;
extern f32 D_8009666C;
extern f32 D_80096670;
extern f32 D_80096674;
extern f32 D_80096678;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15013DE8 CURRENT (3102) */
s32 func_15013DE8(u8 *arg0) {
    struct {
        f32 position[3];
        f32 offsets[5];
        s16 first;
        s16 second;
        s16 angle;
        u8 bytes56[4];
        s16 short5A;
        u8 bytes5C[4];
        s32 field60;
        u8 field64;
        u8 pad65[3];
        f32 zero;
        f32 value6C;
        f32 value70;
        f32 value74;
    } packet;
    f32 scaledY;
    f32 scaledX;
    s32 mode;

    arg0[0x16] |= 4;
    packet.first = 0x6231;
    packet.second = 0x1A4D;
    packet.bytes56[0] = 0;
    packet.bytes56[1] = 0;
    packet.bytes56[2] = 0;
    packet.bytes56[3] = 0xFF;
    packet.short5A = 0;
    packet.bytes5C[1] = 0xFF;
    packet.field60 = 0;
    packet.bytes5C[2] = 0;
    packet.bytes5C[3] = 0;
    packet.field64 = 0;
    packet.value6C = D_8009665C;
    scaledX = (f32)*(s16 *)(arg0 + 6) * D_80096654;
    packet.position[0] = (f32)*(s16 *)(arg0 + 0);
    scaledY = (f32)*(s16 *)(arg0 + 8) * D_80096658;
    packet.position[1] = (f32)*(s16 *)(arg0 + 2);
    packet.angle = 300;
    packet.position[2] = (f32)*(s16 *)(arg0 + 4);
    packet.zero = 0.0f;
    packet.value70 = D_80096660;
    packet.value74 = D_80096664;
    packet.bytes5C[0] = (func_150ADA20() % 56U) + 200;
    packet.offsets[0] = D_80096668 * scaledX;
    packet.offsets[2] = D_8009666C * scaledX;
    packet.offsets[3] = D_80096674 * scaledY;
    packet.offsets[1] = D_80096670 * scaledY;
    packet.offsets[4] = D_80096678 * scaledY;
    mode = *(s32 *)(arg0 + 0x18) ? 2 : 1;
    func_15149550(packet.position, 10, 1, mode & 0xFF, 0xFF, 1);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15013DE8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15013DE8.s")
void func_151CD2C0(s32 arg0, s32 arg1, s32 arg2);

s32 func_15013F9C(s32 arg0) {
    func_151CD2C0(arg0, 0xFF, 1);
    return 1;
}
s32 func_15013FC4(u8 *arg0) {
    Game40490SimpleCallback callback;
    s32 index;

    index = arg0[0x1B];
    callback = D_80082F40[index];
    if (callback != 0) {
        callback(arg0);
    }
    return 1;
}
extern void *D_800E0900[];

s32 func_15014004(void *arg0) {
    s32 index;

    index = *(s32 *)((u8 *)arg0 + 0x1C);
    if (index < 0) {
        return 1;
    }
    if (index >= 6) {
        return 1;
    }
    D_800E0900[index] = arg0;
    return 1;
}
extern void *D_800D9A20;
extern void *D_800D9A24;

s32 func_15014040(void *arg0) {
    s32 temp_v0;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x18);
    *(u8 *)((u8 *)arg0 + 0x16) = (u8) (*(u8 *)((u8 *)arg0 + 0x16) | 4);
    if (temp_v0 == 0) {
        D_800D9A20 = arg0;
    } else if (temp_v0 == 1) {
        D_800D9A24 = arg0;
    }
    return 1;
}
extern s8 D_800D987C;

s32 func_1501407C(s32 arg0) {
    D_800D987C = 0;
    return 1;
}
extern f32 func_15144598(void *arg0, void *arg1);
extern void func_1510F800(s32 arg0);
extern s32 func_1510FD20(s16 arg0, s16 arg1, void *arg2);
void *func_10022EC0(void *, const void *, u32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15014094 CURRENT (1394) */
void func_15014094(void *arg0) {
    s8 sp60;
    s32 sp40;
    f32 sp3C;
    f32 sp38;
    void *sp34;
    s32 temp_v0;

    *(u8 *)((u8 *)arg0 + 0x16) |= 4;
    sp34 = arg0;
    sp38 = func_15144598(arg0, arg0);
    sp3C = 0.0f;
    func_1510F800(0);
    sp40 = func_1510FD20(*(s16 *)((u8 *)arg0 + 0), *(s16 *)((u8 *)arg0 + 4), arg0);
    sp60 = 0;
    temp_v0 = func_15149130(0x12C, -1, 0x21, -1, 0, 0, 0x34, 0xFF, 1);
    if (temp_v0 != 0) {
        func_10022EC0((void *)(temp_v0 + 0x28), &sp34, 0x34);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15014094 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15014094.s")
s32 func_151A9390(s32, u8, void *, s32, f32, f32, s32, s32, s32);
extern f32 D_8009667C;

s32 func_15014144(void *arg0) {
    s32 flags;
    s32 bit0;
    s32 bit1;
    s32 bit2;
    s32 bit3;
    s32 bit4;

    flags = *(s32 *)((u8 *)arg0 + 0x18);
    bit3 = (flags & 8) ? 8 : 0;
    bit2 = (flags & 4) ? 4 : 0;
    bit1 = (flags & 2) ? 0 : 2;
    bit0 = (flags & 1) ? 1 : 0;
    bit4 = (flags & 0x10) ? 0x10 : 0;
    func_151A9390((bit4 | bit0 | bit1 | bit2 | bit3) & 0xFF,
                  *(u8 *)((u8 *)arg0 + 0x1F), arg0, 0,
                  D_8009667C, 100.0f, -1, 0xFF, 1);
    return 1;
}
typedef struct Game4049014210Packet {
    f32 value;
    void *owner;
    u8 active;
    u8 pad9[3];
} Game4049014210Packet;

s32 func_15014220(void *arg0) {
    Game4049014210Packet packet;
    u8 *temp_v0;

    *(u8 *)((u8 *)arg0 + 0x16) = (u8)(*(u8 *)((u8 *)arg0 + 0x16) | 4);
    packet.active = 1;
    packet.owner = arg0;
    packet.value = 0.0f;
    temp_v0 = func_15149130(0x12C, -1, 0x26, -1, 0, 0x24, 0xC, 0xFF, 0);
    if (temp_v0 != 0) {
        func_10022EC0((void *)(temp_v0 + 0x28), &packet, 0xC);
    }
    return 1;
}
extern void *D_800D9AA0[];

s32 func_150142AC(void *arg0) {
    s32 temp_v1;

    temp_v1 = *(u8 *)((u8 *)arg0 + 0x1B);
    *(u8 *)((u8 *)arg0 + 0x16) |= 4;
    if ((temp_v1 < 0) || (temp_v1 >= 3)) {
        return 1;
    }
    D_800D9AA0[temp_v1] = arg0;
    return 1;
}
typedef struct Game40490ScaledPacket {
    void *owner;
    f32 scaledX;
    f32 scaledY;
    f32 x;
    f32 y;
    f32 zero;
} Game40490ScaledPacket;

f32 func_1514462C(void *);
extern s32 D_80082FA0;
extern f32 D_80096680;
extern f32 D_80096684;

s32 func_150142EC(Game40490CallbackState *arg0) {
    Game40490ScaledPacket packet;
    f32 factor;
    f32 low0;
    f32 high0;
    f32 low1;
    f32 high1;
    u32 first;

    arg0->flags |= 4;
    if (D_80082FA0 >= 2) {
        return 1;
    }
    if ((D_800D2E4C[0x11] & 4) && (D_800BE9F0 == 0x13)) {
        return 1;
    }
    low0 = (f32)(arg0->callback_value & 0xFFFF) * D_80096680;
    high0 = (f32)((arg0->callback_value >> 16) & 0xFFFF) * D_80096680;
    first = *(u32 *)((u8 *)arg0 + 0x20);
    low1 = (f32)(first & 0xFFFF) * D_80096680;
    high1 = (f32)((first >> 16) & 0xFFFF) * D_80096680;
    factor = func_1514462C(arg0);
    packet.owner = arg0;
    packet.scaledX = low0 * factor * D_80096684;
    packet.scaledY = high0 * factor * D_80096684;
    packet.x = low1;
    packet.y = high1;
    packet.zero = 0.0f;
    first = (u32)func_15149130(0x12C, -1, 0x29, -1, 0, 0, 0x18, 0xFF, 0);
    if (first != 0) {
        func_10022EC0((void *)(first + 0x28), &packet, 0x18);
    }
    return 1;
}
typedef struct Game40490144B8Packet {
    void *owner;
    s32 choice;
    s32 low;
    s32 range;
    s16 countX, countY;
    f32 sizeX, sizeY;
    f32 angleX, angleY;
    f32 arc, factor;
    f32 steps, inverse, height;
} Game40490144B8Packet;

f32 func_150484A0(f32, f32);
void func_15145974(void *, f32 *, f32 *);
u32 func_150ADA20(void);
extern f32 D_80096688;
extern f32 D_8009668C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150144B8 CURRENT (207) */
s32 func_150144B8(u8 *arg0) {
    Game40490144B8Packet packet;
    register u32 value;
    struct { f32 direction[3]; f32 matrix[16]; } scratch;

    arg0[0x16] |= 4;
    if (D_80082FA0 >= 2) {
        return 1;
    }
    func_150A8050(scratch.matrix, *(f32 *)(arg0 + 0xC), *(f32 *)(arg0 + 0x10), 0.0f);
    func_150A7960(scratch.matrix, 0.0f, 100.0f, 0.0f, &scratch.direction[0], &scratch.direction[1], &scratch.direction[2]);
    func_15145974(scratch.direction, &packet.angleX, &packet.angleY);
    packet.angleX *= D_80096688;
    packet.angleY *= D_80096688;
    packet.low = *(u32 *)(arg0 + 0x18) & 0xFFU;
    packet.range = (*(u32 *)(arg0 + 0x18) >> 8) & 0xFFU;
    value = func_150ADA20();
    packet.owner = arg0;
    packet.choice = value % (u32)(packet.range + 1) + packet.low;
    packet.countX = (*(u32 *)(arg0 + 0x18) >> 16) & 0xFFU;
    packet.countY = (*(u32 *)(arg0 + 0x18) >> 24) & 0xFFU;
    packet.sizeX = (f32)(*(u32 *)(arg0 + 0x1C) & 0xFFU) * 0.015625f;
    packet.sizeY = (f32)((*(u32 *)(arg0 + 0x1C) >> 8) & 0xFFU) * 0.015625f;
    packet.steps = (f32)((*(u32 *)(arg0 + 0x1C) >> 24) & 0xFFU);
    packet.inverse = 1.0f / packet.steps;
    packet.height = (f32)*(s16 *)(arg0 + 8) * packet.inverse;
    packet.arc = func_150484A0((f32)*(s16 *)(arg0 + 6), (f32)*(s16 *)(arg0 + 8));
    packet.factor = (f32)((*(u32 *)(arg0 + 0x1C) >> 16) & 0xFFU) * 0.00390625f * D_8009668C;
    value = func_15149130(0x12C, -1, 0x2A, -1, 0, 0, 0x38, 0xFF, 0);
    if (value != 0) {
        func_10022EC0((void *)((u32)value + 0x28U), &packet, 0x38);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150144B8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_150144B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_1501474C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15014B60.s")
typedef struct {
    void *object;
    s32 rangeStart;
    s32 rangeSize;
    s32 value;
    f32 matrix[12];
    f32 position[3];
    u8 pad4C[4];
    s8 enabled;
    s8 type;
    u8 pad52[2];
} Game40490ParticlePacket;

void func_150A8050(f32 *, f32, f32, f32);
u32 func_150ADA20(void);

typedef struct struct260 { u8 bytes[0x24]; } struct260;

typedef struct Game40490Struct134 {
    s16 unk0; s16 unk2; s16 unk4; s16 unk6; u16 unk8; u16 unkA; s32 unkC; s32 unk10; u16 unk14; u8 unk16; u8 unk17; s32 unk18; s32 unk1C; s32 unk20; s32 unk24;
} struct134;

s32 func_15014F6C(struct134 *arg0) {
    typedef struct {
        struct134 *unk0;
        s32 unk4;
        s32 unk8;
        s32 unkC;
        f32 mtx[4][4];
        u8 unk50;
        u8 unk51;
        u8 pad52[2];
    } Pack;
    Pack p;
    struct260 *v0;
    s32 v;

    arg0->unk16 |= 4;
    p.unk51 = arg0->unk20;
    v = 0;
    if (arg0->unk1C & 1) {
        v = 1;
    } else {
        v = 0;
    }
    p.unk50 = v;
    p.unk0 = arg0;
    p.unk4 = arg0->unk18 & 0xFFFF;
    p.unk8 = ((u32) arg0->unk18 >> 16) & 0xFFFF;
    p.unkC = (func_150ADA20() % (u32) (p.unk8 + 1)) + p.unk4;
    func_150A8050(p.mtx, *(f32 *) &arg0->unkC, *(f32 *) &arg0->unk10, 0.0f);
    p.mtx[3][0] = (f32) arg0->unk0;
    p.mtx[3][1] = (f32) (s16) arg0->unk2;
    p.mtx[3][2] = (f32) arg0->unk4;
    v0 = func_15149130(0x12C, -1, 0x31, -1, 0, 0x2A, 0x54, 0xFF, 0);
    if (v0 != 0) {
        func_10022EC0((u8 *) v0 + 0x28, &p, 0x54);
    }
    return 1;
}
void *func_1515F1B0(void);
void func_1515F25C(void **, void *);

s32 func_150150A4(void) {
    void *temp_v0;

    temp_v0 = func_1515F1B0();
    if (temp_v0 == 0) {
        return 1;
    }
    func_1515F25C(&D_800DCDC4, temp_v0);
    *&D_800DCD90 += *(f32 *)((u8 *)temp_v0 + 8);
    return 1;
}
void *func_10022EC0(void *, const void *, u32);
void func_1510F800(s32);
s32 func_1510FD20(s16, s16, void *);

typedef struct Game40490SpawnPacket {
    void *object;
    s8 value4;
    u8 pad5[3];
    s32 value8;
    s8 valueC;
    u8 padD[3];
    s32 value10;
} Game40490SpawnPacket;

s32 func_15015104(u8 *arg0) {
    Game40490SpawnPacket packet;
    u8 *result;
    s32 present;
    s32 flag1;
    s32 flag2;

    arg0[0x14] = 1;
    packet.object = arg0;
    packet.value4 = *(s32 *)(arg0 + 0x1C);
    func_1510F800(0);
    packet.value8 = func_1510FD20(*(s16 *)arg0, *(s16 *)(arg0 + 4), arg0);
    present = *(s32 *)(arg0 + 0x20);
    if (present != 0) {
        flag1 = 1;
    } else {
        flag1 = 0;
    }
    if (present != 0) {
        flag2 = 2;
    } else {
        flag2 = 0;
    }
    packet.valueC = flag2 | flag1;
    packet.value10 = 0;
    result = func_15149130(0x12C, -1, -1, -1, 0, 0x2C, 0x14, 0xFF,
                           0);
    if (result != 0) {
        func_10022EC0((void *)(result + 0x28), &packet, 0x14);
    }
    return 1;
}
extern f32 D_800966B4;

typedef struct Game40490LargeSpawnPacket {
    void *object;
    f32 zero4;
    s16 minusOne8;
    u8 padA[2];
    f32 coordinates[5];
    f32 constant20;
    u8 pad24[0x14];
    s32 zero38;
    u8 zero3C;
    u8 zero3D;
    u8 pad3E[2];
    s32 zero40;
    s32 value44;
} Game40490LargeSpawnPacket;

s32 func_150151D4(u8 *arg0) {
    Game40490LargeSpawnPacket packet;
    u8 *result;

    arg0[0x16] |= 4;
    arg0[0x14] = 1;
    packet.object = arg0;
    packet.minusOne8 = -1;
    packet.zero4 = 0.0f;
    packet.coordinates[0] = (f32)*(s16 *)(arg0 + 0);
    packet.coordinates[1] = (f32)*(s16 *)(arg0 + 2);
    packet.coordinates[2] = (f32)*(s16 *)(arg0 + 4);
    packet.coordinates[3] = (f32)*(s16 *)(arg0 + 6);
    packet.coordinates[4] = (f32)*(s16 *)(arg0 + 8);
    packet.zero40 = 0;
    packet.zero3D = 0;
    packet.zero3C = 0;
    packet.zero38 = 0;
    packet.constant20 = D_800966B4;
    func_1510F800(0);
    packet.value44 = func_1510FD20(*(s16 *)(arg0 + 0), *(s16 *)(arg0 + 4), arg0);
    result = func_15149130(0x12C, -1, 0x3C, -1, 0, 0x2D, 0x48, 0xFF, 0);
    if (result != 0) {
        func_10022EC0((void *)(result + 0x28), &packet, sizeof(packet));
    }
    return 1;
}
typedef struct {
    u8 pad_0[0x1C];
    s32 field_1C;
} Game40490State;

extern void (*D_80082F70[])(void);

s32 func_15015300(Game40490State *arg0) {
    void (*temp_v1)(void);
    s32 temp_v0;

    temp_v0 = arg0->field_1C;
    if ((temp_v0 < 0) || (temp_v0 >= 2)) {
        return 1;
    }
    temp_v1 = D_80082F70[temp_v0];
    if (temp_v1 != 0) {
        temp_v1();
    }
    return 1;
}
typedef struct Game15354Point { f32 x, y, z; } Game15354Point;
typedef struct Game15354Packet {
    void *owner;
    s16 index;
    f32 elapsed;
    Game15354Point corners[4];
    Game15354Point edges[4];
    s32 region;
    s32 zero;
} Game15354Packet;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15015354 CURRENT (354) */
void func_15015354(void *arg0) {
    Game15354Packet packet;
    Game15354Point origin;
    Game15354Point corners[4];
    f32 matrix[16];
    register u8 index;
    s32 result;

    packet.owner = arg0;
    packet.index = -1;
    packet.elapsed = 0.0f;
    *((u8 *)arg0 + 0x14) = 1;
    origin.x = *(s16 *)arg0;
    origin.y = *(s16 *)((u8 *)arg0 + 2);
    origin.z = *(s16 *)((u8 *)arg0 + 4);
    corners[0].x = *(s16 *)((u8 *)arg0 + 6);
    corners[0].y = 0.0f;
    corners[0].z = *(s16 *)((u8 *)arg0 + 0xA);
    corners[1].x = *(s16 *)((u8 *)arg0 + 6);
    corners[1].y = 0.0f;
    corners[1].z = -*(s16 *)((u8 *)arg0 + 0xA);
    corners[2].x = -*(s16 *)((u8 *)arg0 + 6);
    corners[2].y = 0.0f;
    corners[2].z = -*(s16 *)((u8 *)arg0 + 0xA);
    corners[3].x = -*(s16 *)((u8 *)arg0 + 6);
    corners[3].y = 0.0f;
    corners[3].z = *(s16 *)((u8 *)arg0 + 0xA);
    func_150A8050(matrix, *(f32 *)((u8 *)arg0 + 0xC), *(f32 *)((u8 *)arg0 + 0x10), 0.0f);
    index = 0;
    matrix[12] = origin.x;
    matrix[13] = origin.y;
    matrix[14] = origin.z;
    do {
        func_150A7960(matrix, corners[index].x, corners[index].y, corners[index].z,
                     &packet.corners[index].x, &packet.corners[index].y, &packet.corners[index].z);
        index++;
    } while (index < 4);
    packet.edges[0].x = packet.corners[1].x - packet.corners[0].x;
    packet.edges[0].y = packet.corners[1].y - packet.corners[0].y;
    packet.edges[0].z = packet.corners[1].z - packet.corners[0].z;
    packet.edges[1].x = packet.corners[2].x - packet.corners[1].x;
    packet.edges[1].y = packet.corners[2].y - packet.corners[1].y;
    packet.edges[1].z = packet.corners[2].z - packet.corners[1].z;
    packet.edges[2].x = packet.corners[3].x - packet.corners[2].x;
    packet.edges[2].y = packet.corners[3].y - packet.corners[2].y;
    packet.edges[2].z = packet.corners[3].z - packet.corners[2].z;
    packet.edges[3].x = packet.corners[0].x - packet.corners[3].x;
    packet.edges[3].y = packet.corners[0].y - packet.corners[3].y;
    packet.edges[3].z = packet.corners[0].z - packet.corners[3].z;
    func_1510F800(0);
    packet.region = func_1510FD20(*(s16 *)arg0, *(s16 *)((u8 *)arg0 + 4), arg0);
    packet.zero = 0;
    result = func_15149130(300, -1, 0x3D, -1, 0, 0x2E, sizeof(packet), 0xFF, 0);
    if (result != 0) {
        func_10022EC0((void *)(result + 0x28), &packet, sizeof(packet));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15015354 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15015354.s")

extern f32 func_15144598(void *arg0, void *arg1);

s32 func_15015644(void *arg0, void *arg1) {
    struct { void *owner; f32 value; s32 index; s8 flag; } packet;
    u8 *temp_v0;

    *(u8 *)((u8 *)arg0 + 0x16) |= 4;
    *(u8 *)((u8 *)arg0 + 0x14) = 1;
    packet.owner = arg0;
    packet.value = func_15144598(arg0, arg1);
    func_1510F800(0);
    packet.index = func_1510FD20(*(s16 *)((u8 *)arg0 + 0), *(s16 *)((u8 *)arg0 + 4), arg0);
    packet.flag = 0;
    temp_v0 = func_15149130(0x12C, -1, 0x44, -1, 0, 0x2F, 0x10, 0xFF, 0);
    if (temp_v0 != 0) {
        func_10022EC0((void *)(temp_v0 + 0x28), &packet, 0x10);
    }
    return 1;
}
typedef struct Game40490Point {
    f32 x, y, z;
} Game40490Point;

typedef struct Game40490BoundsRequest {
    u8 index;
    u8 pad1[3];
    Game40490Point upper;
    Game40490Point lower;
    f32 height;
    u8 flag;
    u8 pad21[3];
} Game40490BoundsRequest;

void func_151ACBD4(Game40490BoundsRequest *, s32);
f32 fabsf(f32);
#pragma intrinsic(fabsf)

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150156F4 CURRENT (100) */
s32 func_150156F4(u8 *arg0) {
    Game40490Point points[2];
    f32 matrix[4][4];
    Game40490BoundsRequest request;

    if (D_800BE9F0 == 0xB) {
        if (*(u32 *)(arg0 + 0x18) < 6U) {
            return 1;
        }
    } else if (D_800BE9F0 == 0x2C) {
        if (*(u32 *)(arg0 + 0x18) < 7U) {
            return 1;
        }
    } else if (D_800BE9F0 == 0x26) {
        if (*(u32 *)(arg0 + 0x18) < 2U) {
            return 1;
        }
    }
    func_150A8050(&matrix[0][0], *(f32 *)(arg0 + 0xC), *(f32 *)(arg0 + 0x10), 0.0f);
    matrix[3][0] = (f32)*(s16 *)(arg0 + 0);
    matrix[3][1] = (f32)*(s16 *)(arg0 + 2);
    matrix[3][2] = (f32)*(s16 *)(arg0 + 4);
    func_150A7960(matrix, 0.0f, (f32)*(s16 *)(arg0 + 8), 0.0f,
                  &points[1].x, &points[1].y, &points[1].z);
    points[0].x = (f32)*(s16 *)(arg0 + 0);
    points[0].y = (f32)*(s16 *)(arg0 + 2);
    points[0].z = (f32)*(s16 *)(arg0 + 4);
    request.index = *(u32 *)(arg0 + 0x18);
    request.upper = points[points[0].y < points[1].y];
    request.lower = points[points[1].y < points[0].y];
    request.flag = 0;
    request.height = fabsf(points[1].y - points[0].y);
    func_151ACBD4(&request, 0);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150156F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_150156F4.s")
