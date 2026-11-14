#include "types.h"
#include "game_functions.h"
#include "game_path.h"

/*
 * Reviewed source unit: src/game/game_43D00.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_loader_transfer_emission_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150169A0
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

void func_15016850(void) {
    s32 i;
    s32 j;
    s32 found;
    s32 size;
    s32 id;

    D_800BE590 = 0;
    size = 0;
    for (i = 0; i < D_800D2100; i++) {
        id = *(u8 *)((s32)D_800D20FC + i * 0x30 + 4);
        found = 0;
        for (j = 0; j < D_800BE590; j++) {
            if (id == D_800BE598[j]) {
                found = 1;
                break;
            }
        }
        if (found) {
            continue;
        }
        if (id < 0xBB) {
            func_1502B7F0(&size, 2, 0x12, id);
        }
        if (size != 0) {
            D_800BE5A8[D_800BE590] = size;
            D_800BE598[D_800BE590] = id;
            D_800BE590++;
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_43D00/func_150169A0.s")
void *func_10003C40(s32, s32, s32, s32);
void func_100226F0(void *, s32);
extern s8 D_8008FD8C;
extern u8 D_800D2101;
extern u8 *D_800D2108;
typedef struct Game43D00Entry {
    s32 offset;
    s32 kind;
} Game43D00Entry;

void func_15017114(s32 arg0) {
    s32 index;
    s32 data;
    s32 count;

    data = 0;
    count = D_800D2100;
    D_800D2104 = func_10003C40(count * sizeof(*D_800D2104), 1, 0, 0);
    D_800D2108 = func_10003C40(count * sizeof(*D_800D2108), 1, 0, 0);
    func_100226F0(D_800D2104, count * sizeof(*D_800D2104));
    func_100226F0(D_800D2108, count * sizeof(*D_800D2108));
    for (index = 0; index < D_8008FD8C; index++) {
        D_800D2104[index] = func_10003C40(0x10, 1, 2, 0);
        func_100226F0(D_800D2104[index], 0x10);
        D_800D2108[index] = 2;
    }
    if (func_1502B7F0(&data, 2, 0x10, arg0) != 0) {
        for (index = D_800D2101; index < D_800D2100; index++) {
            if (((Game43D00Entry *)data)[index - D_800D2101].offset != 0) {
                D_800D2108[index] = ((Game43D00Entry *)data)[index - D_800D2101].kind;
                D_800D2104[index] = (void *)(((Game43D00Entry *)data)[index - D_800D2101].offset + data);
            }
        }
    }
}
