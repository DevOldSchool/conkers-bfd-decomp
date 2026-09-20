#include "types.h"

/*
 * Reviewed source unit: src/game/game_20A990.c
 * Boundary evidence: docs/evidence/game_raw_preserved_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151DD4E0
 * - func_151DD65C
 * - func_151DD710
 * - func_151DD8C0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_20A990/func_151DD4E0.s")
extern u8 D_800E0A30[];
extern u8 D_800E0A31[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DD65C CURRENT (3618) */
void func_151DD65C(s32 arg0, const u8 *arg1) {
    u8 packet[0xC];
    u8 *dst;
    s32 i;

    *(s32 *)(D_800E0A30 + 0x3C) = 1;
    packet[0] = 0xA;
    packet[1] = 1;
    packet[2] = 5;
    packet[3] = (u8)arg0;
    for (i = 0; i < 8; i++) {
        packet[4 + i] = arg1[i];
    }
    dst = D_800E0A30;
    dst[0] = 0;
    dst[1] = 0;
    dst[2] = 0;
    for (i = 0; i < 0xC; i++) {
        dst[3 + i] = packet[i];
    }
    dst[0xF] = 0xFE;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151DD65C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20A990/func_151DD65C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20A990/func_151DD710.s")
extern u8 D_800BE748[];
extern s32 D_800BE9E4;
extern u8 D_800E0A70[];
extern s32 D_800E0A74;
extern s8 D_800E0BD2;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151DD8C0 CURRENT (1160) */
void func_151DD8C0(void) {
    s32 temp_t5;
    u16 temp_v0;
    u8 *temp_a0;

    temp_a0 = D_800E0A70 + (D_800E0A74 * 6);
    D_800BE748[2] = temp_a0[0];
    D_800BE748[3] = temp_a0[1];
    D_800E0BD2 = 0;
    *(u16 *)D_800BE748 = *(u16 *)(temp_a0 + 4) | (*(u16 *)D_800BE748 & 0x1000);
    if (D_800E0A74 < 0x1F3) {
        temp_v0 = *(u16 *)(temp_a0 + 8);
        if (D_800BE9E4 < (s32)temp_v0) {
            D_800E0BD2 = temp_v0 - D_800BE9E4;
        }
    }
    temp_t5 = D_800E0A74 + 1;
    D_800BE9E4 = *(u16 *)(temp_a0 + 2);
    D_800E0A74 = temp_t5;
    if (temp_t5 >= 0x1F3) {
        D_800E0A74 = 0x1F3;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151DD8C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20A990/func_151DD8C0.s")
