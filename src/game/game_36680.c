#include "types.h"

/*
 * Reviewed source unit: src/game/game_36680.c
 * Boundary evidence: docs/evidence/game_early_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150091D0
 * - func_15009334
 * - func_1500AC14
 * - func_1500AD84
 * - func_1500AF08
 * - func_1500B1F4
 * - func_1500B3B0
 * - func_1500B714
 * - func_1500B8F4
 * - func_1500BAB8
 * - func_1500BC7C
 * - func_1500BEC0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_100226F0(void *, s32);
void func_1515D4D4(s32, s32, s32, s32);

extern u8 D_800DCD24[3];
extern u8 D_800DCD28[3];
extern u8 D_800DCD30;
extern u8 D_800DCD31;
extern u8 D_800DCD32;
extern u8 D_800DCD33;
extern u8 D_800DCD34;
extern u8 D_800DCD35;
extern u8 D_800DCD36;
extern u8 D_800DCD37;
extern u8 D_800DCD38;
extern u8 D_800DCD39;
extern u8 D_800DCD3A;
extern u8 D_800DCD3B;
extern u8 D_800DCD3C;
extern u8 D_800DCD3D;
extern u8 D_800DCD40[0x38];
extern void *D_800DCD78;
extern s32 D_800DCD7C;
extern s32 D_800DCD80;
extern s32 D_800DCD84;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150091D0 CURRENT (900) */
void func_150091D0(void) {
    D_800DCD78 = 0;
    D_800DCD7C = 1;
    D_800DCD80 = 0;
    D_800DCD84 = 0;
    func_1515D4D4(0xFF, 0xFFU, 0xFFU, 0);
    D_800DCD24[0] = 0;
    D_800DCD24[1] = 0;
    D_800DCD24[2] = 0;
    D_800DCD28[0] = 0xFF;
    D_800DCD28[1] = 0xFF;
    D_800DCD28[2] = 0xFF;
    D_800DCD30 = 0x7F;
    D_800DCD31 = 0;
    D_800DCD32 = 0;
    D_800DCD33 = 0x7F;
    D_800DCD34 = 0;
    D_800DCD35 = 0;
    D_800DCD36 = 0x7F;
    D_800DCD37 = 0;
    D_800DCD38 = 0;
    D_800DCD39 = 0x7F;
    D_800DCD3A = 0;
    D_800DCD3B = 0;
    D_800DCD3C = 0;
    D_800DCD3D = 0;
    func_100226F0(D_800DCD40, sizeof(D_800DCD40));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150091D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_150091D0.s")
void func_15009334(u32);
extern u32 D_800D3094;

void func_150092DC(void) {
    u32 var_s0;

    var_s0 = 0;
    if (D_800D3094 != 0) {
        do {
            func_15009334(var_s0);
            var_s0 += 1;
        } while (var_s0 < D_800D3094);
    }
}
typedef struct Game36680Point {
    s16 position[3];
    u8 pad6[0xF];
    u8 type;
    u8 flags;
    u8 pad17;
    u32 color;
    u32 settings;
    u32 action;
    u8 pad24[0x10];
} Game36680Point;

typedef struct Game36680PointLink {
    struct Game36680PointLink *next;
    Game36680Point *point;
} Game36680PointLink;

extern Game36680Point *D_800D3098;
void *func_10003C40(s32, s32, s32, s32);
void *func_1515D5AC(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_1500AB5C(s32);
void func_1500A94C(s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15009334 CURRENT (3161) */
void func_15009334(u32 index) {
    s32 type;
    s32 bgr[3];
    s32 strength;
    s32 enabled;
    s32 callback;
    s32 duration;
    void *light;
    Game36680PointLink *link;
    Game36680Point *point;
    u32 packed;
    u32 settings;
    u32 action;
    u32 offset;

    offset = index * sizeof(Game36680Point);
    point = (Game36680Point *)((u8 *)D_800D3098 + offset);
    type = point->type >> 2;
    switch (type) {
    case 9:
    case 10:
    case 16:
        packed = point->color;
        bgr[2] = packed & 0xFF;
        bgr[1] = (packed >> 8) & 0xFF;
        bgr[0] = (packed >> 16) & 0xFF;
        point->flags |= 4;
        switch (type) {
        case 10:
            func_1515D4D4(bgr[2], bgr[1], bgr[0], 0);
            action = ((Game36680Point *)((u8 *)D_800D3098 + offset))->action;
            if (action != 0) {
                func_1500AB5C(action);
            }
            break;
        case 9:
            point = (Game36680Point *)((u8 *)D_800D3098 + offset);
            settings = point->settings;
            packed = point->color;
            action = point->action;
            settings = (settings >> 8) & 0xFF;
            strength = packed >> 24;
            strength &= 0x7F;
            enabled = packed >> 31;
            enabled &= 1;
            callback = action & 0xFFFF;
            duration = action >> 16;
            duration &= 0xFFFF;
            light = func_1515D5AC(point->position[0], point->position[1], point->position[2], settings, bgr[2], bgr[1], bgr[0],
                                 strength, enabled, duration);
            if (light != 0 && callback != 0) {
                func_1500A94C((s32)light, callback);
            }
            break;
        case 16:
            D_800DCD24[0] = bgr[2];
            D_800DCD24[1] = bgr[1];
            D_800DCD24[2] = bgr[0];
            point = (Game36680Point *)((u8 *)D_800D3098 + offset);
            D_800DCD28[0] = point->settings;
            D_800DCD28[1] = point->settings >> 8;
            D_800DCD28[2] = point->settings >> 16;
            D_800DCD3C = point->settings >> 24;
            D_800DCD3D = point->color >> 24;
            break;
        }
        break;
    case 15:
        link = func_10003C40(sizeof(Game36680PointLink), 1, 0, 0);
        link->point = (Game36680Point *)(offset + (u8 *)D_800D3098);
        link->next = (Game36680PointLink *)D_800DCD80;
        D_800DCD80 = (s32)link;
        break;
    case 24:
        link = func_10003C40(sizeof(Game36680PointLink), 1, 0, 0);
        link->point = (Game36680Point *)(offset + (u8 *)D_800D3098);
        link->next = (Game36680PointLink *)D_800DCD84;
        D_800DCD84 = (s32)link;
        break;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15009334 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_15009334.s")
void func_1516127C(s32 arg0, s32 arg1, s32 arg2);

void func_150095D8(s32 arg0, u8 arg1) {
    func_1516127C(arg0, 0xFF, 1);
}
void func_15161334(s32 arg0, s32 arg1, s32 arg2);

void func_15009600(s32 arg0, u8 arg1) {
    func_15161334(arg0, 0xFF, 1);
}
typedef struct {
    s8 field_0;
    s8 field_1;
    s16 field_2;
    u8 field_4;
} Game36680LightDescriptor;

typedef struct {
    u8 bytes[4];
} Game36680PackedLightIndices;

void *func_1516037C(Game36680LightDescriptor *, s32, void *, u8, s32);
extern Game36680PackedLightIndices D_80082BE0;

void func_15009628(s32 arg0, s32 arg1) {
    Game36680LightDescriptor descriptor;
    Game36680PackedLightIndices packed = D_80082BE0;

    descriptor.field_0 = 0;
    descriptor.field_1 = -1;
    descriptor.field_2 = 0x12C;
    descriptor.field_4 = packed.bytes[arg1 - 3];
    func_1516037C(&descriptor, arg0, 0, 0xFF, 1);
}
void func_15161408(s32 arg0, s32 arg1, s32 arg2);

void func_1500969C(s32 arg0, u8 arg1) {
    func_15161408(arg0, 0xFF, 1);
}
typedef struct {
    u8 bytes[5];
} Game36680PackedLightIndices5;

extern Game36680PackedLightIndices5 D_80082BE4;

void func_150096C4(s32 arg0, s32 arg1) {
    Game36680LightDescriptor descriptor;
    Game36680PackedLightIndices5 packed = D_80082BE4;

    descriptor.field_0 = 0;
    descriptor.field_1 = -1;
    descriptor.field_2 = 0x12C;
    descriptor.field_4 = packed.bytes[arg1 - 8];
    func_1516037C(&descriptor, arg0, 0, 0xFF, 1);
}

void func_15161494(s32 arg0, s32 arg1, s32 arg2);

void func_15009740(s32 arg0, u8 arg1) {
    func_15161494(arg0, 0xFF, 1);
}
s32 func_151615F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

void func_15009768(s32 arg0, u8 arg1) {
    func_151615F8(arg0, 0, 0, 0xE, 0xFF, 1);
}
void func_15161540(s32 arg0, s32 arg1, s32 arg2);

void func_150097A4(s32 arg0, u8 arg1) {
    func_15161540(arg0, 0xFF, 1);
}
void func_150121C0(s32 arg0);

void func_150097CC(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_151615F8(arg0, 0, 2, 0xE, 0xFF, 1);
    if (temp_v0 != 0) {
        func_150121C0(temp_v0);
    }
}
void func_151B8DB0(void *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_15009818(void *arg0, u8 arg1) {
    func_151B8DB0(arg0, 0, 0xFF, 1);
}
void func_15009844(void *arg0, u8 arg1) {
    func_151B8DB0(arg0, 1, 0xFF, 1);
}
void func_15108850(s32 arg0);

void func_15009870(s32 arg0, s32 arg1) {
    func_15108850(arg0);
}
void func_15009894(s32 arg0, u8 arg1) {
    func_151615F8(arg0, 1, 0, 0xE, 0xFF, 1);
}
void func_15162034(s32 arg0, s32 arg1, s32 arg2);

void func_150098D0(s32 arg0, u8 arg1) {
    func_15162034(arg0, 0xFF, 1);
}
void func_151623F4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);

void func_150098F8(s32 arg0, u8 arg1) {
    func_151623F4(arg0, 1, 0x16, 0, -1, 0x12C, 0xFF, 1);
}
void func_15162740(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);

void func_15009944(s32 arg0, u8 arg1) {
    func_15162740(arg0, 1, 6, 0, 0x12C, 2, 0xFF, 1);
}
void *func_10022EC0(void *, const void *, u32);
s32 func_1516295C(s32, u8, u8, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern u8 D_80095B48[];
extern u8 D_80095B4C[];
extern u8 D_80095B50[];

void func_15009990(void *arg0, s32 arg1) {
    s32 temp_v0;
    u8 sp40[1];

    sp40[0] = D_80095B50[arg1];
    temp_v0 = func_1516295C((s32)arg0, D_80095B48[arg1], D_80095B4C[arg1], 2, 0x12C, 0xC, -1, 0, -1, 1, 1, 0xFF, 1);
    if (temp_v0 != 0) {
        func_10022EC0((u8 *)temp_v0 + 0x48, sp40, 1);
    }
}
extern u8 D_80095B27[];

void func_15009A38(s32 arg0, s32 arg1) {
    Game36680LightDescriptor sp20;

    sp20.field_0 = 2;
    sp20.field_1 = -1;
    sp20.field_2 = 0x12C;
    sp20.field_4 = D_80095B27[arg1];
    func_1516037C(&sp20, arg0, 0, 0xFF, 1);
}
void func_15162FAC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);

void func_15009AA0(s32 arg0, u8 arg1) {
    func_15162FAC(arg0, 1, 0, 2, 0x12C, 0xD, 0xFF, 1);
}
void func_15009AEC(s32 arg0, u8 arg1) {
    func_15162740(arg0, 2, 6, 0, 0x12C, 2, 0xFF, 1);
}
void func_15009B38(s32 arg0, u8 arg1) {
    func_15162740(arg0, 0x14, 6, 0, 0x12C, 2, 0xFF, 1);
}
void func_15009B84(s32 arg0, u8 arg1) {
    func_15162740(arg0, 3, 6, 0, 0x12C, 2, 0xFF, 1);
}
typedef struct Game36680LightParameters {
    s32 index;
    f32 offset;
    f32 radius;
} Game36680LightParameters;

s32 func_15187EC0(s32, f32, s32, s32, u8, u8, u8, u8);
/* These callers consume the allocation pointer left by func_1516037C. */
void *func_1516387C(s32, u8, s8, s16, u8, void *, u8, s32);

void func_15009BD0(s32 arg0, s32 arg1) {
    void *result;
    Game36680LightParameters parameters;

    parameters.offset = 0.0f;
    parameters.radius = 90.0f;
    parameters.index = func_15187EC0(0, 0.0f, 0, 0, 0, 220, 220, 255);
    result = func_1516387C(arg0, 2, 0x10, 0x12C, 0, (void *)12, 255, 1);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x18, &parameters, 12);
    }
}
void func_15009C7C(s32 arg0, s32 arg1) {
    void *result;
    Game36680LightParameters parameters;

    parameters.offset = 0.0f;
    parameters.radius = 50.0f;
    parameters.index = func_15187EC0(0, 0.0f, 0, 0, 0, 220, 220, 255);
    result = func_1516387C(arg0, 2, 0x10, 0x12C, 0, (void *)12, 255, 1);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x18, &parameters, 12);
    }
}
extern void func_15163604(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);

void func_15009D28(s32 arg0, u8 arg1) {
    func_15163604(arg0, 1, 5, 0x12C, 0, 0, 0xFF, 1);
}
void func_15009D6C(s32 arg0, u8 arg1) {
    func_15163604(arg0, 2, 5, 0x12C, 0, 0, 0xFF, 1);
}
void func_15009DB0(s32 arg0, u8 arg1) {
    func_15162740(arg0, 4, 6, 0, 0x12C, 2, 0xFF, 1);
}
void func_15009DFC(s32 arg0, u8 arg1) {
    func_15162740(arg0, 5, 6, 0, 0x12C, 2, 0xFF, 1);
}
void func_15009E48(s32 arg0, u8 arg1) {
    func_151615F8(arg0, 1, 1, 0xE, 0xFF, 1);
}
void func_15009E84(s32 arg0, u8 arg1) {
    func_15163604(arg0, 3, 5, 0x12C, 0, 0, 0xFF, 1);
}
void func_1516381C(void *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_15009EC8(void *arg0, u8 arg1) {
    func_1516381C(arg0, 0x20, 0xFF, 1);
}
void func_15009EF4(s32 arg0, u8 arg1) {
    func_151615F8(arg0, 1, 3, 0x23, 0xFF, 1);
}
void func_15009F30(s32 arg0, u8 arg1) {
    func_15163604(arg0, 4, 0x24, 0x12C, 0, 0, 0xFF, 1);
}
void func_15009F74(s32 arg0, s32 arg1) {
    void *result;
    Game36680LightParameters parameters;

    parameters.offset = 0.0f;
    parameters.radius = 60.0f;
    parameters.index = func_15187EC0(1, 0.1f, 100, 100, 100, 255, 100, 100);
    result = func_1516387C(arg0, 2, 0x10, 0x12C, 0, (void *)12, 255, 1);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x18, &parameters, 12);
    }
}
void func_1500A028(s32 arg0, u8 arg1) {
    func_15163604(arg0, 5, 5, 0x12C, 0, 0, 0xFF, 1);
}
void func_1500A06C(s32 arg0, u8 arg1) {
    func_15163604(arg0, 6, 5, 0x12C, 0, 0, 0xFF, 1);
}
void func_1500A0B0(s32 arg0, u8 arg1) {
    func_15162740(arg0, 7, 6, 0, 0x12C, 2, 0xFF, 1);
}
void func_1500A0FC(s32 arg0, u8 arg1) {
    func_15162740(arg0, 9, 6, 0, 0x12C, 2, 0xFF, 1);
}
void func_1500A148(s32 arg0, u8 arg1) {
    func_15162740(arg0, 0xA, 6, 0, 0x12C, 2, 0xFF, 1);
}
void func_1500A194(s32 arg0, u8 arg1) {
    func_15162740(arg0, 0xB, 0x26, 0, 0x12C, 2, 0xFF, 1);
}
void func_1500A1E0(s32 arg0, u8 arg1) {
    func_151615F8(arg0, 1, 4, 0xE, 0xFF, 1);
}
void func_1500A21C(s32 arg0, u8 arg1) {
    func_15163604(arg0, 7, 5, 0x12C, 0, 0, 0xFF, 1);
}
void func_1500A260(s32 arg0, u8 arg1) {
    func_15162FAC(arg0, 2, 0, 2, 0x12C, 0xD, 0xFF, 1);
}
typedef struct Game36680FourBytes {
    u32 word;
} Game36680FourBytes;
extern Game36680FourBytes D_80095B70;

