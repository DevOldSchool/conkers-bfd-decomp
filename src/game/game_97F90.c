#include "types.h"

/*
 * Reviewed source unit: src/game/game_97F90.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1506AAE0
 * - func_1506AC8C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_97F90/func_1506AAE0.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_97F90/func_1506AC8C.s")
