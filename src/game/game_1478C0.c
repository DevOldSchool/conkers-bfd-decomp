#include "types.h"

/*
 * Reviewed source unit: src/game/game_1478C0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_recovered_pointer_helper_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1511A410
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

typedef struct Game1478C0Object {
    u8 unk_00[0x1C];
    s8 *unk_1C;
    u8 unk_20[0x34];
    u16 unk_54;
} Game1478C0Object;

extern Game1478C0Sequence D_80089324[];
extern s32 D_800BE9F0;
s32 func_1511A410(s8 *, s32 *);
s32 func_1510D0EC(s32, s32 *, s32, s32);
void func_1510D874(s32, s32, s32, s32, s32);

void func_1511A494(void *arg0, void *arg1, void *arg2) {
    s32 i;
    s32 loadedOffset;
    s32 kind;
    Game1478C0Sequence *selected;
    s32 flags;
    s32 position;
    s32 direction;
    s32 upper;
    s32 packed;
    s32 result;
    s32 secondary;
    s32 address;
    s32 source;

    selected = NULL;
    for (i = 0; i < 24; i++) {
        kind = D_80089324[i].kind;
        if (D_80089324[i].world != -1) {
            if (D_800BE9F0 != D_80089324[i].world) {
                continue;
            }
            if (kind != 0xFF) {
                kind |= 0x8000;
            }
        }
        if (kind == 0xFF || kind == ((Game1478C0Object *)arg0)->unk_54) {
            selected = &D_80089324[i];
            break;
        }
    }
    if (selected == NULL) {
        return;
    }
    packed = *(s32 *)arg1;
    if (packed == 0) {
        result = func_1511A410(((Game1478C0Object *)arg0)->unk_1C, &upper);
        *(s32 *)arg1 = (upper << 16) | result;
    } else {
        upper = (packed >> 16) & 0xFFFF;
    }
    direction = (s16)((*(s32 *)arg2 >> 16) & 0xFFFF);
    position = *(s32 *)arg2 & 0xFFFF;
    if (direction == 0) {
        direction = 1;
    }
    position += direction;
    if (selected->bounce != 0) {
        if (position < 0) {
            direction = 1;
            position = selected->stride;
        } else if (position >= selected->count * selected->stride) {
            direction = -1;
            position = (selected->count - 1) * selected->stride;
        }
    } else if (position >= selected->count * selected->stride) {
        position -= selected->count * selected->stride;
        direction = 1;
    }
    source = selected->entries[position / selected->stride];
    secondary = 0;
    if (D_800BE9F0 == 6 || D_800BE9F0 == 0x3B) {
        flags = 3;
    } else {
        flags = 0x3E;
    }
    address = func_1510D0EC(source, &loadedOffset, flags, 0);
    if (upper != 0) {
        secondary = loadedOffset + address - 0x20;
    }
    func_1510D874((s32)arg0, address, secondary, 4, 5);
    *(s32 *)arg2 = (direction << 16) | position;
}
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
