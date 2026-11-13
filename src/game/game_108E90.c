#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_108E90.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_narrow_effect_record_cores.md
 */

typedef struct Game108E90Packet {
    f32 field00;
    f32 field04;
    f32 field08;
    f32 field0C;
    f32 field10;
    f32 field14;
    f32 field18;
    f32 field1C;
    f32 field20;
    s16 field24;
    s16 field26;
    s16 field28;
    s16 field2A;
    s16 field2C;
    s16 field2E;
    s16 field30;
    s16 field32;
    s16 field34;
    s16 field36;
    s8 field38;
    s8 field39;
    u8 pad3A[2];
    s32 field3C;
    s32 field40;
    s32 field44;
    s32 field48;
    s32 field4C;
    s32 field50;
    u8 field54;
    u8 field55;
} Game108E90Packet;

typedef struct Game108E90Config {
    f32 x;
    f32 y;
    f32 z;
    s16 countBase;
    s16 countRange;
    s16 yawBase;
    s16 yawRange;
    s16 pitchBase;
    s16 pitchRange;
    f32 speedBase;
    f32 speedRange;
    s16 lifeBase;
    s16 lifeRange;
    s16 sizeBase;
    s16 sizeRange;
    s8 mode;
    s8 kind;
    s16 fadeBase;
    s16 fadeRange;
    s16 field2E;
    s16 field30;
    s16 field32;
    s16 field34;
    s16 field36;
    void *data;
    u8 color;
    u8 alpha;
} Game108E90Config;

void func_15152F70(void *, u8);
void func_15153298(Game108E90Config *, u8, s32);
void *func_15196438(void *, s32, u8, s32);
extern u8 D_80090514[];
extern f32 D_800A0C00;
extern f32 D_800A0C04;
extern f32 D_800A0C08;
extern f32 D_800A0C0C;
extern f32 D_800A0C10;
extern f32 D_800A0C14;
extern f32 D_800A0C18;
extern f32 D_800A0C1C;
extern f32 D_800A0C20;

void func_150DB9E0(void *arg0, s32 arg1, u8 arg2) {
    Game108E90Packet packet;
    Game108E90Config config;

    if (arg0 != NULL) {
        switch (arg1) {
        case 0:
            func_15196438(arg0, 1, arg2, 0);
            packet.field00 = D_800A0C00;
            packet.field24 = 8;
            packet.field26 = 8;
            packet.field28 = -0x4B;
            packet.field2C = -0x26;
            packet.field2A = 0x16;
            packet.field2E = 0x23;
            packet.field30 = 3;
            packet.field32 = 2;
            packet.field34 = 0x29;
            packet.field36 = 0;
            packet.field38 = 0xA;
            packet.field39 = 0x28;
            packet.field3C = 1;
            packet.field40 = 0;
            packet.field44 = 0;
            packet.field48 = 0;
            packet.field4C = 0;
            packet.field50 = 0;
            packet.field54 = 0xFF;
            packet.field55 = 0xFF;
            packet.field0C = 3.0f;
            packet.field10 = 3.0f;
            packet.field04 = D_800A0C04;
            packet.field08 = D_800A0C08;
            packet.field1C = 9.0f;
            packet.field20 = 8.0f;
            packet.field14 = D_800A0C0C;
            packet.field18 = 0.0f;
            func_15152F70(&packet, arg2);
            func_151491F4(0x1E, -1, 0, 1, 0, 0, arg2, 0);
            config.countBase = 6;
            config.countRange = 3;
            config.yawBase = -0x4A;
            config.pitchBase = -0x26;
            config.yawRange = 0x15;
            config.pitchRange = 0x23;
            config.x = D_800A0C10;
            config.y = D_800A0C14;
            config.z = D_800A0C18;
            config.speedBase = D_800A0C1C;
            config.speedRange = D_800A0C20;
            config.lifeBase = 0xE;
            config.lifeRange = 0xE;
            config.sizeBase = -0x3D;
            config.sizeRange = 0x1C;
            config.mode = -1;
            config.kind = 0x12;
            config.fadeBase = 6;
            config.fadeRange = 6;
            config.field2E = 0;
            config.field30 = 0xAE;
            config.field32 = 0x73;
            config.field34 = 0x73;
            config.field36 = 0x87;
            config.data = D_80090514;
            config.color = 0xFF;
            config.alpha = 0xFF;
            func_15153298(&config, arg2, 1);
            break;
        case 1:
            func_15196438(arg0, 2, arg2, 0);
            break;
        }
    }
}

extern f32 D_800A0C24;
extern f32 D_800A0C28;
extern f32 D_800A0C2C;
extern f32 D_800A0C30;

void func_150DBC60(void *arg0) {
    Game108E90Packet packet;

    packet.field00 = D_800A0C24;
    packet.field24 = 1;
    packet.field26 = 2;
    packet.field28 = -0x4B;
    packet.field2C = -0x26;
    packet.field2A = 0x16;
    packet.field2E = 0x23;
    packet.field30 = 3;
    packet.field32 = 2;
    packet.field34 = 0x29;
    packet.field36 = 0;
    packet.field0C = 2.0f;
    packet.field10 = 2.0f;
    packet.field38 = 0xA;
    packet.field39 = 0x28;
    packet.field3C = 1;
    packet.field40 = 0;
    packet.field44 = 0;
    packet.field48 = 0;
    packet.field4C = 0;
    packet.field50 = 0;
    packet.field54 = 0xFF;
    packet.field55 = 0xFF;
    packet.field04 = D_800A0C28;
    packet.field08 = D_800A0C2C;
    packet.field1C = 7.0f;
    packet.field20 = 5.0f;
    packet.field14 = D_800A0C30;
    packet.field18 = 0.0f;
    func_15152F70(&packet, *(u8 *)((u8 *)arg0 + 0xC));
}
