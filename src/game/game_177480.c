#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_177480.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_table_runs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1514A19C
 * - func_1514A380
 * - func_1514A4EC
 * - func_1514A594
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_10022EC0(void *, const void *, u32);
void func_151D5D60(void *, s16, s32, void **, u8 *);
extern f32 D_800DD1D8[];
extern f32 D_800DD1E8[];

typedef struct Game177480Vertex {
    s16 x, y, z, flag;
    u8 other[8];
} Game177480Vertex;

typedef struct Game177480Owner {
    u8 pad0[0x2C];
    f32 scale;
    f32 height;
    f32 x, y, z;
    u8 pad40[0x80];
    u8 templateData[0x40];
    u8 *buffers[1];
} Game177480Owner;

void *func_15149FD0(Game177480Owner *arg0, s16 arg1) {
    Game177480Vertex *vertices;
    void *result;
    f32 offsetZ;
    f32 offsetX;
    u8 fresh;

    func_151D5D60(arg0->buffers, arg1, 0x40, (void **)&vertices, &fresh);
    result = vertices;
    if (vertices != 0) {
        if (fresh != 0) {
            func_10022EC0(arg0->buffers[arg1], arg0->templateData, 0x40);
            func_10022EC0(arg0->buffers[arg1] + 0x40, arg0->templateData, 0x40);
        }
    } else {
        return 0;
    }
    offsetZ = D_800DD1D8[arg1] * arg0->scale;
    offsetX = D_800DD1E8[arg1] * arg0->scale;
    vertices[0].flag = 0;
    vertices[1].flag = 0;
    vertices[2].flag = 0;
    vertices[3].flag = 0;
    vertices[0].x = vertices[3].x = (s32)(arg0->x + offsetX);
    vertices[0].y = vertices[1].y = (s32)arg0->y;
    vertices[0].z = vertices[3].z = (s32)(arg0->z - offsetZ);
    vertices[1].x = vertices[2].x = (s32)(arg0->x - offsetX);
    vertices[2].y = vertices[3].y = (s32)(arg0->y + arg0->height);
    vertices[1].z = vertices[2].z = (s32)(arg0->z + offsetZ);
    return result;
}
u32 func_150ADA20();                                /* extern */
f32 func_150ADA68();                                /* extern */
extern f32 D_800A5794;
extern f32 D_800A5798;
extern f32 D_800A579C;
extern s32 D_800BE9E4;

typedef struct Game177480Interpolation {
    f32 high0, low0, target0;
    f32 split1, low1, high1, target1;
    s16 timer0, timer1;
    u8 pad20[0x18];
    f32 high2, low2, target2;
    s16 timer2;
} Game177480Interpolation;

