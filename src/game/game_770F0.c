#include "types.h"

/*
 * Reviewed source unit: src/game/game_770F0.c
 * Boundary evidence: docs/evidence/game_raw_preserved_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15049CB8
 * - func_15049EDC
 * - func_1504A140
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15049C40(void *arg0, void *arg1) {
    f32 dot;

    dot = (*(f32 *)((u8 *)arg0 + 0) * *(f32 *)((u8 *)arg1 + 0)) + (*(f32 *)((u8 *)arg0 + 4) * *(f32 *)((u8 *)arg1 + 4)) + (*(f32 *)((u8 *)arg0 + 8) * *(f32 *)((u8 *)arg1 + 8)) + (*(f32 *)((u8 *)arg0 + 0xC) * *(f32 *)((u8 *)arg1 + 0xC));
    if (dot < 0.0f) {
        *(f32 *)((u8 *)arg1 + 0) = (f32) -*(f32 *)((u8 *)arg1 + 0);
        *(f32 *)((u8 *)arg1 + 4) = (f32) -*(f32 *)((u8 *)arg1 + 4);
        *(f32 *)((u8 *)arg1 + 8) = (f32) -*(f32 *)((u8 *)arg1 + 8);
        *(f32 *)((u8 *)arg1 + 0xC) = (f32) -*(f32 *)((u8 *)arg1 + 0xC);
    }
}
typedef struct {
    s32 entries[3];
} Game770F0IndexOrder;

f32 func_10026530(f32);
extern Game770F0IndexOrder D_80085FF0;
extern f32 D_80099090;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15049CB8 CURRENT (3127) */
void func_15049CB8(void *arg0, void *arg1) {
    f32 trace;
    f32 first_root;
    f32 first_factor;
    f32 root;
    f32 factor;
    f32 diagonal;
    s32 index;
    s32 column;
    s32 next;
    s32 last;
    s32 next_column;
    s32 last_column;
    u8 *row;
    u8 *next_row;
    u8 *last_row;

    trace = *(f32 *)((u8 *)arg0 + 0x28) +
            (*(f32 *)arg0 + *(f32 *)((u8 *)arg0 + 0x14)) + 1.0f;
    if (D_80099090 < trace) {
        first_root = func_10026530(trace);
        first_factor = 0.5f / first_root;
        *(f32 *)arg1 = first_root * 0.5f;
        *(f32 *)((u8 *)arg1 + 4) =
            (*(f32 *)((u8 *)arg0 + 0x18) - *(f32 *)((u8 *)arg0 + 0x24)) * first_factor;
        *(f32 *)((u8 *)arg1 + 8) =
            (*(f32 *)((u8 *)arg0 + 0x20) - *(f32 *)((u8 *)arg0 + 8)) * first_factor;
        *(f32 *)((u8 *)arg1 + 0xC) =
            (*(f32 *)((u8 *)arg0 + 4) - *(f32 *)((u8 *)arg0 + 0x10)) * first_factor;
    } else {
        Game770F0IndexOrder order;

        index = 0;
        order = D_80085FF0;
        if (*(f32 *)arg0 < *(f32 *)((u8 *)arg0 + 0x14)) {
            index = 1;
        }
        row = (u8 *)arg0 + index * 0x10;
        column = index * 4;
        diagonal = *(f32 *)(row + column);
        if (diagonal < *(f32 *)((u8 *)arg0 + 0x28)) {
            row = (u8 *)arg0 + 0x20;
            diagonal = *(f32 *)(row + 8);
            column = 8;
        }
        next = *(s32 *)((u8 *)order.entries + column);
        next_column = next * 4;
        last = order.entries[next];
        next_row = (u8 *)arg0 + next * 0x10;
        last_row = (u8 *)arg0 + last * 0x10;
        last_column = last * 4;
        root = func_10026530(((diagonal - *(f32 *)(next_row + next_column)) -
                               *(f32 *)(last_row + last_column)) + 1.0f);
        factor = 0.5f / root;
        *(f32 *)((u8 *)arg1 + column + 4) = root * 0.5f;
        *(f32 *)arg1 = (*(f32 *)(next_row + last_column) -
                       *(f32 *)(last_row + next_column)) * factor;
        *(f32 *)((u8 *)arg1 + next_column + 4) =
            (*(f32 *)(next_row + column) + *(f32 *)(row + next_column)) * factor;
        *(f32 *)((u8 *)arg1 + last_column + 4) =
            (*(f32 *)(last_row + column) + *(f32 *)(row + last_column)) * factor;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15049CB8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_770F0/func_15049CB8.s")
/* Call context: func_15047D60: unique active project prototype */
/* Call context: func_15048360: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15048360(f32);
extern f32 D_80099094;
extern f32 D_80099098;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15049EDC CURRENT (2254) */
void func_15049EDC(void *arg0, void *arg1, f32 arg2, void *arg3) {
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    f32 temp_fv1_2;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 0);
    temp_ft4 = *(f32 *)((u8 *)arg1 + 0);
    temp_fa0 = (*(f32 *)((u8 *)arg1 + 0xC) * *(f32 *)((u8 *)arg0 + 0xC)) + ((temp_fv1 * temp_ft4) + (*(f32 *)((u8 *)arg0 + 4) * *(f32 *)((u8 *)arg1 + 4)) + (*(f32 *)((u8 *)arg0 + 8) * *(f32 *)((u8 *)arg1 + 8)));
    if (temp_fa0 < D_80099094) {
        temp_fv0 = 1.0f - arg2;
        *(f32 *)((u8 *)arg3 + 0) = (f32) ((temp_fv0 * temp_fv1) - (temp_ft4 * arg2));
        *(f32 *)((u8 *)arg3 + 4) = (f32) ((temp_fv0 * *(f32 *)((u8 *)arg0 + 4)) - (*(f32 *)((u8 *)arg1 + 4) * arg2));
        *(f32 *)((u8 *)arg3 + 8) = (f32) ((temp_fv0 * *(f32 *)((u8 *)arg0 + 8)) - (*(f32 *)((u8 *)arg1 + 8) * arg2));
        *(f32 *)((u8 *)arg3 + 0xC) = (f32) ((temp_fv0 * *(f32 *)((u8 *)arg0 + 0xC)) - (*(f32 *)((u8 *)arg1 + 0xC) * arg2));
        return;
    }
    if (temp_fa0 <= D_80099098) {
        temp_fv0_2 = func_15048360(temp_fa0);
        sp24 = (1.0f - arg2) * temp_fv0_2;
        sp20 = arg2 * temp_fv0_2;
        sp1C = func_15047D60(temp_fv0_2);
        temp_fa1 = func_15047D60(sp24) / sp1C;
        sp18 = temp_fa1;
        temp_fv1_2 = func_15047D60(sp20) / sp1C;
        *(f32 *)((u8 *)arg3 + 0) = (f32) ((*(f32 *)((u8 *)arg1 + 0) * temp_fv1_2) + (temp_fa1 * *(f32 *)((u8 *)arg0 + 0)));
        *(f32 *)((u8 *)arg3 + 4) = (f32) ((*(f32 *)((u8 *)arg1 + 4) * temp_fv1_2) + (temp_fa1 * *(f32 *)((u8 *)arg0 + 4)));
        *(f32 *)((u8 *)arg3 + 8) = (f32) ((*(f32 *)((u8 *)arg1 + 8) * temp_fv1_2) + (temp_fa1 * *(f32 *)((u8 *)arg0 + 8)));
        *(f32 *)((u8 *)arg3 + 0xC) = (f32) ((*(f32 *)((u8 *)arg1 + 0xC) * temp_fv1_2) + (temp_fa1 * *(f32 *)((u8 *)arg0 + 0xC)));
        return;
    }
    temp_fv0_3 = 1.0f - arg2;
    *(f32 *)((u8 *)arg3 + 0) = (f32) ((temp_ft4 * arg2) + (temp_fv0_3 * temp_fv1));
    *(f32 *)((u8 *)arg3 + 4) = (f32) ((*(f32 *)((u8 *)arg1 + 4) * arg2) + (temp_fv0_3 * *(f32 *)((u8 *)arg0 + 4)));
    *(f32 *)((u8 *)arg3 + 8) = (f32) ((*(f32 *)((u8 *)arg1 + 8) * arg2) + (temp_fv0_3 * *(f32 *)((u8 *)arg0 + 8)));
    *(f32 *)((u8 *)arg3 + 0xC) = (f32) ((*(f32 *)((u8 *)arg1 + 0xC) * arg2) + (temp_fv0_3 * *(f32 *)((u8 *)arg0 + 0xC)));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15049EDC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_770F0/func_15049EDC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1504A140 CURRENT (4804) */
void func_1504A140(void *arg0, void *arg1) {
    f32 sp44;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fs0;
    f32 temp_ft0;
    f32 temp_ft1;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_ft3;

    temp_fs0 = *(f32 *)((u8 *)arg0 + 0);
    temp_fv0 = *(f32 *)((u8 *)arg0 + 4);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 8);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0xC);
    temp_ft1 = 2.0f / ((temp_fa0 * temp_fa0) + ((temp_fs0 * temp_fs0) + (temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1)));
    temp_ft5 = temp_fv0 * temp_ft1;
    sp44 = temp_ft1;
    temp_ft4 = temp_fv1 * temp_ft1;
    temp_fa1 = temp_fa0 * temp_ft1;
    sp34 = temp_fs0 * temp_ft5;
    sp30 = temp_fs0 * temp_ft4;
    sp2C = temp_fs0 * temp_fa1;
    temp_ft3 = temp_fv0 * temp_fa1;
    sp28 = temp_fv0 * temp_ft5;
    sp24 = temp_fv0 * temp_ft4;
    sp20 = temp_ft3;
    temp_ft0 = temp_fa0 * temp_fa1;
    sp1C = temp_fv1 * temp_ft4;
    sp18 = temp_fv1 * temp_fa1;
    sp14 = temp_ft0;
    *(f32 *)((u8 *)arg1 + 0) = (f32) (1.0f - (sp1C + sp14));
    *(f32 *)((u8 *)arg1 + 4) = (f32) (sp24 + sp2C);
    *(f32 *)((u8 *)arg1 + 8) = (f32) (temp_ft3 - sp30);
    *(f32 *)((u8 *)arg1 + 0x10) = (f32) (sp24 - sp2C);
    *(f32 *)((u8 *)arg1 + 0x18) = (f32) (sp18 + sp34);
    *(f32 *)((u8 *)arg1 + 0x14) = (f32) (1.0f - (sp28 + temp_ft0));
    *(f32 *)((u8 *)arg1 + 0x24) = (f32) (sp18 - sp34);
    *(f32 *)((u8 *)arg1 + 0x20) = (f32) (sp20 + sp30);
    *(f32 *)((u8 *)arg1 + 0xC) = 0.0f;
    *(f32 *)((u8 *)arg1 + 0x1C) = 0.0f;
    *(f32 *)((u8 *)arg1 + 0x2C) = 0.0f;
    *(f32 *)((u8 *)arg1 + 0x3C) = 1.0f;
    *(f32 *)((u8 *)arg1 + 0x28) = (f32) (1.0f - (sp28 + sp1C));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1504A140 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_770F0/func_1504A140.s")
