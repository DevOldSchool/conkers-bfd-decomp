#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D5FD0.c
 * Boundary evidence: docs/evidence/game_raw_extended_code_selected_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A8B20
 * - func_151A8CEC
 * - func_151A8F6C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);
f32 func_15144598(void *);
void func_1510F800(s32);
void *func_1510FD20(s32, s32);
void *func_15149130(s16, s8, s8, s8, u8, u8, s32, u8, s32);
extern f32 D_800A8F50;
extern f32 D_800A8F54;

typedef struct Game1D5FD0Payload {
    u8 flags;
    u8 pad1[3];
    s16 *owner;
    u8 pad8[8];
    f32 x, y, z;
    f32 value1C;
    f32 radius;
    u8 pad24[4];
    f32 time;
    f32 limit;
    u8 pad30[0x14];
    s32 state44;
    u8 state48;
    u8 state49;
    u8 pad4A[2];
    s32 state4C;
    void *node;
    f32 squaredRadius;
} Game1D5FD0Payload;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A8B20 CURRENT (469) */
void *func_151A8B20(void *arg0, s16 arg1, s32 arg2, u8 arg3, s32 arg4) {
    void *result;
    Game1D5FD0Payload packet;
    Game1D5FD0Payload *payload;
    f32 z;
    f32 x;
    s16 *owner;

    func_10022EC0(&packet, arg0, 0x28);
    packet.state44 = 0;
    packet.state48 = 0;
    packet.state49 = 0;
    packet.state4C = 0;
    packet.time = 0.0f;
    packet.limit = D_800A8F50;
    result = func_15149130(arg1 == -1 ? 0x12C : arg1, -1, 0x25, -1,
                           arg1 == -1 ? 0 : 1, 0x22,
                           arg2 + 0x58, arg3, arg4);
    if (result != 0) {
        payload = (Game1D5FD0Payload *)((u8 *)result + 0x28);
        func_10022EC0(payload, &packet, 0x58);
        if (payload->flags & 4) {
            if ((payload->flags & 2) && ((owner = payload->owner) != 0)) {
                x = owner[0];
                z = owner[2];
            } else {
                x = payload->x;
                z = payload->z;
            }
            func_1510F800(0);
            payload->node = func_1510FD20((s32)x, (s32)z);
        } else {
            payload->node = 0;
        }
        if ((payload->flags & 2) && ((owner = payload->owner) != 0)) {
            payload->squaredRadius = func_15144598(owner);
        } else {
            payload->squaredRadius = payload->radius * payload->radius * D_800A8F54;
        }
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A8B20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D5FD0/func_151A8B20.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D5FD0/func_151A8CEC.s")
typedef struct {
    u8 pad_0[0x2C];
    s32 field_2C;
} Game1D5FD0State;

void func_151432BC(s32, f32 *, f32 *, f32 *, s32);

void func_151A8F1C(Game1D5FD0State *arg0, f32 *arg1, f32 *arg2, s32 arg3) {
    func_151432BC(arg0->field_2C, arg1, arg1 + 2, arg2, arg3);
    arg1[1] = *arg2;
}
void func_15143874(s16, s32, f32 *, f32 *);
s32 func_150ADA20(void);
f32 func_150ADA68(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A8F6C CURRENT (396) */
void func_151A8F6C(void *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    s32 sp24;
    u8 *sp20;
    f32 velocity;
    u8 *state;
    void *saved_arg0;
    f32 *saved_arg2;
    f32 *saved_arg3;

    saved_arg0 = arg0;
    saved_arg2 = arg2;
    saved_arg3 = arg3;
    sp24 = func_150ADA20();
    state = (u8 *)saved_arg0 + 0x28;
    sp20 = state;
    velocity = func_150ADA68() * *(f32 *)((u8 *)saved_arg0 + 0x48);
    func_15143874((s16)(sp24 & 0xFF), (s32)velocity, arg1, arg1 + 2);
    arg1[0] += *(f32 *)(state + 0x10);
    arg1[2] += *(f32 *)(state + 0x18);
    arg1[1] = *(f32 *)(state + 0x14);
    *saved_arg2 = *(f32 *)(state + 0x14);
    *saved_arg3 = *(f32 *)(state + 0x1C);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A8F6C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D5FD0/func_151A8F6C.s")
void func_151A931C(void *, u8 *, u8);

void func_151A9024(void *arg0, s32 arg1, u8 arg2) {
    if (*(u8 *)((u8 *)arg0 + 0x4C) != 1) {
        return;
    }
    func_151A931C(arg0, (u8 *)arg1, arg2);
}
