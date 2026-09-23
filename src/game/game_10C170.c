#include "types.h"

/*
 * Reviewed source unit: src/game/game_10C170.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150DECC0
 * - func_150DF334
 * - func_150DF4B8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_10C170/func_150DECC0.s")
typedef struct Game10C170Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Game10C170Vec3;

extern s32 func_1504697C(Game10C170Vec3 *, s32, f32, f32 *);
extern u32 func_150ADA20(void);
extern void func_150E83AC(Game10C170Vec3 *, s16, u8, s32);
extern void func_151A9834(Game10C170Vec3 *, f32, f32, f32 *, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150DF334 CURRENT (2624) */
void func_150DF334(void *arg0) {
    f32 hit;
    volatile u8 flag;
    Game10C170Vec3 alternate;
    Game10C170Vec3 start;
    Game10C170Vec3 result;
    Game10C170Vec3 *position;

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
    position = (Game10C170Vec3 *)((u8 *)arg0 + 0x28);
    if (flag != 0) {
        position = &alternate;
    }
    func_150E83AC(position, (s16)((func_150ADA20() % 62U) + 0x78),
                   *(u8 *)((u8 *)arg0 + 0xC), *(u8 *)((u8 *)arg0 + 1));
    position = (Game10C170Vec3 *)((u8 *)arg0 + 0x28);
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_10C170/func_150DF4B8.s")
