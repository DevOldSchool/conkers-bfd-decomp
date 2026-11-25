#include "types.h"
#include "game_effect_texture_data.h"

/* Evidence: docs/evidence/data-layout/us_effect_textures.md
 * Data-only reconstruction; grouping does not infer original object boundaries.
 */

extern u32 D_80090788[];

EffectTextureDescriptor D_8009078C[2] = {
    { { &D_80090788[0] }, 1, 32, 32, 0, 3 },
    { { &D_80090788[0] }, 1, 32, 32, 0, 3 },
};
