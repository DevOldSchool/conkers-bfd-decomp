#include "types.h"

/*
 * Reviewed source unit: src/game/game_C4DC0.c
 * Boundary evidence: docs/evidence/game_raw_descriptor_callback_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15097910
 * - func_150979CC
 * - func_15097A8C
 * - func_15099C14
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15082A44(void *, s32, s32, s32, s32);
s32 func_15083E0C(s32);
void *func_15083E90(u8, s32);
extern s32 D_800D20FC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15097910 CURRENT (929) */
s32 func_15097910(s32 arg0, u8 arg1) {
    s32 index;
    s32 result;
    void *entry;

    result = func_15083E0C(arg0 & 0xFF);
    if (result != -1) {
        entry = func_15083E90(arg1, result);
        if (entry == 0) {
            *(u8 *)((u8 *)D_800D20FC + result * 0x30 + 2) = 0;
            func_15082A44((u8 *)D_800D20FC + result * 0x30, result, 0, 0, 0);
            if (result == 0) {
                return -1;
            }
            index = func_15083E0C(arg1);
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
#endif /* CONKER_DEFERRED_CANDIDATE func_15097910 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C4DC0/func_15097910.s")
void func_15060F28(u8 *, s32);
void func_15053430(u8 *);
u8 *func_1505EEF4(void);
extern u8 D_800D2100;
extern s32 D_800D3840;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150979CC CURRENT (1439) */
s32 func_150979CC(s32 arg0, void *arg1) {
    u8 *resource;

    resource = func_1505EEF4();
    if (resource == 0) {
        return 0;
    }
    if (arg0 < D_800D2100) {
        *(u8 *)((u8 *)D_800D20FC + arg0 * 0x30 + 2) = 1;
    }
    if (D_800D3840 == 2 && *(s32 *)((u8 *)arg1 + 4) != 0) {
        func_15053430(resource);
    } else {
        func_15060F28(resource, 0);
    }
    return 0xF423F;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150979CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C4DC0/func_150979CC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C4DC0/func_15097A8C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_C4DC0/func_15099C14.s")
