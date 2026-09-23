#include "types.h"

/*
 * Reviewed source unit: src/game/game_FE340.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D0E90
 * - func_150D1204
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_FE340/func_150D0E90.s")
typedef struct GameFE340Packet {
    u8 id;
    u8 pad1[3];
    void *object;
    s8 value8;
    u8 pad9[3];
    f32 valueC;
    f32 value10;
    f32 value14;
    f32 value18;
    f32 value1C;
    f32 value20;
    s8 value24;
    u8 pad25;
    s16 value26;
    s16 value28;
    s16 value2A;
    s16 value2C;
    s8 value2E;
    s8 value2F;
    s8 value30;
    u8 pad31[3];
    f32 value34;
    s8 value38;
    s8 value39;
    u8 pad3A[2];
} GameFE340Packet;

void func_15134DAC(u8 *, s32, void *, s32);
extern f32 D_800A0890;

void func_150D10E4(u8 *arg0, u8 arg1, void *arg2, s32 arg3) {
    GameFE340Packet packet;

    packet.id = arg0[0x3B];
    packet.object = arg0;
    packet.value8 = 0;
    packet.valueC = 0.0f;
    packet.value10 = 0.0f;
    packet.value14 = 0.0f;
    packet.value18 = 0.0f;
    if (arg1 != 0) {
        packet.value1C = -30.0f;
    } else {
        packet.value1C = 30.0f;
    }
    packet.value20 = 0.0f;
    packet.value24 = 2;
    packet.value26 = 0x32;
    packet.value28 = 0x16;
    packet.value2A = 0x7D0;
    packet.value2C = 0;
    packet.value2E = 6;
    packet.value2F = 7;
    packet.value30 = -1;
    packet.value38 = 0;
    packet.value39 = -1;
    packet.value34 = D_800A0890;
    func_15134DAC(&packet.id, 0, arg2, arg3);
}
f32 func_150ADA68();                                /* extern */
extern f32 D_800A0894;

s32 func_150D11B4(void *arg0) {
    *(f32 *)((u8 *)arg0 + 0x74) = (f32) (((func_150ADA68() * 150.0f) + 350.0f) * D_800A0894);
    return 1;
}
typedef struct GameFE340Vec3 {
    f32 x;
    f32 y;
    f32 z;
} GameFE340Vec3;

void func_151DB5D0(s32, void *, void *, f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32);
u32 func_150ADA20(void);
extern f32 D_800A0898;
extern f32 D_800A089C;
extern f32 D_800A08A0;
extern f32 D_800A08A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D1204 CURRENT (891) */
void func_150D1204(GameFE340Vec3 *arg0, GameFE340Vec3 *arg1,
                    GameFE340Vec3 *arg2, GameFE340Vec3 *arg3,
                    f32 arg4, u8 *arg5) {
    GameFE340Vec3 start;
    f32 delta[3];
    f32 endX;
    f32 endY;
    f32 endZ;
    f32 random0;
    f32 random1;
    u32 random2;

    start.x = arg0->x + arg2->x * arg4;
    start.y = arg0->y + arg2->y * arg4;
    start.z = arg0->z + arg2->z * arg4;
    endX = arg1->x + arg3->x * arg4;
    endY = arg1->y + arg3->y * arg4;
    endZ = arg1->z + arg3->z * arg4;
    delta[0] = (endX - start.x) * *(f32 *)(arg5 + 0x74);
    delta[1] = (endY - start.y) * *(f32 *)(arg5 + 0x74);
    delta[2] = (endZ - start.z) * *(f32 *)(arg5 + 0x74);
    random0 = func_150ADA68();
    random1 = func_150ADA68();
    random2 = func_150ADA20();
    func_151DB5D0(0, &start, delta,
                  random0 * 61.0f + 60.0f, D_800A0898, D_800A089C,
                  random1 * D_800A08A0 + D_800A08A4,
                  (random2 & 0xF) + 0x23, (func_150ADA20() % 156U) + 0x64,
                  0x1E, 8, 0, arg5[0xC], arg5[1]);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D1204 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FE340/func_150D1204.s")
