#include "types.h"

/*
 * Reviewed source unit: src/game/game_447B0.c
 * Boundary evidence: docs/evidence/game_next_compact_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15017300
 * - func_150174C0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_100226F0(void *arg0, s32 arg1);
extern u8 D_800D2138[];

/* Call context: func_100226F0: unique active declaration in the allowed source */
/* Call context: func_1501748C: unique active declaration in the allowed source */
/* Call context: func_15085710: unique active project prototype */
void func_1501748C(s32);
void func_15085710(s16, s32, u8);
extern s8 D_80087260;
extern s8 D_80087264;
extern s8 D_8008726C;
extern s8 D_80087270;
extern u8 D_800BE616;
extern s16 D_800D2132;
extern s16 D_800D2340;
extern s8 D_800D2456;
extern s8 D_800D2457;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15017300 CURRENT (3350) */
void func_15017300(s16 arg0, s16 arg1) {
    s16 var_s1;

    func_100226F0(D_800D2138, 0x20C);
    *D_800D2138 = (s32) arg0;
    var_s1 = 0;
    do {
        if ((1 << var_s1) & arg1) {
            func_15085710(var_s1, 0, (u8) *(&D_80087270 + var_s1));
            D_800D2456 = 6;
            D_800D2457 = 6;
            func_15085710(var_s1, 5, (u8) D_8008726C);
            func_15085710(var_s1, 2, (u8) D_80087260);
            if (D_800BE616 != 0) {
                func_15085710(var_s1, 9, (u8) D_80087264);
            }
        }
        func_1501748C((s32) arg1);
        var_s1 += 1;
    } while (var_s1 != 0x10);
    D_800D2340 = arg1;
    D_800D2132 = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15017300 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_447B0/func_15017300.s")
void func_1501748C(s32 arg0) {

}
void func_15017498(void) {
    func_100226F0(D_800D2138, 0x20C);
}
extern u32 D_80087380;
extern void *D_800D23C0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150174C0 CURRENT (965) */
void func_150174C0(s32 arg0) {
    s32 var_a0;
    s32 var_a2;
    s32 var_v0;
    s32 var_v1;
    u16 temp_t2;
    u16 var_t0;
    u8 *temp_t1;
    u8 *base;
    u8 *var_a3;

    var_v0 = 0;
    if ((s32)D_80087380 > 0) {
        var_a2 = 0;
        base = (u8 *)D_800D23C0;
        var_a3 = base;
        do {
            var_t0 = *(u16 *)(var_a3 + 2);
            var_a0 = 0;
            if ((s32)var_t0 > 0) {
                var_v1 = 0;
                while (var_a0 < (s32)var_t0) {
                    temp_t1 = base + (var_v0 * 0x18) + var_v1;
                    temp_t2 = *(u16 *)(temp_t1 + 8);
                    var_a0 += 1;
                    if (((s32)temp_t2 >> 0xC) == 2) {
                        *(u16 *)(temp_t1 + 8) = temp_t2 + arg0;
                        var_a3 = base + var_a2;
                        var_t0 = *(u16 *)(var_a3 + 2);
                    }
                    var_v1 += 2;
                }
            }
            var_v0 += 1;
            var_a2 += 0x18;
            var_a3 += 0x18;
        } while (var_v0 < (s32)D_80087380);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150174C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_447B0/func_150174C0.s")
void *func_1502B5C8(u32 *, s32, ...);
void func_150174C0(s32);
extern u32 D_80087380;
extern void *D_800D23C0;
extern u8 D_800DBF00;

void func_15017578(s32 arg0) {
    u32 sp24;

    sp24 = 0;
    D_800D23C0 = func_1502B5C8(&sp24, 3, 0xC, arg0, 4);
    D_80087380 = sp24 / 24U;
    func_150174C0(D_800DBF00);
}
