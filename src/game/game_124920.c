#include "types.h"

/*
 * Reviewed source unit: src/game/game_124920.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F7470
 * - func_150F78B4
 * - func_150F7E20
 * - func_150F802C
 * - func_150F81BC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_124920/func_150F7470.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_124920/func_150F78B4.s")
/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32, void *);                     /* extern */
extern f32 D_800A1BD8;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F7E20 CURRENT (784) */
s32 func_150F7E20(u8 *arg0) {
    void *sp1C;
    f32 temp_fv1;
    u8 *temp_v0;

    *(s8 *)((u8 *)arg0 + 0x5C) = (s8) (u32) (*(f32 *)((u8 *)arg0 + 0x128) * D_800A1BD8);
    temp_v0 = (void *)(arg0 + 0x110);
    temp_fv1 = (func_15047D60(*(f32 *)((u8 *)arg0 + 0x12C)) * *(f32 *)((u8 *)temp_v0 + 0x28)) + *(f32 *)((u8 *)temp_v0 + 0x24);
    *(f32 *)((u8 *)arg0 + 0x30) = temp_fv1;
    *(f32 *)((u8 *)arg0 + 0x2C) = temp_fv1;
    sp1C = temp_v0;
    *(f32 *)((u8 *)temp_v0 + 0x1C) = func_15144B68(*(f32 *)((u8 *)temp_v0 + 0x1C) + (*(f32 *)((u8 *)temp_v0 + 0x20) * D_800BE9A4), arg0);
    *(f32 *)((u8 *)temp_v0 + 0x18) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x18) - D_800BE9A4);
    {
        s32 var_v0 = 1;
    if (*(f32 *)((u8 *)temp_v0 + 0x18) < 0.0f) {
        var_v0 = 0;
    }
    return var_v0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F7E20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_124920/func_150F7E20.s")
s32 func_15140410(s32, s32, s32, s16);

void func_150F7F58(s32 arg0, s16 arg1) {
    func_15140410(arg0, arg0 + 0x110, arg0 + 0x11C, arg1);
}
f32 func_150ADA68(void);
void func_151541B8(s32, f32, s32, f32, f32, u8, s32);
void func_151D3F14(s32, u8, s32);

void func_150F7F8C(s32 arg0, u8 arg1, s32 arg2) {
    f32 temp_fa0;
    f32 sp28;

    sp28 = func_150ADA68();
    temp_fa0 = func_150ADA68() * 70.0f;
    func_151541B8(arg0, sp28 * 3.0f + 9.0f, 0x3F030C35,
                  temp_fa0 + 70.0f, 0.0f, arg1, arg2);
    func_151D3F14(arg0, arg1, arg2);
}
void *func_1513264C(void *, s32, s32, s32, s32, u8, s32);
void *func_10022EC0(void *, const void *, u32);
extern f32 D_800A1BDC;
extern u32 D_800A5480[3];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F802C CURRENT (5496) */
void func_150F802C(f32 *arg0, s16 arg1, u8 arg2, s32 arg3) {
    u8 packet[0x90];
    void *result;

    *(f32 *)(packet + 0x00) = 1.0f;
    *(f32 *)(packet + 0x04) = 1.0f;
    *(f32 *)(packet + 0x08) = D_800A1BDC;
    *(f32 *)(packet + 0x0C) = D_800A1BDC;
    *(f32 *)(packet + 0x10) = arg0[3];
    *(f32 *)(packet + 0x14) = arg0[4];
    *(f32 *)(packet + 0x18) = arg0[5];
    *(f32 *)(packet + 0x1C) = 1.0f;
    *(f32 *)(packet + 0x20) = 1.0f;
    *(f32 *)(packet + 0x24) = 1.0f;
    *(f32 *)(packet + 0x28) = arg0[0];
    *(f32 *)(packet + 0x2C) = arg0[1];
    *(f32 *)(packet + 0x30) = arg0[2];
    *(f32 *)(packet + 0x34) = 0.0f;
    *(f32 *)(packet + 0x38) = 0.0f;
    *(f32 *)(packet + 0x3C) = 0.0f;
    *(u32 *)(packet + 0x40) = D_800A5480[0];
    *(u32 *)(packet + 0x44) = D_800A5480[1];
    *(u32 *)(packet + 0x48) = D_800A5480[2];
    *(f32 *)(packet + 0x4C) = 0.0f;
    *(s32 *)(packet + 0x50) = 0x980;
    *(s16 *)(packet + 0x54) = arg1;
    *(s16 *)(packet + 0x56) = 0x2F;
    packet[0x58] = 0;
    *(s32 *)(packet + 0x5C) = 0;
    packet[0x60] = 0xFF;
    packet[0x61] = 0x14;
    packet[0x62] = 0;
    packet[0x63] = 0;
    packet[0x64] = 0;
    packet[0x65] = 0;
    packet[0x66] = 0;
    packet[0x67] = 0;
    packet[0x68] = 0;
    packet[0x6A] = 0;
    *(s32 *)(packet + 0x6C) = 0;
    packet[0x70] = 0;
    *(s16 *)(packet + 0x72) = 1;
    *(s16 *)(packet + 0x74) = 0xFF;
    *(s32 *)(packet + 0x78) = 0;
    *(void **)(packet + 0x7C) = arg0;
    *(f32 *)(packet + 0x80) = arg0[0];
    *(f32 *)(packet + 0x84) = arg0[1];
    *(f32 *)(packet + 0x88) = arg0[2];
    *(f32 *)(packet + 0x8C) = 0.0f;
    result = func_1513264C(packet, 3, 0xFF, 0, 0xB4, arg2, arg3);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x170, packet + 0x7C, 0x14);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F802C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_124920/func_150F802C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_124920/func_150F81BC.s")
