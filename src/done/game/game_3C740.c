#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_3C740.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_scene_setup_emission_controller.md
 */

void *func_1513C5B0(s32, s32, u8, u8, f32, f32, f32, f32, f32, u8, u8, s32, u8, s32);
s32 func_151EF610(void);

typedef struct {
    s32 flags;
    s16 duration;
    u8 type, mode;
    s32 field8, fieldC;
    u8 selector, alpha, red, green, blue, flag15, flag16, flag17;
    s32 field18, field1C;
    u8 field20;
    s16 field22, field24;
} Game3C740Packet;

void *func_1500F290(f32 arg0, f32 arg1, f32 arg2) {
    Game3C740Packet packet;
    s32 rand;

    packet.type = 0x38;
    packet.field8 = 0;
    rand = func_151EF610();
    packet.fieldC = (rand % 4096) + 0x4000;
    packet.flags = 0x20014;
    packet.duration = 1;
    packet.selector = 0xFF;
    packet.alpha = 0xFF;
    packet.red = 0;
    packet.green = 0;
    packet.blue = 0;
    packet.flag15 = 0xFF;
    packet.field18 = 0x30001;
    return func_1513C5B0((s32)&packet, 0, 0, 0, arg0, arg1, arg2, 110.0f, 110.0f, 0, 0, 0, 0xFF, 0);
}
typedef struct {
    u8 pad0[0x28];
    s16 field_28;
    s16 field_2A;
    s16 field_2C;
    s16 field_2E;
    s8 field_30;
} Game3C740Object;


void func_1500F378(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Game3C740Object *temp_v0;

    temp_v0 = func_151491F4((s16)((func_150ADA20() & 0x7F) + 0xA), 1, -1, 1, 0, 0xA, 0xFF, 0);
    if (temp_v0 != 0) {
        temp_v0->field_28 = (s16)arg0;
        temp_v0->field_2A = (s16)arg1;
        temp_v0->field_2C = (s16)arg2;
        temp_v0->field_2E = (s16)arg3;
        temp_v0->field_30 = 1;
    }
}
typedef struct Game3C740Descriptor {
    s16 angle, field2, field4, field6;
    f32 x, y, z;
    f32 width, field18, depth;
    f32 field20, field24, field28, field2C, field30, field34;
    s16 field38, field3A;
    f32 field3C, field40;
    s16 field44, field46;
    s32 field48, field4C;
} Game3C740Descriptor;

f32 func_150484A0(f32, f32);
void func_15189900(void *, u8);

extern s32 D_800D98D0[];

