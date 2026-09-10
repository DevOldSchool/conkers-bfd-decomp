#include "types.h"

/*
 * Reviewed source unit: src/game/game_F3270.c
 * Boundary evidence: docs/evidence/game_raw_paired_owner_streams.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C5DC0
 * - func_150C5E0C
 * - func_150C5EFC
 * - func_150C5F40
 * - func_150C5F94
 * - func_150C60D8
 * - func_150C6460
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_F3270/func_150C5DC0.s")
u32 func_150ADA20(void *, s8);                      /* extern */
f32 func_150ADA68();                                /* extern */
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C5E0C CURRENT (1097) */
s8 func_150C5E0C(u8 *arg0) {
    s8 sp27;
    s8 var_a2;
    void *sp1C;
    s32 temp_a0;
    u8 *temp_v1;

    var_a2 = 1;
    temp_v1 = (void *)(arg0 + 0xB0);
    if (*(u8 *)((u8 *)arg0 + 0xB4) == 0) {
        var_a2 = 0;
    }
    *(s8 *)((u8 *)temp_v1 + 4) = 0;
    *(s16 *)((u8 *)temp_v1 + 0x14) = (s16) (*(s16 *)((u8 *)temp_v1 + 0x14) - D_800BE9E4);
    if (*(s16 *)((u8 *)temp_v1 + 0x14) < 0) {
        sp1C = temp_v1;
        sp27 = var_a2;
        *(s16 *)((u8 *)temp_v1 + 0x14) = (s16) ((func_150ADA20(arg0, var_a2) % (u32) (*(s16 *)((u8 *)temp_v1 + 0x18) + 1)) + *(s16 *)((u8 *)temp_v1 + 0x16));
        *(f32 *)((u8 *)temp_v1 + 0x10) = (f32) ((func_150ADA68() * *(f32 *)((u8 *)temp_v1 + 0xC)) + *(f32 *)((u8 *)temp_v1 + 8));
    }
    temp_a0 = *(s32 *)((u8 *)arg0 + 0x24);
    *(s32 *)((u8 *)arg0 + 0x24) = (s32) (temp_a0 + (s32) ((*(f32 *)((u8 *)temp_v1 + 0x10) - (f32) temp_a0) * *(f32 *)((u8 *)temp_v1 + 0x1C)));
    return var_a2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C5E0C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3270/func_150C5E0C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3270/func_150C5EFC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3270/func_150C5F40.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3270/func_150C5F94.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3270/func_150C60D8.s")
s32 func_150C63EC(void *arg0) {
    s32 var_v1;

    var_v1 = 1;
    if (*(u8 *)((u8 *)arg0 + 0x5C) == 0) {
        var_v1 = 0;
    }
    *(u8 *)((u8 *)arg0 + 0x5C) = 0U;
    return var_v1;
}
void func_151346EC(void);

void func_150C6410(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x58) + 0x58;
    *(s32 *)(temp_v0 + 4) = 0;
    func_151346EC();
}
void func_1513470C(void);

void func_150C6438(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x58) + 0x58;
    *(s32 *)(temp_v0 + 4) = 0;
    func_1513470C();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3270/func_150C6460.s")
