#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1D3AB0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_structural_families_continued.md
 */

typedef struct {
    s32 field00, field04;
    s16 field08, field0A;
    s32 field0C, field10;
    u8 colors[8];
    u8 field1C, field1D;
    s16 field1E, field20, field22;
    f32 scale, size1, size2;
    Vec3f position, base, velocity;
    f32 field54;
    s32 flags, field5C;
    u8 field60, field61;
    s8 field62, field63, field64;
    u8 field65, field66, pad67[9];
} Game1D3AB0Descriptor;

typedef struct {
    s16 *origin;
    f32 angle;
    f32 speed;
    u8 pad0C[8];
    u8 phase;
    u8 phaseRate;
    u8 alpha;
    u8 pad17;
    f32 pending;
} Game1D3AB0State;

void func_1508B20C(f32, f32, f32, f32);
f32 func_15144528(f32, f32, f32);
f32 func_150ADA68(void);
void func_15143794(s16, s16, f32, void *);
extern f32 D_800BE9A4;
extern s32 D_800BE9E4;
extern f32 D_800A8DA0, D_800A8DA4, D_800A8DA8, D_800A8DAC;

s32 func_151A6600(u8 *arg0) {
    Game1D3AB0State *state;
    Game1D3AB0Descriptor packet;
    u32 first;
    u32 second;

    state = (Game1D3AB0State *)(arg0 + 0x110);
    if (arg0[0x127] != 0) {
        func_1508B20C(*(f32 *)(arg0 + 0x34), *(f32 *)(arg0 + 0x38), *(f32 *)(arg0 + 0x3C), 500.0f);
    }
    state->angle += state->speed * D_800BE9A4;
    state->angle = func_15144528(state->angle, 2048.0f, 0.0f);
    state->phase += state->phaseRate * D_800BE9E4;
    state->alpha = func_151423D8(state->phase - 0x40) * 63.0f + 192.0f;
    if (!func_151464B8(*(s16 **)(arg0 + 0x60))) {
        state->pending += (0.393f + func_150ADA68() * 0.437f) * D_800BE9A4;
        if (1.0f < state->pending) {
            packet.field1D = 0x28;
            packet.field08 = 0x2203;
            packet.field00 = 0x200005;
            packet.field04 = 0x1F0600;
            packet.colors[0] = 0xFF;
            packet.colors[1] = 0xFF;
            packet.colors[2] = 0xFF;
            packet.colors[3] = 0xFF;
            packet.colors[4] = 0xFF;
            packet.colors[5] = 0xFF;
            packet.base.x = 0.0f;
            packet.base.y = 0.0f;
            packet.base.z = 0.0f;
            packet.field0C = 0;
            packet.field10 = 0;
            packet.colors[6] = 0xFF;
            packet.field1E = 0xC;
            packet.field20 = 0x15;
            packet.field22 = 1;
            packet.scale = 1.0f;
            packet.flags = 0xC207;
            packet.field60 = 6;
            packet.field61 = 8;
            packet.field62 = -1;
            packet.field63 = -1;
            packet.field64 = -1;
            packet.field65 = 0;
            do {
                first = func_150ADA20();
                func_15143874((u8)first, state->origin[3] * func_150ADA68(), &packet.position.x, &packet.position.z);
                packet.position.x += state->origin[0];
                packet.position.y = state->origin[1];
                packet.position.z += state->origin[2];
                packet.field0A = (func_150ADA20() & 0xF) + 0x19;
                packet.colors[7] = func_150ADA20() % 101 + 100;
                packet.size1 = packet.size2 = func_150ADA68() * 205.0f + 98.0f;
                second = func_150ADA20();
                first = func_150ADA20();
                func_15143794((u8)second, first % 35 - 0x40, func_150ADA68() * 10.0f + 10.0f, &packet.velocity);
                packet.field54 = func_150ADA68() * 0.284f + -0.91f;
                func_15130280(&packet, 1, 0, 0, arg0[0xC], arg0[1]);
                state->pending -= 1.0f;
    } while (1.0f < state->pending);
        }
}
    return 1;
}
void func_1000FD38(void *, void *, s32, void *);
extern u8 D_1000EF40;

void func_151A6AB8(void *arg0) {
    void *temp_a0;

    *(s8 *)(*(u8 **)((u8 *)arg0 + 0x110) + 0x14) = 1;
    func_1000FD38(&D_1000EF40, *(void **)((u8 *)arg0 + 0x110), 0, arg0);
    temp_a0 = *(void **)((u8 *)arg0 + 0x120);
    if (temp_a0 != 0) {
        func_1516972C(temp_a0);
    }
}
