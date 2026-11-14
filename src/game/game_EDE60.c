#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_EDE60.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_owner_chain_resource_emitters.md
 */

void func_150C0A48(u8 *arg0);

extern void func_15169850(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_150C09B0(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, (s32) arg2, arg0 + 0x20, arg0 + 0x24, arg0);
}
void func_150C09F0(void *arg0) {
    func_150C0A48(arg0);
    func_15169804(arg0);
}
void func_150C0A1C(void *arg0) {
    func_150C0A48(arg0);
    func_15169824(arg0);
}
typedef struct {
    void *resource;
    s16 next_index;
    u8 pad6[2];
} GameEDE60ResourceEntry;

typedef struct {
    u8 pad0[0x40];
    GameEDE60ResourceEntry *entries;
    s16 first_index;
    s16 last_index;
} GameEDE60ResourceList;

void func_150C0A48(u8 *arg0) {
    GameEDE60ResourceList *list;
    GameEDE60ResourceEntry *entries;
    s32 index;
    s32 offset;

    list = (GameEDE60ResourceList *)arg0;
    index = list->first_index;
    if (index != -1) {
        entries = list->entries;
        do {
            offset = index * sizeof(GameEDE60ResourceEntry);
            func_1516972C(((GameEDE60ResourceEntry *)((u8 *)entries + offset))->resource);
            entries = list->entries;
            index = ((GameEDE60ResourceEntry *)((u8 *)entries + offset))->next_index;
        } while (index != -1);
    }
}
/* SDK memcpy alias and the matched allocator declaration. */
void *func_10022EC0(void *, const void *, u32);

void *func_150C0AC0(u8 *arg0, u8 arg1, s32 arg2) {
    u8 *allocated;
    s32 size;
    s16 index;

    size = (*(s16 *)(arg0 + 0x14) * 8) + 0x48;
    if (!(arg0[0x18] & 2)) {
        if (*(s32 **)(arg0 + 8) == 0) {
            return 0;
        }
        if (**(s32 **)(arg0 + 8) == 0) {
            return 0;
        }
    }
    allocated = func_15167A68(0x25, arg2, size, 1, arg1, 1);
    if (allocated == 0) {
        return 0;
    }
    func_10022EC0(allocated + 0x18, arg0, 0x1C);
    *(u8 **)(allocated + 0x40) = allocated + 0x48;
    if (arg0[0x18] & 2) {
        *(f32 *)(allocated + 0x34) = **(f32 **)(allocated + 0x18);
        *(f32 *)(allocated + 0x38) = *(f32 *)(*(u8 **)(allocated + 0x18) + 8);
    } else {
        *(f32 *)(allocated + 0x34) = *(f32 *)(*(u8 **)(allocated + 0x20) + 0x14);
        *(f32 *)(allocated + 0x38) = *(f32 *)(*(u8 **)(allocated + 0x20) + 0x1C);
    }
    *(f32 *)(allocated + 0x3C) = 0.0f;
    *(s16 *)(allocated + 0x44) = -1;
    *(s16 *)(allocated + 0x46) = 0;
    for (index = 0; index < *(s16 *)(arg0 + 0x14) - 1; index++) {
        *(s16 *)(*(u8 **)(allocated + 0x40) + (index * 8) + 4) = index + 1;
    }
    *(s16 *)(*(u8 **)(allocated + 0x40) + (*(s16 *)(arg0 + 0x14) * 8) - 4) = -1;
    *(s32 *)(allocated + 0x10) = 1;
    *(s32 *)(allocated + 0x14) = 0;
    return allocated;
}
typedef struct GameEDE60Vec {
    f32 x;
    f32 y;
    f32 z;
} GameEDE60Vec;

typedef struct GameEDE60Packet {
    u32 field00, field04;
    s16 field08, field0A;
    u32 field0C, field10;
    u8 field14, field15, field16, field17;
    u8 field18, field19, field1A, field1B, field1C, field1D;
    s16 field1E, field20, field22;
    f32 field24, scaleX, scaleY;
    GameEDE60Vec position;
    f32 field3C, field40, field44, field48, field4C, field50, speed;
    u32 flags;
    u8 pad5C[4];
    s8 field60, field61, field62, field63, field64, field65;
    u8 pad66[0xA];
} GameEDE60Packet;

typedef struct GameEDE60Emitter {
    u8 pad0;
    u8 field01;
    u8 pad2[0xA];
    u8 field0C;
    u8 padD[0xB];
    GameEDE60Vec *source;
    u8 pad1C[4];
    u8 *target;
    u8 field24;
    u8 pad25[3];
    f32 rate;
    u8 pad2C[2];
    s16 timer;
    u8 flags;
    u8 pad31[3];
    f32 lastX;
    f32 lastZ;
    f32 counter;
    GameEDE60ResourceEntry *entries;
    s16 first_index;
    s16 last_index;
} GameEDE60Emitter;

extern f32 D_800A01C0;
extern f32 D_800BE9A4;
extern s32 D_800BE9E4;
f32 func_150ADA68(void);

