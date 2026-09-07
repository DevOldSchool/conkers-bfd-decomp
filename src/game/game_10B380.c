#include "types.h"

/*
 * Reviewed source unit: src/game/game_10B380.c
 * Boundary evidence: docs/evidence/game_raw_code_selected_callback_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150DDED0
 * - func_150DDF88
 * - func_150DDFAC
 * - func_150DE12C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_10B380/func_150DDED0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_10B380/func_150DDF88.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_10B380/func_150DDFAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_10B380/func_150DE12C.s")
typedef struct Game10B380Object {
    u8 pad0[0x1C];
    s16 field_1C;
    u8 pad1E[0xA];
    s8 field_28;
} Game10B380Object;

s32 func_150DE2A4(Game10B380Object *arg0) {
    s16 value = arg0->field_1C;

    if (value < 0x20) {
        arg0->field_28 = value * 8;
    }

    return 1;
}
void func_150DE2C4(void *arg0) {
    *(s16 *)((u8 *)arg0 + 0x34) = (s16) (*(s16 *)((u8 *)arg0 + 0x34) - 0x1A);
    *(s16 *)((u8 *)arg0 + 0x36) = (s16) (*(s16 *)((u8 *)arg0 + 0x36) - 0x1A);
    if ((*(s16 *)((u8 *)arg0 + 0x34) < 0xA) || (*(s16 *)((u8 *)arg0 + 0x36) < 0xA)) {
        *(s16 *)((u8 *)arg0 + 0x38) = 0;
    }
}
