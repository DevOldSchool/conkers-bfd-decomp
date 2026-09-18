#include "types.h"

/*
 * Reviewed source unit: src/game/game_12CCF0.c
 * Boundary evidence: docs/evidence/game_raw_dispatch_position_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FF840
 * - func_150FFD84
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game12CCF0State {
    u8 pad0[0x1D4];
    s32 field1D4;
} Game12CCF0State;

void func_15145EA4(s32 *, s32 *, s32, s32);

extern u8 D_80088BB0;
extern s32 D_800A2130;

#pragma GLOBAL_ASM("asm/nonmatchings/game_12CCF0/func_150FF840.s")
typedef struct Game12CCF0Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Game12CCF0Vec3f;

typedef struct Game12CCF0Actor {
    u8 pad0[0x7A];
    u16 field_7A;
    u8 pad7C[0x2B0];
} Game12CCF0Actor;

s32 func_1505D1C4(f32, f32, f32, s32, s32, s32, s32, s32);
extern u8 D_800CC2D0;

void func_150FFB6C(Game12CCF0Vec3f *arg0, void *arg1, Game12CCF0Actor *arg2, s32 arg3) {
    s32 actor_index;
    u16 actor_id;

    actor_index = ((u8 *)arg2 - &D_800CC2D0) / 0x32C;
    actor_id = arg2->field_7A;
    func_1505D1C4(arg0->x, arg0->y, arg0->z, arg3 | 0x60000,
                  actor_index, actor_id, 0, (s32)arg1);
}
void func_150FFBDC(Game12CCF0State *arg0, s32 arg1, s32 arg2) {
    s32 *sp1C;
    s32 sp18;

    sp1C = &D_800A2130;
    sp18 = arg2;
    func_15145EA4((s32 *) &sp1C, &sp18,
                  arg0->field1D4 + (D_80088BB0 << 6), 1);
}
u32 func_150ADA20(void *);
void func_151D8868(s8 *, s32, s32, s32);

void func_150FFC3C(void *arg0) {
    struct {
        s8 field_0;
        s8 pad1;
        s16 field_2;
        s8 field_4;
        s8 field_5;
        s8 field_6;
    } sp18;

    if (*(void **)((u8 *)arg0 + 0x318) != 0) {
        sp18.field_0 = 1;
        sp18.field_2 = (s16) ((func_150ADA20(arg0) % 11U) + 0x14);
        sp18.field_5 = (s8) (1 << *(u8 *)((u8 *)*(void **)((u8 *)arg0 + 0x318) + 0x23D));
        sp18.field_4 = (s8) ((func_150ADA20(arg0) & 1) + 7);
        sp18.field_6 = -1;
        func_151D8868(&sp18.field_0, 0, 0xFF, 1);
    }
}
void func_151D3E6C(void *, void *, void *, s32);
void func_151D5A18(void *, void *, void *, void *, void *, s32, s32);
extern s32 D_8008FC8C;
extern u8 *D_8008FC94;

void func_150FFCC8(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4) {
    func_151D5A18(arg0, arg1, arg2, arg3, arg4, D_8008FC8C, *D_8008FC94);
    func_151D3E6C(arg0, arg1, arg1, 0x8003A);
}
void func_15081E0C(void *, s32, s32);

void func_150FFD2C(s32 arg0, void *arg1, s32 arg2) {
    u8 temp_v0;

    temp_v0 = *(u8 *)((u8 *)arg1 + 4);
    if (((temp_v0 == 0x9F) || (temp_v0 == 0xA0)) && !(*(s32 *)((u8 *)arg1 + 0x94) & 0x80)) {
        func_15081E0C(arg1, 4, 0);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_12CCF0/func_150FFD84.s")
