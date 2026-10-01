#include "types.h"

/*
 * Reviewed source unit: src/game/game_C3E20.c
 * Boundary evidence: docs/evidence/game_raw_record_command_controller.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15096A68
 * - func_15096D78
 * - func_1509759C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_100226F0(void *arg0, s32 arg1);
extern u8 D_800D2DC0;
extern s32 D_800D2DB4;

void func_15096970(void) {
    func_100226F0(&D_800D2DC0, 0x6C);
    D_800D2DB4 = 0;
}

s32 func_150969A0(s32 arg0) {
    struct Entry {
        u8 flag;
        u8 rest[0x23];
    };
    s32 i;

    for (i = 0; i < arg0; i++) {
        if (((struct Entry *)&D_800D2DC0)[i].flag != 0) {
            return 1;
        }
    }
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_C3E20/func_15096A68.s")
s32 func_15096A68(s32);                             /* extern */
extern u8 D_800C35EA;
extern u8 D_800D2DC0;

void func_15096D08(void) {
    s32 var_s0;
    u8 *var_s1;

    var_s0 = 0;
    if (D_800C35EA != 1) {
        var_s1 = &D_800D2DC0;
loop_2:
        if (*var_s1 != 0) {
            if (func_15096A68(var_s0) == 0) {
                goto block_6;
            }
            return;
        }
block_6:
        var_s0 += 1;
        var_s1 += 0x24;
        if (var_s0 == 3) {

        } else {
            goto loop_2;
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_C3E20/func_15096D78.s")
typedef struct GameC3E20View {
    u8 pad0[0x2A4];
    f32 firstX;
    f32 firstY;
    f32 firstZ;
    u8 pad2B0[0x48];
    f32 secondX;
    f32 secondY;
    f32 secondZ;
    u8 pad304[0x78];
    f32 value37C;
    u8 pad380[0x10];
    f32 value390;
    u8 pad394[8];
    f32 angle;
} GameC3E20View;

f32 func_15047D60(f32);
f32 func_15047C00(f32);
void func_15048F90(void *, void *, void *);
f32 func_150AD900(f32 *, f32 *);
u8 *func_1505EEF4(s32);
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
extern u8 *D_800DBFF0;
extern s32 D_80082FA0;
extern f32 D_8009DF4C;
extern s32 D_800DC020;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1509759C CURRENT (562) */
s32 func_1509759C(s32 arg0, s32 arg1, s32 *arg2) {
    GameC3E20View *view;
    f32 direction[3];
    f32 offset[3];
    f32 angle;
    u8 *actor;
    f32 dx;
    f32 dz;
    s16 *point;
    s32 result;

    view = (GameC3E20View *)(D_800DBFF0 + arg0 * 0x9A0);
    if (D_80082FA0 < arg0) return 0;
    switch (arg1) {
    case 31:
        return (s32)(view->value390 * 65536.0f);
    case 30:
        return (s32)(view->value37C * 65536.0f);
    case 29:
        return (&D_800D2DC0)[arg2[2] * 0x24];
    case 32:
        point = (s16 *)((arg2[2] & 0xFFF) * 0x18 + D_800DC020);
        dx = view->secondX - (f32)point[0];
        dz = view->secondZ - (f32)point[2];
        return (s32)sqrtf(dx * dx + dz * dz);
    case 33:
        actor = func_1505EEF4(arg2[2] & 0xFFF);
        if (actor == 0) return -1;
        angle = view->angle + D_8009DF4C;
        direction[0] = func_15047D60(angle);
        direction[1] = 0.0f;
        direction[2] = func_15047C00(angle);
        func_15048F90(&view->secondX, actor + 0x14, offset);
        offset[1] = 0.0f;
        result = 1;
        if (func_150AD900(direction, offset) >= 0.0f) return -1;
        return result;
    default:
        return 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1509759C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_C3E20/func_1509759C.s")



void func_15048F90(void *, void *, void *);
void func_1504917C(void *, void *);
extern u8 *D_800DBFF0;
extern s32 D_800D2E30[];

void func_15097798(s32 arg0) {
    GameC3E20View *view;
    f32 direction[5];

    view = (GameC3E20View *)(D_800DBFF0 + arg0 * 0x9A0);
    if (D_800D2DB4 != 0) {
        func_15048F90(&view->firstX, &view->secondX, direction + 2);
        func_1504917C(direction + 2, direction + 2);
        view->firstX += direction[2] * -2.5f * (f32)D_800D2E30[arg0];
        view->firstY += direction[3] * -2.0f * (f32)D_800D2E30[arg0];
        view->firstZ += direction[4] * -2.5f * (f32)D_800D2E30[arg0];
        view->secondX += direction[2] * -2.5f * (f32)D_800D2E30[arg0];
        view->secondY += direction[3] * -2.0f * (f32)D_800D2E30[arg0];
        view->secondZ += direction[4] * -2.5f * (f32)D_800D2E30[arg0];
    }
}
