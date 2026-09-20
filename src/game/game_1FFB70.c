#include "types.h"

/*
 * Reviewed source unit: src/game/game_1FFB70.c
 * Boundary evidence: docs/evidence/game_raw_compact_display_resource_pairs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151D275C
 * - func_151D2830
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_15167A68(s32, s32, s32, s32, s32, s32);

void func_151D26C0(s16 arg0) {
    void *temp_v0;

    temp_v0 = func_15167A68(0x3C, 1, 0x18, 0, 0xFF, 1);
    *(s16 *)((u8 *)temp_v0 + 0x14) = 0;
    *(s16 *)((u8 *)temp_v0 + 0x12) = 0;
    *(s16 *)((u8 *)temp_v0 + 0xE) = 0;
    *(s8 *)((u8 *)temp_v0 + 0x16) = 1;
    *(s16 *)((u8 *)temp_v0 + 0x10) = arg0;
}
extern void *D_800DD0E0;

void func_151D2718(s16 arg0) {
    void *var_v0;

    var_v0 = D_800DD0E0;
    if (var_v0 != 0) {
        do {
            if (arg0 == *(s16 *)((u8 *)var_v0 + 0x10)) {
                *(s8 *)((u8 *)var_v0 + 0x16) = -2;
            }
            var_v0 = *(void **)((u8 *)var_v0 + 8);
        } while (var_v0 != 0);
    }
}
void func_1516972C(void);
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D275C CURRENT (115) */
void func_151D275C(void *arg0) {
    s32 temp_v1;
    s8 temp_v0;

    *(s16 *)((u8 *)arg0 + 0xE) = (s16)(*(s16 *)((u8 *)arg0 + 0xE) +
        (D_800BE9E4 * (temp_v0 = *(s8 *)((u8 *)arg0 + 0x16))));
    if ((temp_v0 > 0) && (*(s16 *)((u8 *)arg0 + 0xE) >= 0xED)) {
        temp_v1 = 0x128 - *(s16 *)((u8 *)arg0 + 0xE);
        *(s16 *)((u8 *)arg0 + 0x14) = (s16)(temp_v1 * 4);
        if (*(s16 *)((u8 *)arg0 + 0x14) < 0) {
            *(s16 *)((u8 *)arg0 + 0x14) = 0;
        }
    } else {
        *(s16 *)((u8 *)arg0 + 0x14) = (s16)(*(s16 *)((u8 *)arg0 + 0xE) * 2);
    }
    if (*(s16 *)((u8 *)arg0 + 0x14) >= 0x80) {
        *(s16 *)((u8 *)arg0 + 0x14) = 0x80;
    }
    *(s16 *)((u8 *)arg0 + 0x12) = (s16)(*(s16 *)((u8 *)arg0 + 0x12) + 1);
    if (*(s16 *)((u8 *)arg0 + 0x12) >= 0x100) {
        *(s16 *)((u8 *)arg0 + 0x12) = (s16)(*(s16 *)((u8 *)arg0 + 0x12) - 0x100);
    }
    if ((*(s16 *)((u8 *)arg0 + 0xE) >= 0x12D) || (*(s16 *)((u8 *)arg0 + 0xE) < 0)) {
        func_1516972C();
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D275C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFB70/func_151D275C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FFB70/func_151D2830.s")
