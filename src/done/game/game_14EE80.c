#include "types.h"

/*
 * Reviewed source unit: src/game/game_14EE80.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_structural_families_continued.md
 */

typedef struct {
    u8 pad_0[0x14];
    f32 x;
    f32 y;
    f32 z;
    u8 pad_20[0x30C];
} Game14EE80Actor;

typedef struct {
    u8 pad_0[0x2BC];
    f32 target_x;
    f32 target_y;
    f32 target_z;
    u8 pad_2C8[0x30];
    f32 eye_x;
    f32 eye_y;
    f32 eye_z;
} Game14EE80Bounds;

extern s8 D_8008FD8C;
extern Game14EE80Actor D_800CC2D0[];

void func_151219D0(Game14EE80Bounds *arg0) {
    s32 i;
    f32 x;
    f32 z;
    f32 center_z;
    f32 min_z;
    f32 z_extent;
    f32 max_z;
    f32 max_x;
    f32 sum_y;
    f32 x_extent;
    f32 min_x;
    f32 extent;

    min_z = 10000.0f;
    max_z = -10000.0f;
    min_x = 10000.0f;
    max_x = -10000.0f;
    sum_y = 0.0f;
    for (i = 0; i < D_8008FD8C; i++) {
        x = D_800CC2D0[i].x;
        if (x < min_x) {
            min_x = x;
        }
        if (max_x < x) {
            max_x = x;
        }
        z = D_800CC2D0[i].z;
        sum_y += D_800CC2D0[i].y;
        if (z < min_z) {
            min_z = z;
        }
        if (max_z < z) {
            max_z = z;
        }
    }
    center_z = (min_z + max_z) * 0.5f;
    sum_y /= (f32)D_8008FD8C;
    arg0->target_x = max_x;
    arg0->target_y = sum_y + 150.0f;
    arg0->target_z = center_z;
    extent = 0.0f;
    for (i = 0; i < D_8008FD8C; i++) {
        x_extent = (D_800CC2D0[i].x - max_x) * 0.5f;
        if (x_extent < 0.0f) {
            x_extent = 0.0f;
        }
        z_extent = D_800CC2D0[i].z - center_z;
        if (z_extent < 0.0f) {
            z_extent = -z_extent;
        }
        if (z_extent < x_extent) {
            z_extent = x_extent;
        }
        if (extent < z_extent) {
            extent = z_extent;
        }
    }
    if (extent < 300.0f) {
        extent = 300.0;
    }
    extent += 100.0f;
    arg0->eye_x = arg0->target_x + (2.0f * extent);
    arg0->eye_y = arg0->target_y + (extent * 0.5f);
    arg0->eye_z = arg0->target_z;
}
typedef struct {
    u8 pad_0[0x37C];
    f32 field_37C;
    u8 pad_380[0x1C];
    f32 field_39C;
    u8 pad_3A0[0x414];
    f32 field_7B4;
    u8 pad_7B8[0x108];
    u8 field_8C0;
} Game14EE80State;

void func_15049688(void *, f32, void *, f32, f32, f32);
extern f32 D_800A3430;

void func_15121C00(Game14EE80State *arg0, f32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    func_15049688(&arg0->field_37C, arg1, &arg0->field_8C0, arg3,
                  arg4, arg0->field_7B4);
    arg0->field_39C = arg0->field_37C * D_800A3430;
}
void func_15121C64(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
}
