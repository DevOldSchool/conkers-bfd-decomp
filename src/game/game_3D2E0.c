#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_3D2E0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_scene_setup_emission_controller.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1500FFCC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10003C40(s32, s32, s32, s32);
void func_100226F0(void *, s32);
u32 func_150ADA20(void);
void func_150C851C(s32);
extern u8 *D_800BE4E0;

void func_1500FE30(void) {
    typedef struct Entry {
        s8 group;
        u8 pad1;
        s8 mode;
        u8 pad3;
        s16 choice;
        s16 current;
        s16 target;
    } Entry;
    s32 index;

    D_800BE4E0 = func_10003C40(0x64, 1, 0, 0);
    func_100226F0(D_800BE4E0, 0x64);
    for (index = 0; index < 10; index++) {
        ((Entry *)D_800BE4E0)[index].group = index / 5;
        ((Entry *)D_800BE4E0)[index].mode = -1;
        ((Entry *)D_800BE4E0)[index].choice = func_150ADA20() % 5U;
    }
    func_150C851C(0x64);
    for (index = 0; index < 10; index++) {
        ((Entry *)D_800BE4E0)[index].current = ((Entry *)D_800BE4E0)[index].target;
    }
}
extern s32 D_800917B8;
void func_1510C4AC(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_1500FF9C(void) {
    func_1510C4AC(D_800917B8, 0, 0xAD, 0x75);
}
void *func_10022EC0(void *, const void *, u32);
void func_1500FE30(void);
void func_15195AA8(s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_80088870;
extern s32 D_800902DC;
extern s32 D_800B0E00;
extern s32 D_800B0E04;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1500FFCC CURRENT (565) */
void func_1500FFCC(void) {
    f32 first;
    u8 *object;
    f32 second[2];
    s32 *global_object;

    func_15195AA8(D_800B0E00, D_800902DC, 1, -1, 0, 0, 0, -4);
    func_15195AA8(D_800B0E04, D_800902DC, 1, -1, 0, 1, 0, -4);
    func_1500FE30();
    func_1500FF9C();
    first = 0.0f;
    object = func_151491F4(0x12C, -1, 0x12, 0, 0xE, 4, 0xFF, 0);
    if (object != 0) {
        func_10022EC0(object + 0x28, &first, 4);
    }
    second[0] = 0.0f;
    second[1] = 0.0f;
    object = func_15149130(0x12C, -1, 0x17, -1, 0, 0x14, 8, 0xFF, 1);
    global_object = &D_80088870;
    *global_object = (s32)object;
    if (object != 0) {
        func_10022EC0(object + 0x28, second, 8);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1500FFCC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_3D2E0/func_1500FFCC.s")
