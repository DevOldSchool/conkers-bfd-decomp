#include "types.h"

/*
 * Reviewed source unit: src/game/game_1AC2F0.c
 * Boundary evidence: docs/evidence/game_raw_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1517EE40
 * - func_1517EF00
 * - func_1517EFDC
 * - func_1517F08C
 * - func_1517F3A0
 * - func_1517F40C
 * - func_1517F448
 * - func_1517F488
 * - func_1517F4D8
 * - func_1517F564
 * - func_1517F720
 * - func_1517F75C
 * - func_1517F7B4
 * - func_1517F814
 * - func_1517F9F4
 * - func_1517FB9C
 * - func_15180580
 * - func_151814FC
 * - func_15181CC8
 * - func_15181D00
 * - func_15181D70
 * - func_15181DC8
 * - func_15181E18
 * - func_15181EE0
 * - func_15182670
 * - func_15182768
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517EE40.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517EF00.s")
s32 func_1517EF00();                                /* extern */

s32 func_1517EFAC(void) {
    if (func_1517EF00() == 0xFF) {
        return 1;
    }
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517EFDC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517F08C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517F3A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517F40C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517F448.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517F488.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517F4D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517F564.s")
extern s8 D_800DDD88;
extern s8 D_800DDD89;
extern s8 D_800DDD8A;
extern s8 D_800DDD8B;
extern s8 D_800DDD8C;
extern s16 D_800DDE08;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517F720 CURRENT (1210) */
void func_1517F720(s8 arg0, s16 arg1, s8 arg2, s8 arg3, s32 arg4) {
    D_800DDE08 = arg1;
    D_800DDD88 = arg2;
    D_800DDD89 = 0;
    D_800DDD8A = arg0;
    D_800DDD8B = arg3;
    D_800DDD8C = (s8) arg4;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517F720 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517F720.s")
extern s32 D_80082FA0;
extern s32 D_800BE9E4;
extern u16 D_800DDE10;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517F75C CURRENT (1515) */
void func_1517F75C(void) {
    u16 *var_a0;
    u16 temp_v1;

    var_a0 = &D_800DDE10;
    if (D_80082FA0 >= 0) {
        do {
            temp_v1 = *var_a0;
            if (D_800BE9E4 < (s32) temp_v1) {
                *var_a0 = temp_v1 - D_800BE9E4;
            } else {
                *var_a0 = 0;
            }
            var_a0 += 2;
        } while ((u32) &(&D_800DDE10)[D_80082FA0] >= (u32) var_a0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517F75C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517F75C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517F7B4 CURRENT (30) */
void func_1517F7B4(void) {
    if ((u16) D_800DDE08 != 0) {
        if (D_800BE9E4 < (s32) (u16) D_800DDE08) {
            D_800DDE08 = (u16) D_800DDE08 - D_800BE9E4;
        } else {
            D_800DDE08 = 0;
        }
        D_800DDD89 = (u8) D_800DDD89 + ((u8) D_800DDD88 * D_800BE9E4);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517F7B4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517F7B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517F814.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517F9F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517FB9C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_15180580.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_151814FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_15181CC8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_15181D00.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_15181D70.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_15181DC8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_15181E18.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_15181EE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_15182670.s")
typedef struct Game1AC2F0Object {
    u8 pad0[0xE];
    s16 field_E;
    u8 pad10[0x1B];
    s8 field_2B;
    u8 pad2C[2];
    s16 field_2E;
} Game1AC2F0Object;

void func_15182748(Game1AC2F0Object *arg0) {
    arg0->field_2B = arg0->field_2E * arg0->field_E;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_15182768.s")
