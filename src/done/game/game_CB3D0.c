#include "types.h"
#include "game_functions.h"
#include "game_view.h"

/*
 * Reviewed source unit: src/game/game_CB3D0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_descriptor_callback_families.md
 */

extern f32 D_800D2FC0[];
extern f32 D_800D2FD8[];
extern u8 D_800D2FEC[];
extern s32 D_800D3840;

typedef struct GameCB3D0Record {
    s32 pad0;
    s32 type;
    s32 index;
    s32 value;
} GameCB3D0Record;

void func_1509DF20(s32 arg0, GameCB3D0Record *arg1) {
    if ((arg1->type == 1) && (D_800D3840 == 3)) {
        D_800D2FC0[arg1->index] = (f32)arg1->value * 0.000015258789f;
        D_800D2FD8[arg1->index] = (f32)arg1->value * 0.000015258789f;
        D_800D2FEC[arg1->index] = 1;
    }
}
void func_1509DFB4(s32 arg0, s32 arg1) {
}
typedef struct {
    s32 pad0[2];
    s32 first;
    s32 second;
    s32 third;
    s32 fourth;
} GameCB3D0Query;

void func_15181E18(s32);
void func_15093818(s32);
s32 func_15089BC0(void);
s32 func_1508A1BC(void);
s32 func_1508A6FC(void);
s32 func_1508BF14(void);
s32 func_1508C194(s32);
s32 func_1508CAD8(s32, s32, s32, s32, s32, s32);
s32 func_1508DA1C(void);
s32 func_1508DC24(void);
s32 func_1508DAEC(s32, s32);
s32 func_1508B9BC(void);
s32 func_1508D850(s32);
s32 func_1508E89C(s32, s32);
s32 func_15086D48(s32);
s32 func_15086CBC(s32, f32 *, f32 *, f32 *);
void func_1508B20C(f32, f32, f32, f32);
void func_150870D0(s32, s32, s32);
void func_15087350(s32, s32, f32);
void func_15087DCC(s32, s32);
void func_15087FEC(s32, s32);
void func_15087FC4(s32, s32);
s32 func_150880F8(s32, s32);
void func_1508B1D4(s32);
void *func_15083E90(u8);
void func_15060F28(u8 *, s32);
void func_150495B0(f32 *, f32, f32 *, f32, f32, f32);
void func_15049688(f32 *, f32, f32 *, f32, f32, f32);
extern s32 D_800D2450;
extern u16 D_8008FDBC;

s32 func_1509DFC4(s32 arg0, u32 arg1, GameCB3D0Query *arg2) {
    s32 id;
    f32 x;
    f32 y;
    f32 z;
    u8 *actor;
    f32 scale;

    switch (arg1) {
    case 0:
        func_15181E18(0);
        return 0;
    case 1:
        func_1504332C(0xFF, 0xFF, 0xFF, 0xFF);
        func_15042D94(0x96, 0x56, 1, (s32)"%d", (arg2->first + 59) / 60);
        D_8008FDBC |= 0x80;
        break;
    case 2:
        D_800D2450 = arg2->first;
        break;
    case 3:
        func_15093818(arg2->first);
        return 0;
    case 4:
        return func_15089BC0();
    case 5:
        return func_1508A1BC();
    case 6:
        return func_1508A6FC();
    case 7:
        return func_1508BF14();
    case 8:
        return func_1508C194(arg2->first);
    case 9:
        return func_1508CAD8(arg2->first, arg2->second, arg2->third, arg2->fourth, 0, 0);
    case 10:
        return func_1508DA1C();
    case 11:
        return func_1508DC24();
    case 12:
        return func_1508DAEC(arg2->first, arg2->second);
    case 13:
        return func_1508B9BC();
    case 14:
        return func_1508D850(arg2->first);
    case 15:
        return func_1508E89C(arg2->first, arg2->second);
    case 16:
        id = func_15086D48(arg2->first);

        if (id != 0xFF) {
            func_15086CBC(id, &x, &y, &z);
            func_1508B20C(x, y, z, arg2->second);
            return 0;
        }
        break;
    case 17:
        func_150870D0(arg2->first, arg2->second, arg2->third);
        return 0;
    case 18:
        func_15087350(arg2->first, arg2->second, 0.1f);
        return 0;
    case 19:
        func_15087DCC(arg2->first, arg2->second);
        return 0;
    case 20:
        func_15087FEC(arg2->first, arg2->second);
        return 0;
    case 21:
        func_15087FC4(arg2->first, arg2->second);
        return 0;
    case 22:
        return func_150880F8(arg2->first, arg2->second);
    case 23:
        func_1508B1D4(arg2->first);
        return 0;
    case 25:
        scale = 0.000015258789f;
        {
            struct108 *view = D_800DBFF0;

            func_150495B0(&D_800D2FD8[arg2->first], arg2->second * scale,
                          &D_800D2FC0[arg2->first], arg2->third * scale,
                          arg2->fourth * scale, view->unk7B4);
        }
        return D_800D2FD8[arg2->first] * 65536.0f;
    case 26:
        scale = 0.000015258789f;
        {
            struct108 *view = D_800DBFF0;

            func_15049688(&D_800D2FD8[arg2->first], arg2->second * scale,
                          &D_800D2FC0[arg2->first], arg2->third * scale,
                          arg2->fourth * scale, view->unk7B4);
        }
        return D_800D2FD8[arg2->first] * 65536.0f;
    case 24:
        actor = func_15083E90(arg2->first);

        if (actor != 0) {
            func_15060F28(actor, 0);
        }
        break;
    }
    return 0;
}


