#include "types.h"

/*
 * Reviewed source unit: src/game/game_6EA90.c
 * Boundary evidence: docs/evidence/game_raw_record_glyph_emitter_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150415E0
 * - func_150417AC
 * - func_150428D4
 * - func_15042C40
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_6EA90/func_150415E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6EA90/func_150417AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6EA90/func_150428D4.s")
extern u8 D_80085930;
extern u8 D_80085931;
extern u8 D_80085932;
extern u8 D_80085933[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15042C40 CURRENT (540) */
s32 func_15042C40(u8 arg0) {
    u8 *var_v0_2;
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
    if (var_v0 == D_80085930) {
        return 0;
    }
    if (var_v0 == D_80085931) {
        return 1;
    }
    var_v0_2 = D_80085933;
    var_a0 = 3;
    if (var_v0 == D_80085932) {
        return 2;
    }
    for (;;) {
        if (var_v0 == var_v0_2[0]) {
            return var_a0;
        }
        if (var_v0 == var_v0_2[1]) {
            return var_a0 + 1;
        }
        if (var_v0 == var_v0_2[2]) {
            return var_a0 + 2;
        }
        if (var_v0 == var_v0_2[3]) {
            return var_a0 + 3;
        }
        var_a0 += 4;
        var_v0_2 += 4;
        if (var_a0 == 0x5F) {
            return temp_t6;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15042C40 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6EA90/func_15042C40.s")
