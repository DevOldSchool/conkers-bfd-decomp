#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1EBFD0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_recovered_pointer_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151BEB20
 * - func_151BECB8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

/* Call context: func_150A8050: unique active project prototype */
void func_150A8050(void *, f32, s32, f32);
extern f32 D_800AA8E0;
extern u8 D_800BE9C0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BEB20 CURRENT (565) */
s32 func_151BEB20(u8 *arg0) {
    f32 scale;
    u8 *temp_v1;
    u8 *temp_v1_2;
    u8 *temp_v1_3;
    u8 *temp_v1_4;
    u8 *temp_v1_5;
    u8 *temp_v1_6;
    u8 *temp_v1_7;
    u8 *temp_v1_8;
    u8 *temp_v1_9;

    func_150A8050(arg0 + (D_800BE9C0 << 6) + 0x7C, 0.0f, *(s32 *)((u8 *)arg0 + 0x120), 0.0f);
    scale = D_800AA8E0;
    *(f32 *)((u8 *)(arg0 + (D_800BE9C0 << 6)) + 0xAC) = (f32) *(f32 *)((u8 *)arg0 + 0x54);
    *(f32 *)((u8 *)(arg0 + (D_800BE9C0 << 6)) + 0xB0) = (f32) *(f32 *)((u8 *)arg0 + 0x58);
    *(f32 *)((u8 *)(arg0 + (D_800BE9C0 << 6)) + 0xB4) = (f32) *(f32 *)((u8 *)arg0 + 0x5C);
    temp_v1 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1 + 0x7C) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x7C) * scale);
    temp_v1_2 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_2 + 0x80) = (f32) (*(f32 *)((u8 *)temp_v1_2 + 0x80) * scale);
    temp_v1_3 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_3 + 0x84) = (f32) (*(f32 *)((u8 *)temp_v1_3 + 0x84) * scale);
    temp_v1_4 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_4 + 0x8C) = (f32) (*(f32 *)((u8 *)temp_v1_4 + 0x8C) * scale);
    temp_v1_5 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_5 + 0x90) = (f32) (*(f32 *)((u8 *)temp_v1_5 + 0x90) * scale);
    temp_v1_6 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_6 + 0x94) = (f32) (*(f32 *)((u8 *)temp_v1_6 + 0x94) * scale);
    temp_v1_7 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_7 + 0x9C) = (f32) (*(f32 *)((u8 *)temp_v1_7 + 0x9C) * scale);
    temp_v1_8 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_8 + 0xA0) = (f32) (*(f32 *)((u8 *)temp_v1_8 + 0xA0) * scale);
    temp_v1_9 = (void *)(arg0 + (D_800BE9C0 << 6));
    *(f32 *)((u8 *)temp_v1_9 + 0xA4) = (f32) (*(f32 *)((u8 *)temp_v1_9 + 0xA4) * scale);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BEB20 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EBFD0/func_151BEB20.s")
s32 func_151BEC94(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s8 *arg4) {
    *arg4 = 1;
    return arg0;
}
typedef struct Game1EBFD0Actor {
    u8 pad0[0x127];
    u8 player;
    u8 pad128[0x204];
} Game1EBFD0Actor;

typedef struct Game1EBFD0Event {
    f32 scale;
    f32 position[3];
    u8 value;
} Game1EBFD0Event;

typedef struct Game1EBFD0Owner {
    u8 pad0;
    u8 category;
    u8 pad2[0xA];
    u8 group;
    u8 padD[3];
    u8 flags;
    u8 pad11[0x37];
    u8 mode;
    u8 pad49[0xB];
    f32 position[3];
    s32 field60;
    u8 pad64[0x98];
    s32 fieldFC;
    u8 pad100[0x1B];
    u8 field11B;
    u8 pad11C[4];
    Game1EBFD0Event event;
} Game1EBFD0Owner;

void func_1515C1A0(void *, void *, f32 *, f32 *);
s32 func_151BEE94(void *);
void func_15085710(s16, s32, u8);
void func_10010F30(s32, s32, s32, s32, s32);
void func_151BF340(s32, s32);
void func_151BF0C8(f32 *);
void func_151BEEE0(f32, f32 *, s32, u8, s32, s32, s32, s32, s32);
extern Game1EBFD0Actor D_800CC2D0[];
extern Game1EBFD0Actor D_800D1548;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151BECB8 CURRENT (711) */
s32 func_151BECB8(Game1EBFD0Owner *arg0) {
    Game1EBFD0Actor *actor;
    Game1EBFD0Event *event;
    f32 radius;
    f32 height;
    f32 position[3];
    f32 delta[3];
    s32 ready;
    s32 mode;


    ready = 1;
    actor = D_800CC2D0;
    do {
        if (func_151BEE94(actor) != 0) {
            event = &arg0->event;
            func_1515C1A0(actor, position, &radius, &height);
            delta[0] = position[0] - event->position[0];
            delta[1] = position[1] - event->position[1];
            delta[2] = position[2] - event->position[2];
            if (func_15143E64(delta) - radius < 43.0f) {
                ready = 0;
                func_15085710(actor->player, 3, event->value);
                func_10010F30(0x511, 0x7D00, 0x40, 0, 0);
                func_151BF340(arg0->group, arg0->category);
                func_151BF0C8(event->position);
                switch (arg0->mode) {
                case 0:
                    mode = 0;
                    break;
                case 1:
                    mode = 1;
                    break;
                case 2:
                    mode = 2;
                    break;
                case 3:
                    mode = 0;
                    break;
                default:
                    mode = 0;
                    break;
                }
                func_151BEEE0(event->scale, arg0->position, arg0->fieldFC,
                              arg0->field11B, mode, arg0->flags & 0x10,
                              arg0->field60, arg0->group, arg0->category);
            }
        }
        actor++;
    } while (actor != &D_800D1548);
    return ready;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151BECB8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EBFD0/func_151BECB8.s")
s32 func_151BEE94(void *arg0) {
    if (*(u8 *)((u8 *)arg0 + 0x127) == 0xFF) {
        return 0;
    }
    if (*(s32 *)((u8 *)arg0 + 0) == 0) {
        return 0;
    }
    if (*(u8 *)((u8 *)arg0 + 4) == 0xFF) {
        return 0;
    }
    return 1;
}
