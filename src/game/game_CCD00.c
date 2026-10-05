#include "types.h"

/*
 * Reviewed source unit: src/game/game_CCD00.c
 * Boundary evidence: docs/evidence/game_raw_descriptor_callback_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1509F850
 * - func_1509FE0C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_CCD00/func_1509F850.s")
typedef struct GameCCD00Node {
    u16 flags;
    u16 value;
} GameCCD00Node;

GameCCD00Node *func_1509B704(s16);
s32 func_151E5F64(s32);
f32 func_150ADA68(void);
s32 func_1517EFAC(s32);
extern u8 *D_800D2E4C;
extern s32 D_800BE9F0;
extern s32 D_800BE9F8;
extern s8 D_8008FD8C;
extern s8 D_80087270[];
extern u16 D_800D18A0;
extern s8 D_800BE3DF;
extern u8 D_800BE3E0;
extern s8 D_8008FD90;
extern s8 D_800E0BB1;
extern u16 D_8008FDBC;
extern u16 D_800BE930[];
extern u8 D_800BE918[];
extern u8 D_800E0B94;
extern s32 D_800E9D00;
extern s32 D_800D3840;
extern u8 D_800D2E40;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509FE0C CURRENT (1193) */
s32 func_1509FE0C(s32 arg0, s32 arg1, s32 *arg2) {
    s32 index;
    s32 total;
    s32 playerIndex;
    s32 threshold;
    s32 weight;
    s8 *player;
    s32 *entry;
    s32 *sumEntry;
    GameCCD00Node *node;

    switch (arg1) {
    case 26:
        return D_800D2E4C[arg0 >> 3] & (1 << (arg0 & 7));
    case 27:
        return func_1509B704((s16)arg0)->value;
    case 28:
        return D_800BE9F0;
    case 29:
        total = 0;
        playerIndex = 0;
        if (D_8008FD8C > 0) {
            player = D_80087270;
            do {
                if (*player != 10) {
                    total |= 1U << (playerIndex & 31);
                }
                playerIndex++;
                player++;
            } while (playerIndex < D_8008FD8C);
        }
        return total & ~D_800D18A0;
    case 30:
        return func_151E5F64(arg2[2]);
    case 31:
        return D_800BE9F8;
    case 32:
        return D_800BE3DF;
    case 33:
        return D_800BE3E0;
    case 34:
        total = 0;
        index = 0;
        if (arg2[2] > 0) {
            sumEntry = arg2;
            do {
                total = (s32)((u32)total + (u32)sumEntry[3]);
                sumEntry++;
            } while (sumEntry < arg2 + arg2[2]);
        }
        threshold = (s32)(func_150ADA68() * (f32)total);
        total = 0;
        entry = arg2;
        if (arg2[2] > 0) {
            do {
                weight = entry[3];
                total = (s32)((u32)total + (u32)weight);
                if (total >= threshold && weight != 0) {
                    return index;
                }
                index++;
                entry++;
            } while (index < arg2[2]);
        }
        return arg2[2] - 1;
    case 35:
        return D_8008FD90;
    case 36:
        return D_800E0BB1;
    case 37:
        return D_8008FDBC & 0x10;
    case 38:
        return D_8008FD8C;
    case 39:
        return D_800BE930[arg2[2]];
    case 40:
        return *(u16 *)(D_800BE918 + arg2[2] * 6);
    case 41:
        return D_800E0B94 == 2;
    case 42:
        return arg2[2] & D_800E9D00;
    case 43:
        node = func_1509B704((s16)arg0);
        if (node != 0) {
            return (node->flags & 0x2000) == 0;
        } else {
            return 0;
        }
    case 44:
        total = 0;
        if (D_800D3840 == 3) {
            total = arg2[2];
        }
        return func_1517EFAC(total);
    case 45:
        return D_800D2E40;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509FE0C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CCD00/func_1509FE0C.s")
