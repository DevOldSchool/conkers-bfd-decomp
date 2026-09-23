#include "types.h"

/*
 * Reviewed source unit: src/game/game_90840.c
 * Boundary evidence: docs/evidence/game_raw_connected_controller_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15063628
 * - func_150636A4
 * - func_150636F0
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
void func_150636A4(Game90840Actor *);

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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150636A4 CURRENT (15) */
void func_150636A4(Game90840Actor *arg0) {
    void *temp_a1;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0->field_31C + 0xB0);
    if (temp_v0 != 0) {
        temp_a1 = *(void **)((u8 *)temp_v0 + 0x31C);
        if (temp_a1 != 0) {
            *(s8 *)((u8 *)temp_a1 + 0x195) = 0x1E;
            *(s8 *)((u8 *)*(void **)((u8 *)temp_v0 + 0x31C) + 0x196) =
                (s8)(arg0 - D_800CC2D0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150636A4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_150636A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_150636F0.s")
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15063B64 CURRENT (261) */
void func_15063B64(Game90840Actor *arg0) {
    s32 attachment;
    u8 type;
    u8 count;
    void *inner;
    s32 animation;
    Game90840ActionPacket packet;

    type = *((u8 *)arg0 + 4);
    if ((type == 0x75) || (type == 0xB1)) {
        animation = 0x64;
    } else {
        animation = 0x2C;
    }
    if (func_1503195C(arg0, animation, 0) != 0) {
        attachment = *(s32 *)((u8 *)arg0 + 0x1D4);
        if (attachment != 0) {
            func_15143134(0, packet.position, attachment + 0x100);
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
        count = *(u8 *)((u8 *)inner + 0x19A);
        if (count != 0) {
            *(u8 *)((u8 *)inner + 0x19A) = count - 1;
        }
        ((u8 *)arg0->field_31C)[0x11A] = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15063B64 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_15063B64.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15063C60 CURRENT (12810) */
Game90840Actor *func_15063C60(Game90840Actor *arg0, s32 arg1) {
    Game90840Actor *actor;

    for (actor = D_800CC2D0; actor != &D_800CC2D0[25]; actor++) {
        if ((*(s32 *)actor != 0) &&
            (arg1 == actor->pad0[4]) &&
            (((arg0 - D_800CC2D0) + 1) == actor->pad20[0x45])) {
            return actor;
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_15064B94.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_15065A5C.s")
