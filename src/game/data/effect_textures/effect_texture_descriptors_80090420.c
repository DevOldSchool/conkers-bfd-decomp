#include "types.h"
#include "game_effect_texture_data.h"

/* Evidence: docs/evidence/data-layout/us_effect_textures.md
 * Data-only reconstruction; grouping does not infer original object boundaries.
 */

EffectTextureDescriptor D_80090420[8] = {
    { { (u32 *)1327 }, 1, 16, 16, 3, 1 },
    { { (u32 *)2821 }, 1, 32, 32, 0, 3 },
    { { (u32 *)2822 }, 1, 32, 32, 0, 3 },
    { { (u32 *)2823 }, 1, 32, 32, 0, 3 },
    { { (u32 *)4604 }, 1, 64, 16, 0, 3 },
    { { (u32 *)4606 }, 1, 64, 16, 0, 3 },
    { { (u32 *)4605 }, 1, 64, 16, 0, 3 },
    { { (u32 *)4189 }, 1, 16, 64, 0, 3 },
};
