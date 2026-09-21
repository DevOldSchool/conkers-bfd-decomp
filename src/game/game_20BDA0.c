#include "types.h"

/*
 * Reviewed source unit: src/game/game_20BDA0.c
 * Boundary evidence: docs/evidence/game_raw_dispatch_controller_core.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151DE8F0
 * - func_151DF1BC
 * - func_151DF574
 * - func_151DFF38
 * - func_151E0424
 * - func_151E09DC
 * - func_151E0B70
 * - func_151E1214
 * - func_151E1744
 * - func_151E22BC
 * - func_151E2404
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_20BDA0/func_151DE8F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20BDA0/func_151DF1BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20BDA0/func_151DF574.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20BDA0/func_151DFF38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20BDA0/func_151E0424.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20BDA0/func_151E09DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20BDA0/func_151E0B70.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20BDA0/func_151E1214.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_20BDA0/func_151E1744.s")
void func_151E530C(void);
void func_151E43DC(void);
extern s8 D_8008FD80;

void func_151E2284(void) {
    D_8008FD80 = 3;
    func_151E530C();
    func_151E43DC();
    D_8008FD80 = 0;
}
extern volatile s8 D_800E0BE0[];
extern u8 *D_8008FDD4;
extern s8 D_800AB690[];
extern s8 *D_80082BBC;
void func_151DD9E4();

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151E22BC CURRENT (4755) */
void func_151E22BC(void) {
    s32 index;
    u8 *record;
    volatile s8 *state;
    s32 value;

    index = D_800AB690[*(s8 *)(D_8008FDD4 + 0x42) * 10];
    record = (u8 *)D_80082BBC + index * 10;
    value = record[3];
    if (value >= 5) {
        record[3] = 4;
        value = 4;
    }
    if (value < 0) {
        record[3] = 0;
    }
    value = *(s8 *)(record + 1);
    state = D_800E0BE0;
    if (value <= 0) {
        record[1] = 1;
        value = *(s8 *)(record + 1);
    }
    state[2] = value;
    state[0xB] = 0;
    state[3] = *(s8 *)(record + 2);
    state[0x10] = record[3];
    state[0x11] = record[4];
    switch (index) {
        case 0:
            state[4] = record[5];
            break;
        case 1:
            state[0xD] = record[5];
            state[0xE] = record[6];
            break;
        case 2:
            state[0x12] = record[5];
            break;
        case 3:
            state[0x11] = 0;
            state[0x12] = record[5];
            break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            state[7] = record[5];
            state[0x11] = 1;
            state[3] = 2;
            state[0x13] = record[6];
            break;
    }
    state[0x16] = record[8];
    state[6] = record[9];
    func_151DD9E4();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151E22BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20BDA0/func_151E22BC.s")
extern volatile s8 D_800E0BE0[];
extern u8 *D_8008FDD4;
extern s8 D_800AB690[];
extern s8 *D_80082BBC;
void func_150076A0(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151E2404 */
void func_151E2404(void) {
    volatile s8 *source;
    s8 *record;
    s32 index;

    source = D_800E0BE0;
    index = D_800AB690[*(s8 *)(D_8008FDD4 + 0x42) * 10];
    record = D_80082BBC + (index * 10);
    record[0] = 0;
    record[1] = source[2];
    record[2] = source[3];
    record[3] = source[0x10];
    record[4] = source[0x11];
    switch (index) {
        case 0:
            record[5] = source[4];
            break;
        case 1:
            record[5] = source[0xD];
            record[6] = source[0xE];
            break;
        case 2:
            record[5] = source[0x12];
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            record[5] = source[7];
            record[6] = source[0x13];
            break;
    }
    record[8] = source[0x16];
    record[9] = source[6];
    func_150076A0();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151E2404 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20BDA0/func_151E2404.s")
