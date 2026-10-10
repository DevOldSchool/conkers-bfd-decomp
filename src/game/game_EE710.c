#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_EE710.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_directly_called_families.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150C1260
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    f32 field0;
    f32 field4;
    f32 field8;
    f32 fieldC;
    f32 field10;
    f32 field14;
    f32 field18;
    f32 field1C;
    f32 field20;
    f32 field24;
    f32 field28;
    f32 field2C;
    f32 field30;
    f32 field34;
    f32 field38;
    f32 field3C;
    f32 field40;
    f32 field44;
    f32 field48;
    f32 field4C;
    s32 field50;
    s16 field54;
    s16 field56;
    u8 field58;
    u8 pad59[0x3];
    s32 field5C;
    u8 field60;
    u8 field61;
    u8 field62;
    u8 field63;
    u8 field64;
    u8 field65;
    u8 field66;
    u8 field67;
    u8 field68;
    u8 pad69[0x1];
    u8 field6A;
    u8 pad6B;
    void *owner;
    u8 field70;
    u8 pad71[0x1];
    s16 field72;
    s16 field74;
    u8 pad76[0x6];
} FootParticle;

typedef struct {
    u8 pad0[0x3B];
    u8 channel;
    u8 pad3C[0x110];
    f32 scaleX, scaleY;
    u8 pad154[0x2C];
    f32 height;
    u8 pad184[0x50];
    s32 transform;
} FootActor;

void *func_15132A4C(void *, s32, s32, s32, u8, s32);
void func_15142314(s32, s32, void *);
void func_1514C2F0(f32, f32, f32, f32, u8, s8, s16, u8, s32, f32, s32, u8);
void func_15165F80(s32, s32, s32, s32, s32, s32, s32, u8, s32);
u32 func_150ADA20(void);
f32 func_150ADA68(void);
extern f32 D_800A01D0, D_800A01D4, D_800A01D8, D_800A01DC, D_800A01E0;

/* Raw callers select foot 0 or 1 and supply the active actor. */
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150C1260 CURRENT (6057) */
void func_150C1260(FootActor *arg0, u8 arg1) {
    f32 position[3];
    FootParticle particle;
    s32 sp128;
    f32 sp124;
    f32 sp80;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_fs4;
    f32 temp_fs5;
    f32 temp_fv0;
    f32 temp_fv1;
    u8 temp_s0;
    s32 temp_t6;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_s1;
    void *temp_v0;

    temp_t6 = arg1 & 0xFF;
    sp124 = (arg0->scaleX + arg0->scaleY) * 0.5f;
    if (arg0 != 0) {
        temp_v1 = arg0->transform;
        if (temp_v1 != 0) {
            switch (temp_t6) {                      /* irregular */
            case 0:
                sp128 = 0xD;
                break;
            case 1:
                sp128 = 0x11;
                break;
            }
            func_15142314(temp_v1, sp128, position);
            temp_fv0 = sp124 * 80.0f;
            sp80 = temp_fv0;
            func_1514C2F0(position[0], arg0->height, position[2], temp_fv0, 0U, 0x10, 0x10, 0U, 0, temp_fv0 * 4.0f, 0, 0xFFU);
            func_15165F80(-1, (s32) position[0], (s32) ((f32) (s32) arg0->height + 2.0f), (s32) position[2], 0xB, 0x13, 0, 0xFFU, 0);
            particle.field56 = 5;
            particle.field50 = 0x29E8;
            particle.field58 = 0;
            particle.field5C = 0;
            particle.field60 = 0xFF;
            particle.field61 = 1;
            particle.field62 = 0;
            particle.field63 = 0;
            particle.field64 = 0;
            particle.field65 = 0;
            particle.field66 = 0;
            particle.field67 = 0;
            particle.field68 = 0;
            particle.field6A = 1;
            particle.owner = arg0;
            particle.field1C = 1.0f;
            particle.field20 = 1.0f;
            particle.field24 = 1.0f;
            particle.field4 = D_800A01D0;
            particle.field48 = 0.0f;
            particle.field4C = D_800A01D4;
            particle.field72 = 0x10;
            particle.field74 = 0xF;
            particle.field70 = arg0->channel;
            temp_v1_2 = (func_150ADA20() & 7) + 5;
            var_s1 = temp_v1_2 - 1;
            if (temp_v1_2 != 0) {
                temp_fs5 = D_800A01D8;
                temp_fs4 = D_800A01DC;
                do {
                    temp_s0 = func_150ADA20() & 0xFF;
                    temp_fs0 = ((func_150ADA68() * temp_fs4) + temp_fs5) * 18.0f * sp124;
                    temp_fs1 = func_151423D8((temp_s0 - 0x40) & 0xFF);
                    temp_fs2 = func_151423D8(temp_s0 & 0xFF);
                    particle.field54 = (func_150ADA20() & 0x1F) + 0xF;
                    particle.field28 = (sp80 * temp_fs1) + position[0];
                    particle.field38 = temp_fs0;
                    particle.field2C = arg0->height + 2.0f;
                    particle.field30 = (sp80 * temp_fs2) + position[2];
                    particle.field34 = temp_fs0 * temp_fs1;
                    particle.field3C = temp_fs0 * temp_fs2;
                    temp_fv1 = ((func_150ADA68() * temp_fs4) + temp_fs5) * sp124 * D_800A01E0;
                    particle.field8 = temp_fv1;
                    particle.fieldC = temp_fv1;
                    particle.field0 = temp_fv1;
                    particle.field10 = func_150ADA68() * 360.0f;
                    particle.field14 = func_150ADA68() * 360.0f;
                    particle.field18 = func_150ADA68() * 360.0f;
                    particle.field40 = 25.0f - (func_150ADA68() * 50.0f);
                    particle.field44 = 25.0f - (func_150ADA68() * 50.0f);
                    temp_v0 = func_15132A4C(&particle, 3, 0xFF, 4, 0xFFU, 0);
                    if (temp_v0 != 0) {
                        *(f32 *)((u8 *)temp_v0 + 0x170) = (f32) arg0->height;
                    }
                } while (var_s1-- != 0);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150C1260 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_EE710/func_150C1260.s")
