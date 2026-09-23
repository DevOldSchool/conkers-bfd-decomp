#include "types.h"

/*
 * Reviewed source unit: src/game/game_1F4350.c
 * Boundary evidence: docs/evidence/game_raw_model_anchor_owner_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151C6EA0
 * - func_151C7038
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_1513264C(void *, s32, s32, s32, s32, u8, s32);
void *func_10022EC0(void *, const void *, u32);
extern s32 D_800A5480[3];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C6EA0 CURRENT (7002) */
void func_151C6EA0(u8 *arg0, u8 arg1, s32 arg2) {
    u8 packet[0x80];
    void *result;

    packet[0] = 0;
    *(f32 *)(packet + 4) = 1.0f;
    *(f32 *)(packet + 8) = 1.0f;
    *(f32 *)(packet + 0xC) = 1.0f;
    *(f32 *)(packet + 0x10) = 1.0f;
    *(s32 *)(packet + 0x14) = D_800A5480[0];
    *(s32 *)(packet + 0x18) = D_800A5480[1];
    *(s32 *)(packet + 0x1C) = D_800A5480[2];
    *(f32 *)(packet + 0x20) = 1.0f;
    *(f32 *)(packet + 0x24) = 1.0f;
    *(f32 *)(packet + 0x28) = 1.0f;
    *(s32 *)(packet + 0x2C) = D_800A5480[0];
    *(s32 *)(packet + 0x30) = D_800A5480[1];
    *(s32 *)(packet + 0x34) = D_800A5480[2];
    *(s32 *)(packet + 0x38) = D_800A5480[0];
    *(s32 *)(packet + 0x3C) = D_800A5480[1];
    *(s32 *)(packet + 0x40) = D_800A5480[2];
    *(s32 *)(packet + 0x44) = D_800A5480[0];
    *(s32 *)(packet + 0x48) = D_800A5480[1];
    *(s32 *)(packet + 0x4C) = D_800A5480[2];
    *(f32 *)(packet + 0x50) = 0.0f;
    *(s32 *)(packet + 0x54) = 0x11900;
    *(s16 *)(packet + 0x58) = 0x12C;
    *(s16 *)(packet + 0x5A) = 0xF;
    packet[0x5C] = 0;
    *(s32 *)(packet + 0x60) = 0;
    packet[0x64] = 0x64;
    packet[0x65] = 0x17;
    packet[0x66] = 0;
    packet[0x67] = 0;
    packet[0x68] = 0;
    packet[0x69] = 0;
    packet[0x6A] = 0;
    packet[0x6B] = 0;
    packet[0x6C] = 5;
    packet[0x6D] = -1;
    packet[0x6E] = 1;
    *(void **)(packet + 0x70) = arg0;
    packet[0x74] = arg0[0x3B];
    *(s16 *)(packet + 0x76) = 1;
    *(s16 *)(packet + 0x78) = 0xFF;
    *(s32 *)(packet + 0x7C) = 0;
    result = func_1513264C(packet + 4, 3, 0xFF, 0, 1, arg1, arg2);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x170, packet, 1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C6EA0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1F4350/func_151C6EA0.s")
s32 func_15142A5C(void *, void *, void *);          /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C7038 CURRENT (993) */
s32 func_151C7038(void *arg0) {
    void *sp1C;
    void *temp_a2;

    temp_a2 = *(void **)((u8 *)arg0 + 0x7C);
    if (*(u16 *)((u8 *)temp_a2 + 0x84) != 0xE9) {
        return 0;
    }
    sp1C = temp_a2;
    if (func_15142A5C(temp_a2, arg0, temp_a2) != 0) {
        *(s32 *)((u8 *)arg0 + 0x60) = (s32) (*(s32 *)((u8 *)arg0 + 0x60) | 0x20000);
    } else {
        *(s32 *)((u8 *)arg0 + 0x60) = (s32) (*(s32 *)((u8 *)arg0 + 0x60) & 0xFFFDFFFF);
    }
    {
        f32 var_fv0 = *(f32 *)((u8 *)temp_a2 + 0x4C) * 35.0f;
    if (var_fv0 > 255.0f) {
        var_fv0 = 255.0f;
    } else if (var_fv0 < 0.0f) {
        var_fv0 = 0.0f;
    }
    *(s8 *)((u8 *)arg0 + 0x70) = (s8) (u32) var_fv0;
    return 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C7038 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1F4350/func_151C7038.s")
