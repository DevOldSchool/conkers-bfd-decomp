#include "types.h"

/*
 * Reviewed source unit: src/game/game_E0F60.c
 * Boundary evidence: docs/evidence/game_raw_selected_particle_resource_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B3C0C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
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
void func_151D3FF4(s32, u8, s32);
u32 func_150ADA20(void);
void func_1514C858(f32, f32, s32, f32, s32, s32, s32, s32, s32,
                   s32, f32, s32, s32);
void func_151D8868(s8 *, s32, s32, s32);
extern f32 D_8009FBC0;
extern s32 D_800BE9E8;
extern s32 D_800DBFF0;

void func_150B3AB0(GameE0F60Entity *arg0, volatile u8 arg1) {
    GameE0F60Position position;
    GameE0F60Packet packet;

    if (arg0 != 0 && arg0->field1D4 != 0) {
        func_1512D748((void *)(D_800DBFF0 + D_800BE9E8 * 0x9A0), 6, 1);
        position.fieldE = (arg0->field7A >> 8) + 0x40;
        func_15143134(&D_8009FBC0, &position.x, arg0->field1D4 + 0x640);
        func_1514C858(position.x, position.y, *(s32 *)&position.z, 10.0f,
                       position.fieldE, 0, 0xFF,
                       (func_150ADA20() % 31U) + 0x28, 8, 0, 0.0f, 0,
                       arg1);
        packet.field0 = 1;
        packet.field2 = (func_150ADA20() & 0xF) + 0xC;
        packet.field4 = (func_150ADA20() & 3) + 5;
        packet.field6 = -1;
        packet.field5 = 1;
        func_151D8868(&packet.field0, 0, arg1, 0);
        func_151D3FF4((s32)&position, arg1, 0);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_E0F60/func_150B3C0C.s")
