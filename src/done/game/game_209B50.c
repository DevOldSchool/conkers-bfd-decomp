#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_209B50.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_loader_transfer_emission_groups.md
 */

typedef struct Game209B50Vector {
    f32 values[3];
} Game209B50Vector;

void func_15103254(s32, s32, f32, void *, s32, s32, s32);
void func_15150178(s16 *, f32 *, s32, u8, s32);
void func_15182670(s32, s32, s32, s32, s32, s32, s32, s32);
f32 func_150ADA68(void);
extern f32 D_800AB518, D_800AB51C, D_800AB520, D_800AB524;

typedef struct Game209B50Secondary {
    s16 field00, field02, field04, field06;
    Game209B50Vector position;
    s16 field14, field16;
    f32 field18, field1C;
    s16 field20, field22;
    f32 field24, field28;
    u8 field2C, field2D;
    u8 pad2E[2];
    f32 field30, field34;
    u8 field38, field39;
    u8 pad3A[2];
    f32 field3C;
    u8 field40;
    u8 pad41[3];
    f32 field44;
} Game209B50Secondary;

void func_151DC6A0(void *arg0, s32 arg1, s32 arg2) {
    func_15103254((s16)((func_150ADA20() % 5U) + 0xC), ((func_150ADA20() % 56U) + 0xC8) & 0xFF,
                  (func_150ADA68() * 600.0f) + D_800AB518, arg0, 0xFF, ((u8 *)&arg1)[3], arg2);
    {
        Game209B50Secondary packet;

        packet.position = *(Game209B50Vector *)arg0;
        packet.field18 = 8.0f;
        packet.field14 = 0xC;
        packet.field1C = 10.0f;
        packet.field16 = 7;
        packet.field00 = 0;
        packet.field02 = 0xFF;
        packet.field04 = -0x40;
        packet.field06 = 0x3C;
        packet.field20 = 0x24;
        packet.field22 = 0x3C;
        packet.field2C = 0xC8;
        packet.field2D = 0x37;
        packet.field38 = 0;
        packet.field39 = 0xC;
        packet.field40 = 1;
        packet.field24 = D_800AB51C;
        packet.field28 = D_800AB520;
        packet.field30 = 280.0f;
        packet.field34 = 390.0f;
        packet.field3C = D_800AB524;
        packet.field44 = 1.0f;
        func_15150178(&packet.field00, packet.position.values, 0, ((u8 *)&arg1)[3], arg2);
    }
    func_151D3F14(arg0, ((u8 *)&arg1)[3], arg2);
    func_15182670(0xFF, 0xFF, 0xFF, ((func_150ADA20() % 51U) + 0x96) & 0xFF,
                  (func_150ADA20() % 5U) + 8, 0, ((u8 *)&arg1)[3], arg2);
}

void func_151DC6A0(void *, s32, s32);
void *func_10022EC0(void *, const void *, u32);

void func_151DC8BC(void *arg0, s16 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5) {
    typedef struct { s32 words[3]; } Copy3;
    struct {
        Copy3 header;
        f32 value;
        u8 byte;
    } packet;
    u8 *temp_v0;

    if (arg2 != 0) {
        func_151DC6A0(arg0, arg4, arg5);
    }
    packet.header = *(Copy3 *)arg0;
    packet.value = 0.0f;
    packet.byte = arg3;
    temp_v0 = func_15149130(arg1, -1, 0x5B, -1, 1, 0, 0x14, (s32)arg4, arg5);
    if (temp_v0 != 0) {
        func_10022EC0((u8 *)temp_v0 + 0x28, &packet, 0x14U);
    }
}
typedef struct Game209B50SpawnPacket {
    u32 field00, field04;
    s16 field08, field0A;
    u32 field0C, field10;
    u8 field14, field15, field16, field17;
    u8 field18, field19, field1A, field1B, field1C, field1D;
    s16 field1E, field20, field22;
    f32 field24, scaleX, scaleY;
    Game209B50Vector position;
    f32 field3C, field40, field44, field48, field4C, field50, speed;
    u32 flags;
    u8 pad5C[4];
    s8 field60, field61, field62, field63, field64, field65;
    u8 pad66[0xA];
} Game209B50SpawnPacket;
typedef struct Game209B50SpawnExtension {
    u8 field0, field1, field2, field3;
    f32 x, y, z;
} Game209B50SpawnExtension;
typedef struct Game209B50SpawnState {
    Game209B50Vector position;
    f32 counter;
    u8 useTable;
} Game209B50SpawnState;
extern f32 D_800AB528, D_800AB52C, D_800AB530, D_800AB534;
extern f32 D_800BE9A4;

