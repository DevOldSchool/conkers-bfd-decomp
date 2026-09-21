#include "types.h"

/*
 * Reviewed source unit: src/game/game_40490.c
 * Boundary evidence: docs/evidence/game_early_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15013000
 * - func_150130B4
 * - func_15013778
 * - func_150139AC
 * - func_15013D38
 * - func_15013DE8
 * - func_15014094
 * - func_150142AC
 * - func_150142EC
 * - func_150144B8
 * - func_1501474C
 * - func_15014B60
 * - func_15014F6C
 * - func_150150A4
 * - func_15015354
 * - func_15015644
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
extern void *func_1515D088(u8 *);

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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15013000 CURRENT (780) */
void func_15013000(void) {
    Game40490DispatchCallback callback;
    u32 var_s1;
    s32 var_s0;

    D_800DCDC4 = 0;
    D_800DCD90 = 0.0f;
    var_s1 = 0;
    var_s0 = 0;
    if (D_800D3094 != 0) {
        do {
            callback = D_80082E30[((D_800D3098[var_s0 + 0x15] >> 2) & 0xFF)];
            if (callback != 0) {
                callback(D_800D3098 + var_s0, callback);
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15013D38 CURRENT (3964) */
s32 func_15013D38(Game40490DispatchState *arg0) {
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    s32 temp_v0;
    s32 var_v1;

    arg0->flags |= 4;
    var_v1 = 1;
    sp3C = (f32)arg0->value_x;
    sp40 = (f32)arg0->value_y;
    sp44 = (f32)arg0->value_z;
    temp_v0 = arg0->callback_result;
    if (temp_v0 != 0) {
        var_v1 = temp_v0;
    }
    func_151BE850(&sp3C, arg0->callback_arg, var_v1 & 0xFF, arg0->callback_index, 1, 0xFF, 1);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15013D38 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15013D38.s")
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
extern void func_10022EC0(void *arg0, void *arg1, s32 arg2);
extern s32 func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15014094 CURRENT (1254) */
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
    s32 temp_v0;

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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150142AC CURRENT (245) */
s32 func_150142AC(void *arg0) {
    u8 temp_t6;
    u8 temp_v1;

    temp_t6 = *(u8 *)((u8 *)arg0 + 0x16);
    temp_v1 = *(u8 *)((u8 *)arg0 + 0x1B);
    *(u8 *)((u8 *)arg0 + 0x16) = temp_t6 | 4;
    if (((s8) temp_v1 < 0) || (temp_v1 >= 3)) {
        return 1;
    }
    D_800D9AA0[temp_v1] = arg0;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150142AC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_150142AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_150142EC.s")
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

void func_150A8050(f32 *, s32, s32, s32);
u32 func_150ADA20(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15014F6C CURRENT (800) */
s32 func_15014F6C(u8 *arg0) {
    Game40490ParticlePacket packet;
    s32 result;
    s8 enabled;

    enabled = 0;
    arg0[0x16] |= 4;
    packet.type = *(s32 *)(arg0 + 0x20);
    if (*(s32 *)(arg0 + 0x1C) & 1) {
        enabled = 1;
    }
    packet.enabled = enabled;
    packet.object = arg0;
    packet.rangeStart = *(u32 *)(arg0 + 0x18) & 0xFFFF;
    packet.rangeSize = (*(u32 *)(arg0 + 0x18) >> 16) & 0xFFFF;
    packet.value = (func_150ADA20() % (u32)(packet.rangeSize + 1)) +
                   packet.rangeStart;
    func_150A8050(packet.matrix, *(s32 *)(arg0 + 0xC),
                  *(s32 *)(arg0 + 0x10), 0);
    packet.position[0] = (f32)*(s16 *)(arg0 + 0);
    packet.position[1] = (f32)*(s16 *)(arg0 + 2);
    packet.position[2] = (f32)*(s16 *)(arg0 + 4);
    result = func_15149130(0x12C, -1, 0x31, -1, 0, 0x2A, 0x54,
                           0xFF, 0);
    if (result != 0) {
        func_10022EC0((void *)(result + 0x28), &packet, 0x54);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15014F6C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15014F6C.s")
void *func_1515F1B0(void);
void func_1515F25C(void **, void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150150A4 CURRENT (133) */
s32 func_150150A4(void) {
    void *sp1C;
    void *temp_v0;

    temp_v0 = func_1515F1B0();
    if (temp_v0 == 0) {
        return 1;
    }
    sp1C = temp_v0;
    func_1515F25C(&D_800DCDC4, temp_v0);
    D_800DCD90 += *(f32 *)((u8 *)sp1C + 8);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150150A4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_150150A4.s")
void func_10022EC0(void *, void *, s32);
void func_1510F800(s32);
s32 func_1510FD20(s16, s16, void *);
s32 func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);

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
    s32 result;
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
    s32 result;

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
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15015354.s")
extern f32 func_15144598(void *arg0, void *arg1);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15015644 CURRENT (589) */
s32 func_15015644(void *arg0, void *arg1) {
    s8 sp44;
    s32 sp40;
    f32 sp3C;
    void *sp38;
    s32 temp_v0;

    *(u8 *)((u8 *)arg0 + 0x14) = 1;
    *(u8 *)((u8 *)arg0 + 0x16) |= 4;
    sp38 = arg0;
    sp3C = func_15144598(arg0, arg1);
    func_1510F800(0);
    sp40 = func_1510FD20(*(s16 *)((u8 *)arg0 + 0), *(s16 *)((u8 *)arg0 + 4), arg0);
    sp44 = 0;
    temp_v0 = func_15149130(0x12C, -1, 0x44, -1, 0, 0x2F, 0x10, 0xFF, 0);
    if (temp_v0 != 0) {
        func_10022EC0((void *)(temp_v0 + 0x28), &sp38, 0x10);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15015644 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15015644.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_150156F4.s")
