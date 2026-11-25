#include "types.h"
#include "game_effect_texture_data.h"

/* Evidence: docs/evidence/data-layout/us_effect_textures.md
 * Data-only reconstruction; grouping does not infer original object boundaries.
 */

extern u32 D_80090640[];

EffectTextureDescriptor D_80090660[5] = {
    { { &D_80090640[2] }, 2, 32, 32, 2, 0 },
    { { &D_80090640[0] }, 2, 32, 32, 2, 0 },
    { { &D_80090640[4] }, 2, 32, 32, 2, 0 },
    { { &D_80090640[6] }, 2, 32, 32, 2, 0 },
    { { (u32 *)7208 }, 1, 16, 64, 0, 3 },
};
