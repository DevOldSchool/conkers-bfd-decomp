#include "types.h"

/*
 * Reviewed source unit: src/game/game_AB760.c
 * Boundary evidence: docs/evidence/game_raw_resource_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1507E2B0
 * - func_1507E3C0
 * - func_1507E500
 * - func_1507E5C8
 * - func_1507E6B8
 * - func_1507E73C
 * - func_1507E7E4
 * - func_1507E908
 * - func_1507E968
 * - func_1507E9F8
 * - func_1507EA44
 * - func_1507EABC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E2B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E3C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E500.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E5C8.s")
s32 func_150849A0();                                /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507E6B8 CURRENT (820) */
s32 func_1507E6B8(void *arg0) {
    s32 temp_v0;

    if (*(u8 *)((u8 *)arg0 + 0x1CA) == 0) {
        goto block_9;
    }
    if (*(u8 *)((u8 *)arg0 + 0x70) == *(u8 *)((u8 *)arg0 + 0x6F)) {
        return 1;
    }
    temp_v0 = func_150849A0();
    if (temp_v0 == 0) {
        if (*(u8 *)((u8 *)arg0 + 0x6F) == 0x15) {
            return 1;
        }
        goto block_9;
    }
    if (temp_v0 == 0x52) {
        return 1;
    }
block_9:
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507E6B8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E6B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E73C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E7E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E908.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E968.s")
void func_1507E9E8(s32 arg0, s32 arg1) {
}
extern u8 D_8009D910[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507E9F8 CURRENT (100) */
void *func_1507E9F8(void *arg0, s32 *arg1) {
    if (func_150849A0() == 0) {
        if (arg1 != 0) {
            *arg1 = 5;
        }
        return D_8009D910;
    }
    if (arg1 != 0) {
        *arg1 = 0;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507E9F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507E9F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507EA44.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_AB760/func_1507EABC.s")
void func_1507EB4C(void *arg0, s32 arg1);

void func_1507EB2C(void *arg0) {
    func_1507EB4C(arg0, 0);
}
void func_1507EABC(void);

void func_1507EB4C(void *arg0, s32 arg1) {
    if (arg1 != *(u8 *)((u8 *)arg0 + 0x70)) {
        *(u8 *)((u8 *)arg0 + 0x70) = (u8)arg1;
        func_1507EABC();
    }
}
