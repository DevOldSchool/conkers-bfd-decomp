#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_32740.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_early_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15005290
 * - func_150054C4
 * - func_15005818
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_10003C40(s32 size, s32 pool, s32 flags, s32 alignment);
s32 func_1502B5C8(s32 *size, s32 count, ...);
void func_150054C4(u8 *view, u32 index, s32 resource, s32 mode);
void func_1512ABF8(void);
void func_1512D238(void);

extern s32 D_80082FA0;
extern s32 D_800894B0;
extern s16 D_80089550;
extern u8 *D_800BE2B0[];
extern s32 D_800BE620;
extern u8 *D_800DBFF0;
extern u8 D_800DBFF4[];
extern u8 *D_800DC010;
extern u8 *D_800DC020;
extern u8 *D_800DC2A0[2];
extern u8 *D_800DC2B0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15005290 CURRENT (2519) */
void func_15005290(s32 resource, s32 mode) {
    s32 resource_size;
    u8 **buffer;
    s32 count;
    s32 matrix_bytes;
    u8 *view;
    s32 view_offset;
    u8 *flag;
    u32 index;
    s16 view_resource;

    D_800DC020 = (u8 *)func_1502B5C8(&resource_size, 3, 0xC, resource, 8);
    D_80089550 = (u32)resource_size / 24U;
    count = D_80082FA0 + 1;
    D_800DBFF0 = (u8 *)func_10003C40(count * 0x9A0, 1, 1, 0);
    matrix_bytes = count << 6;
    D_800DC2B0 = (u8 *)func_10003C40(count * 0xB0, 1, 0, 0);
    D_800DC2A0[0] = (u8 *)func_10003C40(matrix_bytes, 1, 1, 0);
    D_800DC2A0[1] = (u8 *)func_10003C40(matrix_bytes, 1, 1, 0);
    view_resource = resource;
    flag = D_800DBFF4;
    buffer = D_800BE2B0;
    index = 0;
    view_offset = 0;
    do {
        view = D_800DBFF0 + view_offset;
        *buffer = (u8 *)func_10003C40(D_800BE620 * 2, 1, 2, 0);
        func_150054C4(view, index, (s16)view_resource, mode);
        *flag = 0;
        index += 1;
        view_offset += 0x9A0;
        buffer += 1;
        flag += 1;
    } while ((u32)D_80082FA0 >= index);
    func_1512ABF8();
    func_1512D238();
    D_800894B0 = 0;
    D_800DC010 = (u8 *)func_10003C40(D_80082FA0 * 0x9A0 + 0x9A0, 1, 2, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15005290 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_32740/func_15005290.s")
typedef struct Game32740View {
    u8 pad0[0x2C];
    s32 field2C;
    u8 pad30[0x54];
    s32 field84;
    u8 pad88[0x54];
    s32 fieldDC;
    u8 padE0[0x54];
    s32 field134;
    u8 pad138[0x7C];
    s16 field1B4;
    s16 field1B6[21];
    s16 field1E0;
    u8 pad1E2[0x56];
    s32 field238;
    u8 field23C;
    u8 field23D;
    u8 pad23E[0x2];
    s32 field240;
    u8 pad244[0x8];
    f32 field24C;
    f32 field250;
    u8 pad254[0x18];
    f32 field26C;
    u8 pad270[0x2];
    s16 field272;
    u8 pad274[0x30];
    f32 field2A4;
    f32 field2A8;
    f32 field2AC;
    f32 field2B0;
    f32 field2B4;
    f32 field2B8;
    s32 field2BC[3];
    u8 pad2C8[0x18];
    s32 field2E0[3];
    s32 field2EC[3];
    s32 field2F8[3];
    u8 pad304[0x60];
    f32 field364;
    s16 field368;
    u8 pad36A[0x1A];
    f32 field384;
    u8 pad388[0x18];
    f32 field3A0;
    u8 pad3A4[0x4];
    f32 field3A8;
    u8 pad3AC[0x20];
    s16 field3CC;
    u8 pad3CE[0x2];
    u8 * field3D0;
    u8 * field3D4;
    u8 pad3D8[0x8];
    f32 field3E0;
    u8 pad3E4[0x4];
    u8 field3E8;
    u8 pad3E9[0xB];
    f32 field3F4;
    f32 field3F8;
    u8 pad3FC[0x1D0];
    f32 field5CC;
    u8 pad5D0[0x4];
    f32 field5D4;
    f32 field5D8;
    u8 pad5DC[0x14];
    u32 field5F0;
    u8 pad5F4[0x6];
    s16 field5FA;
    s16 field5FC;
    s16 field5FE;
    u8 pad600[0x74];
    f32 field674;
    u8 pad678[0x4];
    f32 field67C;
    u8 pad680[0x13C];
    f32 field7BC;
    u8 pad7C0[0xC];
    s32 field7CC;
    u8 pad7D0[0x18];
    f32 field7E8;
    u8 pad7EC[0x80];
    f32 field86C;
    u8 pad870[0x4C];
    u8 * field8BC;
} Game32740View;

typedef struct { s32 words[3]; } Game32740Words3;

void func_100226F0(void *, s32);
void func_15005A60(void *, s16);
void func_15085430(void *, s32, s32);
void func_15124AB4(void *);
void func_15124B18(u8 *);
void func_15125394(void *);
void func_15125924(u8 *);
void func_1512D66C(void *);
void func_1512D6F0(void *);
void func_151298C0(u8 *, s16, void *);
extern s32 D_80089520, D_80089524[], D_80089534[];
extern f32 D_800959E0, D_800959E4, D_800959E8, D_800959EC;
extern void *D_800B0DF0;
extern s32 D_800BE624;
extern s8 D_800C3671;
extern u8 D_800CC2D0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150054C4 CURRENT (615) */
void func_150054C4(u8 *view, u32 index, s32 resource, s32 mode) {
    Game32740View *state = (Game32740View *)view;
    u16 i;
    s32 actorIndex;
    u8 *actor;
    f32 value;

    func_100226F0(view, 0x9A0);
    state->field23D = index;
    state->field23C = 1;
    i = 0;
    do {
        func_151239CC(view, i);
        state->field1B6[i++] = 0x3E7;
    } while (i < 0x15);
    state->field5D4 = ((f32)D_800BE624 * 60.0f) / 216.0f;
    state->field5D8 = ((f32)D_800BE624 * 40.0f) / 216.0f;
    actorIndex = state->field23D;
    actor = D_800CC2D0 + actorIndex * 0x32C;
    state->field2C = 1;
    state->fieldDC = 0;
    state->field3D0 = actor;
    state->field24C = 1.0f;
    state->field250 = 1.0f;
    state->field3CC = actorIndex;
    *(u8 **)(actor + 0x318) = view;
    state->field134 = 1;
    state->field84 = 0xE;
    state->field240 = 0;
    state->field1E0 = 0xD;
    state->field1B4 = 3;
    state->field5CC = 1.0f;
    state->field3A8 = 0.0f;
    func_15124B18(view);
    state->field272 = -1;
    state->field5FA = 1;
    state->field3E8 = 1;
    state->field67C = (f32)(u32)*(u16 *)((u8 *)D_800B0DF0 + 2);
    state->field2B0 = state->field2A4;
    state->field2B4 = state->field2A8;
    state->field2B8 = state->field2AC;
    state->field384 = D_800959E0;
    state->field5F0 |= 0x80000000;
    func_15124AB4(view);
    func_15125394(view);
    state->field5FC = 0xA;
    state->field26C = 1.0f;
    func_1512D66C(view);
    actorIndex = state->field23D;
    state->field238 = -1;
    state->field3CC = actorIndex;
    state->field368 = actorIndex;
    actor = D_800CC2D0 + actorIndex * 0x32C;
    state->field3D0 = actor;
    state->field3D4 = *(u8 **)(actor + 0x31C);
    func_151298C0(view, ((s16 *)&resource)[1], actor);
    value = D_800959E4;
    state->field7CC = 2;
    state->field3F4 = -1.0f;
    state->field3F8 = -1.0f;
    state->field7BC = value;
    state->field3E0 = state->field3A0;
    *(f32 *)(state->field3D4 + 0x18C) = value;
    func_1512D6F0(view);
    func_15125924(view);
    state->field674 = 1.0f;
    func_15085430(state->field3D0, mode, 0);
    func_15005A60(view, ((s16 *)&resource)[1]);
    state->field364 = D_800959E8;
    *(Game32740Words3 *)state->field2E0 = *(Game32740Words3 *)state->field2BC;
    *(Game32740Words3 *)state->field2EC = *(Game32740Words3 *)state->field2F8;
    state->field7E8 = 50.0f;
    state->field86C = D_800959EC;
    state->field8BC = D_800BE2B0[state->field23D];
    D_80089520 = 0;
    D_800C3671 = 0;
    D_80089524[state->field23D] = 0;
    D_80089534[state->field23D] = 0;
    state->field5FE = 0x3C;
    state->field23C = 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150054C4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_32740/func_150054C4.s")
typedef struct {
    f32 x, y, z;
} Game5818Vector;

f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
void func_1510E7A4(s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, u16, s32, f32, f32);
void func_1512523C(void *);
void func_15125330(void *);
void func_1512D560(void *, s32, s32);
void func_15124B18(u8 *);
extern f32 D_800959F0;
extern s32 D_800BE9F0;
extern u8 D_800C35EA;
typedef struct {
    u8 pad0[0xC];
    f32 fieldC;
    u8 tail10[0x1C];
} Game5818FixedView;
extern Game5818FixedView D_800C3600;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15005818 CURRENT (185) */
void func_15005818(u8 *arg0, u8 *arg1, Game5818Vector *volatile arg2) {
    f32 value;

    arg0[0x23C] = 1;
    *(f32 *)(arg0 + 0x2F8) = arg2->x;
    *(f32 *)(arg0 + 0x2FC) = arg2->y;
    *(f32 *)(arg0 + 0x300) = arg2->z;
    *(Game5818Vector *)(arg0 + 0x27C) = *(Game5818Vector *)(arg0 + 0x2F8);
    *(Game5818Vector *)(arg0 + 0x304) = *(Game5818Vector *)(arg0 + 0x2F8);
    func_1510E7A4((s32)(arg0 + 0x644), (s32)(arg0 + 0x648),
                   (s32)(arg0 + 0x354), (s32)(arg0 + 0x360),
                   (s32)(arg0 + 0x640), 0,
                   *(f32 *)(arg0 + 0x2F8), *(f32 *)(arg0 + 0x2FC),
                   *(f32 *)(arg0 + 0x300), *(f32 *)(arg0 + 0x2FC),
                   0, 0, D_800959F0, *(f32 *)(arg0 + 0x2FC));
    value = *(f32 *)(arg0 + 0x354);
    *(f32 *)(arg0 + 0x358) = value;
    *(f32 *)(arg0 + 0x35C) = value;
    *(f32 *)(arg0 + 0x2A4) = *(f32 *)(arg1 + 0x14);
    *(f32 *)(arg0 + 0x2A8) = *(f32 *)(arg1 + 0x18);
    *(f32 *)(arg0 + 0x2AC) = *(f32 *)(arg1 + 0x1C);
    *(Game5818Vector *)(arg0 + 0x2BC) = *(Game5818Vector *)(arg0 + 0x2A4);
    value = sqrtf(
        (*(f32 *)(arg0 + 0x2AC) - *(f32 *)(arg0 + 0x300)) *
        (*(f32 *)(arg0 + 0x2AC) - *(f32 *)(arg0 + 0x300)) +
        (*(f32 *)(arg0 + 0x2A4) - *(f32 *)(arg0 + 0x2F8)) *
        (*(f32 *)(arg0 + 0x2A4) - *(f32 *)(arg0 + 0x2F8)));
    *(Game5818Vector *)(arg0 + 0x2B0) = *(Game5818Vector *)(arg0 + 0x2A4);
    *(f32 *)(arg0 + 0x34C) = *(f32 *)(arg0 + 0x2FC) - *(f32 *)(arg0 + 0x354);
    *(f32 *)(arg0 + 0x348) = *(f32 *)(arg0 + 0x2FC) - *(f32 *)(arg0 + 0x354);
    *(f32 *)(arg0 + 0x374) = value;
    *(Game5818Vector *)(arg0 + 0x2E0) = *(Game5818Vector *)(arg0 + 0x2BC);
    *(Game5818Vector *)(arg0 + 0x2EC) = *(Game5818Vector *)(arg0 + 0x2F8);
    func_15124B18(arg0);
    func_15125330(arg0);
    func_1512523C(arg0);
    func_15123070(arg0);
    *(s32 *)(arg0 + 0x5F0) |= 4;
    if (D_800BE9F0 != 0x21 && D_800C35EA != 1) {
        func_1512D560(arg0, 5, 0);
        D_800C3600.fieldC = *(f32 *)(arg0 + 0x37C);
        func_1512D560(arg0, 8, (s32)&D_800C3600);
        func_1512D560(arg0, 6, 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15005818 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_32740/func_15005818.s")
