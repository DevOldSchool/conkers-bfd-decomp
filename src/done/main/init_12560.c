#include "types.h"

/*
 * Reviewed source unit: src/main/init_12560.c
 * Boundary evidence: docs/evidence/boundaries/main/main_sequence_api_mp3_adapter_boundaries.md
 */

typedef struct {
    s32 buffer;
    s32 capacity;
    s32 readPosition;
    s32 writePosition;
} Mp3TextTransport;

extern Mp3TextTransport D_800427A0;
s32 func_85043BB8(Mp3TextTransport *, s32 *, s32);

void func_80012560(s32 arg0, u8 *text, s32 length) {
    func_85043BB8(&D_800427A0, (s32 *)text, length);
}
void func_85016170(s32);
void func_85043A00(Mp3TextTransport *, s32, s32);
void func_851F3C1C(void (*)(s32, u8 *, s32));
void D_10012560(s32, u8 *, s32);
extern u8 D_800427B0[];

void func_80012588(s32 arg0) {
    func_85016170(arg0);
    func_85043A00(&D_800427A0, (s32)D_800427B0, 0x40);
    func_851F3C1C(D_10012560);
}
s32 func_851F2CDC(void);
void func_851F2D6C(s32, s32);
void func_851F2BA8(void);
extern s32 D_800BE9F8;

void func_800125CC(s32 arg0) {
    s32 state;

    state = func_851F2CDC();
    if ((arg0 != 0x1E) || (D_800BE9F8 != 0x1B)) {
        if (state == 1) {
            func_851F2D6C(0, 0x2B02);
            return;
        }
        if (state != 0) {
            func_851F2BA8();
        }
    }
}
void *func_8502B020(s32 *, s32, ...);
void func_851F2960(s32, s32);
void func_851F2DFC(s32, s32);
void func_851F2E4C(s32, s32);
extern s16 D_800427F4;

void func_8001263C(s32 arg0, s32 volume, s32 pan) {
    void *resource;
    s32 size;

    size = 0;
    resource = func_8502B020(&size, 2, 0x16, arg0);
    D_800427F4 = arg0;
    if ((resource != 0) && (size != 0)) {
        func_851F2D6C(volume, 0);
        func_851F2DFC(pan, 1);
        if (arg0 != 0xD2) {
            func_851F2E4C(0xA, 0x2AF8);
        } else {
            func_851F2E4C(0, 0);
        }
        func_851F2960((s32)resource, size);
    }
}
s32 func_85043CA4(Mp3TextTransport *, u8 *, s32);

s32 func_800126E8(u8 *text, s32 capacity) {
    return func_85043CA4(&D_800427A0, text, capacity);
}
typedef struct {
    u8 pad0[0x14];
    f32 x;
    f32 y;
    f32 z;
    u8 pad20[0x2F8];
    s32 field318;
} Mp3SpatialState;

void func_800114D0(s32, s32, s32, s32, s32, s32, s32 *, s32 *, s32 *);

s32 func_80012718(u16 arg0, u8 *arg1, s32 arg2, s16 arg3, s32 arg4) {
    s32 pan;
    s32 volume;
    s32 spatial;

    if (((Mp3SpatialState *)arg1)->field318 != 0) {
        func_8001263C(arg0, arg2, 0x40);
    } else {
        func_800114D0((s32)((Mp3SpatialState *)arg1)->x,
                     (s32)((Mp3SpatialState *)arg1)->y,
                     (s32)((Mp3SpatialState *)arg1)->z,
                     arg2, (u16)arg4, arg3, &pan, &volume, &spatial);
        func_8001263C(arg0, volume, pan);
    }
    return 1;
}
s32 func_851F2CDC(void);

s32 func_800127D0(void) {
    s32 state;

    state = func_851F2CDC();
    if ((state == 1) || (state == 2) || (state == 5)) {
        return 1;
    }
    return 0;
}
