#include "types.h"

/*
 * Reviewed source unit: src/game/game_3FC60.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_parser_actor_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15012ED8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game3FC60Scene {
    u8 pad0[0x21];
    u8 flags;
} Game3FC60Scene;

typedef struct Game3FC60Record {
    u8 pad0[0x16];
    u16 count;
    u8 pad18[0x10];
    u8 *colors;
    u8 pad2C[0x74];
} Game3FC60Record;

typedef struct Game3FC60Color {
    u8 pad0[0xC];
    u8 r;
    u8 g;
    u8 b;
    u8 padF;
} Game3FC60Color;

typedef struct Game3FC60Group {
    s32 pad0;
    u16 *indices;
    s32 count;
} Game3FC60Group;

void *func_10003C40(s32, s32, s32, s32);
void func_100226F0(void *, s32);
void func_15012C84(u8 *, s32);
void func_15012ED8(u32 *);
extern Game3FC60Scene *D_800B0DF0;
extern u32 *D_800B0E00;
extern u8 *D_800B0E10[4];
extern Game3FC60Group **D_800B0E30;
extern u8 *D_800B0E34;
extern u8 D_800B0E38;
extern s32 D_800B0E40[4];
extern s32 D_800BE510;
extern u8 ***D_800BE520;
extern u16 *D_800BE524;
extern u16 D_800BE528;
extern u8 D_800BE564;
extern s32 D_800DBEF0;
extern Game3FC60Record *D_800DBEF4;

void func_150127B0(void) {
    s32 total;
    s32 i;
    s32 j;
    s32 k;
    u8 *colors;
    Game3FC60Group *groups;

    D_800BE520 = NULL;
    if (D_800B0DF0->flags != 0) {
        total = 0;
        if (D_800B0DF0->flags & 1) {
            for (i = 0; i < 4; i++) {
                total += D_800B0E40[i];
            }
        }
        if (D_800B0DF0->flags & 2) {
            for (i = 0; i < D_800DBEF0; i++) {
                total += D_800DBEF4[i].count;
            }
        }
        ((u8 **)&D_800BE510)[0] = func_10003C40(total * 3, 1, 0, 0);
        if (((u8 **)&D_800BE510)[0] == NULL) {
            ((u8 **)&D_800BE510)[1] = NULL;
            return;
        }
        D_800BE528 = 0;
        D_800BE564 = 0;
        if (D_800B0DF0->flags & 1) {
            for (i = 0; i < 4; i++) {
                if (D_800B0E10[i] != NULL) {
                    ((u8 **)&D_800BE510)[i] = ((u8 **)&D_800BE510)[0] + D_800BE528 * 3U;
                    func_15012C84(D_800B0E10[i], D_800B0E40[i]);
                } else {
                    ((u8 **)&D_800BE510)[i] = NULL;
                }
            }
        }
        if (D_800B0DF0->flags & 2) {
            D_800BE524 = func_10003C40(D_800DBEF0 * 2, 1, 0, 0);
            for (i = 0; i < D_800DBEF0; i++) {
                if (D_800DBEF4[i].count != 0) {
                    D_800BE524[i] = D_800BE528;
                    func_15012C84(D_800DBEF4[i].colors, D_800DBEF4[i].count);
                } else {
                    D_800BE524[i] = 0xFFFF;
                }
            }
        }
        if (D_800B0DF0->flags & 4) {
            D_800BE520 = func_10003C40(D_800B0E38 * 4, 1, 0, 0);
            func_100226F0(D_800BE520, D_800B0E38 * 4);
            for (i = 0; i < D_800B0E38; i++) {
                if (D_800B0E34[i] == 0) {
                    continue;
                }
                D_800BE520[i] = func_10003C40(D_800B0E34[i] * 4, 1, 0, 0);
                groups = D_800B0E30[i];
                for (j = 0; j < D_800B0E34[i]; j++) {
                    D_800BE520[i][j] = func_10003C40(groups[j].count * 3, 1, 0, 0);
                    if (i < 4) {
                        colors = D_800B0E10[i];
                    } else {
                        colors = D_800DBEF4[i - 4].colors;
                    }
                    for (k = 0; k < groups[j].count; k++) {
                        D_800BE520[i][j][k * 3 + 0] = ((Game3FC60Color *)colors)[groups[j].indices[k]].r;
                        D_800BE520[i][j][k * 3 + 1] = ((Game3FC60Color *)colors)[groups[j].indices[k]].g;
                        D_800BE520[i][j][k * 3 + 2] = ((Game3FC60Color *)colors)[groups[j].indices[k]].b;
                    }
                }
            }
        }
        func_15012ED8(D_800B0E00);
    }
}
extern s32 D_800BE510;
extern u16 D_800BE528;

void func_15012C84(u8 *arg0, s32 arg1) {
    u32 i;

    for (i = 0; i < (u32)arg1; i++) {
        ((u8 **)&D_800BE510)[0][D_800BE528 * 3U] = ((Game3FC60Color *)arg0)[i].r;
        ((u8 **)&D_800BE510)[0][D_800BE528 * 3U + 1] = ((Game3FC60Color *)arg0)[i].g;
        ((u8 **)&D_800BE510)[0][D_800BE528 * 3U + 2] = ((Game3FC60Color *)arg0)[i].b;
        D_800BE528++;
    }
}
extern u8 D_800BE530[];
extern s16 D_800BE550[];
extern u8 D_800BE564;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15012ED8 CURRENT (300) */
void func_15012ED8(u32 *arg0) {
    u32 index;
    s32 tag;
    u32 *record;
    u8 value;
    u8 *output;

    index = 0;
    tag = *arg0;
    record = arg0;
    tag = (s8)((u32)tag >> 24);
    while (tag != -0x21) {
        if (tag == -5) {
            tag = D_800BE564;
            D_800BE550[tag] = index;
            output = D_800BE530 + (tag * 3);
            output[0] = (u8)(record[1] >> 24);
            D_800BE564 = tag + 1;
            output[1] = (u8)(record[1] >> 16);
            value = (u8)(record[1] >> 8);
            output[2] = value;
        }
        tag = record[2];
        index += 1;
        record += 2;
        tag = (s8)((u32)tag >> 24);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15012ED8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_3FC60/func_15012ED8.s")
