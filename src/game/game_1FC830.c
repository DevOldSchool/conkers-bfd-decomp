#include "types.h"

/*
 * Reviewed source unit: src/game/game_1FC830.c
 * Boundary evidence: docs/evidence/game_raw_dense_pointer_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151CF380
 * - func_151CF898
 * - func_151CFA4C
 * - func_151D0058
 * - func_151D014C
 * - func_151D08F0
 * - func_151D09A8
 * - func_151D10E4
 * - func_151D1138
 * - func_151D1388
 * - func_151D13E0
 * - func_151D1448
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151CF380.s")
void func_15169850(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_151CF844(void *arg0, s32 arg1, u8 arg2) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    if (*(s32 *)temp_v0 != 0) {
        func_15169850(arg1, (s32) arg2, (s32) temp_v0, (s32) temp_v0 + 4, (s32) arg0);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151CF898.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151CFA4C.s")
void func_151494E0(s32 *arg0, s32 arg1, s32 arg2);

void func_151D0024(void *arg0) {
    struct {
        void *sp18;
        volatile u8 sp1C;
    } sp;

    sp.sp18 = arg0;
    sp.sp1C = *(u8 *)((u8 *)arg0 + 0x3B);
    func_151494E0((s32 *)&sp, 0x18, (s32)arg0);
}
void *func_10022EC0(void *, const void *, u32);
u32 func_150ADA20(void);
void *func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D0058 CURRENT (120) */
void func_151D0058(void *arg0, u8 arg1, u8 arg2, s32 arg3) {
    struct {
        void *object;
        u8 object_type;
        u8 pad_5;
        u16 field_6;
        f32 value;
        u8 random;
        u8 type;
        u8 pad_E[2];
        u32 pad_10;
    } packet;
    void *result;

    packet.object = arg0;
    packet.object_type = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.type = (u8)arg1;
    packet.value = (*(f32 *)((u8 *)arg0 + 0x150) +
                    *(f32 *)((u8 *)arg0 + 0x14C)) * 0.5f;
    packet.random = (func_150ADA20() % 56U) + 0xC8;
    packet.field_6 = *(u16 *)((u8 *)arg0 + 0x84);
    result = func_15149130(0x12C, -1, 0x61, 4, 0, 0x31, 0x10, arg2, arg3);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x28, &packet, 0x10);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D0058 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151D0058.s")
