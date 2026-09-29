#include "types.h"

/*
 * Reviewed source unit: src/game/game_105A40.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D85AC
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
s32 func_150D88AC(void *arg0) {
    u8 var_v0;

    var_v0 = 1;
    if (*(u8 *)(*(u8 **)((u8 *)arg0 + 0x18) + 0x6F) != 0) {
        *(u8 *)(*(u8 **)((u8 *)arg0 + 0x14) + 9) = 0;
    } else {
        *(u8 *)(*(u8 **)((u8 *)arg0 + 0x14) + 9) = 1;
    }
    return (s32) var_v0;
}
