#include "types.h"

/*
 * Reviewed source unit: src/game/game_1F3780.c
 * Boundary evidence: docs/evidence/game_raw_model_anchor_owner_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151C62D0
 * - func_151C69CC
 * - func_151C6A28
 * - func_151C6D70
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1F3780/func_151C62D0.s")
void func_151C69CC();

void func_151C6974(s32 arg0, s32 arg1, s32 arg2) {
    func_151C69CC(arg0, arg2, 0, arg2);
}
void func_151C69A0(s32 arg0, s32 arg1, s32 arg2) {
    func_151C69CC(arg0, arg2, 1, arg2);
}
void func_15143134(f32 *, f32 *, s32);
void func_15102B38(s32, u8, s32, s32, f32 *, s32, s32, f32, s32,
                   s32, s32, s32, s32, s32);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
extern s32 D_800AAB00[];
extern f32 D_800AAB08[];
extern u8 D_800AAB20[];
extern f32 D_800AAC10;
extern f32 D_800AAC14;
extern f32 D_800AAC18;
extern f32 D_800AAC1C;
extern f32 D_800AAC20;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C69CC CURRENT (380) */
void func_151C69CC(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a3;

    temp_a3 = arg2 & 0xFF;
    func_15143134((f32 *)((u8 *)D_800AAB08 + (temp_a3 * 0xC)), (f32 *)arg1,
                   D_800AAB00[temp_a3] + *(s32 *)((u8 *)arg0 + 0x1D4));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C69CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1F3780/func_151C69CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1F3780/func_151C6A28.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C6D70 CURRENT (496) */
void func_151C6D70(s32 arg0, u8 arg1, s32 arg2, s16 arg3, u8 arg4,
                   s32 arg5) {
    struct {
        u32 sp44;
        u32 sp48;
        u32 pad4C;
        f32 sp50[2];
    } locals;
    s32 temp_v0;

    locals.sp50[1] = (func_150ADA68() * D_800AAC10) + D_800AAC14;
    locals.sp50[0] = (func_150ADA68() * D_800AAC18) + D_800AAC1C;
    locals.sp44 = func_150ADA20();
    locals.sp48 = func_150ADA20();
    temp_v0 = arg1 * 0xC;
    func_15102B38(arg0, ((u32)D_800AAB00[arg1] >> 6) & 0xFF,
                  (s32)((u8 *)D_800AAB08 + temp_v0),
                  (s32)(D_800AAB20 + temp_v0), locals.sp50,
                  (locals.sp44 & 3) + 6,
                  0xFF, (func_150ADA68() * 270.0f) + D_800AAC20,
                  arg2, 0xFF, 0, arg3, arg4, arg5);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C6D70 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1F3780/func_151C6D70.s")
