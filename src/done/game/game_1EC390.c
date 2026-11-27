#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1EC390.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_structural_families_continued.md
 */

typedef struct Game1EC390Selector {
    u8 values[3];
} Game1EC390Selector;

typedef struct Game1EC390Position {
    s32 values[3];
} Game1EC390Position;

typedef struct Game1EC390Spawn {
    f32 scale0;
    f32 scale4;
    f32 scale8;
    f32 scaleC;
    f32 zero10;
    f32 amount;
    f32 zero18;
    f32 scale1C;
    f32 scale20;
    f32 scale24;
    Game1EC390Position position;
    f32 zeros[7];
    s32 flags;
    s16 lifetime;
    s16 kind;
    u8 selector;
    u8 pad59[3];
    s32 owner;
    u8 alpha;
    u8 state;
    u8 zero62;
    u8 zero63;
    u8 zero64;
    u8 zero65;
    u8 zero66;
    u8 zero67;
    u8 mode;
    u8 pad69;
    u8 zero6A;
    u8 pad6B;
    s32 zero6C;
    u8 zero70;
    u8 pad71;
    s16 one72;
    s16 maximum;
} Game1EC390Spawn;

void *func_15132A4C(void *, s32, s32, s32, u8, s32);
extern Game1EC390Selector D_8008FBC0;
extern f32 D_800AA8E4;
extern s32 D_800BE9F0;

void *func_151BEEE0(f32 arg0, Game1EC390Position *arg1, s32 arg2,
                   u8 arg3, u8 arg4, u8 arg5, s32 arg6,
                   u8 arg7, s32 arg8) {
    f32 scale;
    Game1EC390Selector selectors;
    u8 *object;
    Game1EC390Spawn spawn;

    selectors = D_8008FBC0;
    if (arg4 >= 3) {
        return 0;
    }
    scale = D_800AA8E4;
    {
        s32 flags;
        u8 *transform;
        s32 i;

        spawn.scale0 = 1.0f;
        spawn.scale4 = 1.0f;
        spawn.scaleC = scale;
        spawn.scale8 = scale;
        spawn.zero10 = 0.0f;
        spawn.amount = arg0;
        spawn.zero18 = 0.0f;
        spawn.scale1C = 1.0f;
        spawn.scale20 = 1.0f;
        spawn.scale24 = 1.0f;
        spawn.position = *arg1;
        spawn.zeros[0] = 0.0f;
        spawn.zeros[1] = 0.0f;
        spawn.zeros[2] = 0.0f;
        spawn.zeros[3] = 0.0f;
        spawn.zeros[4] = 0.0f;
        spawn.zeros[5] = 0.0f;
        spawn.zeros[6] = 0.0f;
        if (arg5 != 0) {
            flags = 0x4000;
        } else {
            flags = 0;
        }
        spawn.flags = flags | 0x1D00 | 0x80000 | 0x40000;
        spawn.lifetime = 0x12C;
        spawn.kind = 0x26;
        spawn.selector = selectors.values[arg4];
        spawn.owner = arg6;
        spawn.alpha = 0xFF;
        if (D_800BE9F0 == 7) {
            spawn.state = 0x18;
        } else {
            spawn.state = 0;
        }
        spawn.zero62 = 0;
        spawn.zero63 = 0;
        spawn.zero64 = 0;
        spawn.zero65 = 0;
        spawn.zero66 = 0;
        spawn.zero67 = 0;
        spawn.mode = 2;
        spawn.zero6A = 0;
        spawn.zero6C = 0;
        spawn.zero70 = 0;
        spawn.one72 = 1;
        spawn.maximum = 0xFF;
        object = func_15132A4C(&spawn, arg2, arg3, 0, arg7, arg8);
        if (object != 0) {
            for (i = 0; i < 2; i++) {
                transform = object + 0x90 + i * 0x40;
                func_15133760((s32)transform, object);
            }
        }
    }
    return object;
}
typedef struct {
    s32 countBase, countRange;
    Game1EC390Position position;
    f32 speedBase, speedRange;
    s16 angleBase, angleRange, pitchBase, pitchRange;
    f32 directionBase, directionRange, jitter;
    f32 sizeBase, sizeRange, scale;
    u8 kind, pad3D;
    s16 lifeBase, lifeRange;
} Game150F90Config;
typedef struct {
    s16 countBase, countRange;
    u8 kind, pad5;
    u16 texture;
    s32 flags, zeroC;
    s16 field10, field12;
    s32 zero14, zero18;
    u8 field1C, field1D, field1E, field1F, field20;
    u8 field21, field22, field23, field24, field25;
    s16 field26, field28, field2A;
    f32 field2C, field30, field34;
    Game1EC390Position position;
    s16 angleBase, angleRange, pitchBase, pitchRange;
    f32 field4C, field50, field54, field58;
    s32 field5C;
    u8 field60;
    s8 field61;
    u8 field62, field63, field64;
    u8 pad65[3];
    f32 field68;
} GameBF0C8Burst;
void func_15150F90(Game150F90Config *, u8, u8, s32);
void func_15153634(GameBF0C8Burst *, u8, u8, s32);
extern f32 D_800AA8E8, D_800AA8EC, D_800AA8F0, D_800AA8F4;
extern f32 D_800AA8F8, D_800AA8FC, D_800AA900;
extern f32 D_800AA904, D_800AA908, D_800AA90C;

