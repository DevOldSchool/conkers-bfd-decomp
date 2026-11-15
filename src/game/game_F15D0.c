#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_F15D0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_owner_chain_resource_emitters.md
 */

void func_150C4AD8(void *arg0);

void *func_10022EC0(void *, const void *, u32);
f32 func_150ADA68(void);

typedef struct { s32 values[4]; } GameF15D0Choices;
extern GameF15D0Choices D_800A0340;
extern Vec3f D_800A5480;
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
    Vec3f position, direction, velocity;
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
        extra.phaseX = func_150ADA20() & 0xFF;
        extra.phaseY = func_150ADA20() & 0xFF;
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
            ((func_150ADA20() & 1) ? 0x80 : 0) | 0x4000 | 0x8000;
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
        parentData->child = func_15130280(&packet, 1U, NULL, 0x10, arg2, arg3);
        if (parentData->child != NULL) {
            func_10022EC0((u8 *)parentData->child + 0xA8, &extra, 0x10U);
        }
    }
}
s32 func_150A29C8(u32, s32);
void func_15143134(f32 *, f32 *, s32);
void func_15143794(s16, s16, f32, void *);
s32 func_1514654C(void *, void *, s32, void **, void **, s32);
s32 func_10010154(s32, void *, s32, s32, s32);
void *func_1503195C(void *, s32, s32);
void func_1504715C(void *, void *);
void func_151C36D8(Vec3f *, u8, s32);
void *func_151D9014(f32 *, f32 *, u8, f32, s16, u8, f32, u8, f32, f32, u8, void *, u8, u8, u8, s32);
extern Vec3f D_800A0350[];
extern u8 D_800A0374[];
extern Vec3f D_800A0378[];
extern u8 D_800A03A8[];
extern f32 D_800BE9A4;
extern s32 D_800BE9F0;
extern u8 D_800CC2D0[];

void func_150C44A4(u8 *arg0) {
    GameF15D0State *state;
    u8 *owner;
    Vec3f pos;
    Vec3f offset;
    f32 ratio;
    s32 index;
    f32 scale;
    u32 surface[9];
    void *offsetPtr;
    void *posPtr;
    void *bone;
    s32 enabled;
    Vec3f *wind;
    Vec3f vel;

    state = (GameF15D0State *)(arg0 + 0x28);
    owner = state->owner;
    if (*(s32 *)owner == 0 || state->ownerId != owner[0x3B]) {
        *(s16 *)(arg0 + 0xE) = -1;
        return;
    }
    if (*(s32 *)(owner + 0x1D4) == 0 || (state->flags & 2)) {
        if (state->child != NULL) {
            *((s8 *)state->child + 0x74) = 3;
        }
        return;
    }
    func_1504715C(surface, owner);
    if (state->field18 == 0) {
        state->field18 = func_10010154(0x96, owner, 0x36B0, 0x190, 0x4268);
    }
    if (state->flags & 1) {
        bone = func_1503195C(owner, state->kind, 0);
        if (bone == NULL) {
            return;
        }
        if (*(s32 *)(owner + 0x2EC) != 0) {
            ratio = *(f32 *)(owner + 0x2D8) * *(f32 *)(owner + 0x2DC);
        } else {
            ratio = 0.0f;
        }
        index = ratio * 4.0f;
        if (index >= 4) {
            index = 3;
        }
        scale = (ratio - index * 0.25f) * 4.0f;
        offset.x = D_800A0378[index].x * scale;
        offset.y = D_800A0378[index].y * scale;
        offset.z = D_800A0378[index].z * scale;
        offsetPtr = &offset;
        posPtr = &pos;
        if (func_1514654C(owner, bone, D_800A03A8[index], &offsetPtr, &posPtr, 1) == 0) {
            pos.x = *(f32 *)(owner + 0x14);
            pos.y = *(f32 *)(owner + 0x18) + 800.0f;
            pos.z = *(f32 *)(owner + 0x1C);
        }
    } else {
        if (*(s32 *)(owner + 0x2E8) != 0) {
            ratio = (f32)*(s32 *)(owner + 0x2E4) / (f32)*(s32 *)(owner + 0x2E8);
        } else {
            ratio = 1.0f;
        }
        index = ratio * 3.0f;
        if (index >= 3) {
            index = 2;
        }
        scale = (ratio - index * 0.33333334f) * 3.0f;
        offset.x = D_800A0350[index].x * scale;
        offset.y = D_800A0350[index].y * scale;
        offset.z = D_800A0350[index].z * scale;
        func_15143134(&offset.x, &pos.x, *(s32 *)(owner + 0x1D4) + (D_800A0374[index] << 6));
    }
    if (state->child != NULL) {
        *((s8 *)state->child + 0x74) = -1;
        *(Vec3f *)((u8 *)state->child + 0x40) = pos;
    }
    enabled = 1;
    if (D_800BE9F0 == 2 && func_150A29C8((owner - D_800CC2D0) / 812, 0x4065) == 0) {
        enabled = 0;
    }
    if (enabled) {
        state->field08 += (0.12900001f + func_150ADA68() * 0.117000006f) * D_800BE9A4;
        while (state->field08 > 1.0f) {
            func_151C36D8(&pos, arg0[0xC], arg0[1]);
            state->field08 -= 1.0f;
        }
    }
    state->field10 += (0.13000001f + func_150ADA68() * 0.2f) * D_800BE9A4;
    if (state->field10 > 1.0f) {
        if (func_1515C0F8((struct Game1890A0State *)owner, (u8 **)&wind) == 0) {
            wind = &D_800A5480;
        }
        do {
            func_15143794(func_150ADA20() & 0xFF, (func_150ADA20() % 25U) - 0x40, func_150ADA68() * 2.5970001f + 4.8700004f, &vel);
            vel.x -= wind->x * 0.6f;
            vel.z -= wind->z * 0.6f;
            func_151D9014(&pos.x, &vel.x, 0xC, func_150ADA68() * 0.25800002f + (-0.60800004f), (func_150ADA20() % 41U) + 0x3C, (func_150ADA20() % 56U) + 0xC8,
                          func_150ADA68() * 160.0f + 121.0f, func_150ADA68() < 0.70000005f, 1.0f, 1.0f, 0, surface, 1, 1, arg0[0xC], arg0[1]);
            state->field10 -= 1.0f;
        } while (state->field10 > 1.0f);
    }
}
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

void func_150C4B60(u8 *arg0, s32 arg1, u8 arg2) {
    u8 *state = arg0 + 0x28;

    if (arg2 == 0x55) {
        state[0x16] &= 0xFFFD;
        return;
    }
    if (arg2 == 0x56) {
        state[0x16] |= 2;
        return;
    }
    func_15149514(arg1, arg2, (s32)state, (s32)(state + 4), (s32)arg0);
}
