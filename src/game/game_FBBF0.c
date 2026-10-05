#include "types.h"

/*
 * Reviewed source unit: src/game/game_FBBF0.c
 * Boundary evidence: docs/evidence/game_raw_pointer_singletons.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150CE740
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    u8 pad00[0x27]; u8 active27;
    u8 pad28[0x24]; u16 angle;
    u8 pad4E[0x36]; u8 active84;
    u8 pad85[0x9B]; u8 active120;
    u8 pad121[0x89]; s16 count; u8 active1AC;
} GameFBBF0State;
typedef struct {
    u8 pad00[4]; u8 kind;
    u8 pad05[0x23]; f32 vertical;
    u8 pad2C[0x10]; f32 speed;
    u8 pad40[4]; f32 desiredSpeed;
    u8 pad48[0x1D]; u8 active65;
    u8 pad66[0x10]; u16 facing, desiredAngle, angle;
    u8 pad7C[7]; u8 active83; u16 mode;
    u8 pad86[3]; u8 timer, active8A;
    u8 pad8B[0x39]; f32 tilt;
    u8 padC8[0x3C]; u8 active104;
    u8 pad105[0x1F]; u8 index, active125;
    u8 pad126[0x16]; u8 control;
    u8 pad13D[0xA8]; s8 animA, animB;
    u8 pad1E7[0x31]; s32 counter;
    u8 pad21C[7]; u8 state;
    u8 pad224[0xE]; u8 action;
    u8 pad233[0x29]; s32 flags;
    u8 pad260[0x84]; s32 turnA, turnB;
    u8 pad2EC[0x30]; GameFBBF0State *owner;
    u8 pad320[0xC];
} GameFBBF0Actor;
typedef struct { u8 pad00[0x37C]; f32 yaw; u8 pad380[0x620]; } GameFBBF0Camera;
typedef struct { u16 buttons; s8 x, y; } GameFBBF0Input;

void func_15052F9C(u8 *, f32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_1505327C(u8 *, f32, f32, s32, s32);
s32 func_1505A630(f32, f32, s32);

void func_1504C854(void *);               /* extern */
void func_15052590(void *);                        /* extern */
f32 func_1505A5CC(void *);                          /* extern */
void func_15063168(void *);                        /* extern */
u32 func_150ADA20(void);                                /* extern */
extern s8 D_8008FD8C;
extern u8 D_800A080F[];                             /* unknown layout; byte-addressed storage */
extern u8 D_800A0818[];                             /* unknown layout; byte-addressed storage */
extern f32 D_800A0820;
extern f32 D_800A0824;
extern f32 D_800A0828;
extern u8 D_800BE616;
extern u16 D_800BE648[];
extern u16 D_800BE710[];
extern u8 D_800C3E78;
extern s32 D_800CC268;
extern s32 D_800CC280;
extern GameFBBF0Input *D_800CC284;
extern s32 D_800CC288;
extern GameFBBF0Actor D_800CC2D0[];
extern GameFBBF0Camera *D_800DBFF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CE740 CURRENT (7973) */
void func_150CE740(GameFBBF0Actor *arg0) {
    u16 sp42;
    u16 sp40;
    f32 temp_ft4;
    f32 temp_fv0;
    s16 var_a0;
    s32 temp_t6;
    s32 temp_v0_2;
    s32 temp_v0_5;
    s32 temp_v1;
    s32 temp_v1_2;
    s8 var_v1;
    s32 temp_t9_3;
    u8 var_a1;
    u8 var_t0;
    GameFBBF0State *temp_t3;
    GameFBBF0State *temp_t3_2;
    GameFBBF0Camera *temp_t8;
    GameFBBF0State *temp_t9;
    GameFBBF0State *temp_t9_2;
    GameFBBF0State *temp_v0;
    GameFBBF0Actor *temp_v0_3;
    u8 *temp_v0_4;
    GameFBBF0State *temp_v0_6;

    var_t0 = 0;
    sp40 = arg0->angle;
    if (arg0->kind == 0x21) {
        var_t0 = 1;
    }
    temp_v1 = arg0->control;
    if ((temp_v1 != 0) || (D_800BE616 != 0)) {
        var_a1 = 0;
        if (D_800BE616 != 0) {
            temp_t9 = arg0->owner;
            if (temp_t9->active84 != 0) {
                func_1504C854(arg0);
            } else {
                D_800CC288 = (s32) D_800BE710[D_800C3E78];
            }
        } else {
            D_800CC288 = (s32) D_800BE648[temp_v1];
        }
        if ((D_800CC288 & 0x8000) && (arg0->active8A == 0) && (arg0->vertical == 0.0f)) {
            var_a1 = 1;
        }
        if ((D_800CC288 & 0x6000) && (arg0->vertical == 0.0f) && (((var_t0 != 0) && (arg0->timer != 0xFF)) || (arg0->timer == 0))) {
            var_a1 = 2;
        }
        if (var_a1 != 0) {
            if (var_t0 != 0) {
                var_a1 = (var_a1 + 4) & 0xFF;
            }
            if (D_800BE616 != 0) {
                var_a1 = (var_a1 + 2) & 0xFF;
            }
            arg0->timer = 0xB4U;
            temp_t6 = *(((u8 *) D_800A080F) + var_a1);
            arg0->counter = 0;
            arg0->action = temp_t6;
            if (((temp_t6 & 0xFF) == 0x22) && (arg0->turnA == 0)) {
                temp_v0 = arg0->owner;
                temp_v0->count = (s16) (temp_v0->count + 1);
            }
        }
        arg0->index = 0U;
        if ((arg0->timer == 0) && ((temp_v0_2 = D_800BE616, (temp_v0_2 == 0)) || (temp_t3 = arg0->owner, (temp_t3->active84 == 0)))) {
            if (temp_v0_2 != 0) {
                temp_t8 = &D_800DBFF0[D_800C3E78];
                D_800CC280 = (s32) (temp_t8->yaw * D_800A0820);
                sp42 = func_1505A630((f32) D_800CC284->x, (f32) D_800CC284->y, 0) + D_800CC280;
                arg0->desiredSpeed = func_1505A5CC(D_800CC284);
            } else {
                temp_v0_3 = &D_800CC2D0[arg0->index];
                arg0->desiredSpeed = (f32) (temp_v0_3->desiredSpeed * 1.75f);
                temp_t9_2 = temp_v0_3->owner;
                sp42 = temp_t9_2->angle;
            }
            if (arg0->state == 0xD) {
                arg0->desiredSpeed = 0.0f;
            }
            if (var_t0 != 0) {
                if (arg0->desiredSpeed < 5.0f) {
                    sp42 = func_150ADA20();
                    arg0->desiredSpeed = (f32) ((f32) (func_150ADA20() % 60U) + 20.0f);
                }
                temp_t9_3 = ((func_150ADA20() % 10000U) + sp42) - 0x1388;
                temp_ft4 = (arg0->desiredSpeed * 0.5f) + 22.0f;
                arg0->desiredAngle = temp_t9_3;
                arg0->desiredSpeed = temp_ft4;
                if (((((s32) (arg0->facing - temp_t9_3) >> 8) - 0x50) & 0xFF) < 0x60) {
                    arg0->counter = 0;
                    arg0->action = 0x10U;
                }
            } else if (arg0->desiredSpeed < 5.0f) {
                arg0->desiredSpeed = 0.0f;
                if (arg0->action != 5) {
                    arg0->desiredAngle = (u16) arg0->facing;
                }
            } else {
                arg0->desiredAngle = sp42;
                if (arg0->state == 1) {
                    var_v1 = 3;
                    if (arg0->speed < 35.0f) {
                        var_v1 = 4;
                    }
                    arg0->animB = var_v1;
                    arg0->animA = var_v1;
                    if (((((s32) (arg0->facing - arg0->desiredAngle) >> 8) - 0x50) & 0xFF) < 0x60) {
                        if (arg0->speed > 35.0f) {
                            arg0->action = 4U;
                        } else {
                            arg0->action = 5U;
                        }
                    } else {
                        arg0->action = 3U;
                    }
                    arg0->counter = 0;
                }
            }
        }
    }
    if ((D_800BE616 == 0) || ((s32) D_800C3E78 >= D_8008FD8C) || (temp_t3_2 = arg0->owner, (temp_t3_2->active120 == 0))) {
        func_15052590(arg0);
    }
    if ((D_800CC2D0[0].owner->active27 != 0) && ((arg0->action != *(((u8 *) D_800A0818) + var_t0)) || (arg0->active104 != 0))) {
        D_800CC2D0[0].owner->active27 = 0U;
        D_800CC2D0[0].timer = 0;
        D_800CC2D0[0].active83 = 0;
        D_800CC2D0[0].active125 = 0;
        arg0->action = 0x11U;
    }
    temp_v0_4 = var_t0 + ((u8 *) D_800A0818);
    if (D_800BE616 == 0) {
        if (arg0->action == temp_v0_4[0]) {
            func_15052F9C((u8 *) arg0, 156.0f, (s32) temp_v0_4[4], 4, 0, (s32) temp_v0_4[2], 0xFF, 0, 0, 0);
            goto block_68;
        }
        if ((D_800CC268 & 1) && (D_800CC2D0[arg0->index].active65 == 0) && (arg0->flags & 0x400)) {
            arg0->index = 0U;
            func_1505327C((u8 *) arg0, 50.0f, 3.0f, (s32) temp_v0_4[0], (s32) temp_v0_4[4]);
block_68:
            ;
        }
    }
    var_a0 = 0;
    if (((var_t0 != 0) && (arg0->speed > 5.0f)) || ((var_t0 == 0) && (arg0->mode == 0xA))) {
        var_a0 = arg0->facing - arg0->desiredAngle;
        if (var_a0 >= 0x3001) {
            var_a0 = 0x3000;
        }
        if (var_a0 < -0x3000) {
            var_a0 = -0x3000;
        }
        if ((var_t0 != 0) && (arg0->control == 0)) {
            var_a0 = (s16) (var_a0 >> 1);
        }
    }
    temp_fv0 = arg0->tilt;
    arg0->tilt = (f32) (temp_fv0 + ((((f32) var_a0 * D_800A0824) - temp_fv0) * D_800A0828));
    if (var_t0 != 0) {
        temp_v0_5 = arg0->turnA;
        temp_v1_2 = arg0->turnB;
        arg0->turnA = (s32) (temp_v0_5 + ((s32) ((s16) ((sp40 - arg0->angle) * 4) - (s16) temp_v0_5) / 8));
        arg0->turnB = (s32) (temp_v1_2 + ((s32) (-var_a0 - temp_v1_2) / 8));
    }
    if ((D_800BE616 != 0) && (D_800CC268 != 0)) {
        temp_v0_6 = arg0->owner;
        if ((temp_v0_6 != 0) && (temp_v0_6->active1AC != 0)) {
            func_15063168(arg0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CE740 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FBBF0/func_150CE740.s")