void func_1500A2AC(void *arg0, s32 arg1) {
    Game36680FourBytes sp1C;

    sp1C = D_80095B70;
    func_151B8DB0(arg0, *((u8 *)&sp1C + arg1 - 0x33), 0xFF, 1);
}
void *func_15164208(s32, u8, u8, s32);
typedef struct Game36680TwoBytes {
    u16 half;
} Game36680TwoBytes;
extern Game36680TwoBytes D_80095B74;

void func_1500A2F4(s32 arg0, s32 arg1) {
    Game36680TwoBytes sp1C;

    sp1C = D_80095B74;
    func_15164208(arg0, *((u8 *)&sp1C + arg1 - 0x38), 0xFF, 1);
}
void func_1500A33C(s32 arg0, u8 arg1) {
    func_15163604(arg0, 8, 5, 0x12C, 0, 0, 0xFF, 1);
}
void func_1500A380(s32 arg0, u8 arg1) {
    func_15163604(arg0, 9, 0x28, 0x12C, 0, 0, 0xFF, 1);
}
void func_1500A3C4(s32 arg0, u8 arg1) {
    func_15162740(arg0, 0xF, 6, 0, 0x12C, 2, 0xFF, 1);
}
void func_1500A410(s32 arg0, u8 arg1) {
    func_15163604(arg0, 0xA, 5, 0x12C, 0, 0, 0xFF, 1);
}
void func_1500A454(s32 arg0, u8 arg1) {
    func_151615F8(arg0, 0, 5, 0xE, 0xFF, 1);
}
void func_1500A490(s32 arg0, u8 arg1) {
    func_15163604(arg0, 0xB, 5, 0x12C, 0, 0, 0xFF, 1);
}
void func_1500A4D4(s32 arg0, u8 arg1) {
    func_15163604(arg0, 0xC, 0x29, 0x12C, 0, 0, 0xFF, 1);
}
void func_1500A518(s32 arg0, u8 arg1) {
    func_15163604(arg0, 0xD, 0x29, 0x12C, 0, 0, 0xFF, 1);
}
void func_1500A55C(s32 arg0, u8 arg1) {
    func_151623F4(arg0, 1, 0x16, 0, -1, 0x12C, 0xFF, 1);
}
void func_1500A5A8(s32 arg0, u8 arg1) {
    func_15162740(arg0, 0x11, 6, 0, 0x12C, 2, 0xFF, 1);
}
void func_1500A5F4(s32 arg0, u8 arg1) {
    func_15162740(arg0, 0x12, 6, 0, 0x12C, 2, 0xFF, 1);
}
void func_1500A640(s32 arg0, u8 arg1) {
    func_15162740(arg0, 0x13, 6, 0, 0x12C, 2, 0xFF, 1);
}
void func_1500A68C(s32 arg0, u8 arg1) {
    func_15162740(arg0, 0x15, 6, 0, 0x12C, 2, 0xFF, 1);
}
typedef struct Game36680SixIndices {
    u8 bytes[6];
} Game36680SixIndices;

