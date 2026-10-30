#include "types.h"

/*
 * Reviewed source unit: src/game/game_A9260.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_call_connected_segments_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1507C22C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct GameA9260Anim {
    void (*callback)(f32);
    u16 flags;
    u8 pad6[2];
    f32 time;
    u8 padC[4];
    f32 speed;
    u8 pad14[4];
    f32 end;
    u8 pad1C[4];
    f32 start;
    u8 pad24[4];
    s32 id;
    u8 pad2C[0xE];
    s16 step;
    s16 countdown;
} GameA9260Anim;

typedef struct GameA9260Character {
    u8 pad0[0x76];
    u16 frame0;
    u16 frame2;
    u16 frame1;
    u8 pad7C[0x38];
    f32 animTime;
    u8 padB8[0x3C];
    s32 state;
    u8 padF8[0x14];
    s16 unk10C;
    u8 pad10E[0x2A];
    s8 unk138;
    u8 pad139[0x8B];
    s32 unk1C4;
    u8 pad1C8[0x34];
    u8 animFlags;
    u8 frameStep;
    u8 pad1FE[0x1E];
    s16 unk21C;
    u8 pad21E[0x10E];
} GameA9260Character;

f32 func_1506AD30(void *, f32, u8);
extern f32 D_800BE9A4;
extern s32 D_800BE9E4;
extern u8 D_800BEA0C;
extern u8 D_800C35EA[];
extern u8 D_800C365E[];
extern s8 D_800C3E78;
extern GameA9260Character *D_800D154C;
extern GameA9260Character D_800CC2D0[];

void func_1507BDB0(GameA9260Anim *arg0, f32 arg1, GameA9260Character *arg2, s32 arg3) {
    f32 time;
    s32 flags;
    u8 changed;
    f32 scaled;
    s32 id;
    f32 result;
    f32 limit;
    s32 step;

    if (arg0->id == 0) {
        return;
    }
    if (arg2 != NULL) {
        if (D_800C35EA[0] == 0) {
            if (D_800BE9A4 < 2.0f) {
                arg1 = D_800BE9A4 * arg1;
            } else {
                arg1 = arg1 + arg1;
            }
        } else {
            arg1 = D_800BE9A4;
        }
    }
    if (D_800BEA0C != 0) {
        arg1 = 0.0f;
    }
    limit = arg0->end;
    scaled = arg0->speed * arg1;
    if (limit < scaled) {
        time = limit;
        time += arg0->time;
    } else {
        time = scaled;
        time += arg0->time;
    }
    flags = arg0->flags & 0x8000;
    if (arg2 != NULL) {
        flags |= arg2->state & 0xE;
        arg2->animFlags &= 0xFFFB;
        D_800C3E78 = arg2 - D_800CC2D0;
        D_800D154C = arg2;
    }
    changed = 0;
    if (arg2 != NULL && (D_800C35EA[arg3] != 1 || D_800C365E[arg3] != 0)) {
        result = func_1506AD30(D_800D154C, time, 0);
        if (result != 0.0f) {
            time = result;
        }
    }
    if (arg0->speed >= 0.0f) {
        limit = arg0->end - 1.0f;
        if (limit <= time && arg0->time < limit && arg0->callback != NULL) {
            id = arg0->id;
            if (arg2 != NULL && (arg2->state & 8)) {
                arg2->unk10C = 0;
                arg2->unk1C4 = 0;
                arg0->speed = 0.0f;
            }
            if (D_800C35EA[0] == 0) {
                arg0->callback(time);
            }
            if (id != arg0->id) {
                time = arg0->time;
                changed = 1;
            }
        }
        if (arg2 != NULL && (step = arg2->frameStep) != 0 && arg0->end - 1.0f <= time) {
            arg2->frame0 += step << 8;
            arg2->frame1 = arg2->frame0;
            arg2->frame2 = arg2->frame0;
            arg0->time = arg0->start;
            if (arg2->state & 4) {
                arg2->unk21C = 0;
            }
        } else if (flags == 0 && (limit = arg0->end) <= time) {
            changed = 1;
            arg0->time = (time - limit) + arg0->start;
            if (arg2 != NULL) {
                arg2->animFlags |= 4;
            }
        } else if (flags != 0 && (limit = arg0->end - 1.0f) <= time) {
            if ((arg2 != NULL && (arg2->state & 0xA)) || (arg0->flags & 0x8000)) {
                arg0->time = limit;
            } else if (arg0->time < limit) {
                arg0->time = limit;
                if (arg2 != NULL && (arg2->state & 4)) {
                    arg2->unk21C = 0;
                }
            } else {
                arg0->time = arg0->start;
                if (arg2 != NULL) {
                    arg2->unk138 = 0;
                    arg2->animFlags |= 2;
                }
            }
            if (arg2 != NULL && (arg2->state & 8)) {
                arg2->unk10C = 0;
                arg2->unk1C4 = 0;
                arg0->speed = 0.0f;
            }
            if (arg0->time < 0.0f) {
                arg0->time = 0.0f;
            }
        } else {
            arg0->time = time;
        }
    } else {
        limit = arg0->start;
        if (time < limit) {
            arg0->time = (time - limit) + arg0->end;
        } else {
            arg0->time = time;
        }
    }
    if (arg0->countdown > 0) {
        arg0->countdown -= arg0->step * D_800BE9E4;
    }
    if (arg2 != NULL) {
        if (changed) {
            func_1506AD30(D_800D154C, arg0->time, 0);
        }
        arg2->animTime = arg0->time;
    }
}
s32 func_150229E4(void *);
extern u8 D_800C3638;
extern u8 D_800C3654;
extern u8 D_800D121C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1507C22C CURRENT (60) */
void func_1507C22C(s32 arg0) {
    u32 address;
    u8 *entry;
    s32 temp_a0;

    address = (u32) &D_800CC2D0;
    do {
        entry = (u8 *)address;
        if ((*(s32 *)(entry + 0) != 0) &&
            !(*(s32 *)(entry + 0x25C) & 0x200) &&
            ((arg0 == 0) || (entry[5] == 4)) &&
            ((D_800C3638 == 0) || (D_800C3654 != 0) ||
             (func_150229E4(entry) != 0))) {
            temp_a0 = *(s32 *)(entry + 0x2D0);
            if ((temp_a0 != 0) && (entry[0x2FA] != 0)) {
                func_1507BDB0((GameA9260Anim *)temp_a0, *(f32 *)(entry + 0x48),
                              (GameA9260Character *)entry, arg0);
            }
        }
        address += 0x32C;
    } while (address != (u32) &D_800D121C);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1507C22C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9260/func_1507C22C.s")
void func_1507C324(void *arg0, void *arg1) {
    f32 temp_fv0;
    void *temp_v0;
    void *temp_v1;

    temp_v0 = *(void **)((u8 *)arg0 + 0x2D0);
    temp_v1 = *(void **)((u8 *)arg1 + 0x2D0);
    if ((temp_v0 != 0) && (temp_v1 != 0)) {
        *(f32 *)((u8 *)temp_v0 + 8) = (f32) *(f32 *)((u8 *)temp_v1 + 8);
        temp_fv0 = *(f32 *)((u8 *)temp_v0 + 0x18) - 1.0f;
        if (temp_fv0 <= *(f32 *)((u8 *)temp_v0 + 8)) {
            *(f32 *)((u8 *)temp_v0 + 8) = temp_fv0;
        }
    }
}
