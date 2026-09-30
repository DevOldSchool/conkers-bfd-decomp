#include "types.h"

/*
 * Reviewed source unit: src/game/game_183640.c
 * Boundary evidence: docs/evidence/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15156190
 * - func_151563B8
 * - func_151564F8
 * - func_151568F8
 * - func_15156B54
 * - func_15156D24
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_183640/func_15156190.s")
void func_15156190(s32 arg0, u8 arg1, s32 arg2, u8 arg3, s32 arg4);

void func_15156388(s32 arg0, u8 arg1, s32 arg2) {
    func_15156190(arg0, arg1, arg2, 0xFF, 0);
}
void func_1516972C(u8 *);
extern f32 D_800BE9A4;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151563B8 CURRENT (30) */
void func_151563B8(u8 *arg0) {
    s32 value;
    s16 product;
    s32 expired;

    expired = 0;
    if (arg0[0x40] & 1) {
        *(s16 *)(arg0 + 0x42) = *(s16 *)(arg0 + 0x42) - D_800BE9E4;
        if (*(s16 *)(arg0 + 0x42) < 0) {
            expired = 1;
        }
    }
    if (expired == 0) {
        *(f32 *)(arg0 + 0x10) += *(f32 *)(arg0 + 0x1C) * D_800BE9A4;
        *(f32 *)(arg0 + 0x14) += *(f32 *)(arg0 + 0x20) * D_800BE9A4;
        *(f32 *)(arg0 + 0x18) += *(f32 *)(arg0 + 0x24) * D_800BE9A4;
        *(f32 *)(arg0 + 0x28) += *(f32 *)(arg0 + 0x34) * D_800BE9A4;
        *(f32 *)(arg0 + 0x2C) += *(f32 *)(arg0 + 0x38) * D_800BE9A4;
        *(f32 *)(arg0 + 0x30) += *(f32 *)(arg0 + 0x3C) * D_800BE9A4;
        if (arg0[0x40] & 8) {
            value = *(s16 *)(arg0 + 0x42);
            if (value < *(s16 *)(arg0 + 0x4E)) {
                product = value * *(s16 *)(arg0 + 0x50);
                if (product < arg0[0x4C]) {
                    arg0[0x4C] = product;
                }
            }
        }
    }
    if (expired != 0) {
        func_1516972C(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151563B8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_183640/func_151563B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_183640/func_151564F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_183640/func_151568F8.s")
s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
u32 func_150ADA20(void);
void func_15156D24(void *, u8);

typedef struct Game183640Point {
    f32 x, y, z;
    s32 value;
} Game183640Point;
extern Game183640Point D_800DCA30[3][10];

typedef struct Game183640Light {
    u8 kind;
    s8 mode;
    s16 lifetime;
    u8 state;
} Game183640Light;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15156B54 CURRENT (2047) */
void func_15156B54(u8 *arg0) {
    u32 row;
    Game183640Light light;
    s32 position[3];
    Game183640Point *point;
    Game183640Point *group;
    u32 index;
    s16 *timers;

    *(s16 *)(arg0 + 0x2C) -= D_800BE9E4;
    if (*(s16 *)(arg0 + 0x2C) < 0) {
        row = func_150ADA20() % 3U;
        index = func_150ADA20() % 10U;
        group = D_800DCA30[row];
        point = &group[index];
        if (point->x != 0.0f && point->y != 0.0f && point->z != 0.0f) {
            point = &group[index];
            func_15156D24(point, arg0[0xC]);
            light.kind = 3;
            light.mode = -1;
            light.lifetime = func_150ADA20() % 11U + 5;
            light.state = 0;
            position[0] = point->x;
            position[1] = point->y;
            position[2] = point->z;
            func_151602C0((u8 *)&light, position, func_150ADA20() % 156U + 0x64,
                         0xFF, 0xFF, 0xFF, 0xFF, 0, 0, arg0[0xC], arg0[1]);
        }
        timers = (s16 *)(arg0 + 0x28);
        timers[2] = func_150ADA20() % (u32)(timers[1] + 1) + timers[0];
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15156B54 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_183640/func_15156B54.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_183640/func_15156D24.s")
void func_15156F94(s32 arg0) {
    func_151D5E30(arg0 + 0x88, arg0);
}
void func_15169804(s32);

void func_15156FB8(s32 arg0) {
    func_15156F94(arg0);
    func_15169804(arg0);
}
void func_15169824(s32 arg0);

void func_15156FE4(s32 arg0) {
    func_15156F94(arg0);
    func_15169824(arg0);
}
