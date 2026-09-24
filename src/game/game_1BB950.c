#include "types.h"

/*
 * Reviewed source unit: src/game/game_1BB950.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1518E73C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_1514EDF0(s32 arg0, s32 arg1);
void func_1518E308(void *arg0);
void func_15169804(s32 arg0);
void func_15169824(s32 arg0);

void func_1518E4A0(void *arg0) {
    func_1518E308(arg0);
    func_1514EDF0((s32) arg0, *(s32 *)((u8 *)arg0 + 0x18));
}
void func_1518E4CC(void *arg0) {
    func_1518E4A0(arg0);
    func_15169804((s32) arg0);
}
void func_1518E4F8(void *arg0) {
    func_1518E4A0(arg0);
    func_15169824((s32) arg0);
}
s32 func_150ADA20();                                /* extern */

void func_1518E524(s8 *arg0, u8 *arg1, s8 *arg2, s8 *arg3, s8 *arg4, u8 *arg5, s16 *arg6) {
    s32 temp_v1;

    *arg1 = 2;
    if (func_150ADA20() & 1) {
        *arg1 |= 1;
    }
    temp_v1 = func_150ADA20() & 1;
    switch (temp_v1) {                              /* irregular */
    case 0:
        *arg0 = 0x13;
        break;
    case 1:
        *arg0 = 0x14;
        break;
    }
    *arg2 = 0;
    *arg3 = 0;
    *arg4 = 0;
    *arg5 = 0xFF;
    *arg6 = 0x301;
}
/* Call context: func_151429E0: unique active project prototype */
void func_151429E0(u8, u8 *, u8 *, u8 *);

void func_1518E5D8(s8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, u8 *arg4, u8 *arg5, s16 *arg6) {
    s32 var_v0;

    if (func_150ADA20() & 1) {
        *arg1 |= 1;
    }
    *arg0 = 0x16;
    if (func_150ADA20() & 1) {
        var_v0 = 3;
    } else {
        var_v0 = 4;
    }
    func_151429E0(var_v0, arg2, arg3, arg4);
    *arg5 = 0xC8;
    *arg6 = 0x401;
}
typedef struct Game1BB950State {
    u8 pad0;
    u8 variant;
    u8 pad2[0xA];
    u8 intensity;
    u8 padD[0xB];
    s32 owner;
    u8 pad1C[2];
    s16 timer;
    u8 pad20;
    s8 callback;
} Game1BB950State;

void *func_1518D1C0(s32, s32, s32, s32, s32, s32, void *);
extern u8 D_800A7460;
extern u8 D_800A749C;

s32 func_1518E66C(Game1BB950State *arg0) {
    func_1518D1C0(arg0->owner, 3, 0, 0, arg0->intensity, arg0->variant, &D_800A7460);
    arg0->timer = 0x80;
    arg0->callback = -1;
    return 0;
}
s32 func_1518E6D4(Game1BB950State *arg0) {
    func_1518D1C0(arg0->owner, 4, 0, 0, arg0->intensity, arg0->variant, &D_800A749C);
    arg0->timer = 0x80;
    arg0->callback = -1;
    return 0;
}
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
/* Call context: func_10022EC0: verified SDK alias memcpy=0x10022EC0 in config/game/us-sdk.ld; prototype and unsigned size_t in lib/ultralib/include/compiler/ido/memory.h */
/* Call context: func_151D5D60: unique active project prototype */
void * func_10022EC0(void *, const void *, u32);
void func_151D5D60(void *, s16, s32, void **, u8 *);

