#include "types.h"

/*
 * Reviewed source unit: src/game/game_15ABA0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_parser_actor_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1512D748
 * - func_1512D980
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern u8 D_800DC2C0[];

void func_1512D6F0(void *arg0) {
    void *temp_v0;

    temp_v0 = D_800DC2C0 + (*(u8 *)((u8 *)arg0 + 0x23D) * 0x68);
    *(s32 *)((u8 *)temp_v0 + 0x50) = 5;
    *(f32 *)((u8 *)temp_v0 + 0x54) = 0.0f;
    *(f32 *)((u8 *)temp_v0 + 0x58) = 0.0f;
    *(f32 *)((u8 *)temp_v0 + 0x5C) = 0.0f;
    *(f32 *)((u8 *)temp_v0 + 0x60) = 0.0f;
    *(f32 *)((u8 *)temp_v0 + 0x2C) = 0.0f;
    *(f32 *)((u8 *)temp_v0 + 0x28) = -1.0f;
}
typedef struct Game15ABA0Envelope {
    f32 preset[10];
    f32 elapsed;
    f32 amplitude;
    f32 threshold[4];
    f32 rate[4];
    s32 state;
    f32 output[4];
    s32 mode;
} Game15ABA0Envelope;

extern u8 D_800895D0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1512D748 CURRENT (1835) */
void func_1512D748(void *view, s32 preset_index, s32 mode) {
    Game15ABA0Envelope *envelope;
    u8 *preset;
    f32 rise_duration;
    f32 fall_duration;
    f32 release_duration;
    f32 peak_level;
    f32 sustain_level;
    f32 fall_end;
    f32 sustain_end;

    envelope = (Game15ABA0Envelope *)(D_800DC2C0 +
        (*(u8 *)((u8 *)view + 0x23D) * 0x68));
    if (*(u8 *)((u8 *)*(void **)((u8 *)view + 0x3D4) + 0x120) == 0) {
        preset = D_800895D0 + preset_index * 10;
        envelope->preset[0] = (f32)(u32)preset[0];
        envelope->preset[1] = (f32)(u32)preset[1];
        envelope->preset[2] = (f32)(u32)preset[2];
        envelope->preset[3] = (f32)(u32)preset[3];
        envelope->preset[4] = (f32)(u32)preset[4];
        envelope->preset[5] = (f32)(u32)preset[5];
        envelope->preset[6] = (f32)(u32)preset[6];
        envelope->preset[7] = (f32)(u32)preset[7];
        envelope->preset[8] = (f32)(u32)preset[8];
        envelope->preset[9] = (f32)(u32)preset[9];
        rise_duration = envelope->preset[4];
        fall_duration = envelope->preset[5];
        fall_end = fall_duration + rise_duration;
        sustain_end = envelope->preset[6] + fall_end;
        release_duration = envelope->preset[7];
        peak_level = envelope->preset[8];
        envelope->threshold[1] = fall_end;
        envelope->threshold[2] = sustain_end;
        envelope->threshold[0] = rise_duration;
        envelope->elapsed = 0.0f;
        envelope->amplitude = 0.0f;
        envelope->threshold[3] = release_duration + sustain_end;
        envelope->rate[0] = peak_level / rise_duration;
        sustain_level = envelope->preset[9];
        envelope->rate[2] = 0.0f;
        envelope->rate[1] = (peak_level - sustain_level) / fall_duration;
        envelope->state = 0;
        envelope->mode = mode;
        envelope->rate[3] = sustain_level / release_duration;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1512D748 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15ABA0/func_1512D748.s")
/* Call context: func_15047D60: unique active project prototype */
/* Call context: func_1512D6F0: unique active declaration in the allowed source */
f32 func_15047D60(f32);
s32 func_150ADA20();                                /* extern */
extern f32 D_800A36F0;
extern f32 D_800A36F4;
extern f32 D_800A36F8;
extern f32 D_800A36FC;
extern f32 D_800A3700;
extern f32 D_800A3704;
extern f32 D_800A3708;
extern f32 D_800A370C;
extern u8 D_800BE9A0;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1512D980 CURRENT (2045) */
void func_1512D980(void *arg0) {
    f32 result;
    volatile f32 sp20;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv1_2;
    f32 temp_fv1;
    f32 var_fa1;
    f32 var_ft3;
    void *temp_s0;

    temp_s0 = (*(u8 *)((u8 *)arg0 + 0x23D) * 0x68) + D_800DC2C0;
    if (func_150ADA20() & 1) {
        var_fa1 = 1.0f;
    } else {
        var_fa1 = -1.0f;
    }
    temp_fv1 = *(f32 *)((u8 *)temp_s0 + 0x28);
    if ((-1.0f != temp_fv1) && (*(s32 *)((u8 *)temp_s0 + 0x50) != 5) && !(*(s32 *)((u8 *)arg0 + 0x84) & 0x80000)) {
        sp20 = var_fa1;
        temp_fa0 = temp_fv1 * D_800A36F0;
        temp_fa0 *= *(f32 *)((u8 *)temp_s0 + 0x0);
        temp_fa0 *= 360.0f;
        temp_fa0 *= D_800A36F4;
        result = func_15047D60(temp_fa0);
        var_fa1 = sp20;
        temp_fa0 = var_fa1 * *(f32 *)((u8 *)temp_s0 + 0x2C);
        *(f32 *)((u8 *)temp_s0 + 0x54) = result * temp_fa0;
        temp_fa0 = *(f32 *)((u8 *)temp_s0 + 0x28) * D_800A36F8;
        temp_fa0 *= *(f32 *)((u8 *)temp_s0 + 0x4);
        temp_fa0 *= 360.0f;
        temp_fa0 *= D_800A36FC;
        result = func_15047D60(temp_fa0);
        temp_fa0 = 1.0f * *(f32 *)((u8 *)temp_s0 + 0x2C);
        *(f32 *)((u8 *)temp_s0 + 0x58) = result * temp_fa0;
        temp_fa0 = *(f32 *)((u8 *)temp_s0 + 0x28) * D_800A3700;
        temp_fa0 *= *(f32 *)((u8 *)temp_s0 + 0x8);
        temp_fa0 *= 360.0f;
        temp_fa0 *= D_800A3704;
        result = func_15047D60(temp_fa0);
        temp_fa0 = -1.0f * *(f32 *)((u8 *)temp_s0 + 0x2C);
        *(f32 *)((u8 *)temp_s0 + 0x5C) = result * temp_fa0;
        temp_fa0 = *(f32 *)((u8 *)temp_s0 + 0x28) * D_800A3708;
        temp_fa0 *= *(f32 *)((u8 *)temp_s0 + 0xc);
        temp_fa0 *= 360.0f;
        temp_fa0 *= D_800A370C;
        result = func_15047D60(temp_fa0);
        temp_fa0 = *(f32 *)((u8 *)temp_s0 + 0x2C);
        temp_fa1 = *(f32 *)((u8 *)temp_s0 + 0x3C);
        temp_fv1_2 = *(f32 *)((u8 *)temp_s0 + 0x28);
        *(f32 *)((u8 *)temp_s0 + 0x60) = result * (-1.0f * temp_fa0);
        if ((temp_fv1_2 <= temp_fa1) && (temp_fa0 >= 0.0f)) {
            if (temp_fv1_2 <= *(f32 *)((u8 *)temp_s0 + 0x30)) {
                if ((*(s32 *)((u8 *)temp_s0 + 0x50) == 0) && (*(s32 *)((u8 *)temp_s0 + 0x64) != 0)) {
                    *(s32 *)((u8 *)temp_s0 + 0x50) = 1;
                }
                *(f32 *)((u8 *)temp_s0 + 0x2C) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x2C) + (*(f32 *)((u8 *)temp_s0 + 0x40) * D_800BE9A4));
            } else if (temp_fv1_2 <= *(f32 *)((u8 *)temp_s0 + 0x34)) {
                if ((*(s32 *)((u8 *)temp_s0 + 0x50) == 1) && (*(s32 *)((u8 *)temp_s0 + 0x64) != 0)) {
                    *(s32 *)((u8 *)temp_s0 + 0x50) = 2;
                }
                *(f32 *)((u8 *)temp_s0 + 0x2C) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x2C) - (*(f32 *)((u8 *)temp_s0 + 0x44) * D_800BE9A4));
            } else if (temp_fv1_2 <= *(f32 *)((u8 *)temp_s0 + 0x38)) {
                if ((*(s32 *)((u8 *)temp_s0 + 0x50) == 2) && (*(s32 *)((u8 *)temp_s0 + 0x64) != 0)) {
                    *(s32 *)((u8 *)temp_s0 + 0x50) = 3;
                }
            } else if (temp_fv1_2 < temp_fa1) {
                if ((*(s32 *)((u8 *)temp_s0 + 0x50) == 3) && (*(s32 *)((u8 *)temp_s0 + 0x64) != 0)) {
                    *(s32 *)((u8 *)temp_s0 + 0x50) = 4;
                }
                *(f32 *)((u8 *)temp_s0 + 0x2C) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x2C) - (*(f32 *)((u8 *)temp_s0 + 0x4C) * D_800BE9A4));
            } else {
                func_1512D6F0(arg0);
            }
            var_ft3 = (f32)(u32)D_800BE9A0;
            *(f32 *)((u8 *)temp_s0 + 0x28) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x28) + var_ft3);
            return;
        }
        *(s32 *)((u8 *)temp_s0 + 0x50) = 5;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1512D980 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15ABA0/func_1512D980.s")
