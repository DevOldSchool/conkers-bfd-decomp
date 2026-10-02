#include "types.h"

/*
 * Reviewed source unit: src/game/game_3BFE0.c
 * Boundary evidence: docs/evidence/game_next_compact_units.md
 */

typedef struct Game3BFE0Object {
    u8 pad0[0x28];
    s16 field_28;
    s16 field_2A;
    s16 field_2C;
    s16 field_2E;
    s8 field_30;
} Game3BFE0Object;

s32 func_150ADA20(void);
Game3BFE0Object *func_151491F4(s16, s32, s32, s32, s32, s32, s32, s32);

void func_1500EB30(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Game3BFE0Object *temp_v0;

    temp_v0 = func_151491F4((s16)((func_150ADA20() & 0x7F) + 0xA), 1, -1, 1, 0, 0xA, 0xFF, 0);
    if (temp_v0 != 0) {
        temp_v0->field_28 = (s16)arg0;
        temp_v0->field_2A = (s16)arg1;
        temp_v0->field_2C = (s16)arg2;
        temp_v0->field_2E = (s16)arg3;
        temp_v0->field_30 = (s8)arg4;
    }
}
void func_1500EBC4(void) {
    func_1500EB30(0x182, 0x23B, -0x628, 0x1A6, 0);
    func_1500EB30(-0x17, 0x31D, -0x8BB, -0x91, 0);
    func_1500EB30(0x71, 0x2E9, -0x8C6, -0xBE, 0);
    func_1500EB30(0x184, 0x464, -0x6CD, 0x1E1, 0);
    func_1500EB30(0x184, 0x464, -0x618, 0x283, 0);
    func_1500EB30(0x184, 0x464, -0x450, 0x394, 0);
    func_1500EB30(0x5B8, 0x447, -0xA5E, -0x1EC, 1);
    func_1500EB30(0x5A8, 0x447, -0x97F, 0x1F6, 0);
    func_1500EB30(0x581, 0x45C, -0x7C9, -0x17B, 0);
    func_1500EB30(0x57B, 0x460, -0x239, -0x194, 0);
    func_1500EB30(0x604, 0x55B, -0x4F1, -0x20D, 0);
    func_1500EB30(0x37C, 0x885, -0x6DF, 0x6C8, 0);
    func_1500EB30(0x2FB, 0x885, -0x4C9, 0x676, 0);
    func_1500EB30(0x4B9, 0x885, -0x383, 0x560, 0);
    func_1500EB30(0x6B7, 0x885, -0x30D, -0x235, 0);
    func_1500EB30(0x48A, 0x885, -0x284, 0x59D, 0);
    func_1500EB30(0x78C, 0x885, -0x4F2, -0x26F, 1);
}
