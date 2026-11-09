#include "types.h"

/*
 * Reviewed source unit: src/game/game_10D080.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_segments_continued.md
 */

s32 func_150DF8C0(s32);
s32 func_1510D0EC(s32, s32 *, s32, s32);
extern u8 D_80090324;
extern u8 D_800DD405;

typedef struct { u32 w0; u32 w1; } Game10D080Command;
void *func_150DFBD0(Game10D080Command *arg0) {
    s32 i;
    s32 segment;
    s32 workspace[2];
    s32 source;
    s32 result;

    for (i = 0, segment = 2; i != 3; i++, segment++) {
        if (func_150DF8C0(i) != 0) {
            result = D_800DD405;
            source = *(s32 *)((u8 *)&D_80090324 + (result * 4) + 0x24);
        } else {
            source = *(s32 *)((u8 *)&D_80090324 + 0x20);
        }
        result = func_1510D0EC(source, workspace, 3, 0);
        { Game10D080Command *command = arg0++; command->w0 = ((segment * 4) & 0xFFFF) | 0xDB060000; command->w1 = result; }
    }
    return arg0;
}
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
