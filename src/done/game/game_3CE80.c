#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_3CE80.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_scene_setup_emission_controller.md
 */

typedef struct {
    u8 pad0[0x28];
    s16 field_28;
    s16 field_2A;
    s16 field_2C;
    s16 field_2E;
    s8 field_30;
} Game3CE80Object;

s32 func_150ADA20(void);

void func_1500F9D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Game3CE80Object *temp_v0;

    temp_v0 = func_151491F4((s16)((func_150ADA20() & 0x7F) + 0xA), 1, -1, 1, 0, 0xA, 0xFF, 0);
    if (temp_v0 != 0) {
        temp_v0->field_28 = (s16)arg0;
        temp_v0->field_2A = (s16)arg1;
        temp_v0->field_2C = (s16)arg2;
        temp_v0->field_2E = (s16)arg3;
        temp_v0->field_30 = (s8)arg4;
    }
}
typedef struct {
    f32 x1, y1, z1, x2, y2, z2;
} Game3CE80Bounds;

typedef struct {
    u8 kind, pad1[3];
    Game3CE80Bounds bounds;
    f32 height;
    u8 flags, pad21[3];
} Game3CE80Descriptor;

void *func_151ACBD4(Game3CE80Descriptor *, void *);
extern Game3CE80Bounds D_80096320, D_80096338, D_80096350, D_80096368, D_80096380;
extern u8 D_800DCD20[], D_800DCD28[];
extern u8 D_800DCD3C, D_800DCD3D;
extern f32 D_800DCDA4, D_800DCDA8, D_800DCDAC, D_800DCDB0;
extern f32 D_800DCDB4, D_800DCDB8, D_800DCDBC, D_800DCDC0;
f32 fabsf(f32);
#pragma intrinsic(fabsf)

void func_1500FA64(void) {
    Game3CE80Descriptor descriptor;

    descriptor.flags = 0;
    descriptor.bounds = D_80096320;
    descriptor.kind = 1;
    descriptor.height = fabsf(descriptor.bounds.y1 - descriptor.bounds.y2);
    func_151ACBD4(&descriptor, 0);
    descriptor.bounds = D_80096338;
    descriptor.kind = 2;
    descriptor.height = fabsf(descriptor.bounds.y1 - descriptor.bounds.y2);
    func_151ACBD4(&descriptor, 0);
    descriptor.bounds = D_80096350;
    descriptor.kind = 3;
    descriptor.height = fabsf(descriptor.bounds.y1 - descriptor.bounds.y2);
    func_151ACBD4(&descriptor, 0);
    descriptor.bounds = D_80096368;
    descriptor.kind = 4;
    descriptor.height = fabsf(descriptor.bounds.y1 - descriptor.bounds.y2);
    descriptor.bounds = D_80096380;
    descriptor.kind = 5;
    descriptor.height = fabsf(descriptor.bounds.y1 - descriptor.bounds.y2);
    func_151ACBD4(&descriptor, 0);
    func_1500F9D0(-0x6E7, -0x46A, 0x421, -0x648, 1);
    func_1500F9D0(-0xA71, 0x71B, 0x82B, -0x602, 2);
    func_1500F9D0(-0x870, 0x36E, 0x4E1, -0x602, 2);
    func_1500F9D0(-0xBD5, 0x3F1, 0x659, -0x602, 2);
    func_1500F9D0(-0xE6B, -0x263, -0x427, -0x647, 1);
    D_800DCDA4 = D_800DCD20[0];
    D_800DCDA8 = D_800DCD20[1];
    D_800DCDAC = D_800DCD20[2];
    D_800DCDB0 = D_800DCD28[0];
    D_800DCDB4 = D_800DCD28[1];
    D_800DCDB8 = D_800DCD28[2];
    D_800DCDBC = D_800DCD3C;
    D_800DCDC0 = D_800DCD3D;
}
