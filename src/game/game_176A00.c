#include "types.h"

/*
 * Reviewed source unit: src/game/game_176A00.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15149550
 * - func_15149838
 * - func_15149A94
 * - func_15149BF4
 * - func_15149C58
 * - func_15149D18
 * - func_15149EC4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_176A00/func_15149550.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_176A00/func_15149838.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_176A00/func_15149A94.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15149BF4 CURRENT (350) */
s32 func_15149BF4(void *arg0) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x2C);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x150);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x30);
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (temp_fv0 - (temp_fv0 * temp_fv1));
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (temp_fa0 - (temp_fa0 * temp_fv1));
    if ((*(f32 *)((u8 *)arg0 + 0x2C) < 2.0f) || (*(f32 *)((u8 *)arg0 + 0x30) < 2.0f)) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15149BF4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_176A00/func_15149BF4.s")
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15149C58 CURRENT (35) */
s32 func_15149C58(void *arg0) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x2C);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x150);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x30);
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (temp_fv0 - (temp_fv0 * temp_fv1));
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (temp_fa0 - (temp_fa0 * temp_fv1));
    *(f32 *)((u8 *)arg0 + 0x50) = (f32) (*(f32 *)((u8 *)arg0 + 0x50) + (*(f32 *)((u8 *)arg0 + 0x4C) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)arg0 + 0x38) + (*(f32 *)((u8 *)arg0 + 0x50) * D_800BE9A4));
    if (*(f32 *)((u8 *)arg0 + 0x15C) < *(f32 *)((u8 *)arg0 + 0x38)) {
        return 0;
    }
    if ((*(f32 *)((u8 *)arg0 + 0x2C) < 4.0f) || (*(f32 *)((u8 *)arg0 + 0x30) < 4.0f)) {
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15149C58 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_176A00/func_15149C58.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_176A00/func_15149D18.s")
typedef struct {
    s32 values[3];
} Game176A00Position;

typedef struct {
    Game176A00Position position;
    u8 pad0C[0xA];
    s16 field16;
    s16 field18;
    s16 field1A;
    s16 field1C;
    s16 field1E;
    s16 field20;
    s16 field22;
    s16 field24;
    s16 field26;
    u8 field28;
    u8 field29;
    u8 field2A;
    u8 field2B;
    u8 field2C;
    u8 field2D;
    s8 field2E;
    s8 field2F;
    s8 field30;
    s8 field31;
} Game176A00Effect;

void func_151429E0(u8, u8 *, u8 *, u8 *);
u32 func_150ADA20(void);
void func_1518CA80(void *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15149EC4 CURRENT (274) */
s32 func_15149EC4(void *arg0) {
    Game176A00Effect effect;
    s16 random_pair;

    effect.position = *(Game176A00Position *)((u8 *)arg0 + 0x34);
    effect.field16 = 0;
    effect.field18 = 0;
    random_pair = (func_150ADA20() % 6U) + 8;
    effect.field1A = random_pair;
    effect.field1E = 0;
    effect.field20 = 0;
    effect.field1C = random_pair;
    effect.field22 = (func_150ADA20() % 201U) + 0x64;
    effect.field24 = (func_150ADA20() % 5U) + 3;
    effect.field26 = 0x258;
    func_151429E0(3, &effect.field28, &effect.field29, &effect.field2A);
    func_151429E0(4, &effect.field2B, &effect.field2C, &effect.field2D);
    effect.field2E = 0xFF;
    effect.field2F = (func_150ADA20() % 65U) + 0x5C;
    effect.field30 = (func_150ADA20() % 3U) + 1;
    effect.field31 = 0;
    func_1518CA80(&effect, 1);
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15149EC4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_176A00/func_15149EC4.s")
