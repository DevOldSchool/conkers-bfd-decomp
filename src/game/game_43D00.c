#include "types.h"

/*
 * Reviewed source unit: src/game/game_43D00.c
 * Boundary evidence: docs/evidence/game_raw_loader_transfer_emission_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15016850
 * - func_150169A0
 * - func_15017114
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

/* Raw 1502B7F0 consumes count-selected word varargs and returns its size word. */
u32 func_1502B7F0(s32 *, s32, ...);
extern u8 D_800BE590;
extern u16 D_800BE598[];
extern s32 D_800BE5A8[];
extern u8 *D_800D20FC;
extern u8 D_800D2100;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15016850 CURRENT (3020) */
void func_15016850(void) {
    s32 sp50;
    s32 found;
    s32 offset;
    s32 index;
    s32 bound;
    u8 *scan;
    u8 count;
    u8 id;

    D_800BE590 = 0;
    count = D_800D2100;
    sp50 = 0;
    offset = 0;
    if (count > 0) {
        do {
            found = 0;
            id = D_800D20FC[offset + 4];
            index = 0;
            if (D_800BE590 > 0) {
                scan = (u8 *)D_800BE598;
                do {
                    index++;
                    if (id == *(u16 *)scan) {
                        found = 1;
                        break;
                    }
                    scan += 2;
                } while (index < D_800BE590);
            }
            if (found) {
                bound = count * 0x30;
            } else {
                if (id < 0xBB) {
                    func_1502B7F0(&sp50, 2, 0x12, id);
                }
                bound = count * 0x30;
                if (sp50 != 0) {
                    D_800BE5A8[D_800BE590] = sp50;
                    D_800BE598[D_800BE590] = id;
                    D_800BE590++;
                }
            }
            offset += 0x30;
        } while (offset < bound);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15016850 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_43D00/func_15016850.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_43D00/func_150169A0.s")
void *func_10003C40(s32, s32, s32, s32);
void func_100226F0(void *, s32);
extern s8 D_8008FD8C;
extern u8 D_800D2101;
extern void **D_800D2104;
extern u8 *D_800D2108;
typedef struct Game43D00Entry {
    s32 offset;
    s32 kind;
} Game43D00Entry;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15017114 CURRENT (2230) */
void func_15017114(s32 arg0) {
    s32 data;
    s32 index;
    s32 byteCount;
    u8 count;
    Game43D00Entry *entry;

    count = D_800D2100;
    data = 0;
    byteCount = count * 4;
    D_800D2104 = func_10003C40(byteCount, 1, 0, 0);
    D_800D2108 = func_10003C40(count, 1, 0, 0);
    func_100226F0(D_800D2104, byteCount);
    func_100226F0(D_800D2108, count);
    for (index = 0; index < D_8008FD8C; index++) {
        D_800D2104[index] = func_10003C40(0x10, 1, 2, 0);
        func_100226F0(D_800D2104[index], 0x10);
        D_800D2108[index] = 2;
    }
    if (func_1502B7F0(&data, 2, 0x10, arg0) != 0) {
        index = D_800D2101;
        while (index < D_800D2100) {
            entry = (Game43D00Entry *)(data + index * 8 - D_800D2101 * 8);
            if (entry->offset != 0) {
                D_800D2108[index] = entry->kind;
                D_800D2104[index] = (void *)(((Game43D00Entry *)(data + index * 8 - D_800D2101 * 8))->offset + data);
            }
            index++;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15017114 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_43D00/func_15017114.s")
