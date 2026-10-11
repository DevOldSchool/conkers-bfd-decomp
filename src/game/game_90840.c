#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_90840.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_connected_controller_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15063628
 * - func_15063B64
 * - func_15063C60
 * - func_15063E84
 * - func_15063FA0
 * - func_150641D8
 * - func_150642AC
 * - func_15064A14
 * - func_15064B94
 * - func_15065A5C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game90840Inner {
    u8 pad0[0x12];
    s16 field_12;
    u8 pad14[0x11C];
    f32 field_130;
    f32 field_134;
    f32 field_138;
    s32 field_13C;
    s32 field_140;
    s32 field_144;
} Game90840Inner;

typedef struct Game90840Actor {
    u8 pad0[0x14];
    f32 x;
    u8 pad18[4];
    f32 z;
    u8 pad20[0x5A];
    u16 field_7A;
    u8 pad7C[0x1A6];
    u8 field_222;
    u8 pad223[0xAD];
    struct Game90840Value *field_2D0;
    u8 pad2D4[0x48];
    Game90840Inner *field_31C;
    u8 pad320[0xC];
} Game90840Actor;

typedef struct Game90840Value {
    u8 pad0[8];
    f32 field_8;
    u8 padC[0xC];
    f32 field_18;
} Game90840Value;

s32 func_1505A630(f32, f32, s32);
extern Game90840Actor D_800CC2D0[];

s16 func_15063390(Game90840Actor *arg0) {
    Game90840Actor *other = &D_800CC2D0[arg0->field_222];

    return func_1505A630(other->x - arg0->x, arg0->z - other->z, 0);
}
s32 func_15083568(void *, s32, f32, s32);
void func_1505E650(void *, s32, f32, f32, f32, f32, s32);

void func_15063404(Game90840Actor *arg0) {
    Game90840Actor *temp_v0;

    temp_v0 = &D_800CC2D0[arg0 - D_800CC2D0];
    temp_v0->field_31C->pad14[0x64] = 9;
    func_15083568(arg0, 0x1D, 1.0f, 0);
    func_15083568(arg0, 0x1E, 1.0f, 0);
    *((u8 *)arg0 + 0x8A) = 0x14;
    *((u8 *)arg0 + 0x89) = 0;
    *((u8 *)arg0 + 0x83) = 0;
    *(s16 *)((u8 *)temp_v0->field_31C + 0x24) = 0x3C;
    temp_v0->field_31C->pad14[0x106] = 2;
    func_1505E650(arg0, 0x7F, 1.0f, 0.0f, 0.0f, 0.0f, 0);
}

void func_150836CC(void *, s32);

void func_150634E4(Game90840Actor *arg0) {
    Game90840Actor *temp_v0;

    temp_v0 = &D_800CC2D0[arg0 - D_800CC2D0];
    temp_v0->field_31C->pad14[0x64] = 0;
    temp_v0->field_31C->pad14[0x106] = 0;
    func_150836CC(arg0, 0x1D);
    func_150836CC(arg0, 0x1E);
    *(u8 *)((u8 *)arg0 + 0x8A) = 0;
    *(u8 *)((u8 *)arg0 + 0x89) = 0;
    *(u8 *)((u8 *)arg0 + 0x83) = 0;
}
void func_15063570(Game90840Actor *arg0) {
    Game90840Actor *actor;

    actor = &D_800CC2D0[arg0 - D_800CC2D0];
    actor->field_31C->pad14[0x64] = 0x3B;
    actor->field_31C->pad14[0x106] = 2;
    func_15083568(arg0, 0x89, 1.0f, 0);
    *((u8 *)arg0 + 0x8A) = 0x14;
    *((u8 *)arg0 + 0x89) = 0;
    *((u8 *)arg0 + 0x83) = 0;
    func_1505E650(arg0, 0x221, 1.0f, 0.0f, 0.0f, 0.0f, 0);
}

