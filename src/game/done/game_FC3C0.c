#include "types.h"

/*
 * Reviewed source unit: src/game/game_FC3C0.c
 * Boundary evidence: docs/evidence/game_remaining_single_function_units_up_to_256_bytes.md
 */

typedef struct {
    u8 pad_0[0x84];
    s32 field_84;
    u8 pad_88[0x12C];
    s16 field_1B4;
    u8 pad_1B6[0x2A];
    s16 field_1E0;
} GameFC3C0State;

void func_15124B18(void);

void func_150CEF10(GameFC3C0State *arg0) {
    arg0->field_84 |= 0x10;
    if (arg0->field_1B4 == 3) {
        arg0->field_1E0 = 5;
        arg0->field_1B4 = 2;
        func_15124B18();
    }
}
