#include "types.h"

/*
 * Reviewed source unit: src/game/game_105A40.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D85AC
 * - func_150D88AC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game105A40Header {
    s16 field_0;
    s16 field_2;
} Game105A40Header;

Game105A40Header *func_150D8590(Game105A40Header *arg0, s32 arg1) {
    arg0->field_0 = 0x42;
    arg0->field_2 = 0;
    return arg0 + 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_105A40/func_150D85AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_105A40/func_150D88AC.s")
