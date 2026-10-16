#include "types.h"

/*
 * Reviewed source unit: src/game/game_6EA90.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_record_glyph_emitter_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150417AC
 * - func_150428D4
 * - func_15042C40
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150415E0(s32 arg0, s32 *arg1, s32 *arg2, f32 *arg3, s32 *arg4, f32 *arg5) {
    if ((arg0 >= 0xA8) && (arg0 < 0x100)) {
        *arg5 = 1.0f;
        switch (arg0) {
            case 0xA8:
            case 0xA9:
                *arg1 = 0x20;
                *arg2 = 0x12;
                *arg3 = 3.1f;
                *arg4 = 1;
                break;
            case 0xAA:
            case 0xAB:
            case 0xAC:
            case 0xAD:
                *arg1 = 0x20;
                *arg2 = 0x1B;
                *arg3 = 2.0f;
                *arg4 = 1;
                *arg5 = 0.603f;
                break;
            case 0xAE:
                *arg1 = 0x10;
                *arg2 = 0x11;
                *arg3 = -1.6f;
                *arg4 = 1;
                break;
            case 0xAF:
            case 0xB0:
                *arg1 = 0x2E;
                *arg2 = 0x10;
                *arg3 = 2.0f;
                *arg4 = 1;
                break;
            case 0xB6:
            case 0xB7:
            case 0xB8:
            case 0xB9:
                *arg1 = 0x10;
                *arg2 = 0xC;
                *arg3 = 2.0f;
                *arg4 = 0;
                break;
            case 0xBA:
                *arg4 = 0;
                *arg3 = 0.2f;
                *arg1 = 0x37;
                *arg2 = 0xC;
                break;
            case 0xB1:
                *arg1 = 0x26;
                *arg2 = 0x18;
                *arg3 = 2.0f;
                *arg4 = 1;
                *arg5 = 0.726f;
                break;
            default:
                *arg1 = 0xC;
                *arg2 = 0x10;
                *arg3 = 2.0f;
                *arg4 = 0;
                break;
        }
    } else {
        *arg3 = 0.0f;
        *arg1 = 0;
        *arg2 = 0;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_6EA90/func_150417AC.s")
s32 func_15042C40(u8);
extern f32 D_800380A0;
extern f32 D_800380A4;
extern s32 D_80085994;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150428D4 CURRENT (4150) */
void func_150428D4(u8 *arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    s32 sp68;
    s32 sp64;
    s32 sp60;
    f32 sp5C;
    s32 sp58;
    f32 sp54;
    s32 temp_a0;
    s32 temp_s3;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_s0;
    s32 var_s5;
    s32 var_t0;
    u8 *temp_v0_4;
    u8 *var_s2;
    u8 var_a0;
    u8 var_v0;
    u8 *temp_v0_5;

    if (arg0 != NULL) {
        *arg1 = 0;
        *arg2 = 0;
        *arg3 = 0;
        var_s5 = 0;
        var_s0 = 0;
        if (*arg0 == 0) {
            *arg2 += 0xC;
        }
        var_s2 = arg0;
        if (*arg0 != 0) {
            var_a0 = *var_s2;
            var_v0 = var_a0;
            do {
                if (var_v0 == 0xBC) {
                    var_s2 += 2;
                } else {
                    temp_v0 = func_15042C40(var_a0);
                    temp_v1 = temp_v0 & 0xFF;
                    temp_s3 = temp_v0 & 0xFF;
                    var_t0 = 0;
                    if (temp_v1 == 0x60) {
                        *arg1 += 4;
                        if (var_s0 < 0xC) {
                            var_s0 = 0xC;
                        }
                    } else if ((temp_v1 < 0xA1) || (temp_v1 >= 0xA8)) {
                        if ((temp_v1 >= 0xA8) && (temp_v1 < 0x100)) {
                            sp68 = 0;
                            func_150415E0(temp_s3, &sp64, &sp60, &sp5C, &sp58, &sp54);
                            var_t0 = sp68;
                            *arg1 = (s32) ((f32) *arg1 + ((f32) sp64 * sp54));
                            temp_v0_2 = (s32) ((f32) (s32) ((f32) sp60 * sp54) - sp5C) + 1;
                            if (var_s0 < temp_v0_2) {
                                var_s0 = temp_v0_2;
                            }
                            if ((f32) *arg3 < sp5C) {
                                *arg3 = (s32) sp5C;
                            }
                        } else if (temp_v1 < 0xA1) {
                            if (*var_s2 == 0xA) {
                                temp_v0_3 = *arg1;
                                if (var_s5 < temp_v0_3) {
                                    var_s5 = temp_v0_3;
                                }
                                *arg1 = 0;
                                if (var_s0 < 0xC) {
                                    var_s0 = 0xC;
                                }
                                *arg2 += var_s0;
                                var_s0 = 0;
                            } else {
                                var_t0 = 1;
                            }
                        }
                    }
                    var_s2 += 1;
                    if (var_t0 != 0) {
                        temp_v1_2 = temp_s3 * 4;
                        temp_v0_4 = (u8 *) (D_80085994 + temp_v1_2);
                        *arg1 = (*arg1 + temp_v0_4[0] + temp_v0_4[2]) - 1;
                        temp_v0_5 = (u8 *) (D_80085994 + temp_v1_2);
                        temp_a0 = temp_v0_5[3] + temp_v0_5[1];
                        if (temp_a0 >= var_s0) {
                            var_s0 = temp_a0;
                        }
                    }
                }
                var_a0 = *var_s2;
                var_v0 = var_a0;
            } while (var_a0 != 0);
        }
        if (*arg1 < var_s5) {
            *arg1 = var_s5;
        }
        *arg2 += var_s0;
        *arg1 = (s32) ((f32) *arg1 * D_800380A0);
        *arg2 = (s32) ((f32) *arg2 * D_800380A4);
        *arg3 = (s32) ((f32) *arg3 * D_800380A0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150428D4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6EA90/func_150428D4.s")
extern u8 D_80085930[0x5F];
extern u8 D_80085931;
extern u8 D_80085932;
extern u8 D_80085933[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15042C40 CURRENT (420) */
s32 func_15042C40(u8 arg0) {
    s32 temp_t6;
    s32 var_a0;
    s32 var_v0;

    temp_t6 = arg0;
    if ((temp_t6 >= 0x61) && (temp_t6 < 0x7B)) {
        var_v0 = (temp_t6 - 0x20) & 0xFF;
    } else {
        var_v0 = temp_t6 & 0xFF;
    }
    if (temp_t6 == 0x20) {
        return 0x60;
    }
    for (var_a0 = 0; var_a0 < 0x5F; var_a0++) {
        if (var_v0 == D_80085930[var_a0]) {
            return var_a0;
        }
    }
    return temp_t6;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15042C40 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6EA90/func_15042C40.s")
