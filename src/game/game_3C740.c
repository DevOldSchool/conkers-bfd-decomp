#include "types.h"

/*
 * Reviewed source unit: src/game/game_3C740.c
 * Boundary evidence: docs/evidence/game_raw_scene_setup_emission_controller.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1500F290
 * - func_1500F40C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_1513C5B0(s32 *, s32, s32, s32, f32, f32, f32, f32, f32, s32, s32, s32, s32, s32);
s32 func_151EF610(void);

typedef struct {
    s32 field_0;
    s16 field_4;
    s8 field_6;
    s8 pad_7;
    s32 field_8;
    s32 field_C;
    u8 field_10;
    u8 field_11;
    u8 field_12;
    u8 field_13;
    u8 field_14;
    u8 field_15;
    u8 pad_16[2];
    s32 field_18;
} Game3C740Effect;

typedef struct {
    s32 pad_0;
    Game3C740Effect effect;
} Game3C740EffectStack;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1500F290 CURRENT (159) */
void func_1500F290(f32 arg0, f32 arg1, f32 arg2) {
    Game3C740EffectStack sp44;

    sp44.effect.field_6 = 0x38;
    sp44.effect.field_8 = 0;
    sp44.effect.field_C = (func_151EF610() % 4096) + 0x4000;
    sp44.effect.field_0 = 0x20014;
    sp44.effect.field_4 = 1;
    sp44.effect.field_10 = 0xFF;
    sp44.effect.field_11 = 0xFF;
    sp44.effect.field_12 = 0;
    sp44.effect.field_13 = 0;
    sp44.effect.field_14 = 0;
    sp44.effect.field_15 = 0xFF;
    sp44.effect.field_18 = 0x30001;
    func_1513C5B0((s32 *)&sp44.effect, 0, 0, 0, arg0, arg1, arg2, 110.0f, 110.0f, 0, 0, 0, 0xFF, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1500F290 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_3C740/func_1500F290.s")
typedef struct {
    u8 pad0[0x28];
    s16 field_28;
    s16 field_2A;
    s16 field_2C;
    s16 field_2E;
    s8 field_30;
} Game3C740Object;

s32 func_150ADA20(void);
Game3C740Object *func_151491F4(s16, s32, s32, s32, s32, s32, s32, s32);

void func_1500F378(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Game3C740Object *temp_v0;

    temp_v0 = func_151491F4((s16)((func_150ADA20() & 0x7F) + 0xA), 1, -1, 1, 0, 0xA, 0xFF, 0);
    if (temp_v0 != 0) {
        temp_v0->field_28 = (s16)arg0;
        temp_v0->field_2A = (s16)arg1;
        temp_v0->field_2C = (s16)arg2;
        temp_v0->field_2E = (s16)arg3;
        temp_v0->field_30 = 1;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_3C740/func_1500F40C.s")
