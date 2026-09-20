#include "types.h"

/*
 * Reviewed source unit: src/game/game_19F150.c
 * Boundary evidence: docs/evidence/game_raw_animated_emission_controllers.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15171CA0
 * - func_15171D4C
 * - func_15171FC0
 * - func_151720C4
 * - func_151725FC
 * - func_15172B20
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game19F150Object {
    u8 pad0[0x16];
    s16 field_16;
    u8 pad18[0x0E];
    s16 field_26;
    u8 pad28[0x0E];
    s16 field_36;
    u8 pad38[0x0E];
    s16 field_46;
    u8 pad48[8];
    s16 field_50;
    s16 field_52;
    s16 field_54;
    u16 field_56;
    u8 field_58;
    s8 field_59;
} Game19F150Object;

extern Game19F150Object *func_15167A68(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15171CA0 CURRENT (595) */
Game19F150Object *func_15171CA0(s16 arg0, u16 arg1, u8 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6, s32 arg7) {
    Game19F150Object *var_v1;

    var_v1 = func_15167A68(arg5 == 0 ? 0xF : 0x43, arg7, 0x60, 1, arg6, 1);
    if (var_v1 == 0) {
        return 0;
    }
    var_v1->field_52 = 0;
    var_v1->field_50 = arg0;
    var_v1->field_54 = arg4;
    var_v1->field_56 = arg1;
    var_v1->field_58 = arg2;
    var_v1->field_16 = 0;
    var_v1->field_26 = 0;
    var_v1->field_36 = 0;
    var_v1->field_46 = 0;
    var_v1->field_59 = arg3;
    return var_v1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15171CA0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19F150/func_15171CA0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19F150/func_15171D4C.s")
void func_1516972C(Game19F150Object *);
Game19F150Object *func_15171CA0(s16, u16, u8, s32, s32, s32, u8, s32);
s32 func_151725FC(s32, s32, f32, f32, f32, f32, s32, s32);
extern u8 *D_8008CA4C[];

void func_15171F04(f32 arg0, f32 arg1, f32 arg2, s32 arg3,
                   s16 arg4, u16 arg5, u8 arg6, s32 arg7, s32 arg8,
                   s32 arg9, s32 arg10, u8 arg11, s32 arg12) {
    Game19F150Object *object;

    object = func_15171CA0(arg4, arg5, arg6, arg8, arg9, arg10,
                           (u8)arg11, arg12);
    if (object != 0) {
        if (func_151725FC((s32)((u8 *)object + 0x10), arg3, arg0, arg1,
                          arg2, 0.0f, arg7,
                          *(u16 *)((u8 *)D_8008CA4C[object->field_58] + 6)) == 0) {
            func_1516972C(object);
        }
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_19F150/func_15171FC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19F150/func_151720C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19F150/func_151725FC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_19F150/func_15172B20.s")