void func_151BF0C8(f32 *arg0) {
    Game150F90Config first;
    GameBF0C8Burst second;

    first.countBase = 24;
    first.countRange = 10;
    first.position = *(Game1EC390Position *)arg0;
    first.angleBase = 0;
    first.angleRange = 255;
    first.pitchBase = -50;
    first.pitchRange = 60;
    first.directionBase = 13.0f;
    first.directionRange = 13.0f;
    first.kind = 3;
    first.lifeBase = 65;
    first.lifeRange = 30;
    first.speedBase = D_800AA8E8;
    first.speedRange = D_800AA8EC;
    first.jitter = D_800AA8F0;
    first.sizeBase = D_800AA8F4;
    first.sizeRange = D_800AA8F8;
    first.scale = D_800AA8FC;
    func_15150F90(&first, 1, 255, 1);
    second.countBase = 20;
    second.countRange = 8;
    second.kind = 108;
    second.texture = 0x5103;
    second.flags = 0x200005;
    second.field10 = 40;
    second.field12 = 40;
    second.field1F = 255;
    second.field1C = 255;
    second.zeroC = 0;
    second.zero14 = 0;
    second.zero18 = 0;
    second.field1D = 145;
    second.field1E = 6;
    second.field20 = 255;
    second.field21 = 255;
    second.field22 = 0;
    second.field23 = 20;
    second.field24 = 200;
    second.field25 = 255;
    second.field26 = 50;
    second.field28 = 5;
    second.field2A = 50;
    second.field2C = D_800AA900;
    second.field30 = 175.0f;
    second.field34 = 160.0f;
    second.position = *(Game1EC390Position *)arg0;
    second.angleBase = 0;
    second.angleRange = -51;
    second.pitchBase = 255;
    second.pitchRange = 80;
    second.field5C = 0x840E07;
    second.field60 = 16;
    second.field61 = -1;
    second.field62 = 8;
    second.field63 = 6;
    second.field64 = 1;
    second.field4C = 4.0f;
    second.field50 = 13.0f;
    second.field54 = D_800AA904;
    second.field58 = D_800AA908;
    second.field68 = D_800AA90C;
    func_15153634(&second, 255, 255, 1);
}

typedef struct Game1EC390Animation {
    void *primary;
    void *secondary[2];
    f32 timer;
    f32 amount;
    u8 flags;
} Game1EC390Animation;

typedef struct Game1EC390AnimationOwner {
    u8 unk_0[0x28];
    Game1EC390Animation animation;
} Game1EC390AnimationOwner;

typedef struct Game1EC390Model {
    u8 flags;
    s8 mode;
    u8 type, extra, field04, unk_5;
    s16 id;
    s32 field08, field0C, field10, field14, field18;
    s32 field1C, field20, field24, field28;
    u8 field2C, field2D, unk_2E[2];
    u8 colors[8];
    u8 field38, unk_39[3];
    s32 field3C;
    u8 field40, field41, unk_42[2];
    Vec3f position;
    s32 field50;
    s16 field54, field56;
} Game1EC390Model;

typedef struct Game1EC390Sprite {
    f32 x, y, width, height;
    u8 kind, unk_11;
    s16 id, flags, field16, field18;
    u8 field1A, colors[9];
    s32 field24, field28, field2C, field30, field34, field38, field3C;
    u8 field40, field41, unk_42[2];
    u8 field44, unk_45[3];
    f32 field48, field4C, field50, field54;
} Game1EC390Sprite;

