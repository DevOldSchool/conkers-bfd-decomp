#include "types.h"

/*
 * Reviewed source unit: src/game/game_EBD00.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150BE850
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameEBD00Actor {
    u8 pad0[0x2C];
    s32 field2C;
    u8 pad30[0x54];
    volatile s32 field84;
    u8 pad88[0xAC];
    s32 field134;
    u8 pad138[0x58];
    f32 field190;
    u8 pad194[0x1B4];
    f32 field348;
    f32 field34C;
    u8 pad350[0x24];
    f32 field374;
    u8 pad378[0x2FC];
    f32 field674;
    u8 pad678[0xC4];
    s16 field73C;
} GameEBD00Actor;

void func_15123070(void *);
void func_151254F4(void *, s32);
s32 func_1509BE40(s32, s32, s32);
void func_1509BFB0(s32, s32, s32);
s32 func_15123934(void *, s32, s32, s32, s32);
s32 func_151239CC(void *, s32);
void func_1512868C(void *);
extern f32 D_800A00B0;
extern f32 D_800A00B4;
extern u8 D_800CC335;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150BE850 CURRENT (65) */
void func_150BE850(GameEBD00Actor *arg0) {
    struct {
        s32 sp28;
        s32 pad;
    } state;
    s32 temp_t0;
    s32 temp_v0;
    f32 value;
    f32 other;

    state.sp28 = func_1509BE40(0,
                               func_1509BE40(0, 0x2006, 0xB7) | 0x2000,
                               0xBC);
    temp_v0 = func_1509BE40(0, 0x2000, 0xBB);
    if (state.sp28 != 0 && temp_v0 != -1) {
        func_1509BFB0(0, 0x400E, 1);
        if (arg0->field2C != 8) {
            func_1512868C(arg0);
        }
        if (func_15123934(arg0, 8, 0, arg0->field134, 3) != 0) {
            func_151254F4(arg0, D_800CC335 - 1);
            temp_t0 = arg0->field84 | 0x01000200;
            arg0->field84 = temp_t0;
            arg0->field73C = 0;
            arg0->field84 = temp_t0 & ~4;
            arg0->field674 = 0.0f;
        }
        value = D_800A00B0;
        other = D_800A00B4;
        arg0->field348 = value;
        arg0->field34C = value;
        arg0->field374 = other;
        arg0->field190 = 0.0f;
        func_15123070(arg0);
        return;
    }
    if (func_151239CC(arg0, 3) != 0) {
        func_151254F4(arg0, 0);
        arg0->field674 = 0.0f;
        func_1509BFB0(0, 0x400E, 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150BE850 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EBD00/func_150BE850.s")
