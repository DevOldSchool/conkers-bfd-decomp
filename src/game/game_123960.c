#include "types.h"

/*
 * Reviewed source unit: src/game/game_123960.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F64DC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150F64B0(s32 arg0) {
    func_150F6478(arg0);
    func_151411C4(arg0);
}
typedef struct Game123960Actor {
    s32 active;
    u8 pad04[0x10];
    f32 position[3];
    u8 pad20[0x1B];
    u8 generation;
    u8 pad3C[0x58];
    u32 flags;
    u8 pad98[0x13C];
    s32 transform;
} Game123960Actor;
typedef struct Game123960Effect {
    Game123960Actor *actor;
    u8 generation;
    u8 pad05;
    s16 timer;
} Game123960Effect;
typedef struct Game123960Object {
    u8 pad00, flags01;
    u8 pad02[0xA];
    u8 flags0C, pad0D;
    s16 lifetime;
    u8 pad10[0x18];
    Game123960Effect effect;
} Game123960Object;
typedef struct Game123960Light {
    u8 type;
    s8 callback;
    s16 duration;
    u8 flags;
    u8 pad05;
} Game123960Light;

s32 func_10010F88(s32, u16, s32, s32, s32, s32, s32, s32, s32, s32);
void func_15143134(f32 *, f32 *, s32);
s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
void *func_15107C1C(void *, u8, f32 *, s16, s32, s32, s32, f32, f32, s32, s32, u8 *, s32, s32);
extern f32 D_800A1B30[3];
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F64DC CURRENT (438) */
void func_150F64DC(Game123960Object *arg0) {
    Game123960Actor *actor;
    f32 position[3];
    Game123960Light light;
    s32 integerPosition[3];
    u8 color[4];
    Game123960Effect *effect;
    s8 count;
    u32 duration, angle, velocity;

    actor = arg0->effect.actor;
    effect = &arg0->effect;
    if (actor->active == 0 || actor->generation != effect->generation) {
        arg0->lifetime = -1;
        return;
    }
    if (actor->transform != 0 && !(actor->flags & 2)) {
        effect->timer = (s16)((u32)effect->timer - (u32)D_800BE9E4);
        if (effect->timer < 0) {
            func_10010F88(0x679, 0x18CE, 0, 0, 0, (s32)actor->position[0],
                (s32)actor->position[1], (s32)actor->position[2], 0x7918, 0x7D00);
            count = (func_150ADA20() & 1) + 2;
            func_15143134(D_800A1B30, position, actor->transform);
            light.type = 3;
            light.callback = -1;
            light.duration = func_150ADA20() % 9U + 0xA;
            light.flags = 0;
            integerPosition[0] = (s32)position[0];
            integerPosition[1] = (s32)position[1];
            integerPosition[2] = (s32)position[2];
            func_151602C0((u8 *)&light, integerPosition, func_150ADA20() % 61U + 0x3C,
                0xFF, 0xFF, 0xFF, 0xFF, 0, 0, arg0->flags0C, arg0->flags01);
            do {
                color[0] = 0xA0;
                color[1] = 0xA0;
                color[2] = 0xFF;
                color[3] = func_150ADA20() % 101U + 0x9B;
                angle = func_150ADA20();
                velocity = func_150ADA20();
                duration = func_150ADA20();
                func_15107C1C(actor, 0, D_800A1B30, (s16)(angle & 0xFF),
                    (s32)(velocity % 43U) - 0x32, duration % 18U + 5, 4, 27.0f,
                    func_150ADA68() * 16.0f + 20.0f, 0, 2, color, arg0->flags0C, arg0->flags01);
                count--;
            } while (count > 0);
            effect->timer = func_150ADA20() % 91U + 0x5A;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F64DC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_123960/func_150F64DC.s")

extern void func_15169850(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_150F6850(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, (s32) arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}
