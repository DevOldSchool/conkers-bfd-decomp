#include "types.h"

/*
 * Reviewed source unit: src/game/game_1028F0.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D54C8
 * - func_150D596C
 * - func_150D5A6C
 * - func_150D6388
 * - func_150D6434
 * - func_150D64E8
 * - func_150D65F0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_10022EC0(void *, void *, s32);
typedef struct Game1028F0D5440Packet {
    void *owner;
    u8 type;
    u8 pad5[3];
    f32 value;
} Game1028F0D5440Packet;

s32 func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_150D5440(void *arg0, u8 arg1, s32 arg2) {
    Game1028F0D5440Packet packet;
    s32 temp_v0;

    packet.owner = arg0;
    packet.type = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.value = 0.0f;
    temp_v0 = func_15149130(0x12C, -1, 0x38, -1, 0, 0x28, 0xC, (s32)arg1, arg2);
    if (temp_v0 != 0) {
        func_10022EC0((void *)(temp_v0 + 0x28), &packet, 0xC);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1028F0/func_150D54C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1028F0/func_150D596C.s")
void func_150D5A2C(void) {
    func_1514933C();
}
void func_150D5A4C(void) {
    func_15149368();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1028F0/func_150D5A6C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1028F0/func_150D6388.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1028F0/func_150D6434.s")
extern s32 D_80082FA0;
extern s8 D_8008FD8C;
extern f32 D_800A0AB8;
extern f32 D_800A0ABC;
extern f32 D_800A0AC0;
extern f32 D_800A0AC4;
extern f32 D_800A0AC8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D64E8 CURRENT (790) */
void func_150D64E8(void *arg0, f32 *arg1) {
    *(s32 *)((u8 *)arg0 + 0) = 6;
    *(s32 *)((u8 *)arg0 + 4) = 3;
    *arg1 = D_800A0AB8;
    *(f32 *)((u8 *)arg0 + 0x14) = (f32) D_800A0ABC;
    *(s32 *)((u8 *)arg0 + 0x2C) = 4;
    *(s32 *)((u8 *)arg0 + 0x30) = 3;
    *(f32 *)((u8 *)arg0 + 0x18) = (f32) D_800A0AC0;
    *(f32 *)((u8 *)arg0 + 0x1C) = 150.0f;
    *(f32 *)((u8 *)arg0 + 0x20) = 105.0f;
    *(f32 *)((u8 *)arg0 + 0x24) = 396.0f;
    *(f32 *)((u8 *)arg0 + 0x28) = 612.0f;
    *(f32 *)((u8 *)arg0 + 0x34) = 25.0f;
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) D_800A0AC4;
    *(f32 *)((u8 *)arg0 + 0x3C) = -2.0f;
    *(s16 *)((u8 *)arg0 + 0x44) = 0x14;
    *(s16 *)((u8 *)arg0 + 0x46) = 0x1E;
    *(s16 *)((u8 *)arg0 + 0x48) = 0x64;
    *(s16 *)((u8 *)arg0 + 0x4A) = 0x64;
    *(s16 *)((u8 *)arg0 + 0x4C) = 0xC;
    *(s16 *)((u8 *)arg0 + 0x4E) = 0x14;
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) D_800A0AC8;
    if ((D_80082FA0 >= 2) || (D_8008FD8C >= 8)) {
        *(s8 *)((u8 *)arg0 + 0x50) = -1;
        return;
    }
    *(s8 *)((u8 *)arg0 + 0x50) = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D64E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1028F0/func_150D64E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1028F0/func_150D65F0.s")
u32 func_150ADA20(void);
void func_15182670(s32, s32, s32, s32, s32, s32, s32, s32);

void func_150D66A4(u8 arg0, u8 arg1, s32 arg2) {
    struct {
        u32 value;
        u32 padding;
    } sp28;

    sp28.value = func_150ADA20();
    func_15182670(0xFF, 0xFF, 0xFF, ((sp28.value % 56U) + 0xC8) & 0xFF, (func_150ADA20() % 6U) + 0x19, (s32) arg0, (s32) arg1, arg2);
}
