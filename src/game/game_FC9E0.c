#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_FC9E0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150CF680
 * - func_150CF800
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern void func_151CF898(void *arg0, f32 arg1, f32 arg2);
typedef struct GameCollisionHeightActor {
    u8 pad00[0x18];
    f32 y;
    u8 pad1C[0x2FC];
    void *entity;
    u8 pad31C[0x10];
} GameCollisionHeightActor;

extern GameCollisionHeightActor D_800CC2D0[];

void func_150CF530(s32 arg0) {
    func_151CF898(&D_800CC2D0[0], D_800CC2D0[0].y + 300.0f, -10000.0f);
}
extern s32 D_80088890;
extern s32 D_80088894;
extern s32 D_80088898;
extern s32 D_800BE9E4;

void func_150CF578(s32 arg0) {
    s32 count;
    s32 temp_v1;

    count = D_800BE9E4;
    D_80088890 += count * 0x1A;
    temp_v1 = count * 0x1C;
    D_80088894 -= temp_v1;
    D_80088898 -= temp_v1;
}
extern s32 D_8008889C;

typedef struct GameFC9E0Command {
    u32 w0;
    u32 w1;
} GameFC9E0Command;

GameFC9E0Command *func_150CF5E8(GameFC9E0Command *arg0) {
    { GameFC9E0Command *command = arg0++; command->w0 = 0xF2000000 | (((D_80088890 >> 7) & 0xFFF) << 12) | ((D_80088894 >> 7) & 0xFFF); command->w1 = 0x47E47E; }
    { GameFC9E0Command *command = arg0++; command->w0 = 0xF2000000 | (((D_80088898 >> 7) & 0xFFF) << 12) | ((D_8008889C >> 7) & 0xFFF); command->w1 = 0x0147E47E; }
    return arg0;
}
void *func_10022EC0(void *, const void *, u32);
extern s32 D_80082FA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CF680 CURRENT (2087) */
void func_150CF680(s16 arg0, u8 arg1, s32 arg2) {
    struct {
        u8 sp30;
        u8 gap31[3];
        f32 sp34, sp38, sp3C, sp40, sp44, sp48, sp4C;
        u8 sp50;
        u8 gap51;
        s16 sp52, sp54, sp56, sp58;
        u8 sp5A, sp5B, sp5C, sp5D, sp5E, sp5F, sp60, sp61, sp62, sp63;
        s32 sp64, sp68, sp6C, sp70, sp74, sp78, sp7C;
        u8 sp80, sp81;
        u8 gap82[2];
        s8 sp84;
        u8 gap85[3];
        f32 sp88, sp8C, sp90, sp94;
    } locals;
    u8 *result;

    locals.sp54 = 0x31;
    locals.sp5A = 8;
    locals.sp50 = 0xC1;
    locals.sp56 = 1;
    locals.sp61 = 0xFF;
    locals.sp52 = arg0;
    locals.sp44 = 72.0f;
    locals.sp58 = 0xFF;
    locals.sp5B = 0xFF;
    locals.sp63 = 0xFF;
    locals.sp68 = 0x200004;
    locals.sp5C = 0xFF;
    locals.sp5D = 0xFF;
    locals.sp5E = 0xFF;
    locals.sp5F = 0xFF;
    locals.sp60 = 0xFF;
    locals.sp62 = 0xFF;
    locals.sp30 = 0;
    locals.sp34 = 0.0f;
    locals.sp40 = -300.0f;
    locals.sp38 = -300.0f;
    locals.sp3C = 0.0f;
    locals.sp4C = 7.5f;
    locals.sp48 = 7.5f;
    locals.sp64 = 0;
    locals.sp6C = 0x9F0601;
    locals.sp80 = 0;
    locals.sp81 = 0xA;
    locals.sp70 = 0x17;
    locals.sp74 = 0x44;
    locals.sp78 = 0x80;
    locals.sp7C = 0x20;
    locals.sp8C = 1.0f;
    locals.sp88 = 1.0f;
    locals.sp94 = 0.0f;
    locals.sp90 = 0.0f;
    locals.sp84 = D_80082FA0;
    result = func_1515548C(&locals.sp40, 0xC, 0, 0, 0x10, arg1, arg2);
    if (result != 0) {
        func_10022EC0(result + 0x70, &locals.sp30, 0x10);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CF680 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FC9E0/func_150CF680.s")
f32 func_15047D60(f32);
f32 func_150ADA68(void);
extern s32 (*D_8008FCD0[])(void);
extern f32 D_800A0860, D_800A0864, D_800A0868, D_800A086C;
extern f32 D_800A0870, D_800A0874;
extern f32 D_800BE9A4;

typedef struct GameFC9E0Position2 {
    f32 x, y;
} GameFC9E0Position2;

typedef struct GameFC9E0SpawnPacket {
    GameFC9E0Position2 position;
    f32 scaleX, scaleY;
    s8 selector;
    u8 pad11;
    s16 lifetime, flags, field16, field18;
    u8 color0, color1, color2, color3, color4;
    u8 color5, color6, color7, color8, color9;
    s32 field24, field28, field2C, field30, field34, field38, field3C;
    s8 field40, field41;
    u8 pad42[2];
    s8 field44;
    u8 pad45[3];
    f32 field48, field4C, field50, field54;
} GameFC9E0SpawnPacket;

typedef struct GameFC9E0Motion {
    f32 x, y, z, height;
} GameFC9E0Motion;

typedef struct GameFC9E0State {
    u8 flags;
    u8 pad01[3];
    f32 phase, originX, deltaX;
} GameFC9E0State;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CF800 CURRENT (1466) */
s32 func_150CF800(void *arg0) {
    f32 phase;
    GameFC9E0SpawnPacket packet;
    GameFC9E0Motion motion;
    GameFC9E0State *state;
    s32 flags1;
    s8 count;
    s8 selectedCount;
    s8 copiedCount;
    u32 random;
    void *result;

    if (*(u8 *)((u8 *)arg0 + 0x70) & 1) {
        state = (GameFC9E0State *)((u8 *)arg0 + 0x70);
        state->phase = state->phase + D_800A0860 * D_800BE9A4;
        phase = state->phase;
        if (phase >= 1.0f) {
            state->phase = 1.0f;
            state->flags &= 0xFFFE;
            selectedCount = (func_150ADA20() & 3) + 2;
            copiedCount = selectedCount;
            motion.height = *(f32 *)((u8 *)arg0 + 0x14) + 15.0f;
            count = copiedCount;
            packet.position = *(GameFC9E0Position2 *)((u8 *)arg0 + 0x10);
            packet.color7 = 0xFF;
            packet.field16 = 0xC;
            packet.field18 = 0x15;
            packet.color8 = 0xFF;
            packet.color1 = 0xFF;
            packet.color2 = 0xFF;
            packet.color3 = 0xFF;
            packet.color5 = 0xFF;
            packet.color6 = 0xFF;
            packet.color9 = 0xFF;
            packet.color0 = 0;
            packet.field24 = 0;
            packet.field28 = 0x200004;
            packet.field2C = 0x9F0601;
            packet.field40 = 0;
            packet.field41 = 0xA;
            packet.field30 = 0x17;
            packet.field34 = 0x44;
            packet.field38 = 0x80;
            packet.field3C = 0x20;
            packet.field48 = 1.0f;
            packet.field4C = 1.0f;
            packet.field54 = 0.0f;
            packet.field50 = 0.0f;
            packet.field44 = D_80082FA0;
            if (selectedCount > 0) {
                phase = 2.0f;
                do {
                    packet.color4 = func_150ADA20() % 101U + 0x9B;
                    packet.selector = D_8008FCD0[2]();
                    random = func_150ADA20();
                    func_15143874((s16)((random % 65U) - 0xA0),
                                   func_150ADA68() * phase + 2.5f,
                                   &motion.x, &motion.y);
                    motion.z = func_150ADA68() * 0.3330000042915344f + 0.40400001406669617f;
                    packet.scaleY = packet.scaleX = func_150ADA68() * 1.7899999618530273f + 1.6999999284744263f;
                    packet.lifetime = func_150ADA20() % 26U + 0x1E;
                    if (func_150ADA20() & 1) flags1 = 2;
                    else flags1 = 0;
                    if (func_150ADA20() & 1) random = 4;
                    else random = 0;
                    packet.flags = random | 1 | flags1 | 0x38;
                    result = func_1515548C(&packet, 0xD, 0, 0, 0x10,
                                           *(u8 *)((u8 *)arg0 + 0xC),
                                           *(u8 *)((u8 *)arg0 + 1));
                    if (result != NULL) {
                        func_10022EC0((u8 *)result + 0x70, &motion, 0x10);
                    }
                    count -= 1;
                } while (count > 0);
            }
            phase = state->phase;
        }
        *(f32 *)((u8 *)arg0 + 0x10) = state->originX + phase * state->deltaX;
        *(f32 *)((u8 *)arg0 + 0x14) =
            func_15047D60(state->phase * D_800A0874) * -17.5f + 72.0f;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CF800 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FC9E0/func_150CF800.s")
void func_150CFBEC(u8 *arg0, f32 *arg1, u8 arg2) {
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + 0x70);
    if (arg2 == 0x52) {
        *temp_v0 = (u8)(*temp_v0 | 1);
        *(f32 *)((u8 *)temp_v0 + 4) = 0.0f;
        *(f32 *)((u8 *)temp_v0 + 8) = (f32) *(f32 *)((u8 *)arg0 + 0x10);
        *(f32 *)((u8 *)temp_v0 + 0xC) = (f32) (*arg1 - *(f32 *)((u8 *)arg0 + 0x10));
    }
}
void func_150CFC38(f32 arg0) {
    f32 sp1C;

    sp1C = arg0;
    func_1515572C(&sp1C, 0x52);
}
