#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D0600.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_continued.md
 */

typedef struct Game1D0600Vector {
    f32 x;
    f32 y;
    f32 z;
} Game1D0600Vector;

typedef struct Game1D0600Particle {
    s32 field0;
    s32 field4;
    Game1D0600Vector position8;
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
} Game1D0600Particle;

typedef struct Game1D0600Owner {
    u8 pad0;
    u8 field1;
    u8 pad2[0xA];
    u8 fieldC;
    u8 padD[0x2B];
    f32 field38;
    f32 field3C;
    Game1D0600Vector position40;
    Game1D0600Vector offset4C;
    u8 pad58[0x10];
    s32 flags68;
} Game1D0600Owner;

void func_15152B38(void *, s32, s32, void *);
extern f32 D_800A8D3C;
extern f32 D_800A8D40;
extern f32 D_800A8D44;

void func_151A3150(Game1D0600Owner *arg0) {
    Game1D0600Particle descriptor;

    descriptor.field0 = 0xA;
    descriptor.field4 = 0xF;
    descriptor.position8 = arg0->position40;
    if (arg0->flags68 & 0x1000) {
        descriptor.position8.x += arg0->offset4C.x;
        descriptor.position8.y += arg0->offset4C.y;
        descriptor.position8.z += arg0->offset4C.z;
    }
    descriptor.field14 = (arg0->field38 + arg0->field3C) * 0.5f * D_800A8D3C;
    descriptor.field18 = (arg0->field38 + arg0->field3C) * 0.5f * D_800A8D40;
    descriptor.field1C = D_800A8D44;
    descriptor.field20 = 0.0f;
    descriptor.field24 = 8.0f;
    descriptor.field28 = 8.0f;
    descriptor.field2C = 0;
    descriptor.field2E = 0xFF;
    descriptor.field30 = -0x40;
    descriptor.field32 = 0x56;
    descriptor.field34 = 3;
    descriptor.field38 = 2;
    descriptor.field3C = 0xF;
    descriptor.field3E = 0x1E;
    descriptor.field40 = 1;
    descriptor.fields42[0] = 4;
    descriptor.fields42[1] = 2;
    descriptor.fields42[2] = 3;
    descriptor.fields42[3] = 0xFF;
    descriptor.fields42[4] = 0xC8;
    descriptor.fields42[5] = 0xC8;
    descriptor.fields42[6] = 0xFF;
    descriptor.fields42[7] = 0;
    descriptor.fields42[8] = 0x37;
    descriptor.fields42[9] = 0x37;
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
    descriptor.fields42[21] = 1;
    descriptor.fields42[22] = 0x24;
    descriptor.field5C = 0x200005;
    descriptor.field60 = 0x60600;
    descriptor.field64 = 0xF;
    descriptor.field66 = 0x11;
    descriptor.field68 = 1;
    descriptor.field6A = 0;
    descriptor.field6C = 1.0f;
    descriptor.fields70[0] = -1;
    descriptor.fields70[1] = 0;
    descriptor.fields70[2] = -1;
    descriptor.fields70[3] = -1;
    func_15152B38(&descriptor, (s32) arg0->fieldC, (s32) arg0->field1, arg0);
}
