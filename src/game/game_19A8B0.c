#include "types.h"

/*
 * Reviewed source unit: src/game/game_19A8B0.c
 * Boundary evidence: docs/evidence/game_raw_state_lifecycle_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1516D400
 * - func_1516D4E8
 * - func_1516D678
 * - func_1516D738
 * - func_1516D99C
 * - func_1516DB90
 * - func_1516E778
 * - func_1516E8CC
 * - func_1516ECAC
 * - func_1516ED68
 * - func_1516EED4
 * - func_1516F024
 * - func_1516F1C0
 * - func_1516F2F8
 * - func_1516F548
 * - func_1516F864
 * - func_1516F8EC
 * - func_1516F91C
 * - func_1516F984
 * - func_1516F9C4
 * - func_1516FA88
 * - func_1516FBCC
 * - func_1516FD50
 * - func_1516FE1C
 * - func_15170034
 * - func_151700D8
 * - func_15170500
 * - func_151707E0
 * - func_151709B4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern u8 D_800BE9A0;
extern u8 D_800DD2A0;
extern u8 D_800DD2A1;
extern u8 D_800DD2A2;
extern u8 D_800DD2A3;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516D400 CURRENT (2640) */
void func_1516D400(void) {
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;

    if ((s32) D_800DD2A0 < 0xFF) {
        var_v0 = D_800DD2A0 + D_800BE9A0;
        if (var_v0 >= 0x100) {
            var_v0 = 0xFF;
        }
        D_800DD2A0 = (u8) var_v0;
    }
    if ((s32) D_800DD2A1 < 0xFF) {
        var_v0_2 = D_800DD2A1 + D_800BE9A0;
        if (var_v0_2 >= 0x100) {
            var_v0_2 = 0xFF;
        }
        D_800DD2A1 = (u8) var_v0_2;
    }
    if ((s32) D_800DD2A2 < 0xFF) {
        var_v0_3 = D_800DD2A2 + D_800BE9A0;
        if (var_v0_3 >= 0x100) {
            var_v0_3 = 0xFF;
        }
        D_800DD2A2 = (u8) var_v0_3;
    }
    if ((s32) D_800DD2A3 < 0xFF) {
        var_v0_4 = D_800DD2A3 + D_800BE9A0;
        if (var_v0_4 >= 0x100) {
            var_v0_4 = 0xFF;
        }
        D_800DD2A3 = (u8) var_v0_4;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516D400 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516D400.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516D4E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516D678.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516D738.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516D99C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516DB90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516E778.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516E8CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516ECAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516ED68.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516EED4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516F024.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516F1C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516F2F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516F548.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516F864 CURRENT (1010) */
void func_1516F864(void *arg0) {
    s32 temp_t1;
    s32 temp_t3;

    temp_t3 = (*(s16 *)((u8 *)arg0 + 0xE) << 8) + *(u8 *)((u8 *)arg0 + 0x2A) + (((*(s8 *)((u8 *)arg0 + 0x26) << 8) + *(u8 *)((u8 *)arg0 + 0x27)) * D_800BE9E4);
    *(s16 *)((u8 *)arg0 + 0xE) = (s16) (temp_t3 >> 8);
    *(u8 *)((u8 *)arg0 + 0x2A) = (u8) temp_t3;
    temp_t1 = (*(s16 *)((u8 *)arg0 + 0x12) << 8) + *(u8 *)((u8 *)arg0 + 0x2B) + (((*(s8 *)((u8 *)arg0 + 0x28) << 8) + *(u8 *)((u8 *)arg0 + 0x29)) * D_800BE9E4);
    *(s16 *)((u8 *)arg0 + 0x12) = (s16) (temp_t1 >> 8);
    *(u8 *)((u8 *)arg0 + 0x2B) = (u8) temp_t1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516F864 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516F864.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516F8EC CURRENT (45) */
void func_1516F8EC(void *arg0, s32 arg1) {
    s32 temp_t0;

    temp_t0 = (s32) (((*(s8 *)((u8 *)arg0 + 0x26) << 8) + *(u8 *)((u8 *)arg0 + 0x27)) * arg1) >> 8;
    *(s8 *)((u8 *)arg0 + 0x26) = (s8) (temp_t0 >> 8);
    *(u8 *)((u8 *)arg0 + 0x27) = (u8) temp_t0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516F8EC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516F8EC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516F91C CURRENT (45) */
void func_1516F91C(void *arg0, s32 arg1) {
    s32 temp_t0;

    temp_t0 = (s32) (((*(s8 *)((u8 *)arg0 + 0x28) << 8) + *(u8 *)((u8 *)arg0 + 0x29)) * arg1) >> 8;
    *(s8 *)((u8 *)arg0 + 0x28) = (s8) (temp_t0 >> 8);
    *(u8 *)((u8 *)arg0 + 0x29) = (u8) temp_t0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516F91C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516F91C.s")
void func_1516F94C(s32 arg0, s32 arg1) {
    func_1516F8EC(arg0, arg1);
    func_1516F91C(arg0, arg1);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516F984 CURRENT (40) */
void func_1516F984(s32 arg0, s32 arg1) {
    func_1516F94C(arg0, arg1);
    *(s16 *)((u8 *)arg0 + 0x18) = (s16) ((s32) (*(s16 *)((u8 *)arg0 + 0x18) * arg1) >> 8);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516F984 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516F984.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516F9C4 CURRENT (1610) */
s32 func_1516F9C4(void *arg0) {
    u8 var_v0;

    var_v0 = *(u8 *)((u8 *)arg0 + 0x1F);
    if (*(u8 *)((u8 *)arg0 + 0x24) != 0) {
        if (var_v0 != 0xFF) {
            var_v0 += D_800BE9E4 * 0x10;
            if ((s32) var_v0 >= 0x100) {
                var_v0 = 0xFF;
            }
            *(u8 *)((u8 *)arg0 + 0x1F) = var_v0;
        }
    } else {
        if (var_v0 != 0) {
            var_v0 -= D_800BE9E4 * 8;
            if ((s32) var_v0 < 0) {
                var_v0 = 0;
            }
            *(u8 *)((u8 *)arg0 + 0x1F) = var_v0;
        }
        {
            s32 temp_t0 = (s32) (var_v0 << 9) >> 8;
        *(s16 *)((u8 *)arg0 + 0x16) = (s16) temp_t0;
        *(s16 *)((u8 *)arg0 + 0x14) = (s16) temp_t0;
    }
    if ((*(u8 *)((u8 *)arg0 + 0x24) == 0) && (var_v0 == 0)) {
        return 1;
    }
    func_1516F864(arg0);
    func_1516F984((s32) arg0, 0xF0);
    return 0;
        }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516F9C4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516F9C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516FA88.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516FBCC CURRENT (1305) */
s32 func_1516FBCC(void *arg0) {
    s16 temp_v1;
    s32 temp_t9;
    s32 var_v0_2;
    u8 temp_v1_2;
    u8 temp_v1_3;
    u8 temp_v1_4;
    u8 var_v0;

    var_v0 = *(u8 *)((u8 *)arg0 + 0x1F);
    if (*(u8 *)((u8 *)arg0 + 0x24) != 0) {
        if (var_v0 != 0xFF) {
            var_v0 += D_800BE9E4 * 0x10;
            if ((s32) var_v0 >= 0x100) {
                var_v0 = 0xFF;
            }
            *(u8 *)((u8 *)arg0 + 0x1F) = var_v0;
        }
    } else if (var_v0 != 0) {
        var_v0 -= D_800BE9E4 << *(u8 *)((u8 *)arg0 + 0x2F);
        if ((s32) var_v0 < 0) {
            var_v0 = 0;
        }
        *(u8 *)((u8 *)arg0 + 0x1F) = var_v0;
    }
    if ((*(u8 *)((u8 *)arg0 + 0x24) == 0) && (var_v0 == 0)) {
        return 1;
    }
    *(s16 *)((u8 *)arg0 + 0x14) = (s16) (*(s16 *)((u8 *)arg0 + 0x14) + (*(s8 *)((u8 *)arg0 + 0x2D) * D_800BE9E4));
    temp_v1 = *(s16 *)((u8 *)arg0 + 0x14);
    *(s16 *)((u8 *)arg0 + 0x16) = (s16) (*(s16 *)((u8 *)arg0 + 0x16) + (*(s8 *)((u8 *)arg0 + 0x2E) * D_800BE9E4));
    if ((temp_v1 <= 0) || (temp_v1 <= 0)) {
        *(s16 *)((u8 *)arg0 + 0x16) = 0;
        *(s16 *)((u8 *)arg0 + 0x14) = (s16) *(s16 *)((u8 *)arg0 + 0x16);
        return 1;
    }
    var_v0_2 = *(u8 *)((u8 *)arg0 + 0x2C) + D_800BE9E4;
    if (var_v0_2 >= 0x80) {
        var_v0_2 = 0x7F;
    }
    temp_v1_2 = *(u8 *)((u8 *)arg0 + 0x26);
    temp_t9 = var_v0_2 * 2;
    *(u8 *)((u8 *)arg0 + 0x2C) = (u8) var_v0_2;
    temp_v1_3 = *(u8 *)((u8 *)arg0 + 0x27);
    *(s8 *)((u8 *)arg0 + 0x1C) = (s8) (((s32) ((*(u8 *)((u8 *)arg0 + 0x29) - temp_v1_2) * temp_t9) >> 8) + temp_v1_2);
    temp_v1_4 = *(u8 *)((u8 *)arg0 + 0x28);
    *(s8 *)((u8 *)arg0 + 0x1D) = (s8) (((s32) ((*(u8 *)((u8 *)arg0 + 0x2A) - temp_v1_3) * temp_t9) >> 8) + temp_v1_3);
    *(s8 *)((u8 *)arg0 + 0x1E) = (s8) (((s32) ((*(u8 *)((u8 *)arg0 + 0x2B) - temp_v1_4) * temp_t9) >> 8) + temp_v1_4);
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516FBCC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516FBCC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516FD50 CURRENT (1835) */
s32 func_1516FD50(void *arg0) {
    u8 var_v0;

    var_v0 = *(u8 *)((u8 *)arg0 + 0x1F);
    if (*(u8 *)((u8 *)arg0 + 0x24) != 0) {
        if (var_v0 != 0xFF) {
            var_v0 += D_800BE9E4 * 0x10;
            if ((s32) var_v0 >= 0x100) {
                var_v0 = 0xFF;
            }
            *(u8 *)((u8 *)arg0 + 0x1F) = var_v0;
        }
    } else {
        if (var_v0 != 0) {
            var_v0 -= D_800BE9E4 * 8;
            if ((s32) var_v0 < 0) {
                var_v0 = 0;
            }
            *(u8 *)((u8 *)arg0 + 0x1F) = var_v0;
        }
        {
            s32 temp_t0 = (s32) (var_v0 << 9) >> 8;
        *(s16 *)((u8 *)arg0 + 0x16) = (s16) temp_t0;
        *(s16 *)((u8 *)arg0 + 0x14) = (s16) temp_t0;
    }
    if ((*(u8 *)((u8 *)arg0 + 0x24) == 0) && (var_v0 == 0)) {
        return 1;
    }
    func_1516F864(arg0);
    *(s16 *)((u8 *)arg0 + 0x18) = (s16) (*(s16 *)((u8 *)arg0 + 0x18) + *(s8 *)((u8 *)arg0 + 0x2C));
    return 0;
        }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516FD50 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516FD50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516FE1C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_15170034.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_151700D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_15170500.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_151707E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_151709B4.s")
