#include "types.h"

/*
 * Reviewed source unit: src/main/init_EB00.c
 * Boundary evidence: docs/evidence/main_sound_record_family_boundary.md
 *
 * TODO: Implement these source-unit functions:
 * - func_8000EB00
 * - func_8000EBC4
 * - func_8000EC24
 * - func_8000ECCC
 * - func_8000EDA0
 * - func_8000EE70
 * - func_8000EF40
 * - func_8000EFB4
 * - func_8000F1A8
 * - func_8000F248
 * - func_8000F3D0
 * - func_8000F44C
 * - func_8000F4D8
 * - func_8000F568
 * - func_8000F6B8
 * - func_8000F85C
 * - func_8000F91C
 * - func_8000F9D4
 * - func_8000FA64
 * - func_8000FC18
 * - func_8000FD38
 * - func_8000FDF4
 * - func_8000FE88
 * - func_8000FEF0
 * - func_8000FF90
 * - func_8001001C
 * - func_800100E0
 * - func_80010154
 * - func_80010344
 * - func_80010558
 * - func_80010630
 * - func_80010720
 * - func_800107F8
 * - func_80010894
 * - func_8001091C
 * - func_800109D0
 * - func_80010A3C
 * - func_80010AA8
 * - func_80010BE8
 * - func_80010E78
 * - func_80010F30
 * - func_80010F88
 * - func_80010FFC
 * - func_800111C8
 * - func_8001123C
 * - func_80011310
 * - func_800114D0
 * - func_80011624
 * - func_80011BB8
 * - func_80011EB8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000EB00.s")
typedef struct {
    u8 pad0[0xC];
    s32 value;
    u8 pad10[8];
    s32 timer;
} SoundDecayState;

extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000EBC4 CURRENT (125) */
s32 func_8000EBC4(SoundDecayState *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 value;
    s32 timer;

    timer = arg0->timer - D_800BE9E4;
    value = arg0->value;
    if (timer <= 0) {
        value -= D_800BE9E4 * 1000;
        if (value < 0) {
            return 1;
        }
        arg0->value = value;
    }
    arg0->timer = timer;
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000EBC4 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000EBC4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000EC24.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000ECCC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000EDA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000EE70.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000EF40.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000EFB4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000F1A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000F248.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000F3D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000F44C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000F4D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000F568.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000F6B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000F85C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000F91C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000F9D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000FA64.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000FC18.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000FD38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000FDF4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000FE88.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000FEF0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000FF90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8001001C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_800100E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80010154.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80010344.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80010558.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80010630.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80010720.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_800107F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80010894.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8001091C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_800109D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80010A3C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80010AA8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80010BE8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80010E78.s")
s32 func_80010BE8(s32, s32, s32, s32, s32, s32, s32);
extern u8 D_80041FD9;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80010F30 CURRENT (248) */
s32 func_80010F30(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    return func_80010BE8(0, arg0, (u16)arg1, (u8)arg2,
                        (s16)arg3, (u8)arg4, D_80041FD9);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80010F30 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80010F30.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80010F88.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80010FFC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_800111C8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8001123C.s")
typedef struct {
    s16 value;
    s8 operation;
    s8 index;
} SoundQueueEntry;

extern SoundQueueEntry D_80041F10[16];
extern s32 D_80041F50;

s32 func_800112BC(s32 arg0, s32 arg1) {
    SoundQueueEntry *entry;
    s32 count = D_80041F50;

    if (count < 0x10) {
        entry = &D_80041F10[count];
        entry->value = arg0;
        entry->operation = arg1;
        entry->index = arg0 & 0xF;
        D_80041F50 = count + 1;
        return 1;
    }
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80011310.s")
typedef struct {
    u16 id;
    u8 pad2[2];
    u16 value;
    u8 pad6[6];
} SoundHandleEntry;

extern SoundHandleEntry D_800425E0[];

s32 func_8001147C(u16 arg0) {
    SoundHandleEntry *entry;

    if (arg0 != 0) {
        entry = &D_800425E0[arg0 & 0xF];
        if (entry->id == arg0) {
            return entry->value & 0x7FFF;
        }
    }
    return -1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_800114D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80011624.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80011BB8.s")
void func_80011E88(s32 arg0) {
}

extern s8 D_80041F61;

void func_80011E94(s32 arg0) {
    if (arg0 != 0) {
        D_80041F61 = 1;
        return;
    }
    D_80041F61 = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80011EB8.s")
