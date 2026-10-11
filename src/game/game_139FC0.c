#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_139FC0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_call_connected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1510CB10
 * - func_1510CDB8
 * - func_1510CE60
 * - func_1510D0EC
 * - func_1510D404
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game139FC0LevelEntry {
    u8 pad0[0x5F0];
    s32 flags5F0;
    u8 pad5F4[0x3AC];
} Game139FC0LevelEntry;
extern Game139FC0LevelEntry *D_800DBFF0;
extern s32 D_800BE9E4;
extern u16 D_800D9E70[][3];
extern u8 D_800D9E88[], D_800D9E98[], D_800D9EA8[], D_800D9EB4[], D_800D9EB8[];
extern u8 D_800D9B68[], D_800D9B78[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510CB10 CURRENT (6625) */
void func_1510CB10(s32 arg0) {
    register u8 *request;
    register volatile u16 *phase;
    register u8 *first;
    register u8 *second;
    register u8 *current;
    register u8 *amplitude;
    register u8 *phaseStep;
    register s32 step;
    register s32 index;
    register s32 enabled;
    register s32 value;
    register s32 target;
    register s32 delta;
    register s32 magnitude;
    register f32 wave;
    register s32 adjustment;
    register s16 nextPhase;

    if (D_800DBFF0[arg0].flags5F0 & 1) {
        request = &D_800D9EB8[arg0 * 3];
        current = &D_800D9EA8[arg0 * 3];
        enabled = *request;
        step = D_800BE9E4 * 2;
        phase = D_800D9E70[arg0];
        second = &D_800D9B78[arg0 * 3];
        first = &D_800D9B68[arg0 * 3];
        phaseStep = &D_800D9E88[arg0 * 3];
        amplitude = &D_800D9E98[arg0 * 3];
        index = 0;
        do {
            value = *current;
            if (enabled != 0) {
                target = D_800D9EB8[arg0 * 3 + index];
            } else {
                target = D_800D9EB4[index];
            }
            delta = target - value;
            if (delta != 0) {
                if (delta < 0) {
                    magnitude = -delta;
                } else {
                    magnitude = delta;
                }
                if (magnitude < step) {
                    value = target;
                } else if (delta < 0) {
                    value -= step;
                } else {
                    value += step;
                }
                *current = value;
            }
            wave = func_150489B0((*phase >> 4) & 0xFF);
            wave *= (f32)(u32)*amplitude;
            index++;
            current++;
            amplitude++;
            adjustment = (s32)wave + value - 127;
            if (adjustment >= 0) {
                *first += adjustment;
            } else {
                *second -= adjustment;
            }
            if (*first >= 128) {
                *first = 127;
            }
            first++;
            if (*second >= 128) {
                *second = 127;
            }
            nextPhase = *phase + *phaseStep;
            phase++;
            phase[-1] = nextPhase;
            second++;
            phaseStep++;
            phase[-1] = nextPhase & 0xFFF;
        } while (index != 3);
        *request = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510CB10 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_139FC0/func_1510CB10.s")

extern u8 D_800D9B68[];
extern u8 D_800D9B78[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510CDB8 CURRENT (1625) */
void *func_1510CDB8(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_t0;
    u8 *temp_a0;
    u8 *temp_t1;
    u8 *temp_t3;

    temp_t0 = arg3 * 3;
    *(s32 *)arg0 = 0xFA00F200;
    temp_t1 = D_800D9B68 + temp_t0;
    *(s32 *)((u8 *)arg0 + 4) = (s32)(((u32)temp_t1[2] << 8) | ((u32)temp_t1[0] << 0x18) | ((u32)temp_t1[1] << 0x10) | (arg1 & 0xFF));
    temp_a0 = (u8 *)arg0 + 8;
    *(s32 *)temp_a0 = 0xFB000000;
    temp_t3 = D_800D9B78 + temp_t0;
    *(s32 *)(temp_a0 + 4) = (s32)(((u32)temp_t3[2] << 8) | ((u32)temp_t3[0] << 0x18) | ((u32)temp_t3[1] << 0x10) | (arg2 & 0xFF));
    return temp_a0 + 8;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510CDB8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_139FC0/func_1510CDB8.s")
void *func_10003C40(s32, s32, s32, s32);
s32 func_1510D0EC(s32, s32 *, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510CE60 CURRENT (7208) */
s32 func_1510CE60(s8 *volatile arg0, volatile s32 arg1, volatile s32 arg2, volatile s32 arg3, s16 **volatile arg4) {
    register s32 index;
    s32 size;
    register s32 flags;
    register s32 failure;
    volatile s32 addressHome;
    register s32 count;
    register s8 *command;
    register s32 resource;
    register s32 address;
    register s32 bit;
    register u8 *byte;
    register s16 *list;
    register s32 total;
    register s32 mask;
    register s32 id;
    volatile s32 countHome;
    u8 bitmap[971];

    failure = 0;
    if (arg4 != 0) {
        for (index = 0; index < 971; index++) {
            bitmap[index] = 0;
        }
        countHome = 0;
    }
    count = countHome;
    index = 0;
    command = arg0;
    if (*command != -0x21) {
        /* Raw code carries an unset stack word until the first resource load. */
        address = addressHome;
        do {
            if (*command == -3 &&
                ((resource = *(s32 *)(command + 4), arg1 == 0) || !(resource & 0xFF000000)) &&
                (u32)(resource & 0xFF000000) < 0x06000000U) {
                flags = resource >> 22;
                bit = resource & 0x0F000000;
                resource &= 0xF03FFFFF;
                if (bit == 0) {
                    countHome = count;
                    address = func_1510D0EC(resource, &size, arg3, arg2);
                    count = countHome;
                    *(s32 *)(command + 4) = address;
                    if (arg4 != 0) {
                        byte = &bitmap[resource >> 3];
                        bit = 1 << (resource & 7);
                        if (!(*byte & bit)) {
                            *byte |= bit;
                            count++;
                        }
                    }
                } else {
                    flags = 0;
                }
                if (address == (s32)0x80000000U) {
                    failure = 1;
                }
                if (flags != 0) {
                    bit = *(s32 *)(command + 4);
                    if (flags & 1) {
                        bit = (s32)((u32)bit + (u32)size - 0x200U);
                        *(s32 *)(command + 4) = bit;
                    } else if (flags & 2) {
                        bit = (s32)((u32)bit + (u32)size - 0x20U);
                        *(s32 *)(command + 4) = bit;
                    }
                    *(s32 *)(command + 4) = bit | ((flags & 0x3C) << 22);
                }
            }
            index++;
            command = (s8 *)((u32)arg0 + ((u32)index << 3));
        } while (*command != -0x21);
        addressHome = address;
    }
    total = count + 1;
    if (arg4 != 0) {
        countHome = count;
        list = func_10003C40(total * 2, 1, 0, 2);
        count = countHome;
        *arg4 = list;
        if (list != 0) {
            *list = count;
            list++;
            mask = 1;
            index = 0;
            id = 0;
            if (total != 1) {
                byte = bitmap;
                do {
                    if (*byte & mask) {
                        list[index] = id;
                        index++;
                    }
                    if (mask != 0x80) {
                        mask *= 2;
                    } else {
                        mask = 1;
                        byte++;
                    }
                    id++;
                } while (index + 1 != total);
            }
        }
    }
    return failure == 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510CE60 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_139FC0/func_1510CE60.s")
void func_10004074(s32);
void func_10004514(s32, s32, s32, s32);
void func_10006240(s32, void *, s32);
u8 *func_1510D374(s32);
u8 *func_10003C6C(s32, s32, s32, s32, s32);
extern u8 D_80091D20;
extern u16 D_800B87A0[];
extern u8 D_800D9F68[];
extern s32 D_800B0E58[];
extern s8 D_800BC448[];
extern s32 D_800D9F58, D_800D9F5C, D_8003809C;
extern u8 D_800DBDBA;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510D0EC CURRENT (2543) */
s32 func_1510D0EC(s32 arg0, s32 *arg1, volatile s32 arg2, s32 arg3) {
    register s32 compressedSize;
    register s32 romAddress;
    register s32 buffer;
    register s32 output;
    register s32 odd;
    register s32 offset;
    register s32 *entry;
    register s32 alignedSize;
    register s32 size;
    register s32 result;
    s8 *state;
    u8 *count;
    s32 previousCount;

    if (arg0 < D_800D9F58) {
        D_800D9F58 = arg0;
    }
    if (D_800D9F5C < arg0) {
        D_800D9F5C = arg0;
    }
    if (arg0 >= 0x1E52 || arg0 < 0) {
        return (s32)0x80000000U;
    }
    offset = arg0 * 2;
    compressedSize = *(u16 *)(&D_80091D20 + offset);
    if (compressedSize == 0) {
        entry = &D_800B0E58[arg0];
        *entry = (s32)0x80000000U;
        goto ready;
    }
    entry = &D_800B0E58[arg0];
    if (*entry == -1) {
        D_800DBDBA = 5;
        if (arg2 == 0x3F) {
            arg2 = 0x3E;
        }
        size = (s32)func_1510D374(arg0);
        romAddress = size;
        if (size & 1) {
            romAddress = (s32)((u32)size - 1U);
            odd = 1;
        } else {
            odd = 0;
        }
        size = compressedSize + odd;
        if (size & 1) {
            size++;
        }
        alignedSize = (size + 15) & ~15;
        buffer = (s32)func_10003C6C(alignedSize, 1, 2, 1, 2);
        if (buffer == 0) {
            return (s32)0x80000000U;
        }
        func_10004514(romAddress, buffer, alignedSize, 1);
        output = (s32)func_10003C6C(*(u16 *)((u8 *)D_800B87A0 + offset),
                                    1, 1, 0, 2);
        if (output == 0) {
            func_10004074(buffer);
            return (s32)0x80000000U;
        }
        func_10006240((s32)((u32)buffer + (u32)odd),
                       (void *)output, D_8003809C);
        func_10004074(buffer);
        *entry = output;
        D_800D9F68[arg0] = 0;
    }
ready:
    if (arg1 != 0) {
        *arg1 = *(u16 *)((u8 *)D_800B87A0 + offset);
    }
    result = *entry;
    state = &D_800BC448[arg0];
    size = arg2;
    if (*state < size) {
        *state = size;
    }
    count = &D_800D9F68[arg0];
    if (arg3 != 0) {
        previousCount = *count;
        if (previousCount < 255) {
            *count = previousCount + 1;
        }
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510D0EC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_139FC0/func_1510D0EC.s")
extern u8 D_1A37E0;
extern u8 D_80091D20;

/* Descriptive role: flat_asset_rom_address.
 * Evidence: docs/evidence/assets/naming/model_resource_role_names.md.
 */
u8 *func_1510D374(s32 resourceIndex) {
    u8 *romAddress;
    s32 sizeIndex;

    romAddress = &D_1A37E0;
    sizeIndex = 0;
    while (sizeIndex < resourceIndex) {
        romAddress += ((u16 *)&D_80091D20)[sizeIndex];
        sizeIndex++;
    }
    return romAddress;
}
void func_10004074(s32);
void func_10006240(s32, void *, s32);
void func_150AD770(void);
extern s32 D_8003809C, D_8003C8E0;
extern s32 D_800B0E58[];
extern s8 D_800BC448[];
extern s32 D_800D9F58, D_800D9F5C, D_800DBDBC;
extern u8 D_800D9F60, D_800DBDBA;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510D404 CURRENT (3874) */
void func_1510D404(void) {
    s32 stop;
    s32 end;
    s32 start;
    s32 index;
    s8 *cursor;
    s8 state;
    s32 old_allocation;

    end = D_800D9F5C;
    if (end != -1 && (D_800DBDBA != 0 || D_800D9F60 == 0)) {
        if (D_800DBDBA != 0) {
            D_800DBDBA--;
        }
        start = D_800D9F58;
        D_800D9F58 = 0xFFFF;
        D_800D9F5C = -1;
        if (start < 0 || end >= 0x1E53) {
            D_8003C8E0 = 0x0C000046;
            func_150AD770();
        }
        D_800DBDBC = -1;
        index = start;
        if (end >= start) {
            cursor = &D_800BC448[start];
            stop = end + 1;
            do {
                state = *cursor;
                if (state != 0) {
                    if (state < 4) {
                        *cursor = state - 1;
                        if (*cursor == 0) {
                            D_800DBDBC = index;
                            func_10004074(D_800B0E58[index]);
                            D_800B0E58[index] = -1;
                        } else {
                            if (index < D_800D9F58) {
                                D_800D9F58 = index;
                            }
                            if (D_800D9F5C < index) {
                                D_800D9F5C = index;
                            }
                        }
                    } else if (state & 0x40) {
                        old_allocation = *(s32 *)D_800B0E58[index];
                        func_10006240(old_allocation + *(s32 *)(D_800B0E58[index] + 4),
                                       (void *)D_800B0E58[index], D_8003809C);
                        func_10004074(old_allocation);
                        *cursor &= ~0x40;
                        if (index < D_800D9F58) {
                            D_800D9F58 = index;
                        }
                        if (D_800D9F5C < index) {
                            D_800D9F5C = index;
                        }
                    }
                }
                index++;
                cursor++;
            } while (stop != index);
        }
        D_800DBDBC = -2;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510D404 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_139FC0/func_1510D404.s")
extern s8 D_800BC448[];

/* Descriptive role: flat_asset_update_nonzero_state.
 * Evidence: docs/evidence/assets/naming/model_resource_role_names.md.
 */
void func_1510D608(s32 resourceIndex, s32 stateBits) {
    s8 *resourceState;
    s8 previousState;

    resourceState = &D_800BC448[resourceIndex];
    previousState = *resourceState;
    if (previousState != 0) {
        *resourceState = (previousState & 0x40) | stateBits;
    }
}
