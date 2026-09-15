#include "types.h"

/*
 * Reviewed source unit: src/game/game_205C90.c
 * Boundary evidence: docs/evidence/game_raw_slot_view_controller_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151D87E0
 * - func_151D8868
 * - func_151D8A24
 * - func_151D8B24
 * - func_151D8C00
 * - func_151D8DB4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern u8 D_80084060[4];
extern u8 D_800BE944[4];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D87E0 CURRENT (315) */
s32 func_151D87E0(u8 arg0) {
    s32 var_a1;
    s32 var_v1;
    s32 var_v0;
    u8 temp_a0;

    var_v0 = 0;
    var_v1 = arg0;
    var_a1 = 0;
loop_1:
    if (var_v1 & (1 << var_a1)) {
        temp_a0 = D_80084060[var_v0];
        if ((s32)temp_a0 >= 4) {
            return 0;
        }
        if (D_800BE944[temp_a0] != 0) {
            return 1;
        }
    }
    var_a1 = (var_v0 + 1) & 0xFF;
    var_v0 = var_a1;
    if (var_a1 < 4) {
        goto loop_1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D87E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_205C90/func_151D87E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_205C90/func_151D8868.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_205C90/func_151D8A24.s")
/* Call context: func_1501C17C: unique active project prototype */
void func_1501C17C(s32);
void func_151D8B24(s32);
void func_1516972C(void *arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D8B24 CURRENT (45) */
void func_151D8B24(s32 arg0) {
    s32 var_s0;
    s32 var_v0;

    var_s0 = 0;
    var_v0 = 0;
    do {
        if (*(u8 *)((u8 *)arg0 + 0x13) & (1 << var_v0)) {
            func_1501C17C(var_s0 & 0xFF);
        }
        var_v0 = (var_s0 + 1) & 0xFF;
        var_s0 = var_v0;
    } while (var_v0 < 4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D8B24 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_205C90/func_151D8B24.s")
void func_151D8B24(s32 arg0);
void func_15169804(s32 arg0);
void func_15169824(s32 arg0);

void func_151D8B88(s32 arg0) {
    func_151D8B24(arg0);
    func_15169804(arg0);
}
void func_151D8BB4(s32 arg0) {
    func_151D8B24(arg0);
    func_15169824(arg0);
}
void func_151D8BE0(s32 arg0) {
    func_151D8C00(arg0, arg0 + 0x18);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_205C90/func_151D8C00.s")
void func_151D8D5C(void *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x58) {
        func_1516972C(arg0);
        return;
    }
    if (arg2 == 0x47) {
        func_1516972C(arg0);
    }
}
void func_15169260(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 D_800AB300;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D8DB4 CURRENT (400) */
void func_151D8DB4(s32 arg0, s32 arg1) {
    func_15169260(&D_800AB300, 1, arg0, arg1 & 0xFF);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D8DB4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_205C90/func_151D8DB4.s")
void func_151D8DB4(s32 arg0, s32 arg1);
extern s8 D_800E0A00;

void func_151D8DE8(void) {
    D_800E0A00 = 1;
    func_151D8DB4(0, 0x58);
}
