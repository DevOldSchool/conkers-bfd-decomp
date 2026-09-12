#include "types.h"

/*
 * Reviewed source unit: src/game/game_16DC80.c
 * Boundary evidence: docs/evidence/game_state_callback_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151407D0
 * - func_151408A4
 * - func_151411E4
 * - func_15141250
 * - func_151412BC
 * - func_1514143C
 * - func_15141478
 * - func_15141564
 * - func_151415D4
 * - func_151416E8
 * - func_151417C4
 * - func_1514182C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_151407D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_151408A4.s")
void func_151411A4(void) {
    func_1513CA6C();
}
void func_151411C4(void) {
    func_1513CAA0();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_151411E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_15141250.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_151412BC.s")
typedef struct Game16DC80Inner {
    u8 pad0[0x44];
    void *field_44;
} Game16DC80Inner;

typedef struct Game16DC80Object {
    u8 pad0[0x110];
    Game16DC80Inner inner;
} Game16DC80Object;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514143C CURRENT (160) */
void func_1514143C(Game16DC80Object *arg0) {
    Game16DC80Inner *temp_v0;
    void *temp_v1;

    if (*(s32 *)((u8 *)arg0 + 0x154) != 0) {
        temp_v0 = &arg0->inner;
        temp_v1 = temp_v0->field_44;
        *(f32 *)((u8 *)temp_v1 + 0) = *(f32 *)((u8 *)arg0 + 0x34);
        temp_v1 = temp_v0->field_44;
        *(f32 *)((u8 *)temp_v1 + 4) = *(f32 *)((u8 *)arg0 + 0x38);
        temp_v1 = temp_v0->field_44;
        *(f32 *)((u8 *)temp_v1 + 8) = *(f32 *)((u8 *)arg0 + 0x3C);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514143C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_1514143C.s")
s32 func_150ADA20();                                /* extern */
f32 func_150ADA68();                                /* extern */
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15141478 CURRENT (2297) */
s32 func_15141478(u8 *arg0) {
    void *sp24;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fv1_2;
    u8 *temp_a0;
    u8 *temp_v1;
    u8 *temp_v1_2;

    *(f32 *)((u8 *)arg0 + 0x180) = (f32) (*(f32 *)((u8 *)arg0 + 0x180) - D_800BE9A4);
    if (*(f32 *)((u8 *)arg0 + 0x180) < 0.0f) {
        temp_v1 = (void *)(arg0 + 0x170);
        *(f32 *)((u8 *)temp_v1 + 0x10) = (f32) (func_150ADA68() * *(f32 *)((u8 *)temp_v1 + 0x14));
        sp24 = temp_v1;
        if (func_150ADA20() & 3) {
            sp24 = temp_v1;
            temp_fv1 = *(f32 *)((u8 *)temp_v1 + 4);
            *(f32 *)((u8 *)temp_v1 + 0xC) = (f32) ((func_150ADA68() * (*(f32 *)((u8 *)arg0 + 0x170) - temp_fv1)) + temp_fv1);
        } else {
            sp24 = temp_v1;
            temp_fv1_2 = *(f32 *)((u8 *)arg0 + 0x170);
            *(f32 *)((u8 *)temp_v1 + 0xC) = (f32) ((func_150ADA68() * (*(f32 *)((u8 *)temp_v1 + 8) - temp_fv1_2)) + temp_fv1_2);
        }
    }
    temp_a0 = (void *)(arg0 + 0x110);
    temp_v1_2 = (void *)(arg0 + 0x170);
    temp_fv0 = *(f32 *)((u8 *)temp_a0 + 0x48);
    *(f32 *)((u8 *)temp_a0 + 0x48) = (f32) (temp_fv0 + ((*(f32 *)((u8 *)temp_v1_2 + 0xC) - temp_fv0) * *(f32 *)((u8 *)temp_v1_2 + 0x18)));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15141478 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_15141478.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32, void *);                     /* extern */
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15141564 CURRENT (73) */
s32 func_15141564(u8 *arg0) {
    void *sp18;
    u8 *temp_v1;

    temp_v1 = (void *)(arg0 + 0x170);
    *(f32 *)((u8 *)arg0 + 0x158) = (f32) (*(f32 *)((u8 *)arg0 + 0x170) + (*(f32 *)((u8 *)temp_v1 + 4) * func_15047D60(*(f32 *)((u8 *)arg0 + 0x178))));
    *(f32 *)((u8 *)temp_v1 + 8) = (f32) (*(f32 *)((u8 *)temp_v1 + 8) + (*(f32 *)((u8 *)temp_v1 + 0xC) * D_800BE9A4));
    sp18 = temp_v1;
    *(f32 *)((u8 *)temp_v1 + 8) = func_15144B68(*(f32 *)((u8 *)temp_v1 + 8), arg0);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15141564 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_15141564.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151415D4 CURRENT (685) */
s32 func_151415D4(u8 *arg0) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_ft2;
    u8 *var_v0;

    var_v0 = (void *)(arg0 + 0x170);
    if (*(f32 *)((u8 *)arg0 + 0x17C) < *(f32 *)((u8 *)arg0 + 0x180)) {
        var_v0 = (void *)(arg0 + 0x170);
        var_ft2 = *(f32 *)((u8 *)var_v0 + 4);
        goto block_7;
    }
    temp_fv1 = *(f32 *)((u8 *)var_v0 + 0xC);
    if (temp_fv1 < *(f32 *)((u8 *)var_v0 + 0x14)) {
        *(f32 *)((u8 *)arg0 + 0x158) = (f32) (*(f32 *)((u8 *)var_v0 + 4) + (*(f32 *)((u8 *)var_v0 + 8) * ((temp_fv1 - *(f32 *)((u8 *)var_v0 + 0x10)) * *(f32 *)((u8 *)var_v0 + 0x20))));
    } else {
        temp_fa0 = *(f32 *)((u8 *)var_v0 + 0x18);
        if (temp_fv1 < temp_fa0) {
            *(f32 *)((u8 *)arg0 + 0x158) = (f32) *(f32 *)((u8 *)arg0 + 0x170);
        } else {
            var_ft2 = *(f32 *)((u8 *)var_v0 + 4) + (*(f32 *)((u8 *)var_v0 + 8) * (1.0f - ((temp_fv1 - temp_fa0) * *(f32 *)((u8 *)var_v0 + 0x20))));
block_7:
            *(f32 *)((u8 *)arg0 + 0x158) = var_ft2;
        }
    }
    temp_fv0 = *(f32 *)((u8 *)var_v0 + 0x1C);
    *(f32 *)((u8 *)var_v0 + 0xC) = (f32) (*(f32 *)((u8 *)var_v0 + 0xC) + D_800BE9A4);
    if (temp_fv0 < *(f32 *)((u8 *)var_v0 + 0xC)) {
        do {
            *(f32 *)((u8 *)var_v0 + 0xC) = (f32) (*(f32 *)((u8 *)var_v0 + 0xC) - temp_fv0);
        } while (temp_fv0 < *(f32 *)((u8 *)var_v0 + 0xC));
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151415D4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_151415D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_151416E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_151417C4.s")
s32 func_15141818(s32 arg0, s32 arg1) {
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_16DC80/func_1514182C.s")
void func_1514182C(void *, void *, s32, s32, f32, f32);

s32 func_15141928(void *arg0) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x178);
    func_1514182C(arg0,
                  (u8 *)arg0 + 0x17C,
                  *(s32 *)((u8 *)arg0 + 0x170),
                  *(s32 *)((u8 *)arg0 + 0x174),
                  *(f32 *)((u8 *)temp_v0 + 0),
                  *(f32 *)((u8 *)temp_v0 + 8));
    return 1;
}
