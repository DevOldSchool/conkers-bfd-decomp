#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1EF500.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_dense_pointer_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151C229C
 * - func_151C2734
 * - func_151C2AD0
 * - func_151C2F48
 * - func_151C329C
 * - func_151C36D8
 * - func_151C3B0C
 * - func_151C436C
 * - func_151C43E0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1EF500EmitterVector {
    f32 x;
    f32 y;
    f32 z;
} Game1EF500EmitterVector;

typedef struct {
    u8 pad0[0x3A0];
    f32 angle;
} Game1C2050Player;

typedef struct {
    u8 pad0[0x318];
    Game1C2050Player *player;
} Game1C2050Owner;

typedef struct {
    u8 pad0[0x2C];
    s16 id;
} Game1C2050Scene;

void func_1000E7A0(u32, s32);
s32 func_100114D0(s32, s32, s32, s32, s32, s32, s32 *, s32 *, s32 *);
s32 func_1510F8CC(s32);
s32 func_1000B060(f32, f32, u32);
extern f32 D_800AAA30, D_800AAA34;
extern Game1C2050Scene *D_800B0DF0;
extern u8 D_800BE616;

void func_151C2050(Game1C2050Owner *arg0, Game1EF500EmitterVector *arg1,
                    Game1EF500EmitterVector *arg2, s32 arg3, f32 arg4) {
    s32 pan;
    s32 volume;
    s16 scene;
    s32 direction;
    s16 playerScene;
    Game1C2050Player *player;
    f32 intensity;

    if (arg0 != 0) {
        if (D_800BE616 != 0 || (player = arg0->player) == 0) {
            scene = D_800B0DF0->id;
            if (scene == 0x24 || scene == 0x13 || scene == 0x4D || scene == 0x85 || scene == 0x93) {
                func_100114D0((s32)arg1->x, (s32)arg1->y, (s32)arg1->z,
                    0x7FFF, 0x3E8, 0x64, &pan, &volume, 0);
                if ((u32)volume >= 0x1001U) {
                    volume = (u32)volume >> 7;
                    func_1000E7A0(8, (func_1510F8CC(arg3) + 1) | (volume << 8) | (pan << 16));
                }
            }
        } else {
            playerScene = D_800B0DF0->id;
            if (playerScene == 0x24 || playerScene == 0x13) {
                intensity = 255.0f - arg4 * D_800AAA30;
                if (intensity > 16.0f) {
                    direction = func_1000B060(arg2->x, arg2->z, (u32)(player->angle * D_800AAA34));
                    func_1000E7A0(8, (func_1510F8CC(arg3) + 1) | ((s32)intensity << 8) | (direction << 16));
                }
            }
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C229C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C2734.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C2AD0.s")
s32 func_151C2E4C(void *arg0, void *arg1) {
    if (arg0 == arg1) {
        return 0;
    }
    if (*(s32 *)((u8 *)arg0 + 0) == 0) {
        return 0;
    }
    if (*(u8 *)((u8 *)arg0 + 4) == 0xFF) {
        return 0;
    }
    return 1;
}
s32 func_151C2E94(void *arg0, void *arg1) {
    if (arg0 == arg1) {
        return 0;
    }
    if (*(s32 *)((u8 *)arg0 + 0) == 0) {
        return 0;
    }
    if (*(u8 *)((u8 *)arg0 + 4) == 0xFF) {
        return 0;
    }
    if (*(u8 *)((u8 *)arg0 + 0x127) == 0xFF) {
        return 0;
    }
    return 1;
}
void func_151D4DAC(s32, s32, s32, s32, s32, s32, void *, s32, s32);
void func_15081690(f32, s32, s32, s32, f32, f32, f32, void *, f32,
                   s32, s32, s32, s32, s32, s32);

void func_151C2EF0(s32 arg0, s32 arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_151D4DAC(arg0, arg1, arg3, arg4, arg5, *(s32 *)((u8 *)arg2 + 0x1B4), (u8 *)arg2 + 0x170, *(u8 *)((u8 *)arg2 + 0xC), *(u8 *)((u8 *)arg2 + 1));
}

typedef struct Game1EF500EmitterParticle {
    s32 field0;
    s32 field4;
    Game1EF500EmitterVector position8;
    f32 field14;
    f32 field18;
    f32 field1C;
    f32 field20;
    f32 field24;
    f32 field28;
    s16 field2C;
    s16 field2E;
    s16 field30;
    s16 field32;
    s32 field34;
    s32 field38;
    s16 field3C;
    s16 field3E;
    s16 field40;
    u8 fields42[23];
    s32 field5C;
    s32 field60;
    s16 field64;
    s16 field66;
    s16 field68;
    u8 field6A;
    f32 field6C;
    s8 fields70[4];
} Game1EF500EmitterParticle;

typedef struct Game1EF500EmitterLight {
    u8 field0;
    s8 field1;
    s16 field2;
    u8 field4;
} Game1EF500EmitterLight;

typedef struct Game1EF500EmitterState {
    u8 pad0[0x30];
    Game1EF500EmitterVector position30;
    u8 pad3C[0x30];
    Game1EF500EmitterVector vector6C;
    u8 pad78[0x10];
    s32 field88;
} Game1EF500EmitterState;

typedef struct Game1EF500EmitterOwner {
    u8 pad0;
    u8 field1;
    u8 pad2[0xA];
    u8 fieldC;
    u8 padD[0x103];
    Game1EF500EmitterState state110;
} Game1EF500EmitterOwner;

s32 func_15102920(f32, s32, void *, void *, s32, s32, s32, s32, s32, s32);
s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_15152B38(void *, s32, s32);
u32 func_150ADA20();
f32 func_150ADA68();
extern f32 D_800AAA3C;
extern f32 D_800AAA40;
extern u8 D_800DCA20;
extern f32 D_800DCA24;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C2F48 CURRENT (570) */
void func_151C2F48(Game1EF500EmitterOwner *arg0) {
    Game1EF500EmitterVector *position;
    Game1EF500EmitterLight light;
    s32 coordinates[3];
    Game1EF500EmitterParticle descriptor;
    f32 random;
    Game1EF500EmitterState *state;

    random = func_150ADA68();
    state = (Game1EF500EmitterState *)((u8 *)arg0 + 0x110);
    position = &state->position30;
    func_15102920(random * 30.0f + 8.0f, 0xFF, &state->vector6C, position,
                 (func_150ADA20() % 46U) + 0x19, 1, 1, state->field88,
                 arg0->fieldC, arg0->field1);
    if (func_150ADA68() < D_800AAA3C * D_800DCA24) {
        light.field0 = 3;
        light.field1 = -1;
        light.field2 = (func_150ADA20() % 7U) + 4;
        light.field4 = 0;
        coordinates[0] = (s32)state->position30.x;
        coordinates[1] = (s32)state->position30.y;
        coordinates[2] = (s32)state->position30.z;
        func_151602C0((u8 *)&light, coordinates, (func_150ADA20() % 9U) + 0xC,
                     0xFF, 0xFF, 0xFF, 0xFF, 0, 0, arg0->fieldC, arg0->field1);
        descriptor.field0 = 5 >> D_800DCA20;
        descriptor.field4 = 4 >> D_800DCA20;
        descriptor.position8 = *position;
        descriptor.field14 = 8.25f;
        descriptor.field18 = D_800AAA40;
        descriptor.field1C = descriptor.field20 = 0.0f;
        descriptor.field24 = 7.0f;
        descriptor.field28 = 16.0f;
        descriptor.field2C = 0;
        descriptor.field2E = 0xFF;
        descriptor.field30 = -0x3D;
        descriptor.field32 = 0x50;
        descriptor.field34 = 3;
        descriptor.field38 = 1;
        descriptor.field3C = 0xC;
        descriptor.field3E = 0xA;
        descriptor.field40 = 1;
        descriptor.fields42[0] = 4;
        descriptor.fields42[1] = 2;
        descriptor.fields42[2] = 3;
        descriptor.fields42[3] = 0xFF;
        descriptor.fields42[4] = 0xFF;
        descriptor.fields42[5] = 0xFF;
        descriptor.fields42[6] = 0xFF;
        descriptor.fields42[7] = 0;
        descriptor.fields42[8] = 0;
        descriptor.fields42[9] = 0;
        descriptor.fields42[10] = 0;
        descriptor.fields42[11] = 0xFF;
        descriptor.fields42[12] = 0xFF;
        descriptor.fields42[13] = 0xFF;
        descriptor.fields42[14] = 0xFF;
        descriptor.fields42[15] = 0;
        descriptor.fields42[16] = 0;
        descriptor.fields42[17] = 0;
        descriptor.fields42[18] = 0;
        descriptor.fields42[19] = 0xFF;
        descriptor.fields42[20] = 0;
        descriptor.fields42[21] = 3;
        descriptor.fields42[22] = 0x24;
        descriptor.field5C = 0x200005;
        descriptor.field60 = 0x60600;
        descriptor.field64 = 0xA;
        descriptor.field66 = 0x19;
        descriptor.field68 = 1;
        descriptor.field6A = 0;
        descriptor.field6C = 1.0f;
        descriptor.fields70[0] = -1;
        descriptor.fields70[1] = 0;
        descriptor.fields70[2] = -1;
        descriptor.fields70[3] = -1;
        func_15152B38(&descriptor, arg0->fieldC, arg0->field1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C2F48 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C2F48.s")
typedef struct Game1EF500EmitterSpawn {
    s32 field0;
    s32 field4;
    s16 field8;
    s16 fieldA;
    s32 fieldC;
    s32 field10;
    u8 colors14[9];
    u8 field1D;
    s16 field1E;
    s16 field20;
    s16 field22;
    f32 field24;
    f32 field28;
    f32 field2C;
    Game1EF500EmitterVector position30;
    f32 field3C;
    f32 field40;
    f32 field44;
    f32 field48;
    f32 field4C;
    f32 field50;
    f32 field54;
    s32 field58;
    s32 field5C;
    s8 fields60[6];
    /* The constructor copies a full 0x70-byte record; these fields are unused here. */
    u8 fields66[0xA];
} Game1EF500EmitterSpawn;

void *func_15130280(void *, u8, void *, s32, u8, s32);
extern f32 D_800AAA54;
extern f32 D_800AAA58;
extern f32 D_800AAA5C;
extern f32 D_800AAA60;

extern f32 D_800AAA44;
extern f32 D_800AAA48;
extern f32 D_800AAA4C;
extern f32 D_800AAA50;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C329C CURRENT (2058) */
void func_151C329C(Game1EF500EmitterVector *arg0, u8 arg1, s32 arg2) {
    Game1EF500EmitterParticle descriptor;
    Game1EF500EmitterSpawn spawn;
    Game1EF500EmitterLight light;
    s32 coordinates[3];
    s32 var_v0;
    s32 var_v1;

    descriptor.field0 = 5;
    descriptor.field4 = 7;
    descriptor.position8 = *arg0;
    descriptor.field14 = D_800AAA44;
    descriptor.field18 = D_800AAA48;
    descriptor.field1C = D_800AAA4C;
    descriptor.field20 = D_800AAA50;
    descriptor.field24 = 15.0f;
    descriptor.field28 = 30.0f;
    descriptor.field2C = 0;
    descriptor.field2E = 0xFF;
    descriptor.field30 = -0x40;
    descriptor.field32 = 0x50;
    descriptor.field34 = 3;
    descriptor.field38 = 1;
    descriptor.field3C = 0x14;
    descriptor.field3E = 0xF;
    descriptor.field40 = 1;
    descriptor.fields42[0] = 4;
    descriptor.fields42[1] = 2;
    descriptor.fields42[2] = 3;
    descriptor.fields42[3] = 0xFF;
    descriptor.fields42[4] = 0xFF;
    descriptor.fields42[5] = 0xFF;
    descriptor.fields42[6] = 0xFF;
    descriptor.fields42[7] = 0;
    descriptor.fields42[8] = 0;
    descriptor.fields42[9] = 0;
    descriptor.fields42[10] = 0;
    descriptor.fields42[11] = 0xFF;
    descriptor.fields42[12] = 0xFF;
    descriptor.fields42[13] = 0xFF;
    descriptor.fields42[14] = 0xFF;
    descriptor.fields42[15] = 0;
    descriptor.fields42[16] = 0;
    descriptor.fields42[17] = 0;
    descriptor.fields42[18] = 0;
    descriptor.fields42[19] = 0xFF;
    descriptor.fields42[20] = 0;
    descriptor.fields42[21] = 3;
    descriptor.fields42[22] = 0x24;
    descriptor.field5C = 0x200005;
    descriptor.field60 = 0x60600;
    descriptor.field64 = 8;
    descriptor.field66 = 0x1F;
    descriptor.field68 = 1;
    descriptor.field6A = 0;
    descriptor.field6C = 1.0f;
    descriptor.fields70[0] = -1;
    descriptor.fields70[1] = 0;
    descriptor.fields70[2] = -1;
    descriptor.fields70[3] = -1;
    func_15152B38(&descriptor, (s32)arg1, arg2);
    spawn.field1D = 0x2B;
    spawn.field8 = 0x4403;
    spawn.field0 = 0x200005;
    spawn.field4 = 0x20000;
    spawn.fieldA = (func_150ADA20() % 7U) + 6;
    spawn.fieldC = 0;
    spawn.field10 = 0;
    spawn.colors14[0] = 0xFF;
    spawn.colors14[1] = 0xFF;
    spawn.colors14[2] = 0xFF;
    spawn.colors14[3] = 0xFF;
    spawn.colors14[4] = 0xFF;
    spawn.colors14[5] = 0xFF;
    spawn.colors14[6] = 0xFF;
    spawn.colors14[7] = 0xFF;
    spawn.colors14[8] = 0xFF;
    spawn.field28 = spawn.field2C = func_150ADA68() * 196.0f + 106.0f;
    spawn.position30 = *arg0;
    spawn.field1E = 3;
    spawn.field20 = 0x55;
    spawn.field22 = 1;
    spawn.field3C = 0.0f;
    spawn.field40 = 0.0f;
    spawn.field44 = 0.0f;
    spawn.field48 = 0.0f;
    spawn.field4C = 0.0f;
    spawn.field50 = 0.0f;
    spawn.field54 = 0.0f;
    spawn.field24 = 1.0f;
    if (func_150ADA20() & 1) {
        var_v1 = 0x40;
    } else {
        var_v1 = 0;
    }
    if (func_150ADA20() & 1) {
        var_v0 = 0x80;
    } else {
        var_v0 = 0;
    }
    spawn.field58 = var_v0 | 1 | var_v1 | 0xC200;
    spawn.fields60[0] = 6;
    spawn.fields60[1] = 6;
    spawn.fields60[2] = -1;
    spawn.fields60[3] = -1;
    spawn.fields60[4] = -1;
    spawn.fields60[5] = 4;
    func_15130280(&spawn, 1, 0, 0, arg1, arg2);
    light.field0 = 3;
    light.field1 = -1;
    light.field2 = (func_150ADA20() % 7U) + 6;
    light.field4 = 0;
    coordinates[0] = (s32)arg0->x;
    coordinates[1] = (s32)arg0->y;
    coordinates[2] = (s32)arg0->z;
    func_151602C0((u8 *)&light, coordinates, (func_150ADA20() & 1) + 5,
                 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, (s32)arg1, arg2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C329C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C329C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C36D8 CURRENT (2058) */
void func_151C36D8(Game1EF500EmitterVector *arg0, u8 arg1, s32 arg2) {
    Game1EF500EmitterParticle descriptor;
    Game1EF500EmitterSpawn spawn;
    Game1EF500EmitterLight light;
    s32 coordinates[3];
    s32 var_v0;
    s32 var_v1;

    descriptor.field0 = 8;
    descriptor.field4 = 6;
    descriptor.position8 = *arg0;
    descriptor.field14 = D_800AAA54;
    descriptor.field18 = D_800AAA58;
    descriptor.field1C = D_800AAA5C;
    descriptor.field20 = D_800AAA60;
    descriptor.field24 = 10.0f;
    descriptor.field28 = 8.0f;
    descriptor.field2C = 0;
    descriptor.field2E = 0xFF;
    descriptor.field30 = -0x40;
    descriptor.field32 = 0x50;
    descriptor.field34 = 3;
    descriptor.field38 = 0;
    descriptor.field3C = 0xF;
    descriptor.field3E = 0xA;
    descriptor.field40 = 1;
    descriptor.fields42[0] = 4;
    descriptor.fields42[1] = 2;
    descriptor.fields42[2] = 3;
    descriptor.fields42[3] = 0xFF;
    descriptor.fields42[4] = 0xFF;
    descriptor.fields42[5] = 0xFF;
    descriptor.fields42[6] = 0xFF;
    descriptor.fields42[7] = 0;
    descriptor.fields42[8] = 0;
    descriptor.fields42[9] = 0;
    descriptor.fields42[10] = 0;
    descriptor.fields42[11] = 0xFF;
    descriptor.fields42[12] = 0xFF;
    descriptor.fields42[13] = 0xFF;
    descriptor.fields42[14] = 0xFF;
    descriptor.fields42[15] = 0;
    descriptor.fields42[16] = 0;
    descriptor.fields42[17] = 0;
    descriptor.fields42[18] = 0;
    descriptor.fields42[19] = 0xFF;
    descriptor.fields42[20] = 0;
    descriptor.fields42[21] = 3;
    descriptor.fields42[22] = 0x24;
    descriptor.field5C = 0x200005;
    descriptor.field60 = 0x60600;
    descriptor.field64 = 8;
    descriptor.field66 = 0x1F;
    descriptor.field68 = 1;
    descriptor.field6A = 0;
    descriptor.field6C = 1.0f;
    descriptor.fields70[0] = -1;
    descriptor.fields70[1] = 0;
    descriptor.fields70[2] = -1;
    descriptor.fields70[3] = -1;
    func_15152B38(&descriptor, (s32)arg1, arg2);
    spawn.field1D = 0x2B;
    spawn.field8 = 0x4403;
    spawn.field0 = 0x200005;
    spawn.field4 = 0x20000;
    spawn.fieldA = (func_150ADA20() % 5U) + 4;
    spawn.fieldC = 0;
    spawn.field10 = 0;
    spawn.colors14[0] = 0xFF;
    spawn.colors14[1] = 0xFF;
    spawn.colors14[2] = 0xFF;
    spawn.colors14[3] = 0xFF;
    spawn.colors14[4] = 0xFF;
    spawn.colors14[5] = 0xFF;
    spawn.colors14[6] = 0xFF;
    spawn.colors14[7] = 0xFF;
    spawn.colors14[8] = 0xFF;
    spawn.field28 = spawn.field2C = func_150ADA68() * 60.0f + 80.0f;
    spawn.position30 = *arg0;
    spawn.field1E = 2;
    spawn.field20 = 0x7F;
    spawn.field22 = 1;
    spawn.field3C = 0.0f;
    spawn.field40 = 0.0f;
    spawn.field44 = 0.0f;
    spawn.field48 = 0.0f;
    spawn.field4C = 0.0f;
    spawn.field50 = 0.0f;
    spawn.field54 = 0.0f;
    spawn.field24 = 1.0f;
    if (func_150ADA20() & 1) {
        var_v1 = 0x40;
    } else {
        var_v1 = 0;
    }
    if (func_150ADA20() & 1) {
        var_v0 = 0x80;
    } else {
        var_v0 = 0;
    }
    spawn.field58 = var_v0 | 1 | var_v1 | 0xC200;
    spawn.fields60[0] = 6;
    spawn.fields60[1] = 6;
    spawn.fields60[2] = -1;
    spawn.fields60[3] = -1;
    spawn.fields60[4] = -1;
    spawn.fields60[5] = 4;
    func_15130280(&spawn, 1, 0, 0, arg1, arg2);
    light.field0 = 3;
    light.field1 = -1;
    light.field2 = (func_150ADA20() % 7U) + 6;
    light.field4 = 0;
    coordinates[0] = (s32)arg0->x;
    coordinates[1] = (s32)arg0->y;
    coordinates[2] = (s32)arg0->z;
    func_151602C0((u8 *)&light, coordinates, (func_150ADA20() & 1) + 5,
                 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, (s32)arg1, arg2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C36D8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C36D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C3B0C.s")
extern f32 D_800AAA7C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C436C CURRENT (110) */
void func_151C436C(s32 arg0, void *arg1, s32 arg2) {
    f32 temp_fa0;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 step;
    f32 target_x;
    f32 target_y;
    f32 target_z;

    if (arg2 > 0) {
        target_x = *(f32 *)((u8 *)arg1 + 0x1C);
        target_y = *(f32 *)((u8 *)arg1 + 0x20);
        target_z = *(f32 *)((u8 *)arg1 + 0x24);
        step = D_800AAA7C;
        do {
            temp_fv0 = *(f32 *)((u8 *)arg1 + 0x10);
            temp_fa0 = *(f32 *)((u8 *)arg1 + 0x14);
            temp_ft4 = *(f32 *)((u8 *)arg1 + 0x18);
            arg2 -= 1;
            *(f32 *)((u8 *)arg1 + 0x10) = (f32) (temp_fv0 + ((target_x - temp_fv0) * step));
            *(f32 *)((u8 *)arg1 + 0x14) = (f32) (temp_fa0 + ((target_y - temp_fa0) * step));
            *(f32 *)((u8 *)arg1 + 0x18) = (f32) (temp_ft4 + ((target_z - temp_ft4) * step));
        } while (arg2 > 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C436C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C436C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_151C43E0 CURRENT (1633) */
u8 func_151C43E0(void *arg0, u8 *arg1, f32 arg2) {
    u8 spDF;
    s32 spD8;
    u8 sp64[0x5A];
    f32 temp_fv1;
    f32 var_fv0;
    u8 temp_v1;
    u8 var_t0;

    var_t0 = 1;
    spD8 = *(s32 *)(arg1 + 0x90);
    temp_v1 = arg1[0];
    if (temp_v1 & 4) {
        temp_fv1 = *(f32 *)(arg1 + 0x8C);
        if (temp_fv1 < arg2) {
            var_fv0 = *(f32 *)(arg1 + 0x98) * temp_fv1;
        } else {
            var_fv0 = *(f32 *)(arg1 + 0x98) * arg2;
        }
        if (var_fv0 != 0.0f) {
            spDF = 1;
            func_15081690(*(f32 *)&spD8,
                          *(s32 *)((u8 *)arg0 + 0x34),
                          *(s32 *)((u8 *)arg0 + 0x38),
                          *(s32 *)((u8 *)arg0 + 0x3C),
                          *(f32 *)(arg1 + 0x60),
                          *(f32 *)(arg1 + 0x64),
                          *(f32 *)(arg1 + 0x68), sp64, var_fv0, 1, 0,
                          (temp_v1 & 8) == 0, *(s8 *)(arg1 + 0xA8), 0,
                          *(s32 *)(arg1 + 0xAC));
            var_t0 = spDF;
            if (sp64[0x59] >= 2) {
                func_151C2EF0(*(s32 *)sp64, spD8, arg0,
                              (s32)(sp64 + 8), (s32)(sp64 + 0x20),
                              (s32)sp64);
                var_t0 = 0;
            }
        }
    }
    return var_t0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151C43E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C43E0.s")
void func_151C4510(void *arg0, void *arg1, f32 arg2) {
    *(f32 *)((u8 *)arg0 + 0x34) = (f32) ((*(f32 *)((u8 *)arg1 + 4) * arg2) + *(f32 *)((u8 *)arg0 + 0x34));
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) ((*(f32 *)((u8 *)arg1 + 8) * arg2) + *(f32 *)((u8 *)arg0 + 0x38));
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) ((*(f32 *)((u8 *)arg1 + 0xC) * arg2) + *(f32 *)((u8 *)arg0 + 0x3C));
}
typedef void (*Game1EF500TimerCallback)(void *, s32);
typedef void (*Game1EF500DoneCallback)(s32);
extern Game1EF500DoneCallback D_8008FBD0[];
extern s32 D_800DBEF4;
extern Game1EF500TimerCallback D_800E0940;

s32 func_151C455C(s32 arg0, u8 *arg1, f32 arg2) {
    s32 temp_v1;
    s32 var_v1;
    s8 temp_v0;

    var_v1 = 1;
    *(f32 *)(arg1 + 0x8C) -= arg2;
    if (*(f32 *)(arg1 + 0x8C) <= 0.0f) {
        if ((D_800E0940 != 0) && (arg1[0] & 1)) {
            temp_v1 = *(s32 *)(arg1 + 0x84);
            if (temp_v1 != 0) {
                D_800E0940(arg1 + 0x30, (temp_v1 - D_800DBEF4) / 160);
            }
        }
        if (arg1[0] & 2) {
            temp_v0 = *(s8 *)(arg1 + 0x9C);
            if (temp_v0 != -1) {
                D_8008FBD0[temp_v0](arg0);
            }
        }
        var_v1 = 0;
    }
    return var_v1;
}
typedef struct Game1EF500TimedEmitter {
    s16 *position;
    s32 timer;
    s32 minimumDelay;
    s32 delayRange;
    s16 minimumLife;
    s16 lifeRange;
    f32 base;
    f32 jitter;
    f32 field1C;
    f32 field20;
    f32 spread;
    f32 field28;
    f32 field2C;
    f32 field30;
    f32 field34;
} Game1EF500TimedEmitter;

typedef struct Game1EF500TimedOwner {
    u8 pad0;
    u8 category;
    u8 pad2[0xA];
    u8 group;
    u8 padD[0x1B];
    Game1EF500TimedEmitter emitter;
} Game1EF500TimedOwner;

extern f32 D_800AAA80;
extern f32 D_800AAA84;
extern s32 D_800BE9E4;

void func_151C4644(Game1EF500TimedOwner *arg0) {
    u8 *object;
    f32 values[17];
    Game1EF500TimedEmitter *emitter;

    emitter = &arg0->emitter;
    arg0->emitter.timer -= (u32)D_800BE9E4;
    if (arg0->emitter.timer < 0) {
        values[0] = emitter->field1C;
        values[1] = emitter->field20;
        values[2] = func_150ADA68() * emitter->spread;
        values[3] = func_150ADA68() * emitter->spread;
        values[4] = func_150ADA68() * D_800AAA80;
        values[5] = func_150ADA68() * D_800AAA84;
        values[6] = emitter->field28;
        values[7] = emitter->field28;
        values[8] = 0.0f;
        values[9] = func_150ADA68() * emitter->jitter + emitter->base;
        values[10] = 0.0f;
        values[11] = emitter->position[0];
        values[12] = emitter->position[1];
        values[13] = emitter->position[2];
        values[14] = emitter->field2C;
        values[15] = emitter->field30;
        values[16] = emitter->field34;
        object = func_15149130((s16)((func_150ADA20() % (u32)(emitter->lifeRange + 1)) + emitter->minimumLife),
                               -1, 0x2B, -1, 1, 0, 0x44, arg0->group, arg0->category);
        if (object != 0) {
            func_10022EC0(object + 0x28, values, 0x44);
        }
        emitter->timer = (func_150ADA20() % ((u32)emitter->delayRange + 1)) + emitter->minimumDelay;
    }
}
