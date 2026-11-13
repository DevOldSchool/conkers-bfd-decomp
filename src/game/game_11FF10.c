#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_11FF10.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F2A60
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game11FF10Actor {
    u8 pad0[0x120];
    u8 disabled;
    u8 pad121[0x1C3];
    s32 scroll;
    u8 pad2E8[0x44];
} Game11FF10Actor;

void func_10010630(u16, void *, s32, s16, u16);
void func_15060F28(u8 *, s32);
void func_1507CD64(void *, s32);
void *func_15083E90(u8);
struct Blood36C3CActor;
void func_15136C3C(struct Blood36C3CActor *, u8, u8, u8, u8, u8, u8, s32);
void func_15145A50(u8 *);
extern void **D_800BE4F0;
extern u8 D_800CC2D0;
extern u8 D_800CC40C;
extern s8 D_800CC49A;
extern void *D_800CC5EC;
extern s32 D_800DBEF4;
extern s32 D_800DBF94;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F2A60 CURRENT (3125) */
void func_150F2A60(s32 arg0) {
    s32 negative;
    s32 resource;
    s32 i;
    s32 index;
    Game11FF10Actor *actor;

    if (D_800CC5EC != 0) {
        i = 0;
        if (((Game11FF10Actor *)D_800CC5EC)->disabled == 0) {
loop:
            {
                resource = func_151149AC((u8)(0xFA - i));
                i++;
                index = (resource - D_800DBEF4) / 160;
                if (*(s32 *)(D_800DBF94 + index * 4) & 1) {
                    if (D_800CC40C != 0) {
                        func_15060F28((u8 *)(D_800CC40C * 0x32C - 81200 + (u32)&D_800CC2D0), 0);
                    }
                    D_800CC49A = 0;
                    func_15136C3C(&D_800CC2D0, 0, 0, 1, 1, 0, 0xFF, 1);
                    func_10010630(0x627, &D_800CC2D0, 0x6D60, 0x1F4, 0x3E8);
                    func_15145A50(&D_800CC2D0);
                    func_1507CD64(&D_800CC2D0, 6);
                } else if (i < 2) {
                    goto loop;
                }
            }
            actor = func_15083E90(0xE);
            if (actor != 0) {
                i = actor->scroll;
            } else {
                i = 0;
            }
            func_15196318(D_800BE4F0[0], i, 0);
            negative = -i;
            func_15196318(D_800BE4F0[1], 0, negative);
            func_15196318(D_800BE4F0[2], i, 0);
            func_15196318(D_800BE4F0[3], negative, 0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F2A60 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_11FF10/func_150F2A60.s")
void *func_10022EC0(void *, const void *, u32);
typedef struct Game11FF10F2C8CPacket {
    void *owner;
    u8 type;
    s8 field5;
    u8 pad6[2];
    f32 value;
    s8 fieldC;
    u8 padD[3];
} Game11FF10F2C8CPacket;

void func_150F2C8C(void *arg0) {
    Game11FF10F2C8CPacket packet;
    u8 *temp_v0;

    packet.owner = arg0;
    packet.type = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.field5 = 0;
    packet.fieldC = 0;
    packet.value = 0.0f;
    temp_v0 = func_15149130(0x12C, -1, 0x5C, -1, 0, 0x44, 0x10, 0xFF, 1);
    if (temp_v0 != 0) {
        func_10022EC0((void *)(temp_v0 + 0x28), &packet, 0x10);
    }
}
typedef struct Game11FF10Spawn {
    u8 field0;
    u8 field1;
    s16 field2;
    s16 field4;
    s32 field8;
    s32 fieldC;
    u8 colors10[4];
    f32 field14;
    f32 field18;
    Vec3f position1C;
    Vec3f field28;
    f32 field34;
    f32 field38;
    f32 field3C;
    s32 field40;
    u8 field44;
    u8 field45;
    u8 field46;
    u8 field47;
    s32 field48;
    u8 field4C;
    s32 field50;
    s16 field54;
    s16 field56;
} Game11FF10Spawn;

typedef struct Game11FF10Target {
    s32 field0;
    u8 pad4[0x3B - 4];
    u8 field3B;
    u8 pad3C[0x1D4 - 0x3C];
    s32 field1D4;
    u8 pad1D8[0x222 - 0x1D8];
    u8 field222;
} Game11FF10Target;

typedef struct Game11FF10Packet {
    Game11FF10Target *owner;
    u8 type;
    f32 field8;
    f32 fieldC;
    f32 field10;
    f32 field14;
    f32 field18;
    Vec3f field1C;
    Vec3f field28;
} Game11FF10Packet;

typedef struct Game11FF10Emitter {
    Game11FF10Target *target;
    u8 type;
    u8 field5;
    u8 pad6[2];
    f32 timer;
    s8 count;
} Game11FF10Emitter;

typedef struct Game11FF10Owner {
    u8 pad0;
    u8 field1;
    u8 pad2[0xA];
    u8 fieldC;
    u8 padD;
    s16 fieldE;
    u8 pad10[0x28 - 0x10];
    Game11FF10Emitter emitter;
} Game11FF10Owner;

void *func_1513D2F0(s32, s32, u8, u8, u8, u8, u8, s32, s32, s32, u8, s32);
void func_15145EA4(f32 **, f32 **, s32, s32);
s32 func_15146078(void *, void *, void *);
f32 func_150ADA68(void);
extern u8 D_800C35EA;
extern f32 D_800A1950;
extern f32 D_800A195C;
extern Vec3f D_800A5480;
extern u8 D_800A4AA0;
extern f32 D_800BE9A4;

void func_150F2D14(Game11FF10Owner *arg0) {
    Game11FF10Emitter *emitter;
    Game11FF10Target *target;
    Game11FF10Spawn spawn;
    Game11FF10Packet packet;
    u8 *result;

    emitter = &arg0->emitter;
    if (D_800C35EA == 1) {
        return;
    }
    target = emitter->target;
    if (target->field0 == 0 || target->field3B != emitter->type) {
        arg0->fieldE = -1;
        return;
    }
    if (emitter->field5 != target->field222) {
        if (target->field222 != 0) {
            emitter->count = 3;
            emitter->timer = 0.0f;
        }
    }
    emitter->field5 = target->field222;
    if (target->field222) {
        func_1502EA98(&D_800CC2D0 + target->field222 * 0x32C, 0xFF, 0, 0, 0x50, 0, 0xF);
    }
    if (target->field1D4 != 0 && emitter->count > 0) {
        emitter->timer += 0.148f * D_800BE9A4;
        if (emitter->timer > 1.0f) {
            do {
                packet.owner = target;
                packet.type = target->field3B;
                packet.field8 = 0.0f;
                packet.fieldC = func_150ADA68() * 6.0f + 13.0f;
                packet.field10 = 58.14f;
                packet.field14 = func_150ADA68() * 40.0f + 60.0f;
                packet.field18 = packet.field14 / (packet.fieldC * packet.fieldC);
                {
                    f32 *srcs[2];
                    f32 *dsts[2];
                    Vec3f dir;

                    srcs[0] = &D_800A1950;
                    srcs[1] = &D_800A195C;
                    dsts[0] = &spawn.position1C.x;
                    dsts[1] = &dir.x;
                    func_15145EA4(srcs, dsts, target->field1D4 + 0x3C0, 2);
                    dir.x -= spawn.position1C.x;
                    dir.y -= spawn.position1C.y;
                    dir.z -= spawn.position1C.z;
                    if (func_15146078(&dir, &packet.field1C, &packet.field28) == 0) {
                        return;
                    }
                    spawn.field44 = packet.field14;
                    spawn.field0 = 0x79;
                    spawn.field1 = 0xC;
                    spawn.field2 = 0x4405;
                    spawn.field4 = 0x12C;
                    spawn.field8 = 0;
                    spawn.fieldC = 0;
                    spawn.colors10[0] = 0xD5;
                    spawn.colors10[1] = 0xDB;
                    spawn.colors10[2] = 0xFF;
                    spawn.colors10[3] = 0xFF;
                    spawn.field18 = 0.0f;
                    spawn.field14 = 0.0f;
                    spawn.field28 = D_800A5480;
                    spawn.field34 = 1.0f;
                    spawn.field38 = 1.0f;
                    spawn.field3C = 1.0f;
                    spawn.field40 = 0x4EC0000;
                    spawn.field45 = 0xFF;
                    spawn.field46 = 0;
                    spawn.field47 = 6;
                    spawn.field48 = 0;
                    spawn.field4C = 0xFF;
                    spawn.field50 = 0;
                    spawn.field54 = 1;
                    spawn.field56 = 0xFF;
                    result = func_1513D2F0((s32)&spawn, (s32)&D_800A4AA0, 0x26, 0, 0, 0x25, 0, 0, 0, 0x34,
                        arg0->fieldC, arg0->field1);
                    if (result != NULL) {
                        func_10022EC0(result + 0x110, &packet, 0x34);
                    }
                }
                emitter->timer -= 1.0f;
                emitter->count--;
            } while (emitter->timer > 1.0f && emitter->count > 0);
        }
    }
}
extern void func_15169850(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_150F3194(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}
void func_150F31D4(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, (s32) arg2, arg0 + 0x110, arg0 + 0x114, arg0);
}
void func_15143134(f32 *, f32 *, s32);
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

s32 func_150F3214(u8 *owner) {
    u8 *link;
    u8 *slot;
    f32 scale;

    link = *(u8 **)(owner + 0x110);
    slot = owner + 0x110;
    if (*(s32 *)link == 0 || slot[4] != link[0x3B] ||
        *(s32 *)(link + 0x1D4) == 0) {
        return 0;
    }
    func_15143134(&D_800A1950, (f32 *)(owner + 0x34), (s32)((u32)*(s32 *)(link + 0x1D4) + 0x3C0U));
    scale = *(f32 *)(slot + 0x10) * sqrtf(*(f32 *)(slot + 8));
    *(f32 *)(owner + 0x30) = scale;
    *(f32 *)(owner + 0x2C) = scale;
    *(s8 *)(owner + 0x5C) = (s8)(u32)(*(f32 *)(slot + 0x14) -
        (*(f32 *)(slot + 8) * (*(f32 *)(slot + 8) * *(f32 *)(slot + 0x18))));
    *(f32 *)(slot + 8) += D_800BE9A4;
    if (*(f32 *)(slot + 0xC) < *(f32 *)(slot + 8)) {
        return 0;
    }
    return 1;
}
s32 func_15140410(s32, s32, s32, s16);

void func_150F337C(s32 arg0, s16 arg1) {
    func_15140410(arg0, arg0 + 0x12C, arg0 + 0x138, arg1);
}
