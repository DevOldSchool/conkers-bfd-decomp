#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1B81D0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1518AD20
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B81D0/func_1518AD20.s")
s32 func_1518B1AC(void *arg0) {
    if (*(f32 *)((u8 *)arg0 + 0x3C) < *(f32 *)((u8 *)arg0 + 0x170)) {
        return 0;
    }
    return 1;
}
s32 func_1518B1D8(void *arg0) {
    f32 temp_fv0;
    s32 var_v0;
    s32 var_a1;
    s32 var_v1;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x3C) - *(f32 *)((u8 *)arg0 + 0x170);
    if (temp_fv0 < 0.0f) {
        return 0;
    }
    var_v0 = *(s16 *)((u8 *)arg0 + 0x64);
    var_v0 *= 4;
    if (var_v0 >= 0x100) {
        var_v0 = 0xFF;
    }
    var_v1 = (s32) temp_fv0 >> 1;
    if (var_v1 >= 0x100) {
        var_v1 = 0xFF;
    }
    var_a1 = var_v1 < var_v0 ? var_v1 : var_v0;
    if (var_a1 < 0) {
        return 0;
    }
    *(s8 *)((u8 *)arg0 + 0x70) = (s8) var_a1;
    return 1;
}
extern void func_1518B2A8(f32 *arg0, f32 arg1, f32 arg2, s32 arg3, u16 arg4, s32 arg5, u8 arg6);

void func_1518B264(void *arg0, f32 arg1, f32 arg2, s32 arg3, u8 arg4) {
    func_1518B2A8(arg0, arg1, arg2, arg3, 4, 0xFF, (s32) arg4);
}
typedef struct Game1B81D0Particle {
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
} Game1B81D0Particle;

typedef struct Game1B81D0Ground {
    f32 height;
    u8 pad4[0x14];
    s32 field18;
    u8 field1C;
    u8 field1D;
    u8 pad1E[0x2];
    s32 field20;
} Game1B81D0Ground;

f32 func_150ADA68(void);
s32 func_15046C80(f32 *, u16, f32, void *);
void *func_15132A4C(void *, s32, s32, s32, u8, s32);

void func_1518B2A8(f32 *arg0, f32 arg1, f32 arg2, s32 arg3, u16 arg4, s32 arg5, u8 arg6) {
    Game1B81D0Particle particle;
    Game1B81D0Ground ground;
    u16 angle;
    f32 spread;
    s32 count;
    f32 baseX;
    f32 baseY;
    f32 baseZ;
    f32 scale;
    void *spawned;

    if (arg0 != NULL) {
        particle.field56 = arg4;
        ground.field18 = 0;
        ground.field1C = 0;
        ground.field1D = 0;
        ground.field20 = 0;
        particle.field54 = 0x12C;
        particle.field50 = 0x9E8;
        particle.field58 = 0;
        particle.field5C = 0;
        particle.field60 = 0xFF;
        particle.field61 = 1;
        particle.field63 = 0;
        particle.field64 = 0;
        particle.field65 = 0;
        particle.field66 = 0;
        particle.field67 = 0;
        particle.field68 = 0;
        particle.field6A = 2;
        particle.field6C = 0;
        particle.field70 = 0;
        particle.field72 = 1;
        particle.field74 = 0xFF;
        particle.field1C = 1.0f;
        particle.field20 = 1.0f;
        particle.field24 = 1.0f;
        ground.height = 99999.9f;
        particle.field48 = 0.0f;
        particle.field34 = 0.0f;
        particle.field38 = 0.0f;
        particle.field3C = 0.0f;
        particle.field4 = 0.4f;
        particle.field4C = -1.3f;
        for (; arg3 > 0; arg3--) {
            angle = func_150ADA20() & 0xFF;
            spread = func_150ADA68() * arg1;
            particle.field8 = arg2;
            particle.fieldC = arg2;
            particle.field0 = arg2;
            particle.field10 = func_150ADA68() * 360.0f;
            particle.field14 = func_150ADA68() * 360.0f;
            particle.field18 = func_150ADA68() * 360.0f;
            particle.field28 = arg0[0] + func_151423D8(angle) * spread;
            particle.field2C = arg0[1] + arg1 - func_150ADA68() * 2.0f * arg1;
            particle.field30 = arg0[2] - func_151423D8(angle - 0x40) * spread;
            particle.field40 = 25.0f - func_150ADA68() * 50.0f;
            particle.field44 = 25.0f - func_150ADA68() * 50.0f;
            if (func_15046C80(&particle.field28, 0, -10000.0f, &ground) != 0) {
                particle.field62 = 2;
                spawned = func_15132A4C(&particle, 3, 0xFF, 4, arg6, 0);
                if (spawned != NULL) {
                    *(f32 *)((u8 *)spawned + 0x170) = ground.height;
                }
                count = (func_150ADA20() & 3) + 1;
                baseX = particle.field28;
                baseY = arg2 * 16.0f + particle.field2C;
                baseZ = particle.field30;
                for (; count > 0; count--) {
                    angle = func_150ADA20() & 0xFF;
                    spread = func_150ADA68() * arg2 * 16.0f;
                    scale = func_150ADA68() * 0.3f + 0.1f;
                    particle.field0 = particle.field8 = particle.fieldC = scale;
                    particle.field10 = func_150ADA68() * 360.0f;
                    particle.field14 = func_150ADA68() * 360.0f;
                    particle.field18 = func_150ADA68() * 360.0f;
                    particle.field28 = func_151423D8(angle) * spread + baseX;
                    particle.field2C = func_150ADA68() * 25.0f + baseY;
                    particle.field30 = baseZ - func_151423D8(angle - 0x40) * spread;
                    particle.field40 = 25.0f - func_150ADA68() * 50.0f;
                    particle.field44 = 25.0f - func_150ADA68() * 50.0f;
                    particle.field62 = 3;
                    spawned = func_15132A4C(&particle, 3, 0xFF, 4, arg6, 0);
                    if (spawned != NULL) {
                        *(f32 *)((u8 *)spawned + 0x170) = ground.height;
                    }
                }
            }
        }
    }
}
