#include "types.h"

/*
 * Reviewed source unit: src/game/game_305D0.c
 * Boundary evidence: docs/evidence/game_early_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15003120
 * - func_150031EC
 * - func_150034B4
 * - func_15003570
 * - func_15003668
 * - func_150039BC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800B0E30;
extern s32 D_800B0E34;
extern s32 D_800B0E00[];
extern s32 D_800D3300[];
void func_15001460(s32);
void func_15001970(void);
void func_15002754(void);
void func_1510F800(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15003120 CURRENT (2105) */
void func_15003120(s32 arg0, s32 arg1, s32 arg2) {
    s32 *temp_a1;
    s32 *temp_v1;
    s32 *var_t0;
    s32 temp_t8;
    s32 temp_v0;
    s32 var_t1;
    s32 var_v1;
    s8 var_a2;
    u8 *temp_t0;

    temp_v0 = arg0 * 4;
    *(u8 *)(D_800B0E30 + temp_v0) = arg2;
    *(u8 *)(D_800B0E34 + arg0) = 0;
    if (arg2 != 0) {
        var_a2 = 0;
        temp_v1 = (void *)(D_800B0E30 + temp_v0);
        *temp_v1 += arg1;
        var_v1 = 0;
        temp_a1 = (void *)(*(u8 *)(D_800B0E30 + temp_v0));
        var_t0 = temp_a1;
        if (*temp_a1 != 0) {
            var_t1 = *temp_a1;
            do {
                *var_t0 = var_t1 + arg1;
                var_a2 += 1;
                temp_t0 = (void *)(*(u8 *)(D_800B0E30 + temp_v0) + var_v1);
                temp_t8 = *(s32 *)((u8 *)temp_t0 + 4);
                var_v1 += 0xC;
                *(s32 *)((u8 *)temp_t0 + 4) = (s32) (temp_t8 + arg1);
                var_t0 = (void *)(*(u8 *)(D_800B0E30 + temp_v0) + var_v1);
                var_t1 = *var_t0;
            } while (var_t1 != 0);
        }
        *(u8 *)(D_800B0E34 + arg0) = var_a2;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15003120 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_305D0/func_15003120.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_305D0/func_150031EC.s")
extern s32 D_800B0E58;
extern s8 D_800BC448;
extern s32 D_800B0E5C;
extern s8 D_800BC449;
extern s32 D_800B0E60[];
extern s8 D_800BC44A[];
extern s8 D_800BE29A[];
extern s32 D_800BE9F0;
extern s32 D_800D9F58;
extern s32 D_800D9F5C;
extern s8 D_800D9F60;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150034B4 CURRENT (5070) */
void func_150034B4(void) {
    s8 *flags;
    s32 *records;

    D_800B0E58 = -1;
    D_800BC448 = 0;
    D_800B0E5C = -1;
    D_800BC449 = 0;
    flags = &D_800BC44A[4];
    records = D_800B0E60;
    do {
        flags += 4;
        records[1] = -1;
        flags[-3] = 0;
        records[2] = -1;
        flags[-2] = 0;
        records[3] = -1;
        flags[-1] = 0;
        records += 4;
        records[0] = -1;
        flags[-4] = 0;
    } while (flags != D_800BE29A);
    D_800D9F58 = 0xFFFF;
    D_800D9F5C = -1;
    D_800D9F60 = (D_800BE9F0 == 1 || D_800BE9F0 == 0x32);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150034B4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_305D0/func_150034B4.s")
void func_10004074(s32);
void *func_10003C40(s32, s32, s32, s32);
void func_10004514(s32, s32, s32, s32);
extern u8 D_1A37E0;
extern u16 D_80091D20;
extern s16 D_800B87A0;
extern s16 D_800BC444;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15003570 CURRENT (605) */
void func_15003570(void) {
    u8 *var_s0;
    u16 *var_s2;
    s16 *var_s3;
    u8 *temp_s4;
    s32 temp_t8;
    s32 var_s1;
    u8 *temp_v0;

    temp_s4 = func_10003C40(0x10, 1, 2, 0);
    var_s0 = &D_1A37E0;
    var_s3 = &D_800B87A0;
    var_s2 = &D_80091D20;
    do {
        if ((s32)var_s0 & 1) {
            var_s0--;
            var_s1 = 1;
        } else {
            var_s1 = 0;
        }
        func_10004514((s32)var_s0, (s32)temp_s4, 0x10, 1);
        temp_v0 = temp_s4 + var_s1;
        var_s3++;
        temp_t8 = *var_s2 + var_s1;
        var_s2++;
        var_s3[-1] = (s16)(temp_v0[3] + (temp_v0[0] << 24) +
                              (temp_v0[1] << 16) + (temp_v0[2] << 8));
        var_s0 += temp_t8;
    } while (var_s3 != &D_800BC444);
    func_10004074((s32)temp_s4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15003570 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_305D0/func_15003570.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_305D0/func_15003668.s")
void func_15001A08(void);
void func_15001BC8(s32, s16 *, s16 *);
void func_15001CEC(s32);
void func_150025FC(void);
extern s16 D_800DBE2A;
extern s16 D_800DBE2C;
extern s8 D_800DBE62;

void func_150038A0(void) {
    func_15001A08();
    func_15001BC8(0, &D_800DBE2A, &D_800DBE2C);
    func_15001BC8(1, 0, 0);
    func_15001CEC(2);
    func_1510F800(0);
    func_150025FC();
    D_800DBE62 = 1;
}
extern s32 D_800B0E58;
extern s32 D_800B0E5C;
extern s32 D_800B0E60[];

s32 func_1500390C(s32 arg0) {
    s32 *entries;
    s32 result;

    if (arg0 == D_800B0E58) {
        return 0;
    }
    if (arg0 == D_800B0E5C) {
        return 1;
    }
    entries = D_800B0E60;
    result = 2;
loop:
        if (arg0 == entries[0]) {
            return result;
        }
        if (arg0 == entries[1]) {
            return result + 1;
        }
        if (arg0 == entries[2]) {
            return result + 2;
        }
        if (arg0 == entries[3]) {
            return result + 3;
        }
        result += 4;
        entries += 4;
    if (result != 0x1E52) {
        goto loop;
    }
    return -1;
}
void func_150039B0(s32 arg0) {

}
extern s32 D_800DBE5C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150039BC CURRENT (25) */
void func_150039BC(s32 arg0) {
    D_800DBE5C = arg0;
    if (arg0 != 0) {
        D_800DBE5C = arg0 + 8;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150039BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_305D0/func_150039BC.s")
