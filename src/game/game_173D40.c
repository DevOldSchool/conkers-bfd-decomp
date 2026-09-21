#include "types.h"

/*
 * Reviewed source unit: src/game/game_173D40.c
 * Boundary evidence: docs/evidence/game_raw_dispatch_position_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15146970
 * - func_15146A98
 * - func_15146BF8
 * - func_15146D60
 * - func_15146E84
 * - func_15147040
 * - func_151470FC
 * - func_15147318
 * - func_15147478
 * - func_151475D8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15142314(s32, s32, void *);
s32 func_15046C80(f32 *, u16, f32, void *);
void func_1504715C(void *, void *);

s32 func_15146890(f32 *arg0, void *arg1, s32 arg2, u8 arg3) {
    f32 position[3];
    s32 var_a1;

    if ((arg3 != 1) && (arg3 != 2)) {
        return 0;
    }
    if (arg3 == 1) {
        var_a1 = 0x13;
    } else {
        var_a1 = 0x17;
    }
    func_15142314(*(s32 *)((u8 *)arg1 + 0x1D4), var_a1, arg0);
    if (arg2 == 0) {
        return 1;
    }
    position[0] = arg0[0];
    position[1] = arg0[1] + 10.0f;
    position[2] = arg0[2];
    func_1504715C((void *)arg2, arg1);
    return func_15046C80(position, 0, arg0[1] - 50.0f, (void *)arg2);
}
s32 func_151420F8(void *);
s32 func_150A2AEC(s32, s32, s32 *, s32);
extern s32 D_800BE9F0;
extern s32 D_800A56D0[5];
extern s32 D_800CC2D0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15146970 CURRENT (1890) */
s32 func_15146970(u32 arg0, void *arg1, s32 arg2) {
    s32 sp1C[5];

    switch (arg0) {
    case 0:
        return 0x10;
    case 1:
        return 0xF;
    case 2:
        return 5;
    case 3:
        return 2;
    case 4:
        return 0;
    case 5:
        if (D_800BE9F0 == 4) {
            if (func_151420F8(arg1) != 0) {
                return 6;
            }
            return 3;
        }
        return 1;
    case 6:
        return 4;
    case 7:
        return 3;
    case 8:
        sp1C[0] = D_800A56D0[0];
        sp1C[1] = D_800A56D0[1];
        sp1C[2] = D_800A56D0[2];
        sp1C[3] = D_800A56D0[3];
        sp1C[4] = D_800A56D0[4];
        if (func_150A2AEC(((u8 *)arg1 - (u8 *)&D_800CC2D0) / 0x32C,
                          5, sp1C, (s32)arg1) == -1) {
            return -1;
        }
        return 6;
    default:
        return -1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15146970 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_173D40/func_15146970.s")
typedef struct Game173D40RawVec3 {
    s32 values[3];
} Game173D40RawVec3;

typedef struct Game173D40Effect {
    s32 field0;
    s32 field4;
    Game173D40RawVec3 position;
    f32 field14;
    f32 field18;
    s16 field1C;
    s16 field1E;
    s16 field20;
    s16 field22;
    f32 field24;
    f32 field28;
    f32 field2C;
    f32 field30;
    f32 field34;
    f32 field38;
    s8 field3C;
    u8 pad3D;
    s16 field3E;
    s16 field40;
} Game173D40Effect;

void func_15150F90(Game173D40Effect *, s32, s32, s32);
extern f32 D_800A5708;
extern f32 D_800A570C;
extern f32 D_800A5710;
extern f32 D_800A5714;
extern f32 D_800A5718;
extern f32 D_800A571C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15146A98 CURRENT (194) */
void func_15146A98(void *volatile arg0, s32 arg1, s32 arg2) {
    Game173D40RawVec3 position;
    Game173D40Effect effect;

    if (*(s32 *)((u8 *)arg0 + 0x1D4) != 0) {
        func_15146890((f32 *)&position, arg0, 0, (u8)arg1);
        effect.field0 = 5;
        effect.field4 = 0x16;
        effect.position = position;
        effect.field14 = D_800A5708;
        effect.field18 = D_800A570C;
        effect.field1C = 0;
        effect.field1E = 0xFF;
        effect.field22 = 0xE;
        effect.field20 = -0x14;
        effect.field3C = 3;
        effect.field3E = 0x19;
        effect.field40 = 0x19;
        effect.field24 = 6.0f;
        effect.field28 = 3.0f;
        effect.field2C = D_800A5710;
        effect.field30 = D_800A5714;
        effect.field34 = D_800A5718;
        effect.field38 = D_800A571C;
        func_15150F90(&effect, 0, 0xFF, 1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15146A98 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_173D40/func_15146A98.s")
void func_15146BF8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_15146BB8(s32 arg0, s32 arg1, s32 arg2) {
    func_15146BF8(arg0, arg1, arg2, 0);
}
void func_15146BD8(s32 arg0, s32 arg1, s32 arg2) {
    func_15146BF8(arg0, arg1, arg2, 1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_173D40/func_15146BF8.s")
void func_15141F78(s32, void *, f32, s32, f32 *, s32);
extern f32 D_800A5728;
extern f32 D_800A572C;

typedef struct {
    s32 saved_arg1;
    u8 work[0x24];
    f32 position[3];
} Game173D40D60Locals;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15146D60 CURRENT (780) */
void func_15146D60(void *volatile arg0, u8 arg1, s32 arg2) {
    Game173D40D60Locals locals;

    if (*(s32 *)((u8 *)arg0 + 0x1D4) != 0) {
        locals.saved_arg1 = arg1;
        if (func_15146890(locals.position, arg0, (s32)locals.work, arg1) != 0) {
            func_15141F78(0xA, locals.work, (f32)arg2 * D_800A5728,
                          (u32)(*(f32 *)((u8 *)arg0 + 0x40) * D_800A572C) & 0xFF,
                          locals.position, locals.saved_arg1);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15146D60 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_173D40/func_15146D60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_173D40/func_15146E84.s")
s32 func_15146890(f32 *, void *, s32, u8);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_1514C678(f32, f32, s32, f32, s32, s32, s32, s32, s32, f32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15147040 CURRENT (210) */
void func_15147040(void *arg0, s32 arg1, s32 arg2) {
    f32 coordinates[3];
    s16 sp42;

    if (*(s32 *)((u8 *)arg0 + 0x1D4) != 0) {
        func_15146890(coordinates, arg0, 0, (u8)arg1);
        sp42 = (s16)((func_150ADA20() % 11U) + 5);
        func_1514C678(coordinates[0], coordinates[1], *(s32 *)&coordinates[2], func_150ADA68() * 11.0f,
                      0, 0xFF, sp42, 0x16, 0, 0.0f, 0, 0xFF);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15147040 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_173D40/func_15147040.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_173D40/func_151470FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_173D40/func_15147318.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_173D40/func_15147478.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_173D40/func_151475D8.s")
