#include "types.h"

/*
 * Reviewed source unit: src/game/game_44C40.c
 * Boundary evidence: docs/evidence/game_early_callback_state_groups.md
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_44C40/func_15017930.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_44C40/func_15017B20.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_44C40/func_15017FA4.s")
