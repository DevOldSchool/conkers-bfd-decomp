#include "types.h"

/*
 * Reviewed source unit: src/game/game_1C0840.c
 * Boundary evidence: docs/evidence/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15193390
 * - func_151934B4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    u8 pad00[0x86];
    s16 field86;
    u8 pad88[4];
    s16 field8C;
    s16 field8E;
    s16 field90;
    s16 field92;
    s16 field94;
    s16 field96;
    s16 field98;
    u8 pad9A[6];
    s8 fieldA0;
    u8 padA1;
    s8 fieldA2;
    u8 fieldA3;
    u8 fieldA4;
    u8 padA5[3];
} Game1C0840Packet;

typedef struct {
    Game1C0840Packet packet;
    u8 tail[8];
} Game1C0840Locals;

void func_100226F0(void *, s32);
void func_1516865C(void *, s32, s32, s32, s32);
void *func_15168800(void *, u8, s32);
u32 func_150ADA20(void);
extern f32 D_800A81B0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15193390 CURRENT (1543) */
void func_15193390(void *volatile arg0) {
    Game1C0840Locals locals;
    s16 temp_v1;
    u8 *temp_v0;

    func_100226F0(&locals.packet, 0xA8);
    temp_v1 = *(s16 *)((u8 *)arg0 + 0x2E);
    temp_v0 = (u8 *)arg0 + 0x28;
    if (D_800A81B0 != (f32)temp_v1) {
        locals.packet.field96 = temp_v1;
    } else {
        locals.packet.field96 = (s16)(s32)((f32)*(s16 *)(temp_v0 + 2) - 200.0f);
        temp_v0[8] = 0;
    }
    locals.packet.field8C = *(s16 *)(temp_v0 + 0);
    locals.packet.field8E = *(s16 *)(temp_v0 + 2);
    locals.packet.field92 = 0;
    locals.packet.field94 = 0;
    locals.packet.fieldA2 = 0xF;
    locals.packet.fieldA0 = 0x45;
    locals.packet.field86 = 0xA;
    locals.packet.field90 = *(s16 *)(temp_v0 + 4);
    locals.packet.field98 = 0x4880;
    locals.packet.fieldA4 = 0x80;
    locals.packet.fieldA3 = temp_v0[8];
    func_1516865C(&locals.packet, 0xFF, 0xFF, 0xFF, 0x80);
    func_15168800(&locals.packet, *((u8 *)arg0 + 0xC), *((u8 *)arg0 + 1));
    *(s16 *)((u8 *)arg0 + 0xE) = (func_150ADA20() & 0x7F) + 0x64;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15193390 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1C0840/func_15193390.s")
void func_151DBCBC(s32, f32, u8, s32, f32 *, s32, s32);
extern s32 D_800BE9E4;

typedef struct Game1C0840Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Game1C0840Vec3;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151934B4 CURRENT (17) */
void func_151934B4(u8 *actor) {
    f32 position[3];
    s16 timer;
    s32 quarter;

    if (*(s16 *)(actor + 0xA4) < *(s16 *)(actor + 0x96)) {
        timer = *(s16 *)(actor + 0xAA);
        quarter = timer >> 2;
        *(s16 *)(actor + 0xA4) = (quarter * 0x18) / 3;
        *(s16 *)(actor + 0xA2) = (quarter * 6) / 3;
        *(s16 *)(actor + 0xAA) = timer + D_800BE9E4;
        return;
    }

    *(s16 *)(actor + 0x94) += 1;
    if (*(s16 *)(actor + 0x94) >= 0x15) {
        *(s16 *)(actor + 0x94) = 0x14;
    }
    *(s16 *)(actor + 0x9E) -= ((s32)(*(s16 *)(actor + 0x94) * D_800BE9E4) >> 1);
    if (*(s16 *)(actor + 0x9E) < *(s16 *)(actor + 0xA6)) {
        if (*(s8 *)(actor + 0xB3) == 1) {
            position[0] = *(s16 *)(actor + 0x9C);
            position[1] = *(s16 *)(actor + 0xA6);
            position[2] = *(s16 *)(actor + 0xA0);
            func_151DBCBC(5, 30.0f, 0xFF, 0, position, actor[0xC], actor[1]);
        }
        *(s16 *)(actor + 0x98) = -1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151934B4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1C0840/func_151934B4.s")
