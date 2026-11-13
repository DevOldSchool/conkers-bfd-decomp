#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_39750.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_early_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1500C2F0
 * - func_1500C8D0
 * - func_1500DE88
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800DC460;
extern s32 D_800DC464;
extern s16 D_800DC468;
extern u8 D_800DC46A[];
extern u8 D_800DC63A[];
extern s32 D_800DC63C;

void func_1500C2A0(void) {
    s32 i;

    for (i = 0; i < 233; i++) {
        (&D_800DC468)[i] = 0;
    }
    D_800DC460 = 0;
    D_800DC464 = 0;
    D_800DC63C = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_39750/func_1500C2F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_39750/func_1500C8D0.s")
typedef struct Game39750Effect {
    u8 kind;
    u8 mode;
    s16 flags;
    s16 lifetime;
    u8 pad6[2];
    s32 field08;
    s32 field0C;
    u8 color[4];
    f32 sizeX;
    f32 sizeY;
    f32 pos[3];
    f32 rot[3];
    f32 field34[3];
    s32 field40;
    u8 field44;
    u8 field45;
    u8 field46;
    u8 field47;
    void *field48;
    u8 pad4C[0xC];
} Game39750Effect;

void *func_10022EC0(void *, const void *, u32);
u32 func_10024770(void);
void func_15008340(void *, f32 *, f32 *, f32 *, f32 *);
void func_1510F800(s32);
void *func_1510FD20(s32, s32);
void *func_1513D2F0(void *, void *, u8, u8, u8, u8, u8, s32, s32, s32, u8, s32);
extern u8 D_800A4AA0[];
f32 fabsf(f32);
#pragma intrinsic(fabsf)

#define RANDF() ((f32)((func_10024770() * func_150ADA20()) & 0xFFFF) * inv)

void func_1500CE4C(void *arg0, f32 arg1) {
    f32 count;
    f32 inv;

    count = func_1514462C(arg0) * arg1 * 0.0000002f;
    if (count > 1.0f) {
        Game39750Effect effect;
        f32 extra[7];
        f32 top;
        f32 bottom;

        effect.kind = 0x57;
        effect.mode = 0;
        effect.flags = 0x3B03;
        effect.lifetime = 0x12C;
        effect.field08 = 0;
        effect.field0C = 0;
        effect.color[3] = 0xFF;
        effect.field34[0] = 0.0f;
        effect.field34[1] = 0.0f;
        effect.field34[2] = 0.0f;
        effect.field40 = 0x037C0000;
        effect.field45 = 0xFF;
        effect.field46 = 0;
        effect.field47 = 6;
        extra[5] = 0.0f;
        effect.color[0] = 0xFF;
        effect.color[1] = 0xFF;
        effect.color[2] = 0xFF;
        inv = 0.000015259022f;
        do {
            void *result;

            effect.sizeX = effect.sizeY = RANDF() * 12.0f + 10.0f;
            func_15008340(arg0, &effect.pos[0], &effect.pos[2], &top, &bottom);
            {
                f32 range;

                range = top - bottom;
                effect.pos[1] = RANDF() * (range * 0.5f) + (bottom + range * 0.25f);
                extra[0] = effect.pos[1];
            }
            {
                f32 above;
                f32 below;
                f32 dist;

                above = fabsf(effect.pos[1] - top);
                below = fabsf(effect.pos[1] - bottom);
                dist = (below < above) ? below : above;
                extra[1] = (RANDF() * 0.75f + 0.25f) * dist;
            }
            extra[2] = 2.0f * RANDF() * 3.1415927f;
            extra[3] = RANDF() * 0.013f + 0.0050000004f;
            extra[4] = RANDF();
            extra[6] = RANDF();
            effect.rot[0] = RANDF() * 360.0f;
            effect.rot[1] = RANDF() * 360.0f;
            effect.rot[2] = RANDF() * 360.0f;
            effect.field44 = (func_10024770() * func_150ADA20()) % 156 + 100;
            func_1510F800(0);
            effect.field48 = func_1510FD20(effect.pos[0], effect.pos[2]);
            result = func_1513D2F0(&effect, D_800A4AA0, 0x23, 0, 0, 0x1E, 0, 3, 0xFF, 0x1C, 0xFF, 1);
            if (result != NULL) {
                func_10022EC0((u8 *)result + 0x110, extra, 0x1C);
            }
            count -= 1.0f;
        } while (count > 1.0f);
    }
}
typedef struct {
    f32 scale[10];
    Vec3f position;
    f32 motion[7];
    u32 flags;
    s16 life;
    u16 resource;
    u8 mode, pad59[3];
    void *surface;
    u8 values[12];
    s32 word6C;
    u8 byte70, pad71;
    s16 half72, half74;
    u8 pad76[6];
} Game39750Particle;

u32 func_10024770(void);
void func_15008340(void *, f32 *, f32 *, f32 *, f32 *);
void func_1510F800(s32);
void *func_15132A4C(void *, s32, s32, s32, u8, s32);
f32 fabsf(f32);
#pragma intrinsic(fabsf)

void func_1500D3AC(void *arg0, f32 arg1) {
    f32 count;
    f32 range;
    Game39750Particle particle;
    f32 high;
    f32 low;
    f32 y;
    u32 ticks;

    count = func_1514462C(arg0) * arg1 * 2e-07f;
    if (count > 1.0f) {
        particle.scale[0] = 1.0f;
        particle.scale[1] = 1.0f;
        particle.scale[7] = 1.0f;
        particle.scale[8] = 1.0f;
        particle.scale[9] = 1.0f;
        particle.flags = 0x4D40;
        particle.life = 300;
        particle.mode = 0;
        particle.values[0] = 0xFF;
        particle.values[1] = 0xE;
        particle.values[2] = 0;
        particle.values[3] = 0;
        particle.values[4] = 0;
        particle.values[5] = 0;
        particle.values[6] = 0;
        particle.values[7] = 0;
        particle.values[8] = 2;
        particle.values[10] = 0;
        particle.word6C = 0;
        particle.byte70 = 0;
        particle.half72 = 1;
        particle.half74 = 0xFF;
        particle.resource = 0x53;
        particle.motion[4] = 0.0f;
        do {
            func_15008340(arg0, &particle.position.x, &particle.position.z, &high, &low);
            range = high - low;
            ticks = func_10024770();
            y = (f32)((func_150ADA20() * ticks) & 0xFFFF) * 1.5259022e-05f * (range * 0.5f) + (low + range * 0.25f);
            particle.motion[1] = y;
            {
                f32 above = fabsf(y - high);
                f32 below;
                f32 dist;

                particle.position.y = y;
                below = fabsf(y - low);
                dist = (below < above) ? below : above;
                ticks = func_10024770();
                particle.motion[6] = ((f32)((func_150ADA20() * ticks) & 0xFFFF) * 1.5259022e-05f * 0.75f + 0.25f) * dist;
            }
            ticks = func_10024770();
            particle.motion[0] = (f32)((func_150ADA20() * ticks) & 0xFFFF) * 1.5259022e-05f * 2.0f * 3.1415927f;
            ticks = func_10024770();
            particle.motion[2] = (f32)((func_150ADA20() * ticks) & 0xFFFF) * 1.5259022e-05f * 0.013f + 0.0050000004f;
            ticks = func_10024770();
            particle.scale[4] = (f32)((func_150ADA20() * ticks) & 0xFFFF) * 1.5259022e-05f * 360.0f;
            ticks = func_10024770();
            particle.scale[5] = (f32)((func_150ADA20() * ticks) & 0xFFFF) * 1.5259022e-05f * 360.0f;
            ticks = func_10024770();
            particle.scale[6] = (f32)((func_150ADA20() * ticks) & 0xFFFF) * 1.5259022e-05f * 360.0f;
            ticks = func_10024770();
            particle.motion[3] = (f32)((func_150ADA20() * ticks) & 0xFFFF) * 1.5259022e-05f * 1.6f;
            ticks = func_10024770();
            particle.motion[5] = (f32)((func_150ADA20() * ticks) & 0xFFFF) * 1.5259022e-05f * 1.6f;
            ticks = func_10024770();
            particle.scale[3] = particle.scale[2] = (f32)((func_150ADA20() * ticks) & 0xFFFF) * 1.5259022e-05f * 0.25f + 1.0f;
            func_1510F800(0);
            particle.surface = func_1510FD20((s32)particle.position.x, (s32)particle.position.z);
            func_15132A4C(&particle, 3, 0xFF, 0, 0xFF, 1);
            count -= 1.0f;
        } while (count > 1.0f);
    }
}
void func_1500D8C8(void *arg0, f32 arg1) {
    f32 count;
    f32 range;
    Game39750Particle particle;
    f32 high;
    f32 low;
    f32 y;

    count = func_1514462C(arg0) * arg1 * 2e-06f;
    if (count > 1.0f) {
        particle.scale[0] = 1.0f;
        particle.scale[1] = 1.0f;
        particle.scale[7] = 1.0f;
        particle.scale[8] = 1.0f;
        particle.scale[9] = 1.0f;
        particle.flags = 0x4D40;
        particle.life = 300;
        particle.mode = 0;
        particle.values[0] = 0xFF;
        particle.values[1] = 0xE;
        particle.values[2] = 0;
        particle.values[3] = 0;
        particle.values[4] = 0;
        particle.values[5] = 0;
        particle.values[6] = 0;
        particle.values[7] = 0;
        particle.values[8] = 2;
        particle.values[10] = 0;
        particle.word6C = 0;
        particle.byte70 = 0;
        particle.half72 = 1;
        particle.half74 = 0xFF;
        particle.motion[4] = 0.0f;
        do {
            const u16 resources[14] = { 0x76, 0x77, 0x78, 0x79, 0x53, 0x3E, 0x3D, 0x39, 0x02, 0x03, 0x4E, 0x4F, 0x50, 0x51 };
            u32 ticks;

            func_15008340(arg0, &particle.position.x, &particle.position.z, &high, &low);
            range = high - low;
            ticks = func_10024770();
            y = (f32)((func_150ADA20() * ticks) & 0xFFFF) * 1.5259022e-05f * (range * 0.5f) + (low + range * 0.25f);
            particle.motion[1] = y;
            {
                f32 above = fabsf(y - high);
                f32 below;
                f32 dist;

                particle.position.y = y;
                below = fabsf(y - low);
                dist = (below < above) ? below : above;
                ticks = func_10024770();
                particle.motion[6] = ((f32)((func_150ADA20() * ticks) & 0xFFFF) * 1.5259022e-05f * 0.75f + 0.25f) * dist;
            }
            ticks = func_10024770();
            particle.motion[0] = (f32)((func_150ADA20() * ticks) & 0xFFFF) * 1.5259022e-05f * 2.0f * 3.1415927f;
            ticks = func_10024770();
            particle.motion[2] = (f32)((func_150ADA20() * ticks) & 0xFFFF) * 1.5259022e-05f * 0.013f + 0.0050000004f;
            ticks = func_10024770();
            particle.scale[4] = (f32)((func_150ADA20() * ticks) & 0xFFFF) * 1.5259022e-05f * 360.0f;
            ticks = func_10024770();
            particle.scale[5] = (f32)((func_150ADA20() * ticks) & 0xFFFF) * 1.5259022e-05f * 360.0f;
            ticks = func_10024770();
            particle.scale[6] = (f32)((func_150ADA20() * ticks) & 0xFFFF) * 1.5259022e-05f * 360.0f;
            ticks = func_10024770();
            particle.motion[3] = (f32)((func_150ADA20() * ticks) & 0xFFFF) * 1.5259022e-05f * 1.6f;
            ticks = func_10024770();
            particle.motion[5] = (f32)((func_150ADA20() * ticks) & 0xFFFF) * 1.5259022e-05f * 1.6f;
            ticks = func_10024770();
            particle.resource = resources[(func_150ADA20() * ticks) % 14];
            ticks = func_10024770();
            particle.scale[3] = (f32)((func_150ADA20() * ticks) & 0xFFFF) * 1.5259022e-05f * 0.25f + 0.5f;
            particle.scale[2] = particle.scale[3];
            if (particle.resource == 0x39) {
                particle.scale[2] *= 0.35f;
                particle.scale[3] *= 0.35f;
            }
            func_1510F800(0);
            particle.surface = func_1510FD20((s32)particle.position.x, (s32)particle.position.z);
            func_15132A4C(&particle, 3, 0xFF, 0, 0xFF, 1);
            count -= 1.0f;
        } while (count > 1.0f);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_39750/func_1500DE88.s")
