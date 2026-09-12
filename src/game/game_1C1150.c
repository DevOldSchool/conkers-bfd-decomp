#include "types.h"

/*
 * Reviewed source unit: src/game/game_1C1150.c
 * Boundary evidence: docs/evidence/game_raw_dispatch_position_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15193CA0
 * - func_15194320
 * - func_15194394
 * - func_15194408
 * - func_151945CC
 * - func_15194794
 * - func_15194810
 * - func_151949F4
 * - func_15194B1C
 * - func_15194B94
 * - func_15194BF0
 * - func_15194DC8
 * - func_15194EA8
 * - func_15194F48
 * - func_15194FF4
 * - func_151951E0
 * - func_15195528
 * - func_15195698
 * - func_15195738
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1C1150/func_15193CA0.s")
void func_15193CA0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_151942B0(s32 arg0, s32 arg1, s32 arg2) {
    func_15193CA0(arg1, 0, 0xFF, 1);
}
void func_151942E8(s32 arg0, s32 arg1, s32 arg2) {
    func_15193CA0(arg1, 1, 0xFF, 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1C1150/func_15194320.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1C1150/func_15194394.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1C1150/func_15194408.s")
extern void func_150C7020(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_15194408(s32 arg0, s32 arg1);

void func_15194588(s32 arg0, s32 arg1, s32 arg2) {
    func_150C7020(arg0, 0x1F4, 0xFF, 1);
    func_15194408(arg0, arg1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1C1150/func_151945CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1C1150/func_15194794.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1C1150/func_15194810.s")
void func_151949E0(s32 arg0, s32 arg1, s32 arg2) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1C1150/func_151949F4.s")
void func_1507DE4C(s32 arg0);
void func_15138BC0(s32 arg0, s32 arg1, s32 arg2);
void func_151949F4(s32 arg0, s32 arg1, s32 arg2);

void func_15194A68(s32 arg0, s32 arg1, s32 arg2) {
    func_1507DE4C(arg1);
    func_15138BC0(arg1, 0xFF, 1);
    func_151949F4(0, arg0, arg1);
}
/* Call context: func_15083568: unique active project prototype */
void func_15083568(void *, s32, s32, s32);

void func_15194AB4(void *arg0) {
    s32 var_a1;
    u8 temp_v0;

    temp_v0 = *(u8 *)((u8 *)arg0 + 4);
    *(s32 *)((u8 *)arg0 + 0x9C) = (s32) (*(s32 *)((u8 *)arg0 + 0x9C) | 0xFFFE);
    var_a1 = -1;
    switch (temp_v0) {                              /* irregular */
    case 0x75:
        var_a1 = 0x73;
        break;
    case 0x80:
        var_a1 = 0x72;
        break;
    }
    if (var_a1 != -1) {
        func_15083568(arg0, var_a1, 0x3F800000, 0);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1C1150/func_15194B1C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1C1150/func_15194B94.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1C1150/func_15194BF0.s")
/* Call context: func_15194FF4: raw o32 argument homes in asm/nonmatchings/game_1C1150/func_15194FF4.s; pointer uses in entry block; caller discards result */
void func_15194FF4(s32, s32, s32); /* CONKER_ABI_DISCARDED_RETURN */

void func_15194D80(s32 arg0, s32 arg1, s32 arg2) {
    func_15194FF4(arg0, arg1, 0);
}
/* Call context: func_15194FF4: raw o32 argument homes in asm/nonmatchings/game_1C1150/func_15194FF4.s; pointer uses in entry block; caller discards result */

void func_15194DA4(s32 arg0, s32 arg1, s32 arg2) {
    func_15194FF4(arg0, arg1, 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1C1150/func_15194DC8.s")
typedef struct {
    u8 pad_0[4];
    u8 field_4;
} Game1C1150Data;

void func_150B06B0(void *, s32, s32, s32);

void func_15194E54(s32 arg0, Game1C1150Data *arg1, s32 arg2) {
    u8 temp_v0;

    temp_v0 = arg1->field_4;
    if ((temp_v0 == 0x3E) || (temp_v0 == 0xA6)) {
        func_150B06B0(arg1, arg0, 0xFF, 1);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1C1150/func_15194EA8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1C1150/func_15194F48.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1C1150/func_15194FF4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1C1150/func_151951E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1C1150/func_15195528.s")
/* Call context: func_151B01B8: unique active project prototype */
/* Call context: func_151B09BC: unique active project prototype */
void func_151B01B8(u8 *, s32);
void func_151B09BC(u8 *, s32, s32, s32, s32);

void func_15195650(u8 *arg0, s32 arg1, s32 arg2) {
    func_151B01B8(arg0, arg1);
    func_151B09BC(arg0, arg1, 0x3E8, 0xFF, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1C1150/func_15195698.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1C1150/func_15195738.s")
