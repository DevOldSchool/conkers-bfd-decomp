#include "types.h"

/*
 * Reviewed source unit: src/game/game_14EE80.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151219D0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
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
extern f32 D_800A3420;
extern f32 D_800A3424;
extern Game14EE80Actor D_800CC2D0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151219D0 CURRENT (4420) */
void func_151219D0(Game14EE80Bounds *arg0) {
    Game14EE80Actor *actor;
    Game14EE80Actor *end;
    s32 count;
    f32 x;
    f32 z;
    f32 center_z;
    f32 y;
    f32 min_z;
    f32 z_extent;
    f32 max_z;
    f32 max_x;
    f32 sum_y;
    f32 x_extent;
    f32 min_x;
    f32 extent;

    min_z = D_800A3420;
    max_z = D_800A3424;
    min_x = D_800A3420;
    max_x = D_800A3424;
    sum_y = 0.0f;
    count = D_8008FD8C;
    if (count > 0) {
        actor = D_800CC2D0;
        end = actor + count;
        do {
            x = actor->x;
            if (x < min_x) {
                min_x = x;
            }
            if (max_x < x) {
                max_x = x;
            }
            z = actor->z;
            y = actor->y;
            actor++;
            sum_y += y;
            if (z < min_z) {
                min_z = z;
            }
            if (max_z < z) {
                max_z = z;
            }
        } while (actor < end);
    }
    arg0->target_x = max_x;
    extent = 0.0f;
    actor = D_800CC2D0;
    center_z = (min_z + max_z) * 0.5f;
    arg0->target_z = center_z;
    sum_y /= (f32) count;
    arg0->target_y = sum_y + 150.0f;
    count = D_8008FD8C;
    if (count > 0) {
        end = actor + count;
        do {
            x_extent = actor->x - max_x;
            x_extent *= 0.5f;
            if (x_extent < 0.0f) {
                x_extent = 0.0f;
            }
            z_extent = actor->z;
            actor++;
            z_extent -= center_z;
            if (z_extent < 0.0f) {
                z_extent = -z_extent;
            }
            if (z_extent < x_extent) {
                z_extent = x_extent;
            }
            if (extent < z_extent) {
                extent = z_extent;
            }
        } while (actor < end);
    }
    if (extent < 300.0f) {
        extent = 300.0f;
    }
    extent += 100.0f;
    arg0->eye_x = arg0->target_x + (2.0f * extent);
    arg0->eye_z = arg0->target_z;
    arg0->eye_y = arg0->target_y + (extent * 0.5f);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151219D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_14EE80/func_151219D0.s")
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
