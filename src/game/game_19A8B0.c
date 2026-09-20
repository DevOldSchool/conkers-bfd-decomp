#include "types.h"

/*
 * Reviewed source unit: src/game/game_19A8B0.c
 * Boundary evidence: docs/evidence/game_raw_state_lifecycle_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1516D400
 * - func_1516D4E8
 * - func_1516D738
 * - func_1516DB90
 * - func_1516E8CC
 * - func_1516ED68
 * - func_1516EED4
 * - func_1516F548
 * - func_1516FE1C
 * - func_151700D8
 * - func_15170500
 * - func_151707E0
 * - func_151709B4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game19A8B0Link {
    u8 pad0[4];
    s16 status;
} Game19A8B0Link;

typedef struct Game19A8B0Motion {
    u8 pad0[0xE];
    s16 x;
    s16 y;
    s16 z;
    s16 scaleX;
    s16 scaleY;
    s16 velocityY;
    u8 pad1A[5];
    u8 alpha;
    u8 pad20[3];
    u8 kind;
    u8 active;
    u8 yFraction;
    s8 velocityXHigh;
    u8 velocityXLow;
    s8 velocityZHigh;
    u8 velocityZLow;
    u8 xFraction;
    u8 zFraction;
    u8 sizeHigh;
    u8 sizeLow;
    u8 pad2E[2];
    struct Game19A8B0Link *link;
} Game19A8B0Motion;

void func_1516D99C(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, u8, s32);

void func_1516D4E8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14, s32 arg15, s32 arg16, s32 arg17, s32 arg18, s32 arg19, s32 arg20, s32 arg21, s32 arg22, s32 arg23, s32 arg24, s32 arg25, s32 arg26, s32 arg27, s32 arg28, u8 arg29, s32 arg30);

s32 func_151EF610();

extern u8 D_800BE9A0;
extern u8 D_800DD2A0[4];
extern u8 D_800DD2A1;
extern u8 D_800DD2A2;
extern u8 D_800DD2A3;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516D400 CURRENT (2640) */
void func_1516D400(void) {
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;

    if ((s32) D_800DD2A0[0] < 0xFF) {
        var_v0 = D_800DD2A0[0] + D_800BE9A0;
        if (var_v0 >= 0x100) {
            var_v0 = 0xFF;
        }
        D_800DD2A0[0] = (u8) var_v0;
    }
    if ((s32) D_800DD2A1 < 0xFF) {
        var_v0_2 = D_800DD2A1 + D_800BE9A0;
        if (var_v0_2 >= 0x100) {
            var_v0_2 = 0xFF;
        }
        D_800DD2A1 = (u8) var_v0_2;
    }
    if ((s32) D_800DD2A2 < 0xFF) {
        var_v0_3 = D_800DD2A2 + D_800BE9A0;
        if (var_v0_3 >= 0x100) {
            var_v0_3 = 0xFF;
        }
        D_800DD2A2 = (u8) var_v0_3;
    }
    if ((s32) D_800DD2A3 < 0xFF) {
        var_v0_4 = D_800DD2A3 + D_800BE9A0;
        if (var_v0_4 >= 0x100) {
            var_v0_4 = 0xFF;
        }
        D_800DD2A3 = (u8) var_v0_4;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516D400 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516D400.s")

void *func_15167A68(s32, s32, s32, s32, u8, u8);
void *func_150448D0(s32, void *, s32, s32, s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516D4E8 CURRENT (60) */
void func_1516D4E8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14, s32 arg15, s32 arg16, s32 arg17, s32 arg18, s32 arg19, s32 arg20, s32 arg21, s32 arg22, s32 arg23, s32 arg24, s32 arg25, s32 arg26, s32 arg27, s32 arg28, u8 arg29, s32 arg30) {
    Game19A8B0Motion *result;
    s32 kind;

    kind = arg27 ? 0x67 : 0x12;
    result = func_15167A68(kind, arg30, 0x34, 0, arg29, 1);
    if (result != 0) {
        result->x = ((s16 *)&arg0)[1];
        result->y = ((s16 *)&arg1)[1];
        result->z = ((s16 *)&arg2)[1];
        result->pad1A[0] = ((u8 *)&arg3)[3];
        result->pad1A[1] = ((u8 *)&arg4)[3];
        result->pad1A[2] = ((u8 *)&arg5)[3];
        result->pad1A[3] = ((u8 *)&arg6)[3];
        result->pad1A[4] = ((u8 *)&arg7)[3];
        result->alpha = ((u8 *)&arg8)[3];
        result->pad20[0] = ((u8 *)&arg9)[3];
        result->pad20[1] = ((u8 *)&arg10)[3];
        result->pad20[2] = ((u8 *)&arg11)[3];
        result->kind = ((u8 *)&arg12)[3];
        result->scaleX = ((s16 *)&arg23)[1];
        result->scaleY = ((s16 *)&arg24)[1];
        result->active = ((u8 *)&arg25)[3];
        result->velocityY = ((s16 *)&arg26)[1];
        result->yFraction = 0;
        result->velocityXHigh = ((u8 *)&arg13)[3];
        result->velocityXLow = ((u8 *)&arg14)[3];
        result->velocityZHigh = ((u8 *)&arg15)[3];
        result->velocityZLow = ((u8 *)&arg16)[3];
        result->xFraction = ((u8 *)&arg17)[3];
        result->zFraction = ((u8 *)&arg18)[3];
        result->sizeHigh = ((u8 *)&arg19)[3];
        result->sizeLow = ((u8 *)&arg20)[3];
        result->pad2E[0] = ((u8 *)&arg21)[3];
        result->pad2E[1] = ((u8 *)&arg22)[3];
        if (arg28 != 0) {
            result->link = func_150448D0(-1, 0, arg28, 0x14, 0x14, 0x14, 0, (s32)&result->x, (s32)&result->scaleX);
            return;
        }
        result->link = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516D4E8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516D4E8.s")

extern s32 D_800BE9E4;
extern s32 (*D_8008CBA0[])(Game19A8B0Motion *);
void func_1516972C(void *);

void func_1516D678(Game19A8B0Motion *arg0) {
    s32 value;
    Game19A8B0Link *link;

    value = arg0->active;
    if (value != 0) {
        value -= D_800BE9E4;
        if (value < 0) {
            value = 0;
        }
        arg0->active = value;
    }
    if (D_8008CBA0[arg0->kind](arg0) == 1) {
        link = arg0->link;
        if (link != 0) {
            link->status = 0;
        }
        func_1516972C(arg0);
        return;
    }
    value = arg0->y;
    value <<= 8;
    value += arg0->yFraction;
    value += arg0->velocityY * D_800BE9E4;
    arg0->y = value >> 8;
    value = (u8)value;
    arg0->yFraction = value;
}
typedef struct Game19A8B0Resource {
    u8 pad0[0xA];
    u8 type;
} Game19A8B0Resource;

typedef struct Game19A8B0Command {
    u32 word0;
    u32 word1;
} Game19A8B0Command;

typedef struct Game19A8B0Sprite {
    s16 x;
    s16 y;
    s16 z;
    s16 scaleX;
    s16 scaleY;
    u8 alpha;
    u8 padB[2];
    u8 flags;
} Game19A8B0Sprite;

extern Game19A8B0Resource *D_8008CA4C[];
extern s32 D_800D2C9C;
extern u8 D_800D2DA8;
extern u8 D_800D2DA9;
extern u8 D_800D2DAA;
extern s8 D_800D2DAB;
extern s16 D_800DD1BC;
extern s16 D_800DD1C8;
extern s16 D_800DD1CA;
extern s16 D_800DD1CC;
s32 func_15142E24(s32, s32, s32, s32, s32, s32, s32, u8, s32, u8 *, s32);
void *func_15142FBC(void *, s32, s32, u8 *);
void *func_15095760(void *, Game19A8B0Sprite *, u8, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516D738 CURRENT (3661) */
void *func_1516D738(s32 arg0, Game19A8B0Motion *arg1, s32 arg2) {
    struct {
        s32 renderFlags;
        u8 pad4[0x18];
        s32 sync;
        Game19A8B0Resource *resource;
        u8 pad24[4];
        Game19A8B0Sprite sprite;
        u8 pad36[6];
    } local;
    Game19A8B0Command *result;
    s16 mode;
    u8 red;
    u8 green;
    u8 blue;

    local.sync = 0;
    D_800D2DAB = 0;
    local.resource = D_8008CA4C[arg1->pad1A[0]];
    result = (void *)func_15142E24(arg0, (s32)local.resource, arg1->pad1A[1] << 8,
        2, 0x100, 0x100, 0, 6, (s32)&local.sprite, (u8 *)&local.sync, 3);
    arg0 = (s32)result;
    mode = local.resource->type == 5 ? 2 : 1;
    if (mode != D_800DD1BC) {
        if (local.sync == 0) {
            arg0 = (s32)(result + 1);
            result->word0 = 0xE7000000;
            result->word1 = 0;
            local.sync = 1;
        }
        D_800DD1BC = mode;
        if (mode == 1) {
            local.renderFlags = 0;
            result = (void *)arg0;
            result->word0 = 0xFC30B261;
            result->word1 = 0x5566FF7F;
            arg0 += 8;
        } else {
            local.renderFlags = 0x100000;
            result = (void *)arg0;
            result->word0 = 0xFC30B5FF;
            result->word1 = 0x5FFEFE38;
            arg0 += 8;
        }
    }
    /* The raw function retains this stack value when the cached mode is unchanged. */
    result = func_15142FBC((void *)arg0, local.renderFlags | D_800D2C9C | 0x2C00,
        0x5049DC, (u8 *)&local.sync);
    local.sprite.x = arg1->x;
    arg0 = (s32)result;
    local.sprite.y = arg1->y;
    local.sprite.z = arg1->z;
    local.sprite.scaleX = arg1->scaleX;
    local.sprite.scaleY = arg1->scaleY;
    local.sprite.alpha = arg1->alpha;
    local.sprite.flags = 0;
    D_800D2DA8 = arg1->pad1A[2];
    D_800D2DA9 = arg1->pad1A[3];
    D_800D2DAA = arg1->pad1A[4];
    red = arg1->pad20[0];
    green = arg1->pad20[1];
    blue = arg1->pad20[2];
    if (red != D_800DD1C8 || green != D_800DD1CA || blue != D_800DD1CC) {
        D_800DD1C8 = red;
        D_800DD1CA = green;
        D_800DD1CC = blue;
        if (local.sync == 0) {
            result->word0 = 0xE7000000;
            arg0 = (s32)(result + 1);
            result->word1 = 0;
        }
        result = (void *)arg0;
        result->word1 = (red << 24) | ((green & 0xFF) << 16) | ((blue & 0xFF) << 8);
        result->word0 = 0xFB000000;
        arg0 += 8;
    }
    return func_15095760((void *)arg0, &local.sprite, green, blue);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516D738 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516D738.s")

typedef struct Game19A8B0Emitter {
    u8 pad0[0xE];
    s16 x;
    s16 y;
    s16 z;
    s16 scaleX;
    s16 scaleY;
    s16 scaleTargetX;
    s16 scaleTargetY;
    s16 angle;
    u16 spread;
    u16 timer;
    u16 flags;
    u8 data[0x25];
    u8 pad49[3];
} Game19A8B0Emitter;

void func_1516D99C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14, s32 arg15, s32 arg16, s32 arg17, s32 arg18, s32 arg19, s32 arg20, s32 arg21, s32 arg22, s32 arg23, s32 arg24, s32 arg25, s32 arg26, s32 arg27, s32 arg28, s32 arg29, s32 arg30, s32 arg31, s32 arg32, s32 arg33, s32 arg34, s32 arg35, s32 arg36, s32 arg37, s32 arg38, s32 arg39, s32 arg40, s32 arg41, s32 arg42, s32 arg43, s32 arg44, s32 arg45, s32 arg46, u8 arg47, s32 arg48) {
    s32 var_a0;
    u16 timer;
    Game19A8B0Emitter *temp_v0;

    if (arg44 != 0) {
        var_a0 = 0x66;
    } else {
        var_a0 = 0x11;
    }
    temp_v0 = func_15167A68(var_a0, arg48, 0x4C, 0, (u8) (s32) arg47, 1U);
    if (temp_v0 != 0) {
        temp_v0->x = ((s16 *)&arg0)[1];
        temp_v0->y = ((s16 *)&arg1)[1];
        temp_v0->z = ((s16 *)&arg2)[1];
        temp_v0->scaleX = ((s16 *)&arg27)[1];
        temp_v0->scaleY = ((s16 *)&arg28)[1];
        temp_v0->scaleTargetX = ((s16 *)&arg29)[1];
        temp_v0->scaleTargetY = ((s16 *)&arg30)[1];
        temp_v0->data[0x0] = ((u8 *)&arg3)[3];
        temp_v0->data[0x1] = ((u8 *)&arg4)[3];
        temp_v0->data[0x2] = ((u8 *)&arg5)[3];
        temp_v0->data[0x3] = ((u8 *)&arg6)[3];
        temp_v0->data[0x4] = ((u8 *)&arg7)[3];
        temp_v0->data[0x6] = ((u8 *)&arg9)[3];
        temp_v0->data[0x7] = ((u8 *)&arg10)[3];
        temp_v0->data[0x8] = ((u8 *)&arg11)[3];
        temp_v0->data[0x5] = ((u8 *)&arg8)[3];
        temp_v0->data[0x9] = ((u8 *)&arg12)[3];
        temp_v0->data[0xA] = ((u8 *)&arg13)[3];
        temp_v0->data[0xB] = ((u8 *)&arg14)[3];
        temp_v0->data[0xC] = ((u8 *)&arg15)[3];
        temp_v0->data[0xD] = ((u8 *)&arg16)[3];
        temp_v0->data[0xE] = ((u8 *)&arg17)[3];
        temp_v0->data[0xF] = ((u8 *)&arg18)[3];
        temp_v0->data[0x10] = ((u8 *)&arg19)[3];
        temp_v0->data[0x11] = ((u8 *)&arg20)[3];
        temp_v0->data[0x12] = ((u8 *)&arg21)[3];
        temp_v0->data[0x13] = ((u8 *)&arg22)[3];
        temp_v0->data[0x14] = ((u8 *)&arg23)[3];
        temp_v0->data[0x15] = ((u8 *)&arg24)[3];
        temp_v0->data[0x16] = ((u8 *)&arg25)[3];
        timer = ((u16 *)&arg31)[1];
        temp_v0->data[0x17] = ((u8 *)&arg26)[3];
        temp_v0->timer = timer;
        temp_v0->data[0x18] = timer;
        temp_v0->data[0x19] = ((u8 *)&arg32)[3];
        temp_v0->data[0x1A] = ((u8 *)&arg33)[3];
        temp_v0->data[0x1B] = ((u8 *)&arg34)[3];
        temp_v0->data[0x1C] = ((u8 *)&arg35)[3];
        temp_v0->angle = ((s16 *)&arg36)[1];
        temp_v0->spread = ((u16 *)&arg37)[1];
        temp_v0->flags = ((u16 *)&arg38)[1];
        temp_v0->data[0x1D] = ((u8 *)&arg39)[3];
        temp_v0->data[0x1E] = 0;
        temp_v0->data[0x1F] = ((u8 *)&arg40)[3];
        if ((arg44 != 0) && ((s32) ((u8 *)&arg41)[3] >= 4)) {
            ((u8 *)&arg41)[3] = 3;
        }
        temp_v0->data[0x20] = ((u8 *)&arg41)[3];
        temp_v0->data[0x21] = ((u8 *)&arg42)[3];
        temp_v0->data[0x22] = ((u8 *)&arg43)[3];
        temp_v0->data[0x23] = ((u8 *)&arg45)[3];
        temp_v0->data[0x24] = ((u8 *)&arg46)[3];
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516DB90.s")
void func_1516E778(u32 arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4) {
    func_1516D99C((s16)(arg0 >> 16), (s16)(arg0 & 0xFFFF), 0, arg2,
        0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0,
        8, 8, 1, 0, 0, 0, 0, 0x155, 0x155, 0x155, 0x155, arg1,
        0x1E, 0, 0xFF, 0x28, 0x168, 0x18, 0x21, 4, 0, 1,
        0, 0, 0, 0, 0, arg3, arg4);
}
extern u8 D_800A6E00[];
extern u8 D_800A6E0C[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516E8CC CURRENT (400) */
s32 func_1516E8CC(Game19A8B0Motion *arg0) {
    s32 value;
    s32 progress;
    s32 index;
    u8 *threshold;
    u8 *color;
    void *cursor;
    f32 amount;
    f32 remaining;

    cursor = arg0;
    value = arg0->alpha;
    if (arg0->active != 0) {
        if (value != 0xFF) {
            value += D_800BE9E4 << 5;
            if (value >= 0x100) {
                value = 0xFF;
            }
            arg0->alpha = value;
        }
    } else if (value != 0) {
        value -= D_800BE9E4 * 0x10;
        if (value < 0) {
            value = 0;
        }
        arg0->alpha = value;
    }
    if (arg0->active == 0 && value == 0) {
        return 1;
    }
    value = arg0->scaleX;
    value += D_800BE9E4 * 0xA;
    arg0->scaleY = value;
    arg0->scaleX = value;
    progress = arg0->active;
    if (arg0->active == 0) {
        progress = arg0->active + (arg0->alpha >> 5);
    } else {
        progress += 8;
    }
    index = (u8)arg0->velocityXHigh;
    if (index < (u8)arg0->velocityXHigh + 8) {
        threshold = D_800A6E00 + index;
        do {
            if (progress >= *threshold) {
                amount = (f32)(progress - *threshold) / (f32)(threshold[-1] - *threshold);
                cursor = D_800A6E0C + index * 3;
                color = cursor;
                remaining = 1.0f - amount;
                arg0->pad1A[2] = (u32)((f32)(u32)color[0] * remaining + (f32)(u32)color[-3] * amount);
                arg0->pad1A[3] = (u32)((f32)(u32)color[1] * remaining + (f32)(u32)color[-2] * amount);
                arg0->pad1A[4] = (u32)((f32)(u32)color[2] * remaining + (f32)(u32)color[-1] * amount);
                break;
            }
            index++;
            threshold++;
        } while (index < (u8)((Game19A8B0Motion *)cursor)->velocityXHigh + 8);
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516E8CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516E8CC.s")

extern s32 D_800BE9E4;



s32 func_1516ECAC(Game19A8B0Motion *arg0) {
    s32 size;
    s32 product;
    s32 var_v1;

    var_v1 = arg0->alpha;
    if (arg0->active != 0) {
        if (var_v1 != 0xFF) {
            var_v1 += D_800BE9E4 << 7;
            if ((s32) var_v1 >= 0x100) {
                var_v1 = 0xFF;
            }
            arg0->alpha = var_v1;
        }
    } else if (var_v1 != 0) {
        var_v1 -= D_800BE9E4 * (u8)arg0->velocityXHigh;
        if ((s32) var_v1 < 0) {
            var_v1 = 0;
        }
        arg0->alpha = var_v1;
    }
    if ((arg0->active == 0) && (var_v1 == 0)) {
        return 1;
    }
    size = (arg0->sizeHigh << 8) | arg0->sizeLow;
    product = size * var_v1;
    arg0->scaleY = product >> 7;
    arg0->scaleX = product >> 7;
    return 0;
}
extern u8 D_800CC2D4[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516ED68 CURRENT (361) */
void func_1516ED68(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    s32 state;

    state = D_800CC2D4[arg0 * 0x32C];
    if (state == 0x3A) {
        func_1516D99C(5, 0, 0, 4, 0, 0xFF, 0xFF, 0xFF,
            0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 8,
            0, 0, 0, 0, 0, 0, 0, 0x124, 0x124, 0, 0, arg1,
            0, 0, arg0, 0xC, 0, 0, 0x81, 2, 0, 1,
            0, 0, 0, 5, 0, arg2, arg3);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516ED68 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516ED68.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516EED4 CURRENT (2667) */
void func_1516EED4(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    u8 *timer;

    timer = &D_800DD2A0[arg0];
    if (arg0 < 4 && *timer >= arg1) {
        *timer = 0;
        func_1516D99C(0, 0, 0, 4, 0, 0xFF, 0xFF, 0xFF,
            0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0x200, 0x200, 0, 0, 0x1E,
            0, 0, arg0, 0x14, 0, 0, 0x81, 8, 0, 1,
            0, 0, 0, 0xC, 0, arg2, arg3);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516EED4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516EED4.s")
typedef struct Game19A8B0Table {
    u8 value[11];
} Game19A8B0Table;

extern const Game19A8B0Table D_8008CBC4;
extern const Game19A8B0Table D_8008CBD0;
extern const Game19A8B0Table D_8008CBDC;
extern const Game19A8B0Table D_8008CBE8;
void func_1516F864(Game19A8B0Motion *);
void func_1516F94C(s32, s32);

s32 func_1516F024(Game19A8B0Motion *arg0) {
    s32 unused[2];
    s32 alpha;
    s32 limit;
    s32 mode;
    Game19A8B0Table damping;
    Game19A8B0Table growth;
    Game19A8B0Table maximum;
    Game19A8B0Table fade;
    s32 size;

    damping = D_8008CBC4;
    growth = D_8008CBD0;
    maximum = D_8008CBDC;
    fade = D_8008CBE8;
    mode = arg0->sizeHigh;
    alpha = arg0->alpha;
    if (arg0->active != 0) {
        limit = maximum.value[mode];
        if (alpha != limit) {
            alpha += D_800BE9E4 * 0x10;
            if (limit < alpha) {
                alpha = limit;
            }
            arg0->alpha = alpha;
        }
    } else if (alpha != 0) {
        alpha -= D_800BE9E4 * fade.value[mode];
        if (alpha < 0) {
            alpha = 0;
        }
        arg0->alpha = alpha;
    }
    if (arg0->active == 0 && alpha == 0) {
        return 1;
    }
    func_1516F864(arg0);
    size = arg0->scaleX;
    size += D_800BE9E4 * growth.value[mode];
    arg0->scaleY = size;
    arg0->scaleX = size;
    if (mode == 3) {
        arg0->velocityY = 0x64;
    }
    func_1516F94C((s32)arg0, damping.value[mode]);
    return 0;
}

void func_1516F1C0(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    func_1516D99C(2, 0, 0, 0x2D, 0, 0xFF, 0xFF, 0xFF,
        0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1,
        0, 0, 0, 0, 0, 0, 0, 0x50, 0x50, 0, 0, arg1,
        0xA, 0xA, arg0, 0x3C, 0, 0, 0x81, 4, 0, 1,
        0, 0, 0, 4, 2, arg2, arg3);
}
void func_1516F2F8(u8 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    func_1516D99C(3, 0, 0, 0x2B, 0, 0xFF, 0xFF, 0xFF,
        0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2,
        0, 0, 0, 0, 0, 0, 0, 0x50, 0x50, 0, 0, arg1,
        4, 4, arg0, 0x10, 0, 0, 0x81, 4, 0, 1,
        0, 0, 0, 1, 0, arg4, arg5);
    func_1516D99C(3, 0, 0, 0x2B, 0, 0xFF, 0xFF, 0xFF,
        0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 3,
        0, 0, 0, 0, 0, 0, 0, 0x50, 0x50, 0, 0, 7,
        4, 4, arg0, arg2, 0, 0, 0x81, 5, 0, 1,
        0, 0, 0, 1, arg3, arg4, arg5);
}
void func_1000FA64(s32, s32, s32, s32, s32, s32, s32, void *, s32, s32, s32, s32);
extern u8 D_1000EBC4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516F548 CURRENT (5360) */
void func_1516F548(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s16 arg5, u8 arg6, s32 arg7, s32 arg8, u8 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14, u8 arg15, s32 arg16) {
    s32 x;
    s32 y;
    s32 z;
    s32 scaleX;
    s32 scaleY;
    s32 timer;

    scaleX = (arg7 << 12) / 4096;
    scaleY = (arg8 << 12) / 4096;
    x = ((s16 *)&arg0)[1];
    y = ((s16 *)&arg1)[1];
    z = ((s16 *)&arg2)[1];
    timer = ((u16 *)&arg3)[1];
    func_1516D99C(x, y, z, 0xD, 0, 0x67, 0x17, 0xD,
        0, 0, 0x12, 0, 2, arg4, 0, arg6, 0, 0, 0, arg10,
        0, 0, 0, 0, 0, 0, 0, (s16)scaleX, (s16)scaleX,
        (s16)scaleY, (s16)scaleY, timer, arg9,
        0x14, 0xFF, 0x10, arg5, 0xC8, 1, 0, 0, 1,
        0, 0, 0, 0, 0, arg15, arg16);
    func_1516D99C(((s16 *)&x)[1], ((s16 *)&y)[1], ((s16 *)&z)[1],
        0xD, 0, 0x67, 0x17, 0xD, 0, 0, 0x12, 0, 2,
        arg4, 0, arg6, 0, 0, 0, arg11, 0, 0, 0, 0, 0, 0, 0,
        (s16)scaleX, (s16)scaleX, (s16)scaleY, (s16)scaleY,
        timer, arg9, 0x14, 0xFF, 0x10, arg5,
        0xC8, 1, 6, 0, 1, 0, 0, 0, 0, 0, arg15, arg16);
    func_1000FA64(7, ((s16 *)&x)[1], ((s16 *)&y)[1], ((s16 *)&z)[1],
        0x36B0, 0x3E8, 0x64, &D_1000EBC4, arg3, 0, 0, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516F548 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516F548.s")

extern s32 D_800BE9E4;



void func_1516F864(Game19A8B0Motion *arg0) {
    s32 x;
    s32 velocity;
    s32 z;

    x = arg0->x;
    x <<= 8;
    x += arg0->xFraction;
    velocity = arg0->velocityXHigh;
    velocity <<= 8;
    velocity += arg0->velocityXLow;
    x += velocity * D_800BE9E4;
    arg0->x = x >> 8;
    x = (u8)x;
    arg0->xFraction = x;
    z = arg0->z;
    z <<= 8;
    z += arg0->zFraction;
    velocity = arg0->velocityZHigh;
    velocity <<= 8;
    velocity += arg0->velocityZLow;
    z += velocity * D_800BE9E4;
    arg0->z = z >> 8;
    z = (u8)z;
    arg0->zFraction = z;
}

void func_1516F8EC(void *arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = *(s8 *)((u8 *)arg0 + 0x26);
    temp_v0 <<= 8;
    temp_v0 += *(u8 *)((u8 *)arg0 + 0x27);
    temp_v0 *= arg1;
    temp_v0 >>= 8;
    *(s8 *)((u8 *)arg0 + 0x26) = (s8)(temp_v0 >> 8);
    temp_v0 = (u8)temp_v0;
    *(u8 *)((u8 *)arg0 + 0x27) = temp_v0;
}
void func_1516F91C(void *arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = *(s8 *)((u8 *)arg0 + 0x28);
    temp_v0 <<= 8;
    temp_v0 += *(u8 *)((u8 *)arg0 + 0x29);
    temp_v0 *= arg1;
    temp_v0 >>= 8;
    *(s8 *)((u8 *)arg0 + 0x28) = (s8)(temp_v0 >> 8);
    temp_v0 = (u8)temp_v0;
    *(u8 *)((u8 *)arg0 + 0x29) = temp_v0;
}
void func_1516F94C(s32 arg0, s32 arg1) {
    func_1516F8EC((void *)arg0, arg1);
    func_1516F91C((void *)arg0, arg1);
}
void func_1516F984(s32 arg0, s32 arg1) {
    s32 temp_t6;
    s32 temp_v0;

    func_1516F94C(arg0, arg1);
    temp_t6 = arg1;
    temp_v0 = *(s16 *)((u8 *)arg0 + 0x18);
    temp_v0 = (temp_v0 * temp_t6) >> 8;
    *(s16 *)((u8 *)arg0 + 0x18) = (s16)temp_v0;
}
s32 func_1516F9C4(Game19A8B0Motion *arg0) {
    s32 alpha;
    s32 scale;

    alpha = arg0->alpha;
    if (arg0->active != 0) {
        if (alpha != 0xFF) {
            alpha += D_800BE9E4 * 0x10;
            if (alpha >= 0x100) {
                alpha = 0xFF;
            }
            arg0->alpha = alpha;
        }
    } else {
        if (alpha != 0) {
            alpha -= D_800BE9E4 * 8;
            if (alpha < 0) {
                alpha = 0;
            }
            arg0->alpha = alpha;
        }
        scale = alpha << 9;
        arg0->scaleY = scale >> 8;
        arg0->scaleX = scale >> 8;
    }
    if (arg0->active == 0 && alpha == 0) {
        return 1;
    }
    func_1516F864(arg0);
    func_1516F984((s32)arg0, 0xF0);
    return 0;
}
void func_1516FA88(s16 arg0, s16 arg1, s16 arg2, s32 arg3, u8 arg4, s32 arg5) {
    func_1516D99C(arg0, arg1, arg2, 0x1B, 0, 0xFF, 0xFF, 0xFF,
        0, 0xFF, 0xFF, 0xFF, 3, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0x400, 0x400, 0, 0, 2,
        0, 0, 0xFF, 0xF, 0, 0, 9, 0, 0xFF, 0xA, 0x5A,
        5, arg3, 0, 0, arg4, arg5);
}
typedef struct Game19A8B0Color {
    u8 pad0[0x14];
    s16 scaleX;
    s16 scaleY;
    u8 pad18[4];
    u8 red, green, blue, alpha;
    u8 pad20[4];
    u8 active;
    u8 pad25;
    u8 fromRed, fromGreen, fromBlue;
    u8 toRed, toGreen, toBlue;
    u8 phase;
    s8 scaleXStep, scaleYStep;
    u8 fadeShift;
} Game19A8B0Color;

s32 func_1516FBCC(Game19A8B0Color *arg0) {
    s32 value;
    s16 scale;
    s32 color;
    s32 target;

    value = arg0->alpha;
    if (arg0->active != 0) {
        if (value != 0xFF) {
            value += D_800BE9E4 * 0x10;
            if (value >= 0x100) {
                value = 0xFF;
            }
            arg0->alpha = value;
        }
    } else if (value != 0) {
        value -= D_800BE9E4 << arg0->fadeShift;
        if (value < 0) {
            value = 0;
        }
        arg0->alpha = value;
    }
    if (arg0->active == 0 && value == 0) {
        return 1;
    }
    value = arg0->scaleXStep;
    value *= D_800BE9E4;
    arg0->scaleX += value;
    value = arg0->scaleYStep;
    value *= D_800BE9E4;
    scale = arg0->scaleX;
    arg0->scaleY += value;
    if (scale <= 0 || scale <= 0) {
        arg0->scaleY = 0;
        arg0->scaleX = arg0->scaleY;
        return 1;
    }
    value = arg0->phase;
    value += D_800BE9E4;
    if (value >= 0x80) {
        value = 0x7F;
    }
    color = arg0->fromRed;
    arg0->phase = value;
    value *= 2;
    target = arg0->toRed;
    arg0->red = (((target - color) * value) >> 8) + color;
    color = arg0->fromGreen;
    target = arg0->toGreen;
    arg0->green = (((target - color) * value) >> 8) + color;
    color = arg0->fromBlue;
    target = arg0->toBlue;
    arg0->blue = (((target - color) * value) >> 8) + color;
    return 0;
}
s32 func_1516FD50(Game19A8B0Motion *arg0) {
    s32 alpha;
    s32 scale;

    alpha = arg0->alpha;
    if (arg0->active != 0) {
        if (alpha != 0xFF) {
            alpha += D_800BE9E4 * 0x10;
            if (alpha >= 0x100) {
                alpha = 0xFF;
            }
            arg0->alpha = alpha;
        }
    } else {
        if (alpha != 0) {
            alpha -= D_800BE9E4 * 8;
            if (alpha < 0) {
                alpha = 0;
            }
            arg0->alpha = alpha;
        }
        scale = alpha << 9;
        arg0->scaleY = scale >> 8;
        arg0->scaleX = scale >> 8;
    }
    if (arg0->active == 0 && alpha == 0) {
        return 1;
    }
    func_1516F864(arg0);
    arg0->velocityY += (s8)arg0->sizeHigh;
    return 0;
}
extern u8 D_800CC2D0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1516FE1C CURRENT (2090) */
void func_1516FE1C(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    s16 upper;
    s16 lower;
    s32 *actor;
    s32 mode;
    s32 index;
    s32 flags;
    s32 kind;
    s32 position;

    actor = (s32 *)(arg0 * 0x32C + D_800CC2D0);
    flags = 0;
    index = 0;
    if (*actor == 1) {
        upper = 4;
        lower = 0;
        kind = 0x19;
        mode = 1;
    } else {
        position = (s32)((u8 *)actor + 0x14);
        upper = position >> 16;
        lower = position;
        arg0 = 0xFF;
        mode = 0x21;
        /* The original inactive-actor path leaves kind uninitialized. */
    }
    do {
        if (index == 1) {
            kind = 0x1B;
            flags = 8;
        }
        func_1516D99C(upper, lower, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, flags, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0xAA, 0xAA, 0xAA, 0xAA, arg1 & 0xFFFF, 0x1E, 0,
            arg0 & 0xFF, 0x1E, 0x168, 0x18, mode & 0xFFFF, 4,
            0, 1, 0, 0, 0, kind, 0, arg2, arg3);
        index++;
    } while (index != 2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1516FE1C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516FE1C.s")
f32 func_150489B0(u8);
f32 func_15048A40(u8);
u32 func_150ADA20(void);

void func_15170034(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    s32 mask;
    f32 other;
    f32 sine;
    f32 cosine;
    s32 angle;

    mask = (arg0 & 0x40) ? 0x3F : 0x7F;
    angle = func_150ADA20() & mask;
    *arg2 = func_150489B0(angle);
    cosine = func_15048A40(angle);
    angle = func_150ADA20() & 0xFF;
    sine = func_150489B0(angle);
    other = func_15048A40(angle);
    *arg1 = cosine * other;
    *arg3 = cosine * sine;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_151700D8.s")
extern u16 D_800CC34A;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15170500 CURRENT (758) */
void func_15170500(s16 arg0, s16 arg1, s16 arg2, s32 arg3, s32 arg4, u8 arg5, s32 arg6) {
    f32 x;
    f32 y;
    f32 z;
    u8 angle;
    f32 factor;
    s32 vx;
    s32 vz;
    union { s32 bits; f32 value; } zero;
    s32 unused;
    s32 random;

    if (arg4 == 0) {
        arg3 = D_800CC34A;
    }
    random = func_151EF610() % 50;
    angle = arg3;
    x = func_150489B0(angle);
    z = -func_15048A40(angle);
    factor = func_150489B0((u8)random);
    x *= factor;
    z *= factor;
    zero.bits = 0;
    y = zero.value + zero.value;
    x += x;
    z += z;
    if (arg4 != 0) {
        vx = (s32) (x * 256.0f);
        vz = (s32) (z * 256.0f);
        func_1516D4E8((s32) arg0, (s32) arg1, (s32) arg2, 0x2A, 0, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 6, vx >> 8, vx & 0xFF, vz >> 8, vz & 0xFF, 0, 0, 0, 0, 0, 1, 0x200, 0x166, 0xFF, (s32) (y * 256.0f) - 0x32, 0, 0, (u8) (s32) arg5, arg6);
        return;
    }
    vx = (s32) (x * 256.0f);
    vz = (s32) (z * 256.0f);
    func_1516D99C((s32) arg0, (s32) arg1, (s32) arg2, 0x2A, 0, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 6, vx >> 8, vx & 0xFF, vz >> 8, vz & 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x200, 0x166, 0, 0, 0x14, 0, 0, 0xFF, 0xFF, (s32) (y * 256.0f) - 0x32, 0xC8, 9, 1, 0, 1, 0x32, 0x14, 0, 0, 0, (u8) (s32) arg5, arg6);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15170500 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_15170500.s")


#if 0 /* CONKER_DEFERRED_CANDIDATE func_151707E0 CURRENT (40) */
s32 func_151707E0(Game19A8B0Motion *arg0) {
    s32 unused;
    s32 value;
    s32 x;
    s32 z;
    s8 high;
    u8 low;

    value = arg0->alpha;
    if (arg0->active != 0) {
        if (value == 0) {
            arg0->active = (func_150ADA20() % 25U) + 0xC8;
        }
        if (value != 0xFE) {
            value += D_800BE9E4 << 6;
            if (value >= 0xFF) {
                value = 0xFE;
            }
            arg0->alpha = value;
        }
    } else if (value != 0) {
        value -= D_800BE9E4 * 0x10;
        if (value < 0) {
            value = 0;
        }
        arg0->alpha = value;
    }
    if (arg0->active == 0 && value == 0) {
        return 1;
    }
    func_1516F864(arg0);
    if (arg0->pad2E[1] != 0) {
        func_1516F8EC(arg0, (func_151EF610() % 32) + 0xE6);
        func_1516F91C(arg0, (func_151EF610() % 32) + 0xE6);
    } else {
        high = arg0->velocityXHigh;
        low = arg0->velocityXLow;
        x = (high << 8) + low;
        z = high;
        z *= 256;
        z += low;
        if (x * x + z * z >= 0x7D1) {
            func_1516F8EC(arg0, (func_151EF610(high, low) % 32) + 0xDC);
            func_1516F91C(arg0, (func_151EF610() % 32) + 0xDC);
        }
    }
    arg0->velocityY = 0;
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151707E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_151707E0.s")


#if 0 /* CONKER_DEFERRED_CANDIDATE func_151709B4 CURRENT (3972) */
void func_151709B4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, u8 arg5, s32 arg6) {
    f32 spF0;
    f32 spEC;
    f32 spE8;
    s32 temp_ft0;
    s32 temp_ft1;
    s32 var_s0;

    var_s0 = 0;
    if (arg3 > 0) {
        arg0 = (s16)arg0;
        arg1 = (s16)arg1;
        arg2 = (s16)arg2;
        do {
            func_15170034(0x40, &spF0, &spEC, &spE8);
            spF0 *= arg4;
            spEC *= 2.0f * arg4;
            spE8 *= arg4;
            temp_ft0 = (s32)spF0;
            temp_ft1 = (s32)spE8;
            func_1516D4E8((s16)arg0, (s16)arg1, (s16)arg2, 0x2F, 0, 0xFF, 0xFF, 0xFF, 0, 0xFF, 0, 0, 7, temp_ft0 >> 8, temp_ft0 & 0xFF, temp_ft1 >> 8, temp_ft1 & 0xFF, 0, 0, 0, 0, 0, 0, 0x200, 0x200, 0x28, (s32) spEC, 0, 0, (u8) (s32) arg5, arg6);
            var_s0 += 1;
        } while (var_s0 != arg3);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151709B4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_151709B4.s")
