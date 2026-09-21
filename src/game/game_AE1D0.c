#include "types.h"

/*
 * Reviewed source unit: src/game/game_AE1D0.c
 * Boundary evidence: docs/evidence/game_raw_preserved_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15080D20
 * - func_1508108C
 * - func_1508114C
 * - func_15081574
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_AE1D0/func_15080D20.s")
extern u16 D_8009BD30;
extern u16 D_8009BD34;
extern u16 D_8009BD38;
extern u16 D_8009BD3C[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1508108C CURRENT (3770) */
s32 func_1508108C(void *arg0) {
    u8 value;
    s32 index;
    u16 *entry;

    value = *(u8 *)((u8 *)arg0 + 4);
    if (value == D_8009BD30) {
        return 0;
    }
    if (value == D_8009BD34) {
        return 1;
    }
    index = 3;
    if (value == D_8009BD38) {
        return 2;
    }
    entry = D_8009BD3C;
    do {
        if (value == entry[0]) {
            return index;
        }
        if (value == entry[2]) {
            return index + 1;
        }
        if (value == entry[4]) {
            return index + 2;
        }
        if (value == entry[6]) {
            return index + 3;
        }
        index += 4;
        entry += 8;
    } while (index != 0x17);
    return -1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1508108C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AE1D0/func_1508108C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AE1D0/func_1508114C.s")
s32 func_15080D20(s32, void *, u8, f32, f32, s32);
s32 func_1508108C(void *);
extern u8 D_800CC2D0;
extern u8 D_800D121C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15081574 CURRENT (555) */
s32 func_15081574(s32 arg0, f32 arg1, f32 arg2, void **arg3, s32 arg4,
                   s32 arg5) {
    u8 *var_s0;
    s32 temp_v0;
    s32 temp_v0_2;

    *arg3 = 0;
    var_s0 = &D_800CC2D0;
    do {
        if ((*(s32 *)(var_s0 + 0) != 0) &&
            (*(s32 *)(var_s0 + 0x1D4) != 0) &&
            (arg5 == var_s0[4])) {
            temp_v0_2 = func_1508108C(var_s0);
            if (temp_v0_2 != -1) {
                temp_v0 = func_15080D20(
                    arg0, var_s0,
                    *((u8 *)&D_8009BD30 + (temp_v0_2 * 4) + 2), arg1,
                    arg2, arg4);
                if (temp_v0 != 0) {
                    *arg3 = var_s0;
                    return temp_v0;
                }
            }
        }
        var_s0 += 0x32C;
    } while (var_s0 != &D_800D121C);
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15081574 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AE1D0/func_15081574.s")
