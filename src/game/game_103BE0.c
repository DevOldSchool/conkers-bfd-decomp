#include "types.h"

/*
 * Reviewed source unit: src/game/game_103BE0.c
 * Boundary evidence: docs/evidence/game_raw_owner_particle_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D6730
 * - func_150D6CC4
 * - func_150D6E60
 * - func_150D6F0C
 * - func_150D7068
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_103BE0/func_150D6730.s")
void func_150D6C98(void *arg0, void *arg1) {
    *(f32 *)((u8 *)arg1 + 0) = (f32) *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)((u8 *)arg1 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 0x18) + 60.0f);
    *(f32 *)((u8 *)arg1 + 8) = (f32) *(f32 *)((u8 *)arg0 + 0x1C);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_103BE0/func_150D6CC4.s")
void func_1516972C(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D6E60 CURRENT (2022) */
void func_150D6E60(void *arg0, void *arg1, s32 arg2) {
    s32 temp_a0;
    s32 temp_t6;
    s32 temp_v1;
    u8 *temp_v0;

    temp_t6 = arg2 & 0xFF;
    if (temp_t6 == 0x2D) {
        temp_v0 = (u8 *)arg0 + 0xA8;
        temp_a0 = *(s32 *)temp_v0;
        temp_v1 = *(s32 *)arg1;
        if (temp_v1 == temp_a0) {
            *(s32 *)temp_v0 = *(s32 *)((u8 *)arg1 + 4);
            *(u8 *)(temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 9);
            return;
        }
        if (*(s32 *)((u8 *)arg1 + 4) == temp_a0) {
            *(s32 *)temp_v0 = temp_v1;
            *(u8 *)(temp_v0 + 4) = *(u8 *)((u8 *)arg1 + 8);
        }
    } else if ((temp_t6 == 0) &&
               ((*(s32 *)arg1 == *(s32 *)((u8 *)arg0 + 0xA8)) ||
                (*(u8 *)((u8 *)arg0 + 0xAC) == *(u8 *)((u8 *)arg1 + 4)))) {
        func_1516972C(arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D6E60 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_103BE0/func_150D6E60.s")
/* Call context: func_150D6C98: unique active project prototype */
extern f32 D_800BE9A4;
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D6F0C CURRENT (893) */
s32 func_150D6F0C(u8 *arg0, s32 arg1) {
    void *sp18;
    f32 temp_fa0;
    f32 temp_fv1;
    s32 var_v0;
    u8 *temp_a3;
    u8 *temp_v0;

    temp_a3 = (void *)(*(void **)((u8 *)arg0 + 0xA8));
    temp_v0 = (void *)(arg0 + 0xA8);
    if ((*(s32 *)((u8 *)temp_a3 + 0) == 0) || (*(u8 *)((u8 *)temp_v0 + 4) != *(u8 *)((u8 *)temp_a3 + 0x3B))) {
        return 0;
    }
    sp18 = temp_v0;
    func_150D6C98(temp_a3, arg0 + 0x40);
    temp_fv1 = sqrtf(*(f32 *)((u8 *)temp_v0 + 8)) * *(f32 *)((u8 *)temp_v0 + 0x10);
    *(f32 *)((u8 *)arg0 + 0x3C) = temp_fv1;
    *(f32 *)((u8 *)arg0 + 0x38) = temp_fv1;
    temp_fa0 = *(f32 *)((u8 *)temp_v0 + 8);
    *(s8 *)((u8 *)arg0 + 0x2B) = (s8) (u32) (*(f32 *)((u8 *)temp_v0 + 0x14) - (*(f32 *)((u8 *)temp_v0 + 0x18) * temp_fa0 * temp_fa0));
    *(f32 *)((u8 *)temp_v0 + 8) = (f32) (*(f32 *)((u8 *)temp_v0 + 8) + D_800BE9A4);
    var_v0 = 1;
    if (*(f32 *)((u8 *)temp_v0 + 0xC) < *(f32 *)((u8 *)temp_v0 + 8)) {
        var_v0 = 0;
    }
    return var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D6F0C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_103BE0/func_150D6F0C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D7068 CURRENT (1087) */
void func_150D7068(void *arg0, void *arg1, s32 arg2) {
    u8 *state;
    s32 current;
    s32 other;

    state = (u8 *)arg0 + 0xA8;
    if ((arg2 & 0xFF) == 0x2D) {
        current = *(s32 *)state;
        if (*(s32 *)arg1 == current) {
            *(s32 *)state = *(s32 *)((u8 *)arg1 + 4);
            state[4] = *(u8 *)((u8 *)arg1 + 9);
        } else if (*(s32 *)((u8 *)arg1 + 4) == current) {
            *(s32 *)state = *(s32 *)arg1;
            state[4] = *(u8 *)((u8 *)arg1 + 8);
        }
    } else if ((arg2 & 0xFF) == 0) {
        other = *(s32 *)arg1;
        if ((other == *(s32 *)state) ||
            (state[4] == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C(arg0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D7068 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_103BE0/func_150D7068.s")
