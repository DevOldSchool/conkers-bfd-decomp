#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_124920.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_dense_pointer_families_continued.md
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
f32 func_15144B68(f32);                     /* extern */
extern f32 D_800A1BD8;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F7E20 CURRENT (764) */
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
    *(f32 *)((u8 *)temp_v0 + 0x1C) = func_15144B68(*(f32 *)((u8 *)temp_v0 + 0x1C) + (*(f32 *)((u8 *)temp_v0 + 0x20) * D_800BE9A4));
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
void func_151541B8(void *, f32, f32, f32, f32, u8, s32);

void func_150F7F8C(void *arg0, u8 arg1, s32 arg2) {
    f32 temp_fa0;
    f32 sp28;

    sp28 = func_150ADA68();
    temp_fa0 = func_150ADA68() * 70.0f;
    func_151541B8(arg0, sp28 * 3.0f + 9.0f, 0.511905f,
                  temp_fa0 + 70.0f, 0.0f, arg1, arg2);
    func_151D3F14(arg0, arg1, arg2);
}
void *func_1513264C(void *, s32, s32, s32, s32, u8, s32);
void *func_10022EC0(void *, const void *, u32);
extern f32 D_800A1BDC;
extern u32 D_800A5480[3];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F802C CURRENT (1325) */
void func_150F802C(f32 *arg0, s16 arg1, u8 arg2, s32 arg3) {
    typedef struct { u32 words[3]; } Copy3;
    u8 packet[0x90];
    void *result;

    *(void **)(packet + 0x7C) = arg0;
    *(f32 *)(packet + 0x80) = arg0[0];
    *(f32 *)(packet + 0x84) = arg0[1];
    *(f32 *)(packet + 0x88) = arg0[2];
    *(f32 *)(packet + 0x8C) = 0.0f;
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
    *(Copy3 *)(packet + 0x40) = *(Copy3 *)D_800A5480;
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
    result = func_1513264C(packet, 3, 0xFF, 0, 0xB4, arg2, arg3);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x170, packet + 0x7C, 0x14);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F802C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_124920/func_150F802C.s")
typedef struct GameF81BCVector { f32 x, y, z; } GameF81BCVector;
typedef struct GameF81BCPacket {
    u8 kind, field1;
    u16 mode;
    s16 lifetime;
    u8 pad6[2];
    s32 field8, fieldC;
    u8 r, g, b, a;
    f32 field14, field18;
    GameF81BCVector position, velocity;
    f32 scaleX, scaleY, scaleZ;
    u32 flags;
    u8 alpha, field45, field46, field47;
    s32 field48;
    u8 field4C, pad4D[3];
    s32 field50, field54;
} GameF81BCPacket;
typedef struct GameF81BCMotion {
    GameF81BCVector first, second;
    f32 phase, rate, amplitude, offset, scale;
} GameF81BCMotion;

