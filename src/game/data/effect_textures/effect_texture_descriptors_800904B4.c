#include "types.h"
#include "game_effect_texture_data.h"

/* Evidence: docs/evidence/data-layout/us_effect_textures.md
 * Data-only reconstruction; grouping does not infer original object boundaries.
 */

extern u32 D_800904A0[];

EffectTextureDescriptor D_800904B4[11] = {
    { { &D_800904A0[0] }, 5, 32, 32, 0, 3 },
    { { (u32 *)2826 }, 1, 16, 64, 0, 3 },
    { { (u32 *)2750 }, 1, 32, 16, 0, 3 },
    { { (u32 *)1665 }, 1, 16, 16, 0, 3 },
    { { (u32 *)2718 }, 1, 32, 32, 0, 3 },
    { { (u32 *)1196 }, 1, 32, 32, 0, 3 },
    { { (u32 *)4163 }, 1, 32, 32, 3, 1 },
    { { (u32 *)7728 }, 1, 32, 32, 0, 3 },
    { { (u32 *)2982 }, 1, 16, 16, 0, 3 },
    { { (u32 *)7211 }, 1, 16, 16, 0, 3 },
    { { (u32 *)1213 }, 1, 16, 16, 5, 2 },
};
