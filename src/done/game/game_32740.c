#include "types.h"
#include "game_functions.h"
#include "game_view.h"
#include "globals.h"

/*
 * Reviewed source unit: src/game/game_32740.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_early_callback_state_groups.md
 */

s32 func_10003C40(s32 size, s32 pool, s32 flags, s32 alignment);
s32 func_1502B5C8(u32 *size, s32 count, ...);
void func_150054C4(u8 *view, u32 index, s16 resource, s32 mode);
void func_1512ABF8(void);
void func_1512D238(void);

extern u8 D_800DBFF4[];

void func_15005290(s32 resource, s32 mode) {
    u32 index;
    u32 resource_size;
    s32 count;
    s32 matrix_bytes;

    D_800DC020 = (u8 *)func_1502B5C8(&resource_size, 3, 0xC, resource, 8);
    D_80089550 = resource_size / 24U;
    count = D_80082FA0 + 1;
    D_800DBFF0 = (struct108 *)func_10003C40(count * 0x9A0, 1, 1, 0);
    matrix_bytes = count << 6;
    D_800DC2B0 = (u8 *)func_10003C40(count * 0xB0, 1, 0, 0);
    D_800DC2A0[0] = (u8 *)func_10003C40(matrix_bytes, 1, 1, 0);
    D_800DC2A0[1] = (u8 *)func_10003C40(matrix_bytes, 1, 1, 0);
    for (index = 0; index <= (u32)D_80082FA0; index++) {
        u8 *view = (u8 *)&D_800DBFF0[index];

        D_800BE2B0[index] = (u8 *)func_10003C40(D_800BE620 * 2, 1, 2, 0);
        func_150054C4(view, index, resource, mode);
        D_800DBFF4[index] = 0;
    }
    func_1512ABF8();
    func_1512D238();
    D_800894B0 = 0;
    D_800DC010 = (u8 *)func_10003C40(D_80082FA0 * 0x9A0 + 0x9A0, 1, 2, 0);
}
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
    u8 pad274[0x8];
    Vec3f unk_27C;
    u8 unk_288[0x1C];
    Vec3f field2A4;
    Vec3f field2B0;
    Vec3f field2BC;
    u8 pad2C8[0x18];
    Vec3f field2E0;
    Vec3f field2EC;
    Vec3f field2F8;
    Vec3f unk_304;
    u8 unk_310[0x38];
    f32 unk_348;
    f32 unk_34C;
    u8 unk_350[0x4];
    f32 unk_354;
    f32 unk_358;
    f32 unk_35C;
    s32 unk_360;
    f32 field364;
    s16 field368;
    u8 pad36A[0xA];
    f32 unk_374;
    u8 unk_378[0x4];
    f32 unk_37C;
    u8 unk_380[0x4];
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
    u8 pad600[0x40];
    s32 unk_640;
    s32 unk_644;
    s32 unk_648;
    u8 unk_64C[0x28];
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
extern void *D_800B0DF0;
extern u8 D_800CC2D0[];

void func_150054C4(u8 *view, u32 index, s16 resource, s32 mode) {
    Game32740View *state = (Game32740View *)view;
    u16 i;
    s32 actorIndex;
    u8 *actor;

    func_100226F0(view, 0x9A0);
    state->field23C = 1;
    state->field23D = index;
    for (i = 0; i < 0x15; i++) {
        func_151239CC(view, i);
        state->field1B6[i] = 0x3E7;
    }
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
    state->field2B0.x = state->field2A4.x;
    state->field2B0.y = state->field2A4.y;
    state->field2B0.z = state->field2A4.z;
    state->field384 = 999.0f;
    state->field5F0 |= 0x80000000;
    func_15124AB4(view);
    func_15125394(view);
    state->field5FC = 0xA;
    state->field26C = 1.0;
    func_1512D66C(view);
    actorIndex = state->field23D;
    state->field238 = -1;
    state->field3CC = actorIndex;
    state->field368 = actorIndex;
    actor = D_800CC2D0 + actorIndex * 0x32C;
    state->field3D0 = actor;
    state->field3D4 = *(u8 **)(actor + 0x31C);
    func_151298C0(view, resource, actor);
    state->field7CC = 2;
    state->field3F4 = -1.0f;
    state->field3F8 = -1.0f;
    state->field7BC = 999.0f;
    state->field3E0 = state->field3A0;
    *(f32 *)(state->field3D4 + 0x18C) = 999.0f;
    func_1512D6F0(view);
    func_15125924(view);
    state->field674 = 1.0f;
    func_15085430(state->field3D0, mode, 0);
    func_15005A60(view, resource);
    state->field364 = -10000.0f;
    state->field2E0 = state->field2BC;
    state->field2EC = state->field2F8;
    state->field7E8 = 50.0f;
    state->field86C = 999.0f;
    state->field8BC = D_800BE2B0[state->field23D];
    D_80089520 = 0;
    D_800C3671 = 0;
    D_80089524[state->field23D] = 0;
    D_80089534[state->field23D] = 0;
    state->field5FE = 0x3C;
    state->field23C = 1;
}


f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
void func_1510E7A4(s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, u16, s32, f32, f32);
void func_1512523C(void *);
void func_15125330(void *);
void func_1512D560(void *, s32, void *);
void func_15124B18(u8 *);
extern u8 D_800C35EA;
typedef struct {
    u8 pad0[0xC];
    f32 fieldC;
    u8 tail10[0x1C];
} Game5818FixedView;
extern Game5818FixedView D_800C3600;

void func_15005818(Game32740View *view, struct127 *actor, Vec3f *position) {
    f32 distance;

    view->field23C = 1;
    view->field2F8.x = position->x;
    view->field2F8.y = position->y;
    view->field2F8.z = position->z;
    view->unk_27C = view->field2F8;
    view->unk_304 = view->field2F8;
    func_1510E7A4((s32)&view->unk_644, (s32)&view->unk_648, (s32)&view->unk_354, (s32)&view->unk_360,
                  (s32)&view->unk_640, 0, view->field2F8.x, view->field2F8.y, view->field2F8.z,
                  view->field2F8.y, 0, 0, -10000.0f, view->field2F8.y);
    view->unk_358 = view->unk_354;
    view->unk_35C = view->unk_354;
    view->field2A4.x = actor->x_position;
    view->field2A4.y = actor->y_position;
    view->field2A4.z = actor->z_position;
    view->field2BC = view->field2A4;
    view->field2B0 = view->field2A4;
    distance = sqrtf((view->field2A4.x - view->field2F8.x) * (view->field2A4.x - view->field2F8.x) +
                     (view->field2A4.z - view->field2F8.z) * (view->field2A4.z - view->field2F8.z));
    view->unk_34C = view->field2F8.y - view->unk_354;
    view->unk_348 = view->field2F8.y - view->unk_354;
    view->unk_374 = distance;
    view->field2E0 = view->field2BC;
    view->field2EC = view->field2F8;
    func_15124B18((u8 *)view);
    func_15125330(view);
    func_1512523C(view);
    func_15123070((struct108 *)view);
    view->field5F0 |= 4;
    if (D_800BE9F0 != 0x21 && D_800C35EA != 1) {
        func_1512D560(view, 5, NULL);
        D_800C3600.fieldC = view->unk_37C;
        func_1512D560(view, 8, &D_800C3600);
        func_1512D560(view, 6, NULL);
    }
}
