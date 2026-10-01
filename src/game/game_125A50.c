#include "types.h"

/*
 * Reviewed source unit: src/game/game_125A50.c
 * Boundary evidence: docs/evidence/game_raw_recovered_pointer_helper_groups_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F85A0
 * - func_150F887C
 * - func_150F892C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game125A50Vector {
    f32 x;
    f32 y;
    f32 z;
} Game125A50Vector;

typedef struct Game125A50Particle {
    s32 field0;
    s32 field4;
    Game125A50Vector position8;
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
} Game125A50Particle;

typedef struct Game125A50Light {
    u8 field0;
    s8 field1;
    s16 field2;
    u8 field4;
} Game125A50Light;

typedef struct Game125A50Position {
    u8 pad0[0x14];
    Game125A50Vector position14;
} Game125A50Position;

/* The raw callee consumes only a0-a2; incoming a3 is not saved before its call. */
void func_15152B38(void *, s32, s32);
s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
u32 func_150ADA20();
extern f32 D_800A1C60;
extern f32 D_800A1C64;
extern f32 D_800A1C68;
extern f32 D_800A1C6C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F85A0 CURRENT (266) */
void func_150F85A0(s32 arg0, Game125A50Position *arg1, s32 arg2) {
    Game125A50Vector position;
    Game125A50Light light;
    s32 coordinates[3];
    Game125A50Particle descriptor;

    position.x = arg1->position14.x;
    position.y = arg1->position14.y + 50.0f;
    position.z = arg1->position14.z;
    light.field0 = 3;
    light.field1 = -1;
    light.field2 = (func_150ADA20() % 9U) + 5;
    light.field4 = 0;
    coordinates[0] = (s32) position.x;
    coordinates[1] = (s32) position.y;
    coordinates[2] = (s32) position.z;
    func_151602C0((u8 *)&light, coordinates, (func_150ADA20() % 31U) + 0x5A,
                 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0xFF, 1);
    descriptor.field0 = 8;
    descriptor.field4 = 0xC;
    descriptor.position8 = position;
    descriptor.field14 = D_800A1C60;
    descriptor.field18 = D_800A1C64;
    descriptor.field1C = D_800A1C68;
    descriptor.field20 = D_800A1C6C;
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
    func_15152B38(&descriptor, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F85A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_125A50/func_150F85A0.s")
void func_151494E0(s32 *arg0, s32 arg1, s32 arg2);

void func_150F884C(s32 arg0, s32 arg1) {
    s32 sp18[2];

    sp18[0] = arg1;
    func_151494E0(&sp18[0], 0x3F, arg1);
}
extern void func_150F892C(void *arg0);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F887C CURRENT (810) */
void func_150F887C(void *arg0, u8 *arg1, u8 arg2) {
    void *owner;
    u8 *base;
    s32 var_v0;

    owner = arg0;
    var_v0 = arg2;
    if (arg2 == 0x42) {
        base = (u8 *)owner + 0x28;
        var_v0 = 0;
        if (arg1[4] == base[4]) {
            for (; var_v0 < 7; var_v0 = (var_v0 + 1) & 0xFF) {
                (*(u8 **)(base + (var_v0 * 4) + 0xC))[0x6E] = 1;
            }
            *(u8 *)((u8 *)*(void **)(base + 0x28) + 0x6E) = 0;
            base[8] = 7;
        }
    } else if ((var_v0 == 0x3F) && (*(s32 *)arg1 == *(s32 *)((u8 *)owner + 0x28))) {
        func_150F892C(owner);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F887C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_125A50/func_150F887C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_125A50/func_150F892C.s")
