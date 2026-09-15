#include "types.h"

/*
 * Reviewed source unit: src/game/game_12D630.c
 * Boundary evidence: docs/evidence/game_raw_selected_particle_resource_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151001B4
 * - func_15100230
 * - func_151002BC
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_151494E0(s32 *arg0, s32 arg1, s32 arg2);

void func_15100180(void *arg0) {
    struct {
        void *sp18;
        volatile u8 sp1C;
    } sp;

    sp.sp18 = arg0;
    sp.sp1C = *(u8 *)((u8 *)arg0 + 0x3B);
    func_151494E0((s32 *)&sp, 0x48, (s32)arg0);
}
typedef struct {
    u8 pad0[0x3B];
    u8 field3B;
} Game12D630Actor;

typedef struct {
    Game12D630Actor *actor;
    u8 field4;
    u8 pad5;
    s16 field6;
} Game12D630EffectPacket;

void func_10022EC0(void *, void *, s32); /* extern */
u8 *func_15149130(s32, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151001B4 CURRENT (100) */
void func_151001B4(Game12D630Actor *arg0) {
    Game12D630EffectPacket packet;
    u8 *effect;

    packet.actor = arg0;
    packet.field4 = arg0->field3B;
    packet.field6 = 0;
    effect = func_15149130(0x12C, -1, 0x4E, -1, 0, 0x3B, 8, 0xFF, 1);
    if (effect != 0) {
        func_10022EC0(effect + 0x28, &packet, sizeof(packet));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151001B4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12D630/func_151001B4.s")
void func_15149514(s32, u8, s32, s32, s32);
void func_1516972C(void *, void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15100230 CURRENT (148) */
void func_15100230(void *arg0, void *arg1, u8 arg2) {
    u8 *temp_a2;

    temp_a2 = (u8 *)arg0 + 0x28;
    if (arg2 == 0x48) {
        if ((*(s32 *)temp_a2 == *(s32 *)arg1) || (*(u8 *)((u8 *)temp_a2 + 4) == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C(arg0, arg1);
        }
    } else {
        func_15149514((s32) arg1, arg2, (s32) temp_a2, (s32) ((u8 *)temp_a2 + 4), (s32) arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15100230 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12D630/func_15100230.s")
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151002BC CURRENT (35) */
void func_151002BC(u8 *arg0) {
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v1 = (void *)(*(void **)((u8 *)arg0 + 0x28));
    if ((*(s32 *)((u8 *)temp_v1 + 0) == 0) || (temp_v0 = arg0 + 0x28, (*(u8 *)((u8 *)temp_v1 + 4) == 0xFF)) || (*(u8 *)((u8 *)temp_v0 + 4) != *(u8 *)((u8 *)temp_v1 + 0x3B))) {
        *(s16 *)((u8 *)arg0 + 0xE) = -1;
        return;
    }
    if (*(s32 *)((u8 *)temp_v1 + 0x318) != 0) {
        *(s16 *)((u8 *)temp_v0 + 6) = (s16) (*(s16 *)((u8 *)temp_v0 + 6) - D_800BE9E4);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151002BC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_12D630/func_151002BC.s")
