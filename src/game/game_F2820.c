#include "types.h"

/*
 * Reviewed source unit: src/game/game_F2820.c
 * Boundary evidence: docs/evidence/game_raw_path_owner_lifecycles.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C5370
 * - func_150C5470
 * - func_150C54C0
 * - func_150C5510
 * - func_150C553C
 * - func_150C5568
 * - func_150C56A4
 * - func_150C5BD4
 * - func_150C5CC4
 * - func_150C5D0C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_15167A68(s32, s32, s32, s32, s32, s32);
void *func_10022EC0(void *, const void *, u32);
f32 func_15143E64(f32 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C5370 CURRENT (280) */
void *func_150C5370(void *arg0, s32 arg1) {
    void *object;
    f32 delta[3];

    object = func_15167A68(0x46, 0, arg1 + 0xC8, 1, 0xFF, 1);
    if (object == 0) {
        return 0;
    }
    func_10022EC0((u8 *)object + 0x18, arg0, 0x24);
    delta[0] = *(f32 *)((u8 *)object + 0x18) - *(f32 *)((u8 *)object + 0x24);
    delta[1] = *(f32 *)((u8 *)object + 0x1C) - *(f32 *)((u8 *)object + 0x28);
    delta[2] = *(f32 *)((u8 *)object + 0x20) - *(f32 *)((u8 *)object + 0x2C);
    *(f32 *)((u8 *)object + 0xC0) = func_15143E64(delta);
    *(s32 *)((u8 *)object + 0x10) = 1;
    *(s32 *)((u8 *)object + 0x14) = 0;
    return object;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C5370 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F2820/func_150C5370.s")
void func_150C5430(void) {
    func_15169804();
}
void func_150C5450(void) {
    func_15169824();
}
typedef struct {
    u8 pad_0[0x38];
    u8 field_38;
} GameF2820State;

extern void (*D_800887B8[])(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C5470 CURRENT (400) */
void func_150C5470(GameF2820State *arg0) {
    u8 temp_v0;

    temp_v0 = arg0->field_38;
    if ((s32)temp_v0 < 0 || (s32)temp_v0 >= 2) {
        temp_v0 = 0;
    }
    D_800887B8[temp_v0]();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C5470 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F2820/func_150C5470.s")
extern void (*D_800887C0[])(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C54C0 CURRENT (400) */
void func_150C54C0(GameF2820State *arg0) {
    u8 temp_v0;

    temp_v0 = arg0->field_38;
    if ((s32)temp_v0 < 0 || (s32)temp_v0 >= 2) {
        temp_v0 = 0;
    }
    D_800887C0[temp_v0]();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C54C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F2820/func_150C54C0.s")
/* Call context: func_150C5430: unique active project prototype */
/* Call context: func_1514EDF0: unique active project prototype */
void func_1514EDF0(s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C5510 CURRENT (360) */
void func_150C5510(void *arg0) {
    func_1514EDF0((s32) arg0, *(s32 *)((u8 *)arg0 + 0xC8));
    func_150C5430();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C5510 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F2820/func_150C5510.s")
/* Call context: func_150C5450: unique active project prototype */
/* Call context: func_1514EDF0: unique active project prototype */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C553C CURRENT (360) */
void func_150C553C(void *arg0) {
    func_1514EDF0((s32) arg0, *(s32 *)((u8 *)arg0 + 0xC8));
    func_150C5450();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C553C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F2820/func_150C553C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F2820/func_150C5568.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_F2820/func_150C56A4.s")
s32 func_150C5B88(void *arg0) {
    void **temp_v1;

    temp_v1 = (void **)((u8 *)arg0 + 0xC8);
    if (*(s32 *)*(void **)((u8 *)arg0 + 0xC8) == 0) {
        return 0;
    }
    *(f32 *)((u8 *)arg0 + 0x24) = *(f32 *)((u8 *)*temp_v1 + 0x14);
    *(f32 *)((u8 *)arg0 + 0x28) = *(f32 *)((u8 *)*temp_v1 + 0x18);
    *(f32 *)((u8 *)arg0 + 0x2C) = *(f32 *)((u8 *)*temp_v1 + 0x1C);
    return 1;
}
void func_15143134(f32 *, f32 *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C5BD4 CURRENT (110) */
s32 func_150C5BD4(void *arg0) {
    s32 temp_t0;
    void *temp_v0;
    void *temp_v1;

    temp_v0 = (u8 *)arg0 + 0xC8;
    if (*(s32 *)*(void **)temp_v0 == 0) {
        return 0;
    }
    temp_v1 = *(void **)temp_v0;
    if (*(u8 *)((u8 *)temp_v0 + 4) != *(u8 *)((u8 *)temp_v1 + 0x3B)) {
        return 0;
    }
    temp_t0 = *(s32 *)((u8 *)temp_v1 + 0x1D4);
    if (temp_t0 == 0) {
        *(f32 *)((u8 *)arg0 + 0x24) = *(f32 *)((u8 *)temp_v1 + 0x14);
        *(f32 *)((u8 *)arg0 + 0x28) = *(f32 *)((u8 *)*(void **)temp_v0 + 0x18);
        *(f32 *)((u8 *)arg0 + 0x2C) = *(f32 *)((u8 *)*(void **)temp_v0 + 0x1C);
    } else {
        func_15143134((f32 *)((u8 *)temp_v0 + 8), (f32 *)((u8 *)arg0 + 0x24),
                      (*(u8 *)((u8 *)temp_v0 + 5) << 6) + temp_t0);
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C5BD4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F2820/func_150C5BD4.s")
void func_1514D3B0(void *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_150C5C74(void *arg0) {
    func_1514D3B0(arg0, 0x15, 1, 0);
}
void func_150C5C9C(void *arg0) {
    func_1514D3B0(arg0, 0x15, 2, 0);
}
extern void (*D_800887C8[])(void *, void *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C5CC4 CURRENT (237) */
void func_150C5CC4(void *arg0, void *arg1, s32 arg2) {
    void (*temp_v0)(void *, void *, s32);

    arg2 &= 0xFF;
    temp_v0 = D_800887C8[((u8 *)arg0)[0x38]];
    if (temp_v0 != 0) {
        temp_v0(arg0, arg1, arg2);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C5CC4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F2820/func_150C5CC4.s")
void func_1516972C(u8 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C5D0C CURRENT (255) */
void func_150C5D0C(void *arg0, void *arg1, u8 arg2) {
    s32 temp_a0;
    s32 temp_v0;
    s32 temp_v1;
    u8 *temp_a3;

    temp_v0 = arg2;
    if (temp_v0 == 0) {
        if ((*(s32 *)((u8 *)arg0 + 0xC8) == *(s32 *)arg1) ||
            (*(u8 *)((u8 *)arg0 + 0xCC) == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C((u8 *)arg0);
        }
    } else {
        temp_a3 = (u8 *)arg0 + 0xC8;
        if (temp_v0 == 0x2D) {
            temp_a0 = *(s32 *)temp_a3;
            temp_v1 = *(s32 *)arg1;
            if (temp_v1 == temp_a0) {
                *(s32 *)temp_a3 = *(s32 *)((u8 *)arg1 + 4);
                *(u8 *)(temp_a3 + 4) = *(u8 *)((u8 *)arg1 + 9);
                return;
            }
            if (*(s32 *)((u8 *)arg1 + 4) == temp_a0) {
                *(s32 *)temp_a3 = temp_v1;
                *(u8 *)(temp_a3 + 4) = *(u8 *)((u8 *)arg1 + 8);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C5D0C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_F2820/func_150C5D0C.s")
