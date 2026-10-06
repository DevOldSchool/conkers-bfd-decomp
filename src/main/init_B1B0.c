#include "types.h"

/*
 * Reviewed source unit: src/main/init_B1B0.c
 * Boundary evidence: docs/evidence/main_audio_driver_sequence_boundaries.md
 *
 * TODO: Implement these source-unit functions:
 * - func_8000BCBC
 * - func_8000C350
 * - func_8000C530
 * - func_8000C7E8
 * - func_8000C934
 * - func_8000CEAC
 * - func_8000D2F8
 * - func_8000D96C
 * - func_8000DF68
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct SequenceRecordState {
    s32 index;
    s32 id;
    void *field8;
    void *fieldC;
    struct SequenceRecordState *owner;
    u8 ownerSync;
    u8 pauseMode;
    u8 pad16[2];
    s32 startMask;
    s32 fadeMask;
    s32 field20;
    s32 field24;
    s32 volumeOverride;
    s32 target;
    s32 current;
    s32 callbackState;
    s32 flags38;
    u8 pad3C[0x10];
    u16 current4C;
    u16 value;
    s16 duration;
    u16 current52;
    u16 target54;
    s16 duration56;
    u16 current58;
    u16 target5A;
    s16 duration5C;
    u8 pad5E[2];
    struct SequenceRecordState *state;
} SequenceRecordState;

extern SequenceRecordState *D_800417B0[];
extern SequenceRecordState *D_800417BC[];

s32 *func_8000B1B0(s32 arg0) {
    s32 index;

    index = 0;
    for (;;) {
        if (D_800417B0[index] != 0 && arg0 == D_800417B0[index]->id) {
            return (s32 *)D_800417B0[index];
        }
        index++;
        if (D_800417BC == &D_800417B0[index]) {
            return 0;
        }
    }
}
void *func_8000B1FC(s32 arg0) {
    s32 index;
    SequenceRecordState *child;

    index = 0;
    do {
        if (D_800417B0[index] != 0 && arg0 == D_800417B0[index]->id) {
            return D_800417B0[index];
        }
        index++;
    } while (index < 3);
    index = 0;
    for (;;) {
        if (D_800417B0[index] != 0) {
            child = D_800417B0[index]->state;
            if (child != 0 && arg0 == child->id) {
                return child;
            }
        }
        index++;
        if (D_800417BC == &D_800417B0[index]) {
            return 0;
        }
    }
}
void func_8000B294(SequenceRecordState *arg0) {
    s32 index;
    SequenceRecordState *child;

    index = 0;
    for (;;) {
        if (D_800417B0[index] != 0) {
            if (arg0 == D_800417B0[index]->owner) {
                D_800417B0[index]->owner = D_800417B0[index];
            }
            child = D_800417B0[index]->state;
            if (child != 0 && arg0 == child->owner) {
                child->owner = child;
            }
        }
        index++;
        if (D_800417BC == &D_800417B0[index]) {
            return;
        }
    }
}
typedef s32 (*SequenceCallback)(s32, s32, f32, f32, f32);

typedef struct {
    u16 volume;
    u8 pad2[2];
    s32 flags;
    SequenceCallback callback;
    u8 markerCount;
    u8 padD[3];
} SequenceVolumeEntry;

extern SequenceVolumeEntry D_8002B074[];
extern u8 D_8002B9D4[];
extern u8 D_8002B9F4[];
extern SequenceRecordState D_800419A8[];
extern u8 D_80041E58[];
void func_800226F0(void *, s32);

SequenceRecordState *func_8000B2F4(s32 arg0) {
    s32 index;

    index = 0;
    for (;;) {
        if (D_800419A8[index].id == -1) {
            func_800226F0(&D_800419A8[index], 0x64);
            D_800419A8[index].index = -1;
            if (arg0 < 0x96) {
                D_800419A8[index].target = D_8002B074[arg0].volume;
            } else {
                D_800419A8[index].target = 0x6590;
            }
            D_800419A8[index].current = D_800419A8[index].target;
            D_800419A8[index].value = D_800419A8[index].current4C = D_800419A8[index].current52 =
                D_800419A8[index].target54 = D_800419A8[index].current58 = D_800419A8[index].target5A = 0x8000;
            D_800419A8[index].id = arg0;
            D_800419A8[index].field8 = D_8002B9D4;
            D_800419A8[index].fieldC = D_8002B9F4;
            D_800419A8[index].owner = &D_800419A8[index];
            return &D_800419A8[index];
        }
        index++;
        if ((SequenceRecordState *)D_80041E58 == &D_800419A8[index]) {
            return 0;
        }
    }
}
SequenceRecordState *func_8000B2F4(s32);
void func_8000B294(SequenceRecordState *);

void func_8000B3D4(SequenceRecordState *arg0, SequenceRecordState *arg1) {
    SequenceRecordState *found;
    SequenceRecordState **slot;
    SequenceRecordState *record;
    s32 i;

    found = 0;
    i = 0;
    if (((SequenceRecordState **)&arg1)[0] != 0) {
        record = ((SequenceRecordState **)&arg1)[0]->state;
        if (record != 0 && arg0 != record) {
            if (record->id == arg0->id) {
                arg0->id = -1;
                return;
            }
            record->id = -1;
        }
        ((SequenceRecordState **)&arg1)[0]->state = arg0;
        return;
    }
    do {
        if (found == 0 && ((slot = &D_800417B0[i], record = *slot) == 0 ||
                          (record->id <= 0 && record->state == 0))) {
            found = func_8000B2F4(0);
            if (found != 0) {
                found->index = i;
                found->state = arg0;
                *slot = found;
            } else {
                arg0->id = -1;
                return;
            }
        } else if (found == 0) {
            slot = &D_800417B0[i];
            record = *slot;
            if (record != 0 && record->state != 0 && record->state->id == 0) {
                found = (SequenceRecordState *)-1;
                func_8000B294(record->state);
                (*slot)->state->id = -1;
                (*slot)->state->index = -1;
                (*slot)->state = arg0;
            }
        }
        i++;
    } while (i != 3);
}
s32 func_8000B548(s32 (*arg0)[]) {
    s32 count;
    s32 index;

    count = 0;
    for (index = 0; index < 12; index++) {
        if (D_800419A8[index].id != -1 && D_800419A8[index].index != -1 && count < 3) {
            (*arg0)[0] = D_800419A8[index].id;
            arg0 = (s32 (*)[])(*arg0 + 1);
            count++;
        }
    }
    return count;
}
extern s32 D_80041F04;
extern s32 D_800BE9F0;
void func_800085B8(s32, s32, s32);
void func_800088F0(s32, s32, s32);
void func_80008790(u8, s32, u8, s32);
void func_80011FA0(s32);
s32 func_8000E704(s32, s32, s32);

s32 func_8000B638(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 bit2;
    SequenceRecordState *record;

    bit2 = arg0 & 2;
    arg0 &= 1;
    record = D_800417B0[(u8)arg1];
    if (record == 0 || record->current < 0x1F4) {
        D_80041F04 &= ~1;
    }
    if (D_80041F04 & 1) {
        if (arg0 == 0) {
            func_800088F0(((u8 *)&arg1)[3], 0x8000, 1);
            if (D_800BE9F0 == 1 || D_800BE9F0 == 0xC) {
                func_80008790(((u8 *)&arg1)[3], 0x7000, 0, 0);
            } else if (D_800BE9F0 != 7) {
                func_80008790(((u8 *)&arg1)[3], 0xCA, 0, 0);
            }
            func_800085B8(((u8 *)&arg1)[3], 0xF, 1);
        }
        arg0 = 1;
    } else if (arg0 != 0) {
        func_800088F0(((u8 *)&arg1)[3], 0x8000, 0);
        if (D_800BE9F0 == 1 || D_800BE9F0 == 0xC) {
            func_80008790(((u8 *)&arg1)[3], 0x7000, 0xFF, 0);
        } else if (D_800BE9F0 != 7) {
            func_80008790(((u8 *)&arg1)[3], 0xCA, 0xFF, 0);
        }
        func_800085B8(((u8 *)&arg1)[3], 0xF, 0);
        arg0 = 0;
    }
    if (D_800BE9F0 == 0x27) {
        func_80011FA0(4);
        if (bit2 == 0) {
            bit2 = 2;
            func_8000E704(1, 1, 0xFFFF);
        }
    } else if (bit2 != 0) {
        func_8000E704(1, 0, 0xFFFF);
        bit2 = 0;
    }
    return bit2 | arg0;
}
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
extern s32 D_800BE9F0;
extern s32 D_80041F08;
extern s32 D_80041F0C;
s32 func_8000C530(s32, u8, f32, f32, f32);
s32 func_8000E46C(s32, s32, s32, s32);
s32 func_8000E588(s32, s32, s32);
void func_8000DF68(s32, s32, s32);

s32 func_8000B8B8(s32 arg0, u8 arg1, f32 arg2, f32 arg3, f32 arg4) {
    s32 volume;

    if (D_800BE9F0 == 4) {
        if ((arg0 & 1) && D_80041F0C == 0) {
            func_8000E46C(0x13, 0, 0x1000, 0);
            arg0 &= ~1;
        } else if (D_80041F0C != 0) {
            volume = D_80041F08 / D_80041F0C / 80;
            if (volume >= 0x65) {
                volume = 0x64;
            }
            func_8000E588(0x13, volume, 0x1000);
            arg0 |= 1;
        }
        D_80041F08 = 0;
        D_80041F0C = 0;
        if (!(arg0 & 2)) {
            func_8000DF68(0x13, 0, 1);
            func_8000DF68(0x13, 0x8000, 0);
            arg0 |= 2;
        }
        return arg0;
    }
    return func_8000C530(arg0, arg1, arg2, arg3, arg4);
}
s32 func_8000E588(s32, s32, s32);
s32 func_8000C530(s32, u8, f32, f32, f32);
s32 func_800114D0(s32, s32, s32, s32, s32, s32, s32 *, s32 *, s32 *);

s32 func_8000BA18(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    s32 volume;
    s32 pan;
    s32 state;

    state = arg0 & 0xFFFFFF;
    arg0 &= 0xFF000000;
    volume = 0;
    func_800114D0(0, -0x179, 0x2023, 0x7FFF, 0xFA0, 0xBB8,
                  &pan, &volume, 0);
    volume = (volume << 16) & 0xFF000000;
    if (arg0 != volume) {
        arg0 = volume;
        func_8000E588(0x4D, (u32)volume >> 24, 0x6000);
    }
    state = func_8000C530(state, (u8)arg1, arg2, arg3, arg4);
    state &= 0xFFFFFF;
    arg0 |= state;
    return arg0;
}
s32 func_8000BAFC(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    s32 volume;
    s32 pan;
    s32 state;

    state = arg0 & 0xFFFFFF;
    arg0 &= 0xFF000000;
    volume = 0;
    func_800114D0(0, 0, 0, 0x7FF8, 0xE74, 0xA28, &pan, &volume, 0);
    volume = ((0x7FFF - volume) << 16) & 0xFF000000;
    if (arg0 != volume) {
        arg0 = volume;
        func_8000E588(0x93, (u32)volume >> 24, 0x6000);
    }
    state = func_8000C530(state, (u8)arg1, arg2, arg3, arg4);
    state &= 0xFFFFFF;
    arg0 |= state;
    return arg0;
}
s32 func_8000E704(s32, s32, s32);

s32 func_8000BBE8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg0 == 0) {
        func_8000E704(0x14, 1, 0xFFFF);
        arg0 = 1;
    }
    return arg0;
}
u8 func_80008A4C(u8, u8);
void func_850C851C(s32);

s32 func_8000BC28(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 value;
    u8 first;

    first = func_80008A4C(((u8 *)&arg1)[3], 0);
    value = func_80008A4C(((u8 *)&arg1)[3], 6) + first + 1;
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
extern f32 D_8002C220;
extern f32 D_8002C224;
extern f32 D_8002C228;
extern f32 D_8002C22C;
extern f32 D_8002C230;
extern f32 D_8002C234;
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
s32 func_850A29C8(s32, s32);
void func_80008790(u8, s32, u8, s32);
void func_8000886C(u8, s32, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000BCBC CURRENT (10) */
s32 func_8000BCBC(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 distance;
    u8 volume;

    if (arg0 == 0) {
        func_80008790(((u8 *)&arg1)[3], 3, 0x10, 0);
        func_8000886C(((u8 *)&arg1)[3], 4, 0);
        arg0 = 1;
    } else if (D_800BE9F0 == 0x13) {
        arg2 -= 24.0f;
        arg4 -= 3015.0f;
        distance = arg2 * arg2 + arg4 * arg4;
        if (36000000.0f < distance) {
            volume = 4;
        } else {
            volume = (u8)((6000.0f - sqrtf(distance)) * 0.041833334f) + 4;
        }
        if (arg0 != volume) {
            func_8000886C(((u8 *)&arg1)[3], 3, volume);
        }
        if (func_850A29C8(0, 0x4041) == 0) {
            distance = 1290.0f - arg3;
            if (1290.0f < arg3) {
                volume = 0x20;
            } else {
                distance *= 0.37166667f;
                if (distance >= 223.0f) {
                    volume = 0xFF;
                } else {
                    volume = (u8)distance + 0x20;
                }
            }
        } else {
            volume = 0;
        }
        if (volume != func_80008A4C(((u8 *)&arg1)[3], 2)) {
            func_8000886C(((u8 *)&arg1)[3], 4, volume);
        }
    }
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000BCBC */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000BCBC.s")
extern u8 D_800C35EA;
extern s32 D_800BE9E4;
void func_800086FC(u8, u8, u8);
void func_80008744(u8, u8, u8);
void func_8000886C(u8, s32, u8);
void func_80008F24(u8);
void func_80011FA0(s32);

s32 func_8000BF60(u32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 mode;
    s32 countdown;
    u32 packed;
    s32 initialized;
    s32 volume;
    s32 pan;
    u32 level;
    s32 volumeChanged;
    s32 panChanged;

    initialized = 0;
    mode = arg0 & 3;
    packed = arg0 >> 8;
    if (!(arg0 & 0x80)) {
        func_8000E40C(0x22, 0x5DC0);
        if (D_800C35EA == 1) {
            func_8000DF68(0x22, 0x14, 1);
        }
        arg0 = 0x80;
        initialized = 1;
    }
    if (D_800BE9F0 != 0x1D) {
        func_80008F24(((u8 *)&arg1)[3]);
        return arg0;
    }
    volumeChanged = 0;
    panChanged = 0;
    func_800114D0(-0x15F, 0, 0x197, 0x7FFF, 0xBB8, 0x12C, &pan, &volume, 0);
    if ((u32)volume < 0x4000) {
        volume = 0x40;
    } else {
        volume = (u32)volume >> 8;
    }
    level = packed >> 8;
    if (volume != level) {
        volumeChanged = 1;
        func_8000886C(((u8 *)&arg1)[3], 6, volume);
    }
    if (pan != (packed & 0xFF)) {
        panChanged = 1;
        func_80008744(((u8 *)&arg1)[3], 1, pan & 0x7F);
        func_80008744(((u8 *)&arg1)[3], 2, pan & 0x7F);
        func_800086FC(((u8 *)&arg1)[3], 1, (u32)pan >> 7);
        func_800086FC(((u8 *)&arg1)[3], 2, (u32)pan >> 7);
    }
    packed = (pan << 8) | (volume << 16);
    func_800114D0(-0x40, 0, 0x21F, 0x7FFF, 0xBB8, 0x12C, &pan, &volume, 0);
    if (volumeChanged != 0) {
        if ((u32)volume < 0x4000) {
            volume = 0x4000;
        }
        func_8000886C(((u8 *)&arg1)[3], 1, (u8)((u32)volume >> 8));
    }
    if (panChanged != 0) {
        func_80008744(((u8 *)&arg1)[3], 0, 0x40);
        func_800086FC(((u8 *)&arg1)[3], 0, 0);
    }
    func_800114D0(-0x126, 0, 0x290, 0x7FFF, 0xBB8, 0x12C, &pan, &volume, 0);
    if (volumeChanged != 0) {
        if ((u32)volume < 0x4000) {
            volume = 0x4000;
        }
        func_8000886C(((u8 *)&arg1)[3], 0x18, (u8)((u32)volume >> 8));
    }
    if (panChanged != 0) {
        func_80008744(((u8 *)&arg1)[3], 3, pan & 0x7F);
        func_80008744(((u8 *)&arg1)[3], 4, pan & 0x7F);
        func_800086FC(((u8 *)&arg1)[3], 3, (u32)pan >> 7);
        func_800086FC(((u8 *)&arg1)[3], 4, (u32)pan >> 7);
    }
    if (mode != D_80041F08) {
        switch (D_80041F08) {
        case 1:
            countdown = arg0 & 0x7C;
            if (countdown != 0) {
                countdown -= (D_800BE9E4 >> 1) * 4;
                if (countdown <= 0) {
                    func_8000E704(0x22, 0, 0xFFFF);
                    arg0 = 0x81;
                } else {
                    arg0 = countdown | 0x80;
                }
            }
            func_8000E46C(0x22, 0x64, 0xFE0, 0);
            break;
        case 2:
            arg0 = 0xF8;
            func_80011FA0(4);
            func_8000E704(0x22, 1, 0xFFFF);
            func_8000E46C(0x22, 0, 0xFE0, initialized);
            break;
        }
    }
    return arg0 | packed;
}
extern u8 D_800C35E8;
extern u8 D_800C35EA;
void func_85178EFC(s32);
void func_80008790(u8, s32, u8, s32);
void func_8000886C(u8, s32, u8);
void func_80008F24(u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000C350 CURRENT (10) */
s32 func_8000C350(s32 arg0, u8 arg1, s32 arg2, s32 arg3) {
    if (!(arg0 & 0x80)) {
        arg0 |= 0x80;
        if (D_800C35EA != 1) {
            func_8000886C(arg1, 0x1E, 1);
            func_8000886C(arg1, 1, 1);
            func_8000E40C(0x23, 0x61A8);
        } else if (D_800C35E8 == 3) {
            func_8000E40C(0x23, 0xFA);
            func_85178EFC(2);
        } else if (D_800C35E8 == 6) {
            func_8000886C(arg1, 0x1E, 1);
            func_8000886C(arg1, 1, 0x40);
            func_85178EFC(2);
        } else {
            func_8000E40C(0x23, 0x61A8);
        }
        return arg0;
    }
    if (D_800BE9F0 != 0x1D) {
        func_80008F24(arg1);
    } else if ((arg0 & 0x7F) != D_80041F08) {
        switch (D_80041F08) {
        case 1:
            func_80008790(arg1, 0x1E, 0, 0);
            func_80008790(arg1, 1, 0x40, 0);
            break;
        case 2:
            func_80008790(arg1, 0x18, 0xFF, 0);
            func_80008790(arg1, 6, 0, 0);
            func_80008790(arg1, 1, 1, 0);
            break;
        }
        arg0 = D_80041F08 | 0x80;
    }
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000C350 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000C350.s")
extern s32 D_800BE9E4;
void func_800085F8(u8, s32);
void func_800086FC(u8, u8, u8);
void func_80008744(u8, u8, u8);
void func_80008824(u8, u8, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000C530 CURRENT (48) */
s32 func_8000C530(s32 arg0, u8 arg1, f32 arg2, f32 arg3, f32 arg4) {
    s32 oldMode;
    s32 mode;
    s32 countdown;
    u32 upper;
    s32 oldLow;
    u32 fade;
    s32 low;
    s32 high;
    s32 oldHigh;
    u8 channel;

    upper = (u32)arg0 >> 8;
    mode = oldMode = arg0 & 3;
    countdown = ((u32)arg0 >> 2) & 0x3F;
    fade = arg0 & 0xFF000000;
    oldHigh = ((u32)arg0 >> 16) & 0xFF;
    oldLow = upper & 0xFF;
    low = oldLow;
    high = oldHigh;
    if (D_80041F08 != 0 &&
        (oldMode != 2 || countdown == 0 || D_80041F08 == 2)) {
        mode = D_80041F08;
        low = D_80041F0C & 0xFF;
        high = D_80041F0C >> 8;
        countdown = 0x1E;
    }
    if (countdown != 0) {
        countdown -= D_800BE9E4;
        if (countdown <= 0) {
            countdown = 0;
            mode = 0;
        }
    }
    if (mode != oldMode) {
        if (oldMode != 0) {
            func_800085F8(((u8 *)&arg1)[0], oldMode + 9);
        }
        if (mode != 0) {
            channel = (u8)(mode + 9);
            func_80008824(((u8 *)&arg1)[0], channel, (u8)low);
            func_800086FC(((u8 *)&arg1)[0], channel, (u8)(high >> 7));
            func_80008744(((u8 *)&arg1)[0], channel, high & 0x7F);
        }
    } else if (oldMode != 0 && D_80041F08 != 0 && upper != D_80041F0C) {
        if (low != oldLow) {
            func_80008824(((u8 *)&arg1)[0], (u8)(oldMode + 9), (u8)low);
        }
        if (high != oldHigh) {
            if ((high ^ oldHigh) & 0x80) {
                func_800086FC(((u8 *)&arg1)[0], (u8)(mode + 9), (u8)(high >> 7));
            }
            func_80008744(((u8 *)&arg1)[0], (u8)(mode + 9), high & 0x7F);
        }
    }
    if (D_80041F04 & 0x10) {
        D_80041F04 &= ~0x10;
        if (fade == 0) {
            func_8000886C(((u8 *)&arg1)[0], 0xC0, 0x80);
        }
        fade = 0xFF000000;
    }
    if (fade != 0) {
        upper = ((u32)D_800BE9E4 << 23) & 0xFF000000;
        if (upper < fade) {
            fade -= upper;
        } else {
            func_80008790(((u8 *)&arg1)[0], 0xC0, 0, 0x5A);
            fade = 0;
        }
    }
    D_80041F08 = 0;
    return (countdown * 4) | mode | (low << 8) | (high << 16) | fade;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000C530 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000C530.s")
extern s32 D_8002B070;
extern s32 D_800BE9F0;
extern f32 D_8002C238;
f32 sqrtf(f32);
s32 *func_8000B1B0(s32);
void func_8000D96C(s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000C7E8 CURRENT (50) */
s32 func_8000C7E8(s32 arg0, s32 arg1, f32 arg2, s32 arg3, f32 arg4) {
    f32 distance;
    f32 value;

    if (D_800BE9F0 == 0x31) {
        if (arg0 != 2) {
            if (func_8000B1B0(9) == 0) {
                func_8000E704(0x3E, 0, 0xFFFF);
                func_8000E40C(0x3E, 0x7FFF);
                func_8000D96C(0x3D, 0x3E, 4);
            }
            return 2;
        }
        return 0;
    }
    if (D_8002B070 == 0) {
        D_8002B070 = 1;
    }
    if (arg0 != D_8002B070) {
        arg0 = D_8002B070;
    }
    arg2 -= -4000.0f;
    distance = 24000.0f - sqrtf(arg2 * arg2 + arg4 * arg4) * 10.0f;
    value = distance;
    if (distance < 100.0f) {
        value = 100.0f;
    } else if (24000.0f < distance) {
        value = 24000.0f;
    }
    func_8000E40C(0x3E, (s32)value);
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000C7E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000C7E8.s")
extern s32 D_800BE9F0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000C934 CURRENT (24) */
s32 func_8000C934(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 output[1];
    s32 maximum;
    s32 flag;
    s32 value;

    output[0] = 0;
    flag = *(s32 *)(D_800DBFF0 + 0x5F0) & 1;
    if (flag != 0) {
        maximum = 0x7FFF;
    } else {
        maximum = 0x2EE0;
    }
    if (D_800BE9F0 == 0x37 && flag == 0) {
        func_800114D0(0x898, 0x42A, -0x640, maximum,
                      0xBB8, 0x5DC, 0, output, 0);
        value = output[0];
        value = maximum - (value & 0xFF00);
        output[0] = value;
    }
    value = output[0];
    if ((u16)(value != arg0)) {
        func_8000E40C(0x54, value);
    }
    return value | 0x80000000;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000C934 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000C934.s")
s32 func_800114D0(s32, s32, s32, s32, s32, s32, s32 *, s32 *, s32 *);
extern s32 D_800BE9F0;

s32 func_8000CA18(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 value;

    if (D_800BE9F0 == 0x37) {
        if (*(s32 *)(D_800DBFF0 + 0x5F0) & 1) {
            value = 0;
        } else {
            func_800114D0(0x898, 0x42A, -0x640, 0x5DC0,
                          0xBB8, 0x5DC, 0, &value, 0);
            value &= 0xFF00;
        }
    }
    else {
        value = 0x5DC0;
    }
    if ((u16)(value != arg0)) {
        func_8000E40C(0x54, value);
    }
    return value | 0x80000000;
}
void func_80011FA0(s32);
void func_80008790(u8, s32, u8, s32);
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
void func_80008988(s32, s32, s32);
void func_80008EE0(u8, s32);

void func_8000CC54(s32 arg0) {
    u32 value;
    SequenceRecordState *record;

    record = D_800417B0[arg0];
    if (record != 0) {
        value = (record->current58
                 * ((u32)(record->current4C * record->current52) >> 15) >> 15)
                 * record->target >> 15;
        if (value != record->current) {
            if (record->current == 0) {
                func_80008988((u8)arg0, record->flags38 ^ 0xFFFF, 1);
            } else if (value == 0) {
                func_80008988((u8)arg0, record->flags38 ^ 0xFFFF, 0);
            }
            record->current = value;
            func_80008EE0((u8)arg0, value);
        }
    }
}
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
typedef struct {
    s32 flags;
    u8 pad4[0xC];
} SequenceModeEntry;

extern SequenceModeEntry D_8002B078[];

extern u8 D_800418AC[];
s32 func_8000853C(s32);

s32 func_8000CDA0(u8 arg0, SequenceRecordState *record) {
    if (arg0 == 0) {
        return 1;
    }
    if (record != 0) {
        if (record->index >= 0) {
            if (D_800417B0[record->index] == 0 || record->id <= 0) {
                return 1;
            }
            if (func_8000853C(record->index & 0xFF) == 3) {
                return 1;
            }
            if (!(D_8002B078[record->id].flags & 0x20)) {
                D_800418AC[record->index] |= 3;
            }
            arg0 &= ~D_800418AC[record->index];
        } else {
            return 1;
        }
    } else {
        return 1;
    }
    return arg0 == 0;
}
typedef struct MessageQueue MessageQueue;

extern s32 D_800417C0[][16];
extern s32 D_800418B0[][16];
extern s32 D_80041880[];
extern s32 D_80041890[];
extern s32 D_800418A0[];
extern u8 D_80041970[][16];
extern u8 D_800419A0;
extern u8 D_800CC2D0[];
s32 func_80023440(MessageQueue *, void **, s32);
void func_8507E7E4(void *, s32, s32, s32, s32);
void func_800084D8(u8);
void func_80008F58(u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000CEAC CURRENT (9425) */
void func_8000CEAC(s32 arg0) {
    void *message;
    s32 step;
    s32 *modes;
    u16 *masks;
    MessageQueue *queue;
    SequenceRecordState **slot;
    SequenceRecordState *record;
    u8 *flags;
    s32 *levels;
    u32 event;
    u16 mask;
    s32 bit;
    s32 mode;
    s32 previous;
    s32 lower;
    s32 upper;

    slot = &D_800417B0[arg0];
    record = *slot;
    flags = &D_800418AC[arg0];
    if (record != 0) {
        modes = record->field8;
        masks = record->fieldC;
        queue = (MessageQueue *)(D_80041E58 + arg0 * 0x18);
        *flags = 0;
        while (func_80023440(queue, &message, 0) == 0) {
            event = (s32)message & 7;
            if ((s32)message & 0x10) {
                if (event < 2) {
                    previous = D_80041890[arg0];
                    message = (void *)((s32)message >> 5);
                    step = 0x514;
                    if (previous != 0) {
                        D_800418A0[arg0] = (s32)message - previous;
                    }
                    D_80041890[arg0] = (s32)message;
                    D_80041880[arg0] = (s32)message;
                }
                mask = masks[event];
                if (mask != 0) {
                    bit = 0;
                    *flags |= mask & 0x7F;
                    do {
                        if (mask & 1) {
                            mode = modes[bit];
                            if (mode == 0) {
                                D_80041970[arg0][bit] ^= 1;
                                D_800418B0[arg0][bit] = 0x8000;
                                D_800417C0[arg0][bit] = step;
                            } else if (mode == 1) {
                                step >>= 1;
                                D_80041970[arg0][bit] ^= 1;
                                if (D_80041970[arg0][bit] == 0) {
                                    D_800418B0[arg0][bit] = step * D_800BE9E4 + 0x8000;
                                }
                                D_800417C0[arg0][bit] = step;
                            } else if (mode == 2) {
                                lower = bit & 7;
                                upper = bit | 8;
                                D_80041970[arg0][lower] ^= 1;
                                D_80041970[arg0][upper] = D_80041970[arg0][lower] ^ 1;
                                D_800418B0[arg0][lower] = 0x8000;
                                D_800418B0[arg0][upper] = 0x8000;
                                D_800417C0[arg0][bit] = 0;
                            } else {
                                D_80041970[arg0][bit] |= 1;
                                D_800418B0[arg0][bit] = step * D_800BE9E4;
                                D_800417C0[arg0][bit] = step;
                            }
                        }
                        bit++;
                        mask >>= 1;
                    } while (bit < 16 && mask != 0);
                }
                D_800419A0 = arg0;
            } else if (D_80041F04 & 1) {
                func_8507E7E4(D_800CC2D0, 0x44, 1, 0x12, 5);
            }
        }
        record = *slot;
        levels = D_800418B0[arg0];
        if (record->current == 0) {
            *flags |= 0x80;
            if (record->pauseMode == 0) {
                func_80008F58(arg0 & 0xFF);
                (*slot)->pauseMode = 1;
            }
        } else if (record->pauseMode == 1) {
            func_800084D8(arg0 & 0xFF);
            (*slot)->pauseMode = 0;
        }
        for (bit = 0; bit != 16; bit++) {
            if (levels[bit] != 0) {
                levels[bit] -= D_800417C0[arg0][bit] * D_800BE9E4;
                if (levels[bit] < 0) {
                    levels[bit] = 0;
                }
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000CEAC */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000CEAC.s")
s32 func_8000CDA0(u8, SequenceRecordState *);
void func_8000B3D4(SequenceRecordState *, SequenceRecordState *);
void func_80008C6C(s32, s32);
void func_80008660(s32, s32, s32, s32);
void func_80008C04(s32, s32, s32);
s32 func_80008CE8(s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000D2F8 CURRENT (3869) */
void func_8000D2F8(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    s32 status;
    s32 channel;
    SequenceRecordState **slot;
    SequenceRecordState *record;
    SequenceRecordState *child;
    SequenceRecordState *owner;
    SequenceCallback callback;
    s32 i;

    channel = (u8)((u32 *)&arg0)[0];
    status = func_8000853C((u8)((u32 *)&channel)[0]);
    slot = &D_800417B0[(s32)((u32 *)&arg0)[0]];
    record = *slot;
    if (record != 0) {
        if (record->field24 != 0 &&
            func_8000CDA0(((u8 *)record)[0x23], record->owner)) {
            func_80008C6C((u8)((u32 *)&channel)[0], ((*slot)->field24 - 1) & 0xFF);
            record = *slot;
            if (record->volumeOverride != 0) {
                record->current = record->volumeOverride;
                (*slot)->target = record->volumeOverride;
            }
            (*slot)->current4C = 0x7FFF;
            (*slot)->value = 0x7FFF;
            func_8000CC54((s32)((u32 *)&arg0)[0]);
            (*slot)->field24 = 0;
            (*slot)->field20 = 0;
        }
        record = *slot;
        if (status == 0) {
            record->id = 0;
            record = *slot;
        }
        child = record->state;
        if (child != 0) {
            if (record->id == 0) {
                if (func_8000CDA0(((u8 *)child)[0x1B], child->owner)) {
                    (*slot)->id = -1;
                    func_8000B294(*slot);
                    child = (*slot)->state;
                    if (child->id > 0) {
                        if (func_80008CE8((u8)((u32 *)&channel)[0], child->id) == -1) {
                            (*slot)->state->owner = 0;
                            (*slot)->state->startMask = 0;
                            func_8000B3D4((*slot)->state, 0);
                            (*slot)->state = 0;
                            *slot = 0;
                        } else {
                            *slot = (*slot)->state;
                            (*slot)->index = (s32)((u32 *)&arg0)[0];
                            (*slot)->startMask = 0;
                            D_800418A0[(s32)((u32 *)&arg0)[0]] = 0;
                            D_80041890[(s32)((u32 *)&arg0)[0]] = 0;
                            D_80041880[(s32)((u32 *)&arg0)[0]] = 0;
                            if (D_8002B074[(*slot)->id].markerCount != 0) {
                                func_80008C04((u8)((u32 *)&channel)[0], D_8002B074[(*slot)->id].markerCount, 0x64);
                            }
                            if ((*slot)->field24 != 0) {
                                func_80008C6C((u8)((u32 *)&channel)[0], ((*slot)->field24 - 1) & 0xFF);
                                (*slot)->field24 = 0;
                            }
                            (*slot)->current = 0;
                            func_8000CC54((s32)((u32 *)&arg0)[0]);
                            func_800084D8((u8)((u32 *)&channel)[0]);
                            if ((*slot)->flags38 != 0) {
                                func_800088F0((u8)((u32 *)&channel)[0], (*slot)->flags38, 0);
                            }
                            i = 0;
                            do {
                                if ((*slot)->pad3C[i] != 0) {
                                    func_80008660((u8)((u32 *)&channel)[0], i & 0xFF, (*slot)->pad3C[i], 1);
                                    (*slot)->pad3C[i] = 0;
                                }
                                i++;
                            } while (i != 16);
                        }
                    } else {
                        child->id = -1;
                        (*slot)->state->owner = 0;
                        (*slot)->state->startMask = 0;
                        (*slot)->index = -1;
                        *slot = 0;
                    }
                }
            } else if (func_8000CDA0(((u8 *)child)[0x1B], child->owner)) {
                (*slot)->pauseMode = 0;
                func_80008F24((u8)((u32 *)&channel)[0]);
            }
            record = *slot;
        } else if (record->id == 0) {
            func_8000B294(record);
            record = 0;
            (*slot)->id = -1;
            (*slot)->index = -1;
            *slot = 0;
        }
        if (record != 0) {
            if (record->id > 0) {
                callback = D_8002B074[record->id].callback;
                if (callback != 0) {
                    (*slot)->callbackState = callback(record->callbackState, (u8)((u32 *)&channel)[0], arg1, arg2, arg3);
                    record = *slot;
                }
            }
            if (func_8000CDA0(((u8 *)record)[0x1F], record->owner)) {
                record = *slot;
                record->current4C = func_8000CD40(record->current4C, record->value, (u16)record->duration);
                record = *slot;
                record->current52 = func_8000CD40(record->current52, record->target54, (u16)record->duration56);
                record = *slot;
                record->current58 = func_8000CD40(record->current58, record->target5A, (u16)record->duration5C);
                (*slot)->fadeMask = 0;
            }
            func_8000CC54((s32)((u32 *)&arg0)[0]);
            record = *slot;
            owner = record->owner;
            if (record->ownerSync != 0 &&
                (owner == 0 || owner == record || owner->id <= 0 ||
                 record->id <= 0 || owner->index < 0)) {
                record->ownerSync = 0;
                record = *slot;
                record->owner = record;
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000D2F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000D2F8.s")
extern s8 D_80041F00;
extern u16 D_800427F4;
s32 func_851F2CDC(void);
void func_8000CEAC(s32);
void func_8000D2F8(s32, f32, f32, f32);

void func_8000D758(f32 arg0, f32 arg1, f32 arg2) {
    SequenceVolumeEntry *entries;
    s32 mask5;
    s32 mask40;
    s32 mask34;
    s32 mask12;
    s32 i;
    s32 id;
    s32 flags;
    s32 mode;
    SequenceRecordState *record;

    mask5 = 0;
    mask40 = 0;
    mask34 = 0;
    mask12 = 0;
    if ((u8)D_80041F00 == 0) {
        entries = D_8002B074;
        for (i = 0; i < 3; i++) {
            record = D_800417B0[i];
            if (record != 0) {
                id = record->id;
                if (id > 0) {
                    flags = entries[id].flags;
                    mode = flags & ~0xF0;
                    if (flags & 0x40) {
                        mask40 |= 1 << i;
                    }
                    if (mode == 5) {
                        mask5 |= 1 << i;
                    } else if (mode == 4 || mode == 3) {
                        mask34 |= 1 << i;
                    } else if (mode == 1 || mode == 2) {
                        mask12 |= 1 << i;
                    }
                }
            }
        }
        if (mask5 != 0) {
            func_8000CBF0(0x1770, 0x400, mask5 ^ 0xFF ^ mask40);
            func_8000CBF0(0x8000, 0x6400, mask5);
        } else if (mask34 != 0) {
            func_8000CBF0(0x1F4, 0x400, mask34 ^ 0xFF);
            func_8000CBF0(0x8000, 0x800, mask34);
        } else if (func_851F2CDC() == 1 &&
                   (D_800427F4 < 0x7D || D_800427F4 >= 0x81) &&
                   D_800427F4 < 0x1C9 && D_800427F4 != 0x170 &&
                   D_800427F4 != 0x171) {
            func_8000CBF0(0x36B0, 0x200, mask12 ^ 0xFF);
        } else {
            func_8000CBF0(0x8000, 0x800, 0xFF);
        }
        i = 0;
        do {
            func_8000CEAC(i);
            i++;
        } while (i < 3);
        i = 0;
        do {
            func_8000D2F8(i, arg0, arg1, arg2);
            i++;
        } while (i != 3);
    }
}
void *func_8000B1FC(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000D96C CURRENT (1068) */
void func_8000D96C(s32 arg0, s32 arg1, s32 arg2) {
    SequenceRecordState *outgoing;
    SequenceRecordState *incoming;
    s32 sync;

    outgoing = 0;
    incoming = 0;
    sync = 0;
    arg0 &= 0xFFF;
    arg1 &= 0xFFF;
    if (arg0 != 0 && func_8000B1FC(arg0) != 0) {
        SequenceRecordState *record;
        SequenceRecordState *child;

        record = (SequenceRecordState *)func_8000B1B0(arg0);
        if (record == 0) {
            return;
        }
        child = record->state;
        if (child != 0) {
            if (child->index == -1) {
                record->target54 = 0x8000;
                record->duration56 = 0x400;
                child->id = -1;
                record->state->index = -1;
                record->state = 0;
            }
            arg0 = 0;
            if (arg1 == 0) {
                return;
            }
        } else if (record->pauseMode != 0 || record->target54 == 0) {
            record->target54 = 0x8000;
            record->current52 = 0;
            record->duration56 = 0x400;
            arg0 = 0;
            if (arg1 == 0) {
                return;
            }
        } else {
            return;
        }
    }
    if (arg1 != 0) {
        outgoing = (SequenceRecordState *)func_8000B1B0(arg1);
    }
    if (outgoing != 0) {
        if (outgoing != 0 && outgoing->state != 0) {
            if (arg0 != 0) {
                return;
            }
        } else if (arg2 == 4 || arg2 == 6) {
            if (arg0 != 0) {
                incoming = func_8000B2F4(arg0);
            }
            if (incoming != 0 || arg0 == 0) {
                if (arg0 != 0) {
                    SequenceVolumeEntry *entry;

                    entry = &D_8002B074[arg0];
                    if ((entry->flags & 0x20) && (D_8002B074[arg1].flags & 0x20)) {
                        sync = 1;
                    }
                    incoming->ownerSync = sync;
                    if (entry->flags & 8) {
                        incoming->target54 = 0x8000;
                        incoming->current52 = 0;
                        incoming->duration56 = 0x3C;
                    } else if (sync != 0) {
                        incoming->target54 = 0x8000;
                        incoming->current52 = 0;
                        incoming->duration56 = 0x100;
                    }
                    incoming->owner = outgoing;
                    incoming->startMask = 2;
                    func_8000B3D4(incoming, 0);
                }
                if (arg2 == 6) {
                    if (arg0 != 0) {
                        outgoing->fadeMask = 2;
                    }
                    outgoing->ownerSync = 0;
                    outgoing->owner = outgoing;
                    outgoing->target54 = 0;
                    if (D_8002B074[arg1].flags & 8) {
                        outgoing->duration56 = 0x28;
                        return;
                    }
                    outgoing->duration56 = 0xA0;
                    return;
                }
                incoming = func_8000B2F4(0);
                if (incoming != 0) {
                    if (arg0 != 0) {
                        outgoing->fadeMask = 2;
                    }
                    outgoing->ownerSync = 0;
                    outgoing->owner = outgoing;
                    outgoing->target54 = 0;
                    if (sync != 0) {
                        outgoing->duration56 = 0x80;
                    } else {
                        outgoing->duration56 = 0x200;
                    }
                    incoming->startMask = 0x80;
                    incoming->owner = outgoing;
                    func_8000B3D4(incoming, outgoing);
                }
            }
        } else {
            goto simple_transition;
        }
        return;
    }
    if (arg1 != 0) {
        outgoing = func_8000B1FC(arg1);
        if (outgoing != 0) {
            if (arg0 != 0) {
                func_800226F0(outgoing, 0x64);
                outgoing->index = -1;
                if (arg0 < 0x96) {
                    outgoing->target = D_8002B074[arg0].volume;
                } else {
                    outgoing->target = 0x6590;
                }
                outgoing->current = outgoing->target;
                outgoing->value = outgoing->current4C = outgoing->current52 =
                    outgoing->target54 = outgoing->current58 =
                    outgoing->target5A = 0x8000;
                outgoing->field8 = D_8002B9D4;
                outgoing->fieldC = D_8002B9F4;
                outgoing->owner = outgoing;
            } else {
                outgoing->startMask = 0x80;
            }
            outgoing->id = arg0;
            return;
        }
    }
simple_transition:
    if (arg0 != 0 || outgoing != 0) {
        incoming = func_8000B2F4(arg0);
    }
    if (incoming != 0) {
        if (arg2 == 3) {
            incoming->target54 = 0x8000;
            incoming->current52 = 0;
            incoming->duration56 = 0x400;
        } else if (arg2 == 2) {
            incoming->startMask = 1;
            incoming->owner = outgoing;
        } else if (arg2 == 1) {
            incoming->startMask = 2;
            incoming->owner = outgoing;
        } else if (arg2 == 5) {
            incoming->startMask = 0x80;
            incoming->owner = outgoing;
            if (outgoing != 0) {
                outgoing->target54 = 0;
                outgoing->duration56 = 0x200;
            }
        }
        func_8000B3D4(incoming, outgoing);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000D96C */
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

void func_8000DEC4(void) {
    s32 index;

    for (index = 0; index < 12; index++) {
        if (D_800419A8[index].index == -1) {
            if (D_800419A8[index].id != -1) {
                D_800419A8[index].id = -1;
            }
        } else if (func_8000853C(D_800419A8[index].index & 0xFF) == 0) {
            D_800417B0[D_800419A8[index].index] = 0;
            D_800419A8[index].index = -1;
            D_800419A8[index].id = -1;
        }
        D_800419A8[index].state = 0;
    }
}
void *func_8000B1FC(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000DF68 CURRENT (605) */
void func_8000DF68(s32 arg0, s32 arg1, s32 arg2) {
    SequenceRecordState *record;
    s32 step;

    record = func_8000B1FC(arg0);
    if (record != 0) {
        record->value = arg1;
        if (arg2 == 1) {
            record->current4C = arg1;
            if (record->index >= 0) {
                func_8000CC54(record->index);
            }
        }
        if (arg2 >= 2) {
            step = record->current4C - arg1;
            if (step < 0) {
                step = -step;
            }
            step /= arg2;
            if (step <= 0) {
                step = 2;
            } else if (step < 0x8000) {
                record->duration = step;
                goto interpolation_done;
            } else {
                step = 0x7FFF;
            }
            record->duration = step;
interpolation_done:
            return;
        }
        record->duration = 0x200;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000DF68 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_B1B0/func_8000DF68.s")
s32 *func_8000B1B0(s32);
void func_800084D8(u8);
void func_80008F58(u8);
void func_8000CC54(s32);

void func_8000E054(s32 arg0, s32 arg1) {
    SequenceRecordState *record;

    record = (SequenceRecordState *)func_8000B1B0(arg0);
    if (record != 0) {
        if (record->pauseMode == 2 && arg1 == 0) {
            func_800084D8(((u8 *)record)[3]);
            record->pauseMode = 0;
            record->current = -1;
            func_8000CC54(record->index);
            return;
        }
        if (record->pauseMode != 2 && arg1 != 0) {
            if (record->pauseMode != 1) {
                func_80008F58(((u8 *)record)[3]);
            }
            record->pauseMode = 2;
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
void func_8000E17C(void) {
    s32 index;
    SequenceRecordState *related;
    s32 id;

    index = 0;
    do {
        id = D_800419A8[index].id;
        if (id > 0) {
            if (((D_8002B074[id].flags & ~0xF0) == 1 || (D_8002B074[id].flags & ~0xF0) == 3) && D_800419A8[index].index == -1) {
                D_800419A8[index].id = -1;
            }
        }
        index++;
    } while (index < 12);
    index = 0;
    do {
        if (D_800419A8[index].id > 0) {
            related = D_800419A8[index].state;
            if (related != 0 && related->id == -1) {
                D_800419A8[index].state = 0;
            }
            related = D_800419A8[index].owner;
            if (related != 0 && related->id == -1) {
                D_800419A8[index].owner = 0;
            }
        }
        index++;
    } while (index < 12);
    index = 0;
    do {
        id = D_800419A8[index].id;
        if (id > 0) {
            if (((D_8002B074[id].flags & ~0xF0) == 1 || (D_8002B074[id].flags & ~0xF0) == 3) && D_800419A8[index].index != -1) {
                func_8000DE1C(id, 4);
            }
        }
        index++;
    } while ((SequenceRecordState *)D_80041E58 != &D_800419A8[index]);
}
extern s8 D_80041F00;

void func_8000E2F4(s32 arg0) {
    s32 i;
    u8 channel;

    for (i = 0; i < 3; i++) {
        if (D_800417B0[i] != 0 && D_800417B0[i]->id > 0 && D_800417B0[i]->pauseMode == 0) {
            if (arg0 != 0) {
                channel = i;
                func_80008EE0(channel, 0);
                if (!(D_8002B074[D_800417B0[i]->id].flags & 0x10)) {
                    func_80008F58(channel);
                }
            } else {
                if (!(D_8002B074[D_800417B0[i]->id].flags & 0x10)) {
                    func_800084D8((u8)i);
                }
                D_800417B0[i]->current = -1;
                func_8000CC54(i);
            }
        }
    }
    D_80041F00 = arg0;
}
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
void func_8000886C(u8, s32, u8);

s32 func_8000E46C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    SequenceRecordState *record;
    s32 i;

    record = func_8000B1FC(arg0);
    arg1 = arg1 * 0xFF / 100;
    if (arg1 >= 0x100) {
        arg1 = 0xFF;
    } else if (arg1 < 0) {
        arg1 = 0;
    }
    if (record != 0) {
        if (record->index >= 0) {
            if (arg3 < 0) {
                func_8000886C(((u8 *)record)[3], arg2, arg1);
                return 1;
            }
            func_80008790(((u8 *)record)[3], arg2, arg1, arg3);
            return 1;
        }
        if (arg1 == 0) {
            record->flags38 |= arg2;
        } else if (arg1 > 0) {
            record->flags38 &= ~arg2;
        }
        i = 0;
        while (arg2 != 0) {
            if (arg2 & 1) {
                record->pad3C[i] = arg1;
            }
            i++;
            arg2 >>= 1;
        }
        return 1;
    }
    return 0;
}
void func_8000886C(u8, s32, u8);

s32 func_8000E588(s32 arg0, s32 arg1, s32 arg2) {
    SequenceRecordState *record;

    record = func_8000B1FC(arg0);
    if (record != 0) {
        if (record->index >= 0) {
            if (arg1 >= 0x65) {
                arg1 = 0x64;
            } else if (arg1 < 0) {
                arg1 = 0;
            }
            func_8000886C(((u8 *)record)[3], arg2, arg1 * 0xFF / 100);
            return 1;
        }
        if (arg1 <= 0) {
            record->flags38 |= arg2;
            return 1;
        }
        if (arg1 > 0) {
            record->flags38 &= ~arg2;
            return 1;
        }
    }
    return 0;
}
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
void func_8000E7A0(s32 arg0, s32 arg1) {
    if (((u32)arg0 & 1U) == 1U) {
        D_80041F04 |= 1;
    } else if (arg0 & 2) {
        D_80041F08 += arg1;
        D_80041F0C++;
    } else if (arg0 & 4) {
        D_80041F08 = arg1 + 1;
        D_80041F04 |= 4;
    } else if (arg0 & 8) {
        D_80041F0C = arg1 >> 8;
        arg1 &= 0xFF;
        if (arg1 == 0 || arg1 == 4 || arg1 == 5) {
            D_80041F08 = 2;
        } else if (arg1 == 0xA) {
            D_80041F08 = 1;
        } else {
            D_80041F08 = 3;
        }
    } else if (arg0 & 0x10) {
        D_80041F04 |= 0x10;
    }
}
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
extern s32 D_800417C0[][16];
extern s32 D_800418B0[][16];
extern s32 D_80041880[];
extern s32 D_80041890[];
extern s32 D_800418A0[];
extern u8 D_800419A0;
void func_80008F24(u8);

void func_8000E934(void) {
    u32 i;
    s32 j;
    s32 index;

    for (i = 0; i < 3; i++) {
        for (j = 0; j != 16; j++) {
            D_800418B0[i][j] = 0x8000;
            D_800417C0[i][j] = 0x100;
        }
        func_80008F24(i);
        D_800417B0[i] = 0;
        D_800418A0[i] = 0;
        D_80041890[i] = 0;
        D_80041880[i] = 0;
    }
    func_800226F0(D_800419A8, 0x4B0);
    D_800419A0 = 0;
    for (index = 0; index < 12; index++) {
        D_800419A8[index].id = -1;
    }
}

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
