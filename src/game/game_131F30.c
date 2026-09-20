#include "types.h"

/*
 * Reviewed source unit: src/game/game_131F30.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15104A80
 * - func_15104C44
 * - func_15104FF8
 * - func_151050B0
 * - func_1510550C
 * - func_15105548
 * - func_1510558C
 * - func_15105848
 * - func_151058B4
 * - func_15105C24
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/func_15104A80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/func_15104C44.s")
void func_1000FA64(s32, s32, s32, s32, s32, s32, s32, void *, s32, s32, s32, s32);
void func_1000FD38(void *, void *, s32);
extern u8 D_1000EF40[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15104FF8 CURRENT (1548) */
void func_15104FF8(void *arg0, s32 arg1, s32 arg2) {
    void *sp40;
    u8 *sp3C;
    void *state;
    void *object;

    state = (u8 *)arg0 + 0x28;
    if ((arg2 & 0xFF) != 0x38) {
        return;
    }
    object = *(void **)state;
    if (*(u8 *)((u8 *)object + 0x14) != 1) {
        return;
    }
    *(s16 *)((u8 *)state + 8) = 0x12C;
    sp3C = D_1000EF40;
    sp40 = state;
    func_1000FD38(D_1000EF40, object, 0);
    object = *(void **)state;
    func_1000FA64(0x236,
                  *(s16 *)((u8 *)object + 0),
                  *(s16 *)((u8 *)object + 2),
                  *(s16 *)((u8 *)object + 4),
                  0x4000, 0x5DC, 0x3E8, sp3C,
                  (s32)object, 0, 8, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15104FF8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/func_15104FF8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/func_151050B0.s")
void func_1516972C(s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510550C CURRENT (577) */
void func_1510550C(s32 arg0, s32 arg1, s32 arg2) {
    arg2 = arg2 & 0xFF;
    if (arg2 == 0x4B) {
        func_1516972C(arg0, arg1, arg2);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510550C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/func_1510550C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15105548 CURRENT (410) */
void func_15105548(void *arg0, s32 *arg1, u8 arg2) {
    void *temp_v0;

    temp_v0 = (u8 *)arg0 + 0x28;
    if ((arg2 == 0x38) && (*(u8 *)((u8 *)(*(void **)temp_v0) + 0x14) == 1)) {
        *(s16 *)((u8 *)temp_v0 + 4) = 0x12C;
        *(s32 *)((u8 *)temp_v0 + 0x70) = *arg1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15105548 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/func_15105548.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/func_1510558C.s")

void func_151058B4(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15105848 CURRENT (210) */
void func_15105848(void *arg0, s32 arg1, u8 arg2) {
    void *part;

    if (arg2 == 0x38) {
        func_151058B4(arg0);
        arg0 = (u8 *)arg0 + 0x28;
        *(u8 *)((u8 *)arg0 + 0xC) = *(u8 *)((u8 *)arg0 + 0xC) | 1;
        return;
    }
    part = (u8 *)arg0 + 0x28;
    if (arg2 == 0x39) {
        *(u8 *)((u8 *)part + 0xC) = *(u8 *)((u8 *)part + 0xC) & ~1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15105848 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/func_15105848.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/func_151058B4.s")
void func_1508B20C(f32, f32, f32, s32);

void func_15105BC8(void *arg0) {
    void *temp_v0;

    if (*(u8 *)((u8 *)arg0 + 0x34) & 1) {
        temp_v0 = *(void **)((u8 *)arg0 + 0x28);
        func_1508B20C((f32)*(s16 *)temp_v0, (f32)*(s16 *)((u8 *)temp_v0 + 2),
                       (f32)*(s16 *)((u8 *)temp_v0 + 4), 0x43FA0000);
    }
}
extern s32 D_800A5770[];
extern u8 D_800DCE50[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15105C24 CURRENT (2160) */
void *func_15105C24(s32 arg0) {
    s32 temp_t4;
    s32 temp_t5;
    s32 var_v0;
    s32 var_v1;
    void *var_a0;

    var_v0 = 0;
loop_1:
    var_v1 = 0;
loop_2:
    var_a0 = *(void **)(D_800DCE50 + (var_v1 * 0x1A0) + (D_800A5770[var_v0] * 4));
    if (var_a0 != 0) {
loop_3:
        if ((*(u8 *)((u8 *)var_a0 + 0x13) == 0x2E) &&
            (arg0 == *(s32 *)((u8 *)var_a0 + 0x28))) {
            return var_a0;
        }
        var_a0 = *(void **)((u8 *)var_a0 + 8);
        if (var_a0 == 0) {
            goto block_7;
        }
        goto loop_3;
    }
block_7:
    temp_t4 = (var_v1 + 1) & 0xFF;
    var_v1 = temp_t4;
    if (temp_t4 >= 2) {
        temp_t5 = (var_v0 + 1) & 0xFF;
        var_v0 = temp_t5;
        if (temp_t5 >= 2) {
            return 0;
        }
        goto loop_1;
    }
    goto loop_2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15105C24 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/func_15105C24.s")