typedef struct Game36680LightAttachment {
    f32 offset;
    f32 scale;
    s32 object;
    f32 x;
    f32 y;
    f32 z;
} Game36680LightAttachment;

s32 func_150B060C(s32, void *);
extern Game36680SixIndices D_80082BEC;
extern s32 D_800BE9F0;

void func_1500A6D8(s32 arg0, s32 arg1) {
    Game36680LightDescriptor descriptor;
    Game36680LightAttachment attachment;
    s32 row;
    Game36680SixIndices indices = D_80082BEC;
    void *result;

    row = (D_800BE9F0 == 6) ? 1 : 0;
    if (func_150B060C(indices.bytes[row * 3 + arg1 - 0x49], &attachment) != 0) {
        descriptor.field_0 = 0;
        descriptor.field_1 = 0x17;
        descriptor.field_2 = 0x12C;
        descriptor.field_4 = 0;
        result = func_1516037C(&descriptor, arg0, (void *)0x18, 255, 1);
        if (result != 0) {
            func_10022EC0((u8 *)result + 0x18, &attachment, 0x18);
        }
    }
}
void func_1500A79C(s32 arg0, u8 arg1) {
    func_15162740(arg0, 0x16, 6, 0, 0x12C, 2, 0xFF, 1);
}
typedef struct Game36680AttachmentObject {
    u8 pad0[0x10];
    s16 x;
    s16 y;
    s16 z;
} Game36680AttachmentObject;

