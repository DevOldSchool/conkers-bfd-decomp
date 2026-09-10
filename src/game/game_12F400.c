#include "types.h"

/*
 * Reviewed source unit: src/game/game_12F400.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15101F50
 * - func_151022AC
 * - func_151025F4
 * - func_151026BC
 * - func_151027E8
 * - func_1510281C
 * - func_151028AC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_12F400/func_15101F50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_12F400/func_151022AC.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151025F4 CURRENT (2343) */
s32 func_151025F4(u8 *arg0, s32 arg1) {
    f32 sp24;
    f32 temp_ft3;
    u8 *temp_s0;

    sp24 = func_15047D60(*(f32 *)((u8 *)arg0 + 0xC0));
    temp_s0 = (void *)(arg0 + 0xA8);
    temp_ft3 = *(f32 *)((u8 *)temp_s0 + 0xC) + (*(f32 *)((u8 *)temp_s0 + 0x14) * func_15047D60(*(f32 *)((u8 *)arg0 + 0xC4)));
    *(f32 *)((u8 *)arg0 + 0xA8) = (f32) (*(f32 *)((u8 *)temp_s0 + 8) + (*(f32 *)((u8 *)temp_s0 + 0x10) * sp24));
    *(f32 *)((u8 *)temp_s0 + 4) = temp_ft3;
    *(f32 *)((u8 *)temp_s0 + 0x18) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x18) + (*(f32 *)((u8 *)temp_s0 + 0x20) * D_800BE9A4));
    *(f32 *)((u8 *)temp_s0 + 0x1C) = (f32) (*(f32 *)((u8 *)temp_s0 + 0x1C) + (*(f32 *)((u8 *)temp_s0 + 0x24) * D_800BE9A4));
    *(f32 *)((u8 *)temp_s0 + 0x18) = func_15144B68(*(f32 *)((u8 *)temp_s0 + 0x18));
    *(f32 *)((u8 *)temp_s0 + 0x1C) = func_15144B68(*(f32 *)((u8 *)temp_s0 + 0x1C));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151025F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12F400/func_151025F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_12F400/func_151026BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_12F400/func_151027E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_12F400/func_1510281C.s")
s32 func_15102884(void *arg0, s32 arg1) {
    if (!(*(u8 *)((u8 *)arg0 + 0xAC) & 1)) {
        return 0;
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_12F400/func_151028AC.s")
