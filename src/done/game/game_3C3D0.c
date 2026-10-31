#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_3C3D0.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_medium_single_function_units.md
 */

typedef struct Game3C3D0Packet {
    f32 x;
    f32 y;
    f32 height;
    f32 z;
} Game3C3D0Packet;

void *func_10022EC0(void *, const void *, u32);
void func_15195AA8(s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_800902B8;
extern f32 D_80096220;
extern f32 D_80096224;
extern f32 D_80096228;
extern f32 D_8009622C;
extern f32 D_80096230;
extern f32 D_80096234;
extern f32 D_80096238;
extern f32 D_8009623C;
extern f32 D_80096240;
extern f32 D_80096244;
extern s32 D_800B0E00;
extern s32 D_800B0E04;
extern u8 D_800DCD20[];
extern f32 D_800DCD94;
extern f32 D_800DCD98;
extern f32 D_800DCD9C;
extern f32 D_800DCDA0;

void func_1500EF20(void) {
    void *result;
    Game3C3D0Packet packet;

    func_15195AA8(D_800B0E00, D_800902B8, 1, -1, 0, 0, 0, -8);
    func_15195AA8(D_800B0E04, D_800902B8, 1, -1, 0, 1, 0, -8);
    packet.x = D_80096220;
    packet.y = D_80096224;
    packet.z = D_80096228;
    packet.height = 400.0f;
    result = func_151491F4(func_150ADA20() % 51 + 25, 5, -1, 1, 0, 0x10, 0xFF, 0);
    if (result != NULL) {
        func_10022EC0((u8 *)result + 0x28, &packet, sizeof(packet));
    }
    packet.x = D_8009622C;
    packet.y = D_80096230;
    packet.z = D_80096234;
    result = func_151491F4(func_150ADA20() % 51 + 25, 5, -1, 1, 0, 0x10, 0xFF, 0);
    if (result != NULL) {
        func_10022EC0((u8 *)result + 0x28, &packet, sizeof(packet));
    }
    packet.y = D_80096238;
    result = func_151491F4(func_150ADA20() % 51 + 25, 5, -1, 1, 0, 0x10, 0xFF, 0);
    if (result != NULL) {
        func_10022EC0((u8 *)result + 0x28, &packet, sizeof(packet));
    }
    packet.x = D_8009623C;
    packet.y = D_80096240;
    packet.z = D_80096244;
    result = func_151491F4(func_150ADA20() % 51 + 25, 5, -1, 1, 0, 0x10, 0xFF, 0);
    if (result != NULL) {
        func_10022EC0((u8 *)result + 0x28, &packet, sizeof(packet));
    }
    D_800DCD94 = (u32)D_800DCD20[0];
    D_800DCD98 = (u32)D_800DCD20[1];
    D_800DCD9C = (u32)D_800DCD20[2];
    D_800DCDA0 = 0.0f;
}
