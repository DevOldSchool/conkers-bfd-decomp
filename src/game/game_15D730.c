#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_15D730.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_text_view_descriptor_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15130A9C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game15D730ColorState {
    u8 pad0[0x24];
    u8 field24;
    u8 field25;
    u8 field26;
    u8 field27;
    u8 field28;
    u8 field29;
    u8 field2A;
    u8 field2B;
    u8 field2C;
    u8 pad2D[0x43];
    u8 mode70;
    u8 mode71;
} Game15D730ColorState;

void func_1513137C(s16 *, s16 *, s16 *, s16 *, Game15D730ColorState *);
void func_15131514(s16 *, s16 *, s16 *, s16 *, Game15D730ColorState *);

typedef struct Game15D730CopyBlock {
    s32 words[9];
} Game15D730CopyBlock;

void *func_10022EC0(void *, const void *, u32);

void *func_15130280(void *arg0, u8 arg1, Game15D730CopyBlock *arg2,
                   s32 arg3, u8 arg4, s32 arg5) {
    void *sp24;
    s32 var_a0;

    switch (arg1) {
    case 0:
        var_a0 = 0x2B;
        break;
    case 1:
        var_a0 = 0x52;
        break;
    case 2:
        var_a0 = 0x47;
        break;
    default:
        var_a0 = 0x2B;
        break;
    }
    sp24 = func_15167A68(var_a0, arg5, arg3 + 0xA8, 1, arg4, 1);
    if (sp24 == 0) {
        return 0;
    }
    func_10022EC0((u8 *)sp24 + 0x10, arg0, 0x70);
    if (arg2 != 0) {
        *(Game15D730CopyBlock *)((u8 *)sp24 + 0x80) = *arg2;
    } else {
        *(s8 *)((u8 *)sp24 + 0x9C) = 0;
    }
    return sp24;
}

void *func_15130374(s32 arg0, u8 arg1, s32 arg2, u8 arg3, s32 arg4) {
    return func_15130280((void *)arg0, arg1, 0, arg2, arg3, arg4);
}

void *func_15130374(s32, u8, s32, u8, s32);

void *func_151303BC(s32 arg0, u8 arg1, s32 arg2) {
    return func_15130374(arg0, arg1, arg2, 0xFF, 0);
}
typedef struct Game15D730Particle {
    u8 pad0[0x1A];
    s16 timer1A;
    s32 frame1C;
    s32 rate20;
    u8 pad24[0x7];
    u8 alpha2B;
    u8 pad2C;
    u8 anim2D;
    s16 fade2E;
    s16 fadeMul30;
    s16 scaleT32;
    f32 scaleK34;
    f32 scale38;
    f32 scale3C;
    Vec3f pos40;
    u8 pad4C[0xC];
    f32 vel58;
    f32 vel5C;
    f32 vel60;
    f32 grav64;
    s32 flags68;
    u8 pad6C[6];
    s8 update72;
    s8 kill73;
} Game15D730Particle;

typedef struct Game15D730AnimEntry {
    u8 frames;
    u8 pad1[0xB];
} Game15D730AnimEntry;

extern s32 D_800BE9E4;
extern f32 D_800BE9A4;
extern s32 (*D_80089760[])(Game15D730Particle *, Vec3f *);
extern void (*D_80089800[])(Game15D730Particle *);
extern Game15D730AnimEntry D_80090B64[];

