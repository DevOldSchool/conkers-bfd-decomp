#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_135780.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151082D0
 * - func_15108658
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game135780EmitterState {
    f32 accumulator;
    s16 *configuration;
    u8 flags;
} Game135780EmitterState;

typedef struct Game135780SpawnPacket {
    s32 flags;
    s32 word4;
    s16 kind;
    s16 life;
    s32 wordC;
    s32 word10;
    u8 byte14, byte15, byte16, byte17;
    u8 byte18, byte19, byte1A, byte1B;
    u8 byte1C, byte1D;
    s16 short1E, short20, short22;
    f32 scale, width, height;
    f32 x, y, z;
    f32 float3C, float40, float44, float48, float4C, float50, float54;
    s32 flags58;
    s32 word5C;
    s8 mode60, mode61, mode62, mode63, mode64, mode65;
    u8 tail66[0xA];
} Game135780SpawnPacket;

void *func_10022EC0(void *, const void *, u32);
void func_1514373C(f32, f32, f32 *, f32 *);
f32 func_150ADA68(void);
extern f32 D_800A2450, D_800A2454, D_800A245C;
extern const f32 D_800A2458;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151082D0 CURRENT (4162) */
void func_151082D0(u8 *arg0) {
    u8 *temp_v0_2;
    Game135780SpawnPacket packet;
    f32 extra[5];
    f32 temp_fa0;
    f32 temp_fv1;
    Game135780EmitterState *state;

    state = (Game135780EmitterState *)(arg0 + 0x28);
    state->accumulator = (f32) (state->accumulator + ((D_800A2450 + (func_150ADA68() * D_800A2454)) * D_800BE9A4));
    if (state->accumulator > 1.0f) {
        if (state->flags & 1) {
            packet.byte1D = 0x74;
            packet.kind = 0x5310;
            packet.flags = 0x200005;
            packet.word4 = 0x9F0600;
            packet.byte14 = 0xFF;
            packet.byte15 = 0xFF;
            packet.byte16 = 0xFF;
            packet.byte17 = 0xFF;
            packet.byte1C = 0xFF;
            packet.short1E = 1;
            packet.wordC = 0;
            packet.word10 = 0;
            packet.float3C = 0.0f;
            packet.float40 = 0.0f;
            packet.float44 = 0.0f;
            packet.float48 = 0.0f;
            packet.float4C = 0.0f;
            packet.float50 = 0.0f;
            packet.float54 = 0.0f;
            packet.short20 = 0xFF;
            packet.short22 = 1;
            packet.scale = 1.0f;
            packet.mode60 = 6;
            packet.mode61 = 6;
            packet.mode62 = 0x18;
            packet.mode63 = -1;
            packet.mode64 = -1;
            packet.mode65 = 0;
            packet.word5C = 0;
            packet.life = 0x12C;
            packet.byte18 = 0xFF;
            packet.byte19 = 0xFF;
            packet.byte1A = 0xFF;
            extra[4] = 0.0f;
            do {
                temp_fv1 = (func_150ADA68() * 20.0f) + 30.0f;
                temp_fa0 = temp_fv1 * D_800A2458;
                extra[0] = temp_fv1;
                extra[1] = temp_fv1;
                extra[2] = temp_fa0;
                extra[3] = temp_fa0 * 0.5f;
                temp_fv1 = (func_150ADA68() * 500.0f) + 600.0f;
                packet.width = temp_fv1;
                packet.height = temp_fv1 * 0.5f;
                temp_fv1 = func_150ADA68();
                func_1514373C(2.0f * (temp_fv1 * D_800A245C), (f32) state->configuration[3], &packet.x, &packet.z);
                packet.x += (f32) state->configuration[0];
                packet.z += (f32) state->configuration[2];
                temp_fv1 = func_150ADA68();
                packet.y = (temp_fv1 * (f32) state->configuration[4]) + (f32) state->configuration[1];
                packet.flags58 = ((func_150ADA20() & 1) ? 0x40 : 0) | 0xC000;
                packet.byte1B = (func_150ADA20() & 0x7F) + 0x80;
                temp_v0_2 = func_15130280(&packet, 2, 0, 0x14, (s32) arg0[0xC], (s32) arg0[1]);
                if (temp_v0_2 != 0) {
                    func_10022EC0(temp_v0_2 + 0xA8, extra, 0x14U);
                }
                state->accumulator = (f32) (state->accumulator - 1.0f);
            } while (state->accumulator > 1.0f);
            return;
        }
        do {
            state->accumulator = (f32) (state->accumulator - 1.0f);
        } while (state->accumulator > 1.0f);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151082D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_135780/func_151082D0.s")
f32 func_150ADA68();                                /* extern */
extern f32 D_800A2460;
extern f32 D_800A2464;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15108658 CURRENT (1491) */
s32 func_15108658(u8 *arg0, s32 arg1) {
    void *sp18;
    f32 temp_fv0;
    f32 temp_fv1;
    u8 *var_v0;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0xA8);
    var_v0 = (void *)(arg0 + 0xA8);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0xAC) - temp_fv0;
    if ((temp_fv0 < *(f32 *)((u8 *)arg0 + 0xB4)) || (temp_fv1 < *(f32 *)((u8 *)var_v0 + 0xC))) {
        *(s32 *)((u8 *)arg0 + 0x1C) = 0;
        var_v0 = (void *)(arg0 + 0xA8);
    } else {
        temp_fv0 = *(f32 *)((u8 *)var_v0 + 8);
        if ((*(f32 *)((u8 *)var_v0 + 0) < temp_fv0) || (temp_fv1 < temp_fv0)) {
            *(s32 *)((u8 *)arg0 + 0x1C) = 0x10000;
        } else {
            *(s32 *)((u8 *)arg0 + 0x1C) = 0x20000;
        }
    }
    temp_fv0 = *(f32 *)((u8 *)var_v0 + 0x10);
    if (temp_fv0 != 0.0f) {
        if ((temp_fv0 < D_800A2460) || ((11.0f - temp_fv0) < D_800A2460)) {
            *(s32 *)((u8 *)arg0 + 0x1C) = 0;
            *(s8 *)((u8 *)arg0 + 0x74) = -1;
        } else {
            *(s8 *)((u8 *)arg0 + 0x74) = 3;
        }
        *(f32 *)((u8 *)var_v0 + 0x10) = (f32) (*(f32 *)((u8 *)var_v0 + 0x10) - D_800BE9A4);
        if (*(f32 *)((u8 *)var_v0 + 0x10) < 0.0f) {
            *(f32 *)((u8 *)var_v0 + 0x10) = 0.0f;
            *(s8 *)((u8 *)arg0 + 0x74) = -1;
        }
        goto block_19;
    }
    *(f32 *)((u8 *)var_v0 + 0) = (f32) (*(f32 *)((u8 *)var_v0 + 0) - D_800BE9A4);
    if (*(f32 *)((u8 *)var_v0 + 0) < 0.0f) {
        return 0;
    }
    if (*(s32 *)((u8 *)arg0 + 0x1C) == 0x20000) {
        sp18 = var_v0;
        if (func_150ADA68() < D_800A2464) {
            *(f32 *)((u8 *)var_v0 + 0x10) = 11.0f;
        }
    }
block_19:
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15108658 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_135780/func_15108658.s")
void func_151087FC(u8 *arg0, u8 arg1, u8 arg2) {
    u8 *state = arg0 + 0x28;

    if (arg2 == 0x2B) {
        state[8] |= 1;
    } else if (arg2 == 0x2C) {
        state[8] &= ~1;
    }
}
