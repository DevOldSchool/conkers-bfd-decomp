#include "types.h"

/*
 * Reviewed source unit: src/main/init_39C0.c
 * Boundary evidence: docs/evidence/main_system_wrapper_boundaries.md
 *
 * TODO: Implement these source-unit functions:
 * - func_80003ACC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern u16 *D_8002AAE8[2];
extern s32 D_800BE620;
extern s32 D_800BE624;

typedef struct VideoMode VideoMode;
s32 func_80003C40(s32, s32, s32, s32);
void func_80003ACC(s32, s32, s32);
void func_800247C0(VideoMode *);
void func_80024830(void *);
void func_85015FBC(s32, s32);
extern s32 D_80000300;
extern VideoMode D_8002AB90;
extern VideoMode D_8002ABE0;
extern f32 D_800380A0;
extern f32 D_800380A4;
extern u8 D_800BE9C0;
extern u16 *D_800BE9C4;

void func_800039C0(void) {
    D_800BE620 = 0x124;
    D_800BE624 = 0xD8;
    D_800380A0 = (f32)D_800BE620 / 292.0f;
    D_800380A4 = (f32)D_800BE624 / 216.0f;
    D_800BE9C4 = (u16 *)func_80003C40(D_800BE620 * D_800BE624 * 2, 0xFF, 3, 0);
    func_80003ACC(0, 0, 0);
    func_85015FBC(D_800BE620, D_800BE624);
    func_800247C0(D_80000300 == 2 ? &D_8002ABE0 : &D_8002AB90);
    func_80024830(D_8002AAE8[D_800BE9C0 ^ 1]);
}

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80003ACC CURRENT (265) */
void func_80003ACC(s32 red, s32 green, s32 blue) {
    u16 *pixels;
    u16 *second;
    u32 byteCount;
    s32 count;
    s32 i;

    byteCount = (u32)D_800BE620 * (u32)D_800BE624 * 2;
    pixels = D_8002AAE8[0];
    second = pixels;
    count = (s32)byteCount >> 1;
    i = 0;
    if (second != 0) {
        for (; i < count; i++) {
            pixels++;
            pixels[-1] = (((u32)red << 8) & 0xF800) |
                        (((u32)green << 3) & 0x7C0) |
                        ((blue >> 2) & 0x3E) | 1;
        }
        second = D_8002AAE8[1];
        for (i = 0; i < count; i++) {
            second[i] = (((u32)red << 8) & 0xF800) |
                               (((u32)green << 3) & 0x7C0) |
                               ((blue >> 2) & 0x3E) | 1;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80003ACC */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_39C0/func_80003ACC.s")
