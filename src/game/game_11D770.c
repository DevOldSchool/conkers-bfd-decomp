#include "types.h"

/*
 * Reviewed source unit: src/game/game_11D770.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F02C0
 * - func_150F02EC
 * - func_150F0328
 * - func_150F0354
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game11D770Inner {
    u8 pad0[0x134];
    s32 field_134;
} Game11D770Inner;

typedef struct Game11D770Object {
    u8 pad0[0x28];
    Game11D770Inner *inner;
} Game11D770Object;

#pragma GLOBAL_ASM("asm/nonmatchings/game_11D770/func_150F02C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D770/func_150F02EC.s")
Game11D770Inner *func_150F0318(Game11D770Object *arg0) {
    Game11D770Inner *inner = arg0->inner;

    inner->field_134 = 0;
    return inner;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D770/func_150F0328.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_11D770/func_150F0354.s")
