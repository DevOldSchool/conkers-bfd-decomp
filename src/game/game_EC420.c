#include "types.h"

/*
 * Reviewed source unit: src/game/game_EC420.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150BF0F4
 * - func_150BF21C
 * - func_150BF760
 * - func_150BFA7C
 * - func_150BFFE0
 * - func_150C01DC
 * - func_150C0648
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150BEF70(s32 arg0) {

}
/* Call context: func_1516D99C: matched US definition in src/game/game_19A8B0.c */
void func_1516D99C(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, u8, s32);

void func_150BEF7C(s32 arg0) {
    s32 var_s0;
    s32 var_s1;

    var_s0 = 0x17C;
    var_s1 = 0;
    do {
        func_1516D99C(
            0x1FDB, 0x25, (s16)var_s0, 0xD,
            0, 0x50, 0x8F, 0,
            0, 0, 0, 0,
            8, 0xC8, 0xA, 0,
            0, 0, 0, 0,
            0x28, 0x28, 4, 0,
            0, 0, 0, 0x555,
            0x555, 0x555, 0x555, arg0 & 0xFFFF,
            0x32, 0, 0xFF, 0x14,
            0xFA0, 0x7D0, 1, 6,
            0, 1, 0, 0,
            0, 0, 3, 0xFFU,
            0);
        var_s1 += 1;
        var_s0 = -var_s0;
    } while (var_s1 != 2);
}
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150BF0F4 CURRENT (1515) */
s32 func_150BF0F4(void *arg0) {
    s16 temp_v1_2;
    s32 var_v1;
    u8 temp_v1;
    u8 var_v0;

    var_v0 = *(u8 *)((u8 *)arg0 + 0x1F);
    temp_v1 = *(u8 *)((u8 *)arg0 + 0x26);
    if (*(u8 *)((u8 *)arg0 + 0x24) != 0) {
        if (var_v0 != temp_v1) {
            var_v0 += D_800BE9E4 * *(u8 *)((u8 *)arg0 + 0x27);
            if ((s32) temp_v1 < (s32) var_v0) {
                var_v0 = temp_v1;
            }
            *(u8 *)((u8 *)arg0 + 0x1F) = var_v0;
        }
    } else if (var_v0 != 0) {
        var_v0 -= D_800BE9E4 * *(u8 *)((u8 *)arg0 + 0x2F);
        if ((s32) var_v0 < 0) {
            var_v0 = 0;
        }
        *(u8 *)((u8 *)arg0 + 0x1F) = var_v0;
    }
    if ((*(u8 *)((u8 *)arg0 + 0x24) == 0) && (var_v0 == 0)) {
        return 1;
    }
    *(s16 *)((u8 *)arg0 + 0x14) = (s16) (*(s16 *)((u8 *)arg0 + 0x14) + (*(s8 *)((u8 *)arg0 + 0x2D) * D_800BE9E4));
    temp_v1_2 = *(s16 *)((u8 *)arg0 + 0x14);
    *(s16 *)((u8 *)arg0 + 0x16) = (s16) (*(s16 *)((u8 *)arg0 + 0x16) + (*(s8 *)((u8 *)arg0 + 0x2E) * D_800BE9E4));
    if ((temp_v1_2 <= 0) || (temp_v1_2 <= 0)) {
        *(s16 *)((u8 *)arg0 + 0x16) = 0;
        *(s16 *)((u8 *)arg0 + 0x14) = (s16) *(s16 *)((u8 *)arg0 + 0x16);
        return 1;
    }
    var_v1 = *(u8 *)((u8 *)arg0 + 0x2C) + D_800BE9E4;
    if (var_v1 >= 0x80) {
        var_v1 = 0x7F;
    }
    *(u8 *)((u8 *)arg0 + 0x2C) = (u8) var_v1;
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150BF0F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EC420/func_150BF0F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EC420/func_150BF21C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EC420/func_150BF760.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EC420/func_150BFA7C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EC420/func_150BFFE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EC420/func_150C01DC.s")
typedef struct GameEC420Vec3 {
    s32 x;
    s32 y;
    s32 z;
} GameEC420Vec3;

typedef struct GameEC420Head {
    s32 value;
} GameEC420Head;

typedef struct GameEC420Packet {
    f32 base;
    GameEC420Head head;
    s32 arg2;
    s16 config[4];
    s32 count;
    s32 mode;
    GameEC420Vec3 position;
    f32 value4;
    f32 value7;
    f32 value2C;
    f32 value30;
    s16 value50;
    s16 value3C;
    f32 value38;
    f32 value3CFloat;
    f32 value40;
    s32 arg1;
    f32 value48;
    f32 value4C;
    f32 value50Float;
    f32 value10;
    s32 *arg2Pointer;
    s32 *headPointer;
    s32 one;
    f32 value78;
    s8 enabled;
    s8 value14;
    u8 pad6A[2];
    s32 four;
    f32 *basePointer;
} GameEC420Packet;

void func_15150400(s32 *, s16 *, u8, s32);
extern GameEC420Head D_800A0108;
extern f32 D_800A0170;
extern f32 D_800A0174;
extern f32 D_800A0178;
extern f32 D_800A017C;
extern f32 D_800A0180;
extern f32 D_800A0184;
extern f32 D_800A0188;
extern f32 D_800A018C;
extern f32 D_800A0190;

void func_150C04C0(void *arg0, s32 arg1, s32 arg2, u8 arg3, u8 arg4, s32 arg5) {
    GameEC420Packet packet;
    s8 enabled;

    packet.head = D_800A0108;
    packet.arg2 = arg2;
    packet.count = 9;
    packet.mode = 4;
    packet.base = D_800A0170;
    packet.position = *(GameEC420Vec3 *)arg0;
    packet.value4 = 4.0f;
    packet.value7 = 7.0f;
    packet.value2C = D_800A0174;
    packet.value30 = D_800A0178;
    packet.value38 = D_800A017C;
    packet.value3CFloat = D_800A0180;
    packet.value50 = 0x50;
    packet.value3C = 0x3C;
    packet.arg1 = arg1;
    packet.arg2Pointer = &packet.arg2;
    packet.headPointer = &packet.head.value;
    packet.one = 1;
    packet.value40 = D_800A0184;
    packet.value48 = D_800A0188;
    packet.value4C = D_800A018C;
    packet.value50Float = D_800A0190;
    packet.value10 = 10.0f;
    packet.value78 = 78.0f;
    if (arg3 != 0) {
        enabled = 1;
    } else {
        enabled = 0;
    }
    packet.enabled = enabled;
    packet.value14 = 0xE;
    packet.four = 4;
    packet.basePointer = &packet.base;
    packet.config[0] = 0;
    packet.config[1] = 0xFF;
    packet.config[2] = -0x32;
    packet.config[3] = 0x23;
    func_15150400(&packet.count, packet.config, arg4, arg5);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_EC420/func_150C0648.s")
