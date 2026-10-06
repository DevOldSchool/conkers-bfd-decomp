#include "types.h"

/*
 * Reviewed source unit: src/game/game_1478C0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_recovered_pointer_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1511A410
 * - func_1511A494
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1511A410 CURRENT (1696) */
s32 func_1511A410(volatile s8 *arg0, s32 *arg1) {
    s32 slots[2];
    s32 var_v0;
    s32 var_v1;
    s32 var_a1;

    slots[0] = 0;
    slots[1] = 0;
    var_v0 = 0;
    var_v1 = 0;
    if (*arg0 != -0x21) {
        var_a1 = *((0 * 8) + arg0);
loop_2:
        if (var_a1 == -3) {
            slots[var_v0] = var_v1;
            var_v0 += 1;
        }
        var_v1 += 1;
        var_a1 = *((var_v1 * 8) + arg0);
        if ((var_a1 != -0x21) && (var_v0 < 2)) {
            goto loop_2;
        }
    }
    *arg1 = slots[1];
    return slots[0];
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1511A410 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1478C0/func_1511A410.s")
typedef struct {
    s32 *entries;
    u8 count, kind;
    s8 world;
    u8 stride, bounce;
    u8 pad9[3];
} Game1478C0Sequence;

extern Game1478C0Sequence D_80089324[], D_80089444[];
extern s32 D_800BE9F0;
s32 func_1511A410(s8 *, s32 *);
s32 func_1510D0EC(s32, s32 *, s32, s32);
void func_1510D874(s32, s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1511A494 CURRENT (4215) */
void func_1511A494(void *arg0, void *arg1, void *arg2) {
    s32 loadedOffset;
    Game1478C0Sequence *selected;
    s32 position;
    s32 directionSaved;
    s32 upper;
    volatile s32 zero;
    Game1478C0Sequence *cursor;
    s32 kind;
    s8 world;
    s32 direction;
    s32 packed;
    s32 result;
    s32 frames;
    s32 currentWorld;
    s32 flags;
    s32 address;
    s32 secondary;
    s32 source;

    selected = 0;
    cursor = D_80089324;
    do {
        world = cursor->world;
        kind = cursor->kind;
        if (world != -1) {
            if (D_800BE9F0 != world) {
                cursor++;
                continue;
            }
            if (kind != 0xFF) {
                kind |= 0x8000;
            }
        }
        if (kind == 0xFF || kind == *(u16 *)((u8 *)arg0 + 0x54)) {
            selected = cursor;
            break;
        }
        cursor++;
    } while (cursor != D_80089444);
    if (selected != 0) {
        packed = *(s32 *)arg1;
        if (packed == 0) {
            result = func_1511A410(*(s8 **)((u8 *)arg0 + 0x1C), &upper);
            *(u32 *)arg1 = ((u32)upper << 16) | (u32)result;
        } else {
            upper = (packed >> 16) & 0xFFFF;
        }
        currentWorld = D_800BE9F0;
        packed = *(s32 *)arg2;
        direction = (s16)((packed >> 16) & 0xFFFF);
        if (direction == 0) {
            direction = 1;
        }
        position = (packed & 0xFFFF) + direction;
        frames = selected->stride;
        if (selected->bounce != 0) {
            if (position < 0) {
                direction = 1;
                position = frames;
            } else if (position >= selected->count * frames) {
                direction = -1;
                position = (selected->count - 1) * frames;
            }
        } else if (position >= selected->count * frames) {
            position -= selected->count * frames;
            direction = 1;
        }
        source = selected->entries[position / frames];
        zero = 0;
        flags = 0x3E;
        if (currentWorld == 6 || currentWorld == 0x3B) {
            flags = 3;
        }
        directionSaved = direction;
        address = func_1510D0EC(source, &loadedOffset, flags, 0);
        secondary = zero;
        if (upper != 0) {
            secondary = (s32)((u32)loadedOffset + (u32)address - 0x20U);
        }
        func_1510D874((s32)arg0, address, secondary, 4, 5);
        *(u32 *)arg2 = ((u32)directionSaved << 16) | (u32)position;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1511A494 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1478C0/func_1511A494.s")
void func_15116110(void);
void func_1511A494(void *, void *, void *);

void func_1511A6FC(void *arg0) {
    if (*(s32 *)((u8 *)arg0 + 0x3C) != 0) {
        func_15116110();
    }
    func_1511A494(arg0, (u8 *)arg0 + 0x80, (u8 *)arg0 + 0x84);
}
s32 func_15022B08(s32, s32);
void func_151162D4(void *);
extern u8 D_800C35EA;
extern s32 D_800DBEF4;

void func_1511A738(void *arg0) {
    if ((D_800C35EA == 1) &&
        (func_15022B08(((s32)arg0 - D_800DBEF4) / 160, 0) != 0)) {
        *(s32 *)((u8 *)arg0 + 0x7C) = 0;
        *(f32 *)((u8 *)arg0 + 0x18) = 0.0f;
    }
    func_151162D4(arg0);
    func_1511A494(arg0, (u8 *)arg0 + 0x80, (u8 *)arg0 + 0x84);
}
