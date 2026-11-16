#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_10A350.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150DD640
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

f32 func_150ADA68(void);
extern f32 D_800BE9A4;
extern s32 D_800BE9E4;

typedef struct Game10A350Emission {
    s32 texture;
    char pad4[8];
    s16 frame;
    s16 frame_rate;
    s16 position[3];
    s16 velocity_x;
    s16 velocity_z;
    char pad1A[2];
    u8 fraction_x;
    u8 fraction_y;
    u8 fraction_z;
    s8 callback;
    s16 velocity_y;
    s16 acceleration;
    s16 width;
    s16 height;
    s16 lifetime;
    s8 fade;
    char pad2B;
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
    u8 environment[3];
    char pad33;
    u16 flags;
    char pad36[2];
} Game10A350Emission;

typedef struct Game10A350Record {
    f32 x;
    f32 y;
    f32 z;
    f32 speed;
    f32 width;
    s16 alpha;
    u8 color;
    u8 pad17;
} Game10A350Record;

typedef struct Game10A350State {
    f32 swayX;
    u8 angleX;
    u8 pad5;
    s16 angleXRange;
    f32 swayZ;
    u8 angleZ;
    u8 padD;
    s16 angleZRange;
    f32 x;
    f32 z;
    f32 gravity;
    f32 rate;
    f32 count;
    u8 pad24[5];
    u8 alpha;
    u8 pad2A[2];
    f32 widthBase;
    f32 widthRange;
    u8 widthAngle;
    u8 pad35;
    s16 widthAngleRange;
    f32 speed;
    u8 colorStep;
    u8 pad3D;
    s16 colorStepRange;
    u8 color;
    u8 pad41[0x23];
    f32 spawnRate;
    f32 spawnCount;
    f32 radius;
    s16 pitchBase;
    s16 pitchRange;
    f32 speedBase;
    f32 speedRange;
    s16 lifetime;
    s16 accelBase;
    f32 accelRange;
    s16 fadeBase;
    s16 fadeRange;
    s16 sizeBase;
    u8 pad8A[2];
    f32 sizeRange;
    s32 texture;
    s32 frameRate;
    s8 callback;
    u8 pad99[0x7F];
    s16 timer;
} Game10A350State;

typedef struct Game10A350Actor {
    u8 pad0;
    u8 field1;
    u8 pad2[0xA];
    u8 fieldC;
    u8 padD[3];
    f32 x;
    f32 y;
    f32 z;
    u8 pad1C[2];
    u16 flags;
    u8 pad20[5];
    u8 capacity;
    u8 pad26[6];
    s8 count;
    s8 head;
    s8 tail;
    u8 pad2F;
    s8 active;
    u8 pad31[0x63];
    Game10A350Record *records;
    Game10A350State *state;
} Game10A350Actor;

