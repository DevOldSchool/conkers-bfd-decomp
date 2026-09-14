#include "types.h"

/*
 * Reviewed source unit: src/game/game_1EF500.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151C2050
 * - func_151C229C
 * - func_151C2734
 * - func_151C2AD0
 * - func_151C2F48
 * - func_151C329C
 * - func_151C36D8
 * - func_151C3B0C
 * - func_151C436C
 * - func_151C43E0
 * - func_151C4510
 * - func_151C455C
 * - func_151C4644
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C2050.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C229C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C2734.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C2AD0.s")
s32 func_151C2E4C(void *arg0, void *arg1) {
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
s32 func_151C2E94(void *arg0, void *arg1) {
    if (arg0 == arg1) {
        return 0;
    }
    if (*(s32 *)((u8 *)arg0 + 0) == 0) {
        return 0;
    }
    if (*(u8 *)((u8 *)arg0 + 4) == 0xFF) {
        return 0;
    }
    if (*(u8 *)((u8 *)arg0 + 0x127) == 0xFF) {
        return 0;
    }
    return 1;
}
void func_151D4DAC(s32, s32, s32, s32, s32, s32, void *, s32, s32);

void func_151C2EF0(s32 arg0, s32 arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_151D4DAC(arg0, arg1, arg3, arg4, arg5, *(s32 *)((u8 *)arg2 + 0x1B4), (u8 *)arg2 + 0x170, *(u8 *)((u8 *)arg2 + 0xC), *(u8 *)((u8 *)arg2 + 1));
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C2F48.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C329C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C36D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C3B0C.s")
extern f32 D_800AAA7C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C436C CURRENT (19910) */
void func_151C436C(s32 arg0, void *arg1, s32 arg2) {
    f32 temp_fa0;
    f32 temp_ft4;
    f32 temp_fv0;
    s32 var_a2;

    var_a2 = arg2;
    if (var_a2 > 0) {
        do {
            temp_fv0 = *(f32 *)((u8 *)arg1 + 0x10);
            temp_fa0 = *(f32 *)((u8 *)arg1 + 0x14);
            temp_ft4 = *(f32 *)((u8 *)arg1 + 0x18);
            var_a2 -= 1;
            *(f32 *)((u8 *)arg1 + 0x10) = (f32) (temp_fv0 + ((*(f32 *)((u8 *)arg1 + 0x1C) - temp_fv0) * D_800AAA7C));
            *(f32 *)((u8 *)arg1 + 0x14) = (f32) (temp_fa0 + ((*(f32 *)((u8 *)arg1 + 0x20) - temp_fa0) * D_800AAA7C));
            *(f32 *)((u8 *)arg1 + 0x18) = (f32) (temp_ft4 + ((*(f32 *)((u8 *)arg1 + 0x24) - temp_ft4) * D_800AAA7C));
        } while (var_a2 > 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C436C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C436C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C43E0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C4510 CURRENT (490) */
void func_151C4510(void *arg0, void *arg1, f32 arg2) {
    *(f32 *)((u8 *)arg0 + 0x34) = (f32) (*(f32 *)((u8 *)arg0 + 0x34) + (*(f32 *)((u8 *)arg1 + 4) * arg2));
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)arg0 + 0x38) + (*(f32 *)((u8 *)arg1 + 8) * arg2));
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C) + (*(f32 *)((u8 *)arg1 + 0xC) * arg2));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C4510 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C4510.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C455C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C4644.s")
