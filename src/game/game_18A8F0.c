#include "types.h"

/*
 * Reviewed source unit: src/game/game_18A8F0.c
 * Boundary evidence: docs/evidence/game_raw_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1515D440
 * - func_1515D480
 * - func_1515D4D4
 * - func_1515D520
 * - func_1515D5AC
 * - func_1515D5F8
 * - func_1515D6D0
 * - func_1515D914
 * - func_1515E278
 * - func_1515E43C
 * - func_1515E544
 * - func_1515E888
 * - func_1515EB84
 * - func_1515EC78
 * - func_1515EF74
 * - func_1515F008
 * - func_1515F040
 * - func_1515F0AC
 * - func_1515F10C
 * - func_1515F170
 * - func_1515F1B0
 * - func_1515F270
 * - func_1515F2B8
 * - func_1515F2E8
 * - func_1515F338
 * - func_1515F5C4
 * - func_1515F850
 * - func_1515FB70
 * - func_1515FB94
 * - func_1515FBC4
 * - func_1515FC34
 * - func_1515FC60
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game18A8F0Node {
    u8 pad0[0xC];
    struct Game18A8F0Node *next;
} Game18A8F0Node;

#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515D440.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515D480.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515D4D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515D520.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515D5AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515D5F8.s")
extern void *D_800DCD78;

void func_1515D69C(void) {
    void *var_v0;

    var_v0 = D_800DCD78;
    if (var_v0 != 0) {
        do {
            *(s8 *)((u8 *)var_v0 + 0xC) = 0;
            *(s8 *)((u8 *)var_v0 + 0x30) = 0;
            var_v0 = *(void **)((u8 *)var_v0 + 0);
        } while (var_v0 != 0);
    }
}
void func_1515D6C8(void) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515D6D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515D914.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515E278.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515E43C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515E544.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515E888.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515EB84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515EC78.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515EF74.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515F008 CURRENT (60) */
f32 func_1515F008(s32 arg0, s32 arg1) {
    void *temp_v1;

    temp_v1 = arg0 + (arg1 * 2);
    return (f32) (*(u16 *)((u8 *)temp_v1 + 0x20) | (*(s16 *)((u8 *)temp_v1 + 0) << 0x10)) * 0.000015258789f;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515F008 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515F008.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515F040.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515F0AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515F10C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515F170 CURRENT (315) */
void func_1515F170(s32 arg0, s32 arg1) {
    void *var_v0;

    var_v0 = D_800DCD78;
    if (var_v0 != 0) {
        do {
            if (arg0 == *(u8 *)((u8 *)var_v0 + 0xB)) {
                *(s8 *)((u8 *)var_v0 + 9) = (s8) (arg1 & 0xFF);
            }
            var_v0 = *(void **)((u8 *)var_v0 + 0);
        } while (var_v0 != 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515F170 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515F170.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515F1B0.s")
void func_1515F25C(Game18A8F0Node **arg0, Game18A8F0Node *arg1) {
    arg1->next = *arg0;
    *arg0 = arg1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515F270.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515F2B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515F2E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515F338.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515F5C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515F850.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515FB70 CURRENT (300) */
void func_1515FB70(void *arg0, void *arg1) {
    if ((*(u8 *)((u8 *)arg0 + 0x3B) == 1) && (*(s32 *)((u8 *)arg1 + 0x1C) >= 0)) {

    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515FB70 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515FB70.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515FB94.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515FBC4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515FC34.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515FC60.s")
