#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_113D60.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_actor_classification_emitter.md
 */

typedef struct Game113D60Emission {
    f32 x, y, amplitudeX, amplitudeY;
    f32 phaseX, phaseY, speedX, speedY;
    f32 time, rate, remaining;
    Vec3f position;
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

typedef struct Game113D60Source {
    f32 chance;
    s8 start;
    s8 end;
    s8 motion;
    u8 pad7;
    s16 duration;
    s16 durationRange;
    u8 color;
    u8 padD[3];
} Game113D60Source;

typedef void (*Game113D60EndCallback)(Vec3f *, s32);
typedef void (*Game113D60StartCallback)(Vec3f *);
typedef void (*Game113D60MotionCallback)(Vec3f *, Vec3f *, Vec3f *, Game113D60Emission *);

void *func_10022EC0(void *, const void *, u32);
extern Game113D60StartCallback D_80088A20[];
extern Game113D60EndCallback D_80088A2C[];
extern Game113D60MotionCallback D_80088A34[];
extern Game113D60Source D_800A1190[];
extern f32 D_800A12F8;
extern f32 D_800A12FC;
extern f32 D_800A1300;
extern u8 D_800C35E8;
extern u8 D_800C35EA;
f32 func_150ADA68();

void func_150E68B0(s32 arg0, s32 arg1, s32 arg2, u8 arg3) {
    Game113D60Source *source;
    Vec3f end;
    Vec3f start;
    Vec3f delta;
    Game113D60Emission emission;
    void *result;

    if ((arg0 != 0) && ((D_800C35EA != 1) || (D_800C35E8 != 9))) {
        source = &D_800A1190[arg3];
        if ((func_150ADA68() < source->chance) && (source->start != -1)) {
            if (source->end != -1) {
                D_80088A2C[source->end](&end, arg0);
            } else {
                end.x = 0.0f;
                end.y = 0.0f;
                end.z = 0.0f;
            }
            if (source->start != -1) {
                D_80088A20[source->start](&start);
            } else {
                start.x = 0.0f;
                start.y = 0.0f;
                start.z = 0.0f;
            }
            delta.x = end.x - start.x;
            delta.y = end.y - start.y;
            delta.z = end.z - start.z;
            if ((delta.x != 0) || (delta.z != 0)) {
                if (source->motion != -1) {
                    D_80088A34[source->motion](&start, &end, &delta, &emission);
                } else {
                    emission.x = 0.0f;
                    emission.amplitudeX = 0.0f;
                    emission.phaseX = 0.0f;
                    emission.y = 0.0f;
                    emission.amplitudeY = 0.0f;
                    emission.phaseY = 0.0f;
                }
                emission.rate = func_150ADA68() * D_800A12F8 + D_800A12FC;
                emission.remaining = 0.0f;
                emission.position = start;
                emission.time = 0.0f;
                emission.scale = (func_150ADA68() * 100.0f + 150.0f) * D_800A1300;
                emission.duration = source->duration;
                emission.durationRange = source->durationRange;
                emission.color = source->color;
                result = func_151491F4(func_150ADA68() * 70.0f + 30.0f, -1, 0xF, 1, 0xB, 0x44, 0xFF, 1);
                if (result != NULL) {
                    func_10022EC0((u8 *)result + 0x28, &emission, 0x44);
                }
            }
        }
    }
}

f32 func_15047D60(f32);
f32 func_150ADA68();
f32 func_15144528(f32, f32, f32);
void *func_150E5FD0(void *, void *, f32, f32, f32, s32, s32, s32, s32, s32, s32);
extern f32 D_800BE9A4;

void func_150E6B84(Game113D60Effect *arg0) {
    Game113D60Emission *emission;
    f32 inverse;
    f32 time;
    f32 timeStep;
    f32 phaseStepX;
    f32 phaseStepY;
    f32 speedX;
    f32 speedY;
    f32 factor;
    f32 period;
    Vec3f direction;
    f32 phaseX;
    f32 phaseY;
    f32 sineX;
    f32 sineY;
    f32 randomX;
    f32 randomY;
    u32 randomDuration;
    s32 randomColor;

    emission = &arg0->emission;
    arg0->emission.remaining += arg0->emission.rate * D_800BE9A4;
    if (arg0->emission.remaining > 1.0f) {
        inverse = 1.0f / emission->remaining;
        factor = 0.1f;
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
        } while (emission->remaining > 1.0f);
        period = 6.2831855f;
        emission->phaseX = func_15144528(phaseX, period, 0.0f);
        emission->phaseY = func_15144528(phaseY, period, 0.0f);
        emission->time = time;
    }
}
f32 func_150ADA68();                                /* extern */
typedef struct Game113D60Segment {
    Vec3f start;
    Vec3f end;
} Game113D60Segment;
extern Game113D60Segment *D_80088A44[];
extern Game113D60Segment *D_80088A3C;
extern Game113D60Segment *D_80088A40;
extern f32 D_800A130C;

void func_150E6E34(Vec3f *arg0) {
    Game113D60Segment *segment;

    if (func_150ADA68() < D_800A130C) {
        segment = D_80088A3C;
    } else {
        segment = D_80088A40;
    }
    {
        f32 r = func_150ADA68();

        arg0->x = (segment->end.x - segment->start.x) * r + segment->start.x;
        arg0->y = (segment->end.y - segment->start.y) * r + segment->start.y;
        arg0->z = (segment->end.z - segment->start.z) * r + segment->start.z;
    }
}
extern s32 D_800D9A20[];
extern void func_1514470C(s32 arg0, s32 arg1);

void func_150E6ED8(s32 arg0) {
    func_1514470C(D_800D9A20[func_150ADA20() & 1], arg0);
}
void func_150E6F18(Vec3f *arg0) {
    Game113D60Segment *segment = D_80088A44[func_150ADA20() % 6U];
    f32 t = func_150ADA68();

    arg0->x = (segment->end.x - segment->start.x) * t + segment->start.x;
    arg0->y = (segment->end.y - segment->start.y) * t + segment->start.y;
    arg0->z = (segment->end.z - segment->start.z) * t + segment->start.z;
}
s32 func_1514ECE0();

void func_150E6FAC(f32 *arg0, u8 *arg1) {
    void *model;

    if (func_1514ECE0(*(s32 *)(arg1 + 0x2F4), 0x16, &model) != 0) {
        u8 *node;
        f32 radius;
        s16 angle;
        f32 cosine;
        f32 sine;

        radius = func_150ADA68() * 100.0f + 80.0f;
        angle = func_150ADA20() & 0xFF;
        cosine = func_151423D8(angle - 0x40);
        sine = func_151423D8(angle);
        node = *(u8 **)((u8 *)model + 0x10);
        arg0[0] = *(f32 *)(node + 0x38) * -80.0f + *(f32 *)(arg1 + 0x14) + cosine * radius;
        arg0[1] = *(f32 *)(node + 0x3C) * -80.0f + *(f32 *)(arg1 + 0x18) + 100.0f;
        arg0[2] = *(f32 *)(node + 0x40) * -80.0f + *(f32 *)(arg1 + 0x1C) + sine * radius;
    } else {
        arg0[0] = *(f32 *)(arg1 + 0x14);
        arg0[1] = *(f32 *)(arg1 + 0x18);
        arg0[2] = *(f32 *)(arg1 + 0x1C);
    }
}
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
