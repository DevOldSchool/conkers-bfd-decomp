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
