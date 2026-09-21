#include "types.h"

/*
 * Reviewed source unit: src/game/game_43D00.c
 * Boundary evidence: docs/evidence/game_raw_loader_transfer_emission_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15016850
 * - func_150169A0
 * - func_15017114
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_1502B7F0(s32 *, s32, s32, u8);
extern u8 D_800BE590;
extern u16 D_800BE598[];
extern s32 D_800BE5A8[];
extern u8 *D_800D20FC;
extern u8 D_800D2100;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15016850 CURRENT (3020) */
void func_15016850(void) {
    s32 sp50;
    s32 found;
    s32 offset;
    s32 index;
    s32 bound;
    u8 *scan;
    u8 count;
    u8 id;

    D_800BE590 = 0;
    count = D_800D2100;
    sp50 = 0;
    offset = 0;
    if (count > 0) {
        do {
            found = 0;
            id = D_800D20FC[offset + 4];
            index = 0;
            if (D_800BE590 > 0) {
                scan = (u8 *)D_800BE598;
                do {
                    index++;
                    if (id == *(u16 *)scan) {
                        found = 1;
                        break;
                    }
                    scan += 2;
                } while (index < D_800BE590);
            }
            if (found) {
                bound = count * 0x30;
            } else {
                if (id < 0xBB) {
                    func_1502B7F0(&sp50, 2, 0x12, id);
                }
                bound = count * 0x30;
                if (sp50 != 0) {
                    D_800BE5A8[D_800BE590] = sp50;
                    D_800BE598[D_800BE590] = id;
                    D_800BE590++;
                }
            }
            offset += 0x30;
        } while (offset < bound);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15016850 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_43D00/func_15016850.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_43D00/func_150169A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_43D00/func_15017114.s")
