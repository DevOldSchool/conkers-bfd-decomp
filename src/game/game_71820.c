#include "types.h"

/*
 * Reviewed source unit: src/game/game_71820.c
 * Boundary evidence: docs/evidence/game_raw_core_state_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15044380
 * - func_1504452C
 * - func_15044660
 * - func_15044B78
 * - func_15044ED0
 * - func_150450CC
 * - func_15045880
 * - func_15045AE4
 * - func_15045D48
 * - func_15045F8C
 * - func_150461D0
 * - func_15046460
 * - func_150466F8
 * - func_1504697C
 * - func_1504715C
 * - func_150472C0
 * - func_15047390
 * - func_15047700
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800CBD9C;

typedef struct Game71820Node {
    struct Game71820Node *next;
    s16 field4;
    s16 field6;
    s16 field8;
    s16 fieldA;
    u8 fieldC;
    u8 fieldD;
    u8 fieldE;
    u8 padF;
} Game71820Node;

extern Game71820Node *D_800CBE00;
extern s32 D_800BE9E4;
extern s32 (*D_80085E80[])(Game71820Node *);
extern void (*D_80085E8C[])(void);
void *func_10003C40(s32, s32, s32, s32);
void func_100043B4(void *, s32);
f32 func_15048A40(s32);
f32 func_150489B0(u8, void *);
f32 fabsf(f32);
#pragma intrinsic(fabsf)

typedef struct Game71820Bounds {
    u8 pad0[0x114];
    s16 vertical_offset;
    s16 horizontal_extent;
    s16 depth_extent;
} Game71820Bounds;

typedef struct Game71820Global {
    u8 pad0[0x14];
    f32 x;
    f32 y;
    f32 z;
    u8 pad20[0xD8];
    u32 flagsF8;
    u8 padFC[0x179];
    u8 status275;
    u8 pad276[0xA6];
    Game71820Bounds *bounds;
} Game71820Global;

typedef struct Game71820Volume {
    u8 pad0[6];
    s16 x;
    s16 y;
    s16 z;
    u8 padC[4];
    s16 depth;
    s16 width;
    s16 height;
    u8 type;
    u8 pad17;
} Game71820Volume;

extern u8 D_800CC2D0[];

void func_15044370(void) {
    D_800CBD9C = 0;
}
extern u8 D_80089120;
extern u8 D_80089123;
extern u8 D_800CBDD3;
extern f32 D_800CBDF4;
extern f32 D_800CBDF8;
extern u8 D_800DBE62;
void func_1510F800(s32);
void func_15044660(Game71820Global *, f32, f32, f32);
s32 func_150AB1F0(f32, f32, f32, Game71820Global *, s32);
void func_150AC3E4(f32, f32, f32, Game71820Global *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15044380 CURRENT (120) */
s32 func_15044380(f32 arg0, f32 arg1, f32 arg2, Game71820Global *arg3, s32 arg4, s32 arg5) {
    s32 pad[2];
    s32 saved_mode;
    s32 index;
    s32 total;
    u8 *active;

    D_800CBDF4 = -32768.0f;
    D_800CBDF8 = -32768.0f;
    total = 0;
    arg3->status275 = 0;
    func_15044660(arg3, arg0, arg1, arg2);
    active = &D_80089123;
    index = 3;
    saved_mode = D_800CBDD3;
    do {
        if (*active == 1 && (index != 3 || !(arg3->flagsF8 & 0x200))) {
            func_1510F800(index);
            if (D_800DBE62 != 0) {
                total += func_150AB1F0(arg0, arg1, arg2, arg3, arg4);
            }
        }
        index--;
        active = (u8 *)((s32)active - 1);
    } while (index >= 0);
    active = &D_80089120;
    index = 0;
    if (arg5 != 0) {
        do {
            if (*active == 1) {
                func_1510F800(index);
                if (D_800DBE62 != 0) {
                    func_150AC3E4(arg0, arg1, arg2, arg3, 0);
                }
            }
            index++;
            active = (u8 *)((s32)active + 1);
        } while (index != 3);
    }
    func_1510F800(0);
    D_800CBDD3 = saved_mode;
    return total;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15044380 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15044380.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1504452C CURRENT (6172) */
void func_1504452C(s32 *arg0, void *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7) {
    f32 temp_ft1;
    f32 temp_ft1_2;
    f32 temp_ft3;
    f32 temp_ft3_2;
    f32 var_fa0;
    s16 var_ft4;
    s32 *var_v1;
    u8 *temp_a3;
    u8 *var_a3;
    u8 *var_v0;

    var_v1 = arg0;
    var_a3 = arg1;
    {
        s32 var_a2 = 0xC;
    var_v0 = (void *)(*var_v1 + arg7);
    var_ft4 = *(s16 *)((u8 *)var_v0 + 4);
    var_fa0 = (f32) *(s16 *)((u8 *)var_v0 + 0);
    if (0xC != 0x24) {
        do {
            var_a2 += 0xC;
            var_v1 += 4;
            temp_ft1 = var_fa0 - arg4;
            var_a3 += 0xC;
            temp_ft3 = (f32) var_ft4 - arg6;
            *(f32 *)((u8 *)var_a3 + -8) = (f32) ((f32) *(s16 *)((u8 *)var_v0 + 2) - arg5);
            *(f32 *)((u8 *)var_a3 + -0xC) = (f32) ((temp_ft1 * arg3) + (temp_ft3 * arg2));
            *(f32 *)((u8 *)var_a3 + -4) = (f32) ((temp_ft3 * arg3) - (temp_ft1 * arg2));
            var_v0 = (void *)(*var_v1 + arg7);
            var_ft4 = *(s16 *)((u8 *)var_v0 + 4);
            var_fa0 = (f32) *(s16 *)((u8 *)var_v0 + 0);
        } while (var_a2 != 0x24);
    }
    temp_a3 = (void *)(var_a3 + 0xC);
    temp_ft1_2 = var_fa0 - arg4;
    temp_ft3_2 = (f32) var_ft4 - arg6;
    *(f32 *)((u8 *)temp_a3 + -0xC) = (f32) ((temp_ft1_2 * arg3) + (temp_ft3_2 * arg2));
    *(f32 *)((u8 *)temp_a3 + -4) = (f32) ((temp_ft3_2 * arg3) - (temp_ft1_2 * arg2));
    *(f32 *)((u8 *)temp_a3 + -8) = (f32) ((f32) *(s16 *)((u8 *)var_v0 + 2) - arg5);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1504452C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_1504452C.s")
void func_15044658(void) {

}
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15044660.s")
void *func_15044964(s32, s32, s32, void *, s32, s32, s32, s32);

void *func_150448D0(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    void *temp_v0;

    temp_v0 = func_15044964(0x20, 1, arg0, arg1, arg2, 0, 0, 0);
    if (temp_v0 == 0) {
        return 0;
    }
    *(s16 *)((u8 *)temp_v0 + 0x10) = (s16)arg3;
    *(s16 *)((u8 *)temp_v0 + 0x12) = (s16)arg4;
    *(s16 *)((u8 *)temp_v0 + 0x14) = (s16)arg5;
    *(s8 *)((u8 *)temp_v0 + 0x16) = (s8)arg6;
    *(s32 *)((u8 *)temp_v0 + 0x18) = arg7;
    *(s32 *)((u8 *)temp_v0 + 0x1C) = arg8;
    return temp_v0;
}
void *func_15044964(s32 arg0, s32 arg1, s32 arg2, void *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    Game71820Node *node;
    Game71820Node *head;
    Game71820Node *current;
    Game71820Node *next;

    node = func_10003C40(arg0, 1, 0, 0);
    if (node == 0) {
        return 0;
    }
    node->next = 0;
    node->field4 = arg2;
    node->fieldC = arg1;
    node->fieldD = arg4;
    node->fieldE = (s32)arg3;
    node->field6 = arg5;
    node->field8 = arg6;
    node->fieldA = arg7;
    head = D_800CBE00;
    if (head == 0) {
        D_800CBE00 = node;
    } else {
        current = head;
        next = current->next;
        while (next != 0) {
            current = next;
            next = next->next;
        }
        current->next = node;
    }
    return node;
}
void func_15044A28(void) {
    Game71820Node *current;
    Game71820Node *previous;
    Game71820Node *next;
    s32 timer;
    s32 work;
    s32 delay;

    current = D_800CBE00;
    previous = 0;
    while (current != 0) {
        delay = current->fieldE;
        work = current->fieldC;
        next = current->next;
        if (delay == 0) {
            if (D_80085E80[work](current) != 0) {
                D_80085E8C[current->fieldD]();
            }
        } else {
            work = delay - D_800BE9E4;
            if (work < 0) {
                work = 0;
            }
            current->fieldE = work;
        }
        timer = current->field4;
        if (timer != -1) {
            timer -= D_800BE9E4;
            if (timer <= 0) {
                if (previous == 0) {
                    D_800CBE00 = current->next;
                } else {
                    previous->next = current->next;
                }
                func_100043B4(current, 2);
            } else {
                current->field4 = timer;
                previous = current;
            }
        } else {
            previous = current;
        }
        current = next;
    }
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15044B78 CURRENT (4435) */
s32 func_15044B78(Game71820Volume *arg0) {
    Game71820Global *global;
    f32 delta_x;
    f32 adjusted_y;
    f32 delta_z;
    f32 angle_sin;
    f32 angle_cos;
    f32 rotated_x;
    f32 rotated_z;
    s32 vertical_offset;
    s32 horizontal_extent;
    s32 depth_extent;
    s32 result;

    global = (Game71820Global *)D_800CC2D0;
    horizontal_extent = global->bounds->horizontal_extent;
    vertical_offset = global->bounds->vertical_offset >> 1;
    depth_extent = global->bounds->depth_extent;
    delta_x = global->x - arg0->x;
    adjusted_y = (global->y - arg0->y) + vertical_offset;
    delta_z = global->z - arg0->z;
    angle_sin = func_15048A40(arg0->type);
    angle_cos = func_150489B0(arg0->type, arg0);
    rotated_z = (delta_z * angle_cos) + (delta_x * angle_sin);
    rotated_x = (delta_x * angle_cos) - (delta_z * angle_sin);
    result = 0;
    if ((fabsf(adjusted_y) < (f32)(arg0->height + vertical_offset)) &&
        (fabsf(rotated_x) < (f32)(arg0->width + horizontal_extent)) &&
        (fabsf(rotated_z) < (f32)(arg0->depth + depth_extent))) {
        result = 1;
    }
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15044B78 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15044B78.s")

void func_15044CE4(void *arg0) {
    s32 temp_t0;
    void *temp_v0;

    temp_v0 = *(void **)((u8 *)arg0 + 0x18);
    *(s16 *)((u8 *)arg0 + 6) = *(s16 *)temp_v0;
    *(s16 *)((u8 *)arg0 + 8) = *(s16 *)((u8 *)temp_v0 + 2);
    *(s16 *)((u8 *)arg0 + 0xA) = *(s16 *)((u8 *)temp_v0 + 4);
    temp_t0 = *(s16 *)*(void **)((u8 *)arg0 + 0x1C) / 32;
    *(s16 *)((u8 *)arg0 + 0x10) = temp_t0;
    *(s16 *)((u8 *)arg0 + 0x12) = temp_t0;
    *(s16 *)((u8 *)arg0 + 0x14) = temp_t0;
    func_15044B78(arg0);
}
s32 func_1505D1C4(f32, f32, f32, s16, s32, s32, s32, s32);

s32 func_15044D40(void *arg0) {
    s32 sp1C;

    sp1C = 0;
    func_1505D1C4((f32)*(s16 *)((u8 *)arg0 + 6), (f32)*(s16 *)((u8 *)arg0 + 8),
                  (f32)*(s16 *)((u8 *)arg0 + 0xA), *(s16 *)((u8 *)arg0 + 0x10),
                  0xFF, 0, 0, sp1C);
    return 0;
}
extern void func_1505D024(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 D_800CC2D0[];

void func_15044DA0(void) {
    volatile u8 *state;

    state = D_800CC2D0;
    if ((state[0x104] == 0) && (state[0x125] == 0)) {
        func_1505D024((void *)state, 5, *(volatile u16 *)(state + 0x7A), -1);
    }
}
/* Call context: func_1505D024: unique active project prototype */
extern u8 D_800C35EA;

void func_15044DE8(void) {
    volatile u8 *state;

    state = D_800CC2D0;
    if ((state[0x104] == 0) && (state[0x125] == 0) && (D_800C35EA != 1)) {
        func_1505D024((void *)state, 4, *(volatile u16 *)(state + 0x7A), -1);
    }
}
void func_15044E40(void) {
    volatile u8 *state;

    state = D_800CC2D0;
    if ((state[0x104] == 0) && (state[0x125] == 0)) {
        func_1505D024((void *)state, 0x40, *(volatile u16 *)(state + 0x7A), -1);
    }
}
void func_15044E88(void) {
    volatile u8 *state;

    state = D_800CC2D0;
    if ((state[0x104] == 0) && (state[0x125] == 0)) {
        func_1505D024((void *)state, 1, *(volatile u16 *)(state + 0x7A), -1);
    }
}
typedef struct Game71820XZ {
    f32 x;
    f32 y;
    f32 z;
} Game71820XZ;

typedef struct Game71820Hit {
    f32 height;
    s16 points[9];
    s32 object;
    u8 flags;
    u8 active;
    u8 pad1E[2];
    s32 field20;
} Game71820Hit;

typedef struct Game71820Candidate {
    s32 height;
    s32 *sources;
    s32 index;
    s32 padC;
} Game71820Candidate;

s32 func_150A3A70(s32, s32);
void func_1510F800(s32);
extern f32 D_80098D40;
extern f32 D_80098D44;
extern f32 D_80098D48;
extern f32 D_80098D4C;
extern Game71820Candidate D_800D3300[];
extern u8 *D_800DBE3C;
extern s32 **D_800DBE5C;
extern f32 D_800DBE68;
extern f32 D_800DBE6C;
extern f32 D_800DBE70;
extern f32 D_800DBE74;
s32 func_150A4FA0(s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15044ED0 CURRENT (65) */
s32 func_15044ED0(Game71820XZ *arg0, f32 arg1, volatile Game71820Hit *arg2) {
    s32 count;
    s32 best;
    s32 scan_index;
    f32 height;

    if (arg1 < arg0->y) {
        arg2->flags &= ~2;
        return 0;
    }
    arg2->height = D_80098D40;
    best = -1;
    func_1510F800(0);
    count = func_150A3A70((s32)arg0->x, (s32)arg0->z);
    scan_index = 0;
    if (count > 0) {
        Game71820Candidate *scan = D_800D3300;

        do {
            height = (f32)scan->height * 0.00390625f;
            if ((arg0->y <= height) && (height < arg2->height)) {
                best = scan_index;
                arg2->height = height;
            }
            scan_index++;
            scan++;
        } while (scan_index < count);
    }
    if (best != -1) {
        Game71820Candidate *candidate;
        u32 index;
        volatile s32 *source;
        u32 copy_index;
        volatile u8 *output;
        s32 offset;
        s32 updated_flags;
        s32 flags;
        u8 *object_base;
        s32 *object_sources;
        s32 object_difference;
        s32 object_index;
        s32 object;

        candidate = &D_800D3300[best];
        source = candidate->sources;
        copy_index = 0;
        output = (volatile u8 *)arg2;
        index = candidate->index;
        offset = index * 0x10;
        for (; copy_index != 3; copy_index++, output += 6) {
            s16 *point = (s16 *)(source[copy_index] + offset);
            *(s16 *)(output + 4) = point[0];
            *(s16 *)(output + 6) = point[1];
            *(s16 *)(output + 8) = point[2];
        }
        object_difference = (u8 *)candidate->sources - D_800DBE3C;
        object_difference /= 12;
        arg2->object = (s32)D_800DBE5C[object_difference];
        flags = arg2->flags;
        arg2->active = 1;
        arg2->field20 = 0;
        updated_flags = flags | 5;
        arg2->flags = updated_flags;
        {
            f32 threshold = arg1;

            if (arg2->height <= threshold) {
                arg2->flags = updated_flags | 2;
                return 1;
            }
        }
        return 0;
    }
    arg2->flags &= ~2;
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15044ED0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15044ED0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150450CC CURRENT (100) */
s32 func_150450CC(Game71820XZ *arg0, f32 arg1, volatile Game71820Hit *arg2) {
    s32 count;
    s32 best;
    s32 scan_index;
    f32 height;

    if (arg0->y < arg1) {
        arg2->flags &= ~2;
        return 0;
    }
    arg2->height = D_80098D44;
    best = -1;
    func_1510F800(0);
    D_800DBE68 = arg0->x;
    D_800DBE6C = arg0->y;
    D_800DBE70 = arg0->z;
    D_800DBE74 = arg1;
    count = func_150A3A70((s32)arg0->x, (s32)arg0->z);
    scan_index = 0;
    if (count > 0) {
        Game71820Candidate *scan = D_800D3300;

        do {
            height = (f32)scan->height * 0.00390625f;
            if ((height <= arg0->y) && (arg2->height < height)) {
                best = scan_index;
                arg2->height = height;
            }
            scan_index++;
            scan++;
        } while (scan_index < count);
    }
    if (best != -1) {
        Game71820Candidate *candidate;
        u32 index;
        s32 *source;
        u32 copy_index;
        volatile u8 *output;
        s32 offset;
        s32 flags;
        s32 updated_flags;
        s32 **objects;
        s32 difference;

        candidate = &D_800D3300[best];
        source = candidate->sources;
        copy_index = 0;
        output = (volatile u8 *)arg2;
        index = candidate->index;
        offset = index * 0x10;
        for (; copy_index != 3; copy_index++, output += 6) {
            s16 *point = (s16 *)(source[copy_index] + offset);
            *(s16 *)(output + 4) = point[0];
            *(s16 *)(output + 6) = point[1];
            *(s16 *)(output + 8) = point[2];
        }
        objects = D_800DBE5C;
        if (objects != 0) {
            difference = (u8 *)candidate->sources - D_800DBE3C;
            arg2->object = (s32)objects[difference / 12];
            flags = arg2->flags;
        } else {
            arg2->object = 0;
            flags = arg2->flags;
        }
        arg2->active = 1;
        updated_flags = flags | 7;
        arg2->flags = updated_flags;
        arg2->field20 = 0;
        if (arg1 <= arg2->height) {
            arg2->flags = updated_flags | 2;
            return 1;
        }
        return 0;
    }
    arg2->flags &= ~2;
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150450CC */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_150450CC.s")
s32 func_15044ED0(Game71820XZ *, f32, volatile Game71820Hit *); /* extern */
s32 func_150470B0(void *, f32, void *);             /* extern */

s32 func_1504530C(Game71820XZ *arg0, f32 arg1, Game71820Hit *arg2) {
    /* func_150470B0 returns only 0, 1, or 2. */
    switch (func_150470B0(arg0, arg1, arg2)) {
    case 0:
        return func_15044ED0(arg0, arg1, arg2);
    case 1:
        return 0;
    case 2:
        return 1;
    }
}
s32 func_15045384(Game71820XZ *arg0, f32 arg1, Game71820Hit *arg2) {
    s32 count;
    s32 best;
    s32 scan_index;
    f32 height;

    if (arg1 < arg0->y) {
        arg2->flags &= ~2;
        return 0;
    }
    arg2->height = D_80098D48;
    best = -1;
    func_1510F800(3);
    count = func_150A4FA0((s32)arg0->x, (s32)arg0->z);
    scan_index = 0;
    if (count > 0) {
        Game71820Candidate *scan = D_800D3300;

        do {
            height = (f32)scan->height * 0.00390625f;
            if ((arg0->y <= height) && (height < arg2->height)) {
                best = scan_index;
                arg2->height = height;
            }
            scan_index++;
            scan++;
        } while (scan_index < count);
    }
    if (best != -1) {
        Game71820Candidate *candidate;
        s32 *source;
        u32 copy_index;
        u8 *output;
        s32 offset;
        s32 flags;
        s32 updated_flags;
        s32 active;

        candidate = &D_800D3300[best];
        source = candidate->sources;
        offset = candidate->index;
        copy_index = 0;
        output = (u8 *)arg2;
        for (; copy_index != 3; copy_index++, output += 6) {
            s16 *point = (s16 *)(source[copy_index] + offset);
            *(s16 *)(output + 4) = point[0];
            *(s16 *)(output + 6) = point[1];
            *(s16 *)(output + 8) = point[2];
        }
        arg2->object = 0;
        arg2->flags |= 6;
        arg2->active = 4;
        arg2->field20 = 0;
        if (arg2->height <= arg1) {
            arg2->flags |= 2;
            return 1;
        }
        return 0;
    }
    arg2->flags &= ~2;
    return 0;
}
s32 func_1504554C(Game71820XZ *arg0, f32 arg1, Game71820Hit *arg2) {
    s32 count;
    s32 best;
    s32 scan_index;
    f32 height;

    if (arg0->y < arg1) {
        arg2->flags &= ~2;
        return 0;
    }
    arg2->height = D_80098D4C;
    best = -1;
    func_1510F800(3);
    count = func_150A4FA0((s32)arg0->x, (s32)arg0->z);
    scan_index = 0;
    if (count > 0) {
        Game71820Candidate *scan = D_800D3300;

        do {
            height = (f32)scan->height * 0.00390625f;
            if ((height <= arg0->y) && (arg2->height < height)) {
                best = scan_index;
                arg2->height = height;
            }
            scan_index++;
            scan++;
        } while (scan_index < count);
    }
    if (best != -1) {
        Game71820Candidate *candidate;
        s32 *source;
        u32 copy_index;
        u8 *output;
        s32 offset;
        s32 flags;
        s32 updated_flags;
        s32 active;

        candidate = &D_800D3300[best];
        source = candidate->sources;
        offset = candidate->index;
        copy_index = 0;
        output = (u8 *)arg2;
        for (; copy_index != 3; copy_index++, output += 6) {
            s16 *point = (s16 *)(source[copy_index] + offset);
            *(s16 *)(output + 4) = point[0];
            *(s16 *)(output + 6) = point[1];
            *(s16 *)(output + 8) = point[2];
        }
        arg2->object = 0;
        arg2->flags |= 6;
        arg2->active = 4;
        arg2->field20 = 0;
        if (arg1 <= arg2->height) {
            arg2->flags |= 2;
            return 1;
        }
        return 0;
    }
    arg2->flags &= ~2;
    return 0;
}
s32 func_150A6500(s16, s16, s32, u16);
void func_1510F800(s32);

void func_15045714(Game71820XZ *arg0, u16 arg1, s32 *arg2, s32 arg3) {
    func_1510F800(2);
    *arg2 = func_150A6500((s16)(s32)arg0->x, (s16)(s32)arg0->z, arg3, arg1);
}
s32 func_15045F8C(Game71820XZ *, f32, void *, Game71820Hit *); /* extern */

s32 func_15045780(Game71820XZ *arg0, u16 arg1, f32 arg2, Game71820Hit *arg3) {
    s32 sp1C;
    s32 sp18;

    if (arg0->y < arg2) {
        arg3->flags &= ~2;
        return 0;
    }
    func_15045714(arg0, arg1, &sp1C, (s32) &sp18);
    return func_15045F8C(arg0, arg2, &sp18, arg3);
}
s32 func_15045780(Game71820XZ *, u16, f32, Game71820Hit *); /* extern */
s32 func_15047004(void *, f32, void *);             /* extern */

s32 func_15045800(Game71820XZ *arg0, u16 arg1, f32 arg2, Game71820Hit *arg3) {
    /* func_15047004 returns only 0, 1, or 2. */
    switch (func_15047004(arg0, arg2, arg3)) {
    case 0:
        return func_15045780(arg0, arg1, arg2, arg3);
    case 1:
        return 0;
    case 2:
        return 1;
    }
}
typedef struct Game71820Surface {
    u8 pad0[0x40];
    s32 default_material;
    s32 *materials;
    u8 pad48[0x10];
    u16 first_triangle;
    u8 pad5A[0x15];
    u8 flags;
    u8 pad70[0x30];
} Game71820Surface;

s32 func_150A43E0(s32, s32, s32, void *);
void func_150A44F0(s32, void *, s32);
extern f32 D_80098D58;
extern u8 D_800D3830[];
extern s32 D_800DBEF4;

extern f32 D_80098D50;
extern u8 D_800D37E0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15045880 CURRENT (1300) */
u8 func_15045880(Game71820XZ *arg0, f32 arg1, s32 *arg2, Game71820Hit *arg3) {
    s32 count;
    s32 best;
    s32 scan_index;
    f32 height;

    arg3->height = D_80098D50;
    best = -1;
    func_150A44F0(*arg2, D_800D37E0, 0);
    count = func_150A43E0((s32)arg0->x, (s32)arg0->z, *arg2, D_800D37E0);
    scan_index = 0;
    if (count > 0) {
        Game71820Candidate *scan = D_800D3300;
        do {
            height = (f32)scan->height * 0.00390625f;
            if ((arg0->y <= height) && (height < arg3->height)) {
                best = scan_index;
                arg3->height = height;
            }
            scan_index++;
            scan++;
        } while (scan_index < count);
    }
    if (best != -1) {
        Game71820Candidate *candidate;
        s32 *source;
        s32 copy_index;
        s32 *copy_source;
        s32 surface_index;
        u8 *output;
        s32 offset;
        Game71820Surface *surface;
        s32 *materials;
        s32 triangle_index;
        s32 surface_address;

        candidate = &D_800D3300[best];
        source = candidate->sources;
        offset = candidate->index;
        copy_index = 0;
        output = (u8 *)arg3;
        copy_source = source;
        for (; copy_index != 3; copy_index++, copy_source++, output += 6) {
            s16 *point = (s16 *)(*copy_source + offset);
            *(s16 *)(output + 4) = point[0];
            *(s16 *)(output + 6) = point[1];
            *(s16 *)(output + 8) = point[2];
        }
        triangle_index = candidate->padC;
        surface_address = triangle_index * 0xA0 + D_800DBEF4;
        arg3->field20 = surface_address;
        materials = ((Game71820Surface *)surface_address)->materials;
        surface = (Game71820Surface *)surface_address;
        if (materials != 0) {
            triangle_index = ((u8 *)source - D_800DBE3C) / 12 - ((Game71820Surface *)surface_address)->first_triangle;
            *(s32 *)((u8 *)arg3 + 0x18) = materials[triangle_index];
        } else {
            *(s32 *)((u8 *)arg3 + 0x18) = surface->default_material;
        }
        arg3->flags |= 6;
        if ((*(u8 *)(D_800DBEF4 + candidate->padC * 0xA0 + 0x6F) & 0x80) == 0x80) {
            arg3->flags |= 1;
        }
        arg3->active = 2;
        if (arg3->height <= arg1) {
            arg3->flags |= 2;
            return 1;
        }
        return 0;
    }
    arg3->flags &= ~2;
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15045880 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15045880.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15045AE4.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15045D48 CURRENT (335) */
s32 func_15045D48(Game71820XZ *arg0, f32 arg1, s32 *arg2, Game71820Hit *arg3) {
    s32 count;
    s32 best;
    s32 scan_index;
    f32 height;

    arg3->height = D_80098D58;
    best = -1;
    func_150A44F0(*arg2, D_800D3830, 0);
    count = func_150A43E0((s32)arg0->x, (s32)arg0->z, *arg2, D_800D3830);
    scan_index = 0;
    if (count > 0) {
        Game71820Candidate *scan = D_800D3300;
        do {
            height = (f32)scan->height * 0.00390625f;
            if ((arg0->y <= height) && (height < arg3->height)) {
                best = scan_index;
                arg3->height = height;
            }
            scan_index++;
            scan++;
        } while (scan_index < count);
    }
    if (best != -1) {
        Game71820Candidate *candidate;
        s32 *source;
        s32 copy_index;
        s32 *copy_source;
        s32 surface_index;
        u8 *output;
        s32 offset;
        Game71820Surface *surface;
        s32 *materials;
        s32 triangle_index;

        candidate = &D_800D3300[best];
        source = candidate->sources;
        offset = candidate->index;
        copy_index = 0;
        output = (u8 *)arg3;
        copy_source = source;
        for (; copy_index != 3; copy_index++, copy_source++, output += 6) {
            s16 *point = (s16 *)(*copy_source + offset);
            *(s16 *)(output + 4) = point[0];
            *(s16 *)(output + 6) = point[1];
            *(s16 *)(output + 8) = point[2];
        }
        surface = (Game71820Surface *)(candidate->padC * 0xA0 + D_800DBEF4);
        arg3->field20 = (s32)surface;
        materials = surface->materials;
        if (materials != 0) {
            triangle_index = ((u8 *)source - D_800DBE3C) / 12 - surface->first_triangle;
            *(s32 *)((u8 *)arg3 + 0x18) = materials[triangle_index];
        } else {
            *(s32 *)((u8 *)arg3 + 0x18) = surface->default_material;
        }
        arg3->flags |= 6;
        if ((surface->flags & 0x80) == 0x80) {
            arg3->flags |= 1;
        }
        arg3->active = 3;
        if (arg3->height <= arg1) {
            arg3->flags |= 2;
            return 1;
        }
        return 0;
    }
    arg3->flags &= ~2;
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15045D48 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15045D48.s")
extern f32 D_80098D5C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15045F8C CURRENT (335) */
s32 func_15045F8C(Game71820XZ *arg0, f32 arg1, void *arg2, Game71820Hit *arg3) {
    s32 count;
    s32 best;
    s32 scan_index;
    f32 height;

    arg3->height = D_80098D5C;
    best = -1;
    func_150A44F0(*(s32 *)arg2, D_800D3830, 0);
    count = func_150A43E0((s32)arg0->x, (s32)arg0->z, *(s32 *)arg2, D_800D3830);
    scan_index = 0;
    if (count > 0) {
        Game71820Candidate *scan = D_800D3300;
        do {
            height = (f32)scan->height * 0.00390625f;
            if ((height <= arg0->y) && (arg3->height < height)) {
                best = scan_index;
                arg3->height = height;
            }
            scan_index++;
            scan++;
        } while (scan_index < count);
    }
    if (best != -1) {
        Game71820Candidate *candidate;
        s32 *source;
        s32 copy_index;
        s32 *copy_source;
        s32 surface_index;
        u8 *output;
        s32 offset;
        Game71820Surface *surface;
        s32 *materials;
        s32 triangle_index;

        candidate = &D_800D3300[best];
        source = candidate->sources;
        offset = candidate->index;
        copy_index = 0;
        output = (u8 *)arg3;
        copy_source = source;
        for (; copy_index != 3; copy_index++, copy_source++, output += 6) {
            s16 *point = (s16 *)(*copy_source + offset);
            *(s16 *)(output + 4) = point[0];
            *(s16 *)(output + 6) = point[1];
            *(s16 *)(output + 8) = point[2];
        }
        surface = (Game71820Surface *)(candidate->padC * 0xA0 + D_800DBEF4);
        arg3->field20 = (s32)surface;
        materials = surface->materials;
        if (materials != 0) {
            triangle_index = ((u8 *)source - D_800DBE3C) / 12 - surface->first_triangle;
            *(s32 *)((u8 *)arg3 + 0x18) = materials[triangle_index];
        } else {
            *(s32 *)((u8 *)arg3 + 0x18) = surface->default_material;
        }
        arg3->flags |= 6;
        if ((surface->flags & 0x80) == 0x80) {
            arg3->flags |= 1;
        }
        arg3->active = 3;
        if (arg1 <= arg3->height) {
            arg3->flags |= 2;
            return 1;
        }
        return 0;
    }
    arg3->flags &= ~2;
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15045F8C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15045F8C.s")
u8 func_15045880(Game71820XZ *, f32, s32 *, Game71820Hit *);
s32 func_15045D48(Game71820XZ *, f32, s32 *, Game71820Hit *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150461D0 CURRENT (120) */
s32 func_150461D0(Game71820XZ *arg0, u16 arg1, f32 arg2, Game71820Hit *arg3) {
    s32 first_set;
    s32 second_set;
    Game71820Hit first_hit;
    Game71820Hit second_hit;
    u8 first_result;
    u8 second_result;

    if (arg2 < arg0->y) {
        arg3->flags &= ~2;
        return 0;
    }
    first_hit = *arg3;
    second_hit = *arg3;
    func_15045714(arg0, arg1, &first_set, (s32)&second_set);
    first_result = func_15045880(arg0, arg2, &first_set, &first_hit);
    second_result = func_15045D48(arg0, arg2, &second_set, &second_hit);
    if (first_result != 0 && second_result != 0) {
        if (first_hit.height < second_hit.height) {
            *arg3 = first_hit;
            return 1;
        }
        *arg3 = second_hit;
        return 1;
    }
    if (first_result != 0) {
        *arg3 = first_hit;
        return 1;
    }
    if (second_result != 0) {
        *arg3 = second_hit;
        return 1;
    }
    if (first_hit.height < second_hit.height) {
        *arg3 = first_hit;
    } else {
        *arg3 = second_hit;
    }
    arg3->flags &= ~2;
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150461D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_150461D0.s")
u8 func_15045AE4(Game71820XZ *, f32, s32 *, Game71820Hit *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15046460 CURRENT (120) */
s32 func_15046460(Game71820XZ *arg0, u16 arg1, f32 arg2, Game71820Hit *arg3) {
    s32 first_set;
    s32 second_set;
    Game71820Hit first_hit;
    Game71820Hit second_hit;
    u8 first_result;
    u8 second_result;

    if (arg0->y < arg2) {
        arg3->active = 0;
        arg3->field20 = 0;
        arg3->flags &= ~2;
        return 0;
    }
    first_hit = *arg3;
    second_hit = *arg3;
    func_15045714(arg0, arg1, &first_set, (s32)&second_set);
    first_result = func_15045AE4(arg0, arg2, &first_set, &first_hit);
    second_result = func_15045F8C(arg0, arg2, &second_set, &second_hit);
    if (first_result != 0 && second_result != 0) {
        if (second_hit.height < first_hit.height) {
            *arg3 = first_hit;
            return 1;
        }
        *arg3 = second_hit;
        return 1;
    }
    if (first_result != 0) {
        *arg3 = first_hit;
        return 1;
    }
    if (second_result != 0) {
        *arg3 = second_hit;
        return 1;
    }
    if (second_hit.height < first_hit.height) {
        *arg3 = first_hit;
    } else {
        *arg3 = second_hit;
    }
    arg3->flags &= ~2;
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15046460 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15046460.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_150466F8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_1504697C.s")
s32 func_150466F8(Game71820XZ *, u16, f32, Game71820Hit *);              /* extern */

s32 func_15046C00(Game71820XZ *arg0, u16 arg1, f32 arg2, Game71820Hit *arg3) {
    /* func_150470B0 returns only 0, 1, or 2. */
    switch (func_150470B0(arg0, arg2, arg3)) {
    case 0:
        return func_150466F8(arg0, arg1, arg2, arg3);
    case 1:
        return 0;
    case 2:
        return 1;
    }
}
s32 func_1504697C(Game71820XZ *, u16, f32, Game71820Hit *);              /* extern */

s32 func_15046C80(Game71820XZ *arg0, u16 arg1, f32 arg2, Game71820Hit *arg3) {
    /* func_15047004 returns only 0, 1, or 2. */
    switch (func_15047004(arg0, arg2, arg3)) {
    case 0:
        return func_1504697C(arg0, arg1, arg2, arg3);
    case 1:
        return 0;
    case 2:
        return 1;
    }
}
s32 func_15046D00(Game71820XZ *arg0, u16 arg1, f32 arg2, Game71820Hit *arg3) {
    Game71820Hit first_hit;
    Game71820Hit second_hit;
    u8 first_result;
    u8 second_result;

    if (arg0->y < arg2) {
        arg3->flags &= ~2;
        return 0;
    }
    first_hit = *arg3;
    second_hit = *arg3;
    first_result = func_1504697C(arg0, arg1, arg2, &first_hit);
    second_result = func_1504554C(arg0, arg2, &second_hit);
    if (first_result != 0 && second_result != 0) {
        if (second_hit.height < first_hit.height) {
            *arg3 = first_hit;
            return 1;
        }
        *arg3 = second_hit;
        return 1;
    }
    if (first_result != 0) {
        *arg3 = first_hit;
        return 1;
    }
    if (second_result != 0) {
        *arg3 = second_hit;
        return 1;
    }
    if (second_hit.height < first_hit.height) {
        *arg3 = first_hit;
    } else {
        *arg3 = second_hit;
    }
    arg3->flags &= ~2;
    return 0;
}
s32 func_15046D00(Game71820XZ *, u16, f32, Game71820Hit *);              /* extern */

s32 func_15046F84(Game71820XZ *arg0, u16 arg1, f32 arg2, Game71820Hit *arg3) {
    /* func_15047004 returns only 0, 1, or 2. */
    switch (func_15047004(arg0, arg2, arg3)) {
    case 0:
        return func_15046D00(arg0, arg1, arg2, arg3);
    case 1:
        return 0;
    case 2:
        return 1;
    }
}
extern s32 func_150A3FC4(f32, f32, s32, void *, f32 *);

s32 func_15047004(void *arg0, f32 arg1, void *arg2) {
    f32 sp24;

    if ((*(u8 *)((u8 *)arg2 + 0x1C) & 4) &&
        (func_150A3FC4(*(f32 *)arg0, *(f32 *)((u8 *)arg0 + 8), 0, (u8 *)arg2 + 4, &sp24) != 0)) {
        if ((arg1 <= sp24) && (sp24 <= *(f32 *)((u8 *)arg0 + 4))) {
            *(f32 *)arg2 = sp24;
            *(u8 *)((u8 *)arg2 + 0x1C) = (u8)(*(u8 *)((u8 *)arg2 + 0x1C) | 2);
            return 2;
        }
        return 1;
    }
    return 0;
}
s32 func_150470B0(void *arg0, f32 arg1, void *arg2) {
    f32 sp24;

    if ((*(u8 *)((u8 *)arg2 + 0x1C) & 4) &&
        (func_150A3FC4(*(f32 *)arg0, *(f32 *)((u8 *)arg0 + 8), 0, (u8 *)arg2 + 4, &sp24) != 0)) {
        if ((sp24 <= arg1) && (*(f32 *)((u8 *)arg0 + 4) <= sp24)) {
            *(f32 *)arg2 = sp24;
            *(u8 *)((u8 *)arg2 + 0x1C) = (u8)(*(u8 *)((u8 *)arg2 + 0x1C) | 2);
            return 2;
        }
        return 1;
    }
    return 0;
}
typedef struct Game71820Triangle {
    s16 points[9];
} Game71820Triangle;

typedef struct Game71820CollisionState {
    u8 pad0[0x14];
    f32 x;
    f32 y;
    f32 z;
    u8 pad20[0xD8];
    s32 flags;
    u8 padFC[0x84];
    f32 height;
    s32 object;
    u8 pad188[4];
    Game71820Triangle triangle;
    u8 pad19E[2];
    u16 index;
} Game71820CollisionState;

s32 func_15145C90(s32);
extern s32 D_800DBEF4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1504715C CURRENT (1010) */
void func_1504715C(Game71820Hit *arg0, Game71820CollisionState *arg1) {
    s16 x;
    s16 y;
    s16 z;
    s16 right;
    s32 index;
    s32 active;
    u16 id;

    arg0->height = arg1->height;
    if (arg1->flags & 0x200000) {
        x = (s32)arg1->x;
        y = (s32)arg1->height;
        z = (s32)arg1->z;
        right = x + 1000;
        arg0->points[0] = right;
        arg0->points[3] = x - 1000;
        arg0->points[2] = z + 1000;
        arg0->points[6] = right;
        arg0->points[8] = z - 1000;
        arg0->points[1] = y;
        arg0->points[4] = y;
        arg0->points[7] = y;
        arg0->points[5] = z;
    } else {
        *(Game71820Triangle *)arg0->points = arg1->triangle;
    }
    arg0->object = arg1->object;
    arg0->flags = 6;
    id = arg1->index;
    index = id - 1;
    if (id != 0) {
        arg0->active = 2;
        arg0->field20 = D_800DBEF4 + index * 0xA0;
        if (func_15145C90(index) != 0) {
            active = 1;
        } else {
            active = 0;
        }
        arg0->flags |= active;
        return;
    } else {
        arg0->active = 1;
        arg0->field20 = 0;
        arg0->flags |= 1;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1504715C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_1504715C.s")
typedef struct Game71820PackedBlock {
    u8 bytes[16];
} Game71820PackedBlock;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150472C0 CURRENT (665) */
void func_150472C0(void *arg0, void *arg1) {
    s32 one;
    u8 active;
    s32 var_a2;
    s32 var_v0;
    s32 var_v1;
    s32 temp_v0;

    one = 1;
    *(f32 *)arg0 = *(f32 *)((u8 *)arg1 + 0xC);
    *(Game71820PackedBlock *)((u8 *)arg0 + 4) = *(Game71820PackedBlock *)((u8 *)arg1 + 0x44);
    *(u16 *)((u8 *)arg0 + 0x14) = *(u16 *)((u8 *)arg1 + 0x54);
    *(s32 *)((u8 *)arg0 + 0x18) = *(s32 *)((u8 *)arg1 + 0x60);
    temp_v0 = *(u8 *)((u8 *)arg1 + 0x59);
    var_v1 = 0;
    var_a2 = 0;
    var_v1 = (one == temp_v0) ? 2 : var_v1;
    active = 1;
    var_a2 = (one == temp_v0) ? one : var_a2;
    if (one == temp_v0) {
        var_v0 = 4;
    } else {
        var_v0 = 0;
    }
    *(s8 *)((u8 *)arg0 + 0x1C) = var_v0 | var_a2 | var_v1;
    if (*(u8 *)((u8 *)arg1 + 0x59) == one) {
        *(s8 *)((u8 *)arg0 + 0x1D) = active;
    } else {
        *(s8 *)((u8 *)arg0 + 0x1D) = 0;
    }
    *(s32 *)((u8 *)arg0 + 0x20) = *(s32 *)((u8 *)arg1 + 0x5C);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150472C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_150472C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15047390.s")
typedef struct {
    f32 elements[16];
} Game71820Matrix;

void func_15047390(Game71820Matrix *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void func_150A7790(void *, s32);

void func_15047688(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9) {
    Game71820Matrix matrix;

    func_15047390(&matrix, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
    func_150A7790(&matrix, arg0);
}
/* Call context: func_150A7BC0: unique active project prototype */
void func_150A7BC0(s32, s32);
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
void func_15047700(Game71820Matrix *, s32, f32, f32, f32, f32, f32, f32, f32, f32, f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15047700 CURRENT (16646) */
void func_15047700(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10) {
    f32 sp4C;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fa0_3;
    f32 temp_fa0_4;
    f32 temp_fa0_6;
    f32 temp_fa0_7;
    f32 temp_fa0_8;
    f32 temp_fa1;
    f32 temp_fa1_2;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 temp_fv1_3;
    f32 temp_fv1_4;
    f32 temp_fv1_5;
    f32 var_fs0;
    f32 var_fs1;
    f32 var_fs2;
    f32 var_fs4;
    f32 var_fs5;
    f32 var_ft5;
    f32 var_fv0;
    f32 var_fv0_2;
    f32 var_fv0_3;
    f32 var_fv0_4;
    f32 var_fv0_5;
    f32 var_fv0_6;

    func_150A7BC0(arg0, arg1);
    temp_fv0 = arg6 - arg3;
    temp_fv1 = arg7 - arg4;
    var_fs1 = temp_fv0;
    var_fs0 = arg5 - arg2;
    var_fs2 = temp_fv1;
    if ((arg5 == arg2) && (temp_fv0 == 0.0f) && (temp_fv1 == 0.0f)) {
        var_fs2 = 1.0f;
        var_fs0 = 0.0f;
        var_fs1 = 0.0f;
    }
    temp_fv1_2 = -1.0f / sqrtf((var_fs0 * var_fs0) + (var_fs1 * var_fs1) + (var_fs2 * var_fs2));
    temp_fs0 = var_fs0 * temp_fv1_2;
    temp_fs1 = var_fs1 * temp_fv1_2;
    temp_fs2 = var_fs2 * temp_fv1_2;
    temp_fa0 = (arg9 * temp_fs2) - (arg10 * temp_fs1);
    temp_fa1 = (arg10 * temp_fs0) - (arg8 * temp_fs2);
    temp_ft5 = (arg8 * temp_fs1) - (arg9 * temp_fs0);
    sp4C = temp_ft5;
    temp_fv0_2 = (temp_fa0 * temp_fa0) + (temp_fa1 * temp_fa1) + (temp_ft5 * temp_ft5);
    if (temp_fv0_2 != 0.0f) {
        temp_fv1_3 = 1.0f / sqrtf(temp_fv0_2);
        var_fs4 = temp_fa0 * temp_fv1_3;
        var_fs5 = temp_fa1 * temp_fv1_3;
        sp4C *= temp_fv1_3;
    } else {
        var_fs4 = 1.0f;
        var_fs5 = 0.0f;
        sp4C = 0.0f;
    }
    temp_fv0_3 = (temp_fs1 * sp4C) - (temp_fs2 * var_fs5);
    arg8 = temp_fv0_3;
    temp_fv1_4 = (temp_fs2 * var_fs4) - (temp_fs0 * sp4C);
    arg9 = temp_fv1_4;
    temp_fa0_2 = (temp_fs0 * var_fs5) - (temp_fs1 * var_fs4);
    arg10 = temp_fa0_2;
    temp_fa1_2 = (temp_fv0_3 * temp_fv0_3) + (temp_fv1_4 * temp_fv1_4) + (temp_fa0_2 * temp_fa0_2);
    if (temp_fa1_2 != 0.0f) {
        temp_fv1_5 = 1.0f / sqrtf(temp_fa1_2);
        var_ft5 = arg8 * temp_fv1_5;
        arg9 *= temp_fv1_5;
        arg10 *= temp_fv1_5;
    } else {
        arg8 = 0.0f;
        var_ft5 = arg8;
        arg10 = 0.0f;
        arg9 = 1.0f;
    }
    temp_fa0_3 = var_fs4 * 128.0f;
    if (temp_fa0_3 < 127.0f) {
        var_fv0 = temp_fa0_3;
    } else {
        var_fv0 = 127.0f;
    }
    temp_fa0_4 = var_fs5 * 128.0f;
    *(s8 *)((u8 *)arg1 + 8) = (s8) (s32) var_fv0;
    if (temp_fa0_4 < 127.0f) {
        var_fv0_2 = temp_fa0_4;
    } else {
        var_fv0_2 = 127.0f;
    }
    *(s8 *)((u8 *)arg1 + 9) = (s8) (s32) var_fv0_2;
    {
        f32 temp_fa0_5 = sp4C * 128.0f;
    if (temp_fa0_5 < 127.0f) {
        var_fv0_3 = temp_fa0_5;
    } else {
        var_fv0_3 = 127.0f;
    }
    temp_fa0_6 = var_ft5 * 128.0f;
    *(s8 *)((u8 *)arg1 + 0xA) = (s8) (s32) var_fv0_3;
    if (temp_fa0_6 < 127.0f) {
        var_fv0_4 = temp_fa0_6;
    } else {
        var_fv0_4 = 127.0f;
    }
    *(s8 *)((u8 *)arg1 + 0x18) = (s8) (s32) var_fv0_4;
    temp_fa0_7 = arg9 * 128.0f;
    if (temp_fa0_7 < 127.0f) {
        var_fv0_5 = temp_fa0_7;
    } else {
        var_fv0_5 = 127.0f;
    }
    temp_fa0_8 = arg10 * 128.0f;
    *(s8 *)((u8 *)arg1 + 0x19) = (s8) (s32) var_fv0_5;
    if (temp_fa0_8 < 127.0f) {
        var_fv0_6 = temp_fa0_8;
    } else {
        var_fv0_6 = 127.0f;
    }
    *(s8 *)((u8 *)arg1 + 0) = 0;
    *(s8 *)((u8 *)arg1 + 1) = 0;
    *(s8 *)((u8 *)arg1 + 2) = 0;
    *(s8 *)((u8 *)arg1 + 3) = 0;
    *(s8 *)((u8 *)arg1 + 4) = 0;
    *(s8 *)((u8 *)arg1 + 5) = 0;
    *(s8 *)((u8 *)arg1 + 6) = 0;
    *(s8 *)((u8 *)arg1 + 7) = 0;
    *(s8 *)((u8 *)arg1 + 0x10) = 0;
    *(s8 *)((u8 *)arg1 + 0x11) = 0x80;
    *(s8 *)((u8 *)arg1 + 0x12) = 0;
    *(s8 *)((u8 *)arg1 + 0x13) = 0;
    *(s8 *)((u8 *)arg1 + 0x14) = 0;
    *(s8 *)((u8 *)arg1 + 0x15) = 0x80;
    *(s8 *)((u8 *)arg1 + 0x16) = 0;
    *(s8 *)((u8 *)arg1 + 0x17) = 0;
    *(s8 *)((u8 *)arg1 + 0x1A) = (s8) (s32) var_fv0_6;
    *(f32 *)((u8 *)arg0 + 0) = var_fs4;
    *(f32 *)((u8 *)arg0 + 0x10) = var_fs5;
    *(f32 *)((u8 *)arg0 + 4) = var_ft5;
    *(f32 *)((u8 *)arg0 + 0x20) = sp4C;
    *(f32 *)((u8 *)arg0 + 0x30) = (f32) -((arg2 * var_fs4) + (arg3 * var_fs5) + (arg4 * sp4C));
    *(f32 *)((u8 *)arg0 + 0x24) = arg10;
    *(f32 *)((u8 *)arg0 + 0x14) = arg9;
    *(f32 *)((u8 *)arg0 + 8) = temp_fs0;
    *(f32 *)((u8 *)arg0 + 0x18) = temp_fs1;
    *(f32 *)((u8 *)arg0 + 0x28) = temp_fs2;
    *(f32 *)((u8 *)arg0 + 0x34) = (f32) -((arg2 * var_ft5) + (arg3 * arg9) + (arg4 * arg10));
    *(f32 *)((u8 *)arg0 + 0xC) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x1C) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x2C) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x3C) = 1.0f;
    *(f32 *)((u8 *)arg0 + 0x38) = (f32) -((arg2 * temp_fs0) + (arg3 * temp_fs1) + (arg4 * temp_fs2));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15047700 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_71820/func_15047700.s")
void func_15047B80(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10) {
    Game71820Matrix matrix;

    func_15047700(&matrix, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
    func_150A7790(&matrix, arg0);
}
