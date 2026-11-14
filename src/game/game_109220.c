#include "types.h"

/*
 * Reviewed source unit: src/game/game_109220.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_isolated_selectors_and_calls.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150DC558
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game109220Data {
    f32 field0;
    u8 field4;
    u8 pad5;
    s16 field6;
    f32 field8;
    u8 fieldC;
    u8 padD;
    s16 fieldE;
    f32 field10;
    f32 field14;
    f32 field18;
    f32 field1C;
    f32 field20;
    f32 field24;
    u8 field28;
    u8 field29;
    u8 pad2A[2];
    f32 field2C;
    f32 field30;
    u8 field34;
    u8 pad35;
    s16 field36;
    f32 field38;
    u8 field3C;
    u8 pad3D;
    s16 field3E;
    u8 field40;
    u8 field41;
    u8 field42;
    u8 pad43;
    s32 field44;
    s32 field48;
    s32 field4C;
    s32 field50;
    s32 field54;
    s32 field58;
    s32 field5C;
    u8 field60;
    u8 pad61[3];
    f32 field64;
    f32 field68;
    f32 field6C;
    s16 field70;
    s16 field72;
    f32 field74;
    f32 field78;
    s16 field7C;
    s16 field7E;
    f32 field80;
    s16 field84;
    s16 field86;
    s16 field88;
    u8 pad8A[2];
    f32 field8C;
    void *field90;
    s32 field94;
    s8 field98;
    u8 pad99[3];
    f32 field9C;
    f32 fieldA0;
    f32 fieldA4;
    s16 fieldA8;
    s16 fieldAA;
    f32 fieldAC;
    f32 fieldB0;
    f32 fieldB4;
    f32 fieldB8;
    f32 fieldBC;
    f32 fieldC0;
    s16 fieldC4;
    s16 fieldC6;
    s16 fieldC8;
    u8 fieldCA;
    u8 padCB;
    f32 fieldCC;
    f32 fieldD0;
    f32 fieldD4;
    s16 fieldD8;
    s16 fieldDA;
    f32 fieldDC;
    f32 fieldE0;
    s16 fieldE4;
    s16 fieldE6;
    s16 fieldE8;
    s16 fieldEA;
    s16 fieldEC;
    s16 fieldEE;
    f32 fieldF0;
    void *fieldF4;
    s32 fieldF8;
    s8 fieldFC;
    u8 padFD[3];
    f32 field100;
    f32 field104;
    f32 field108;
    f32 field10C;
    f32 field110;
    u8 pad114[2];
    s16 field116;
    s16 field118;
    u8 pad11A[2];
} Game109220Data;

typedef struct Game109220Spawn {
    struct {
        f32 x;
        f32 y;
        f32 z;
    } position;
    s16 lifetime;
    u16 flags;
    s32 kind;
    u8 pad14;
    u8 type;
    u8 pad16[2];
    u8 unknown18[4];
} Game109220Spawn;

void *func_10022EC0(void *, const void *, u32);
void *func_15147A80(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void *func_15083E90(u8);
extern u8 D_800903C8[];
extern u8 D_80090414[];

void *func_150DBD70(u8 arg0) {
    Game109220Spawn spawn;
    Game109220Data data;
    void *result;

    data.field20 = 0.0f;
    data.field40 = 0;
    spawn.flags = 0;
    data.field34 = 0;
    switch (arg0) {
    case 0:
    case 5:
        switch (arg0) {
        case 0:
            spawn.position.x = 5.0f;
            spawn.position.y = 115.0f;
            spawn.position.z = -1938.0f;
            data.field24 = 40.4f;
            break;
        case 5:
            spawn.position.x = -693.79346f;
            spawn.position.y = 205.64001f;
            spawn.position.z = -1944.8138f;
            data.field24 = 90.0f;
            break;
        }
        data.field10 = spawn.position.x;
        data.field14 = spawn.position.z;
        data.field18 = -1.6f;
        data.field1C = 1.67f;
        data.field2C = 14.0f;
        data.field30 = 4.0f;
        data.field8 = 3.6f;
        data.field6C = 45.19f;
        data.field74 = 40.0f;
        data.field80 = -185.0f;
        data.field8C = 385.0f;
        data.field9C = 0.225f;
        data.fieldAC = 5.95f;
        data.fieldB0 = 5.63f;
        data.fieldB4 = 5.0f;
        data.fieldBC = 1.1f;
        spawn.type = 0x19;
        spawn.lifetime = 0x85;
        data.field118 = 0x78;
        data.field28 = 0xFF;
        data.field29 = 0xFF;
        data.field36 = 0xC;
        data.field3C = 2;
        data.field3E = 2;
        data.fieldC0 = 0.42f;
        data.field6 = 10;
        data.fieldE = 5;
        spawn.flags |= 1;
        data.field41 = 0x18;
        data.field42 = 0x51;
        data.field44 = 8;
        data.field58 = 5;
        data.field60 = 1;
        data.field70 = 0x3F;
        data.field7C = 0x38;
        data.fieldCC = 1.48f;
        data.field7E = -0x80;
        data.field84 = 8;
        data.field86 = 10;
        data.field88 = 0x181;
        data.field98 = -1;
        data.fieldA8 = -0x3F;
        data.fieldAA = 0x2B;
        data.fieldC4 = 0x56;
        data.fieldC6 = 3;
        data.fieldC8 = 3;
        data.field38 = 0.0f;
        data.field4 = 0;
        data.fieldC = 0;
        data.field48 = 0;
        data.field4C = 0;
        data.field50 = 0;
        data.field54 = 0;
        data.field5C = 0;
        data.field64 = 0.0f;
        data.field68 = 0.0f;
        data.field72 = 0;
        data.field90 = D_800903C8;
        data.field94 = 0;
        data.fieldA0 = 0.0f;
        data.fieldCA = 0xC;
        data.fieldD0 = 0.0f;
        data.fieldD8 = -0x3E;
        data.fieldDA = 7;
        data.fieldE4 = 0x38;
        data.fieldE6 = -0x39;
        data.fieldE8 = 0x15;
        data.fieldEA = 7;
        data.fieldEC = 3;
        data.fieldEE = 0x135;
        data.fieldF4 = D_800903C8;
        data.fieldF8 = 0;
        data.fieldFC = -1;
        data.field104 = 0.0f;
        data.field108 = 0.0f;
        data.field0 = 6.0f;
        data.fieldB8 = 6.0f;
        data.field10C = 100.0f;
        data.field110 = 100.0f;
        data.field78 = 25.0f;
        data.fieldA4 = 25.0f;
        data.fieldD4 = 17.19f;
        data.fieldDC = 270.0f;
        data.fieldE0 = 154.0f;
        data.fieldF0 = 173.0f;
        data.field100 = 60.0f;
        break;
    case 1:
    case 2:
    case 3:
    case 4: {
        void *actor = func_15083E90(6);

        if (actor == 0) {
            return 0;
        }
        if (*(u16 *)((u8 *)actor + 0x84) == 6) {
            data.field24 = 498.0f;
        } else {
            data.field24 = -37.0f;
        }
        spawn.position.y = 736.0f;
        switch (arg0) {
        case 1:
            spawn.position.x = 650.0f;
            spawn.position.z = -650.0f;
            break;
        case 2:
            spawn.position.x = -650.0f;
            spawn.position.z = -650.0f;
            break;
        case 3:
            spawn.position.z = 650.0f;
            spawn.position.x = -650.0f;
            break;
        case 4:
            spawn.position.x = 650.0f;
            spawn.position.z = 650.0f;
            break;
        }
        data.field10 = spawn.position.x;
        data.field14 = spawn.position.z;
        data.field18 = -2.0f;
        data.field1C = 1.26f;
        data.field2C = 132.0f;
        data.field30 = 17.6f;
        data.field38 = -9.1f;
        data.field64 = 0.32f;
        data.field6C = 114.9f;
        data.field74 = 1039.0f;
        data.field78 = 769.0f;
        data.field80 = -51.0f;
        data.field9C = 0.31f;
        data.fieldA4 = 139.53f;
        data.fieldAC = 18.8f;
        spawn.type = 0x1E;
        data.fieldB4 = 15.0f;
        spawn.lifetime = 0xA0;
        data.fieldB8 = 12.0f;
        data.fieldBC = 2.75f;
        data.field118 = 0x6E;
        data.field28 = 0xFF;
        data.field29 = 0xFF;
        data.field36 = 0xC;
        data.field3C = 1;
        data.field3E = 3;
        data.field6 = 6;
        data.fieldE = 6;
        spawn.flags |= 1;
        data.fieldC0 = 1.19f;
        data.field41 = 0x19;
        data.field42 = 0x51;
        data.field44 = 8;
        data.field4C = 6;
        data.field60 = 2;
        data.field70 = 0x24;
        data.field72 = 0x1A;
        data.field7C = 0x258;
        data.field7E = -0x48;
        data.field84 = 6;
        data.fieldCC = 0.72f;
        data.field86 = 3;
        data.field88 = 0x514;
        data.field94 = 0xAB;
        data.field98 = 0xC;
        data.fieldA8 = -0x3A;
        data.fieldAA = 0xB;
        data.fieldC4 = 0x46;
        data.fieldC6 = 4;
        data.fieldC8 = 2;
        data.fieldCA = 9;
        data.field4 = 0;
        data.fieldC = 0;
        data.field48 = 0;
        data.field50 = 0;
        data.field54 = 0;
        data.field58 = 0;
        data.field5C = 0;
        data.field68 = 0.0f;
        data.field90 = D_80090414;
        data.fieldA0 = 0.0f;
        data.fieldD0 = 0.0f;
        data.fieldD8 = -0x38;
        data.fieldDA = 0xA;
        data.fieldE4 = 0x258;
        data.fieldE6 = -0xDF;
        data.fieldE8 = 0x40;
        data.fieldEA = 6;
        data.fieldEC = 4;
        data.fieldEE = 0x514;
        data.fieldF4 = D_80090414;
        data.fieldF8 = 0xAB;
        data.fieldFC = 0xC;
        data.field108 = 0.0f;
        data.field0 = 22.0f;
        data.field8 = 22.0f;
        data.field10C = 100.0f;
        data.field110 = 100.0f;
        data.field8C = 500.0f;
        data.fieldF0 = 500.0f;
        data.fieldB0 = 25.0f;
        data.fieldD4 = 131.0f;
        data.fieldDC = 2366.0f;
        data.fieldE0 = 1231.0f;
        data.field100 = 3.0f;
        data.field104 = 0.078f;
    } break;
    default:
        return 0;
    }
    spawn.kind = 5;
    data.field116 = 0x1B8;
    result = func_15147A80(&spawn, (void *)0x120, 0x18, 4, 4, 4, 0, 0, 0, 0xFF, 1);
    if (result != 0) {
        func_10022EC0(*(void **)((u8 *)result + 0x98), &data, sizeof(data));
    }
    return result;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_109220/func_150DC558.s")
