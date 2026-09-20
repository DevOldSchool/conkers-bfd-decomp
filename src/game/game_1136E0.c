#include "types.h"

/*
 * Reviewed source unit: src/game/game_1136E0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_subranges.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E6230
 * - func_150E63A0
 * - func_150E67D0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1136E0/func_150E6230.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1136E0/func_150E63A0.s")
s32 func_150E679C(void *arg0) {
    s16 temp_v0;
    s32 temp_v1;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    if (temp_v0 < 8) {
        temp_v1 = temp_v0 << 5;
        if (temp_v1 < (s32) *(u8 *)((u8 *)arg0 + 0x5C)) {
            *(u8 *)((u8 *)arg0 + 0x5C) = (u8) temp_v1;
        }
    }
    return 1;
}
s32 func_150ADA20();
void *func_1513C73C(s32 *, s32, s32, void *, f32, f32, f32, f32, f32,
                    s32, s32, s32, s32, s32);

typedef struct Game1136E0Descriptor {
    s32 field_0;
    s16 field_4;
    s8 field_6;
    u8 pad7;
    s32 field_8;
    s32 field_C;
    u8 field_10;
    u8 field_11;
    u8 field_12;
    u8 field_13;
    u8 field_14;
    u8 field_15;
    u8 pad16[2];
    s32 field_18;
    u8 pad1C[0x14];
} Game1136E0Descriptor;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E67D0 CURRENT (100) */
s32 func_150E67D0(u8 *arg0) {
    Game1136E0Descriptor descriptor;
    u8 *temp_v1;

    descriptor.field_6 = 0x3A;
    descriptor.field_0 = 1;
    descriptor.field_4 = 0x64;
    descriptor.field_8 = 0;
    descriptor.field_C = 0;
    descriptor.field_10 = 0xFF;
    descriptor.field_11 = 0xFF;
    descriptor.field_12 = 0;
    descriptor.field_13 = 0;
    descriptor.field_14 = 0;
    descriptor.field_15 = 0xFF;
    descriptor.field_18 = 0x130001;
    temp_v1 = arg0 + 0x110;
    func_1513C73C((s32 *)&descriptor, 0, 0, temp_v1 + 0x14,
                  *(f32 *)(temp_v1 + 4), *(f32 *)(temp_v1 + 8),
                  *(f32 *)(temp_v1 + 0xC), 50.0f, 50.0f,
                  func_150ADA20() & 0xFF, 0, 0, arg0[0xC], arg0[1]);
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E67D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1136E0/func_150E67D0.s")
