#include "types.h"

/*
 * Reviewed source unit: src/game/game_128D70.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FB8C0
 * - func_150FC438
 * - func_150FC818
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_128D70/func_150FB8C0.s")
/* Call context: func_151C3B0C: unique active project prototype */
void func_151C3B0C(void *, f32, f32, f32, f32, s32, s32, s32);

void func_150FC368(void *arg0) {
    u8 var_v0;
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;

    temp_v0 = *(void **)((u8 *)arg0 + 0x1A0);
    if ((temp_v0 == 0) || (*(s32 *)((u8 *)temp_v0 + 0) == 0) || (*(u8 *)((u8 *)temp_v0 + 4) == 0xFF) || (*(u8 *)((u8 *)arg0 + 0x1A4) != *(u8 *)((u8 *)temp_v0 + 0x3B)) || (temp_v1 = *(void **)((u8 *)temp_v0 + 0x31C), (temp_v1 == 0)) || (*(u8 *)((u8 *)temp_v1 + 0x84) != 0) || (*(u8 *)((u8 *)temp_v0 + 0x127) == 0xFF) || (temp_v1_2 = *(void **)((u8 *)temp_v0 + 0x318), (temp_v1_2 == 0))) {
        var_v0 = 0xFF;
    } else {
        var_v0 = ~(1U << *(u8 *)((u8 *)temp_v1_2 + 0x23D)) & 0xFF;
    }
    func_151C3B0C(arg0, 1.0f, 1.0f, 0.6f, 0.0f, 0xFF, 0xFF, var_v0);
}
typedef struct Game128D70Player {
    u8 pad0[0x23D];
    u8 index;
} Game128D70Player;

typedef struct Game128D70Actor {
    u8 pad0[0x3B];
    u8 type;
    u8 pad3C[0x2DC];
    Game128D70Player *player;
} Game128D70Actor;

typedef struct Game128D70Owner {
    Game128D70Actor *owner;
    u8 type;
    u8 pad5[3];
    f32 value;
    u8 fieldC;
    u8 mode;
    u8 padE[2];
    void *effect;
    s16 field14;
    s8 player;
    u8 pad17;
    Game128D70Actor *other;
    u8 otherType;
    u8 field1D;
    u8 pad1E[2];
} Game128D70Owner;

typedef struct Game128D70Effect {
    u8 kind;
    s8 field1;
    s8 field2;
    u8 pad3;
    s16 lifetime;
    u8 player;
    u8 pad7;
    f32 field8, fieldC, field10, field14, field18, field1C;
    f32 field20, field24, field28, field2C, field30, field34;
} Game128D70Effect;

