#include "types.h"

/*
 * Reviewed source unit: src/game/game_1A6360.c
 * Boundary evidence: docs/evidence/game_raw_animated_emission_controllers.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15178EFC
 * - func_15179008
 * - func_151794C8
 * - func_15179600
 * - func_151797B0
 * - func_15179AB8
 * - func_15179B14
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern u8 D_800DD432;
extern s8 D_800DD433;
extern s8 D_800DD434;
extern s16 D_800DD436;
extern s32 D_800DD440;
extern s16 D_800DD444;
extern s8 D_800DD446;

void func_15178EB0(void) {
    D_800DD434 = 0;
    D_800DD446 = 0;
    D_800DD444 = 0x258;
    D_800DD432 = 0xF0;
    D_800DD433 = 0x14;
    D_800DD436 = 0;
    D_800DD440 = 0;
}
void func_10004074(s32);
void func_1516972C(u8 *);
void func_100111C8(u16);
extern u16 D_800DD430;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15178EFC CURRENT (75) */
void func_15178EFC(s32 arg0) {
    s32 temp_v0;
    s32 var_s0;
    u8 *temp_a0;

    if (arg0 == 2) {
        D_800DD434 = 0;
        temp_v0 = D_800DD440;
        D_800DD446 = 0;
        if (temp_v0 != 0) {
            var_s0 = 0;
            do {
                temp_a0 = *(u8 **)((u8 *)temp_v0 + var_s0);
                if (temp_a0 != 0) {
                    func_1516972C(temp_a0);
                    *(s32 *)((u8 *)(s32)D_800DD440 + var_s0) = 0;
                    temp_v0 = D_800DD440;
                }
                var_s0 += 4;
            } while (var_s0 != 0x4B0);
            func_10004074(temp_v0);
            D_800DD440 = 0;
        }
        func_100111C8(D_800DD430);
        D_800DD444 = 0;
        D_800DD436 = 0;
        return;
    }
    if (arg0 == 3) {
        if (D_800DD446 == 0) {
            D_800DD444 = 0x258;
        } else if (D_800DD446 == 3) {
            D_800DD446 = 1;
        }
        D_800DD434 = arg0;
        return;
    }
    D_800DD434 = arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15178EFC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A6360/func_15178EFC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A6360/func_15179008.s")
f32 func_150AD780(f32);
f32 func_150AD78C(f32);
extern void *D_800DBFF0;
extern s16 D_800DD438[3];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151794C8 CURRENT (3899) */
void func_151794C8(void) {
    s32 x;
    s32 y;
    s32 z;
    f32 offset_y;
    f32 offset_z;
    f32 trig;
    f32 angle;
    f32 second_z;

    x = (s32)*(f32 *)((u8 *)D_800DBFF0 + 0x2F8);
    y = (s32)*(f32 *)((u8 *)D_800DBFF0 + 0x2FC);
    z = (s32)*(f32 *)((u8 *)D_800DBFF0 + 0x300);
    angle = *(f32 *)((u8 *)D_800DBFF0 + 0x398);
    trig = func_150AD78C(angle);
    offset_y = 500.0f * trig;
    offset_z = -500.0f * func_150AD780(angle);
    angle = *(f32 *)((u8 *)D_800DBFF0 + 0x3A0);
    trig = func_150AD78C(angle);
    second_z = (offset_z * func_150AD780(angle)) - 0.0f;
    D_800DD438[0] = (s16)(s32)((f32)x + (0.0f + (offset_z * trig)));
    D_800DD438[2] = (s16)(s32)((f32)z + second_z);
    D_800DD438[1] = (s16)(s32)((f32)y + offset_y);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151794C8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A6360/func_151794C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A6360/func_15179600.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A6360/func_151797B0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15179AB8 CURRENT (25) */
void func_15179AB8(void) {
    void **var_a0;
    void *temp_v0_2;
    s32 var_v1;
    s32 temp_v0;
    s32 temp_a1;

    temp_v0 = D_800DD436 - 1;
    if (temp_v0 >= 0) {
        var_v1 = temp_v0 * 4;
        var_a0 = (void **)((u8 *)(s32)D_800DD440 + var_v1);
        do {
            temp_v0_2 = *var_a0;
            var_v1 -= 4;
            if (temp_v0_2 != 0) {
                temp_a1 = *(s32 *)((u8 *)temp_v0_2 + 0x90);
                if (!(temp_a1 & 2)) {
                    *(s32 *)((u8 *)temp_v0_2 + 0x90) = temp_a1 | 2;
                    return;
                }
            }
            var_a0--;
        } while (var_v1 >= 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15179AB8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A6360/func_15179AB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A6360/func_15179B14.s")
extern void *D_800DBFF0;

f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
void func_15179CB0(void *arg0) {
    f32 temp_fa0;
    f32 temp_fv1;
    f32 scale;

    temp_fv1 = (f32) *(s16 *)((u8 *)arg0 + 0xA0) - *(f32 *)((u8 *)D_800DBFF0 + 0x300);
    temp_fa0 = (f32) *(s16 *)((u8 *)arg0 + 0x9C) - *(f32 *)((u8 *)D_800DBFF0 + 0x2F8);
    scale = 160.0f;
    scale *= sqrtf((temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0));
    *(s8 *)((u8 *)arg0 + 0xB4) = (s8) (u32) (255.0f - (scale / 1000.0f));
}
