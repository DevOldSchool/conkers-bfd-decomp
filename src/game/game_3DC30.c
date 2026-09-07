#include "types.h"

/*
 * Reviewed source unit: src/game/game_3DC30.c
 * Boundary evidence: docs/evidence/game_next_compact_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15010880
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15010880 CURRENT (210) */
void func_15010880(void) {
    Game3DC30Packet packet;
    u8 *object;

    func_15177410(0x10, 0xE9, -0x1B5, 0x463, -0xCBF, 90.0f, 0x3A98, 36.0f,
                  0x4D, 0xF, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F);
    D_800E0934 = func_150DE32C;
    packet.value = 0;
    packet.first = *(s32 *)D_800D3098 + 0xEA0;
    packet.second = *(s32 *)D_800D3098 + 0xED4;
    object = func_15149130(0x12C, -1, 0x5E, -1, 0, 0, 0xC, 0xFF, 1);
    if (object != 0) {
        func_10022EC0(object + 0x28, &packet, sizeof(packet));
    }
    if (D_800D2E4C[0x12] & 0x40) {
        func_15149130(5, 9, -1, -1, 1, 0, 0, 0xFF, 1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15010880 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_3DC30/func_15010880.s")
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
