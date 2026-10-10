#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_E0F60.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_selected_particle_resource_groups.md
 */

typedef struct GameE0F60Entity {
    u8 pad0[0x7A];
    u16 field7A;
    u8 pad7C[0x158];
    s32 field1D4;
} GameE0F60Entity;

typedef struct GameE0F60Position {
    f32 x;
    f32 y;
    f32 z;
    u8 padC[2];
    s16 fieldE;
} GameE0F60Position;

typedef struct GameE0F60Packet {
    s8 field0;
    u8 pad1;
    s16 field2;
    s8 field4;
    s8 field5;
    s8 field6;
} GameE0F60Packet;

void func_1512D748(void *, s32, s32);
void func_15143134(f32 *, f32 *, s32);
u32 func_150ADA20(void);
void func_1514C858(f32, f32, f32, f32, s32, s32, s32, s32, s32,
                   s32, f32, s32, u8);
void func_151D8868(s8 *, s32, u8, s32);
extern f32 D_8009FBC0;
extern s32 D_800BE9E8;
extern s32 D_800DBFF0;

void func_150B3AB0(GameE0F60Entity *arg0, u8 arg1) {
    GameE0F60Position position;
    GameE0F60Packet packet;

    if (arg0 != 0 && arg0->field1D4 != 0) {
        func_1512D748((void *)(D_800DBFF0 + D_800BE9E8 * 0x9A0), 6, 1);
        position.fieldE = (arg0->field7A >> 8) + 0x40;
        func_15143134(&D_8009FBC0, &position.x, arg0->field1D4 + 0x640);
        func_1514C858(position.x, position.y, position.z, 10.0f,
                       position.fieldE, 0, 0xFF,
                       (func_150ADA20() % 31U) + 0x28, 8, 0, 0.0f, 0,
                       arg1);
        packet.field0 = 1;
        packet.field2 = (func_150ADA20() & 0xF) + 0xC;
        packet.field4 = (func_150ADA20() & 3) + 5;
        packet.field6 = -1;
        packet.field5 = 1;
        func_151D8868(&packet.field0, 0, arg1, 0);
        func_151D3FF4(&position.x, arg1, 0);
    }
}
typedef struct GameE0F60Particle {
    f32 position[3];
    f32 velocity[3];
    f32 field18;
    f32 field1C;
    u8 color20[4];
    u8 color24[4];
    u8 flags;
    s16 lifetime;
    s16 sprite;
    f32 field30;
    u8 field34;
    s16 field36;
    s16 field38;
} GameE0F60Particle;

void func_151429E0(u8, u8 *, u8 *, u8 *);
void func_15156190(void *, u8, s32, u8, s32);
void func_15156388(void *, u8, s32);
f32 func_150ADA68(void);
extern f32 D_8009FBCC;
extern f32 D_8009FBD0;
extern f32 D_8009FBD4;
extern f32 D_8009FBD8;
extern f32 D_8009FBDC;
extern f32 D_8009FBE0;

s32 func_150B3C0C(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4,
                  s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                  s32 arg10, s32 arg11, s32 arg12, s32 arg13, u8 arg14) {
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 temp_fv1;
    GameE0F60Particle particle;

    sp6C = func_151423D8((u8)(arg9 - 0x40));
    sp68 = func_151423D8((u8)arg9);
    sp64 = func_151423D8((u8)(arg8 - 0x40));
    temp_fv1 = func_151423D8((u8)arg8);
    temp_fv1 = 10.0f * temp_fv1;
    particle.position[0] = arg2;
    particle.position[1] = arg3;
    particle.position[2] = arg4;
    particle.velocity[0] = temp_fv1 * sp6C;
    particle.velocity[1] = -10.0f * sp64;
    particle.velocity[2] = temp_fv1 * sp68;
    particle.field18 = (func_150ADA68() * D_8009FBCC) + D_8009FBD0;
    particle.field1C = (func_150ADA68() * D_8009FBD4) + D_8009FBD8;
    func_151429E0(8, &particle.color20[0], &particle.color20[1], &particle.color20[2]);
    func_151429E0(8, &particle.color24[0], &particle.color24[1], &particle.color24[2]);
    particle.color20[3] = 0xFF;
    particle.color24[3] = 0xFF;
    particle.flags = 9;
    particle.lifetime = (func_150ADA20() & 0xF) + 0xF;
    temp_fv1 = func_150ADA68();
    particle.sprite = 0x1601;
    particle.field34 = 0xFF;
    particle.field36 = 0xA;
    particle.field38 = 0x19;
    particle.field30 = temp_fv1 * D_8009FBDC + D_8009FBE0;
    func_15156190(&particle, 1, 0, arg14, 1);
    func_15156388(&particle, 1, 0);
    return 1;
}
