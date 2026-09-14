#include "types.h"

/*
 * Reviewed source unit: src/game/game_14EE80.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151219D0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_14EE80/func_151219D0.s")
typedef struct {
    u8 pad_0[0x37C];
    f32 field_37C;
    u8 pad_380[0x1C];
    f32 field_39C;
    u8 pad_3A0[0x414];
    f32 field_7B4;
    u8 pad_7B8[0x108];
    u8 field_8C0;
} Game14EE80State;

void func_15049688(void *, f32, void *, f32, f32, f32);
extern f32 D_800A3430;

void func_15121C00(Game14EE80State *arg0, f32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    func_15049688(&arg0->field_37C, arg1, &arg0->field_8C0, arg3,
                  arg4, arg0->field_7B4);
    arg0->field_39C = arg0->field_37C * D_800A3430;
}
void func_15121C64(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
}
