#include "types.h"

/*
 * Reviewed source unit: src/game/game_13AE20.c
 * Boundary evidence: docs/evidence/game_raw_type4b_framebuffer_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1510D970
 * - func_1510DA84
 * - func_1510E120
 * - func_1510E388
 * - func_1510E634
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_15167A68(s32, s32, s32, s32, u8, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510D970 CURRENT (890) */
void *func_1510D970(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 size;
    s32 enabled;
    s32 i;
    s32 j;
    u8 *result;
    u8 *entry;

    size = 0x128;
    enabled = arg3 & 1;
    if (enabled != 0) {
        size = 0x13A;
    }
    result = func_15167A68(0x4B, 0, size, 1, 0xFF, 1);
    if (result != 0) {
        i = 0;
        entry = result;
        do {
            i++;
            entry += 0x40;
            *(s16 *)(entry + 0x56) = 0;
            *(s16 *)(entry + 0x58) = 0x800;
            *(s16 *)(entry + 0x5A) = 0;
            *(s16 *)(entry + 0x66) = 0;
            *(s16 *)(entry + 0x68) = 0;
            *(s16 *)(entry + 0x6A) = 0;
            *(s16 *)(entry + 0x76) = 0;
            *(s16 *)(entry + 0x78) = 0;
            *(s16 *)(entry + 0x7A) = 0x800;
            *(s16 *)(entry + 0x86) = 0;
            *(s16 *)(entry + 0x88) = 0x800;
            *(s16 *)(entry + 0x8A) = 0x800;
        } while (i < 2);

        result[0x120] = arg0;
        *(s32 *)(result + 0x110) = arg1;
        result[0x121] = arg2;
        result[0x124] = arg4;
        if (enabled != 0) {
            *(s16 *)(result + 0x128) = 0x7FFF;
            j = 1;
            entry = result + 2;
            do {
                j += 4;
                *(s16 *)(entry + 0x12A) = 0x7FFF;
                *(s16 *)(entry + 0x12C) = 0x7FFF;
                *(s16 *)(entry + 0x12E) = 0x7FFF;
                entry += 8;
                *(s16 *)(entry + 0x120) = 0x7FFF;
            } while (j != 9);
        }
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510D970 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13AE20/func_1510D970.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13AE20/func_1510DA84.s")
typedef struct { u32 first, second; } Game13AE20Command;
typedef struct {
    u8 pad0[0x110];
    u8 *source;
    f32 x, y, z;
    u8 mode;
    volatile u8 texture;
    u8 alpha, visible;
} Game13AE20RenderState;

void func_150A7D00(volatile s64 *, f32, f32, f32);
s32 func_1506196C(u8 *, s32);
s32 func_1510D0EC(s32, s32 *, s32, s32);
extern s32 D_80091770[];
extern u8 D_800BE9C0;
extern s32 D_800DD1B4;
extern s16 D_800DD1C6;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510E120 CURRENT (3154) */
Game13AE20Command *func_1510E120(Game13AE20Command *arg0, Game13AE20RenderState *arg1, s32 arg2) {
    volatile s32 opacity;
    s32 alpha;
    s32 address;
    s32 combined;
    u8 mode;
    u8 texture;
    u8 *source;
    Game13AE20Command *command0, *command1, *command2, *command3, *command4, *command5, *command6, *command7, *command8, *command9, *command10, *command11;

    if (arg1->visible != 0) {
        func_150A7D00((volatile s64 *)((u8 *)arg1 + (D_800BE9C0 << 6) + 0x10),
                      arg1->x, arg1->z, arg1->y);
        command0 = arg0++;
        command0->first = 0xDA380003;
        command0->second = (u32)((u8 *)arg1 + (D_800BE9C0 << 6) + 0x10);
        texture = arg1->texture;
        if (D_800DD1B4 != texture) {
            D_800DD1B4 = texture;
            address = func_1510D0EC(D_80091770[arg1->texture], 0, 0x3E, 0);
            command1 = arg0++;
            command1->first = 0xE7000000;
            command1->second = 0;
            command2 = arg0++;
            command2->first = 0xFD900000;
            command2->second = address;
            command3 = arg0++;
            command3->first = 0xF3000000;
            command3->second = 0x077FF000;
        }
        command4 = arg0++;
        command4->first = 0xE7000000;
        command4->second = 0;
        command5 = arg0++;
        command5->first = 0xD9FFF9FF;
        command5->second = 0;
        mode = arg1->mode;
        alpha = arg1->alpha;
        switch (mode) {
        case 0:
            opacity = func_1506196C(arg1->source, (s16)arg2);
            break;
        case 1:
            source = arg1->source;
            opacity = (source[(s16)arg2 + 0x8B] * source[0x8A] + 0xFF) >> 8;
            break;
        }
        combined = (s32)((u32)alpha * (u32)opacity + 0xFFU) >> 8;
        if (combined != D_800DD1C6) {
            D_800DD1C6 = combined;
            command6 = arg0++;
            command6->first = 0xE7000000;
            command6->second = 0;
            command7 = arg0++;
            command7->second = combined & 0xFF;
            command7->first = 0xFA000100;
        }
        command8 = arg0++;
        command8->first = 0x01004008;
        command8->second = (u32)((u8 *)arg1 + (D_800BE9C0 << 6) + 0x90);
        command9 = arg0++;
        command9->first = 0x05000204;
        command9->second = 0;
        command10 = arg0++;
        command10->first = 0x05000406;
        command10->second = 0;
        command11 = arg0++;
        command11->first = 0xE7000000;
        command11->second = 0;
    }
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510E120 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13AE20/func_1510E120.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_13AE20/func_1510E388.s")
extern s32 D_80089470;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510E634 CURRENT (485) */
void *func_1510E634(void *arg0, volatile s32 arg1, volatile s32 arg2) {
    void *temp_v1;

    temp_v1 = arg0;
    *(s32 *)temp_v1 = 0xDA380003;
    *(void **)((u8 *)temp_v1 + 4) = &D_80089470;
    arg0 = (u8 *)arg0 + 8;
    return arg0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510E634 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_13AE20/func_1510E634.s")
