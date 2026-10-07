#include "types.h"

/*
 * Reviewed source unit: src/game/game_10D080.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150DFBD0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_150DF8C0(s32);
s32 func_1510D0EC(s32, s32 *, s32, s32);
extern u8 D_80090324;
extern u8 D_800DD405;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DFBD0 CURRENT (540) */
void *func_150DFBD0(void *arg0) {
    struct Command { s32 word0; s32 word1; };
    struct Command *command;
    s32 result;
    s32 workspace[2];
    s32 source;
    s32 index;
    s32 command_offset;

    index = 0;
    command_offset = 8;
    do {
        if (func_150DF8C0(index) != 0) {
            result = D_800DD405;
            source = *(s32 *)((u8 *)&D_80090324 + (result * 4) + 0x24);
        } else {
            source = *(s32 *)((u8 *)&D_80090324 + 0x20);
        }
        result = func_1510D0EC(source, workspace, 3, 0);
        command = arg0;
        command->word0 = (command_offset & 0xFFFF) | 0xDB060000;
        command->word1 = result;
        arg0 = command + 1;
        index++;
        command_offset += 4;
    } while (index != 3);
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DFBD0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10D080/func_150DFBD0.s")
extern f32 D_800A0FA0;
extern f32 D_800A0FA4;
extern f32 D_800A0FA8;
extern f32 D_800A0FAC;
extern s32 D_800BE9E4;

void func_150DFCA8(void *arg0) {
    f32 temp_fa0;
    f32 var_fv0;

    var_fv0 = *(f32 *)((u8 *)arg0 + 0x64) * (f32)D_800BE9E4;
    *(f32 *)((u8 *)arg0 + 4) += var_fv0;
    temp_fa0 = *(f32 *)((u8 *)arg0 + 4);
    if (temp_fa0 < 11.0f) {
        var_fv0 = D_800A0FA0;
        *(f32 *)((u8 *)arg0 + 0x7C) = var_fv0;
    } else if (*(f32 *)((u8 *)arg0 + 4) > 55.0f) {
        temp_fa0 = D_800A0FA4;
        var_fv0 = -temp_fa0;
        *(f32 *)((u8 *)arg0 + 0x7C) = var_fv0;
    } else {
        var_fv0 = *(f32 *)((u8 *)arg0 + 0x7C);
    }
    if (*(f32 *)((u8 *)arg0 + 0x64) < var_fv0) {
        *(f32 *)((u8 *)arg0 + 0x64) = (f32) (*(f32 *)((u8 *)arg0 + 0x64) + D_800A0FA8);
        if (var_fv0 < *(f32 *)((u8 *)arg0 + 0x64)) {
            *(f32 *)((u8 *)arg0 + 0x64) = var_fv0;
        }
    } else if (var_fv0 < *(f32 *)((u8 *)arg0 + 0x64)) {
        *(f32 *)((u8 *)arg0 + 0x64) = (f32) (*(f32 *)((u8 *)arg0 + 0x64) - D_800A0FAC);
        if (*(f32 *)((u8 *)arg0 + 0x64) < var_fv0) {
            *(f32 *)((u8 *)arg0 + 0x64) = var_fv0;
        }
    }
}
extern f32 D_800A0FB0;

void func_150DFDA4(void *arg0) {
    void *temp_v0;

    temp_v0 = (void *)(*(s32 *)((u8 *)arg0 + 0x1D4) + 0x40);
    *(f32 *)((u8 *)temp_v0 + 0x30) = (f32) *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)((u8 *)temp_v0 + 0x34) = (f32) D_800A0FB0;
    *(f32 *)((u8 *)temp_v0 + 0x38) = (f32) *(f32 *)((u8 *)arg0 + 0x1C);
}
