#include "types.h"

/*
 * Reviewed source unit: src/game/game_FC9E0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150CF530
 * - func_150CF578
 * - func_150CF5E8
 * - func_150CF680
 * - func_150CF800
 * - func_150CFBEC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_FC9E0/func_150CF530.s")
extern s32 D_80088890;
extern s32 D_80088894;
extern s32 D_80088898;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CF578 CURRENT (265) */
void func_150CF578(s32 arg0) {
    s32 temp_v1;

    temp_v1 = D_800BE9E4 * 0x1C;
    D_80088890 += D_800BE9E4 * 0x1A;
    D_80088894 -= temp_v1;
    D_80088898 -= temp_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CF578 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FC9E0/func_150CF578.s")
extern s32 D_8008889C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CF5E8 CURRENT (575) */
void *func_150CF5E8(u8 *arg0) {
    u8 *temp_a0;

    *(s32 *)((u8 *)arg0 + 0) = (s32) (((((s32) D_80088890 >> 7) & 0xFFF) << 0xC) | 0xF2000000 | (((s32) D_80088894 >> 7) & 0xFFF));
    *(s32 *)((u8 *)arg0 + 4) = 0x47E47E;
    temp_a0 = (void *)(arg0 + 8);
    *(s32 *)((u8 *)arg0 + 8) = (s32) (((((s32) D_80088898 >> 7) & 0xFFF) << 0xC) | 0xF2000000 | (((s32) D_8008889C >> 7) & 0xFFF));
    *(s32 *)((u8 *)temp_a0 + 4) = 0x0147E47E;
    return temp_a0 + 8;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CF5E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FC9E0/func_150CF5E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FC9E0/func_150CF680.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FC9E0/func_150CF800.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CFBEC CURRENT (385) */
void func_150CFBEC(u8 *arg0, f32 *arg1, s32 arg2) {
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + 0x70);
    if ((arg2 & 0xFF) == 0x52) {
        *(u8 *)((u8 *)arg0 + 0x70) = (u8) (*(u8 *)((u8 *)arg0 + 0x70) | 1);
        *(f32 *)((u8 *)temp_v0 + 4) = 0.0f;
        *(f32 *)((u8 *)temp_v0 + 8) = (f32) *(f32 *)((u8 *)arg0 + 0x10);
        *(f32 *)((u8 *)temp_v0 + 0xC) = (f32) (*arg1 - *(f32 *)((u8 *)arg0 + 0x10));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CFBEC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FC9E0/func_150CFBEC.s")
void func_150CFC38(f32 arg0) {
    f32 sp1C;

    sp1C = arg0;
    func_1515572C(&sp1C, 0x52);
}
