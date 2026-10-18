#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_129EE0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_recovered_pointer_helper_groups_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150FCBC0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_15164F0C(u8, s32, void *, u8, s32);
s32 func_1000FA64(s32, s32, s32, s32, s32, s32, s32, void *, s32, s32, s32, s32);
void func_150FCBC0(s32);
void func_151D8868(s8 *, s32, s32, s32);
extern u8 D_1000EC24[];
extern s32 D_80082FA0;

void func_150FCA30(void) {
    s8 spawn[11];
    s32 index;

    func_150FCBC0(0);
    func_150FCBC0(1);
    func_150FCBC0(2);
    func_1000FA64(0x2B8, -0x7F6, 0x618, -0xA47, 0x6D60, 0x2328, 0x1B58,
                  D_1000EC24, 0x2D, 0, 0, 0);
    func_1000FA64(0x2B7, -0x13F, -0x111, -0xD5B, 0x6D60, 0x2328, 0x1B58,
                  D_1000EC24, 0, 0, 0, 0);
    func_1000FA64(0x2B6, 0x5EF, 0x3B3, -0xA49, 0x6D60, 0x2328, 0x1B58,
                  D_1000EC24, 0x5A, 0, 0, 0);
    index = 0;
    if (D_80082FA0 + 1 > 0) {
        do {
            func_15164F0C(4, (u8)index, 0, 0xFF, 1);
            index++;
        } while (D_80082FA0 >= index);
    }
    spawn[0] = 1;
    *(s16 *)&spawn[2] = 0x64;
    spawn[5] = 0xF;
    spawn[4] = 8;
    spawn[6] = -1;
    func_151D8868((s8 *)spawn, 0, 0xFF, 0);
}
f32 func_150ADA68(void);
void func_1514FCE8(s16 *, s32, s32);
void *func_151541B8(void *, f32, f32, f32, f32, u8, s32);
extern void *D_800D9AA0;
extern u8 D_800A1EE0[];
extern f32 D_800A1F14, D_800A1F18, D_800A1F1C, D_800A1F20;
extern f32 D_800A1F24, D_800A1F28;

typedef struct Game129EE0Values {
    f32 value0;
    f32 value1;
    f32 value2;
} Game129EE0Values;

typedef struct {
    s16 angle, spread, pitch, pitchSpread;
    s32 count, countSpread;
    Game129EE0Values position;
    f32 field1C, field20, field24, field28, field2C, field30;
    s32 field34, field38;
    f32 field3C, field40, field44, field48;
    s16 field4C, field4E, field50, field52, field54, field56;
    s8 field58;
} Game129EE0Particle;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150FCBC0 CURRENT (2166) */
void func_150FCBC0(s32 arg0) {
    s16 count;
    Game129EE0Values position;
    s32 angle;
    Game129EE0Particle particle;
    s16 *region;
    s16 *range;
    f32 randomFloat;

    arg0 = (u8)arg0;
    if (arg0 < 3) {
        region = ((s16 **)&D_800D9AA0)[arg0];
        if (region != 0) {
            position.value0 = (f32)region[0];
            position.value1 = (f32)region[1] + (f32)region[4] * 0.5f;
            position.value2 = (f32)region[2];
            randomFloat = func_150ADA68();
            func_151541B8(&position, randomFloat * 4.0f + 12.0f, 6.694309711456299f, (f32)(func_150ADA20() % 56U + 200), D_800A1F14, 0xFF, 1);
            count = (func_150ADA20() & 1) + 3;
            if (count > 0) {
                particle.field1C = 249.0f;
                particle.field20 = D_800A1F18;
                particle.field24 = 506.0f;
                particle.field34 = 3;
                particle.field28 = 100.0f;
                particle.spread = 80;
                particle.pitch = -32;
                particle.pitchSpread = 43;
                particle.count = 1;
                particle.countSpread = 8;
                range = (s16 *)(D_800A1EE0 + arg0 * 4);
                particle.field38 = 2;
                particle.field4C = 12;
                particle.field4E = 50;
                particle.field50 = 100;
                particle.field52 = 100;
                particle.field54 = 12;
                particle.field56 = 12;
                particle.field58 = -1;
                particle.field2C = D_800A1F1C;
                particle.field30 = D_800A1F20;
                particle.field3C = 90.0f;
                particle.field40 = D_800A1F24;
                particle.field44 = -2.0f;
                particle.field48 = D_800A1F28;
                do {
                    angle = (func_150ADA20() % (u32)(range[1] + 1) + range[0]) & 0xFF;
                    particle.angle = angle - 40;
                    func_15143874((s16)angle, (f32)region[3], &particle.position.value0, &particle.position.value2);
                    particle.position.value0 += (f32)region[0];
                    particle.position.value2 += (f32)region[2];
                    particle.position.value1 = func_150ADA68() * (f32)region[4] + (f32)region[1];
                    func_1514FCE8((s16 *)&particle, 0xFF, 1);
                    count--;
                } while (count > 0);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150FCBC0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_129EE0/func_150FCBC0.s")
f32 func_15165BB0(void *, void *, f32, f32, f32);
extern f32 D_800A1F2C;

f32 func_150FCF1C(void *arg0) {
    s16 *source;
    Game129EE0Values sp20;

    source = (s16 *)D_800D9AA0;

    if (source == 0) {
        return 1.0f;
    }
    sp20.value0 = (f32)source[0];
    sp20.value1 = (f32)source[1];
    sp20.value2 = (f32)source[2];
    return func_15165BB0(arg0, &sp20, 2007.0f, 9005.0f, D_800A1F2C);
}
