#include "types.h"

/*
 * Reviewed source unit: src/game/game_179400.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1514BF50
 * - func_1514BF9C
 * - func_1514C2B8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514BF50 CURRENT (40) */
void func_1514BF50(void *arg0) {
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) *(f32 *)((u8 *)arg0 + 0x34);
    *(f32 *)((u8 *)arg0 + 0x48) = (f32) *(f32 *)((u8 *)arg0 + 0x3C);
    *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)arg0 + 0x38) + 100.0f);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514BF50 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_179400/func_1514BF50.s")
void func_1514BF7C(s32 arg0) {
    func_1514BC08(arg0, arg0 + 0x110);
}
void func_1514BF9C(s32 arg0);
void func_1514BE20(s32 arg0);
#pragma GLOBAL_ASM("asm/nonmatchings/game_179400/func_1514BF9C.s")
s32 func_1514C258(s32 arg0) {
    func_1514BF9C(arg0);
    func_1514BE20(arg0);
    return 1;
}
s32 func_1514C288(s32 arg0) {
    func_1514BF9C(arg0);
    func_1514BF50((void *)arg0);
    return 1;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514C2B8 CURRENT (30) */
s32 func_1514C2B8(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x72) = 0;
    *(s8 *)((u8 *)arg0 + 0x71) = 0x24;
    *(s32 *)((u8 *)arg0 + 0x58) = (s32) (*(s32 *)((u8 *)arg0 + 0x58) | 0x08000000);
    *(s16 *)((u8 *)arg0 + 0x1C) = (s16) *(s16 *)((u8 *)arg0 + 0x164);
    *(f32 *)((u8 *)arg0 + 0x154) = (f32) *(f32 *)((u8 *)arg0 + 0x160);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514C2B8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_179400/func_1514C2B8.s")
