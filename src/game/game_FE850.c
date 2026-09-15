#include "types.h"

/*
 * Reviewed source unit: src/game/game_FE850.c
 * Boundary evidence: docs/evidence/game_raw_complete_callback_clusters.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D13A0
 * - func_150D149C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameFE850State {
    u8 pad0[0x3C];
    f32 field_3C;
    u8 pad40[0x78];
    f32 field_B8;
    f32 field_BC;
    u8 padC0[4];
    f32 field_C4;
    u8 padC8[0x80];
    f32 field_148;
} GameFE850State;

void func_15059C84(GameFE850State *);
void func_151467A4(s32, s32, s32, s32, f32, f32, f32, s32);
void func_1515D4D4(s32, u8, u8, s32);
extern f32 D_800A08B0;
extern f32 D_800A08B4;
extern f32 D_800A08B8;
extern f32 D_800A08C0;
extern u8 D_800DCD20[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D13A0 CURRENT (745) */
void func_150D13A0(GameFE850State *arg0) {
    f32 velocity_x;
    f32 velocity_y;

    velocity_x = arg0->field_BC;
    arg0->field_B8 += velocity_x;
    arg0->field_BC = velocity_x * D_800A08B0;
    velocity_y = arg0->field_148;
    arg0->field_C4 += velocity_y;
    arg0->field_3C *= D_800A08B4;
    arg0->field_148 = velocity_y * D_800A08B8;
    func_15059C84(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D13A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FE850/func_150D13A0.s")
/* Call context: func_151149AC: unique active project prototype */
s32 func_151149AC(u8);
extern u8 D_800CC2D0;

void func_150D1410(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_151149AC(0xF9U);
    if (temp_v0 != 0) {
        if (((arg0 - (s32)&D_800CC2D0) / 0x32C) == 0) {
            *(s8 *)((u8 *)temp_v0 + 0x6E) = 1;
            return;
        }
        *(s8 *)((u8 *)temp_v0 + 0x6E) = 0;
    }
}

void func_150D146C(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_151149AC(0xF9U);
    if (temp_v0 != 0) {
        *(s8 *)((u8 *)temp_v0 + 0x6E) = 1;
    }
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D149C CURRENT (200) */
void func_150D149C(void *arg0) {
    s32 sp28;

    sp28 = (s32)arg0 + 0x28;
    func_151467A4((s32)((u8 *)arg0 + 0x30), 0x41200000,
                  (s32)((u8 *)arg0 + 0x2C), 0x42480000,
                  100.0f, 123.0f, D_800A08C0, sp28);
    func_1515D4D4((s32)*(f32 *)sp28, D_800DCD20[1], D_800DCD20[2], 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D149C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FE850/func_150D149C.s")
