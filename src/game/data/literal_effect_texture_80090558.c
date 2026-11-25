#include "types.h"
#include "game_effect_texture_data.h"

/* Evidence: docs/evidence/data-layout/us_literal_effect_data.md
 * Native selectors establish these extents; grouping does not infer original C objects.
 */

typedef struct {
    u32 frames[1];
    LiteralTextureDescriptor descriptor;
} LiteralTextureOne;

LiteralTextureOne D_80090558[5] = {
    { { 4167 }, { D_80090558[0].frames, 1, 64, 64, 3, 1 } },
    { { 4168 }, { D_80090558[1].frames, 1, 64, 64, 3, 1 } },
    { { 4169 }, { D_80090558[2].frames, 1, 16, 16, 3, 1 } },
    { { 4170 }, { D_80090558[3].frames, 1, 16, 16, 3, 1 } },
    { { 1204 }, { D_80090558[4].frames, 1, 16, 32, 3, 1 } },
};
