#include "types.h"

/*
 * Reviewed source unit: src/game/game_322B0.c
 * Boundary evidence: docs/evidence/game_small_multi_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15004E00
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    s32 field0;
    s32 field4;
    s32 field8;
    u8 padC[3];
    s8 fieldF;
} Game322B0Record;

extern s32 D_800C6660;
extern s32 D_800C6664;
extern s32 D_800C6668;
extern s8 D_800C666F;
extern Game322B0Record D_800C6670;
extern Game322B0Record D_800C67F0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15004E00 CURRENT (90) */
void func_15004E00(void) {
    u32 cursor;
    u32 end;

    D_800C6660 = 0;
    D_800C6664 = 0;
    D_800C6668 = 0;
    D_800C666F = 0;
    end = (u32)&D_800C67F0;
    cursor = (u32)&D_800C6670;
clear_records:
    cursor += 0x40;
    *(s32 *)(cursor - 0x30) = 0;
    *(s32 *)(cursor - 0x2c) = 0;
    *(s32 *)(cursor - 0x28) = 0;
    *(s8 *)(cursor - 0x21) = 0;
    *(s32 *)(cursor - 0x20) = 0;
    *(s32 *)(cursor - 0x1c) = 0;
    *(s32 *)(cursor - 0x18) = 0;
    *(s8 *)(cursor - 0x11) = 0;
    *(s32 *)(cursor - 0x10) = 0;
    *(s32 *)(cursor - 0xc) = 0;
    *(s32 *)(cursor - 0x8) = 0;
    *(s8 *)(cursor - 0x1) = 0;
    *(s32 *)(cursor - 0x40) = 0;
    *(s32 *)(cursor - 0x3c) = 0;
    *(s32 *)(cursor - 0x38) = 0;
    *(s8 *)(cursor - 0x31) = 0;
    if (cursor != end) {
        goto clear_records;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15004E00 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_322B0/func_15004E00.s")
/* Call context: func_10003C40: unique active project prototype */
void * func_10003C40(s32, s32, s32, s32);
extern void *D_800B0DF0;
extern u16 D_800C3E7C;
extern void *D_800C3E80;
extern void *D_800C3E84;

void func_15004E80(void) {
    D_800C3E80 = func_10003C40((D_800C3E7C = *(u16 *)((u8 *)D_800B0DF0 + 0x1A)) << 6, 1, 3, 0);
    D_800C3E84 = func_10003C40(D_800C3E7C << 6, 1, 3, 0);
}