typedef struct Game177480InterpolationOwner {
    u8 pad0[0x24];
    s32 integer;
    u8 pad28[4];
    f32 scale, height;
    u8 pad34[0xDC];
    Game177480Interpolation state;
} Game177480InterpolationOwner;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514A19C CURRENT (525) */
s32 func_1514A19C(Game177480InterpolationOwner *arg0) {
    Game177480Interpolation *state;
    s32 integer;

    arg0->state.timer1 -= D_800BE9E4;
    if (arg0->state.timer1 < 0) {
        state = &arg0->state;
        state->timer1 = func_150ADA20() % 6U;
        if (func_150ADA20() & 3) {
            state->target1 = func_150ADA68() * (state->split1 - state->low1) + state->low1;
        } else {
            state->target1 = func_150ADA68() * (state->high1 - state->split1) + state->split1;
        }
    }
    state = &arg0->state;
    arg0->height += (state->target1 - arg0->height) * D_800A5794;
    state->timer0 -= D_800BE9E4;
    if (state->timer0 < 0) {
        state->timer0 = func_150ADA20() % 17U;
        state->target0 = func_150ADA68() * (state->high0 - state->low0) + state->low0;
    }
    arg0->scale += (state->target0 - arg0->scale) * D_800A5798;
    state->timer2 -= D_800BE9E4;
    if (state->timer2 < 0) {
        state->timer2 = func_150ADA20() % 15U;
        state->target2 = func_150ADA68() * (state->high2 - state->low2) + state->low2;
    }
    integer = arg0->integer;
    arg0->integer = (s32)((state->target2 - (f32)integer) * D_800A579C) + integer;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514A19C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_177480/func_1514A19C.s")

extern f32 D_800A57A0;
extern f32 D_800A57A4;
extern f32 D_800A57A8;
extern f32 D_800A57AC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514A380 CURRENT (805) */
s32 func_1514A380(void *arg0) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    s32 var_v1;
    u8 temp_t8;
    u8 var_v0;
    void *temp_v0;
    void *temp_v0_2;

    var_v0 = *(u8 *)((u8 *)arg0 + 0x74);
    var_v1 = 1;
    if (!(var_v0 & 2)) {
        temp_v0 = (u8 *)arg0 + 0x110;
        temp_fv0 = *(f32 *)((u8 *)arg0 + 0x2C);
        *(f32 *)((u8 *)arg0 + 0x2C) =
            temp_fv0 + ((*(f32 *)((u8 *)temp_v0 + 8) - temp_fv0) * D_800A57A0);
        if ((*(f32 *)((u8 *)temp_v0 + 8) * D_800A57A4) <
            *(f32 *)((u8 *)arg0 + 0x2C)) {
            temp_t8 = *(u8 *)((u8 *)arg0 + 0x74) | 2;
            *(u8 *)((u8 *)arg0 + 0x74) = temp_t8;
            var_v0 = temp_t8;
        } else {
            var_v1 = 0;
            var_v0 = *(u8 *)((u8 *)arg0 + 0x74);
        }
    }
    temp_v0_2 = (u8 *)arg0 + 0x110;
    if (!(var_v0 & 8)) {
        temp_fv0_2 = *(f32 *)((u8 *)arg0 + 0x30);
        *(f32 *)((u8 *)arg0 + 0x30) =
            temp_fv0_2 + ((*(f32 *)((u8 *)temp_v0_2 + 0x18) - temp_fv0_2) * D_800A57A8);
        if ((*(f32 *)((u8 *)temp_v0_2 + 0x18) * D_800A57AC) <
            *(f32 *)((u8 *)arg0 + 0x30)) {
            *(u8 *)((u8 *)arg0 + 0x74) |= 8;
        } else {
            var_v1 = 0;
        }
    }
    if (var_v1 != 0) {
        func_1513F680(arg0, *(u8 *)((u8 *)arg0 + 0x70), 4,
                       *(u8 *)((u8 *)arg0 + 0x72),
                       *(u8 *)((u8 *)arg0 + 0x73));
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514A380 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_177480/func_1514A380.s")
s32 func_1514A498(void *arg0) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x30);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x144);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x2C);
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) (temp_fv0 - (temp_fv0 * temp_fv1));
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) (temp_fa0 - (temp_fa0 * temp_fv1));
    if (*(s16 *)((u8 *)arg0 + 0x1C) < *(s16 *)((u8 *)arg0 + 0x156)) {
        *(s8 *)((u8 *)arg0 + 0x5C) = (s8) (*(s16 *)((u8 *)arg0 + 0x158) * *(s16 *)((u8 *)arg0 + 0x1C));
    }
    return 1;
}
extern f32 D_800BE9A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514A4EC CURRENT (95) */
s32 func_1514A4EC(void *arg0) {
    typedef struct { f32 words[3]; } Copy3;
    f32 temp_fv0;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x140);
    *(Copy3 *)((u8 *)arg0 + 0x40) = *(Copy3 *)((u8 *)arg0 + 0x34);
    *(f32 *)((u8 *)arg0 + 0x130) = (f32) (*(f32 *)((u8 *)arg0 + 0x130) * temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x134) += *(f32 *)((u8 *)arg0 + 0x13C) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x138) = (f32) (*(f32 *)((u8 *)arg0 + 0x138) * temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x34) += *(f32 *)((u8 *)arg0 + 0x130) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x38) += *(f32 *)((u8 *)arg0 + 0x134) * D_800BE9A4;
    *(f32 *)((u8 *)arg0 + 0x3C) += *(f32 *)((u8 *)arg0 + 0x138) * D_800BE9A4;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514A4EC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_177480/func_1514A4EC.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1514A594 CURRENT (475) */
s32 func_1514A594(void *arg0) {
    volatile f32 sp4;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv1;
    f32 temp_ft4;
    f32 temp_fv0;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x140);
    *(f32 *)((u8 *)arg0 + 0x130) = (f32) (*(f32 *)((u8 *)arg0 + 0x130) * temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x134) = (f32) ((*(f32 *)((u8 *)arg0 + 0x13C) * D_800BE9A4) + *(f32 *)((u8 *)arg0 + 0x134));
    *(f32 *)((u8 *)arg0 + 0x138) = (f32) (*(f32 *)((u8 *)arg0 + 0x138) * temp_fv0);
    temp_fv1 = D_800BE9A4;
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x130) * temp_fv1;
    temp_fa1 = *(f32 *)((u8 *)arg0 + 0x134) * temp_fv1;
    temp_ft4 = *(f32 *)((u8 *)arg0 + 0x138) * temp_fv1;
    *(f32 *)((u8 *)arg0 + 0x34) = (f32) (*(f32 *)((u8 *)arg0 + 0x34) + temp_fa0);
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) (*(f32 *)((u8 *)arg0 + 0x38) + temp_fa1);
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C) + temp_ft4);
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) (*(f32 *)((u8 *)arg0 + 0x40) + temp_fa0);
    *(f32 *)((u8 *)arg0 + 0x44) = (f32) (*(f32 *)((u8 *)arg0 + 0x44) + temp_fa1);
    *(f32 *)((u8 *)arg0 + 0x48) = (f32) (*(f32 *)((u8 *)arg0 + 0x48) + temp_ft4);
    sp4 = *(f32 *)((u8 *)arg0 + 0x54);
    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x38);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x3C);
    *(f32 *)((u8 *)arg0 + 0x40) = (f32) (*(f32 *)((u8 *)arg0 + 0x34) + ((*(f32 *)((u8 *)arg0 + 0x40) - *(f32 *)((u8 *)arg0 + 0x34)) * sp4));
    *(f32 *)((u8 *)arg0 + 0x44) = (f32) (temp_fv0 + ((*(f32 *)((u8 *)arg0 + 0x44) - temp_fv0) * sp4));
    *(f32 *)((u8 *)arg0 + 0x48) = (f32) (temp_fv1 + ((*(f32 *)((u8 *)arg0 + 0x48) - temp_fv1) * sp4));
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1514A594 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_177480/func_1514A594.s")
