#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_61D10.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_compact_display_resource_pairs.md
 */

/*
 * Actor fields used by func_15034860; the full actor is 0x32C bytes
 * (see Game61490Actor in game_61490.c).
 */
typedef struct Game61D10Actor {
    u8 pad0[4];
    u8 type;
    u8 pad5[0x1F9];
    u8 unk_1FE;
    u8 unk_1FF;
    u8 unk_200;
    u8 unk_201;
    s8 unk_202;
    s8 unk_203;
    s16 unk_204;
    u8 unk_206;
    u8 unk_207;
    s8 unk_208;
    s8 unk_209;
} Game61D10Actor;

extern s16 D_800C3EF0;
extern s32 D_800BE9E4;
f32 fabsf(f32);
#pragma intrinsic(fabsf)

GameCommand *func_15034860(GameCommand *cmd, Game61D10Actor *actor, s32 arg2, s32 arg3) {
    s32 skip;
    s32 value;
    f32 scale;
    s32 mode;
    s32 low;
    s32 high;
    s32 offsetA;
    s32 offsetB;
    s32 spread;
    s32 dir;
    s32 reroll;
    s32 flip;
    s16 limit;

    limit = 0xFF;
    skip = (actor->type == 0x70) ? 1 : 0;
    if (actor->type == 0x7C) {
        offsetA = 4;
        offsetB = 0;
    } else {
        offsetA = 0;
        offsetB = 2;
    }
    switch (actor->type) {
    case 0x69:
    case 0x7C:
    case 0x87:
        spread = 0;
        break;
    default:
        spread = 10;
        break;
    }
    if (arg2 != 0xFF) {
        if (actor->unk_201 == 0) {
            scale = 8191.875f;
        } else {
            scale = actor->unk_201 * 182.04445f;
        }
        value = (s16)(actor->unk_1FE * scale * (1.0f / 255.0f));
        if (!skip) {
            cmd->opcode = arg2 * 6 + offsetA;
            cmd->value = value;
            cmd++;
        }
        D_800C3EF0 = value;
        value = (s16)((f32)((actor->unk_202 * actor->unk_1FE) / 255) * 65535.0f * (1.0f / 255.0f));
        if (!skip) {
            cmd->opcode = arg2 * 6 + offsetB;
            cmd->value = value;
            cmd++;
        }
        if (actor->type == 0x42) {
            low = 80;
            high = 120;
        } else {
            low = 40;
            high = 60;
        }
        mode = actor->unk_1FF;
        if (mode == 0) {
            actor->unk_203 = -high;
        } else if (mode == 2) {
            actor->unk_203 = high;
            actor->unk_202 = 0;
        } else if (actor->unk_203 == 0 || actor->unk_1FE == 0 || actor->unk_1FE == limit) {
            actor->unk_203 = func_150ADA20() % (high - low) + low;
            if (actor->unk_1FE == limit) {
                actor->unk_203 = -actor->unk_203;
            } else if (actor->unk_1FE == 0 && spread != 0) {
                actor->unk_202 = func_150ADA20() % (spread * 2) - spread;
            }
        }
        mode = actor->unk_1FF;
        value = (s16)(actor->unk_1FE + (u16)actor->unk_203);
        value = (value < 0) ? 0 : (s16)((value > limit) ? limit : value);
        actor->unk_1FE = value;
        if (mode == 3) {
            if (actor->unk_200 >= D_800BE9E4) {
                actor->unk_200 -= D_800BE9E4;
            } else {
                actor->unk_200 = 0;
                actor->unk_1FF = 0;
            }
        }
    }
    if (arg3 != 0xFF) {
        if (actor->unk_208 == 0) {
            scale = 8191.875f;
        } else {
            scale = actor->unk_208 * 182.04445f;
        }
        if (scale < 0.0f) {
            dir = -1;
        } else {
            dir = 1;
        }
        scale = fabsf(scale);
        reroll = (s16)(actor->unk_204 * scale * (1.0f / 255.0f));
        cmd->opcode = arg3 * 6 + offsetA;
        cmd->value = -reroll;
        cmd++;
        reroll = 0;
        flip = 0;
        if (actor->unk_206 == 0) {
            if (dir > 0) {
                actor->unk_209 = -60;
            } else {
                actor->unk_209 = 60;
            }
        } else if (actor->unk_206 == 2) {
            if (dir > 0) {
                actor->unk_209 = 60;
            } else {
                actor->unk_209 = -60;
            }
        } else if (actor->unk_209 == 0) {
            reroll = 1;
        } else {
            value = actor->unk_204;
            if (dir > 0) {
                if (value < 0 && actor->unk_209 < 0) {
                    flip = 1;
                } else if (value == 0 && actor->unk_209 < 0) {
                    reroll = 1;
                } else if (value == limit) {
                    flip = 1;
                    reroll = 1;
                }
            } else {
                if (value > 0 && actor->unk_209 > 0) {
                    flip = 1;
                } else if (value == 0 && actor->unk_209 > 0) {
                    reroll = 1;
                } else if (value == -limit) {
                    flip = 1;
                    reroll = 1;
                }
            }
        }
        if (reroll) {
            actor->unk_209 = func_150ADA20() % 20 + 40;
            actor->unk_209 *= dir;
        }
        if (flip) {
            actor->unk_209 = -actor->unk_209;
        }
        actor->unk_204 += actor->unk_209;
        if (dir > 0) {
            if (actor->unk_204 < 0 && actor->unk_209 < 0) {
                actor->unk_204 = 0;
            } else if (actor->unk_204 > limit) {
                actor->unk_204 = limit;
            }
        } else {
            if (actor->unk_204 > 0 && actor->unk_209 > 0) {
                actor->unk_204 = 0;
            } else if (actor->unk_204 < -limit) {
                actor->unk_204 = -limit;
            }
        }
        if (actor->unk_206 == 3) {
            if (actor->unk_207 >= D_800BE9E4) {
                actor->unk_207 -= D_800BE9E4;
            } else {
                actor->unk_206 = actor->unk_207 = 0;
            }
        }
    }
    return cmd;
}

void func_15034EB4(void *arg0, s32 arg1, s32 arg2) {
    f32 temp_fv0;
    s32 temp_v1;
    void *temp_a2;
    void *tmp2;
    u8 *tmp3;
    s16 *tmp4;
    void *temp_v0;

    if (D_800C3EF0 != 0) {
        tmp2 = arg0;
        temp_v1 = *(s32 *)((u8 *)arg0 + 0x1D4);
        tmp3 = (u8 *)tmp2 + 0x14C;
        temp_a2 = (void *)(((u32)arg1 << 6) + temp_v1);
        temp_v0 = (void *)(((u32)arg2 << 6) + temp_v1);
        tmp4 = &D_800C3EF0;
        temp_fv0 = *(f32 *)tmp3 * ((f32) *tmp4 * 0.00076296274f);
        *(f32 *)((u8 *)temp_a2 + 0x34) = (f32) (*(f32 *)((u8 *)temp_a2 + 0x34) - temp_fv0);
        if (arg2 != -1) {
            *(f32 *)((u8 *)temp_v0 + 0x34) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x34) - temp_fv0);
        }
    }
}
