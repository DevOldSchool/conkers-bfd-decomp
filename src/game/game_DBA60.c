#include "types.h"

/*
 * Reviewed source unit: src/game/game_DBA60.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150AE5B0
 * - func_150AE790
 * - func_150AEB9C
 * - func_150AECCC
 * - func_150AED4C
 * - func_150AED9C
 * - func_150AEDF8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_DBA60/func_150AE5B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_DBA60/func_150AE790.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_DBA60/func_150AEB9C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_DBA60/func_150AECCC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_DBA60/func_150AED4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_DBA60/func_150AED9C.s")
typedef struct GameDBA60Object {
    u8 pad0[0x1C];
    s16 field_1C;
    u8 pad1E[0xA];
    s8 field_28;
} GameDBA60Object;

s32 func_150AEDD8(GameDBA60Object *arg0) {
    s16 value = arg0->field_1C;

    if (value < 0x20) {
        arg0->field_28 = value * 8;
    }

    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_DBA60/func_150AEDF8.s")
