#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_114740.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_direct_helper_pairs.md
 */

typedef struct Game114740Pair { s32 words[2]; } Game114740Pair;
typedef struct Game114740Event {
    s8 type;
    u8 pad1;
    s16 duration;
    s8 field4, field5, field6;
    u8 pad7;
} Game114740Event;

f32 func_150ADA68(void);
void func_10010F30(s32, s32, s32, s32, s32);
void func_150E75A0(void *, f32, s16, u8, u8, u8, s16, s16, s32, s32, u8, s32);
void func_150E76D0(f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void *func_15164F0C(u8, u8, void *, u8, s32);
void *func_151D8868(void *, s32, u8, s32);
extern Game114740Pair D_80088A5C;
extern f32 D_800A1340, D_800A1344, D_800A1348, D_800A134C;

void func_150E7290(s32 arg0, s32 arg1, s32 arg2) {
    Game114740Pair pair;
    f32 position[2];
    Game114740Event event;
    s32 choice;
    s32 flags4;
    s32 flags2;
    u32 random;
    f32 scale;

    if (func_150ADA68() < D_800A1340) {
        pair = D_80088A5C;
        if (func_150ADA68() < D_800A1344) {
            position[0] = func_150ADA68() * 300.0f + -150.0f;
            position[1] = func_150ADA68() * 200.0f + -100.0f;
            scale = func_150ADA68();
            random = func_150ADA20();
            choice = func_150ADA20() & 1;
            if (choice) flags2 = 2;
            else flags2 = 0;
            if (func_150ADA20() & 1) flags4 = 4;
            else flags4 = 0;
            func_150E75A0(position, (scale * 150.0f + 200.0f) * D_800A1348,
                (s16)(random % 201U + 0x1F4), (u8)(flags4 | flags2) | 9,
                (func_150ADA20() % 26U + 0x64), 0xFF, 0x40, 3,
                (s32)&pair, 2, *((u8 *)&arg1 + 3), arg2);
        } else {
            scale = func_150ADA68();
            flags4 = func_150ADA20();
            func_150E76D0((scale * 100.0f + 150.0f) * D_800A134C,
                (s16)(flags4 % 201U + 0x1F4), 9,
                (u8)(func_150ADA20() % 26U + 0x64), 0xFF, 0x40, 3,
                (s32)&pair, 2, *((u8 *)&arg1 + 3), arg2);
        }
        func_10010F30(0x360, 0x7FFF, 0, 0, 0);
        func_15164F0C(1, *((u8 *)&arg0 + 3), 0, *((u8 *)&arg1 + 3), arg2);
        event.type = 1;
        event.duration = func_150ADA20() % 26U + 0x19;
        event.field5 = 1;
        event.field4 = func_150ADA20() % 6U + 3;
        event.field6 = -1;
        func_151D8868(&event, 0, 0xFF, 0);
    }
}
typedef struct {
    u8 sp28;
    u8 pad29[3];
    s32 source[2];
    f32 sp34;
    f32 sp38;
    u8 sp3C;
    u8 pad3D;
    s16 sp3E;
    s16 sp40;
    s16 sp42;
    s16 sp44;
    u8 sp46;
    u8 sp47;
    u8 sp48;
    u8 sp49;
    u8 sp4A;
    u8 sp4B;
    u8 sp4C;
    u8 sp4D;
    u8 sp4E;
    u8 sp4F;
    s32 sp50;
    s32 sp54;
    s32 sp58;
    s32 sp5C;
    s32 sp60;
    s32 sp64;
    s32 sp68;
    u8 sp6C;
    u8 sp6D;
    u8 pad6E[0x1A];
} Game114740Local;


typedef struct Game114740Position {
    f32 x, y;
} Game114740Position;

typedef struct Game114740Rectangle {
    Game114740Position position;
    f32 width, height;
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
} Game114740Rectangle;

typedef struct Game114740Kinds {
    u8 value[1];
} Game114740Kinds;
extern Game114740Kinds D_80088A64;

void func_150E75A0(void *arg0, f32 arg1, s16 arg2, u8 arg3, u8 arg4,
                   u8 arg5, s16 arg6, s16 arg7, s32 arg8, s32 arg9,
                   u8 arg10, s32 arg11) {
    Game114740Position *position;
    Game114740Rectangle rectangle;
    Game114740Kinds kinds;

    kinds = D_80088A64;
    position = arg0;
    rectangle.position = *position;
    rectangle.width = arg1;
    rectangle.height = arg1;
    rectangle.kind = kinds.value[0];
    rectangle.lifetime = arg2;
    rectangle.flags = arg3 | 0x40;
    rectangle.field16 = arg6;
    rectangle.field18 = arg7;
    rectangle.field1A = 4;
    rectangle.field1B = 0xFF;
    rectangle.field1C = 0xE6;
    rectangle.field1D = 0xBE;
    rectangle.field1E = arg4;
    rectangle.field1F = 0xFF;
    rectangle.field20 = 0xFF;
    rectangle.field21 = 0xFF;
    rectangle.field22 = 0xFF;
    rectangle.field23 = arg5;
    rectangle.field24 = 1;
    rectangle.field28 = 0;
    rectangle.field2C = 0;
    rectangle.field40 = 0;
    rectangle.field41 = 0xA;
    rectangle.field30 = 7;
    rectangle.field34 = 0x3C;
    rectangle.field38 = 0x80;
    rectangle.field3C = 0x20;
    func_1515548C(&rectangle, 0, arg8, arg9, 0, arg10, arg11);
}
