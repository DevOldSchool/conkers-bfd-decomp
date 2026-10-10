#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_131F30.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15104A80
 * - func_15104C44
 * - func_151050B0
 * - func_1510558C
 * - func_15105848
 * - func_151058B4
 * - func_15105C24
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game131F30Choices {
    u8 bytes[9];
} Game131F30Choices;

typedef struct Game131F30Request {
    s32 count;
    Game131F30Choices *choices;
    void *selected;
} Game131F30Request;

void func_151494E0(s32, u8);
extern Game131F30Choices D_800A2380;
extern Game131F30Choices D_800A238C;
extern Game131F30Choices D_800A2398;
extern u8 D_800CC2D0[];
extern u8 *D_800DBEF4;
extern s32 *D_800DBF94;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15104A80 CURRENT (4055) */
void func_15104A80(void *arg0) {
    u8 *selected;
    u8 *cursor;
    s32 mask;
    s32 index;
    Game131F30Request request;
    Game131F30Choices choicesF9;
    Game131F30Choices choicesF8;
    Game131F30Choices choicesF7;
    void *single;
    u8 kind;

    selected = 0;
    mask = D_800DBF94[((s32)arg0 - (s32)D_800DBEF4) / 160];
    index = 0;
    if (mask != 0) {
        cursor = D_800CC2D0 + index * 0x2EC;
        do {
            if ((*(s32 *)cursor != 0) && (mask & (1 << index))) {
                selected = cursor;
            }
            index++;
            cursor += 0x32C;
        } while ((index < 0x19) && (selected == 0));
    }
    kind = *((u8 *)arg0 + 0x72);
    if ((kind == 0xF9) || (kind == 0xF8) || (kind == 0xF7)) {
        request.selected = selected;
        kind = *((u8 *)arg0 + 0x72);
        if (kind == 0xF9) {
            choicesF9 = D_800A2380;
            request.count = 9;
            request.choices = &choicesF9;
        } else if (kind == 0xF8) {
            choicesF8 = D_800A238C;
            request.count = 9;
            request.choices = &choicesF8;
        } else if (kind == 0xF7) {
            choicesF7 = D_800A2398;
            request.count = 9;
            request.choices = &choicesF7;
        }
        func_151494E0((s32)&request, 0x35);
        return;
    }
    if (kind == 0xF6) {
        single = selected;
        func_151494E0((s32)&single, 0x38);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15104A80 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/func_15104A80.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/func_15104C44.s")
u16 func_1000FA64(u16, s16, s16, s16, s32, u16, s16, s32, void *, s32, s32, s32);
s32 func_1000FD38();
s32 D_1000EF40();

typedef struct struct205 { u8 pad0[0x14]; u8 unk14; } struct205;
typedef struct struct206 { struct205 *unk0; u16 unk4; u8 pad6[0x6]; u8 unkC; u8 padD[0x63]; s32 *unk70; } struct206;
typedef struct struct207 { u8 pad0[0x28]; struct206 *unk28; } struct207;

void func_15104FF8(struct207 *arg0, s32 arg1, u8 arg2) {
    struct206 *m = &arg0->unk28;
    if ((arg2 == 0x38) && (m->unk0->unk14 == 1)) {
        *(s16 *)((u8 *)m + 8) = 300;
        func_1000FD38(D_1000EF40, (struct205 *)((s32)m->unk0), 0);
        func_1000FA64(
            0x236,
            ((s16 *)m->unk0)[0],
            ((s16 *)m->unk0)[1],
            ((s16 *)m->unk0)[2],
            0x4000,
            0x5DC,
            0x3E8,
            (s32)D_1000EF40,
            m->unk0,
            0,
            8,
            0);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/func_151050B0.s")

void func_1510550C(s32 arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x4B) {
        func_1516972C((u8 *)arg0);
    }
}
void func_15105548(void *arg0, s32 *arg1, u8 arg2) {
    void *temp_v0;

    temp_v0 = (u8 *)arg0 + 0x28;
    if ((arg2 == 0x38) && (*(u8 *)((u8 *)(*(void **)temp_v0) + 0x14) == 1)) {
        *(s32 *)((u8 *)temp_v0 + 0x70) = *arg1;
        *(s16 *)((u8 *)temp_v0 + 4) = 0x12C;
    }
}
typedef struct Game131F30Vector { f32 x, y, z; } Game131F30Vector;
typedef struct Game131F30Surface { s16 values[9]; } Game131F30Surface;
typedef struct Game131F30Color { s32 value; } Game131F30Color;
typedef struct Game131F30Factor { f32 value; } Game131F30Factor;
typedef struct Game131F30Descriptor {
    s32 count, spread;
    Game131F30Vector position, velocity;
    Game131F30Surface surface;
    u8 pad32[2];
    f32 field34, field38, field3C, field40, field44;
    s16 duration, durationRange;
    f32 field4C, field50, field54;
} Game131F30Descriptor;
typedef struct Game131F30Part {
    u8 pad0[0x30];
    Game131F30Vector position;
    u8 pad3C[0x24];
    Game131F30Vector velocity;
    Game131F30Surface surface;
    u8 pad7E[0xA];
    s32 flags;
} Game131F30Part;
typedef struct Game131F30Emitter {
    u8 pad0, group, pad2[0xA], mode, padD[0x103];
    Game131F30Part part;
} Game131F30Emitter;

s32 func_15102920(f32, s32, void *, void *, s32, s32, s32, s32, s32, s32);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_151C329C(void *, u8, s32);
void func_15151D6C(Game131F30Descriptor *, Game131F30Color *, Game131F30Factor *, s32, u8, s32);
extern Game131F30Color D_800A23A4;
extern Game131F30Factor D_800A23A8;
extern f32 D_800A23C0, D_800A23C4, D_800A23C8, D_800A23CC, D_800A23D0;
extern f32 D_800A23D4, D_800A23D8, D_800A23DC, D_800A23E0, D_800A23E4, D_800A23E8;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510558C CURRENT (335) */
void func_1510558C(Game131F30Emitter *arg0) {
    register Game131F30Part *part;
    register u32 flags;
    struct {
        Game131F30Factor factor;
        Game131F30Color color;
        Game131F30Descriptor descriptor;
    } work;
    u32 random;
    f32 fraction;
    Game131F30Vector *position;
    Game131F30Surface *surface;

    fraction = func_150ADA68();
    random = func_150ADA20();
    part = (Game131F30Part *)((u8 *)arg0 + 0x110);
    surface = &part->surface;
    position = &part->position;
    func_15102920(fraction * 25.0f + 15.0f, ((random % 56U) + 0xC8) & 0xFF,
                  surface, position, func_150ADA20() % 81U + 0x32, 1, 1,
                  part->flags, arg0->mode, arg0->group);
    flags = part->flags;
    if ((flags & 0x1F) == 9) {
        if (func_150ADA68() < D_800A23C0) {
            func_151C329C(position, arg0->mode, arg0->group);
        }
    } else {
        if (func_150ADA68() < D_800A23C4) {
            func_151C329C(position, arg0->mode, arg0->group);
        }
        if (func_150ADA68() < D_800A23C8) {
            work.color = D_800A23A4;
            work.factor = D_800A23A8;
            work.descriptor.count = 1;
            work.descriptor.spread = 3;
            work.descriptor.position = *position;
            work.descriptor.velocity.x = -part->velocity.x;
            work.descriptor.velocity.y = -part->velocity.y;
            work.descriptor.velocity.z = -part->velocity.z;
            work.descriptor.surface = *surface;
            work.descriptor.field34 = D_800A23CC;
            work.descriptor.field38 = D_800A23D0;
            work.descriptor.duration = 15;
            work.descriptor.durationRange = 15;
            work.descriptor.field3C = D_800A23D4;
            work.descriptor.field40 = D_800A23D8;
            work.descriptor.field44 = D_800A23DC;
            work.descriptor.field4C = D_800A23E0;
            work.descriptor.field50 = D_800A23E4;
            work.descriptor.field54 = D_800A23E8;
            func_15151D6C(&work.descriptor, &work.color, &work.factor, 1, arg0->mode, arg0->group);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510558C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/func_1510558C.s")


void func_151058B4(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15105848 CURRENT (210) */
void func_15105848(void *arg0, s32 arg1, u8 arg2) {
    void *part;

    if (arg2 == 0x38) {
        func_151058B4(arg0);
        arg0 = (u8 *)arg0 + 0x28;
        *(u8 *)((u8 *)arg0 + 0xC) = *(u8 *)((u8 *)arg0 + 0xC) | 1;
        return;
    }
    part = (u8 *)arg0 + 0x28;
    if (arg2 == 0x39) {
        *(u8 *)((u8 *)part + 0xC) = *(u8 *)((u8 *)part + 0xC) & ~1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15105848 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/func_15105848.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/func_151058B4.s")
void func_1508B20C(f32, f32, f32, s32);

void func_15105BC8(void *arg0) {
    void *temp_v0;

    if (*(u8 *)((u8 *)arg0 + 0x34) & 1) {
        temp_v0 = *(void **)((u8 *)arg0 + 0x28);
        func_1508B20C((f32)*(s16 *)temp_v0, (f32)*(s16 *)((u8 *)temp_v0 + 2),
                       (f32)*(s16 *)((u8 *)temp_v0 + 4), 0x43FA0000);
    }
}
extern s32 D_800A5770[];
extern u8 D_800DCE50[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15105C24 CURRENT (60) */
void *func_15105C24(s32 arg0) {
    u8 var_v0;
    u8 var_v1;
    void *var_a0;
    void *(*table)[104];

    table = (void *(*)[104])D_800DCE50;
    var_v0 = 0;
loop_1:
    var_v1 = 0;
loop_2:
    var_a0 = table[var_v1][D_800A5770[var_v0]];
    if (var_a0 != 0) {
loop_3:
        if ((*(u8 *)((u8 *)var_a0 + 0x13) == 0x2E) &&
            (arg0 == *(s32 *)((u8 *)var_a0 + 0x28))) {
            return var_a0;
        }
        var_a0 = *(void **)((u8 *)var_a0 + 8);
        if (var_a0 == 0) {
            goto block_7;
        }
        goto loop_3;
    }
block_7:
    var_v1++;
    if (var_v1 >= 2) {
        var_v0++;
        if (var_v0 >= 2) {
            return 0;
        }
        goto loop_1;
    }
    goto loop_2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15105C24 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/func_15105C24.s")
