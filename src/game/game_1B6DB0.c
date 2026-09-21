#include "types.h"

/*
 * Reviewed source unit: src/game/game_1B6DB0.c
 * Boundary evidence: docs/evidence/game_raw_loader_transfer_emission_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15189900
 * - func_15189A00
 * - func_15189EBC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    u8 pad0[0x10];
    u8 pad10[8];
    f32 field18;
    f32 field1C;
    f32 field20;
    f32 field24;
    f32 field28;
    f32 field2C;
    u8 pad30[0x30];
    s16 field60;
    u8 pad62[2];
    f32 field64;
    f32 field68;
    s32 field6C;
    s8 field70;
} Game1B6DB0Effect;

void *func_10022EC0(void *, const void *, u32);
Game1B6DB0Effect *func_15167A68(s32, s32, s32, s32, u8, u8);
void func_1510F800(s32);
s32 func_1510FD20(s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15189900 CURRENT (320) */
void func_15189900(void *arg0, u8 arg1) {
    f32 temp_fv0;
    s32 var_v0;
    Game1B6DB0Effect *effect;

    effect = func_15167A68(0x1A, 1, 0x78, 1, 0xFF, 1);
    if (effect != 0) {
        func_10022EC0((u8 *)effect + 0x10, arg0, 0x50);
        func_1510F800(0);
        effect->field6C = func_1510FD20(
            (s32)(effect->field18 + (effect->field24 * 0.5f)),
            (s32)(effect->field20 + (effect->field2C * 0.5f)));
        if (arg1 == 0) {
            var_v0 = 0;
        } else {
            var_v0 = 1;
        }
        temp_fv0 = effect->field28;
        effect->field70 = var_v0;
        effect->field60 = 0;
        effect->field64 = 0.0f;
        if (temp_fv0 < 0.0f) {
            effect->field68 = effect->field1C + temp_fv0;
            return;
        }
        effect->field68 = effect->field1C;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15189900 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B6DB0/func_15189900.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B6DB0/func_15189A00.s")
typedef struct Game1B6DB0RoutePoint {
    f32 x;
    f32 y;
    f32 z;
    u8 padC[8];
} Game1B6DB0RoutePoint;

typedef struct Game1B6DB0Emitter {
    f32 scale;
    u8 pad4[0x17];
    u8 field_1B;
    u8 pad1C[4];
    s8 field_20;
    u8 pad21[0x27];
    f32 height;
} Game1B6DB0Emitter;

typedef struct Game1B6DB0RouteObject {
    u8 pad0;
    u8 field_01;
    u8 pad2[0xA];
    u8 field_0C;
    u8 padD[0x20];
    s8 route_index;
    u8 pad2E[0x66];
    Game1B6DB0RoutePoint *route;
    Game1B6DB0Emitter *emitter;
} Game1B6DB0RouteObject;

u8 func_151D8E20(void);
void func_151DBCBC(s32, f32, u8, s32, f32 *, s32, s32);
f32 func_150ADA68(void);
extern f64 D_800A73A8;
extern f32 D_800A73B0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15189EBC CURRENT (49) */
s32 func_15189EBC(Game1B6DB0RouteObject *arg0) {
    Game1B6DB0RoutePoint *sp40;
    f32 position[3];
    Game1B6DB0RoutePoint *point;
    Game1B6DB0Emitter *emitter;

    point = arg0->route;
    emitter = arg0->emitter;
    if (point[arg0->route_index].y < emitter->height) {
        sp40 = point;
        if ((f64)func_150ADA68() < D_800A73A8) {
            position[0] = point[arg0->route_index].x;
            position[1] = emitter->height;
            position[2] = point[arg0->route_index].z;
            func_151DBCBC(func_151D8E20() & 0xFF, emitter->scale * 6.0f,
                          emitter->field_1B, 0, position, arg0->field_0C,
                          arg0->field_01);
        }
        emitter->field_20 = 4;
        emitter->height = D_800A73B0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15189EBC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B6DB0/func_15189EBC.s")
