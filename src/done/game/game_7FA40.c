#include "types.h"

/*
 * Reviewed source unit: src/game/game_7FA40.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_singletons_continued.md
 */

void func_1502178C(void *, s32, s32);
s32 func_150229E4(void *);
void func_1504BB88(u8 *);
s32 func_150535F4(u8 *);
void func_15056B08(u8 *);
void func_150585F0(u8 *, f32);
void func_15059140(u8 *);
void func_150AFC68(s32, s32, s32, s32, u8, s32);
void func_15053750(u8 *);
void func_15054F74(u8 *);
void func_150562FC(u8 *);
void func_150597FC(u8 *);
extern f32 D_80099344;
extern u8 D_800C35EA;
extern u8 D_800C3654;
extern u8 D_800C3E78;

typedef struct Game7FA40Owner {
    u8 pad0[0x28];
    f32 value28;
    u8 pad2C[0x14];
    f32 angle;
    u8 pad44[0x36];
    u16 heading;
    u8 pad7C[4];
    u8 state80;
    u8 pad81[0x43];
    f32 smooth;
    u8 padC8[0x3C];
    u8 active;
    u8 pad105[0x38];
    u8 mode;
    u8 pad13E[0x46];
    s32 flags184;
    u8 pad188[0x42];
    u8 state1CA;
    u8 pad1CB[0x91];
    s32 flags25C;
} Game7FA40Owner;

void func_15052590(Game7FA40Owner *arg0) {
    s32 flags;

    flags = arg0->flags25C;
    if (flags & 0x80) {
        arg0->flags25C = flags & ~0x80;
        func_150AFC68(D_800C3E78, 3, 0x3FC, 6, 0xFF, 0);
        func_150AFC68(D_800C3E78, 2, 0x3FC, 6, 0xFF, 0);
    }
    if ((D_800C35EA != 1) || ((D_800C3654 != 0) && (func_150229E4(arg0) == 0))) {
        func_15053750((u8 *)arg0);
        func_1504BB88((u8 *)arg0);
        arg0->state80 = 0xA;
        if (arg0->active == 0) {
            func_15056B08((u8 *)arg0);
        } else if (arg0->mode == 0) {
            func_150585F0((u8 *)arg0, 0.05f);
        }
        arg0->angle = (f32)(s16)(arg0->heading + 0x4000) * 0.0054931640625f;
        func_15059140((u8 *)arg0);
        if ((arg0->value28 == 0.0f) && ((arg0->flags184 & 0x1F) == 0xE)) {
            arg0->state1CA = 0;
        }
        func_150597FC((u8 *)arg0);
        if (arg0->mode != 0) {
            func_150562FC((u8 *)arg0);
        } else {
            arg0->smooth += (0.0f - arg0->smooth) * D_80099344;
        }
        func_15054F74((u8 *)arg0);
        if (func_150535F4((u8 *)arg0) == 0) {
            func_1502178C(arg0, 0, -1);
        }
    }
}
