#include "types.h"
#include "game_effect_texture_data.h"

/* Evidence: docs/evidence/data-layout/us_effect_textures.md
 * Data-only reconstruction; grouping does not infer original object boundaries.
 */

extern u32 D_80090480[];

EffectTextureDescriptor D_80090494[1] = {
    { { &D_80090480[0] }, 5, 32, 32, 0, 3 },
};
