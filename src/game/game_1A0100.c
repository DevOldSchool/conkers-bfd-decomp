#include "types.h"

/*
 * Reviewed source unit: src/game/game_1A0100.c
 * Boundary evidence: docs/evidence/game_raw_slot_view_controller_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15172C50
 * - func_15172CA8
 * - func_15172D80
 * - func_15172E7C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    u8 field_0;
    u8 field_1;
    u8 field_2;
    u8 field_3;
} Game1A0100Record;

extern Game1A0100Record D_800DD2B0;
extern Game1A0100Record D_800DD2C0;
extern Game1A0100Record D_800DD2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15172C50 CURRENT (5195) */
void func_15172C50(s8 arg0) {
    Game1A0100Record *var_v1;
    Game1A0100Record *var_a1;

    var_a1 = &D_800DD2C0;
    var_v1 = &D_800DD2B0;
    do {
        var_a1++;
        var_v1->field_1 = 0xFF;
        var_a1[-1].field_1 = 0;
        var_v1->field_2 = 0xFF;
        var_a1[-1].field_2 = 0;
        var_v1->field_3 = 0xFF;
        var_a1[-1].field_3 = 0;
        var_v1++;
        var_v1[-1].field_0 = 0xFF;
        var_a1[-1].field_0 = 0;
    } while (var_a1 != &D_800DD2D0);
    D_800DD2C0.field_0 = arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15172C50 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A0100/func_15172C50.s")
void func_1517EE40(s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15172CA8 CURRENT (100) */
void func_15172CA8(s32 arg0) {
    s8 *temp_v0;

    temp_v0 = (s8 *)&D_800DD2B0 + arg0;
    if (*temp_v0 != -1) {
        *temp_v0 = -1;
        func_1517EE40(0, 0, 0, 0, 1, arg0);
        func_1517EE40(0, 0, 0, 0x32, 0, arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15172CA8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A0100/func_15172CA8.s")
void func_15085430(void *, s32, s32);
extern u8 D_800BE9B4;

void func_15172D28(void *arg0, s32 arg1) {
    void *temp_v0;

    func_15085430(arg0, arg1, 1);
    *(u16 *)((u8 *)arg0 + 0x2F8) &= 0xFFEF;
    if (D_800BE9B4 == 0) {
        temp_v0 = *(void **)((u8 *)arg0 + 0x31C);
        if (temp_v0 != 0) {
            *(s8 *)((u8 *)temp_v0 + 0x56) = 3;
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A0100/func_15172D80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A0100/func_15172E7C.s")
