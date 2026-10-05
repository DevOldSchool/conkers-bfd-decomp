#include "types.h"

/*
 * Reviewed source unit: src/game/game_2D540.c
 * Boundary evidence: docs/evidence/game_raw_directly_called_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150000B0
 * - func_150006E0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15000090(void) {
    func_1000DEC4();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_2D540/func_150000B0.s")
void func_15000940(s32);
void *func_1515D480(s32);
extern s32 D_80082FA0;
extern void *D_800B0DF0;
extern f32 D_800D3670, D_800D9B1C, D_800D9B20;
extern f32 D_800D9AC0[], D_800D9AF8[];
extern u8 D_800D9B68[], D_800D9B78[], D_800D9B84[], D_800D9B88[];
extern u8 D_800D9BD0[];
extern s32 D_800D9E10[];
extern u8 D_800D9E20;
extern u8 D_800D9AF0, D_800D9B18, D_800D9B8B, D_800D9B8C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150006E0 CURRENT (1220) */
void func_150006E0(s32 arg0) {
    u8 *first;
    u8 *second;
    u8 *first_byte;
    u8 *second_byte;
    u8 *record;
    u8 *record_byte;
    s32 *handle;
    f32 *value;
    s32 i;
    s32 limit;
    s32 allocated;

    D_800D9B20 = (f32)(u32)*(u16 *)((u8 *)D_800B0DF0 + 2);
    D_800D9B1C = (f32)(u32)*(u16 *)D_800B0DF0;
    D_800D3670 = 100.0f - D_800D9B1C;
    func_15000940(arg0);
    first = D_800D9B68;
    second = D_800D9B78;
    do {
        for (i = 0; i < 3; i++) {
            first[i] = 0;
            second[i] = 0;
        }
        second += 3;
        first += 3;
    } while ((u32)second < (u32)D_800D9B84);
    first_byte = D_800D9B84;
    second_byte = D_800D9B88;
    do {
        second_byte++;
        first_byte++;
        first_byte[-1] = 0;
        second_byte[-1] = 0;
    } while ((u32)second_byte < (u32)&D_800D9B8B);
    D_800D9B8B = 0xFF;
    D_800D9B8C = 0xFF;
    limit = D_80082FA0;
    D_800D9E20 = 0xB;
    i = 0;
    if (limit >= 0) {
        handle = D_800D9E10;
        do {
            allocated = (s32)func_1515D480(D_800D9E20);
            limit = D_80082FA0;
            i++;
            handle++;
            handle[-1] = allocated;
        } while (limit >= i);
    }
    if (limit >= 0) {
        record = D_800D9BD0;
        do {
            i = 0;
            record_byte = record;
            do {
                i++;
                record_byte += 8;
                record_byte[-4] = 0xFF;
                record_byte[-8] = 0xFF;
                record_byte[-3] = 0xFF;
                record_byte[-7] = 0xFF;
                record_byte[-2] = 0xFF;
                record_byte[-6] = 0xFF;
            } while (i != 2);
            record += 0x10;
        } while ((u32)(D_800D9BD0 + limit * 0x10) >= (u32)record);
    }
    if (limit >= 0) {
        value = D_800D9AC0;
        do {
            value += 3;
            value[-3] = -1.0f;
        } while ((u32)(D_800D9AC0 + limit * 3) >= (u32)value);
    }
    D_800D9AF0 = 0;
    if (limit >= 0) {
        value = D_800D9AF8;
        do {
            value += 2;
            value[-2] = -1.0f;
        } while ((u32)(D_800D9AF8 + limit * 2) >= (u32)value);
    }
    D_800D9B18 = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150006E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_2D540/func_150006E0.s")
