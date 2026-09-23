#include "types.h"

/*
 * Reviewed source unit: src/game/game_14F8F0.c
 * Boundary evidence: docs/evidence/game_raw_directly_called_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15122440
 * - func_15122980
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_14F8F0/func_15122440.s")
typedef struct Game14F8F0Actor {
    u8 pad0[0x84];
    s32 flags;
    u8 pad88[0x54];
    s32 state;
    u8 padE0[0x1B8];
    s16 enabled;
    u8 pad29A[0x22];
    f32 first[3];
    f32 second[3];
    u8 pad2D4[0x24];
    f32 origin[3];
    u8 pad304[0x78];
    f32 field37C;
    u8 pad380[0x10];
    f32 field390;
    u8 pad394[8];
    f32 field39C;
    u8 pad3A0[0x414];
    f32 field7B4;
    u8 pad7B8[0x11C];
    f32 field8D4;
    f32 field8D8;
    f32 field8DC;
} Game14F8F0Actor;

f32 func_15048A70(f32, f32);
void func_15048F90(f32 *, f32 *, f32 *);
void func_15123A54(void *);
void func_1512A390(void *);
f32 func_15048FC8(f32 *);
void func_150495B0(f32 *, f32, f32 *, f32, f32, f32);
void func_1512E140(void *);
extern f32 D_800A34A0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15122980 CURRENT (62) */
void func_15122980(Game14F8F0Actor *arg0) {
    f32 sp44[3];
    f32 sp38[3];
    f32 sp34;
    f32 sp30;
    f32 *sp28;
    f32 temp_fv0;

    sp28 = arg0->origin;
    if (arg0->state != 4) {
        func_15048F90(sp28, arg0->second, sp44);
        func_15048F90(sp28, arg0->first, sp38);
        sp34 = func_15048FC8(sp44);
        sp30 = func_15048FC8(sp38);
        if (arg0->enabled == 0) {
            arg0->field8D4 = 0.0f;
        } else if ((arg0->flags & 0x100000) ||
                   ((temp_fv0 = arg0->field390, temp_fv0 > 180.0f) &&
                    (temp_fv0 < 270.0f))) {
            arg0->field8D4 = 0.75f;
        } else {
            arg0->field8D4 = 0.5f;
        }
        func_150495B0(&arg0->field8DC, arg0->field8D4,
                        &arg0->field8D8, 1.0f, 2.0f, arg0->field7B4);
        arg0->field37C += func_15048A70(sp34, sp30) * arg0->field8DC;
        arg0->field39C = arg0->field37C * D_800A34A0;
    }
    func_15123A54(arg0);
    func_1512E140(arg0);
    func_1512A390(arg0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15122980 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_14F8F0/func_15122980.s")
