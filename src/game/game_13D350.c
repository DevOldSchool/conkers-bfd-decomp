#include "types.h"

/*
 * Reviewed source unit: src/game/game_13D350.c
 * Boundary evidence: docs/evidence/game_raw_text_view_descriptor_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1510FEA0
 * - func_151102CC
 * - func_151103C8
 * - func_15110544
 * - func_15110600
 * - func_151106A8
 * - func_151108C4
 * - func_15110CFC
 * - func_1511172C
 * - func_15111858
 * - func_15111AF4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_1510FEA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_151102CC.s")
typedef struct Game13D350Record {
    u8 pad0[0xBC];
    u8 payload[0xC4];
} Game13D350Record;

extern Game13D350Record *D_800BE628;
void func_151102CC(void *, f32, f32, f32);
void func_150A7A48(void *, void *, void *);

void func_15110360(s32 arg0, void *arg1, f32 arg2, f32 arg3, f32 arg4) {
    func_151102CC(arg1, arg2, arg3, arg4);
    func_150A7A48(arg1, D_800BE628[arg0].payload, arg1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_151103C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_15110544.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_15110600.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_151106A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_151108C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_15110CFC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_1511172C.s")
/* Call context: func_10003C40: unique active project prototype */
void * func_10003C40(s32, s32, s32, s32);
f32 func_150AD780(f32);                             /* extern */
f32 func_150AD78C(f32);                             /* extern */
u32 func_150ADA20();                                /* extern */
extern f32 D_800A2F24;
extern f32 D_800A2F28;
extern f32 D_800A2F2C;
extern void *D_800DBE80;
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15111858 CURRENT (14900) */
void func_15111858(void) {
    f32 sp78;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_fs3;
    f32 temp_fv1;
    f32 var_fa0;
    f32 var_ft1;
    s32 temp_ft3;
    s32 var_s1;
    u32 temp_hi;
    void *temp_v0;
    u8 *var_s0;

    temp_v0 = func_10003C40(0xFA00, 1, 0, 0);
    D_800DBE80 = temp_v0;
    temp_fs3 = D_800A2F24;
    temp_fs2 = D_800A2F28;
    var_s1 = 0;
    var_s0 = temp_v0;
    do {
        temp_hi = func_150ADA20() % 36000U;
        var_ft1 = (f32) temp_hi;
        if ((s32) temp_hi < 0) {
            var_ft1 += 4294967296.0f;
        }
        temp_fs1 = var_ft1 * temp_fs2;
        temp_fv1 = (f32) ((func_150ADA20() % 1584400U) - 0xC1624) * temp_fs3;
        if (temp_fv1 >= 0.0f) {
            var_fa0 = 89.0f - sqrtf(temp_fv1);
        } else {
            var_fa0 = sqrtf(-temp_fv1) + -89.0f;
        }
        temp_ft3 = (s32) (func_150AD78C(var_fa0 * D_800A2F2C) * 256.0f);
        sp78 = (f32) temp_ft3;
        *(u16 *)((u8 *)var_s0 + 2) = (u16) sp78;
        temp_fs0 = sqrtf((f32) (0x10000 - (temp_ft3 * temp_ft3)));
        sp78 = (f32) (s32) (func_150AD78C(temp_fs1) * temp_fs0);
        *(u16 *)((u8 *)var_s0 + 0) = (u16) sp78;
        sp78 = (f32) (s32) (func_150AD780(temp_fs1) * temp_fs0);
        *(u16 *)((u8 *)var_s0 + 4) = (u16) sp78;
        *(s8 *)((u8 *)var_s0 + 7) = (s8) ((func_150ADA20() % 191U) + 0x40);
        *(s8 *)((u8 *)var_s0 + 6) = (s8) (func_150ADA20() % 5U);
        var_s1 += 1;
        var_s0 += 8;
    } while (var_s1 != 0x1F40);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15111858 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_15111858.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_15111AF4.s")
