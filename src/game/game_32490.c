#include "types.h"

/*
 * Reviewed source unit: src/game/game_32490.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_medium_single_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15004FE0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_10004074(s32);
void *func_10003C40(s32, s32, s32, s32);
u32 func_1502B7F0(s32 *, s32, ...);
extern s32 D_800C6650;
extern u32 D_800C6654;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15004FE0 CURRENT (1464) */
s32 func_15004FE0(s32 arg0) {
    s32 source;
    s32 index;
    s32 remaining;
    volatile s32 indexHome;
    register s32 outputOffset;
    register s32 inputOffset;

    source = 0;
    indexHome = 0;
    remaining = (s32)(func_1502B7F0(&source, 3, 0xC, arg0, 3) / 24U);
    D_800C6650 = (s32)func_10003C40((u32)remaining * 20U, 1, 1, 0);
    index = indexHome;
    D_800C6654 = remaining;
    if ((s32)remaining > 0) {
        outputOffset = index * 20;
        inputOffset = index * 24;
        do {
            *(s16 *)((u8 *)D_800C6650 + outputOffset) = (s16)(s32)*(f32 *)((u8 *)source + inputOffset);
            *(s16 *)((u8 *)D_800C6650 + outputOffset + 2) = (s16)(s32)*(f32 *)((u8 *)source + inputOffset + 4);
            *(s16 *)((u8 *)D_800C6650 + outputOffset + 4) = (s16)(s32)*(f32 *)((u8 *)source + inputOffset + 8);
            *(s16 *)((u8 *)D_800C6650 + outputOffset + 6) = 0;
            *(u32 *)((u8 *)D_800C6650 + outputOffset + 8) = (u32)(*(f32 *)((u8 *)source + inputOffset + 0xC) * *(f32 *)((u8 *)source + inputOffset + 0xC));
            remaining--;
            index++;
            *(s16 *)((u8 *)D_800C6650 + outputOffset + 0xC) = (s16)(s32)*(f32 *)((u8 *)source + inputOffset + 0x10);
            *(s16 *)((u8 *)D_800C6650 + outputOffset + 0xE) = (s16)(s32)(*(f32 *)((u8 *)source + inputOffset + 0xC) + *(f32 *)((u8 *)source + inputOffset));
            *(s16 *)((u8 *)D_800C6650 + outputOffset + 0x10) = (s16)(s32)(*(f32 *)((u8 *)source + inputOffset) - *(f32 *)((u8 *)source + inputOffset + 0xC));
            *(s16 *)((u8 *)D_800C6650 + outputOffset + 0x12) = (s16)(s32)*(f32 *)((u8 *)source + inputOffset + 0x14);
            outputOffset += 20;
            inputOffset += 24;
        } while ((s32)remaining > 0);
    }
    if (source != 0) {
        indexHome = index;
        func_10004074(source);
        index = indexHome;
    }
    return index;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15004FE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_32490/func_15004FE0.s")
