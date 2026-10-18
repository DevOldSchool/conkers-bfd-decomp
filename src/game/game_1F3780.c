#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1F3780.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_model_anchor_owner_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151C62D0
 * - func_151C6A28
 * - func_151C6D70
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
void func_15102B38(s32, u8, s32, s32, f32 *, s32, s32, f32, s32,
                   s32, s32, s32, s32, s32);
f32 func_150ADA68(void);
extern s32 D_800AAB00[];
extern f32 D_800AAB08[];
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

void func_150F7470(f32 *, f32 *, s32, s32, s32, s32, f32, f32, f32,
                   void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_15142A5C(void *);
void func_15145EA4(s32 *, s32 *, s32, s32);
s32 func_1514ECE0(void *, s16, void **);
void func_151D4408(void *, void *, s32, void *, f32, s32, s32);
void func_151D5148(void *);
void func_151C6D70(s32, u8, s32, s16, u8, s32);
extern u8 D_800AAB38[], D_800AAB50[];
extern f32 D_800AAC04, D_800AAC08, D_800AAC0C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C6A28 CURRENT (7885) */
void func_151C6A28(void *arg0, u8 arg1, u8 arg2, s32 arg3) {
    Vec3f first;
    Vec3f second;
    Vec3f third;
    s32 transform;
    s32 inputs[3];
    f32 *outputs[3];
    s32 matrix;
    Vec3f position;
    void *entry;
    u8 *object;
    u8 *state;
    Game1F3780EffectPacket *original;
    s32 mode;
    f32 deltaX, deltaY, deltaZ;
    Game1F3780EffectPacket packet;

    if ((arg0 != NULL) && ((s32)arg1 < 2) && (func_15142A5C(arg0) == 0)) {
        func_151D5148(arg0);
        matrix = *(s32 *)((u8 *)arg0 + 0x1D4);
        if (matrix != 0) {
            transform = D_800AAB00[arg1] + matrix;
            inputs[0] = (s32)((Vec3f *)D_800AAB08 + arg1);
            inputs[1] = (s32)((Vec3f *)D_800AAB38 + arg1);
            inputs[2] = (s32)((Vec3f *)D_800AAB50 + arg1);
            outputs[0] = &first.x;
            outputs[1] = &second.x;
            outputs[2] = &third.x;
            func_15145EA4(inputs, (s32 *)outputs, transform, 3);
            third.x -= second.x;
            third.y -= second.y;
            third.z -= second.z;
            func_151D3F14(&first, arg2, arg3);
            func_151D4408(&second, &third, transform, arg0, 1.0f, arg2, arg3);
            func_151C6D70((s32)arg0, arg1, (s32)&first, -1, arg2, arg3);
            if (func_1514ECE0(*(void **)((u8 *)arg0 + 0x2F4), 0x1B, &entry) != 0) {
                object = *(u8 **)((u8 *)entry + 0x10);
                state = object + 0x28;
                if (object[0x9C] & 1) {
                    original = (Game1F3780EffectPacket *)(state + 0x10);
                    if (state[0x69] != 0) {
                        if (original->count >= 2) {
                            deltaX = original->position.x - first.x;
                            deltaY = original->position.y - first.y;
                            deltaZ = original->position.z - first.z;
                            position.x = (deltaX * D_800AAC04) + first.x;
                            position.y = (deltaY * D_800AAC04) + first.y;
                            position.z = (deltaZ * D_800AAC04) + first.z;
                        } else {
                            position = original->position;
                        }
                        packet = *original;
                        packet.end = position;
                        mode = 1;
                        if (original->count >= 2) {
                            mode = 0;
                        }
                        func_150F7470(&first.x, NULL, 0, 0, 0, (s32)&packet,
                                       D_800AAC08, D_800AAC0C, 500.0f, arg0,
                                       0, mode, 1, 0, 0x1A, -1, 0, 1, arg2, arg3);
                    }
                }
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C6A28 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1F3780/func_151C6A28.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C6D70 CURRENT (496) */
void func_151C6D70(s32 arg0, u8 arg1, s32 arg2, s16 arg3, u8 arg4,
                   s32 arg5) {
    struct {
        u32 sp44;
        u32 sp48;
        u32 pad4C;
        f32 sp50[2];
    } locals;
    s32 temp_v0;

    locals.sp50[1] = (func_150ADA68() * D_800AAC10) + D_800AAC14;
    locals.sp50[0] = (func_150ADA68() * D_800AAC18) + D_800AAC1C;
    locals.sp44 = func_150ADA20();
    locals.sp48 = func_150ADA20();
    temp_v0 = arg1 * 0xC;
    func_15102B38(arg0, ((u32)D_800AAB00[arg1] >> 6) & 0xFF,
                  (s32)((u8 *)D_800AAB08 + temp_v0),
                  (s32)(D_800AAB20 + temp_v0), locals.sp50,
                  (locals.sp44 & 3) + 6,
                  0xFF, (func_150ADA68() * 270.0f) + D_800AAC20,
                  arg2, 0xFF, 0, arg3, arg4, arg5);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C6D70 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1F3780/func_151C6D70.s")
