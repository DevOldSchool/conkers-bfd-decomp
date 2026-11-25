#include "types.h"
#include "game_effect_texture_data.h"

/* Evidence: docs/evidence/data-layout/us_effect_textures.md
 * Data-only reconstruction; grouping does not infer original object boundaries.
 */

extern u32 D_80090358[];

EffectTextureDescriptor D_80090388[1] = {
    { { &D_80090358[0] }, 12, 44, 44, 0, 2 },
};
