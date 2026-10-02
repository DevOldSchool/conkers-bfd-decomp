#include "types.h"

/*
 * Reviewed source unit: src/game/game_1AFC80.c
 * Boundary evidence: docs/evidence/game_raw_scene_setup_emission_controller.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151827D0
 * - func_15182C5C
 * - func_15182FDC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game362B0Sample {
    f32 component0;
    f32 component1;
    f32 component2;
} Game362B0Sample;

typedef struct Game362B0Preset {
    f32 force00;
    f32 damping04;
    f32 scale08;
    u8 unknown0C[0x8];
    s16 initial14;
    u8 unknown16;
    u8 state17;
} Game362B0Preset;

typedef struct Game1AFC80Actor {
    s32 active00;
    u8 unknown04[0x10];
    f32 x14;
    f32 y18;
    f32 z1C;
    u8 unknown20[0x64];
    u16 kind84;
    u8 unknown86[0x2A6];
} Game1AFC80Actor;

extern s8 D_800DDE50;
extern u8 D_800DDE54[];
extern Game362B0Sample *D_800DDE60[];
extern Game362B0Preset D_8008D050[];
extern Game1AFC80Actor D_800CC2D0[];
extern s32 D_800BE9E4;
s32 func_15182FDC(void *, s32, s32);
u32 func_150ADA20(void);
s32 func_10010F88(s32, u16, s32, s32, s32, s32, s32, s32, s32, s32);
f32 fabsf(f32);
#pragma intrinsic(fabsf)

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151827D0 CURRENT (560) */
void func_151827D0(void) {
    s32 contributions[38];
    s32 bank;
    s32 sample;
    s32 actorIndex;
    s32 contribution;
    s32 lastActor;
    s32 moving;
    s32 pass;
    s32 left;
    s32 right;
    s32 sound;
    f32 x;
    f32 y;
    f32 z;
    f32 force;
    f32 damping;
    Game1AFC80Actor *actor;

    for (bank = 0; bank < (u8)D_800DDE50; bank++) {
        lastActor = 0;
        moving = 0;
        force = D_8008D050[D_800DDE54[bank]].force00;
        damping = D_8008D050[D_800DDE54[bank]].damping04;
        for (sample = 1; sample < 39; sample++) {
            contributions[sample - 1] = 0;
            for (actorIndex = 0; actorIndex < 4; actorIndex++) {
                actor = &D_800CC2D0[actorIndex];
                if (actor->active00 != 0) {
                    contribution = func_15182FDC(actor, sample, bank);
                    if (actor->kind84 == 75) {
                        contribution *= 2;
                    }
                    contributions[sample - 1] += contribution;
                    if (contribution != 0) {
                        lastActor = actorIndex + 1;
                    }
                }
            }
        }
        for (pass = 0; pass < 3; pass++) {
            for (sample = 1; sample < 39; sample++) {
                left = (s32)(D_800DDE60[bank][sample - 1].component2 -
                             D_800DDE60[bank][sample].component2);
                right = (s32)(D_800DDE60[bank][sample + 1].component2 -
                              D_800DDE60[bank][sample].component2);
                D_800DDE60[bank][sample].component0 = (f32)(left + right) + force;
                D_800DDE60[bank][sample].component0 += (f32)contributions[sample - 1];
                D_800DDE60[bank][sample].component1 += D_800DDE60[bank][sample].component0;
                D_800DDE60[bank][sample].component1 *= damping;
                if (fabsf(D_800DDE60[bank][sample].component1) < 1.0f) {
                    D_800DDE60[bank][sample].component1 = 0.0f;
                }
            }
            for (sample = 1; sample < 39; sample++) {
                D_800DDE60[bank][sample].component2 += D_800DDE60[bank][sample].component1;
                if (lastActor != 0 && D_800DDE60[bank][sample].component1 < -30.0f) {
                    moving = 1;
                }
            }
            if (lastActor == 0) {
                D_8008D050[D_800DDE54[bank]].state17 = 0;
            }
            if (moving != 0 && D_8008D050[D_800DDE54[bank]].state17 == 0) {
                actor = &D_800CC2D0[lastActor];
                D_8008D050[D_800DDE54[bank]].state17 = (func_150ADA20() & 0x3F) + 180;
                if (D_800DDE54[bank] == 2 || D_800DDE54[bank] == 3) {
                    sound = (func_150ADA20() & 8) + 0x507;
                    x = actor[-1].x14;
                    y = actor[-1].y18;
                    z = actor[-1].z1C;
                    func_10010F88(sound, 0x5DC0U, 0, 0, 0,
                                  (s32)x, (s32)y, (s32)z, 300, 800);
                } else {
                    x = actor[-1].x14;
                    y = actor[-1].y18;
                    z = actor[-1].z1C;
                    func_10010F88(15, 0x5DC0U, 0, 0, 0,
                                  (s32)x, (s32)y, (s32)z, 300, 800);
                }
            } else if (moving == 0) {
                if (D_8008D050[D_800DDE54[bank]].state17 != 0) {
                    if (D_8008D050[D_800DDE54[bank]].state17 != 0) {
                        D_8008D050[D_800DDE54[bank]].state17 -= D_800BE9E4;
                    }
                }
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151827D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AFC80/func_151827D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AFC80/func_15182C5C.s")
f32 func_15182F58(s32 arg0, s32 arg1) {
    f32 var_fv1;

    var_fv1 = D_8008D050[D_800DDE54[arg1]].scale08 * (f32)(arg0 * 0x28);
    if (var_fv1 < 0.0f) {
        var_fv1 = 0.0f;
    } else if (var_fv1 > 39.0f) {
        var_fv1 = 39.0f;
    }
    return var_fv1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AFC80/func_15182FDC.s")
