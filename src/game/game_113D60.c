#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_113D60.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_actor_classification_emitter.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E68B0
 * - func_150E6B84
 * - func_150E6E34
 * - func_150E6F18
 * - func_150E6FAC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E68B0.s")
typedef struct Game113D60Vector { f32 x, y, z; } Game113D60Vector;
typedef struct Game113D60Emission {
    f32 x, y, amplitudeX, amplitudeY;
    f32 phaseX, phaseY, speedX, speedY;
    f32 time, rate, remaining;
    Game113D60Vector position;
    f32 scale;
    s16 duration, durationRange;
    u8 color;
} Game113D60Emission;
typedef struct Game113D60Effect {
    u8 pad0, kind;
    u8 pad2[0xA];
    u8 owner;
    u8 padD[0x1B];
    Game113D60Emission emission;
} Game113D60Effect;

f32 func_15047D60(f32);
f32 func_150ADA68();
s32 func_150ADA20(void);
f32 func_15144528(f32, f32, f32);
void *func_150E5FD0(void *, void *, f32, f32, f32, s32, s32, s32, s32, s32, s32);
extern f32 D_800A1304, D_800A1308, D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E6B84 CURRENT (1907) */
void func_150E6B84(Game113D60Effect *arg0) {
    Game113D60Emission *emission;
    volatile f32 time;
    f32 timeStep, phaseStepX, phaseStepY;
    f32 speedX, speedY;
    Game113D60Vector direction;
    f32 phaseX, phaseY, sineX, sineY;
    f32 randomX, randomY, inverse, period;
    register f32 factor;
    u32 randomDuration;
    s32 randomColor;

    emission = &arg0->emission;
    arg0->emission.remaining += arg0->emission.rate * D_800BE9A4;
    if (*(volatile f32 *)&arg0->emission.remaining > 1.0f) {
        inverse = 1.0f / emission->remaining;
        factor = D_800A1304;
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
            randomColor = func_150ADA20();
            randomDuration = func_150ADA20();
            func_150E5FD0(&emission->position, &direction, emission->scale,
                (randomX * 300.0f + 100.0f) * factor,
                (randomY * 700.0f + 300.0f) * factor,
                arg0->owner, arg0->kind, emission->color,
                (u32)randomColor % 86U + 0xAA,
                randomDuration % (u32)(emission->durationRange + 1) + emission->duration, -1);
            phaseX += phaseStepX;
            phaseY += phaseStepY;
            time -= timeStep;
            emission->remaining -= 1.0f;
        } while (*(volatile f32 *)&emission->remaining > 1.0f);
        period = D_800A1308;
        emission->phaseX = func_15144528(phaseX, period, 0.0f);
        emission->phaseY = func_15144528(phaseY, period, 0.0f);
        emission->time = time;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E6B84 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E6B84.s")
f32 func_150ADA68();                                /* extern */
extern s32 func_150ADA20(void);
extern void *D_80088A44[];
extern void *D_80088A3C;
extern void *D_80088A40;
extern f32 D_800A130C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E6E34 CURRENT (40) */
void func_150E6E34(void *arg0) {
    void *var_v0;

    if (func_150ADA68() < D_800A130C) {
        var_v0 = D_80088A3C;
    } else {
        var_v0 = D_80088A40;
    }
    {
        void * sp1C = var_v0;
    {
        f32 temp_fv0 = func_150ADA68();
    {
        f32 temp_fv1 = *(f32 *)((u8 *)var_v0 + 0);
    *(f32 *)((u8 *)arg0 + 0) = (f32) (((*(f32 *)((u8 *)var_v0 + 0xC) - temp_fv1) * temp_fv0) + temp_fv1);
    {
        f32 temp_fa0 = *(f32 *)((u8 *)var_v0 + 4);
    *(f32 *)((u8 *)arg0 + 4) = (f32) (((*(f32 *)((u8 *)var_v0 + 0x10) - temp_fa0) * temp_fv0) + temp_fa0);
    {
        f32 temp_fa1 = *(f32 *)((u8 *)var_v0 + 8);
    *(f32 *)((u8 *)arg0 + 8) = (f32) (((*(f32 *)((u8 *)var_v0 + 0x14) - temp_fa1) * temp_fv0) + temp_fa1);
    }
    }
    }
    }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E6E34 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E6E34.s")
extern s32 func_150ADA20(void);
extern s32 D_800D9A20[];
extern void func_1514470C(s32 arg0, s32 arg1);

void func_150E6ED8(s32 arg0) {
    func_1514470C(D_800D9A20[func_150ADA20() & 1], arg0);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E6F18 CURRENT (82) */
void func_150E6F18(void *arg0) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 temp_v1;

    temp_v1 = (s32)D_80088A44[func_150ADA20() % 6U];
    temp_fv0 = func_150ADA68();
    temp_fv1 = *(f32 *)((u8 *)temp_v1 + 0);
    *(f32 *)((u8 *)arg0 + 0) =
        (f32)(((*(f32 *)((u8 *)temp_v1 + 0xC) - temp_fv1) * temp_fv0) + temp_fv1);
    temp_fa0 = *(f32 *)((u8 *)temp_v1 + 4);
    *(f32 *)((u8 *)arg0 + 4) =
        (f32)(((*(f32 *)((u8 *)temp_v1 + 0x10) - temp_fa0) * temp_fv0) + temp_fa0);
    temp_fa1 = *(f32 *)((u8 *)temp_v1 + 8);
    *(f32 *)((u8 *)arg0 + 8) =
        (f32)(((*(f32 *)((u8 *)temp_v1 + 0x14) - temp_fa1) * temp_fv0) + temp_fa1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E6F18 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E6F18.s")
s32 func_1514ECE0();

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E6FAC CURRENT (1025) */
void func_150E6FAC(f32 *arg0, u8 *arg1) {
    void *sp34;
    f32 sp2C;
    s16 sp2A;
    f32 sp24;
    f32 temp_fv0;
    s16 temp_t6;
    u8 *temp_v0;

    if (func_1514ECE0(*(s32 *)(arg1 + 0x2F4), 0x16, &sp34) != 0) {
        sp2C = (func_150ADA68() * 100.0f) + 80.0f;
        temp_t6 = func_150ADA20() & 0xFF;
        sp2A = temp_t6;
        sp24 = func_151423D8((temp_t6 - 0x40) & 0xFF);
        temp_fv0 = func_151423D8(*((u8 *)&sp2A + 1));
        temp_v0 = *(u8 **)((u8 *)sp34 + 0x10);
        arg0[0] = *(f32 *)(arg1 + 0x14) +
                  (*(f32 *)(temp_v0 + 0x38) * -80.0f) + (sp24 * sp2C);
        arg0[1] = *(f32 *)(arg1 + 0x18) +
                  (*(f32 *)(temp_v0 + 0x3C) * -80.0f) + 100.0f;
        arg0[2] = *(f32 *)(arg1 + 0x1C) +
                  (*(f32 *)(temp_v0 + 0x40) * -80.0f) + (temp_fv0 * sp2C);
        return;
    }
    arg0[0] = *(f32 *)(arg1 + 0x14);
    arg0[1] = *(f32 *)(arg1 + 0x18);
    arg0[2] = *(f32 *)(arg1 + 0x1C);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E6FAC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_113D60/func_150E6FAC.s")
void func_150E70CC(f32 *arg0, f32 *arg1) {
    arg0[0] = arg1[5];
    arg0[1] = arg1[6];
    arg0[2] = arg1[7];
}
/* Call context: func_150484A0: unique active project prototype */
f32 func_150484A0(f32, f32);
extern f32 D_800A1310;
extern f32 D_800A1314;
extern f32 D_800A1318;
extern f32 D_800A131C;
extern f32 D_800A1320;
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

void func_150E70EC(s32 arg0, s32 arg1, void *arg2, void *arg3) {
    f32 temp_ft4;
    f32 temp_fv1;

    *(f32 *)((u8 *)arg3 + 0) = func_150484A0(*(f32 *)((u8 *)arg2 + 0), *(f32 *)((u8 *)arg2 + 8));
    *(f32 *)((u8 *)arg3 + 8) = (f32) (func_150ADA68() * D_800A1310);
    *(f32 *)((u8 *)arg3 + 0x10) = (f32) (func_150ADA68() * D_800A1314);
    *(f32 *)((u8 *)arg3 + 0x18) = (f32) (func_150ADA68() * 0.5f);
    temp_fv1 = *(f32 *)((u8 *)arg2 + 0);
    temp_ft4 = *(f32 *)((u8 *)arg2 + 8);
    *(f32 *)((u8 *)arg3 + 4) = (f32) (func_150484A0(sqrtf((temp_fv1 * temp_fv1) + (temp_ft4 * temp_ft4)), *(f32 *)((u8 *)arg2 + 4)) - D_800A1318);
    *(f32 *)((u8 *)arg3 + 0xC) = (f32) (func_150ADA68() * D_800A131C);
    *(f32 *)((u8 *)arg3 + 0x14) = (f32) (func_150ADA68() * D_800A1320);
    *(f32 *)((u8 *)arg3 + 0x1C) = (f32) (func_150ADA68() * 0.5f);
}
f32 func_150484A0(f32, f32);                        /* extern */
extern f32 D_800A1324;
extern f32 D_800A1328;
extern f32 D_800A132C;
extern f32 D_800A1330;
extern f32 D_800A1334;
extern f32 D_800A1338;
extern f32 D_800A133C;

void func_150E71E4(s32 arg0, s32 arg1, void *arg2, void *arg3) {
    *(f32 *)((u8 *)arg3 + 0) = func_150484A0(*(f32 *)((u8 *)arg2 + 0), *(f32 *)((u8 *)arg2 + 8));
    *(f32 *)((u8 *)arg3 + 8) = (f32) D_800A1324;
    *(f32 *)((u8 *)arg3 + 0x10) = (f32) (func_150ADA68() * D_800A1328);
    *(f32 *)((u8 *)arg3 + 0x18) = (f32) (func_150ADA68() * D_800A132C);
    *(f32 *)((u8 *)arg3 + 4) = (f32) D_800A1330;
    *(f32 *)((u8 *)arg3 + 0xC) = (f32) D_800A1334;
    *(f32 *)((u8 *)arg3 + 0x14) = (f32) (func_150ADA68() * D_800A1338);
    *(f32 *)((u8 *)arg3 + 0x1C) = (f32) (func_150ADA68() * D_800A133C);
}