void func_151D0128(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x28);
    if (*(u16 *)(temp_v0 + 0x84) != *(u16 *)(arg0 + 0x2E)) {
        *(s16 *)(arg0 + 0xE) = -1;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151D014C.s")
/* Call context: func_1516972C: unique active declaration in the allowed source */
void func_1516972C(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D08F0 CURRENT (1602) */
void func_151D08F0(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 temp_a0;
    s32 temp_t6;
    s32 temp_v1;
    u8 *temp_v0;

    temp_t6 = arg2 & 0xFF;
    if ((temp_t6 == 0) || (temp_t6 == 0x18)) {
        if ((*(s32 *)((u8 *)arg1 + 0) == *(s32 *)((u8 *)arg0 + 0x28)) || (*(u8 *)((u8 *)(arg0 + 0x28) + 4) == (u8) *(s32 *)((u8 *)arg1 + 4))) {
            func_1516972C(arg0);
        }
    } else {
        temp_v0 = (void *)(arg0 + 0x28);
        if (temp_t6 == 0x2D) {
            temp_a0 = *(s32 *)((u8 *)arg0 + 0x28);
            temp_v1 = *(s32 *)((u8 *)arg1 + 0);
            if (temp_v1 == temp_a0) {
                *(s32 *)((u8 *)arg0 + 0x28) = (s32) *(s32 *)((u8 *)arg1 + 4);
                *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 9);
                return;
            }
            if (*(s32 *)((u8 *)arg1 + 4) == temp_a0) {
                *(s32 *)((u8 *)arg0 + 0x28) = temp_v1;
                *(u8 *)((u8 *)temp_v0 + 4) = (u8) *(u8 *)((u8 *)arg1 + 8);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D08F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151D08F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151D09A8.s")
void func_1516972C(void *arg0);
void func_151D0ED8(void *arg0) {
    volatile void **field_A8 = (volatile void **)((u8 *)arg0 + 0xA8);

    if (*field_A8 != 0) {
        func_1516972C((void *)*field_A8);
    }
}
void func_1513173C();
void func_1513175C();

void func_151D0F08(s32 arg0) {
    func_151D0ED8((void *)*(s32 *)&arg0);
    func_1513173C(arg0);
}
void func_151D0F34(s32 arg0) {
    func_151D0ED8((void *)arg0);
    func_1513175C(arg0);
}
typedef struct Game1FC830Vector {
    s32 x;
    s32 y;
    s32 z;
} Game1FC830Vector;

typedef s32 (*Game1FC830PositionCallback)(void *, Game1FC830Vector *);
extern Game1FC830PositionCallback D_8008FC30[];
extern Game1FC830Vector D_800A5480;

typedef struct Game1FC830ParticlePacket {
    void *object;
    u8 object_type;
    u8 pad5[3];
    s32 field_08;
    Game1FC830Vector position;
    Game1FC830Vector callback_position;
    Game1FC830Vector default_position;
    f32 field_30;
    u8 type;
    u8 pad35[3];
    u8 tail_pad[4];
} Game1FC830ParticlePacket;

void func_151D0F60(void *arg0, u8 arg1, u8 arg2, s32 arg3) {
    Game1FC830ParticlePacket packet;
    register void *result;

    packet.object = arg0;
    packet.object_type = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.field_08 = 0;
    if (D_8008FC30[arg1](arg0, &packet.callback_position) == 0) {
        packet.callback_position = D_800A5480;
    }
    packet.position = packet.callback_position;
    packet.default_position = D_800A5480;
    packet.field_30 = 0.0f;
    packet.type = arg1;
    result = func_15149130(0x12C, -1, 0x5F, -1, 0, 0x48, 0x38, arg2, arg3);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x28, &packet, 0x38);
    }
}
s32 func_151D1074(void *arg0, void *arg1) {
    *(f32 *)((u8 *)arg1 + 0) = (f32) *(f32 *)((u8 *)arg0 + 0x14);
    *(f32 *)((u8 *)arg1 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 0x180) + 8.0f);
    *(f32 *)((u8 *)arg1 + 8) = (f32) *(f32 *)((u8 *)arg0 + 0x1C);
    return 1;
}
s32 func_151D10E4(s32 arg0, s32 arg1, s32 arg2);

void func_151D10A4(s32 arg0, s32 arg1) {
    func_151D10E4(arg0, arg1, 0);
}
void func_151D10C4(s32 arg0, s32 arg1) {
    func_151D10E4(arg0, arg1, 1);
}
typedef struct {
    u8 pad_0[0x1D4];
    s32 field_1D4;
} Game1FC830State;

void func_15143134(f32 *, f32 *, s32);
extern f32 D_800AAF9C[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D10E4 CURRENT (1150) */
s32 func_151D10E4(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a3;
    s32 temp_v0;

    temp_a3 = arg2 & 0xFF;
    temp_v0 = *(s32 *)((u8 *)arg0 + 0x1D4);
    if (temp_v0 == 0) {
        return 0;
    }
    func_15143134((f32 *)((u8 *)D_800AAF9C + (temp_a3 * 0xC)), (f32 *)arg1, temp_v0);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D10E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151D10E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151D1138.s")
void func_151D1328(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, (s32) arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}
void func_151D13E0();

void func_151D1368() {
    func_151D13E0();
}
void func_1514933C(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D1388 CURRENT (200) */
void func_151D1388(s32 arg0) {
    func_151D1368();
    func_1514933C(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D1388 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151D1388.s")
void func_15149368(s32 arg0);

void func_151D13B4(s32 arg0) {
    func_151D1368(arg0);
    func_15149368(arg0);
}
typedef struct Game1FC830ActorState {
    s32 active;
} Game1FC830ActorState;

typedef struct Game1FC830Actor {
    u8 pad0[0x1C];
    s16 timer;
    u16 flags;
    u8 pad20[0x10];
    s8 mode;
    u8 pad31[0x67];
    Game1FC830ActorState * volatile state;
} Game1FC830Actor;

typedef struct Game1FC830ActorLink {
    u8 pad0[8];
    Game1FC830Actor *actor;
} Game1FC830ActorLink;

typedef struct Game1FC830ActorContext {
    u8 pad0[0x28];
    Game1FC830ActorLink link;
} Game1FC830ActorContext;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D13E0 CURRENT (70) */
void func_151D13E0(Game1FC830ActorContext *arg0) {
    Game1FC830ActorState *temp_v1;
    Game1FC830Actor *temp_a1;
    Game1FC830ActorLink *temp_v0;
    s32 temp_t3;

    temp_v0 = &arg0->link;
    if (temp_v0->actor != 0) {
        temp_a1 = temp_v0->actor;
        temp_t3 = 0x28;
        temp_v1 = temp_a1->state;
        temp_a1->mode = 0;
        temp_a1 = temp_v0->actor;
        temp_a1->flags &= 0xFFFD;
        temp_a1 = temp_v0->actor;
        temp_a1->flags |= 8;
        temp_a1 = temp_v0->actor;
        temp_a1->flags |= 1;
        temp_v0->actor->timer = temp_t3;
        temp_v1->active = 0;
        temp_v0->actor = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D13E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151D13E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151D1448.s")
