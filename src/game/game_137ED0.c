#include "types.h"

/*
 * Reviewed source unit: src/game/game_137ED0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_subranges.md
 */

void func_1510AA20(s32 arg0) {
    func_15179008(0);
}
/* Call context: func_15114D24: unique active declaration in the allowed source */
void func_15114D24(s32, s32, s32, s16, s32, s32);
extern s32 D_800BE3E4;
extern s32 D_800BE9E4;

typedef struct Game137ED0Clock {
    u8 unk_0[0x8];
    f32 minuteAngle;
    u8 unk_C[0x3C - 0xC];
    s32 time;
    u8 unk_40[0x68 - 0x40];
    f32 unk_68;
    u8 unk_6C[0x7C - 0x6C];
    s32 chimes;
    s32 lastChimeSecond;
    s32 initialised;
    u8 unk_88[0xA8 - 0x88];
    f32 hourAngle;
    u8 unk_AC[0x108 - 0xAC];
    f32 unk_108;
} Game137ED0Clock;

void func_1510AA44(Game137ED0Clock *clock) {
    s32 lastMinute;
    s32 minute;
    s32 seconds;
    f32 angle;
    s32 quarter;

    lastMinute = clock->time / 3600 % 60;
    if ((clock->initialised == 0) && (D_800BE3E4 != 0)) {
        clock->initialised = 1;
        clock->time = (u32)(D_800BE3E4 * 180) % 43200U;
        clock->time *= 60;
        lastMinute = clock->time / 3600 % 60;
    }
    if (lastMinute < 0) {
        lastMinute += 60;
    }
    clock->time += D_800BE9E4;
    if (clock->time >= 0x278D00) {
        clock->time -= 0x278D00;
    }
    seconds = clock->time / 60;
    angle = (f32)(seconds / 300) * 2.5f;
    minute = seconds / 60;
    if (angle > 360.0f) {
        clock->time -= 0x278D00;
    }
    minute %= 60;
    if (minute < 0) {
        minute += 60;
    }
    if (lastMinute != minute) {
        quarter = minute / 15;
        if (lastMinute / 15 != quarter) {
            if (!(quarter & 3)) {
                clock->chimes = angle / 30.0f;
                if (clock->chimes == 0) {
                    clock->chimes = 12;
                }
            } else {
                clock->chimes = 1;
            }
            clock->lastChimeSecond = -1;
        }
    }
    if ((clock->chimes != 0) && (seconds != clock->lastChimeSecond)) {
        clock->lastChimeSecond = seconds;
        clock->chimes -= 1;
        func_15114D24((s32)clock, 0x4CC, 0x7FFF, 0xC8, 0x3E8, 0xC);
    }
    clock->unk_68 = 5.0f;
    clock->unk_108 = 5.0f;
    clock->minuteAngle = -((f32)minute * 6.0f);
    clock->hourAngle = -angle;
}

/* Call context: func_15114D24: unique active project prototype */
void func_15114D24(s32, s32, s32, s16, s32, s32);
f32 func_15047C00(f32);                             /* extern */
extern f32 D_800A26B0;
extern f32 D_800A26B4;
extern f32 D_800A26B8;
extern s32 D_800BE9E4;

void func_1510ADD8(void *arg0) {
    f32 temp_fv0;
    f32 temp_fv1;

    *(f32 *)((u8 *)arg0 + 0x80) = (f32) (*(f32 *)((u8 *)arg0 + 0x80) + ((D_800A26B0 * (f32) D_800BE9E4) / 60.0f));
    temp_fv0 = func_15047C00(*(f32 *)((u8 *)arg0 + 0x80));
    temp_fv1 = temp_fv0 * 10.0f;
    *(f32 *)((u8 *)arg0 + 0x60) = *(f32 *)((u8 *)arg0 + 0) - temp_fv1;
    *(f32 *)((u8 *)arg0 + 0) = temp_fv1;
    if (*(s32 *)((u8 *)arg0 + 0x7C) == 0) {
        if (*(f32 *)((u8 *)arg0 + 0x80) >= D_800A26B4) {
            *(s32 *)((u8 *)arg0 + 0x7C) = 1;
            func_15114D24((s32) arg0, 0x4CA, 0x2EE0, 0xC8, 0x3E8, 4);
        }
    } else {
        temp_fv1 = D_800A26B8;
        temp_fv0 = *(f32 *)((u8 *)arg0 + 0x80);
        if (temp_fv1 <= temp_fv0) {
            *(s32 *)((u8 *)arg0 + 0x7C) = 0;
            *(f32 *)((u8 *)arg0 + 0x80) = (f32) (temp_fv0 - temp_fv1);
            func_15114D24((s32) arg0, 0x4CB, 0x2EE0, 0xC8, 0x3E8, 4);
        }
    }
}