s32 func_15145128(f32 *, f32 *, f32 *, f32 *);
s32 func_15146078(void *, void *, void *);
void *func_1513D2F0(s32, s32, u8, u8, u8, u8, u8, s32, s32, s32, u8, s32);
extern f32 D_800A1BE0, D_800A1BE4, D_800A1BE8, D_800A1BEC;
extern f32 D_800A1BF0, D_800A1BF4;
extern u8 D_800A4AA0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F81BC CURRENT (5790) */
s32 func_150F81BC(void *arg0) {
    GameF81BCVector delta;
    f32 length;
    f32 inverseLength;
    GameF81BCVector normal;
    f32 stepZ;
    f32 stepY;
    GameF81BCPacket packet;
    GameF81BCMotion motion;
    f32 interval;
    f32 temp_fs2;
    f32 temp_fs4;
    f32 var_fs0;
    void *temp_v0_2;
    void *temp_s0;

    {
        f32 *temp_v0;

        temp_v0 = *(f32 * *)((u8 *)(arg0) + 0x170);
        *(f32 *)((u8 *)(arg0) + 0x38) = (f32) *(f32 *)((u8 *)(temp_v0) + 0);
        *(f32 *)((u8 *)(arg0) + 0x3C) = (f32) *(f32 *)((u8 *)(temp_v0) + 4);
        *(f32 *)((u8 *)(arg0) + 0x40) = (f32) *(f32 *)((u8 *)(temp_v0) + 8);
        *(f32 *)((u8 *)(arg0) + 0x20) = (f32) *(f32 *)((u8 *)(temp_v0) + 0xC);
        *(f32 *)((u8 *)(arg0) + 0x24) = (f32) *(f32 *)((u8 *)(temp_v0) + 0x10);
        *(f32 *)((u8 *)(arg0) + 0x28) = (f32) *(f32 *)((u8 *)(temp_v0) + 0x14);
    }
    delta.x = *(f32 *)((u8 *)(arg0) + 0x38) - *(f32 *)((u8 *)(arg0) + 0x174);
    delta.y = *(f32 *)((u8 *)(arg0) + 0x3C) - *(f32 *)((u8 *)(arg0) + 0x178);
    delta.z = *(f32 *)((u8 *)(arg0) + 0x40) - *(f32 *)((u8 *)(arg0) + 0x17C);
    *(f32 *)((u8 *)(arg0) + 0x180) = (f32) (*(f32 *)((u8 *)(arg0) + 0x180) + D_800BE9A4);
    if (func_15145128(&delta.x, &normal.x, &length, &inverseLength) != 0) {
        temp_s0 = (u8 *) arg0 + 0x170;
        stepY = normal.y * 20.0f;
        stepZ = normal.z * 20.0f;
        var_fs0 = length * D_800A1BE0;
        if (var_fs0 > 1.0f) {
            interval = *(f32 *)((u8 *)(temp_s0) + 0x10) / var_fs0;
            func_15146078(&delta.x, &motion.first, &motion.second);
            packet.kind = 0x7A;
            packet.field1 = 0;
            packet.mode = 0x4404;
            packet.lifetime = 0xA;
            packet.field8 = 0;
            packet.fieldC = 0;
            packet.r = 0xFF;
            packet.g = 0xFF;
            packet.b = 0xFF;
            packet.a = 0xFF;
            motion.amplitude = D_800A1BE4;
            motion.offset = D_800A1BE8;
            packet.field18 = 0.0f;
            packet.field14 = 0.0f;
            motion.scale = D_800A1BEC;
            packet.velocity = *(GameF81BCVector *)D_800A5480;
            temp_fs4 = D_800A1BF0;
            packet.scaleX = 1.0f;
            packet.scaleY = 1.0f;
            packet.scaleZ = 1.0f;
            packet.flags = 0xCC0008;
            packet.field45 = 0xFF;
            packet.field46 = 0;
            packet.field47 = 6;
            packet.field48 = 0;
            packet.field4C = 0xFF;
            packet.field50 = 0;
            temp_fs2 = D_800A1BF4;
            do {
                motion.rate = temp_fs2;
                motion.phase = 27.0f - *(f32 *)((u8 *)(temp_s0) + 0x10);
                packet.position = *(GameF81BCVector *)((u8 *)temp_s0 + 4);
                packet.alpha = (s8) (u32) (motion.phase * temp_fs4);
                temp_v0_2 = func_1513D2F0((s32)&packet, (s32)D_800A4AA0, 0x24, 0, 0, 0x21, 0, 0, 0, 0x2C, (s32) *(u8 *)((u8 *)(arg0) + 0xC), (s32) *(u8 *)((u8 *)(arg0) + 1));
                if (temp_v0_2 != 0) {
                    func_10022EC0((u8 *)temp_v0_2 + 0x110, &motion, 0x2CU);
                }
                var_fs0 -= 1.0f;
                *(f32 *)((u8 *)(temp_s0) + 4) = (f32) (*(f32 *)((u8 *)(temp_s0) + 4) + (normal.x * 20.0f));
                *(f32 *)((u8 *)(temp_s0) + 8) = (f32) (*(f32 *)((u8 *)(temp_s0) + 8) + stepY);
                *(f32 *)((u8 *)(temp_s0) + 0xC) = (f32) (*(f32 *)((u8 *)(temp_s0) + 0xC) + stepZ);
                *(f32 *)((u8 *)(temp_s0) + 0x10) = (f32) (*(f32 *)((u8 *)(temp_s0) + 0x10) - interval);
            } while (var_fs0 > 1.0f);
        }
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F81BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_124920/func_150F81BC.s")