void *func_151149AC(u8);
extern Game36680SixIndices D_80082BF4;

void func_1500A7E8(s32 arg0, s32 arg1) {
    Game36680LightDescriptor descriptor;
    Game36680LightAttachment attachment;
    s32 unused;
    Game36680SixIndices indices = D_80082BF4;
    void *result;

    attachment.object = (s32)func_151149AC(indices.bytes[arg1 - 0x50]);
    if (attachment.object != 0) {
        attachment.offset = -400.0f;
        attachment.scale = 4.0f;
        attachment.x = ((Game36680AttachmentObject *)attachment.object)->x;
        attachment.y = ((Game36680AttachmentObject *)attachment.object)->y;
        attachment.z = ((Game36680AttachmentObject *)attachment.object)->z;
        descriptor.field_0 = 0;
        descriptor.field_1 = 0x17;
        descriptor.field_2 = 0x12C;
        descriptor.field_4 = 0;
        result = func_1516037C(&descriptor, arg0, (void *)0x18, 255, 1);
        if (result != 0) {
            func_10022EC0((u8 *)result + 0x18, &attachment, 0x18);
        }
    }
}
void func_1500A8C8(s32 arg0, u8 arg1) {
    func_151615F8(arg0, 0, 6, 0xE, 0xFF, 1);
}
void func_1500A904(s32 arg0, s32 arg1) {
    func_151615F8(arg0, 1, (arg1 - 0x50) & 0xFF, 0xE, 0xFF, 1);
}
typedef void (*Func1500A94CCallback)(s32 arg0, s32 arg1);
extern Func1500A94CCallback D_80082BFC[];

