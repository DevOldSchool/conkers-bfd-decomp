#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_A9D90.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1507CD64
 * - func_1507DB6C
 * - func_1507E1D0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameA9D90Inner {
    u8 pad0[0x120];
    u8 field_120;
    u8 pad121[3];
    s16 field_124;
} GameA9D90Inner;

typedef struct GameA9D90Object {
    u8 pad0[0x31C];
    GameA9D90Inner *field_31C;
} GameA9D90Object;

void func_1507C8E0(GameA9D90Object *arg0, s32 arg1) {
    arg0->field_31C->field_120 = 2;
    arg0->field_31C->field_124 = arg1;
}
typedef struct GameA9D90Status {
    u8 pad0[0x84];
    u8 team;
    u8 pad85[0x9B];
    u8 state;
    u8 pad121;
    u8 finished;
    u8 pad123;
    s16 timer;
    s16 elapsed;
} GameA9D90Status;

typedef struct GameA9D90Player {
    u8 pad0[7];
    u8 controller;
    u8 pad8[0x314];
    GameA9D90Status *status;
    u8 pad320[0xC];
} GameA9D90Player;

void func_1506160C(u8 *, u8, u8, u8, u8);
void func_1507CD0C(void *);
void func_1507D4F8(s32);
void func_1507E1D0(void *, f32 *, f32 *, f32 *);
s32 func_150859AC(s32, s32);
void func_1517F814(s32, f32, f32, f32, s32);
extern s8 D_8008FD8C;
extern u16 D_8008FDBC;
extern s32 D_80082FA0;
extern u16 D_800BE710[];
extern u8 D_800BE616;
extern s32 D_800BE9E4;
extern u8 D_800BEAC0;
extern u8 D_800CC2D0;
extern u16 D_800D18A2;

void func_1507C8FC(void) {
    s32 i;
    f32 x;
    f32 y;
    f32 z;
    GameA9D90Player *player;

    if (D_800BEAC0 == 0) {
        player = (GameA9D90Player *)&D_800CC2D0;
        for (i = 0; i < D_8008FD8C; i++, player++) {
            if (player->status == NULL) {
                continue;
            }
            if (player->status->state == 0) {
                player->status->elapsed = 0;
                continue;
            }
            if (player->status->state == 1) {
                continue;
            }
            if (i <= D_80082FA0) {
                if (D_800BE616 != 0 && (D_800D18A2 & (1 << i))) {
                    player->status->state = 2;
                    player->status->timer = 60;
                }
                if (player->status->state == 11) {
                    func_1517EE40(0, 0, 0, 15, 1, i);
                    player->status->state = 12;
                    continue;
                }
                if (player->status->state == 12) {
                    if (func_1517EFAC(i) != 0) {
                        func_1507D4F8(i);
                    }
                    continue;
                }
                if (player->status->state == 2) {
                    if (player->status->timer > 0) {
                        player->status->timer -= D_800BE9E4;
                    } else {
                        func_1507CD0C(player);
                    }
                } else if (player->status->state == 7) {
                    if (player->status->timer > 0) {
                        player->status->timer -= D_800BE9E4;
                    } else {
                        player->status->state = 8;
                        func_1506160C((u8 *)player, 2, 0, 60, 0);
                    }
                }
                player->status->elapsed += D_800BE9E4;
                if ((D_800BE710[i] & 0x8000) || (D_800BE616 != 0 && player->status->team == 0) ||
                    func_150859AC((s16)i, 3) < 2 || (player->status->team == 1 && player->status->elapsed >= 181)) {
                    player->status->finished = 1;
                }
                if (D_8008FDBC & 0x80) {
                    player->status->finished = 0;
                }
                func_1507E1D0(player, &x, &y, &z);
                func_1517F814(0, x, y, z, i);
                if (player->status->finished != 0 && player->status->state == 5) {
                    player->status->state = 6;
                }
                if (player->status->state == 9) {
                    func_1507D4F8(i);
                }
            } else if (player->status->state == 11) {
                func_1507D4F8(i);
                continue;
            } else if (player->status->state == 2) {
                if (player->status->timer > 0) {
                    player->status->timer -= D_800BE9E4;
                } else {
                    player->status->state = 7;
                }
            } else {
                player->status->elapsed += D_800BE9E4;
                if (player->controller == 0xFF && player->status->elapsed >= 161) {
                    func_1506160C((u8 *)player, 2, 0, 60, 0);
                }
                if (player->status->elapsed >= 181 && player->status->state != 10) {
                    func_1507D4F8(i);
                }
            }
        }
        D_8008FDBC &= ~0x80;
    }
}
void func_15181D70(s32);
extern s32 D_80082FA0;
extern u8 D_800CC2D0;

