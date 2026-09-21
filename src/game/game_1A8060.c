#include "types.h"

/*
 * Reviewed source unit: src/game/game_1A8060.c
 * Boundary evidence: docs/evidence/game_raw_compact_display_resource_pairs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1517ABB0
 * - func_1517AD00
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern u8 *D_800DD460[];
extern u8 D_800A7230[];
extern u16 D_800C4310[];
void func_10004074(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1517ABB0 CURRENT (2305) */
void func_1517ABB0(void) {
    u8 **groups = D_800DD460;
    u8 *configs = D_800A7230;
    u16 *counts = D_800C4310;
    s32 groupIndex = 0;

    do {
        u8 *config = configs + groupIndex * 8;
        if (*groups != 0) {
            s32 setIndex = 0;
            u16 setCount = counts[config[0]];
            if (setCount > 0) {
                do {
                    s32 entryIndex = 0;
                    u8 slotCount = config[1];
                    if (slotCount > 0) {
                        s32 setOffset = setIndex * 4;
                        s32 entryOffset = 0;
                        do {
                            u8 *entry = *(u8 **)(*groups + setOffset) + entryOffset;
                            s32 resource = *(s32 *)entry;
                            if (resource != 0) {
                                u8 timer = entry[4];
                                if (timer != 0) {
                                    entry[4] = timer - 1;
                                    slotCount = config[1];
                                } else {
                                    func_10004074(resource);
                                    *(s32 *)(*(u8 **)(*groups + setOffset) + entryOffset) = 0;
                                    slotCount = config[1];
                                }
                            }
                            entryIndex++;
                            entryOffset += 8;
                        } while (entryIndex < slotCount);
                        setCount = counts[config[0]];
                    }
                    setIndex++;
                } while (setIndex < setCount);
            }
        }
        groupIndex++;
        groups++;
    } while (groupIndex != 2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1517ABB0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A8060/func_1517ABB0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A8060/func_1517AD00.s")
