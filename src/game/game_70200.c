#include "types.h"

/*
 * Reviewed source unit: src/game/game_70200.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 * HUD layout naming evidence: docs/evidence/hud_layout_semantics.md
 * Ring helper evidence: docs/evidence/naming/record_ring_helper_semantics.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15043384
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

/* Keep address symbols for linking and registered match evidence. */
#define hud_set_layout_flags func_15042D78
#define hud_queue_layout_at func_15042D94
#define hud_queue_layout_at_current_position func_15042E3C
#define hud_parse_and_queue_layout func_15042ECC
#define hud_set_layout_scale func_150432BC
#define hud_attach_layout_to_object func_150432CC
#define hud_set_layout_position func_150432FC
#define hud_set_primary_rgba func_1504332C
#define record_ring_init func_15043A00
#define record_ring_copy_in func_15043A20
#define record_ring_copy_out func_15043AC8
#define record_ring_advance func_15043B70
#define record_ring_write func_15043BB8

typedef u8 *Game70200VaList;
#define GAME70200_VA_START(ap, last) ((ap) = (u8 *)&(last) + sizeof(last))
#define GAME70200_VA_ARG(ap, type) (*(((type *)((ap) = (u8 *)((((s32)(ap) + 3) & ~3) + sizeof(type)))) - 1))
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
void hud_parse_and_queue_layout();

/* hud_set_layout_flags: set raw flags for subsequently queued layout nodes. */
void hud_set_layout_flags(u8 flagsRaw) {
    D_800CBD74 = flagsRaw;
}
/* hud_queue_layout_at: set position/flags and pass sixteen argument words to the parser. */
void hud_queue_layout_at(s32 x, s32 y, u8 flagsRaw, s32 format, ...) {
    Game70200VaList args;
    s32 argumentWords[16];
    s32 argumentIndex;

    D_800CBD74 = flagsRaw;
    D_800CBD70 = x;
    D_800CBD72 = y;
    GAME70200_VA_START(args, format);
    for (argumentIndex = 0; argumentIndex < 16; argumentIndex++) {
        argumentWords[argumentIndex] = GAME70200_VA_ARG(args, s32);
    }
    GAME70200_VA_END(args);
    hud_parse_and_queue_layout(format, argumentWords);
}

/* hud_queue_layout_at_current_position: pass sixteen argument words to the parser. */
void hud_queue_layout_at_current_position(s32 format, ...) {
    Game70200VaList args;
    s32 argumentWords[16];
    s32 argumentIndex;

    GAME70200_VA_START(args, format);
    for (argumentIndex = 0; argumentIndex < 16; argumentIndex++) {
        argumentWords[argumentIndex] = GAME70200_VA_ARG(args, s32);
    }
    GAME70200_VA_END(args);
    hud_parse_and_queue_layout(format, argumentWords);
}

typedef struct Game70200Anchor {
    u8 pad0[0x14];
    f32 x;
    f32 y;
    f32 z;
} Game70200Anchor;

