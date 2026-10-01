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
 * - func_8000CC54
 * - func_8000CDA0
 * - func_8000CEAC
 * - func_8000D2F8
 * - func_8000D758
 * - func_8000D96C
 * - func_8000DEC4
 * - func_8000DF68
 * - func_8000E17C
 * - func_8000E2F4
 * - func_8000E46C
 * - func_8000E588
 * - func_8000E7A0
 * - func_8000E934
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct SequenceRecordState {
    s32 index;
    s32 id;
    u8 pad8[8];
    struct SequenceRecordState *owner;
    u8 pad14[0xC];
    s32 field20;
    s32 field24;
    u8 pad28[4];
    s32 target;
    s32 current;
    u8 pad34[0x1A];
    s16 value;
    s16 duration;
    u8 pad52[6];
    s16 current58;
    s16 target5A;
    s16 duration5C;
    u8 pad5E[2];
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000B1FC CURRENT (1555) */
void *func_8000B1FC(s32 arg0) {
    SequenceRecordState **cursor;
    SequenceRecordState *record;
    SequenceRecordState *child;

    cursor = D_800417B0;
    do {
        record = *cursor;
        cursor++;
        if (record != 0 && arg0 == record->id) {
            return record;
        }
    } while ((u32)cursor < (u32)D_800417BC);
    cursor = D_800417B0;
    for (;;) {
        record = *cursor;
        cursor++;
        if (record != 0) {
            child = record->state;
            if (child != 0 && arg0 == child->id) {
                return child;
            }
        }
        if (cursor == D_800417BC) {
            return 0;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000B1FC */
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
void func_8000E40C(s32, s32);
extern u8 *D_800DBFF0;

s32 func_8000B830(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 flag;

    flag = *(s32 *)(D_800DBFF0 + 0x5F0) & 1;
    if (flag != 0 && arg0 == 0) {
        arg0 = 1;
        func_8000E40C(0x10, 0x3E8);
    } else if (flag == 0 && arg0 != 0) {
        arg0 = 0;
        func_8000E40C(0x10, 0x4650);
    }
    return arg0;
}
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
u8 func_80008A4C(s32, s32);
void func_850C851C(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000BC28 CURRENT (400) */
s32 func_8000BC28(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 value;
    u8 first;

    first = func_80008A4C(arg1, 0);
    value = func_80008A4C(arg1, 6) + first + 1;
    if (value >= 0x100) {
        value = 0xFF;
    } else if (value < 0x10) {
        value = 1;
    }
    if (value != arg0) {
        func_850C851C(value - 1);
        arg0 = value;
    }
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000BC28 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000BC28.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000BCBC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000BF60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000C350.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000C530.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000C7E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000C934.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000CA18.s")
void func_80011FA0(s32);
void func_80008790(s32, s32, s32, s32);
extern s32 D_800BE9F0;

s32 func_8000CAE4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 bit2;

    bit2 = arg0 & 2;
    arg0 &= 1;
    if (D_800BE9F0 == 0x42) {
        func_80011FA0(4);
        if (arg0 == 0) {
            arg0 = 1;
            func_8000E704(0x58, 1, 0xFFFF);
        }
    } else if (arg0 != 0) {
        func_8000E704(0x58, 0, 0xFFFF);
        func_8000E40C(0x58, 0x3E80);
        arg0 = 0;
    }
    if (bit2 == 0) {
        func_80008790((u8)arg1, 0x1000, 0, 1);
        bit2 = 2;
    }
    return bit2 | arg0;
}
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
void func_8000CBF0(s32 arg0, s32 arg1, s32 arg2) {
    SequenceRecordState **slot;
    SequenceRecordState *record;
    s32 i;

    for (i = 0; i != 3; i++) {
        if ((1 << i) & arg2) {
            slot = &D_800417B0[i];
            record = *slot;
            if (record != 0) {
                record->target5A = arg0;
                (*slot)->duration5C = arg1;
                if (arg1 == 0) {
                    (*slot)->current58 = arg0;
                }
            }
        }
    }
}
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
s32 func_8000B548(s32 (*)[]);
void func_8000DEC4(void);
void func_8000D96C(s32, s32, s32);

void func_8000DE1C(s32 arg0, s32 arg1) {
    s32 count;
    s32 i;
    s32 ids[3];
    s32 value;

    arg0 &= 0xFFF;
    if (arg0 == 0) {
        func_8000DEC4();
        count = func_8000B548(&ids);
        for (i = 0; i < count; i++) {
            value = ids[i];
            if (value > 0) {
                func_8000D96C(0, value, arg1);
            }
        }
    } else {
        func_8000D96C(0, arg0, arg1);
    }
}
s32 func_8000853C(s32);
extern SequenceRecordState D_800419A8[];
extern u8 D_80041E58[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000DEC4 CURRENT (55) */
void func_8000DEC4(void) {
    SequenceRecordState *record;
    s32 index;

    record = D_800419A8;
    do {
        index = record->index;
        if (index == -1) {
            if (record->id != -1) {
                record->id = -1;
            }
        } else if (func_8000853C(index & 0xFF) == 0) {
            D_800417B0[record->index] = 0;
            record->index = -1;
            record->id = -1;
        }
        record++;
        record[-1].state = 0;
    } while ((u8 *)record != D_80041E58);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000DEC4 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000DEC4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000DF68.s")
s32 *func_8000B1B0(s32);
void func_800084D8(s32);
void func_80008F58(s32);
void func_8000CC54(s32);

void func_8000E054(s32 arg0, s32 arg1) {
    SequenceRecordState *record;

    record = (SequenceRecordState *)func_8000B1B0(arg0);
    if (record != 0) {
        if (record->pad14[1] == 2 && arg1 == 0) {
            func_800084D8(((u8 *)record)[3]);
            record->pad14[1] = 0;
            record->current = -1;
            func_8000CC54(record->index);
            return;
        }
        if (record->pad14[1] != 2 && arg1 != 0) {
            if (record->pad14[1] != 1) {
                func_80008F58(((u8 *)record)[3]);
            }
            record->pad14[1] = 2;
        }
    }
}
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
void func_80008C6C(s32, s32);

s32 func_8000E654(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    SequenceRecordState *record;
    SequenceRecordState *owner;

    record = func_8000B1FC(arg0);
    owner = 0;
    if (arg3 >= 0) {
        owner = func_8000B1FC(arg3);
    }
    if (record != 0) {
        if (arg2 == 0 && record->index >= 0) {
            func_80008C6C(record->index & 0xFF, (arg1 - 1) & 0xFF);
            return 1;
        }
        record->field24 = arg1;
        record->field20 = arg2;
        if (owner != 0) {
            record->owner = owner;
        }
        return 1;
    }
    return 0;
}
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

u16 func_8000EA94(s32 arg0) {
    u16 selection;

    if (arg0 == 0) {
        selection = 0x52;
    } else if (arg0 == 2) {
        selection = 0x51;
    } else if (arg0 == 1) {
        selection = 0x53;
    }
    func_8000D96C(selection, 0, 0);
    return selection;
}
