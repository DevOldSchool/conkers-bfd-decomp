#include "types.h"

/*
 * Reviewed source unit: src/game/game_70200.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15042D94
 * - func_15042E3C
 * - func_15042ECC
 * - func_150432CC
 * - func_1504332C
 * - func_15043384
 * - func_15043A20
 * - func_15043AC8
 * - func_15043B70
 * - func_15043BB8
 * - func_15043CA4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15043384(s32 arg0);
extern s32 D_800CBD64;

void func_15042D50(void) {
    D_800CBD64 = 0;
    func_15043384(0);
}
extern s8 D_800CBD74;

void func_15042D78(u8 arg0) {
    D_800CBD74 = arg0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/func_15042D94.s")
void func_15042ECC(s32, s32 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15042E3C CURRENT (1660) */
void func_15042E3C(s32 arg0, s32 arg1, ...) {
    u8 sp24[0x40];
    u8 *var_a1;
    u8 *var_v0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;

    var_v0 = (u8 *)&arg1;
    var_a1 = (u8 *)sp24;
    do {
        temp_v0 = ((s32)(var_v0 + 3)) & ~3;
        *(s32 *)(var_a1 + 0) = *(s32 *)temp_v0;
        temp_v0_2 = (temp_v0 + 7) & ~3;
        *(s32 *)(var_a1 + 4) = *(s32 *)temp_v0_2;
        temp_v0_3 = (temp_v0_2 + 7) & ~3;
        *(s32 *)(var_a1 + 8) = *(s32 *)temp_v0_3;
        var_a1 += 0x10;
        temp_v0_4 = (temp_v0_3 + 7) & ~3;
        *(s32 *)(var_a1 - 4) = *(s32 *)temp_v0_4;
        var_v0 = (u8 *)(temp_v0_4 + 4);
    } while (var_a1 != sp24 + 0x40);
    func_15042ECC(arg0, (s32 *)sp24);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15042E3C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/func_15042E3C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/func_15042ECC.s")
extern f32 D_800CBD80;

void func_150432BC(f32 arg0) {
    D_800CBD80 = arg0;
}
extern s32 D_800CBD78;
extern s16 D_800CBD7C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150432CC CURRENT (445) */
void func_150432CC(s32 arg0, s16 arg1) {
    s8 temp_t8;

    temp_t8 = (u8) D_800CBD74 | 1;
    D_800CBD74 = temp_t8;
    D_800CBD74 = temp_t8;
    D_800CBD7C = arg1;
    D_800CBD78 = arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150432CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/func_150432CC.s")
extern s16 D_800CBD70;
extern s16 D_800CBD72;

void func_150432FC(s16 arg0, s16 arg1) {
    D_800CBD70 = arg0;
    D_800CBD72 = arg1;
}
extern s8 D_800CBD60;
extern s8 D_800CBD61;
extern s8 D_800CBD62;
extern s8 D_800CBD63;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1504332C CURRENT (1200) */
void func_1504332C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_800CBD60 = arg0 & 0xFF;
    D_800CBD61 = arg1 & 0xFF;
    D_800CBD62 = arg2 & 0xFF;
    D_800CBD63 = arg3 & 0xFF;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1504332C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/func_1504332C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/func_15043384.s")
typedef struct Game70200Entry {
    s32 field_0;
    s32 field_4;
    s32 field_8;
    s32 field_C;
} Game70200Entry;

void func_15043A00(Game70200Entry *arg0, s32 arg1, s32 arg2) {
    if (arg0) {
        arg0->field_0 = arg1;
        arg0->field_4 = arg2;
        arg0->field_C = 0;
        arg0->field_8 = 0;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/func_15043A20.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/func_15043AC8.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15043B70 CURRENT (390) */
s32 func_15043B70(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_a2;
    s32 var_a3;
    s32 var_v0;

    var_a2 = arg2;
    var_a3 = arg3;
    if (var_a3 != 0) {
        do {
            var_v0 = var_a3;
            if (arg1 < (var_a2 + var_a3)) {
                var_v0 = arg1 - var_a2;
            }
            var_a2 += var_v0;
            var_a3 -= var_v0;
            if (var_a2 >= arg1) {
                var_a2 = 0;
            }
        } while (var_a3 != 0);
    }
    return var_a2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15043B70 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/func_15043B70.s")
s32 func_15043A20(s32, s32, s32, s32 *, s32);       /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15043BB8 CURRENT (905) */
s32 func_15043BB8(void *arg0, s32 *arg1, s32 arg2) {
    s32 temp_a2;
    s32 temp_t0;
    s32 temp_t8;
    s32 temp_v0;

    if (arg2 != 0) {
        temp_t8 = arg2 + 4;
        if (arg1 != 0) {
            arg2 = temp_t8;
            temp_t0 = (temp_t8 + 3) & ~3;
            arg2 = temp_t0;
            temp_a2 = *(s32 *)((u8 *)arg0 + 0xC);
            temp_v0 = *(s32 *)((u8 *)arg0 + 8);
            if (temp_a2 < temp_v0) {
                if ((temp_a2 + temp_t0) >= temp_v0) {
                    return 1;
                }
                goto block_7;
            }
            if (((temp_a2 + arg2) - *(s32 *)((u8 *)arg0 + 4)) >= temp_v0) {
                return 1;
            }
block_7:
            arg2 -= 4;
            *(s32 *)((u8 *)arg0 + 0xC) = func_15043A20(*(s32 *)((u8 *)arg0 + 0), *(s32 *)((u8 *)arg0 + 4), func_15043A20(*(s32 *)((u8 *)arg0 + 0), *(s32 *)((u8 *)arg0 + 4), temp_a2, &arg2, 4), arg1, arg2);
            goto block_8;
        }
    }
block_8:
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15043BB8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/func_15043BB8.s")
s32 func_15043AC8(s32, s32, s32, s32 *, s32);       /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15043CA4 CURRENT (1673) */
s32 func_15043CA4(void *arg0, s32 *arg1, s32 arg2) {
    s32 sp30;
    s32 sp2C;
    s32 temp_s0;
    s32 temp_a2;
    s32 var_a2;
    s32 var_v0;
    s32 temp_t6;

    sp30 = 0;
    temp_t6 = *(s32 *)((u8 *)arg0 + 8);
    sp2C = temp_t6;
    if (temp_t6 == *(s32 *)((u8 *)arg0 + 0xC)) {
        return 0;
    }
    var_a2 = func_15043AC8(*(s32 *)((u8 *)arg0 + 0), *(s32 *)((u8 *)arg0 + 4), sp2C, &sp30, 4);
    temp_s0 = arg2 - 1;
    if (arg2 < sp30) {
        temp_a2 = func_15043AC8(*(s32 *)((u8 *)arg0 + 0), *(s32 *)((u8 *)arg0 + 4), var_a2, arg1, temp_s0);
        *(arg1 + temp_s0) = 0;
        var_v0 = func_15043B70(*(s32 *)((u8 *)arg0 + 0), *(s32 *)((u8 *)arg0 + 4), temp_a2, sp30 - temp_s0);
        goto block_6;
    }
    if (sp30 != 0) {
        var_v0 = func_15043AC8(*(s32 *)((u8 *)arg0 + 0), *(s32 *)((u8 *)arg0 + 4), var_a2, arg1, sp30);
block_6:
        var_a2 = var_v0;
    }
    *(s32 *)((u8 *)arg0 + 8) = var_a2;
    return sp30;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15043CA4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/func_15043CA4.s")
