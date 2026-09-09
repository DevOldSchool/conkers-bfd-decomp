#include "types.h"

/*
 * Reviewed source unit: src/game/game_1FA770.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151CD2C0
 * - func_151CD35C
 * - func_151CD394
 * - func_151CD3CC
 * - func_151CD4C0
 * - func_151CD674
 * - func_151CD7BC
 * - func_151CDB94
 * - func_151CDE20
 * - func_151CE47C
 * - func_151CE49C
 * - func_151CE4DC
 * - func_151CE51C
 * - func_151CE634
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CD2C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CD35C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CD394.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CD3CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CD4C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CD674.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CD7BC.s")
extern f32 D_800AAFE4;
extern f32 D_800AAFE8;
extern f32 D_800AAFEC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CDB94 CURRENT (7501) */
s32 func_151CDB94(void *arg0) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    s32 temp_v0;
    s32 var_v1;
    s8 temp_a2;
    s8 var_v1_2;
    void *temp_a1;
    void *temp_a2_2;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x94);
    if (*(s8 *)((u8 *)arg0 + 0x2C) <= 0) {

    } else {
        var_v1 = *(s8 *)((u8 *)arg0 + 0x2E) - 1;
        if (var_v1 < 0) {
            var_v1 = *(u8 *)((u8 *)arg0 + 0x25) - 1;
        }
        temp_a2 = *(s8 *)((u8 *)arg0 + 0x2D);
        temp_a1 = (temp_a2 * 0x1C) + temp_v0;
        temp_fv0 = fabsf(*(f32 *)((u8 *)((var_v1 * 0x1C) + temp_v0) + 4) - *(f32 *)((u8 *)temp_a1 + 4));
        if (temp_fv0 == 0.0f) {

        } else {
            temp_fa1 = 1.0f / temp_fv0;
            var_v1_2 = temp_a2;
            do {
                temp_a2_2 = (var_v1_2 * 0x1C) + temp_v0;
                *(s16 *)((u8 *)temp_a2_2 + 0x14) = 0xFF;
                temp_fa0 = *(f32 *)((u8 *)temp_a2_2 + 4) - *(f32 *)((u8 *)temp_a1 + 4);
                if (temp_fa0 < (temp_fv0 * D_800AAFE4)) {
                    *(s16 *)((u8 *)temp_a2_2 + 0x14) = (s16) ((u32) (temp_fa0 * (temp_fa1 * D_800AAFEC) * 255.0f) & 0xFF);
                } else if ((temp_fv0 - (temp_fv0 * D_800AAFE8)) < temp_fa0) {
                    *(s16 *)((u8 *)temp_a2_2 + 0x14) = (s16) ((u32) ((temp_fv0 - temp_fa0) * (temp_fa1 * 10.0f) * 255.0f) & 0xFF);
                }
                var_v1_2 += 1;
                if (var_v1_2 >= (s32) *(u8 *)((u8 *)arg0 + 0x25)) {
                    var_v1_2 = 0;
                }
            } while (var_v1_2 != *(s8 *)((u8 *)arg0 + 0x2E));
        }
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CDB94 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CDB94.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CDE20.s")
typedef struct Game1FA770Object {
    u8 pad0[0x1E];
    volatile u16 flags;
    u8 pad20[0x10];
    s8 field_30;
} Game1FA770Object;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CE47C CURRENT (35) */
void func_151CE47C(Game1FA770Object *arg0) {
    u16 flags;

    arg0->field_30 = 0;
    flags = arg0->flags & 0xFFFD;
    arg0->flags = flags;
    arg0->flags = flags | 8;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CE47C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CE47C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CE49C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CE4DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CE51C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FA770/func_151CE634.s")
