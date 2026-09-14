#include "types.h"

/*
 * Reviewed source unit: src/game/game_13ABD0.c
 * Boundary evidence: docs/evidence/game_raw_directly_called_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1510D720
 * - func_1510D7AC
 * - func_1510D874
 * - func_1510D8C0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_13ABD0/func_1510D720.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13ABD0/func_1510D7AC.s")
extern s8 D_800D9ED0;
extern u8 D_800D9ED8[];

void func_1510D864(void) {
    D_800D9ED0 = 0;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510D874 CURRENT (505) */
void func_1510D874(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *temp_v1;

    if ((u8)D_800D9ED0 < 8) {
        temp_v1 = &D_800D9ED8[(u8)D_800D9ED0 * 0x10];
        *(s32 *)(temp_v1 + 0) = arg0;
        *(s32 *)(temp_v1 + 4) = arg1;
        *(s32 *)(temp_v1 + 8) = arg2;
        *(s8 *)(temp_v1 + 0xC) = arg3;
        D_800D9ED0 = (u8)D_800D9ED0 + 1;
        *(s8 *)(temp_v1 + 0xD) = (s8)arg4;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510D874 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13ABD0/func_1510D874.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13ABD0/func_1510D8C0.s")
