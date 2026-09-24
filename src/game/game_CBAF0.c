#include "types.h"

/*
 * Reviewed source unit: src/game/game_CBAF0.c
 * Boundary evidence: docs/evidence/game_raw_descriptor_callback_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1509E640
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern void func_1001263C(s32 arg0, s32 arg1, s32 arg2);
extern void func_151F2D6C(s32 arg0, s32 arg1);
extern void func_151F2BA8(void);
extern s32 D_800D3840;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509E640 CURRENT (535) */
s32 func_1509E640(s32 arg0, s32 arg1, void *arg2) {
    s32 var_a1;

    switch (arg1) {
    case 0:
        var_a1 = 0x7FFF;
        if (D_800D3840 >= 3) {
            var_a1 = *(s32 *)((u8 *)arg2 + 8);
        }
        func_1001263C(arg0, var_a1, 0x40);
        return 1;
    case 1:
        if (D_800D3840 != 4) {
            func_151F2D6C(*(s32 *)((u8 *)arg2 + 8), 0);
            return 1;
        }
        func_151F2D6C(*(s32 *)((u8 *)arg2 + 8), *(s32 *)((u8 *)arg2 + 0xC));
        return 1;
    case 2:
        func_151F2BA8();
        return 1;
    default:
        return 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509E640 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CBAF0/func_1509E640.s")
s32 func_151F2CDC();                                /* extern */

s32 func_1509E6F0(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 3) {
        return func_151F2CDC() == 1;
    }
    return 0;
}
