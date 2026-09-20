#include "types.h"

/*
 * Reviewed source unit: src/game/game_1BDC20.c
 * Boundary evidence: docs/evidence/game_raw_owner_particle_lifecycle.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15190770
 * - func_15190898
 * - func_15190F9C
 * - func_1519108C
 * - func_15191400
 * - func_15191520
 * - func_151918BC
 * - func_15191980
 * - func_15191A84
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);
void func_100226F0(void *, s32);
void *func_15167A68(s32, s32, s32, s32, u8, u8);
void func_15191B8C(s32, u8);
u8 func_151D8E20(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15190770 CURRENT (630) */
void *func_15190770(void *arg0, s32 arg1, u8 arg2, u8 arg3) {
    struct {
        void *field_0;
        u8 field_4;
    } data;
    void *source;

    source = arg0;
    data.field_0 = *(void **)source;
    data.field_4 = *(u8 *)((u8 *)data.field_0 + 0x3B);
    func_15191B8C((s32)&data, 0xE);
    arg0 = func_15167A68(0x20, arg3, arg1 + 0x300, 1, arg2, 1);
    if (arg0 == 0) {
        return 0;
    }
    func_10022EC0((u8 *)arg0 + 0x10, source, 0xC);
    *(void **)((u8 *)arg0 + 0x24) = (u8 *)arg0 + 0x30;
    *(void **)((u8 *)arg0 + 0x28) = (u8 *)arg0 + 0x300;
    *(s32 *)((u8 *)arg0 + 0x20) = 0;
    *(f32 *)((u8 *)arg0 + 0x1C) = 0.0f;
    func_100226F0((u8 *)arg0 + 0x30, 0x2D0);
    *(u8 *)((u8 *)arg0 + 0x2C) = func_151D8E20();
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15190770 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDC20/func_15190770.s")
void func_15190840(s32 arg0) {
    func_15191400(arg0);
    func_15169804(arg0);
}
void func_15169824(s32 arg0);

void func_1519086C(s32 arg0) {
    func_15191400(arg0);
    func_15169824(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDC20/func_15190898.s")
/* Call context: func_151423D8: unique active project prototype */
f32 func_151423D8(u8);
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15190F9C CURRENT (917) */
s32 func_15190F9C(u8 *arg0) {
    f32 sp24;
    void *sp1C;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    u8 temp_a0;
    u8 *temp_v1;

    temp_a0 = *(u8 *)((u8 *)arg0 + 0x131) + (*(s8 *)((u8 *)arg0 + 0x133) * D_800BE9E4);
    *(u8 *)((u8 *)arg0 + 0x131) = temp_a0;
    *(u8 *)((u8 *)arg0 + 0x132) = (u8) (*(u8 *)((u8 *)arg0 + 0x132) + (*(s8 *)((u8 *)arg0 + 0x134) * D_800BE9E4));
    sp24 = func_151423D8((temp_a0 - 0x40) & 0xFF);
    temp_v1 = (void *)(arg0 + 0x110);
    sp1C = temp_v1;
    temp_fv0 = func_151423D8((*(u8 *)((u8 *)temp_v1 + 0x22) - 0x40) & 0xFF);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x2C);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x30);
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (temp_fv1 + (((*(f32 *)((u8 *)temp_v1 + 0x28) + (*(f32 *)((u8 *)temp_v1 + 0x30) * sp24)) - temp_fv1) * 0.5f));
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (temp_fa0 + (((*(f32 *)((u8 *)temp_v1 + 0x2C) + (*(f32 *)((u8 *)temp_v1 + 0x34) * temp_fv0)) - temp_fa0) * 0.5f));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15190F9C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDC20/func_15190F9C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDC20/func_1519108C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDC20/func_15191400.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDC20/func_15191520.s")
s32 func_1519187C(void *arg0) {
    s16 temp_v0;
    s32 temp_lo;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    if (temp_v0 < *(s16 *)((u8 *)arg0 + 0x124)) {
        temp_lo = temp_v0;
        temp_lo *= *(s16 *)((u8 *)arg0 + 0x126);
        if (temp_lo < (s32) *(u8 *)((u8 *)arg0 + 0x5C)) {
            *(u8 *)((u8 *)arg0 + 0x5C) = (u8) temp_lo;
        }
    }
    return 1;
}
void func_1516972C(void *);
void *func_15190770(void *, s32, u8, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151918BC CURRENT (895) */
void func_151918BC(void *arg0) {
    u8 sp27;
    s32 var_v0;
    u8 *temp_a0;
    u8 *temp_v1;

    temp_v1 = *(u8 **)((u8 *)arg0 + 0x28);
    var_v0 = 0;
    if (*(s32 *)temp_v1 == 0) {
        var_v0 = 1;
    } else if (*(u8 *)((u8 *)arg0 + 0x2C) != *(u8 *)(temp_v1 + 0x3B)) {
        var_v0 = 1;
    }
    if ((var_v0 == 0) && (*(s32 *)(temp_v1 + 0x1D4) != 0)) {
        temp_a0 = (u8 *)arg0 + 0x28;
        if ((*(u8 *)((u8 *)arg0 + 0xD) & 1) != 0) {
            *(u8 *)(temp_a0 + 8) |= 1;
            *(s16 *)(temp_a0 + 6) = *(s16 *)((u8 *)arg0 + 0xE);
        } else {
            *(s16 *)(temp_a0 + 6) = 0x12C;
        }
        sp27 = 1;
        func_15190770(temp_a0, 0, *(u8 *)((u8 *)arg0 + 0xC), *(u8 *)((u8 *)arg0 + 1));
        var_v0 = sp27;
    }
    if (var_v0 != 0) {
        func_1516972C(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151918BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDC20/func_151918BC.s")
void func_15169850(s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15191980 CURRENT (2074) */
void func_15191980(void *arg0, void *arg1, u8 arg2) {
    void *temp_s0;

    temp_s0 = arg0;
    if (arg2 == 0xD) {
        if ((*(s32 *)((u8 *)temp_s0 + 0x10) == *(s32 *)arg1) ||
            (*(u8 *)((u8 *)temp_s0 + 0x14) == *(u8 *)((u8 *)arg1 + 4))) {
            *(s16 *)((u8 *)temp_s0 + 0x16) = 0x64;
            *(u8 *)((u8 *)temp_s0 + 0x18) |= 1;
        }
    } else if ((arg2 == 0xC) || (arg2 == 0x50) || (arg2 == 0xE)) {
        if ((*(s32 *)((u8 *)temp_s0 + 0x10) == *(s32 *)arg1) ||
            (*(u8 *)((u8 *)temp_s0 + 0x14) == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C(temp_s0);
        }
    } else {
        if (arg2 == 0x4E) {
            func_1516972C(temp_s0);
            return;
        }
        func_15169850((s32)arg1, (s32)arg2, (s32)((u8 *)temp_s0 + 0x10),
                      (s32)((u8 *)temp_s0 + 0x14), (s32)temp_s0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15191980 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDC20/func_15191980.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BDC20/func_15191A84.s")
void func_151494E0(s32, u8);
void func_15169260(s32 *, s32, s32, u8);
extern s32 D_800A8010;

void func_15191B8C(s32 arg0, u8 arg1) {
    s32 sp1C;

    sp1C = D_800A8010;
    func_151494E0(arg0, arg1);
    func_15169260(&sp1C, 1, arg0, arg1);
}
