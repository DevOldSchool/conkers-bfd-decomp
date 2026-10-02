#include "types.h"

/*
 * Reviewed source unit: src/game/game_32740.c
 * Boundary evidence: docs/evidence/game_early_callback_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15005290
 * - func_150054C4
 * - func_15005818
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_10003C40(s32 size, s32 pool, s32 flags, s32 alignment);
s32 func_1502B5C8(s32 *size, s32 count, ...);
void func_150054C4(u8 *view, u32 index, s32 resource, s32 mode);
void func_1512ABF8(void);
void func_1512D238(void);

extern s32 D_80082FA0;
extern s32 D_800894B0;
extern s16 D_80089550;
extern u8 *D_800BE2B0[];
extern s32 D_800BE620;
extern u8 *D_800DBFF0;
extern u8 D_800DBFF4[];
extern u8 *D_800DC010;
extern u8 *D_800DC020;
extern u8 *D_800DC2A0[2];
extern u8 *D_800DC2B0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15005290 CURRENT (2519) */
void func_15005290(s32 resource, s32 mode) {
    s32 resource_size;
    u8 **buffer;
    s32 count;
    s32 matrix_bytes;
    u8 *view;
    s32 view_offset;
    u8 *flag;
    u32 index;
    s16 view_resource;

    D_800DC020 = (u8 *)func_1502B5C8(&resource_size, 3, 0xC, resource, 8);
    D_80089550 = (u32)resource_size / 24U;
    count = D_80082FA0 + 1;
    D_800DBFF0 = (u8 *)func_10003C40(count * 0x9A0, 1, 1, 0);
    matrix_bytes = count << 6;
    D_800DC2B0 = (u8 *)func_10003C40(count * 0xB0, 1, 0, 0);
    D_800DC2A0[0] = (u8 *)func_10003C40(matrix_bytes, 1, 1, 0);
    D_800DC2A0[1] = (u8 *)func_10003C40(matrix_bytes, 1, 1, 0);
    view_resource = resource;
    flag = D_800DBFF4;
    buffer = D_800BE2B0;
    index = 0;
    view_offset = 0;
    do {
        view = D_800DBFF0 + view_offset;
        *buffer = (u8 *)func_10003C40(D_800BE620 * 2, 1, 2, 0);
        func_150054C4(view, index, (s16)view_resource, mode);
        *flag = 0;
        index += 1;
        view_offset += 0x9A0;
        buffer += 1;
        flag += 1;
    } while ((u32)D_80082FA0 >= index);
    func_1512ABF8();
    func_1512D238();
    D_800894B0 = 0;
    D_800DC010 = (u8 *)func_10003C40(D_80082FA0 * 0x9A0 + 0x9A0, 1, 2, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15005290 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_32740/func_15005290.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_32740/func_150054C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_32740/func_15005818.s")
