#ifndef CONKER_GAME_EFFECT_TEXTURE_DATA_H
#define CONKER_GAME_EFFECT_TEXTURE_DATA_H

#include "types.h"

/* Effect texture descriptor records shared by the game data tables.
 * Promoted from identical copies in src/game/data effect texture sources.
 * Evidence: docs/evidence/data-layout/us_effect_textures.md and
 * us_literal_effect_data.md.
 */
typedef union {
    u32 *frames;
    u32 resource;
} EffectTextureStorage;

typedef struct {
    EffectTextureStorage storage;
    u8 frameCount;
    u16 width;
    u16 height;
    u8 format;
    u8 size;
} EffectTextureDescriptor;

typedef struct {
    u32 *frames;
    u8 storedCount;
    u16 width;
    u16 height;
    u8 format;
    u8 size;
} LiteralTextureDescriptor;

#endif
