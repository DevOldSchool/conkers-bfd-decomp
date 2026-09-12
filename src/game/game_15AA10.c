#include "types.h"

/*
 * Reviewed source unit: src/game/game_15AA10.c
 * Boundary evidence: docs/evidence/game_raw_preserved_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1512D560
 * - func_1512D604
 * - func_1512D66C
 * - func_1512D6B0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_15AA10/func_1512D560.s")
extern s32 D_800DC2B0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1512D604 CURRENT (630) */
void *func_1512D604(u8 *arg0) {
    s32 temp_a1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_v0 = (void *)(D_800DC2B0 + (*(u8 *)((u8 *)arg0 + 0x23D) * 0xB0));
    temp_a1 = *(s32 *)((u8 *)temp_v0 + 0xA8);
    *(s32 *)((u8 *)temp_v0 + 0xA8) = (s32) (temp_a1 + 1);
    temp_v0_2 = (void *)(D_800DC2B0 + (*(u8 *)((u8 *)arg0 + 0x23D) * 0xB0));
    if (*(s32 *)((u8 *)temp_v0_2 + 0xA8) == 0x14) {
        *(s32 *)((u8 *)temp_v0_2 + 0xA8) = 0;
    }
    return temp_v0 + (temp_a1 * 8);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1512D604 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15AA10/func_1512D604.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1512D66C CURRENT (95) */
void func_1512D66C(void *arg0) {
    s32 *temp_t6;
    u8 *temp_v0;

    temp_t6 = &D_800DC2B0;
    temp_v0 = (u8 *) (*temp_t6 + (*(u8 *)((u8 *) arg0 + 0x23D) * 0xB0));
    *(s32 *)(temp_v0 + 0xA8) = 0;
    temp_v0 = (u8 *) (*temp_t6 + (*(u8 *)((u8 *) arg0 + 0x23D) * 0xB0));
    *(s32 *)(temp_v0 + 0xAC) = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1512D66C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15AA10/func_1512D66C.s")
extern s32 D_800DC2B0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1512D6B0 CURRENT (85) */
s32 func_1512D6B0(void *arg0) {
    void *temp_v1;

    temp_v1 = D_800DC2B0 + (*(u8 *)((u8 *)arg0 + 0x23D) * 0xB0);
    return *(s32 *)((u8 *)temp_v1 + 0xA8) == *(s32 *)((u8 *)temp_v1 + 0xAC);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1512D6B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15AA10/func_1512D6B0.s")