void func_1507CD0C(void *arg0) {
    s32 temp_a1;
    s32 temp_lo;

    temp_a1 = (s32)((u32)arg0 - (u32)&D_800CC2D0);
    temp_lo = temp_a1 / 812;
    *(s8 *)(*(u8 **)((u8 *)arg0 + 0x31C) + 0x120) = 3;
    if (temp_lo <= D_80082FA0) {
        func_15181D70(temp_lo);
    }
}
typedef struct GameA9D90ActorState {
    u8 pad0[0x46];
    s16 field_46;
    u8 pad48[0xD8];
    u8 field_120;
    u8 field_121;
    u8 pad122[0x8A];
    u8 field_1AC;
} GameA9D90ActorState;

typedef struct GameA9D90Actor {
    s32 field_0;
    u8 kind;
    u8 field_5;
    u8 pad6[0xE];
    f32 x;
    f32 y;
    f32 z;
    f32 field_20;
    u8 pad24[0x17];
    u8 field_3B;
    f32 field_3C;
    f32 field_40;
    u8 pad44[0x21];
    u8 field_65;
    u8 pad66[0x23];
    u8 field_89;
    u8 pad8A[0x2E];
    f32 field_B8;
    u8 padBC[8];
    f32 field_C4;
    u8 padC8[0x1C];
    s16 field_E4;
    s16 field_E6;
    u8 padE8[0x10];
    s32 field_F8;
    u8 padFC[8];
    u8 field_104;
    u8 pad105[0x20];
    u8 field_125;
    u8 pad126;
    u8 field_127;
    u8 field_128;
    u8 pad129[0x13];
    u8 field_13C;
    u8 pad13D[0x8D];
    u8 field_1CA;
    u8 pad1CB[0x121];
    s32 field_2EC;
    u8 pad2F0[0x2C];
    GameA9D90ActorState *state;
    u8 pad320[8];
    u8 field_328;
} GameA9D90Actor;

