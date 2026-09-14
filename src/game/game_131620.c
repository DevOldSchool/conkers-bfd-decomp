#include "types.h"

/*
 * Reviewed source unit: src/game/game_131620.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151041E4
 * - func_1510448C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game131620Effect {
    u8 pad0[0x10];
    s32 field_10;
    s32 field_14;
    s16 field_18;
    s8 field_1A;
    s8 field_1B;
    s8 field_1C;
    u8 pad1D[3];
} Game131620Effect;

Game131620Effect *func_15167A68(s32, s32, s32, s32, u8, u8);

void func_15104170(s32 arg0, s32 arg1, s32 arg2) {
    Game131620Effect *effect;

    effect = func_15167A68(0x64, 0, sizeof(*effect), 0, 0xFF, 1);
    if (effect != 0) {
        effect->field_18 = 0xF;
        effect->field_1A = 0;
        effect->field_1B = 0;
        effect->field_10 = arg1;
        effect->field_14 = arg2;
        effect->field_1C = arg0;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_131620/func_151041E4.s")
typedef struct Game131620ScaleState {
    u8 pad0[0x1B];
    u8 scale;
} Game131620ScaleState;

s32 func_1517F08C(s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510448C CURRENT (275) */
s32 func_1510448C(s32 arg0, Game131620ScaleState * volatile arg1, s16 arg2) {
    u8 temp_v0;

    if ((arg2 != 0) || ((temp_v0 = arg1->scale) == 0)) {
        return arg0;
    }
    return func_1517F08C(arg0, (temp_v0 * 0x3F) >> 8, 0, 0, 0, arg2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510448C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_131620/func_1510448C.s")
extern void *D_800CC5EC;

u8 func_151044F4(void) {
    if (D_800CC5EC != 0) {
        return *(u8 *)((u8 *)D_800CC5EC + 0x7D);
    }
    return 0U;
}