f32 func_150489B0(s32);                             /* extern */
f32 func_15048A40(s32);                   /* extern */
extern f32 D_800A7B60;
extern f32 D_800A7B64;
extern f32 D_800BE9A8;
extern f32 D_800DD1D8[];
extern f32 D_800DD1E8[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518E73C CURRENT (5356) */
void *func_1518E73C(void *arg0, s16 arg1) {
    void *sp74;
    void *sp70;
    f32 sp68;
    f32 sp60;
    f32 sp50;
    f32 sp4C;
    u8 sp3F;
    volatile f32 negative;
    f32 temp_fa0;
    f32 temp_fa1;
    register f32 temp_fs0;
    f32 temp_ft2;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    f32 var_fa0;
    f32 var_fv1;
    s32 temp_t0;
    s32 temp_t2;
    s32 var_v1;
    void *temp_a1;
    void *temp_v0;

    func_151D5D60((u8 *)arg0 + 0x100, arg1, 0x40, &sp74, &sp3F);
    sp70 = sp74;
    if (sp74 != 0) {
        if (sp3F != 0) {
            temp_v0 = (u8 *)arg0 + (arg1 * 4);
            temp_a1 = (u8 *)arg0 + 0xC0;
            func_10022EC0((*(void **)((u8 *)temp_v0 + 0x100)), temp_a1, 0x40U);
            func_10022EC0((*(u8 **)((u8 *)temp_v0 + 0x100)) + 0x40, temp_a1, 0x40U);
        }
        temp_t0 = arg1 * 4;
        temp_ft5 = *(f32 *)((u8 *)D_800DD1D8 + temp_t0);
        temp_fs0 = *(f32 *)((u8 *)D_800DD1E8 + temp_t0);
        var_v1 = -1;
        var_fa0 = ((((*(f32 *)((u8 *)arg0 + 0x40)) - (*(f32 *)((u8 *)arg0 + 0x34))) * temp_fs0) - (temp_ft5 * ((*(f32 *)((u8 *)arg0 + 0x48)) - (*(f32 *)((u8 *)arg0 + 0x3C))))) * D_800BE9A8;
        if (var_fa0 < 0.0f) {
            var_fa0 = -var_fa0;
            var_v1 = 0;
        }
        var_fv1 = sqrtf(var_fa0) * (*(f32 *)((u8 *)arg0 + 0x160));
        if (D_800A7B60 < var_fv1) {
            var_fv1 = D_800A7B60;
        }
        if (var_v1 != 0) {
            var_fv1 = -var_fv1;
        }
        temp_t2 = (u32) (var_fv1 * D_800A7B64) & 0xFF;
        sp68 = temp_ft5;
        sp60 = func_15048A40(temp_t2);
        temp_fv0 = func_150489B0(temp_t2);
        temp_fa0 = (*(f32 *)((u8 *)arg0 + 0x2C));
        temp_fa1 = (*(f32 *)((u8 *)arg0 + 0x30));
        temp_fv1 = temp_fa0 * temp_fv0;
        temp_ft4 = temp_fa0 * sp60;
        temp_ft2 = temp_fa1 * temp_fv0;
        sp50 = temp_fa1 * sp60;
        sp4C = temp_ft2;
        (*(s16 *)((u8 *)sp74 + 0)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + (temp_fv1 * temp_fs0));
        (*(s16 *)((u8 *)sp74 + 2)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + temp_ft4);
        (*(s16 *)((u8 *)sp74 + 4)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - (temp_fv1 * temp_ft5));
        negative = -temp_fv1;
        (*(s16 *)((u8 *)sp74 + 0x10)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + (negative * temp_fs0));
        (*(s16 *)((u8 *)sp74 + 0x12)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) - temp_ft4);
        (*(s16 *)((u8 *)sp74 + 0x14)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - (negative * temp_ft5));
        temp_fv0_2 = -(temp_fv1 + sp50);
        (*(s16 *)((u8 *)sp74 + 0x20)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + (temp_fv0_2 * temp_fs0));
        (*(s16 *)((u8 *)sp74 + 0x22)) = (s16) (s32) (((*(f32 *)((u8 *)arg0 + 0x38)) + temp_ft2) - temp_ft4);
        (*(s16 *)((u8 *)sp74 + 0x24)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - (temp_fv0_2 * temp_ft5));
        temp_fv0_3 = temp_fv1 - sp50;
        (*(s16 *)((u8 *)sp74 + 0x30)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x34)) + (temp_fv0_3 * temp_fs0));
        (*(s16 *)((u8 *)sp74 + 0x32)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x38)) + sp4C + temp_ft4);
        (*(s16 *)((u8 *)sp74 + 0x34)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x3C)) - (temp_fv0_3 * temp_ft5));
        return sp70;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518E73C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BB950/func_1518E73C.s")