void func_151303EC(Game15D730Particle *arg0) {
    s32 unused;
    Vec3f sp48;
    u8 dead;
    s32 i;
    s32 max;
    s32 rate;
    s32 frames;

    dead = 0;
    if (arg0->flags68 & 1) {
        arg0->timer1A -= D_800BE9E4;
        if (arg0->timer1A < 0) {
            dead = 1;
        }
    }
    if (arg0->flags68 & 2) {
        arg0->vel5C += arg0->grav64 * D_800BE9A4;
    }
    sp48 = arg0->pos40;
    if (arg0->flags68 & 4) {
        arg0->pos40.x += arg0->vel58 * D_800BE9A4;
        arg0->pos40.y += arg0->vel5C * D_800BE9A4;
        arg0->pos40.z += arg0->vel60 * D_800BE9A4;
    }
    if (arg0->flags68 & 0x200) {
        if (arg0->timer1A < arg0->fade2E) {
            i = arg0->timer1A * arg0->fadeMul30;
            i = (s16)i;
            if (i < arg0->alpha2B) {
                arg0->alpha2B = i;
            }
        }
    }
    if ((arg0->flags68 & 0x400) && (arg0->timer1A < arg0->scaleT32)) {
        if (arg0->flags68 & 0x800) {
            i = D_800BE9E4;
            if (arg0->flags68 & 0x80000) {
                for (; i != 0; i--) {
                    arg0->scale38 *= arg0->scaleK34;
                }
            } else if (arg0->flags68 & 0x100000) {
                for (; i != 0; i--) {
                    arg0->scale3C *= arg0->scaleK34;
                }
            } else {
                for (; i != 0; i--) {
                    arg0->scale38 *= arg0->scaleK34;
                    arg0->scale3C *= arg0->scaleK34;
                }
            }
        } else {
            if (!(arg0->flags68 & 0x80000)) {
                arg0->scale3C += arg0->scaleK34 * D_800BE9E4;
            }
            if (!(arg0->flags68 & 0x100000)) {
                arg0->scale38 += arg0->scaleK34 * D_800BE9E4;
            }
        }
    }
    if (!dead) {
        rate = arg0->rate20;
        if (rate != 0) {
            frames = D_80090B64[arg0->anim2D].frames;
            max = (frames << 16) - 1;
            arg0->frame1C += rate * D_800BE9E4;
            if (max < arg0->frame1C) {
                if (arg0->flags68 & 0x10) {
                    dead = 1;
                } else if (arg0->flags68 & 8) {
                    arg0->frame1C = max - arg0->frame1C % max;
                    arg0->rate20 = -rate;
                } else {
                    do {
                        arg0->frame1C -= max;
                    } while (max < arg0->frame1C);
                }
            } else if (arg0->frame1C < 0) {
                if (arg0->flags68 & 0x20) {
                    dead = 1;
                } else if (arg0->flags68 & 8) {
                    arg0->frame1C = -arg0->frame1C % max;
                    arg0->rate20 = -rate;
                } else {
                    do {
                        arg0->frame1C += max;
                    } while (arg0->frame1C < 0);
                }
            }
        }
    }
    if (arg0->update72 != -1 && !dead) {
        if (D_80089760[arg0->update72](arg0, &sp48) == 0) {
            dead = 1;
        }
    }
    if (dead) {
        if (arg0->kill73 != -1) {
            D_80089800[arg0->kill73](arg0);
        }
        func_1516972C(arg0);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_15D730/func_15130A9C.s")
void func_1513137C(s16 *arg0, s16 *arg1, s16 *arg2, s16 *arg3, Game15D730ColorState *arg4) {
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;

    switch (arg4->mode70) {
    case 1:
        *arg2 = 0;
        temp_v0 = *arg2;
        *arg1 = temp_v0;
        *arg0 = temp_v0;
        *arg3 = (s16) ((s32) (arg4->field27 * arg4->field2B) >> 8);
        return;
    case 2:
        *arg0 = (s16) arg4->field24;
        *arg1 = (s16) arg4->field25;
        *arg2 = (s16) arg4->field26;
        *arg3 = (s16) ((s32) (arg4->field27 * arg4->field2B) >> 8);
        return;
    case 3:
        *arg0 = (s16) arg4->field28;
        *arg1 = (s16) arg4->field29;
        *arg2 = (s16) arg4->field2A;
        *arg3 = (s16) ((s32) (arg4->field27 * arg4->field2B) >> 8);
        return;
    case 4:
    case 6:
        *arg3 = 0;
        temp_v0_2 = *arg3;
        *arg2 = temp_v0_2;
        *arg1 = temp_v0_2;
        *arg0 = temp_v0_2;
        return;
    case 5:
        *arg2 = 0;
        temp_v0_3 = *arg2;
        *arg1 = temp_v0_3;
        *arg0 = temp_v0_3;
        *arg3 = (s16) arg4->field2B;
        return;
    case 7:
        *arg0 = (s16) arg4->field24;
        *arg1 = (s16) arg4->field25;
        *arg2 = (s16) arg4->field26;
        *arg3 = (s16) arg4->field2B;
        return;
    case 8:
        *arg0 = (s16) arg4->field24;
        *arg1 = (s16) arg4->field25;
        *arg2 = (s16) arg4->field26;
        *arg3 = 0;
        return;
    default:
        *arg0 = (s16) ((s32) (arg4->field24 * arg4->field2C) >> 8);
        *arg1 = (s16) ((s32) (arg4->field25 * arg4->field2C) >> 8);
        *arg2 = (s16) ((s32) (arg4->field26 * arg4->field2C) >> 8);
        *arg3 = 0;
        return;
    }
}
void func_15131514(s16 *arg0, s16 *arg1, s16 *arg2, s16 *arg3, Game15D730ColorState *arg4) {
    s16 temp_v0;
    s16 temp_v0_3;
    u8 temp_v0_2;
    u8 temp_v0_4;
    u8 temp_v0_5;

    switch (arg4->mode71) {
    case 1:
    case 5:
        *arg2 = 0;
        temp_v0 = *arg2;
        *arg1 = temp_v0;
        *arg0 = temp_v0;
        *arg3 = 0;
        return;
    case 2:
        temp_v0_2 = arg4->field2C;
        *arg2 = (s16) temp_v0_2;
        *arg1 = (s16) temp_v0_2;
        *arg0 = (s16) temp_v0_2;
        *arg3 = 0;
        return;
    case 8:
        *arg2 = 0;
        temp_v0_3 = *arg2;
        *arg1 = temp_v0_3;
        *arg0 = temp_v0_3;
        *arg3 = (s16) arg4->field2B;
        return;
    case 3:
        *arg0 = (s16) arg4->field24;
        *arg1 = (s16) arg4->field25;
        *arg2 = (s16) arg4->field26;
        *arg3 = 0;
        return;
    case 4:
    case 6:
        *arg0 = (s16) arg4->field28;
        *arg1 = (s16) arg4->field29;
        *arg2 = (s16) arg4->field2A;
        *arg3 = (s16) arg4->field2B;
        return;
    case 7:
        temp_v0_4 = arg4->field2C;
        *arg2 = (s16) temp_v0_4;
        *arg1 = (s16) temp_v0_4;
        *arg0 = (s16) temp_v0_4;
        *arg3 = (s16) arg4->field2B;
        return;
    case 9:
        *arg0 = (s16) arg4->field24;
        *arg1 = (s16) arg4->field25;
        *arg2 = (s16) arg4->field26;
        *arg3 = (s16) arg4->field2B;
        return;
    default:
        temp_v0_5 = arg4->field2C;
        *arg2 = (s16) temp_v0_5;
        *arg1 = (s16) temp_v0_5;
        *arg0 = (s16) temp_v0_5;
        *arg3 = (s16) ((s32) (arg4->field27 * arg4->field2B) >> 8);
        return;
    }
}
void func_1513164C(s16 *arg0, s16 *arg1, s16 *arg2, s16 *arg3,
                   s16 *arg4, s16 *arg5, s16 *arg6, s16 *arg7,
                   Game15D730ColorState *arg8) {
    func_15131514(arg4, arg5, arg6, arg7, arg8);
    func_1513137C(arg0, arg1, arg2, arg3, arg8);
}
void func_151318E8(void *, f32);

s32 func_151316AC(u8 *arg0, s32 arg1) {
    func_151318E8(arg0 + 0x58, *(f32 *)((u8 *)arg0 + 0xA8));
    return 1;
}
void func_15131918(void *, f32);

s32 func_151316DC(u8 *arg0, s32 arg1) {
    func_15131918(arg0 + 0x58, *(f32 *)((u8 *)arg0 + 0xA8));
    return 1;
}
void func_15131958(void *, f32);

s32 func_1513170C(u8 *arg0, s32 arg1) {
    func_15131958(arg0 + 0x58, *(f32 *)((u8 *)arg0 + 0xA8));
    return 1;
}
void func_1513173C(void *arg0) {
    func_15169804(arg0);
}
void func_1513175C(void *arg0) {
    func_15169824(arg0);
}
extern void (*D_80089814[])(void);

void func_1513177C(void *arg0) {
    u8 var_v0;

    if (*(s32 *)((u8 *)arg0 + 0x68) & 0x4000) {
        var_v0 = *(u8 *)((u8 *)arg0 + 0x75);
    } else {
        var_v0 = 0;
    }
    D_80089814[var_v0]();
}
extern void (*D_80089844[])(void);

void func_151317C8(void *arg0) {
    u8 var_v0;

    if (*(s32 *)((u8 *)arg0 + 0x68) & 0x4000) {
        var_v0 = *(u8 *)((u8 *)arg0 + 0x75);
    } else {
        var_v0 = 0;
    }
    D_80089844[var_v0]();
}
s32 func_15131814(s32 arg0, s32 arg1) {
    return 0;
}
/* Call context: func_151423D8: unique active project prototype */
extern s32 D_800BE9E4;

void func_15131828(void *arg0, void *arg1, void *arg2, void *arg3) {
    *(f32 *)((u8 *)arg0 + 0x4C) = *(f32 *)((u8 *)arg1 + 0) * func_151423D8(*(u8 *)((u8 *)arg2 + 0) - 0x40);
    *(f32 *)((u8 *)arg0 + 0x54) = *(f32 *)((u8 *)arg1 + 4) * func_151423D8(*(u8 *)((u8 *)arg2 + 1) - 0x40);
    *(u8 *)((u8 *)arg2 + 0) += *(u8 *)((u8 *)arg3 + 0) * D_800BE9E4;
    *(u8 *)((u8 *)arg2 + 1) += *(u8 *)((u8 *)arg3 + 1) * D_800BE9E4;
}
extern s32 D_800BE9E4;

void func_151318E8(void *arg0, f32 arg1) {
    s32 var_v0;

    var_v0 = D_800BE9E4;
    if (var_v0 > 0) {
        do {
            var_v0 -= 1;
            *(f32 *)((u8 *)arg0 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) * arg1);
        } while (var_v0 > 0);
    }
}
void func_15131918(void *arg0, f32 arg1) {
    s32 var_v0;

    var_v0 = D_800BE9E4;
    if (var_v0 > 0) {
        do {
            var_v0 -= 1;
            *(f32 *)((u8 *)arg0 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) * arg1);
            *(f32 *)((u8 *)arg0 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) * arg1);
        } while (var_v0 > 0);
    }
}
void func_15131958(void *arg0, f32 arg1) {
    s32 var_v0;

    var_v0 = D_800BE9E4;
    if (var_v0 > 0) {
        do {
            var_v0 -= 1;
            *(f32 *)((u8 *)arg0 + 0) = (f32) (*(f32 *)((u8 *)arg0 + 0) * arg1);
            *(f32 *)((u8 *)arg0 + 4) = (f32) (*(f32 *)((u8 *)arg0 + 4) * arg1);
            *(f32 *)((u8 *)arg0 + 8) = (f32) (*(f32 *)((u8 *)arg0 + 8) * arg1);
        } while (var_v0 > 0);
    }
}
s32 func_151319C4(void *arg0, s32 arg1, void *arg2);

