#include "types.h"

/*
 * Reviewed source unit: src/main/init_EB00.c
 * Boundary evidence: docs/evidence/boundaries/main/main_sound_record_family_boundary.md
 *
 * TODO: Implement these source-unit functions:
 * - func_8000F6B8
 * - func_8000FA64
 * - func_8000FEF0
 * - func_80010154
 * - func_80010344
 * - func_80010630
 * - func_80010FFC
 * - func_80011310
 * - func_80011624
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


s32 func_8000EBC4(SoundDecayState *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 value;
    s32 timer;

    timer = arg0->timer;
    value = arg0->value;
    timer -= D_800BE9E4;
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

s32 func_8000EC24(SoundDelayedState *state, s32 arg1, s32 *active,
                 u8 *arg3, s16 *arg4, s32 *arg5, u16 *arg6) {
    s16 remaining = state->timer.halves.low;
    s32 handle;

    if (*arg6 != 0) {
        state->value = *arg6;
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
typedef struct {
    u32 field0;
    u8 field4;
    u8 pad5[0xF];
    f32 field14;
    f32 field18;
    f32 field1C;
    u8 pad20[0x1B];
    u8 field3B;
    u8 pad3C[0x48];
    u16 field84;
    u8 pad86[6];
    u16 handle8C;
    u16 handle8E;
    u8 pad90[0xAC];
    u8 field13C;
    u8 pad13D[0xF];
    f32 field14C;
    u8 pad150[0x34];
    u32 field184;
    u8 pad188[0x190];
    u32 field318;
    u8 *field31C;
} SoundOwnerState;

typedef struct {
    u16 field0;
    u8 pad2[6];
    u16 field8;
    s16 fieldA;
    s32 valueC;
    u8 pad10[8];
    s32 packed;
    void *owner;
} SoundQueuedState;

s32 func_80010894(SoundOwnerState *);
s32 func_80010344(u16, void *, u32, s16, u16);

s32 func_8000ECCC(SoundQueuedState *state, s32 arg1, s32 arg2,
                 s32 arg3, s32 arg4, s32 arg5, u16 *output) {
    u16 value;
    s32 remaining;

    value = *output;
    remaining = (s16)state->packed;

    if (value != 0) {
        state->packed = ((u32)value << 16) | (state->packed & 0xFFFF);
        state->field0 = 0;
        *output = 0;
    }
    remaining = (s16)(remaining - D_800BE9E4);
    if (remaining <= 0) {
        value = state->packed >> 16;
        state->field0 = *output = value;
        if (func_80010894(state->owner) == 0) {
            func_80010344(*output, state->owner, state->valueC,
                          state->fieldA, state->field8);
        }
        return 1;
    }
    state->packed = (state->packed & 0xFFFF0000) | remaining;
    return 0;
}

void func_80010630(u16, SoundOwnerState *, s32, s16, u16);

s32 func_8000EDA0(SoundQueuedState *state, s32 arg1, s32 arg2,
                 s32 arg3, s32 arg4, s32 arg5, u16 *output) {
    s32 remaining = (s16)state->packed;
    u16 value = *output;

    if (value != 0) {
        state->packed = ((u32)value << 16) | (state->packed & 0xFFFF);
        state->field0 = 0;
        *output = 0;
    }
    remaining = (s16)(remaining - D_800BE9E4);
    if (remaining <= 0) {
        state->field0 = *output = state->packed >> 16;
        func_80010630(*output, state->owner, state->valueC,
                      state->fieldA, state->field8);
        return 1;
    }
    state->packed = (state->packed & 0xFFFF0000) | remaining;
    return 0;
}
typedef struct {
    u16 field0;
    s16 positionX;
    s16 positionY;
    s16 positionZ;
    u16 field8;
    s16 fieldA;
    s32 valueC;
    u32 flags;
    void *callback;
    void *owner;
    s32 key;
    s16 cents;
    u8 field22;
    u8 field23;
    u16 handle;
    s16 field26;
    s16 field28;
    u8 pad2A[2];
    f32 pitch;
} SoundArrayRecord;

s32 func_8000F44C(u16);

s32 func_8000EE70(SoundArrayRecord *record, s32 arg1, s32 *active,
                 s32 arg3, s32 arg4, s32 *output, s32 arg6) {
    SoundOwnerState *owner = record->owner;

    if ((owner != 0) && (*active != 0)) {
        u16 key = record->key & 0xFF;

        if ((owner->field0 != 0) && (key == owner->field3B)) {
            *output = ((owner->field184 >> 3) & 0x30) * 2;
            record->positionX = (s16)(s32)owner->field14;
            record->positionY = (s16)(s32)owner->field18;
            record->positionZ = (s16)(s32)owner->field1C;
            return 0;
        }
        if (func_8000F44C(record->handle) == 0) {
            return 0;
        }
    }
    return 1;
}
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
typedef struct {
    u16 field0;
    s16 x;
    s16 y;
    s16 z;
    u8 pad8[8];
    u32 flags;
    u8 pad14[4];
    SoundOwnerState *owner;
    u16 *ids;
} SoundListRecord;

s32 func_8000EFB4(SoundListRecord *record, s32 arg1, s32 *active,
                  u8 *arg3, s32 arg4, s32 *output, u16 *sound) {
    SoundOwnerState *owner = record->owner;
    s32 value;
    u16 *id;
    s32 soundId;

    if (owner != 0) {
        value = *active;
        if (value != 0) {
            if (owner->field0 != 0) {
                for (id = record->ids; *id != 0; id++) {
                    if ((owner->field84 == *id) || !(record->flags & 1)) {
                        *output = ((owner->field184 >> 3) & 0x30) * 2;
                        record->x = (s32)owner->field14;
                        record->y = (s32)owner->field18;
                        record->z = (s32)owner->field1C;
                        return 0;
                    }
                }
            }
            soundId = *sound;
            if (soundId == 0xCA) {
                func_80010F30(0xCB, value & 0xFFFF, arg3[3], 0, *output);
            } else if (soundId == 0x2CF) {
                func_80010F30(0x2D7, value & 0xFFFF, arg3[3], 0, *output);
                func_80010F30((func_850ADA20() % 3U) + 0x2EB,
                             0x3E80, arg3[3], 0, *output);
            } else if (soundId == 0x2D2) {
                func_80010F30(0x2DA, value & 0xFFFF, arg3[3], 0, *output);
                func_80010F30((func_850ADA20() % 3U) + 0x2EB,
                             0x3E80, arg3[3], 0, *output);
            }
        }
    }
    return 1;
}
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
s32 func_80003C40(s32, s32, s32, s32);
void func_80011E88(s32);
void func_80017780(u8, u16);
extern u8 *D_80041F5C;
extern s32 D_80041F54;
extern f32 D_80041F58;
extern s32 D_80041FDC;
extern f32 D_8002C3F8;
extern f32 D_8002C3FC;

void func_8000F248(s32 mode) {
    func_8000F1A8();
    if (mode == 4) {
        D_80041F54 = 0;
        D_80041F58 = D_8002C3F8;
    } else {
        D_80041F54 = 0x59D8;
        D_80041F58 = D_8002C3FC;
    }
    if (mode == 0x35) {
        D_80041FD9 = 0;
    } else if (mode == 0x36) {
        D_80041FD9 = 0;
    } else if (mode == 0x3C) {
        D_80041FD9 = 0;
        D_80041FD8 = 0x3C;
    } else if (mode == 0x27) {
        D_80041FD9 = 0;
        D_80041FD8 = 0x28;
    } else if ((mode == 0x3A) || (mode == 0x40)) {
        D_80041FD9 = 0;
        D_80041FD8 = 0x3C;
    }
    D_80041F5C = (u8 *)func_80003C40(0x6E2, 1, 0, 0);
    func_800226F0(D_80041F5C, 0x6E2);
    if (mode == 0x31) {
        D_80041FDC = 0x36B0;
    } else {
        D_80041FDC = 0x59D8;
    }
    func_80011E88(mode);
    D_80041F60 = D_80041F61 = 0;
    func_80017780(0, ((u16 *)&D_80041F54)[1]);
    func_80017780(1, ((u16 *)&D_80041F54)[1]);
    func_80017780(2, 0x59D8);
}
void func_80017594(struct sndstate *);

s32 func_800173C4(struct sndstate **);

s32 func_8000F3D0(u16 arg0) {
    SoundHandleEntry *entry;
    s32 index;

    index = arg0 & 0xF;
    entry = &D_800425E0[index];
    if ((entry->state != 0) &&
        ((entry->id == arg0) || (arg0 == index)) &&
        (func_800173C4(&entry->state) != 0)) {
        return 1;
    }
    return 0;
}
s32 func_80022DC0(void);
void func_80022DE0(s32);

s32 func_8000F44C(u16 arg0) {
    s32 savedMask;
    SoundHandleEntry *entry;
    struct sndstate *state;
    s32 handle;

    savedMask = func_80022DC0();
    handle = arg0;
    entry = &D_800425E0[handle & 0xF];
    state = entry->state;
    if ((state != 0) && (entry->id == handle) &&
        (*((u8 *)state + 0x53) & 2)) {
        func_80022DE0(savedMask);
        return 1;
    }
    func_80022DE0(savedMask);
    return 0;
}
extern u8 D_800426A0[];

s32 func_8000F4D8(u16 arg0) {
    s32 index;

    arg0 &= 0x7FFF;
    index = 0;
    do {
        if (D_800425E0[index].state != 0) {
            if ((D_800425E0[index].value & 0x7FFF) == arg0) {
                if (func_800173C4(&D_800425E0[index].state) != 0) {
                    return 1;
                }
            }
        }
        index++;
    } while ((SoundHandleEntry *)D_800426A0 != &D_800425E0[index]);
    return 0;
}
extern u8 *D_80041F5C;

s32 func_8000F568(s32 base, s32 count) {
    s32 mask;
    u32 initial;
    s32 choice;
    u8 *entry;
    u8 current;
    s32 available;
    u8 updated;

    initial = func_850ADA20() % (u32)count;
    choice = initial;
    if (base >= 0x6E2) {
        return 1;
    }
    if (count < 2) {
        return base;
    }
    if (D_80041F5C != 0) {
        entry = D_80041F5C + base;
        current = *entry;
        if (count < 8) {
            if (!(current & 0x80) ||
                (mask = (1 << count) - 1, !((s32)current & mask))) {
                mask = (1 << count) - 1;
                current = 0xFF;
            }
            if (!(current & (1 << initial))) {
                do {
                    choice = (choice + 1) % count;
                } while (!(current & (1 << choice)));
            }
            available = current;
            updated = current ^ (1 << choice);
            *entry = updated;
            if (!(updated & mask)) {
                D_80041F5C[base] = available ^ mask;
            }
        } else {
            *entry = initial + 1;
        }
    }
    return (u32)base + (u32)choice;
}

typedef struct {
    s32 x0;
    s32 y4;
    s32 z8;
    s32 xC;
    s32 y10;
    s32 z14;
    f32 field18;
} SoundSpatialRecord;

extern SoundSpatialRecord D_80041F68[];
extern s32 D_80082FA0;
s32 func_8000A420(s32, s32, s32, f32, s32, s32, s32, s32, s32,
                 s32 *, s32 *, s32 *);


#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000F6B8 CURRENT (230) */
s32 func_8000F6B8(s32 arg0, s16 arg1, s16 arg2, s16 arg3,
                   s32 *output, s32 nearDistance, s32 farDistance) {
    s32 result;
    SoundSpatialRecord *selected;
    s32 index;
    s32 dx;
    s32 dy;
    s32 bestX;
    s32 bestY;
    s32 bestZ;
    s32 dz;
    u32 distance;
    u32 closest;

    if (D_80082FA0 != 0) {
        closest = 0xFFFFFFFF;
        for (index = 0; index <= D_80082FA0; index++) {
            dx = arg1 - D_80041F68[index].xC;
            dy = arg2 - D_80041F68[index].y10;
            dz = arg3 - D_80041F68[index].z14;
            distance = dx * dx + dy * dy + dz * dz;
            if (distance < closest) {
                closest = distance;
                selected = &D_80041F68[index];
                bestX = dx;
                bestY = dy;
                bestZ = dz;
            }
        }
    } else {
        selected = D_80041F68;
        bestX = arg1 - selected->xC;
        bestY = arg2 - selected->y10;
        bestZ = arg3 - selected->z14;
    }
    func_8000A420(bestX, bestY, bestZ, selected->field18,
                 arg1 - selected->x0, arg2 - selected->y4, arg3 - selected->z8,
                 (s16)farDistance, (s16)nearDistance, output, &result, 0);
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000F6B8 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000F6B8.s")
s32 func_8000F3D0(u16);
f32 func_80019AB0(s32);
void func_80017714(struct sndstate *, s16, s32);

void func_8000F85C(u16 arg0, s16 arg1, s32 arg2) {
    if ((arg0 >= 0x10) && (func_8000F3D0(arg0) != 0)) {
        if (arg1 == 0x10) {
            f32 pitch;
            pitch = func_80019AB0(arg2);
            arg2 = *(s32 *)&pitch;
        } else if (arg1 == 0x11) {
            arg1 = 0x10;
        }
        func_80017714(D_800425E0[arg0 & 0xF].state, arg1, arg2);
    }
}

s32 func_8000F6B8(s32, s16, s16, s16, s32 *, s32, s32);
void func_8000F85C(u16, s16, s32);

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
void func_8000F9D4(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {
    s32 value;

    func_8000F6B8(-1, arg1, arg2, arg3,
                  &value, 0x7FF8, 0x7FFD);
    func_8000F85C((u16)((u32 *)&arg0)[0], 4, value & 0x7F);
    func_8000F85C((u16)((u32 *)&arg0)[0], 0x100, value & 0x80);
}
extern SoundArrayRecord D_80041FE0[];
void func_80011624(SoundArrayRecord *, s32 *, s32, s32);
s32 func_85083E0C(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000FA64 CURRENT (1483) */
u16 func_8000FA64(u16 sound, s16 x, s16 y, s16 z, s32 volume,
                  u16 farDistance, s16 nearDistance, void *callback,
                  s32 owner, s32 key, s32 flags, s32 cents) {
    s32 count;
    s32 index;

    index = D_80042760;
    if (D_80042760 < 0x20) {
        D_80042760++;
    } else {
        return 0;
    }
    if (callback != 0) {
        D_80041FE0[index].flags = flags | 0x12;
    } else {
        D_80041FE0[index].flags = (flags & 0x108) | 2;
    }
    if (flags & 0x40) {
        s16 height;

        height = (s16)func_85083E0C((u8)x);
        y = height;
        if (height == -1) {
            return 0;
        }
    }
    D_80041FE0[index].handle = 0;
    D_80041FE0[index].field23 = 0;
    D_80041FE0[index].field22 = 0;
    D_80041FE0[index].field0 = sound;
    D_80041FE0[index].positionX = x;
    D_80041FE0[index].positionY = ((s16 *)&y)[0];
    D_80041FE0[index].positionZ = z;
    D_80041FE0[index].field8 = farDistance;
    D_80041FE0[index].fieldA = nearDistance;
    D_80041FE0[index].valueC = volume;
    D_80041FE0[index].callback = callback;
    D_80041FE0[index].owner = (void *)owner;
    D_80041FE0[index].key = key;
    D_80041FE0[index].pitch = func_80019AB0(cents);
    D_80041FE0[index].field26 = 0;
    D_80041FE0[index].field28 = 0;
    D_80041FE0[index].cents = cents;
    count = D_80042760;
    func_80011624(D_80041FE0, &D_80042760, index, index + 1);
    if (count == D_80042760) {
        D_80041FE0[index].flags |= 0x1000;
        return D_80041FE0[index].handle;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000FA64 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000FA64.s")
extern SoundArrayRecord D_80041FE0[];

void func_8000FC18(u16 sound, s16 x, s16 y, s16 z, u16 arg4) {
    s32 index;
    s32 soundId;

    soundId = sound;
    for (index = 0; index < D_80042760; index++) {
        if ((soundId == D_80041FE0[index].field0) &&
            (x == D_80041FE0[index].positionX) &&
            (y == D_80041FE0[index].positionY) &&
            (z == D_80041FE0[index].positionZ) &&
            ((D_80041FE0[index].field8 & 0x7FFF) == arg4)) {
            if (D_80041FE0[index].handle != 0) {
                func_800111C8(D_80041FE0[index].handle);
            }
            D_80041FE0[index].flags |= 0x80;
        }
    }
}

void func_8000FD38(void *callback, void *owner, s32 key) {
    s32 index;

    for (index = 0; index < D_80042760; index++) {
        if ((callback == D_80041FE0[index].callback) &&
            (owner == D_80041FE0[index].owner) && (key == D_80041FE0[index].key)) {
            if (D_80041FE0[index].handle != 0) {
                func_800111C8(D_80041FE0[index].handle);
            }
            D_80041FE0[index].flags |= 0x80;
        }
    }
}

void func_8000FDF4(u16 arg0) {
    s32 index;
    s32 handleId = arg0;

    for (index = 0; index < D_80042760; index++) {
        if ((u32)D_80041FE0[index].handle == (u32)handleId) {
            if (D_80041FE0[index].handle != 0) {
                func_800111C8(D_80041FE0[index].handle);
            }
            D_80041FE0[index].flags |= 0x80;
        }
    }
}
s32 func_8000FE88(SoundArrayRecord *records, s32 index, s32 *count) {
    if (index < *count) {
        index = (u32)index * sizeof(SoundArrayRecord);
        if (((SoundArrayRecord *)((u8 *)records + (u32)index))->handle != 0) {
            func_800111C8(((SoundArrayRecord *)((u8 *)records + (u32)index))->handle);
        }
        ((SoundArrayRecord *)((u8 *)records + (u32)index))->flags |= 0x80;
        return 0;
    }
    return 1;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000FEF0 CURRENT (500) */
s32 func_8000FEF0(u16 arg0, void *owner, s32 key) {
    SoundArrayRecord *record;
    s32 index;
    u16 handle;

    if (arg0 == 0) {
        return -1;
    }
    handle = arg0;
    index = 0;
    if (D_80042760 > 0) {
        record = D_80041FE0;
        do {
            if ((record->handle == handle) && (owner == record->owner) &&
                (key == record->key) && !(record->flags & 0x80)) {
                return index;
            }
            index++;
            record++;
        } while (index < D_80042760);
    }
    return -1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000FEF0 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_8000FEF0.s")
s32 func_8000FF90(u8 *callback, void *owner, s32 key) {
    s32 index;

    for (index = 0; index < D_80042760; index++) {
        if ((callback == D_80041FE0[index].callback) &&
            ((owner == D_80041FE0[index].owner) || (owner == (void *)-1)) &&
            ((key == D_80041FE0[index].key) || (key == -1)) &&
            !(D_80041FE0[index].flags & 0x80)) {
            return index;
        }
    }
    return -1;
}
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
void func_800100E0(void *callback, void *owner, s32 key,
                  void *newCallback, void *newOwner, s32 newKey) {
    s32 index;

    for (index = 0; index < D_80042760; index++) {
        if ((callback == D_80041FE0[index].callback) &&
            (owner == D_80041FE0[index].owner) &&
            (key == D_80041FE0[index].key)) {
            D_80041FE0[index].callback = newCallback;
            D_80041FE0[index].owner = newOwner;
            D_80041FE0[index].key = newKey;
        }
    }
}
u16 func_8000FA64(u16, s16, s16, s16, s32, u16, s16,
                  void *, s32, s32, s32, s32);
void func_8000FD38(void *, void *, s32);
u16 func_80010BE8(u16, s32, u16, u8, s16, u8, u8);
extern u8 D_1000EE70[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80010154 CURRENT (2065) */
void func_80010154(u16 sound, SoundOwnerState *owner, s32 volume,
                   s16 arg3, u16 farDistance) {
    s32 result = 0;
    s32 flags = 0;
    u32 callback;

    if ((owner->field0 == 0) || (owner->field0 == 5)) {
        return;
    }
    if (owner->field318 != 0) {
        u32 mixFlags = owner->field184;

        result = func_80010BE8(owner->handle8E, sound, (u16)volume,
                              0x40, 0, ((mixFlags >> 3) & 0x30) * 2,
                              D_80041FD9);
    } else {
        if (owner->field4 == 0x16) {
            arg3 *= 2;
            if (farDistance < arg3) {
                arg3 = farDistance - 0xC8;
            }
        } else if ((owner->field4 == 5) || (owner->field4 == 0x4F) ||
                   (owner->field4 == 0x83)) {
            flags = 4;
        } else if ((owner->field13C != 0) &&
                   ((owner->field4 == 0x8A) || (owner->field4 == 0x23))) {
            flags = 0x100;
        }
        callback = (u32)D_1000EE70;
        func_8000FD38((void *)callback, owner, owner->field3B | 0x10000);
        if (owner->field0 != 0) {
            result = func_8000FA64(sound, (s16)(s32)owner->field14,
                                  (s16)(s32)owner->field18,
                                  (s16)(s32)owner->field1C, volume,
                                  farDistance, arg3,
                                  (void *)callback, (s32)owner,
                                  owner->field3B | 0x10000, flags, 0);
        }
    }
    owner->handle8E = result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80010154 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80010154.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_80010344 CURRENT (745) */
s32 func_80010344(u16 sound, void *arg1, u32 volume,
                  s16 nearDistance, u16 farDistance) {
    SoundOwnerState *owner = arg1;
    s32 flags = 0;
    u8 enabled;
    s32 mix;
    void *callback;

    if ((owner->field0 == 0) || (owner->field0 == 5)) {
        return 0;
    }
    if ((s32)volume < 0) {
        volume = -(s32)volume;
        flags = 0x100;
    }
    if (owner->field318 != 0) {
        enabled = D_80041FD9;
        mix = ((owner->field184 >> 3) & 0x30) * 2;
        if ((owner->field31C != 0) && (owner->field31C[0x94] == 1)) {
            enabled = 1;
            volume = 0x7FFF;
        }
        flags = func_80010BE8(owner->handle8C, (u16)sound, (u16)volume,
                              0x40, 0, mix, enabled);
    } else {
        if (owner->field4 == 0x16) {
            nearDistance *= 2;
            if (((u16 *)&farDistance)[0] < nearDistance) {
                nearDistance = ((u16 *)&farDistance)[0] - 0xC8;
            }
        } else if ((owner->field4 == 0x8A) && (owner->field13C != 0)) {
            flags |= 0x100;
        } else if ((owner->field4 == 0x4F) || (owner->field4 == 0x83)) {
            flags |= 4;
        }
        callback = D_1000EE70;
        func_8000FD38(callback, owner, owner->field3B | 0x20000);
        flags = func_8000FA64((u16)sound, (s16)(s32)owner->field14,
                              (s16)(s32)owner->field18,
                              (s16)(s32)owner->field1C, volume,
                              ((u16 *)&farDistance)[0], nearDistance,
                              *(void **)&callback, (s32)owner,
                              owner->field3B | 0x20000, flags, 0);
    }
    owner->handle8C = flags;
    return flags;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80010344 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80010344.s")
u16 func_8000FA64(u16, s16, s16, s16, s32, u16, s16,
                  void *, s32, s32, s32, s32);
extern u8 D_1000ECCC[];

void func_80010558(u16 sound, SoundOwnerState *owner, s32 volume,
                  s16 arg3, u16 arg4, s32 delay) {
    if (delay <= 0) {
        func_80010344(sound, owner, volume, arg3, arg4);
        return;
    }
    func_8000FA64(sound, (s16)(s32)owner->field14,
                  (s16)(s32)owner->field18, (s16)(s32)owner->field1C,
                  volume, arg4, arg3, D_1000ECCC,
                  delay, (s32)owner, 0, 0);
}
extern u8 D_1000EE70[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80010630 CURRENT (1802) */
void func_80010630(u16 sound, SoundOwnerState *owner, s32 volume,
                  s16 arg3, u16 arg4) {
    u16 localVolume;
    u32 currentValue = volume;

    if (owner->field0 != 0) {
        if (owner->field318 != 0) {
            localVolume = currentValue;
            currentValue = owner->field184;
            func_80010F30(sound, localVolume, 0x40, 0,
                          ((currentValue >> 3) & 0x30) * 2);
            return;
        }
        func_8000FA64(sound, (s16)(s32)owner->field14,
                      (s16)(s32)owner->field18, (s16)(s32)owner->field1C,
                      (s32)currentValue, arg4, arg3, D_1000EE70,
                      (s32)owner, owner->field3B, 0, 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80010630 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80010630.s")
extern u8 D_1000EDA0[];

void func_80010720(u16 arg0, SoundOwnerState *owner, s32 volume,
                  s16 arg3, u16 arg4, s32 delay) {
    if (delay <= 0) {
        func_80010630(arg0, owner, volume, arg3, arg4);
        return;
    }
    func_8000FA64(arg0, (s16)(s32)owner->field14,
                  (s16)(s32)owner->field18, (s16)(s32)owner->field1C,
                  volume, arg4, arg3, D_1000EDA0,
                  delay, (s32)owner, 0, 0);
}
void func_8000FD38(void *, void *, s32);

s32 func_8000F3D0(u16);
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
typedef struct {
    s32 value;
    u8 pad4[0x2C];
} SoundRecordValueSlot;

extern SoundRecordValueSlot D_80041FEC[];

void func_8001091C(SoundOwnerState *owner, s32 value) {
    s32 index;

    if ((value != 0) && (owner->field0 != 0)) {
        if (owner->field318 != 0) {
            if (owner->handle8E != 0) {
                func_8000F85C(owner->handle8E, 8, (s32)((u32 *)&value)[0]);
            }
        } else {
            index = func_8000FF90(D_1000EE70, owner, owner->field3B | 0x10000);
            if (index != -1) {
                D_80041FEC[index].value = value;
                return;
            }
            owner->handle8E = 0;
        }
    }
}
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
s32 func_8000FEF0(u16, void *, s32);

void func_80010AA8(SoundOwnerState *owner) {
    s32 index;
    SoundArrayRecord *record;

    if (owner->field318 != 0) {
        if ((owner->handle8C != 0) && (func_8000F44C(owner->handle8C) != 0)) {
            func_800111C8(owner->handle8C);
        }
        if ((owner->handle8E != 0) && (func_8000F44C(owner->handle8E) != 0)) {
            func_800111C8(owner->handle8E);
        }
    } else {
        index = func_8000FEF0(owner->handle8C, owner, owner->field3B);
        if (index != -1) {
            if (func_8000F44C(owner->handle8C) != 0) {
                func_800111C8(owner->handle8C);
            }
            record = &D_80041FE0[index];
            record->flags |= 0x80;
        }
        index = func_8000FEF0(owner->handle8E, owner, owner->field3B);
        if (index != -1) {
            if (func_8000F44C(owner->handle8E) != 0) {
                func_800111C8(owner->handle8E);
            }
            record = &D_80041FE0[index];
            record->flags |= 0x80;
        }
    }
    owner->handle8C = 0;
    owner->handle8E = 0;
}
extern void *D_8003E368;
struct sndstate *func_80017438(void *, s16, u16, u8, f32, u8, u8,
                               struct sndstate **);

u16 func_80010BE8(u16 arg0, s32 sound, u16 volume, u8 pan,
                  s16 cents, u8 arg5, u8 bus) {
    u16 result;
    u16 next;
    u32 index;

    index = arg0 & 0xF;
    if ((arg0 == D_800425E0[index].id) && (arg0 != 0)) {
        if ((D_800425E0[index].state != 0) &&
            (func_800173C4(&D_800425E0[index].state) != 0)) {
            func_80017594(D_800425E0[index].state);
            D_800425E0[index].state = 0;
        }
    } else if (((D_800425E0[index].state != 0) &&
                (func_800173C4(&D_800425E0[index].state) != 0)) ||
               (D_800425E0[index].value & 0x8000)) {
        index = 0;
        while ((index < 0x10) &&
               (((D_800425E0[index].state != 0) &&
                 (func_800173C4(&D_800425E0[index].state) != 0)) ||
                (D_800425E0[index].value & 0x8000))) {
            index++;
        }
    }
    if (volume < 0x64) {
        return 0;
    }
    if (index >= 0x10) {
        result = 0;
    } else {
        if (sound == 0) {
            return 0;
        }
        if ((sound & 0x7FFF) >= 0x6E3) {
            return 0;
        }
        result = D_800425E0[index].field2;
        next = result + 0x10;
        D_800425E0[index].id = result;
        if (next < 0x10) {
            next += 0x10;
        }
        D_800425E0[index].field2 = next;
        D_800425E0[index].value = sound;
        if (D_800425E0[index].state != 0) {
            ((u8 *)D_800425E0[index].state)[0x54] = 5;
        }
        if ((arg5 & 0x7F) + (u8)D_80041FD8 < 0x80) {
            arg5 = (u8)(arg5 + (u8)D_80041FD8);
        } else {
            arg5 = (u8)(arg5 | 0x7F);
        }
        func_80017438(D_8003E368, (sound & 0x7FFF), volume, pan,
                     func_80019AB0(cents), arg5, bus, &D_800425E0[index].state);
    }
    return result;
}
u16 func_80010BE8(u16, s32, u16, u8, s16, u8, u8);

u16 func_80010E78(s32 arg0, s32 arg1, u16 arg2, s32 arg3, s32 arg4,
                 s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10) {
    s32 value;
    u32 volume;

    volume = func_8000F6B8(arg5, (s16)arg6, (s16)arg7,
                           (s16)arg8, &value, (s16)arg9, (s16)arg10);
    volume = ((u32)arg2 * volume) >> 15;
    if (volume != 0) {
        return func_80010BE8((u16)arg0, arg1, (u16)volume,
                             value & 0x7F, ((s16 *)&arg3)[1],
                             (value & 0x80) | (u8)arg4, D_80041FD9);
    }
    return 0;
}
s32 func_80010F30(arg0, arg1, arg2, arg3, arg4)
s32 arg0;
u16 arg1;
u8 arg2;
s16 arg3;
s32 arg4;
{
    return func_80010BE8(0, arg0, arg1, arg2,
                        arg3, ((u8 *)&arg4)[3], D_80041FD9);
}
u16 func_80010E78(s32, s32, u16, s32, s32, s32, s32, s32, s32, s32, s32);

s32 func_80010F88(s32 arg0, u16 arg1, s16 arg2, u8 arg3, s32 arg4,
                 s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    return func_80010E78(0, arg0, arg1, arg2, arg3, arg4,
                        (s16)arg5, (s16)arg6, (s16)arg7, (s16)arg8, (s16)arg9);
}
typedef struct {
    u8 pad0[0xE];
    u16 fieldE;
} SoundOwnerScale;

extern SoundOwnerScale *D_800D1C90[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80010FFC CURRENT (935) */
s32 func_80010FFC(u16 arg0, s32 arg1, u16 arg2, s16 arg3,
                  u8 arg4, SoundOwnerState *owner) {
    s32 handle = arg0;
    u16 result;
    f32 scale;

    if ((owner == 0) || (owner->field0 == 0)) {
        return 0;
    }
    if (owner->field318 != 0) {
        result = func_80010BE8(handle, arg1, arg2, 0x40,
                              arg3, arg4, D_80041FD9);
    } else {
        arg2 = (u16)((arg2 + arg2 + arg2) >> 2);
        if (owner->field4 != 0xFF) {
            scale = (f32)(u32)D_800D1C90[owner->field4]->fieldE * owner->field14C;
        } else {
            scale = 0.0f;
        }
        if (scale > 256.0f) {
            scale = 1.0f;
        } else if (scale < 80.0f) {
            scale = 0.3125f;
        } else {
            scale *= 0.00390625f;
        }
        result = func_80010E78(handle, arg1, arg2, arg3,
                              arg4, 0, (s32)owner->field14,
                              (s32)owner->field18, (s32)owner->field1C,
                              0x1F4, (s32)(2000.0f * scale) + 0x1F5);
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80010FFC */
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

void func_8001123C(u16 arg0) {
    SoundHandleEntry *entry;
    entry = &D_800425E0[arg0 & 0xF];
    if ((entry->state != 0) && (entry->id == arg0)) {
        if (func_800112BC(arg0, 1) == 0) {
            func_80017594(entry->state);
            entry->state = 0;
        }
    }
}
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
#if 0 /* CONKER_DEFERRED_CANDIDATE func_80011310 CURRENT (3775) */
void func_80011310(void) {
    SoundHandleEntry *entry;
    SoundQueueEntry *cursor;
    SoundQueueEntry *end;
    SoundQueueEntry *destination;
    s32 count;
    s32 index;
    s32 flag;
    s32 remaining;
    struct sndstate *state;
    s32 operation;

    count = D_80041F50;
    flag = 0;
    index = 0;
    remaining = count;
    if (count > 0) {
        cursor = D_80041F10;
        do {
            operation = (u8)cursor->operation;
            destination = (SoundQueueEntry *)((index << 2) + (s32)D_80041F10);
            if (operation > 0) {
                end = &D_80041F10[count];
                cursor->operation = operation - 1;
            } else {
                flag = 1;
                entry = &D_800425E0[(u8)cursor->index];
                if (entry->id == (u16)cursor->value) {
                    state = entry->state;
                    entry->id = 0;
                    entry->value = 0;
                    if (state != 0) {
                        func_80017594(state);
                        count = D_80041F50;
                    }
                    entry->state = 0;
                }
                remaining--;
                end = &D_80041F10[count];
            }
            if (destination != cursor) {
                D_80041F10[index] = *cursor;
            }
            cursor++;
            if (flag != 0) {
                index++;
            } else {
                flag = 0;
            }
        } while ((u32)cursor < (u32)end);
    }
    D_80041F50 = remaining;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80011310 */
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

s32 func_800114D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                  s32 arg4, s32 arg5, s32 *arg6, s32 *arg7, s32 *arg8) {
    SoundSpatialRecord *best;
    s32 dx;
    s32 dy;
    s32 dz;
    u32 distance;
    s32 result;
    s32 output;
    u32 index;
    u32 bestDistance;

    best = D_80041F68;
    if (D_80082FA0 != 0) {
        bestDistance = 0xFFFFFFFF;
        for (index = 0; index <= (u32)D_80082FA0; index++) {
            dx = arg0 - D_80041F68[index].xC;
            dy = arg1 - D_80041F68[index].y10;
            dz = arg2 - D_80041F68[index].z14;
            distance = dx * dx + dy * dy + dz * dz;
            if (distance < bestDistance) {
                bestDistance = distance;
                best = &D_80041F68[index];
            }
        }
    }
    result = func_8000A420(arg0 - best->xC, arg1 - best->y10, arg2 - best->z14,
                 best->field18, arg0 - best->x0, arg1 - best->y4,
                 arg2 - best->z8, arg4, arg5, arg6, &output, arg8);
    *arg7 = (u32)(output * arg3) >> 15;
    return result;
}
s32 func_800114D0(s32, s32, s32, s32, s32, s32, s32 *, s32 *, s32 *);
s32 func_8000A750(s32, s32, s32, s32, f32, s32, s32, s32, s32, s32,
                  s32 *, s32 *, s32 *);
s32 func_8000FE88(SoundArrayRecord *, s32, s32 *);
extern f32 D_8002C400;
extern f32 D_8002C404;
extern u8 D_800BE615;

typedef s32 (*SoundRecordCallback)(void *, s32 *, u32 *, s32 *, s32 *,
                                    s32 *, u16 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80011624 CURRENT (298) */
void func_80011624(SoundArrayRecord *records, s32 *count, s32 start, s32 end) {
    SoundArrayRecord *record;
    u32 flags;
    s32 pan;
    s32 temporary;
    u32 volume;
    s32 active;
    s32 distance;
    s32 cents;
    u16 sound;
    u16 handle;
    s32 mix;
    union {
        f32 value;
        s32 bits;
    } pitch;
    s32 index;
    s32 offset;
    s32 *panOut;
    s32 fxmix;
    s32 eventValue;
    f32 ratio;
    f32 unclampedRatio;
    f32 pitchDelta;

    index = start;
    if ((index < *count) && (index < end)) {
        offset = index * sizeof(*records);
        record = (SoundArrayRecord *)((u8 *)records + offset);
        do {
        flags = record->flags;
        if (record->flags & 0x80) {
            goto next_record;
        }
        if (record->flags & 0x1000) {
            record->flags &= ~0x1000;
            goto next_record;
        }
        handle = record->handle;
        if ((flags & 1) && (handle != 0) && (func_8000F3D0(handle) == 0)) {
            handle = 0;
            flags &= ~1;
            if (!(flags & 8)) {
                flags |= 0x80;
                record->field0 = 0;
            }
            record->field26 = 0;
            record->field22 = 0;
            record->handle = 0;
            record->flags = flags;
            record->pitch = 1.0f;
        }
        if ((flags & 2) || (handle == 0)) {
            if (flags & 0x100) {
                pan = 0x40;
                panOut = 0;
            } else {
                panOut = &pan;
            }
            if (flags & 0x40) {
                active = func_8000A750(record->positionY,
                         D_80041F68->xC, D_80041F68->y10, D_80041F68->z14,
                         D_80041F68->field18, D_80041F68->x0,
                         D_80041F68->y4, D_80041F68->z8,
                         record->field8, record->fieldA, &pan,
                         (s32 *)&volume, &distance);
                volume = (u32)(record->valueC * volume) >> 15;
            } else {
                active = func_800114D0(record->positionX, record->positionY,
                         record->positionZ, record->valueC, record->field8,
                         record->fieldA, panOut, (s32 *)&volume, &distance);
            }
            if (D_800BE615 != 0) {
                volume = 0;
            }
            cents = record->cents;
            mix = record->field23;
            sound = record->field0;
            if ((flags & 0x10) && (record->callback != 0)) {
                record->flags = flags;
                if (((SoundRecordCallback)record->callback)((void *)(offset + (u32)records),
                        &active, &volume, &pan, &cents, &mix, &sound) != 0) {
                    func_8000FE88(records, index, count);
                    goto next_record;
                }
                handle = record->handle;
                flags = record->flags;
            }
            if (sound != 0) {
                if (volume != 0) {
                    fxmix = (pan & 0x80) | mix;
                    pan &= 0x7F;
                    if (flags & 0x200) {
                        pan = 0x80 - pan;
                        if (pan == 0x80) {
                            pan = 0x7F;
                        }
                        fxmix ^= 0x80;
                    }
                    pitch.value = func_80019AB0(cents);
                    if (handle == 0) {
                        if (flags & 0xC00) {
                            if ((flags & 0xC00) == 0x400) {
                                temporary = 0;
                            } else {
                                temporary = 1;
                            }
                        } else {
                            temporary = D_80041FD9;
                        }
                        handle = func_80010BE8(0, sound, (u16)volume,
                                             (u8)pan, cents, fxmix, temporary);
                        if (handle != 0) {
                            flags |= 1;
                            record->field0 = sound;
                        }
                    } else {
                        if (volume != (u16)record->field26) {
                            func_8000F85C(handle, 8, volume);
                        }
                        if (pan != (record->field22 & 0x7F)) {
                            func_8000F85C(handle, 4, pan);
                        }
                        if (fxmix != (record->field23 | (record->field22 & 0x80))) {
                            func_8000F85C(handle, 0x100, fxmix);
                        }
                        if (flags & 4) {
                            temporary = ((u16)record->field28 - distance) * D_800BE9E4 / 3;
                            if (temporary >= 0x16F) {
                                ratio = 2.0f;
                            } else {
                                unclampedRatio = D_8002C400 / (f32)(0x16F - temporary);
                                ratio = unclampedRatio;
                                if (unclampedRatio > 2.0f) {
                                    ratio = 2.0f;
                                } else if (unclampedRatio < 0.5f) {
                                    ratio = 0.5f;
                                }
                            }
                            pitch.value *= ratio;
                            pitchDelta = pitch.value - record->pitch;
                            pitch.value = record->pitch + pitchDelta * D_8002C404;
                        }
                        eventValue = pitch.bits;
                        if (pitch.value != record->pitch) {
                            func_8000F85C(handle, 0x11, eventValue);
                        }
                    }
                    record->field28 = distance;
                    record->field26 = volume;
                    record->field22 = pan | fxmix;
                    record->field23 = mix;
                    record->pitch = pitch.value;
                } else if (flags & 8) {
                    if (handle != 0) {
                        func_800111C8(handle);
                    }
                    handle = 0;
                    flags &= ~1;
                } else {
                    func_8000FE88(records, index, count);
                    goto next_record;
                }
            }
        }
        record->handle = handle;
        record->flags = flags;
next_record:
        index++;
        offset += sizeof(*records);
        record++;
        } while ((index < *count) && (index < end));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80011624 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_EB00/func_80011624.s")

typedef struct {
    u8 pad0[0x2C];
    u32 flags;
    u8 pad30[0x274];
    f32 field2A4;
    f32 field2A8;
    f32 field2AC;
    u8 pad2B0[0x48];
    f32 field2F8;
    f32 field2FC;
    f32 field300;
    u8 pad304[0x7C];
    f32 field380;
    u8 pad384[0x61C];
} SoundListenerState;

extern SoundListenerState *D_800DBFF0;
void func_80011310(void);

void func_80011BB8(void) {
    s32 index;
    s32 kept;
    s32 delta;

    if ((D_80041F60 == 0) && (D_80041F61 == 0)) {
        for (index = 0; index <= D_80082FA0; index++) {
            SoundListenerState *current = &D_800DBFF0[index];

            if ((D_80082FA0 != 0) || (current->flags & 0x80000)) {
                D_80041F68[index].x0 = (s32)current->field2F8;
                D_80041F68[index].y4 = (s32)current->field2FC;
                D_80041F68[index].z8 = (s32)current->field300;
            } else {
                D_80041F68[index].x0 = (s32)current->field2A4;
                D_80041F68[index].y4 = (s32)current->field2A8;
                D_80041F68[index].z8 = (s32)current->field2AC;
            }
            D_80041F68[index].xC = (s32)current->field2F8;
            D_80041F68[index].y10 = (s32)current->field2FC;
            D_80041F68[index].z14 = (s32)current->field300;
            D_80041F68[index].field18 = current->field380;
        }
        func_80011310();
        func_80011624(D_80041FE0, &D_80042760, 0, D_80042760);
        for (index = 0, kept = 0; index < D_80042760; index++) {
            D_80041FE0[kept] = D_80041FE0[index];
            if (!(D_80041FE0[kept].flags & 0x80)) {
                kept++;
            }
        }
        D_80042760 = kept;
    }
    if ((D_80041F54 != D_80041FDC) || (D_80041F60 != D_80041F61)) {
        if (D_80041F61 == 1) {
            func_80017780(0, 0);
            func_80017780(1, 0);
        } else {
            func_80017780(0, D_80041F54);
            func_80017780(1, ((u16 *)&D_80041F54)[1]);
            delta = (s32)((f32)(D_80041FDC - D_80041F54) * D_80041F58);
            if (delta != 0) {
                D_80041F54 += delta;
            } else {
                D_80041F54 = D_80041FDC;
            }
        }
        D_80041F60 = D_80041F61;
    }
}
void func_80011E88(s32 arg0) {
}


void func_80011E94(s32 arg0) {
    if (arg0 != 0) {
        D_80041F61 = 1;
        return;
    }
    D_80041F61 = 0;
}
typedef struct {
    u16 base;
    u16 count;
} SoundVariant;

extern SoundVariant D_8002C240[][5];
s32 func_8510F8CC(s32);
s32 func_8000F568(s32, s32);

s32 func_80011EB8(s32 arg0, s16 *volume, s32 variant) {
    s32 sound;

    arg0 = func_8510F8CC(arg0);
    if (volume != 0) {
        if (D_80082FA0 != 0) {
            *volume = 0x7FFF / (D_80082FA0 + 1);
        } else {
            *volume = 0x7FFF;
        }
    }
    sound = D_8002C240[arg0][variant].base;
    if (D_8002C240[arg0][variant].count >= 2) {
        sound = func_8000F568(sound, D_8002C240[arg0][variant].count);
    }
    return sound & 0xFFFF;
}