void func_1500F40C(void) {
    func_1500F378(0x1612, -0x553, -0x2DC, -0x69F);
    func_1500F378(0x1633, -0x553, -0x3C2, -0x69F);
    D_800D98D0[0] = func_1500F290(4054.0f, -1692.0f, 0.0f);
    D_800D98D0[1] = func_1500F290(3890.0f, -1692.0f, -78.0f);
    D_800D98D0[2] = func_1500F290(4380.0f, -1692.0f, -664.0f);
    D_800D98D0[3] = func_1500F290(4218.0f, -1692.0f, -740.0f);
    {
        Game3C740Descriptor descriptor;

        descriptor.field28 = 0.0f;
        descriptor.field2C = 0.24000002f;
        descriptor.field30 = 2.0f;
        descriptor.field34 = 6.0f;
        descriptor.field20 = 7.0f;
        descriptor.field24 = 10.0f;
        descriptor.field3C = 0.497f;
        descriptor.field40 = 0.31500003f;
        descriptor.field48 = 3;
        descriptor.field4C = 2;
        descriptor.field2 = 0x12;
        descriptor.field4 = -0x15;
        descriptor.field6 = 0xF;
        descriptor.field38 = 0x9B;
        descriptor.field3A = 0x64;
        descriptor.field44 = 0x29;
        descriptor.field46 = 0x29;
        descriptor.x = 2686.0f;
        descriptor.y = -1667.0f;
        descriptor.z = 2063.0f;
        descriptor.width = 2810.0f - descriptor.x;
        descriptor.field18 = 0;
        descriptor.depth = 1637.0f - descriptor.z;
        descriptor.angle = (s16)(func_150484A0(descriptor.width, descriptor.depth) * 40.743664f) - 64;
        func_15189900(&descriptor, 1);
        descriptor.x = 2810.0f;
        descriptor.y = -1667.0f;
        descriptor.z = 1637.0f;
        descriptor.width = 2667.0f - descriptor.x;
        descriptor.field18 = -1668.0f - descriptor.y;
        descriptor.depth = 1236.0f - descriptor.z;
        descriptor.angle = (s16)(func_150484A0(descriptor.width, descriptor.depth) * 40.743664f) - 64;
        func_15189900(&descriptor, 1);
        descriptor.x = 2667.0f;
        descriptor.y = -1668.0f;
        descriptor.z = 1236.0f;
        descriptor.width = 2220.0f - descriptor.x;
        descriptor.field18 = -1676.0f - descriptor.y;
        descriptor.depth = 1025.0f - descriptor.z;
        descriptor.angle = (s16)(func_150484A0(descriptor.width, descriptor.depth) * 40.743664f) - 64;
        func_15189900(&descriptor, 1);
        descriptor.x = 1894.0f;
        descriptor.y = -1674.0f;
        descriptor.z = 788.0f;
        descriptor.width = 1841.0f - descriptor.x;
        descriptor.field18 = -1677.0f - descriptor.y;
        descriptor.depth = 557.0f - descriptor.z;
        descriptor.angle = (s16)(func_150484A0(descriptor.width, descriptor.depth) * 40.743664f) - 64;
        func_15189900(&descriptor, 1);
        descriptor.x = 1841.0f;
        descriptor.y = -1677.0f;
        descriptor.z = 557.0f;
        descriptor.width = 1594.0f - descriptor.x;
        descriptor.field18 = -1678.0f - descriptor.y;
        descriptor.depth = 455.0f - descriptor.z;
        descriptor.angle = (s16)(func_150484A0(descriptor.width, descriptor.depth) * 40.743664f) - 64;
        func_15189900(&descriptor, 1);
        descriptor.x = 1594.0f;
        descriptor.y = -1678.0f;
        descriptor.z = 455.0f;
        descriptor.width = 1400.0f - descriptor.x;
        descriptor.field18 = 0.0f;
        descriptor.depth = 613.0f - descriptor.z;
        descriptor.angle = (s16)(func_150484A0(descriptor.width, descriptor.depth) * 40.743664f) - 64;
        func_15189900(&descriptor, 1);
        descriptor.x = 1253.0f;
        descriptor.y = -1673.0f;
        descriptor.z = 668.0f;
        descriptor.width = 1075.0f - descriptor.x;
        descriptor.field18 = -1682.0f - descriptor.y;
        descriptor.depth = 572.0f - descriptor.z;
        descriptor.angle = (s16)(func_150484A0(descriptor.width, descriptor.depth) * 40.743664f) - 64;
        func_15189900(&descriptor, 1);
        descriptor.x = 1075.0f;
        descriptor.y = -1682.0f;
        descriptor.z = 572.0f;
        descriptor.width = 872.0f - descriptor.x;
        descriptor.field18 = -1680.0f - descriptor.y;
        descriptor.depth = 687.0f - descriptor.z;
        descriptor.angle = (s16)(func_150484A0(descriptor.width, descriptor.depth) * 40.743664f) - 64;
        func_15189900(&descriptor, 1);
        descriptor.x = 872.0f;
        descriptor.y = -1680.0f;
        descriptor.z = 687.0f;
        descriptor.width = 772.0f - descriptor.x;
        descriptor.field18 = -1676.0f - descriptor.y;
        descriptor.depth = 931.0f - descriptor.z;
        descriptor.angle = (s16)(func_150484A0(descriptor.width, descriptor.depth) * 40.743664f) - 64;
        func_15189900(&descriptor, 1);
    }
}
