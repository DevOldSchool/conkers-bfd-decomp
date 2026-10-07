#include "types.h"

/*
 * Reviewed source unit: src/main/init_5AB0.c
 * Boundary evidence: docs/evidence/boundaries/main/main_handwritten_family_boundaries.md
 *
 * TODO: Implement these source-unit functions:
 * - func_80005AB0
 * - func_80005B04
 * - func_80005BE0
 * - func_80005C2C
 * - func_800061F8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/main/init_5AB0/func_80005AB0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_5AB0/func_80005B04.s")
extern s32 D_8003BE70;
extern s16 D_8003BE78;
extern u8 *D_8003BE7C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80005BE0 CURRENT (945) */
void func_80005BE0(void) {
    u8 *cursor;
    u8 *end;
    u8 *written;
    s32 remainder;

    cursor = (u8 *)D_8003BE70;
    end = D_8003BE7C;
    do {
        written = cursor;
        *cursor = 0xFF;
        cursor++;
    } while (written != end);
    remainder = D_8003BE78 & 7;
    if (remainder != 0) {
        *end = (2 << (remainder - 1)) - 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80005BE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_5AB0/func_80005BE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_5AB0/func_80005C2C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_5AB0/func_800061F8.s")
