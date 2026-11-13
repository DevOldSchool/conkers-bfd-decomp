#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_10C170.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150DECC0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_10C170/func_150DECC0.s")

extern s32 func_1504697C(Vec3f *, u16, f32, Game71820Hit *);
extern void func_150E83AC(Vec3f *, s16, u8, s32);
extern void func_151A9834(Vec3f *, f32, f32, f32 *, s32, s32, s32, s32, s32);

void func_150DF334(void *arg0) {
    Vec3f *position;
    Game71820Hit hit;
    u8 flag;
    Vec3f alternate;
    Vec3f start;
    Vec3f result;

    flag = 0;
    position = (Vec3f *)((u8 *)arg0 + 0x28);
    start.x = position->x;
    start.y = position->y + 500.0f;
    start.z = position->z;
    if (func_1504697C(&start, 0, start.y - 1000.0f, &hit) != 0) {
        alternate.x = position->x;
        alternate.y = hit.height;
        alternate.z = position->z;
        flag = 1;
    }
    func_150E83AC(flag ? &alternate : position, (s16)((func_150ADA20() % 62U) + 0x78),
                  *(u8 *)((u8 *)arg0 + 0xC), *(u8 *)((u8 *)arg0 + 1));
    result = *(flag ? &alternate : position);
    result.y += 500.0f;
    func_151A9834(&result, result.y - 1000.0f, 250.0f, &hit.height, (func_150ADA20() % 3U) + 3, 1, 0,
                  *(u8 *)((u8 *)arg0 + 0xC), *(u8 *)((u8 *)arg0 + 1));
}
typedef struct Game10C170Particle {
    Vec3f position;
    f32 field0C;
    f32 field10;
    f32 field14;
    f32 field18;
    f32 field1C;
    s16 field20;
    s16 field22;
    s16 field24;
    u8 field26;
    u8 field27;
    u8 field28;
    u8 field29;
    s16 field2A;
    u8 field2C;
    u8 field2D;
    u8 field2E;
    u8 field2F;
    s32 field30;
    u8 field34;
    f32 field38;
    f32 field3C;
    f32 field40;
    f32 field44;
} Game10C170Particle;

f32 func_150ADA68(void);
void *func_15149550(f32 *, u8, u8, u8, u8, s32);

void func_150DF4B8(Vec3f *arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    Game10C170Particle particle;
    f32 firstScale;
    f32 secondScale;
    s32 count;

    particle.position = *arg0;
    firstScale = func_150ADA68() * 0.5f + 1.0f;
    secondScale = func_150ADA68() * 0.5f + 1.0f;
    particle.field0C = 22.6f * firstScale;
    particle.field14 = 13.786f * firstScale;
    particle.field10 = 57.969f * secondScale;
    particle.field18 = 42.714f * secondScale;
    particle.field1C = 118.763f * secondScale;
    particle.field20 = 0x6231; particle.field22 = 0x1A4D;
    particle.field24 = func_150ADA20() % 151 + 150;
    particle.field26 = 0;
    particle.field27 = 0;
    particle.field28 = 0;
    particle.field29 = 0xFF;
    particle.field2A = 1;
    particle.field2C = func_150ADA20() % 156 + 100;
    particle.field2D = 0xFF;
    particle.field2E = 0;
    particle.field2F = 1;
    particle.field30 = 0;
    particle.field34 = 0xF;
    particle.field38 = 0.0f;
    particle.field3C = 10000.0f;
    particle.field40 = 0.045f;
    particle.field44 = 0.7f;
    func_15149550(&particle.position.x, 10, 0, 0, arg3, arg4);
    count = func_150ADA20() % 3 + 1;
    for (; count > 0; count--) {
        func_15143874(func_150ADA20() & 0xFF, 30.0f, &particle.position.x, &particle.position.z);
        particle.position.x += arg0->x;
        particle.position.z += arg0->z;
        firstScale = func_150ADA68() * 0.5f + 0.75f;
        secondScale = func_150ADA68() * 0.5f + 0.75f;
        particle.field0C = 22.6f * firstScale;
        particle.field14 = 13.786f * firstScale;
        particle.field10 = 57.969f * secondScale;
        particle.field18 = 42.714f * secondScale;
        particle.field1C = 118.763f * secondScale;
        particle.field24 = func_150ADA20() % 151 + 150;
        particle.field2C = func_150ADA20() % 156 + 100;
        particle.field2F = 0;
        func_15149550(&particle.position.x, 10, 0, 0, arg3, arg4);
    }
}
