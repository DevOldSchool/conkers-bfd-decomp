#include "types.h"

/*
 * Reviewed source unit: src/game/game_BC510.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1508F060
 * - func_1508F0D4
 * - func_1508F7BC
 * - func_1508F9F4
 * - func_1508FD38
 * - func_150900F0
 * - func_15090630
 * - func_1509093C
 * - func_150911F4
 * - func_15091534
 * - func_150916B4
 * - func_150918EC
 * - func_150938BC
 * - func_15093B58
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern u8 D_800D2460[][0x10];
extern s8 D_800D246D;
extern s8 D_800D247D;
extern s32 D_800D24C0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1508F060 CURRENT (625) */
void func_1508F060(void) {
    s32 temp_v0;
    u8 *temp_v1;

    D_800D246D = 0;
    D_800D247D = 0;
    temp_v0 = 2;
    temp_v1 = D_800D2460[temp_v0];
    temp_v1[0x1D] = 0;
    temp_v1[0x2D] = 0;
    temp_v1[0x3D] = 0;
    temp_v1[0xD] = 0;
    D_800D24C0 = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1508F060 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_1508F060.s")
void func_1508F0A4(void) {
    func_1508F0D4();
    func_1508F9F4();
    func_1509093C();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_1508F0D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_1508F7BC.s")
extern f32 D_800D2410[];
extern u8 D_800D2456;

void func_1508F9C4(void) {
    D_800D2410[D_800D2456] = 0.0f;
    D_800D2456 += 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_1508F9F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_1508FD38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_150900F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_15090630.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_1509093C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_150911F4.s")
s32 func_1510D0EC(s32, s32 *, s32, s32);
extern u8 D_D16;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15091534 CURRENT (6295) */
void *func_15091534(void *arg0, s32 arg1, s8 *arg2) {
    u8 *cursor = arg0;
    u8 *next;
    s32 address;

    *arg2 = 0;
    address = func_1510D0EC((s32)&D_D16 + arg1, 0, 3, 0);
    if (address != 0x80000000) {
        *(u32 *)cursor = 0xFD500000;
        *(u32 *)(cursor + 4) = address;
        next = cursor + 8;
        *(u32 *)(cursor + 8) = 0xF5500000;
        *(u32 *)(next + 4) = 0x07098260;
        cursor = next + 8;
        *(u32 *)(next + 8) = 0xE6000000;
        *(u32 *)(cursor + 4) = 0;
        next = cursor + 8;
        *(u32 *)(cursor + 8) = 0xF3000000;
        *(u32 *)(next + 4) = 0x073FF000;
        cursor = next + 8;
        *(u32 *)(next + 8) = 0xE7000000;
        *(u32 *)(cursor + 4) = 0;
        next = cursor + 8;
        *(u32 *)(cursor + 8) = 0xF5400800;
        *(u32 *)(next + 4) = 0x00098260;
        cursor = next + 8;
        *(u32 *)(next + 8) = 0xF2000000;
        *(u32 *)(cursor + 4) = 0x000FC0FC;
        next = cursor + 8;
        *(u32 *)(next + 4) = address + 0x800;
        *(u32 *)(cursor + 8) = 0xFD100000;
        cursor = next + 8;
        *(u32 *)(next + 8) = 0xE6000000;
        *(u32 *)(cursor + 4) = 0;
        next = cursor + 8;
        *(u32 *)(cursor + 8) = 0xF0000000;
        *(u32 *)(next + 4) = 0x0603C000;
        cursor = next + 8;
        *(u32 *)(next + 8) = 0xEF00AC3F;
        *(u32 *)(cursor + 4) = 0x00504244;
        cursor += 8;
        *arg2 = 1;
    }
    return cursor;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15091534 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_15091534.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_150916B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_150918EC.s")
/* Call context: func_15093878: unique active project prototype */
void func_15093878(void);
extern u8 D_800D2458;

void func_15093818(s32 arg0) {
    if ((arg0 != 0) && (D_800D2458 == 0)) {
        D_800D2458 = 1;
        func_15093878();
        return;
    }
    if ((arg0 == 0) && (D_800D2458 != 0)) {
        D_800D2458 = 0;
    }
}
extern void *func_10003C40(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_1518C900(s32 arg0);
extern s32 D_800D2448;
extern void *D_800D244C;

void func_15093878(void) {
    D_800D2448 = func_1518C900(0xBA);
    D_800D244C = func_10003C40(0x80, 1, 1, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_150938BC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_15093B58.s")