void *func_10022EC0(void *, const void *, u32);
u8 *func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);
void *func_15164780(u8 *, s32, u8, s32);
extern f32 D_800A1EB0, D_800A1EB4, D_800A1EB8;
extern f32 D_800A1EBC, D_800A1EC0, D_800A1EC4;
extern f32 D_800A1EC8, D_800A1ECC, D_800A1ED0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FC438 CURRENT (629) */
void func_150FC438(Game128D70Actor *arg0, Game128D70Actor *arg1, s32 arg2, u8 arg3) {
    Game128D70Owner owner;
    u8 *object;
    Game128D70Player *player;
    Game128D70Effect effect;
    Game128D70Owner *result;

    arg2 &= 0xFF;
    owner.owner = arg0;
    owner.type = arg0->type;
    owner.value = 0.0f;
    owner.fieldC = 0;
    owner.mode = arg2;
    owner.effect = 0;
    owner.field14 = 0;
    owner.field1D = arg3;
    if (arg1 != 0 && (player = arg1->player) != 0) {
        owner.player = player->index;
    } else {
        owner.player = -1;
    }
    owner.other = arg1;
    if (arg1 != 0) {
        owner.otherType = arg1->type;
    } else {
        owner.otherType = 0xFF;
    }
    object = func_15149130(0x12C, -1, 0x27, -1, 0, 0x25, 0x20, 0xFF, 1);
    result = (Game128D70Owner *)((u32)object + 0x28U);
    if (object != 0) {
        func_10022EC0(result, &owner, 0x20);
        if (arg1 != 0 && arg1->player != 0) {
            effect.kind = 4;
            effect.field1 = -1;
            effect.field2 = -1;
            effect.lifetime = 0x12C;
            effect.player = arg1->player->index;
            effect.field8 = 12.0f;
            effect.fieldC = 20.0f;
            effect.field10 = 19.0f;
            effect.field14 = D_800A1EB0;
            effect.field18 = D_800A1EB4;
            effect.field1C = D_800A1EB8;
            effect.field20 = D_800A1EBC;
            effect.field24 = D_800A1EC0;
            effect.field28 = D_800A1EC4;
            effect.field2C = D_800A1EC8;
            effect.field30 = D_800A1ECC;
            effect.field34 = D_800A1ED0;
            result->effect = func_15164780((u8 *)&effect, 0, 0xFF, 1);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FC438 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_128D70/func_150FC438.s")
u32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_150FB8C0(void *, s32, f32, s32, s32, s32);
void *func_151D8868(s8 *, s32, s32, s32);
extern f32 D_800BE9A4;
extern s32 D_800BE9E4;
extern u8 D_800C35EA;

void func_150FC614(u8 *arg0) {
    u8 *actor;
    Game128D70Owner *owner;
    s8 event[8];
    u8 *state;

    actor = *(u8 **)(arg0 + 0x28);
    if (*(s32 *)actor == 0 ||
        (owner = (Game128D70Owner *)(arg0 + 0x28), actor[4] == 0xFF) ||
        owner->type != actor[0x3B] || D_800C35EA == 1) {
        *(s16 *)(arg0 + 0xE) = -1;
        return;
    }
    if (owner->field1D != *(u16 *)(actor + 0x84)) {
        *(s16 *)(arg0 + 0xE) = -1;
        return;
    }
    owner->value -= D_800BE9A4;
    if (owner->value < 0.0f) {
        do {
            func_150FB8C0(actor, owner->fieldC, -owner->value, owner->mode,
                           arg0[0xC], arg0[1]);
            owner->fieldC ^= 1;
            if (owner->other != 0) {
                state = *(u8 **)((u8 *)owner->other + 0x31C);
                if (state != 0) {
                    *(s16 *)(state + 0x1AA) += 1;
                }
            }
            owner->value += 4.0f + func_150ADA68() * 4.0f;
        } while (owner->value < 0.0f);
    }
    if (owner->player != -1) {
        owner->field14 -= D_800BE9E4;
        if (owner->field14 < 0) {
            event[0] = 1;
            func_150ADA20();
            *(s16 *)&event[2] = 0x1E;
            event[5] = 1 << owner->player;
            event[4] = (func_150ADA20() % 6U) + 3;
            event[6] = -1;
            func_151D8868(event, 0, arg0[0xC], arg0[1]);
            func_150ADA20();
            owner->field14 = 0xFA;
        }
    }
}
void func_1516972C(u8 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FC818 CURRENT (1585) */
void func_150FC818(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 first;
    s32 second;
    s32 current;
    s32 alternate;
    u8 subtype;
    u8 *state;

    if (arg2 == 0) {
        state = arg0 + 0x28;
        first = *(s32 *)arg1;
        current = *(s32 *)state;
        if ((current == first) ||
            (subtype = arg1[4], subtype == state[4])) {
            func_1516972C(arg0);
            return;
        }
        alternate = *(s32 *)(state + 0x18);
        if ((alternate != 0) &&
            ((first == alternate) || (subtype == state[0x1C]))) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        state = arg0 + 0x28;
        first = *(s32 *)arg1;
        current = *(s32 *)state;
        if (first == current) {
            *(s32 *)state = *(s32 *)(arg1 + 4);
            state[4] = arg1[9];
            return;
        }
        second = *(s32 *)(arg1 + 4);
        if (second == current) {
            *(s32 *)state = first;
            state[4] = arg1[8];
            return;
        }
        alternate = *(s32 *)(state + 0x18);
        if (alternate != 0) {
            if (first == alternate) {
                *(s32 *)(state + 0x18) = second;
                state[0x1C] = arg1[9];
                return;
            }
            if (second == alternate) {
                *(s32 *)(state + 0x18) = first;
                state[0x1C] = arg1[8];
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FC818 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_128D70/func_150FC818.s")
