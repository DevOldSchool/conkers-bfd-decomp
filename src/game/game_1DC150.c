#include "types.h"

/*
 * Reviewed source unit: src/game/game_1DC150.c
 * Boundary evidence: docs/evidence/game_raw_direct_call_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151AECA0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct { f32 x, y, z; } Game1DC150Vec;
typedef struct {
    f32 height;
    s16 vertices[3][3];
    u8 pad16[2]; s32 owner;
    u8 flags, kind, pad1E[2];
    void *record;
} Game1DC150Hit;
typedef struct {
    Game1DC150Vec position;
    f32 values[6];
    s16 ranges[8];
    u8 flags, pad35[3];
    f32 scale;
    s16 mode, count;
    s32 word40;
} Game1DC150Params;
typedef struct { u8 pad00[0x14]; Game1DC150Vec position; } Game1DC150Actor;
void func_1504715C(void *, void *);
s32 func_15046C80(void *, u16, f32, void *);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_15143874(s16, f32, f32 *, f32 *);
void func_15153F18(s16 *, void *, void *, s32, s32);
void func_151D9B8C(u8, f32, s32, s32, f32 *, s32, s32, s32, s32, s32, s32);
void func_151DAB58(u8, f32, u8, f32 *, s32, u8, s32);
void func_15136698(f32, f32, s32, s32, s32, void *, void *, s32, s32, s32, s32);
extern f32 D_800A9DA8, D_800A9DAC, D_800A9DB0, D_800A9DB4, D_800A9DB8;
extern f32 D_800A9DBC, D_800A9DC0, D_800A9DC4, D_800A9DC8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AECA0 CURRENT (12471) */
void func_151AECA0(Game1DC150Actor *arg0, s32 arg1, s32 arg2) {
    Game1DC150Hit hit;
    Game1DC150Params params;
    s16 angles[4];
    Game1DC150Vec top;
    Game1DC150Vec point;
    Game1DC150Vec center;
    Game1DC150Vec centerTop;
    f32 randomB;
    u32 angle;
    f32 randomA;
    s32 channel;
    s32 count;
    u32 colorA, colorB;

    channel = arg1 & 0xFF;
    if (arg0 == 0) return;
    func_1504715C(&hit, arg0);
    params.position.x = arg0->position.x;
    params.position.y = arg0->position.y;
    params.position.z = arg0->position.z;
    params.values[0] = D_800A9DA8;
    params.ranges[0] = 10;
    angles[1] = 255;
    angles[2] = -63;
    params.ranges[1] = 0;
    angles[0] = 0;
    angles[3] = 45;
    params.ranges[2] = 3;
    params.ranges[3] = 2;
    params.ranges[4] = 40;
    params.ranges[5] = 20;
    params.ranges[6] = 155;
    params.ranges[7] = 100;
    params.mode = 16;
    params.count = 15;
    params.word40 = 0;
    params.flags = 0;
    params.values[1] = D_800A9DAC;
    params.values[2] = D_800A9DB0;
    params.values[3] = D_800A9DB4;
    params.values[4] = 18.0f;
    params.values[5] = D_800A9DB8;
    params.scale = 0.5f;
    func_15153F18(angles, &params, &hit, 255, 1);
    count = (func_150ADA20() % 6U) + 7;
    top.y = arg0->position.y + 100.0f;
    if (count != 0) {
        do {
            angle = func_150ADA20();
            func_15143874((s16) (angle & 255), func_150ADA68() * 59.0f + 90.0f, &point.x, &point.z);
            point.x += arg0->position.x;
            top.x = point.x;
            point.z += arg0->position.z;
            top.z = point.z;
            if (func_15046C80(&top, 0, arg0->position.y - 500.0f, &hit) == 0 || hit.kind == 3) return;
            point.y = hit.height + 10.0f;
            if (func_150ADA20() & 1) {
                randomA = func_150ADA68();
                func_151D9B8C(0, randomA * 4.5f + 15.0f, (u32) (func_150ADA68() * 100.0f + 155.0f) & 255, (s32) hit.vertices, &point.x, 100, 0, 1, 0, channel, arg2);
            } else {
                randomA = func_150ADA68();
                func_151DAB58(0, randomA * D_800A9DBC + D_800A9DC0, (u32) (func_150ADA68() * 100.0f + 155.0f) & 255, &point.x, 1, (u8) channel, arg2);
            }
            count--;
        } while (count != 0);
    }
    center.x = arg0->position.x;
    center.y = arg0->position.y;
    centerTop.x = center.x;
    center.z = arg0->position.z;
    centerTop.y = center.y + 100.0f;
    centerTop.z = center.z;
    if (func_15046C80(&centerTop, 0, center.y - 500.0f, &hit) != 0 && hit.kind != 3) {
        center.y = hit.height + 10.0f;
        randomA = func_150ADA68();
        randomB = func_150ADA68();
        colorA = func_150ADA20();
        colorB = func_150ADA20();
        func_15136698((randomA * 30.0f + 90.0f) * D_800A9DC4, (randomB * 103.0f + 103.0f) * D_800A9DC8, ((colorA % 101U) + 155) & 255, ((colorB % 101U) + 100) & 255, (func_150ADA20() % 56U) + 70, hit.vertices, &center, 0, 1, channel, arg2);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AECA0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DC150/func_151AECA0.s")
