#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D6E80.c
 * Boundary evidence: docs/evidence/game_raw_callback_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A99D0
 * - func_151A9AA4
 * - func_151A9BA0
 * - func_151A9CA0
 * - func_151A9DC0
 * - func_151A9EC0
 * - func_151A9FC8
 * - func_151AA09C
 * - func_151AA17C
 * - func_151AA210
 * - func_151AA264
 * - func_151AA30C
 * - func_151AA48C
 * - func_151AA5A4
 * - func_151AA6D8
 * - func_151AAA4C
 * - func_151AAABC
 * - func_151AAB50
 * - func_151AAB78
 * - func_151AABC4
 * - func_151AADBC
 * - func_151AADF8
 * - func_151AB090
 * - func_151AB180
 * - func_151AB1C4
 * - func_151AB2C4
 * - func_151AB3A4
 * - func_151AB6B8
 * - func_151AB788
 * - func_151AB7D8
 * - func_151AB828
 * - func_151AB854
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151A99D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151A9AA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151A9BA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151A9CA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151A9DC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151A9EC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151A9FC8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AA09C.s")
void func_151AA170(s32 arg0) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AA17C.s")
void func_151AA1D0(void) {
    func_1519F400();
}
void func_151AA1F0(void) {
    func_1519F400();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AA210.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AA264.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AA30C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AA48C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AA5A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AA6D8.s")
/* Call context: func_151423D8: unique active project prototype */
f32 func_151423D8(u8);
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AAA4C CURRENT (900) */
f32 func_151AAA4C(u8 *arg0) {
    f32 temp_fv1;

    temp_fv1 = (func_151423D8((((u32) *(u32 *)((u8 *)arg0 + 0x88) >> 0x10) - 0x40) & 0xFF) * *(f32 *)((u8 *)arg0 + 0x94)) + *(f32 *)((u8 *)arg0 + 0x90);
    *(s32 *)((u8 *)(arg0 + 0x80) + 8) = (s32) (*(u32 *)((u8 *)arg0 + 0x88) + (*(s32 *)((u8 *)arg0 + 0x8C) * D_800BE9E4));
    return temp_fv1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AAA4C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AAA4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AAABC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AAB50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AAB78.s")
s32 func_151AABA0(void *arg0) {
    s32 var_v1;

    var_v1 = 1;
    if (*(u8 *)((u8 *)arg0 + 0x84) == 0) {
        var_v1 = 0;
    }
    *(u8 *)((u8 *)arg0 + 0x84) = 0U;
    return var_v1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AABC4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AADBC CURRENT (130) */
s32 func_151AADBC(void *arg0) {
    s32 temp_t6;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    temp_t6 = *(s16 *)((u8 *)arg0 + 0x1C) * 0x10;
    {
        s32 var_v1 = temp_t6;
    if (temp_t6 >= 0x100) {
        var_v1 = 0xFF;
    }
    if (var_v1 < (s32) *(u8 *)((u8 *)temp_v0 + 0x1B)) {
        *(u8 *)((u8 *)temp_v0 + 0x1B) = (u8) var_v1;
    }
    return 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AADBC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AADBC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AADF8.s")
u32 func_150ADA20(void *, s8);                      /* extern */
f32 func_150ADA68();                                /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AB090 CURRENT (1097) */
s8 func_151AB090(u8 *arg0) {
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
#endif /* CONKER_DEFERRED_CANDIDATE func_151AB090 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AB090.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AB180.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AB1C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AB2C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AB3A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AB6B8.s")
/* Call context: func_100111C8: unique active project prototype */
/* Call context: func_151346EC: unique active project prototype */
void func_100111C8(s32, u16);
void func_151346EC(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AB788 CURRENT (690) */
void func_151AB788(void *arg0) {
    void *sp18;
    void *temp_v0;

    temp_v0 = (void *)(*(s32 *)((u8 *)arg0 + 0x58) + 0x58);
    if (*(u16 *)((u8 *)arg0 + 0x5E) != 0) {
        sp18 = temp_v0;
        func_100111C8((s32) *(u16 *)((u8 *)arg0 + 0x5E), (u16) arg0);
    }
    *(s32 *)((u8 *)temp_v0 + 0x1C) = 0;
    func_151346EC();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AB788 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AB788.s")
/* Call context: func_100111C8: unique active project prototype */
/* Call context: func_1513470C: unique active project prototype */
void func_1513470C(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151AB7D8 CURRENT (690) */
void func_151AB7D8(void *arg0) {
    void *sp18;
    void *temp_v0;

    temp_v0 = (void *)(*(s32 *)((u8 *)arg0 + 0x58) + 0x58);
    if (*(u16 *)((u8 *)arg0 + 0x5E) != 0) {
        sp18 = temp_v0;
        func_100111C8((s32) *(u16 *)((u8 *)arg0 + 0x5E), (u16) arg0);
    }
    *(s32 *)((u8 *)temp_v0 + 0x1C) = 0;
    func_1513470C();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151AB7D8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AB7D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AB828.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D6E80/func_151AB854.s")
void func_151AB920(s32 arg0, s32 arg1) {
}
