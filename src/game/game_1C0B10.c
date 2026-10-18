#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1C0B10.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15193660
 * - func_151938FC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game193660Packet {
    s32 head[2];
    u8 scratch[0xC];
    s16 shorts34[4];
    f32 floats3C[5];
    s16 shorts50[2];
    s32 words54[3];
    f32 floats60[10];
    u8 bytes88[10];
    s16 shorts92[2];
    u8 pad96[2];
} Game193660Packet;

void func_15152520(s32 *, u8, s32);
extern f32 D_800A81C0;
extern f32 D_800A81C4;
extern f32 D_800A81C8;
extern f32 D_800A81CC;
extern f32 D_800A81D0;
extern f32 D_800A81D4;
extern f32 D_800A81D8;
extern f32 D_800A81DC;
extern f32 D_800A81E0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15193660 CURRENT (1021) */
void func_15193660(u8 *arg0, u8 arg1, s32 arg2) {
    Game193660Packet packet;
    s32 temp_v0;

    if (arg0 != 0 && *(s32 *)arg0 != 0) {
        temp_v0 = *(s32 *)(arg0 + 0x1D4);
        if (temp_v0 != 0) {
            func_15142314(temp_v0, 0xA, packet.scratch);
            packet.head[0] = 8;
            packet.floats3C[0] = D_800A81C8;
            packet.head[1] = 7;
            packet.shorts34[2] = -0x21;
            packet.shorts34[3] = 0x18;
            packet.shorts50[0] = 0x28;
            packet.shorts50[1] = 0x23;
            packet.words54[0] = 0xA0;
            packet.words54[1] = 0x13;
            packet.bytes88[8] = 0x21;
            packet.bytes88[0] = 0xFF;
            packet.shorts34[0] = 0;
            packet.shorts34[1] = 0xFF;
            packet.words54[2] = 0;
            packet.bytes88[1] = 0xFF;
            packet.bytes88[2] = 0xFF;
            packet.bytes88[3] = 0xFF;
            packet.bytes88[4] = 0xFF;
            packet.bytes88[5] = 0xFF;
            packet.bytes88[6] = 0xFF;
            packet.bytes88[7] = 0xFF;
            packet.bytes88[9] = 0xF;
            packet.shorts92[0] = 0x19;
            packet.shorts92[1] = 0xA;
            packet.floats60[6] = D_800A81C0;
            packet.floats60[4] = D_800A81C0;
            packet.floats60[9] = D_800A81C4;
            packet.floats60[7] = D_800A81C4;
            packet.floats3C[1] = D_800A81CC;
            packet.floats3C[2] = D_800A81D0;
            packet.floats3C[3] = D_800A81D4;
            packet.floats3C[4] = D_800A81D8;
            packet.floats60[1] = D_800A81DC;
            packet.floats60[0] = 0.0f;
            packet.floats60[3] = 0.0f;
            packet.floats60[5] = 0.0f;
            packet.floats60[8] = 0.0f;
            packet.floats60[2] = D_800A81E0;
            func_15152520(packet.head, arg1, arg2);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15193660 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1C0B10/func_15193660.s")
typedef struct {
    u8 id;
    u8 pad1[3];
    void *object;
    s8 field8;
    u8 pad9[3];
    f32 values[6];
    s8 field24;
    u8 pad25;
    s16 field26;
    s16 field28;
    s16 field2A;
    u8 pad2C[2];
    s8 field2E;
    s8 field2F;
    s8 field30;
    u8 pad31[3];
    f32 field34;
    s8 field38;
    s8 field39;
} Game1C0B10Packet;

void *func_15134DAC();
extern f32 D_800A81E4;

void func_151937F4(void *arg0, s32 arg1, s32 arg2) {
    Game1C0B10Packet packet;

    if ((arg0 != 0) && (*(s32 *)arg0 != 0)) {
        packet.id = *(u8 *)((u8 *)arg0 + 0x3B);
        packet.values[0] = -28.0f;
        packet.object = arg0;
        packet.field8 = 0;
        packet.field24 = 2;
        packet.field26 = 0x1E;
        packet.field28 = 0x19;
        packet.field2A = 0x2EE;
        packet.field2E = 3;
        packet.field2F = 3;
        packet.field30 = -1;
        packet.field38 = 4;
        packet.field39 = -1;
        packet.values[1] = 6.0f;
        packet.values[2] = 1.0f;
        packet.values[3] = -58.0f;
        packet.values[4] = -3.0f;
        packet.values[5] = -31.0f;
        packet.field34 = D_800A81E4;
        func_15134DAC(&packet.id, 0, arg0);
    }
}
extern f32 D_800A81E8;

s32 func_151938E4(u8 *arg0) {
    *(f32 *)(arg0 + 0x74) = D_800A81E8;
    return 1;
}

typedef struct Game1938FCDescriptor {
    u8 kind, field01, field02;
    s8 field03, field04;
    u8 pad05;
    s16 lifetime;
    s32 field08, field0C, field10, flags14, flags18;
    s32 field1C, field20, field24, field28;
    u8 field2C, field2D;
    u8 pad2E[2];
    u8 colors[8];
    u8 field38;
    u8 pad39[3];
    struct Game1890A0State *owner;
    u8 generation, field41;
    u8 pad42[2];
    Vec3f position;
    u8 pad50[4];
    s16 field54, field56;
} Game1938FCDescriptor;

typedef struct Game1938FCMotion {
    f32 rotationX, rotationY, rotationZ;
    f32 speed;
    Vec3f velocity;
    f32 field1C, field20, field24, field28, field2C;
    u8 flags;
    u8 pad31[3];
} Game1938FCMotion;

s32 func_15157898(s32, s32, s32, f32, s32, s32, s32, u8, s32);
f32 func_150ADA68(void);
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
extern f32 D_800A81EC;
extern f32 D_800A81F0;
extern f32 D_800A81F4;
extern f32 D_800A81F8;
extern f32 D_800A81FC;
extern f32 D_800A8200;
extern f32 D_800A8204;
extern f32 D_800A8208;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151938FC CURRENT (1409) */
void func_151938FC(Vec3f *arg0, Vec3f *arg1, s32 arg2, s32 arg3, f32 arg4, u8 *arg5) {
    Game1938FCDescriptor descriptor;
    Game1938FCMotion motion;
    u8 *velocity;
    Vec3f delta;
    f32 random;

    if (func_1515C0F8(*(struct Game1890A0State **)(arg5 + 0x1C), &velocity) != 0) {
        if (*(u8 *)(*(u8 **)(arg5 + 0x1C) + 0xAD) == 0) {
            delta.x = *(f32 *)(velocity + 0);
            delta.y = *(f32 *)(velocity + 4);
            delta.z = *(f32 *)(velocity + 8);
            if (!(sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z) < D_800A81EC)) {
                descriptor.field38 = 0;
                descriptor.kind = 0x27;
                descriptor.field01 = 0;
                descriptor.field02 = 1;
                descriptor.field03 = -1;
                descriptor.field04 = -1;
                descriptor.lifetime = func_150ADA20() % 41U + 0x5A;
                descriptor.field08 = 0xA0;
                descriptor.field0C = 0x13;
                descriptor.flags14 = 0x220405;
                descriptor.flags18 = 0x40200;
                descriptor.field2D = 8;
                descriptor.field1C = 1;
                descriptor.field20 = 0x38;
                descriptor.field10 = 0;
                descriptor.field2C = 0;
                descriptor.field24 = 0x80;
                descriptor.field28 = 0x20;
                descriptor.colors[0] = 0xFF;
                descriptor.colors[1] = 0xFF;
                descriptor.colors[2] = 0xFF;
                descriptor.colors[3] = 0xFF;
                descriptor.colors[4] = 0xFF;
                descriptor.colors[5] = 0xFF;
                descriptor.colors[6] = 0xFF;
                descriptor.colors[7] = 0xFF;
                descriptor.owner = *(struct Game1890A0State **)(arg5 + 0x1C);
                descriptor.generation = *(u8 *)(*(u8 **)(arg5 + 0x1C) + 0x3B);
                descriptor.field41 = 1;
                descriptor.position = *arg0;
                delta.x = (arg1->x - arg0->x) * *(f32 *)(arg5 + 0x74);
                motion.velocity.x = delta.x;
                delta.y = (arg1->y - arg0->y) * *(f32 *)(arg5 + 0x74);
                motion.velocity.y = delta.y;
                delta.z = (arg1->z - arg0->z) * *(f32 *)(arg5 + 0x74);
                motion.velocity.z = delta.z;
                descriptor.position.x += delta.x * arg4;
                descriptor.position.y += delta.y * arg4;
                descriptor.position.z += delta.z * arg4;
                motion.rotationX = func_150ADA68() * 360.0f;
                motion.rotationY = func_150ADA68() * 360.0f;
                motion.rotationZ = func_150ADA68() * 360.0f;
                func_150ADA68();
                motion.speed = 340.0f * D_800A81F0;
                random = func_150ADA68() * 1000.0f;
                motion.field1C = (random + -500.0f) * D_800A81F4;
                motion.field20 = 0.0f;
                motion.field24 = (func_150ADA68() * 1000.0f + -500.0f) * D_800A81F8;
                random = func_150ADA68() * 121.0f + -135.0f;
                descriptor.field54 = 0x19;
                descriptor.field56 = 0xA;
                motion.flags = 0xF;
                motion.field28 = random * D_800A81FC;
                motion.field2C = D_800A8200;
                func_15157898((s32)&descriptor, (s32)&motion, 0, func_150ADA68() * D_800A8204 * D_800A8208,
                    0, 0, 0, arg5[0xC], arg5[1]);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151938FC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1C0B10/func_151938FC.s")
