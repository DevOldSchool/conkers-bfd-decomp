#include "types.h"

/*
 * Reviewed source unit: src/game/game_2DF70.c
 * Boundary evidence: docs/evidence/game_2DF70.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15000AD0
 * - func_15001460
 * - func_15001970
 * - func_15001A08
 * - func_15001B10
 * - func_15001B8C
 * - func_15001BC8
 * - func_15001CEC
 * - func_15001DE0
 * - func_15002008
 * - func_15002248
 * - func_15002560
 * - func_150025FC
 * - func_15002754
 * - func_150027F8
 * - func_15002878
 * - func_150028BC
 * - func_15002FB4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern signed char D_800D9E64;
extern s8 *D_800B0DE0;
s32 func_150027F8();

void func_15000AC0(void) {
    D_800D9E64 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15000AD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15001460.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15001970.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15001A08.s")
extern s32 D_800B0DCC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15001B10 CURRENT (140) */
void func_15001B10(void) {
    s32 temp_v0;

    temp_v0 = (s32) (D_800B0DE0 + 3) & ~3;
    D_800B0DE0 = (s8 *) temp_v0;
    D_800B0DCC += 1;
    *(s16 *)((u8 *)temp_v0 + 0xC) = 0;
    *(s16 *)((u8 *)temp_v0 + 4) = 0;
    D_800B0DE0 += 0xE;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15001B10 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15001B10.s")
void func_15001B5C(u8 arg0) {
    *D_800B0DE0 = arg0;
    D_800B0DE0 += 1;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15001B8C */
void func_15001B8C(u16 arg0) {
    D_800B0DE0[0] = arg0 >> 8;
    D_800B0DE0[1] = arg0;
    D_800B0DE0 += 2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15001B8C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15001B8C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15001BC8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15001CEC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15001DE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15002008.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15002248.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15002560 CURRENT (980) */
void func_15002560(void *arg0, u8 *arg1) {
    s16 temp_v0;
    s16 var_v0;
    u8 *temp_s0;
    u8 *var_a0;
    u8 *var_s1;

    var_a0 = arg0;
loop_1:
    if (var_a0 != 0) {
        if (*(s16 *)((u8 *)var_a0 + 4) == 0) {
            var_v0 = 0;
            if (arg1 != 0) {
                var_v0 = arg1 - var_a0;
            }
            *(s16 *)((u8 *)var_a0 + 4) = var_v0;
        }
        temp_v0 = *(s16 *)((u8 *)var_a0 + 0xC);
        var_s1 = (void *)(var_a0 + temp_v0);
        if (temp_v0 != 0) {
            if (*(s16 *)((u8 *)var_s1 + 4) != 0) {
                do {
                    temp_s0 = (void *)(var_s1 + *(s16 *)((u8 *)var_s1 + 4));
                    func_15002560(var_s1, temp_s0);
                    var_s1 = temp_s0;
                } while (*(s16 *)((u8 *)temp_s0 + 4) != 0);
            }
            var_a0 = var_s1;
            goto loop_1;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15002560 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15002560.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_150025FC.s")
extern s32 D_800DBE38;
extern s32 D_800B0DE4;
extern s32 D_800DBE18[];
extern s32 D_800DBE1C;
extern s32 D_800DBE28;
extern s32 D_800DBE4C;

void func_150026C4(void) {
    D_800DBE38 = 0;
    func_1510F800();
}
void func_150026E8(s32 arg0) {
    D_800DBE18[arg0] = D_800DBE38;
    D_800DBE4C = D_800DBE38;
    D_800B0DE4 += D_800DBE38;
}
void func_15002724(void) {
    D_800DBE38 += func_150027F8();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15002754.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150027F8 CURRENT (855) */
s32 func_150027F8(s8 *arg0) {
    s32 var_v0;
    s32 var_v1;
    s8 var_a1;

    if (arg0 == 0) {
        return 0;
    }
    var_a1 = *arg0;
    var_v0 = 0;
    var_v1 = 0;
    if (var_a1 != -0x21) {
        do {
            var_v0 += 1;
            if ((var_a1 >> 4) == 1) {
                var_v1 += 4;
            } else if (var_a1 == 6) {
                var_v1 += 2;
            } else if (var_a1 == 5) {
                var_v1 += 1;
            }
            var_a1 = *((var_v0 * 8) + arg0);
        } while (var_a1 != -0x21);
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150027F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_150027F8.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15002878 */
s32 func_15002878(void) {
    u8 *current;
    s32 value;
    s32 maximum;

    maximum = D_800DBE18[0];
    current = (u8 *)&D_800DBE1C;
    do {
        value = *(s32 *)current;
        current += 4;
        if (maximum < value) {
            maximum = value;
        }
    } while (current != (u8 *)&D_800DBE28);
    return maximum;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15002878 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15002878.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_150028BC.s")
extern u8 D_800BE616;
extern f32 D_800DBE64;

void func_15002F40(s32 arg0) {
    if ((arg0 == 0x32) || (arg0 == 0x33)) {
        D_800DBE64 = 150.0f;
        return;
    }
    if (D_800BE616 != 0) {
        D_800DBE64 = 85.0f;
        return;
    }
    D_800DBE64 = 50.0f;
}

s32 func_15002FA0(s32 arg0) {
    return arg0 ^ 0xF0F0F0F0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15002FB4.s")
