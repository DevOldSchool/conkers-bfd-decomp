#include "types.h"

/*
 * Reviewed source unit: src/game/game_1A1B40.c
 * Boundary evidence: docs/evidence/game_raw_compact_display_resource_pairs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15174690
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game1A1B40Effect {
    s32 resource, value, parameter;
    s16 fieldC, fieldE, x, y, z, field16, field18, field1A;
    u8 pad1C[3];
    u8 kind;
    s16 field20, field22, scaleX, scaleY, field28;
    u8 field2A, field2B, red, green, blue, alpha;
    u8 pad30[4];
    s16 field34;
} Game1A1B40Effect;

f32 func_15047D60(f32);
f32 func_15047C00(f32);
s32 func_150ADA20(void);
void func_15167D84(void *, s32, s32, s32, u8, s32);
extern s32 D_8008CA4C;
extern f32 D_800A7160, D_800A7164;
extern u8 D_800CC2D0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15174690 CURRENT (815) */
void func_15174690(s32 arg0, s32 arg1, s32 arg2, u32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, s32 arg8) {
    f32 angle;
    f32 x;
    f32 y;
    f32 z;
    volatile s32 random;
    u8 *actor;
    Game1A1B40Effect effect;

    actor = D_800CC2D0 + arg0 * 0x32C;
    if (actor[0xAD] == 0 && D_800A7160 == *(f32 *)(actor + 0x118)) {
        x = *(f32 *)(actor + 0x14);
        y = *(f32 *)(actor + 0x18) + 5.0f;
        z = *(f32 *)(actor + 0x1C);
        angle = *(f32 *)(actor + 0x40) * D_800A7164;
        x -= 10.0f * func_15047D60(angle);
        z -= 10.0f * func_15047C00(angle);
        if (arg1 != 0) {
            x += (f32)((random = func_150ADA20()) % arg1);
            z += (f32)((random = func_150ADA20()) % arg1);
        }
        if (arg3 != 0) {
            arg2 += (u32)func_150ADA20() % arg3;
        }
        effect.resource = D_8008CA4C;
        effect.value = arg2;
        effect.parameter = arg5;
        effect.fieldC = 0;
        effect.fieldE = 0x100;
        effect.x = (s16)(s32)x;
        effect.y = (s16)(s32)y;
        effect.z = (s16)(s32)z;
        effect.field16 = 0;
        effect.field18 = 0;
        effect.field1A = 0;
        effect.kind = 5;
        effect.field20 = (s16)arg6;
        effect.field22 = 0;
        effect.scaleX = (s16)arg4;
        effect.scaleY = (s16)arg4;
        effect.field28 = 0x200;
        effect.field2A = 0;
        effect.field2B = 0;
        effect.red = 0xFF;
        effect.green = 0xFF;
        effect.blue = 0xFF;
        effect.alpha = 0xFF;
        effect.field34 = 0;
        func_15167D84(&effect, 0, 0, -1, arg7, arg8);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15174690 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1A1B40/func_15174690.s")
extern s32 D_800BE9E4;

void func_15174920(void *arg0) {
    s32 temp_v1;
    s32 value;

    value = *(u8 *)((u8 *)arg0 + 0x3F);
    if (value >= 0xC9) {
        value = 0xC8;
    }
    value -= D_800BE9E4 * *(s32 *)((u8 *)arg0 + 0x18);
    if (value < 0) {
        *(s16 *)((u8 *)arg0 + 0x38) = 0;
        return;
    }
    temp_v1 = *(s32 *)((u8 *)arg0 + 0x14);
    *(u8 *)((u8 *)arg0 + 0x3F) = (u8) value;
    *(s16 *)((u8 *)arg0 + 0x34) = (s16) (*(s16 *)((u8 *)arg0 + 0x34) + temp_v1);
    *(s16 *)((u8 *)arg0 + 0x36) = (s16) (*(s16 *)((u8 *)arg0 + 0x36) + ((s32) (temp_v1 * 8) / 7));
}
