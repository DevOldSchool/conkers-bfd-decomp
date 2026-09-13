#include "types.h"

/*
 * Reviewed source unit: src/game/game_138B40.c
 * Boundary evidence: docs/evidence/game_raw_call_connected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1510B690
 * - func_1510B7B4
 * - func_1510B958
 * - func_1510B9D0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_138B40/func_1510B690.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_138B40/func_1510B7B4.s")
typedef struct {
    u8 pad0[0x64];
    f32 base_x;
    f32 base_y;
    f32 scale_x;
    f32 scale_y;
    f32 value_x;
    f32 value_y;
    u8 pad7C[0x104];
} Game138B40Record;

extern Game138B40Record *D_800BE628;
extern volatile f32 D_800D35E0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510B958 CURRENT (460) */
void func_1510B958(s32 arg0) {
    Game138B40Record *record;

    record = &D_800BE628[arg0];
    D_800D35E0 = (((record->value_x / record->scale_x) - 1.0f) * -1.0f) + record->base_x;
    *(volatile f32 *)((u8 *)&D_800D35E0 + 4) = (((record->value_y / record->scale_y) - 1.0f) * -1.0f) + record->base_y;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510B958 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_138B40/func_1510B958.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_138B40/func_1510B9D0.s")
