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
typedef struct {
    u8 pad0[0x10];
    u32 flags;
    void *callback;
    void *owner;
    s32 key;
    u8 pad20[4];
    u16 handle;
    u8 pad26[0xA];
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
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000F1A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000F248.s")
struct sndstate;

typedef struct {
    u16 id;
    u8 pad2[2];
    u16 value;
    u8 pad6[2];
    struct sndstate *state;
} SoundHandleEntry;

extern SoundHandleEntry D_800425E0[];
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
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000FEF0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000FF90.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8001001C.s")
extern SoundArrayRecord D_80041FE0[];
extern s32 D_80042760;

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
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_800107F8.s")
typedef struct {
    u8 pad0[0x3B];
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
