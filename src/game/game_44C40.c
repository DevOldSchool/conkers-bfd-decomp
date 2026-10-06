#include "types.h"

/*
 * Reviewed source unit: src/game/game_44C40.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_early_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15017930
 * - func_15017B20
 * - func_15017FA4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_100226F0(void *, s32);
void func_1509BA04(s32);
void func_1509C120(void);
void func_150A00F0(void);
extern f32 D_800968C0;
extern f32 D_800D2DB0;
extern s8 D_800D2E41;
extern s8 D_800D2E42;
extern s8 D_800D2E44;
extern void *D_800D2E4C;
extern u8 D_800D2E50[];
extern u8 D_800D2E60[];
extern u8 D_800D2E70[];
extern u8 D_800D2F48[];
extern s32 D_800D3858;

void func_15017790(void) {
    func_1509C120();
    func_100226F0(D_800D2E4C, 0x1B);
    func_100226F0(D_800D2E50, 0x10);
    func_100226F0(D_800D2E60, 9);
    func_100226F0(D_800D2E70, 0xCC);
    D_800D2E44 = 0;
}
void func_150177F8(void) {
    func_1509BA04(1);
    func_100226F0(D_800D2F48, 0xC);
    func_150A00F0();
    D_800D2DB0 = D_800968C0;
    D_800D2E41 = 0xA;
    D_800D2E42 = 6;
    D_800D3858 = 0;
    D_800D2E44 = 0;
}
typedef struct Game44C40Node {
    u16 flags;
    s16 value;
} Game44C40Node;

void func_1509B4A0(s16, s32);
Game44C40Node *func_1509B704(s16);
extern s32 D_800BE9F0;
extern u8 D_800D2F3C;
extern s16 *D_800D2F40;

void func_15017868(void) {
    s32 index;
    s32 offset;
    Game44C40Node *node;

    index = 0;
    offset = 0;
    if ((s32) D_800D2F3C > 0) {
        do {
            node = func_1509B704(*(s16 *) ((u8 *) D_800D2F40 + offset));
            if ((node != 0) && (node->flags & 0x1000)) {
                node->value = (s16) D_800BE9F0;
            }
            index += 1;
            offset += 2;
        } while (index < (s32) D_800D2F3C);
    }
    func_1509BA04(0);
    func_1509B4A0(*(s16 *) ((u8 *) &D_800BE9F0 + 2), 1);
}
typedef struct Game44C40Entry {
    u8 pad0[0x15];
    u8 type;
    u8 pad16;
    u8 mode;
    u8 pad18[8];
    s32 state;
    u8 pad24[0x10];
} Game44C40Entry;

void *func_10003C40(s32, s32, s32, s32);
void func_15017B20(s32, u32);
u32 func_1502B7F0(s32 *, s32, ...);
extern u32 D_800D3094;
extern s32 D_800D3098;
extern u8 D_800D30D0[];
extern u8 D_800D30F0[];
extern s32 *D_800D3270;
extern s32 D_800D3274;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15017930 CURRENT (2145) */
void func_15017930(s32 arg0) {
    s32 *allocated;
    s32 *out;
    s32 type;
    s32 offset;
    s32 nextOffset;
    u32 index;
    u32 nextIndex;
    u8 mode;
    u8 nextMode;
    Game44C40Entry *entry;
    Game44C40Entry *next;

    D_800D3094 = func_1502B7F0(&D_800D3098, 3, 12, arg0, 5);
    D_800D3094 /= 52U;
    func_15017B20(D_800D3098, D_800D3094);
    D_800D3274 = 0;
    D_800D3270 = 0;
    index = 0;
    if (D_800D3094 != 0) {
        offset = 0;
        do {
            index++;
            entry = (Game44C40Entry *)(D_800D3098 + offset);
            type = (s32)entry->type >> 2;
            if (type == 1 && ((mode = entry->mode) == 2 || mode == 0 || mode == 6)) {
                D_800D3274++;
                type = (s32)entry->type >> 2;
            }
            if (type == 2 || type == 7) entry->state = 0;
            offset += sizeof(Game44C40Entry);
        } while (index < D_800D3094);
    }
    if (D_800D3274 != 0) {
        allocated = func_10003C40(D_800D3274 * 4, 1, 0, 0);
        D_800D3270 = allocated;
        if (allocated != 0) {
            out = allocated;
            nextIndex = 0;
            nextOffset = 0;
            if (D_800D3094 != 0) {
                do {
                    nextIndex++;
                    next = (Game44C40Entry *)(D_800D3098 + nextOffset);
                    if (((s32)next->type >> 2) == 1 &&
                        ((nextMode = next->mode) == 2 || nextMode == 0 || nextMode == 6)) {
                        *out = nextOffset + D_800D3098;
                        out++;
                    }
                    nextOffset += sizeof(Game44C40Entry);
                } while (nextIndex < D_800D3094);
            }
        }
    }
    func_100226F0(D_800D30F0, 0x180);
    func_100226F0(D_800D30D0, 0x20);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15017930 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_44C40/func_15017930.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_44C40/func_15017B20.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_44C40/func_15017FA4.s")
