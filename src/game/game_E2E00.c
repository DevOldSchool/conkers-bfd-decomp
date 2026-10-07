#include "types.h"

/*
 * Reviewed source unit: src/game/game_E2E00.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_owner_particle_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B5950
 * - func_150B5E34
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameE2E00Target5950 {
    s32 active;
    u8 pad4[0x10];
    f32 position[3];
    u8 pad20[0x1B];
    u8 type;
    u8 pad3C[0x198];
    s32 field_1D4;
} GameE2E00Target5950;

typedef struct GameE2E00Owner5950 {
    u8 pad0;
    u8 field_1;
    u8 pad2[0xA];
    u8 field_C;
    u8 padD;
    s16 result;
    u8 pad10[0x18];
    GameE2E00Target5950 *target;
    u8 field_2C;
} GameE2E00Owner5950;

f32 func_150ADA68(void);
void func_150B5A3C(void *, u8, s32, void *);
void func_150B60E0(void *, f32 *);
extern f32 D_8009FC98;
extern f32 D_8009FC9C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B5950 CURRENT (96) */
void func_150B5950(GameE2E00Owner5950 *arg0) {
    GameE2E00Target5950 *target;
    struct {
        u8 pad[8];
        f32 position[3];
    } local;

    target = arg0->target;
    if ((target->active == 0) || (target->type != arg0->field_2C)) {
        arg0->result = -1;
        return;
    }
    if (target->field_1D4 != 0) {
        if (func_150ADA68() < D_8009FC98) {
            local.position[0] = target->position[0];
            local.position[1] = target->position[1];
            local.position[2] = target->position[2];
            func_150B5A3C(local.position, arg0->field_C, arg0->field_1, target);
        }
        if (func_150ADA68() < D_8009FC9C) {
            func_150B60E0(target, local.position);
            func_150B5A3C(local.position, arg0->field_C, arg0->field_1);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B5950 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E2E00/func_150B5950.s")
typedef struct GameE2E00Vector {
    f32 x;
    f32 y;
    f32 z;
} GameE2E00Vector;

typedef struct GameE2E00Particle {
    s32 field0;
    s32 field4;
    GameE2E00Vector position8;
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
} GameE2E00Particle;

void func_150B5E34(void *, u8, s32);
void func_150B6000(void *, u8, s32);
void func_15152B38(void *, s32, s32, void *);
extern f32 D_8009FCA0;
extern f32 D_8009FCA4;
extern f32 D_8009FCA8;

void func_150B5A3C(void *arg0, u8 arg1, s32 arg2, void *arg3) {
    GameE2E00Particle descriptor;

    descriptor.field0 = 5;
    descriptor.field4 = 5;
    descriptor.position8 = *(GameE2E00Vector *)arg0;
    descriptor.field14 = 20.0f;
    descriptor.field18 = D_8009FCA0;
    descriptor.field1C = D_8009FCA4;
    descriptor.field20 = D_8009FCA8;
    descriptor.field24 = 39.0f;
    descriptor.field28 = 35.0f;
    descriptor.field2C = 0;
    descriptor.field2E = 0xFF;
    descriptor.field30 = -0x1F;
    descriptor.field32 = 0x50;
    descriptor.field34 = 3;
    descriptor.field38 = 2;
    descriptor.field3C = 0x14;
    descriptor.field3E = 0x1E;
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
    func_15152B38(&descriptor, (s32) arg1, arg2, arg3);
    func_150B5E34(arg0, arg1, arg2);
    func_150B6000(arg0, arg1, arg2);
}
extern f32 D_8009FCAC;
extern f32 D_8009FCB0;
extern f32 D_8009FCB4;
extern f32 D_8009FCB8;

void func_150B5C38(void *arg0, u8 arg1, s32 arg2, void *arg3) {
    GameE2E00Particle descriptor;

    descriptor.field0 = 0xD;
    descriptor.field4 = 8;
    descriptor.position8 = *(GameE2E00Vector *)arg0;
    descriptor.field14 = D_8009FCAC;
    descriptor.field18 = D_8009FCB0;
    descriptor.field1C = D_8009FCB4;
    descriptor.field20 = D_8009FCB8;
    descriptor.field24 = 152.0f;
    descriptor.field28 = 100.0f;
    descriptor.field2C = 0;
    descriptor.field2E = 0xFF;
    descriptor.field30 = -0x14;
    descriptor.field32 = 0x32;
    descriptor.field34 = 3;
    descriptor.field38 = 2;
    descriptor.field3C = 0x14;
    descriptor.field3E = 0xF;
    descriptor.field40 = 1;
    descriptor.fields42[0] = 4;
    descriptor.fields42[1] = 2;
    descriptor.fields42[2] = 3;
    descriptor.fields42[3] = 0xFF;
    descriptor.fields42[4] = 0xFF;
    descriptor.fields42[5] = 0xB4;
    descriptor.fields42[6] = 0xFF;
    descriptor.fields42[7] = 0;
    descriptor.fields42[8] = 0;
    descriptor.fields42[9] = 0;
    descriptor.fields42[10] = 0;
    descriptor.fields42[11] = 0xFF;
    descriptor.fields42[12] = 0xFF;
    descriptor.fields42[13] = 0xB4;
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
    func_15152B38(&descriptor, (s32) arg1, arg2, arg3);
    func_150B5E34(arg0, arg1, arg2);
    func_150B6000(arg0, arg1, arg2);
}

typedef struct GameE2E00Spawn {
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
    GameE2E00Vector position30;
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
} GameE2E00Spawn;

u32 func_150ADA20();
void *func_15130280(void *, u8, void *, s32, u8, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B5E34 CURRENT (303) */
void func_150B5E34(void *arg0, u8 arg1, s32 arg2) {
    GameE2E00Spawn spawn;
    s32 var_v0;
    s32 var_v1;

    spawn.field1D = 0x2B;
    spawn.field8 = 0x4403;
    spawn.field0 = 0x200005;
    spawn.field4 = 0x20000;
    spawn.fieldA = (func_150ADA20() % 7U) + 4;
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
    spawn.field28 = spawn.field2C = func_150ADA68() * 500.0f + 500.0f;
    spawn.position30 = *(GameE2E00Vector *)arg0;
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
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B5E34 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E2E00/func_150B5E34.s")
s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
u32 func_150ADA20();

void func_150B6000(void *arg0, u8 arg1, s32 arg2) {
    struct {
        u8 type;
        s8 subtype;
        s16 lifetime;
        s8 flag;
    } descriptor;
    s32 position[3];

    descriptor.type = 3;
    descriptor.subtype = -1;
    descriptor.lifetime = (func_150ADA20() % 9U) + 3;
    descriptor.flag = 0;
    position[0] = (s32)*(f32 *)((u8 *)arg0 + 0);
    position[1] = (s32)*(f32 *)((u8 *)arg0 + 4);
    position[2] = (s32)*(f32 *)((u8 *)arg0 + 8);
    func_151602C0((u8 *)&descriptor, position, (func_150ADA20(arg0) % 201U) + 0x37,
                  0xFF, 0xFF, 0xFF, 0xFF, 0, 0, (s32)arg1, arg2);
}
/* Call context: func_15143134: unique active project prototype */
void func_15143134(f32 *, f32 *, s32);
extern f32 D_8009FC30;

void func_150B60E0(void *arg0, f32 *arg1) {
    func_15143134(&D_8009FC30, arg1, *(s32 *)((u8 *)arg0 + 0x1D4) + 0x140);
}
