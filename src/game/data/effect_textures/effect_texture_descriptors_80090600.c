#include "types.h"
#include "game_effect_texture_data.h"

/* Evidence: docs/evidence/data-layout/us_effect_textures.md
 * Data-only reconstruction; grouping does not infer original object boundaries.
 */

extern u32 D_800905FC[];

EffectTextureDescriptor D_80090600[1] = {
    { { &D_800905FC[0] }, 1, 32, 32, 0, 2 },
};
