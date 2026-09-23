#include "types.h"

/*
 * Reviewed source unit: src/game/game_CA630.c
 * Boundary evidence: docs/evidence/game_raw_descriptor_callback_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1509D180
 * - func_1509D780
 * - func_1509D8FC
 * - func_1509DBBC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameCA630Node {
    u8 pad0[8];
    struct GameCA630Node *next;
    u8 padC[0x3C];
    u8 kind;
} GameCA630Node;

extern s32 D_800A6060[];
extern u8 D_800DCE50[];
void func_150E36BC(s32, s32 *, s32 *, s32 *);

#pragma GLOBAL_ASM("asm/nonmatchings/game_CA630/func_1509D180.s")
void func_150B3DD0(void);
void func_150C5C9C(void *);
void func_150F6DB0(void *);
void func_151CD394(s32);
void func_151D2718(s16);
void *func_1505EEF4(s32);
void func_150C522C(void);
void func_150E35DC(s32);
void func_150EB8C4(void);
void func_150F9720(u8);
void func_151616D0(s32, s32, s32);
extern s8 D_800D9920;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509D780 CURRENT (600) */
void func_1509D780(s32 arg0, u8 *arg1) {
    void *temp_v0;

    switch (arg0) {
    case 41:
        func_150EB8C4();
        return;
    case 39:
        func_150F9720(arg1[7]);
        return;
    case 38:
        func_151616D0(0x29, 0x18, 0);
        return;
    case 36:
        temp_v0 = func_1505EEF4(*(s32 *)(arg1 + 4) & 0xFFF);
        if (temp_v0 != 0) {
            func_150F6DB0(temp_v0);
        }
        return;
    case 26:
        func_151616D0(0x26, 0x18, 0);
        return;
    case 18:
        func_151CD394(*(s32 *)(arg1 + 4));
        return;
    case 2:
        D_800D9920 = 0;
        return;
    case 4:
    case 5:
    case 6:
        func_150E35DC(arg0 >> 6);
        return;
    case 8:
        func_150B3DD0();
        return;
    case 9:
        temp_v0 = func_1505EEF4(*(s32 *)(arg1 + 4) & 0xFFF);
        if (temp_v0 != 0) {
            func_150C5C9C(temp_v0);
            return;
        }
        break;
    case 10:
        func_150C522C();
        return;
    case 19:
        func_151D2718(*(s16 *)(arg1 + 6));
        return;
    case 21:
        func_151616D0(0x20, 0x18, 0);
        return;
    case 22:
        func_151616D0(0x23, 0x28, 0);
        func_151616D0(0x24, 0x28, 0);
        break;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509D780 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CA630/func_1509D780.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CA630/func_1509D8FC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509DBBC CURRENT (3648) */
s32 func_1509DBBC(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp3C = 0;
    s32 sp38 = 0;
    s32 sp34 = 0;
    s32 result = 4;
    s32 outer;
    s8 inner;
    GameCA630Node *node;

    if ((arg0 != 4) && (arg0 != 5) && (arg0 != 6)) {
        if ((arg0 == 0x19) && (arg1 == 4)) {
            outer = 0;
            do {
                inner = 0;
                do {
                    node = *(GameCA630Node **)(D_800DCE50 + (outer * 0x1A0) + (D_800A6060[inner] * 4));
                    inner++;
                    while (node != 0) {
                        if (node->kind == 2) {
                            return 0;
                        }
                        node = node->next;
                    }
                } while (inner < 3);
                outer = (outer + 1) & 0xFF;
            } while (outer < 2);
            return 1;
        }
        return result;
    }
    if ((arg1 == 0) || (arg1 == 1)) {
        s32 index = arg0 >> 6;
        if (index != 0) {
            func_150E36BC(index, &sp3C, &sp38, &sp34);
            if (arg1 == 0) {
                sp38 = (sp3C << 16) | (sp34 & 0xFFFF);
            }
            result = sp38;
        }
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509DBBC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CA630/func_1509DBBC.s")
