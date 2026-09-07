#include "types.h"

/*
 * Reviewed source unit: src/game/game_1E9A30.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151BC580
 * - func_151BC5A4
 * - func_151BC64C
 * - func_151BC794
 * - func_151BCA90
 * - func_151BD21C
 * - func_151BD2BC
 * - func_151BD2F8
 * - func_151BD43C
 * - func_151BD750
 * - func_151BD79C
 * - func_151BD7F4
 * - func_151BD828
 * - func_151BDD8C
 * - func_151BE0AC
 * - func_151BE138
 * - func_151BE1B8
 * - func_151BE1E4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BC580 CURRENT (80) */
s32 func_151BC580(void *arg0) {
    if (**(s32 **)((u8 *)arg0 + 0x40) == 0) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BC580 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BC580.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BC5A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BC64C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BC794.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BCA90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BD21C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BD2BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BD2F8.s")
s32 func_151BD42C(u8 *arg0) {
    *(s16 *)(arg0 + 0x80) = 0;
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BD43C.s")
extern f32 D_800AA860;
extern f32 D_800AA864;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BD750 CURRENT (945) */
f32 func_151BD750(void *arg0) {
    s16 temp_v0;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x80);
    *(s16 *)((u8 *)arg0 + 0x80) = (s16) (temp_v0 + D_800BE9E4);
    return ((f32) temp_v0 * 2.0f * D_800AA860) + D_800AA864;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BD750 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BD750.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BD79C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BD7F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BD828.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BDD8C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BE0AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BE138.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BE1B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1E9A30/func_151BE1E4.s")
