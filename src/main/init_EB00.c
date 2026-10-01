#include "types.h"

/*
 * Reviewed source unit: src/main/init_EB00.c
 * Boundary evidence: docs/evidence/main_sound_record_family_boundary.md
 *
 * TODO: Implement these source-unit functions:
 * - func_8000EBC4
 * - func_8000EC24
 * - func_8000ECCC
 * - func_8000EDA0
 * - func_8000EE70
 * - func_8000EFB4
 * - func_8000F248
 * - func_8000F3D0
 * - func_8000F44C
 * - func_8000F4D8
 * - func_8000F568
 * - func_8000F6B8
 * - func_8000F85C
 * - func_8000F9D4
 * - func_8000FA64
 * - func_8000FC18
 * - func_8000FD38
 * - func_8000FDF4
 * - func_8000FE88
 * - func_8000FEF0
 * - func_8000FF90
 * - func_800100E0
 * - func_80010154
 * - func_80010344
 * - func_80010558
 * - func_80010630
 * - func_80010720
 * - func_8001091C
 * - func_80010AA8
 * - func_80010BE8
 * - func_80010E78
 * - func_80010F30
 * - func_80010F88
 * - func_80010FFC
 * - func_8001123C
 * - func_80011310
 * - func_800114D0
 * - func_80011624
 * - func_80011BB8
 * - func_80011EB8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    s16 field0;
    u8 pad2[0x16];
    s32 timer;
    u8 pad1C[8];
    u16 handle;
} SoundRandomState;

u32 func_850ADA20(void);
extern u8 D_800CC37D;
extern s32 D_800BE9E4;

s32 func_8000EB00(SoundRandomState *state, s32 arg1, s32 *active,
                 s32 *arg3, s32 arg4, s32 arg5, s16 *output) {
    if (state->handle != 0) {
        state->handle = 0;
    }
    *arg3 = 0x40;
    if ((D_800CC37D != 0) || (*active == 0)) {
        *active = 0;
        *output = 0;
        return 0;
    }
    state->timer -= D_800BE9E4;
    if (state->timer > 0) {
        *active = 0;
        *output = 0;
    } else {
        state->timer = (func_850ADA20() & 0x7F) + 0x80;
        state->field0 = (func_850ADA20() % 3U) + 0x6C;
    }
    return 0;
}
typedef struct {
    u8 pad0[0xC];
    s32 value;
    u8 pad10[8];
    s32 timer;
} SoundDecayState;


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
typedef struct {
    s16 field0;
    u8 pad2[0x16];
    union {
        s32 word;
        struct {
            s16 high;
            s16 low;
        } halves;
    } timer;
    s32 value;
} SoundDelayedState;

s32 func_80010F30(s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000EC24 CURRENT (888) */
s32 func_8000EC24(SoundDelayedState *state, s32 arg1, s32 *active,
                 u8 *arg3, s16 *arg4, s32 *arg5, u16 *arg6) {
    u16 value = *arg6;
    s16 remaining = state->timer.halves.low;
    s32 handle;

    if (value != 0) {
        state->value = value;
        state->field0 = 0;
        *arg6 = 0;
    }
    remaining -= D_800BE9E4;
    if (remaining <= 0) {
        handle = *active;
        if (handle != 0) {
            func_80010F30(state->value, handle & 0xFFFF,
                         arg3[3], arg4[1], *arg5);
        }
        return 1;
    }
    state->timer.word = remaining;
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000EC24 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000EC24.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000ECCC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000EDA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000EE70.s")
typedef struct {
    u8 pad0[0xC];
    s32 valueC;
    u32 flags;
    void *callback;
    void *owner;
    s32 key;
    u8 pad20[4];
    u16 handle;
    u8 pad26[6];
    f32 pitch;
} SoundArrayRecord;

void func_800111C8(u16);

s32 func_8000EF40(SoundArrayRecord *record, s32 arg1, s32 *active,
                 s32 arg3, s32 arg4, s32 arg5, s16 *output) {
    if (record->flags & 0x80) {
        record->flags &= ~0x80;
    }
    if (*active == 0) {
        if (record->handle != 0) {
            func_800111C8(record->handle);
            record->handle = 0;
        }
        *output = 0;
    }
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000EFB4.s")
struct sndstate;

typedef struct {
    u16 id;
    u16 field2;
    u16 value;
    u8 pad6[2];
    struct sndstate *state;
} SoundHandleEntry;

extern SoundHandleEntry D_800425E0[];
void func_800226F0(void *, s32);
void func_800176EC(void);
extern s32 D_80042760;
extern u8 D_80041FD9;
extern s8 D_80041FD8;
extern s32 D_80041F50;
extern u8 D_80041F60;
extern u8 D_80041F61;

void func_8000F1A8(void) {
    s32 index;

    D_80042760 = 0;
    D_80041FD9 = 1;
    D_80041FD8 = 0;
    func_800226F0(D_800425E0, 0x180);
    for (index = 0; index < 0x10; index++) {
        D_800425E0[index].field2 = index + 0x10;
    }
    D_80041F50 = 0;
    func_800176EC();
    D_80041F60 = D_80041F61 = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000F248.s")
void func_80017594(struct sndstate *);

s32 func_800173C4(struct sndstate **);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000F3D0 CURRENT (324) */
s32 func_8000F3D0(s32 arg0) {
    SoundHandleEntry *entry;
    s32 index;

    arg0 &= 0xFFFF;
    index = arg0 & 0xF;
    entry = &D_800425E0[index];
    if ((entry->state != 0) &&
        ((entry->id == arg0) || (arg0 == index)) &&
        (func_800173C4(&entry->state) != 0)) {
        return 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000F3D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000F3D0.s")
s32 func_80022DC0(void);
void func_80022DE0(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000F44C CURRENT (425) */
s32 func_8000F44C(s32 arg0) {
    s32 savedMask;
    SoundHandleEntry *entry;
    struct sndstate *state;
    u16 handle;

    savedMask = func_80022DC0();
    handle = arg0;
    entry = &D_800425E0[handle & 0xF];
    state = entry->state;
    if ((state != 0) && (handle == entry->id) &&
        (*((u8 *)state + 0x53) & 2)) {
        func_80022DE0(savedMask);
        return 1;
    }
    func_80022DE0(savedMask);
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000F44C */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000F44C.s")
extern u8 D_800426A0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000F4D8 CURRENT (40) */
s32 func_8000F4D8(u16 arg0) {
    SoundHandleEntry *entry;

    arg0 &= 0x7FFF;
    entry = D_800425E0;
    do {
        if ((entry->state != 0) &&
            (arg0 == (entry->value & 0x7FFF)) &&
            (func_800173C4(&entry->state) != 0)) {
            return 1;
        }
        entry++;
    } while (entry != (SoundHandleEntry *)D_800426A0);
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000F4D8 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000F4D8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000F568.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000F6B8.s")
s32 func_8000F3D0(s32);
f32 func_80019AB0(s32);
void func_80017714(struct sndstate *, s16, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000F85C CURRENT (3166) */
void func_8000F85C(u16 arg0, s32 arg1, s32 arg2) {
    union {
        f32 number;
        s32 word;
    } pitch;
    s32 handle = arg0;
    s16 eventType = arg1;

    if ((handle >= 0x10) && (func_8000F3D0(handle) != 0)) {
        if (eventType == 0x10) {
            pitch.number = func_80019AB0(arg2);
            arg2 = pitch.word;
        } else if (eventType == 0x11) {
            eventType = 0x10;
        }
        func_80017714(D_800425E0[handle & 0xF].state, eventType, arg2);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000F85C */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000F85C.s")
s32 func_8000F6B8(s32, s32, s32, s32, s32 *, s32, s32);
void func_8000F85C(u16, s32, s32);

void func_8000F91C(u16 arg0, s32 arg1, s16 arg2, s32 arg3, s32 arg4,
                 s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    s32 value;
    u32 scale;

    scale = func_8000F6B8(arg4, (s16)arg5, (s16)arg6,
                          (s16)arg7, &value, (s16)arg8, (s16)arg9);
    func_8000F85C(arg0, 8, ((u32)(u16)arg1 * scale) >> 15);
    func_8000F85C(arg0, 4, value & 0x7F);
    func_8000F85C(arg0, 0x100, (value & 0x80) | (u8)arg3);
    func_8000F85C(arg0, 0x10, arg2);
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000F9D4 CURRENT (1794) */
void func_8000F9D4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 value;

    func_8000F6B8(-1, (s16)arg1, (s16)arg2, (s16)arg3,
                  &value, 0x7FF8, 0x7FFD);
    func_8000F85C((u16)arg0, 4, value & 0x7F);
    func_8000F85C((u16)arg0, 0x100, value & 0x80);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000F9D4 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000F9D4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000FA64.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000FC18.s")
extern SoundArrayRecord D_80041FE0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000FD38 CURRENT (280) */
void func_8000FD38(void *callback, void *owner, s32 key) {
    SoundArrayRecord *record = D_80041FE0;
    s32 index;

    for (index = 0; index < D_80042760; index++, record++) {
        if ((callback == record->callback) &&
            (owner == record->owner) && (key == record->key)) {
            if (record->handle != 0) {
                func_800111C8(record->handle);
            }
            record->flags |= 0x80;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000FD38 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000FD38.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000FDF4 CURRENT (956) */
void func_8000FDF4(s32 arg0) {
    SoundArrayRecord *record;
    s32 index;

    arg0 &= 0xFFFF;
    index = 0;
    if (D_80042760 > 0) {
        record = D_80041FE0;
        do {
            if (arg0 == record->handle) {
                if (record->handle != 0) {
                    func_800111C8(record->handle);
                }
                record->flags |= 0x80;
            }
            index++;
            record++;
        } while (index < D_80042760);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000FDF4 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000FDF4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000FE88 CURRENT (18) */
s32 func_8000FE88(SoundArrayRecord *records, s32 index, s32 *count) {
    SoundArrayRecord *record;

    if (index < *count) {
        record = &records[index];
        if (record->handle != 0) {
            func_800111C8(record->handle);
        }
        record->flags |= 0x80;
        return 0;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000FE88 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000FE88.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000FEF0 CURRENT (2265) */
s32 func_8000FEF0(s32 arg0, void *owner, s32 key) {
    SoundArrayRecord *record;
    s32 index;

    arg0 &= 0xFFFF;
    if (arg0 == 0) {
        return -1;
    }
    index = 0;
    if (D_80042760 > 0) {
        record = D_80041FE0;
    next_record:
        if ((arg0 == record->handle) && (owner == record->owner) &&
            (key == record->key) && !(record->flags & 0x80)) {
            return index;
        }
        index++;
        record++;
        if (index < D_80042760) {
            goto next_record;
        }
    }
    return -1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000FEF0 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000FEF0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000FF90 CURRENT (290) */
s32 func_8000FF90(u8 *callback, void *owner, s32 key) {
    SoundArrayRecord *record = D_80041FE0;
    s32 index = 0;

    if (D_80042760 > 0) {
    next_record:
        if ((callback == record->callback) &&
            ((owner == record->owner) || (owner == (void *)-1)) &&
            ((key == record->key) || (key == -1)) &&
            !(record->flags & 0x80)) {
            return index;
        }
        index++;
        record++;
        if (index < D_80042760) {
            goto next_record;
        }
    }
    return -1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000FF90 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000FF90.s")
void func_8001001C(void *callback, void *owner, s32 key, s32 value, s32 cents) {
    SoundArrayRecord *record = D_80041FE0;
    s32 index;

    for (index = 0; index < D_80042760; index++, record++) {
        if ((callback == record->callback) &&
            (owner == record->owner) && (key == record->key)) {
            record->pitch = func_80019AB0(cents);
            record->valueC = value;
        }
    }
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_800100E0 CURRENT (330) */
void func_800100E0(void *callback, void *owner, s32 key,
                  void *newCallback, void *newOwner, s32 newKey) {
    s32 count = D_80042760;
    SoundArrayRecord *record;

    record = D_80041FE0;
    if (count > 0) {
        do {
            if ((callback == record->callback) &&
                (owner == record->owner) && (key == record->key)) {
                record->callback = newCallback;
                record->owner = newOwner;
                record->key = newKey;
            }
            record++;
        } while (record < D_80041FE0 + count);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_800100E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_800100E0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80010154.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80010344.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80010558.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80010630.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80010720.s")
typedef struct {
    u32 field0;
    u8 pad4[0x37];
    u8 field3B;
    u8 pad3C[0x50];
    u16 handle8C;
    u16 handle8E;
    u8 pad90[0x288];
    u32 field318;
} SoundOwnerState;

void func_8000FD38(void *, void *, s32);
extern u8 D_1000EE70[];

s32 func_8000F3D0(s32);
s32 func_8000FF90(u8 *, void *, s32);

s32 func_800107F8(SoundOwnerState *owner) {
    if (owner->field0 == 0) {
        return 0;
    }
    if (owner->field318 != 0) {
        if ((owner->handle8E != 0) && (func_8000F3D0(owner->handle8E) != 0)) {
            return 1;
        }
    } else if (func_8000FF90(D_1000EE70, owner, owner->field3B | 0x10000) != -1) {
        return 1;
    }
    owner->handle8E = 0;
    return 0;
}
s32 func_80010894(SoundOwnerState *owner) {
    if (owner->field318 != 0) {
        if ((owner->handle8C != 0) && (func_8000F3D0(owner->handle8C) != 0)) {
            return 1;
        }
    } else if (func_8000FF90(D_1000EE70, owner, owner->field3B | 0x20000) != -1) {
        return 1;
    }
    owner->handle8C = 0;
    return 0;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_8001091C CURRENT (210) */
void func_8001091C(SoundOwnerState *owner, s32 value) {
    s32 index;

    if ((value != 0) && (owner->field0 != 0)) {
        if (owner->field318 != 0) {
            if (owner->handle8E != 0) {
                func_8000F85C(owner->handle8E, 8, value);
            }
        } else {
            index = func_8000FF90(D_1000EE70, owner, owner->field3B | 0x10000);
            if (index != -1) {
                D_80041FE0[index].valueC = value;
                return;
            }
            owner->handle8E = 0;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8001091C */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8001091C.s")
void func_800109D0(SoundOwnerState *owner) {
    if (owner->field318 != 0) {
        if (owner->handle8E != 0) {
            func_800111C8(owner->handle8E);
        }
    } else {
        func_8000FD38(D_1000EE70, owner, owner->field3B | 0x10000);
    }
    owner->handle8E = 0;
}
void func_80010A3C(SoundOwnerState *owner) {
    if (owner->field318 != 0) {
        if (owner->handle8C != 0) {
            func_800111C8(owner->handle8C);
        }
    } else {
        func_8000FD38(D_1000EE70, owner, owner->field3B | 0x20000);
    }
    owner->handle8C = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80010AA8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80010BE8.s")
u16 func_80010BE8(s32, s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80010E78 CURRENT (855) */
u16 func_80010E78(s32 arg0, s32 arg1, u16 arg2, s32 arg3, s32 arg4,
                 s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10) {
    s32 value;
    u32 volume;

    volume = func_8000F6B8(arg5, (s16)arg6, (s16)arg7,
                           (s16)arg8, &value, (s16)arg9, (s16)arg10);
    volume = ((u32)arg2 * volume) >> 15;
    if (volume != 0) {
        return func_80010BE8((u16)arg0, arg1, (u16)volume,
                             value & 0x7F, (s16)arg3,
                             (value & 0x80) | (u8)arg4, D_80041FD9);
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80010E78 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80010E78.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_80010F30 CURRENT (248) */
s32 func_80010F30(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    return func_80010BE8(0, arg0, (u16)arg1, (u8)arg2,
                        (s16)arg3, (u8)arg4, D_80041FD9);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80010F30 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80010F30.s")
u16 func_80010E78(s32, s32, u16, s32, s32, s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80010F88 CURRENT (120) */
s32 func_80010F88(s32 arg0, u16 arg1, s32 arg2, s32 arg3, s32 arg4,
                 s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    return func_80010E78(0, arg0, arg1, (s16)arg2, (u8)arg3, arg4,
                        (s16)arg5, (s16)arg6, (s16)arg7, (s16)arg8, (s16)arg9);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80010F88 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80010F88.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80010FFC.s")
void func_800111C8(u16 arg0) {
    SoundHandleEntry *entry;

    entry = &D_800425E0[arg0 & 0xF];
    if ((entry->state != 0) && (entry->id == arg0)) {
        entry->id = 0;
        entry->value = 0;
        func_80017594(entry->state);
        entry->state = 0;
    }
}
s32 func_800112BC(s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8001123C CURRENT (321) */
void func_8001123C(s32 arg0) {
    SoundHandleEntry *entry;

    arg0 &= 0xFFFF;
    entry = &D_800425E0[arg0 & 0xF];
    if ((entry->state != 0) && (entry->id == arg0)) {
        if (func_800112BC(arg0, 1) == 0) {
            func_80017594(entry->state);
            entry->state = 0;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8001123C */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8001123C.s")
typedef struct {
    s16 value;
    s8 operation;
    s8 index;
} SoundQueueEntry;

extern SoundQueueEntry D_80041F10[16];

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


void func_80011E94(s32 arg0) {
    if (arg0 != 0) {
        D_80041F61 = 1;
        return;
    }
    D_80041F61 = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80011EB8.s")
