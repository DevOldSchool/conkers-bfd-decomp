#include "types.h"

/*
 * Reviewed source unit: src/game/game_3EFB0.c
 * Boundary evidence: docs/evidence/game_compact_multi_function_units.md
 */

typedef struct Game3EFB0Object {
    u8 pad0[0x28];
    s16 field_28;
    s16 field_2A;
    s16 field_2C;
    s16 field_2E;
    s8 field_30;
} Game3EFB0Object;

s32 func_150ADA20(void);
Game3EFB0Object *func_151491F4(s16, s32, s32, s32, s32, s32, s32, s32);

void func_15011B00(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Game3EFB0Object *temp_v0;
    s32 temp_t3;

    temp_v0 = func_151491F4((s16)((func_150ADA20() & 0x7F) + 0xA), 1, -1, 1, 0, 0xA, 0xFF, 0);
    if (temp_v0 != 0) {
        temp_v0->field_28 = (s16)arg0;
        temp_v0->field_2A = (s16)arg1;
        temp_v0->field_2C = (s16)arg2;
        temp_v0->field_2E = (s16)arg3;
        temp_v0->field_30 = 1;
    }
}
void func_15011B00(s32, s32, s32, s32);
void func_1515F170(s32, s32);
void func_1000FA64(s32, s32, s32, s32, s32, s32, s32, void *, s32, s32, s32, s32);
extern u8 D_1000EF40[];

void func_15011B94(void) {
    func_15011B00(0x4E9, 0x152, -0xBAC, -0x16F);
    func_15011B00(0x76D, 0x152, -0xAC1, -0x16F);
    func_1515F170(1, 0);
    func_1515F170(2, 1);
    func_1000FA64(0x4D, 0x2FD, 0x37, -0x59, 0x2EE0, 0x258, 0x12C,
                  D_1000EF40, 0, 0, 8, 0);
}
