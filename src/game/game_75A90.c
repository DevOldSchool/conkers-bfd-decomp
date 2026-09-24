#include "types.h"

/*
 * Reviewed source unit: src/game/game_75A90.c
 * Boundary evidence: docs/evidence/game_compact_multi_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150485E0
 * - func_15048664
 * - func_150486B8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern u16 D_80085EC0[];
extern u16 D_80085F3C[];
extern u16 D_80085FBC[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150485E0 CURRENT (30) */
 s32 func_150485E0(s32 arg0) {
    s32 var_a1;
    s32 var_v1;
    u16 *var_a2;
    s32 temp_a3;
    u16 *temp_t0;
    u16 temp_t1;

    var_v1 = 7;
    if (arg0 >= 0x7FE0) {
        var_a1 = 3;
        var_a2 = D_80085FBC;
        arg0 -= 0x7FE0;
    } else {
        var_v1 = 0x1FF;
        if (arg0 >= 0x7800) {
            var_v1 = 0x1F;
            var_a1 = 5;
            var_a2 = D_80085F3C;
            arg0 -= 0x7800;
        } else {
            var_a1 = 9;
            var_a2 = D_80085EC0;
        }
    }
    temp_t0 = (u16 *)((u8 *)var_a2 + ((arg0 >> var_a1) * 2));
    temp_a3 = temp_t0[0];
    temp_t1 = temp_t0[1];
    return temp_a3 - (((s32)(temp_a3 - temp_t1) * (arg0 & var_v1)) >> var_a1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150485E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_75A90/func_150485E0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15048664 CURRENT (510) */
s32 func_15048664(s32 arg0) {
    s32 temp_v0;
    s16 temp_a1;
    s32 var_a0;

    temp_a1 = arg0;
    arg0 = -temp_a1;
    if (temp_a1 >= 0) {
        arg0 = temp_a1;
    }
    temp_v0 = func_150485E0(arg0, temp_a1);
    var_a0 = temp_v0;
    if (temp_a1 < 0) {
        var_a0 = 0xFFFF - temp_v0;
    }
    return var_a0 & 0xFFFF;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15048664 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_75A90/func_15048664.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150486B8 CURRENT (720) */
s16 func_150486B8(s32 arg0) {
    s32 temp_v0;
    s16 temp_a1;
    s32 var_a0;

    temp_a1 = arg0;
    arg0 = -temp_a1;
    if (temp_a1 >= 0) {
        arg0 = temp_a1;
    }
    temp_v0 = func_150485E0(arg0, temp_a1);
    var_a0 = temp_v0 - 0x8000;
    if (temp_a1 >= 0) {
        var_a0 = 0x7FFF - temp_v0;
    }
    return var_a0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150486B8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_75A90/func_150486B8.s")
