#include "types.h"
#include "game_effect_texture_data.h"

/* Evidence: docs/evidence/data-layout/us_effect_textures.md
 * Data-only reconstruction; grouping does not infer original object boundaries.
 */

extern u32 D_800906D0[];

EffectTextureDescriptor D_800906F8[3] = {
    { { &D_800906D0[0] }, 10, 64, 64, 4, 1 },
    { { (u32 *)7171 }, 1, 32, 32, 0, 3 },
    { { (u32 *)7170 }, 1, 16, 64, 0, 3 },
};
