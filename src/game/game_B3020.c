#include "types.h"

/*
 * Reviewed source unit: src/game/game_B3020.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_call_connected_beta_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15086098
 * - func_15086364
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    s16 width;
    s16 height;
    u8 data[1];
} GameB3020Image;

GameB3020Image *func_1502B5C8(s32, s32, s32, void *);
s32 func_15085BE8(void);
extern s16 D_80087290;
extern s16 D_80087294;
extern u8 *D_800D2350;

void func_15085B70(void *arg0) {
    GameB3020Image *image;

    image = func_1502B5C8(0, 2, 0x19, arg0);
    if (image == 0) {
        D_80087290 = 0;
        D_80087294 = 0;
        D_800D2350 = 0;
    } else {
        D_80087290 = image->width;
        D_80087294 = image->height;
        D_800D2350 = image->data;
    }
    func_15085BE8();
}
extern u8 D_800D2358;
extern f32 D_800D2360;
extern u8 D_800D237C[];

s32 func_15085BE8(void) {
    s32 overlap;
    s32 i;
    s32 slot;
    f32 value;
    s32 lo;
    s32 hi;
    f32 minimum[6];
    f32 maximum[6];

    overlap = 0;
    for (i = 0; i < 6; i++) {
        minimum[i] = 10000.0f;
        maximum[i] = -10000.0f;
    }
    for (i = 0; i < D_80087290; i++) {
        value = *(s16 *)(D_800D2350 + i * 16 + 2);
        slot = D_800D2350[i * 16 + 6];
        if (value < minimum[slot]) {
            minimum[slot] = value;
        }
        if (maximum[slot] < value) {
            maximum[slot] = value;
        }
    }
    D_800D2358 = 0;
    for (i = 0; i < 6; i++) {
        if (minimum[i] <= maximum[i]) {
            D_800D237C[D_800D2358] = i;
            D_800D2358++;
        }
    }
    for (i = 0; i < D_800D2358 - 1; i++) {
        lo = D_800D237C[i];
        hi = D_800D237C[i + 1];
        (&D_800D2360)[i] = (maximum[lo] + minimum[hi]) * 0.5f;
        if (minimum[hi] < maximum[lo]) {
            overlap = 1;
        }
    }
    (&D_800D2360)[i] = 100000.0f;
    return overlap;
}
u8 func_15085DA8(f32 arg0) {
    s32 i;

    i = 0;
    while ((&D_800D2360)[i] <= arg0) {
        i++;
    }
    return D_800D237C[i];
}
f32 func_15086D94(f32, f32, f32, f32, f32);         /* extern */
extern s16 D_80087290;
extern u8 D_8008729C;
extern f32 D_8009D9CC;
extern s32 D_800D2354;

f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
typedef struct GameB3020Point {
    s16 x;
    s16 y;
    s16 z;
    u8 group;
    u8 pad7[7];
    u8 room;
    u8 padF;
} GameB3020Point;

s32 func_15085DF8(f32 x, f32 y, f32 z, s8 room, s8 group) {
    GameB3020Point *point;
    f32 best;
    f32 dist;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 checkSight;
    s32 i;
    s32 found;

    checkSight = 0;
    best = D_8009D9CC;
    if (room == 0) {
        checkSight = 1;
    }
    if (D_8008729C != 0xFF) {
        point = (GameB3020Point *)(D_800D2350 + (D_8008729C << 4));
        dx = point->x - x;
        dy = point->y - y;
        dz = point->z - z;
        if (checkSight == 0 || (checkSight != 0 && func_15086D94(x, y, z, dx, dz) < 0.0f)) {
            best = dx * dx + dy * dy + dz * dz + 10.0f;
        }
        D_8008729C = 0xFF;
    }
    found = 0xFF;
    for (i = 0; i < D_80087290; i++) {
        point = (GameB3020Point *)(D_800D2350 + (i << 4));
        if ((group == point->group || group == -1) && (room == point->room || room == -1)) {
            dx = point->x - x;
            dy = point->y - y;
            dz = point->z - z;
            dist = dx * dx + dy * dy + dz * dz;
            if (dist < best && (checkSight == 0 || (checkSight != 0 && func_15086D94(x, y, z, dx, dz) < 0.0f))) {
                best = dist;
                found = i;
            }
        }
    }
    D_800D2354 = sqrtf(best);
    return found;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_15086098.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_15086364.s")