typedef struct Game1EC390Placement {
    Vec3f position;
    f32 scaleX;
    f32 scaleY;
} Game1EC390Placement;

typedef struct Game1EC390ModelObject {
    u8 unk_0[0x120];
    Game1EC390Placement placement;
} Game1EC390ModelObject;

s32 func_150859AC(s16, s16);
void func_100226F0(void *, s32);
void *func_10022EC0(void *, const void *, u32);
s32 func_15157010(s32, s32, f32, s32, s32, s32, s32, s32);
f32 func_15047D60(f32);

typedef struct Game1EC390Kinds {
    s32 values[10];
} Game1EC390Kinds;

extern Vec3f D_800A5480;
extern f32 D_800AA910;
extern Game1EC390Kinds D_800AA8B4;
extern u8 D_800D2458;

void func_151BF340(u8 arg0, s32 arg1) {
    Game1EC390Animation animation;
    s32 count;
    Game1EC390AnimationOwner *object;
    s32 digits[2];
    Game1EC390Animation *resources;

    func_151494E0(NULL, 0x57);
    count = func_150859AC(0, 3);
    if (count != 0) {
        count--;
    }
    if (count >= 100) {
        count = 99;
    }
    digits[0] = count / 10;
    digits[1] = count % 10;
    animation.primary = NULL;
    func_100226F0(animation.secondary, 8);
    animation.timer = 110.0f;
    animation.amount = func_15047D60(D_800AA910);
    animation.flags = 0;
    object = func_15149130(300, -1, 0x60, -1, 0, 0x49, 0x18, arg0, arg1);
    if (object == NULL) {
        return;
    }
    resources = &object->animation;
    func_10022EC0(resources, &animation, 0x18);
    {
        Game1EC390Model model;
        Game1EC390Placement placement;

        model.flags = 0xC0;
        model.mode = -1;
        model.type = 5;
        model.extra = 3;
        model.id = 300;
        model.field08 = 0xA3;
        model.field0C = 8;
        model.field10 = 0x100000;
        model.field18 = 0x60601;
        model.field2D = 8;
        model.field1C = 1;
        model.field20 = 0x38;
        model.field24 = 0x80;
        model.field38 = 0;
        model.field04 = 0;
        model.field14 = 0x200004;
        model.field2C = 0;
        model.field28 = 0x20;
        model.colors[0] = 0xFF;
        model.colors[1] = 0xFF;
        model.colors[2] = 0xFF;
        model.colors[3] = 0xFF;
        model.colors[4] = 0xFF;
        model.colors[5] = 0xFF;
        model.colors[6] = 0xFF;
        model.colors[7] = 0xFF;
        model.field3C = 0;
        model.field40 = 0;
        model.field41 = 1;
        model.field54 = 1;
        model.field56 = 0xFF;
        model.position.x = 300.0f;
        if (D_800D2458 != 0) {
            model.position.y = 32.0f;
        } else {
            model.position.y = 79.0f;
        }
        model.position.z = 0.0f;
        placement.position = D_800A5480;
        placement.scaleX = 0.30100003f;
        placement.scaleY = 0.30100003f;
        resources->primary = (void *)func_15157010((s32)&model, 0, 1, 0, 0, 0x14, arg0, arg1);
        if (resources->primary != NULL) {
            func_10022EC0(&((Game1EC390ModelObject *)resources->primary)->placement, &placement, 0x14);
        }
        {
            u8 i;
            Game1EC390Sprite sprite;
            Game1EC390Kinds kinds;

            kinds = D_800AA8B4;
            sprite.x = -500.0f;
            if (D_800D2458 != 0) {
                sprite.y = -15.0f;
            } else {
                sprite.y = -62.0f;
            }
            sprite.id = 300;
            sprite.flags = 0x20;
            sprite.field16 = 1;
            sprite.field18 = 0xFF;
            sprite.colors[0] = 0xFF;
            sprite.colors[1] = 0xFF;
            sprite.colors[2] = 0xFF;
            sprite.colors[3] = 0xFF;
            sprite.field1A = 0;
            sprite.colors[4] = 0xFF;
            sprite.colors[5] = 0xFF;
            sprite.colors[6] = 0xFF;
            sprite.colors[7] = 0xFF;
            sprite.colors[8] = 0xFF;
            sprite.field24 = 0;
            sprite.field28 = 0x200004;
            sprite.field2C = 0x9F0601;
            sprite.field40 = 0;
            sprite.field41 = 0;
            sprite.field30 = 0x19;
            sprite.field34 = 0x13;
            sprite.field38 = 0x80;
            sprite.field3C = 0x20;
            sprite.field44 = 0;
            sprite.field50 = 0.0f;
            sprite.field54 = 0.0f;
            sprite.height = 16.0f;
            sprite.width = 16.0f;
            sprite.field48 = 1.0f;
            sprite.field4C = 1.0f;
            if (digits[0] == 0) {
                sprite.kind = kinds.values[digits[1]];
                resources->secondary[0] = func_1515548C(&sprite, 0, 0, 0, 0, arg0, arg1);
                resources->secondary[1] = NULL;
                return;
            }
            for (i = 0; i < 2; i++) {
                sprite.kind = kinds.values[digits[i]];
                resources->secondary[i] = func_1515548C(&sprite, 0, 0, 0, 0, arg0, arg1);
            }
        }
    }
}

