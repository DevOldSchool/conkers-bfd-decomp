#include "types.h"

/*
 * Reviewed source unit: src/game/game_362B0.c
 * Boundary evidence: docs/evidence/game_next_compact_units.md
 */

typedef struct Game362B0Sample {
    f32 component0;
    f32 component1;
    f32 component2;
} Game362B0Sample;

typedef struct Game362B0Preset {
    f32 force00;
    f32 damping04;
    f32 scale08;
    u8 unknown0C[0x8];
    s16 initial14;
    u8 unknown16;
    u8 state17;
} Game362B0Preset;

extern s32 func_10003C40(s32, s32, s32, s32);
extern u8 D_800DDE54[];
extern Game362B0Sample *D_800DDE60[];
extern Game362B0Preset D_8008D050[];

extern s8 D_800DDE50;

void func_15008E00(void) {
    D_800DDE50 = 0;
}
void func_15008E10(s32 preset) {
    s32 i;

    D_800DDE54[(u8)D_800DDE50] = preset;
    D_800DDE60[(u8)D_800DDE50] =
        (Game362B0Sample *)func_10003C40(0x1E0, 1, 0, 0);
    for (i = 0; i < 40; i++) {
        D_800DDE60[(u8)D_800DDE50][i].component0 = 0.0f;
        D_800DDE60[(u8)D_800DDE50][i].component2 =
            D_800DDE60[(u8)D_800DDE50][i].component1 =
                D_800DDE60[(u8)D_800DDE50][i].component0;
    }
    D_800DDE60[(u8)D_800DDE50][39].component2 =
        (f32)D_8008D050[preset].initial14;
    D_8008D050[preset].state17 = 0;
    D_800DDE50 = (u8)D_800DDE50 + 1;
}