void func_1500A94C(s32 arg0, s32 arg1) {
    Func1500A94CCallback temp_v0;

    if ((arg1 > 0) && (arg1 < 0x59)) {
        temp_v0 = D_80082BFC[arg1];
        if (temp_v0 != 0) {
            temp_v0(arg0, arg1);
        }
    }
}
s32 func_10024770(void);
u32 func_150ADA20(void);
void *func_15149130(s16, s8, s8, s8, u8, u8, s32, u8, s32);
extern f32 D_80095BB8;
extern f32 D_80095BBC;
extern f32 D_80095BC0;
extern f32 D_80095BC4;
extern f32 D_80095BC8;
extern f32 D_80095BCC;
extern f32 D_80095BD0;
extern f32 D_80095BD4;
extern f32 D_80095BD8;

void func_1500A990(s32 arg0) {
    f32 parameters[12];
    f32 fraction;
    s32 seed;
    void *result;

    parameters[0] = 35.0f;
    parameters[1] = 35.0f;
    parameters[2] = 60.0f;
    parameters[3] = 34.0f;
    parameters[4] = 30.0f;
    parameters[5] = 50.0f;
    seed = func_10024770();
    fraction = (f32)((func_150ADA20() * seed) & 0xFFFFU) * D_80095BB8;
    parameters[6] = (fraction + fraction) * D_80095BBC;
    seed = func_10024770();
    fraction = (f32)((func_150ADA20() * seed) & 0xFFFFU) * D_80095BC0;
    parameters[7] = (fraction + fraction) * D_80095BC4;
    seed = func_10024770();
    fraction = (f32)((func_150ADA20() * seed) & 0xFFFFU) * D_80095BC8;
    parameters[8] = (fraction + fraction) * D_80095BCC;
    parameters[9] = D_80095BD0;
    parameters[10] = D_80095BD4;
    parameters[11] = D_80095BD8;
    result = func_15149130(0x12C, -1, 0x2D, -1, 0, 0, 0x30, 255, 1);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0x28, parameters, 0x30);
    }
}
typedef void (*Func1500AB5CCallback)(s32 arg0);
extern Func1500AB5CCallback D_80082D60[];

void func_1500AB5C(s32 arg0) {
    Func1500AB5CCallback temp_v0;

    if ((arg0 > 0) && (arg0 < 6)) {
        temp_v0 = D_80082D60[arg0];
        if (temp_v0 != 0) {
            temp_v0(arg0);
        }
    }
}

void func_100226F0(void *, s32);
void func_1502B8E0(void *, s32, s32, s32, s32, s32);
extern u8 D_800BE4A0[0x3C];
extern u8 D_800DD478[0x618];
extern u8 D_800DDA90[0xF0];

void func_1500ABA0(s32 arg0) {
    func_100226F0(D_800BE4A0, sizeof(D_800BE4A0));
    func_1502B8E0(D_800BE4A0, sizeof(D_800BE4A0), 3, 0xC, arg0, 0xA);
    func_100226F0(D_800DDA90, sizeof(D_800DDA90));
    func_100226F0(D_800DD478, sizeof(D_800DD478));
}
typedef struct Game36680ResourceState {
    void *data;
    s32 size;
    s32 cursor;
    u8 active;
    u8 padD[3];
} Game36680ResourceState;

typedef struct Game36680ResourceChoice {
    u16 id;
    u16 flags;
} Game36680ResourceChoice;

typedef struct Game36680ResourceInfo {
    u8 flags;
    u8 frames;
    u16 length;
    s16 x;
    s16 y;
    u8 width;
    u8 pad9;
} Game36680ResourceInfo;