s32 func_1517EF00(s32);
s32 func_15181CC8(s32);
extern f32 D_800AA918, D_800AA91C, D_800AA920;
extern f32 D_800AA924, D_800AA928, D_800AA92C;
extern f32 D_800BE9A4;
extern u8 D_800BE9B4, D_800BEAC0, D_800BEAC1, D_800C35EA;

void func_151BF81C(void *arg0) {
    f32 amount;
    Game1EC390Animation *animation;

    if (D_800BEAC1 != 0 || (animation = (Game1EC390Animation *)((u8 *)arg0 + 0x28), D_800BEAC0 != 0)) {
        *(s16 *)((u8 *)arg0 + 0xE) = -1;
        *((u8 *)arg0 + 0xD) |= 1;
        return;
    }
    if (!(animation->flags & 1)) {
        if (D_800C35EA == 1) return;
        if (func_15181CC8(0) == 0) return;
        if (func_1517EF00(0) != 0 || D_800BE9B4 != 0) return;
        animation->flags |= 1;
    }
    if (animation->timer < D_800AA918) {
        amount = func_15047D60(animation->timer * D_800AA91C * D_800AA920);
    } else if (D_800AA924 < animation->timer) {
        amount = func_15047D60((110.0f - animation->timer) * D_800AA928 * D_800AA92C);
    } else {
        amount = animation->amount;
    }
    if (animation->primary != NULL) {
        *(f32 *)((u8 *)animation->primary + 0x54) = amount * -85.0f + 150.0f;
        if (D_800D2458 != 0) *(f32 *)((u8 *)animation->primary + 0x58) = 32.0f;
        else *(f32 *)((u8 *)animation->primary + 0x58) = 79.0f;
    }
    if (animation->secondary[0] != NULL) {
        *(f32 *)((u8 *)animation->secondary[0] + 0x10) = ((amount * -85.0f + 150.0f) / 1.0f + 48.0f) - 12.0f;
        if (D_800D2458 != 0) *(f32 *)((u8 *)animation->secondary[0] + 0x14) = -15.0f;
        else *(f32 *)((u8 *)animation->secondary[0] + 0x14) = -62.0f;
    }
    if (animation->secondary[1] != NULL) {
        *(f32 *)((u8 *)animation->secondary[1] + 0x10) = ((amount * -85.0f + 150.0f) / 1.0f + 48.0f) + 12.0f;
        if (D_800D2458 != 0) *(f32 *)((u8 *)animation->secondary[1] + 0x14) = -15.0f;
        else *(f32 *)((u8 *)animation->secondary[1] + 0x14) = -62.0f;
    }
    animation->timer -= D_800BE9A4;
    if (animation->timer < 0.0f) {
        *(s16 *)((u8 *)arg0 + 0xE) = -1;
        *((u8 *)arg0 + 0xD) |= 1;
    }
}

typedef struct Game1EC390Resources {
    void *primary;
    void *secondary[2];
} Game1EC390Resources;

typedef struct {
    u8 pad0[0x28];
    Game1EC390Resources resources;
} Game1EC390ResourceOwner;

void func_151BFB2C(Game1EC390ResourceOwner *arg0) {
    u8 i;
    Game1EC390Resources *resources = &arg0->resources;

    if (resources->primary != NULL) {
        func_1516972C(resources->primary);
    }
    for (i = 0; i < 2; i++) {
        if (resources->secondary[i] != NULL) {
            func_1516972C(resources->secondary[i]);
        }
    }
}

void func_151BFBA4(void *arg0) {
    func_151BFB2C(arg0);
    func_1514933C(arg0);
}
