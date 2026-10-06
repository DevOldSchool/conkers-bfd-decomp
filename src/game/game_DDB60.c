#include "types.h"

/*
 * Reviewed source unit: src/game/game_DDB60.c
 * Boundary evidence: docs/evidence/game_raw_direct_call_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B06B0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameDDB60Vector { f32 x, y, z; } GameDDB60Vector;
typedef struct GameDDB60Actor {
    u8 pad00[4];
    u8 kind;
    u8 pad05[0xF];
    GameDDB60Vector position;
} GameDDB60Actor;
typedef struct GameDDB60Hit {
    f32 height;
    s16 vertices[3][3];
    u8 pad16[2];
    s32 owner;
    u8 flags, kind;
    u8 pad1E[2];
    void *record;
} GameDDB60Hit;
typedef struct GameDDB60Emitter {
    s32 count, countRange;
    GameDDB60Vector position;
    s16 yaw, yawRange, pitch, pitchRange;
    f32 field1C, field20, field24, field28;
    s16 field2C, field2E;
    f32 field30, field34, field38;
} GameDDB60Emitter;
typedef struct GameDDB60Particles {
    GameDDB60Vector position;
    f32 field0C, field10, field14, field18, field1C, field20;
    s16 field24, field26, field28, field2A, field2C, field2E, field30, field32;
    u8 mode;
    u8 pad35[3];
    f32 field38;
    s16 field3C, field3E;
    s32 field40;
} GameDDB60Particles;
s16 func_15143E24(void *);
void func_15152190(void *, void *, void *, s32, f32, s32, s32, s32);
void func_1504715C(void *, void *);
void func_15153F18(s16 *, void *, void *, s32, s32);
void func_151C329C(void *, u8, s32);
extern u8 D_8009F810[], D_8009F814[], D_8009F818[], D_8009F81C[];
extern f32 D_8009F820, D_8009F824, D_8009F828, D_8009F82C, D_8009F830;
extern f32 D_8009F834, D_8009F838, D_8009F83C, D_8009F840, D_8009F844;
extern f32 D_8009F848, D_8009F84C, D_8009F850, D_8009F854, D_8009F858, D_8009F85C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B06B0 CURRENT (4624) */
void func_150B06B0(GameDDB60Actor *arg0, void *arg1, s32 arg2, s32 arg3) {
    GameDDB60Vector position;
    s8 angle;
    GameDDB60Hit hit;
    GameDDB60Vector raised;
    GameDDB60Emitter special;
    GameDDB60Emitter normal;
    GameDDB60Particles particles;
    s16 direction[4];
    register s32 flags;

    flags = arg2 & 0xFF;
    position.x = arg0->position.x;
    position.y = arg0->position.y;
    position.z = arg0->position.z;
    angle = func_15143E24(arg1) + 0x40;
    func_1504715C(&hit, arg0);
    if (arg0->kind == 0xA6) {
        raised.y = position.y + 50.0f;
        raised.x = position.x;
        raised.z = position.z;
        func_151C329C(&raised, (u8)flags, arg3);
        special.count = 10;
        special.countRange = 10;
        special.position = position;
        special.field1C = 7.0f;
        special.field20 = 17.0f;
        special.yaw = angle - 0x28;
        special.yawRange = 0x50;
        special.pitch = -0x2D;
        special.pitchRange = 0x1A;
        special.field2C = 0x19;
        special.field2E = 0x19;
        special.field24 = D_8009F820;
        special.field28 = D_8009F824;
        special.field30 = D_8009F828;
        special.field34 = D_8009F82C;
        special.field38 = D_8009F830;
        func_15152190(&special, D_8009F810, D_8009F814, 1, 0.0f, 0, flags, arg3);
        return;
    }
    normal.count = 10;
    normal.countRange = 10;
    normal.position = position;
    normal.field1C = 7.0f;
    normal.field20 = 17.0f;
    normal.yaw = angle - 0x28;
    normal.yawRange = 0x50;
    normal.pitch = -0x15;
    normal.pitchRange = 0xD;
    normal.field2C = 0x19;
    normal.field2E = 0x19;
    normal.field24 = D_8009F834;
    normal.field28 = D_8009F838;
    normal.field30 = D_8009F83C;
    normal.field34 = D_8009F840;
    normal.field38 = D_8009F844;
    func_15152190(&normal, D_8009F818, D_8009F81C, 1, 0.0f, 0, flags, arg3);
    particles.position = position;
    particles.field0C = D_8009F848;
    particles.field24 = 7;
    particles.field26 = 3;
    direction[0] = angle - 0x3C;
    direction[1] = 0x78;
    direction[2] = -0x1E;
    direction[3] = 0x10;
    particles.field28 = 3;
    particles.field2A = 2;
    particles.field2C = 0x14;
    particles.field2E = 0x14;
    particles.field30 = 0x9B;
    particles.field32 = 0x64;
    particles.field3C = 0x10;
    particles.field3E = 0xF;
    particles.field40 = 0;
    particles.mode = 0;
    particles.field10 = D_8009F84C;
    particles.field14 = D_8009F850;
    particles.field18 = D_8009F854;
    particles.field1C = D_8009F858;
    particles.field20 = D_8009F85C;
    particles.field38 = 0.5f;
    func_15153F18(direction, &particles, &hit, (u8)flags, arg3);
    particles.mode = 1;
    func_15153F18(direction, &particles, &hit, (u8)flags, arg3);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B06B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DDB60/func_150B06B0.s")
