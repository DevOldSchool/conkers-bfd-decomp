#include "types.h"
#include "game_effect_texture_data.h"

/* Evidence: docs/evidence/data-layout/us_effect_textures.md
 * Data-only reconstruction; grouping does not infer original object boundaries.
 */

extern u32 D_8009071C[];

EffectTextureDescriptor D_80090730[1] = {
    { { &D_8009071C[0] }, 5, 32, 32, 0, 3 },
};
