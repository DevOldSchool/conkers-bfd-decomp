#include "types.h"

/*
 * Reviewed source unit: src/game/game_CB3D0.c
 * Boundary evidence: docs/evidence/game_raw_descriptor_callback_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1509DFC4
 * - func_1509E3DC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
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

void func_1509DF20(volatile s32 arg0, GameCB3D0Record *arg1) {
    if ((arg1->type == 1) && (D_800D3840 == 3)) {
        D_800D2FC0[arg1->index] = (f32)arg1->value * 0.000015258789f;
        D_800D2FD8[arg1->index] = (f32)arg1->value * 0.000015258789f;
        D_800D2FEC[arg1->index] = 1;
    }
}
void func_1509DFB4(s32 arg0, s32 arg1) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_CB3D0/func_1509DFC4.s")
typedef struct {
    s32 pad0[2];
    s32 first;
    s32 second;
    s32 third;
    s32 fourth;
} GameCB3D0Query;

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
void *func_15083E90(u8);
extern s8 D_800E0BD0;
extern s8 D_800E0BE0[];
extern u16 D_8008FDBC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509E3DC CURRENT (265) */
s32 func_1509E3DC(volatile s32 arg0, u32 arg1, GameCB3D0Query *arg2) {
    s32 dx;
    s32 dz;
    GameCB3D0Position *actor;

    switch (arg1) {
    case 0:
        return (s32)func_150CF040(arg2->first, arg2->second);
    case 1:
        dx = arg2->first - arg2->third;
        dz = arg2->second - arg2->fourth;
        return (s32)sqrtf((f32)(s32)((u32)dx * (u32)dx + (u32)dz * (u32)dz));
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
    case 18:
        actor = func_15083E90(*(u8 *)((u8 *)arg2 + 0xB));
        if (actor != 0) {
            dx = (s32)actor->x;
            dz = (s32)actor->z;
            return ((u32)dx << 16) | (dz & 0xFFFF);
        }
        return 0;
    case 19:
        actor = func_15083E90(*(u8 *)((u8 *)arg2 + 0xB));
        if (actor != 0) {
            return (s16)(s32)actor->y;
        }
        return 0;
    default:
        return 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509E3DC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CB3D0/func_1509E3DC.s")
