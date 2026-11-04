#include "types.h"

/*
 * Reviewed source unit: src/game/game_1B5370.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_display_transition_groups.md
 */

void func_100226F0(void *, s32);
extern s32 D_800DF7B4;

typedef struct Game1B5370Fade {
    u8 color[6];
    u8 start[3];
    u8 pad9[7];
    s32 type;
    f32 rate;
    u8 work[0xC];
} Game1B5370Fade;

extern Game1B5370Fade D_800DF700[];

s32 func_15187EC0(s32 arg0, f32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7) {
    if (D_800DF7B4 < 5) {
        D_800DF700[D_800DF7B4].type = arg0;
        D_800DF700[D_800DF7B4].rate = arg1;
        D_800DF700[D_800DF7B4].color[0] = D_800DF700[D_800DF7B4].start[0] = arg2;
        D_800DF700[D_800DF7B4].color[1] = D_800DF700[D_800DF7B4].start[1] = arg3;
        D_800DF700[D_800DF7B4].color[2] = D_800DF700[D_800DF7B4].start[2] = arg4;
        D_800DF700[D_800DF7B4].color[3] = arg5;
        D_800DF700[D_800DF7B4].color[4] = arg6;
        D_800DF700[D_800DF7B4].color[5] = arg7;
        func_100226F0(D_800DF700[D_800DF7B4].work, 0xC);
        D_800DF7B4++;
        return D_800DF7B4 - 1;
    }
    return -1;
}
void func_100226F0(void *arg0, s32 arg1);
extern s32 D_800DF7B4;

void func_15187F90(void) {
    func_100226F0(&D_800DF700, 0xB4);
    D_800DF7B4 = 0;
}
void func_15187FC0(s32 arg0, void *arg1) {
    void *temp_v0;

    if ((arg0 < D_800DF7B4) && (arg0 >= 0)) {
        temp_v0 = (u8 *)&D_800DF700 + (arg0 * 0x24);
        *(s32 *)((u8 *)arg1 + 0) = (s32) *(u8 *)((u8 *)temp_v0 + 6);
        *(s32 *)((u8 *)arg1 + 4) = (s32) *(u8 *)((u8 *)temp_v0 + 7);
        *(s32 *)((u8 *)arg1 + 8) = (s32) *(u8 *)((u8 *)temp_v0 + 8);
    }
}
extern f32 D_800DF70C[];

void func_15188010(s32 arg0, f32 *arg1) {
    if ((arg0 < D_800DF7B4) && (arg0 >= 0)) {
        *arg1 = *(f32 *)((u8 *)D_800DF70C + (arg0 * 0x24));
    }
}
void func_1518804C(s32 arg0, f32 arg1) {
    if ((arg0 < D_800DF7B4) && (arg0 >= 0)) {
        if (arg1 > 1.0f) {
            arg1 = 1.0f;
        } else if (arg1 < 0.0f) {
            arg1 = 0.0f;
        }
        *(f32 *)((u8 (*)[0x24])D_800DF70C)[arg0] = arg1;
    }
}
#define FADE ((Game1B5370FadeAnim *)D_800DF700)
f32 func_15047D60(f32);
s32 func_151EF610(void);
extern u8 D_800A7390[];
extern f32 D_800BE9A4;
extern s32 D_800BE9E4;

typedef union Game1B5370FadeWord {
    f32 f;
    s32 i;
    u32 u;
} Game1B5370FadeWord;

typedef struct Game1B5370FadeAnim {
    u8 color[6];
    u8 start[3];
    u8 pad9[3];
    f32 t;
    u32 type;
    f32 rate;
    s32 unk18;
    Game1B5370FadeWord a;
    Game1B5370FadeWord b;
} Game1B5370FadeAnim;

void func_151880C0(void) {
    s32 i;

    for (i = 0; i < D_800DF7B4; i++) {
        switch (FADE[i].type) {
        case 0:
            break;
        case 1:
            FADE[i].t = (func_15047D60(FADE[i].a.f) + 1.0f) * 0.5f;
            FADE[i].a.f += FADE[i].rate * D_800BE9A4;
            if (FADE[i].a.f >= 6.2831855f) {
                FADE[i].a.f -= 6.2831855f;
            }
            break;
        case 2:
            if (FADE[i].b.i == 0) {
                FADE[i].b.i = -8;
                FADE[i].t = 1.0f;
            } else if (FADE[i].b.i < 0) {
                FADE[i].b.i += D_800BE9E4;
                if (FADE[i].b.i >= 0) {
                    FADE[i].t = 0.0f;
                    if (++FADE[i].a.u >= 8) {
                        FADE[i].a.u = 0;
                    }
                    FADE[i].b.i = D_800A7390[FADE[i].a.u];
                }
            } else {
                FADE[i].b.i -= D_800BE9E4;
                if (FADE[i].b.i < 0) {
                    FADE[i].b.i = 0;
                }
            }
            break;
        case 3:
            switch (FADE[i].a.u) {
            case 0:
                FADE[i].t += FADE[i].rate * D_800BE9E4;
                if (FADE[i].b.f <= FADE[i].t) {
                    FADE[i].t = FADE[i].b.f;
                    if (FADE[i].b.f == 1.0f) {
                        FADE[i].b.f = !(func_151EF610() & 1) ? 0.0f : 0.5f;
                        FADE[i].a.u = 2;
                    } else {
                        FADE[i].a.u = 1;
                        FADE[i].b.i = func_151EF610() % 30 + 30;
                    }
                }
                break;
            case 1:
                FADE[i].b.i -= D_800BE9E4;
                if (FADE[i].b.i <= 0) {
                    FADE[i].a.u = (func_151EF610() % 2) * 2;
                    if (FADE[i].a.u == 0) {
                        FADE[i].b.f = 1.0f;
                    } else {
                        FADE[i].b.f = 0.0f;
                    }
                }
                break;
            case 2:
                FADE[i].t -= FADE[i].rate * D_800BE9E4;
                if (FADE[i].t <= FADE[i].b.f) {
                    FADE[i].t = FADE[i].b.f;
                    if (FADE[i].b.f == 0.0f) {
                        FADE[i].a.u = 3;
                        FADE[i].b.i = func_151EF610() % 30 + 30;
                    } else {
                        FADE[i].a.u = 1;
                        FADE[i].b.i = func_151EF610() % 30 + 30;
                    }
                }
                break;
            case 3:
                FADE[i].b.i -= D_800BE9E4;
                if (FADE[i].b.i <= 0) {
                    FADE[i].a.u = 0;
                    FADE[i].b.f = !(func_151EF610() & 1) ? 0.5f : 1.0f;
                }
                break;
            }
            break;
        }
        FADE[i].start[0] = (u32)((u32)FADE[i].color[0] + (FADE[i].color[3] - FADE[i].color[0]) * FADE[i].t);
        FADE[i].start[1] = (u32)((u32)FADE[i].color[1] + (FADE[i].color[4] - FADE[i].color[1]) * FADE[i].t);
        FADE[i].start[2] = (u32)((u32)FADE[i].color[2] + (FADE[i].color[5] - FADE[i].color[2]) * FADE[i].t);
    }
}
