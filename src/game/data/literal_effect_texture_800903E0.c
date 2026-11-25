#include "types.h"
#include "game_effect_texture_data.h"

/* Evidence: docs/evidence/data-layout/us_literal_effect_data.md
 * Native selectors establish these extents; grouping does not infer original C objects.
 */

typedef struct {
    u32 frames[5];
    LiteralTextureDescriptor descriptor;
} LiteralTextureFive;

LiteralTextureFive D_800903E0 = {
    { 2320, 2321, 2322, 2323, 2324 },
    { D_800903E0.frames, 5, 32, 32, 0, 3 },
};