void func_151319A4(void *arg0, s32 arg1) {
    func_151319C4(arg0, arg1, (u8 *)arg0 + 0xA8);
}
s32 func_1514672C(f32 *);
s32 func_15046C80(f32 *, u16, f32, void *);
extern s32 (*D_80089874[])();
extern f32 D_800A3844;

s32 func_151319C4(void *arg0, s32 arg1, void *arg2) {
    u8 result;
    s8 index;

    result = 1;
    if ((*(u8 *)arg2 & 1) &&
        ((index = *(s8 *)((u8 *)arg2 + 1)) != -1) &&
        (D_80089874[index] != 0) &&
        (*(f32 *)(((u8 *)arg0) + 0x44) < *(f32 *)(arg1 + 4))) {
        f32 position[3];
        position[0] = *(f32 *)(((u8 *)arg0) + 0x40);
        position[1] = *(f32 *)(arg1 + 4);
        position[2] = *(f32 *)((u8 *)arg0 + 0x48);
        if (func_1514672C(position) == 0) {
            return 0;
        }
        if (func_15046C80(position, 0,
                          *(f32 *)((u8 *)arg0 + 0x44) -
                              (*(f32 *)((u8 *)arg0 + 0x3C) * D_800A3844),
                          (u8 *)arg0 + 0x80) != 0) {
            f32 output[3];
            output[0] = position[0];
            output[1] = *(f32 *)((u8 *)arg0 + 0x80);
            output[2] = position[2];
            result = D_80089874[*(s8 *)((u8 *)arg2 + 1)](
                arg0, arg1, output, arg2);
        }
    }
    return result;
}
/* Call context: func_15131958: unique active project prototype */
/* Call context: func_151319C4: unique active project prototype */