void func_1504BAF0(void *);
void func_1505E650(void *, s32, f32, f32, f32, f32, s32);
void func_1507CD64(GameA9D90Actor *, s32);
void func_15085710(s32, s32, s32);
f32 func_150ADA68(void);
void func_150E7994(s16, f32, s32, s32);
void func_15169040(s32, u8);
extern void *D_800D154C;
extern u8 D_800D18A9;
extern s16 D_800E0AD0[];
extern s32 D_800BE9F0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507CD64 CURRENT (640) */
void func_1507CD64(GameA9D90Actor *arg0, s32 arg1) {
    GameA9D90ActorState *state;
    s32 sound;
    s32 flag;
    s32 mode;
    s32 restart;
    struct { void *object; u8 kind; } descriptor;
    void *saved;
    s32 slot;
    u32 random;
    f32 scale;

    state = arg0->state;
    if (state != NULL) {
        slot = ((u8 *)arg0 - &D_800CC2D0) / 812;
        if (slot < D_8008FD8C) {
            if (state->field_120 != 0) {
                if (arg1 != 9) {
                    return;
                }
                if (arg1 == state->field_121) {
                    return;
                }
                restart = 1;
            } else {
                restart = 0;
            }
            state->field_121 = arg1;
            if (D_800BE616 != 0 && restart == 0) {
                if (slot < 0x10) {
                    D_800E0AD0[slot]++;
                }
                if ((D_8008FDBC & 0x20) && arg0->field_128 == 0) {
                    func_15085710(1, 0xA, 1);
                }
            }
            descriptor.object = arg0;
            descriptor.kind = arg0->field_3B;
            func_15169040((s32)&descriptor, 3);
            D_800D18A9 = 0;
            sound = -1;
            flag = 0;
            mode = 0;
            if (arg0->state->field_1AC != 0) {
                D_800D18A9 = 2;
            }
            switch (arg1) {
            case 11:
                sound = 0x2D4;
                break;
            case 12:
                sound = 0x2D6;
                break;
            case 0:
                sound = 0x58;
                break;
            case 1:
                sound = 0x13;
                flag = 1;
                break;
            case 2:
                sound = 7;
                flag = 1;
                break;
            case 3:
                sound = 0x28;
                D_800D18A9 = 1;
                break;
            case 4:
                sound = 0x24;
                mode = 1;
                D_800D18A9 = 1;
                break;
            case 5:
                sound = 0x24;
                mode = 1;
                D_800D18A9 = 3;
                break;
            case 6:
                if (arg0->field_0 == 1 || arg0->field_0 == 0x15 || arg0->field_5 == 3 || arg0->field_65 != 0) {
                    sound = 0x170;
                }
                mode = 1;
                break;
            case 7:
                sound = 0x16F;
                break;
            case 8:
                sound = 0x170;
                mode = 1;
                D_800D18A9 = 3;
                break;
            case 15:
                sound = 0x170;
                mode = 3;
                D_800D18A9 = 3;
                break;
            case 9:
                mode = 2;
                break;
            case 10:
                sound = 0x2F;
                D_800D18A9 = 3;
                break;
            case 14:
                sound = 0x1E;
                mode = 1;
                break;
            case 13:
                sound = 0x2D8;
                mode = 1;
                break;
            case 16:
                sound = 0xF6;
                mode = 1;
                break;
            }
            if (sound != -1) {
                func_1505E650(arg0, sound & 0xFFFF, 1.0f, 3.0f, 0.0f, 0.0f, flag);
            }
            arg0->field_1CA = 0;
            arg0->field_125 = 0xFF;
            arg0->field_104 = 0xFF;
            arg0->field_89 = 0xFF;
            arg0->field_F8 |= 0x200;
            arg0->field_E4 = 0;
            arg0->field_E6 = 0;
            arg0->field_3C = 0.0f;
            arg0->state->field_46 = 0;
            if (arg0->field_13C != 0) {
                saved = D_800D154C;
                D_800D154C = arg0;
                func_1504BAF0(arg0);
                D_800D154C = saved;
            }
            if (mode == 0 || mode == 3) {
                arg0->state->field_120 = 1;
            } else {
                func_1507C8E0((GameA9D90Object *)arg0, 0);
            }
            if (mode == 2) {
                arg0->state->field_120 = 0xB;
            } else if (mode == 3) {
                func_1507D4F8(slot);
            }
            if (slot == 0 && D_800BE9F0 == 4) {
                random = func_150ADA20();
                scale = func_150ADA68() * 0.1f + 0.3f;
                func_150E7994((random % 3) + 4, scale, 0xFF, 0);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507CD64 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507CD64.s")
typedef struct GameA9D90EntityIdRecord {
    u8 field_0;
    u8 pad_1[0x32B];
} GameA9D90EntityIdRecord;

extern GameA9D90EntityIdRecord D_800CC40F[];
void func_1509BFB0(s32, s32, s32, s32, s32, s32);

void func_1507D158(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 temp_v0;

    temp_v0 = D_800CC40F[arg0].field_0;
    func_1509BFB0(3, temp_v0 | 0x2000, arg1, arg2, arg3, arg4);
}
void func_150054C4(u8 *, u32, s32, s32);
void func_15060F28(u8 *, s32);
void func_15085430(void *, s32, s32);
void func_15085710(s32, s32, s32);
s32 func_150859AC(s32, s32);
void func_15181DC8(s32);
void func_15082A44(s32, s32, s32, s32, s32);
void func_15088D58(GameA9D90Object *);
extern s16 D_800BE9F2;
extern s32 D_800BE9F0;
extern s32 D_800D20FC;
extern u8 *D_800DBFF0;
extern u8 D_800BE616;
extern u8 D_800D18A8;
extern s8 D_8008726C;

void func_1507D1D8(GameA9D90Object *arg0) {
    s32 value;
    s32 saved;
    s8 player;
    s8 state;
    s8 actorState;
    s8 mode;
    s32 choice;
    GameA9D90Inner *inner;
    s32 slot;
    union { s32 word; s16 halves[2]; } index;

    inner = arg0->field_31C;
    saved = *(s16 *)((u8 *)inner + 0x1AA);
    state = *(s8 *)((u8 *)inner + 0x1B0);
    actorState = *(s8 *)((u8 *)arg0 + 0x328);
    mode = *(s8 *)((u8 *)inner + 0x1AF);
    if (D_800BE616 != 0) {
        player = inner->pad0[0x11B];
    } else {
        player = -1;
    }
    if (D_800BE9F0 == 0x2B) {
        slot = ((u8 *)arg0 - &D_800CC2D0) / 812;
        index.word = (s16)slot;
        value = func_150859AC(index.word, 1);
        if (value >= 0x11 && value < 0x21) {
            choice = (func_150ADA20() & 0xF) + 0x11;
            func_15085710(index.halves[1], 0, choice);
            if (choice < 0x1D) {
                *(u8 *)(D_800D20FC + slot * 0x30 + 4) = 0x9C;
            } else {
                *(u8 *)(D_800D20FC + slot * 0x30 + 4) = 0x9D;
            }
        }
    }
    slot = ((u8 *)arg0 - &D_800CC2D0) / 812;
    index.word = slot * 0x30;
    func_15060F28((u8 *)arg0, 0);
    D_800D18A8 = 1;
    func_15082A44(index.word + D_800D20FC, slot, 0, 0, 0);
    *(s8 *)((u8 *)arg0->field_31C + 0x1B0) = state;
    *(s8 *)((u8 *)arg0->field_31C + 0x1AF) = mode;
    *(s8 *)((u8 *)arg0 + 0x328) = actorState;
    if (D_80082FA0 >= slot) {
        func_150054C4(slot * 0x9A0 + D_800DBFF0, slot, D_800BE9F2, (s8)player);
        func_15181DC8(slot);
        func_1517EE40(0, 0, 0, 0, 1, slot);
        func_1517EE40(0, 0, 0, 0x1E, 0, slot);
    } else {
        func_15085430(arg0, (s8)player, 0);
    }
    D_800D18A8 = 0;
    arg0->field_31C->field_120 = 0;
    arg0->field_31C->pad121[1] = 0;
    arg0->field_31C->field_124 = 0;
    *(s16 *)((u8 *)arg0->field_31C + 0x1AA) = saved;
    arg0->pad0[0x1CA] = D_8008726C;
    *(u16 *)((u8 *)arg0 + 0x22C) = *(u16 *)((u8 *)arg0 + 0x22C) | 0x100;
    arg0->field_31C->pad0[0x75] = 0;
    arg0->pad0[0x20F] = 0xFF;
    arg0->pad0[0x210] = 0xFF;
    arg0->pad0[0x211] = 0xFF;
    arg0->pad0[0x232] = 1;
    *(s32 *)((u8 *)arg0 + 0x218) = 0;
    arg0->field_31C->pad0[0x11B] = (s8)player;
    if (D_800BE616 != 0) {
        arg0->pad0[0x125] = 0x96;
        *(u8 *)((u8 *)arg0->field_31C + 0x1B1) = arg0->pad0[0x125];
        if (D_800BE9F0 == 0x33) {
            func_1507D158(slot, 0x78, 0, 0, 0);
            func_15088D58(arg0);
        }
    }
}
void func_1501C730(s32, s32, s32, s32, s32);
s32 func_150859AC(s32, s32);
void func_1509C3A0(void);
void func_1507D1D8(GameA9D90Object *);
void func_15085710(s32, s32, s32);
extern s8 D_80087260;
extern s8 D_8008726C;
extern s8 D_8008FD94;
extern s8 D_8008FDA8;
extern u16 D_8008FDBC;
extern u8 D_800BE616;
extern s8 D_800BE618;
extern u16 D_800D18A0;
extern s8 D_800D2E43;
extern u8 *D_800D2E4C;
extern s8 D_800E0C20;
extern s8 D_800BE3DF;
extern u8 D_800BE3E0;
extern u8 D_800D18A8;

void func_1507D4F8(s32 arg0) {
    GameA9D90Object *actor;
    GameA9D90Object *actor2;
    union {
        s32 word;
        s16 halves[2];
    } index;

    if (!(D_8008FDBC & 1)) {
        func_15085710((s16)arg0, 4, 1);
    }
    index.word = (s16)arg0;
    if (func_150859AC(index.word, 3) != 0) {
        func_15085710(index.halves[1], 5, D_8008726C);
        actor = (GameA9D90Object *)((s32)&D_800CC2D0 + arg0 * 0x32C);
        *(s16 *)((u8 *)actor + 0xB2) = 0;
        if (D_800BE616 != 0) {
            if (D_800E0C20 == 0) {
                func_1507D1D8(actor);
                return;
            }
            actor->field_31C->field_120 = 0xA;
            return;
        }
        D_800D18A8 = 1;
        if (!(D_800D2E4C[0x19] & 4) && D_8008FDA8 >= 0) {
            func_1501C730(1, 0x22, 0, 0, 0);
            return;
        }
        func_1501C730(2, D_800BE3DF, D_800BE3E0, 0, 0);
        return;
    }
    if (D_800BE616 == 0) {
        D_800D2E43 = 1;
        func_1509C3A0();
        D_800D18A8 = 1;
        func_15085710(index.halves[1], 5, D_8008726C);
        func_15085710(index.halves[1], 2, D_80087260);
        func_1501C730(1, 0x18, 0, 0, 0);
    } else {
        D_800D18A0 |= 1U << arg0;
    }
    actor2 = (GameA9D90Object *)((s32)&D_800CC2D0 + arg0 * 0x32C);
    if (actor2->field_31C->pad0[0x84] == 0) {
        D_8008FD94 -= 1;
    }
    actor2->field_31C->field_120 = 0xA;
    D_800BE618 -= 1;
}

typedef struct GameA9D90Spawn {
    f32 field_0;
    f32 field_4;
    f32 field_8;
    u8 padC[4];
    s16 x;
    s16 y;
    s16 z;
    u8 pad16[0x58];
    u8 field_6E;
    u8 pad6F[0xD];
    s32 field_7C;
    s32 field_80;
    s32 field_84;
    u8 pad88[2];
    u8 field_8A;
} GameA9D90Spawn;

void func_1507DB44(void *, s32);
s32 *func_1507515C(s32);
void func_150AEB9C(void *);
void func_150B0348(void *, s32, s32);
void func_150B7B40(void *, s32, s32);
void func_150BBB5C(void *);
void func_150BC488(void *);
void func_150BE494(void *, u8, s32);
void func_150BFFE0(void *);
void func_150D85AC(void *);
void func_150E0870(void *, s32, s32);
void func_150F1D10(u8 *, u8, s32);
void func_15136C3C(void *, s32, s32, s32, s32, s32, s32, s32);
void func_15145A50(u8 *);
void func_151A6C90(void *, s32, s32);
void func_151BA518(void *, s32, s32);
void func_151C9740(u8 *, s32, s32);
void func_151CFA4C(void *, s32, s32);
void func_151D22B0(void *, s32, s32);
extern u8 D_800C35EA;

s32 func_1507D754(GameA9D90Actor *arg0) {
    GameA9D90Spawn *spawn;
    s32 *target;

    switch (arg0->kind) {
    case 0x7F:
        func_150B0348(arg0, 0xFF, 1);
        break;
    case 0x10:
    case 0x38:
    case 0x91:
        func_150BFFE0(arg0);
        break;
    case 0x3A:
    case 0x3D:
        func_150D85AC(arg0);
        break;
    case 0x4A:
        func_150F1D10((u8 *)arg0, 0xFF, 1);
        break;
    case 0x47:
        func_151C9740((u8 *)arg0, 0xFF, 1);
        break;
    case 0x25:
        if (arg0->field_2EC != 0 || D_800BE9F0 == 6 || D_800BE9F0 == 0x3B) {
            func_151CFA4C(arg0, 0xFF, 1);
        }
        return 0;
    case 0x79:
        func_150BE494(arg0, 0xFF, 1);
        break;
    case 0x5:
    case 0xAD:
    case 0xAE:
    case 0xAF:
        arg0->field_328 = 0;
        func_1507DB44(arg0, 0);
        func_150AEB9C(arg0);
        return 1;
    case 0x53:
        if (D_800BE616 != 0) {
            func_1507CD64(arg0, 0xA);
            return 2;
        }
        break;
    case 0x90:
        if (D_800BE616 != 0 && D_800BE9F0 == 0x33) {
            func_1507CD64(arg0, 8);
            return 2;
        }
        break;
    case 0x28:
    case 0x77:
        spawn = NULL;
        func_151BA518(arg0, 0xFF, 1);
        func_15145A50((u8 *)arg0);
        if (D_800BE616 != 0) {
            func_1507CD64(arg0, 6);
            spawn = func_151149AC(arg0->field_127 + 0xB);
        } else {
            if (D_800BE9F0 == 0x23) {
                spawn = func_151149AC(1);
            }
            target = func_1507515C((s32)arg0);
            if (target != NULL && D_800C35EA != 1) {
                func_15136C3C(target, 1, 1, 1, 1, 0, 0xFF, 1);
            }
        }
        if (spawn != NULL) {
            spawn->field_6E = 0;
            spawn->x = arg0->x;
            spawn->y = arg0->y;
            spawn->z = arg0->z;
            spawn->field_0 = arg0->field_B8;
            spawn->field_4 = arg0->field_40;
            spawn->field_8 = arg0->field_C4;
            spawn->field_8A = 0xFF;
            spawn->field_7C = 0;
            spawn->field_80 = 0;
            spawn->field_84 = 0;
        }
        if (D_800BE616 != 0) {
            return 2;
        }
        break;
    case 0xD:
        func_150B7B40(arg0, 0xFF, 1);
        break;
    case 0x20:
        if (arg0->field_20 < -20.0f) {
            func_150BC488(arg0);
        } else {
            func_150BBB5C(arg0);
        }
        break;
    case 0x4F:
    case 0x83:
        func_151A6C90(arg0, 0xFF, 1);
        break;
    case 0x34:
        func_150E0870(arg0, 0xFF, 1);
        break;
    case 0x44:
        func_151D22B0(arg0, 0xFF, 1);
        break;
    }
    return 0;
}

void func_1507DB34(void) {
}

void func_1507DB3C(void) {
}

void func_1507DB44(void *arg0, s32 arg1) {
    func_1503DE70(arg0, arg1, -1);
}

void func_1507DB64(void) {
}
typedef struct { u32 first, second; } GameA9D90Command;

s32 func_1510D0EC(s32, s32 *, s32, s32);
void func_15181DC8(s32);
extern u8 D_80086B80[];
extern u8 D_D0F;
extern s32 D_800BE628;
extern u16 D_800D18A2;
extern u8 D_800D18A4[];

#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507DB6C CURRENT (5190) */
GameA9D90Command *func_1507DB6C(GameA9D90Command *arg0, s32 arg1) {
    s32 texture;
    u8 level;
    u8 *levelByte;
    u8 *viewport;
    u32 flags, bit;
    u16 *flagWord;
    s32 centerX, centerY;
    register s32 radius;
    s32 right, left, bottom, top;

    { GameA9D90Command *command = arg0++; command->first = 0xDE000000; command->second = (u32)D_80086B80; }
    texture = func_1510D0EC((s32)&D_D0F, 0, 3, 0);
    { GameA9D90Command *command = arg0++; command->first = 0xFD180000; command->second = texture; }
    { GameA9D90Command *command = arg0++; command->first = 0xF5180000; command->second = 0x07080200; }
    { GameA9D90Command *command = arg0++; command->first = 0xE6000000; command->second = 0; }
    { GameA9D90Command *command = arg0++; command->first = 0xF3000000; command->second = 0x073FF000; }
    { GameA9D90Command *command = arg0++; command->first = 0xE7000000; command->second = 0; }
    { GameA9D90Command *command = arg0++; command->first = 0xF5181000; command->second = 0x00080200; }
    { GameA9D90Command *command = arg0++; command->first = 0xF2000000; command->second = 0x0007C07C; }
    { GameA9D90Command *command = arg0++; command->first = 0xEF002C3F; command->second = 0x0F0A4004; }
    flagWord = (u16 *)(u32)&D_800D18A2;
    flags = *flagWord;
    bit = 1U << arg1;
    if (flags & bit) {
        levelByte = D_800D18A4 + arg1;
        level = *levelByte;
        if (level >= 4) {
            *levelByte = level - 4;
            level = (u8)(level - 4);
            goto draw;
        }
        *flagWord = flags & ~bit;
        func_15181DC8(arg1);
        func_1517EE40(0, 0, 0, 120, 0, arg1);
        return arg0;
    } else {
        levelByte = D_800D18A4 + arg1;
        level = (u8)(*levelByte + 4);
        *levelByte = level;
        if (level >= 61) {
            *levelByte = 60;
            level = 60;
        }
    }
draw:
    viewport = (u8 *)D_800BE628 + arg1 * 0x180;
    centerX = (s32)(*(f32 *)(viewport + 0x2C) + *(f32 *)(viewport + 0x30)) * 2;
    centerY = (s32)(*(f32 *)(viewport + 0x24) + *(f32 *)(viewport + 0x28)) * 2;
    radius = level + 4;
    left = centerX - radius;
    right = centerX + radius;
    top = centerY - radius;
    bottom = centerY + radius;
    { GameA9D90Command *command = arg0++; command->first = _SHIFTL(0xE4, 24, 8) | _SHIFTL(right, 12, 12) | _SHIFTL(bottom, 0, 12); command->second = _SHIFTL(0, 24, 3) | _SHIFTL(left, 12, 12) | _SHIFTL(top, 0, 12); } { GameA9D90Command *command = arg0++; command->first = _SHIFTL(0xE1, 24, 8); command->second = _SHIFTL(0, 16, 16) | _SHIFTL(0, 0, 16); } { GameA9D90Command *command = arg0++; command->first = _SHIFTL(0xF1, 24, 8); command->second = _SHIFTL(0x20000 / (right - left), 16, 16) | _SHIFTL(0x20000 / (right - left), 0, 16); }
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507DB6C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507DB6C.s")
void func_150836CC(void *, s32);

void func_1507DE4C(void *arg0) {
    s32 temp_v0;

    if (*(s32 *)arg0 == 1) {
        func_150836CC(arg0, 0x44);
        func_150836CC(arg0, 0x23);
        *(s32 *)((u8 *)arg0 + 0x9C) |= 0xF000;
        func_150836CC(arg0, 0x44);
        func_150836CC(arg0, 0x23);
        return;
    }
    temp_v0 = *(u8 *)((u8 *)arg0 + 4);
    if ((temp_v0 != 0x5A) && (temp_v0 != 0x74) && (temp_v0 != 0x7A)) {
        if ((temp_v0 == 0x9F) || (temp_v0 == 0xA0)) {
            *(s32 *)((u8 *)arg0 + 0x9C) |= 0xF000;
        }
    } else {
        *(s32 *)((u8 *)arg0 + 0x9C) |= 0xFF8;
    }
}
void func_1507DF10(void *arg0, s32 arg1) {
    switch (arg1) {
    case 9:
        *(s32 *)((u8 *)arg0 + 0x94) = (s32) (*(s32 *)((u8 *)arg0 + 0x94) | 0x20);
        *(s32 *)((u8 *)arg0 + 0x9C) = (s32) (*(s32 *)((u8 *)arg0 + 0x9C) | 0x78);
        *(s32 *)((u8 *)arg0 + 0x2E4) = 1;
        return;
    case 8:
        *(s32 *)((u8 *)arg0 + 0x94) |= 0x40;
        *(s32 *)((u8 *)arg0 + 0x94) &= ~0x200;
        *(s32 *)((u8 *)arg0 + 0x9C) = (s32) (*(s32 *)((u8 *)arg0 + 0x9C) | 0xF00);
        *(s32 *)((u8 *)arg0 + 0x2E4) = 2;
        return;
    case 6:
    case 7:
        *(s32 *)((u8 *)arg0 + 0x94) |= 0xE;
        *(s32 *)((u8 *)arg0 + 0x94) &= ~0x410;
        *(s32 *)((u8 *)arg0 + 0x9C) = (s32) (*(s32 *)((u8 *)arg0 + 0x9C) | 0xEE0000);
        *(s32 *)((u8 *)arg0 + 0x2E4) = 4;
        return;
    case 4:
    case 5:
        *(s32 *)((u8 *)arg0 + 0x94) |= 0x80;
        *(s32 *)((u8 *)arg0 + 0x94) &= ~0x500;
        *(s32 *)((u8 *)arg0 + 0x2E4) = 8;
        /* fallthrough */
    default:
        return;
    }
}
void func_1501D348(s32, s32, s32, u8, s32);
void func_15022190(s16, s16, s16, f32);
void func_15084D70(s32, s32, s32, void *, void *, void *, void *, void *, void *, s32, s32 *);
extern s32 D_800BE9F0;
extern u8 D_800C35EA;
extern s8 D_800C3670;
extern s8 D_800C3671;

void func_1507DFE4(s32 arg0, s32 arg1) {
    s32 sp64;
    s16 sp5C[3];
    u8 sp50[12];
    u8 sp4F;
    u8 sp4E;
    s32 sp48;
    s32 sp44;
    f32 angle;
    s32 sp3C;
    s32 sp38;

    if (D_800C35EA != 1) {
        func_15084D70(0, arg0, 1, sp5C, sp50, &sp4F, &sp4E,
                      &sp44, &sp48, 1, &sp38);
        angle = ((f32)(sp4E - 0x40) * 1.40625f) + 180.0f;
        if (sp38 == 0) {
            sp3C = 1;
            goto play;
        }
        if (sp38 == 1) {
            sp3C = 3;
play:
            func_15022190(sp5C[0], sp5C[1], sp5C[2], angle);
            sp64 = D_800BE9F0;
            D_800BE9F0 = 0x25;
            D_800C3671 = 1;
            func_1501D348(0x25, sp3C, 0, 0, 0);
            D_800C3670 = 1;
            D_800BE9F0 = sp64;
        }
    }
}
extern s8 D_800BE3DF;
extern u8 D_800BE3E0;
extern s32 D_800BE9F4;
extern u8 D_800D18A8;

s32 func_1507E114(s32 arg0) {
    s32 sp5C;
    u8 sp54[8];
    u8 sp48[12];
    s32 sp44;
    u8 sp43;
    u8 sp42;
    u8 sp3C[6];

    if (D_800D18A8 == 0) {
        return 0;
    }
    if ((D_800BE9F4 == 0x22) || (D_800BE9F4 == 0x18)) {
        return 0;
    }
    D_800BE9F4 = D_800BE3DF;
    func_15084D70(0, D_800BE3E0, 1, &sp54, &sp48, &sp43, &sp42, &sp44, &sp3C, 1, &sp5C);
    return sp5C + 1;
}

void func_15143134(f32 *, f32 *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507E1D0 CURRENT (300) */
void func_1507E1D0(void *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    if (*(s32 *)((u8 *)arg0 + 0x1D4) != 0) {
        s32 var_a2;
        Vec3f input;
        Vec3f output;

        input.x = 0.0f;
        input.y = *(f32 *)((u8 *)arg0 + 0x150) * 30.0f;
        input.z = 0.0f;
        var_a2 = *(s32 *)((u8 *)arg0 + 0x1D4);
        if (*(s32 *)arg0 == 1) {
            var_a2 += 0x300;
        } else if (*(s32 *)arg0 == 0x1E) {
            var_a2 += 0xC0;
        }
        func_15143134(&input.x, &output.x, var_a2);
        *arg1 = output.x;
        *arg2 = output.y;
        *arg3 = output.z;
    } else {
        *arg1 = *(f32 *)((u8 *)arg0 + 0x14);
        *arg2 = *(f32 *)((u8 *)arg0 + 0x18);
        *arg3 = *(f32 *)((u8 *)arg0 + 0x1C);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507E1D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507E1D0.s")
