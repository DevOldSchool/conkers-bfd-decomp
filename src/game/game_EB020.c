#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_EB020.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150BDB70
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameEB020State {
    u8 pad0[0x24];
    s16 unk24;
    u8 pad26[0x16C - 0x26];
    f32 unk16C;
    f32 unk170;
    u8 pad174[0x197 - 0x174];
    u8 unk197;
    u8 pad198[3];
    u8 unk19B;
    u8 pad19C[2];
    s16 unk19E;
} GameEB020State;

typedef struct GameEB020Actor {
    u8 pad0[4];
    u8 unk4;
    u8 pad5[0x65 - 5];
    u8 unk65;
    u8 unk66;
    u8 pad67[0x76 - 0x67];
    s16 unk76;
    u8 pad78[2];
    s16 unk7A;
    u8 pad7C[0x124 - 0x7C];
    s8 unk124;
    u8 pad125[2];
    u8 unk127;
    u8 pad128[0x13C - 0x128];
    u8 unk13C;
    u8 pad13D[0x232 - 0x13D];
    u8 unk232;
    u8 pad233[0x23D - 0x233];
    u8 unk23D;
    u8 pad23E[0x2E4 - 0x23E];
    s32 unk2E4;
    s32 unk2E8;
    u8 pad2EC[0x2FC - 0x2EC];
    s8 unk2FC;
    u8 pad2FD[0x318 - 0x2FD];
    struct GameEB020Actor *unk318;
    GameEB020State *unk31C;
    u8 pad320[0xC];
} GameEB020Actor;

void func_15052F9C(u8 *, f32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_1505327C(u8 *, f32, f32, s32, s32);
void *func_15072208(void *, s32);
extern f32 D_8009FFF0;
extern u8 D_800BE616;
extern s32 D_800CC268;
extern u8 D_800CC2D0[];
extern u16 D_800D18A0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150BDB70 CURRENT (1520) */
void func_150BDB70(GameEB020Actor *arg0) {
    s32 sp58;
    s32 sp50;
    f32 var_fv0;
    s32 temp_ft3;
    s32 temp_v1_3;
    s32 var_a1;
    s32 var_t0;
    s32 var_v0;
    GameEB020Actor *actor;
    GameEB020State *state;

    var_a1 = 1;
    if (arg0->unk4 == 0x23) {
        var_a1 = 0xA;
        sp58 = 0xB;
        var_t0 = 0xC;
        sp50 = 1;
    } else {
        sp58 = 2;
        var_t0 = 3;
        sp50 = 3;
    }
    arg0->unk2E8 = 0;
    arg0->unk2FC = 0;
    arg0->unk2E4 = arg0->unk2E4 - (arg0->unk2E4 >> 3);
    if (D_800BE616 != 0) {
        arg0->unk66 &= 0xFFDF;
    }
    if (arg0->unk13C != 0) {
        /* Raw owner IDs use a 100-entry bias (100 * 0x32C = 0x13D30). */
        actor = (GameEB020Actor *) ((u32) D_800CC2D0 + arg0->unk13C * 0x32C - 0x13D30);
        if (actor->unk318 != 0) {
            arg0->unk2FC = (s8) (1U << (actor->unk318->unk23D & 31));
        }
        state = actor->unk31C;
        if ((state != 0) && (state->unk197 != 0)) {
            temp_ft3 = (s32) (state->unk16C * D_8009FFF0);
            arg0->unk7A = temp_ft3;
            arg0->unk76 = temp_ft3;
            var_fv0 = actor->unk31C->unk170;
            if (var_fv0 > 180.0f) {
                var_fv0 -= 360.0f;
            }
            arg0->unk2E8 = 1;
            arg0->unk66 |= 0x20;
            arg0->unk2E4 = (s32) (var_fv0 * 10.0f);
        }
    }
    func_15052590(arg0);
    if (sp58 == arg0->unk232) {
        func_15052F9C((u8 *) arg0, 100.0f, sp50, 4, 0, var_t0, 0, 0, 0, 0);
        return;
    }
    if ((var_a1 == arg0->unk232) && (~D_800D18A0 & D_800CC268) && (func_15072208(arg0, 0) == 0)) {
        var_v0 = 0;
        temp_v1_3 = ~D_800D18A0 & D_800CC268;
loop_19:
        if (!((1 << var_v0) & temp_v1_3) && (var_v0 < 0x19)) {
loop_21:
            var_v0 += 1;
            if (!((1 << var_v0) & temp_v1_3)) {
                if (var_v0 < 0x19) {
                    goto loop_21;
                }
            }
        }
        if (var_v0 < 0x19) {
            actor = (GameEB020Actor *) (D_800CC2D0 + var_v0 * 0x32C);
            if ((actor->unk127 != 0xFF) && (actor->unk65 == 0)) {
                state = actor->unk31C;
                if ((state->unk19B == 0) && (state->unk197 == 0) && (actor->unk13C == 0)) {
                    arg0->unk124 = var_v0;
                    func_1505327C((u8 *) arg0, 44.0f, 3.2f, sp58, sp50);
                    actor->unk31C->unk24 = 0x258;
                    actor->unk31C->unk19E = 0;
                    return;
                }
            }
            var_v0 += 1;
            if (var_v0 < 0x19) {
                goto loop_19;
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150BDB70 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EB020/func_150BDB70.s")
