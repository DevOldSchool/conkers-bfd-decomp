#include "types.h"

/*
 * Reviewed source unit: src/main/init_1420.c
 * Boundary evidence: docs/evidence/main_bootstrap_source_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_bootstrap_clear_region
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if PROFILE_US
#define clear_bootstrap_region func_80001420
#define bootstrap_region D_80043B40
#else
#define clear_bootstrap_region func_800014B0
#define bootstrap_region D_80043ED0
#endif

extern s32 bootstrap_region[];
void func_80001420(void);
void func_80004074(s32);
void func_80005B04(s32);
void func_80005BE0(void);
void func_800061F8(s32, s32);
void func_80022C90(void *, s32);
s32 func_80022DC0(void);
void func_80022DE0(s32);
void func_80022E00(void *);
extern u8 D_1002AAD0;
extern u8 D_80031AE0;
extern s32 D_8003BE70;
extern s32 D_8003BE74;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_bootstrap_clear_region CURRENT (10) */
void clear_bootstrap_region(void) {
    s32 *ptr;
    s32 count;
    s32 bias;
    s32 bias2;

    count = 4064;
    bias = 0;
    bias2 = 0;
    ptr = bootstrap_region;
    do {
        *ptr++ = 0;
    } while ((u32)ptr <
             (u32)bootstrap_region + count + bias + bias2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_bootstrap_clear_region */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_1420/func_bootstrap_clear_region.s")

void func_80001444(void) {
    s32 saved_mask;

    saved_mask = func_80022DC0();
    func_800061F8(2, 0x1F);
    func_80001420();
    func_80005BE0();
    func_80022C90(&D_1002AAD0, 0x80400000 - (s32)&D_1002AAD0);
    func_80022DE0(saved_mask);
}

void func_800014A0(void) {
    func_80022E00(&D_80031AE0);
}

void func_800014C4(s32 arg0) {
    s32 saved_mask;

    saved_mask = func_80022DC0();
    func_800061F8(2, 0x1F);
    if (D_8003BE74 != 0) {
        func_80004074(D_8003BE74 | 0x80000000);
    }
    if (D_8003BE70 != 0) {
        func_80004074(D_8003BE70 | 0x80000000);
    }
    func_80005B04(arg0);
    func_80001420();
    func_80005BE0();
    func_80022DE0(saved_mask);
}
