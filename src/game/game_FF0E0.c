#include "types.h"

/*
 * Reviewed source unit: src/game/game_FF0E0.c
 * Boundary evidence: docs/evidence/game_raw_child_chain_render_lists.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D1C30
 * - func_150D1F6C
 * - func_150D2054
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_1516972C(void *arg0);
extern s32 D_800A5480;

typedef struct {
    u8 pad_0[0x18];
    s32 field_18;
    s32 field_1C;
    s32 field_20;
    u8 pad_24[0x18];
    f32 field_3C;
    void *field_40;
    u8 field_44;
} GameFF0E0State;

#pragma GLOBAL_ASM("asm/nonmatchings/game_FF0E0/func_150D1C30.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D1F6C CURRENT (1915) */
void func_150D1F6C(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 temp_t6;
    GameFF0E0State *temp_v0;

    temp_t6 = arg2;
    if (temp_t6 == 0x32) {
        temp_v0 = (GameFF0E0State *)(arg0 + 0x28);
        temp_v0->field_18 = *(s32 *)arg1;
        temp_v0->field_1C = *(s32 *)(arg1 + 4);
        temp_v0->field_20 = *(s32 *)(arg1 + 8);
        temp_v0->field_3C = *(f32 *)(arg1 + 0xC);
        return;
    }
    if ((temp_t6 == 0x30) || (temp_t6 == 0x31)) {
        temp_v0 = (GameFF0E0State *)(arg0 + 0x28);
        if (arg1 == temp_v0->field_40) {
            if (temp_t6 == 0x30) {
                temp_v0->field_44 |= 1;
                return;
            }
            temp_v0->field_44 &= 0xFFFE;
        }
    } else {
        if (temp_t6 == 0x4E) {
            *(s32 *)(arg0 + 0x40) = *(&D_800A5480 + 0);
            *(s32 *)(arg0 + 0x44) = *(&D_800A5480 + 1);
            *(s32 *)(arg0 + 0x48) = *(&D_800A5480 + 2);
            return;
        }
        if (temp_t6 == 0x4F) {
            func_1516972C(arg0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D1F6C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FF0E0/func_150D1F6C.s")
void func_150D2054(s32 arg0);
void func_1514933C(s32 arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D2054 CURRENT (435) */
void func_150D2054(void *arg0) {
    s32 temp_t8;
    s32 var_s0;
    void *temp_a0;
    u8 *var_s1;

    var_s0 = 0;
    var_s1 = (u8 *)arg0 + 0x28;
    do {
        temp_a0 = *(void **)(var_s1 + (var_s0 * 4) + 0x24);
        if (temp_a0 != 0) {
            func_1516972C(temp_a0);
        }
        temp_t8 = (var_s0 + 1) & 0xFF;
        var_s0 = temp_t8;
    } while (temp_t8 < 6);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D2054 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FF0E0/func_150D2054.s")

void func_150D20B0(s32 arg0) {
    func_150D2054(arg0);
    func_15149368(arg0);
}

void func_150D20DC(s32 arg0) {
    func_150D2054(arg0);
    func_1514933C(arg0);
}
