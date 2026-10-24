#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_20A290.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_direct_call_singletons.md
 */

void func_15152190(void *, void *, void *, s32, f32, s32, s32, s32);
extern f32 D_800AB550;
extern f32 D_800AB554;

typedef struct {
    s32 field0;
    s32 field4;
    Vec3i position;
    s16 field14;
    s16 field16;
    s16 field18;
    s16 field1A;
    f32 field1C;
    f32 field20;
    f32 field24;
    f32 field28;
    s16 field2C;
    s16 field2E;
    f32 field30;
    f32 field34;
    f32 field38;
} Game20A290Config;

void func_151DCDE0(void *arg0, u8 arg1, s32 arg2) {
    Game20A290Config config;
    f32 temp_fv0 = 0.2f;

    config.field0 = 0xC;
    config.field4 = 5;
    config.position = *(Vec3i *)arg0;
    config.field14 = 0;
    config.field16 = 0xFF;
    config.field18 = -0x40;
    config.field1A = 0x31;
    config.field2C = 0x19;
    config.field2E = 0x14;
    config.field30 = temp_fv0;
    config.field34 = temp_fv0;
    config.field1C = 3.0f;
    config.field20 = 9.0f;
    config.field24 = -0.693f;
    config.field28 = 0.30400002f;
    config.field38 = 25.714f;
    func_15152190(&config, &D_800AB550, &D_800AB554, 1, 26.0f, 0,
                  (s32)arg1, arg2);
}
