#include "types.h"

/*
 * Reviewed source unit: src/game/game_10DD20.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_directly_called_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E0870
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game10DD20Position { f32 x, y, z; } Game10DD20Position;
typedef struct Game10DD20Object {
    u8 pad00[0x14];
    Game10DD20Position position;
} Game10DD20Object;
typedef struct Game10DD20Hit {
    f32 height;
    s16 vertices[3][3];
    u8 pad16[2];
    s32 owner;
    u8 flags, kind;
    u8 pad1E[2];
    void *record;
} Game10DD20Hit;

void func_10010630(u16, void *, s32, s16, u16);
s32 func_15046C80(void *, u16, f32, void *);
void func_1504715C(void *, void *);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_150E7FEC(f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_150E83AC(void *, s16, u8, s32);
void func_151541B8(s32, f32, s32, f32, f32, u8, s32);
void func_15136C3C(void *, s32, s32, s32, s32, s32, s32, s32);
void func_151D3FF4(s32, u8, s32);
void func_151D40D4(void *, s32, s32, s32, s32, s32, s32, s32);
void func_151D5334(s32, s32, s32, s32, s32, s32, s32);
void func_151D5404(void *, f32, f32, f32, s16, s16);
void func_151D5514(s32, u8, s32);
extern u8 D_800C35EA;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E0870 CURRENT (6232) */
void func_150E0870(Game10DD20Object *arg0, s32 arg1, s32 arg2) {
    Game10DD20Position origin;
    Game10DD20Position impact;
    u8 hitValid;
    Game10DD20Position top;
    Game10DD20Hit hit;
    u32 random;
    f32 randomFloat;
    Game10DD20Position *position;
    s32 flags;

    flags = arg1 & 0xFF;
    if (arg0 != 0) {
        if (D_800C35EA != 1) {
            func_10010630(0x2BB, arg0, 0x7FFF, 0x3E8, 0x7D0);
            func_10010630(0x2BA, arg0, 0x7FFF, 0x3E8, 0x7D0);
        }
        origin.x = arg0->position.x;
        origin.y = arg0->position.y + 20.0f;
        hitValid = 0;
        origin.z = arg0->position.z;
        top.x = origin.x;
        top.z = origin.z;
        top.y = origin.y + 100.0f;
        func_1504715C(&hit, arg0);
        if (func_15046C80(&top, 0, origin.y - 200.0f, &hit) != 0 && (hit.flags & 1)) {
            impact.x = top.x;
            hitValid = 1;
            impact.y = hit.height;
            impact.z = top.z;
            randomFloat = func_150ADA68();
            random = func_150ADA20();
            func_150E7FEC(randomFloat * 125.0f + 204.0f, (random % 101U + 0x9B) & 0xFF,
                (s32)hit.vertices, (s32)&impact, func_150ADA20() % 302U + 0x1F4,
                0, 1, 0, 0, 0, flags, 0);
        }
        /* Follow the accepted callee's six-argument contract. */
        func_151D5404(&origin, 506.0f, 1013.0f, 0.0009871669f, 0xF, 0x14);
        func_151D5334((s32)&origin, 0x43FD0000, 0x447D4000, 0x3A8163D3, 5, flags, arg2);
        func_151D5514((s32)&origin, (u8)flags, arg2);
        func_151D3FF4((s32)&origin, (u8)flags, arg2);
        position = &origin;
        if (hitValid != 0) {
            position = &impact;
        }
        func_150E83AC(position, (s16)(func_150ADA20() % 62U + 0x78), (u8)flags, arg2);
        randomFloat = func_150ADA68();
        random = func_150ADA20() % 56U + 0xC8;
        func_151541B8((s32)&origin, randomFloat * 4.0f + 12.0f, 0x3FD20C49, (f32)random, 0.0f, flags, arg2);
        func_15136C3C(arg0, 1, 1, 1, 1, 0, flags, arg2);
        func_151D40D4(&origin, 0, (s32)arg0, (s32)arg0, 0, 0x16, 0x15, 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E0870 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10DD20/func_150E0870.s")