/* 0x5C-byte queued layout node; field_12..field_15 remain unresolved. */
typedef struct Game70200TextNode {
    Game70200Anchor *attachedObject;
    f32 scale;
    s16 x;
    s16 yOrVerticalOffset;
    u8 flagsRaw;
    u8 kindSelector;
    u8 primaryRed;
    u8 primaryGreen;
    u8 primaryBlue;
    u8 primaryAlpha;
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

/* hud_parse_and_queue_layout: append text or 1-based HUD sprite-selector nodes. */
void hud_parse_and_queue_layout(u8 *format, s32 *argumentWords) {
    struct {
        Game70200TextNode *node;
        s32 pad;
        s32 finished;
        s32 pad2;
    } local;
    Game70200TextNode *node;
    u8 *out;
    s32 argumentIndex;
    s32 conversionIndex;
    u8 ch;
    u8 flags;
    u8 *conversion;

    argumentIndex = 0;
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
        local.node->kindSelector = 0;
        do {
            ch = *format;
            if (ch == '%') {
                format++;
                *conversion = '%';
                for (conversionIndex = 1; conversionIndex != 0; conversionIndex++, format++) {
                    u8 *destination = &(&D_80085CC4)[conversionIndex];

                    destination[0] = *format;
                    destination[1] = 0;
                    switch (destination[0]) {
                    case 'X':
                    case 'd':
                    case 'x':
                        func_151EFF94(out, &D_80085CC4,
                                     argumentWords[argumentIndex++]);
                        while (*out != 0) {
                            out++;
                        }
                        conversionIndex = -1;
                        break;
                    case 'F':
                    case 'f': {
                        f32 *number = (f32 *)argumentWords[argumentIndex++];
                        f32 value = *number;

                        func_151EFF94(out, D_80085CC0, &D_80098B90,
                                     &D_80098B94,
                                     (f64)value);
                        while (*out != 0) {
                            out++;
                        }
                        conversionIndex = -1;
                        break;
                    }
                    case 's':
                        func_151EFF94(out, &D_80085CC4,
                                     argumentWords[argumentIndex++]);
                        while (*out != 0) {
                            out++;
                        }
                        conversionIndex = -1;
                        break;
                    case '%':
                        *out++ = *format;
                        *out = 0;
                        conversionIndex = -1;
                        break;
                    default:
                        break;
                    }
                }
            } else if (ch == '#') {
                local.node->kindSelector = argumentWords[argumentIndex++];
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
        node->flagsRaw = D_800CBD74;
        node->attachedObject = (Game70200Anchor *)D_800CBD78;
        if (node->attachedObject != 0) {
            node->yOrVerticalOffset = D_800CBD7C;
            flags = node->flagsRaw | 1;
            node->flagsRaw = (node->flagsRaw = flags);
            if (D_8008FD90 >= 2) {
                node->scale = D_800CBD80 + D_800CBD80;
            } else {
                node->scale = D_800CBD80;
            }
        } else {
            node->x = D_800CBD70;
            node->yOrVerticalOffset = D_800CBD72;
            node->scale = D_800CBD80;
        }
        node->primaryRed = D_800CBD60;
        node->primaryGreen = D_800CBD61;
        node->primaryBlue = D_800CBD62;
        node->primaryAlpha = D_800CBD63;
        node->field_12 = D_800CBD6C;
        node->field_13 = D_800CBD6D;
        node->field_14 = D_800CBD6E;
        node->field_15 = D_800CBD6F;
        D_800CBD68 = node;
        if (node->kindSelector != 0) {
            node->primaryRed = 0xFF;
            node->primaryGreen = 0xFF;
            node->primaryBlue = 0xFF;
        } else {
            D_800CBD72 += 0xB;
        }
    }
    D_800CBD78 = 0;
}
extern f32 D_800CBD80;

/* hud_set_layout_scale: set scale for subsequently queued layout nodes. */
void hud_set_layout_scale(f32 scale) {
    D_800CBD80 = scale;
}
extern s32 D_800CBD78;
extern s16 D_800CBD7C;

/* hud_attach_layout_to_object: set the object and pre-projection vertical offset. */
void hud_attach_layout_to_object(s32 attachedObject, s32 verticalOffset) {
    D_800CBD74 = (D_800CBD74 |= 1);
    D_800CBD7C = verticalOffset;
    D_800CBD78 = attachedObject;
}
/* hud_set_layout_position: set X/Y for subsequently queued screen layout nodes. */
void hud_set_layout_position(s16 x, s16 y) {
    D_800CBD70 = x;
    D_800CBD72 = y;
}
extern u8 D_800CBD60;
extern u8 D_800CBD61;
extern u8 D_800CBD62;
extern u8 D_800CBD63;

/* hud_set_primary_rgba: set primary color bytes for subsequently queued nodes. */
void hud_set_primary_rgba(u8 red, u8 green, u8 blue, u8 alpha) {
    D_800CBD60 = red;
    D_800CBD61 = green;
    D_800CBD62 = blue;
    D_800CBD63 = alpha;
}
/* Partial renderer descriptor; field_4 remains unresolved. */
typedef struct Game70200TextureInfo {
    s32 flatAssetIndex;
    s16 field_4;
    s16 tileWidth;
    s16 tileHeight;
} Game70200TextureInfo;

void func_10004074(s32);
s32 func_10022EEC(void *);
void *func_150417AC(void *, f32, f32, void *, s32, s32, s32, s32, f32, f32, s32);
void func_150428D4(void *, s32 *, s32 *, s32 *);
s32 func_1509563C(f32, f32, f32, f32 *, f32 *, f32 *, f32 *, f32);
void *func_151ED430(void *, Game70200TextureInfo *, s16, s16, s32, s32, f32, s32);
extern s32 D_80082FA4;
extern u8 D_800859A0[];
/* Eight-byte HUD selector metadata at D_800859E0; scaleByte is divided by 128. */
typedef struct Game70200Effect {
    u8 tileColumns;
    u8 tileRows;
    u8 scaleByte;
    u8 flagsRaw;
    s32 flatAssetIndex;
} Game70200Effect;
extern Game70200Effect D_800859E0[];
extern Game70200Effect D_80085AA8;
extern s32 D_80085CD0;
extern f32 D_8008FE1C;
extern f32 D_8008FE20;
extern f32 D_80098C64;
extern s32 D_800BE9AC;
extern Game70200TextureInfo D_80090060;

#define GAME70200_COMMAND(p, first, second) do { Game70200Command *command = (p)++; command->words.w0 = (u32)(first); command->words.w1 = (u32)(second); } while (0)

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
                if (text->kindSelector == 0) {
                    visible = 1;
                    extra_pass = 0;
                    if (text->flagsRaw & 0x40) {
                        text->flagsRaw &= ~0x40;
                    } else {
                        text->x = (s32)((f32)text->x * D_8008FE1C);
                        text->yOrVerticalOffset = (s32)((f32)text->yOrVerticalOffset * D_8008FE20);
                    }
                    if (text->flagsRaw & 0x80) {
                        extra_pass = 1;
                        text->flagsRaw &= ~0x80;
                    }
                    base = (s32)text->attachedObject;
                    if (base != 0) {
                        D_80082FA4 = 0;
                        visible = func_1509563C(
                            ((Game70200Anchor *)base)->x,
                            ((Game70200Anchor *)base)->y + (f32)text->yOrVerticalOffset,
                            ((Game70200Anchor *)base)->z,
                            &projected_x, &projected_y,
                            &projected_z, &projected_w,
                            D_80098C64);
                        if (visible != 0) {
                            text->x = (s32)projected_x;
                            text->yOrVerticalOffset = (s32)projected_y;
                        }
                    }
                    if ((text->flagsRaw == 1) || (text->field_15 != 0)) {
                        func_150428D4(text->text, &width,
                                      &unused1, &unused2);
                        width = (s32)((f32)width * text->scale);
                    }
                    if (text->flagsRaw == 1) {
                        text->x -= width >> 1;
                    }
                    if (visible != 0) {
                        scale = text->scale * 4096.0f;
                        if (extra_pass != 0) {
                            dl = func_150417AC(dl,
                                (f32)(text->x + 1), (f32)(text->yOrVerticalOffset + 1), text->text,
                                0, 0, 0, text->primaryAlpha, scale, scale,
                                func_10022EEC(text->text));
                        }
                        dl = func_150417AC(dl,
                            (f32)text->x, (f32)text->yOrVerticalOffset, text->text,
                            text->primaryRed, text->primaryGreen, text->primaryBlue, text->primaryAlpha,
                            scale, scale, func_10022EEC(text->text));
                    }
                    GAME70200_COMMAND(dl, 0xE7000000, 0);
                } else {
                    pulse = text->kindSelector - 1;
                    effect = &D_800859E0[pulse];
                    scale = (f32)effect->scaleByte * 0.0078125f;
                    GAME70200_COMMAND(dl, 0xFC12D225, 0xFFA7FFFF);
                    base = effect->flagsRaw;
                    if (base & 2) {
                        D_80090060.tileWidth = 0x10;
                        D_80090060.tileHeight = 0x10;
                    }
                    if (base & 1) {
                        GAME70200_COMMAND(dl, 0xE7000000, 0);
                        GAME70200_COMMAND(dl, 0xFB000000, (text->primaryRed << 24) | (text->primaryGreen << 16) |
                                (text->primaryBlue << 8) | text->primaryAlpha);
                        D_80090060.flatAssetIndex = effect[-1].flatAssetIndex;
                        dl = func_151ED430(dl, &D_80090060, text->x, text->yOrVerticalOffset,
                                          effect[-1].tileColumns, effect[-1].tileRows, scale, 0);
                        pulse = (D_800BE9AC * 2) & 0x7F;
                        if (pulse >= 0x40) {
                            pulse = 0x7F - pulse;
                        }
                        alpha = (s32)(text->primaryAlpha * ((pulse + pulse + pulse) + 0x3F)) >> 8;
                        if (alpha >= 0x100) {
                            alpha = 0xFF;
                        }
                        text->primaryAlpha = alpha;
                    }
                    GAME70200_COMMAND(dl, 0xE7000000, 0);
                    GAME70200_COMMAND(dl, 0xFB000000, (text->primaryRed << 24) | (text->primaryGreen << 16) |
                            (text->primaryBlue << 8) | text->primaryAlpha);
                    base = effect->flatAssetIndex;
                    D_80090060.flatAssetIndex = base;
                    if (effect == &D_80085AA8) {
                        pulse = (D_80085CD0 >> 1) % 10;
                        if (pulse >= 6) {
                            pulse = 10 - pulse;
                        }
                        D_80090060.flatAssetIndex = base + pulse;
                    }
                    dl = func_151ED430(dl, &D_80090060, text->x, text->yOrVerticalOffset,
                                      effect->tileColumns, effect->tileRows, scale, 0);
                    GAME70200_COMMAND(dl, 0xDE000000, (s32)D_800859A0);
        GAME70200_COMMAND(dl, 0xEF002C3F, 0x00504240);
                    if (effect->flagsRaw & 2) {
                        D_80090060.tileWidth = 0x20;
                        D_80090060.tileHeight = 0x20;
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

void record_ring_init(Game70200Entry *arg0, s32 arg1, s32 arg2) {
    if (arg0) {
        arg0->field_0 = arg1;
        arg0->field_4 = arg2;
        arg0->field_C = 0;
        arg0->field_8 = 0;
    }
}
s32 record_ring_copy_in(s32 arg0, s32 arg1, s32 arg2, s32 *arg3, s32 arg4) {
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
s32 record_ring_copy_out(s32 arg0, s32 arg1, s32 arg2, s32 *arg3, s32 arg4) {
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
s32 record_ring_advance(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
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
s32 record_ring_copy_in(s32, s32, s32, s32 *, s32);       /* extern */

s32 record_ring_write(Game70200Entry *arg0, s32 *arg1, s32 arg2) {
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
        arg0->field_C = record_ring_copy_in(arg0->field_0, arg0->field_4,
            record_ring_copy_in(arg0->field_0, arg0->field_4, position, &arg2, 4),
            arg1, arg2);
    }
    return 0;
}
s32 record_ring_copy_out(s32, s32, s32, s32 *, s32);       /* extern */

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
