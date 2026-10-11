#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1BFDD0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15192920
 * - func_151929A4
 * - func_15192D48
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);
typedef struct Game1BFDD0Packet {
    void *owner;
    u8 type;
    u8 pad5[3];
    f32 value;
} Game1BFDD0Packet;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15192920 CURRENT (507) */
void func_15192920(void *arg0) {
    Game1BFDD0Packet packet;
    s32 temp_v0;

    if (arg0 != 0) {
        packet.owner = arg0;
        packet.type = *(u8 *)((u8 *)arg0 + 0x3B);
        packet.value = 0.0f;
        temp_v0 = func_151491F4(0x23, -1, 0x14, 1, 0x10, 0xC, 0xFF, 1);
        if (temp_v0 != 0) {
            func_10022EC0((void *)(temp_v0 + 0x28), &packet, 0xC);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15192920 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BFDD0/func_15192920.s")
typedef struct Game1BFDD0Emitter {
    s32 flags;
    s32 field04;
    s16 effect;
    s16 lifetime;
    s32 field0C;
    s32 field10;
    u8 red, green, blue, alpha;
    u8 field18, field19, field1A, field1B;
    u8 field1C, kind;
    s16 field1E, field20, field22;
    f32 field24, field28, field2C;
    f32 x, y, z;
    u8 pad3C[0xC];
    f32 velocityX, velocityY, velocityZ;
    f32 field54;
    s32 soundFlags;
    u8 pad5C[4];
    u8 field60, field61, field62;
    s8 field63;
} Game1BFDD0Emitter;

void *func_15130374(s32, u8, s32, u8, s32);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
extern f32 D_800A8180;
extern f32 D_800A8184;
extern f32 D_800A8188;
extern f32 D_800A818C;
extern f32 D_800A8190;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151929A4 CURRENT (1190) */
void func_151929A4(void *arg0) {
    void *result;
    s32 side;
    f32 scale;
    f32 speed;
    Game1BFDD0Emitter emitter;
    Game1BFDD0Packet *packet;
    f32 extra;
    u8 *velocity;

    packet = (Game1BFDD0Packet *)((u8 *)arg0 + 0x28);
    packet->value += (312.0f + func_150ADA68() * D_800A8180) * D_800A8184 * D_800BE9A4;
    if ((packet->value > 1.0f) && (func_1515C0F8(packet->owner, &velocity) != 0)) {
        emitter.kind = 0x29;
        emitter.effect = 0xE03;
        emitter.flags = 0x200005;
        emitter.field18 = 0xB0;
        emitter.field19 = 0xA0;
        emitter.field1A = 0x2A;
        emitter.red = 0x40;
        emitter.green = 0xB;
        emitter.blue = 0x6A;
        emitter.field04 = 0;
        emitter.field0C = 0;
        emitter.field10 = 0;
        emitter.alpha = 0xFF;
        emitter.field1C = 0xFF;
        emitter.field60 = 3;
        emitter.field61 = 3;
        emitter.soundFlags = 0xE05;
        emitter.field62 = 0xA;
        emitter.field63 = -1;
        emitter.field1E = 0x14;
        emitter.field20 = 0xC;
        emitter.field22 = 0x23;
        emitter.field24 = D_800A8188;
        extra = D_800A818C;
        emitter.field54 = 0.0f;
        scale = D_800A8190;
        do {
            side = func_150ADA20();
            side &= 1;
            emitter.lifetime = func_150ADA20() % 31U + 0x14;
            emitter.field1B = func_150ADA20() % 156U + 0x64;
            speed = func_150ADA68() * 150.0f + 100.0f;
            emitter.field28 = speed;
            emitter.field2C = speed;
            if (side != 0) {
                speed = 20.0f;
            } else {
                speed = -20.0f;
            }
            func_15143874((s16)(*(u16 *)((u8 *)packet->owner + 0x7A) >> 8), speed, &emitter.x, &emitter.z);
            emitter.x += *(f32 *)((u8 *)packet->owner + 0x14);
            emitter.z += *(f32 *)((u8 *)packet->owner + 0x1C);
            emitter.y = *(f32 *)((u8 *)packet->owner + 0x180) + 20.0f;
            emitter.soundFlags &= ~0xC0;
            if (func_150ADA20() & 1) {
                emitter.soundFlags |= 0x40;
            }
            if (func_150ADA20() & 1) {
                emitter.soundFlags |= 0x80;
            }
            emitter.velocityX = *(f32 *)(velocity + 0) * scale;
            emitter.velocityY = *(f32 *)(velocity + 4) * scale;
            emitter.velocityZ = *(f32 *)(velocity + 8) * scale;
            result = func_15130374((s32)&emitter, 1, 4, ((u8 *)arg0)[0xC], ((u8 *)arg0)[1]);
            if (result != NULL) {
                func_10022EC0((u8 *)result + 0xA8, &extra, 4);
            }
            packet->value -= 1.0f;
        } while (packet->value > 1.0f);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151929A4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BFDD0/func_151929A4.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15192D48 CURRENT (146) */
s32 func_15192D48(void *arg0, s16 arg1, u8 arg2, s32 arg3) {
    Game1BFDD0Packet packet;
    s32 temp_v0;
    s32 var_v1;

    if (arg0 == 0) {
        return 0;
    }
    packet.owner = arg0;
    packet.type = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.value = 0.0f;
    temp_v0 = func_151491F4(arg1, -1, 0x18, 1, 0x16, 0xC, (s32)arg2, arg3);
    var_v1 = temp_v0;
    if (temp_v0 != 0) {
        func_10022EC0((u8 *)temp_v0 + 0x28, &packet, 0xC);
        var_v1 = temp_v0;
    }
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15192D48 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1BFDD0/func_15192D48.s")
