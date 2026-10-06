#include "types.h"

/*
 * Reviewed source unit: src/game/game_C4DC0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_descriptor_callback_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150979CC
 * - func_15097A8C
 * - func_15099C14
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_15082A44(void *, s32, s32, s32, s32);
s32 func_15083E0C(s32);
void *func_15083E90(u8, s32);
extern s32 D_800D20FC;

s32 func_15097910(s32 arg0, u8 arg1) {
    s32 result;
    s32 index;
    s32 selector;
    void *entry;

    selector = arg0 & 0xFF;
    result = func_15083E0C(selector);
    if (result != -1) {
        entry = func_15083E90(((u8 *)&selector)[3], result);
        if (entry == 0) {
            *(u8 *)((u8 *)D_800D20FC + result * 0x30 + 2) = 0;
            if (func_15082A44((void *)(result * 0x30 + D_800D20FC), result, 0, 0, 0) == 0) {
                return -1;
            }
            index = func_15083E0C(((u8 *)&selector)[3]);
            result = index;
        } else {
            result = *(u8 *)((u8 *)entry + 0x13F);
        }
    }
    if (result != 0) {
        result |= 0x2000;
    }
    return result;
}
void func_15060F28(u8 *, s32);
void func_15053430(u8 *);
u8 *func_1505EEF4(void);
extern u8 D_800D2100;
extern s32 D_800D3840;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150979CC CURRENT (256) */
s32 func_150979CC(s32 arg0, void *arg1) {
    void *descriptor;

    descriptor = arg1;
    arg1 = func_1505EEF4();
    if (arg1 == 0) {
        return 0;
    }
    if (arg0 < D_800D2100) {
        *(u8 *)((u8 *)D_800D20FC + arg0 * 0x30 + 2) = 1;
    }
    if (D_800D3840 == 2) {
        if (*(s32 *)((u8 *)descriptor + 4) == 0) {
            func_15060F28(arg1, 0);
        } else {
            func_15053430(arg1);
        }
    } else {
        func_15060F28(arg1, 0);
    }
    return 0xF423F;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150979CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C4DC0/func_150979CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C4DC0/func_15097A8C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C4DC0/func_15099C14.s")