s32 func_150DCEA0(Game10A350Actor *arg0) {
    Game10A350State *state;
    Game10A350Record *records;
    u8 angle2;
    s32 index;
    f32 stepScale;
    f32 inverse;
    f32 scale;
    f32 x;
    f32 z;
    f32 dx;
    f32 dz;
    f32 speed;

    state = arg0->state;
    records = arg0->records;
    state->angleX += (func_150ADA20() % (u32)(state->angleXRange + 1)) * D_800BE9E4;
    state->angleZ += (func_150ADA20() % (u32)(state->angleZRange + 1)) * D_800BE9E4;
    state->count += state->rate * D_800BE9A4;
    if (state->count > 0.99999f) {
        inverse = 1.0f / state->count;
        {
            Game10A350Emission packet;
            f32 stepX;
            f32 stepZ;
            f32 sine1;
            f32 cosine1;
            f32 sine2;
            f32 cosine2;
            u8 angle;
            s32 ok;

            scale = D_800BE9A4;
            stepScale = D_800BE9A4 * inverse;
            x = state->x;
            z = state->z;
            dx = ((func_151423D8((u8)(state->angleX - 0x40)) * state->swayX) + arg0->x) - state->x;
            dz = ((func_151423D8((u8)(state->angleZ - 0x40)) * state->swayZ) + arg0->z) - state->z;
            if (state->count > 1.0f) {
                stepX = dx * inverse;
                stepZ = dz * inverse;
                do {
                    state->spawnCount += state->spawnRate;
                    if (state->spawnCount > 1.0f) {
                        packet.fraction_x = 0;
                        packet.fraction_z = 0;
                        packet.fraction_y = 0;
                        packet.red = 0xFF;
                        packet.green = 0xFF;
                        packet.blue = 0xFF;
                        packet.environment[0] = 0;
                        packet.environment[1] = 0;
                        packet.environment[2] = 0;
                        packet.alpha = 0xFF;
                        packet.callback = state->callback;
                        packet.flags = 0x12;
                        packet.frame = 0;
                        ok = 1;
                        packet.frame_rate = state->frameRate;
                        packet.texture = state->texture;
                        packet.position[1] = (s16)arg0->y;
                        packet.lifetime = state->lifetime;
                        do {
                            speed = func_150ADA68() * state->speedRange + state->speedBase;
                            angle = func_150ADA20();
                            sine1 = func_151423D8(angle);
                            cosine1 = func_151423D8((u8)(angle - 0x40));
                            angle2 = ((func_150ADA20() % (u32)(state->pitchRange + 1)) + state->pitchBase);
                            sine2 = func_151423D8(angle2);
                            cosine2 = func_151423D8((u8)(angle2 - 0x40));
                            packet.position[0] = (s16)(arg0->x + state->radius * cosine1);
                            packet.position[2] = (s16)(arg0->z + state->radius * sine1);
                            packet.velocity_x = (s16)(speed * sine2 * cosine1);
                            packet.velocity_y = (s16)(-speed * cosine2);
                            packet.velocity_z = (s16)(speed * sine2 * sine1);
                            packet.acceleration = (s16)(func_150ADA68() * state->accelRange + state->accelBase);
                            packet.fade = (func_150ADA20() % (u32)(state->fadeRange + 1)) + state->fadeBase;
                            packet.width = packet.height = (s32)(func_150ADA68() * state->sizeRange + state->sizeBase);
                            if (func_15167D84(&packet, 0, 0, -1, arg0->fieldC, arg0->field1) == NULL) {
                                ok = 0;
                            }
                            state->spawnCount -= 1.0f;
                        } while (state->spawnCount > 1.0f && ok != 0);
                        while (state->spawnCount > 1.0f) {
                            state->spawnCount -= 1.0f;
                        }
                    }
                    records[arg0->tail].x = x;
                    records[arg0->tail].y = arg0->y;
                    records[arg0->tail].z = z;
                    records[arg0->tail].speed = state->speed;
                    state->widthAngle += func_150ADA20() % (u32)(state->widthAngleRange + 1);
                    records[arg0->tail].width = func_151423D8((u8)(state->widthAngle - 0x40)) * state->widthRange + state->widthBase;
                    records[arg0->tail].alpha = state->alpha;
                    records[arg0->tail].color = state->color;
                    state->color += state->colorStep + (func_150ADA20() % (u32)(state->colorStepRange + 1));
                    records[arg0->tail].speed += state->gravity * scale;
                    records[arg0->tail].y += records[arg0->tail].speed * scale;
                    arg0->tail++;
                    if (arg0->tail == arg0->capacity) {
                        arg0->tail = 0;
                    }
                    arg0->count++;
                    if (arg0->tail == arg0->head) {
                        arg0->head++;
                        if (arg0->head == arg0->capacity) {
                            arg0->head = 0;
                        }
                        arg0->count--;
                    }
                    x += stepX;
                    z += stepZ;
                    scale -= stepScale;
                    state->count -= 1.0f;
                } while (state->count > 1.0f);
            }
        }
        state->x = x;
        state->z = z;
    }
    state->timer -= D_800BE9E4;
    if (state->timer < 0) {
        index = arg0->tail - 1;
        if (index < 0) {
            index = arg0->capacity - 1;
        }
        records[index].alpha = 0;
        index--;
        if (index < 0) {
            index = arg0->capacity - 1;
        }
        records[index].alpha = 0x3F;
        index--;
        if (index < 0) {
            index = arg0->capacity - 1;
        }
        records[index].alpha = 0x7F;
        index--;
        if (index < 0) {
            index = arg0->capacity - 1;
        }
        records[index].alpha = 0xBE;
        arg0->active = 0;
        arg0->flags &= ~2;
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_10A350/func_150DD640.s")
