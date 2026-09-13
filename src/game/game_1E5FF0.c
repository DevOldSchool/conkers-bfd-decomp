#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E5FF0.c
 * Boundary evidence: docs/evidence/game_raw_preserved_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B8B40
 * - func_151B8C54
 * - func_151B8CFC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

f32 func_15047D60(f32);                             /* extern */
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B8B40 CURRENT (110) */
s32 func_151B8B40(void *arg0) {
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) ((func_15047D60(*(f32 *)((u8 *)arg0 + 0x44)) * *(f32 *)((u8 *)arg0 + 0x5C)) + *(f32 *)((u8 *)arg0 + 0x48));
    *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)arg0 + 0x44) + (*(f32 *)((u8 *)arg0 + 0x4C) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x44) = func_15144B68(*(f32 *)((u8 *)arg0 + 0x44), arg0);
    *(f32 *)((u8 *)arg0 + 0x20) = (f32) (*(f32 *)((u8 *)arg0 + 0x20) + (*(f32 *)((u8 *)arg0 + 0x50) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x28) = (f32) (*(f32 *)((u8 *)arg0 + 0x28) + (*(f32 *)((u8 *)arg0 + 0x58) * D_800BE9A4));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B8B40 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E5FF0/func_151B8B40.s")
typedef struct Game1E5FF0MotionState {
    u8 pad0[0x44];
    f32 field_44;
    u8 pad48[0x10];
    f32 field_58;
    f32 field_5C;
    f32 field_60;
    f32 field_64;
} Game1E5FF0MotionState;

s32 func_151D9450(s32, s32);

void func_151B8BE0(Game1E5FF0MotionState *arg0, s32 arg1) {
    arg0->field_44 = (func_15047D60(arg0->field_58) * arg0->field_64) +
                     arg0->field_5C;
    arg0->field_58 += arg0->field_60 * D_800BE9A4;
    arg0->field_58 = func_15144B68(arg0->field_58);
    func_151D9450((s32)arg0, arg1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E5FF0/func_151B8C54.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E5FF0/func_151B8CFC.s")
