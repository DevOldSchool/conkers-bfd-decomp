#include "types.h"

/*
 * Reviewed source unit: src/game/game_357F0.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_early_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15008340
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game357F0Region {
    s16 x, y, z;
    s16 radiusX, radiusY, radiusZ;
    u8 pad0C[4];
    f32 angle;
    u8 byte14, flags;
} Game357F0Region;
f32 func_15047C00(f32);
f32 func_15047D60(f32);
u32 func_10024770(void);
u32 func_150ADA20(void);
extern f32 D_80095B10, D_80095B14, D_80095B18, D_80095B1C, D_80095B20;
extern f32 D_80095B24, D_80095B28, D_80095B2C, D_80095B30;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15008340 CURRENT (870) */
void func_15008340(Game357F0Region *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
    f32 angle2;
    f32 sine2;
    f32 cosine2;
    f32 offsetX;
    f32 offsetZ;
    f32 angle0;
    f32 sine0;
    f32 cosine0;
    f32 distance0;
    f32 angle1;
    f32 sine1;
    f32 cosine1;
    f32 distance1;
    f32 randomValue;
    u32 ticks;
    s32 radius;

    switch (arg0->flags & 3) {
    default:
        *arg1 = (f32) arg0->x;
        *arg2 = (f32) arg0->z;
        *arg3 = (f32) arg0->y + (f32) arg0->radiusY;
        *arg4 = (f32) arg0->y - (f32) arg0->radiusY;
        return;
    case 2:
        angle2 = arg0->angle * D_80095B10;
        sine2 = func_15047D60(angle2);
        cosine2 = func_15047C00(angle2);
        ticks = func_10024770();
        randomValue = (f32) ((func_150ADA20() * ticks) & 0xFFFF);
        radius = arg0->radiusX;
        offsetX = randomValue * D_80095B14 * (2.0f * (f32) radius) + (f32) -radius;
        ticks = func_10024770();
        randomValue = (f32) ((func_150ADA20() * ticks) & 0xFFFF);
        radius = arg0->radiusZ;
        offsetZ = randomValue * D_80095B18 * (2.0f * (f32) radius) + (f32) -radius;
        *arg1 = (f32) arg0->x + (offsetX * cosine2 + offsetZ * sine2);
        *arg2 = (f32) arg0->z + (offsetZ * cosine2 - offsetX * sine2);
        *arg3 = (f32) arg0->y + (f32) arg0->radiusY;
        *arg4 = (f32) arg0->y;
        break;
    case 0:
        ticks = func_10024770();
        randomValue = (f32) ((func_150ADA20() * ticks) & 0xFFFF) * D_80095B1C;
        angle0 = (randomValue + randomValue) * D_80095B20;
        sine0 = func_15047D60(angle0);
        cosine0 = func_15047C00(angle0);
        ticks = func_10024770();
        distance0 = (f32) ((func_150ADA20() * ticks) & 0xFFFF) * D_80095B24 * (f32) arg0->radiusX;
        *arg1 = (f32) arg0->x + distance0 * cosine0;
        *arg2 = (f32) arg0->z - distance0 * sine0;
        *arg3 = (f32) arg0->y + (f32) arg0->radiusY;
        *arg4 = (f32) arg0->y;
        break;
    case 1:
        ticks = func_10024770();
        randomValue = (f32) ((func_150ADA20() * ticks) & 0xFFFF) * D_80095B28;
        angle1 = (randomValue + randomValue) * D_80095B2C;
        sine1 = func_15047D60(angle1);
        cosine1 = func_15047C00(angle1);
        ticks = func_10024770();
        distance1 = (f32) ((func_150ADA20() * ticks) & 0xFFFF) * D_80095B30 * (f32) arg0->radiusX;
        *arg1 = (f32) arg0->x + distance1 * cosine1;
        *arg2 = (f32) arg0->z - distance1 * sine1;
        *arg3 = (f32) arg0->y + (f32) arg0->radiusX;
        *arg4 = (f32) arg0->y - (f32) arg0->radiusX;
        return;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15008340 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_357F0/func_15008340.s")
