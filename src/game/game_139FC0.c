#include "types.h"

/*
 * Reviewed source unit: src/game/game_139FC0.c
 * Boundary evidence: docs/evidence/game_raw_call_connected_segments_continued.md
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
    *(s32 *)((u8 *)arg0 + 4) = (s32)((temp_t1[2] << 8) | (temp_t1[0] << 0x18) | (temp_t1[1] << 0x10) | (arg1 & 0xFF));
    temp_a0 = (u8 *)arg0 + 8;
    *(s32 *)temp_a0 = 0xFB000000;
    temp_t3 = D_800D9B78 + temp_t0;
    *(s32 *)(temp_a0 + 4) = (s32)((temp_t3[2] << 8) | (temp_t3[0] << 0x18) | (temp_t3[1] << 0x10) | (arg2 & 0xFF));
    return temp_a0 + 8;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510CDB8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_139FC0/func_1510CDB8.s")
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
 * Evidence: docs/evidence/model_resource_role_names.md.
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
 * Evidence: docs/evidence/model_resource_role_names.md.
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
