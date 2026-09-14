#include "types.h"

/*
 * Reviewed source unit: src/game/game_17CAF0.c
 * Boundary evidence: docs/evidence/game_raw_emission_descriptor_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1514F640
 * - func_1514F6E8
 * - func_1514F808
 * - func_1514F8F8
 * - func_1514FBFC
 * - func_1514FCE8
 * - func_1514FF44
 * - func_15150178
 * - func_15150400
 * - func_1515080C
 * - func_15150D1C
 * - func_15150F90
 * - func_151511FC
 * - func_15151670
 * - func_15151A38
 * - func_15151D6C
 * - func_15152190
 * - func_15152520
 * - func_15152874
 * - func_15152B38
 * - func_15152F70
 * - func_15153298
 * - func_15153634
 * - func_151539B4
 * - func_15153CCC
 * - func_15153F18
 * - func_151541B8
 * - func_1515452C
 * - func_15154684
 * - func_15154884
 * - func_15154A88
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

f32 func_15144A74(void *, void *);                  /* extern */
s32 func_15144E80(void *, void *, void *, void *);  /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514F640 CURRENT (42) */
void func_1514F640(u8 *arg0, u8 *arg1) {
    void *sp24;
    void *temp_a3;

    *(s8 *)((u8 *)arg1 + 0) = 2;
    temp_a3 = (void *)(arg1 + 4);
    *(f32 *)((u8 *)arg1 + 0x28) = (f32) *(f32 *)((u8 *)arg0 + 0x20);
    sp24 = temp_a3;
    if ((func_15144E80(arg0 + 0xC, arg1 + 0x10, arg1 + 0x1C, temp_a3) != 0) && (func_15144A74(temp_a3, arg0) < 0.0f)) {
        *(f32 *)((u8 *)arg1 + 4) = (f32) -*(f32 *)((u8 *)arg1 + 4);
        *(f32 *)((u8 *)arg1 + 8) = (f32) -*(f32 *)((u8 *)arg1 + 8);
        *(f32 *)((u8 *)arg1 + 0xC) = (f32) -*(f32 *)((u8 *)arg1 + 0xC);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514F640 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_1514F640.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_1514F6E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_1514F808.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_1514F8F8.s")
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Game17CAF0Vec3f;

typedef struct {
    u8 pad_0[0xC];
    f32 field_C;
    u8 field_10;
} Game17CAF0Emitter;

s32 func_15146078(Game17CAF0Emitter *, Game17CAF0Vec3f *,
                  Game17CAF0Vec3f *, s32);
void func_1514F8F8(void *, Game17CAF0Emitter *, Game17CAF0Vec3f *,
                   Game17CAF0Vec3f *, f32, s32, s32);

void func_1514FB98(Game17CAF0Emitter *arg0, u8 arg1, s32 arg2, s32 arg3) {
    Game17CAF0Vec3f sp34;
    Game17CAF0Vec3f sp28;

    if (func_15146078(arg0, &sp34, &sp28, arg3) != 0) {
        func_1514F8F8(&arg0->field_10, arg0, &sp34, &sp28, arg0->field_C,
                      arg1, arg2);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_1514FBFC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_1514FCE8.s")
void func_1514F640(s32, void *);
void func_1514FF44(void *, s32, s32, u8, s32);

void func_1514FEFC(s32 arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    u8 sp24[0x30];

    func_1514F640(arg0, sp24 + 4);
    func_1514FF44(sp24 + 4, arg1, arg2, arg3, arg4);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_1514FF44.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15150178.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15150400.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_1515080C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15150D1C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15150F90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_151511FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15151670.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15151A38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15151D6C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15152190.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15152520.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15152874.s")
typedef struct {
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
} Game17CAF0Color;

u32 func_150ADA20(); /* extern */
extern u8 D_800A5FE0[];

void func_15152ABC(Game17CAF0Color *arg0) {
    struct {
        u8 *color;
        u8 *unused;
    } locals;

    locals.color = (((func_150ADA20() % 5U) & 0xFF) * 3) + D_800A5FE0;
    arg0->alpha = (func_150ADA20() % 101U) + 0x9B;
    arg0->red = locals.color[0];
    arg0->green = locals.color[1];
    arg0->blue = locals.color[2];
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15152B38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15152F70.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15153298.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15153634.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_151539B4.s")
void func_1514F640(s32, void *);
void func_15153CCC(void *, s32, s32, u8, s32);

void func_15153C84(s32 arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    u8 sp24[0x30];

    func_1514F640(arg0, sp24 + 4);
    func_15153CCC(sp24 + 4, arg1, arg2, arg3, arg4);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15153CCC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15153F18.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_151541B8.s")
extern f32 D_800BE9A4;
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1515452C CURRENT (425) */
s32 func_1515452C(u8 *arg0) {
    f32 temp_fv1;
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + 0x170);
    temp_fv1 = sqrtf(*(f32 *)((u8 *)arg0 + 0x170)) * *(f32 *)((u8 *)arg0 + 0x178);
    *(f32 *)((u8 *)arg0 + 0x18) = temp_fv1;
    if (!(*(u8 *)((u8 *)arg0 + 0x184) & 1)) {
        *(f32 *)((u8 *)arg0 + 0x1C) = temp_fv1;
    }
    {
        f32 temp_fv0 = *(f32 *)((u8 *)arg0 + 0x170);
    *(s8 *)((u8 *)arg0 + 0x70) = (s8) (u32) (*(f32 *)((u8 *)temp_v0 + 0xC) - (*(f32 *)((u8 *)temp_v0 + 0x10) * temp_fv0 * temp_fv0));
    *(f32 *)((u8 *)arg0 + 0x170) = (f32) (*(f32 *)((u8 *)arg0 + 0x170) + D_800BE9A4);
    if (*(f32 *)((u8 *)temp_v0 + 4) < *(f32 *)((u8 *)arg0 + 0x170)) {
        return 0;
    }
    *(f32 *)((u8 *)arg0 + 0x20) = (f32) (*(f32 *)((u8 *)arg0 + 0x20) + (*(f32 *)((u8 *)arg0 + 0x50) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x24) = (f32) (*(f32 *)((u8 *)arg0 + 0x24) + (*(f32 *)((u8 *)arg0 + 0x54) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x28) = (f32) (*(f32 *)((u8 *)arg0 + 0x28) + (*(f32 *)((u8 *)arg0 + 0x58) * D_800BE9A4));
    return 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1515452C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_1515452C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15154684.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15154884.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15154A88 CURRENT (1560) */
s32 func_15154A88(u8 *arg0) {
    f32 temp_fv0;
    f32 var_ft4;
    s32 temp_t8;
    u8 *temp_v1;

    temp_fv0 = func_15047D60(*(f32 *)((u8 *)arg0 + 0x17C));
    temp_v1 = (void *)(arg0 + 0x170);
    {
        f32 temp_fv1 = *(f32 *)((u8 *)temp_v1 + 4) * temp_fv0;
    *(f32 *)((u8 *)arg0 + 0x1C) = temp_fv1;
    *(f32 *)((u8 *)arg0 + 0x18) = temp_fv1;
    temp_t8 = (u32) *(f32 *)((u8 *)temp_v1 + 8) & 0xFF;
    var_ft4 = (f32) temp_t8;
    if (temp_t8 < 0) {
        var_ft4 += 4294967296.0f;
    }
    *(s8 *)((u8 *)arg0 + 0x70) = (s8) (u32) (var_ft4 * temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x170) = (f32) (*(f32 *)((u8 *)arg0 + 0x170) - D_800BE9A4);
    if (*(f32 *)((u8 *)arg0 + 0x170) <= 0.0f) {
        return 0;
    }
    *(f32 *)((u8 *)temp_v1 + 0xC) = (f32) (*(f32 *)((u8 *)temp_v1 + 0xC) + (*(f32 *)((u8 *)temp_v1 + 0x10) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x20) = (f32) (*(f32 *)((u8 *)arg0 + 0x20) + (*(f32 *)((u8 *)arg0 + 0x50) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x24) = (f32) (*(f32 *)((u8 *)arg0 + 0x24) + (*(f32 *)((u8 *)arg0 + 0x54) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x28) = (f32) (*(f32 *)((u8 *)arg0 + 0x28) + (*(f32 *)((u8 *)arg0 + 0x58) * D_800BE9A4));
    return 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15154A88 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_17CAF0/func_15154A88.s")
