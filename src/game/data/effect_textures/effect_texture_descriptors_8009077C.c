#include "types.h"
#include "game_effect_texture_data.h"

/* Evidence: docs/evidence/data-layout/us_effect_textures.md
 * Data-only reconstruction; grouping does not infer original object boundaries.
 */

extern u32 D_80090768[];

EffectTextureDescriptor D_8009077C[1] = {
    { { &D_80090768[0] }, 5, 32, 32, 0, 3 },
};
