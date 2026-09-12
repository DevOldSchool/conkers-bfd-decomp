#include "types.h"

/*
 * Reviewed source unit: src/game/game_18A8F0.c
 * Boundary evidence: docs/evidence/game_raw_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1515D480
 * - func_1515D4D4
 * - func_1515D520
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
 * - func_1515F2E8
 * - func_1515F338
 * - func_1515F5C4
 * - func_1515F850
 * - func_1515FB70
 * - func_1515FBC4
 * - func_1515FC60
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game18A8F0Node {
    u8 pad0[0xC];
    struct Game18A8F0Node *next;
} Game18A8F0Node;

extern void *func_10003C40(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_100226F0(void *arg0, s32 arg1);

void *func_1515D440(void) {
    void *temp_v0;

    temp_v0 = func_10003C40(0x10, 1, 2, 0);
    func_100226F0(temp_v0, 0x10);
    return temp_v0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515D480.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515D4D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515D520.s")
void func_1515D5AC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, u8 arg9) {
    func_1515D5F8(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, (u8) (s32) arg9);
}
void *func_1515D520();                              /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515D5F8 CURRENT (999) */
void *func_1515D5F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, u8 arg9) {
    void *temp_v0;

    temp_v0 = func_1515D520();
    if (temp_v0 != 0) {
        *(s8 *)((u8 *)temp_v0 + 4) = 0;
        *(s8 *)((u8 *)temp_v0 + 5) = (s8) arg4;
        *(s8 *)((u8 *)temp_v0 + 6) = (s8) arg5;
        *(s8 *)((u8 *)temp_v0 + 7) = (s8) arg6;
        *(s8 *)((u8 *)temp_v0 + 8) = (s8) arg7;
        *(s8 *)((u8 *)temp_v0 + 9) = (s8) arg8;
        *(s8 *)((u8 *)temp_v0 + 0xA) = 0;
        *(u8 *)((u8 *)temp_v0 + 0xB) = arg9;
        *(s16 *)((u8 *)temp_v0 + 0xE) = (s16) arg0;
        *(s16 *)((u8 *)temp_v0 + 0x10) = (s16) arg1;
        *(s16 *)((u8 *)temp_v0 + 0x12) = (s16) arg2;
        *(s8 *)((u8 *)temp_v0 + 0x2C) = 0x7F;
        *(s8 *)((u8 *)temp_v0 + 0x2D) = 0;
        *(s8 *)((u8 *)temp_v0 + 0x2E) = 0;
        *(s8 *)((u8 *)temp_v0 + 0x2F) = (s8) arg3;
    }
    return temp_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515D5F8 */
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
void func_1505D024(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_1515F2B8(void *arg0, s32 arg1) {
    func_1505D024((s32)arg0, 0x6001D, *(u16 *)((u8 *)arg0 + 0x7A), -1);
}
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
void func_1515FB94(void *arg0, s32 arg1) {
    func_1505D024((s32)arg0, 0x6002D, *(u16 *)((u8 *)arg0 + 0x7A), -1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515FBC4.s")
void func_1505D024(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_1515FC34(s32 arg0, s32 arg1) {
    func_1505D024(arg0, 0x33, 0xC000, -1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_18A8F0/func_1515FC60.s")