void func_15131AFC(u8 *arg0, s32 arg1) {
    func_15131958(arg0 + 0x58, *(f32 *)((u8 *)arg0 + 0xA8));
    func_151319C4(arg0, arg1, arg0 + 0xB0);
}
/* Call context: func_15131918: unique active project prototype */
/* Call context: func_151319C4: unique active project prototype */

void func_15131B3C(u8 *arg0, s32 arg1) {
    func_15131918(arg0 + 0x58, *(f32 *)((u8 *)arg0 + 0xA8));
    func_151319C4(arg0, arg1, arg0 + 0xB0);
}
extern f32 D_800A3848;
extern f32 D_800A384C;
f32 fabsf(f32);
#pragma intrinsic(fabsf)

s32 func_15131B7C(void *arg0, s32 arg1, void *arg2, void *arg3) {
    f32 temp_fv0;

    *(f32 *)((u8 *)arg0 + 0x44) = (f32) ((*(f32 *)((u8 *)arg0 + 0x3C) * D_800A3848) + *(f32 *)((u8 *)arg2 + 4));
    *(f32 *)((u8 *)arg0 + 0x58) *= *(f32 *)((u8 *)arg3 + 4);
    *(f32 *)((u8 *)arg0 + 0x5C) *= -*(f32 *)((u8 *)arg3 + 4);
    temp_fv0 = fabsf(*(f32 *)((u8 *)arg0 + 0x5C));
    *(f32 *)((u8 *)arg0 + 0x60) *= *(f32 *)((u8 *)arg3 + 4);
    if (temp_fv0 < D_800A384C) {
        *(f32 *)((u8 *)arg0 + 0x58) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x5C) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x60) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x64) = 0.0f;
        *(u8 *)((u8 *)arg3 + 0) = (u8) (*(u8 *)((u8 *)arg3 + 0) & 0xFFFE);
        *(s32 *)((u8 *)arg0 + 0x68) = (s32) (*(s32 *)((u8 *)arg0 + 0x68) & ~6);
    }
    return 1;
}
typedef void (*Game15D730Callback)(void *, s32, u8);

