#include "types.h"

/*
 * Reviewed source unit: src/game/game_182C30.c
 * Boundary evidence: docs/evidence/game_raw_indexed_controller_view_worklist.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15155780
 * - func_151557FC
 * - func_1515589C
 * - func_15155CFC
 * - func_15155EF8
 * - func_15155F3C
 * - func_15155FD4
 * - func_15156028
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_182C30/func_15155780.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_182C30/func_151557FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_182C30/func_1515589C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_182C30/func_15155CFC.s")
extern void func_1515F10C(void *arg0);
extern void func_15169804(s32 arg0);
extern void func_1518CA04(s32 arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15155EF8 CURRENT (40) */
void func_15155EF8(void *arg0) {
    void *temp_a1;
    void *temp_a2;

    temp_a1 = arg0;
    temp_a2 = *(void **)((u8 *) temp_a1 + 0x14);
    if (temp_a2 != 0) {
        func_1515F10C(temp_a2);
    }
    func_15169804((s32) temp_a1);
    func_1518CA04(0xA6);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15155EF8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_182C30/func_15155EF8.s")
/* Call context: func_15155FD4: unique active project prototype */
void * func_15155FD4(s32);
extern u8 D_800C3E78;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15155F3C CURRENT (15) */
void func_15155F3C(void) {
    u8 temp_v1;
    void *temp_v0;

    temp_v0 = func_15155FD4(D_800C3E78);
    if (temp_v0 != 0) {
        temp_v1 = *(u8 *)((u8 *)temp_v0 + 0x11);
        if (temp_v1 == 2) {
            *(u8 *)((u8 *)temp_v0 + 0x11) = 0U;
            return;
        }
        if (temp_v1 == 3) {
            *(u8 *)((u8 *)temp_v0 + 0x11) = 2U;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15155F3C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_182C30/func_15155F3C.s")
void *func_15155FD4(s32);                           /* extern */
extern u8 D_800C3E78;

void func_15155F90(void) {
    void *temp_v0;

    temp_v0 = func_15155FD4(D_800C3E78);
    if ((temp_v0 != 0) && (*(u8 *)((u8 *)temp_v0 + 0x11) == 3)) {
        *(u8 *)((u8 *)temp_v0 + 0x11) = 1U;
    }
}
typedef struct Game182C30Node {
    u8 pad_0[8];
    struct Game182C30Node *next;
    u8 pad_C[4];
    u8 field_10;
} Game182C30Node;

typedef struct {
    u8 pad_0[0x140];
    Game182C30Node *field_140;
    u8 pad_144[0x5C];
} Game182C30Block;

extern Game182C30Block D_800DCE50;
extern Game182C30Block D_800DD190;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15155FD4 CURRENT (35) */
void *func_15155FD4(s32 arg0) {
    Game182C30Block *var_a1;
    Game182C30Node *var_v1;

    var_a1 = &D_800DCE50;
    do {
        var_v1 = var_a1->field_140;
        var_a1++;
        while (var_v1 != 0) {
            if (arg0 == var_v1->field_10) {
                return var_v1;
            }
            var_v1 = var_v1->next;
        }
    } while (var_a1 != &D_800DD190);
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15155FD4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_182C30/func_15155FD4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_182C30/func_15156028.s")
