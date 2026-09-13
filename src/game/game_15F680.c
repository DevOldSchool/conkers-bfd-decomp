#include "types.h"

/*
 * Reviewed source unit: src/game/game_15F680.c
 * Boundary evidence: docs/evidence/game_raw_clipping_resource_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151321D0
 * - func_15132444
 * - func_151325C8
 * - func_1513264C
 * - func_15132A88
 * - func_15132B80
 * - func_15132DDC
 * - func_151332DC
 * - func_15133510
 * - func_15133588
 * - func_151336A8
 * - func_15133760
 * - func_151337C0
 * - func_15133894
 * - func_151339D4
 * - func_15133A50
 * - func_15133A94
 * - func_15133B98
 * - func_15133C58
 * - func_15133D20
 * - func_15133DE8
 * - func_15133E3C
 * - func_15133EEC
 * - func_15133FD8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game15F680TransformState {
    u8 pad0[0x18];
    f32 field18;
    f32 field1C;
    f32 field20;
    f32 field24;
    f32 field28;
    u8 pad2C[0xC];
    f32 field38;
    f32 field3C;
    f32 field40;
} Game15F680TransformState;

void func_15142838(s32, f32, f32, f32, f32, f32, f32, f32, f32);

#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_151321D0.s")
extern void (*D_800899B0[])(void);

void func_151323AC(void *arg0) {
    u8 var_v0;

    if (*(s32 *)((u8 *)arg0 + 0x60) & 0x100) {
        var_v0 = *(u8 *)((u8 *)arg0 + 0x68);
    } else {
        var_v0 = 0;
    }
    D_800899B0[var_v0]();
}
extern void (*D_800899D4[])(void);

void func_151323F8(void *arg0) {
    u8 var_v0;

    if (*(s32 *)((u8 *)arg0 + 0x60) & 0x100) {
        var_v0 = *(u8 *)((u8 *)arg0 + 0x68);
    } else {
        var_v0 = 0;
    }
    D_800899D4[var_v0]();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15132444.s")
void func_15132444(s32 arg0);
void func_15169824(s32 arg0);

void func_15132570(s32 arg0) {
    func_15132444(arg0);
    func_15169804(arg0);
}
void func_1513259C(s32 arg0) {
    func_15132444(arg0);
    func_15169824(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_151325C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_1513264C.s")
void func_1513264C(s32, s32, s32, s32, s32, u8, s32);

void func_15132A4C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    func_1513264C(arg0, arg1, arg2, 0, arg3, arg4, arg5);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15132A88.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15132B80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15132DDC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_151332DC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133510.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133588.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_151336A8.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15133760 CURRENT (100) */
s32 func_15133760(s32 arg0, Game15F680TransformState *arg1) {
    func_15142838(arg0, arg1->field18, arg1->field1C, arg1->field20,
                  arg1->field24, arg1->field28, arg1->field38,
                  arg1->field3C, arg1->field40);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15133760 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133760.s")
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151337C0 CURRENT (325) */
s32 func_151337C0(void *arg0) {
    f32 temp_fa0;
    f32 temp_fv1;

    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x5C);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x48);
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)arg0 + 0x38) + (*(f32 *)((u8 *)arg0 + 0x44) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C) + ((temp_fv1 * D_800BE9A4) + (D_800BE9A4 * temp_fa0 * D_800BE9A4 * 0.5f)));
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) (*(f32 *)((u8 *)arg0 + 0x40) + (*(f32 *)((u8 *)arg0 + 0x4C) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x48) = (f32) (temp_fv1 + (temp_fa0 * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x20) = (f32) (*(f32 *)((u8 *)arg0 + 0x20) + (*(f32 *)((u8 *)arg0 + 0x50) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x24) = (f32) (*(f32 *)((u8 *)arg0 + 0x24) + (*(f32 *)((u8 *)arg0 + 0x54) * D_800BE9A4));
    *(f32 *)((u8 *)arg0 + 0x28) = (f32) (*(f32 *)((u8 *)arg0 + 0x28) + (*(f32 *)((u8 *)arg0 + 0x58) * D_800BE9A4));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151337C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_151337C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133894.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151339D4 CURRENT (275) */
s32 func_151339D4(void *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    f32 temp_fv0;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x10) + arg4);
    *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)arg0 + 0x44) * temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x48) = (f32) (*(f32 *)((u8 *)arg0 + 0x48) * -temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x4C) = (f32) (*(f32 *)((u8 *)arg0 + 0x4C) * temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x50) = (f32) (*(f32 *)((u8 *)arg0 + 0x50) * temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x54) = (f32) (*(f32 *)((u8 *)arg0 + 0x54) * temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * temp_fv0);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151339D4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_151339D4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15133A50 CURRENT (460) */
