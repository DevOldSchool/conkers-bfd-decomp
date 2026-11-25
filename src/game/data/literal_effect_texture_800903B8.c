#include "types.h"
#include "game_effect_texture_data.h"

/* Evidence: docs/evidence/data-layout/us_literal_effect_data.md
 * Native selectors establish these extents; grouping does not infer original C objects.
 */

typedef struct {
    u32 frames[1];
    LiteralTextureDescriptor descriptor;
} LiteralTextureOne;

LiteralTextureOne D_800903B8[1] = {
    { { 1293 }, { D_800903B8[0].frames, 1, 32, 16, 0, 2 } },
};
