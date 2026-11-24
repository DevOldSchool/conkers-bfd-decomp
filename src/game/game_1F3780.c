#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1F3780.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_model_anchor_owner_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151C62D0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1F3780/func_151C62D0.s")
void func_151C69CC();

void func_151C6974(s32 arg0, s32 arg1, s32 arg2) {
    func_151C69CC(arg0, arg2, 0, arg2);
}
void func_151C69A0(s32 arg0, s32 arg1, s32 arg2) {
    func_151C69CC(arg0, arg2, 1, arg2);
}
void func_15143134(f32 *, f32 *, s32);
void *func_15102B38(s32, u8, s32, s32, f32 *, s16, u8, f32, s32, u8, s32, s16, u8, s32);
f32 func_150ADA68(void);
extern s32 D_800AAB00[];
extern Vec3f D_800AAB08[];
extern u8 D_800AAB20[];
extern f32 D_800AAC10;
extern f32 D_800AAC14;
extern f32 D_800AAC18;
extern f32 D_800AAC1C;
extern f32 D_800AAC20;

void func_151C69CC(arg0, arg1, arg2)
s32 arg0;
s32 arg1;
u8 arg2;
{
    s32 matrixAddress;

    matrixAddress = *(s32 *)((u8 *)arg0 + 0x1D4) + D_800AAB00[arg2];
    func_15143134((f32 *)((u8 *)D_800AAB08 + (arg2 * 0xC)), (f32 *)arg1,
                   matrixAddress);
}

typedef struct Game1F3780EffectPacket {
    u8 pad0[8];
    Vec3f position;
    u8 pad14[0x18];
    Vec3f end;
    u8 pad38[0x21];
    u8 count;
    u8 pad5A[0xA];
} Game1F3780EffectPacket;

void func_150F7470(Vec3f *, Vec3f *, s32, Vec3f *, u8, s32, f32, f32, f32, u8 *, u8, u8, u8, u8, s32, s8, s32, u8, u8, s32);
s32 func_15142A5C(void *);
void func_15145EA4(s32 *, s32 *, s32, s32);
s32 func_1514ECE0(void *, s16, void **);
void func_151D4408(void *, void *, s32, void *, f32, s32, s32);
void func_151D5148(void *);
void func_151C6D70(s32, u8, s32, s16, u8, s32);
extern Vec3f D_800AAB38[], D_800AAB50[];

typedef struct Game1F3780EffectState {
    u8 unk_00[0x10];
    Game1F3780EffectPacket packet;
    u8 unk_74;
} Game1F3780EffectState;

typedef struct Game1F3780EffectObject {
    u8 unk_00[0x28];
    Game1F3780EffectState state;
} Game1F3780EffectObject;

typedef struct Game1F3780EffectEntry {
    u8 unk_00[0x10];
    Game1F3780EffectObject *object;
} Game1F3780EffectEntry;

typedef struct Game1F3780Actor {
    u8 unk_00[0x1D4];
    s32 unk_1D4;
    u8 unk_1D8[0x11C];
    void *unk_2F4;
} Game1F3780Actor;

void func_151C6A28(Game1F3780Actor *arg0, u8 arg1, u8 arg2, s32 arg3) {
    Vec3f first;
    Vec3f second;
    Vec3f third;
    s32 transform;

    if (arg0 == NULL) {
        goto end;
    }
    if (arg1 >= 2) {
        goto end;
    }
    if (func_15142A5C(arg0) != 0) {
        goto end;
    }
    func_151D5148(arg0);
    {
        Vec3f *inputs[3];
        Vec3f *outputs[3];
        s32 matrix;

        matrix = arg0->unk_1D4;
        if (matrix == 0) {
            goto end;
        }
        transform = D_800AAB00[arg1] + matrix;
        inputs[0] = &D_800AAB08[arg1];
        inputs[1] = &D_800AAB38[arg1];
        inputs[2] = &D_800AAB50[arg1];
        outputs[0] = &first;
        outputs[1] = &second;
        outputs[2] = &third;
        func_15145EA4((s32 *)inputs, (s32 *)outputs, transform, 3);
        third.x -= second.x;
        third.y -= second.y;
        third.z -= second.z;
    }
    func_151D3F14(&first, arg2, arg3);
    func_151D4408(&second, &third, transform, arg0, 1.0f, arg2, arg3);
    func_151C6D70((s32)arg0, arg1, (s32)&first, -1, arg2, arg3);
    {
        Vec3f position;
        Game1F3780EffectEntry *entry;
        Game1F3780EffectState *state;
        Game1F3780EffectPacket *original;

        if (func_1514ECE0(arg0->unk_2F4, 0x1B, (void **)&entry) == 0) {
            goto end;
        }
        state = &entry->object->state;
        if (!(entry->object->state.unk_74 & 1)) {
            goto end;
        }
        original = &state->packet;
        if (state->packet.count == 0) {
            goto end;
        }
        if (original->count >= 2) {
            f32 deltaX = original->position.x - first.x;
            f32 deltaY = original->position.y - first.y;
            f32 deltaZ = original->position.z - first.z;

            position.x = deltaX * 1.1f + first.x;
            position.y = deltaY * 1.1f + first.y;
            position.z = deltaZ * 1.1f + first.z;
        } else {
            position = original->position;
        }
        {
            Game1F3780EffectPacket packet;

            packet = *original;
            packet.end = position;
            func_150F7470(&first, NULL, 0, 0, 0, (s32)&packet,
                           54.000004f, 0.018518517f, 500.0f, (u8 *)arg0,
                           0, (original->count >= 2) ? 0 : 1, 1, 0, 0x1A, -1, 0, 1, arg2, arg3);
        }
    }
end:
    return;
}

void func_151C6D70(s32 arg0, u8 arg1, s32 arg2, s16 arg3, u8 arg4,
                   s32 arg5) {
    f32 values[2];
    f32 angle;
    u32 random1;
    u32 random0;

    values[1] = (func_150ADA68() * D_800AAC10) + D_800AAC14;
    values[0] = (func_150ADA68() * D_800AAC18) + D_800AAC1C;
    random0 = func_150ADA20();
    /* Range form shared with the other func_15102B38 callers; here lo == hi == 0xFF. */
    random1 = func_150ADA20();
    angle = func_150ADA68();
    func_15102B38(arg0, (u32)D_800AAB00[arg1] >> 6,
                  (s32)((u8 *)D_800AAB08 + arg1 * 0xC), (s32)(D_800AAB20 + arg1 * 0xC), values,
                  (random0 % 4U) + 6,
                  (random1 % 1U) + 0xFF, (angle * 270.0f) + D_800AAC20,
                  arg2, 0xFF, 0, arg3, arg4, arg5);
}
