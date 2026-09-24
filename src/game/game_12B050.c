#include "types.h"

/*
 * Reviewed source unit: src/game/game_12B050.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FDC2C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_1513EDE4(void *, s16);                   /* extern */
void func_150FDC2C(s32 arg0);
void func_1513CA6C(s32 arg0);
void func_1513CAA0(s32 arg0);

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
void func_1516972C(void *);
void func_100111C8(u16);

typedef struct Game12B050Cleanup {
    u8 pad0[0x28];
    void *resource;
    u8 pad2C[0x28];
    u16 sound1;
    u16 sound2;
} Game12B050Cleanup;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FDC2C CURRENT (421) */
void func_150FDC2C(s32 arg0) {
    Game12B050Cleanup *state;
    void *resource;
    u16 sound1;
    u16 sound2;

    if (*(volatile s32 *)((u8 *)arg0 + 0x134) != 0) {
        func_1516972C((void *)*(s32 *)((u8 *)arg0 + 0x134));
    }
    state = (Game12B050Cleanup *)((u8 *)arg0 + 0x110);
    resource = state->resource;
    if (resource != 0) {
        func_1516972C(resource);
    }
    sound1 = state->sound1;
    if (sound1 != 0) {
        func_100111C8(sound1);
    }
    sound2 = state->sound2;
    if (sound2 != 0) {
        func_100111C8(sound2);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FDC2C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12B050/func_150FDC2C.s")

void func_150FDCAC(s32 arg0) {
    func_150FDC2C(arg0);
    func_1513CA6C(arg0);
}
void func_150FDCD8(s32 arg0) {
    func_150FDC2C(arg0);
    func_1513CAA0(arg0);
}
