#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_A9D90.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1507C8FC
 * - func_1507CD0C
 * - func_1507CD64
 * - func_1507D1D8
 * - func_1507D4F8
 * - func_1507D754
 * - func_1507DB6C
 * - func_1507DFE4
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507C8FC.s")
void func_15181D70(s32, s32);
extern s32 D_80082FA0;
extern u8 D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507CD0C CURRENT (35) */
void func_1507CD0C(void *arg0) {
    s32 temp_a1;
    s32 temp_lo;

    temp_a1 = (u8 *)arg0 - &D_800CC2D0;
    temp_lo = temp_a1 / 812;
    *(s8 *)(*(u8 **)((u8 *)arg0 + 0x31C) + 0x120) = 3;
    if (temp_lo <= D_80082FA0) {
        func_15181D70(temp_lo, temp_a1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507CD0C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507CD0C.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507D1D8.s")
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507D4F8 CURRENT (879) */
void func_1507D4F8(s32 arg0) {
    union {
        s32 word;
        s16 halves[2];
    } index;
    GameA9D90Object *actor;
    u8 *actor2;

    if (!(D_8008FDBC & 1)) {
        func_15085710((s16)arg0, 4, 1);
    }
    index.word = (s16)arg0;
    if (func_150859AC(index.word, 3) != 0) {
        func_15085710(index.halves[1], 5, D_8008726C);
        actor = (GameA9D90Object *)(&D_800CC2D0 + arg0 * 0x32C);
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
    actor2 = &D_800CC2D0 + arg0 * 0x32C;
    if ((*(u8 **)(actor2 + 0x31C))[0x84] == 0) {
        D_8008FD94 -= 1;
    }
    (*(u8 **)(actor2 + 0x31C))[0x120] = 0xA;
    D_800BE618 -= 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507D4F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507D4F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507D754.s")
void func_1503DE70(void *arg0, s32 arg1, s32 arg2);

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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507DB6C CURRENT (7590) */
void *func_1507DB6C(register void *arg0, s32 arg1) {
    s32 texture;
    u8 level;
    u8 *levelByte;
    u8 *viewport;
    u32 flags, bit;
    u16 *flagWord;
    s32 centerX, centerY;
    register s32 radius;
    s32 right, left, bottom, top;
    s32 step;

    {
        GameA9D90Command *command0;

        command0 = (GameA9D90Command *)arg0;
        arg0 = (u8 *)arg0 + 8;
        command0->first = 0xDE000000;
        command0->second = (u32)D_80086B80;
    }
    texture = func_1510D0EC((s32)&D_D0F, 0, 3, 0);
    {
        GameA9D90Command *command1;

        command1 = (GameA9D90Command *)arg0;
        arg0 = (u8 *)arg0 + 8;
        command1->first = 0xFD180000;
        command1->second = texture;
    }
    {
        GameA9D90Command *command2;

        command2 = (GameA9D90Command *)arg0;
        arg0 = (u8 *)arg0 + 8;
        command2->first = 0xF5180000;
        command2->second = 0x07080200;
    }
    {
        GameA9D90Command *command3;

        command3 = (GameA9D90Command *)arg0;
        arg0 = (u8 *)arg0 + 8;
        command3->first = 0xE6000000;
        command3->second = 0;
    }
    {
        GameA9D90Command *command4;

        command4 = (GameA9D90Command *)arg0;
        arg0 = (u8 *)arg0 + 8;
        command4->first = 0xF3000000;
        command4->second = 0x073FF000;
    }
    {
        GameA9D90Command *command5;

        command5 = (GameA9D90Command *)arg0;
        arg0 = (u8 *)arg0 + 8;
        command5->first = 0xE7000000;
        command5->second = 0;
    }
    {
        GameA9D90Command *command6;

        command6 = (GameA9D90Command *)arg0;
        arg0 = (u8 *)arg0 + 8;
        command6->first = 0xF5181000;
        command6->second = 0x00080200;
    }
    {
        GameA9D90Command *command7;

        command7 = (GameA9D90Command *)arg0;
        arg0 = (u8 *)arg0 + 8;
        command7->first = 0xF2000000;
        command7->second = 0x0007C07C;
    }
    {
        GameA9D90Command *command8;

        command8 = (GameA9D90Command *)arg0;
        arg0 = (u8 *)arg0 + 8;
        command8->first = 0xEF002C3F;
        command8->second = 0x0F0A4004;
    }
    flagWord = &D_800D18A2;
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
    {
        GameA9D90Command *command9;
        GameA9D90Command *command10;
        GameA9D90Command *command11;

        command9 = (GameA9D90Command *)arg0;
        arg0 = (u8 *)arg0 + 8;
        command10 = (GameA9D90Command *)arg0;
        arg0 = (u8 *)arg0 + 8;
        left = centerX - radius;
        right = centerX + radius;
        top = centerY - radius;
        bottom = centerY + radius;
        command9->first = ((right & 0xFFF) << 12) | 0xE4000000 | (bottom & 0xFFF);
        command9->second = ((left & 0xFFF) << 12) | (top & 0xFFF);
        command10->first = 0xE1000000;
        command10->second = 0;
        step = (0x20000 / (right - left)) & 0xFFFF;
        command11 = (GameA9D90Command *)arg0;
        arg0 = (u8 *)arg0 + 8;
        command11->first = 0xF1000000;
        command11->second = (step << 16) | step;
    }
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
void func_15084D70(s32, u8, s32, void *, void *, void *, void *, void *, void *, s32, s32 *);
extern s32 D_800BE9F0;
extern u8 D_800C35EA;
extern s8 D_800C3670;
extern s8 D_800C3671;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507DFE4 CURRENT (487) */
void func_1507DFE4(u8 arg0, s32 arg1) {
    s32 sp64;
    s16 sp5C[3];
    u8 sp50[12];
    u8 sp4F;
    u8 sp4E;
    s32 sp48;
    s32 sp44;
    s32 sp3C;
    s32 sp38;
    f32 angle;

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
#endif /* CONKER_DEFERRED_CANDIDATE func_1507DFE4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507DFE4.s")
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
typedef struct GameA9D90Vec3 {
    f32 x;
    f32 y;
    f32 z;
} GameA9D90Vec3;

void func_15143134(f32 *, f32 *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507E1D0 CURRENT (975) */
void func_1507E1D0(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    struct {
        GameA9D90Vec3 output;
        GameA9D90Vec3 input;
    } local;
    s32 temp_v0;
    s32 var_a2;

    if (*(s32 *)(arg0 + 0x1D4) != 0) {
        local.input.x = 0.0f;
        local.input.z = 0.0f;
        local.input.y = *(f32 *)(arg0 + 0x150) * 30.0f;
        temp_v0 = *(s32 *)arg0;
        var_a2 = *(s32 *)(arg0 + 0x1D4);
        if (temp_v0 == 1) {
            var_a2 += 0x300;
        } else if (temp_v0 == 0x1E) {
            var_a2 += 0xC0;
        }
        func_15143134(&local.input.x, &local.output.x, var_a2);
        *arg1 = local.output.x;
        *arg2 = local.output.y;
        *arg3 = local.output.z;
        return;
    }
    *arg1 = *(f32 *)(arg0 + 0x14);
    *arg2 = *(f32 *)(arg0 + 0x18);
    *arg3 = *(f32 *)(arg0 + 0x1C);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507E1D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507E1D0.s")
