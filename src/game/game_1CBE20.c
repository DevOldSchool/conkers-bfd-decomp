#include "types.h"

/*
 * Reviewed source unit: src/game/game_1CBE20.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1519E970
 * - func_1519EA78
 * - func_1519EB8C
 * - func_1519ED24
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_15167A68(s32, s32, s32, s32, u8, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519E970 CURRENT (275) */
void *func_1519E970(s16 arg0, s32 arg1, u8 arg2, s32 arg3, s32 arg4, u8 arg5, s32 arg6) {
    void *temp_v0;

    temp_v0 = func_15167A68(0x26, arg6, 0x2C, 1, arg5, 1);
    if (temp_v0 == 0) {
        return 0;
    }
    *(s32 *)((u8 *)temp_v0 + 0x18) = arg3;
    *(s32 *)((u8 *)temp_v0 + 0x1C) = arg4;
    *(s16 *)((u8 *)temp_v0 + 0x20) = arg0;
    *(u8 *)((u8 *)temp_v0 + 0x28) = arg2;
    *(s32 *)((u8 *)temp_v0 + 0x10) = 1;
    *(s32 *)((u8 *)temp_v0 + 0x14) = 0;
    *(s32 *)((u8 *)temp_v0 + 0x24) = arg1;
    return temp_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519E970 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CBE20/func_1519E970.s")
typedef struct Game1CBE20Owner {
    u8 pad0[0x30];
    s32 effect;
} Game1CBE20Owner;

typedef struct Game1CBE20Effect {
    u8 pad0[0x10];
    u32 flags;
    u8 pad14[0xC];
    s16 timer;
    u8 pad22[2];
    Game1CBE20Owner *owner;
    u8 field_28;
} Game1CBE20Effect;

extern s32 D_800BE9E4;
void func_1516972C(void *);

void func_1519EA04(Game1CBE20Effect *arg0) {
    Game1CBE20Owner *owner;
    s32 expired;

    if (arg0->flags & 1) {
        expired = 0;
        arg0->timer = (s16)(arg0->timer - D_800BE9E4);
        if (arg0->timer < 0) {
            expired = 1;
        }
        if (expired != 0) {
            if (arg0->field_28 == 0) {
                owner = arg0->owner;
                owner->effect = 0;
            }
            func_1516972C(arg0);
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CBE20/func_1519EA78.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CBE20/func_1519EB8C.s")
extern f32 D_800A8CD8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1519ED24 CURRENT (505) */
s32 func_1519ED24(void *arg0) {
    void *temp_v1;

    temp_v1 = *(void **)((u8 *)arg0 + 0x170);
    *(f32 *)((u8 *)arg0 + 0x18) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x18) * D_800A8CD8);
    *(f32 *)((u8 *)arg0 + 0x1C) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x1C) * D_800A8CD8);
    *(f32 *)((u8 *)arg0 + 0x20) = (f32) *(f32 *)((u8 *)temp_v1 + 0xC);
    *(f32 *)((u8 *)arg0 + 0x24) = (f32) *(f32 *)((u8 *)temp_v1 + 0x10);
    *(f32 *)((u8 *)arg0 + 0x28) = (f32) *(f32 *)((u8 *)temp_v1 + 0x14);
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) *(f32 *)((u8 *)temp_v1 + 0);
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) *(f32 *)((u8 *)temp_v1 + 4);
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) *(f32 *)((u8 *)temp_v1 + 8);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1519ED24 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1CBE20/func_1519ED24.s")
typedef struct Game1CBE20SpawnPacket {
    s8 field0;
    s8 field1;
    s16 field2;
    s16 field4;
    u8 pad6[2];
    s32 field8;
    s32 fieldC;
    u8 colour[4];
    f32 values[11];
    s32 field40;
    u8 field44;
    u8 field45;
    u8 field46;
    u8 field47;
    s32 field48;
    u8 field4C;
    u8 pad4D[3];
    s32 field50;
    s16 field54;
    s16 field56;
} Game1CBE20SpawnPacket;

void *func_10022EC0(void *, const void *, u32);
void *func_1513D2F0(s32, s32, u8, u8, u8, u8, u8, s32, s32, s32, u8, s32);
extern u8 D_800A4AA0;

void func_1519ED84(f32 *arg0, s32 arg1, s16 arg2, u8 arg3, s32 arg4) {
    Game1CBE20SpawnPacket packet;
    f32 *owner;
    void *result;

    owner = arg0;
    packet.field0 = arg1;
    packet.field1 = 0;
    packet.field2 = 0x3B03;
    packet.field4 = arg2;
    packet.field8 = 0;
    packet.fieldC = 0;
    packet.colour[0] = 0xFF;
    packet.colour[1] = 0xFF;
    packet.colour[2] = 0xFF;
    packet.colour[3] = 0xFF;
    packet.values[0] = arg0[6] * 10.0f;
    packet.values[1] = arg0[7] * 10.0f;
    packet.values[2] = arg0[0];
    packet.values[3] = arg0[1];
    packet.values[4] = arg0[2];
    packet.values[5] = arg0[3];
    packet.values[6] = arg0[4];
    packet.values[7] = arg0[5];
    packet.values[8] = 1.0f;
    packet.values[9] = 1.0f;
    packet.values[10] = 1.0f;
    packet.field40 = 0x045C0081;
    packet.field44 = 0xFF;
    packet.field45 = 0xFF;
    packet.field46 = 0;
    packet.field47 = 7;
    packet.field48 = 0;
    packet.field4C = 0xFF;
    packet.field50 = 0;
    packet.field54 = 1;
    packet.field56 = 0xFF;
    result = func_1513D2F0((s32)&packet, (s32)&D_800A4AA0, 0x27, 0, 0,
                          0x17, 0, 3, 0xFF, 4, arg3, arg4);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x110, &owner, 4);
    }
}
s32 func_1519EF04(void *arg0) {
    void *temp_v1;

    temp_v1 = *(void **)((u8 *)arg0 + 0x110);
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x18) * 10.0f);
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x1C) * 10.0f);
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) *(f32 *)((u8 *)temp_v1 + 0xC);
    *(f32 *)((u8 *)arg0 + 0x44) = (f32) *(f32 *)((u8 *)temp_v1 + 0x10);
    *(f32 *)((u8 *)arg0 + 0x48) = (f32) *(f32 *)((u8 *)temp_v1 + 0x14);
    *(f32 *)((u8 *)arg0 + 0x34) = (f32) *(f32 *)((u8 *)temp_v1 + 0);
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) *(f32 *)((u8 *)temp_v1 + 4);
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) *(f32 *)((u8 *)temp_v1 + 8);
    return 1;
}
