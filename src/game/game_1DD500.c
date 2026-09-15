#include "types.h"

/*
 * Reviewed source unit: src/game/game_1DD500.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151B0050
 * - func_151B01B8
 * - func_151B03B8
 * - func_151B09BC
 * - func_151B0B88
 * - func_151B118C
 * - func_151B14AC
 * - func_151B1828
 * - func_151B1918
 * - func_151B19A4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B0050.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B01B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B03B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B09BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B0B88.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B118C.s")
s32 func_151B1478(void *arg0) {
    s16 temp_v0;
    s32 temp_v1;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    if (temp_v0 < 0x20) {
        temp_v1 = temp_v0 * 8;
        if (temp_v1 < (s32) *(u8 *)((u8 *)arg0 + 0x5C)) {
            *(u8 *)((u8 *)arg0 + 0x5C) = (u8) temp_v1;
        }
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B14AC.s")
/* Call context: func_151423D8: unique active project prototype */
f32 func_151423D8(u8);
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B1828 CURRENT (917) */
s32 func_151B1828(u8 *arg0) {
    f32 sp24;
    void *sp1C;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    u8 temp_a0;
    u8 *temp_v1;

    temp_a0 = *(u8 *)((u8 *)arg0 + 0x120) + (*(s8 *)((u8 *)arg0 + 0x122) * D_800BE9E4);
    *(u8 *)((u8 *)arg0 + 0x120) = temp_a0;
    *(u8 *)((u8 *)arg0 + 0x121) = (u8) (*(u8 *)((u8 *)arg0 + 0x121) + (*(s8 *)((u8 *)arg0 + 0x123) * D_800BE9E4));
    sp24 = func_151423D8((temp_a0 - 0x40) & 0xFF);
    temp_v1 = (void *)(arg0 + 0x110);
    sp1C = temp_v1;
    temp_fv0 = func_151423D8((*(u8 *)((u8 *)temp_v1 + 0x11) - 0x40) & 0xFF);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x2C);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x30);
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (temp_fv1 + (((*(f32 *)((u8 *)temp_v1 + 0x14) + (*(f32 *)((u8 *)temp_v1 + 0x1C) * sp24)) - temp_fv1) * 0.5f));
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (temp_fa0 + (((*(f32 *)((u8 *)temp_v1 + 0x18) + (*(f32 *)((u8 *)temp_v1 + 0x20) * temp_fv0)) - temp_fa0) * 0.5f));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B1828 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B1828.s")
void func_1516972C(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151B1918 CURRENT (520) */
void func_151B1918(s32 arg0) {
    s32 var_s3;
    u8 *var_s0;
    u8 *var_s1;
    u8 *var_s2;

    var_s2 = (u8 *)(arg0 + 0x28);
    *(s32 *)((u8 *)arg0 + 0x30) = 0;
    var_s0 = var_s2 + 0xC;
    var_s3 = 0;
    *(f32 *)((u8 *)arg0 + 0xB8) = 0.0f;
    do {
        var_s1 = var_s0;
        if (*(s32 *)(var_s2 + 0xC) != 0) {
            func_1516972C(*(s32 *)var_s0);
        }
        *(s32 *)(var_s1 + 4) = 0;
        *(s32 *)(var_s1 + 8) = 0;
        var_s3 += 0xC;
        var_s2 += 0xC;
        var_s0 += 0xC;
    } while (var_s3 != 0x84);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151B1918 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B1918.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B19A4.s")
void func_151B1918(s32 arg0);
void func_1514933C(s32 arg0);
void func_15149368(s32 arg0);

void func_151B1A58(s32 arg0) {
    func_151B1918(arg0);
    func_1514933C(arg0);
}
void func_151B1A84(s32 arg0) {
    func_151B1918(arg0);
    func_15149368(arg0);
}
