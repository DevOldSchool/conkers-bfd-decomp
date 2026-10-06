#include "types.h"

/*
 * Reviewed source unit: src/game/game_1FBB80.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151CE6D0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1FBB80Owner {
    s16 field00;
    s16 mask;
} Game1FBB80Owner;

typedef struct Game1FBB80Effect {
    void *shape;
    f32 rate;
    f32 accumulator;
    Game1FBB80Owner *owner;
    f32 height;
} Game1FBB80Effect;

typedef struct Game1FBB80Object {
    u8 pad00, flags01;
    u8 pad02[0xA];
    u8 flags0C;
    u8 pad0D[0x1B];
    Game1FBB80Effect effect;
} Game1FBB80Object;

typedef struct Game1FBB80Packet {
    u8 field00, field01;
    s16 field02, field04;
    u8 pad06[2];
    s32 field08, field0C;
    u8 field10, field11, field12, field13;
    f32 field14, field18;
    f32 x, y, z;
    f32 field28, field2C, field30, field34, field38, field3C;
    u32 flags40;
    u8 field44, field45, field46, field47;
    Game1FBB80Owner *owner;
    u8 pad4C[0xC]; /* func_1513D2F0 copies the complete 0x58-byte packet. */
} Game1FBB80Packet;

s32 func_1504530C(void *, f32, void *);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
s32 func_1513D2F0(void *, void *, u8, u8, u8, u8, u8, s32, s32, s32, u8, s32);
void func_151432BC(void *, f32 *, f32 *, f32 *, f32 *);
extern s32 D_80082FA0;
extern u8 D_800A4AA0[];
extern f32 D_800AAFF0, D_800AAFF4, D_800AAFF8, D_800AAFFC;
extern f32 D_800AB000, D_800AB004, D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151CE6D0 CURRENT (3460) */
void func_151CE6D0(Game1FBB80Object *arg0) {
    Game1FBB80Packet packet;
    f32 upperHeight;
    f32 offset, range, scale;
    s16 mask;
    s32 index;
    Game1FBB80Effect *effect;

    effect = &arg0->effect;
    effect->accumulator += (D_800AAFF0 + func_150ADA68() * D_800AAFF4) * D_800AAFF8 * D_800BE9A4 * effect->rate;
    if (effect->accumulator > 1.0f) {
        index = 0;
        mask = 0;
        if (D_80082FA0 >= 0) {
            do {
                mask |= 1U << (index & 31);
                index++;
            } while (D_80082FA0 >= index);
        }
        if (!(effect->owner->mask & mask)) {
            do {
                effect->accumulator -= 1.0f;
            } while (effect->accumulator > 1.0f);
            return;
        }
        offset = D_800AAFFC;
        packet.field00 = 0x6A;
        packet.field01 = 0;
        packet.field02 = 0x2203;
        packet.field04 = 0x64;
        packet.field08 = 0;
        packet.field0C = 0;
        packet.field10 = 0xFF;
        packet.field11 = 0xFF;
        packet.field12 = 0xFF;
        packet.field13 = 0xFF;
        packet.field2C = 0.0f;
        packet.field30 = 0.0f;
        packet.field38 = 0.0f;
        packet.field3C = 1.0f;
        packet.flags40 = 0x01CC0061;
        packet.field45 = 0xFF;
        packet.field46 = 0;
        packet.field47 = 7;
        range = D_800AB000;
        scale = D_800AB004;
        packet.owner = effect->owner;
        do {
            packet.field28 = (func_150ADA68() * range + offset) * scale;
            packet.field34 = (func_150ADA68() * 121.0f + 23.0f) * scale;
            packet.field14 = func_150ADA68() * 25.0f + 10.0f;
            packet.field18 = func_150ADA68() * 60.0f + 60.0f;
            func_151432BC(effect->shape, &packet.x, &packet.z, &upperHeight, &packet.y);
            if (func_1504530C(&packet.x, upperHeight, (u8 *)effect + 0x10) != 0) {
                packet.y = effect->height;
                packet.field44 = func_150ADA20() % 101U + 0x9B;
                func_1513D2F0(&packet, D_800A4AA0, 0x1C, 0, 0, 0x22, 0, 0, 0, 0, arg0->flags0C, arg0->flags01);
            }
            effect->accumulator -= 1.0f;
        } while (effect->accumulator > 1.0f);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151CE6D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1FBB80/func_151CE6D0.s")