/* The second argument counts variadic resource-path components. */
void *func_1502B020(s32 *, s32, ...);
extern Game36680ResourceInfo D_80095CE0[];
extern u16 D_800BE478[];
extern s16 D_800DDB80[][2];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1500AC14 CURRENT (1688) */
void func_1500AC14(void) {
    s32 index;
    s32 offset;
    u32 id;
    u32 length;
    s32 size;
    Game36680ResourceState *state;
    Game36680ResourceChoice *choice;
    u32 width;
    Game36680ResourceInfo *info;
    s16 *dimensions;
    s32 actual_size;

    choice = (Game36680ResourceChoice *)D_800BE4A0;
    state = (Game36680ResourceState *)D_800DDA90;
    index = 0;
    offset = 0;
    do {
        id = choice->id;
        state->data = 0;
        state->cursor = 0;
        state->size = 0;
        state->active = 0;
        if ((id != 255) && ((D_800BE478[index] != 0) || (id == 0x3B))) {
            dimensions = (s16 *)((s32)D_800DDB80 + offset);
            info = &D_80095CE0[id];
            state->data = func_1502B020(&size, 2, 0, id);
            actual_size = size;
            state->size = (actual_size + 15) & ~15;
            length = info->length;
            if ((actual_size == 0) || (length == 0)) {
                length = 0;
                state->data = 0;
            }
            width = info->width;
            dimensions[0] = (width << 5) - 1;
            dimensions[1] = ((u32)((length / width) << 6) / 5U) - 1;
        }
        index++;
        state++;
        offset += 4;
        choice++;
    } while (index != 15);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1500AC14 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500AC14.s")
extern u8 D_80095CC4[];
extern s16 D_800BE438[][2];
extern u8 D_800DDBC0[];
extern u8 D_800DDBD0[];
extern u8 D_800DDBE0[];
extern u8 D_800DDBF0[];
extern u8 D_800DDC20[][2];
extern u8 D_800DDC80[];
extern s32 D_800DDC00;
extern s32 D_800DDC04;
extern s32 D_800DDC08;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1500AD84 CURRENT (500) */
void func_1500AD84(s32 arg0, s32 arg1, s32 arg2) {
    Game36680ResourceInfo *info;
    u8 *cursor;
    u8 palette;
    s32 options;
    u8 last;

    if (arg1 != 255) {
        cursor = &D_800DDBD0[arg0];
        info = &D_80095CE0[arg1];
        options = arg2;
        arg2 = info->flags;
        *cursor = info->frames;
        if (arg2 & 0x10) {
            *cursor -= 1;
            D_800DDBE0[arg0] = *cursor;
        } else {
            D_800DDBE0[arg0] = 0;
        }
        if (arg2 & 0x80) {
            D_800DDBF0[arg0] = 2;
        } else {
            D_800DDBF0[arg0] = 1;
        }
        cursor = (u8 *)D_800BE438[arg0];
        ((s16 *)cursor)[0] = info->x;
        ((s16 *)cursor)[1] = info->y;
        D_800DDBC0[arg0] = arg1;
        D_800DDC80[arg0] = options & 0xFF7F;
        if (options & 0x80) {
            D_800DDC00 |= 1 << arg0;
        }
        if (arg2 & 1) {
            D_800DDC04 |= 1 << arg0;
        }
        if (arg2 & 8) {
            D_800DDC08 |= 1 << arg0;
        }
    } else {
        D_800DDBD0[arg0] = 0;
    }
    arg1 = D_80095CC4[arg0];
    D_800BE478[arg0] = 0;
    cursor = D_800DDC20[arg0];
    cursor[0] = arg1;
    cursor[1] = arg1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1500AD84 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500AD84.s")
typedef struct Game36680Record {
    s16 x;
    s16 y;
    s16 z;
    u8 type;
    u8 frame;
    u8 resource;
    u8 pad9;
    u8 alpha;
    u8 padB;
    s8 scaleX;
    s8 scaleY;
} Game36680Record;

typedef struct Game36680RecordHeader {
    u8 pad0[0x18];
    u16 count;
} Game36680RecordHeader;

extern Game36680RecordHeader *D_800B0DF0;
extern Game36680Record *volatile D_800DDD18;
s32 func_151EF610(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1500AF08 CURRENT (3213) */
u32 func_1500AF08(u32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                  s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    s16 scale;
    s32 offset;
    u8 *resource;
    s16 *position;
    s16 random_scale;
    u32 limit;
    s32 resource_index;

    resource_index = arg1;
    arg3 = (s16)arg3;
    limit = D_800B0DF0->count - 1;
    if (arg0 >= limit) {
        return limit;
    }
    offset = arg0 * sizeof(Game36680Record);
    ((Game36680Record *)((u8 *)D_800DDD18 + offset))->x = arg3;
    ((Game36680Record *)((u8 *)D_800DDD18 + offset))->y = ((s16 *)&arg4)[1];
    ((Game36680Record *)((u8 *)D_800DDD18 + offset))->z = ((s16 *)&arg5)[1];
    if (D_800DDBD0[resource_index] >= 2) {
        if ((1 << resource_index) & D_800DDC00) {
            ((Game36680Record *)((u8 *)D_800DDD18 + offset))->frame = resource_index * 4 + (arg8 & 1);
        } else {
            ((Game36680Record *)((u8 *)D_800DDD18 + offset))->frame = (arg0 & 3) + resource_index * 4;
        }
    } else {
        ((Game36680Record *)((u8 *)D_800DDD18 + offset))->frame = 0x3C;
    }
    ((Game36680Record *)((u8 *)D_800DDD18 + offset))->type = (arg2 << 5) | resource_index;
    ((Game36680Record *)((u8 *)D_800DDD18 + offset))->alpha = ((u8 *)&arg7)[3];
    resource = &D_800DDBC0[resource_index];
    ((Game36680Record *)((u8 *)D_800DDD18 + offset))->resource = *resource;
    if (arg6 != 0) {
        random_scale = (((func_151EF610() % arg6) + arg6) - arg6) + 256;
        scale = random_scale;
        position = D_800BE438[resource_index];
        ((Game36680Record *)((u8 *)D_800DDD18 + offset))->scaleX = (position[0] * random_scale) >> 10;
        if (D_80095CE0[*resource].flags & 4) {
            scale += (func_151EF610() % arg6) * 4;
        }
        ((Game36680Record *)((u8 *)D_800DDD18 + offset))->scaleY = (position[1] * scale) >> 10;
    } else {
        position = D_800BE438[resource_index];
        ((Game36680Record *)((u8 *)D_800DDD18 + offset))->scaleX = position[0] >> 2;
        ((Game36680Record *)((u8 *)D_800DDD18 + offset))->scaleY = position[1] >> 2;
    }
    return arg0 + 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1500AF08 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500AF08.s")
extern f32 D_80095C64[][2];
u32 func_1500AF08(u32, s32, s32, s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1500B1F4 CURRENT (5052) */
u32 func_1500B1F4(s16 arg0, s32 arg1, s32 arg2, s32 arg3, u32 arg4, s16 **arg5) {
    f32 *weights;
    f32 x;
    f32 y;
    f32 z;
    f32 first;
    f32 second;
    s16 x0;
    s16 y0;
    s16 z0;
    s32 index;
    u32 result;
    u32 count;
    s16 *point0;
    s16 *point1;
    s16 *point2;

    index = 0;
    if (arg0 != 0) {
        weights = D_80095C64[0];
        count = arg4;
        do {
            point1 = arg5[1];
            point0 = arg5[0];
            point2 = arg5[2];
            x0 = point0[0];
            first = weights[0];
            second = weights[1];
            y0 = point0[1];
            x = (f32)(point1[0] - x0) * first + (f32)x0;
            y = (f32)(point1[1] - y0) * first + (f32)y0;
            z0 = point0[2];
            z = (f32)(point1[2] - z0) * first + (f32)z0;
            result = func_1500AF08(count, arg2, arg3,
                (s16)(s32)(((f32)point2[0] - x) * second + x),
                (s32)(((f32)point2[1] - y) * second + y),
                (s32)(((f32)point2[2] - z) * second + z),
                128, arg1 & 255, count);
            index++;
            weights += 2;
            count = result;
        } while (index != arg0);
        arg4 = result;
    }
    return arg4;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1500B1F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500B1F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500B3B0.s")
void func_1000FA64(s32, s32, s32, s32, s32, s32, s32, void *, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1500B714 CURRENT (2143) */
u32 func_1500B714(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u32 arg4, s16 **arg5) {
    u16 volume;
    u32 count;
    s32 x;
    s32 y;
    s32 z;
    s32 divisor;
    s16 *third;
    s16 *first;
    s16 *second;

    divisor = 3;
    count = (s16)arg0;
    third = arg5[2];
    first = arg5[0];
    second = arg5[1];
    volume = count;
    x = (third[0] + second[0] + first[0]) / divisor;
    y = (third[1] + second[1] + first[1]) / divisor;
    z = (third[2] + second[2] + first[2]) / divisor;
    arg4 = func_1500AF08(arg4, arg2, arg3, (s16)x, (s16)y, (s16)z, 0x80, arg1, arg4);
    if ((f32)(u32)(count & 0xFFFF) > 62.5f) {
        volume = 62;
    }
    func_1000FA64(0x4D, (s16)x, (s16)y, (s16)z, 0x8000, volume, (s32)volume >> 3, 0, 0, 0, 0, 0);
    return arg4;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1500B714 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500B714.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1500B8F4 CURRENT (4535) */
void func_1500B8F4(s16 count, s32 alpha, s32 resource, s32 type, u32 first_record, s16 **points) {
    f32 (*weights)[2];
    f32 x;
    f32 y;
    f32 z;
    f32 first;
    f32 second;
    s16 x0;
    s16 y0;
    s16 z0;
    s32 index;
    u32 result;
    u32 record;
    s16 *point0;
    s16 *point2;
    s16 *point1;

    index = 0;
    if (count != 0) {
        weights = D_80095C64;
        record = first_record;
        do {
            point1 = points[1];
            point0 = points[0];
            point2 = points[2];
            x0 = point0[0];
            first = (*weights)[0];
            second = (*weights)[1];
            y0 = point0[1];
            x = (f32)(point1[0] - x0) * first + (f32)x0;
            y = (f32)(point1[1] - y0) * first + (f32)y0;
            z0 = point0[2];
            z = (f32)(point1[2] - z0) * first + (f32)z0;
            result = func_1500AF08(record, resource, type,
                (s16)((f32)(point2[0] - x) * second + x),
                (s32)((f32)(point2[1] - y) * second + y),
                (s32)((f32)(point2[2] - z) * second + z),
                0, alpha & 0xFF, record);
            index++;
            weights++;
            record = result;
        } while (index != count);
        first_record = result;
    }
    D_800DDBD0[resource] = 0x57;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1500B8F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500B8F4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1500BAB8 CURRENT (3055) */
void func_1500BAB8(s16 arg0, u8 arg1, s32 arg2, s32 arg3, u32 arg4, s16 **arg5) {
    f32 (*var_s0)[2];
    f32 temp_fv0;
    f32 temp_fv1;
    s32 alpha;
    s32 count;
    s32 var_s1;
    u32 temp_v0_2;
    u32 var_s3;
    s16 *temp_t0;
    s16 *temp_v0;
    s16 *temp_v1;

    alpha = arg1;
    count = arg0;
    var_s1 = 0;
    if (arg0 != 0) {
        var_s0 = D_80095C64;
        var_s3 = arg4;
        do {
            temp_v1 = arg5[1];
            temp_t0 = arg5[0];
            temp_v0 = arg5[2];
            temp_fv0 = var_s0[0][0];
            temp_fv1 = var_s0[0][1];
            temp_v0_2 = func_1500AF08(var_s3, arg2, arg3, (s32) (s16) (s32) ((((f32) temp_v0[0] - (((f32)(temp_v1[0] - temp_t0[0]) * temp_fv0) + (f32)temp_t0[0])) * temp_fv1) + (((f32)(temp_v1[0] - temp_t0[0]) * temp_fv0) + (f32)temp_t0[0])), (s32) ((((f32) temp_v0[1] - (((f32)(temp_v1[1] - temp_t0[1]) * temp_fv0) + (f32)temp_t0[1])) * temp_fv1) + (((f32)(temp_v1[1] - temp_t0[1]) * temp_fv0) + (f32)temp_t0[1])), (s32) ((((f32) temp_v0[2] - (((f32)(temp_v1[2] - temp_t0[2]) * temp_fv0) + (f32)temp_t0[2])) * temp_fv1) + (((f32)(temp_v1[2] - temp_t0[2]) * temp_fv0) + (f32)temp_t0[2])), 0, alpha, (s32) var_s3);
            var_s1 += 1;
            var_s0++;
            var_s3 = temp_v0_2;
        } while (var_s1 != count);
        arg4 = temp_v0_2;
    }
    D_800DDBD0[arg2] = 8;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1500BAB8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500BAB8.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1500BC7C CURRENT (1604) */
void func_1500BC7C(s16 arg0, u8 arg1, s32 arg2, s32 arg3, u32 arg4, s16 **arg5) {
    f32 (*var_s0)[2];
    s16 x0;
    s16 y0;
    s16 z0;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 count;
    s32 var_s1;
    u32 temp_v0_2;
    u32 var_s3;
    s16 *temp_t0;
    s16 *temp_v0;
    s16 *temp_v1;

    count = arg0;
    var_s1 = 0;
    if (arg0 != 0) {
        var_s0 = D_80095C64;
        var_s3 = arg4;
        do {
            temp_v1 = arg5[1];
            temp_t0 = arg5[0];
            temp_v0 = arg5[2];
            x0 = temp_t0[0];
            y0 = temp_t0[1];
            z0 = temp_t0[2];
            temp_fv0 = var_s0[0][0];
            temp_fv1 = var_s0[0][1];
            temp_v0_2 = func_1500AF08(var_s3, arg2, arg3, (s32) (s16) (s32) ((((f32) temp_v0[0] - (((f32)(temp_v1[0] - x0) * temp_fv0) + (f32)x0)) * temp_fv1) + (((f32)(temp_v1[0] - x0) * temp_fv0) + (f32)x0)), (s32) ((((f32) temp_v0[1] - (((f32)(temp_v1[1] - y0) * temp_fv0) + (f32)y0)) * temp_fv1) + (((f32)(temp_v1[1] - y0) * temp_fv0) + (f32)y0)), (s32) ((((f32) temp_v0[2] - (((f32)(temp_v1[2] - z0) * temp_fv0) + (f32)z0)) * temp_fv1) + (((f32)(temp_v1[2] - z0) * temp_fv0) + (f32)z0)), 0, arg1, (s32) var_s3);
            var_s1 += 1;
            var_s0++;
            var_s3 = temp_v0_2;
        } while (var_s1 != count);
        arg4 = temp_v0_2;
    }
    D_800DDBD0[arg2] = 0x21;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1500BC7C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500BC7C.s")
extern s32 D_800DDD0C;
extern s32 D_800DDD10[];

void func_1500BE40(s32 arg0) {
    D_800DDD10[0] = 0;
    D_800DDD10[1] = 0;
    D_800DDD0C = 0x6E;
}
/* Call context: func_1500BE40: unique active project prototype */
extern s8 D_8008CEB0;
extern s32 D_800DDC00;
extern s32 D_800DDC04;
extern s32 D_800DDC08;
extern s8 D_800DDD1C;
extern s32 D_800DDD20;

void func_1500BE68(void) {
    D_800DDD1C = 0;
    D_8008CEB0 = 0;
    D_800DDC04 = D_800DDC00 = D_800DDC08 = 0;
    D_800DDD20 = 0;
    func_1500BE40(0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_36680/func_1500BEC0.s")
