#include "types.h"

/*
 * Reviewed source unit: src/game/game_1B8B60.c
 * Boundary evidence: docs/evidence/game_raw_directly_called_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1518B6B0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    f32 field0;
    f32 field4;
    f32 field8;
    f32 fieldC;
    f32 field10;
    f32 field14;
    f32 field18;
    f32 field1C;
    f32 field20;
    f32 field24;
    f32 field28;
    f32 field2C;
    f32 field30;
    f32 field34;
    f32 field38;
    f32 field3C;
    f32 field40;
    f32 field44;
    f32 field48;
    f32 field4C;
    s32 field50;
    s16 field54;
    s16 field56;
    u8 field58;
    u8 pad59[0x3];
    s32 field5C;
    u8 field60;
    u8 field61;
    u8 field62;
    u8 field63;
    u8 field64;
    u8 field65;
    u8 field66;
    u8 field67;
    u8 field68;
    u8 pad69[0x1];
    u8 field6A;
    u8 pad6B[0x1];
    s32 field6C;
    u8 field70;
    u8 pad71[0x1];
    s16 field72;
    s16 field74;
    u8 pad76[0x6];
} ParticleSpawn;

typedef struct {
    f32 x, y, z;
    s16 integer_x, integer_y, integer_z;
    u8 fraction_x, fraction_z, fraction_y, pad15;
    s16 field16, field18, delta_high, delta_low;
    s16 field1E, field20, field22, field24, field26;
    u8 color0[3], color1[3];
    u8 brightness, alpha;
    s8 callback;
    u8 callback_flags;
} RingSpawn;

void *func_15132A4C(void *, s32, s32, s32, u8, s32);
f32 func_151423D8(u8);
void func_151429E0(u8, u8 *, u8 *, u8 *);
void func_1518CA80(RingSpawn *, u8);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
extern f32 D_800A7400, D_800A7404, D_800A7408, D_800A740C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518B6B0 CURRENT (5061) */
void func_1518B6B0(f32 arg0, f32 arg1, f32 arg2, u8 arg3, s32 arg4) {
    ParticleSpawn particle;
    RingSpawn ring;
    f32 temp_fa0;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_fs3;
    f32 temp_fs4;
    f32 temp_fs5;
    f32 temp_fv1;
    u8 temp_s0;
    u8 temp_s1;
    s32 var_s2;

    particle.field56 = 4;
    particle.field1C = 1.0f;
    particle.field20 = 1.0f;
    particle.field24 = 1.0f;
    particle.field50 = 0x29E8;
    particle.field58 = 0;
    particle.field5C = 0;
    particle.field60 = 0xFF;
    particle.field61 = 1;
    particle.field62 = 0;
    particle.field63 = 0;
    particle.field64 = 0;
    particle.field65 = 0;
    particle.field66 = 0;
    particle.field67 = 0;
    particle.field68 = 0;
    particle.field6A = 2;
    particle.field6C = 0;
    particle.field70 = 0;
    particle.field72 = 0x4000;
    particle.field74 = 0;
    particle.field4 = D_800A7400;
    particle.field48 = 0.0f;
    particle.field4C = D_800A7404;
    var_s2 = (func_150ADA20() & 7) + 3;
    if (var_s2 > 0) {
        do {
            temp_fs2 = (func_150ADA68() * D_800A7408) + D_800A740C;
            temp_s0 = func_150ADA20() & 0xFF;
            temp_s1 = (-0x10 - (func_150ADA20() & 0x1F)) & 0xFF;
            temp_fs3 = (func_150ADA68() * 10.0f) + 5.0f;
            temp_fs0 = func_151423D8((temp_s0 - 0x40) & 0xFF);
            temp_fs1 = func_151423D8(temp_s0 & 0xFF);
            temp_fs4 = func_151423D8((temp_s1 - 0x40) & 0xFF);
            temp_fs5 = func_151423D8(temp_s1 & 0xFF);
            temp_fv1 = func_150ADA68() * 20.0f;
            particle.field2C = arg1;
            temp_fa0 = temp_fs3 * temp_fs5;
            particle.field28 = (temp_fv1 * temp_fs0) + arg0;
            particle.field30 = (temp_fv1 * temp_fs1) + arg2;
            particle.field34 = temp_fa0 * temp_fs0;
            particle.field38 = -temp_fs3 * temp_fs4;
            particle.field3C = temp_fa0 * temp_fs1;
            particle.field54 = (func_150ADA20() & 0x1F) + 0x14;
            particle.field0 = temp_fs2;
            particle.field8 = temp_fs2;
            particle.fieldC = temp_fs2;
            particle.field10 = func_150ADA68() * 360.0f;
            particle.field14 = func_150ADA68() * 360.0f;
            particle.field18 = func_150ADA68() * 360.0f;
            particle.field40 = 25.0f - (func_150ADA68() * 50.0f);
            particle.field44 = 25.0f - (func_150ADA68() * 50.0f);
            func_15132A4C(&particle, 3, 0xFF, 0, arg3, arg4);
            var_s2 -= 1;
        } while (var_s2 != 0);
    }
    ring.field16 = 0x1F4;
    ring.field18 = 0x1F4;
    ring.x = arg0;
    ring.y = arg1;
    ring.z = arg2;
    ring.delta_high = (func_150ADA20() & 0xF) + 0x32;
    ring.delta_low = (func_150ADA20() & 0xF) + 0x32;
    ring.field1E = 0;
    ring.field20 = 0;
    ring.field22 = (func_150ADA20() % 201U) + 0x12C;
    ring.field24 = 0;
    ring.field26 = 0x258;
    func_151429E0(1U, &ring.color0[0], &ring.color0[1], &ring.color0[2]);
    func_151429E0(1U, &ring.color1[0], &ring.color1[1], &ring.color1[2]);
    ring.brightness = 0xFF;
    ring.alpha = 0xFF;
    ring.callback = 0xA;
    ring.callback_flags = 0;
    func_1518CA80(&ring, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518B6B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B8B60/func_1518B6B0.s")
