#include "types.h"

/*
 * Reviewed source unit: src/game/game_14C3F0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_complete_11ef40.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1511EF40
 * - func_1511F31C
 * - func_1511F3E8
 * - func_1511F4D0
 * - func_1511F788
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_14C3F0/func_1511EF40.s")
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
void func_1511490C(void *, s32);
s32 func_151149AC(u8);
extern s32 D_800BE9F0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1511F31C CURRENT (784) */
void func_1511F31C(u8 *arg0) {
    u8 transform[0x48];
    f32 x;
    f32 y;
    f32 z;
    s32 object;

    if ((*(u16 *)(arg0 + 0x54) == 0x8005) && (D_800BE9F0 == 0x35)) {
        object = func_151149AC(*(u16 *)(arg0 + 0x3E) & 0xFF);
        if (object != 0) {
            func_1511490C(transform, object);
            func_150A7960(transform, -3.0f, 223.0f, 549.0f, &x, &y, &z);
            *(s16 *)(arg0 + 0x10) = (s16)(s32)x;
            *(s16 *)(arg0 + 0x12) = (s16)(s32)y;
            *(s16 *)(arg0 + 0x14) = (s16)(s32)z;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1511F31C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_14C3F0/func_1511F31C.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1511F3E8 CURRENT (170) */
void func_1511F3E8(void *arg0) {
    s32 temp_t2;
    s32 temp_t4;
    s32 temp_v1;
    s32 temp_v1_2;

    if (*(s32 *)((u8 *)arg0 + 0x7C) == 0) {
        *(s32 *)((u8 *)arg0 + 0x7C) = 1;
        *(s32 *)((u8 *)arg0 + 0x80) = (s32) ((((s32) *(s32 *)((u8 *)arg0 + 0x3C) >> 0x10) & 0xFFFF) * 0x3C);
    }
    temp_v1 = *(s32 *)((u8 *)arg0 + 0x80);
    temp_t2 = (*(s32 *)((u8 *)arg0 + 0x3C) & 0xFFFF) * 0x3C;
    if (temp_v1 != 0) {
        if (D_800BE9E4 < temp_v1) {
            *(s32 *)((u8 *)arg0 + 0x80) = (s32) (temp_v1 - D_800BE9E4);
            return;
        }
        *(s32 *)((u8 *)arg0 + 0x80) = 0;
        *(s32 *)((u8 *)arg0 + 0x84) = temp_t2;
        return;
    }
    temp_v1_2 = *(s32 *)((u8 *)arg0 + 0x84);
    temp_t4 = temp_v1_2 - D_800BE9E4;
    if (D_800BE9E4 < temp_v1_2) {
        *(s32 *)((u8 *)arg0 + 0x84) = temp_t4;
        *(s8 *)((u8 *)arg0 + 0x8A) = (s8) ((s32) (temp_t4 * 0xFF) / temp_t2);
        return;
    }
    *(s8 *)((u8 *)arg0 + 0x6E) = 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1511F3E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_14C3F0/func_1511F3E8.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1511F4D0 CURRENT (6785) */
void func_1511F4D0(void *arg0) {
    s32 sp8;
    s32 sp4;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_a2_3;
    s32 temp_a2_4;
    s32 temp_a2_5;
    s32 temp_ft4;
    s32 temp_lo;
    s32 temp_t4;
    s32 var_a1;
    s32 var_a3;
    s32 var_t0;
    s32 var_v0;
    u8 temp_t4_2;
    u8 temp_v1;

    temp_v1 = *(u8 *)((u8 *)arg0 + 0x73);
    var_v0 = temp_v1 & 3;
    if ((temp_v1 & 4) == 4) {
        if (var_v0 == 2) {
            var_v0 = 0;
        } else if (var_v0 == 1) {
            var_v0 = 3;
        }
    }
    temp_a2 = *(s32 *)((u8 *)arg0 + 0x84);
    var_t0 = *(s32 *)((u8 *)arg0 + 0x7C);
    var_a3 = (temp_a2 >> 0x10) & 0xFFFF;
    var_a1 = temp_a2 & 0xFFFF;
    temp_ft4 = (s32) ((f32) *(s32 *)((u8 *)arg0 + 0x3C) * *(f32 *)((u8 *)arg0 + 0x30));
    if (var_t0 == 0) {
        temp_t4 = (*(s16 *)((u8 *)arg0 + 0x10) & 0xFFFF) | (*(s16 *)((u8 *)arg0 + 0x12) << 0x10);
        *(s32 *)((u8 *)arg0 + 0x7C) = temp_t4;
        if (var_v0 == 3) {
            var_a1 = 0xD;
            var_a3 = 0xD;
            var_t0 = temp_t4;
        } else {
            var_a3 = 0;
            var_a1 = 0;
            var_t0 = *(s32 *)((u8 *)arg0 + 0x7C);
        }
    }
    sp4 = (s32) (s16) var_t0;
    sp8 = (s32) (s16) (((s32) *(s32 *)((u8 *)arg0 + 0x7C) >> 0x10) & 0xFFFF);
    if (var_v0 == 2) {
        temp_a2_2 = var_a1 + D_800BE9E4;
        var_a1 = 0xD;
        if (temp_a2_2 < 0xD) {
            var_a1 = temp_a2_2;
        }
        if (var_a1 >= 9) {
            temp_a2_3 = var_a3 + D_800BE9E4;
            var_a3 = 0xD;
            if (temp_a2_3 < 0xD) {
                var_a3 = temp_a2_3;
            } else {
                var_v0 = 3;
            }
        }
    } else if (var_v0 == 1) {
        temp_a2_4 = var_a3 - D_800BE9E4;
        var_a3 = 0;
        if (temp_a2_4 > 0) {
            var_a3 = temp_a2_4;
        }
        if (var_a3 < 4) {
            temp_a2_5 = var_a1 - D_800BE9E4;
            var_a1 = 0;
            if (temp_a2_5 > 0) {
                var_a1 = temp_a2_5;
            } else {
                var_v0 = 0;
            }
        }
    }
    *(s16 *)((u8 *)arg0 + 0x12) = (s16) (sp8 + ((s32) (var_a1 * temp_ft4) / 13));
    *(s16 *)((u8 *)arg0 + 0xB2) = (s16) (sp8 - ((s32) ((temp_ft4 + 1) * var_a1) / 13));
    temp_lo = (s32) (temp_ft4 * var_a3) / 13;
    *(s16 *)((u8 *)arg0 + 0x150) = (s16) (sp4 - temp_lo);
    temp_t4_2 = *(u8 *)((u8 *)arg0 + 0x73) & ~3;
    *(u8 *)((u8 *)arg0 + 0x73) = temp_t4_2;
    *(s16 *)((u8 *)arg0 + 0x1F0) = (s16) (sp4 + temp_lo);
    *(s32 *)((u8 *)arg0 + 0x84) = (s32) ((var_a1 & 0xFFFF) | ((var_a3 & 0xFFFF) << 0x10));
    *(u8 *)((u8 *)arg0 + 0x73) = (u8) ((temp_t4_2 & 0xFF) | var_v0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1511F4D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_14C3F0/func_1511F4D0.s")
void func_1511F768(s32 *arg0, s32 arg1) {
    if (arg0[0x20] == 0) {
        arg0[0x20] = 1;
    }
}
f32 func_15047C00(f32, void *);                     /* extern */
s32 func_150ADA20();                                /* extern */
extern u8 D_800BE9B4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1511F788 CURRENT (1942) */
void func_1511F788(void *arg0) {
    s32 sp24;
    s32 temp_lo;
    s32 temp_v0;
    s32 temp_t9;
    s16 sp1E;

    sp1E = (s16) (s32) ((f32) *(s16 *)((u8 *)arg0 + 0x12) + *(f32 *)((u8 *)arg0 + 0x18));
    temp_lo = (s32) (*(s32 *)((u8 *)arg0 + 0x3C) * 0x3C) / 60;
    if (D_800BE9B4 != 0) {
        sp24 = temp_lo;
        *(s32 *)((u8 *)arg0 + 0x7C) = (s32) (func_150ADA20() & 0xFFFF);
    }
    sp24 = temp_lo;
    temp_v0 = *(s32 *)((u8 *)arg0 + 0x80);
    *(f32 *)((u8 *)arg0 + 0x18) = (f32) (func_15047C00((f32) *(s32 *)((u8 *)arg0 + 0x7C) * 0.005493164f, arg0) * 25.0f);
    *(s32 *)((u8 *)arg0 + 0x7C) = (s32) (*(s32 *)((u8 *)arg0 + 0x7C) + (D_800BE9E4 * 0xA));
    if (temp_v0 == 1) {
        temp_t9 = *(s32 *)((u8 *)arg0 + 0x84) + D_800BE9E4;
        *(s32 *)((u8 *)arg0 + 0x84) = temp_t9;
        if (temp_lo < temp_t9) {
            *(s32 *)((u8 *)arg0 + 0x80) = 2;
        }
    } else if (temp_v0 == 2) {
        *(s16 *)((u8 *)arg0 + 0x12) = (s16) (*(s16 *)((u8 *)arg0 + 0x12) - D_800BE9E4);
        if (*(s16 *)((u8 *)arg0 + 0x12) < -0x2710) {
            *(s8 *)((u8 *)arg0 + 0x6E) = 1;
        }
    }
    *(s16 *)((u8 *)arg0 + 0x5C) = (s16) (s32) (((f32) *(s16 *)((u8 *)arg0 + 0x12) + *(f32 *)((u8 *)arg0 + 0x18)) - (f32) sp1E);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1511F788 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_14C3F0/func_1511F788.s")
/* Call context: func_151149AC: unique active project prototype */
s32 func_151149AC(u8);

void func_1511F92C(void *arg0) {
    s32 temp_v0;

    temp_v0 = func_151149AC(*(u8 *)((u8 *)arg0 + 0x3F));
    if (temp_v0 != 0) {
        *(s16 *)((u8 *)arg0 + 0x10) = (s16) *(s16 *)((u8 *)temp_v0 + 0x10);
        *(s16 *)((u8 *)arg0 + 0x12) = (s16) *(s16 *)((u8 *)temp_v0 + 0x12);
        *(s16 *)((u8 *)arg0 + 0x14) = (s16) *(s16 *)((u8 *)temp_v0 + 0x14);
    }
}
