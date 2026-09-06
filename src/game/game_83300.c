#include "types.h"

/*
 * Reviewed source unit: src/game/game_83300.c
 * Boundary evidence: docs/evidence/game_state_callback_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15055E50
 * - func_15056150
 * - func_15056258
 * - func_150562FC
 * - func_1505693C
 * - func_15056A00
 * - func_15056B08
 * - func_1505841C
 * - func_150585F0
 * - func_15058898
 * - func_15058EA4
 * - func_15058F24
 * - func_15059140
 * - func_150593C4
 * - func_15059444
 * - func_1505959C
 * - func_150597FC
 * - func_150599C8
 * - func_15059B54
 * - func_15059C84
 * - func_1505A184
 * - func_1505A250
 * - func_1505A3A8
 * - func_1505A5CC
 * - func_1505A630
 * - func_1505A6F8
 * - func_1505A72C
 * - func_1505A770
 * - func_1505A9AC
 * - func_1505B5F8
 * - func_1505B9C4
 * - func_1505C140
 * - func_1505C1A4
 * - func_1505C1E4
 * - func_1505C7D8
 * - func_1505D024
 * - func_1505D1C4
 * - func_1505D2B8
 * - func_1505D34C
 * - func_1505D408
 * - func_1505D5D0
 * - func_1505D6F0
 * - func_1505DADC
 * - func_1505DDA8
 * - func_1505DF10
 * - func_1505DFDC
 * - func_1505E060
 * - func_1505E0C4
 * - func_1505E650
 * - func_1505E7CC
 * - func_1505E874
 * - func_1505ED34
 * - func_1505EEB0
 * - func_1505EEF4
 * - func_1505EFD0
 * - func_1505F0AC
 * - func_1505F188
 * - func_1505F298
 * - func_1506045C
 * - func_15060778
 * - func_15060A30
 * - func_15060A9C
 * - func_15060B04
 * - func_15060B70
 * - func_15060BA4
 * - func_15060BE0
 * - func_15060D54
 * - func_15060F28
 * - func_150611E8
 * - func_150615DC
 * - func_1506160C
 * - func_150617BC
 * - func_1506196C
 * - func_150619A8
 * - func_15061B4C
 * - func_150623F4
 * - func_150626EC
 * - func_150627D4
 * - func_15062800
 * - func_15062AC4
 * - func_15062B1C
 * - func_15062B50
 * - func_15062B84
 * - func_15062BDC
 * - func_15062D10
 * - func_15062E24
 * - func_15062FC0
 * - func_15063168
 * - func_15063254
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15055E50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15056150.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15056258.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150562FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505693C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15056A00.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15056B08.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505841C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150585F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15058898.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15058EA4 CURRENT (35) */
void func_15058EA4(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x18);
    if (arg1 < temp_fv0) {
        *(f32 *)((u8 *)arg0 + 0x24) = arg2;
    } else if (temp_fv0 < arg3) {
        *(f32 *)((u8 *)arg0 + 0x24) = arg4;
    }
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x20);
    if (arg5 < temp_fv1) {
        *(f32 *)((u8 *)arg0 + 0x20) = arg5;
        return;
    }
    if (temp_fv1 < arg6) {
        *(f32 *)((u8 *)arg0 + 0x20) = arg6;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15058EA4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15058EA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15058F24.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15059140.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150593C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15059444.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505959C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150597FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150599C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15059B54.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15059C84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A184.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A250.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A3A8.s")
extern f32 D_800994D4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505A5CC CURRENT (2035) */
f32 func_1505A5CC(void *arg0) {
    f32 temp_fa0;
    f32 temp_fv1;

    temp_fv1 = (f32) *(s8 *)((u8 *)arg0 + 2);
    temp_fa0 = (f32) *(s8 *)((u8 *)arg0 + 3);
    {
        f32 var_fv1 = sqrtf((temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0)) * D_800994D4;
    if (var_fv1 > 35.0f) {
        var_fv1 = 35.0f;
    }
    return var_fv1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505A5CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A5CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A630.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505A6F8 CURRENT (1055) */
f32 func_1505A6F8(void *arg0, void *arg1) {
    f32 temp_fa0;
    f32 temp_fv1;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x14) - *(f32 *)((u8 *)arg1 + 0x14);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x1C) - *(f32 *)((u8 *)arg1 + 0x1C);
    return sqrtf((temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505A6F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A6F8.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505A72C CURRENT (1075) */
f32 func_1505A72C(void *arg0, void *arg1) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv1;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x14) - *(f32 *)((u8 *)arg1 + 0x14);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x1C) - *(f32 *)((u8 *)arg1 + 0x1C);
    temp_fa1 = *(f32 *)((u8 *)arg0 + 0x18) - *(f32 *)((u8 *)arg1 + 0x18);
    return sqrtf((temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0) + (temp_fa1 * temp_fa1));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505A72C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A72C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A770.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A9AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505B5F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505B9C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505C140.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505C1A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505C1E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505C7D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D024.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D1C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D2B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D34C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D408.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D5D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D6F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505DADC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505DDA8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505DF10.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505DFDC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505E060.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505E0C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505E650.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505E7CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505E874.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505ED34.s")
extern s32 D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1505EEB0 CURRENT (780) */
s32 *func_1505EEB0(s32 arg0, s32 *arg1) {
    s32 *var_v1;
    s32 var_a2;

    var_v1 = &D_800CC2D0;
    var_a2 = 0;
    if (arg0 != D_800CC2D0) {
loop_1:
        var_a2 += 1;
        var_v1 += 0x32C;
        if (var_a2 < 0x19) {
            if (arg0 != *var_v1) {
                goto loop_1;
            }
        }
    }
    *arg1 = var_a2;
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1505EEB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505EEB0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505EEF4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505EFD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505F0AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505F188.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505F298.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1506045C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060778.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060A30.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060A9C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060B04.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060B70.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15060BA4 CURRENT (115) */
s32 func_15060BA4(void *arg0, s32 arg1) {
    u8 temp_t6;
    u8 temp_v0;

    temp_v0 = *(u8 *)((u8 *)arg0 + 0x1CA);
    temp_t6 = temp_v0 + arg1;
    if (temp_v0 == 6) {
        return 0;
    }
    *(u8 *)((u8 *)arg0 + 0x1CA) = temp_t6;
    if ((temp_t6 & 0xFF) >= 7) {
        *(u8 *)((u8 *)arg0 + 0x1CA) = 6U;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15060BA4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060BA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060BE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060D54.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060F28.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150611E8.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150615DC CURRENT (40) */
void func_150615DC(void *arg0) {
    *(s8 *)((u8 *)arg0 + 7) = 0xFF;
    *(s8 *)((u8 *)arg0 + 8) = 0xFF;
    *(s8 *)((u8 *)arg0 + 9) = 0;
    *(s8 *)((u8 *)arg0 + 0xA) = 0;
    *(s8 *)((u8 *)arg0 + 0xF) = 0;
    *(s8 *)((u8 *)arg0 + 0xE) = 0xFF;
    *(s8 *)((u8 *)arg0 + 0xD) = 0xFF;
    *(s8 *)((u8 *)arg0 + 0xC) = 0xFF;
    *(s8 *)((u8 *)arg0 + 0xB) = 0xFF;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150615DC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150615DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1506160C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150617BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1506196C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150619A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15061B4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150623F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150626EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150627D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062800.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15062AC4 CURRENT (170) */
void func_15062AC4(void *arg0) {
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_v0;
    s16 temp_v1;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0xE6);
    if (temp_v0 != 0) {
        temp_v1 = *(s16 *)((u8 *)arg0 + 0xE4);
        if (temp_v1 != 0) {
            temp_fv0 = (f32) temp_v1;
            temp_fv1 = (f32) temp_v0;
            *(f32 *)((u8 *)arg0 + 0xEC) = (f32) (temp_fv0 / temp_fv1);
            *(f32 *)((u8 *)arg0 + 0xF0) = (f32) (temp_fv1 / temp_fv0);
            return;
        }
    }
    *(f32 *)((u8 *)arg0 + 0xEC) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0xF0) = 0.0f;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15062AC4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062AC4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062B1C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062B50.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15062B84 CURRENT (170) */
void func_15062B84(void *arg0) {
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_v0;
    s16 temp_v1;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0xD4);
    if (temp_v0 != 0) {
        temp_v1 = *(s16 *)((u8 *)arg0 + 0xD2);
        if (temp_v1 != 0) {
            temp_fv0 = (f32) temp_v1;
            temp_fv1 = (f32) temp_v0;
            *(f32 *)((u8 *)arg0 + 0xDC) = (f32) (temp_fv0 / temp_fv1);
            *(f32 *)((u8 *)arg0 + 0xE0) = (f32) (temp_fv1 / temp_fv0);
            return;
        }
    }
    *(f32 *)((u8 *)arg0 + 0xDC) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0xE0) = 0.0f;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15062B84 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062B84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062BDC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062D10.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062E24.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062FC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15063168.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15063254.s")