void func_150C0C38(GameEDE60Emitter *arg0) {
    GameEDE60Emitter *self;
    u8 kill;
    GameEDE60Vec position;
    s32 i;
    GameEDE60Packet packet;
    void *owner;
    f32 sinv;
    f32 cosv;
    f32 radius;

    self = arg0;
    kill = 0;
    if (!(arg0->flags & 2)) {
        if (*(s32 *)arg0->target == 0) kill = 1;
        if (arg0->field24 != arg0->target[0x3B]) kill = 1;
        position.x = *(f32 *)(arg0->target + 0x14);
        position.y = *(f32 *)(arg0->target + 0x180);
        position.z = *(f32 *)(arg0->target + 0x1C);
    } else {
        func_10022EC0(&position, arg0->source, 0xC);
        position.y -= 65.0f;
    }
    if (kill == 0) {
        u8 enabled;
        u8 random;
        u8 flip;
        i = arg0->first_index;
        enabled = 1;
        if (i != -1) {
            do {
                *(GameEDE60Vec *)((u8 *)arg0->entries[i].resource + 0x40) = position;
                i = arg0->entries[i].next_index;
            } while (i != -1);
        }
        if (arg0->flags & 4) {
            if (*(u16 *)(arg0->target + 0x84) != 0x1D && *(u16 *)(arg0->target + 0x84) != 0x1E) enabled = 0;
        }
        if (*(f32 *)(arg0->target + 0x3C) < 3.0f) enabled = 0;
        if ((position.x != arg0->lastX || position.z != arg0->lastZ) && enabled) {
            arg0->counter += arg0->rate * D_800BE9A4;
            if (arg0->counter > 1.0f) {
                s32 index;
                packet.field1D = 0x6C;
                packet.field08 = 0x5103;
                packet.field00 = 0x200005;
                packet.field04 = 0x1F0600;
                packet.field0C = 0;
                packet.field10 = 0;
                packet.field17 = 0xFF;
                packet.field1C = 0xFF;
                packet.field48 = 0.0f;
                packet.field4C = 0.0f;
                packet.field50 = 0.0f;
                packet.speed = 0.0f;
                packet.field1E = 0x1E;
                packet.field20 = 8;
                packet.flags = 0x80DE01;
                packet.field60 = 8;
                packet.field61 = 6;
                packet.field62 = -1;
                packet.field63 = 0;
                packet.field64 = -1;
                packet.field65 = 0;
                owner = arg0;
                while (arg0->counter > 1.0f && self->last_index != -1) {
                    index = arg0->last_index;
                    random = func_150ADA20() & 0xFF;
                    sinv = func_151423D8(random - 0x40);
                    cosv = func_151423D8(random);
                    radius = func_150ADA68() * 33.0f + 40.0f;
                    packet.field18 = 0x52;
                    packet.field19 = 0x6B;
                    packet.field1A = 0x97;
                    packet.field14 = 0x87;
                    packet.field15 = 0x6B;
                    packet.field16 = 0x97;
                    packet.field1B = func_150ADA20() % 121U + 0x50;
                    packet.scaleX = packet.scaleY = func_150ADA68() * 17.0f + 67.0f;
                    packet.position = position;
                    packet.field3C = radius * sinv;
                    packet.field40 = 0.0f;
                    packet.field44 = radius * cosv;
                    packet.flags &= ~0xC0;
                    flip = func_150ADA20() & 1 ? 0x80 : 0;
                    packet.flags |= (func_150ADA20() & 1 ? 0x40 : 0) | flip;
                    packet.field0A = packet.field22 = func_150ADA20() % 22U + 0x46;
                    packet.field24 = D_800A01C0;
                    arg0->entries[index].resource = func_15130280(&packet, 1, NULL, 4, arg0->field0C, arg0->field01);
                    if (arg0->entries[index].resource != NULL) {
                        func_10022EC0((u8 *)arg0->entries[index].resource + 0xA8, &owner, 4);
                        arg0->last_index = arg0->entries[index].next_index;
                        arg0->entries[index].next_index = arg0->first_index;
                        arg0->first_index = index;
                    }
                    arg0->counter -= 1.0f;
                }
                while (arg0->counter > 1.0f) arg0->counter -= 1.0f;
            }
        }
        arg0->lastX = position.x;
        arg0->lastZ = position.z;
    }
    if (arg0->flags & 1) {
        arg0->timer -= D_800BE9E4;
        if (arg0->timer < 0) kill = 1;
    }
    if (kill) func_1516972C(arg0);
}
void func_150C1198(u8 *arg0) {
    GameEDE60ResourceList *list;
    s16 index;
    s16 previous;
    s32 found;

    list = *(GameEDE60ResourceList **) (arg0 + 0xA8);
    found = 0;
    previous = -1;
    index = list->first_index;
    if (index != -1) {
        do {
            if (arg0 == list->entries[index].resource) {
                found = 1;
            } else {
                previous = index;
                index = list->entries[index].next_index;
            }
        } while ((index != -1) && (found == 0));
    }
    if (found != 0) {
        if (index == list->first_index) {
            list->first_index = list->entries[index].next_index;
        } else {
            list->entries[previous].next_index = list->entries[index].next_index;
        }
        list->entries[index].next_index = list->last_index;
        list->last_index = index;
    }
}
