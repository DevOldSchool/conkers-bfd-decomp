#include "types.h"

/*
 * Reviewed source unit: src/game/game_F44D0.c
 * Boundary evidence: docs/evidence/game_raw_selected_particle_resource_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C7020
 * - func_150C71C0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_1516962C(s32, void *, s32);
void func_15134DAC(void *, s32);
u32 func_150ADA20(void);
extern f32 D_800A0490;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C7020 CURRENT (2180) */
void func_150C7020(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct {
        u8 kind;
        u8 pad01[3];
        void *owner;
        s8 mode;
        u8 pad09[3];
        f32 x0;
        f32 y0;
        f32 z0;
        f32 x1;
        f32 y1;
        f32 z1;
        s8 enabled;
        u8 pad25;
        s16 rand0;
        s16 rand1;
        s16 duration;
        u8 pad2c[2];
        s8 flag0;
        s8 flag1;
        s8 flag2;
        u8 pad31[3];
        f32 scale;
        s8 mode2;
        s8 flag3;
    } effect;

    if (arg0 != 0) {
        func_1516962C(0x29, arg0, 0x12);
        effect.mode = 0xD;
        effect.enabled = 0;
        effect.flag0 = -1;
        effect.flag1 = 1;
        effect.flag2 = -1;
        effect.mode2 = 2;
        effect.flag3 = -1;
        effect.owner = arg0;
        effect.kind = arg0[0x3B];
        effect.z0 = 34.0f;
        effect.z1 = 34.0f;
        effect.x0 = 2.0f;
        effect.x1 = -15.0f;
        effect.y0 = 0.0f;
        effect.y1 = 0.0f;
        effect.scale = D_800A0490;
        if ((s16)arg1 != 0) {
            effect.duration = (s16)arg1;
            effect.enabled = 2;
        } else {
            effect.duration = 0x12C;
        }
        effect.rand0 = (func_150ADA20() % 66U) + 0x23;
        effect.rand1 = (func_150ADA20() % 26U) + 0x19;
        func_15134DAC(&effect, 0);
        effect.mode = 0xC;
        effect.z0 = 34.0f;
        effect.z1 = 34.0f;
        effect.x0 = -2.0f;
        effect.y0 = 0.0f;
        effect.y1 = 0.0f;
        effect.x1 = 15.0f;
        effect.rand0 = (func_150ADA20() % 66U) + 0x23;
        effect.rand1 = (func_150ADA20() % 26U) + 0x19;
        func_15134DAC(&effect, 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C7020 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F44D0/func_150C7020.s")
f32 func_150ADA68(void);
void func_151DB5D0(s32, void *, f32 *, f32, f32, f32, f32, s32, s32, s32,
                   s32, s32, s32, s32);
extern f32 D_800A0494;
extern f32 D_800A0498;
extern f32 D_800A049C;
extern f32 D_800A04A0;
extern f32 D_800A04A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C71C0 CURRENT (442) */
void func_150C71C0(f32 *arg0, f32 *arg1, s32 arg2, s32 arg3, s32 arg4,
                    u8 *arg5) {
    f32 vector[3];
    s16 sp52;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 scale = D_800A0494;

    vector[0] = (arg1[0] - arg0[0]) * scale;
    vector[1] = (arg1[1] - arg0[1]) * scale;
    vector[2] = (arg1[2] - arg0[2]) * scale;
    sp52 = (func_150ADA20() % 31U) + 0x2A;
    sp40 = func_150ADA68();
    sp44 = func_150ADA68();
    sp48 = func_150ADA68();
    func_151DB5D0(0, arg0, vector, (sp40 * 70.0f) + 30.0f,
                   (sp44 * D_800A0498) + D_800A049C, 1.0f,
                   (sp48 * D_800A04A0) + D_800A04A4,
                   sp52, (func_150ADA20() % 101U) + 0x9B, sp52,
                   0xFF / sp52, 1, arg5[0xC], arg5[1]);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C71C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F44D0/func_150C71C0.s")
