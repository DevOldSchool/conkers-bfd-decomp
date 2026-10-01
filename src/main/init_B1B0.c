#include "types.h"

/*
 * Reviewed source unit: src/main/init_B1B0.c
 * Boundary evidence: docs/evidence/main_audio_driver_sequence_boundaries.md
 *
 * TODO: Implement these source-unit functions:
 * - func_8000B1B0
 * - func_8000B1FC
 * - func_8000B294
 * - func_8000B2F4
 * - func_8000B3D4
 * - func_8000B548
 * - func_8000B638
 * - func_8000B830
 * - func_8000B8B8
 * - func_8000BA18
 * - func_8000BAFC
 * - func_8000BC28
 * - func_8000BCBC
 * - func_8000BF60
 * - func_8000C350
 * - func_8000C530
 * - func_8000C7E8
 * - func_8000C934
 * - func_8000CA18
 * - func_8000CAE4
 * - func_8000CBA8
 * - func_8000CBF0
 * - func_8000CC54
 * - func_8000CD40
 * - func_8000CDA0
 * - func_8000CEAC
 * - func_8000D2F8
 * - func_8000D758
 * - func_8000D96C
 * - func_8000DE1C
 * - func_8000DEC4
 * - func_8000DF68
 * - func_8000E054
 * - func_8000E134
 * - func_8000E17C
 * - func_8000E2F4
 * - func_8000E40C
 * - func_8000E46C
 * - func_8000E588
 * - func_8000E654
 * - func_8000E704
 * - func_8000E7A0
 * - func_8000E934
 * - func_8000EA94
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000B1B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000B1FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000B294.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000B2F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000B3D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000B548.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000B638.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000B830.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000B8B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000BA18.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000BAFC.s")
s32 func_8000E704(s32, s32, s32);

s32 func_8000BBE8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg0 == 0) {
        func_8000E704(0x14, 1, 0xFFFF);
        arg0 = 1;
    }
    return arg0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000BC28.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000BCBC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000BF60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000C350.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000C530.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000C7E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000C934.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000CA18.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000CAE4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000CBA8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000CBF0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000CC54.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000CD40.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000CDA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000CEAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000D2F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000D758.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000D96C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000DE1C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000DEC4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000DF68.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000E054.s")
typedef struct {
    u8 pad0[0x60];
    s32 state;
} SequenceRecordState;

void *func_8000B1FC(s32);

s32 func_8000E0F8(s32 arg0) {
    SequenceRecordState *record;

    arg0 &= 0xFFF;
    record = func_8000B1FC(arg0);
    if (record != 0 && record->state == 0) {
        return 1;
    }
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000E134.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000E17C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000E2F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000E40C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000E46C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000E588.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000E654.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000E704.s")
extern s32 D_8002B070;

void func_8000E75C(s32 arg0) {
    D_8002B070 = arg0 >> 1;
}
extern s32 D_80041F04;
extern s32 D_80041F08;
extern s32 D_80041F0C;

s32 func_8000E770(s32 *arg0, s32 *arg1) {
    if (arg0 != 0) {
        *arg0 = D_80041F08;
    }
    if (arg1 != 0) {
        *arg1 = D_80041F0C;
    }
    return D_80041F04;
}
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000E7A0.s")
void func_8000E8C4(s32 arg0) {
    if ((arg0 & 1) == 1) {
        D_80041F04 &= ~1;
    }
}
s32 *func_8000B1B0(s32);
extern u8 D_800418AC[];

s32 func_8000E8F0(s32 arg0) {
    s32 *record;

    record = func_8000B1B0(arg0);
    if (record != 0 && *record >= 0) {
        return D_800418AC[*record];
    }
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000E934.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000EA94.s")
