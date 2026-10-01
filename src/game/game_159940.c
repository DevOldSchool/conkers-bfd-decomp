#include "types.h"

/*
 * Reviewed source unit: src/game/game_159940.c
 * Boundary evidence: docs/evidence/game_raw_state_resource_helpers.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1512C490
 * - func_1512D238
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game159940Object {
    u8 pad0[0x84D];
    u8 field_84D;
    u8 field_84E;
    u8 pad84F;
    s32 field_850;
} Game159940Object;

typedef struct Game159940Resource Game159940Resource;

extern s32 D_800BE9E4;
extern Game159940Resource *D_800DC280[];
extern u32 D_800DC290[];

#pragma GLOBAL_ASM("asm/nonmatchings/game_159940/func_1512C490.s")
typedef struct Game159940Motion {
    u8 pad0[0x2C];
    s32 mode;
    u8 pad30[0x20C];
    u8 direct;
    u8 matrixIndex;
    u8 pad23E[0x5A];
    s16 variant;
    u8 pad29A[0x356];
    s32 flags;
    u8 pad5F4[0x1BC];
    f32 angle;
    f32 rate;
    u8 pad7B8[0x20];
    f32 velocity;
    f32 amplitude;
} Game159940Motion;

void func_150495B0(f32 *, f32, f32 *, f32, f32, f32);
void func_150A7BC0(void *);
void func_150A7790(void *, s32);
f32 func_150AD780(f32);
f32 func_150AD78C(f32);
void func_151F00E0(void *, void *, void *);
extern f32 D_800A36C0;
extern f32 D_800A36C4;
extern f32 D_800A36C8;
extern f32 D_800A36CC;
extern f32 D_800A36D0;
extern f32 D_800A36D4;
extern f32 D_800A36D8;
extern u8 D_800BE9C0;
extern u8 *D_800DC2A0[];

void func_1512D070(Game159940Motion *arg0) {
    u32 fixedMatrix[16];
    f32 matrix[16];
    f32 amplitude;
    void *destination;

    if (arg0->mode & 0x80000) {
        amplitude = D_800A36C0;
    } else if (arg0->variant != 0) {
        amplitude = D_800A36C4;
    } else {
        amplitude = D_800A36C8;
    }
    if ((arg0->mode & 0x80000) || (arg0->flags & 1) ||
        (arg0->mode != 0x40000 && (arg0->flags & 8))) {
        arg0->angle += D_800A36CC * (f32)D_800BE9E4;
        if (D_800A36D0 < arg0->angle) {
            arg0->angle -= D_800A36D4;
        }
    } else {
        amplitude = 0.0f;
    }
    if (arg0->direct != 0 || (arg0->flags & 4)) {
        arg0->amplitude = amplitude;
    } else {
        func_150495B0(&arg0->amplitude, amplitude, &arg0->velocity,
                      0.2f, D_800A36D8, arg0->rate);
    }
    func_150A7BC0(matrix);
    matrix[0] = 2.0f * (func_150AD78C(arg0->angle) * arg0->amplitude) +
                (arg0->amplitude + arg0->amplitude) + 1.0f;
    matrix[5] = func_150AD780(arg0->angle) * arg0->amplitude +
                arg0->amplitude + 1.0f;
    func_150A7790(matrix, (s32)fixedMatrix);
    destination = D_800DC2A0[D_800BE9C0] + (arg0->matrixIndex << 6);
    func_151F00E0(destination, fixedMatrix, destination);
}
Game159940Resource *func_1502B5C8(u32 *arg0, s32 arg1, s32 arg2, s32 arg3);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1512D238 CURRENT (240) */
void func_1512D238(void) {
    Game159940Resource **var_s1;
    u32 *var_s2;
    u32 sp3C;
    Game159940Resource *temp_v0;
    s32 var_s0;

    var_s1 = D_800DC280;
    var_s2 = D_800DC290;
    var_s0 = 0;
    do {
        temp_v0 = func_1502B5C8(&sp3C, 2, 0x1B, var_s0);
        var_s0 += 1;
        var_s1 += 1;
        var_s2 += 1;
        var_s1[-1] = temp_v0;
        var_s2[-1] = sp3C / 24U;
    } while (var_s0 != 4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1512D238 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_159940/func_1512D238.s")
void func_1512D2E4(Game159940Object *arg0, s32 arg1) {
    arg0->field_850 = arg1;
    arg0->field_84D = 1;
}
void func_1512D2F8(Game159940Object *arg0) {
    u8 state;
    u8 value;

    state = arg0->field_84D;
    switch (state) {
    case 1:
        arg0->field_84E = 0;
        arg0->field_84D = 2;
        return;
    case 2:
        value = arg0->field_84E + D_800BE9E4;
        arg0->field_84E = value;
        if ((value & 0xFF) >= (s32)D_800DC290[arg0->field_850]) {
            arg0->field_84D = 0;
        }
        return;
    }
}
void func_1512D368(s32 arg0) {

}
