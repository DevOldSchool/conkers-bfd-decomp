#include "types.h"

/*
 * Reviewed source unit: src/game/game_F4890.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C73E0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameF4890LightState {
    u8 pad0[0x13];
    u8 state;
    u8 pad14[0x24];
    s32 remaining;
    s32 brightness;
} GameF4890LightState;

void func_151616D0(u8, u8, s32);
void func_10010F30(s32, s32, s32, s32, s32);
u32 func_150ADA20(void);
extern f32 D_800A04B0;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C73E0 CURRENT (1150) */
s32 func_150C73E0(GameF4890LightState *arg0, void *arg1) {
    f32 brightness;
    f32 quarter;
    register s32 remaining;
    u32 random;

    remaining = arg0->remaining;
    brightness = (f32)arg0->brightness / 255.0f;
    if (remaining == 0) {
        arg0->state = 0xC;
        if (*(s32 *)((u8 *)arg1 + 0x2E4) != 0) {
            func_151616D0(0x11, 0x41, 0);
            *(s32 *)((u8 *)arg1 + 0x2E4) = 0;
        }
        return 0;
    } else {
        if (remaining < 60) {
            random = func_150ADA20();
            remaining = arg0->remaining;
            brightness = (f32)(random & 1U) * (((f32)remaining / 60.0f) * 0.25f);
        } else if (remaining < 300) {
            brightness = ((f32)(remaining - 60) / 240.0f) * 0.75f + 0.25f;
        } else if ((f32)remaining < 330.0f) {
            quarter = 0.25f;
            if (1.0f - quarter < brightness) {
                brightness = 0.25f;
            } else {
                brightness = brightness + quarter;
            }
        } else {
            brightness = brightness + (1.0f - brightness) * D_800A04B0;
        }
        if (D_800BE9E4 >= remaining) {
            arg0->remaining = 0;
        } else {
            arg0->remaining = (s32)((u32)remaining - (u32)D_800BE9E4);
        }
        arg0->brightness = (s32)(brightness * 255.0f);
        if (brightness != 0.0f) {
            if (arg0->state != 2) {
                func_10010F30((func_150ADA20() & 7U) + 0x44B, 0x7D00, 0x40, 0, 0);
            }
            arg0->state = 2;
            if (*(s32 *)((u8 *)arg1 + 0x2E4) != 1) {
                func_151616D0(0x11, 0x40, 0);
                *(s32 *)((u8 *)arg1 + 0x2E4) = 1;
            }
        } else {
            arg0->state = 0xC;
            if (*(s32 *)((u8 *)arg1 + 0x2E4) != 0) {
                func_151616D0(0x11, 0x41, 0);
                *(s32 *)((u8 *)arg1 + 0x2E4) = 0;
            }
        }
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C73E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F4890/func_150C73E0.s")
