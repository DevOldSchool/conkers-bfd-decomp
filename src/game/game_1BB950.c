#include "types.h"

/*
 * Reviewed source unit: src/game/game_1BB950.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1518E524
 * - func_1518E5D8
 * - func_1518E66C
 * - func_1518E6D4
 * - func_1518E73C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_1514EDF0(s32 arg0, s32 arg1);
void func_1518E308(void *arg0);
void func_15169804(s32 arg0);
void func_15169824(s32 arg0);

void func_1518E4A0(void *arg0) {
    func_1518E308(arg0);
    func_1514EDF0((s32) arg0, *(s32 *)((u8 *)arg0 + 0x18));
}
void func_1518E4CC(void *arg0) {
    func_1518E4A0(arg0);
    func_15169804((s32) arg0);
}
void func_1518E4F8(void *arg0) {
    func_1518E4A0(arg0);
    func_15169824((s32) arg0);
}
s32 func_150ADA20();                                /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518E524 CURRENT (5) */
void func_1518E524(s8 *arg0, u8 *arg1, s8 *arg2, s8 *arg3, s8 *arg4, s8 *arg5, s16 *arg6) {
    s32 temp_v1;

    *arg1 = 2;
    if (func_150ADA20() & 1) {
        *arg1 |= 1;
    }
    temp_v1 = func_150ADA20() & 1;
    switch (temp_v1) {                              /* irregular */
    case 0:
        *arg0 = 0x13;
        break;
    case 1:
        *arg0 = 0x14;
        break;
    }
    *arg2 = 0;
    *arg3 = 0;
    *arg4 = 0;
    *arg5 = 0xFF;
    *arg6 = 0x301;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518E524 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BB950/func_1518E524.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BB950/func_1518E5D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BB950/func_1518E66C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BB950/func_1518E6D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BB950/func_1518E73C.s")
