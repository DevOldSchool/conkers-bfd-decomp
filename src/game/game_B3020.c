#include "types.h"

/*
 * Reviewed source unit: src/game/game_B3020.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_call_connected_beta_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15085BE8
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
extern f32 D_8009D9C0;
extern f32 D_8009D9C4;
extern f32 D_8009D9C8;
extern u8 D_800D2358;
extern f32 D_800D2360;
extern u8 D_800D237C[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15085BE8 CURRENT (4345) */
s32 func_15085BE8(void) {
    f32 lower[6];
    f32 upper[6];
    f32 *lowerPtr;
    f32 *upperPtr;
    u8 *record;
    u8 *order;
    f32 *split;
    f32 value;
    f32 a;
    f32 b;
    f32 initialLower;
    f32 initialUpper;
    s32 offset;
    s32 i;
    s32 count;
    s32 overlap;

    initialLower = D_8009D9C0;
    initialUpper = D_8009D9C4;
    overlap = 0;
    lowerPtr = lower;
    upperPtr = upper;
    do {
        lowerPtr++;
        upperPtr++;
        upperPtr[-1] = initialUpper;
        lowerPtr[-1] = initialLower;
    } while ((u32)lowerPtr < (u32)upper);
    if (D_80087290 > 0) {
        offset = 0;
        record = D_800D2350;
        do {
            value = (f32)*(s16 *)(record + 2);
            i = record[6];
            offset += 0x10;
            if (value < upper[i]) {
                upper[i] = value;
            }
            if (lower[i] < value) {
                lower[i] = value;
            }
            record += 0x10;
        } while (offset < D_80087290 * 0x10);
    }
    D_800D2358 = 0;
    lowerPtr = lower;
    upperPtr = upper;
    for (i = 0; i < 6; i++, lowerPtr++, upperPtr++) {
        if (*upperPtr <= *lowerPtr) {
            D_800D237C[D_800D2358] = i;
            D_800D2358++;
        }
    }
    order = D_800D237C;
    count = (s32)D_800D2358 - 1;
    i = 0;
    if (count > 0) {
        split = &D_800D2360;
loop_overlap:
            i++;
            a = lower[order[0]];
            b = upper[order[1]];
            order++;
            *split = (b + a) * 0.5f;
            if (b < a) {
                overlap = 1;
            }
            split++;
            if (i < count) {
                goto loop_overlap;
            }
    }
    (&D_800D2360)[i] = D_8009D9C8;
    return overlap;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15085BE8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_15085BE8.s")
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