s32 func_15133A50(void *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    *(f32 *)((u8 *)arg0 + 0x44) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x48) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x4C) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x50) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x54) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x10) + arg4);
    *(f32 *)((u8 *)arg0 + 0x58) = 0.0f;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15133A50 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133A50.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133A94.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15133B98 CURRENT (3897) */
s32 func_15133B98(void *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    f32 temp_ft1;
    f32 temp_ft5;

    temp_ft5 = *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)((u8 *)arg0 + 0x48) = (f32) (*(f32 *)((u8 *)arg0 + 0x48) * -temp_ft5);
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x10) + arg4);
    temp_ft1 = fabsf(*(f32 *)((u8 *)arg0 + 0x48));
    *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)arg0 + 0x44) * temp_ft5);
    *(f32 *)((u8 *)arg0 + 0x4C) = (f32) (*(f32 *)((u8 *)arg0 + 0x4C) * temp_ft5);
    *(f32 *)((u8 *)arg0 + 0x50) = (f32) (*(f32 *)((u8 *)arg0 + 0x50) * temp_ft5);
    *(f32 *)((u8 *)arg0 + 0x54) = (f32) (*(f32 *)((u8 *)arg0 + 0x54) * temp_ft5);
    *(f32 *)((u8 *)arg0 + 0x58) = (f32) (*(f32 *)((u8 *)arg0 + 0x58) * temp_ft5);
    if (temp_ft1 < 4.0f) {
        *(f32 *)((u8 *)arg0 + 0x44) = 0.0f;
        *(s32 *)((u8 *)arg0 + 0x60) = (s32) (*(s32 *)((u8 *)arg0 + 0x60) & ~0x69);
        *(f32 *)((u8 *)arg0 + 0x48) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x4C) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x50) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x54) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x58) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x5C) = 0.0f;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15133B98 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133B98.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133C58.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133D20.s")
void func_1516972C(void *arg0);
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15133DE8 CURRENT (40) */
void func_15133DE8(void *arg0, s32 *arg1, u8 arg2) {
    if (arg2 == 0) {
        if ((*arg1 == *(s32 *)((u8 *)arg0 + 0x7C)) ||
            (*((u8 *)arg1 + 4) == *(u8 *)((u8 *)arg0 + 0x80))) {
            func_1516972C(arg0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15133DE8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133DE8.s")
void func_15169260(void *, s32, s32, s32);
typedef struct {
    s32 field0;
    s32 field4;
} Func15133E3CData;
extern Func15133E3CData D_800A3860;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15133E3C CURRENT (460) */
void func_15133E3C(s32 arg0, s32 arg1) {
    Func15133E3CData sp18;

    sp18 = D_800A3860;
    func_15169260(&sp18, 2, arg0, arg1 & 0xFF);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15133E3C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133E3C.s")
/* Call context: func_15133EEC: unique active project prototype */
s32 func_15133EEC(s32, u16, u8, s32);

void func_15133E84(s32 arg0, void *arg1, s32 arg2) {
    func_15133EEC(arg0, *(u16 *)((u8 *)arg1 + 0x170), *(u8 *)((u8 *)arg1 + 0x172), *(s32 *)((u8 *)arg1 + 0x174));
}
/* Call context: func_15133EEC: unique active project prototype */

void func_15133EB8(s32 arg0, void *arg1, s32 arg2) {
    func_15133EEC(arg0, *(u16 *)((u8 *)arg1 + 0x174), *(u8 *)((u8 *)arg1 + 0x176), *(s32 *)((u8 *)arg1 + 0x178));
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133EEC.s")
s32 func_15133EEC(s32, u16, u8, s32);               /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15133FD8 CURRENT (1545) */
s32 func_15133FD8(s32 arg0, u8 *arg1, s32 arg2) {
    s32 temp_at;
    s32 temp_t8;
    s32 var_s0;
    s32 var_s1;
    u8 *temp_v0;

    var_s1 = arg0;
    var_s0 = 0;
    if ((s32) *(u8 *)((u8 *)arg1 + 0x170) > 0) {
        do {
            temp_v0 = (void *)(arg1 + 0x170 + (var_s0 * 8));
            temp_t8 = (var_s0 + 1) & 0xFF;
            temp_at = temp_t8 < (s32) *(u8 *)((u8 *)arg1 + 0x170);
            var_s0 = temp_t8;
            var_s1 = func_15133EEC(var_s1, *(u16 *)((u8 *)temp_v0 + 4), *(u8 *)((u8 *)temp_v0 + 6), *(s32 *)((u8 *)temp_v0 + 8));
        } while (temp_at != 0);
    }
    return var_s1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15133FD8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133FD8.s")
