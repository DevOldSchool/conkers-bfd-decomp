#include "types.h"

/*
 * Reviewed source unit: src/game/game_117490.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E9FE0
 * - func_150EA11C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);
s32 func_15134DAC(u8 *, s32, void *, s16);
extern f32 D_800A1410;
extern f32 D_800A1414;

typedef struct {
    u8 type;
    u8 pad01[3];
    void *object;
    s8 count;
    u8 pad09[3];
    f32 value0C;
    f32 value10;
    f32 value14;
    f32 value18;
    f32 value1C;
    f32 value20;
    s8 mode;
    u8 pad25;
    s16 size0;
    s16 size1;
    s16 argument;
    u8 pad2C[2];
    s8 flag0;
    s8 flag1;
    s8 flag2;
    u8 pad31[3];
    f32 scale;
    s8 kind;
    s8 end;
} Game117490Descriptor;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E9FE0 CURRENT (283) */
s32 func_150E9FE0(void *arg0, s16 arg1, s32 arg2, s32 arg3) {
    Game117490Descriptor descriptor;
    s32 saved;
    u8 copy[0x10];
    s32 temp_v0;
    s32 var_v1;

    descriptor.type = *((u8 *) arg0 + 0x3B);
    descriptor.value0C = -9.0f;
    descriptor.object = arg0;
    descriptor.count = 8;
    descriptor.value10 = -14.0f;
    descriptor.value1C = -14.0f;
    descriptor.mode = 2;
    descriptor.size0 = 0x3C;
    descriptor.size1 = 0x3C;
    descriptor.argument = arg1;
    descriptor.flag0 = 2;
    descriptor.flag1 = 2;
    descriptor.flag2 = 2;
    descriptor.kind = 3;
    descriptor.end = -1;
    *(s32 *) (copy + 0x0) = 0;
    *(s32 *) (copy + 0x4) = 0x11111;
    descriptor.value14 = 27.0f;
    descriptor.value18 = -21.0f;
    descriptor.value20 = 41.0f;
    descriptor.scale = 0.5f;
    *(f32 *) (copy + 0x8) = D_800A1410;
    *(f32 *) (copy + 0xC) = D_800A1414;
    temp_v0 = func_15134DAC((u8 *) &descriptor, 0x10, arg0, arg1);
    var_v1 = temp_v0;
    if (temp_v0 != 0) {
        saved = temp_v0;
        func_10022EC0((void *) (temp_v0 + 0x80), copy, 0x10U);
        var_v1 = saved;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E9FE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_117490/func_150E9FE0.s")
s32 func_150EA10C(u8 *arg0) {
    *(s32 *)(arg0 + 0x80) = 0;
    return 1;
}
typedef struct { f32 x, y, z; } Game117490Vector;
typedef struct {
    s32 flags, field04;
    s16 kind, life;
    s32 field0C, field10;
    u8 bytes14[9];
    u8 mode;
    s16 size0, size1, field22;
    f32 field24, scale0, scale1;
    Game117490Vector position, rotation, velocity;
    f32 field54;
    s32 flags58;
    u8 pad5C[4];
    s8 modes[4];
    u8 pad64[0xC];
} Game117490Particle;
typedef struct {
    f32 scale;
    u8 modes0[4];
    f32 values0[4];
    u8 modes1[4];
    f32 values1[2];
    u8 pad24[4];
} Game117490Extra;

void *func_151303BC(s32, u8, s32);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
extern f32 D_800A1418, D_800A141C, D_800A1420, D_800A1424;
extern f32 D_800A1428, D_800A142C, D_800A1430, D_800A1434;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EA11C CURRENT (360) */
void func_150EA11C(Game117490Vector *arg0, Game117490Vector *arg1,
                   s32 arg2, s32 arg3, f32 arg4, u8 *arg5) {
    Game117490Particle particle;
    void *result;
    Game117490Extra extra;

    particle.mode = 0x2F;
    particle.kind = 0xC01;
    particle.flags = 0x200005;
    particle.field04 = 0;
    particle.bytes14[6] = 0;
    particle.bytes14[5] = 0;
    particle.bytes14[4] = 0;
    particle.bytes14[3] = 0;
    particle.bytes14[2] = 0;
    particle.bytes14[1] = 0;
    particle.bytes14[0] = 0;
    particle.field10 = 0;
    particle.field0C = 0;
    particle.bytes14[8] = 0xFF;
    particle.field22 = 0;
    particle.field24 = 0.0f;
    particle.flags58 = 0x1207;
    particle.modes[0] = 5;
    particle.modes[1] = 5;
    particle.modes[2] = 4;
    particle.modes[3] = -1;
    particle.rotation.x = 0.0f;
    particle.rotation.y = 0.0f;
    particle.rotation.z = 0.0f;
    particle.size0 = 0x14;
    particle.size1 = 0xC;
    extra.modes0[0] = 0;
    extra.modes0[1] = 0;
    extra.modes1[0] = 0;
    extra.modes1[1] = 0;
    extra.values0[2] = 3.5f;
    extra.values0[3] = D_800A1418;
    particle.velocity.x = *(f32 *)(arg5 + 0x74) * (arg1->x - arg0->x);
    particle.velocity.y = *(f32 *)(arg5 + 0x74) * (arg1->y - arg0->y);
    particle.velocity.z = *(f32 *)(arg5 + 0x74) * (arg1->z - arg0->z);
    particle.position = *arg0;
    particle.position.x += particle.velocity.x * arg4;
    particle.position.y += particle.velocity.y * arg4;
    particle.position.z += particle.velocity.z * arg4;
    if (func_150ADA20() & 1) particle.flags58 |= 0x40;
    if (func_150ADA20() & 1) particle.flags58 |= 0x80;
    particle.life = (func_150ADA20() % 51U) + 0x32;
    particle.bytes14[7] = (func_150ADA20() % 101U) + 0x64;
    extra.scale = particle.scale0 = particle.scale1 = func_150ADA68() * 39.0f + 31.0f;
    extra.modes0[2] = (func_150ADA20() % 5U) + 4;
    extra.modes0[3] = (func_150ADA20() % 5U) + 4;
    extra.values0[0] = (func_150ADA68() * 0.25f + D_800A141C) * extra.scale;
    extra.values0[1] = (func_150ADA68() * 0.25f + D_800A1420) * extra.scale;
    extra.modes1[2] = (func_150ADA20() % 5U) + 4;
    extra.modes1[3] = (func_150ADA20() % 5U) + 4;
    extra.values1[0] = (func_150ADA68() * D_800A1424 + D_800A1428) * extra.scale;
    extra.values1[1] = (func_150ADA68() * D_800A142C + D_800A1430) * extra.scale;
    particle.field54 = (func_150ADA68() * 70.0f + 73.0f) * D_800A1434;
    result = func_151303BC((s32)&particle, 2U, 0x28);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0xA8, &extra, 0x28U);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EA11C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_117490/func_150EA11C.s")