void func_15081690(f32, s32, s32, s32, f32, f32, f32, void *, f32, s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15063628 CURRENT (481) */
void func_15063628(Game90840Actor *arg0, f32 arg1) {
    Game90840Inner *inner;

    inner = arg0->field_31C;
    func_15081690(arg1, inner->field_13C, inner->field_140, inner->field_144,
                  inner->field_130, inner->field_134, inner->field_138,
                  (u8 *)inner + 0xB0, arg1, 0, 0, 0, -1, 0, 0);
    func_150636A4(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15063628 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_15063628.s")

void func_150636A4(Game90840Actor *arg0) {
    void *temp_a1;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0->field_31C + 0xB0);
    if (temp_v0 != 0) {
        temp_a1 = *(void **)((u8 *)temp_v0 + 0x31C);
        if (*(void **)((u8 *)temp_v0 + 0x31C) != 0) {
            *(s8 *)((u8 *)temp_a1 + 0x195) = 0x1E;
            *(s8 *)((u8 *)*(void **)((u8 *)temp_v0 + 0x31C) + 0x196) =
                (s8)(arg0 - D_800CC2D0);
        }
    }
}
typedef struct Game90840Requests {
    u8 pad0[0x78];
    u8 action;
    u8 pad79[0x36];
    u8 soundPending;
    u8 padB0[0xFA];
    s16 count;
    u8 pad1AC[8];
    u8 pending;
} Game90840Requests;

extern s8 D_800CC2B0;
extern u8 D_800C3E78;
extern Game90840Actor *D_800D154C;
void func_15063628(Game90840Actor *, f32);
void func_15063FA0(Game90840Actor *, s32);
void func_151D57F8(Game90840Actor *, s32);
s32 func_15081E78(Game90840Actor *, void *, s32);
s32 func_10010894(void *);
u32 func_150ADA20(void);
void func_10010558(u16, void *, s32, s32, s32, s32);
void func_150FFCC8(void *, void *, void *, void *, void *);
void func_150FFD84(f32 *, f32 *, s32, s32);

void func_150636F0(void) {
    Game90840Actor *actor;
    s32 index;
    s32 action;
    f32 position[3];
    f32 direction[3];
    f32 side[3];
    f32 up[3];
    Game90840Requests *requests;
    void *resource;

    D_800CC2B0 = 0;
    actor = D_800CC2D0;
    index = 0;
    do {
        if ((*(s32 *)actor != 0) && (actor->field_31C != 0) &&
            (((Game90840Requests *)actor->field_31C)->pending != 0)) {
            D_800C3E78 = index;
            D_800D154C = actor;
            requests = (Game90840Requests *)actor->field_31C;
            if (requests->pending & 1) {
                func_15063628(actor, 0.0f);
                requests = (Game90840Requests *)actor->field_31C;
            }
            if (requests->pending & 4) {
                func_151D57F8(actor, 0);
                requests = (Game90840Requests *)actor->field_31C;
            }
            if (requests->pending & 8) {
                func_151D57F8(actor, 1);
                requests = (Game90840Requests *)actor->field_31C;
            }
            if (requests->pending & 2) {
                action = requests->action & ~0x80;
                switch (action) {
                case 0x18:
                case 0x41:
                    func_15063FA0(actor, 6);
                    requests = (Game90840Requests *)actor->field_31C;
                    requests->count++;
                    resource = *(void **)((u8 *)actor + 0x318);
                    if (resource != 0) {
                        func_1512D2E4(resource, 1);
                    }
                    break;
                case 0x14:
                case 0x3F:
                    if (action == 0x14) {
                        func_15063FA0(actor, 2);
                    } else {
                        func_15063FA0(actor, 0x12);
                    }
                    requests = (Game90840Requests *)actor->field_31C;
                    requests->count++;
                    resource = *(void **)((u8 *)actor + 0x318);
                    if (resource != 0) {
                        func_1512D2E4(resource, 1);
                    }
                    break;
                case 0x24:
                    if (func_15081E78(actor, (u8 *)requests + 0xB0, 7) != 2) {
                        requests = (Game90840Requests *)actor->field_31C;
                        if (requests->soundPending != 0) {
                            requests->soundPending = 0;
                            if (func_10010894(actor) == 0) {
                                func_10010558((u16)(func_150ADA20() % 3 + 0x53B),
                                             actor, 0x7D00, 0x320, 0xBB8, 0x1E);
                            }
                        }
                    }
                    resource = *(void **)((u8 *)actor + 0x318);
                    if (resource != 0) {
                        func_1512D2E4(resource, 1);
                    }
                    break;
                case 0x3B:
                    func_15081E78(actor, (u8 *)requests + 0xB0, 0x10);
                    func_150FFCC8(actor, position, direction, side, up);
                    func_150FFD84(position, direction, 0xFF, 1);
                    break;
                case 0x23:
                    func_15081E78(actor, (u8 *)requests + 0xB0, 8);
                    resource = *(void **)((u8 *)actor + 0x318);
                    if (resource != 0) {
                        func_1512D2E4(resource, 0);
                    }
                    break;
                }
                requests = (Game90840Requests *)actor->field_31C;
            }
            requests->pending = 0;
        }
        index++;
        actor++;
    } while (index != 0x19);
}
extern s16 D_800CC2B2;

s16 func_150639BC(Game90840Actor *arg0) {
    D_800CC2B2 = (arg0->field_7A - arg0->field_31C->field_12) - func_15063390(arg0);
    if (D_800CC2B2 >= 0x3E81) {
        D_800CC2B2 = 0x3E80;
    }
    if (D_800CC2B2 < -0x3E80) {
        D_800CC2B2 = -0x3E80;
    }
    return D_800CC2B2;
}

extern s16 D_800CC264;
extern void *D_800CC284;
extern f32 D_800CC2B4;

s32 func_15063A38(Game90840Actor *arg0, s32 arg1, s32 arg2) {
    s16 temp_v1;
    u16 temp_t0;
    u16 temp_t3;

    if (arg1 & arg2) {
        D_800CC2B2 = *(s8 *)((u8 *)D_800CC284 + 2) * 0xC8;
        if (arg0->field_31C->pad14[0x70] != 0) {
            D_800CC2B2 = func_150639BC(arg0);
        }
        D_800CC2B4 = 12.0f;
        D_800CC2B2 = arg0->field_31C->field_12 + ((s32) (D_800CC2B2 * D_800CC264) / 2000);
        temp_v1 = D_800CC2B2;
        if (temp_v1 < -0x2328) {
            temp_t0 = (arg0->field_7A - temp_v1) - 0x2328;
            arg0->field_7A = temp_t0;
            *(u16 *)((u8 *)arg0 + 0x76) = temp_t0;
            D_800CC2B2 = -0x2328;
            temp_v1 = D_800CC2B2;
        }
        if (temp_v1 >= 0x2329) {
            temp_t3 = (arg0->field_7A - temp_v1) + 0x2328;
            arg0->field_7A = temp_t3;
            *(u16 *)((u8 *)arg0 + 0x76) = temp_t3;
            D_800CC2B2 = 0x2328;
            temp_v1 = D_800CC2B2;
        }
        arg0->field_31C->field_12 = temp_v1;
        return 1;
    }
    return 0;
}
s32 func_1503195C(void *, s32, s32);
void func_1506AC8C(void *, s32, void *);
void func_15143134(f32 *, f32 *, s32);

typedef struct Game90840ActionPacket {
    Game90840Actor *actor;
    f32 position[3];
    s32 actorIndex;
} Game90840ActionPacket;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15063B64 CURRENT (250) */
void func_15063B64(Game90840Actor *arg0) {
    s32 value;
    void *inner;
    s32 animation;
    Game90840ActionPacket packet;

    value = *((u8 *)arg0 + 4);
    if ((value == 0x75) || (value == 0xB1)) {
        animation = 0x64;
    } else {
        animation = 0x2C;
    }
    if (func_1503195C(arg0, animation, 0) != 0) {
        value = *(s32 *)((u8 *)arg0 + 0x1D4);
        if (value != 0) {
            func_15143134(0, packet.position, value + 0x100);
        } else {
            packet.position[0] = arg0->x;
            packet.position[1] = *(f32 *)((u8 *)arg0 + 0x18);
            packet.position[2] = arg0->z;
        }
        packet.actorIndex = (arg0 - D_800CC2D0) + 1;
        packet.actor = arg0;
        func_1506AC8C(arg0, 0xB, &packet);
        func_150836CC(arg0, animation);
        inner = arg0->field_31C;
        value = *(u8 *)((u8 *)inner + 0x19A);
        if (value != 0) {
            *(u8 *)((u8 *)inner + 0x19A) = value - 1;
        }
        ((u8 *)arg0->field_31C)[0x11A] = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15063B64 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_15063B64.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15063C60 CURRENT (40) */
Game90840Actor *func_15063C60(Game90840Actor *arg0, s32 arg1) {
    s32 index;

    for (index = 0; index < 25; index++) {
        if ((*(s32 *)&D_800CC2D0[index] != 0) &&
            (arg1 == D_800CC2D0[index].pad0[4]) &&
            (((arg0 - D_800CC2D0) + 1) == D_800CC2D0[index].pad20[0x45])) {
            return &D_800CC2D0[index];
        }
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15063C60 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_15063C60.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15063E84 CURRENT (1885) */
s32 func_15063E84(void *arg0, u16 arg1, u16 arg2, register s32 arg3, s32 arg4) {
    register s32 temp_t6;
    register s32 temp_t7;
    u8 temp_a1;
    u8 *temp_v0;

    temp_t6 = arg1;
    temp_t7 = arg2;
    arg2 = temp_t7;
    arg1 = temp_t6;
    if ((arg4 & 0x4000) &&
        (*(f32 *)((u8 *)arg0 + 0x28) == 0.0f) &&
        (*(f32 *)((u8 *)arg0 + 0x20) <= 0.0f)) {
        temp_v0 = *(u8 **)((u8 *)arg0 + 0x31C);
        if ((temp_v0[0x95] == 0) &&
            (temp_t6 != *(u16 *)((u8 *)arg0 + 0x84)) &&
            ((temp_a1 = temp_v0[0x11A], temp_a1 == 0) ||
             (temp_a1 == 2)) &&
            (temp_v0[0x27] == 0)) {
            if ((arg3 != 0) && (*(u8 *)((u8 *)arg0 + 0x8A) != 0)) {
                return 0x3E7;
            }
            if (temp_t7 & 1) {
                *(u8 *)((u8 *)arg0 + 0x8A) = 0x14;
            }
            if (arg3 != 0) {
                if ((*(u8 **)((u8 *)arg0 + 0x31C))[0x11A] == 2) {
                    return 0x3E7;
                }
                (*(u8 **)((u8 *)arg0 + 0x31C))[0x11A] = 1;
            } else {
                (*(u8 **)((u8 *)arg0 + 0x31C))[0x11A] = 3;
            }
            (*(u8 **)((u8 *)arg0 + 0x31C))[0x78] = arg3;
            *(u8 *)((u8 *)arg0 + 0x89) = 0xFF;
            *(u8 *)((u8 *)arg0 + 0x83) = 0xFF;
            return temp_t6;
        }
    }
    return 0x3E7;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15063E84 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_15063E84.s")
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Game90840Vector;

typedef struct {
    u8 pad0[0xB8];
    Game90840Vector target;
    u8 padC4[0x45];
    u8 aiming;
    u8 pad10A[0x32];
    Game90840Vector position;
    u8 pad148[0x24];
    f32 heading;
    f32 pitch;
} Game90840AimState;

f32 func_15047D60(f32);
f32 func_15047C00(f32);
f32 func_150484A0(f32, f32);
void func_1505A184(s32, f32, f32, f32 *, f32 *, f32 *);
void *func_1506C460(f32, f32, f32, f32, s32, s32, f32, f32,
                       f32 *, s32, s32);
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
extern f32 D_80099790;
extern f32 D_80099794;
extern f32 D_80099798;
extern f32 D_8009979C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15063FA0 CURRENT (382) */
void func_15063FA0(Game90840Actor *arg0, s32 arg1) {
    f32 horizontal;
    f32 verticalVelocity;
    f32 unusedDirection;
    f32 magnitude;
    Game90840Vector position;
    f32 horizontalOffset[2];
    f32 height;
    f32 radius;
    f32 radians;
    f32 pitch;
    f32 heading;
    f32 deltaX;
    f32 deltaY;
    f32 deltaZ;
    s32 inclination;

    magnitude = 300.0f;
    height = 0.0f;
    radius = 0.0f;
    switch (arg1) {
    case 2:
        radius = 27.0f;
        break;
    case 3:
    case 6:
        height = -11.0f;
        magnitude = 500.0f;
        break;
    }
    radians = ((Game90840AimState *)arg0->field_31C)->heading * D_80099790;
    horizontalOffset[0] = func_15047D60(radians) * radius;
    horizontalOffset[1] = func_15047C00(radians) * radius;
    position.x = horizontalOffset[0] + ((Game90840AimState *)arg0->field_31C)->position.x;
    position.y = ((Game90840AimState *)arg0->field_31C)->position.y + height;
    position.z = horizontalOffset[1] + ((Game90840AimState *)arg0->field_31C)->position.z;
    if (((Game90840AimState *)arg0->field_31C)->aiming == 0) {
        pitch = -((Game90840AimState *)arg0->field_31C)->pitch;
        heading = ((Game90840AimState *)arg0->field_31C)->heading + 90.0f;
    } else {
        deltaX = ((Game90840AimState *)arg0->field_31C)->target.x - position.x;
        deltaY = ((Game90840AimState *)arg0->field_31C)->target.y - position.y;
        deltaZ = ((Game90840AimState *)arg0->field_31C)->target.z - position.z;
        pitch = func_150484A0(deltaY, sqrtf(deltaX * deltaX + deltaZ * deltaZ)) * D_80099794;
        heading = func_150484A0(deltaX, deltaZ) * D_80099798;
    }
    inclination = (s32)(pitch * D_8009979C);
    func_1505A184(inclination & 0xFFFF, magnitude, 0.0f,
                  &horizontal, &verticalVelocity, &unusedDirection);
    verticalVelocity = -verticalVelocity;
    func_1506C460(heading, horizontal, verticalVelocity, 0.0f, 100, arg1,
                  0.0f, 0.5f, &position.x, 1, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15063FA0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_15063FA0.s")
s32 func_1505DADC(void *, u16 *, s32, s32, s32);
u32 func_150ADA20(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150641D8 CURRENT (1340) */
u16 func_150641D8(void *arg0, u16 arg1, u16 arg2, u16 arg3) {
    u16 selected;
    u16 output;
    u16 current;

    output = 0;
    selected = arg1;
    if (func_150ADA20() & 1) {
        selected = arg2;
    }
    current = *(u16 *)((u8 *)arg0 + 0x84);
    if ((arg1 == current) || (arg2 == current)) {
        selected = arg3;
        if (*(u8 *)((u8 *)arg0 + 0x107) < 0x28) {
            return 0x3E7;
        }
    }
    if (arg3 == current) {
        selected = 0x3E7;
    }
    if (func_1505DADC(arg0, &output, 0, 0xFE, 0x40) != 0xFF) {
        *(u16 *)((u8 *)arg0 + 0x76) = output;
    }
    *(u8 *)((u8 *)arg0 + 0x83) = 0xFF;
    return selected;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150641D8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_150641D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_150642AC.s")

void func_150649A0(u32 arg0, u32 arg1) {
    Game90840Value *first = D_800CC2D0[arg1].field_2D0;
    Game90840Value *second = D_800CC2D0[arg0].field_2D0;

    if ((first != 0) && (second != 0)) {
        f32 limit = first->field_18;

        first->field_8 = second->field_8;
        if (limit <= first->field_8) {
            first->field_8 = limit - 1.0f;
        }
    }
}
void func_150649A0(u32, u32);
extern u8 D_800C3E78;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15064A14 CURRENT (2376) */
void func_15064A14(Game90840Actor *arg0) {
    u8 *actor;
    u8 type;
    s32 animation;
    s32 active;
    void *other;
    u16 state1;
    u16 state2;

    actor = (u8 *)(&D_800CC2D0[*((u8 *)arg0 + 0x65)] - 1);
    type = actor[4];
    animation = 0xF;

    if (type == 0xC) {
        state1 = *(u16 *)(actor + 0x84);
        animation = 0x5A;
        if (state1 == 0xC) {
            animation = 0x5B;
        } else if (state1 == 0xD) {
            animation = 0x5C;
        }
    } else if (type == 0x53) {
        state2 = *(u16 *)(actor + 0x84);
        animation = 0x8C;
        if (state2 == 0xB) {
            animation = 0xA2;
        } else if (state2 == 0xD) {
            animation = 0xA3;
        }
    } else if (type == 0x21) {
        animation = 0x169;
    } else if (type == 0x8A) {
        other = arg0->field_31C;
        if (other != 0 && *(u8 *)((u8 *)other + 0x1B2) != 0) {
            active = 1;
        } else {
            active = 0;
        }
        if (actor[0x232] == 4) {
            if (active != 0) {
                animation = 0x350;
            } else {
                animation = 0x1A4;
            }
        } else {
            animation = 0x1A1;
            if (active != 0) {
                animation = 0x34F;
            }
        }
    }
    func_1505E650(arg0, animation & 0xFFFF, 1.0f, 6.0f,
                   0.0f, 0.0f, 0);
    func_150649A0(*((u8 *)arg0 + 0x65) - 1, D_800C3E78);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15064A14 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_15064A14.s")
s32 func_1504C078(void);
s32 func_1504C0B8(void);
void func_1506E5FC(void);
extern f32 D_800997E8;
extern f32 D_800997EC;
extern f32 D_800997F0;
extern f32 D_800997F4;
extern f32 D_800997F8;
extern f32 D_800997FC;
extern f32 D_80099800;
extern f32 D_80099804;
extern f32 D_80099808;
extern f32 D_8009980C;
extern f32 D_80099810;
extern f32 D_80099814;
extern f32 D_80099818;
extern f32 D_8009981C;
extern f32 D_80099820;
extern f32 D_80099824;
extern f32 D_80099828;
extern f32 D_8009982C;
extern f32 D_80099830;
extern f32 D_80099834;
extern f32 D_80099838;
extern f32 D_8009983C;
extern f32 D_80099840;
extern f32 D_80099844;
extern f32 D_80099848;
extern f32 D_8009984C;
extern f32 D_80099850;
extern f32 D_80099854;
extern f32 D_80099858;
extern f32 D_8009985C;
extern f32 D_80099860;
extern f32 D_80099864;
extern f32 D_80099868;
extern f32 D_8009986C;
extern f32 D_80099870;
extern f32 D_80099874;
extern f32 D_80099878;
extern f32 D_8009987C;
extern u8 D_800B85A4[];
extern u8 D_800BE616;
extern s32 D_800D1580;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15064B94 CURRENT (2155) */
s32 func_15064B94(u8 *arg0, f32 arg1, f32 arg2, s32 arg3, f32 arg4) {
    s32 anim;
    f32 blend;
    f32 speed;
    u8 *inner;

    anim = 0;
    blend = 4.0f;
    inner = *(u8 **)(arg0 + 0x31C);
    speed = 1.0f;
    if (*(s16 *)(inner + 0x46) > 0) {
        anim = 0x4C;
        speed = arg1 / 24.0f;
    } else if (inner[0x4E] == 2) {
        anim = 5;
        if ((s8)inner[0x50] > 0) {
            anim = 0x54;
        }
        blend = 2.0f;
    } else if (arg0[0x13C] >= 100) {
        if (*(f32 *)(arg0 + 0x3C) < 1.0f) {
            speed = 1.0f;
            anim = func_1504C078();
        } else {
            switch (D_800B85A4[D_800D154C->pad7C[0xC0] * 0x32C]) {
            case 0x8C:
                arg0[0xAA] = 0x5A;
                anim = 0x1A6;
                speed = arg1 / 6.0f + D_800997E8;
                if (*(f32 *)(arg0 + 0x3C) > 14.0f) {
                    anim = 0x1A7;
                    speed = arg1 / 26.0f + 0.5f;
                }
                break;
            case 0x57:
                arg0[0xAA] = 0x5A;
                anim = 0x116;
                speed = arg1 / 6.0f + D_800997EC;
                if (*(f32 *)(arg0 + 0x3C) > 14.0f) {
                    anim = 0x117;
                    speed = arg1 / 26.0f + 0.5f;
                }
                break;
            case 0xA8:
            case 0xA9:
                if (*(f32 *)(arg0 + 0x3C) > 14.0f) {
                    anim = 0x1B1;
                    speed = arg1 / 22.0f + D_800997F0;
                } else {
                    anim = 0x1B0;
                    speed = arg1 * 0.0625f + D_800997F4;
                }
                break;
            case 0x13:
                anim = 0x14C;
                speed = arg1 / 6.0f;
                break;
            case 0x89:
                anim = 0x1FB;
                speed = arg1 / 6.0f;
                break;
            default:
                if (*(f32 *)(arg0 + 0x3C) > 14.0f) {
                    anim = 0x2E4;
                    speed = arg1 * 0.0625f + 0.5f;
                } else {
                    anim = 0xD7;
                    speed = arg1 / 6.0f + D_800997F8;
                }
                break;
            }
        }
    } else if (arg3 != 0 && inner[0x78] == 0) {
        anim = arg3;
        speed = arg1 / 15.0f + D_800997FC;
    } else if (D_80099800 < *(f32 *)(arg0 + 0x44) && (*(u16 *)(inner + 0x32) & 1)) {
        arg0[0xAA] = 0x28;
        blend = 5.0f;
        speed = *(f32 *)(arg0 + 0x44) / 15.0f + 0.5f;
        anim = func_1504C0B8();
    } else if (inner[0x78] == 0x16) {
        if (*(f32 *)(arg0 + 0x44) >= 1.0f) {
            anim = 0xE8;
            if (inner[0x1B2] != 0) {
                anim = 0x2C6;
            }
            arg0[0xAA] = 0x1E;
            speed = arg1 * 0.0625f + D_80099804;
        } else {
            speed = 1.0f;
            anim = func_1504C078();
        }
    } else if (inner[0x78] == 9) {
        if (*(f32 *)(arg0 + 0x44) >= 1.0f) {
            if (D_800BE616 == 0) {
                arg0[0xAA] = 0x37;
            }
            anim = 0x7E;
            if (D_800BE616 == 0) {
                speed = arg1 * 0.0625f + D_80099808;
            } else if (*(f32 *)(arg0 + 0x44) >= 20.0f) {
                anim = 0x22C;
                speed = arg1 / 22.0f + D_8009980C;
            }
        } else {
            speed = 1.0f;
            anim = func_1504C078();
        }
    } else if (inner[0x78] == 0x38) {
        if (*(f32 *)(arg0 + 0x44) >= 1.0f) {
            anim = 0x1E1;
            if (*(f32 *)(arg0 + 0x44) >= 20.0f) {
                anim = 0x1E2;
                speed = arg1 / 22.0f + D_80099810;
            }
        } else {
            speed = 1.0f;
            anim = func_1504C078();
        }
    } else if (inner[0x78] == 0x39) {
        if (*(u16 *)(arg0 + 0x84) != 0x1EB) {
            if (*(f32 *)(arg0 + 0x44) >= 1.0f) {
                anim = 0x1EC;
                if (*(f32 *)(arg0 + 0x44) >= 20.0f) {
                    anim = 0x1ED;
                    speed = arg1 / 22.0f + D_80099814;
                }
            } else {
                speed = 1.0f;
                anim = func_1504C078();
            }
        } else {
            anim = 999;
        }
    } else if (inner[0x78] == 0x37) {
        if (*(u16 *)(arg0 + 0x84) != 0x1F4) {
            if (*(f32 *)(arg0 + 0x44) >= 1.0f) {
                anim = 0x1F5;
                if (*(f32 *)(arg0 + 0x44) >= 20.0f) {
                    anim = 0x1F6;
                    speed = arg1 / 22.0f + D_80099818;
                }
            } else {
                speed = 1.0f;
                anim = func_1504C078();
            }
        } else {
            anim = 999;
        }
    } else if (inner[0x78] == 0x3B) {
        if (*(u16 *)(arg0 + 0x84) != 0x222 && *(u16 *)(arg0 + 0x84) != 0x236) {
            if (*(f32 *)(arg0 + 0x44) >= 1.0f || (s8)inner[0x23] > 0) {
                anim = 0x223;
                arg0[0xAA] = 0x37;
                if (*(f32 *)(arg0 + 0x44) >= 20.0f) {
                    anim = 0x224;
                    speed = arg1 / 22.0f + D_8009981C;
                }
            } else {
                speed = 1.0f;
                anim = func_1504C078();
            }
        } else {
            anim = 999;
        }
    } else if (inner[0x78] == 0x12 || inner[0x78] == 0x18 || inner[0x78] == 0x41) {
        if (*(f32 *)(arg0 + 0x44) >= 1.0f) {
            arg0[0xAA] = 0x50;
            anim = 0xEC;
            speed = arg1 * 0.0625f + D_80099820;
            if (*(f32 *)(arg0 + 0x44) >= 20.0f) {
                anim = 0xF8;
                speed = arg1 / 22.0f + D_80099824;
            }
        } else {
            speed = 1.0f;
            anim = func_1504C078();
        }
    } else if (inner[0x78] == 0x24) {
        if (*(f32 *)(arg0 + 0x44) >= 1.0f) {
            arg0[0xAA] = 0x50;
            anim = 0x158;
            speed = arg1 * 0.0625f + D_80099828;
            if (*(f32 *)(arg0 + 0x44) >= 20.0f) {
                anim = 0x159;
                speed = arg1 / 22.0f + D_8009982C;
            }
        } else {
            speed = 1.0f;
            anim = func_1504C078();
        }
    } else if (inner[0x78] == 0x22) {
        if (*(f32 *)(arg0 + 0x44) >= 1.0f) {
            arg0[0xAA] = 0x50;
            anim = 0x15B;
            speed = arg1 * 0.0625f + D_80099830;
            if (*(f32 *)(arg0 + 0x44) >= 20.0f) {
                anim = 0x15C;
                speed = arg1 / 22.0f + D_80099834;
            }
        } else {
            speed = 1.0f;
            anim = func_1504C078();
        }
    } else if (inner[0x78] == 0x21) {
        if (*(f32 *)(arg0 + 0x44) >= 1.0f) {
            arg0[0xAA] = 0x6E;
            anim = 0x123;
            speed = arg1 * 0.0625f + D_80099838;
            if (*(f32 *)(arg0 + 0x44) >= 15.0f) {
                anim = 0x124;
                speed = arg1 / 27.0f;
            }
        } else {
            speed = 1.0f;
            anim = func_1504C078();
        }
    } else if (inner[0x78] == 0x26) {
        if (*(f32 *)(arg0 + 0x44) >= 1.0f) {
            arg0[0xAA] = 0x50;
            anim = 0x178;
            speed = arg1 * 0.0625f + D_8009983C;
            if (*(f32 *)(arg0 + 0x44) >= 20.0f) {
                anim = 0x179;
                speed = arg1 / 22.0f + D_80099840;
            }
        } else {
            speed = 1.0f;
            anim = func_1504C078();
        }
    } else if (inner[0x78] == 0x3A) {
        if (*(f32 *)(arg0 + 0x44) >= 1.0f) {
            arg0[0xAA] = 0x50;
            anim = 0x1FB;
            speed = arg1 * 0.0625f + D_80099844;
        } else {
            speed = 1.0f;
            anim = func_1504C078();
        }
    } else if (inner[0x78] == 0x25) {
        if (*(f32 *)(arg0 + 0x44) >= 1.0f) {
            arg0[0xAA] = 0x50;
            anim = 0xD7;
            speed = arg1 * 0.0625f + D_80099848;
            if (*(f32 *)(arg0 + 0x44) >= 20.0f) {
                speed = arg1 / 22.0f + D_8009984C;
            }
        } else {
            speed = 1.0f;
            anim = func_1504C078();
        }
    } else if (inner[0x78] == 0x2D || inner[0x78] == 0x2E) {
        if (*(f32 *)(arg0 + 0x44) >= 1.0f) {
            anim = 0x1B0;
            speed = arg1 * 0.0625f + D_80099850;
            if (*(f32 *)(arg0 + 0x44) >= 20.0f) {
                anim = 0x1B1;
                speed = arg1 / 22.0f + D_80099854;
            }
        } else {
            speed = 1.0f;
            anim = func_1504C078();
        }
    } else if (inner[0x78] == 0x23) {
        if (*(f32 *)(arg0 + 0x44) >= 1.0f) {
            arg0[0xAA] = 0x50;
            anim = 0x161;
            speed = arg1 * 0.0625f + D_80099858;
            if (*(f32 *)(arg0 + 0x44) >= 20.0f) {
                anim = 0x162;
                speed = arg1 / 22.0f + D_8009985C;
            }
        } else {
            speed = 1.0f;
            anim = func_1504C078();
        }
    } else if (inner[0x78] == 0x15) {
        if (*(f32 *)(arg0 + 0x44) >= 1.0f) {
            arg0[0xAA] = 0x50;
            anim = 0xED;
            speed = arg1 * 0.0625f + D_80099860;
            if (*(f32 *)(arg0 + 0x44) >= 20.0f) {
                speed = arg1 / 22.0f + D_80099864;
            }
        } else {
            speed = 1.0f;
            anim = func_1504C078();
        }
    } else if (inner[0x78] == 0x19 || inner[0x78] == 0x40) {
        if (*(f32 *)(arg0 + 0x3C) >= 1.0f) {
            anim = 0x112;
            speed = arg1 * 0.125f + D_80099868;
            blend = 8.0f;
            if (*(f32 *)(arg0 + 0x3C) >= 18.0f) {
                anim = 0x111;
                speed = arg1 / 20.0f + D_80099868;
            }
        } else {
            speed = 1.0f;
            anim = func_1504C078();
        }
    } else if (inner[0x1A] != 0 && arg2 > 1.0f) {
        anim = 0x6D;
        speed = arg1 / 6.5f + D_8009986C;
        arg0[0xAA] = 0x28;
        blend = 8.0f;
    } else if (*(s16 *)(inner + 8) > 0) {
        if (arg2 < 1.0f) {
            speed = 1.0f;
            anim = func_1504C078();
        } else {
            anim = *(u16 *)(inner + 0xE);
            blend = 16.0f;
            speed = arg1 / 6.0f + D_80099870;
        }
    } else if (inner[0x17] != 0) {
        blend = 5.0f;
        if (*(u16 *)D_800CC284 & 0x2000) {
            if (*(u16 *)(arg0 + 0x84) != 0x283) {
                *(f32 *)(arg0 + 0x3C) *= D_80099874;
                D_800D1580 = 0xFF010604;
                func_1506E5FC();
                speed = 1.0f;
            }
            anim = 0x283;
            arg0[0x89] = 3;
            arg0[0x8A] = 3;
        } else {
            if (*(u16 *)(arg0 + 0x84) == 0x283) {
                D_800D1580 = 0xFF010604;
                func_1506E5FC();
            }
            if (*(f32 *)(arg0 + 0x44) >= 1.0f && arg0[0x89] == 0) {
                arg0[0xAA] = 0x2D;
                anim = 0x4E;
                speed = *(f32 *)(arg0 + 0x3C) / 9.0f;
            } else {
                speed = 1.0f;
                anim = func_1504C078();
            }
        }
    } else if ((*(u16 *)(inner + 0x32) & 2) && *(f32 *)(arg0 + 0x44) >= 1.0f) {
        inner[0x3C] = 0x1C;
        arg0[0xAA] = 0xF;
        speed = arg4 / 5.0f + D_80099878;
        blend = 8.0f;
        anim = 0x64;
        if (func_150ADA20() % 1000 >= 988) {
            anim = (func_150ADA20() & 1) + 0x65;
            speed = D_8009987C;
            arg0[0x89] = 0xFF;
            arg0[0x83] = 0xFF;
        }
    }
    if (anim != 0 && anim != 999) {
        func_1505E650(arg0, anim & 0xFFFF, speed, blend, 0.0f, 0.0f, 0);
    }
    return anim;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15064B94 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_15064B94.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_15065A5C.s")
