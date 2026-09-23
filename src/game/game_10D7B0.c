#include "types.h"

/*
 * Reviewed source unit: src/game/game_10D7B0.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E0348
 * - func_150E03F8
 * - func_150E05F8
 * - func_150E06D8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern void func_1515F170(s32 arg0, s32 arg1);
extern void func_1513BAE8(void);
extern u8 D_80088980;

void func_150E0300(void) {
    if (D_80088980 == 0) {
        func_1515F170(6, 0);
        func_1513BAE8();
        D_80088980 = 1;
    }
}
extern u32 func_1513418C(void *arg0, s32 arg1, u8 arg2, s32 arg3);
extern f32 D_800A0FB4;
extern f32 D_800A0FB8;
extern s32 D_800A5480[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E0348 CURRENT (3363) */
void func_150E0348(void *arg0, u8 arg1, s32 arg2) {
    s8 sp45;
    s8 sp44;
    s8 sp43;
    s8 sp42;
    s16 sp40;
    f32 sp3C;
    f32 sp38;
    s32 sp2C[3];
    s8 sp28;
    void *sp24;
    u8 sp20;
    s32 sp1C;
    s32 sp18;

    sp18 = 0;
    sp1C = 0;
    sp28 = 0;
    sp24 = arg0;
    sp20 = *(u8 *)((u8 *)arg0 + 0x3B);
    sp2C[0] = D_800A5480[0];
    sp2C[1] = D_800A5480[1];
    sp2C[2] = D_800A5480[2];
    sp40 = 0x12C;
    sp42 = 0x1B;
    sp43 = 0xB;
    sp44 = -1;
    sp45 = 0;
    sp38 = D_800A0FB4;
    sp3C = D_800A0FB8;
    func_1513418C(&sp18, 0, arg1, arg2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E0348 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10D7B0/func_150E0348.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_10D7B0/func_150E03F8.s")
extern f32 D_800A0FD0;
extern f32 D_800A0FD4;
extern void *D_800DBFF0;

f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E05F8 CURRENT (970) */
void func_150E05F8(void *arg0) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 var_v0;

    temp_fv1 = *(f32 *)((u8 *)D_800DBFF0 + 0x300) - (f32) *(s16 *)((u8 *)arg0 + 0x14);
    temp_fa0 = *(f32 *)((u8 *)D_800DBFF0 + 0x2F8) - (f32) *(s16 *)((u8 *)arg0 + 0x10);
    temp_fa1 = *(f32 *)((u8 *)D_800DBFF0 + 0x2FC) - (f32) *(s16 *)((u8 *)arg0 + 0x12);
    temp_fv0 = sqrtf((temp_fv1 * temp_fv1) + ((temp_fa0 * temp_fa0) + (temp_fa1 * temp_fa1)));
    if (temp_fv0 <= D_800A0FD0) {
        var_v0 = 0xFF;
    } else if (D_800A0FD4 <= temp_fv0) {
        var_v0 = 0;
    } else {
        var_v0 = (s32) (255.0f - ((temp_fv0 - D_800A0FD0) * (1.0f / (D_800A0FD4 - D_800A0FD0)) * 255.0f));
    }
    *(s8 *)((u8 *)arg0 + 0x8A) = (s8) var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E05F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10D7B0/func_150E05F8.s")
void func_15102B38(s32, u8, s32, s32, f32 *, s32, s32, f32, s32, s32,
                   s32, s32, s32, s32);
void func_15145EA4(s32 *, s32 *, s32, s32);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
extern u8 D_80088988;
extern u8 D_800A0F70[];
extern u8 D_800A0F88[];

typedef struct {
    u32 random1;
    u32 random2;
    s32 pad4C;
    s32 *target;
    s32 *source;
    f32 dimensions[2];
    s32 pad60;
    s32 position[3];
} Game10D7B0EffectLocals;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E06D8 CURRENT (3213) */
void func_150E06D8(void *arg0, u8 arg1, u8 arg2, s32 arg3) {
    Game10D7B0EffectLocals locals;

    if (*(s32 *)((u8 *)arg0 + 0x1D4) != 0) {
        locals.source = (s32 *)(D_800A0F70 + (arg1 * 0xC));
        locals.target = locals.position;
        func_15145EA4((s32 *)&locals.source, (s32 *)&locals.target,
                      *(s32 *)((u8 *)arg0 + 0x1D4) + (D_80088988 << 6), 1);
        locals.dimensions[1] = (func_150ADA68() * 1.0f) + 2.0f;
        locals.dimensions[0] = (func_150ADA68() * 14.0f) + 28.0f;
        locals.random1 = func_150ADA20();
        locals.random2 = func_150ADA20();
        func_15102B38((s32)arg0, D_80088988,
                       (s32)(D_800A0F70 + (arg1 * 0xC)),
                       (s32)(D_800A0F88 + (arg1 * 0xC)),
                       locals.dimensions, (locals.random1 % 3U) + 4,
                       (locals.random2 % 156U) + 0x64,
                       (func_150ADA68() * 300.0f) + 400.0f,
                       (s32)locals.position, 0xFF, 0, -1, arg2, arg3);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E06D8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10D7B0/func_150E06D8.s")
