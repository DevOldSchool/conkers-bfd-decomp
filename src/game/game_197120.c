#include "types.h"

/*
 * Reviewed source unit: src/game/game_197120.c
 * Boundary evidence: docs/evidence/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15169C70
 * - func_1516A3F4
 * - func_1516A538
 * - func_1516A648
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_197120/func_15169C70.s")
typedef struct Game197120SpawnPacket {
    s32 resource;
    s16 field_4;
    s16 field_6;
    s16 field_8;
    s16 field_A;
    s16 field_C;
    s16 field_E;
    s16 field_10;
    s8 field_12;
    u8 pad_13;
    s8 field_14;
    u8 field_15;
} Game197120SpawnPacket;

void func_1510F800(s32);
s32 func_1510F8D8(s16, s16, s16, s32);
void func_15167AD8(void *, u8, s32);
extern s32 D_8008CADC;
extern f32 D_800A6CC8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516A3F4 CURRENT (2217) */
void func_1516A3F4(void *arg0) {
    Game197120SpawnPacket packet;
    s32 limit;
    s32 current;
    s32 shade;
    u8 color;

    current = *(s32 *)((u8 *)arg0 + 0x14);
    limit = *(s16 *)((u8 *)arg0 + 0x22) + *(s16 *)((u8 *)arg0 + 0x2A);
    if (current >= limit) {
        func_1510F800(0);
        current = func_1510F8D8(*(s16 *)((u8 *)arg0 + 0x20),
                                *(s16 *)((u8 *)arg0 + 0x22),
                                *(s16 *)((u8 *)arg0 + 0x24), 0);
        *(s32 *)((u8 *)arg0 + 0x14) = current;
    }
    if (current >= limit) {
        *(s16 *)((u8 *)arg0 + 0x38) = 0;
        if ((limit - current) < 0x32) {
            packet.field_4 = 0;
            packet.field_6 = 0x100;
            packet.resource = D_8008CADC;
            packet.field_8 = *(s16 *)((u8 *)arg0 + 0x20);
            packet.field_A = *(s32 *)((u8 *)arg0 + 0x14) + 0xA;
            packet.field_C = *(s16 *)((u8 *)arg0 + 0x24);
            color = *(u8 *)((u8 *)arg0 + 0x3B);
            packet.field_12 = 0;
            packet.field_14 = 3;
            shade = ((s32)(color << 12) / 5100) + 0xCC;
            packet.field_E = shade;
            packet.field_10 = shade;
            packet.field_15 = color;
            func_15167AD8(&packet, *(u8 *)((u8 *)arg0 + 0xC),
                           *(u8 *)((u8 *)arg0 + 1));
        }
    } else {
        *(s16 *)((u8 *)arg0 + 0x26) = (s32)((f32)*(s16 *)((u8 *)arg0 + 0x26) * D_800A6CC8);
        *(s16 *)((u8 *)arg0 + 0x28) = (s32)((f32)*(s16 *)((u8 *)arg0 + 0x28) * D_800A6CC8);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516A3F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_197120/func_1516A3F4.s")
u32 func_150ADA20(void *);
void func_15171D4C(f32, f32, f32, s32, s32, s32, f32, s32, s32,
                   s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516A538 CURRENT (50) */
void func_1516A538(u8 *arg0) {
    u32 sp48;
    s32 sp44;
    volatile s32 pad40;

    if (*(s16 *)(arg0 + 0x14) >= 0x300) {
        sp48 = func_150ADA20(arg0) % 3U;
        sp44 = arg0[0x25];
        func_15171D4C((f32)*(s16 *)(arg0 + 0x18),
                      (f32)(*(s16 *)(arg0 + 0x1A) - 0xA),
                      (f32)*(s16 *)(arg0 + 0x1C), 0x64, 0,
                      sp48 + 0x20,
                      (f32)(func_150ADA20(arg0) % 360U), 0,
                      ((sp44 * 0x19) / 0xFF) + 0x19, 0, 0x100, 0,
                      arg0[0xC], arg0[1]);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516A538 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_197120/func_1516A538.s")
void func_1516F94C(s32, s32);
s32 func_1510F8D8(s16, s16, s16, s32);
void func_1516F864(void *);
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516A648 CURRENT (30) */
s32 func_1516A648(u8 *arg0) {
    s32 value;
    s32 height;

    value = arg0[0x1F];
    if (arg0[0x24] != 0) {
        if (value != 0xFF) {
            value += D_800BE9E4 * 0x10;
            if (value >= 0x100) {
                value = 0xFF;
            }
            arg0[0x1F] = value;
        }
    } else if (value != 0) {
        value -= D_800BE9E4 * 4;
        if (value < 0) {
            value = 0;
        }
        arg0[0x1F] = value;
    }
    if ((arg0[0x24] == 0) && (value == 0)) {
        return 1;
    }
    *(s16 *)(arg0 + 0x18) -= 0x12C;
    func_1516F864(arg0);
    height = func_1510F8D8(*(s16 *)(arg0 + 0xE), *(s16 *)(arg0 + 0x10),
                           *(s16 *)(arg0 + 0x12), 0) + 0xA;
    arg0[0x2C] = height >> 8;
    arg0[0x2D] = height;
    if (*(s16 *)(arg0 + 0x10) < height) {
        *(s16 *)(arg0 + 0x10) = height;
        *(s16 *)(arg0 + 0x18) = (s32)((f32)*(s16 *)(arg0 + 0x18) * -0.5f);
        func_1516F94C((s32)arg0, 0xE6);
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516A648 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_197120/func_1516A648.s")
