#include "types.h"

/*
 * Reviewed source unit: src/game/game_10E090.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E0BE0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_1502178C(void *, s32, s32);
s32 func_150535F4(u8 *);
void func_15056B08(u8 *);
void func_150585F0(u8 *, f32);
void func_15059140(u8 *);
void func_150599C8(u8 *, s32, u16);
void func_1506E8D8(void);
extern u8 D_800BE9A0;
extern u8 D_800CC2D0;
extern u16 D_800CC346;
extern u8 *D_800D154C;
extern s32 D_800D1580;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E0BE0 CURRENT (720) */
void func_150E0BE0(u8 *actor) {
    s32 counter;
    s32 updated;
    u8 state;
    u16 *current_frame;

    actor[0xB0] = 0xF;
    actor[0x80] = 0xA;
    if (actor[0x87] != 0) {
        counter = actor[0x83];
        if (counter < 0x64) {
            updated = counter + D_800BE9A0;
            actor[0x83] = updated;
            counter = updated & 0xFF;
        }
        if (counter >= 5) {
            state = actor[0x251];
            current_frame = &D_800CC346;
            if (state != 3) {
                *(s32 *)(actor + 0x218) = 0;
                actor[0x232] = 4;
                *(u16 *)(actor + 0x78) = *current_frame;
                if (state == 2) {
                    actor[0x232] = 2;
                }
            }
        }
    } else {
        if (actor[0x83] >= 0x3D) {
            D_800D1580 = 0xFF020133;
            D_800D154C = &D_800CC2D0;
            func_1506E8D8();
            D_800D154C = actor;
        }
        actor[0x83] = 0;
    }
    if (actor[0x232] == 4) {
        if (actor[0x83] == 0) {
            *(u16 *)(actor + 0x78) = *(u16 *)(actor + 0x76);
        }
        func_150599C8(actor, 3, *(u16 *)(actor + 0x78));
    }
    actor[0x87] = 0;
    if (actor[0x104] == 0) {
        func_15056B08(actor);
    } else {
        func_150585F0(actor, 0.05f);
    }
    *(f32 *)(actor + 0x40) = (s16)(*(u16 *)(actor + 0x7A) + 0x4000) * 0.005493164f;
    func_15059140(actor);
    *(f32 *)(actor + 0xBC) = *(f32 *)(actor + 0x14) - *(f32 *)(actor + 0x2C);
    *(f32 *)(actor + 0x148) = *(f32 *)(actor + 0x1C) - *(f32 *)(actor + 0x34);
    if (func_150535F4(actor) == 0) {
        func_1502178C(actor, 0, -1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E0BE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_10E090/func_150E0BE0.s")
