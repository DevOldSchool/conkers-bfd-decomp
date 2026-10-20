#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1B7870.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_preserved_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1518A5F4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    u8 kind;
    u8 enabled;
    u8 field2;
    u8 field3;
    s16 life;
    u8 image;
    u8 pad7;
    s32 field8;
    u32 fieldC;
    u32 field10;
    s32 field14;
    s32 field18;
    s32 field1C;
    s32 field20;
    u8 field24;
    u8 field25;
    u8 pad26[2];
    u8 color0;
    u8 color1;
    u8 color2;
    u8 color3;
    u8 color4;
    u8 color5;
    u8 color6;
    u8 color7;
    s32 field30;
    u8 field34;
    u8 field35;
    u8 pad36[2];
    Vec3f position;
} Game1B7870Descriptor;

typedef struct {
    Vec3f first;
    f32 scale;
    Vec3f second;
    Vec3f third;
    f32 field28;
    f32 field2C;
} Game1B7870Payload;

typedef struct {
    s16 kind;
    u8 pad2[2];
    s32 flags;
} Game1B7870Header;

void *func_151580B0(void *, s32, s32, u8, s32, u8, s32);
void *func_10022EC0(void *, const void *, u32);
extern s32 D_8008D5B0[];
extern s32 D_8008D5B8[];

void *func_1518A3C0(Vec3f *arg0, Vec3f *arg1,
                       f32 arg2, Vec3f *arg3, Vec3f *arg4,
                       f32 arg5, f32 arg6, u8 arg7, s16 arg8, u8 arg9,
                       s32 arg10, u8 arg11, s32 arg12) {
    u8 *result;
    Game1B7870Descriptor descriptor;
    Game1B7870Payload payload;
    Game1B7870Header header;

    payload.first = *arg1;
    payload.second = *arg3;
    payload.third = *arg4;
    payload.scale = arg2;
    payload.field28 = arg5;
    payload.field2C = arg6;
    descriptor.kind = (u8)arg7;
    descriptor.field2 = 1;
    descriptor.field3 = 1;
    descriptor.life = (s16)arg8;
    if ((u8)arg9 != 0) {
        descriptor.image = D_8008D5B8[func_150ADA20() & 1];
    } else {
        descriptor.image = D_8008D5B0[func_150ADA20() & 1];
    }
    descriptor.fieldC = 0x220205;
    descriptor.field10 = 0x40600;
    descriptor.field25 = 7;
    descriptor.field14 = 1;
    descriptor.field18 = 0x4A;
    descriptor.field1C = 0x80;
    descriptor.field20 = 0x20;
    descriptor.field8 = 0;
    descriptor.field24 = 0;
    descriptor.enabled = 1;
    descriptor.color0 = 0xFF;
    descriptor.color1 = 0xFF;
    descriptor.color2 = 0xFF;
    descriptor.color3 = 0xFF;
    descriptor.color4 = 0xFF;
    descriptor.color5 = 0xFF;
    descriptor.color6 = 0xFF;
    descriptor.color7 = 0xFF;
    descriptor.field30 = 0;
    descriptor.field34 = 0;
    descriptor.field35 = 2;
    descriptor.position = *arg0;
    header.kind = 0xC;
    header.flags = 0x15;
    result = func_151580B0(&descriptor, 3, 0xFF, 1, arg10 + 0x38,
                          (u8)arg11, arg12);
    if (result == 0) {
        return 0;
    }
    func_10022EC0(result + 0xF8, &header, 8);
    func_10022EC0(result + 0x100, &payload, 0x30);
    return result;
}
typedef struct {
    u8 pad0[0x48];
    Vec3f position;
    u8 pad54[0xAC];
    Game1B7870Payload payload;
} Game1B7870Object;

s32 func_15158AFC(void *);
extern f32 D_800BE9A4;
extern f32 D_800BE9A8;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1518A5F4 CURRENT (1505) */
s32 func_1518A5F4(Game1B7870Object *arg0) {
    f32 changeX;
    Vec3f previous;
    f32 changeY;
    f32 changeZ;
    register Game1B7870Payload *payload;
    s32 count;

    func_15158AFC(arg0);
    payload = (Game1B7870Payload *)((u32)arg0 + 0x100);
    previous = payload->second;
    payload->second.y += payload->field28 * D_800BE9A4;
    for (count = D_800BE9E4; count != 0; count--) {
        payload->second.x *= payload->field2C;
        payload->second.y *= payload->field2C;
        payload->second.z *= payload->field2C;
    }
    changeX = (payload->second.x - previous.x) * D_800BE9A8;
    changeY = (payload->second.y - previous.y) * D_800BE9A8;
    changeZ = (payload->second.z - previous.z) * D_800BE9A8;
    arg0->position.x += (previous.x + 0.5f * changeX * D_800BE9A4) * D_800BE9A4;
    arg0->position.y += (previous.y + 0.5f * changeY * D_800BE9A4) * D_800BE9A4;
    arg0->position.z += (previous.z + 0.5f * changeZ * D_800BE9A4) * D_800BE9A4;
    payload->first.x += payload->third.x * D_800BE9A4;
    payload->first.y += payload->third.y * D_800BE9A4;
    payload->first.z += payload->third.z * D_800BE9A4;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1518A5F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B7870/func_1518A5F4.s")
void func_150A7790(void *, s32);
void func_150A8050(f32 *, f32, f32, f32);

s32 func_1518A914(s32 arg0, u8 *arg1) {
    f32 *rotation;
    f32 matrix[4][4];

    rotation = (f32 *)(arg1 + 0x100);
    func_150A8050((f32 *)matrix, rotation[0], rotation[1], rotation[2]);
    matrix[3][0] = *(f32 *)(arg1 + 0x48);
    matrix[3][1] = *(f32 *)(arg1 + 0x4C);
    matrix[3][2] = *(f32 *)(arg1 + 0x50);
    matrix[0][0] *= rotation[3];
    matrix[0][1] *= rotation[3];
    matrix[0][2] *= rotation[3];
    matrix[1][0] *= rotation[3];
    matrix[1][1] *= rotation[3];
    matrix[1][2] *= rotation[3];
    matrix[2][0] *= rotation[3];
    matrix[2][1] *= rotation[3];
    matrix[2][2] *= rotation[3];
    func_150A7790(matrix, arg0);
    return 1;
}
