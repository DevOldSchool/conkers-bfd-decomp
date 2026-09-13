#include "types.h"

/*
 * Reviewed source unit: src/game/game_3D9A0.c
 * Boundary evidence: docs/evidence/game_compact_multi_function_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150104F0
 * - func_15010538
 * - func_15010600
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 func_151149AC(u8 arg0);
extern u8 D_800D9950[];
extern s8 D_80088980;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150104F0 CURRENT (140) */
void func_150104F0(void) {
    D_800D9950[1] = 0;
    D_800D9950[0] = 0;
    D_800D9950[2] = 0;
    *(f32 *)((u8 *)func_151149AC(0xF6) + 0x7C) = 2.0f;
    D_80088980 = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150104F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_3D9A0/func_150104F0.s")

void func_10022EC0(void *arg0, void *arg1, s32 arg2);
u8 *func_15149130(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);
void func_15161E24(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);

typedef struct Game3D9A0Packet {
    void *owner;
    u8 type;
    u8 pad5;
    s16 x;
    s16 y;
    s16 z;
} Game3D9A0Packet;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15010538 CURRENT (195) */
void func_15010538(void *arg0) {
    Game3D9A0Packet packet;
    u8 *object;

    func_15161E24(arg0, 2, 2, 0x12C, 0x1E, 0x64, 0xC8, 0xFF, 0xFF, 1);
    packet.owner = arg0;
    packet.x = 0;
    packet.y = 0;
    packet.z = 0;
    packet.type = ((u8 *)arg0)[0x3B];

    object = func_15149130(0x12C, -1, 0x50, -1, 0, 0x3D, 0xC, 0xFF, 1);
    if (object != 0) {
        func_10022EC0(object + 0x28, &packet, sizeof(packet));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15010538 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_3D9A0/func_15010538.s")

typedef struct Game3D9A0Bytes4 {
    s8 byte0;
    s8 byte1;
    s8 byte2;
    s8 byte3;
} Game3D9A0Bytes4;

extern s8 D_800D9920;
extern s8 D_800D9921;
extern s8 D_800D9928;
extern s8 D_800D9929;
extern Game3D9A0Bytes4 D_800D992A;
extern s8 D_800D9938;
extern s8 D_800D9939;
extern Game3D9A0Bytes4 D_800D993A;
extern s8 D_800D9946;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15010600 CURRENT (1945) */
void func_15010600(void) {
    Game3D9A0Bytes4 *var_a0;
    Game3D9A0Bytes4 *var_v1;

    D_800D9921 = 0;
    D_800D9920 = 0;
    D_800D9928 = 0;
    D_800D9938 = 0;
    D_800D9929 = 0;
    var_a0 = &D_800D993A;
    var_v1 = &D_800D992A;
    D_800D9939 = 0;
    do {
        var_a0++;
        var_v1->byte1 = 0;
        var_a0[-1].byte1 = 0;
        var_v1->byte2 = 0;
        var_a0[-1].byte2 = 0;
        var_v1->byte3 = 0;
        var_a0[-1].byte3 = 0;
        var_v1++;
        var_v1[-1].byte0 = 0;
        var_a0[-1].byte0 = 0;
    } while ((s8 *)var_a0 != &D_800D9946);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15010600 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_3D9A0/func_15010600.s")
