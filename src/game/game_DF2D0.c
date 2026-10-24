#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_DF2D0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_subranges.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B1F90
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_1509BE40();

void func_150B1E20(void *arg0) {
    void *state;

    if (func_1509BE40(1, 0x4054, 6, 0x9000) != 0) {
        *(s32 *)((u8 *)arg0 + 0x84) |= 0x10000;
    } else {
        *(s32 *)((u8 *)arg0 + 0x84) &= 0xFFFEFFFF;
    }
    if (func_1509BE40(1, 0x405C, 6, 0x9000) == 0 &&
        func_1509BE40(1, 0x405B, 6, 0x2000) != 0 &&
        *(s32 *)((u8 *)arg0 + 0x2C) != 0x40) {
        state = *(void **)((u8 *)arg0 + 0x3D0);
        *(f32 *)((u8 *)state + 0x17C) = *(f32 *)((u8 *)state + 0x180) + 10.0f;
    }
}
typedef struct GameDF2D0Packet {
    s32 field_0;
    s32 field_4;
    s32 field_8;
    f32 field_C;
} GameDF2D0Packet;

void *func_10022EC0(void *, const void *, u32);

void func_150B1EE0(void *arg0, GameDF2D0Packet *arg1, s32 arg2, s32 arg3) {
    typedef struct { s32 words[3]; } Copy3;
    GameDF2D0Packet packet;
    s16 temp_a0;
    u8 *temp_v0;

    *(Copy3 *)&packet = *(Copy3 *)arg1;
    packet.field_C = 0.0f;
    temp_a0 = (func_150ADA20() % 133U) + 0x45;
    temp_v0 = func_15149130(temp_a0, -1, 0x49, -1, 1, 0, 0x10,
        *(u8 *)((u8 *)arg0 + 0xC), *(u8 *)((u8 *)arg0 + 1));
    if (temp_v0 != 0) {
        func_10022EC0((u8 *)temp_v0 + 0x28, &packet, 0x10);
    }
}

typedef struct GameDF2D0Descriptor {
    s32 field00, field04;
    s16 field08, field0A;
    s32 field0C, field10;
    u8 field14, field15, field16, field17;
    u8 field18, field19, field1A, field1B, field1C, field1D;
    s16 field1E, field20, field22;
    f32 field24, scaleY, scaleX;
    Vec3i position;
    f32 x3C, y40, z44, x48, y4C, z50, field54;
    s32 flags, field5C;
    s8 field60, field61, field62, field63, field64, field65;
    u8 pad66[10];
} GameDF2D0Descriptor;

typedef struct GameDF2D0Extension {
    s8 field0, field1, field2, field3;
    f32 field4, field8, fieldC;
} GameDF2D0Extension;

f32 func_150ADA68(void);
extern f32 D_8009F8E0, D_8009F8E4, D_8009F8E8, D_8009F8EC;
extern f32 D_8009F8F0, D_8009F8F4, D_8009F8F8, D_8009F8FC;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B1F90 CURRENT (1136) */
void func_150B1F90(void *arg0) {
    s32 firstFlip, secondFlip;
    void *result;
    GameDF2D0Descriptor packet;
    GameDF2D0Extension extension;
    f32 speedRange, speedBase, scaleRange, scaleBase;
    GameDF2D0Packet *state;

    state = (GameDF2D0Packet *)((u8 *)arg0 + 0x28);
    state->field_C += (D_8009F8E0 + func_150ADA68() * D_8009F8E4) * D_800BE9A4;
    if (state->field_C > 1.0f) {
        packet.field1D = 0x6C;
        packet.field08 = 0x5103;
        packet.field00 = 0x200005;
        packet.field1E = 0x50;
        packet.field20 = 3;
        packet.flags = 0x90DE07;
        packet.field60 = 8;
        packet.field61 = 6;
        packet.field62 = 0x16;
        extension.field0 = 0;
        extension.field1 = 0;
        packet.field04 = 0;
        packet.field0C = 0;
        packet.field10 = 0;
        packet.field63 = -1;
        packet.field64 = -1;
        packet.field65 = 0;
        packet.field22 = 0x50;
        packet.field14 = 0x67;
        packet.field15 = 0x6C;
        packet.field16 = 0x6C;
        packet.field17 = 0xFF;
        packet.field18 = 0x16;
        packet.field19 = 0xB;
        packet.field1A = 0;
        packet.field1C = 0xFF;
        extension.fieldC = D_8009F8E8;
        packet.field24 = D_8009F8EC;
        packet.position = *(Vec3i *)state;
        scaleBase = D_8009F8F0;
        scaleRange = D_8009F8F4;
        speedBase = D_8009F8F8;
        speedRange = D_8009F8FC;
        packet.x3C = 0.0f;
        packet.y40 = 0.0f;
        packet.z44 = 0.0f;
        packet.x48 = 0.0f;
        packet.y4C = 0.0f;
        packet.z50 = 0.0f;
        do {
            extension.field2 = func_150ADA20() % 5U + 4;
            extension.field3 = func_150ADA20() % 5U + 4;
            extension.field4 = func_150ADA68() * 27.0f;
            extension.field8 = func_150ADA68() * 27.0f;
            packet.field54 = func_150ADA68() * speedRange + speedBase;
            packet.flags &= ~0xC0;
            firstFlip = (func_150ADA20() & 1) ? 0x80 : 0;
            if (func_150ADA20() & 1) secondFlip = 0x40;
            else secondFlip = 0;
            packet.flags = (secondFlip | firstFlip) | packet.flags;
            packet.field1B = func_150ADA20() % 101U + 0x64;
            packet.field0A = func_150ADA20() % 78U + 0x7E;
            packet.scaleY = packet.scaleX = func_150ADA68() * scaleRange + scaleBase;
            result = func_15130280(&packet, 1, NULL, 0x10, *((u8 *)arg0 + 0xC), *((u8 *)arg0 + 1));
            if (result != NULL) func_10022EC0((u8 *)result + 0xA8, &extension, 0x10);
            state->field_C -= 1.0f;
        } while (state->field_C > 1.0f);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B1F90 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DF2D0/func_150B1F90.s")

void func_150B2340(void *arg0) {
    s32 sp24;
    s32 sp20;
    s32 first;
    u8 *state;

    state = arg0;
    first = func_1509BE40(0, 0x2007, 0xB7);
    sp24 = func_1509BE40(0, first | 0x2000, 0xBC);
    sp20 = func_1509BE40(0, 0x2000, 0xBB);
    if (func_1509BE40(0, 0x5043, 0x1A) != 0) {
        if (func_1509BE40(0, 0x5045, 0x1A) != 0) {
            *(s32 *)(state + 0x84) |= 0x4000;
        }
        *(s32 *)(state + 0x84) |= 0x400000;
        *(f32 *)(state + 0x190) = 0.0f;
    } else if (func_1509BE40(1, 0x4030, 6, 0x2000) != 0) {
        *(f32 *)(state + 0x190) = 235.0f;
    } else {
        *(f32 *)(state + 0x348) = 114.0f;
        *(f32 *)(state + 0x34C) = 114.0f;
        *(f32 *)(state + 0x374) = 384.0f;
        *(f32 *)(state + 0x190) = 60.0f;
    }
    if ((sp24 != 0) && (sp20 != -1)) {
        *(s32 *)(state + 0x5F0) |= 0x100;
    } else {
        *(s32 *)(state + 0x5F0) &= ~0x100;
    }
}
