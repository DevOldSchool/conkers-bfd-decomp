#include "types.h"

/*
 * Reviewed source unit: src/game/game_F3BA0.c
 * Boundary evidence: docs/evidence/game_raw_paired_owner_streams.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C66F0
 * - func_150C673C
 * - func_150C682C
 * - func_150C6870
 * - func_150C68C4
 * - func_150C6A08
 * - func_150C6D90
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_150C6D90();                                  /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C66F0 CURRENT (165) */
void func_150C66F0(void *arg0) {
    void *temp_v0;

    if (*(s32 *)((u8 *)arg0 + 0x6C) != 0) {
        temp_v0 = *(void **)((u8 *)arg0 + 0x6C);
        temp_v0 = (void *)((u8 *)temp_v0 + 0xB0);
        *(s8 *)((u8 *)temp_v0 + 4) = 1;
    } else {
        *(s32 *)((u8 *)arg0 + 0x6C) = func_150C6D90();
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C66F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3BA0/func_150C66F0.s")

u32 func_150ADA20(void *, s8);                      /* extern */
f32 func_150ADA68();                                /* extern */
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C673C CURRENT (1097) */
s8 func_150C673C(u8 *arg0) {
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
#endif /* CONKER_DEFERRED_CANDIDATE func_150C673C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3BA0/func_150C673C.s")
extern void func_1513F6C0(void *arg0, s32 arg1, s32 arg2);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C682C CURRENT (100) */
s32 func_150C682C(void *arg0) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *) arg0 + 0xB0);
    *(s32 *)((u8 *) temp_v0 + 0x6C) = 0;
    *(void **)((u8 *) arg0 + 0xB0) = 0;
    temp_v0 = (u8 *) temp_v0 + 0x58;
    *(s32 *)((u8 *) arg0 + 0x18) |= 2;
    func_1513F6C0(arg0, 0, 0);
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C682C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3BA0/func_150C682C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3BA0/func_150C6870.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3BA0/func_150C68C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3BA0/func_150C6A08.s")
s32 func_150C6D1C(void *arg0) {
    s32 var_v1;

    var_v1 = 1;
    if (*(u8 *)((u8 *)arg0 + 0x5C) == 0) {
        var_v1 = 0;
    }
    *(u8 *)((u8 *)arg0 + 0x5C) = 0U;
    return var_v1;
}
void func_151346EC(void);

void func_150C6D40(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x58) + 0x58;
    *(s32 *)(temp_v0 + 0x18) = 0;
    func_151346EC();
}
void func_1513470C(void);

void func_150C6D68(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x58) + 0x58;
    *(s32 *)(temp_v0 + 0x18) = 0;
    func_1513470C();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_F3BA0/func_150C6D90.s")
