#include "types.h"

/*
 * Reviewed source unit: src/game/game_114B80.c
 * Boundary evidence: docs/evidence/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E76D0
 * - func_150E7994
 * - func_150E7C9C
 * - func_150E7FEC
 * - func_150E81A8
 * - func_150E83AC
 * - func_150E8470
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game114B80Choices {
    s32 value[3];
} Game114B80Choices;

typedef struct Game114B80Rectangle {
    f32 x, y, width, height;
    s8 kind, pad11;
    s16 lifetime;
    u16 flags;
    s16 field16, field18;
    u8 field1A, field1B, field1C, field1D, field1E;
    u8 field1F, field20, field21, field22, field23;
    s32 field24, field28, field2C, field30;
    s32 field34, field38, field3C;
    u8 field40, field41, pad42[2], field44, pad45[3];
    f32 scaleX, scaleY, offsetX, offsetY;
} Game114B80Rectangle;

s32 func_150ADA20(void);
f32 func_150ADA68(void);
void *func_1515548C(Game114B80Rectangle *, s32, s32, s32, s32, s32, s32);
extern Game114B80Choices D_80088A68, D_80088A74;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E76D0 CURRENT (1082) */
void func_150E76D0(f32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10) {
    s32 random;
    Game114B80Rectangle rectangle;
    u8 selector;
    Game114B80Choices horizontal;
    Game114B80Choices vertical;

    random = func_150ADA20();
    rectangle.lifetime = *((s16 *) &arg1 + 1);
    rectangle.field18 = *((s16 *) &arg6 + 1);
    selector = random & 3;
    rectangle.flags = *((u8 *) &arg2 + 3) & 0xFFF9;
    rectangle.field1A = 5;
    rectangle.field1B = 255;
    rectangle.field1C = 230;
    rectangle.field1D = 190;
    rectangle.field1F = 255;
    rectangle.field16 = *((s16 *) &arg5 + 1);
    rectangle.field1E = *((u8 *) &arg3 + 3);
    rectangle.field20 = 255;
    rectangle.field21 = 255;
    rectangle.field22 = 255;
    rectangle.field24 = 1;
    rectangle.field28 = 0;
    rectangle.field2C = 0;
    rectangle.field40 = 0;
    rectangle.field41 = 10;
    rectangle.field30 = 7;
    rectangle.field34 = 60;
    rectangle.field38 = 128;
    rectangle.field3C = 32;
    rectangle.height = arg0;
    rectangle.width = arg0;
    rectangle.field23 = *((u8 *) &arg4 + 3);
    /* The sole raw caller supplies flags 9; optional scale/offset fields are inactive. */
    switch (selector) {
    case 0:
    case 1:
        horizontal = D_80088A68;
        rectangle.kind = horizontal.value[(u32) func_150ADA20() % 3U];
        rectangle.y = func_150ADA68() * 160.0f + -80.0f;
        switch (selector) {
        case 0:
            rectangle.flags |= 2;
            rectangle.x = 145.0f - arg0;
            break;
        case 1:
            rectangle.x = arg0 - 145.0f;
            break;
        }
        break;
    case 2:
    case 3:
        vertical = D_80088A74;
        rectangle.kind = vertical.value[(u32) func_150ADA20() % 3U];
        rectangle.x = func_150ADA68() * 260.0f + -130.0f;
        switch (selector) {
        case 2:
            rectangle.flags |= 4;
            rectangle.y = 110.0f - arg0;
            break;
        case 3:
            rectangle.y = arg0 - 110.0f;
            break;
        }
        break;
    }
    func_1515548C(&rectangle, 0, arg7, arg8, 0, *((u8 *) &arg9 + 3), arg10);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E76D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_114B80/func_150E76D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_114B80/func_150E7994.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_114B80/func_150E7C9C.s")
typedef struct GameE7FECLocals {
    s32 command;
    s16 lifetime;
    s8 type;
    s8 zero;
    s32 clear0;
    s32 clear1;
    u8 color[6];
    u8 zero2;
    u8 six;
    s32 style;
    u8 pad78[6];
    s16 size;
    s16 count;
} GameE7FECLocals;

void *func_1513C650(s32, u8, u8, s32, f32, f32, f32, f32,
                     f32, u8, u8, s32, s32, s32, u8, s32);
s32 func_150ADA20();

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E7FEC CURRENT (2172) */
void func_150E7FEC(f32 arg0, u8 arg1, s32 arg2, f32 *arg3,
                   s16 arg4, u8 arg5, u8 arg6, u8 arg7,
                   u8 arg8, u8 arg9, u8 arg10, s32 arg11) {
    GameE7FECLocals local;
    s32 random0;
    s32 random1;
    s32 control0;
    s32 control1;
    s32 enabled;
    s32 mode;

    local.size = 0x14;
    local.count = 0xC;
    local.type = 0x4F;
    local.zero = 0;
    enabled = arg4 == -1 ? 0 : 1;
    mode = 0;
    if (arg5 != 0) {
        mode = 0x400;
    }
    local.command = mode | enabled | 0x9300 | 0x40000;
    if (arg4 == -1) {
        local.lifetime = 0x12C;
    } else {
        local.lifetime = arg4 + 0x14;
    }
    local.clear0 = 0;
    local.clear1 = 0;
    local.color[1] = 0xFF;
    local.color[5] = 0xFF;
    local.color[0] = arg1;
    local.color[2] = arg7;
    local.color[3] = arg8;
    local.color[4] = arg9;
    local.style = (arg6 != 0 ? 2 : 1) + 0x480000;
    local.zero2 = 0;
    local.six = 6;
    if (arg5 != 0) {
        control1 = 3;
        control0 = 0xFF;
    } else {
        control1 = 0;
        control0 = 0;
    }
    random0 = func_150ADA20(arg4, arg5);
    random1 = func_150ADA20();
    mode = func_150ADA20();
    func_1513C650((s32)&local.command, 0, 0, arg2,
                   arg3[0], arg3[1], arg3[2], arg0, arg0,
                   (u8)random0,
                   (u8)(((mode & 1) * 2) + (random1 & 1)),
                   control1, control0, 0, arg10, arg11);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E7FEC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_114B80/func_150E7FEC.s")
typedef struct GameE81A8Position {
    f32 x, y, z;
} GameE81A8Position;

typedef struct GameE81A8Effect {
    s16 field00, field02, field04, field06;
    s32 field08, field0C;
    GameE81A8Position position;
    f32 field1C, field20, field24, field28, field2C, field30;
    s32 field34, field38;
    f32 field3C, field40, field44, field48;
    s16 field4C, field4E, field50, field52, field54, field56;
    s8 field58;
} GameE81A8Effect;

typedef struct GameE81A8Event {
    s8 field0;
    s16 field2;
    s8 field4, field5, field6;
} GameE81A8Event;

void func_1514FCE8(s16 *, s32, s32);
void func_151D3FF4(s32, u8, s32);
void *func_151D8868(s8 *, s32, s32, s32);
extern GameE81A8Position D_800A1290[];
extern f32 D_800A1354, D_800A1358, D_800A135C, D_800A1360, D_800A1364;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E81A8 CURRENT (1696) */
void func_150E81A8(s32 arg0, s32 arg1, s32 arg2) {
    GameE81A8Position position;
    GameE81A8Effect effect;
    GameE81A8Event event;
    s32 selector;

    selector = arg0 & 0xFF;
    if (selector == 4 || selector == 5 || selector == 6 || selector == 7) {
        position = D_800A1290[selector];
        position.y += 200.0f;
        func_151D3FF4((s32)&position, (u8)arg1, arg2);
        effect.field00 = 0;
        effect.field02 = 0xFF;
        effect.field04 = -0x40;
        effect.field06 = 0x4D;
        effect.field08 = 0xA;
        effect.field0C = 5;
        effect.position = position;
        effect.field1C = 252.0f;
        effect.field20 = 117.0f;
        effect.field24 = 308.0f;
        effect.field28 = 256.0f;
        effect.field34 = 4;
        effect.field38 = 7;
        effect.field4C = 0x19;
        effect.field4E = 0xF;
        effect.field50 = 0x64;
        effect.field52 = 0x64;
        effect.field54 = 0xC;
        effect.field56 = 0x14;
        effect.field58 = 0;
        effect.field2C = D_800A1354;
        effect.field30 = D_800A1358;
        effect.field3C = 27.0f;
        effect.field40 = D_800A135C;
        effect.field44 = D_800A1360;
        effect.field48 = D_800A1364;
        func_1514FCE8(&effect.field00, (u8)arg1, arg2);
        event.field0 = 1;
        event.field2 = ((u32)func_150ADA20() % 11U) + 0x1E;
        event.field4 = 8;
        event.field6 = -1;
        event.field5 = 1;
        func_151D8868(&event.field0, 0, 0xFF, 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E81A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_114B80/func_150E81A8.s")
void func_10022EC0(void *, void *, s32);
u8 *func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E83AC CURRENT (1230) */
void func_150E83AC(void *arg0, s16 arg1, u8 arg2, s32 arg3) {
    typedef struct { s32 words[3]; } Copy3;
    struct {
        Copy3 header;
        f32 value;
    } packet;
    s32 var_v1;
    s32 var_v0;
    u8 *temp_v0;

    packet.header = *(Copy3 *)arg0;
    var_v1 = arg1;
    packet.value = 0.0f;
    if (arg1 == -1) {
        var_v1 = 0x12C;
    }
    if (arg1 == -1) {
        var_v0 = 0;
    } else {
        var_v0 = 1;
    }
    temp_v0 = func_15149130((s32)var_v1, -1, 0x28, -1, var_v0, 0, 0x10,
        (s32)arg2, arg3);
    if (temp_v0 != 0) {
        func_10022EC0(temp_v0 + 0x28, &packet, 0x10);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E83AC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_114B80/func_150E83AC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_114B80/func_150E8470.s")
void func_15131828(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_150E8824(s32 arg0, s32 arg1) {
    func_15131828(arg0, arg0 + 0xAC, arg0 + 0xA8, arg0 + 0xAA);
    return 1;
}

void func_10022EC0(void *, void *, s32);
u8 *func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_150E8854(void) {
    u8 *object;
    f32 value;

    value = 10.0f;
    object = func_15149130(0x12C, -1, 0x35, -1, 0, 0, 4, 0xFF, 1);
    if (object != 0) {
        func_10022EC0(object + 0x28, &value, 4);
    }
}
