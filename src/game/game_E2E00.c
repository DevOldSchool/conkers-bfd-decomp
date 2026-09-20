#include "types.h"

/*
 * Reviewed source unit: src/game/game_E2E00.c
 * Boundary evidence: docs/evidence/game_raw_owner_particle_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150B5950
 * - func_150B5A3C
 * - func_150B5C38
 * - func_150B5E34
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameE2E00Target5950 {
    s32 active;
    u8 pad4[0x10];
    f32 position[3];
    u8 pad20[0x1B];
    u8 type;
    u8 pad3C[0x198];
    s32 field_1D4;
} GameE2E00Target5950;

typedef struct GameE2E00Owner5950 {
    u8 pad0;
    u8 field_1;
    u8 pad2[0xA];
    u8 field_C;
    u8 padD;
    s16 result;
    u8 pad10[0x18];
    GameE2E00Target5950 *target;
    u8 field_2C;
} GameE2E00Owner5950;

f32 func_150ADA68(void);
void func_150B5A3C();
void func_150B60E0(void *, f32 *);
extern f32 D_8009FC98;
extern f32 D_8009FC9C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150B5950 CURRENT (96) */
void func_150B5950(GameE2E00Owner5950 *arg0) {
    GameE2E00Target5950 *target;
    struct {
        u8 pad[8];
        f32 position[3];
    } local;

    target = arg0->target;
    if ((target->active == 0) || (target->type != arg0->field_2C)) {
        arg0->result = -1;
        return;
    }
    if (target->field_1D4 != 0) {
        if (func_150ADA68() < D_8009FC98) {
            local.position[0] = target->position[0];
            local.position[1] = target->position[1];
            local.position[2] = target->position[2];
            func_150B5A3C(local.position, arg0->field_C, arg0->field_1, target);
        }
        if (func_150ADA68() < D_8009FC9C) {
            func_150B60E0(target, local.position);
            func_150B5A3C(local.position, arg0->field_C, arg0->field_1);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150B5950 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_E2E00/func_150B5950.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E2E00/func_150B5A3C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E2E00/func_150B5C38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_E2E00/func_150B5E34.s")
s32 func_151602C0(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
u32 func_150ADA20();

void func_150B6000(void *arg0, u8 arg1, s32 arg2) {
    struct {
        u8 type;
        s8 subtype;
        s16 lifetime;
        s8 flag;
    } descriptor;
    s32 position[3];

    descriptor.type = 3;
    descriptor.subtype = -1;
    descriptor.lifetime = (func_150ADA20() % 9U) + 3;
    descriptor.flag = 0;
    position[0] = (s32)*(f32 *)((u8 *)arg0 + 0);
    position[1] = (s32)*(f32 *)((u8 *)arg0 + 4);
    position[2] = (s32)*(f32 *)((u8 *)arg0 + 8);
    func_151602C0((u8 *)&descriptor, position, (func_150ADA20(arg0) % 201U) + 0x37,
                  0xFF, 0xFF, 0xFF, 0xFF, 0, 0, (s32)arg1, arg2);
}
/* Call context: func_15143134: unique active project prototype */
void func_15143134(f32 *, f32 *, s32);
extern f32 D_8009FC30;

void func_150B60E0(void *arg0, f32 *arg1) {
    func_15143134(&D_8009FC30, arg1, *(s32 *)((u8 *)arg0 + 0x1D4) + 0x140);
}
