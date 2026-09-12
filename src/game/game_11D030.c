#include "types.h"

/*
 * Reviewed source unit: src/game/game_11D030.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150EFB80
 * - func_150EFEC8
 * - func_150F00EC
 * - func_150F0198
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_11D030/func_150EFB80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D030/func_150EFEC8.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F00EC CURRENT (1860) */
s32 func_150F00EC(u8 *arg0) {
    s32 temp_t4;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v0 = (void *)(*(void **)((u8 *)arg0 + 0x178));
    if (*(u8 *)((u8 *)temp_v0 + 0x128) & 1) {
        temp_v1 = (void *)(temp_v0 + 0x110);
        *(f32 *)((u8 *)arg0 + 0x34) = (f32) *(f32 *)((u8 *)temp_v0 + 0x34);
        *(f32 *)((u8 *)arg0 + 0x38) = (f32) *(f32 *)((u8 *)temp_v0 + 0x38);
        *(f32 *)((u8 *)arg0 + 0x3C) = (f32) *(f32 *)((u8 *)temp_v0 + 0x3C);
        *(f32 *)((u8 *)arg0 + 0x40) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x34) + (*(f32 *)((u8 *)temp_v1 + 0x30) * 500.0f));
        *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x38) + (*(f32 *)((u8 *)temp_v1 + 0x34) * 500.0f));
        *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) | 6);
        *(f32 *)((u8 *)arg0 + 0x48) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x3C) + (*(f32 *)((u8 *)temp_v1 + 0x38) * 500.0f));
    } else {
        temp_t4 = *(s32 *)((u8 *)arg0 + 0x58) & ~4;
        *(s32 *)((u8 *)arg0 + 0x58) = temp_t4;
        *(s32 *)((u8 *)arg0 + 0x58) = (s32) (temp_t4 & ~2);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F00EC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D030/func_150F00EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D030/func_150F0198.s")
