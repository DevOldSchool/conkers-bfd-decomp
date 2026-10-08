#include "types.h"

/*
 * Reviewed source unit: src/game/game_3DC30.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_next_compact_units.md
 */

void func_15177410(s32, s32, s32, s32, s32, f32, s32, f32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_15010780(void) {
    func_15177410(1, 0xFF, 0, 0x6C, 0, 0.0f, 0x3A98, 80.0f,
                  0x4D, 0xF, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F);
    func_15177410(0, 0xFF, 0x19E4, 0x6C, 0, 0.0f, 0x3A98, 80.0f,
                  0x4D, 0xF, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F);
}
typedef struct Game3DC30Packet {
    s16 value;
    u8 pad2[2];
    s32 first;
    s32 second;
} Game3DC30Packet;

void func_10022EC0(void *, void *, s32);
u8 *func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_150DE32C(void);
extern u8 *D_800D2E4C;
extern u8 D_800D3098[];
extern void (*D_800E0934)(void);

typedef struct Game3DC30Temp { s16 unk0; s16 pad2; s32 unk4; s32 unk8; } Game3DC30Temp;

void func_15010880(void) {
    Game3DC30Temp tmp;
    struct37 *temp_v0;

    if (*((u8 *)D_800D2E4C + 0x12)) {
    }
    func_15177410(0x10, 0xE9, -437, 0x463, -0xCBF, 90.0f, 15000, 36.0f, 0x4D, 15, 127, 127, 127, 127, 127, 127);
    D_800E0934 = func_150DE32C;
    if (((!temp_v0) && (!temp_v0)) && (!temp_v0)) {
    }
    tmp.unk0 = 0;
    tmp.unk4 = (*((s32 *)(&D_800D3098))) + 0xEA0;
    tmp.unk8 = (*((s32 *)(&D_800D3098))) + 0xED4;
    temp_v0 = func_15149130(300, -1, 94, -1, 0, 0, 12, 255, 1);
    if (temp_v0 != 0) {
        func_10022EC0(&temp_v0->unk28, &tmp, 12);
    }
    if ((*((u8 *)D_800D2E4C + 0x12) & 0x40) != 0) {
        func_15149130(5, 9, -1, -1, 1, 0, 0, 255, 1);
    }
}
typedef struct Game3DC30PositionBlock {
    f32 values[6];
} Game3DC30PositionBlock;

typedef struct Game3DC30Request {
    s8 enabled;
    u8 pad1[3];
    Game3DC30PositionBlock position;
    f32 distance;
    s8 unused;
} Game3DC30Request;

void func_150E8854(void);
void func_151ACBD4(Game3DC30Request *, s32);
f32 fabsf(f32);
#pragma intrinsic(fabsf)
extern Game3DC30PositionBlock D_80096430;

void func_150109D0(void) {
    Game3DC30Request request;

    request.unused = 0;
    request.position = D_80096430;
    request.enabled = 1;
    request.distance = fabsf(request.position.values[1] - request.position.values[4]);
    func_151ACBD4(&request, 0);
    func_150E8854();
}
