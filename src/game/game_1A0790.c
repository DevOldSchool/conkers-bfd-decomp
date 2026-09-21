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

typedef struct Game1A0790Output {
    u8 field0;
    u8 field1;
    u8 field2;
    u8 field3;
    s16 field4;
    s16 field6;
    s16 field8;
    s16 fieldA;
    u16 fieldC;
    u16 fieldE;
} Game1A0790Output;

void func_151733E4(s32, s32, s32, s32, s32);
extern s8 *D_800B0DF0;
extern Game1A0790Output D_8008CC70;
extern s8 D_800DD2E0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151732E0 CURRENT (10) */
void func_151732E0(s32 arg0) {
    s16 temp_v0;
    s8 temp_a0;

    temp_v0 = *(s16 *)(D_800B0DF0 + 0x3C);
    if ((temp_v0 == *(s16 *)(D_800B0DF0 + 0x40)) && (temp_v0 == 0)) {
        *(s16 *)(D_800B0DF0 + 0x40) = 0x64;
    }
    D_8008CC70.field0 = ((u8 *)D_800B0DF0)[0x42];
    D_8008CC70.field1 = ((u8 *)D_800B0DF0)[0x43];
    D_8008CC70.field2 = ((u8 *)D_800B0DF0)[0x44];
    D_8008CC70.field3 = ((u8 *)D_800B0DF0)[0x45];
    D_8008CC70.field4 = *(s16 *)(D_800B0DF0 + 0x3A);
    D_8008CC70.field6 = *(s16 *)(D_800B0DF0 + 0x3C);
    D_8008CC70.field8 = *(s16 *)(D_800B0DF0 + 0x3E);
    D_8008CC70.fieldA = *(s16 *)(D_800B0DF0 + 0x40);
    D_8008CC70.fieldC = *(u16 *)(D_800B0DF0 + 2);
    D_8008CC70.fieldE = *(u16 *)D_800B0DF0;
    if (D_800B0DF0[0x46] != -1) {
        D_800DD2E0 = 1;
        temp_a0 = D_800B0DF0[0x46];
        func_151733E4((s32)temp_a0, (s32)temp_a0, arg0, 0, -1);
        return;
    }
    D_800DD2E0 = 0;
    func_151733E4(0, 0, arg0, 0, -1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151732E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A0790/func_151732E0.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151733D8 CURRENT (160) */
void *func_151733D8(void *arg0, s32 arg1) {
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151733D8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A0790/func_151733D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A0790/func_151733E4.s")
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
