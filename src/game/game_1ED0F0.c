#include "types.h"

/*
 * Reviewed source unit: src/game/game_1ED0F0.c
 * Boundary evidence: docs/evidence/game_raw_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151BFC40
 * - func_151BFDA0
 * - func_151BFE84
 * - func_151C0098
 * - func_151C02E4
 * - func_151C0360
 * - func_151C0418
 * - func_151C04F8
 * - func_151C05A4
 * - func_151C05F0
 * - func_151C0644
 * - func_151C0698
 * - func_151C110C
 * - func_151C1180
 * - func_151C1570
 * - func_151C1654
 * - func_151C1798
 * - func_151C1814
 * - func_151C1860
 * - func_151C196C
 * - func_151C1D5C
 * - func_151C1FB8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_80082FA0;
extern s8 D_8008FD8C;
extern f32 D_800AA97C;
extern f32 D_800AA980;
extern f32 D_800AA984;
extern f32 D_800AA988;
extern f32 D_800AA98C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BFC40 CURRENT (1690) */
void func_151BFC40(void *arg0, f32 *arg1) {
    s32 var_v0;
    s32 var_v0_2;

    *(s32 *)((u8 *)arg0 + 0) = 3;
    if (D_80082FA0 >= 2) {
        var_v0 = 1;
    } else {
        var_v0 = 0;
    }
    *(s32 *)((u8 *)arg0 + 4) = (s32) (4 >> var_v0);
    *arg1 = 494.0f;
    *(f32 *)((u8 *)arg0 + 0x14) = (f32) D_800AA97C;
    *(s32 *)((u8 *)arg0 + 0x2C) = 7;
    *(f32 *)((u8 *)arg0 + 0x18) = (f32) D_800AA980;
    *(f32 *)((u8 *)arg0 + 0x1C) = 45.0f;
    *(f32 *)((u8 *)arg0 + 0x20) = 53.0f;
    *(f32 *)((u8 *)arg0 + 0x24) = 203.0f;
    *(f32 *)((u8 *)arg0 + 0x28) = 414.0f;
    if ((D_80082FA0 >= 2) || (var_v0_2 = 0, ((D_8008FD8C < 8) == 0))) {
        var_v0_2 = 1;
    }
    *(s32 *)((u8 *)arg0 + 0x30) = (s32) (3 >> var_v0_2);
    *(f32 *)((u8 *)arg0 + 0x34) = 15.0f;
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) D_800AA984;
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) D_800AA988;
    *(s16 *)((u8 *)arg0 + 0x44) = 0x19;
    *(s16 *)((u8 *)arg0 + 0x46) = 0xF;
    *(s16 *)((u8 *)arg0 + 0x48) = 0x64;
    *(s16 *)((u8 *)arg0 + 0x4A) = 0x64;
    *(s16 *)((u8 *)arg0 + 0x4C) = 0xC;
    *(s16 *)((u8 *)arg0 + 0x4E) = 0x14;
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) D_800AA98C;
    if ((D_80082FA0 >= 2) || (D_8008FD8C >= 8)) {
        *(s8 *)((u8 *)arg0 + 0x50) = -1;
        return;
    }
    *(s8 *)((u8 *)arg0 + 0x50) = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BFC40 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151BFC40.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151BFDA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151BFE84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C0098.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C02E4 CURRENT (20) */
s32 func_151C02E4(void *arg0, void *arg1, s32 arg2, void **arg3) {
    s32 temp_t6;
    void **temp_t7;
    void *temp_t8;
    s32 temp_t9;
    s32 var_v0;

    var_v0 = 0;
    if (arg2 > 0) {
loop_1:
        temp_t6 = var_v0 << 2;
        temp_t7 = (void **)((u8 *)arg3 + temp_t6);
        temp_t8 = *temp_t7;
        if (arg0 == temp_t8) {
            return 0;
        }
        var_v0 += 1;
        temp_t9 = var_v0 & 0xFF;
        if (temp_t9 >= arg2) {
            goto block_4;
        }
        goto loop_1;
    }
block_4:
    if (arg0 == arg1) {
        return 0;
    }
    if (*(s32 *)((u8 *)arg0 + 0) == 0) {
        return 0;
    }
    if (*(u8 *)((u8 *)arg0 + 4) == 0xFF) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C02E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C02E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C0360.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C0418.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C04F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C05A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C05F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C0644.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C0698.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C110C CURRENT (8) */
s32 func_151C110C(void *arg0, s32 arg1, s32 *arg2, s32 arg3, s16 *arg6) {
    void *temp_v1;

    temp_v1 = *(void **)((u8 *)arg0 + 0x18);
    if ((temp_v1 != 0) && (*arg2 != 0)) {
        *(s16 *)((u8 *)arg0 + 2) = (s16) (s32) *(f32 *)((u8 *)temp_v1 + 0x38);
        *(s16 *)((u8 *)arg0 + 4) = (s16) (s32) *(f32 *)((u8 *)temp_v1 + 0x3C);
        *(s16 *)((u8 *)arg0 + 6) = (s16) (s32) *(f32 *)((u8 *)temp_v1 + 0x40);
        return 0;
    }
    *arg6 = 0;
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C110C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C110C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C1180.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C1570.s")
void func_151C1570(s32 arg0);
void func_1513259C(s32 arg0);

void func_151C15FC(s32 arg0) {
    func_151C1570(arg0);
    func_15132570(arg0);
}
void func_151C1628(s32 arg0) {
    func_151C1570(arg0);
    func_1513259C(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C1654.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C1798.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C1814 CURRENT (205) */
void func_151C1814(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 temp_a2;
    s32 temp_v1;
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + 0x170);
    if ((arg2 & 0xFF) == 0x2D) {
        temp_v1 = *(s32 *)((u8 *)arg1 + 0);
        temp_a2 = *(s32 *)((u8 *)temp_v0 + 0x6C);
        if (temp_v1 == temp_a2) {
            *(s32 *)((u8 *)temp_v0 + 0x6C) = (s32) *(s32 *)((u8 *)arg1 + 4);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_a2) {
            *(s32 *)((u8 *)temp_v0 + 0x6C) = temp_v1;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C1814 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C1814.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C1860.s")
s32 func_151C02E4(void *arg0, void *arg1, s32 arg2, void **arg3);

void func_151C1940(void *arg0, void *arg1, s32 *arg2) {
    func_151C02E4(arg0, arg1, *arg2, (void **)((u8 *)arg2 + 4));
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C196C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C1D5C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1ED0F0/func_151C1FB8.s")
