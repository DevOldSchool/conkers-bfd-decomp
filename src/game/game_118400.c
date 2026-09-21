#include "types.h"

/*
 * Reviewed source unit: src/game/game_118400.c
 * Boundary evidence: docs/evidence/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150EB090
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game118400Record Game118400Record;

s32 func_151420F8(Game118400Record *);
extern s32 D_800BE9F0;

void func_15142314(s32, s32, void *);
s32 func_15046C80(f32 *, u16, f32, void *);
void func_1504715C(void *, void *);

s32 func_150EAF50(u8 *arg0, u8 *arg1, void *arg2, u8 arg3) {
    f32 position[3];
    s32 var_a1;

    if ((arg3 != 1) && (arg3 != 2)) {
        return 0;
    }
    if (arg3 == 1) {
        var_a1 = 0x21;
    } else {
        var_a1 = 0x1D;
    }
    func_15142314(*(s32 *)(arg1 + 0x1D4), var_a1, arg0);
    if (arg2 == 0) {
        return 1;
    }
    position[0] = *(f32 *)(arg0 + 0);
    position[1] = *(f32 *)(arg0 + 4) + 10.0f;
    position[2] = *(f32 *)(arg0 + 8);
    func_1504715C(arg2, arg1);
    return func_15046C80(position, 0, *(f32 *)(arg0 + 4) - 50.0f, arg2);
}

s32 func_150EB030(s32 arg0, Game118400Record *arg1) {
    if (arg0 == 1) {
        if (D_800BE9F0 == 4) {
            if (func_151420F8(arg1) != 0) {
                return 6;
            }
            return 3;
        }
        return -1;
    }
    return -1;
}

void func_15141F78(s32, void *, f32, s32, f32 *, s32);
extern f32 D_800A1470;
extern f32 D_800A1474;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150EB090 CURRENT (860) */
void func_150EB090(u8 *arg0, u8 arg1, s32 arg2) {
    u8 sp4C[12];
    u8 sp28[0x24];
    volatile s32 sp24;

    if (*(s32 *)(arg0 + 0x1D4) != 0) {
        sp24 = arg1;
        if (func_150EAF50(sp4C, arg0, sp28, arg1) != 0) {
            func_15141F78(0xA, sp28, (f32)arg2 * D_800A1470,
                          (u32)(*(f32 *)(arg0 + 0x40) * D_800A1474) & 0xFF,
                          (f32 *)sp4C, sp24);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150EB090 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_118400/func_150EB090.s")
