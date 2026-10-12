#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_F15D0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_owner_chain_resource_emitters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C4120
 * - func_150C44A4
 * - func_150C4B60
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150C4AD8(void *arg0);

void *func_10022EC0(void *, const void *, u32);
u32 func_150ADA20(void);
f32 func_150ADA68(void);

typedef struct { f32 x, y, z; } GameF15D0Vec3;
typedef struct { s32 values[4]; } GameF15D0Choices;
extern GameF15D0Choices D_800A0340;
extern GameF15D0Vec3 D_800A5480;
extern f32 D_800A03AC, D_800A03B0, D_800A03B4;

typedef struct {
    u8 *owner;
    u8 ownerId, pad05[3];
    f32 field08;
    void *child;
    f32 field10;
    s16 kind;
    u8 flags, pad17;
    s32 field18;
} GameF15D0State;

typedef struct {
    s32 flags, field04;
    s16 kind, life;
    s32 field0C, field10;
    u8 colors[10];
    s16 field1E, field20, field22;
    f32 size, width, height;
    GameF15D0Vec3 position, direction, velocity;
    f32 field54;
    s32 flags58, field5C;
    u8 mode60, mode61, mode62;
    s8 mode63, mode64;
    u8 mode65, mode66, pad67;
    s16 field68;
    u8 pad6A[2];
    f32 field6C;
} GameF15D0Packet;

typedef struct {
    u8 phaseX, phaseY;
    s8 rateX, rateY;
    f32 size, field08, field0C;
} GameF15D0Extra;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C4120 CURRENT (816) */
void func_150C4120(u8 *arg0, s16 arg1, u8 arg2, s32 arg3) {
    GameF15D0State state;
    u8 *result;
    GameF15D0State *parentData;
    GameF15D0Packet packet;
    GameF15D0Extra extra;
    GameF15D0Choices choices;

    state.owner = arg0;
    state.ownerId = arg0[0x3B];
    state.field08 = 0.0f;
    state.child = 0;
    state.field10 = 0.0f;
    state.kind = -1;
    state.flags = 0;
    state.field18 = 0;
    if (arg0[4] == 0x34) {
        state.kind = 0x54;
        state.flags = 1;
    }
    result = func_15149130(arg1 == -1 ? 0x12C : arg1, -1, 0x53, -1,
        arg1 == -1 ? 0 : 1, 0x40, 0x1C, arg2, arg3);
    if (result != NULL) {
        parentData = (GameF15D0State *)(result + 0x28);
        func_10022EC0(parentData, &state, 0x1C);
        choices = D_800A0340;
        extra.phaseX = func_150ADA20();
        extra.phaseY = func_150ADA20();
        packet.height = 700.0f;
        packet.width = 700.0f;
        extra.size = 700.0f;
        extra.rateX = (func_150ADA20() % 6U) + 5;
        extra.rateY = (func_150ADA20() % 6U) + 5;
        extra.field08 = ((func_150ADA68() * 0.25f) + D_800A03AC) * extra.size;
        extra.field0C = ((func_150ADA68() * 0.25f) + D_800A03B0) * extra.size;
        packet.colors[9] = *(choices.values + (func_150ADA20() & 3));
        packet.kind = 0x2203;
        packet.flags = 0x200005;
        packet.field04 = 0;
        packet.field0C = 0;
        packet.field10 = 0;
        packet.colors[0] = 0;
        packet.colors[1] = 0;
        packet.colors[2] = 0;
        packet.colors[3] = 0xFF;
        packet.colors[4] = 0;
        packet.colors[5] = 0;
        packet.colors[6] = 0;
        packet.colors[7] = 0xFF;
        packet.colors[8] = 0xFF;
        packet.position = D_800A5480;
        packet.direction = D_800A5480;
        packet.velocity = D_800A5480;
        packet.field22 = 1;
        packet.field54 = 0.0f;
        packet.size = 1.0f;
        packet.flags58 = ((func_150ADA20() & 1) ? 0x40 : 0) |
            ((func_150ADA20() & 1) ? 0x80 : 0) | 0xC000;
        packet.life = 0x12C;
        packet.field1E = 1;
        packet.field20 = 0xFF;
        packet.mode60 = 6;
        packet.mode61 = 8;
        packet.mode64 = -1;
        packet.mode62 = 0x26;
        packet.mode63 = -1;
        packet.mode65 = 0;
        packet.field5C = 0;
        packet.mode66 = 0xFF;
        packet.field68 = 0;
        packet.field6C = D_800A03B4;
        result = func_15130280(&packet, 1U, NULL, 0x10, (u8) (s32) arg2, arg3);
        parentData->child = result;
        if (result != NULL) {
            func_10022EC0((u8 *) result + 0xA8, &extra, 0x10U);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C4120 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F15D0/func_150C4120.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F15D0/func_150C44A4.s")
void func_150C4AD8(void *arg0) {
    void **field_34 = (void **)((u8 *)arg0 + 0x34);

    if (*field_34 != 0) {
        func_1516972C((void *)*field_34);
    }
}
void func_150C4B08(void *arg0) {
    func_150C4AD8(arg0);
    func_1514933C(arg0);
}
void func_150C4B34(void *arg0) {
    func_150C4AD8(arg0);
    func_15149368(arg0);
}
/* Call context: func_15149514: unique active project prototype */
void func_15149514(s32, u8, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C4B60 CURRENT (415) */
void func_150C4B60(u8 *volatile arg0, volatile s32 arg1, volatile u8 arg2) {
    u8 *temp_a2;
    u8 *owner;
    s32 selector;

    selector = arg2;
    temp_a2 = arg0;
    if (selector == 0x55) {
        temp_a2 += 0x28;
        temp_a2[0x16] &= 0xFFFD;
        return;
    }
    owner = arg0;
    if (selector == 0x56) {
        temp_a2 = arg0 + 0x28;
        temp_a2[0x16] |= 2;
        return;
    }
    temp_a2 = owner + 0x28;
    func_15149514(arg1, arg2, (s32)temp_a2, (s32)(temp_a2 + 4), (s32)owner);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C4B60 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F15D0/func_150C4B60.s")