extern Game15D730Callback D_80089878[];

void func_15131C2C(void *arg0, s32 arg1, u8 arg2) {
    Game15D730Callback temp_v0;

    if (*(s32 *)((u8 *)arg0 + 0x68) & 0x4000) {
        temp_v0 = D_80089878[*(u8 *)((u8 *)arg0 + 0x75)];
        if (temp_v0 != 0) {
            temp_v0(arg0, arg1, arg2);
        }
    }
}
/* Call context: func_151423D8: unique active project prototype */

void func_15131C84(s16 *arg0, s16 *arg1, s32 arg2, s32 *arg3, s32 *arg4, s32 *arg5) {
    ((u8 *)arg0)[0] += ((s8 *)arg1)[0] * D_800BE9E4;
    ((u8 *)arg0)[1] += ((s8 *)arg1)[1] * D_800BE9E4;
    *(f32 *)arg4 = *(f32 *)&arg2 + ((f32 *)arg3)[0] * func_151423D8(((u8 *)arg0)[0] - 0x40);
    *(f32 *)arg5 = *(f32 *)&arg2 + ((f32 *)arg3)[1] * func_151423D8(((u8 *)arg0)[1] - 0x40);
}
typedef struct {
    s32 field_0;
    s32 field_4;
    s32 field_8;
} Game15D730Args;

extern Game15D730Args D_800A37F0;
void func_15169260(Game15D730Args *, s32, void *, u8);

void func_15131D4C(void *arg0, u8 arg1) {
    Game15D730Args sp1C;

    sp1C = D_800A37F0;
    func_15169260(&sp1C, 3, arg0, arg1);
}
typedef struct {
    u8 pad_0[0x38];
    s32 field_38;
    s32 field_3C;
    u8 pad_40[0x68];
    s16 field_A8;
    s16 field_AA;
    s32 field_AC;
    s32 field_B0;
} Game15D730State;

void func_15131C84(s16 *, s16 *, s32, s32 *, s32 *, s32 *);

s32 func_15131D9C(Game15D730State *arg0, s32 arg1) {
    func_15131C84(&arg0->field_A8, &arg0->field_AA, arg0->field_AC, &arg0->field_B0,
                  &arg0->field_38, &arg0->field_3C);
    return 1;
}
extern f32 D_800BE9A4;

