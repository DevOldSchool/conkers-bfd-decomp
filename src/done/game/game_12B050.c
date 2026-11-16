#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_12B050.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_recovered_pointer_helper_groups.md
 */

void *func_1513EDE4(void *, s16);
void func_150FDC2C(u8 *arg0);

void *func_150FDBA0(void *arg0, s16 arg1) {
    void *temp_v0;

    temp_v0 = func_1513EDE4(arg0, arg1);
    if (temp_v0 != 0) {
        *(s16 *)((u8 *)temp_v0 + 8) = (s16) (s32) *(f32 *)((u8 *)arg0 + 0x124);
        *(s16 *)((u8 *)temp_v0 + 0x18) = (s16) (s32) *(f32 *)((u8 *)arg0 + 0x128);
        *(s16 *)((u8 *)temp_v0 + 0x28) = (s16) (s32) *(f32 *)((u8 *)arg0 + 0x128);
        *(s16 *)((u8 *)temp_v0 + 0x38) = (s16) (s32) *(f32 *)((u8 *)arg0 + 0x124);
    }
    return temp_v0;
}
void func_100111C8(u16);

typedef struct Game12B050Cleanup {
    u8 pad0[0x28];
    void *resource;
    u8 pad2C[0x28];
    u16 sound1;
    u16 sound2;
} Game12B050Cleanup;

void func_150FDC2C(u8 *arg0) {
    Game12B050Cleanup *state = (Game12B050Cleanup *)(arg0 + 0x110);

    if (*(s32 *)(arg0 + 0x134) != 0) {
        func_1516972C(*(void **)(arg0 + 0x134));
    }
    if (state->resource != NULL) {
        func_1516972C(state->resource);
    }
    if (state->sound1 != 0) {
        func_100111C8(state->sound1);
    }
    if (state->sound2 != 0) {
        func_100111C8(state->sound2);
    }
}

void func_150FDCAC(void *arg0) {
    func_150FDC2C(arg0);
    func_1513CA6C(arg0);
}
void func_150FDCD8(void *arg0) {
    func_150FDC2C(arg0);
    func_1513CAA0(arg0);
}
