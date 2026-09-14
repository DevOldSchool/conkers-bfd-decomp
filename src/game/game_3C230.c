#include "types.h"

/*
 * Reviewed source unit: src/game/game_3C230.c
 * Boundary evidence: docs/evidence/game_compact_multi_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1500EE94
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15177410(s32, s32, s32, s32, s32, f32, s32, f32,
                   s32, s32, s32, s32, s32, s32, s32, s32);
void func_150124A0(void);

void func_1500ED80(void) {
    func_15177410(1, 0xD8, -0xDAC, 0, 0x4BB, 0.0f, 0x3A98, 30.0f,
                  0x4D, 0xF, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F);
    func_150124A0();
}

typedef struct {
    u8 pad0[0x3B];
    u8 type;
} Game3C230Actor;

typedef struct {
    Game3C230Actor *owner;
    u8 type;
    u8 pad5[3];
} Game3C230Packet;

typedef struct {
    void *owner;
    f32 value;
    u8 type;
    u8 pad9[3];
} Game3C230PacketWithValue;

void func_10022EC0(void *, void *, s32);
u8 *func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_1500EE18(Game3C230Actor *arg0, s32 arg1, s32 arg2) {
    Game3C230Packet packet;
    u8 *object;

    packet.owner = arg0;
    packet.type = arg0->type;
    object = func_15149130(0x12C, -1, 0x45, -1, 0, 0, 8, 0xFF, 1);
    if (object != 0) {
        func_10022EC0(object + 0x28, &packet, sizeof(packet));
    }
}

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1500EE94 CURRENT (400) */
void func_1500EE94(void *arg0) {
    Game3C230PacketWithValue packet;
    u8 *temp_v0;

    packet.owner = arg0;
    packet.value = 0.0f;
    packet.type = *(u8 *)((u8 *)arg0 + 0x14);
    temp_v0 = func_15149130(0x12C, -1, 0x46, -1, 0, 0x39, 0xC, 0xFF, 1);
    if (temp_v0 != 0) {
        func_10022EC0(temp_v0 + 0x28, &packet, 0xC);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1500EE94 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_3C230/func_1500EE94.s")
