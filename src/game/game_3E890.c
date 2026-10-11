#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_3E890.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_3E890.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150113E0
 * - func_1501175C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_3E890/func_150113E0.s")
typedef struct Game3E890Controller {
    void *owner;
    u8 id;
    s32 effect, light;
} Game3E890Controller;

typedef struct Game3E890Motion {
    void *owner;
    u8 id;
    f32 field08, field0C, field10, field14, field18, field1C, field20;
    f32 field24, field28, field2C, field30, field34, field38, field3C;
    f32 field40, field44, field48, field4C;
    void *controller;
    f32 size;
    s8 active;
} Game3E890Motion;

typedef struct Game3E890Words { s32 words[3]; } Game3E890Words;

typedef struct Game3E890Effect {
    u8 kind, mode;
    s16 texture, lifetime;
    s32 field08, field0C;
    u8 red, green, blue, alpha;
    f32 field14, field18;
    Game3E890Words first, second;
    f32 scaleX, scaleY, scaleZ;
    s32 field40;
    u8 field44, field45, field46, field47;
    s32 field48;
    u8 pad4C[8];
} Game3E890Effect;

typedef struct Game3E890Light {
    u8 kind;
    s8 id;
    s16 lifetime;
    s8 field4;
    s32 position[3];
} Game3E890Light;

void *func_10022EC0(void *, const void *, u32);
u32 func_150ADA20(void);
void *func_1513D2F0(s32, s32, u8, u8, u8, u8, u8, s32, s32, s32, u8, s32);
s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 D_80096508, D_8009650C, D_80096510, D_80096514;
extern f32 D_80096518, D_8009651C, D_80096520, D_80096524;
extern Game3E890Words D_800A5480;
extern u8 D_800A4AA0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501175C CURRENT (8185) */
void func_1501175C(void *arg0, u8 arg1, s32 arg2) {
    void *created;
    Game3E890Controller controller;
    u8 *state;
    Game3E890Motion motion;
    void *spawned;
    Game3E890Effect effect;
    Game3E890Light light;
    s32 mode;

    controller.owner = arg0;
    controller.id = *(u8 *)((u8 *)arg0 + 0x3B);
    controller.effect = 0;
    controller.light = 0;
    created = func_15149130(0x12C, -1, 0x54, -1, 0, 0x34, 0x10, arg1, arg2);
    state = (u8 *)created + 0x28;
    if (created != NULL) {
        func_10022EC0(state, &controller, 0x10);
        motion.active = 0;
        motion.owner = arg0;
        motion.size = (*(f32 *)((u8 *)arg0 + 0x150) + *(f32 *)((u8 *)arg0 + 0x14C)) * 0.5f;
        motion.field08 = D_80096508;
        motion.field10 = D_8009650C;
        motion.field18 = D_80096510;
        motion.field0C = D_80096514;
        motion.field24 = 0.0f;
        motion.field28 = 0.0f;
        motion.field38 = 0.0f;
        effect.field14 = 0.0f;
        effect.field18 = 0.0f;
        motion.field3C = 0.0f;
        motion.field48 = 1.0f;
        motion.field40 = 1.0f;
        motion.field4C = 1.0f;
        motion.field44 = 1.0f;
        motion.controller = created;
        effect.kind = 0x5F;
        effect.mode = 9;
        effect.texture = 0x2203;
        effect.lifetime = 0x12C;
        effect.field08 = 0;
        effect.field0C = 0;
        effect.red = 0xFF;
        effect.green = 0xFF;
        effect.blue = 0xFF;
        effect.alpha = 0xFF;
        motion.id = *(u8 *)((u8 *)arg0 + 0x3B);
        motion.field14 = D_80096518;
        motion.field20 = D_8009651C;
        motion.field1C = D_80096520;
        motion.field2C = 160.0f;
        motion.field30 = 95.0f;
        motion.field34 = D_80096524;
        effect.first = D_800A5480;
        effect.second = D_800A5480;
        effect.scaleX = 1.0f;
        effect.scaleY = 1.0f;
        effect.scaleZ = 1.0f;
        effect.field40 = 0x40EC0000;
        effect.field44 = 0;
        effect.field45 = 0xFF;
        effect.field46 = 0;
        effect.field47 = 7;
        effect.field48 = 0;
        mode = (func_150ADA20() & 1) ? 2 : 0;
        spawned = func_1513D2F0((s32)&effect, (s32)&D_800A4AA0, 0, 0x25, 0,
                                0x1D, mode + 1, 0, 0, 0x5C, arg1, arg2);
        *(s32 *)(state + 8) = (s32)spawned;
        if (spawned != NULL) {
            func_10022EC0((u8 *)spawned + 0x110, &motion, 0x5C);
        }
        light.kind = 2;
        light.id = -1;
        light.lifetime = 0x12C;
        light.field4 = 0;
        light.position[0] = 0;
        light.position[1] = 0;
        light.position[2] = 0;
        *(s32 *)(state + 0xC) = func_151602C0(&light.kind, light.position, 0x28, 0xFF, 0xFF,
                                    0xFF, 0xFF, 1, 0, arg1, arg2);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501175C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_3E890/func_1501175C.s")
void *func_10022EC0(void *, const void *, u32);

typedef struct Game3E890Packet {
    void *owner;
    u8 type;
    u8 pad5;
    s16 field6;
} Game3E890Packet;

void func_15011A78(void *arg0, u8 arg1, s32 arg2) {
    Game3E890Packet packet;
    u8 *temp_v0;

    packet.owner = arg0;
    packet.type = *(u8 *)((u8 *)arg0 + 0x3B);
    packet.field6 = 0;
    temp_v0 = func_15149130(0x12C, -1, 0x55, -1, 0, 0x42, 8, (s32)arg1, arg2);
    if (temp_v0 != 0) {
        func_10022EC0(temp_v0 + 0x28, &packet, 8);
    }
}
