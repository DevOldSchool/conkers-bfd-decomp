#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_10C170.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150DECC0
 * - func_150DF334
 * - func_150DF4B8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_10C170/func_150DECC0.s")

extern s32 func_1504697C(Vec3f *, s32, f32, f32 *);
extern u32 func_150ADA20(void);
extern void func_150E83AC(Vec3f *, s16, u8, s32);
extern void func_151A9834(Vec3f *, f32, f32, f32 *, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DF334 CURRENT (2624) */
void func_150DF334(void *arg0) {
    f32 hit;
    volatile u8 flag;
    Vec3f alternate;
    Vec3f start;
    Vec3f result;
    Vec3f *position;

    flag = 0;
    start.x = *(f32 *)((u8 *)arg0 + 0x28);
    start.y = *(f32 *)((u8 *)arg0 + 0x2C) + 500.0f;
    start.z = *(f32 *)((u8 *)arg0 + 0x30);
    if (func_1504697C(&start, 0, start.y - 1000.0f, &hit) != 0) {
        alternate.x = *(f32 *)((u8 *)arg0 + 0x28);
        alternate.y = hit;
        flag = 1;
        alternate.z = *(f32 *)((u8 *)arg0 + 0x30);
    }
    position = (Vec3f *)((u8 *)arg0 + 0x28);
    if (flag != 0) {
        position = &alternate;
    }
    func_150E83AC(position, (s16)((func_150ADA20() % 62U) + 0x78),
                   *(u8 *)((u8 *)arg0 + 0xC), *(u8 *)((u8 *)arg0 + 1));
    position = (Vec3f *)((u8 *)arg0 + 0x28);
    if (flag != 0) {
        position = &alternate;
    }
    result = *position;
    result.y += 500.0f;
    func_151A9834(&result, result.y - 1000.0f, 250.0f, &hit,
                   (func_150ADA20() % 3U) + 3, 1, 0,
                   *(u8 *)((u8 *)arg0 + 0xC), *(u8 *)((u8 *)arg0 + 1));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DF334 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10C170/func_150DF334.s")
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
extern f32 D_800A0F28;
extern f32 D_800A0F2C;
extern f32 D_800A0F30;
extern f32 D_800A0F34;
extern f32 D_800A0F38;
extern f32 D_800A0F3C;
extern f32 D_800A0F40;
extern f32 D_800A0F44;
extern f32 D_800A0F48;
extern f32 D_800A0F4C;
extern f32 D_800A0F50;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DF4B8 CURRENT (7325) */
void func_150DF4B8(Vec3f *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Game10C170Particle particle;
    f32 firstScale;
    f32 secondScale;
    f32 firstBase;
    f32 secondBase;
    u8 channel;
    s32 count;

    channel = arg3 & 0xFF;
    particle.position = *arg0;
    firstScale = func_150ADA68() * 0.5f + 1.0f;
    secondScale = func_150ADA68();
    firstBase = D_800A0F28;
    secondBase = D_800A0F2C;
    particle.field0C = firstBase * firstScale;
    particle.field14 = secondBase * firstScale;
    secondScale = secondScale * 0.5f + 1.0f;
    particle.field20 = 0x6231;
    particle.field22 = 0x1A4D;
    particle.field10 = D_800A0F30 * secondScale;
    particle.field18 = D_800A0F34 * secondScale;
    particle.field1C = D_800A0F38 * secondScale;
    arg1 = 151;
    particle.field24 = func_150ADA20() % (u32)arg1 + 0x96;
    particle.field26 = 0;
    particle.field27 = 0;
    particle.field28 = 0;
    particle.field29 = 0xFF;
    particle.field2A = 1;
    arg2 = 156;
    particle.field2C = func_150ADA20() % (u32)arg2 + 0x64;
    particle.field2D = 0xFF;
    particle.field2E = 0;
    particle.field2F = 1;
    particle.field30 = 0;
    particle.field34 = 0xF;
    particle.field3C = D_800A0F3C;
    particle.field40 = D_800A0F40;
    particle.field38 = 0.0f;
    particle.field44 = D_800A0F44;
    func_15149550(&particle.position.x, 0xA, 0, 0, channel, arg4);
    count = func_150ADA20() % 3U + 1;
    if (count > 0) {
        do {
            func_15143874((s16)(func_150ADA20() & 0xFF), 30.0f, &particle.position.x, &particle.position.z);
            particle.position.x += arg0->x;
            particle.position.z += arg0->z;
            firstScale = func_150ADA68() * 0.5f + 0.75f;
            secondScale = func_150ADA68();
            particle.field0C = firstBase * firstScale;
            particle.field14 = secondBase * firstScale;
            secondScale = secondScale * 0.5f + 0.75f;
            particle.field10 = D_800A0F48 * secondScale;
            particle.field18 = D_800A0F4C * secondScale;
            particle.field1C = D_800A0F50 * secondScale;
            particle.field24 = func_150ADA20() % (u32)arg1 + 0x96;
            particle.field2C = func_150ADA20() % (u32)arg2 + 0x64;
            particle.field2F = 0;
            func_15149550(&particle.position.x, 0xA, 0, 0, channel, arg4);
            count--;
        } while (count != 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150DF4B8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10C170/func_150DF4B8.s")