f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
s32 func_15131DEC(void *arg0, s32 arg1) {
    f32 temp_fa0;
    f32 temp_fv1;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 0xA8);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0xB0) * sqrtf(temp_fv1);
    *(f32 *)((u8 *)arg0 + 0x3C) = temp_fa0;
    *(f32 *)((u8 *)arg0 + 0x38) = temp_fa0;
    *(s8 *)((u8 *)arg0 + 0x2B) = (s8) (u32) (*(f32 *)((u8 *)arg0 + 0xB4) - (*(f32 *)((u8 *)arg0 + 0xB8) * temp_fv1 * temp_fv1));
    *(f32 *)((u8 *)arg0 + 0xA8) = (f32) (temp_fv1 + D_800BE9A4);
    if (*(f32 *)((u8 *)arg0 + 0xAC) < *(f32 *)((u8 *)arg0 + 0xA8)) {
        return 0;
    }
    return 1;
}
typedef struct Game131EE4Spawn {
    s32 flags;
    s32 resource;
    s16 renderFlags;
    s16 lifetime;
    s32 frame;
    s32 frameStep;
    u8 primaryR, primaryG, primaryB, primaryA;
    u8 secondaryR, secondaryG, secondaryB, secondaryA;
    u8 intensity;
    u8 effect;
    s16 fadeStart;
    s16 fadeRate;
    s16 resizeStart;
    f32 resizeRate;
    f32 width;
    f32 height;
    Game15D730Args position;
    Game15D730Args offset;
    Game15D730Args velocity;
    f32 acceleration;
    s32 behavior;
    s32 attachment;
    u8 colorMode;
    u8 alternateColorMode;
    s8 update;
    s8 death;
    s8 render;
    u8 callback;
    u8 visibility;
    s16 minimumSize;
    s16 reserved6A;
    f32 maximumSize;
} Game131EE4Spawn;

typedef struct Game131EE4Fade {
    f32 elapsed;
    f32 duration;
    f32 scale;
    f32 brightness;
    f32 decay;
} Game131EE4Fade;

f32 func_150ADA68(void);
extern f32 D_800A3850;
extern Game15D730Args D_800A5480;

void *func_15131EE4(void *arg0, f32 arg1, u8 arg2, s32 arg3) {
    Game131EE4Spawn spawn;
    Game131EE4Fade fade;
    void *result;
    s32 secondFlag;
    s32 firstFlag;

    fade.elapsed = 0.0f;
    fade.scale = D_800A3850 * arg1;
    fade.duration = 2.0f * func_150ADA68() + 5.0f;
    fade.brightness = func_150ADA68() * 15.0f + 240.0f;
    fade.decay = fade.brightness / (fade.duration * fade.duration);
    spawn.secondaryA = (u8)(u32)fade.brightness;
    spawn.effect = 0x69;
    spawn.renderFlags = 0x4417;
    spawn.flags = 0x200004;
    spawn.resource = 1;
    spawn.frame = 0;
    spawn.frameStep = 0;
    spawn.secondaryR = 0xFF;
    spawn.secondaryG = 0xFF;
    spawn.secondaryB = 0xFF;
    spawn.primaryA = 0xFF;
    spawn.primaryR = 0xFF;
    spawn.primaryG = 0xFF;
    spawn.primaryB = 0xFF;
    spawn.intensity = 0xFF;
    spawn.position = *(Game15D730Args *)arg0;
    spawn.offset = D_800A5480;
    spawn.fadeStart = 1;
    spawn.fadeRate = 0xFF;
    spawn.resizeStart = 1;
    spawn.resizeRate = 1.0f;
    firstFlag = (func_150ADA20() & 1) ? 0x40 : 0;
    if (func_150ADA20() & 1) {
        secondFlag = 0x80;
    } else {
        secondFlag = 0;
    }
    spawn.behavior = secondFlag | 0x4C000 | firstFlag;
    spawn.colorMode = 6;
    spawn.alternateColorMode = 6;
    spawn.update = 0x27;
    spawn.death = -1;
    spawn.render = -1;
    spawn.callback = 0;
    spawn.attachment = 0;
    spawn.visibility = 0xFF;
    spawn.velocity = D_800A5480;
    spawn.lifetime = 300;
    spawn.width = 0.0f;
    spawn.height = 0.0f;
    spawn.acceleration = 0.0f;
    result = func_15130280(&spawn, 1, 0, sizeof(fade), arg2, arg3);
    if (result != 0) {
        func_10022EC0((u8 *)result + 0xA8, &fade, sizeof(fade));
    }
    return result;
}