typedef struct {
    u8 pad0[0x14];
    f32 x;
    f32 y;
    f32 z;
} GameCB3D0Position;

f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
f32 func_150CF040(s32, s32);
s8 func_1508CA88(void);
s32 func_1508C9CC(void);
s32 func_1508C5B8(s32, s32);
s32 func_15089F9C(s32);
s32 func_1508E6D0(s32);
s32 func_150881CC(u8 *);
s32 func_15088218(s32);
s32 func_15088270(s32);
s8 func_150882B0(s32);
s32 func_150882E4(s32, s32);
s32 func_150887F8(void);
s16 func_1508B194(s32);
extern s8 D_800E0BD0;
extern s8 D_800E0BE0[];

s32 func_1509E3DC(s32 arg0, u32 arg1, GameCB3D0Query *arg2) {
    switch (arg1) {
    case 0:
        return (s32)func_150CF040(arg2->first, arg2->second);
    case 1: {
        s32 dx = arg2->first - arg2->third;
        s32 dz = arg2->second - arg2->fourth;

        return (s32)sqrtf((f32)(dx * dx + dz * dz));
    }
    case 2:
        return func_1508CA88();
    case 3:
        return func_1508C9CC();
    case 4:
        return func_1508C5B8(arg2->first, arg2->second);
    case 5:
        return D_800E0BD0;
    case 6:
        return func_15089F9C(arg2->first);
    case 7:
        return func_1508E6D0(arg2->first);
    case 8:
        return 0;
    case 9:
        return func_150881CC((u8 *)arg2->first);
    case 10:
        return func_15088218(arg2->first);
    case 11:
        return func_15088270(arg2->first);
    case 12:
        return func_150882B0(arg2->first);
    case 13:
        return func_150882E4(arg2->first, arg2->second);
    case 14:
        return func_150887F8();
    case 15:
        return D_8008FDBC & 0x40;
    case 16:
        return D_800E0BE0[arg2->first];
    case 17:
        return func_1508B194(arg2->first);
    case 20:
    case 21:
        return (s32)(D_800D2FD8[arg2->first] * 65536.0f);
    case 18: {
        GameCB3D0Position *actor = func_15083E90(arg2->first);

        if (actor != 0) {
            s32 dx = (s32)actor->x;
            s32 dz = (s32)actor->z;

            return ((u32)dx << 16) | (dz & 0xFFFF);
        }
        return 0;
    }
    case 19: {
        GameCB3D0Position *actor = func_15083E90(arg2->first);

        if (actor != 0) {
            return (s16)(s32)actor->y;
        }
        return 0;
    }
    default:
        return 0;
    }
}
