#include "types.h"

/*
 * Reviewed source unit: src/game/game_1A0790.c
 * Boundary evidence: docs/evidence/game_raw_slot_view_controller_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151732E0
 * - func_151733D8
 * - func_151733E4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A0790/func_151732E0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151733D8 CURRENT (160) */
void *func_151733D8(void *arg0, s32 arg1) {
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151733D8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A0790/func_151733D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A0790/func_151733E4.s")
void func_151733E4(s32, s32, s32, s32, s32);
extern s8 *D_800B0DF0;
extern void *D_800DBFF0;
extern u8 D_800DBEA8[];
extern u8 D_800DD2E4[];

void func_151738C4(s32 arg0) {
    if (D_800B0DF0[0x46] == -1) {
        if (*(s32 *)((u8 *)D_800DBFF0 + 0x5F0) & 1) {
            func_151733E4(6, 6, arg0, 0, -1);
            D_800DBEA8[0] = D_800DD2E4[0];
            D_800DBEA8[1] = D_800DD2E4[1];
            D_800DBEA8[2] = D_800DD2E4[2];
            return;
        }
        func_151733E4(0, 0, arg0, 0, -1);
        D_800DBEA8[0] = ((u8 *)D_800B0DF0)[5];
        D_800DBEA8[1] = ((u8 *)D_800B0DF0)[6];
        D_800DBEA8[2] = ((u8 *)D_800B0DF0)[7];
    }
}

s8 func_15173994(s32 arg0) {
    return D_800B0DF0[0x46];
}
