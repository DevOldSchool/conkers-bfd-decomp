#include "types.h"

/*
 * Reviewed source unit: src/game/game_12B7D0.c
 * Boundary evidence: docs/evidence/game_raw_slot_motion_attachment_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FE320
 * - func_150FE49C
 * - func_150FE604
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_12B7D0/func_150FE320.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_12B7D0/func_150FE49C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_12B7D0/func_150FE604.s")
extern void func_151D3E04(s32 arg0, s32 arg1, s32 *arg2, u8 arg3, f32 arg4);
extern u8 D_80088B94;
extern s32 D_800A1FC8;

void func_150FE794(s32 arg0, s32 arg1, s32 arg2) {
    func_151D3E04(arg0, arg2, &D_800A1FC8, D_80088B94, 0.0f);
}
u32 func_150ADA20(void *);
void func_151D8868(s8 *, s32, s32, s32);

void func_150FE7D4(void *arg0) {
    struct {
        s8 field_0;
        s8 pad1;
        s16 field_2;
        s8 field_4;
        s8 field_5;
        s8 field_6;
    } sp18;

    if (*(void **)((u8 *)arg0 + 0x318) != 0) {
        sp18.field_0 = 1;
        sp18.field_2 = (s16) ((func_150ADA20(arg0) % 13U) + 0x14);
        sp18.field_5 = (s8) (1 << *(u8 *)((u8 *)*(void **)((u8 *)arg0 + 0x318) + 0x23D));
        func_150ADA20(arg0);
        sp18.field_4 = 8;
        sp18.field_6 = -1;
        func_151D8868(&sp18.field_0, 0, 0xFF, 1);
    }
}
