#include "types.h"

/*
 * Reviewed source unit: src/game/game_97F90.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1506AC8C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15137610(void *, void *, void *, s32, s32, s32);
extern s32 D_800CC260;
extern u8 D_800CC2D0;
extern u8 D_800D1560;
extern u8 D_800D1570;

void func_1506AAE0(s32 arg0, s32 arg1) {
    u8 *temp_s1;
    s32 temp_t9;
    s32 var_s0;

    var_s0 = D_800CC260;
    temp_s1 = &D_800CC2D0;
    if (var_s0 != 0) {
        do {
            if (var_s0 & 1) {
                func_15137610(temp_s1, &D_800D1560, &D_800D1570, 0, 0xFF, 1);
            }
            temp_t9 = var_s0 >> 1;
            var_s0 = temp_t9;
            temp_s1 += 0x32C;
            if (var_s0 == 0) {
                break;
            }
        } while (1);
    }
}
extern void func_15103E40();

void func_1506AB7C(s32 arg0, void *arg1) {
    func_15103E40(arg0, *(s32 *)((u8 *)arg1 + 0), (u8 *)arg1 + 4, 1, *(s32 *)((u8 *)arg1 + 0x10), 0xFF, 1);
}
void func_1506ABC4(s32 arg0, void *arg1) {
    func_15103E40(arg0, *(s32 *)((u8 *)arg1 + 0), (u8 *)arg1 + 4, 2, *(s32 *)((u8 *)arg1 + 0x10), 0xFF, 1);
}
void func_151B7328(void **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

typedef struct Func1506AC0CPacket {
    void *field_0;
    u8 field_4;
} Func1506AC0CPacket;

void func_1506AC0C(void *arg0, s32 arg1) {
    Func1506AC0CPacket sp20;

    sp20.field_0 = arg0;
    sp20.field_4 = *(u8 *)((u8 *)arg0 + 0x3B);
    func_151B7328((void **)&sp20, 0, 8, 0xFF, 1);
}
void func_151CEAAC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_1506AC58(s32 arg0, s32 arg1) {
    func_151CEAAC(arg0, 0, 1, 0xFF, 1);
}
extern void (*D_80086110[])(void *, s32);
extern f32 D_800CC254;
extern f32 D_800CC258;
extern f32 D_800CC25C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506AC8C CURRENT (400) */
void func_1506AC8C(void *arg0, s32 arg1, s32 arg2) {
    void (*callback)(void *, s32);

    if ((arg1 >= 0) && (arg1 < 0xF)) {
        *(f32 *)(void *)&D_800D1560 = *(f32 *)((u8 *)arg0 + 0x2C);
        *(f32 *)((u8 *)&D_800D1560 + 4) = *(f32 *)((u8 *)arg0 + 0x30);
        *(f32 *)((u8 *)&D_800D1560 + 8) = *(f32 *)((u8 *)arg0 + 0x34);
        *(f32 *)(void *)&D_800D1570 = D_800CC254;
        *(f32 *)((u8 *)&D_800D1570 + 4) = D_800CC258;
        *(f32 *)((u8 *)&D_800D1570 + 8) = D_800CC25C;
        callback = D_80086110[arg1];
        if (callback != 0) {
            callback(arg0, arg2);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506AC8C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_97F90/func_1506AC8C.s")
