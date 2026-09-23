#include "types.h"

/*
 * Reviewed source unit: src/game/game_EC0E0.c
 * Boundary evidence: docs/evidence/game_raw_internal_call_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150BEC30
 * - func_150BED4C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15142314(s32, s32, void *);
s32 func_15046C80(f32 *, u16, f32, void *);
void func_1504715C(void *, void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150BEC30 CURRENT (1793) */
s32 func_150BEC30(f32 *arg0, void *arg1, void *arg2, s32 arg3) {
    f32 position[3];
    s32 temp_t6;
    s32 var_a1;

    temp_t6 = arg3 & 0xFF;
    if (temp_t6 != 4) {
        if (temp_t6 != 5) {
            var_a1 = 0x10;
            switch (temp_t6) {
            case 7:
                break;
            case 6:
                var_a1 = 0xC;
                break;
            }
        } else {
            var_a1 = 0x16;
        }
    } else {
        var_a1 = 0x19;
    }
    func_15142314(*(s32 *)((u8 *)arg1 + 0x1D4), var_a1, arg0);
    if (arg2 == 0) {
        return 1;
    }
    position[0] = arg0[0];
    position[1] = arg0[1] + 10.0f;
    position[2] = arg0[2];
    func_1504715C(arg2, arg1);
    return func_15046C80(position, 0, arg0[1] - 50.0f, arg2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150BEC30 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EC0E0/func_150BEC30.s")

s32 func_150BED28(s32 arg0, s32 arg1) {
    if ((arg0 == 0) || (arg0 == 1)) {
        return 0x12;
    }
    return -1;
}
s32 func_150BEC30(f32 *, void *, void *, s32);
void func_15141F78(s32, void *, f32, s32, f32 *, s32);
void func_15142180(u8, f32 *, s32, f32, f32);
extern f32 D_800A00D0;
extern f32 D_800A00D4;
extern f32 D_800A00D8;

typedef struct {
    s32 saved_arg1;
    s32 work[9];
    f32 position[3];
} GameEC0E0ED4CLocals;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150BED4C CURRENT (1790) */
void func_150BED4C(void *arg0, s32 arg1, s32 arg2) {
    GameEC0E0ED4CLocals locals;
    union {
        u32 bits;
        f32 value;
    } double_scale;

    double_scale.bits = 0x40000000;

    if (*(s32 *)((u8 *)arg0 + 0x1D4) != 0) {
        locals.saved_arg1 = (u8)arg1;
        if (func_150BEC30(locals.position, arg0, locals.work, (u8)arg1) != 0) {
            func_15141F78(0xB, locals.work,
                          (f32)arg2 * D_800A00D0 * double_scale.value,
                          (u32)(*(f32 *)((u8 *)arg0 + 0x40) * D_800A00D4) & 0xFF,
                          locals.position, locals.saved_arg1);
            if (arg2 >= 0x4C) {
                func_15142180(2, locals.position, locals.work[6], 3.232f, D_800A00D8);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150BED4C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EC0E0/func_150BED4C.s")