void func_151DC97C(u8 *arg0) {
    Game209B50SpawnState *state;
    Game209B50SpawnPacket packet;

    state = (Game209B50SpawnState *)(arg0 + 0x28);
    state->counter += (D_800AB528 + func_150ADA68() * D_800AB52C) * D_800BE9A4;
    if (state->counter > 1.0f) {
        Game209B50SpawnExtension extension;
        extension.z = D_800AB530;
        packet.field1D = 0x6C;
        packet.field08 = 0x5103;
        packet.field00 = 0x200005;
        extension.field0 = 0;
        extension.field1 = 0;
        packet.field04 = 0;
        packet.field0C = 0;
        packet.field10 = 0;
        packet.field1E = 0x28;
        packet.field20 = 6;
        packet.flags = 0x80DE07;
        packet.field60 = 8;
        packet.field61 = 6;
        packet.field62 = 0x16;
        packet.field63 = -1;
        packet.field64 = -1;
        packet.field65 = 0;
        packet.field22 = 0x78;
        packet.field1C = 0xFF;
        packet.field24 = D_800AB534;
        packet.position = state->position;
        packet.field3C = 0.0f;
        packet.field40 = 0.0f;
        packet.field44 = 0.0f;
        packet.field48 = 0.0f;
        packet.field4C = 0.0f;
        packet.field50 = 0.0f;
        if (state->useTable == 0) {
            packet.field14 = 0xEF;
            packet.field15 = 0xE0;
            packet.field16 = 0xCD;
            packet.field17 = 0xFF;
            packet.field18 = 0x30;
            packet.field19 = 0x30;
            packet.field1A = 0x30;
        }
        do {
            void *result;
            extension.field2 = func_150ADA20() % 5U + 4;
            extension.field3 = func_150ADA20() % 5U + 4;
            extension.x = func_150ADA68() * 50.0f;
            extension.y = func_150ADA68() * 50.0f;
            packet.speed = func_150ADA68() * 0.15100001f + 0.19100001f;
            packet.flags &= ~0xC0;
            packet.flags |= (func_150ADA20() & 1 ? 0x40 : 0) | (func_150ADA20() & 1 ? 0x80 : 0);
            packet.field1B = func_150ADA20() % 56U + 0xC8;
            packet.field0A = func_150ADA20() % 36U + 0x6E;
            packet.scaleX = packet.scaleY = func_150ADA68() * 370.0f + 403.0f;
            if (state->useTable != 0) {
                const u8 tableA[3][3] = { { 0xEF, 0xE0, 0xCD }, { 0x9E, 0x9C, 0xA0 }, { 0x9E, 0x9C, 0xA0 } };
                u8 index;
                const u8 tableB[3][3] = { { 0x30, 0x30, 0x30 }, { 0x9A, 0x69, 0xD2 }, { 0xD5, 0x83, 0x91 } };
                index = func_150ADA20() % 3U;
                packet.field14 = tableA[index][0];
                packet.field15 = tableA[index][1];
                packet.field16 = tableA[index][2];
                packet.field17 = 0xFF;
                packet.field18 = tableB[index][0];
                packet.field19 = tableB[index][1];
                packet.field1A = tableB[index][2];
            }
            result = func_15130280(&packet, 0, NULL, 0x10, arg0[0xC], arg0[1]);
            if (result != NULL) {
                func_10022EC0((u8 *)result + 0xA8, &extension, 0x10);
            }
            state->counter -= 1.0f;
        } while (state->counter > 1.0f);
    }
}
