#include "types.h"

/*
 * Reviewed source unit: src/game/game_157840.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1512A390
 * - func_1512ABF8
 * - func_1512AD54
 * - func_1512B100
 * - func_1512B1B8
 * - func_1512B53C
 * - func_1512B630
 * - func_1512B730
 * - func_1512BB10
 * - func_1512C068
 * - func_1512C150
 * - func_1512C20C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512A390.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512ABF8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512AD54.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512B100.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512B1B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512B53C.s")
void func_1512B5FC(void *arg0, s32 arg1, s32 arg2) {
    *(u8 *)((u8 *)arg0 + 2) = (u8) *(u8 *)((u8 *)arg0 + 1);
    if (*(s32 *)((u8 *)arg0 + 4) < arg1) {
        *(u8 *)((u8 *)arg0 + 1) = 0U;
    } else {
        *(u8 *)((u8 *)arg0 + 1) = 1U;
    }
    *(s32 *)((u8 *)arg0 + 8) = arg2;
    *(s32 *)((u8 *)arg0 + 4) = arg1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512B630.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512B730.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512BB10.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512C068.s")
f32 func_15048A70(f32, f32);                        /* extern */
extern f32 D_800A3694;
extern f32 D_800A3698;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1512C150 CURRENT (150) */
void func_1512C150(void *arg0) {
    f32 temp_fv0;

    *(f32 *)((u8 *)arg0 + 0x5CC) = (f32) (*(f32 *)((u8 *)arg0 + 0x5CC) + D_800A3694);
    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x5CC);
    if (temp_fv0 > 1.0f) {
        *(f32 *)((u8 *)arg0 + 0x5CC) = 1.0f;
    } else {
        *(f32 *)((u8 *)arg0 + 0x5CC) = temp_fv0;
    }
    if (*(f32 *)((u8 *)arg0 + 0x5CC) == 1.0f) {
        *(s32 *)((u8 *)arg0 + 0x240) = (s32) (*(s32 *)((u8 *)arg0 + 0x240) & ~2);
        *(f32 *)((u8 *)arg0 + 0x384) = (f32) D_800A3698;
        return;
    }
    *(f32 *)((u8 *)arg0 + 0x384) = (f32) (*(f32 *)((u8 *)arg0 + 0x384) + (func_15048A70(*(f32 *)((u8 *)arg0 + 0x384), *(f32 *)((u8 *)arg0 + 0x37C)) * *(f32 *)((u8 *)arg0 + 0x5CC)));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1512C150 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512C150.s")
void func_1512C200(s32 arg0) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_157840/func_1512C20C.s")
s32 func_1512C47C(s32 arg0) {
    return 1;
}
