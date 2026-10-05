#include "types.h"

/*
 * Reviewed source unit: src/game/game_203E20.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151D69B4
 * - func_151D6BFC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern void func_150D6730(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_800BE9F0;

void func_151D6970(s32 arg0, s32 arg1) {
    if ((D_800BE9F0 == 0x32) || (D_800BE9F0 == 0x33)) {
        func_150D6730(arg0, 0xFF, 1);
    }
}
typedef struct Game203E20Primary {
    s16 field00;
    s16 field02;
    s16 field04;
    s16 field06;
    f32 position[3];
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
    s16 field34;
    s16 field36;
    s16 field38;
    s16 field3A;
    u8 field3C;
    u8 pad3D[3];
    f32 field40;
    s16 field44;
    s16 field46;
    s32 field48;
} Game203E20Primary;

typedef struct {
    s16 field00;
    s16 field02;
    s16 field04;
    s16 field06;
    f32 position[3];
    s16 field14;
    s16 field16;
    f32 field18;
    f32 field1C;
    s16 field20;
    s16 field22;
    f32 field24;
    f32 field28;
    u8 field2C;
    s8 field2D;
    u8 pad2E[2];
    f32 field30;
    f32 field34;
    s8 field38;
    s8 field39;
    u8 pad3A[2];
    f32 field3C;
    s8 field40;
    u8 pad41[3];
    f32 field44;
} Game203E20Secondary;

void func_1504715C(void *, void *);
void func_15153F18(s16 *, void *, void *, s32, s32);
void func_15150178(s16 *, f32 *, void *, u8, s32);
extern f32 D_800AB25C;
extern f32 D_800AB260;
extern f32 D_800AB264;
extern f32 D_800AB268;
extern f32 D_800AB26C;
extern f32 D_800AB270;
extern f32 D_800AB274;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D69B4 CURRENT (1345) */
void func_151D69B4(void *arg0, void *arg1) {
    struct { u32 words[9]; } hit;
    Game203E20Primary primary;
    Game203E20Secondary secondary;

    func_1504715C(&hit, arg1);
    primary.position[0] = (f32) *(s16 *)((u8 *)arg0 + 0x10);
    primary.position[1] = (f32) *(s16 *)((u8 *)arg0 + 0x12);
    primary.position[2] = (f32) *(s16 *)((u8 *)arg0 + 0x14);
    primary.field14 = D_800AB25C;
    primary.field2C = 3;
    primary.field2E = 3;
    primary.field02 = 0xFF;
    primary.field04 = -0x2B;
    primary.field06 = 0x20;
    primary.field00 = 0;
    primary.field30 = 3;
    primary.field32 = 2;
    primary.field34 = 0x28;
    primary.field36 = 0x14;
    primary.field38 = 0x9B;
    primary.field3A = 0x64;
    primary.field44 = 0x10;
    primary.field46 = 0xF;
    primary.field48 = 0;
    primary.field3C = 9;
    primary.field18 = D_800AB260;
    primary.field1C = D_800AB264;
    primary.field20 = D_800AB268;
    primary.field24 = 17.0f;
    primary.field28 = 3.5f;
    primary.field40 = D_800AB26C;
    func_15153F18(&primary.field00, &primary.position[0], &hit, 0xFF, 1);
    secondary.position[0] = (f32) *(s16 *)((u8 *)arg0 + 0x10);
    secondary.position[1] = (f32) *(s16 *)((u8 *)arg0 + 0x12);
    secondary.position[2] = (f32) *(s16 *)((u8 *)arg0 + 0x14);
    secondary.field14 = 0xF;
    secondary.field16 = 6;
    secondary.field00 = 0;
    secondary.field02 = 0xFF;
    secondary.field04 = -0x40;
    secondary.field06 = 0xC;
    secondary.field20 = 0x3C;
    secondary.field22 = 0x2D;
    secondary.field2C = 0xC8;
    secondary.field2D = 0x37;
    secondary.field38 = 1;
    secondary.field39 = 9;
    secondary.field3C = 1.0f;
    secondary.field40 = 0;
    secondary.field44 = secondary.field3C;
    secondary.field18 = 10.0f;
    secondary.field1C = 6.0f;
    secondary.field24 = D_800AB270;
    secondary.field28 = D_800AB274;
    secondary.field30 = 44.0f;
    secondary.field34 = 88.0f;
    func_15150178(&secondary.field00, &secondary.position[0], &hit, 0xFFU, 1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D69B4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_203E20/func_151D69B4.s")
typedef struct { s32 words[3]; } Game203E20Copy3;
typedef struct {
    s8 type, field1, field2, field3, field4, pad5;
    s16 lifetime;
    s32 field8, fieldC, field10, field14, field18, field1C, field20, field24, field28;
    u8 field2C, field2D, pad2E[2];
    u8 colors[8];
    u8 field38, pad39[3];
    void *owner;
    u8 mode, enabled, pad42[2];
    Game203E20Copy3 position;
    u8 pad50[4];
    s16 field54, field56;
} Game203E20Spawn;
typedef struct {
    void *owner;
    u8 mode, pad5[3];
    s32 weight;
    s16 fieldC, fieldE;
} Game203E20Payload;
typedef struct {
    s32 variant;
    Game203E20Payload payload;
} Game203E20SpawnWork;

void *func_10022EC0(void *, const void *, u32);
s32 func_150859AC(s32, s32);
s32 func_15157010(s32, s32, f32, s32, s32, s32, s32, s32);
void *func_1509B570(s32);
void *func_150CFF10(u8, u8 *, s16, s32, s8, u8, u8, s32);
extern Game203E20Copy3 D_800A5480;
extern s32 D_800AB250;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151D6BFC CURRENT (3543) */
void func_151D6BFC(u8 * volatile arg0, s32 arg1, s32 arg2) {
    Game203E20Spawn packet;
    Game203E20SpawnWork work;
    void *state;
    void *object;
    s32 amount;

    packet.field3 = 1;
    packet.field4 = -1;
    packet.type = 0x27;
    packet.field1 = -1;
    packet.field2 = 3;
    packet.field24 = 0x80;
    packet.field28 = 0x20;
    packet.lifetime = 0x96;
    packet.field8 = 0xA5;
    packet.fieldC = 0x17;
    packet.field14 = 0x220405;
    packet.field18 = 0x40200;
    packet.field2D = 8;
    packet.field1C = 1;
    packet.field20 = 0x38;
    packet.field38 = 0;
    packet.field10 = 0;
    packet.field2C = 0;
    packet.colors[0] = 0xFF;
    packet.colors[1] = 0xFF;
    packet.colors[2] = 0xFF;
    packet.colors[3] = 0xFF;
    packet.colors[4] = 0xFF;
    packet.colors[5] = 0xFF;
    packet.colors[6] = 0xFF;
    packet.colors[7] = 0xFF;
    packet.owner = arg0;
    packet.enabled = 1;
    packet.mode = arg0[0x3B];
    packet.position = D_800A5480;
    packet.field54 = 8;
    packet.field56 = 0x1F;
    func_15157010((s32)&packet, 0, 1.0f, 0, 0, 0, (u8)arg1, arg2);
    work.payload.owner = arg0;
    work.variant = D_800AB250;
    work.payload.fieldC = 8;
    work.payload.fieldE = 0x1F;
    work.payload.mode = arg0[0x3B];
    work.payload.weight = func_150859AC(0, 6);
    state = func_1509B570(0x83);
    if (state != 0) {
        amount = *(s32 *)((u8 *)state + 0x64) + 1;
        if (amount == 0xFF) {
            work.payload.weight += 100;
        } else if (amount == 0) {
            work.payload.weight = 0;
        } else if (amount < 3) {
            work.payload.weight = (s32)((u32)work.payload.weight * (u32)amount) / 3;
        }
    } else {
        work.payload.weight = 0;
    }
    object = func_150CFF10(0x63, (u8 *)&work, 0x96, 0x10, 3, 1, (u8)arg1, arg2);
    if (object != 0) {
        func_10022EC0(*(void **)((u8 *)object + 0x48), &work.payload, 0x10);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151D6BFC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_203E20/func_151D6BFC.s")
