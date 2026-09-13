#include "types.h"

/*
 * Reviewed source unit: src/game/game_C8950.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1509B4A0
 * - func_1509B570
 * - func_1509B5AC
 * - func_1509B704
 * - func_1509B764
 * - func_1509B810
 * - func_1509B8FC
 * - func_1509B950
 * - func_1509BA04
 * - func_1509BBA0
 * - func_1509BE40
 * - func_1509BFB0
 * - func_1509C120
 * - func_1509C228
 * - func_1509C3A0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameC8950Node {
    u16 key;
    u8 pad2[0x16];
    struct GameC8950Node *next;
} GameC8950Node;

typedef struct GameC8950List {
    u16 count;
    u8 pad2[2];
    GameC8950Node *head;
} GameC8950List;

extern GameC8950List D_800D2F48;

#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509B4A0.s")
GameC8950Node *func_1509B704(s16);                  /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509B570 CURRENT (454) */
void *func_1509B570(s16 arg0) {
    u8 *temp_v0;

    temp_v0 = func_1509B704(arg0, arg0);
    if (temp_v0 != 0) {
        return temp_v0 + *(u16 *)((u8 *)temp_v0 + 0xA);
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509B570 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509B570.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509B5AC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509B704 CURRENT (220) */
GameC8950Node *func_1509B704(s16 arg0) {
    s32 index;
    s32 mask;
    GameC8950Node *node;

    node = D_800D2F48.head;
    mask = 0xFFFF03FF;
    index = 0;
    if ((s32) D_800D2F48.count > 0) {
        do {
            index += 1;
            if (arg0 == (node->key & mask)) {
                return node;
            }
            node = node->next;
        } while (index < (s32) D_800D2F48.count);
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509B704 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509B704.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509B764.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509B810.s")
typedef struct {
    u16 field_0;
    s16 field_2;
} GameC8950Data;

GameC8950Data *func_1502B5C8(void *, s32, s32, s16);
void func_1509B950(void *);
extern s32 D_800BE9F0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509B8FC CURRENT (5) */
void func_1509B8FC(s16 arg0) {
    s16 sp18;
    GameC8950Data *temp_v0;

    temp_v0 = func_1502B5C8(&sp18, 2, 0x14, arg0);
    temp_v0->field_0 |= arg0;
    temp_v0->field_2 = D_800BE9F0;
    func_1509B950(temp_v0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509B8FC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509B8FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509B950.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509BA04.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509BBA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509BE40.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509BFB0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509C120.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509C228.s")
extern s32 D_800BE9F0;
extern u8 D_800D2E44;

s32 func_1509C2A4(void) {
    if ((D_800BE9F0 == 3) || (D_800BE9F0 == 5) || (D_800BE9F0 == 9) || (D_800BE9F0 == 0xD) || (D_800BE9F0 == 0xF) || (D_800BE9F0 == 0x11) || (D_800BE9F0 == 0x15) || (D_800BE9F0 == 0x16) || (D_800BE9F0 == 0x18) || (D_800BE9F0 == 0x1A) || (D_800BE9F0 == 0x1D) || (D_800BE9F0 == 0x1F) || (D_800BE9F0 == 0x20) || (D_800BE9F0 == 0x21) || (D_800BE9F0 == 0x22) || (D_800BE9F0 == 0x24) || (D_800BE9F0 == 0x25) || (D_800BE9F0 == 0x2A) || (D_800BE9F0 == 0x2B) || (D_800BE9F0 == 0x2D) || (D_800BE9F0 == 0x30) || (D_800BE9F0 == 0x33) || (D_800BE9F0 == 0x34) || (D_800BE9F0 == 0x38) || (D_800BE9F0 == 0x3E) || (D_800BE9F0 == 0x3F) || (D_800D2E44 != 0)) {
        return 0;
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_C8950/func_1509C3A0.s")
extern void *D_800D2E4C;

s32 func_1509C414(s32 arg0) {
    return ((*(u8 *)((u8 *)D_800D2E4C + 3) & 1) << 0xA) + arg0 + 0x1400;
}
