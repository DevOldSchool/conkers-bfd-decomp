#include "types.h"

/*
 * Reviewed source unit: src/game/game_770F0.c
 * Boundary evidence: docs/evidence/game_raw_preserved_helper_groups.md
 * Semantic evidence: docs/evidence/vector_transform_helper_semantics.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15049CB8
 * - func_15049EDC
 * - func_1504A140
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

/* Keep address symbols for linking and registered match evidence. */
#define quaternion_align_hemisphere func_15049C40

void quaternion_align_hemisphere(void *arg0, void *arg1) {
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
    s32 indices[3];
} Game770F0IndexCycle;

f32 func_10026530(f32);
extern Game770F0IndexCycle D_80085FF0;
extern f32 D_80099090;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15049CB8 CURRENT (3005) */
void func_15049CB8(f32 matrix[4][4], f32 *arg1) {
    f32 *result;
    f32 trace;
    f32 root;
    f32 scale;
    f32 diagonal;
    s32 i;
    s32 j;
    s32 k;
    f32 *rowI;
    f32 *rowJ;
    f32 *rowK;

    result = arg1;
    trace = matrix[2][2] + (matrix[0][0] + matrix[1][1]) + 1.0f;
    if (D_80099090 < trace) {
        root = func_10026530(trace);
        scale = 0.5f / root;
        result[0] = root * 0.5f;
        result[1] = (matrix[1][2] - matrix[2][1]) * scale;
        result[2] = (matrix[2][0] - matrix[0][2]) * scale;
        result[3] = (matrix[0][1] - matrix[1][0]) * scale;
    } else {
    Game770F0IndexCycle cycle;

    cycle = D_80085FF0;
    i = 0;
    if (matrix[0][0] < matrix[1][1]) {
        i = 1;
    }
    rowI = matrix[i];
    diagonal = rowI[i];
    if (diagonal < matrix[2][2]) {
        rowI = matrix[2];
        diagonal = rowI[2];
        i = 2;
    }
    j = cycle.indices[i];
    k = cycle.indices[j];
    rowJ = matrix[j];
    rowK = matrix[k];
    root = func_10026530((diagonal - rowJ[j] - rowK[k]) + 1.0f);
    scale = 0.5f / root;
    result[i + 1] = root * 0.5f;
    result[0] = (rowJ[k] - rowK[j]) * scale;
    result[j + 1] = (rowJ[i] + rowI[j]) * scale;
    result[k + 1] = (rowK[i] + rowI[k]) * scale;
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15049EDC CURRENT (2044) */
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
    temp_fa0 = (temp_fv1 * temp_ft4) + (*(f32 *)((u8 *)arg0 + 4) * *(f32 *)((u8 *)arg1 + 4));
    temp_fa0 = temp_fa0 + (*(f32 *)((u8 *)arg0 + 8) * *(f32 *)((u8 *)arg1 + 8));
    temp_fa0 = (*(f32 *)((u8 *)arg1 + 0xC) * *(f32 *)((u8 *)arg0 + 0xC)) + temp_fa0;
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
