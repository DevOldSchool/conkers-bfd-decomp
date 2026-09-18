#include "types.h"

/*
 * Reviewed source unit: src/game/game_70200.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15043384
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef u8 *Game70200VaList;
#define GAME70200_VA_START(ap, last) ((ap) = (u8 *)&(last) + sizeof(last))
#define GAME70200_VA_ARG(ap, type) \
    (*(((type *)((ap) = (u8 *)((((s32)(ap) + 3) & ~3) + sizeof(type)))) - 1))
#define GAME70200_VA_END(ap) ((void)0)

typedef union Game70200Command {
    struct { u32 w0; u32 w1; } words;
    u64 alignment;
} Game70200Command;

s32 func_15043384(Game70200Command *dl);
extern s32 D_800CBD64;
void *func_10022EC0(void *, const void *, u32);

void func_15042D50(void) {
    D_800CBD64 = 0;
    func_15043384(0);
}
extern u8 D_800CBD74;
extern s16 D_800CBD70;
extern s16 D_800CBD72;
void func_15042ECC();

void func_15042D78(u8 arg0) {
    D_800CBD74 = arg0;
}
void func_15042D94(s32 arg0, s32 arg1, u8 arg2, s32 arg3, ...) {
    Game70200VaList args;
    s32 storage[16];
    s32 i;

    D_800CBD74 = arg2;
    D_800CBD70 = arg0;
    D_800CBD72 = arg1;
    GAME70200_VA_START(args, arg3);
    for (i = 0; i < 16; i++) {
        storage[i] = GAME70200_VA_ARG(args, s32);
    }
    GAME70200_VA_END(args);
    func_15042ECC(arg3, storage);
}

void func_15042E3C(s32 arg0, ...) {
    Game70200VaList args;
    s32 storage[16];
    s32 i;

    GAME70200_VA_START(args, arg0);
    for (i = 0; i < 16; i++) {
        storage[i] = GAME70200_VA_ARG(args, s32);
    }
    GAME70200_VA_END(args);
    func_15042ECC(arg0, storage);
}

typedef struct Game70200Anchor {
    u8 pad0[0x14];
    f32 x;
    f32 y;
    f32 z;
} Game70200Anchor;

typedef struct Game70200TextNode {
    Game70200Anchor *field_0;
    f32 field_4;
    s16 field_8;
    s16 field_A;
    u8 field_C;
    u8 field_D;
    u8 field_E;
    u8 field_F;
    u8 field_10;
    u8 field_11;
    u8 field_12;
    u8 field_13;
    u8 field_14;
    u8 field_15;
    u8 pad_16[2];
    struct Game70200TextNode *next;
    u8 text[0x40];
} Game70200TextNode;

void *func_10003C40(s32, s32, s32, s32);
s32 func_151EFF94(u8 *, const u8 *, ...);
extern u8 D_80085CC0[];
extern u8 D_80085CC4;
extern s8 D_8008FD90;
extern s32 D_80098B90;
extern s32 D_80098B94;
extern Game70200TextNode *D_800CBD68;
extern u8 D_800CBD6C;
extern u8 D_800CBD6D;
extern u8 D_800CBD6E;
extern u8 D_800CBD6F;
extern u8 D_800CBD60;
extern u8 D_800CBD61;
extern u8 D_800CBD62;
extern u8 D_800CBD63;
extern s32 D_800CBD78;
extern s16 D_800CBD7C;
extern f32 D_800CBD80;

void func_15042ECC(u8 *format, s32 *arg_data) {
    struct {
        Game70200TextNode *node;
        s32 pad;
        s32 finished;
        s32 pad2;
    } local;
    Game70200TextNode *node;
    u8 *out;
    s32 arg_index;
    s32 format_index;
    u8 ch;
    u8 flags;
    u8 *conversion;

    arg_index = 0;
    conversion = &D_80085CC4;
    while (*format != 0) {
        local.node = func_10003C40(sizeof(Game70200TextNode), 1, 0, 1);
        if (local.node == 0) {
            return;
        }
        local.node->next = 0;
        local.finished = 0;
        if (D_800CBD68 == 0) {
            D_800CBD64 = (s32)local.node;
        } else {
            D_800CBD68->next = local.node;
        }
        out = local.node->text;
        local.node->field_D = 0;
        do {
            ch = *format;
            if (ch == '%') {
                format++;
                *conversion = '%';
                for (format_index = 1; format_index != 0; format_index++, format++) {
                    u8 *destination = &(&D_80085CC4)[format_index];

                    destination[0] = *format;
                    destination[1] = 0;
                    switch (destination[0]) {
                    case 'X':
                    case 'd':
                    case 'x':
                        func_151EFF94(out, &D_80085CC4,
                                     arg_data[arg_index++]);
                        while (*out != 0) {
                            out++;
                        }
                        format_index = -1;
                        break;
                    case 'F':
                    case 'f': {
                        f32 *number = (f32 *)arg_data[arg_index++];
                        f32 value = *number;

                        func_151EFF94(out, D_80085CC0, &D_80098B90,
                                     &D_80098B94,
                                     (f64)value);
                        while (*out != 0) {
                            out++;
                        }
                        format_index = -1;
                        break;
                    }
                    case 's':
                        func_151EFF94(out, &D_80085CC4,
                                     arg_data[arg_index++]);
                        while (*out != 0) {
                            out++;
                        }
                        format_index = -1;
                        break;
                    case '%':
                        *out++ = *format;
                        *out = 0;
                        format_index = -1;
                        break;
                    default:
                        break;
                    }
                }
            } else if (ch == '#') {
                local.node->field_D = arg_data[arg_index++];
                format += 2;
            } else if (ch == '\n') {
                format++;
                local.finished = 1;
            } else if (ch == 0) {
                local.finished = 1;
            } else {
                *out = ch;
                format++;
                out++;
                *out = 0;
            }
        } while (local.finished == 0);

        node = local.node;
        node->field_C = D_800CBD74;
        node->field_0 = (Game70200Anchor *)D_800CBD78;
        if (node->field_0 != 0) {
            node->field_A = D_800CBD7C;
            flags = node->field_C | 1;
            node->field_C = (node->field_C = flags);
            if (D_8008FD90 >= 2) {
                node->field_4 = D_800CBD80 + D_800CBD80;
            } else {
                node->field_4 = D_800CBD80;
            }
        } else {
            node->field_8 = D_800CBD70;
            node->field_A = D_800CBD72;
            node->field_4 = D_800CBD80;
        }
        node->field_E = D_800CBD60;
        node->field_F = D_800CBD61;
        node->field_10 = D_800CBD62;
        node->field_11 = D_800CBD63;
        node->field_12 = D_800CBD6C;
        node->field_13 = D_800CBD6D;
        node->field_14 = D_800CBD6E;
        node->field_15 = D_800CBD6F;
        D_800CBD68 = node;
        if (node->field_D != 0) {
            node->field_E = 0xFF;
            node->field_F = 0xFF;
            node->field_10 = 0xFF;
        } else {
            D_800CBD72 += 0xB;
        }
    }
    D_800CBD78 = 0;
}
extern f32 D_800CBD80;

void func_150432BC(f32 arg0) {
    D_800CBD80 = arg0;
}
extern s32 D_800CBD78;
extern s16 D_800CBD7C;

void func_150432CC(s32 arg0, s32 arg1) {
    D_800CBD74 = (D_800CBD74 |= 1);
    D_800CBD7C = arg1;
    D_800CBD78 = arg0;
}
void func_150432FC(s16 arg0, s16 arg1) {
    D_800CBD70 = arg0;
    D_800CBD72 = arg1;
}
extern u8 D_800CBD60;
extern u8 D_800CBD61;
extern u8 D_800CBD62;
extern u8 D_800CBD63;

void func_1504332C(u8 arg0, u8 arg1, u8 arg2, u8 arg3) {
    D_800CBD60 = arg0;
    D_800CBD61 = arg1;
    D_800CBD62 = arg2;
    D_800CBD63 = arg3;
}
typedef struct Game70200TextureInfo {
    s32 field_0;
    s16 field_4;
    s16 field_6;
    s16 field_8;
} Game70200TextureInfo;

void func_10004074(s32);
s32 func_10022EEC(void *);
void *func_150417AC(void *, f32, f32, void *, s32, s32, s32, s32, f32, f32, s32);
void func_150428D4(void *, s32 *, s32 *, s32 *);
s32 func_1509563C(f32, f32, f32, f32 *, f32 *, f32 *, f32 *, f32);
void *func_151ED430(void *, Game70200TextureInfo *, s16, s16, s32, s32, f32, s32);
extern s32 D_80082FA4;
extern u8 D_800859A0[];
typedef struct Game70200Effect {
    u8 width;
    u8 height;
    u8 scale;
    u8 flags;
    s32 data;
} Game70200Effect;
extern Game70200Effect D_800859E0[];
extern Game70200Effect D_80085AA8;
extern s32 D_80085CD0;
extern f32 D_8008FE1C;
extern f32 D_8008FE20;
extern f32 D_80098C64;
extern s32 D_800BE9AC;
extern Game70200TextureInfo D_80090060;

#define GAME70200_COMMAND(p, first, second) do { \
    Game70200Command *command = (p)++; \
    command->words.w0 = (u32)(first); \
    command->words.w1 = (u32)(second); \
} while (0)

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15043384 CURRENT (3873) */
s32 func_15043384(Game70200Command *dl) {
    s32 width;
    s32 unused1;
    s32 unused2;
    Game70200TextNode *text;
    Game70200Effect *effect;
    s32 visible;
    s32 extra_pass;
    f32 scale;
    s32 pulse;
    s32 alpha;
    f32 projected_x;
    f32 projected_y;
    f32 projected_z;
    f32 projected_w;
    s32 base;

    text = (Game70200TextNode *)D_800CBD64;
    D_80085CD0++;
    if (text != 0) {
        GAME70200_COMMAND(dl, 0xDE000000, (s32)D_800859A0);
        GAME70200_COMMAND(dl, 0xEF002C3F, 0x00504240);
        while (text != 0) {
                if (text->field_D == 0) {
                    visible = 1;
                    extra_pass = 0;
                    if (text->field_C & 0x40) {
                        text->field_C &= ~0x40;
                    } else {
                        text->field_8 = (s32)((f32)text->field_8 * D_8008FE1C);
                        text->field_A = (s32)((f32)text->field_A * D_8008FE20);
                    }
                    if (text->field_C & 0x80) {
                        extra_pass = 1;
                        text->field_C &= ~0x80;
                    }
                    base = (s32)text->field_0;
                    if (base != 0) {
                        D_80082FA4 = 0;
                        visible = func_1509563C(
                            ((Game70200Anchor *)base)->x,
                            ((Game70200Anchor *)base)->y + (f32)text->field_A,
                            ((Game70200Anchor *)base)->z,
                            &projected_x, &projected_y,
                            &projected_z, &projected_w,
                            D_80098C64);
                        if (visible != 0) {
                            text->field_8 = (s32)projected_x;
                            text->field_A = (s32)projected_y;
                        }
                    }
                    if ((text->field_C == 1) || (text->field_15 != 0)) {
                        func_150428D4(text->text, &width,
                                      &unused1, &unused2);
                        width = (s32)((f32)width * text->field_4);
                    }
                    if (text->field_C == 1) {
                        text->field_8 -= width >> 1;
                    }
                    if (visible != 0) {
                        scale = text->field_4 * 4096.0f;
                        if (extra_pass != 0) {
                            dl = func_150417AC(dl,
                                (f32)(text->field_8 + 1), (f32)(text->field_A + 1), text->text,
                                0, 0, 0, text->field_11, scale, scale,
                                func_10022EEC(text->text));
                        }
                        dl = func_150417AC(dl,
                            (f32)text->field_8, (f32)text->field_A, text->text,
                            text->field_E, text->field_F, text->field_10, text->field_11,
                            scale, scale, func_10022EEC(text->text));
                    }
                    GAME70200_COMMAND(dl, 0xE7000000, 0);
                } else {
                    pulse = text->field_D - 1;
                    effect = &D_800859E0[pulse];
                    scale = (f32)effect->scale * 0.0078125f;
                    GAME70200_COMMAND(dl, 0xFC12D225, 0xFFA7FFFF);
                    base = effect->flags;
                    if (base & 2) {
                        D_80090060.field_6 = 0x10;
                        D_80090060.field_8 = 0x10;
                    }
                    if (base & 1) {
                        GAME70200_COMMAND(dl, 0xE7000000, 0);
                        GAME70200_COMMAND(dl, 0xFB000000, (text->field_E << 24) | (text->field_F << 16) |
                                (text->field_10 << 8) | text->field_11);
                        D_80090060.field_0 = effect[-1].data;
                        dl = func_151ED430(dl, &D_80090060, text->field_8, text->field_A,
                                          effect[-1].width, effect[-1].height, scale, 0);
                        pulse = (D_800BE9AC * 2) & 0x7F;
                        if (pulse >= 0x40) {
                            pulse = 0x7F - pulse;
                        }
                        alpha = (s32)(text->field_11 * ((pulse + pulse + pulse) + 0x3F)) >> 8;
                        if (alpha >= 0x100) {
                            alpha = 0xFF;
                        }
                        text->field_11 = alpha;
                    }
                    GAME70200_COMMAND(dl, 0xE7000000, 0);
                    GAME70200_COMMAND(dl, 0xFB000000, (text->field_E << 24) | (text->field_F << 16) |
                            (text->field_10 << 8) | text->field_11);
                    base = effect->data;
                    D_80090060.field_0 = base;
                    if (effect == &D_80085AA8) {
                        pulse = (D_80085CD0 >> 1) % 10;
                        if (pulse >= 6) {
                            pulse = 10 - pulse;
                        }
                        D_80090060.field_0 = base + pulse;
                    }
                    dl = func_151ED430(dl, &D_80090060, text->field_8, text->field_A,
                                      effect->width, effect->height, scale, 0);
                    GAME70200_COMMAND(dl, 0xDE000000, (s32)D_800859A0);
        GAME70200_COMMAND(dl, 0xEF002C3F, 0x00504240);
                    if (effect->flags & 2) {
                        D_80090060.field_6 = 0x20;
                        D_80090060.field_8 = 0x20;
                    }
                }
            {
                Game70200TextNode *next = text->next;
                func_10004074((s32)text);
                text = next;
            }
        }
        GAME70200_COMMAND(dl, 0xE7000000, 0);
    }
    D_800CBD60 = 0xFF;
    D_800CBD61 = 0xFF;
    D_800CBD62 = 0xFF;
    D_800CBD63 = 0xFF;
    D_800CBD6C = 0;
    D_800CBD6D = 0;
    D_800CBD6E = 0;
    D_800CBD6F = 0x80;
    D_800CBD70 = 10;
    D_800CBD72 = 10;
    D_800CBD80 = 1.0f;
    D_800CBD74 = 0;
    D_800CBD64 = 0;
    D_800CBD68 = 0;
    D_800CBD78 = 0;
    return (s32)dl;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15043384 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_70200/func_15043384.s")
typedef struct Game70200Entry {
    s32 field_0;
    s32 field_4;
    s32 field_8;
    s32 field_C;
} Game70200Entry;

void func_15043A00(Game70200Entry *arg0, s32 arg1, s32 arg2) {
    if (arg0) {
        arg0->field_0 = arg1;
        arg0->field_4 = arg2;
        arg0->field_C = 0;
        arg0->field_8 = 0;
    }
}
s32 func_15043A20(s32 arg0, s32 arg1, s32 arg2, s32 *arg3, s32 arg4) {
    s32 count;

    if (arg4 != 0) {
        do {
            if (arg1 < arg2 + arg4) {
                count = arg1 - arg2;
            } else {
                count = arg4;
            }
            func_10022EC0((u8 *)arg0 + arg2, arg3, count);
            arg2 += count;
            arg3 = (s32 *)((u8 *)arg3 + count);
            arg4 -= count;
            if (arg2 >= arg1) {
                arg2 = 0;
            }
        } while (arg4 != 0);
    }
    return arg2;
}
s32 func_15043AC8(s32 arg0, s32 arg1, s32 arg2, s32 *arg3, s32 arg4) {
    s32 count;

    if (arg4 != 0) {
        do {
            if (arg1 < arg2 + arg4) {
                count = arg1 - arg2;
            } else {
                count = arg4;
            }
            func_10022EC0(arg3, (u8 *)arg0 + arg2, count);
            arg2 += count;
            arg3 = (s32 *)((u8 *)arg3 + count);
            arg4 -= count;
            if (arg2 >= arg1) {
                arg2 = 0;
            }
        } while (arg4 != 0);
    }
    return arg2;
}
s32 func_15043B70(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_v0;

    if (arg3 != 0) {
        do {
            if (arg1 < (arg2 + arg3)) {
                var_v0 = arg1 - arg2;
            } else {
                var_v0 = arg3;
            }
            arg2 += var_v0;
            arg3 -= var_v0;
            if (arg2 >= arg1) {
                arg2 = 0;
            }
        } while (arg3 != 0);
    }
    return arg2;
}
s32 func_15043A20(s32, s32, s32, s32 *, s32);       /* extern */

s32 func_15043BB8(Game70200Entry *arg0, s32 *arg1, s32 arg2) {
    s32 position;
    s32 limit;

    if (arg2 != 0 && arg1 != 0) {
        arg2 += 4;
        arg2 = (arg2 + 3) & ~3;
        position = arg0->field_C;
        limit = arg0->field_8;
        if (position < limit) {
            if (position + arg2 >= limit) {
                return 1;
            }
        } else if (position + arg2 - arg0->field_4 >= limit) {
            return 1;
        }
        arg2 -= 4;
        arg0->field_C = func_15043A20(arg0->field_0, arg0->field_4,
            func_15043A20(arg0->field_0, arg0->field_4, position, &arg2, 4),
            arg1, arg2);
    }
    return 0;
}
s32 func_15043AC8(s32, s32, s32, s32 *, s32);       /* extern */

s32 func_15043CA4(Game70200Entry *arg0, u8 *arg1, s32 arg2) {
    s32 count[2];
    s32 position;
    s32 result;

    count[0] = 0;
    position = arg0->field_8;
    if (position == arg0->field_C) {
        return 0;
    }
    result = func_15043AC8(arg0->field_0, arg0->field_4, position, count, 4);
    if (arg2 < count[0]) {
        arg2 -= 1;
        result = func_15043AC8(arg0->field_0, arg0->field_4, result, (s32 *)arg1, arg2);
        arg1[arg2] = 0;
        result = func_15043B70(arg0->field_0, arg0->field_4, result, count[0] - arg2);
    } else if (count[0] != 0) {
        result = func_15043AC8(arg0->field_0, arg0->field_4, result, (s32 *)arg1, count[0]);
    }
    arg0->field_8 = result;
    return count[0];
}
