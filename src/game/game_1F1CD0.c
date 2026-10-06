#include "types.h"

/*
 * Reviewed source unit: src/game/game_1F1CD0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_singletons_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151C4820
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1F1CD0Vec3 { f32 x, y, z; } Game1F1CD0Vec3;
typedef struct Game1F1CD0Emission {
    f32 x, y;
    f32 amplitudeX, amplitudeY;
    f32 phaseX, phaseY;
    f32 speedX, speedY;
    f32 time, rate;
    f32 remaining;
    Game1F1CD0Vec3 position;
    f32 scaleX, scaleY, parameter;
} Game1F1CD0Emission;
typedef struct Game1F1CD0Actor {
    u8 pad0;
    u8 kind;
    u8 pad2[0xA];
    u8 owner;
    u8 padD[0x1B];
    Game1F1CD0Emission emission;
} Game1F1CD0Actor;

f32 func_15047D60(f32);
void func_151436B4(f32, f32, f32, void *);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
f32 func_15144B68(f32);
s32 func_151C229C(Game1F1CD0Vec3 *, Game1F1CD0Vec3 *, s32, s32, s32, s32,
                  f32, f32, f32, f32, f32, s32, s32, s32, s32, s32, s32,
                  s32, s32, s32, s32, f32, s32, s32, s32, s32, s32);
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C4820 CURRENT (974) */
void func_151C4820(Game1F1CD0Actor *arg0) {
    f32 sineY;
    f32 sineX;
    f32 timeStep;
    f32 randomX;
    f32 randomY;
    f32 speedX;
    f32 speedY;
    f32 inverse;
    Game1F1CD0Emission *emission;
    Game1F1CD0Vec3 direction;
    f32 phaseStepX;
    f32 phaseStepY;
    f32 time;
    f32 phaseX;
    f32 phaseY;

    emission = &arg0->emission;
    arg0->emission.remaining += arg0->emission.rate * D_800BE9A4;
    if (*(volatile f32 *)&arg0->emission.remaining > 1.0f) {
        inverse = 1.0f / emission->remaining;
        time = emission->time + D_800BE9A4;
        timeStep = time * inverse;
        speedX = emission->speedX * D_800BE9A4;
        speedY = emission->speedY * D_800BE9A4;
        phaseX = emission->phaseX;
        phaseY = emission->phaseY;
        phaseStepX = speedX * inverse;
        phaseStepY = speedY * inverse;
        do {
            sineX = func_15047D60(phaseX);
            sineY = func_15047D60(phaseY);
            func_151436B4(emission->x + sineX * emission->amplitudeX,
                          emission->y + sineY * emission->amplitudeY, 5.0f, &direction);
            randomX = func_150ADA68();
            randomY = func_150ADA68();
            func_151C229C(&emission->position, &direction, 0, 0, 0, 0,
                          emission->scaleX, emission->scaleY, randomX * 40.0f + 55.0f,
                          randomY * 300.0f + 250.0f, emission->parameter,
                          func_150ADA20() % 56U + 0xC8, 0, 0, 0, 0, 0, 0, 0,
                          -1, 0, time, 0xFF, -1, 0, arg0->owner, arg0->kind);
            phaseX += phaseStepX;
            emission->remaining -= 1.0f;
            phaseY += phaseStepY;
            time -= timeStep;
        } while (*(volatile f32 *)&emission->remaining > 1.0f);
        emission->phaseX = func_15144B68(phaseX);
        emission->phaseY = func_15144B68(phaseY);
        emission->time = time;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C4820 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1F1CD0/func_151C4820.s")
