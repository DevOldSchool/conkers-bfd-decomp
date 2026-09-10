#include "types.h"

/*
 * Reviewed source unit: src/game/game_1FFF60.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151D2AB0
 * - func_151D2B4C
 * - func_151D2BA4
 * - func_151D2C40
 * - func_151D2DCC
 * - func_151D2E14
 * - func_151D2E5C
 * - func_151D2F00
 * - func_151D2F90
 * - func_151D3130
 * - func_151D31F4
 * - func_151D3220
 * - func_151D324C
 * - func_151D3354
 * - func_151D33B8
 * - func_151D33FC
 * - func_151D343C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D2AB0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D2B4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D2BA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D2C40.s")
void func_151D2DAC(void) {
    func_151D3354();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D2DCC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D2E14.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D2E5C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D2F00.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D2F90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D3130.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D31F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D3220.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D324C.s")
void func_151D3308(void *arg0) {
    void *temp_v0;
    void *temp_v1;

    temp_v0 = *(void **)((u8 *)arg0 + 0x30);
    if (temp_v0 != 0) {
        *(void **)((u8 *)arg0 + 0x40) = (void *) *(void **)((u8 *)temp_v0 + 0x24);
        temp_v1 = *(void **)((u8 *)temp_v0 + 0x24);
        if (temp_v1 != 0) {
            *(void **)((u8 *)temp_v1 + 0x44) = arg0;
        } else {
            *(void **)((u8 *)temp_v0 + 0x28) = arg0;
        }
        *(s32 *)((u8 *)arg0 + 0x44) = 0;
        *(void **)((u8 *)temp_v0 + 0x24) = arg0;
        *(s16 *)((u8 *)temp_v0 + 0x20) = (s16) (*(s16 *)((u8 *)temp_v0 + 0x20) + 1);
        *(void **)((u8 *)arg0 + 0x30) = temp_v0;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D3354.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D33B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D33FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFF60/func_151D343C.s")
