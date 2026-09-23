#include "types.h"

/*
 * Reviewed source unit: src/game/game_1045D0.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D728C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1045D0Position {
    s32 words[3];
} Game1045D0Position;

typedef struct Game1045D0Effect {
    s16 control0;
    s16 control1;
    s16 control2;
    s16 control3;
    s32 control4;
    s32 control5;
    Game1045D0Position position;
    f32 values[6];
    s32 control6;
    s32 control7;
    f32 values2[4];
    s16 ends[6];
    s8 final;
} Game1045D0Effect;

void func_1514FCE8(s16 *, s32, s32);
void func_151C04F8(s32, u8, s32);
void func_151C05A4(s32, u8, s32);
void func_151C05F0(s32, u8, s32);
extern f32 D_800A0AE0;
extern f32 D_800A0AE4;
extern f32 D_800A0AE8;

void func_150D7120(Game1045D0Position *arg0, u8 arg1, s32 arg2) {
    Game1045D0Effect effect;

    func_151C04F8((s32)arg0, arg1, arg2);
    func_151C05A4((s32)arg0, arg1, arg2);
    func_151C05F0((s32)arg0, arg1, arg2);
    effect.control0 = 0;
    effect.control1 = 0xFF;
    effect.control2 = -0x40;
    effect.control3 = 0x47;
    effect.control4 = 6;
    effect.control5 = 4;
    effect.position = *arg0;
    effect.values[0] = 23.0f;
    effect.values[1] = 30.0f;
    effect.values[2] = 45.0f;
    effect.values[3] = 53.0f;
    effect.control6 = 7;
    effect.control7 = 3;
    effect.ends[0] = 0x19;
    effect.ends[1] = 0xF;
    effect.ends[2] = 0x64;
    effect.ends[3] = 0x64;
    effect.ends[4] = 0xC;
    effect.ends[5] = 0x14;
    effect.final = 0;
    effect.values[4] = 203.0f;
    effect.values[5] = 414.0f;
    effect.values2[0] = 15.0f;
    effect.values2[1] = D_800A0AE0;
    effect.values2[2] = D_800A0AE4;
    effect.values2[3] = D_800A0AE8;
    func_1514FCE8((s16 *)&effect, arg1, arg2);
}
typedef struct GameD728CPayload {
    u8 bytes[0x12];
} GameD728CPayload;

void func_151BFC40(void *, f32 *);
void func_1514FBFC(void *, u8, s32);
void func_1514FB98(f32 *, u8, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D728C CURRENT (3507) */
void func_150D728C(GameD728CPayload *arg0, Game1045D0Position *arg1,
                   f32 *arg2, u8 arg3, s32 arg4) {
    f32 negative[3];
    f32 scratch_f;
    Game1045D0Position scratch_position;
    GameD728CPayload payload;
    u8 scratch[0x20];

    func_151C04F8((s32)arg1, arg3, arg4);
    func_151C05A4((s32)arg1, arg3, arg4);
    func_151C05F0((s32)arg1, arg3, arg4);
    if (arg0 != 0) {
        negative[0] = -arg2[0];
        negative[1] = -arg2[1];
        negative[2] = -arg2[2];
        payload = *arg0;
        scratch_position = *arg1;
        func_151BFC40(scratch, &scratch_f);
        func_1514FBFC(negative, arg3, arg4);
        return;
    }
    negative[0] = -arg2[0];
    negative[1] = -arg2[1];
    negative[2] = -arg2[2];
    func_151BFC40(scratch, &scratch_f);
    scratch_position = *arg1;
    func_1514FB98(negative, arg3, arg4);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D728C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1045D0/func_150D728C.s")
