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
 * - func_8000CBF0
 * - func_8000CC54
 * - func_8000CDA0
 * - func_8000CEAC
 * - func_8000D2F8
 * - func_8000D758
 * - func_8000D96C
 * - func_8000DE1C
 * - func_8000DEC4
 * - func_8000DF68
 * - func_8000E054
 * - func_8000E17C
 * - func_8000E2F4
 * - func_8000E46C
 * - func_8000E588
 * - func_8000E654
 * - func_8000E7A0
 * - func_8000E934
 * - func_8000EA94
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct SequenceRecordState {
    s32 index;
    s32 id;
    u8 pad8[8];
    struct SequenceRecordState *owner;
    u8 pad14[0x18];
    s32 target;
    s32 current;
    u8 pad34[0x1A];
    s16 value;
    s16 duration;
    u8 pad52[0xE];
    struct SequenceRecordState *state;
} SequenceRecordState;

extern SequenceRecordState *D_800417B0[];
extern SequenceRecordState *D_800417BC[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000B1B0 CURRENT (290) */
s32 *func_8000B1B0(s32 arg0) {
    SequenceRecordState **cursor;
    SequenceRecordState *record;

    cursor = D_800417B0;
    for (;;) {
        record = *cursor;
        cursor++;
        if (record != 0 && arg0 == record->id) {
            return (s32 *)record;
        }
        if (cursor == D_800417BC) {
            return 0;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000B1B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000B1B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000B1FC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000B294 CURRENT (140) */
void func_8000B294(SequenceRecordState *arg0) {
    SequenceRecordState **cursor;
    SequenceRecordState *child;

    cursor = D_800417B0;
    for (;;) {
        if (*cursor != 0) {
            if (arg0 == (*cursor)->owner) {
                (*cursor)->owner = *cursor;
            }
            child = (*cursor)->state;
            if (child != 0 && arg0 == child->owner) {
                child->owner = child;
            }
        }
        cursor++;
        if (cursor == D_800417BC) {
            return;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000B294 */
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
void func_8000CBA8(s32 arg0) {
    if (D_800417B0[0] != 0) {
        D_800417B0[0]->value = arg0;
        D_800417B0[0]->duration = 0x500;
    }
    if (D_800417B0[1] != 0) {
        D_800417B0[1]->value = arg0;
        D_800417B0[1]->duration = 0x500;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000CBF0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000CC54.s")
extern s32 D_800BE9E4;

s32 func_8000CD40(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 != arg0) {
        arg2 *= D_800BE9E4;
        if (arg0 < arg1) {
            arg0 += arg2;
            if (arg1 < arg0) {
                arg0 = arg1;
            }
        } else {
            arg0 -= arg2;
            if (arg0 < arg1 || arg0 < 0) {
                arg0 = arg1;
            }
        }
    }
    return arg0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000CDA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000CEAC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000D2F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000D758.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000D96C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000DE1C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000DEC4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000DF68.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000E054.s")
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
typedef struct {
    s32 flags;
    u8 pad4[0xC];
} SequenceModeEntry;

extern SequenceModeEntry D_8002B078[];

s32 func_8000E134(s32 arg0) {
    s32 mode;

    if (arg0 < 0x96) {
        mode = D_8002B078[arg0].flags & ~0xF0;
        if (mode == 1 || mode == 3) {
            return 1;
        }
    }
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000E17C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000E2F4.s")
void func_8000E40C(s32 arg0, s32 arg1) {
    SequenceRecordState *record;

    if (arg1 >= 0x8000) {
        arg1 = 0x7FFF;
    } else if (arg1 < 0) {
        arg1 = 0;
    }
    record = func_8000B1FC(arg0);
    if (record != 0) {
        if (record->index < 0) {
            record->current = arg1;
        }
        record->target = arg1;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000E46C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000E588.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000E654.s")
s32 *func_8000B1B0(s32);
void func_80008A94(s32, s32, s32);

s32 func_8000E704(s32 arg0, s32 arg1, s32 arg2) {
    s32 *record;

    record = func_8000B1B0(arg0);
    if (record != 0 && *record >= 0) {
        func_80008A94(((u8 *)record)[3], arg2, arg1);
        return 1;
    }
    return 0;
}
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
