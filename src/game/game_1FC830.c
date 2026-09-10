#include "types.h"

/*
 * Reviewed source unit: src/game/game_1FC830.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151CF380
 * - func_151CF844
 * - func_151CF898
 * - func_151CFA4C
 * - func_151D0024
 * - func_151D0058
 * - func_151D014C
 * - func_151D08F0
 * - func_151D09A8
 * - func_151D0ED8
 * - func_151D0F08
 * - func_151D0F34
 * - func_151D0F60
 * - func_151D10E4
 * - func_151D1138
 * - func_151D1328
 * - func_151D1388
 * - func_151D13B4
 * - func_151D13E0
 * - func_151D1448
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151CF380.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151CF844.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151CF898.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151CFA4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151D0024.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151D0058.s")
void func_151D0128(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x28);
    if (*(u16 *)(temp_v0 + 0x84) != *(u16 *)(arg0 + 0x2E)) {
        *(s16 *)(arg0 + 0xE) = -1;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151D014C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151D08F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151D09A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151D0ED8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151D0F08.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151D0F34.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151D0F60.s")
s32 func_151D1074(void *arg0, void *arg1) {
    *(f32 *)((u8 *)arg1 + 0) = (f32) *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)((u8 *)arg1 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 0x180) + 8.0f);
    *(f32 *)((u8 *)arg1 + 8) = (f32) *(f32 *)((u8 *)arg0 + 0x1C);
    return 1;
}
void func_151D10E4(s32 arg0, s32 arg1, s32 arg2);

void func_151D10A4(s32 arg0, s32 arg1) {
    func_151D10E4(arg0, arg1, 0);
}
void func_151D10C4(s32 arg0, s32 arg1) {
    func_151D10E4(arg0, arg1, 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151D10E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151D1138.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151D1328.s")
void func_151D1368(void) {
    func_151D13E0();
}
void func_1514933C(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D1388 CURRENT (200) */
void func_151D1388(s32 arg0) {
    func_151D1368();
    func_1514933C(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D1388 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151D1388.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151D13B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151D13E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151D1448.s")
