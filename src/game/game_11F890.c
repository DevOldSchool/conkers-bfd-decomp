#include "types.h"

/*
 * Reviewed source unit: src/game/game_11F890.c
 * Boundary evidence: docs/evidence/game_raw_table_selected_collections.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F23E0
 * - func_150F2480
 * - func_150F2518
 * - func_150F25A0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_11F890/func_150F23E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11F890/func_150F2480.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11F890/func_150F2518.s")
typedef struct Game11F890Work {
    u8 transform[0x30];
    f32 position_x;
    f32 position_y;
    f32 position_z;
} Game11F890Work;

void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
void func_150A8050(void *, f32, s32, f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F25A0 CURRENT (367) */
s32 func_150F25A0(u8 *arg0) {
    f32 output_z;
    f32 output_y;
    f32 output_x;
    Game11F890Work work;
    u8 *source;
    u8 **source_ptr;

    source = *(u8 **)(arg0 + 0x18);
    func_150A8050(&work, *(f32 *)(source + 0x20) * 3.0f, 0,
                  *(f32 *)(source + 0x28) * 3.0f);
    source_ptr = (u8 **)(arg0 + 0x18);
    work.position_x = *(f32 *)(*source_ptr + 0x38);
    work.position_y = *(f32 *)(*source_ptr + 0x3C);
    work.position_z = *(f32 *)(*source_ptr + 0x40);
    func_150A7960(&work, 0.0f, -495.0f, 0.0f,
                  &output_x, &output_y, &output_z);
    *(s16 *)(*(u8 **)(arg0 + 0x14) + 0xE) = (s32)output_x;
    *(s16 *)(*(u8 **)(arg0 + 0x14) + 0x10) = (s32)output_y;
    *(s16 *)(*(u8 **)(arg0 + 0x14) + 0x12) = (s32)output_z;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F25A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11F890/func_150F25A0.s")
