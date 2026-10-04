#include "types.h"

/*
 * Reviewed source unit: src/game/game_135D00.c
 * Boundary evidence: docs/evidence/game_raw_sorted_record_object_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15108850
 * - func_15108AB4
 * - func_15108B80
 * - func_15108BC0
 * - func_15108D24
 * - func_15108E10
 * - func_15109064
 * - func_15109120
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    f32 values[5];
    s32 lifetime;
    u8 field18;
    u8 pad19[3];
    s32 field1C;
    u8 field20;
    u8 pad21[3];
} Game135D00Parameters;

typedef struct {
    s8 type, field1, field2, pad3;
    s16 lifetime;
    u8 pad6[2];
    s32 field8, fieldC, field10, field14, field18, field1C, field20;
    u8 field24, field25;
    u8 pad26[0xA];
    s32 field30, field34;
    u8 field38;
    u8 pad39[3];
} Game135D00SpawnDescriptor;

typedef struct {
    Game135D00Parameters parameters;
    Game135D00SpawnDescriptor descriptor;
} Game135D00SpawnWork;

typedef struct {
    void *owner;
    u8 mode, intensity;
    s16 lifetime;
    u8 kind;
    u8 pad9[3];
} Game135D00LightWork;

void *func_1513B5E0(s8 *, u8, s32, u8, s32);
void *func_1516037C(void *, s32, void *, u8, s32);
void *func_10022EC0(void *, const void *, u32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15108850 CURRENT (886) */
void func_15108850(s32 arg0) {
    void *saved;
    Game135D00SpawnWork first;
    Game135D00LightWork light;
    Game135D00SpawnWork second;
    void *object;
    void *lamp;

    first.parameters.lifetime = 999;
    first.parameters.field18 = 0xFF;
    first.parameters.field1C = -1;
    first.parameters.field20 = 1;
    first.descriptor.field2 = 1;
    first.descriptor.lifetime = 300;
    first.descriptor.field30 = 9;
    first.parameters.values[0] = 0.0f;
    first.parameters.values[1] = 0.0f;
    first.parameters.values[2] = 0.0f;
    first.parameters.values[3] = 0.0f;
    first.descriptor.type = 0;
    first.descriptor.field1 = 0;
    first.descriptor.field34 = 427;
    first.descriptor.field8 = 1;
    first.descriptor.fieldC = 0x220205;
    first.descriptor.field10 = 0x40600;
    first.descriptor.field24 = 0;
    first.descriptor.field25 = 0;
    first.descriptor.field14 = 1;
    first.descriptor.field18 = 0x36;
    first.descriptor.field1C = 0x80;
    first.descriptor.field20 = 0x20;
    first.descriptor.field38 = 1;
    first.parameters.values[4] = 226.0f;
    object = func_1513B5E0(&first.descriptor.type, 1, 0x24, 0xFF, 1);
    if (object != 0) {
        saved = object;
        func_10022EC0((u8 *)object + *(s32 *)((u8 *)object + 0x50) + 0xF8,
                      &first.parameters, 0x24);
        light.owner = saved;
        light.mode = 2;
        light.intensity = 8;
        light.lifetime = 300;
        light.kind = 0x13;
        lamp = func_1516037C(&light.mode, arg0, (void *)4, 0xFF, 1);
        if (lamp != 0) {
            func_10022EC0((u8 *)lamp + 0x18, &light.owner, 4);
        }
    }
    second.parameters.lifetime = 999;
    second.parameters.field18 = 0xFF;
    second.parameters.field1C = -1;
    second.parameters.field20 = 1;
    second.descriptor.field1 = 1;
    second.descriptor.field2 = 4;
    second.descriptor.lifetime = 300;
    second.descriptor.field30 = 9;
    second.parameters.values[0] = 0.0f;
    second.parameters.values[1] = 0.0f;
    second.parameters.values[2] = 0.0f;
    second.parameters.values[3] = 0.0f;
    second.descriptor.type = 0;
    second.descriptor.field34 = 428;
    second.descriptor.field8 = 1;
    second.descriptor.fieldC = 0x220205;
    second.descriptor.field10 = 0x40600;
    second.descriptor.field24 = 0;
    second.descriptor.field25 = 0;
    second.descriptor.field14 = 1;
    second.descriptor.field18 = 0x36;
    second.descriptor.field1C = 0x80;
    second.descriptor.field20 = 0x20;
    second.descriptor.field38 = 1;
    second.parameters.values[4] = 226.0f;
    object = func_1513B5E0(&second.descriptor.type, 1, 0x24, 0xFF, 1);
    if (object != 0) {
        func_10022EC0((u8 *)object + *(s32 *)((u8 *)object + 0x50) + 0xF8,
                      &second.parameters, 0x24);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15108850 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_135D00/func_15108850.s")

/* Call context: func_15047D60: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15144B68(f32);                             /* extern */
extern f32 D_800A2470;
extern f32 D_800A2474;
extern f32 D_800A2478;
extern f32 D_800A247C;
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15108AB4 CURRENT (310) */
s32 func_15108AB4(u8 *arg0) {
    u8 *temp_s0;
    f32 first;

    temp_s0 = (void *)(arg0 + *(s32 *)((u8 *)arg0 + 0x50));
    first = *(f32 *)(temp_s0 + 0x100);
    temp_s0 += 0xF8;
    *(f32 *)(temp_s0 + 8) = first + (D_800A2470 * D_800BE9A4);
    *(f32 *)(temp_s0 + 0xC) += D_800A2474 * D_800BE9A4;
    *(f32 *)(temp_s0 + 8) = func_15144B68(*(f32 *)(temp_s0 + 8));
    *(f32 *)(temp_s0 + 0xC) = func_15144B68(*(f32 *)(temp_s0 + 0xC));
    *(f32 *)temp_s0 = func_15047D60(*(f32 *)(temp_s0 + 8)) * D_800A2478;
    *(f32 *)(temp_s0 + 4) = func_15047D60(*(f32 *)(temp_s0 + 0xC)) * D_800A247C;
    func_15108B80(arg0);
    func_15108BC0(arg0);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15108AB4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_135D00/func_15108AB4.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15108B80 CURRENT (60) */
void func_15108B80(u8 *arg0) {
    s32 temp_t0;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_v0 = (void *)(arg0 + *(s32 *)((u8 *)arg0 + 0x50));
    temp_v0_2 = (void *)(temp_v0 + 0xF8);
    if (*(s32 *)((u8 *)temp_v0 + 0x10C) != 0x3E7) {
        temp_t0 = *(s32 *)((u8 *)temp_v0_2 + 0x1C) - D_800BE9E4;
        *(s32 *)((u8 *)temp_v0_2 + 0x1C) = temp_t0;
        if (temp_t0 < 0) {
            *(s32 *)((u8 *)temp_v0_2 + 0x14) = 0x3E7;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15108B80 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_135D00/func_15108B80.s")
extern u8 D_800C35EA;
extern s32 D_800C3958;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15108BC0 CURRENT (270) */
void func_15108BC0(u8 *arg0) {
    s32 temp_v1;
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + *(s32 *)((u8 *)arg0 + 0x50));
    temp_v1 = *(s32 *)((u8 *)temp_v0 + 0x10C);
    temp_v0 += 0xF8;
    if (temp_v1 == 0x3E7) {
        *(f32 *)(temp_v0 + 0x10) = 226.0f;
        return;
    }
    if (D_800C35EA == 1) {
        arg0 = ((u8 (*)[0x44])D_800C3958)[temp_v1];
        *(f32 *)(temp_v0 + 0x10) = *(f32 *)(arg0 + 4);
        return;
    }
    *(f32 *)(temp_v0 + 0x10) = 226.0f;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15108BC0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_135D00/func_15108BC0.s")
/* Call context: func_15047D60: unique active project prototype */
extern f32 D_800A2480;
extern f32 D_800A2484;
extern f32 D_800A2488;
extern f32 D_800A248C;

s32 func_15108C38(u8 *arg0) {
    u8 *temp_s0;

    temp_s0 = arg0;
    temp_s0 += *(s32 *)(arg0 + 0x50);
    temp_s0 += 0xF8;
    *(f32 *)((u8 *)temp_s0 + 8) = (f32) (*(f32 *)((u8 *)temp_s0 + 8) + (D_800A2480 * D_800BE9A4));
    *(f32 *)((u8 *)temp_s0 + 0xC) = (f32) (*(f32 *)((u8 *)temp_s0 + 0xC) + (D_800A2484 * D_800BE9A4));
    *(f32 *)((u8 *)temp_s0 + 8) = func_15144B68(*(f32 *)((u8 *)temp_s0 + 8));
    *(f32 *)((u8 *)temp_s0 + 0xC) = func_15144B68(*(f32 *)((u8 *)temp_s0 + 0xC));
    *(f32 *)((u8 *)temp_s0 + 0) = (f32) (func_15047D60(*(f32 *)((u8 *)temp_s0 + 8)) * D_800A2488);
    *(f32 *)((u8 *)temp_s0 + 4) = (f32) (func_15047D60(*(f32 *)((u8 *)temp_s0 + 0xC)) * D_800A248C);
    func_15108B80(arg0);
    func_15108BC0(arg0);
    if (*(u8 *)((u8 *)temp_s0 + 0x20) != 0) {
        *(s8 *)((u8 *)arg0 + 0x12) = 4;
    } else {
        *(s8 *)((u8 *)arg0 + 0x12) = 2;
    }
    return 1;
}
typedef struct Game135D00MatrixWork {
    f32 values[12];
    s32 pad_30;
    f32 saved;
    s32 pad_38;
    s32 pad_3C;
} Game135D00MatrixWork;

void func_150A8050(f32 *, f32, f32, f32);
void func_150A7790(void *, s32);
extern f32 D_800A2490;
extern u8 D_800BE9C0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15108D24 CURRENT (50) */
s32 func_15108D24(u8 *arg0, s32 arg1) {
    Game135D00MatrixWork work;
    u8 *source;

    source = arg0 + *(s32 *)(arg0 + 0x50) + 0xF8;
    func_150A8050(work.values, *(f32 *)(source + 0), 0.0f,
                  *(f32 *)(source + 4));
    work.saved = *(f32 *)(source + 0x10);
    work.values[0] *= D_800A2490;
    work.values[1] *= D_800A2490;
    work.values[2] *= D_800A2490;
    work.values[4] *= D_800A2490;
    work.values[5] *= D_800A2490;
    work.values[6] *= D_800A2490;
    work.values[8] *= D_800A2490;
    work.values[9] *= D_800A2490;
    work.values[10] *= D_800A2490;
    func_150A7790(work.values, (s32)(arg0 + (D_800BE9C0 << 6) + 0x78));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15108D24 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_135D00/func_15108D24.s")
typedef struct Game135D00Point {
    f32 x;
    f32 y;
    f32 z;
} Game135D00Point;

void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
s32 func_150AC9C0(f32, f32, f32, f32, f32, f32, void *, s16 *,
                  f32 *, f32 *, f32 *, f32 *, s32 *, void *, f32);
extern f32 D_800A2494;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15108E10 CURRENT (889) */
s32 func_15108E10(u8 *arg0) {
    Game135D00Point point;
    Game135D00MatrixWork work;
    f32 difference;
    f32 height;
    u8 *state;
    Game135D00Point output;
    u8 *base;

    base = *(u8 **)(arg0 + 0x18);
    state = base;
    state += *(s32 *)(base + 0x50);
    state += 0xF8;
    func_150A8050(work.values, *(f32 *)(state + 0), 0.0f,
                  *(f32 *)(state + 4));
    work.saved = *(f32 *)(state + 0x10);
    work.values[0] *= D_800A2494;
    work.values[1] *= D_800A2494;
    work.values[2] *= D_800A2494;
    work.values[4] *= D_800A2494;
    work.values[5] *= D_800A2494;
    work.values[6] *= D_800A2494;
    work.values[8] *= D_800A2494;
    work.values[9] *= D_800A2494;
    work.values[10] *= D_800A2494;
    func_150A7960(work.values, 0.0f, -1108.0f, 0.0f,
                  &point.x, &point.y, &point.z);
    height = *(f32 *)(state + 0x10);
    difference = point.y - height;
    if (func_150AC9C0(0.0f, height, 0.0f, point.x, difference,
                      point.z, 0, 0, &output.x, &output.y, &output.z,
                      0, 0, 0, 0.0f) == 0) {
        output = point;
    }
    *(s16 *)(*(u8 **)(arg0 + 0x14) + 0xE) = (s32)output.x;
    *(s16 *)(*(u8 **)(arg0 + 0x14) + 0x10) = (s32)output.y;
    *(s16 *)(*(u8 **)(arg0 + 0x14) + 0x12) = (s32)output.z;
    if (state[0x20] != 0) {
        *(*(u8 **)(arg0 + 0x14) + 9) = 0;
    } else {
        *(*(u8 **)(arg0 + 0x14) + 9) = 1;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15108E10 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_135D00/func_15108E10.s")
typedef struct Game135D00DispatchDescriptor {
    s32 field0;
    s32 field4;
} Game135D00DispatchDescriptor;

typedef struct Game135D00DispatchMessage {
    s32 arg0;
    s32 arg1;
    u8 arg2;
} Game135D00DispatchMessage;

extern Game135D00DispatchDescriptor D_80088C50;
void func_15169260(Game135D00DispatchDescriptor *, s32, Game135D00DispatchMessage *, s32);

void func_15108FFC(s32 arg0, s32 arg1, u8 arg2) {
    Game135D00DispatchMessage message;
    Game135D00DispatchDescriptor descriptor;

    descriptor = D_80088C50;
    message.arg0 = arg0;
    message.arg1 = arg1;
    message.arg2 = arg2;
    func_15169260(&descriptor, 2, &message, 0x1D);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15109064 CURRENT (130) */
void func_15109064(u8 *arg0, u8 *arg1, u8 arg2) {
    u8 *temp_v0;

    temp_v0 = (void *)(arg0 + *(s32 *)((u8 *)arg0 + 0x50) + 0xF8);
    switch (arg2) {                              /* irregular */
    case 29:
        *(s32 *)((u8 *)temp_v0 + 0x14) = (s32) *(s32 *)((u8 *)arg1 + 0);
        *(u8 *)((u8 *)temp_v0 + 0x18) = (u8) *(u8 *)((u8 *)arg1 + 8);
        *(s32 *)((u8 *)temp_v0 + 0x1C) = (s32) *(s32 *)((u8 *)arg1 + 4);
        return;
    case 30:
        if (*(u8 *)((u8 *)temp_v0 + 0x20) != 0) {
            *(u8 *)((u8 *)temp_v0 + 0x20) = 0U;
            return;
        }
        *(u8 *)((u8 *)temp_v0 + 0x20) = 1U;
        return;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15109064 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_135D00/func_15109064.s")
extern Game135D00DispatchDescriptor D_80088C58;

void func_151090DC(void) {
    Game135D00DispatchDescriptor sp18;

    sp18 = D_80088C58;
    func_15169260(&sp18, 2, 0, 0x1E);
}
typedef struct Game109120Vertex {
    s16 x, y, z, flag;
    s16 s, t;
    u8 color[4];
} Game109120Vertex;

s32 func_15144B34(s32);
f32 sqrtf(f32);
f32 fabsf(f32);
#pragma intrinsic(sqrtf)
#pragma intrinsic(fabsf)
extern f32 D_800A2498;
extern f32 D_800A249C;
extern f32 D_800A24A0;
extern f32 D_800A24A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15109120 CURRENT (2838) */
s32 func_15109120(u8 *arg0, register s32 arg1) {
    f32 matrix[16];
    f32 horizontalX, horizontalZ;
    f32 inverse, cameraX, cameraZ;
    f32 horizontalScale, verticalScale;
    s32 index;
    u8 *state;
    f32 *camera;
    Game109120Vertex *vertex;
    f32 transformedY;
    f32 textureS, textureT;
    Game135D00Point output;

    arg1 = (s16)arg1;
    state = arg0 + *(s32 *)(arg0 + 0x50) + 0xF8;
    func_150A8050(matrix, *(f32 *)state, 0.0f, *(f32 *)(state + 4));
    matrix[13] = *(f32 *)(state + 0x10);
    matrix[0] *= D_800A2498;
    matrix[1] *= D_800A2498;
    matrix[2] *= D_800A2498;
    matrix[4] *= D_800A2498;
    matrix[5] *= D_800A2498;
    matrix[6] *= D_800A2498;
    matrix[8] *= D_800A2498;
    matrix[9] *= D_800A2498;
    matrix[10] *= D_800A2498;
    func_150A7790(matrix, (s32)(arg0 + (D_800BE9C0 << 6) + 0x78));
    camera = (f32 *)func_15144B34(arg1);
    cameraX = camera[0];
    index = 0;
    if (D_800A249C < fabsf(cameraX) || D_800A249C < fabsf(camera[1])) {
        cameraZ = camera[2];
        inverse = 1.0f / sqrtf(cameraX * cameraX + cameraZ * cameraZ);
        horizontalX = cameraZ * inverse;
        horizontalZ = -cameraX * inverse;
    } else {
        horizontalX = 1.0f;
        horizontalZ = 0.0f;
    }
    horizontalScale = D_800A24A0;
    inverse = 81.0f;
    verticalScale = D_800A24A4;
    do {
        vertex = *(Game109120Vertex **)(arg0 + D_800BE9C0 * 0x10 + arg1 * 4 + 0x58) + index;
        func_150A7960(matrix, vertex->x, vertex->y, vertex->z, &output.x, &output.y, &output.z);
        index++;
        transformedY = output.y;
        cameraX = output.x;
        cameraZ = output.z;
        textureT = transformedY * verticalScale + inverse;
        textureS = (cameraX * horizontalX + cameraZ * horizontalZ) * horizontalScale + 26.0f;
        vertex->s = (s32)(textureS * 32.0f);
        vertex->t = (s32)(textureT * 32.0f);
    } while (index != 0x10);
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15109120 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_135D00/func_15109120.s")
