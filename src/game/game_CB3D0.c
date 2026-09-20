#include "types.h"

/*
 * Reviewed source unit: src/game/game_CB3D0.c
 * Boundary evidence: docs/evidence/game_raw_descriptor_callback_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1509DFC4
 * - func_1509E3DC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern f32 D_800D2FC0[];
extern f32 D_800D2FD8[];
extern u8 D_800D2FEC[];
extern s32 D_800D3840;

typedef struct GameCB3D0Record {
    s32 pad0;
    s32 type;
    s32 index;
    s32 value;
} GameCB3D0Record;

void func_1509DF20(volatile s32 arg0, GameCB3D0Record *arg1) {
    if ((arg1->type == 1) && (D_800D3840 == 3)) {
        D_800D2FC0[arg1->index] = (f32)arg1->value * 0.000015258789f;
        D_800D2FD8[arg1->index] = (f32)arg1->value * 0.000015258789f;
        D_800D2FEC[arg1->index] = 1;
    }
}
void func_1509DFB4(s32 arg0, s32 arg1) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_CB3D0/func_1509DFC4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_CB3D0/func_1509E3DC.s")
