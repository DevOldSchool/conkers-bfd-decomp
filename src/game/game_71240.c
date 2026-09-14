#include "types.h"

/*
 * Reviewed source unit: src/game/game_71240.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15043D90
 * - func_15043E68
 * - func_15043F6C
 * - func_15043FF0
 * - func_150440A0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_71240/func_15043D90.s")
void func_150A8050(void *, f32, f32, s32);
void func_150A7790(void *, s32);

typedef struct {
    u8 unk0[0x30];
    f32 unk30;
    f32 unk34;
    f32 unk38;
} Game71240Work;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15043E68 CURRENT (4562) */
void func_15043E68(s32 arg0, f32 arg1, f32 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    Game71240Work sp18;

    func_150A8050(&sp18, arg1, arg2, arg3);
    sp18.unk30 = arg4;
    sp18.unk34 = arg5;
    sp18.unk38 = arg6;
    func_150A7790(&sp18, arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15043E68 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71240/func_15043E68.s")
void func_15043EC8(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    *(f32 *)((u8 *)arg0 + 0x30) = arg4;
    *(f32 *)((u8 *)arg0 + 0x34) = arg5;
    *(f32 *)((u8 *)arg0 + 0x38) = arg6;
    *(f32 *)((u8 *)arg0 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) * arg1);
    *(f32 *)((u8 *)arg0 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) * arg1);
    *(f32 *)((u8 *)arg0 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) * arg1);
    *(f32 *)((u8 *)arg0 + 0x10) = (f32) (*(f32 *)((u8 *)arg0 + 0x10) * arg2);
    *(f32 *)((u8 *)arg0 + 0x14) = (f32) (*(f32 *)((u8 *)arg0 + 0x14) * arg2);
    *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) * arg2);
    *(f32 *)((u8 *)arg0 + 0x20) = (f32) (*(f32 *)((u8 *)arg0 + 0x20) * arg3);
    *(f32 *)((u8 *)arg0 + 0x24) = (f32) (*(f32 *)((u8 *)arg0 + 0x24) * arg3);
    *(f32 *)((u8 *)arg0 + 0x28) = (f32) (*(f32 *)((u8 *)arg0 + 0x28) * arg3);
}
void func_150A9B0C(void *, f32, f32, s32, f32, f32, f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15043F6C CURRENT (745) */
void func_15043F6C(Game71240Work *arg0, f32 arg1, f32 arg2, s32 arg3,
                   f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9) {
    s32 temp_a3;

    temp_a3 = arg3;
    func_150A9B0C(arg0, arg1, arg2, temp_a3, arg4, arg5, arg6);
    arg0->unk30 = arg7;
    arg0->unk34 = arg8;
    *(f32 *)((u8 *)arg0 + 0xC) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x1C) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x2C) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x3C) = 1.0f;
    arg0->unk38 = arg9;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15043F6C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71240/func_15043F6C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15043FF0 CURRENT (710) */
void func_15043FF0(void *arg0, void *arg1) {
    *(f32 *)((u8 *)arg0 + 0) = (f32) *(s16 *)((u8 *)arg1 + 0x18);
    *(f32 *)((u8 *)arg0 + 4) = (f32) *(s16 *)((u8 *)arg1 + 0x1A);
    *(f32 *)((u8 *)arg0 + 8) = (f32) *(s16 *)((u8 *)arg1 + 0x1C);
    *(f32 *)((u8 *)arg0 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) + ((f32) *(s16 *)((u8 *)arg1 + 0x38) * 0.000015258789f));
    *(f32 *)((u8 *)arg0 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) + ((f32) *(s16 *)((u8 *)arg1 + 0x3A) * 0.000015258789f));
    *(f32 *)((u8 *)arg0 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) + ((f32) *(s16 *)((u8 *)arg1 + 0x3C) * 0.000015258789f));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15043FF0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71240/func_15043FF0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_71240/func_150440A0.s")
