#include "types.h"
#ifndef F3DEX_GBI_2
#define F3DEX_GBI_2
#endif
#include <PR/mbi.h>
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1FC830.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_dense_pointer_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151CF380
 * - func_151CFA4C
 * - func_151D014C
 * - func_151D09A8
 * - func_151D10E4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1FC830RibbonOffset {
    f32 x;
    f32 z;
} Game1FC830RibbonOffset;

typedef struct Game1FC830RibbonPoint {
    Vec3f position;
    u8 padC[8];
    f32 width;
    Game1FC830RibbonOffset offset;
    f32 directionX;
    f32 directionZ;
} Game1FC830RibbonPoint;

typedef struct Game1FC830RibbonTarget {
    u8 pad0[0x1D4];
    s32 active;
} Game1FC830RibbonTarget;

void func_151D5D60(void *, s16, s32, void **, u8 *);
Gfx *func_15142C10(Gfx *, s32, s32, s32, s32, u8 *);
Gfx *func_15142B7C(Gfx *, s32, s32);
Gfx *func_1513F4E4(Gfx *, u8, u8 *);
Gfx *func_15142FBC(Gfx *, s32, s32, u8 *);
extern s32 D_800A4AC8[][2];
extern s32 D_800D2C9C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CF380 */
Gfx *func_151CF380(u8 *arg0, Gfx *arg1, s16 arg2) {
    Game1FC830RibbonTarget **state;
    Vec3f next;
    Vec3f first;
    s32 index;
    s32 previous;
    Game1FC830RibbonPoint *points;
    u8 flag;
    f32 firstX;
    f32 firstZ;
    f32 nextX;
    f32 nextZ;
    f32 firstWidth;
    f32 nextWidth;
    Game1FC830RibbonOffset nextOffset;
    Game1FC830RibbonOffset firstOffset;
    Vtx_t *vtx;

    if (*(s8 *)(arg0 + 0x2C) < 2) {
        return arg1;
    }
    state = *(Game1FC830RibbonTarget ***)(arg0 + 0x98);
    points = *(Game1FC830RibbonPoint **)(arg0 + 0x94);
    if (*state != NULL && (*state)->active == 0) {
        return arg1;
    }
    func_151D5D60(arg0 + 0x84, arg2, (arg0[0x25] * 2 + 10) * sizeof(Vtx_t), (void **)&vtx, NULL);
    flag = 1;
    arg1 = func_15142C10(arg1, 0xED, 0xD2, 0x85, 0xC8, &flag);
    arg1 = func_15142B7C(arg1, 0x200005, 0x1F0600);
    arg1 = func_1513F4E4(arg1, 0x54, &flag);
    arg1 = func_15142FBC(arg1, D_800D2C9C | 0x80000 | 0x2000 | 0xC00 | 0x80 | 0x20, D_800A4AC8[1][0] | D_800A4AC8[1][1], &flag);
    previous = *(s8 *)(arg0 + 0x2E) - 1;
    if (previous < 0) {
        previous = arg0[0x25] - 1;
    }
    index = previous - 1;
    if (index < 0) {
        index = arg0[0x25] - 1;
    }
    first = points[previous].position;
    firstWidth = points[previous].width;
    firstX = firstWidth * points[previous].directionX;
    firstZ = firstWidth * points[previous].directionZ;
    firstOffset = points[previous].offset;
    next = points[index].position;
    nextWidth = points[index].width;
    nextX = nextWidth * points[index].directionX;
    nextZ = nextWidth * points[index].directionZ;
    nextOffset = points[index].offset;
    vtx->ob[0] = first.x + firstOffset.x + firstX;
    vtx->ob[1] = first.y;
    vtx->ob[2] = first.z + firstOffset.z + firstZ;
    vtx->flag = 0;
    vtx++;
    vtx->ob[0] = first.x - firstOffset.x + firstX;
    vtx->ob[1] = first.y;
    vtx->ob[2] = first.z - firstOffset.z + firstZ;
    vtx->flag = 0;
    vtx++;
    do {
        vtx->ob[0] = next.x + nextOffset.x + nextX;
        vtx->ob[1] = next.y;
        vtx->ob[2] = next.z + nextOffset.z + nextZ;
        vtx->flag = 0;
        vtx++;
        vtx->ob[0] = next.x - nextOffset.x + nextX;
        vtx->ob[1] = next.y;
        vtx->ob[2] = next.z - nextOffset.z + nextZ;
        vtx->flag = 0;
        vtx++;
        gSPVertex(arg1++, vtx - 4, 4, 0);
        gSP2Triangles(arg1++, 0, 1, 2, 0, 1, 3, 2, 0);
        previous = index;
        index--;
        if (index < 0) {
            index = arg0[0x25] - 1;
        }
        if (previous != *(s8 *)(arg0 + 0x2D)) {
            first = points[previous].position;
            next = points[index].position;
            nextWidth = points[index].width;
            nextX = nextWidth * points[index].directionX;
            nextZ = nextWidth * points[index].directionZ;
            nextOffset = points[index].offset;
            firstOffset = points[previous].offset;
        }
    } while (previous != *(s8 *)(arg0 + 0x2D));
    return arg1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CF380 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151CF380.s")
void func_15169850(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_151CF844(void *arg0, s32 arg1, u8 arg2) {
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x98);
    if (*(s32 *)temp_v0 != 0) {
        func_15169850(arg1, (s32) arg2, (s32) temp_v0, (s32) temp_v0 + 4, (s32) arg0);
    }
}

f32 func_150ADA68(void);
f32 func_15047D60(f32);
f32 func_15047C00(f32);
s32 func_15046C80(Vec3f *, u16, f32, Game71820Hit *);
f32 func_15144AA8(s32);
s32 func_15144B34(s32);
void *func_10022EC0(void *, const void *, u32);
extern f32 D_800AB020;
extern f32 D_800AB024;
extern Game71820Hit D_800D9860;

void func_151CF898(void *arg0, f32 arg1, f32 arg2) {
    void *entity;
    Vec3f position;
    f32 *camera;
    f32 yaw;
    f32 angle;
    f32 distance;
    struct {
        Vec3f position;
        f32 extra;
    } effect;
    void *result;

    entity = *(void **)((u8 *)arg0 + 0x318);
    if (entity != 0 && func_150ADA68() < D_800AB020) {
        camera = (f32 *)func_15144B34(*(u8 *)((u8 *)entity + 0x23D));
        yaw = func_15144AA8(*(u8 *)((u8 *)entity + 0x23D));
        angle = ((func_150ADA68() * 80.0f) + (yaw - 40.0f)) * D_800AB024;
        distance = func_150ADA68() * 2000.0f;
        position.x = camera[0] - (func_15047D60(angle) * distance);
        position.y = arg1;
        position.z = camera[2] - (func_15047C00(angle) * distance);
        if (func_15046C80(&position, 0, arg2, &D_800D9860) != 0) {
            position.y = D_800D9860.height;
            effect.position = position;
            effect.extra = 0.0f;
            result = func_15149130((s16)((func_150ADA20() % 131U) + 0x33), -1, 0x20, -1, 1, 0, 0x10, 0xFF, 1);
            if (result != 0) {
                func_10022EC0((u8 *)result + 0x28, &effect, 0x10);
            }
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151CFA4C.s")

void func_151D0024(void *arg0) {
    struct {
        void *sp18;
        u8 sp1C;
    } sp;

    sp.sp18 = arg0;
    sp.sp1C = *(u8 *)((u8 *)arg0 + 0x3B);
    func_151494E0(&sp, 0x18);
}
void *func_10022EC0(void *, const void *, u32);

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
    packet.value = (*(f32 *)((u8 *)arg0 + 0x150) +
                    *(f32 *)((u8 *)arg0 + 0x14C)) * 0.5f;
    packet.type = (u8)arg1;
    packet.random = (func_150ADA20() % 56U) + 0xC8;
    packet.field_6 = *(u16 *)((u8 *)arg0 + 0x84);
    result = func_15149130(0x12C, -1, 0x61, 4, 0, 0x31, 0x10, arg2, arg3);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x28, &packet, 0x10);
    }
}
void func_151D0128(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = *(u8 **)(arg0 + 0x28);
    if (*(u16 *)(temp_v0 + 0x84) != *(u16 *)(arg0 + 0x2E)) {
        *(s16 *)(arg0 + 0xE) = -1;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151D014C.s")
/* Call context: func_1516972C: unique active declaration in the allowed source */

void func_151D08F0(void *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0;
    s32 temp_v1;

    temp_v0 = (u8 *)arg0 + 0x28;
    if ((arg2 == 0) || (arg2 == 0x18)) {
        temp_v1 = *(s32 *)arg1;
        if ((temp_v1 == *(s32 *)temp_v0) ||
            (*(u8 *)(temp_v0 + 4) == *(u8 *)(arg1 + 4))) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)temp_v0) {
            *(s32 *)temp_v0 = *(s32 *)(arg1 + 4);
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 9);
            return;
        }
        if (*(s32 *)(arg1 + 4) == *(s32 *)temp_v0) {
            *(s32 *)temp_v0 = *(s32 *)arg1;
            *(u8 *)(temp_v0 + 4) = *(u8 *)(arg1 + 8);
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151D09A8.s")
void func_151D0ED8(void *arg0) {
    void **field_A8 = (void **)((u8 *)arg0 + 0xA8);

    if (*field_A8 != 0) {
        func_1516972C((void *)*field_A8);
    }
}

void func_151D0F08(void *arg0) {
    func_151D0ED8(*(void **)&arg0);
    func_1513173C(arg0);
}
void func_151D0F34(void *arg0) {
    func_151D0ED8(arg0);
    func_1513175C(arg0);
}

typedef s32 (*Game1FC830PositionCallback)(void *, Vec3i *);
extern Game1FC830PositionCallback D_8008FC30[];
extern Vec3i D_800A5480;

typedef struct Game1FC830ParticlePacket {
    void *object;
    u8 object_type;
    u8 pad5[3];
    s32 field_08;
    Vec3i position;
    Vec3i callback_position;
    Vec3i default_position;
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
s32 func_151D10E4(s32 arg0, s32 arg1, u8 arg2);

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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D10E4 CURRENT (845) */
s32 func_151D10E4(s32 arg0, s32 arg1, u8 arg2) {
    s32 temp_v0;

    temp_v0 = *(s32 *)((u8 *)arg0 + 0x1D4);
    if (temp_v0 == 0) {
        return 0;
    }
    func_15143134((f32 *)((u8 *)D_800AAF9C + (arg2 * 0xC)), (f32 *)arg1, temp_v0);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D10E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FC830/func_151D10E4.s")
s32 func_1510F8CC(s32);
void func_151D13E0();
void func_151D1448(u8 *);

void func_151D1138(void *arg0) {
    Game1FC830ParticlePacket *packet;
    void *actor;
    u8 failed;
    s32 mode;

    packet = (Game1FC830ParticlePacket *)((u8 *)arg0 + 0x28);
    actor = packet->object;
    failed = 0;
    if (*(s32 *)actor == 0 || packet->object_type != *((u8 *)actor + 0x3B)) {
        *(s16 *)((u8 *)arg0 + 0xE) = -1;
        return;
    }
    packet->position = packet->callback_position;
    if (D_8008FC30[packet->type](actor, &packet->callback_position) == 0) {
        failed = 1;
        packet->callback_position = packet->position;
    }
    *(f32 *)&packet->default_position.x = *(f32 *)&packet->callback_position.x - *(f32 *)&packet->position.x;
    *(f32 *)&packet->default_position.y = *(f32 *)&packet->callback_position.y - *(f32 *)&packet->position.y;
    *(f32 *)&packet->default_position.z = *(f32 *)&packet->callback_position.z - *(f32 *)&packet->position.z;
    packet->field_30 = func_15143E64(&packet->default_position);
    mode = func_1510F8CC(*(s32 *)((u8 *)actor + 0x184));
    if (packet->field_30 > 300.0f || packet->field_30 <= 0.0f ||
        *(f32 *)((u8 *)actor + 0x28) != 0.0f || *((u8 *)actor + 0xAD) != 0 ||
        mode == 5 || mode == 6 || mode == 9 || mode == 13 || mode == 14) {
        failed = 1;
    }
    if (failed != 0) {
        func_151D13E0(arg0);
        return;
    }
    if (packet->field_08 == 0) {
        func_151D1448(arg0);
    }
}

void func_151D1328(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, (s32) arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}
void func_151D13E0();

void func_151D1368() {
    func_151D13E0();
}

void func_151D1388(void *arg0) {
    func_151D1368(arg0);
    func_1514933C(arg0);
}

void func_151D13B4(void *arg0) {
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

void func_151D13E0(Game1FC830ActorContext *arg0) {
    Game1FC830ActorState *temp_v1;
    Game1FC830ActorLink *temp_v0;
    s32 temp_t3;

    temp_v0 = &arg0->link;
    if (temp_v0->actor != 0) {
        temp_t3 = 0x28;
        temp_v1 = temp_v0->actor->state;
        temp_v0->actor->mode = 0;
        temp_v0->actor->flags &= 0xFFFD;
        temp_v0->actor->flags |= 8;
        temp_v0->actor->flags |= 1;
        temp_v0->actor->timer = temp_t3;
        temp_v1->active = 0;
        temp_v0->actor = 0;
    }
}
extern s32 D_80082FA0;
void *func_15147A80(void *, void *, s32, s32, s32, s32, s32, s32, s32, u8, s32);

void func_151D1448(u8 *arg0) {
    u8 *link;
    struct {
        Vec3i position;
        s16 type;
        s16 subtype;
        s32 mode;
        u8 flag;
        u8 value;
        u8 pad_16[2];
        s32 reserved;
        u8 *object;
        f32 zero;
        u8 color;
        u8 pad_25[3];
        f32 range;
        f32 width;
        f32 height;
        f32 extent;
        f32 source_value;
    } packet;
    u8 *state;
    u8 *result;

    link = arg0 + 0x28;
    state = *(u8 **)link;
    packet.object = arg0;
    packet.color = 0xFF;
    packet.zero = 0.0f;
    if (state[4] == 0x25) {
        packet.range = 800.0f;
        packet.width = 36.0f;
        packet.height = 50.0f;
        packet.extent = 200.0f;
    } else {
        if (D_80082FA0 > 0) {
            packet.range = 260.0f;
        } else {
            packet.range = 500.0f;
        }
        packet.width = 40.0f;
        packet.height = 40.0f;
        packet.extent = 180.0f;
    }
    packet.source_value = *(f32 *)(*(u8 **)link + 0x14C);
    packet.value = 0x19;
    packet.position = *(Vec3i *)(link + 0x18);
    packet.type = 0x12C;
    packet.subtype = 0x36;
    packet.mode = 0x13;
    packet.flag = 6;
    packet.reserved = 0;
    result = func_15147A80(&packet, (void *)0x20, 0x28, 0, 0x11, 0x12, 0, 0, 0, arg0[0xC], arg0[1]);
    if (result != 0) {
        func_10022EC0(*(void **)(result + 0x98), &packet.object, 0x20);
        *(u8 **)(link + 8) = result;
    }
}
