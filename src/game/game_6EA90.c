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

/* Keep address symbols for linking and registered match evidence. */
#define text_get_special_glyph_metadata func_150415E0

void text_get_special_glyph_metadata(s32 arg0, s32 *arg1, s32 *arg2, f32 *arg3, s32 *arg4, f32 *arg5) {
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
