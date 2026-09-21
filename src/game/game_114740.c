#include "types.h"

/*
 * Reviewed source unit: src/game/game_114740.c
 * Boundary evidence: docs/evidence/game_raw_direct_helper_pairs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E7290
 * - func_150E75A0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_114740/func_150E7290.s")
typedef struct {
    u8 sp28;
    u8 pad29[3];
    s32 source[2];
    f32 sp34;
    f32 sp38;
    u8 sp3C;
    u8 pad3D;
    s16 sp3E;
    s16 sp40;
    s16 sp42;
    s16 sp44;
    s8 sp46;
    s8 sp47;
    s8 sp48;
    s8 sp49;
    u8 sp4A;
    s8 sp4B;
    s8 sp4C;
    s8 sp4D;
    s8 sp4E;
    u8 sp4F;
    s32 sp50;
    s32 sp54;
    s32 sp58;
    s32 sp5C;
    s32 sp60;
    s32 sp64;
    s32 sp68;
    s8 sp6C;
    s8 sp6D;
    u8 pad6E[0x1A];
} Game114740Local;

void func_1515548C(void *, s32, s32, s32, s32, s32, s32);
extern u8 D_80088A64;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E75A0 CURRENT (3476) */
void func_150E75A0(void *arg0, f32 arg1, s16 arg2, u8 arg3, u8 arg4,
                   u8 arg5, s16 arg6, s16 arg7, s32 arg8, s32 arg9,
                   u8 arg10, s32 arg11) {
    Game114740Local local;

    local.sp28 = D_80088A64;
    local.source[0] = *(s32 *)arg0;
    local.source[1] = *(s32 *)((u8 *)arg0 + 4);
    local.sp3C = local.sp28;
    local.sp40 = arg3 | 0x40;
    local.sp3E = arg2;
    local.sp4C = 0xFF;
    local.sp4D = 0xFF;
    local.sp44 = arg7;
    local.sp46 = 4;
    local.sp47 = 0xFF;
    local.sp48 = 0xE6;
    local.sp49 = 0xBE;
    local.sp4B = 0xFF;
    local.sp42 = arg6;
    local.sp4A = arg4;
    local.sp34 = arg1;
    local.sp38 = arg1;
    local.sp4E = 0xFF;
    local.sp50 = 1;
    local.sp54 = 0;
    local.sp58 = 0;
    local.sp6C = 0;
    local.sp6D = 0xA;
    local.sp5C = 7;
    local.sp60 = 0x3C;
    local.sp64 = 0x80;
    local.sp68 = 0x20;
    local.sp4F = arg5;
    func_1515548C(&local.source, 0, arg8, arg9, 0, arg10, arg11);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E75A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_114740/func_150E75A0.s")
