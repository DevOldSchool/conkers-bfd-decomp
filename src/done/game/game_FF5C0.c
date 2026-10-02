#include "types.h"

/*
 * Reviewed source unit: src/game/game_FF5C0.c
 * Boundary evidence: docs/evidence/game_raw_periodic_actor_resource_groups.md
 */

typedef struct GameFF5C0Packet {
    s8 field0;
    u8 pad1[3];
    f32 field4;
    f32 field8;
    f32 fieldC;
    f32 field10;
    u8 field14;
    u8 field15;
    u8 pad16[2];
} GameFF5C0Packet;

extern u8 D_800D9900;
void *func_10022EC0(void *, const void *, u32);
void *func_15149130(s16, s8, s8, s8, u8, u8, s32, u8, s32);

void func_150D2110(s16 arg0, f32 arg1, f32 arg2, u8 arg3, u8 arg4,
                   u8 arg5, s32 arg6) {
    GameFF5C0Packet packet;
    void *temp_v0;

    D_800D9900++;
    packet.field8 = arg1;
    packet.fieldC = arg2;
    packet.field10 = arg1 + arg2;
    packet.field0 = 0;
    packet.field4 = 0.0f;
    packet.field14 = arg3;
    packet.field15 = arg4;
    temp_v0 = func_15149130(arg0, -1, 0x2F, 2, 1, 0x26, 0x18, arg5, arg6);
    if (temp_v0 != 0) {
        func_10022EC0((u8 *)temp_v0 + 0x28, &packet, sizeof(packet));
    }
}
extern f32 D_800BE9A4;
void func_1515D4D4(s32, u8, u8, s32);

void func_150D21CC(void *arg0) {
    GameFF5C0Packet *packet;

    packet = (GameFF5C0Packet *)((u8 *)arg0 + 0x28);
    packet->field4 += D_800BE9A4;
    while (packet->field4 > packet->field10) {
        packet->field4 -= packet->field10;
    }
    if (packet->field4 <= packet->field8) {
        packet->field0 = 1;
        func_1515D4D4(0xFF, 0xFF, 0xFF, 0xFF);
    } else {
        packet->field0 = 0;
    }
}
void func_150D22D4(s32 arg0);
void func_15149368(s32 arg0);

void func_150D227C(s32 arg0) {
    func_150D22D4(arg0);
    func_1514933C(arg0);
}
void func_150D22A8(s32 arg0) {
    func_150D22D4(arg0);
    func_15149368(arg0);
}
void func_150D22D4(s32 arg0) {
    D_800D9900--;
}
typedef struct GameFF5C0Params {
    u8 pad0[0x28];
    u8 field_28;
    u8 pad29[0x13];
    u8 field_3C;
    u8 field_3D;
} GameFF5C0Params;

s32 func_1517F08C(s32, s32, s32, s32, s32, s32);

s32 func_150D22F4(s32 arg0, GameFF5C0Params *arg1, s16 arg2) {
    if (arg1->field_28 == 1) {
        arg0 = func_1517F08C(arg0, arg1->field_3C, 0xFF, 0xFF, 0xFF, arg2);
    } else {
        arg0 = func_1517F08C(arg0, arg1->field_3D, 0, 0, 0, arg2);
    }
    return arg0;
}
typedef struct GameFF5C0SpawnParams {
    s32 base_delay;
    s32 random_delay;
    s32 next_delay;
    s16 base_id;
    s16 random_id;
    f32 value0;
    f32 value1;
    u8 field18;
    u8 field19;
} GameFF5C0SpawnParams;

typedef struct GameFF5C0Controller {
    u8 pad0;
    u8 field1;
    u8 pad2[0xA];
    u8 fieldC;
    u8 padD[0x1B];
    GameFF5C0SpawnParams params;
} GameFF5C0Controller;

u32 func_150ADA20(void);
extern s32 D_800BE9E4;

void func_150D2374(GameFF5C0Controller *arg0) {
    s16 temp_a0;
    GameFF5C0SpawnParams *temp_v1;

    arg0->params.next_delay -= D_800BE9E4;
    if (arg0->params.next_delay < 0) {
        temp_v1 = &arg0->params;
        temp_a0 = (func_150ADA20() % (u32)(temp_v1->random_id + 1))
                + temp_v1->base_id;
        func_150D2110(temp_a0, temp_v1->value0, temp_v1->value1,
                       temp_v1->field18, temp_v1->field19, arg0->fieldC,
                       arg0->field1);
        temp_v1->next_delay =
            (func_150ADA20() % (u32)(temp_v1->random_delay + 1))
            + temp_v1->base_delay;
    }
}
