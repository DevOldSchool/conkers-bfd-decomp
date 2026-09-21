#include "types.h"

/*
 * Reviewed source unit: src/game/game_97AA0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1506A5F0
 * - func_1506A79C
 * - func_1506A864
 * - func_1506A968
 * - func_1506AA48
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_151A6F00(s16 *, s32, s32, s32);
extern f32 D_80099A10;
extern f32 D_80099A14;
extern f32 D_80099A18;
extern f32 D_80099A1C;
extern f32 D_80099A20;
extern f32 D_80099A24;

typedef struct {
    s16 type;
    u8 pad02[2];
    f32 x;
    f32 y;
    f32 z;
    s16 angle;
    u8 pad12[2];
    f32 field14;
    s16 field18;
    s16 field1A;
    s16 field1C;
    s16 field1E;
    f32 field20;
    f32 field24;
    u8 pad28[8];
    f32 field30;
    f32 field34;
    f32 field38;
    f32 field3C;
    f32 field40;
    f32 field44;
    f32 field48;
    f32 field4C;
    f32 field50;
    s8 field54;
    s8 field55;
    s16 field56;
    s16 field58;
} Game97AA0Effect;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506A5F0 CURRENT (518) */
void func_1506A5F0(void *arg0, s32 arg1) {
    Game97AA0Effect effect;

    effect.type = 3;
    effect.x = *(f32 *)((u8 *)arg0 + 0x14);
    effect.y = *(f32 *)((u8 *)arg0 + 0x18);
    effect.z = *(f32 *)((u8 *)arg0 + 0x1C);
    effect.angle = 0x5A;
    effect.field14 = D_80099A10;
    effect.field18 = 0;
    effect.field1A = 0xFF;
    effect.field1C = -0x40;
    effect.field1E = 0x28;
    effect.field20 = D_80099A14;
    effect.field24 = D_80099A18;
    effect.field30 = 0.0f;
    effect.field34 = 0.0f;
    effect.field38 = 0.0f;
    effect.field3C = D_80099A1C;
    effect.field40 = D_80099A20;
    effect.field44 = D_80099A24;
    effect.field48 = 0.0f;
    effect.field4C = -4.0f;
    effect.field50 = 8.0f;
    effect.field54 = 0;
    effect.field55 = 0;
    effect.field56 = 0x32;
    effect.field58 = 0x19;
    func_151A6F00(&effect.type, 1, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506A5F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_97AA0/func_1506A5F0.s")
void func_150E0348(s32 arg0, s32 arg1, s32 arg2);

void func_1506A6FC(s32 arg0, u8 arg1) {
    func_150E0348(arg0, 0xFF, 1);
}
void func_151BB61C(void *, void *, void *, s32, s32);
extern f32 D_800D1560[];
extern f32 D_800D1570[];

void func_1506A724(void *arg0, s32 arg1) {
    func_151BB61C(arg0, &D_800D1560, &D_800D1570, 0xFF, 1);
}
void func_151BBA9C(void *, void *, void *, s32, s32);

void func_1506A760(void *arg0, s32 arg1) {
    func_151BBA9C(arg0, &D_800D1560, &D_800D1570, 0xFF, 1);
}
void func_151D3480(f32 *, f32 *, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506A79C CURRENT (545) */
void func_1506A79C(void *arg0, s32 arg1) {
    f32 sp2C[3];
    f32 sp20[3];

    sp2C[0] = *(f32 *)((u8 *)arg0 + 0x14);
    sp2C[1] = *(f32 *)((u8 *)arg0 + 0x18);
    sp20[0] = D_800D1570[0] - D_800D1560[0];
    sp2C[2] = *(f32 *)((u8 *)arg0 + 0x1C);
    sp20[1] = D_800D1570[1] - D_800D1560[1];
    sp20[2] = D_800D1570[2] - D_800D1560[2];
    func_151D3480(sp2C, sp20, 0, 0, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506A79C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_97AA0/func_1506A79C.s")
void func_151BC104(s32 arg0, s32 arg1, s32 arg2);

void func_1506A83C(s32 arg0, u8 arg1) {
    func_151BC104(arg0, 0xFF, 1);
}
typedef struct {
    u8 type;
    u8 subtype;
    s16 value;
    s8 count;
    u8 pad[3];
} Game97AA0Descriptor;

typedef struct {
    s32 position[3];
    f32 values[4];
    Game97AA0Descriptor descriptor;
    u8 tailPad[4];
} Game97AA0Spawn;

void func_10022EC0(void *, void *, s32);
s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32,
                   s32, s32);
extern f32 D_80099A28;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506A864 CURRENT (3545) */
void func_1506A864(void *arg0, s32 arg1) {
    Game97AA0Spawn spawn;
    void *result;

    spawn.position[0] = (s32)*(f32 *)((u8 *)arg0 + 0x14);
    spawn.position[1] = (s32)(*(f32 *)((u8 *)arg0 + 0x18) + 50.0f);
    spawn.values[0] = 0.0f;
    spawn.values[2] = 0.0f;
    spawn.descriptor.type = 2;
    spawn.descriptor.subtype = 0xF;
    spawn.descriptor.value = 0x12C;
    spawn.position[2] = (s32)*(f32 *)((u8 *)arg0 + 0x1C);
    spawn.descriptor.count = 5;
    spawn.values[1] = 80.0f;
    spawn.values[3] = D_80099A28;
    result = (void *)func_151602C0((u8 *)&spawn.descriptor,
                                   spawn.position, 0, 0xFF, 0xFF, 0x5A,
                                   0xFF, 0, 0x10, 0xFF, 1);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x18, spawn.values, 0x10);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506A864 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_97AA0/func_1506A864.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506A968 CURRENT (545) */
void func_1506A968(void *arg0, s32 arg1) {
    f32 sp2C[3];
    f32 sp20[3];

    sp2C[0] = *(f32 *)((u8 *)arg0 + 0x14);
    sp2C[1] = *(f32 *)((u8 *)arg0 + 0x18);
    sp20[0] = D_800D1570[0] - D_800D1560[0];
    sp2C[2] = *(f32 *)((u8 *)arg0 + 0x1C);
    sp20[1] = D_800D1570[1] - D_800D1560[1];
    sp20[2] = D_800D1570[2] - D_800D1560[2];
    func_151D3480(sp2C, sp20, 0, 1, 0xFF, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506A968 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_97AA0/func_1506A968.s")
extern void func_151B6320(s32 arg0, s32 arg1, s32 arg2);
extern void func_151B7144(s32 arg0, s32 arg1, s32 arg2);

void func_1506AA08(s32 arg0, s32 arg1) {
    func_151B7144(arg0, 0xFF, 1);
    func_151B6320(arg0, 0xFF, 1);
}
void func_10022EC0(void *, void *, s32);
void *func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);
typedef struct Game97AA0Packet {
    void *arg0;
    u8 byte;
    u8 pad[3];
    s32 values[2];
} Game97AA0Packet;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1506AA48 CURRENT (859) */
void func_1506AA48(void *arg0, void *arg1) {
    Game97AA0Packet packet;
    void *temp_v0;

    packet.arg0 = arg0;
    packet.byte = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.values[0] = *(s32 *)arg1;
    packet.values[1] = *(s32 *)((u8 *)arg1 + 4);
    temp_v0 = func_15149130(0xA, 7, 0x23, -1, 1, 0x21, 0x10, 0xFF, 1);
    if (temp_v0 != 0) {
        func_10022EC0((u8 *)temp_v0 + 0x28, &packet, 0x10);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1506AA48 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_97AA0/func_1506AA48.s")
