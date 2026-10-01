#include "types.h"

/*
 * Reviewed source unit: src/game/game_10D7B0.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
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

void func_150E0348(void *arg0, u8 arg1, s32 arg2) {
    typedef struct { s32 words[3]; } Copy3;
    struct {
        s32 sp18;
        s32 sp1C;
        u8 sp20;
        u8 pad21[3];
        void *sp24;
        s8 sp28;
        u8 pad29[3];
        Copy3 sp2C;
        f32 sp38;
        f32 sp3C;
        s16 sp40;
        s8 sp42;
        s8 sp43;
        s8 sp44;
        s8 sp45;
    } packet;

    packet.sp18 = 0;
    packet.sp1C = 0;
    packet.sp20 = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.sp28 = 0;
    packet.sp24 = arg0;
    packet.sp2C = *(Copy3 *)D_800A5480;
    packet.sp40 = 0x12C;
    packet.sp42 = 0x1B;
    packet.sp43 = 0xB;
    packet.sp44 = -1;
    packet.sp45 = 0;
    packet.sp38 = D_800A0FB4;
    packet.sp3C = D_800A0FB8;
    func_1513418C(&packet, 0, arg1, arg2);
}
/* Call context: func_150ADA20: unique active declaration in the allowed source */
/* Call context: func_150ADA68: unique active declaration in the allowed source */
/* Call context: func_15143794: matched US definition in src/game/game_16EE20.c */
/* Call context: func_151A26EC: unique active project prototype */
u32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_15143794(s16, s16, f32, void *);
void func_151A26EC(f32 *, f32 *, f32 *, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

extern f32 D_800A0FBC;
extern f32 D_800A0FC0;
extern f32 D_800A0FC4;
extern f32 D_800A0FC8;
extern f32 D_800A0FCC;
extern f32 D_800BE9A8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E03F8 CURRENT (1008) */
void func_150E03F8(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, void *arg6) {
    f32 position[3];
    f32 direction[3];
    f32 acceleration[3];
    f32 scale;
    f32 size_random;
    u32 random_b;
    u32 random_a;
    f32 alpha_random;

    position[0] = arg0;
    position[1] = arg1;
    position[2] = arg2;
    random_a = func_150ADA20();
    random_b = func_150ADA20();
    func_15143794((s16) (random_a & 0xFF), (s16) ((random_b % 65U) - 0x20), func_150ADA68() * D_800A0FBC, &direction[0]);
    scale = (func_150ADA68() * D_800A0FC0) + D_800A0FC4;
    acceleration[0] = 0.0f;
    acceleration[1] = 0.0f;
    acceleration[2] = 0.0f;
    direction[0] += -arg3 * D_800BE9A8 * scale;
    direction[1] += -arg4 * D_800BE9A8 * scale;
    direction[2] += -arg5 * D_800BE9A8 * scale;
    alpha_random = func_150ADA68();
    size_random = func_150ADA68();
    random_a = func_150ADA20();
    func_151A26EC(&position[0], &acceleration[0], &direction[0], 0.986891f, (alpha_random * D_800A0FC8) + D_800A0FCC, (size_random * 200.0f) + 150.0f, (random_a % 26U) + 0x28, (func_150ADA20() % 201U) + 0x37, 0x1E, 0x14, 0, -1, 0x34, 0x35, 0x34, (s32) *((u8 *)arg6 + 0xC), (s32) *((u8 *)arg6 + 1));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E03F8 */
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
