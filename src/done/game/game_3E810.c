#include "types.h"

/*
 * Reviewed source unit: src/game/game_3E810.c
 * Boundary evidence: docs/evidence/game_small_units_3D6F0_3FC30.md
 */

typedef struct Game3E810State {
    u8 pad0[0x14];
    u8 flags;
} Game3E810State;

typedef struct Game3E810Colors {
    u8 pad0[5];
    s8 field_5;
    s8 field_6;
    s8 field_7;
} Game3E810Colors;

void func_15008E00(void);
void func_15008E10(s32);
extern Game3E810Colors *volatile D_800B0DF0;
extern Game3E810State *D_800D2E4C;

void func_15011360(void) {
    func_15008E00();
    func_15008E10(2);
    func_15008E10(3);
    if (D_800D2E4C->flags & 1) {
        D_800B0DF0->field_5 = 0x30;
        D_800B0DF0->field_6 = 0x38;
        D_800B0DF0->field_7 = 0x5F;
    }
}
