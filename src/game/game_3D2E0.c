#include "types.h"

/*
 * Reviewed source unit: src/game/game_3D2E0.c
 * Boundary evidence: docs/evidence/game_raw_scene_setup_emission_controller.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1500FE30
 * - func_1500FFCC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10003C40(s32, s32, s32, s32);
void func_100226F0(void *, s32);
u32 func_150ADA20(void);
void func_150C851C(s32);
extern u8 *D_800BE4E0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1500FE30 CURRENT (1463) */
void func_1500FE30(void) {
    s32 index;
    s32 offset;
    s32 copy_offset;
    u8 *entry;
    u32 random_value;

    D_800BE4E0 = func_10003C40(0x64, 1, 0, 0);
    func_100226F0(D_800BE4E0, 0x64);
    index = 0;
    offset = 0;
    do {
        D_800BE4E0[offset] = (s8)(index / 5);
        *(s8 *)(D_800BE4E0 + offset + 2) = -1;
        random_value = func_150ADA20();
        index++;
        entry = D_800BE4E0 + offset;
        offset += 0xA;
        *(s16 *)(entry + 4) = (s16)(random_value % 5U);
    } while (index < 0xA);
    func_150C851C(0x64);
    copy_offset = 0x14;
    *(s16 *)(D_800BE4E0 + 6) = *(s16 *)(D_800BE4E0 + 8);
    *(s16 *)(D_800BE4E0 + 0x10) = *(s16 *)(D_800BE4E0 + 0x12);
    do {
        entry = D_800BE4E0 + copy_offset;
        *(s16 *)(entry + 6) = *(s16 *)(entry + 8);
        entry = D_800BE4E0 + copy_offset;
        *(s16 *)(entry + 0x10) = *(s16 *)(entry + 0x12);
        entry = D_800BE4E0 + copy_offset;
        *(s16 *)(entry + 0x1A) = *(s16 *)(entry + 0x1C);
        entry = D_800BE4E0 + copy_offset;
        copy_offset += 0x28;
        *(s16 *)(entry + 0x24) = *(s16 *)(entry + 0x26);
    } while (copy_offset != 0x64);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1500FE30 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_3D2E0/func_1500FE30.s")
extern s32 D_800917B8;
void func_1510C4AC(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_1500FF9C(void) {
    func_1510C4AC(D_800917B8, 0, 0xAD, 0x75);
}
void *func_10022EC0(void *, const void *, u32);
void func_1500FE30(void);
void func_15195AA8(s32, s32, s32, s32, s32, s32, s32, s32);
void *func_151491F4(s16, s8, s8, u8, u8, s32, u8, s32);
void *func_15149130(s16, s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_80088870;
extern s32 D_800902DC;
extern s32 D_800B0E00;
extern s32 D_800B0E04;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1500FFCC CURRENT (565) */
void func_1500FFCC(void) {
    struct {
        f32 second[2];
        f32 padding;
        f32 first;
    } values;
    u8 *object;
    s32 *global_object;

    func_15195AA8(D_800B0E00, D_800902DC, 1, -1, 0, 0, 0, -4);
    func_15195AA8(D_800B0E04, D_800902DC, 1, -1, 0, 1, 0, -4);
    func_1500FE30();
    func_1500FF9C();
    values.first = 0.0f;
    object = func_151491F4(0x12C, -1, 0x12, 0, 0xE, 4, 0xFF, 0);
    if (object != 0) {
        func_10022EC0(object + 0x28, &values.first, 4);
    }
    values.second[0] = 0.0f;
    values.second[1] = 0.0f;
    object = func_15149130(0x12C, -1, 0x17, -1, 0, 0x14, 8, 0xFF, 1);
    global_object = &D_80088870;
    *global_object = (s32)object;
    if (object != 0) {
        func_10022EC0(object + 0x28, values.second, 8);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1500FFCC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_3D2E0/func_1500FFCC.s")
