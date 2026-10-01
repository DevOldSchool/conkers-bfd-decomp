#include "types.h"

/*
 * Reviewed source unit: src/main/init_8F90.c
 * Boundary evidence: docs/evidence/main_audio_driver_sequence_boundaries.md
 *
 * TODO: Implement these source-unit functions:
 * - func_80008F90
 * - func_80009400
 * - func_800095A0
 * - func_800097CC
 * - func_800099BC
 * - func_80009BE4
 * - func_80009CBC
 * - func_8000A03C
 * - func_8000A348
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8F90/func_80008F90.s")
void func_80022E00(void *);
extern u8 D_8002AE40;
extern u8 D_8003E3A0[];

void func_800093CC(void) {
    if (D_8002AE40 != 0) {
        func_80022E00(D_8003E3A0);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8F90/func_80009400.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8F90/func_800095A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8F90/func_800097CC.s")
/* SDK ALDMAproc contract, using the project scalar aliases. */
typedef s32 (*ALDMAproc)(s32 addr, s32 len, void *state);

typedef struct {
    u8 initialized;
    u8 pad1[3];
    s32 field4;
    void *base;
} AudioDmaManager;

extern AudioDmaManager D_80040F78;
extern u8 D_800406B8[];
s32 D_100097CC(s32, s32, void *);

ALDMAproc func_80009980(void *state) {
    if (D_80040F78.initialized == 0) {
        D_80040F78.field4 = 0;
        D_80040F78.base = D_800406B8;
        D_80040F78.initialized = 1;
    }
    *(void **)state = 0;
    return D_100097CC;
}
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8F90/func_800099BC.s")
typedef struct {
    u8 pad0[0x14];
    s8 count;
    u8 state;
    u8 field16;
} AudioBufferState;

void func_80009B2C(void *arg0) {
    if (((u32)arg0 & 1) == 0) {
        ((AudioBufferState *)arg0)->count--;
    }
}
void func_80009BE4(void *);

void func_80009B4C(void *arg0) {
    if (((u32)arg0 & 1) == 0) {
        ((AudioBufferState *)arg0)->count--;
        if (((AudioBufferState *)arg0)->count == 0) {
            func_80009BE4(arg0);
        }
    }
}
void func_80009B90(void *arg0) {
    if (((u32)arg0 & 1) == 0) {
        if (((AudioBufferState *)arg0)->state == 1) {
            if (((AudioBufferState *)arg0)->field16 == 1) {
                ((AudioBufferState *)arg0)->count++;
            }
            ((AudioBufferState *)arg0)->state = 2;
            return;
        }
        ((AudioBufferState *)arg0)->count++;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8F90/func_80009BE4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8F90/func_80009CBC.s")
typedef void *(*ConkerBankFetch)(void *, s32);

typedef struct {
    u8 initialized;
    u8 pad1[3];
    s32 field4;
    void *base;
    s32 fieldC;
    s32 field10;
} AudioBankManager;

extern AudioBankManager D_800406A0;
extern u8 D_80040AC8[];
void *D_10009CBC(void *, s32);

ConkerBankFetch func_80009FFC(void) {
    if (D_800406A0.initialized == 0) {
        D_800406A0.field4 = 0;
        D_800406A0.base = D_80040AC8;
        D_800406A0.fieldC = 0;
        D_800406A0.field10 = 0;
        D_800406A0.initialized = 1;
    }
    return D_10009CBC;
}
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8F90/func_8000A03C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8F90/func_8000A348.s")
