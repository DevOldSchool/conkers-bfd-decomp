#include "types.h"

/*
 * Reviewed source unit: src/game/game_360A0.c
 * Boundary evidence: docs/evidence/game_medium_single_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15008BF0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game360A0Owner {
    s16 x, y, z, radius;
    u8 pad8[4];
    f32 angleC;
    f32 angle10;
    u8 pad14[2];
    u8 flags;
    u8 pad17[4];
    u8 style;
} Game360A0Owner;

typedef struct Game360A0Descriptor {
    s16 angle, field2, field4, field6;
    f32 x, y, z;
    f32 width, field18, depth;
    f32 field20, field24, field28, field2C, field30, field34;
    s16 field38, field3A;
    f32 field3C, field40;
    s16 field44, field46;
    s32 field48, field4C;
} Game360A0Descriptor;

void func_15143874(s16, f32, f32 *, f32 *);
void func_15189900(void *, u8);
extern f32 D_80095B40, D_80095B44, D_80095B48;
extern f32 D_80095B4C, D_80095B50, D_80095B54;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15008BF0 CURRENT (1909) */
s32 func_15008BF0(Game360A0Owner *arg0) {
    Game360A0Descriptor descriptor;
    f32 sine;
    f32 cosine;
    f32 angleScale = D_80095B40;

    arg0->flags |= 4;
    descriptor.field28 = (f32)arg0->radius * D_80095B44 * D_80095B48;
    descriptor.field2C = 0.0f;
    descriptor.field48 = 4;
    descriptor.field4C = 2;
    descriptor.field38 = 100;
    descriptor.field3A = 100;
    descriptor.field44 = 40;
    descriptor.field46 = 20;
    descriptor.field30 = 7.0f;
    descriptor.field34 = 6.0f;
    descriptor.field20 = D_80095B4C;
    descriptor.field24 = 7.5f;
    descriptor.field3C = D_80095B50;
    descriptor.field40 = D_80095B54;
    descriptor.field2 = 20;
    descriptor.angle = (s32)(arg0->angle10 * angleScale);
    descriptor.field6 = 8;
    descriptor.field4 = (s32)(arg0->angleC * angleScale - 64.0f);
    func_15143874((s16)(descriptor.angle - 64), arg0->radius, &cosine, &sine);
    descriptor.x = arg0->x - cosine;
    descriptor.y = arg0->y;
    descriptor.z = arg0->z - sine;
    descriptor.width = 2.0f * cosine;
    descriptor.field18 = 0.0f;
    descriptor.depth = 2.0f * sine;
    func_15189900(&descriptor, arg0->style);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15008BF0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_360A0/func_15008BF0.s")
