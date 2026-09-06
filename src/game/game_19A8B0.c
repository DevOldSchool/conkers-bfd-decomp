#include "types.h"

/*
 * Reviewed source unit: src/game/game_19A8B0.c
 * Boundary evidence: docs/evidence/game_raw_state_lifecycle_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1516D400
 * - func_1516D4E8
 * - func_1516D678
 * - func_1516D738
 * - func_1516D99C
 * - func_1516DB90
 * - func_1516E778
 * - func_1516E8CC
 * - func_1516ECAC
 * - func_1516ED68
 * - func_1516EED4
 * - func_1516F024
 * - func_1516F1C0
 * - func_1516F2F8
 * - func_1516F548
 * - func_1516F864
 * - func_1516F8EC
 * - func_1516F91C
 * - func_1516F984
 * - func_1516F9C4
 * - func_1516FA88
 * - func_1516FBCC
 * - func_1516FD50
 * - func_1516FE1C
 * - func_15170034
 * - func_151700D8
 * - func_15170500
 * - func_151707E0
 * - func_151709B4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516D400.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516D4E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516D678.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516D738.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516D99C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516DB90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516E778.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516E8CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516ECAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516ED68.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516EED4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516F024.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516F1C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516F2F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516F548.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516F864 CURRENT (1010) */
void func_1516F864(void *arg0) {
    s32 temp_t1;
    s32 temp_t3;

    temp_t3 = (*(s16 *)((u8 *)arg0 + 0xE) << 8) + *(u8 *)((u8 *)arg0 + 0x2A) + (((*(s8 *)((u8 *)arg0 + 0x26) << 8) + *(u8 *)((u8 *)arg0 + 0x27)) * D_800BE9E4);
    *(s16 *)((u8 *)arg0 + 0xE) = (s16) (temp_t3 >> 8);
    *(u8 *)((u8 *)arg0 + 0x2A) = (u8) temp_t3;
    temp_t1 = (*(s16 *)((u8 *)arg0 + 0x12) << 8) + *(u8 *)((u8 *)arg0 + 0x2B) + (((*(s8 *)((u8 *)arg0 + 0x28) << 8) + *(u8 *)((u8 *)arg0 + 0x29)) * D_800BE9E4);
    *(s16 *)((u8 *)arg0 + 0x12) = (s16) (temp_t1 >> 8);
    *(u8 *)((u8 *)arg0 + 0x2B) = (u8) temp_t1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516F864 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516F864.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516F8EC CURRENT (45) */
void func_1516F8EC(void *arg0, s32 arg1) {
    s32 temp_t0;

    temp_t0 = (s32) (((*(s8 *)((u8 *)arg0 + 0x26) << 8) + *(u8 *)((u8 *)arg0 + 0x27)) * arg1) >> 8;
    *(s8 *)((u8 *)arg0 + 0x26) = (s8) (temp_t0 >> 8);
    *(u8 *)((u8 *)arg0 + 0x27) = (u8) temp_t0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516F8EC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516F8EC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516F91C CURRENT (45) */
void func_1516F91C(void *arg0, s32 arg1) {
    s32 temp_t0;

    temp_t0 = (s32) (((*(s8 *)((u8 *)arg0 + 0x28) << 8) + *(u8 *)((u8 *)arg0 + 0x29)) * arg1) >> 8;
    *(s8 *)((u8 *)arg0 + 0x28) = (s8) (temp_t0 >> 8);
    *(u8 *)((u8 *)arg0 + 0x29) = (u8) temp_t0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516F91C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516F91C.s")
void func_1516F94C(s32 arg0, s32 arg1) {
    func_1516F8EC(arg0, arg1);
    func_1516F91C(arg0, arg1);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516F984 CURRENT (40) */
void func_1516F984(s32 arg0, s32 arg1) {
    func_1516F94C(arg0, arg1);
    *(s16 *)((u8 *)arg0 + 0x18) = (s16) ((s32) (*(s16 *)((u8 *)arg0 + 0x18) * arg1) >> 8);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516F984 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516F984.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516F9C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516FA88.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516FBCC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516FD50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516FE1C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_15170034.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_151700D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_15170500.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_151707E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_151709B4.s")
