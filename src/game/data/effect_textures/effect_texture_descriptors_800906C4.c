#include "types.h"
#include "game_effect_texture_data.h"

/* Evidence: docs/evidence/data-layout/us_effect_textures.md
 * Data-only reconstruction; grouping does not infer original object boundaries.
 */

extern u32 D_8009069C[];

EffectTextureDescriptor D_800906C4[1] = {
    { { &D_8009069C[0] }, 10, 16, 16, 4, 1 },
};
