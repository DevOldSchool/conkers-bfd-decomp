#include "types.h"

/*
 * Reviewed source unit: src/game/game_C3E20.c
 * Boundary evidence: docs/evidence/game_raw_record_command_controller.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15096A68
 * - func_15096D78
 * - func_1509759C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_100226F0(void *arg0, s32 arg1);
extern u8 D_800D2DC0;
extern s32 D_800D2DB4;

void func_15096970(void) {
    func_100226F0(&D_800D2DC0, 0x6C);
    D_800D2DB4 = 0;
}

s32 func_150969A0(s32 arg0) {
    struct Entry {
        u8 flag;
        u8 rest[0x23];
    };
    s32 i;

    for (i = 0; i < arg0; i++) {
        if (((struct Entry *)&D_800D2DC0)[i].flag != 0) {
            return 1;
        }
    }
    return 0;
}
typedef struct GameC3E20Command {
    u8 state, actor, pose, unknown3;
    s16 timer;
    u8 unknown6[6];
    s32 flags;
    f32 duration;
    u8 unknown14[0xC];
    f32 finalSpeed;
} GameC3E20Command;

typedef struct GameC3E20Pose {
    s16 x, y, z;
    u8 unknown6[6];
    f32 valueC, value10, value14;
} GameC3E20Pose;

typedef struct GameC3E20Child {
    u8 unknown0[7];
    u8 mode;
    u8 unknown8[0x1C2];
    u8 active;
    u8 unknown1CB[0x91];
    s32 flags;
} GameC3E20Child;

typedef struct GameC3E20Actor {
    u8 unknown0[0x2C0];
    f32 value;
    u8 unknown2C4[0xE0];
    f32 speed;
    u8 unknown3A8[0x28];
    GameC3E20Child *child;
} GameC3E20Actor;

typedef struct GameC3E20Packet {
    s32 enabled, state;
    f32 time;
    u8 unknownC[8];
    f32 x, y, z;
    f32 value20, value24, value28;
} GameC3E20Packet;

void func_1512D560(void *, s32, s32);
extern u8 *D_800DBFF0;
extern s32 D_800DC020;
extern s32 D_800D2E30[];
extern u8 D_800BE9A0;
extern u8 D_800DBFF4[];
extern f32 D_800D2DB8;
extern GameC3E20Packet D_800C3600;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15096A68 CURRENT (4205) */
s32 func_15096A68(s32 arg0) {
    GameC3E20Command *entry;
    GameC3E20Pose *pose;
    s32 actorIndex;
    s32 flags;

    entry = (GameC3E20Command *)(&D_800D2DC0 + arg0 * 0x24);
    switch (entry->state) {
    case 1: {
        GameC3E20Actor *actor;
        s32 poseIndex;
        actorIndex = entry->actor;
        poseIndex = entry->pose;
        actor = (GameC3E20Actor *)(D_800DBFF0 + actorIndex * 0x9A0);
        D_800D2DB8 = actor->value;
        D_800D2DB4 = 1;
        D_800DBFF4[actorIndex] = 3;
        D_800C3600.enabled = 1;
        D_800C3600.state = 0;
        pose = (GameC3E20Pose *)(D_800DC020 + poseIndex * 0x18);
        D_800C3600.x = (f32)pose->x;
        D_800C3600.y = (f32)pose->y;
        D_800C3600.z = (f32)pose->z;
        D_800C3600.value20 = pose->value14;
        D_800C3600.value24 = pose->valueC;
        D_800C3600.time = 0.0f;
        D_800C3600.value28 = pose->value10;
        func_1512D560(actor, 5, 0);
        func_1512D560(actor, 7, (s32)&D_800C3600);
        if (!(entry->flags & 1)) {
            actor->child->mode = 0;
            actor->child->flags |= 0x200;
        }
        D_800D2E30[arg0] = (s32)entry->duration;
        entry->state = 2;
        return 1;
    }
    case 2: {
        GameC3E20Actor *actor;
        entry->timer -= D_800BE9A0;
        actor = (GameC3E20Actor *)(D_800DBFF0 + entry->actor * 0x9A0);
        if (actor->child->active == 0) {
            entry->timer = 0;
        }
        if (entry->timer <= 0) {
            actor->speed = entry->finalSpeed;
            flags = entry->flags;
            if (!(flags & 2)) {
                func_1512D560(actor, 6, 0);
                flags = entry->flags;
            }
            D_800D2DB4 = 0;
            if (!(flags & 1)) {
                actor->child->flags &= ~0x200;
                actor->child->mode = 0xFF;
            }
            entry->timer = 0;
            entry->state = 0;
            actor->value = D_800D2DB8;
            return 0;
        }
        break;
    }
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15096A68 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C3E20/func_15096A68.s")

s32 func_15096A68(s32);                             /* extern */
extern u8 D_800C35EA;
extern u8 D_800D2DC0;

void func_15096D08(void) {
    s32 var_s0;
    u8 *var_s1;

    var_s0 = 0;
    if (D_800C35EA != 1) {
        var_s1 = &D_800D2DC0;
loop_2:
        if (*var_s1 != 0) {
            if (func_15096A68(var_s0) == 0) {
                goto block_6;
            }
            return;
        }
block_6:
        var_s0 += 1;
        var_s1 += 0x24;
        if (var_s0 == 3) {

        } else {
            goto loop_2;
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_C3E20/func_15096D78.s")
typedef struct GameC3E20View {
    u8 pad0[0x2A4];
    f32 firstX;
    f32 firstY;
    f32 firstZ;
    u8 pad2B0[0x48];
    f32 secondX;
    f32 secondY;
    f32 secondZ;
    u8 pad304[0x78];
    f32 value37C;
    u8 pad380[0x10];
    f32 value390;
    u8 pad394[8];
    f32 angle;
} GameC3E20View;

f32 func_15047D60(f32);
f32 func_15047C00(f32);
void func_15048F90(void *, void *, void *);
f32 func_150AD900(f32 *, f32 *);
u8 *func_1505EEF4(s32);
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
extern u8 *D_800DBFF0;
extern s32 D_80082FA0;
extern f32 D_8009DF4C;
extern s32 D_800DC020;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509759C CURRENT (562) */
s32 func_1509759C(s32 arg0, s32 arg1, s32 *arg2) {
    GameC3E20View *view;
    f32 direction[3];
    f32 offset[3];
    f32 angle;
    u8 *actor;
    f32 dx;
    f32 dz;
    s16 *point;
    s32 result;

    view = (GameC3E20View *)(D_800DBFF0 + arg0 * 0x9A0);
    if (D_80082FA0 < arg0) return 0;
    switch (arg1) {
    case 31:
        return (s32)(view->value390 * 65536.0f);
    case 30:
        return (s32)(view->value37C * 65536.0f);
    case 29:
        return (&D_800D2DC0)[arg2[2] * 0x24];
    case 32:
        point = (s16 *)((arg2[2] & 0xFFF) * 0x18 + D_800DC020);
        dx = view->secondX - (f32)point[0];
        dz = view->secondZ - (f32)point[2];
        return (s32)sqrtf(dx * dx + dz * dz);
    case 33:
        actor = func_1505EEF4(arg2[2] & 0xFFF);
        if (actor == 0) return -1;
        angle = view->angle + D_8009DF4C;
        direction[0] = func_15047D60(angle);
        direction[1] = 0.0f;
        direction[2] = func_15047C00(angle);
        func_15048F90(&view->secondX, actor + 0x14, offset);
        offset[1] = 0.0f;
        result = 1;
        if (func_150AD900(direction, offset) >= 0.0f) return -1;
        return result;
    default:
        return 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509759C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C3E20/func_1509759C.s")



void func_15048F90(void *, void *, void *);
void func_1504917C(void *, void *);
extern u8 *D_800DBFF0;
extern s32 D_800D2E30[];

void func_15097798(s32 arg0) {
    GameC3E20View *view;
    f32 direction[5];

    view = (GameC3E20View *)(D_800DBFF0 + arg0 * 0x9A0);
    if (D_800D2DB4 != 0) {
        func_15048F90(&view->firstX, &view->secondX, direction + 2);
        func_1504917C(direction + 2, direction + 2);
        view->firstX += direction[2] * -2.5f * (f32)D_800D2E30[arg0];
        view->firstY += direction[3] * -2.0f * (f32)D_800D2E30[arg0];
        view->firstZ += direction[4] * -2.5f * (f32)D_800D2E30[arg0];
        view->secondX += direction[2] * -2.5f * (f32)D_800D2E30[arg0];
        view->secondY += direction[3] * -2.0f * (f32)D_800D2E30[arg0];
        view->secondZ += direction[4] * -2.5f * (f32)D_800D2E30[arg0];
    }
}
